/***************************************************************************
                          uipageheader.cpp  -  description
                             -------------------
    begin                : Sat Mar 3 2001
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


#include "uipageheader.h"
#include "uipageheaderdrag.h"
#include "uipageheaderbutton.h"

UIPageHeader::UIPageHeader(QWidget *parent, const char *name )
             :QHBox(parent,name)
{
        drag = new UIPageHeaderDrag( this );

        CHECK_PTR( drag );

        button = new UIPageHeaderButton( this );

        CHECK_PTR( button );

        connect( button, SIGNAL(clicked()), SIGNAL(closeClicked()) );

        setSpacing( 0 );
        setStretchFactor( button, 0 );
        setStretchFactor( drag, 10 );
        setFixedHeight( 9 );
}
UIPageHeader::~UIPageHeader()
{
}

void UIPageHeader::setButtonVisible( bool show )
{
        show ? button->show() : button->hide();
}

