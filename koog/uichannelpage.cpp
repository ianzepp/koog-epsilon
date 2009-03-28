/***************************************************************************
                          uichannelpage.cpp  -  description
                             -------------------
    begin                : Mon Mar 12 2001
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

#include "uiconfig.h"
#include "uichannelpage.h"
#include "uilistview.h"
#include "uipagemenu.h"
#include "uipagetext.h"

UIChannelPage::UIChannelPage(QWidget *parent, const char *name )
              :UIPage(parent,name)
{
        //
        // menu
        //

        m_menu = new UIPageMenu( this, name );

        //
        // hbox and text / view
        //

        QHBox * hblayout = new QHBox( this );

        m_text = new UIPageText( hblayout );

        m_view = new UIListView( hblayout );
        m_view->addColumn( tr( "Nickname" ) );
        m_view->addColumn( tr( "#"        ) );
        m_view->addColumn( tr( "Speed"    ) );
        m_view->setColumnWidthMode( Col_Nick, UIListView::Manual );
        m_view->setColumnAlignment( Col_Size, AlignCenter );
        m_view->setColumnAlignment( Col_Link, AlignCenter );
        m_view->setFixedWidth( 200 );
        m_view->setSelectionMode( UIListView::Extended );
        m_view->setRootIsDecorated( false );

        connect( m_view, SIGNAL(clicked(QListViewItem *)),
                 this, SLOT(slot_ViewClicked(QListViewItem *)) );
        connect( m_view, SIGNAL(executed(QListViewItem *)),
                 this, SLOT(slot_ViewExecuted(QListViewItem *)) );
        connect( m_view, SIGNAL(contextMenu(QListViewItem *, const QPoint &)),
                 this, SLOT(slot_ViewMenu(QListViewItem *, const QPoint &)) );

        //
        // edit
        //

        m_edit = new QLineEdit( this );

        connect( m_edit, SIGNAL(returnPressed()),
                 this, SLOT(slot_EditReturn()) );

        //
        // setup page
        //

        hblayout->setStretchFactor( m_text,   10 );
        hblayout->setStretchFactor( m_view,    0 );
        layout()->setStretchFactor( hblayout, 10 );
        title() ->setText( name );
}
UIChannelPage::~UIChannelPage()
{
}

void UIChannelPage::recvIOEvent( IOMessage * io )
{
        if ( io->find( "channel" ) != name() )
                return ;

        switch ( io->messageType() )
        {
        case IONapsterCodes::ChanList:
                recvIO_ChanList( io );
                break;
        case IONapsterCodes::ChanListDone:
                recvIO_ChanListDone( io );
                break;
        case IONapsterCodes::ChanJoin:
                recvIO_ChanJoin( io );
                break;
        case IONapsterCodes::ChanPart:
                recvIO_ChanPart( io );
                break;
        case IONapsterCodes::ChanMessage:
                recvIO_ChanMessage( io );
                break;
        case IONapsterCodes::ChanTopic:
                recvIO_ChanTopic( io );
                break;
        case IONapsterCodes::ChanMotd:
                recvIO_ChanMotd( io );
                break;
        }

        emit recvIO( io );
}

void UIChannelPage::recvIO_ChanList( IOMessage * io )
{
        QListViewItem * item = new QListViewItem( m_view );
        item->setText( Col_Nick, io->find( "nick" ) );
        item->setText( Col_Size, io->find( "size" ) );
        item->setText( Col_Link, io->find( "speed" ) );

        m_view->triggerUpdate();
}

void UIChannelPage::recvIO_ChanListDone( IOMessage * )
{
}

void UIChannelPage::recvIO_ChanJoin( IOMessage * io )
{
        //
        // view
        //

        QListViewItem * item = new QListViewItem( m_view );
        item->setText( Col_Nick, io->find( "nick" ) );
        item->setText( Col_Size, io->find( "size" ) );
        item->setText( Col_Link, io->find( "speed" ) );

        m_view->triggerUpdate();

        //
        // text
        //

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** $nick ($speed, sharing $size) joined $channel" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIChannelPage::recvIO_ChanPart( IOMessage * io )
{
        //
        // view
        //

        m_view->selectItems( 0, QRegExp( io->find( "nick" ), false ) );

        QList<QListViewItem> list = m_view->selectedItems();
        QListViewItem      * item;

        for ( item = list.first(); item != 0; item = list.next() )
                delete item;

        m_view->triggerUpdate();

        //
        // text
        //

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** $nick ($speed, sharing $size) left $channel" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIChannelPage::recvIO_ChanTopic( IOMessage * io )
{
        QString text = "%1: %2";
        text = text.arg( name() );
        text = text.arg( io->find( "message" ) );
        title()->setText( text );
}

void UIChannelPage::recvIO_ChanMotd( IOMessage * io )
{
        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** $message" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIChannelPage::recvIO_ChanMessage( IOMessage * io )
{
        QString text = tr( "&lt;<strong>$nick</strong>&gt; $message" );
        m_text->append( io->formatVariables( text ) );
}

void UIChannelPage::slot_EditReturn()
{
        QString text = m_edit->text();

        if ( text.isEmpty() == true )
                return ;

        IOMessage * io = new IOMessage( 0 );
        io->setMessageType( IONapsterCodes::ChanMessageRequest );
        io->insert( "rawdata", QString( "%1 %2" ).arg( name() ).arg( text ) );
        emit sendIO( io );

        delete io;

        m_edit->clear();
}

void UIChannelPage::slot_ViewClicked( QListViewItem * )
{
}

void UIChannelPage::slot_ViewExecuted( QListViewItem * )
{
        menu_Message();
}

void UIChannelPage::slot_ViewMenu( QListViewItem *, const QPoint & point )
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
        case UIPageMenu::Id_Select:
                menu_Select();
                break;

/*
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
*/
        }
}

void UIChannelPage::menu_Select()
{
        m_view->selectItemsDialog();
}

void UIChannelPage::menu_Browse()
{
        QList<QListViewItem> list = m_view->selectedItems();
        QListViewItem * item;
        QString path;

        for ( item = list.first(); item != 0; item = list.next() )
        {
                IOMessage * io = new IOMessage( 0 );
                io->setMessageType( IONapsterCodes::BrowseRequest );
                io->insert( "nick",     item->text( Col_Nick ) );
                io->insert( "speed",    item->text( Col_Link ) );
                emit sendIO( io );

                delete io;
        }
}
void UIChannelPage::menu_Message()
{
}

void UIChannelPage::menu_Copy( int col_id )
{
        QListViewItem * item = m_view->currentItem();

        if ( item == 0 )
                return ;

        QApplication::clipboard()->setText( item->text( col_id ) );
}

void UIChannelPage::menu_Sort( int col_id, int menu_id )
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

void UIChannelPage::menu_Column( int col_id, int menu_id )
{
        bool visible = ( ! m_view->columnVisible( col_id ) );

        m_menu->setItemChecked( menu_id, visible );
        m_view->setColumnVisible( col_id, visible );
        m_view->triggerUpdate();
}

