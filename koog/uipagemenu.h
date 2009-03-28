/***************************************************************************
                          uipagemenu.h  -  description
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

#ifndef UIPAGEMENU_H
#define UIPAGEMENU_H

#include <qiconset.h>
#include <qpixmap.h>
#include <qstring.h>
#include <qwidget.h>

// kde
#include <kiconloader.h>
#include <kpopupmenu.h>

/**
  *@author Ian Zepp
  */

class UIPageMenu : public KPopupMenu
{
        Q_OBJECT
public: 
	UIPageMenu(QWidget *parent=0, const char *name=0);
	~UIPageMenu();

        enum MenuItems {
                Id_Download,
                Id_Message,
                Id_Browse,
                Id_Cancel,
                Id_Select,
                Id_Cleanup,

                Id_Sort,
                Id_Sort_Name,
                Id_Sort_Bitr,
                Id_Sort_Size,
                Id_Sort_Time,
                Id_Sort_Freq,
                Id_Sort_Nick,

                Id_Copy,
                Id_Copy_Name,
                Id_Copy_Nick,
                Id_Copy_Path,
                Id_Copy_Host,

                Id_Col,
                Id_Col_Name,
                Id_Col_Bitr,
                Id_Col_Size,
                Id_Col_Rate,
                Id_Col_Freq,
                Id_Col_Time,
                Id_Col_Link,
                Id_Col_Nick,
                Id_Col_Ping,
                Id_Col_Path,
                Id_Col_Host,

                Id_Audio,
                Id_Audio_Play,
                Id_Audio_Pause,
                Id_Audio_Stop,

                Id_File,
                Id_File_Copy,
                Id_File_Delete,
                Id_File_Rename,
                Id_File_Trash,

                // last item
                __null_item
        };

protected:
        KPopupMenu      * m_sort;
        KPopupMenu      * m_copy;
        KPopupMenu      * m_cols;
        KPopupMenu      * m_audio;
        KPopupMenu      * m_file;
};


#endif
