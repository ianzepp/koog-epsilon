/***************************************************************************
                          koog.h  -  description
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

#ifndef KOOG_H
#define KOOG_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// qt
#include <qdict.h>
#include <qevent.h>
#include <qlistview.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qwidgetstack.h>

// kde
#include <kapp.h>
#include <kdockwidget.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <ktoolbar.h>

// internal classes
class IOMessage;
class IONapsterConnection;
class UIListView;
class UISearch;

struct KoogData
{
        KPopupMenu * menu;
        QWidget    * page;
};

/** Koog is the base class of the porject */
class Koog : public KDockMainWindow
{
        Q_OBJECT
public:
        /** construtor */
        Koog(QWidget* parent=0, const char *name=0);
        /** destructor */
        ~Koog();

public slots:
        void recvIOEvent( IOMessage * );
        void sendIOEvent( IOMessage * );
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

protected:
        // received
        void recvIO_ServerStats( IOMessage * );
        void recvIO_ChanJoinReply( IOMessage * );

        // sending
        void sendIO_BrowseRequest( IOMessage * );
        void sendIO_SearchRequest( IOMessage * );
        void sendIO_DownloadRequest( IOMessage * );

protected slots:
        void slot_SourceClicked( QListViewItem * );
        void slot_SourceMenu( QListViewItem *, const QPoint & );

protected slots:
        void menu_FileConnectOfficial();
        void menu_FileConnectLast();
        void menu_FileDisconnect();
        void menu_FileSetup();
        void menu_FileExit();

        void menu_ChanAvailable();
        void menu_ChanLeaveAll()                        {};

        void menu_ViewToolBar();
        void menu_ViewStatusBar();
        void menu_ViewSource();
        void menu_ViewSearch();

        void menu_SearchCancel();
        void menu_SearchClose();
        void menu_BrowseClose();

protected:
        Q_UINT32 currentStackID();
        QString  currentStackIDString();
        void     incrementStackID();

        Q_UINT32 currentSearchCount();
        QString  currentSearchCountString();
        void     incrementSearchCount();

        Q_UINT32 currentBrowseCount();
        QString  currentBrowseCountString();
        void     incrementBrowseCount();

protected slots:
//        void paintEvent( QPaintEvent * );
//        void closeEvent( QCloseEvent * );

private:
        Q_UINT32                  m_id;
        Q_UINT32                  m_search_cnt;
        Q_UINT32                  m_browse_cnt;

        IONapsterConnection     * m_napster;

        KMenuBar                * m_menubar;
        KToolBar                * m_toolbar;
        KStatusBar              * m_statusbar;

        KPopupMenu              * m_fileMenu;
        KPopupMenu              * m_viewMenu;
        KPopupMenu              * m_chanMenu;

        KDockWidget             * m_dockStack;
        KDockWidget             * m_dockSource;
        KDockWidget             * m_dockSearch;

        QWidgetStack            * m_mainStack;
        UIListView              * m_mainSource;
        UISearch                * m_mainSearch;

        QListViewItem           * m_itemLibrary;
        QListViewItem           * m_itemNapster;
        QListViewItem           * m_itemBrowsing;
        QListViewItem           * m_itemChannels;
        QListViewItem           * m_itemSearches;
        QListViewItem           * m_itemTransfers;

        QDict<KoogData>         * m_pageData;
};

inline Q_UINT32 Koog::currentStackID()
{ return m_id; }

inline QString Koog::currentStackIDString()
{ return QString::number( m_id ); }

inline void Koog::incrementStackID()
{ m_id++; }

inline Q_UINT32 Koog::currentSearchCount()
{ return m_search_cnt; }

inline QString Koog::currentSearchCountString()
{ return QString::number( m_search_cnt ); }

inline void Koog::incrementSearchCount()
{ m_search_cnt++; }

inline Q_UINT32 Koog::currentBrowseCount()
{ return m_browse_cnt; }

inline QString Koog::currentBrowseCountString()
{ return QString::number( m_browse_cnt ); }

inline void Koog::incrementBrowseCount()
{ m_browse_cnt++; }


#endif
