/***************************************************************************
                          uitransferpage.cpp  -  description
                             -------------------
    begin                : Wed Mar 7 2001
    copyright            : (C) 2001 by Ian Zepp
    email                : iszepp@bulldog.unca.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "iomessage.h"
#include "ionapstercodes.h"
#include "ionapstertransfer.h"
#include "iosupport.h"

#include "uiconfig.h"
#include "uipagemenu.h"
#include "uipageview.h"
#include "uitransferpage.h"

/***************************************************************************/

UITransferPage::UITransferPage(QWidget *parent, const char *name )
             :UIPage(parent,name)
{
        //
        // m_menu
        //

        m_menu = new UIPageMenu( this );
        m_menu->removeItem( UIPageMenu::Id_Download );
        m_menu->removeItem( UIPageMenu::Id_Audio );
        m_menu->removeItem( UIPageMenu::Id_File );
        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Select ) - 1 );

        //
        // m_view
        //

        m_view = new UIPageView( this );
        m_view->setColumnVisible( UIPageView::Col_Freq, false );
        m_view->setColumnVisible( UIPageView::Col_Time, false );
        m_view->setColumnVisible( UIPageView::Col_Rate, true  );
        m_view->initColumnMenu( m_menu );

        connect( m_view, SIGNAL(clicked(QListViewItem *)),
                 this, SLOT(slot_ViewClicked(QListViewItem *)) );
        connect( m_view, SIGNAL(executed(QListViewItem *)),
                 this, SLOT(slot_ViewExecuted(QListViewItem *)) );
        connect( m_view, SIGNAL(contextMenu(QListViewItem *, const QPoint &)),
                 this, SLOT(slot_ViewMenu(QListViewItem *, const QPoint &)) );

        //
        // other data
        //

        m_recv_cnt = 0;
        m_send_cnt = 0;
        m_xfers = new TransferDict();
        m_items = new ItemDict();

        //
        // title
        //

        updateTitle();

        //
        // page
        //

        layout()->setStretchFactor( m_view, 10 );
}
UITransferPage::~UITransferPage()
{
        delete m_xfers;
        delete m_items;
}

void UITransferPage::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::DownloadRequest:
                recvIO_DownloadRequest( io );
                break;
        case IONapsterCodes::DownloadReply:
                recvIO_DownloadReply( io );
                break;
        case IONapsterCodes::DownloadError:
                recvIO_DownloadError( io );
                break;
        }

        emit recvIO( io );
}

void UITransferPage::recvIO_DownloadRequest( IOMessage * io )
{
        //
        // config checks
        //

        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
        c->setGroup( "Options - Transfer" );

        //
        // base download directory
        //

        QString base_path = c->readEntry( "recv_path" );

        if ( base_path.isEmpty() == true )
        {
                QMessageBox::information( this, tr( "Invalid settings" ),
                        tr( "No download directory set. Check your settings." ),
                        QMessageBox::Ok );
                return;
        }

        //
        // dir exists?
        //

        QDir base_dir( base_path );

        if ( base_dir.exists() == false )
        {
                QMessageBox::information( this, tr( "Invalid settings" ),
                        tr( "Directory does not exist: %1\n"
                            "Check your settings." ).arg( base_path ),
                        QMessageBox::Ok );
                return;
        }

        //
        // temp download dir
        //

        QString temp_path = base_dir.absFilePath( "incomplete" );
        QDir    temp_dir( temp_path );

        if ( temp_dir.exists() == false )
        {
                if ( base_dir.mkdir( "incomplete" ) == false )
                {
                        QMessageBox::information( this, tr( "Operation not allowed" ),
                                tr( "Unable to create temp directory: %1\n"
                                    "Check your settings." ).arg( temp_path ),
                                QMessageBox::Ok );
                        return;
                }

                QMessageBox::information( this, tr( "Directory created" ),
                        tr( "Created temp directory: %1" ).arg( temp_path ),
                        QMessageBox::Ok );
        }

        //
        // file exists as temp download ?
        //

        QFile temp_file( temp_dir.absFilePath( io->find( "name" ) ) );

        if ( temp_file.exists() == true )
        {
                int response = QMessageBox::information( this,
                        tr( "Overwriting file" ),
                        tr( "Overwriting temp download file: %1\n"
                            "Do you really want to do this?"
                          ).arg( temp_path ),
                        QMessageBox::Ok );

                if ( response == QMessageBox::No )
                        return ;
        }

        //
        // file exists as real file ?
        //

        QFile base_file( base_dir.absFilePath( io->find( "name" ) ) );

        if ( base_file.exists() == true )
        {
                int response = QMessageBox::information( this,
                        tr( "Overwriting file" ),
                        tr( "Overwriting existing file: %1\n"
                            "Do you really want to do this?"
                          ).arg( temp_path ),
                        QMessageBox::Yes, QMessageBox::No );

                if ( response == QMessageBox::No )
                        return ;
        }

        c->setGroup( "Options - User" );
        QString local_nick = c->readEntry( "nick" );

        incrementTransferID();

        //
        // item
        //

        QListViewItem * parent = findItem( tr( "Connecting" ) );

        QListViewItem * item = new QListViewItem( parent );
        item->setText( UIPageView::Col_Name, io->find( "name" ) );
        item->setText( UIPageView::Col_Link, io->find( "speed" ) );
        item->setText( UIPageView::Col_Bitr, io->find( "bitrate" ) );
        item->setText( UIPageView::Col_Freq, io->find( "freq" ) );
        item->setText( UIPageView::Col_Time, io->find( "time" ) );
        item->setText( UIPageView::Col_Nick, io->find( "nick" ) );
        item->setText( UIPageView::Col_Path, io->find( "path" ) );
        item->setText( UIPageView::Col_Host, io->find( "host" ) );
        item->setText( UIPageView::Col_Guid, currentTransferIDString() );
        item->setText( UIPageView::Col_Size, tr( "requesting from server" ) );

        //
        // xfer
        //

        IONapsterTransfer * xfer = new IONapsterTransfer( this );
        xfer->setConnectionID( currentTransferID() );
        xfer->setLocalUser( local_nick );
        xfer->setLocalFile( temp_dir.absFilePath( io->find( "name" ) ) );
        xfer->setRemoteUser( io->find( "nick" ) );
        xfer->setRemoteFile( io->find( "path" ) );
        xfer->setUploadTransfer( false );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 xfer, SLOT(recvIOEvent(IOMessage *)) );
        connect( xfer, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );
        connect( xfer, SIGNAL(updateAvailable(Q_INT32)),
                 this, SLOT(updateItemEvent(Q_INT32)) );

        m_xfers->insert( currentTransferIDString(), xfer );
}

void UITransferPage::recvIO_DownloadReply( IOMessage * io )
{
        QListViewItemIterator it( m_view );
        QListViewItem * item = 0;
        QString         snum = "";

        for ( ; it.current(); ++it )
        {
                if ( io->find( "nick" ) != it.current()->text( UIPageView::Col_Nick ) )
                        continue ;
                if ( io->find( "path" ) != it.current()->text( UIPageView::Col_Path ) )
                        continue ;

                item = it.current();
                snum = item->text( UIPageView::Col_Guid );
                break;
        }

        if ( item == 0 )
                return ;
        if ( snum.isEmpty() )
                return ;

        //
        // connect
        //

        IONapsterTransfer * xfer = m_xfers->find( snum );

        if ( xfer == 0 )
                return ; // ???

        QString  host = io->find( "host" );
        Q_UINT16 port = io->find( "port" ).toUInt();

        item->setText( UIPageView::Col_Size, tr( "server accepted, connecting" ) );
        xfer->connectToHost( host, port );
}

void UITransferPage::recvIO_DownloadError( IOMessage * io )
{
        QListViewItemIterator it( m_view );
        QListViewItem * item = 0;
        QString         snum = "";

        for ( ; it.current(); ++it )
        {
                if ( io->find( "nick" ) != it.current()->text( UIPageView::Col_Nick ) )
                        continue ;
                if ( io->find( "path" ) != it.current()->text( UIPageView::Col_Path ) )
                        continue ;

                item = it.current();
                snum = item->text( UIPageView::Col_Guid );
                break;
        }

        if ( item == 0 )
                return ;
        if ( snum.isEmpty() )
                return ;

        IONapsterTransfer * xfer = m_xfers->find( snum );

        if ( xfer == 0 )
                return ; // ???

        item->setText( UIPageView::Col_Size, tr( "server refused transfer" ) );
        xfer->setTransferState( IONapsterTransfer::Error );
}

void UITransferPage::slot_ViewClicked( QListViewItem * )
{
}

void UITransferPage::slot_ViewExecuted( QListViewItem * )
{
}

void UITransferPage::slot_ViewMenu( QListViewItem * , const QPoint & point )
{
        int id = m_menu->exec( point );

        switch ( id )
        {
        case UIPageMenu::Id_Browse:
                menu_Browse();
                break;
        case UIPageMenu::Id_Message:
                menu_Message();
                break;
        case UIPageMenu::Id_Cancel:
                menu_Cancel();
                break;
        case UIPageMenu::Id_Select:
                menu_Select();
                break;

        case UIPageMenu::Id_Sort_Name:
                menu_Sort( UIPageView::Col_Name, id );
                break;
        case UIPageMenu::Id_Sort_Bitr:
                menu_Sort( UIPageView::Col_Bitr, id );
                break;
        case UIPageMenu::Id_Sort_Size:
                menu_Sort( UIPageView::Col_Size, id );
                break;
        case UIPageMenu::Id_Sort_Time:
                menu_Sort( UIPageView::Col_Time, id );
                break;
        case UIPageMenu::Id_Sort_Freq:
                menu_Sort( UIPageView::Col_Freq, id );
                break;
        case UIPageMenu::Id_Sort_Nick:
                menu_Sort( UIPageView::Col_Nick, id );
                break;

        case UIPageMenu::Id_Copy_Name:
                menu_Copy( UIPageView::Col_Name );
                break;
        case UIPageMenu::Id_Copy_Nick:
                menu_Copy( UIPageView::Col_Nick );
                break;
        case UIPageMenu::Id_Copy_Path:
                menu_Copy( UIPageView::Col_Path );
                break;
        case UIPageMenu::Id_Copy_Host:
                menu_Copy( UIPageView::Col_Host );
                break;

        case UIPageMenu::Id_Col_Name:
                menu_Column( UIPageView::Col_Name, id );
                break;
        case UIPageMenu::Id_Col_Bitr:
                menu_Column( UIPageView::Col_Bitr, id );
                break;
        case UIPageMenu::Id_Col_Size:
                menu_Column( UIPageView::Col_Size, id );
                break;
        case UIPageMenu::Id_Col_Rate:
                menu_Column( UIPageView::Col_Rate, id );
                break;
        case UIPageMenu::Id_Col_Time:
                menu_Column( UIPageView::Col_Time, id );
                break;
        case UIPageMenu::Id_Col_Freq:
                menu_Column( UIPageView::Col_Freq, id );
                break;
        case UIPageMenu::Id_Col_Link:
                menu_Column( UIPageView::Col_Link, id );
                break;
        case UIPageMenu::Id_Col_Nick:
                menu_Column( UIPageView::Col_Nick, id );
                break;
        case UIPageMenu::Id_Col_Ping:
                menu_Column( UIPageView::Col_Ping, id );
                break;
        case UIPageMenu::Id_Col_Path:
                menu_Column( UIPageView::Col_Path, id );
                break;
        case UIPageMenu::Id_Col_Host:
                menu_Column( UIPageView::Col_Host, id );
                break;
        }
}

void UITransferPage::menu_Message()
{
}

void UITransferPage::menu_Select()
{
        m_view->selectItemsDialog();
}

void UITransferPage::menu_Cleanup()
{
        m_view->firstChild();

        QListViewItemIterator it( m_view );
        QListViewItem           * item;
        IONapsterTransfer       * xfer;
        QString name;

        for ( ; it.current(); ++it )
        {
                item = it.current();
                name = item->text( UIPageView::Col_Guid );

                if ( name.isEmpty() )
                        continue ;

                xfer = m_xfers->find( name );

                if ( xfer == 0 )
                        continue;

                switch ( xfer->transferState() )
                {
                case IONapsterTransfer::Success:
                case IONapsterTransfer::Error:
                case IONapsterTransfer::Cancelled:
                        break;
                default:
                        continue;
                }

                m_xfers->remove( name );
                delete xfer;
                delete item;
        }

        // for good luck
        cleanupItems();
        cleanupItems();
}

void UITransferPage::menu_Cancel()
{
        // set current item as first item
        m_view->firstChild();

        //
        // run through items
        //

        QListViewItemIterator it( m_view );
        QListViewItem * item = 0;

        for ( ; it.current(); ++it )
        {
                item = it.current();

                if ( item->isSelected() == false )
                        continue ;

                QString snum = item->text( UIPageView::Col_Guid );

                if ( snum.isEmpty() )
                        continue ;

                IONapsterTransfer * xfer = m_xfers->find( snum );

                if ( xfer == 0 )
                        continue ;

                xfer->close();
                xfer->setTransferState( IONapsterTransfer::Cancelled );

                updateItemEvent( xfer->connectionID() );
        }
}

void UITransferPage::menu_Browse()
{
        QList<QListViewItem> list = m_view->selectedItems();
        QListViewItem * item;
        QString path;

        for ( item = list.first(); item != 0; item = list.next() )
        {
                path = item->text( UIPageView::Col_Path );

                if ( path.isEmpty() )
                        return ;

                IOMessage * io = new IOMessage( 0 );
                io->setMessageType( IONapsterCodes::BrowseRequest );
                io->insert( "nick",     item->text( UIPageView::Col_Nick ) );
                io->insert( "path",     item->text( UIPageView::Col_Path ) );
                io->insert( "name",     item->text( UIPageView::Col_Name ) );
                io->insert( "speed",    item->text( UIPageView::Col_Link ) );
                io->insert( "bitrate",  item->text( UIPageView::Col_Bitr ) );
                io->insert( "host",     item->text( UIPageView::Col_Host ) );
                io->insert( "time",     item->text( UIPageView::Col_Time ) );
                io->insert( "size",     item->text( UIPageView::Col_Size ) );
                io->insert( "freq",     item->text( UIPageView::Col_Freq ) );
                emit sendIO( io );

                delete io;
        }
}
void UITransferPage::menu_Copy( int col_id )
{
        QListViewItem * item = m_view->currentItem();

        if ( item == 0 )
                return ;

        QApplication::clipboard()->setText( item->text( col_id ) );
}

void UITransferPage::menu_Sort( int col_id, int menu_id )
{
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Name, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Bitr, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Size, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Time, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Nick, false );
        m_menu->setItemChecked( menu_id, true );

        m_view->setSorting( col_id, true );
        m_view->triggerUpdate();
}

void UITransferPage::menu_Column( int col_id, int menu_id )
{
        bool visible = ( ! m_view->columnVisible( col_id ) );

        m_menu->setItemChecked( menu_id, visible );
        m_view->setColumnVisible( col_id, visible );
        m_view->triggerUpdate();
}

void UITransferPage::updateTitle()
{
        QString text = tr( "Transfers: %1 download(s), %2 upload(s)" );
        text = text.arg( currentRecvCountString() );
        text = text.arg( currentSendCountString() );
        title()->setText( text );
}

void UITransferPage::updateItemEvent( Q_INT32 num )
{
        QString snum = QString::number( num );

        IONapsterTransfer * xfer = m_xfers->find( snum );

        if ( xfer == 0 )
                return ; // ???

        QListViewItemIterator it( m_view );
        QListViewItem * item = 0;

        for ( ; it.current(); ++it )
        {
                if ( it.current()->text( UIPageView::Col_Guid ) != snum )
                        continue;

                item = it.current();
                break;
        }

        if ( item == 0 )
                return ; // ???

        //
        // pick the transfer state
        //

        QString temp;
        QListViewItem * from = item->QListViewItem::parent();
        QListViewItem * next = 0;

        switch ( xfer->transferState() )
        {
        case IONapsterTransfer::Offline:
                item->setText( UIPageView::Col_Size, tr( "resolving hostname" ) );
                next = findItem( tr( "Connecting" ) );
                next->setPixmap( UIPageView::Col_Name,
                        m_icons.loadIcon( "connect_creating.png" , KIcon::Small ) );
                break;
        case IONapsterTransfer::HostFound:
                item->setText( UIPageView::Col_Size, tr( "connecting to client" ) );
                next = findItem( tr( "Connecting" ) );
                next->setPixmap( UIPageView::Col_Name,
                        m_icons.loadIcon( "connect_creating.png" , KIcon::Small ) );
                break;
        case IONapsterTransfer::Login:
                item->setText( UIPageView::Col_Size, tr( "transferring login" ) );
                next = findItem( tr( "Login and setup" ) );
                break;
        case IONapsterTransfer::Command:
                item->setText( UIPageView::Col_Size, tr( "transferring command" ) );
                next = findItem( tr( "Login and setup" ) );
                break;
        case IONapsterTransfer::Name:
                item->setText( UIPageView::Col_Size, tr( "transferring file name" ) );
                next = findItem( tr( "Login and setup" ) );
                break;
        case IONapsterTransfer::Size:
                item->setText( UIPageView::Col_Size, tr( "transferring file size" ) );
                next = findItem( tr( "Login and setup" ) );
                break;
        case IONapsterTransfer::Block:
                temp = tr( "%1% @ %2 bytes" );
                temp = temp.arg( xfer->transferPercentString() );
                temp = temp.arg( xfer->totalTransferBytesString() );
                item->setText( UIPageView::Col_Size, temp );

                temp = tr( "%1 kbps" );
                temp = temp.arg( xfer->transferRateString() );
                item->setText( UIPageView::Col_Rate, temp );

                next = findItem( tr( "Transferring" ) );
                break;

        //
        // these three cases also delete the transfer
        //

        case IONapsterTransfer::Success:
                item->setText( UIPageView::Col_Size, tr( "finished successfully" ) );
                next = findItem( tr( "Successfull" ) );
                break;
        case IONapsterTransfer::Error:
                item->setText( UIPageView::Col_Size, tr( "transfer error!" ) );
                next = findItem( tr( "Errors" ) );
                break;
        case IONapsterTransfer::Cancelled:
                item->setText( UIPageView::Col_Size, tr( "transfer cancelled" ) );
                next = findItem( tr( "Errors" ) );
                break;

        //
        // what the fuck here?
        //

        default:
                item->setText( UIPageView::Col_Size, tr( "unknown status" ) );
                break;
        }

        //
        // reparent ?
        //

        if ( next != 0 && next != from )
        {
                if ( from != 0 )
                        from->takeItem( item );
                next->insertItem( item );
        }

        //
        // resize ?
        //

        cleanupItems();
        m_view->triggerUpdate();
}

QListViewItem * UITransferPage::findItem( const QString & name, bool create )
{
        QListViewItem * item = m_items->find( name );

        if ( item == 0 && create )
        {
                item = new QListViewItem( m_view );
                item->setText( UIPageView::Col_Name, name );
                item->setOpen( true );

                m_items->insert( name, item );
        }

        return item;
}

void UITransferPage::removeItem( QListViewItem * item )
{
        if ( item == 0 )
                return ;

        m_items->remove( item->text( UIPageView::Col_Name ) );
        delete item;
}


void UITransferPage::cleanupItems()
{
        m_view->firstChild();

        ItemDictIterator it( *m_items );

        for ( ; it.current(); ++it )
        {
                if ( it.current()->firstChild() == 0 )
                        removeItem( it.current() );
        }
}

