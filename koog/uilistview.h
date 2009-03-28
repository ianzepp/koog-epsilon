/***************************************************************************
                          uilistview.h  -  description
                             -------------------
    begin                : Thu Mar 1 2001
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


#ifndef UILISTVIEW_H
#define UILISTVIEW_H

#include <qevent.h>
#include <qheader.h>
#include <qintdict.h>
#include <qlist.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qpoint.h>
#include <qregexp.h>
#include <qstring.h>
#include <qwidget.h>

// kde
#include <klineeditdlg.h>

struct UIListViewColumnData
{
        QString                 name;   // columnText
        Q_INT32                 size;   // columnWidth
        QListView::WidthMode    mode;   // columnWidthMode
};

/**
  *@author Ian Zepp
  */

class UIListView : public QListView
{
        Q_OBJECT
public: 
	UIListView(QWidget *parent=0, const char *name=0);
	~UIListView();

        typedef UIListViewColumnData ColumnData;

public:
        QList<QListViewItem> selectedItems();
        Q_UINT32 selectItems( int, const QRegExp &, bool clear = true );
        Q_UINT32 selectItems( int, const QString &, bool clear = true );

        void selectItemsDialog();
        void invertSelection();

        void triggerUpdate();

        int  addColumn( const QString & );
        void removeColumn( int );

        bool columnVisible( int );
        void setColumnVisible( int, bool );

protected slots:
        void paintEvent( QPaintEvent * );

protected slots:
        void internalMenu( void *, QListViewItem *, const QPoint & );

signals:
        void executed( QListViewItem * );
        void contextMenu( QListViewItem *, const QPoint & );

private:
        QIntDict<ColumnData>    m_data;
};

inline bool UIListView::columnVisible( int col )
{ return columnWidth( col ) > 0; }

#endif
