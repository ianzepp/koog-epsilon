/***************************************************************************
                          uipage.h  -  description
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

#ifndef UIPAGE_H
#define UIPAGE_H

#include <qevent.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qwidget.h>

// kde
#include <kapp.h>

// internal classes
class IOMessage;
class UIPageHeader;

/**
  *@author Ian Zepp
  */

class UIPage : public QWidget
{
        Q_OBJECT
public: 
	UIPage(QWidget *parent=0, const char *name=0);
	~UIPage();

public slots:
        void recvIOEvent( IOMessage * io )      { emit recvIO( io ); };
        void sendIOEvent( IOMessage * io )      { emit sendIO( io ); };
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

        // send right before we close
        void closing( QWidget * );

protected slots:
        void closeEvent( QCloseEvent * );

protected:
        QBoxLayout      * layout()              { return __layout; };
        UIPageHeader    * header()              { return __header; };
        QLabel          * title()               { return __title;  };

private:
        QLabel          * __title;
        UIPageHeader    * __header;
        QBoxLayout      * __layout;
};

#endif
