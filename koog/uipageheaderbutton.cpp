/***************************************************************************
                          uipageheaderbutton.cpp  -  description
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


#include "uipageheaderbutton.h"

static const char * close_xpm[]={
"5 5 2 1",
"# c black",
". c None",
"#...#",
".#.#.",
"..#..",
".#.#.",
"#...#"};

UIPageHeaderButton::UIPageHeaderButton(QWidget *parent, const char *name )
                   :QPushButton(parent,name)
{
        moveMouse = false;
        setFocusPolicy( NoFocus );
        setPixmap( QPixmap( close_xpm ) );
}
UIPageHeaderButton::~UIPageHeaderButton()
{
}

void UIPageHeaderButton::drawButton( QPainter * paint )
{
        paint->fillRect( 0,0, width(), height(),
                QBrush(colorGroup().brush(QColorGroup::Background)) );
        paint->drawPixmap( (width() - pixmap()->width()) / 2,
                           (height() - pixmap()->height()) / 2, *pixmap() );

        if ( moveMouse && !isDown() )
        {
                paint->setPen( white );
                paint->moveTo( 0, height() - 1 );
                paint->lineTo( 0, 0 );
                paint->lineTo( width() - 1, 0 );

                paint->setPen( colorGroup().dark() );
                paint->lineTo( width() - 1, height() - 1 );
                paint->lineTo( 0, height() - 1 );
        }

        if ( isOn() || isDown() )
        {
                paint->setPen( colorGroup().dark() );
                paint->moveTo( 0, height() - 1 );
                paint->lineTo( 0, 0 );
                paint->lineTo( width() - 1, 0 );

                paint->setPen( white );
                paint->lineTo( width() - 1, height() - 1 );
                paint->lineTo( 0, height() - 1 );
        }
}

void UIPageHeaderButton::enterEvent( QEvent * )
{
        moveMouse = true;
        repaint();
}

void UIPageHeaderButton::leaveEvent( QEvent * )
{
        moveMouse = false;
        repaint();
}

