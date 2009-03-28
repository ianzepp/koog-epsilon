/***************************************************************************
                          uipage.cpp  -  description
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

#include "uipage.h"
#include "uipageheader.h"

UIPage::UIPage(QWidget *parent, const char *name )
       :QWidget(parent,name)
{
        __layout = new QBoxLayout( this, QBoxLayout::TopToBottom );
        __layout->setAutoAdd( true );

        __header = new UIPageHeader( this );
        __header->setButtonVisible( false );

        __title = new QLabel( this );
        __title->setText( name );
        __title->setAlignment( AlignCenter );
        __title->setFixedHeight( 25 );
}
UIPage::~UIPage()
{
        emit closing( this );
}

void UIPage::closeEvent( QCloseEvent * event )
{
        QWidget::closeEvent( event );
}

