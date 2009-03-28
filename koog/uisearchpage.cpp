/***************************************************************************
                          uisearchpage.cpp  -  description
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
#include "iosupport.h"

#include "uipagemenu.h"
#include "uipageview.h"
#include "uisearchpage.h"

#define ICON_CANCEL             "stop.png"
#define ICON_QUESTION           "help.png"
#define ICON_FOLDER             "fileopen.png"

/***************************************************************************/

UISearchPage::UISearchPage(QWidget *parent, const char *name )
             :UIPage(parent,name)
{
        //
        // menu
        //

        m_menu = new UIPageMenu( this, tr( "Search: \"%1\"" ).arg( name ) );
        m_menu->removeItem( UIPageMenu::Id_Audio );
        m_menu->removeItem( UIPageMenu::Id_File );
        m_menu->removeItem( UIPageMenu::Id_Cleanup );
        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Select ) - 1 );
        m_menu->removeItem( UIPageMenu::Id_Col_Rate );

        //
        // view
        //
        m_view = new UIPageView( this );
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

        m_count  = 0;
        m_done   = false;
        m_items  = new ItemDict( 101 ); // largest expected prime number
        m_folder = KIconLoader().loadIcon( ICON_FOLDER, KIcon::Small );

        //
        // title
        //

        updateTitle();

        //
        // page
        //

        layout()->setStretchFactor( m_view, 10 );
}
UISearchPage::~UISearchPage()
{
        delete m_items;
}

void UISearchPage::finishedSearch()
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
                        tr( "No results found!" ) );
                item->setPixmap( UIPageView::Col_Name,
                        KIconLoader().loadIcon( ICON_QUESTION, KIcon::Small ) );
        }

        updateTitle();
}

void UISearchPage::canceledSearch()
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
                        tr( "Search was canceled" ) );
                item->setPixmap( UIPageView::Col_Name,
                        KIconLoader().loadIcon( ICON_CANCEL, KIcon::Small ) );
        }

        updateTitle();
}

void UISearchPage::updateTitle()
{
        QString text;

        if ( m_done == false )
                text = tr( "Search: %1 (%2 results, running)" );
        else
                text = tr( "Search: %1 (%2 results, finished)" );

        text = text.arg( name() );
        text = text.arg( currentCountString() );
        title()->setText( text );
}

void UISearchPage::searchCanceledEvent()
{
}

void UISearchPage::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::SearchRequest:
                recvIO_SearchRequest( io );
                break;
        case IONapsterCodes::SearchReply:
                recvIO_SearchReply( io );
                break;
        case IONapsterCodes::SearchDone:
                recvIO_SearchDone( io );
                break;
        }

        emit recvIO( io );
}

void UISearchPage::recvIO_SearchRequest( IOMessage * )
{
        m_view->clear();
}

void UISearchPage::recvIO_SearchReply( IOMessage * io )
{
        if ( m_done == true )
                return ;


        // Order of appearance
        //
        // the first time a filename shows up it gets it's own line,
        // and if it shows up more than once it is reparented.

        QListViewItem * item = new QListViewItem( m_view );
        item->setText( UIPageView::Col_Name, io->find( "name" ) );
        item->setText( UIPageView::Col_Bitr, io->find( "bitrate" ) );
        item->setText( UIPageView::Col_Size, io->find( "size" ) );
        item->setText( UIPageView::Col_Time, io->find( "time" ) );
        item->setText( UIPageView::Col_Freq, io->find( "freq" ) );
        item->setText( UIPageView::Col_Link, io->find( "speed" ) );
        item->setText( UIPageView::Col_Nick, io->find( "nick" ) );
        item->setText( UIPageView::Col_Path, io->find( "path" ) );
        item->setText( UIPageView::Col_Host, io->find( "host" ) );

        //
        // count gets bumped, title gets updated
        //

        incrementCount();
        updateTitle();

        //
        // do some bizzare tree m_view stuff ?
        //

        QListViewItem * item2 = m_items->find( io->find( "name" ) );

        if ( item2 == 0 )
        {
                m_items->replace( io->find( "name" ), item );
        }
        else
        {
                QListViewItem * from = 0;

                if ( item2->text( UIPageView::Col_Path ).isEmpty() == false )
                {
                        from = new QListViewItem( m_view );
                        from->setText( UIPageView::Col_Name, io->find( "name" ) );
                        from->setOpen( true );
                        from->setPixmap( UIPageView::Col_Name, m_folder );

                        // also add this item under parent
                        m_view->takeItem( item2 );
                        from->insertItem( item2 );
                }
                else
                {
                        from = item2;
                }

                m_view->takeItem( item );
                from->insertItem( item );

                m_items->replace( io->find( "name" ), from );
        }

        m_view->triggerUpdate();
}

void UISearchPage::recvIO_SearchDone( IOMessage * )
{
        finishedSearch();
}

void UISearchPage::slot_ViewClicked( QListViewItem * )
{
}

void UISearchPage::slot_ViewExecuted( QListViewItem * )
{
        menu_Download();
}

void UISearchPage::slot_ViewMenu( QListViewItem * , const QPoint & point )
{
        int id = m_menu->exec( point );

        switch ( id )
        {
        case UIPageMenu::Id_Download:
                menu_Download();
                break;
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

void UISearchPage::menu_Copy( int col_id )
{
        QListViewItem * item = m_view->currentItem();

        if ( item == 0 )
                return ;

        QApplication::clipboard()->setText( item->text( col_id ) );
}

void UISearchPage::menu_Sort( int col_id, int menu_id )
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

void UISearchPage::menu_Column( int col_id, int menu_id )
{
        bool visible = ( ! m_view->columnVisible( col_id ) );

        m_menu->setItemChecked( menu_id, visible );
        m_view->setColumnVisible( col_id, visible );
        m_view->triggerUpdate();
}

void UISearchPage::menu_Message()
{
}

void UISearchPage::menu_Cancel()
{
}

void UISearchPage::menu_Select()
{
        m_view->selectItemsDialog();
}

void UISearchPage::menu_Browse()
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

void UISearchPage::menu_Download()
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

