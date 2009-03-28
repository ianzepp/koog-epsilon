/***************************************************************************
                          uipageheaderdrag.h  -  description
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


#ifndef UIPAGEHEADERDRAG_H
#define UIPAGEHEADERDRAG_H

#include <qwidget.h>
#include <qframe.h>
#include <qevent.h>
#include <qpixmap.h>
#include <qpainter.h>

/**
  *@author Ian Zepp
  */

class UIPageHeaderDrag : public QFrame
{
        Q_OBJECT
public: 
	UIPageHeaderDrag(QWidget *parent=0, const char *name=0);
	~UIPageHeaderDrag();

protected slots:
        void paintEvent( QPaintEvent * );
};

#endif
