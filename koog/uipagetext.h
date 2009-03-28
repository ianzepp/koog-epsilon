/***************************************************************************
                          uipagetext.h  -  description
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

#ifndef UIPAGETEXT_H
#define UIPAGETEXT_H

#include <qstring.h>
#include <qtextview.h>
#include <qwidget.h>

/**
  *@author Ian Zepp
  */

class UIPageText : public QTextView
{
        Q_OBJECT
public: 
	UIPageText(QWidget *parent=0, const char *name=0);
	~UIPageText();

public:
        void updateContents();
        void append( const QString &, bool update = true );
};

#endif
