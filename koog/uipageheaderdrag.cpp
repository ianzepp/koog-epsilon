/***************************************************************************
                          uipageheaderdrag.cpp  -  description
                             -------------------
    begin                : Mon Mar 5 2001
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


#include "uipageheaderdrag.h"

UIPageHeaderDrag::UIPageHeaderDrag(QWidget *parent, const char *name )
                 :QFrame(parent,name)
{
        setFixedHeight( 9 );
}
UIPageHeaderDrag::~UIPageHeaderDrag()
{
}

void UIPageHeaderDrag::paintEvent( QPaintEvent * )
{
        QPixmap drawBuffer( width(), height() );
        QPainter paint;

        paint.begin( &drawBuffer );
        paint.fillRect( drawBuffer.rect(),
                QBrush(colorGroup().brush(QColorGroup::Background)) );

        paint.setPen( colorGroup().light() );
        paint.drawLine( 1, 3, 1, 2 );
        paint.drawLine( 1, 2, width(), 2 );

        paint.setPen( colorGroup().mid() );
        paint.drawLine( 1, 4, width(), 4 );
        paint.drawLine( width(), 4, width(), 3 );

        paint.setPen( colorGroup().light() );
        paint.drawLine( 1, 6, 1, 5 );
        paint.drawLine( 1, 5, width(), 5 );

        paint.setPen( colorGroup().mid() );
        paint.drawLine( 1, 7, width(), 7 );
        paint.drawLine( width(), 7, width(), 6 );

        bitBlt( this, 0, 0, &drawBuffer, 0, 0, width(), height() );
        paint.end();
}
