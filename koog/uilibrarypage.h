/***************************************************************************
                          uilibrarypage.h  -  description
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

#ifndef UILIBRARYPAGE_H
#define UILIBRARYPAGE_H

#include <qapp.h>
#include <qclipboard.h>
#include <qdir.h>
#include <qiconset.h>
#include <qfileinfo.h>
#include <qhbox.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qpoint.h>
#include <qregexp.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qdict.h>

// kde
#include <kiconloader.h>
#include <klineeditdlg.h>
#include <kpopupmenu.h>
#include <kprocess.h>
#include <ksimpleconfig.h>

// internal
#include "uipage.h"

// classes
class IOMessage;
class UIListView;
class UIPageMenu;
class UIPageView;
class UIPlayer;

/**
  *@author Ian Zepp
  */

class UILibraryPage : public UIPage
{
        Q_OBJECT
public:
	UILibraryPage(QWidget *parent=0, const char *name=0);
	~UILibraryPage();

        typedef QDict<QListViewItem>            ItemDict;
        typedef QDictIterator<QListViewItem>    ItemDictIterator;

public slots:
        void reload();

public slots:
        void recvIOEvent( IOMessage * );

protected slots:
        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );

        void slot_ProcessNextFile();

protected:
        void menu_Select();

        void menu_AudioPlay();
        void menu_AudioPause();
        void menu_AudioStop();

        void menu_Copy( int );
        void menu_Sort( int, int );
        void menu_Column( int, int );

        void menu_FileCopy();
        void menu_FileDelete();
        void menu_FileRename();
        void menu_FileTrash();

protected:
        Q_UINT32 currentCount();
        QString  currentCountString();
        void     incrementCount();
        void     resetCount();

        void updateTitle();

private:
        UIPageView              * m_view;
        UIPageMenu              * m_menu;

        Q_UINT32                  m_count;
        QStringList               m_pending;
        QTimer                  * m_timer;
        ItemDict                * m_items;
        QPixmap                   m_folder;
};

inline Q_UINT32 UILibraryPage::currentCount()
{ return m_count; }

inline QString UILibraryPage::currentCountString()
{ return QString::number( currentCount() ); }

inline void UILibraryPage::incrementCount()
{ m_count++; }

inline void UILibraryPage::resetCount()
{ m_count = 0; }

#endif
