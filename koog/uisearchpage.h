/***************************************************************************
                          uisearchpage.h  -  description
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

#ifndef UISEARCHPAGE_H
#define UISEARCHPAGE_H

#include <qclipboard.h>
#include <qiconset.h>
#include <qdict.h>
#include <qheader.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qpoint.h>
#include <qpopupmenu.h>
#include <qregexp.h>
#include <qstring.h>
#include <qwidget.h>

// kde
#include <kapp.h>
#include <kiconloader.h>
#include <klineeditdlg.h>

// internal
#include "uipage.h"

// internal classes
class IOMessage;
class UIPageView;
class UIPageMenu;

/**
  *@author Ian Zepp
  */

class UISearchPage : public UIPage
{
        Q_OBJECT
public: 
	UISearchPage(QWidget *parent=0, const char *name=0);
	~UISearchPage();

        typedef QDict<QListViewItem>            ItemDict;
        typedef QDictIterator<QListViewItem>    ItemDictIterator;

public slots:
        void recvIOEvent( IOMessage * );

signals:
        void searchCanceled();
public slots:
        void searchCanceledEvent();

protected:
        void recvIO_SearchRequest( IOMessage * );
        void recvIO_SearchReply( IOMessage * );
        void recvIO_SearchDone( IOMessage * );

protected slots:
        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );

        void menu_Download();
        void menu_Browse();
        void menu_Message();
        void menu_Cancel();
        void menu_Select();

        void menu_Copy( int );
        void menu_Sort( int, int );
        void menu_Column( int, int );

protected:
        void incrementCount();
        QString  currentCountString();
        Q_UINT32 currentCount();

        void finishedSearch();
        void canceledSearch();
        void updateTitle();

private:
        UIPageView              * m_view;
        UIPageMenu              * m_menu;

        Q_UINT32                  m_count;
        bool                      m_done;
        ItemDict                * m_items;

        QPixmap                   m_folder;
};

inline Q_UINT32 UISearchPage::currentCount()
{ return m_count; }

inline QString UISearchPage::currentCountString()
{ return QString::number( currentCount() ); }

inline void UISearchPage::incrementCount()
{ m_count++; }

#endif
