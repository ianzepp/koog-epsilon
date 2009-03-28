/***************************************************************************
                          uibrowsepage.h  -  description
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

#ifndef UIBROWSEPAGE_H
#define UIBROWSEPAGE_H

#include <qclipboard.h>
#include <qiconset.h>
#include <qdict.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpopupmenu.h>
#include <qwidget.h>

// kde
#include <kapp.h>
#include <kiconloader.h>
#include <kpopupmenu.h>

// internal
#include "uipage.h"

// internal classes
class IOMessage;
class UIPageMenu;
class UIPageView;

/**
  *@author Ian Zepp
  */

class UIBrowsePage : public UIPage
{
        Q_OBJECT
public:
	UIBrowsePage(QWidget *parent=0, const char *name=0);
	~UIBrowsePage();

        typedef QDict<QListViewItem>            ItemDict;
        typedef QDictIterator<QListViewItem>    ItemDictIterator;

public slots:
        void recvIOEvent( IOMessage * );

protected:
        void recvIO_BrowseRequest( IOMessage * );
        void recvIO_BrowseReply( IOMessage * );
        void recvIO_BrowseDone( IOMessage * );

protected slots:
        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );

        void menu_Download();
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

        void finishedBrowse();
        void canceledBrowse();
        void updateTitle();

private:
        UIPageView              * m_view;
        UIPageMenu              * m_menu;

        Q_UINT32                  m_count;
        bool                      m_done;
        ItemDict                * m_items;
};

inline Q_UINT32 UIBrowsePage::currentCount()
{ return m_count; }

inline QString UIBrowsePage::currentCountString()
{ return QString::number( currentCount() ); }

inline void UIBrowsePage::incrementCount()
{ m_count++; }

#endif
