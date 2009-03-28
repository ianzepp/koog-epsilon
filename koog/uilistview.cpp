/***************************************************************************
                          uilistview.cpp  -  description
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


#include "uilistview.h"

UIListView::UIListView(QWidget *parent, const char *name )
           :QListView(parent,name)
{
        setTreeStepSize( 25 );
        setRootIsDecorated( true );
        setAllColumnsShowFocus( true );
        setShowSortIndicator( true );
        setVScrollBarMode( AlwaysOn );
        setHScrollBarMode( AlwaysOff );

        connect( this, SIGNAL(doubleClicked(QListViewItem *)),
                 this, SIGNAL(executed(QListViewItem *)) );
        connect( this, SIGNAL(returnPressed(QListViewItem *)),
                 this, SIGNAL(executed(QListViewItem *)) );
        connect( this, SIGNAL(rightButtonClicked(QListViewItem *, const QPoint &, int)),
                 this, SIGNAL(contextMenu(QListViewItem *, const QPoint &)) );

        //
        // items
        //

        m_data.setAutoDelete( true );
}
UIListView::~UIListView()
{
}


int UIListView::addColumn( const QString & name )
{
        int col_id = QListView::addColumn( name );

        // data stuff will be set later in setColumnVisible()
        m_data.insert( col_id, new ColumnData );

        return col_id;
}

void UIListView::removeColumn( int col_id )
{
        QListView::removeColumn( col_id );
        m_data.remove( col_id );
}

void UIListView::triggerUpdate()
{
        int vis = visibleWidth();
        int num = columns();

        //
        // grab all the max width columns
        //

        for ( int col = 0; col < columns(); col++ )
        {
                if (( columnWidth( col ) == 0 ) ||
                    ( columnWidthMode( col ) == Maximum ))
                {
                        vis -= columnWidth( col );
                        num -= 1;
                }
        }

        //
        // split all the other columns into equal sized bites
        //

        if ( num == 0 )
                return ;

        int avg = vis / num;

        for ( int col = 0; col < num; col++ )
        {
                if ( columnWidthMode( col ) == Maximum )
                        continue;
                if ( columnWidth( col ) == 0 )
                        continue;

                setColumnWidth( col, avg );
        }

        // reimpl
        QListView::triggerUpdate();
}

void UIListView::setColumnVisible( int col, bool show )
{
        if ( columnVisible( col ) == show )
                return ;

        ColumnData * data = m_data.find( col );

        if ( show == false )
        {
                data->name = columnText( col );
                data->size = columnWidth( col );
                data->mode = columnWidthMode( col );

                setColumnText ( col, "" );
                setColumnWidth( col, 0 );
                setColumnWidthMode( col, QListView::Manual );
                header()->setResizeEnabled( false, col );
        }
        else
        {
                setColumnText ( col, data->name );
                setColumnWidth( col, data->size );
                setColumnWidthMode( col, data->mode );
                header()->setResizeEnabled( true, col );
        }
}

void UIListView::paintEvent( QPaintEvent * event )
{
        triggerUpdate();

        QListView::paintEvent( event );
}

void UIListView::internalMenu( void *, QListViewItem * item, const QPoint & pt )
{
        emit contextMenu( item, pt );
}

QList<QListViewItem> UIListView::selectedItems()
{
        QList<QListViewItem> list;

        // set current item as first item
        firstChild();

        //
        // run through items
        //

        QListViewItemIterator it( this );
        QListViewItem * item = 0;

        for ( ; it.current(); ++it )
        {
                item = it.current();

                if ( item->isSelected() == false )
                        continue;

                list.append( item );
        }

        return list;
}

Q_UINT32 UIListView::selectItems( int col, const QRegExp & regex, bool clear )
{
        firstChild();

        QListViewItemIterator it( this );
        QListViewItem * item = 0;
        Q_UINT32        count = 0;

        for ( ; it.current(); ++it )
        {
                item = it.current();

                if ( clear == true )
                        setSelected( item, false );
                if ( regex.match( item->text( col ) ) == -1 )
                        continue;

                setSelected( item, true );
                count++;
        }

        return count;
}

Q_UINT32 UIListView::selectItems( int col, const QString & data, bool clear )
{
        firstChild();

        QListViewItemIterator it( this );
        QListViewItem * item  = 0;
        Q_UINT32        count = 0;

        for ( ; ( item = it.current() ); ++it )
        {
                if ( clear == true )
                        setSelected( item, false );
                if ( data.find( item->text( col ) ) == -1 )
                        continue;

                setSelected( item, true );
                count++;
        }

        return count;
}

void UIListView::selectItemsDialog()
{
        QString text   = tr( "Please enter text or regular expression to match:" );
        QString name   = "";
        bool    accept = false;
        QString data   = KLineEditDlg::getText( text, name, &accept, 0 );

        if ( accept == false )
                return ;
        if ( data.isEmpty() )
                return ;

        QRegExp regex = QRegExp( data, false );
        QString count = QString::number( selectItems( 0, regex ) );

        QMessageBox::information( this, tr( "Selection results" ),
                tr( "Selected %1 files" ).arg( count ),
                QMessageBox::Ok );
}

void UIListView::invertSelection()
{
        firstChild();

        QListViewItemIterator it( this );
        QListViewItem * item;

        for ( ; ( item = it.current() ); ++it )
                setSelected( item, ! item->isSelected() );
}
