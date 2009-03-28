/***************************************************************************
                          koog.cpp  -  description
                             -------------------
    begin                : Wed Mar  7 00:47:09 EST 2001
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

#include "koog.h"

#include <qlistview.h>
#include <qpoint.h>
#include <qstring.h>
#include <qwidgetstack.h>

#include <kdockwidget.h>

#include "iomessage.h"
#include "ionapstercodes.h"
#include "ionapsterconnection.h"

#include "uibrowsepage.h"
#include "uichanneldialog.h"
#include "uichannelpage.h"
#include "uiconsolepage.h"
#include "uilibrarypage.h"
#include "uilistview.h"
#include "uisearch.h"
#include "uisearchpage.h"
#include "uisetupdialog.h"
#include "uitransferpage.h"

#define COL_SOURCE      0
#define COL_PAGE        1

#define ID_VIEW_TOOLBAR         10200
#define ID_VIEW_STATUSBAR       10201
#define ID_VIEW_SOURCE          10202
#define ID_VIEW_SEARCH          10203
#define ID_SB_NAP_STATS         20100
#define ID_SB_UPTIME            20200
#define ID_SB_CONNECTED         20300

#define ICON_LIBRARY            "fileopen.png"
#define ICON_NAPSTER            "gohome.png"
#define ICON_CHANNELS           "history.png"
#define ICON_SEARCHES           "filefind.png"
#define ICON_BROWSING           "contents.png"
#define ICON_TRANSFERS          "connect_established.png"

/***************************************************************************/

Koog::Koog(QWidget *parent, const char *name) : KDockMainWindow(parent, name)
{
        resize( 640, 480 );

        //
        // pages and menus
        //

        m_pageData = new QDict<KoogData>;
        m_pageData->setAutoDelete( false );

        //
        // menubar and menues
        //

        m_fileMenu = new KPopupMenu( this );
        m_fileMenu->setTitle( tr( "Napster" ) );
        m_fileMenu->insertItem( tr( "Connect to &offical server" ), this,
                SLOT(menu_FileConnectOfficial()), CTRL+Key_O );
        m_fileMenu->insertItem( tr( "Connect to &last host" ), this,
                SLOT(menu_FileConnectLast()), CTRL+Key_L );
        m_fileMenu->insertItem( tr( "&Disconnect from napster" ), this,
                SLOT(menu_FileDisconnect()), CTRL+Key_D );
        m_fileMenu->insertSeparator();
        m_fileMenu->insertItem( tr( "Preferences" ), this,
                SLOT(menu_FileSetup()) );
        m_fileMenu->insertSeparator();
        m_fileMenu->insertItem( tr( "E&xit now" ), this,
                SLOT(menu_FileExit()), CTRL+Key_Q );

        m_chanMenu = new KPopupMenu( this );
        m_chanMenu->setTitle( tr( "Channels" ) );
        m_chanMenu->insertItem( "Join a channel", this,
                SLOT(menu_ChanAvailable()) );
        m_chanMenu->insertSeparator();
        m_chanMenu->insertItem( "Leave all channels", this,
                SLOT(menu_ChanLeaveAll()) );

        m_viewMenu = new KPopupMenu( this );
        m_viewMenu->setTitle( tr( "View" ) );
        m_viewMenu->setCheckable( true );
        m_viewMenu->insertItem( tr( "Toolbar" ), this,
                SLOT(menu_ViewToolBar()), 0, ID_VIEW_TOOLBAR );
        m_viewMenu->insertItem( tr( "Statusbar" ), this,
                SLOT(menu_ViewStatusBar()), 0, ID_VIEW_STATUSBAR );
        m_viewMenu->insertSeparator();
        m_viewMenu->insertItem( tr( "Source dock" ), this,
                SLOT(menu_ViewSource()), 0, ID_VIEW_SOURCE );
        m_viewMenu->insertItem( tr( "Search dock" ), this,
                SLOT(menu_ViewSearch()), 0, ID_VIEW_SEARCH );

        m_menubar = new KMenuBar( this );
        m_menubar->insertItem( tr( "&Napster" ), m_fileMenu );
        m_menubar->insertItem( tr( "&Channels" ), m_chanMenu );
        m_menubar->insertItem( tr( "&View" ), m_viewMenu );

        //
        // tool bar
        //

        m_toolbar = new KToolBar( this );
        m_toolbar->hide();
        m_viewMenu->setItemChecked( ID_VIEW_TOOLBAR, false );

        //
        // statusbar
        //

        m_statusbar = new KStatusBar( this );
        m_statusbar->message( tr( "Ready." ) );
        m_statusbar->insertItem( tr( "Offline" ), ID_SB_NAP_STATS, 0, true );
        m_viewMenu->setItemChecked( ID_VIEW_STATUSBAR, true );

        //
        // stack
        //

        m_dockStack = createDockWidget( tr( "Pages" ), QPixmap( 0 ) );
        m_mainStack = new QWidgetStack( m_dockStack, tr( "Pages" ) );
        m_dockStack->setWidget( m_mainStack );
        m_dockStack->setEnableDocking( KDockWidget::DockNone );

        setView( m_dockStack );
        setMainDockWidget( m_dockStack );

        //
        // view
        //

        m_dockSource = createDockWidget( tr( "Source" ), QPixmap( 0 ) );
        m_mainSource = new UIListView( m_dockSource, tr( "Source" ) );
        m_dockSource->setWidget ( m_mainSource );
        m_dockSource->manualDock( m_dockStack, KDockWidget::DockLeft, 0 );

        m_mainSource->addColumn( tr( "Source" ) );
        m_mainSource->addColumn( tr( "Page"   ) );
        m_mainSource->setMinimumWidth( 150 );
        m_mainSource->setVScrollBarMode( UIListView::Auto );
        m_mainSource->setColumnWidthMode( COL_SOURCE, UIListView::Manual );
        m_mainSource->setColumnVisible( COL_PAGE, false );
        m_mainSource->header()->hide();

        connect( m_mainSource, SIGNAL(clicked(QListViewItem *)),
                 this, SLOT(slot_SourceClicked(QListViewItem *)) );
        connect( m_mainSource, SIGNAL(currentChanged(QListViewItem *)),
                 this, SLOT(slot_SourceClicked(QListViewItem *)) );
        connect( m_mainSource, SIGNAL(rightButtonClicked(QListViewItem *, const QPoint &, int)),
                 this, SLOT(slot_SourceMenu(QListViewItem *, const QPoint &)) );

        m_viewMenu->setItemChecked( ID_VIEW_SOURCE, true );

        //
        // search
        //

        m_dockSearch = createDockWidget( tr( "Search" ), QPixmap( 0 ) );
        m_mainSearch = new UISearch( m_dockSearch, tr( "Search" ) );
        m_dockSearch->setWidget ( m_mainSearch );
        m_dockSearch->manualDock( m_dockStack, KDockWidget::DockTop, 0 );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 m_mainSearch, SLOT(recvIOEvent(IOMessage *)) );
        connect( m_mainSearch, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_viewMenu->setItemChecked( ID_VIEW_SEARCH, true );

        //
        // items
        //

        KoogData   * data;

        incrementStackID();

        m_itemLibrary = new QListViewItem( m_mainSource );
        m_itemLibrary->setText( COL_SOURCE, tr( "Library" ) );
        m_itemLibrary->setText( COL_PAGE, currentStackIDString() );
        m_itemLibrary->setOpen( true );
        m_itemLibrary->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_LIBRARY, KIcon::Small ) );

        data = new KoogData();
        data->page = new UILibraryPage( this );
        data->menu = 0;

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainStack->addWidget( data->page, currentStackID() );

        incrementStackID();

        m_itemNapster = new QListViewItem( m_mainSource );
        m_itemNapster->setText( COL_SOURCE, tr( "Napster" ) );
        m_itemNapster->setText( COL_PAGE, currentStackIDString() );
        m_itemNapster->setOpen( true );
        m_itemNapster->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_NAPSTER, KIcon::Small ) );

        data = new KoogData();
        data->page = new UIConsolePage( this );
        data->menu = m_fileMenu;

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainStack->addWidget( data->page, currentStackID() );

        incrementStackID();

        m_itemBrowsing = new QListViewItem( m_itemNapster );
        m_itemBrowsing->setText( COL_SOURCE, tr( "Browsing" ) );
        m_itemBrowsing->setText( COL_PAGE, currentStackIDString() );
        m_itemBrowsing->setOpen( true );
        m_itemBrowsing->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_BROWSING, KIcon::Small ) );

        data = new KoogData();
        data->page = 0;
        data->menu = 0;

        m_pageData->insert( currentStackIDString(), data );

        incrementStackID();

        m_itemChannels = new QListViewItem( m_itemNapster );
        m_itemChannels->setText( COL_SOURCE, tr( "Channels" ) );
        m_itemChannels->setText( COL_PAGE, currentStackIDString() );
        m_itemChannels->setOpen( true );
        m_itemChannels->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_CHANNELS, KIcon::Small ) );

        data = new KoogData();
        data->page = 0;
        data->menu = m_chanMenu;

        m_pageData->insert( currentStackIDString(), data );

        incrementStackID();

        m_itemSearches = new QListViewItem( m_itemNapster );
        m_itemSearches->setText( COL_SOURCE, tr( "Searches" ) );
        m_itemSearches->setText( COL_PAGE, currentStackIDString() );
        m_itemSearches->setOpen( true );
        m_itemSearches->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_SEARCHES, KIcon::Small ) );

        incrementStackID();

        m_itemTransfers = new QListViewItem( m_mainSource );
        m_itemTransfers->setText( COL_SOURCE, tr( "Transfers" ) );
        m_itemTransfers->setText( COL_PAGE, currentStackIDString() );
        m_itemTransfers->setOpen( true );
        m_itemTransfers->setPixmap( COL_SOURCE,
                KIconLoader().loadIcon( ICON_TRANSFERS, KIcon::Small ) );

        data = new KoogData();
        data->page = new UITransferPage;
        data->menu = 0;

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainStack->addWidget( data->page, currentStackID() );

        //
        // napster
        //

        m_napster = new IONapsterConnection( this );

        connect( m_napster, SIGNAL(recvIO(IOMessage *)),
                 this, SLOT(recvIOEvent(IOMessage *)) );
        connect( this, SIGNAL(sendIO(IOMessage *)),
                 m_napster, SLOT(sendIOEvent(IOMessage *)) );

        //
        // final setup
        //

        m_id            = 0;
        m_search_cnt    = 0;
        m_browse_cnt    = 0;

        slot_SourceClicked( m_itemNapster );
}

Koog::~Koog()
{
        delete m_pageData;
}

/***************************************************************************/

void Koog::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::ServerStats:
                recvIO_ServerStats( io );
                break;
        case IONapsterCodes::ChanJoinReply:
                recvIO_ChanJoinReply( io );
                break;
        }

        emit recvIO( io );
}

void Koog::sendIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::BrowseRequest:
                sendIO_BrowseRequest( io );
                break;
        case IONapsterCodes::DownloadRequest:
                sendIO_DownloadRequest( io );
                break;
        case IONapsterCodes::SearchRequest:
                sendIO_SearchRequest( io );
                break;
        }

        emit sendIO( io );
}

void Koog::recvIO_ServerStats( IOMessage * io )
{
        QString text = tr( "Online: %1 users, sharing %2 files (%3 Gb)" );
        text.prepend( "  " );
        text.append ( "  " );
        text = text.arg( io->find( "users" ) );
        text = text.arg( io->find( "files" ) );
        text = text.arg( io->find( "size"  ) );
        m_statusbar->changeItem( text, ID_SB_NAP_STATS );
}

void Koog::recvIO_ChanJoinReply( IOMessage * io )
{
        incrementStackID();

        QString name = io->find( "channel" );

        QListViewItem * item = new QListViewItem( m_itemChannels, name );
        item->setText( COL_SOURCE, name );
        item->setText( COL_PAGE, currentStackIDString() );
        item->setOpen( true );
        item->setPixmap( COL_SOURCE, QPixmap( 0 ) );

        KoogData * data = new KoogData();
        data->page = new UIChannelPage( this, name );
        data->menu = new KPopupMenu( this );
        data->menu->setTitle( tr( "Channel: \"%1\"" ).arg( name ) );
        data->menu->insertItem( tr( "Close window" ), this,
                SLOT(menu_ChannelClose()), 0 );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainSource->setSelected( item, true );
        m_mainSource->setCurrentItem( item );
        m_mainStack->addWidget( data->page, currentStackID() );
        m_mainStack->raiseWidget( data->page );
}

void Koog::sendIO_BrowseRequest( IOMessage * io )
{
        incrementStackID();
        incrementBrowseCount();

        QString name = io->find( "nick" );
        QString narg = "%1. %2";
        narg = narg.arg( currentBrowseCountString() );
        narg = narg.arg( name );

        QListViewItem * item = new QListViewItem( m_itemBrowsing, name );
        item->setText( COL_SOURCE, narg );
        item->setText( COL_PAGE, currentStackIDString() );
        item->setOpen( true );
        item->setPixmap( COL_SOURCE, QPixmap( 0 ) );

        KoogData * data = new KoogData();
        data->page = new UIBrowsePage( this, name );
        data->menu = new KPopupMenu( this );
        data->menu->setTitle( tr( "Browse: \"%1\"" ).arg( name ) );
        data->menu->insertItem( tr( "Close window" ), this,
                SLOT(menu_BrowseClose()), 0 );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainSource->setSelected( item, true );
        m_mainSource->setCurrentItem( item );
        m_mainStack->addWidget( data->page, currentStackID() );
        m_mainStack->raiseWidget( data->page );
}

void Koog::sendIO_SearchRequest( IOMessage * io )
{
        incrementStackID();
        incrementSearchCount();

        QString name = io->find( "name" );
        QString narg = "%1. %2";
        narg = narg.arg( currentSearchCountString() );
        narg = narg.arg( name );

        QListViewItem * item = new QListViewItem( m_itemSearches, name );
        item->setText( COL_SOURCE, narg );
        item->setText( COL_PAGE, currentStackIDString() );
        item->setOpen( true );
        item->setPixmap( COL_SOURCE, QPixmap( 0 ) );

        KoogData * data = new KoogData();
        data->page = new UISearchPage( this, name );
        data->menu = new KPopupMenu( this );
        data->menu->setTitle( tr( "Search: \"%1\"" ).arg( name ) );
        data->menu->insertItem( tr( "Cancel search" ), this,
                SLOT(menu_SearchCancel()), CTRL+Key_C );
        data->menu->insertItem( tr( "Close window" ), this,
                SLOT(menu_SearchClose()), CTRL+Key_W );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 data->page, SLOT(recvIOEvent(IOMessage *)) );
        connect( data->page, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        m_pageData->insert( currentStackIDString(), data );
        m_mainSource->setSelected( item, true );
        m_mainSource->setCurrentItem( item );
        m_mainStack->addWidget( data->page, currentStackID() );
        m_mainStack->raiseWidget( data->page );
}

void Koog::sendIO_DownloadRequest( IOMessage * io )
{
        // XXX bad hack! fix me!
        emit recvIO( io );

        QListViewItem * item = m_itemTransfers;

        if ( item == 0 )
                return ;

        KoogData * data = m_pageData->find( item->text( COL_PAGE ) );

        if ( data == 0 )
                return ;

        m_mainSource->setSelected( item, true );
        m_mainSource->setCurrentItem( item );
        m_mainStack->raiseWidget( data->page );
}

void Koog::slot_SourceClicked( QListViewItem * item )
{
        if ( item == 0 )
                return ;

        KoogData * data = m_pageData->find( item->text( COL_PAGE ) );

        if ( data == 0 )
                return ;
        if ( data->page == 0 )
                return ;

        m_mainStack->raiseWidget( data->page );
}

void Koog::slot_SourceMenu( QListViewItem * item, const QPoint & point )
{
        if ( item == 0 )
                return ;

        KoogData * data = m_pageData->find( item->text( COL_PAGE ) );

        if ( data == 0 )
                return ;
        if ( data->menu == 0 )
                return ;

        data->menu->exec( point );
}

/***************************************************************************

void Koog::paintEvent( QPaintEvent * event )
{
}

void Koog::closeEvent( QPaintEvent * event )
{
}

 ***************************************************************************/

void Koog::menu_FileConnectOfficial()
{
        m_napster->napsterDisconnect();
        m_napster->napsterBestHost();
}

void Koog::menu_FileConnectLast()
{
        m_napster->napsterDisconnect();
        m_napster->napsterConnect();
}

void Koog::menu_FileDisconnect()
{
        m_napster->napsterDisconnect();
}

void Koog::menu_FileSetup()
{
        UISetupDialog * d = new UISetupDialog( 0 );
        d->exec();
}

void Koog::menu_FileExit()
{
        m_napster->napsterDisconnect();
        close();
}

void Koog::menu_ChanAvailable()
{
        UIChannelDialog * widg = new UIChannelDialog( 0 );

        connect( this, SIGNAL(recvIO(IOMessage *)),
                 widg, SLOT(recvIOEvent(IOMessage *)) );
        connect( widg, SIGNAL(sendIO(IOMessage *)),
                 this, SLOT(sendIOEvent(IOMessage *)) );

        // send IOMessage
        IOMessage * io = new IOMessage( 0 );
        io->setMessageType( IONapsterCodes::ListChansRequest );
        emit sendIO( io );

        delete io;

        // show
        widg->exec();
}

void Koog::menu_ViewToolBar()
{
        int id = ID_VIEW_TOOLBAR;
        bool b =  m_viewMenu->isItemChecked( id );

        if ( b == true )
        {
                m_viewMenu->setItemChecked( id, false );
                m_toolbar ->hide();
        }
        else
        {
                m_viewMenu->setItemChecked( id, true );
                m_toolbar ->show();
        }
}

void Koog::menu_ViewStatusBar()
{
        int id = ID_VIEW_STATUSBAR;
        bool b =  m_viewMenu->isItemChecked( id );

        if ( b == true )
        {
                m_viewMenu ->setItemChecked( id, false );
                m_statusbar->hide();
        }
        else
        {
                m_viewMenu ->setItemChecked( id, true );
                m_statusbar->show();
        }
}

void Koog::menu_ViewSource()
{
        int id = ID_VIEW_TOOLBAR;
        bool b =  m_viewMenu->isItemChecked( id );

        if ( b == true )
        {
                if ( m_dockSource->mayBeHide() == false )
                        return ;
                m_viewMenu  ->setItemChecked( id, false );
                m_dockSource->hide();
        }
        else
        {
                if ( m_dockSource->mayBeShow() == false )
                        return ;
                m_viewMenu  ->setItemChecked( id, true );
                m_dockSource->show();
        }
}

void Koog::menu_ViewSearch()
{
}

void Koog::menu_SearchCancel()
{
}

void Koog::menu_SearchClose()
{
        QListViewItem * item = m_mainSource->currentItem();

        if ( item == 0 )
                return ;

        KoogData * data = m_pageData->find( item->text( COL_PAGE ) );

        if ( data == 0 )
                return ;
        if ( data->page )
                delete data->page;
        if ( data->menu )
                delete data->menu;

        delete item;

        //
        // default back to console
        //

        slot_SourceClicked( m_itemNapster );
}

void Koog::menu_BrowseClose()
{
        QListViewItem * item = m_mainSource->currentItem();

        if ( item == 0 )
                return ;

        KoogData * data = m_pageData->find( item->text( COL_PAGE ) );

        if ( data == 0 )
                return ;
        if ( data->page )
                delete data->page;
        if ( data->menu )
                delete data->menu;

        delete item;

        //
        // default back to console
        //

        slot_SourceClicked( m_itemNapster );
}




