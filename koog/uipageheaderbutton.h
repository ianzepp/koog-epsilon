/***************************************************************************
                          uipageheaderbutton.h  -  description
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


#ifndef UIPAGEHEADERBUTTON_H
#define UIPAGEHEADERBUTTON_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qevent.h>

/**
  *@author Ian Zepp
  */

class UIPageHeaderButton : public QPushButton
{
        Q_OBJECT
public: 
	UIPageHeaderButton(QWidget *parent=0, const char *name=0);
	~UIPageHeaderButton();

protected:
        virtual void drawButton( QPainter * );
        virtual void enterEvent( QEvent * );
        virtual void leaveEvent( QEvent * );

private:
        bool moveMouse;
};

#endif
