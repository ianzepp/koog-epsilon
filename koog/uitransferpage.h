/***************************************************************************
                          uitransferpage.h  -  description
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

#ifndef UITRANSFERPAGE_H
#define UITRANSFERPAGE_H

#include <qclipboard.h>
#include <qdict.h>
#include <qdir.h>
#include <qfile.h>
#include <qiconset.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qpoint.h>
#include <qstring.h>
#include <qwidget.h>

// kde
#include <kiconloader.h>
#include <kpopupmenu.h>

// internal
#include "uipage.h"

// classes
class IOMessage;
class IONapsterTransfer;
class UIPageView;
class UIPageMenu;

typedef QDict<IONapsterTransfer>        UITransferPageTransferDict;
typedef QDict<QListViewItem>            UITransferPageItemDict;
typedef QDictIterator<QListViewItem>    UITransferPageItemDictIterator;

/**
  *@author Ian Zepp
  */

class UITransferPage : public UIPage
{
        Q_OBJECT
public: 
	UITransferPage(QWidget *parent=0, const char *name=0);
	~UITransferPage();

        typedef UITransferPageTransferDict      TransferDict;
        typedef UITransferPageItemDict          ItemDict;
        typedef UITransferPageItemDictIterator  ItemDictIterator;

public slots:
        void recvIOEvent( IOMessage * );

protected:
        void recvIO_DownloadRequest( IOMessage * );
        void recvIO_DownloadReply( IOMessage * );
        void recvIO_DownloadError( IOMessage * );

protected slots:
        void slot_ViewClicked( QListViewItem * );
        void slot_ViewExecuted( QListViewItem * );
        void slot_ViewMenu( QListViewItem *, const QPoint & );

        void updateTitle();
        void updateItemEvent( Q_INT32 );

        void menu_Browse();
        void menu_Message();
        void menu_Cancel();
        void menu_Select();
        void menu_Cleanup();

        void menu_Copy( int );
        void menu_Sort( int, int );
        void menu_Column( int, int );

protected:
        Q_UINT32 currentTransferID();
        QString  currentTransferIDString();
        void     incrementTransferID();

        Q_UINT32 currentRecvCount();
        QString  currentRecvCountString();
        void     incrementRecvCount();
        void     decrementRecvCount();

        Q_UINT32 currentSendCount();
        QString  currentSendCountString();
        void     incrementSendCount();
        void     decrementSendCount();

        QListViewItem * findItem( const QString &, bool create = true );
        void removeItem( QListViewItem * );
        void cleanupItems();

private:
        UIPageMenu              * m_menu;
        UIPageView              * m_view;
        KIconLoader               m_icons;

        Q_UINT32                  m_xfer_id;
        Q_UINT32                  m_recv_cnt;
        Q_UINT32                  m_send_cnt;

        TransferDict            * m_xfers;
        ItemDict                * m_items;
};

inline Q_UINT32 UITransferPage::currentTransferID()
{ return m_xfer_id; }

inline QString UITransferPage::currentTransferIDString()
{ return QString::number( currentTransferID() ); }

inline void UITransferPage::incrementTransferID()
{ m_xfer_id++; }

inline Q_UINT32 UITransferPage::currentRecvCount()
{ return m_recv_cnt; }

inline QString UITransferPage::currentRecvCountString()
{ return QString::number( currentRecvCount() ); }

inline void UITransferPage::incrementRecvCount()
{ m_recv_cnt++; }

inline void UITransferPage::decrementRecvCount()
{ m_recv_cnt--; }

inline Q_UINT32 UITransferPage::currentSendCount()
{ return m_send_cnt; }

inline QString UITransferPage::currentSendCountString()
{ return QString::number( currentSendCount() ); }

inline void UITransferPage::incrementSendCount()
{ m_send_cnt++; }

inline void UITransferPage::decrementSendCount()
{ m_send_cnt--; }

#endif
