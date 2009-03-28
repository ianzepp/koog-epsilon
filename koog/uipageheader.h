/***************************************************************************
                          uipageheader.h  -  description
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


#ifndef UIPAGEHEADER_H
#define UIPAGEHEADER_H

#include <qwidget.h>
#include <qhbox.h>

// classes
class UIPageHeaderButton;
class UIPageHeaderDrag;

/**
  *@author Ian Zepp
  */

class UIPageHeader : public QHBox
{
        Q_OBJECT
public: 
	UIPageHeader(QWidget *parent=0, const char *name=0);
	~UIPageHeader();

        void setButtonVisible( bool );

signals:
        void closeClicked();

protected:
        UIPageHeaderButton      * button;
        UIPageHeaderDrag        * drag;
};

#endif
