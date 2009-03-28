/***************************************************************************
                          uichanneldialog.h  -  description
                             -------------------
    begin                : Tue Mar 13 2001
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

#ifndef UICHANNELDIALOG_H
#define UICHANNELDIALOG_H

#include <qclipboard.h>
#include <qlist.h>
#include <qlistview.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qwidget.h>

// kde
#include <kpopupmenu.h>
#include <ksimpleconfig.h>

// internal
#include "uichanneldialogbase.h"

// classes
class IOMessage;

/**
  *@author Ian Zepp
  */

class UIChannelDialog : public UIChannelDialogBase
{
        Q_OBJECT
public: 
	UIChannelDialog(QWidget *parent=0, const char *name=0);
	~UIChannelDialog();

public slots:
        void recvIOEvent( IOMessage * io );
        void sendIOEvent( IOMessage * io );
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

protected:
        void recvIO_ListChansReply( IOMessage * );
        void recvIO_ListChansDone( IOMessage * );
        void recvIO_ListAllChansReply( IOMessage * );
        void recvIO_ListAllChansDone( IOMessage * );

protected slots:
        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );
        void slot_Join();
        void slot_ChanToggled( bool );

protected:
        void toggleEnabled( bool );

        enum { Col_Chan, Col_Size, Col_Topic };

private:
        QListViewItem * m_itemNapster;
        QListViewItem * m_itemOther;
};

#endif
