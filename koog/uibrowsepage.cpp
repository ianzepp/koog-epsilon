/***************************************************************************
                          uibrowsepage.cpp  -  description
                             -------------------
    begin                : Thu Mar 8 2001
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
#include "iosupport.h"

#include "uibrowsepage.h"
#include "uipagemenu.h"
#include "uipageview.h"

/***************************************************************************/

UIBrowsePage::UIBrowsePage(QWidget *parent, const char *name )
             :UIPage(parent,name)
{
        //
        // menu
        //

        m_menu = new UIPageMenu( this, name );
        m_menu->removeItem( UIPageMenu::Id_Cleanup );
        m_menu->removeItem( UIPageMenu::Id_Browse );
        m_menu->removeItem( UIPageMenu::Id_Audio );
        m_menu->removeItem( UIPageMenu::Id_File );
        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Select ) - 1 );
        m_menu->removeItem( UIPageMenu::Id_Col_Rate );
        m_menu->removeItem( UIPageMenu::Id_Col_Link );

        //
        // view
        //

        m_view = new UIPageView( this );
        m_view->setColumnVisible( UIPageView::Col_Nick, false );
        m_view->setColumnVisible( UIPageView::Col_Link, false );
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

        m_count = 0;
        m_done  = false;
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
UIBrowsePage::~UIBrowsePage()
{
        delete m_items;
}

void UIBrowsePage::finishedBrowse()
{
        if ( m_done == true )
                return ;

        m_done = true;

        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Cancel ) - 1 );
        m_menu->removeItem( UIPageMenu::Id_Cancel );

        if ( m_view->firstChild() == 0 )
        {
                QListViewItem * item = new QListViewItem( m_view );
                item->setText( UIPageView::Col_Name,
                        tr( "No files shared!" ) );
        }

        updateTitle();
}

void UIBrowsePage::canceledBrowse()
{
        if ( m_done == true )
                return ;

        m_done = true;

        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Cancel ) - 1 );
        m_menu->removeItem( UIPageMenu::Id_Cancel );

        if ( m_view->firstChild() == 0 )
        {
                QListViewItem * item = new QListViewItem( m_view );
                item->setText( UIPageView::Col_Name,
                        tr( "Browsing was canceled" ) );
        }

        updateTitle();
}

void UIBrowsePage::updateTitle()
{
        QString text;

        if ( m_done == false )
                text = tr( "Browsing: %1 (%2 results, running)" );
        else
                text = tr( "Browsing: %1 (%2 results, finished)" );

        text = text.arg( name() );
        text = text.arg( currentCountString() );
        title()->setText( text );
}

void UIBrowsePage::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::BrowseRequest:
                recvIO_BrowseRequest( io );
                break;
        case IONapsterCodes::BrowseReply:
                recvIO_BrowseReply( io );
                break;
        case IONapsterCodes::BrowseDone:
                recvIO_BrowseDone( io );
                break;
        }

        emit recvIO( io );
}

void UIBrowsePage::recvIO_BrowseRequest( IOMessage * )
{
        m_view->clear();
}

void UIBrowsePage::recvIO_BrowseReply( IOMessage * io )
{
        if ( m_done == true )
                return ;

        //
        // count gets bumped, title gets updated
        //

        incrementCount();
        updateTitle();

        //
        // find dir, add file
        //

        QStringList dirs = QStringList::split( "\\", io->find( "path" ) );

        // get or create the first item ?
        QListViewItem * item = m_view->firstChild();
        QListViewItem * next;
        QString path;

        // create the first item as needed
        if ( item == 0 )
        {
                path = tr( "Browsing: \"%1\"" );
                path = path.arg( name() );

                item = new QListViewItem( m_view );
                item->setText( UIPageView::Col_Name, path );
                item->setText( UIPageView::Col_Nick, io->find( "nick" ) );
                item->setOpen( true );
	}

        // initialize the path
        path = item->text( UIPageView::Col_Name );

        for ( ; dirs.count() > 0; dirs.remove( dirs.begin() ) )
        {
                path += "\\" + dirs.first();
                next  = m_items->find( path );

                // if the item was not found, create a new one
                item = next == 0 ? new QListViewItem( item ) : next;

                // save the item name
                item->setText( UIPageView::Col_Name, dirs.first() );
                item->setText( UIPageView::Col_Nick, io->find( "nick" ) );
                item->setOpen( true );

                // make sure the item is in the dict
                m_items->replace( path, item );
        }

        // exhausted dirs, item should point correctly;
        item->setText( UIPageView::Col_Size, io->find( "size" ) );
        item->setText( UIPageView::Col_Bitr, io->find( "bitrate" ) );
        item->setText( UIPageView::Col_Time, io->find( "time" ) );
        item->setText( UIPageView::Col_Freq, io->find( "freq" ) );
        item->setText( UIPageView::Col_Path, io->find( "path" ) );
        item->setText( UIPageView::Col_Host, io->find( "host" ) );
        item->setPixmap( UIPageView::Col_Name, 0 );

        m_view->triggerUpdate();
}

void UIBrowsePage::recvIO_BrowseDone( IOMessage * )
{
        finishedBrowse();
}

void UIBrowsePage::slot_ViewClicked( QListViewItem * )
{
}

void UIBrowsePage::slot_ViewExecuted( QListViewItem * )
{
        menu_Download();
}

void UIBrowsePage::slot_ViewMenu( QListViewItem * , const QPoint & point )
{
        int id = m_menu->exec( point );

        switch ( id )
        {
        case UIPageMenu::Id_Download:
                menu_Download();
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
        case UIPageMenu::Id_Col_Time:
                menu_Column( UIPageView::Col_Time, id );
                break;
        case UIPageMenu::Id_Col_Rate:
                menu_Column( UIPageView::Col_Rate, id );
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

void UIBrowsePage::menu_Copy( int col_id )
{
        QListViewItem * item = m_view->currentItem();

        if ( item == 0 )
                return ;

        QApplication::clipboard()->setText( item->text( col_id ) );
}

void UIBrowsePage::menu_Sort( int col_id, int menu_id )
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

void UIBrowsePage::menu_Column( int col_id, int menu_id )
{
        bool visible = ( ! m_view->columnVisible( col_id ) );

        m_menu->setItemChecked( menu_id, visible );

        m_view->setColumnVisible( col_id, visible );
        m_view->triggerUpdate();
}

void UIBrowsePage::menu_Message()
{
}

void UIBrowsePage::menu_Cancel()
{
}

void UIBrowsePage::menu_Select()
{
        m_view->selectItemsDialog();
}

void UIBrowsePage::menu_Download()
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
                io->setMessageType( IONapsterCodes::DownloadRequest );
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

