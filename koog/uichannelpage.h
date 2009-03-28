/***************************************************************************
                          uichannelpage.h  -  description
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

#ifndef UICHANNELPAGE_H
#define UICHANNELPAGE_H

#include <qclipboard.h>
#include <qdict.h>
#include <qhbox.h>
#include <qiconset.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlist.h>
#include <qlistview.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qregexp.h>
#include <qwidget.h>

// kde
#include <kapp.h>
#include <kiconloader.h>
#include <kpopupmenu.h>
#include <ksimpleconfig.h>

// internal
#include "uipage.h"

// internal classes
class IOMessage;
class UIListView;
class UIPageMenu;
class UIPageText;

/**
  *@author Ian Zepp
  */

class UIChannelPage : public UIPage
{
        Q_OBJECT
public: 
	UIChannelPage(QWidget *parent=0, const char *name=0);
	~UIChannelPage();

public slots:
        void recvIOEvent( IOMessage * );

protected:
        void recvIO_ChanList( IOMessage * );
        void recvIO_ChanListDone( IOMessage * );

        void recvIO_ChanJoin( IOMessage * );
        void recvIO_ChanPart( IOMessage * );
        void recvIO_ChanMessage( IOMessage * );

        void recvIO_ChanTopic( IOMessage * );
        void recvIO_ChanMotd( IOMessage * );

protected slots:
        void slot_EditReturn();

        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );

protected:
        void menu_Browse();
        void menu_Message();
        void menu_Select();

        void menu_Copy( int );
        void menu_Sort( int, int );
        void menu_Column( int, int );

        enum Columns { Col_Nick, Col_Size, Col_Link };

protected:
        UIListView              * m_view;
        UIPageText              * m_text;
        UIPageMenu              * m_menu;
        QLineEdit               * m_edit;

        KIconLoader               m_icons;
};

#endif
