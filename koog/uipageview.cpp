/***************************************************************************
                          uipageview.cpp  -  description
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

#include "uipagemenu.h"
#include "uipageview.h"

UIPageView::UIPageView(QWidget *parent, const char *name )
           :UIListView(parent,name)
{
        addColumn( tr( "Filename"       ) );
        addColumn( tr( "Bitrate"        ) );
        addColumn( tr( "Size"           ) );
        addColumn( tr( "Rate"           ) );
        addColumn( tr( "Frequency"      ) );
        addColumn( tr( "Time"           ) );
        addColumn( tr( "Speed"          ) );
        addColumn( tr( "User"           ) );
        addColumn( tr( "Ping"           ) );
        addColumn( tr( "Full path"      ) );
        addColumn( tr( "Remote host"    ) );
        addColumn( tr( "GUID"           ) );

        setColumnAlignment( Col_Bitr, AlignCenter );
        setColumnAlignment( Col_Size, AlignCenter );
        setColumnAlignment( Col_Rate, AlignCenter );
        setColumnAlignment( Col_Link, AlignCenter );
        setColumnAlignment( Col_Time, AlignCenter );
        setColumnAlignment( Col_Freq, AlignCenter );
        setColumnAlignment( Col_Link, AlignCenter );
        setColumnAlignment( Col_Ping, AlignCenter );
        setColumnWidthMode( Col_Name, QListView::Manual );
        setColumnWidthMode( Col_Path, QListView::Manual );
        setColumnWidthMode( Col_Guid, QListView::Manual );
        setColumnVisible( Col_Rate, false );
        setColumnVisible( Col_Ping, false );
        setColumnVisible( Col_Path, false );
        setColumnVisible( Col_Host, false );
        setColumnVisible( Col_Guid, false );
        setSelectionMode( Extended );
}
UIPageView::~UIPageView()
{
}

void UIPageView::initColumnMenu( UIPageMenu * m )
{
        m->setItemChecked( UIPageMenu::Id_Col_Name,
                columnVisible( Col_Name ) );
        m->setItemChecked( UIPageMenu::Id_Col_Bitr,
                columnVisible( Col_Bitr ) );
        m->setItemChecked( UIPageMenu::Id_Col_Size,
                columnVisible( Col_Size ) );
        m->setItemChecked( UIPageMenu::Id_Col_Rate,
                columnVisible( Col_Rate ) );
        m->setItemChecked( UIPageMenu::Id_Col_Time,
                columnVisible( Col_Time ) );
        m->setItemChecked( UIPageMenu::Id_Col_Freq,
                columnVisible( Col_Freq ) );
        m->setItemChecked( UIPageMenu::Id_Col_Link,
                columnVisible( Col_Link ) );
        m->setItemChecked( UIPageMenu::Id_Col_Nick,
                columnVisible( Col_Nick ) );
        m->setItemChecked( UIPageMenu::Id_Col_Ping,
                columnVisible( Col_Ping ) );
        m->setItemChecked( UIPageMenu::Id_Col_Path,
                columnVisible( Col_Path ) );
        m->setItemChecked( UIPageMenu::Id_Col_Host,
                columnVisible( Col_Host ) );

}
