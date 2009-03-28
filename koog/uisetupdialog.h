/***************************************************************************
                          uisetupdialog.h  -  description
                             -------------------
    begin                : Fri Mar 9 2001
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

#ifndef UISETUPDIALOG_H
#define UISETUPDIALOG_H

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdir.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qwidget.h>

// kde
#include <kfiledialog.h>
#include <ksimpleconfig.h>

// internal
#include "uisetupdialogbase.h"

/**
  *@author Ian Zepp
  */

class UISetupDialog : public UISetupDialogBase
{
        Q_OBJECT
public: 
	UISetupDialog(QWidget *parent=0, const char *name=0);
	~UISetupDialog();

        void saveConfig();
        void loadConfig();

protected:
        void loadConfig_User();
        void loadConfig_Transfer();

        void saveConfig_User();
        void saveConfig_Transfer();

protected slots:
        void slot_Accept();
        void slot_Cancel();

        void slot_RecvReset();
        void slot_RecvBrowse();
        void slot_SendRemove();
        void slot_SendBrowse();
        void slot_SendChanged( QListViewItem * );
};

#endif
