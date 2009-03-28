/***************************************************************************
                          uipagetext.cpp  -  description
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

#include "uipagetext.h"

UIPageText::UIPageText(QWidget *parent, const char *name )
           :QTextView(parent,name)
{
        setHScrollBarMode( AlwaysOff );
        setVScrollBarMode( AlwaysOn  );
}
UIPageText::~UIPageText()
{
}

void UIPageText::updateContents()
{
        int ch = contentsHeight();
        int vw = visibleWidth();

        ensureVisible( 0, ch, 0, 0 );
        repaintContents( 0, ch - 40, vw, 40, true );
}

void UIPageText::append( const QString & data, bool update )
{
        QTextView::append( data );

        if ( update == true )
                updateContents();
}

