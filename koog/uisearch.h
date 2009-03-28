/***************************************************************************
                          uisearch.h  -  description
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

#ifndef UISEARCH_H
#define UISEARCH_H

#include <qapp.h>
#include <qwidget.h>
#include <qstring.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qcombobox.h>
#include <qlineedit.h>

// kde
#include <ksimpleconfig.h>

// internal
#include "uisearchbase.h"

/**
  *@author Ian Zepp
  */

class IOMessage;

class UISearch : public UISearchBase
{
   Q_OBJECT
public:
	UISearch(QWidget *parent=0, const char *name=0);
	~UISearch();

public slots:
        void recvIOEvent( IOMessage * );
        void sendIOEvent( IOMessage * );
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

signals:
        void searchCanceled();
public slots:
        void searchCanceledEvent();

protected slots:
        void handleEditChanged( const QString & );
        void handleSearchToggled( bool );
        void handleAdvancedToggled( bool );

protected:
        void recvIO_SearchDone( IOMessage * );

        QString convertCompare( const QString & );

        void saveConfig();
        void loadConfig();
};

#endif
