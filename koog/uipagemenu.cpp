/***************************************************************************
                          uipagemenu.cpp  -  description
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

#define ICON_AUDIO_PLAY         "1rightarrow.png"
#define ICON_AUDIO_PAUSE        "player_pause.png"
#define ICON_AUDIO_STOP         "player_stop.png"
#define ICON_FILE_COPY          "editcopy.png"
#define ICON_FILE_DELETE        "editdelete.png"
#define ICON_FILE_RENAME        ""
#define ICON_FILE_TRASH         "edittrash.png"
#define ICON_BROWSE             "fileopen.png"
#define ICON_DOWNLOAD           "connect_creating.png"
#define ICON_MESSAGE            "mail_generic.png"
#define ICON_CANCEL             "stop.png"
#define ICON_SELECT             "find.png"

UIPageMenu::UIPageMenu(QWidget *parent, const char *name )
           :KPopupMenu(parent,name)
{
        //
        // sorting child menu
        //

        m_sort = new KPopupMenu( this );
        m_sort->setTitle( tr( "Sorting" ) );
        m_sort->setCheckable( true );
        m_sort->insertItem(
                tr( "Sort by &filename" ),
                Id_Sort_Name );
        m_sort->insertSeparator();
        m_sort->insertItem(
                tr( "Sort by &bitrate" ),
                Id_Sort_Bitr );
        m_sort->insertItem(
                tr( "Sort by &nickname" ),
                Id_Sort_Nick );
        m_sort->insertItem(
                tr( "Sort by &time" ),
                Id_Sort_Time );
        m_sort->insertItem(
                tr( "Sort by &size" ),
                Id_Sort_Size );
        m_sort->insertItem(
                tr( "Sort by f&requency" ),
                Id_Sort_Freq );
        m_sort->setItemChecked( Id_Sort_Name, true );

        //
        // copy child menu
        //

        m_copy = new KPopupMenu( this );
        m_copy->setTitle( tr( "Copy" ) );
        m_copy->insertItem(
                tr( "&Filename" ),
                Id_Copy_Name );
        m_copy->insertSeparator();
        m_copy->insertItem(
                tr( "Full &path" ),
                Id_Copy_Path );
        m_copy->insertItem(
                tr( "&Nickname" ),
                Id_Copy_Nick );
        m_copy->insertItem(
                tr( "&Remote host" ),
                Id_Copy_Host );

        //
        // column child menu
        //

        m_cols = new KPopupMenu( this );
        m_cols->setTitle( tr( "Columns" ) );
        m_cols->setCheckable( true );
        m_cols->insertItem( tr( "&Filename" ), Id_Col_Name );
        m_cols->insertSeparator();
        m_cols->insertItem( tr( "&Bitrate" ), Id_Col_Bitr );
        m_cols->insertItem( tr( "&Size" ), Id_Col_Size );
        m_cols->insertItem( tr( "&Rate" ), Id_Col_Rate );
        m_cols->insertItem( tr( "&Time" ), Id_Col_Time );
        m_cols->insertItem( tr( "&Frequency" ), Id_Col_Freq );
        m_cols->insertSeparator();
        m_cols->insertItem( tr( "&Speed" ), Id_Col_Link );
        m_cols->insertItem( tr( "&Nickname" ), Id_Col_Nick );
        m_cols->insertItem( tr( "&Ping" ), Id_Col_Ping );
        m_cols->insertSeparator();
        m_cols->insertItem( tr( "Full &path" ), Id_Col_Path );
        m_cols->insertItem( tr( "&Remote host" ), Id_Col_Host );

        //
        // audio child menu
        //

        m_audio = new KPopupMenu( this );
        m_audio->setTitle( tr( "Audio" ) );
        m_audio->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_AUDIO_PLAY, KIcon::Small ) ),
                tr( "Play" ), Id_Audio_Play );
        m_audio->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_AUDIO_PAUSE, KIcon::Small ) ),
                tr( "Pause" ), Id_Audio_Pause );
        m_audio->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_AUDIO_STOP, KIcon::Small ) ),
                tr( "Stop" ), Id_Audio_Stop );

        //
        // file child menu
        //

        m_file = new KPopupMenu( this );
        m_file->setTitle( tr( "Files" ) );
        m_file->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_FILE_COPY, KIcon::Small ) ),
                tr( "Copy" ), Id_File_Copy );
        m_file->insertItem(
                tr( "Rename" ), Id_File_Rename );
        m_file->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_FILE_TRASH, KIcon::Small ) ),
                tr( "Move to trash" ), Id_File_Trash );
        m_file->insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_FILE_DELETE, KIcon::Small ) ),
                tr( "Delete" ), Id_File_Delete );

        //
        // menu
        //

        setTitle( name );
        insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_DOWNLOAD, KIcon::Small ) ),
                tr( "&Download" ), Id_Download );
        insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_BROWSE, KIcon::Small ) ),
                tr( "&Browse" ), Id_Browse );
        insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_MESSAGE, KIcon::Small ) ),
                tr( "&Message" ), Id_Message );
        insertSeparator();
        insertItem( tr( "&Files..." ), m_file, Id_File );
        insertItem( tr( "&Audio..." ), m_audio, Id_Audio );
        insertSeparator();
        insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_SELECT, KIcon::Small ) ),
                tr( "&Select items" ), Id_Select );
        insertSeparator();
        insertItem( tr( "Clip&board..." ), m_copy, Id_Copy );
        insertItem( tr( "S&orting..." ), m_sort, Id_Sort );
        insertItem( tr( "Co&lumns..." ), m_cols, Id_Col );
        insertSeparator();
        insertItem(
                QIconSet( KIconLoader().loadIcon( ICON_CANCEL, KIcon::Small ) ),
                tr( "&Cancel" ), Id_Cancel );
        insertItem( tr( "&Cleanup" ), Id_Cleanup );

}
UIPageMenu::~UIPageMenu()
{
}
