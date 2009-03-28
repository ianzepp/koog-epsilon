/***************************************************************************
                          uipageview.h  -  description
                             -------------------
    begin                : Mon Mar 12 2001
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

#ifndef UIPAGEVIEW_H
#define UIPAGEVIEW_H

#include <qwidget.h>

// internal
#include "uilistview.h"

// classes
class UIPageMenu;

/**
  *@author Ian Zepp
  */

class UIPageView : public UIListView
{
        Q_OBJECT
public: 
	UIPageView(QWidget *parent=0, const char *name=0);
	~UIPageView();

        enum Columns
        {
                Col_Name,
                Col_Bitr,
                Col_Size,
                Col_Rate,
                Col_Freq,
                Col_Time,
                Col_Link,
                Col_Nick,
                Col_Ping,
                Col_Path,
                Col_Host,
                Col_Guid,

                // last value
                __last_enum
        };

public:
        void initColumnMenu( UIPageMenu * );
};

#endif
