/***************************************************************************
                          uilibrarypage.cpp  -  description
                             -------------------
    begin                : Thu Mar 8 2001
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

#include "iomessage.h"
#include "ionapstercodes.h"
#include "iosupport.h"
#include "mp3header.h"
#include "uiconfig.h"
#include "uilibrarypage.h"
#include "uipagemenu.h"
#include "uipageview.h"

#define ICON_CANCEL             "stop.png"
#define ICON_QUESTION           "help.png"
#define ICON_FOLDER             "fileopen.png"

/***************************************************************************/

UILibraryPage::UILibraryPage(QWidget *parent, const char *name )
              :UIPage(parent,name)
{
        //
        // menu
        //

        m_menu = new UIPageMenu( this, tr( "Library" ) );
        m_menu->removeItem( UIPageMenu::Id_Download );
        m_menu->removeItem( UIPageMenu::Id_Browse );
        m_menu->removeItem( UIPageMenu::Id_Message );
        m_menu->removeItem( UIPageMenu::Id_Cancel );
        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_File ) - 1 );
        m_menu->removeItemAt( m_menu->indexOf( UIPageMenu::Id_Col ) + 1 );
        m_menu->setItemEnabled( UIPageMenu::Id_File_Copy, false );
        m_menu->setItemEnabled( UIPageMenu::Id_File_Delete, false );
        m_menu->setItemEnabled( UIPageMenu::Id_File_Trash, false );

        //
        // view
        //

        m_view = new UIPageView( this );
        m_view->setColumnVisible( UIPageView::Col_Link, false );
        m_view->setColumnVisible( UIPageView::Col_Nick, false );
        m_view->initColumnMenu( m_menu );

        connect( m_view, SIGNAL(clicked(QListViewItem *)),
                 this, SLOT(slot_ViewClicked(QListViewItem *)) );
        connect( m_view, SIGNAL(executed(QListViewItem *)),
                 this, SLOT(slot_ViewExecuted(QListViewItem *)) );
        connect( m_view, SIGNAL(contextMenu(QListViewItem *, const QPoint &)),
                 this, SLOT(slot_ViewMenu(QListViewItem *, const QPoint &)) );

        //
        // other data
        //

        m_count  = 0;
        m_items  = new ItemDict( 9973 );
        m_timer  = new QTimer( this );
        m_folder = KIconLoader().loadIcon( ICON_FOLDER, KIcon::Small );

        connect( m_timer, SIGNAL(timeout()),
                 this, SLOT(slot_ProcessNextFile()) );

        // reload asap
        QTimer * timer = new QTimer( this );
        connect( timer, SIGNAL(timeout()),SLOT(reload()) );
        timer->start( 0, true );

        //
        // title
        //

        updateTitle();

        //
        // page
        //

        layout()->setStretchFactor( m_view, 10 );
}
UILibraryPage::~UILibraryPage()
{
        delete m_items;
}

void UILibraryPage::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        }

        emit recvIO( io );
}

void UILibraryPage::slot_ViewClicked( QListViewItem * )
{
}

void UILibraryPage::slot_ViewExecuted( QListViewItem * )
{
        menu_AudioPlay();
}

void UILibraryPage::slot_ViewMenu( QListViewItem * , const QPoint & point )
{
        int id = m_menu->exec( point );

        switch ( id )
        {
        case UIPageMenu::Id_Select:
                menu_Select();
                break;

        case UIPageMenu::Id_Sort_Name:
                menu_Sort( UIPageView::Col_Name, id );
                break;
        case UIPageMenu::Id_Sort_Bitr:
                menu_Sort( UIPageView::Col_Bitr, id );
                break;
        case UIPageMenu::Id_Sort_Size:
                menu_Sort( UIPageView::Col_Size, id );
                break;
        case UIPageMenu::Id_Sort_Time:
                menu_Sort( UIPageView::Col_Time, id );
                break;
        case UIPageMenu::Id_Sort_Freq:
                menu_Sort( UIPageView::Col_Freq, id );
                break;
        case UIPageMenu::Id_Sort_Nick:
                menu_Sort( UIPageView::Col_Nick, id );
                break;

        case UIPageMenu::Id_Copy_Name:
                menu_Copy( UIPageView::Col_Name );
                break;
        case UIPageMenu::Id_Copy_Nick:
                menu_Copy( UIPageView::Col_Nick );
                break;
        case UIPageMenu::Id_Copy_Path:
                menu_Copy( UIPageView::Col_Path );
                break;
        case UIPageMenu::Id_Copy_Host:
                menu_Copy( UIPageView::Col_Host );
                break;

        case UIPageMenu::Id_Col_Name:
                menu_Column( UIPageView::Col_Name, id );
                break;
        case UIPageMenu::Id_Col_Bitr:
                menu_Column( UIPageView::Col_Bitr, id );
                break;
        case UIPageMenu::Id_Col_Size:
                menu_Column( UIPageView::Col_Size, id );
                break;
        case UIPageMenu::Id_Col_Time:
                menu_Column( UIPageView::Col_Time, id );
                break;
        case UIPageMenu::Id_Col_Freq:
                menu_Column( UIPageView::Col_Freq, id );
                break;
        case UIPageMenu::Id_Col_Link:
                menu_Column( UIPageView::Col_Link, id );
                break;
        case UIPageMenu::Id_Col_Nick:
                menu_Column( UIPageView::Col_Nick, id );
                break;
        case UIPageMenu::Id_Col_Path:
                menu_Column( UIPageView::Col_Path, id );
                break;
        case UIPageMenu::Id_Col_Host:
                menu_Column( UIPageView::Col_Host, id );
                break;

        case UIPageMenu::Id_Audio_Play:
                menu_AudioPlay();
                break;
        case UIPageMenu::Id_Audio_Pause:
                menu_AudioPause();
                break;
        case UIPageMenu::Id_Audio_Stop:
                menu_AudioStop();
                break;

        case UIPageMenu::Id_File_Copy:
                menu_FileCopy();
                break;
        case UIPageMenu::Id_File_Delete:
                menu_FileDelete();
                break;
        case UIPageMenu::Id_File_Rename:
                menu_FileRename();
                break;
        case UIPageMenu::Id_File_Trash:
                menu_FileTrash();
                break;
        }
}

void UILibraryPage::menu_AudioStop()
{
        KProcess proc;
        proc << "xmms" << "--stop";
        proc.start( KProcess::DontCare, KProcess::NoRead );
}

void UILibraryPage::menu_AudioPause()
{
        KProcess proc;
        proc << "xmms" << "--pause";
        proc.start( KProcess::DontCare, KProcess::NoRead );
}

void UILibraryPage::menu_AudioPlay()
{
        QList<QListViewItem> list = m_view->selectedItems();
        QListViewItem * item;
        KProcess        proc;
        QString         path;

        proc << "xmms" << "--play";

        for ( item = list.first(); item != 0; item = list.next() )
        {
                path = item->text( UIPageView::Col_Path );

                if ( path.isEmpty() )
                        continue ;

                proc << path;
        }

        proc.start( KProcess::DontCare, KProcess::NoRead );
}

void UILibraryPage::menu_Copy( int col_id )
{
        QListViewItem * item = m_view->currentItem();

        if ( item == 0 )
                return ;

        QApplication::clipboard()->setText( item->text( col_id ) );
}

void UILibraryPage::menu_Sort( int col_id, int menu_id )
{
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Name, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Bitr, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Size, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Time, false );
        m_menu->setItemChecked( UIPageMenu::Id_Sort_Nick, false );
        m_menu->setItemChecked( menu_id, true );

        m_view->setSorting( col_id, true );
        m_view->triggerUpdate();
}

void UILibraryPage::menu_Column( int col_id, int menu_id )
{
        bool visible = ( ! m_view->columnVisible( col_id ) );

        m_menu->setItemChecked( menu_id, visible );
        m_view->setColumnVisible( col_id, visible );
        m_view->triggerUpdate();
}

void UILibraryPage::menu_FileCopy()
{
}

void UILibraryPage::menu_FileDelete()
{
}

void UILibraryPage::menu_FileTrash()
{
}

void UILibraryPage::menu_FileRename()
{
        QList<QListViewItem> list = m_view->selectedItems();
        QListViewItem * item;
        QString         name, path, newname;
        QString         text;
        bool            accept;
        QFile           file;

        for ( item = list.first(); item != 0; item = list.next() )
        {
restart_operation:
                name   = item->text( UIPageView::Col_Name );
                path   = item->text( UIPageView::Col_Path );
                accept = false;
                text   = tr( "Rename file: %1" ).arg( name );

                if ( name.isEmpty() )
                        return ;

                newname = KLineEditDlg::getText( text, name, &accept, 0 );

                if ( accept == false )
                        continue ;
                if ( newname.isEmpty() )
                        continue ;

                QDir dir( IOSupport::stripFile( path )  );

                if ( dir.rename( name, newname ) == true )
                {
                        item->setText( UIPageView::Col_Name, newname );
                        item->setText( UIPageView::Col_Path,
                                dir.absFilePath( newname ) );
                        continue;
                }

                int response = QMessageBox::warning( this,
                        tr( "Operation failed!" ),
                        tr( "Unable to rename file. "
                            "Would you like to try again?" ),
                        QMessageBox::Retry,
                        QMessageBox::Cancel );

                switch ( response )
                {
                case QMessageBox::Retry:
                        goto restart_operation;
                        break;
                case QMessageBox::Cancel:
                        return;
                }
        }
}

void UILibraryPage::menu_Select()
{
        m_view->selectItemsDialog();
}

void UILibraryPage::updateTitle()
{
        QString text = tr( "Library: %1 file(s) shared" );
        title()->setText( text.arg( currentCountString() ) );
}

void UILibraryPage::reload()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
        c->setGroup( "Options - Transfer" );

        QStringList dirs = c->readListEntry( "send_path" );
        QStringList::Iterator it = dirs.begin();

        // clear the view
        m_view->clear();

        // start over count
        resetCount();

        // clear the pending list
        m_pending.clear();

        // add all the director entries onto the pending queue
        for ( ; it != dirs.end(); ++it )
        {
                QDir dir( *it, "*.mp3" );
                QStringList files = dir.entryList();
                QStringList::Iterator fit = files.begin();

                for ( ; fit != files.end(); ++fit )
                        m_pending.append( dir.absFilePath( *fit ) );
        }

        // all the files have been added, now start processing
        m_timer->start( 0, true );
}

void UILibraryPage::slot_ProcessNextFile()
{
        if ( m_pending.begin() == m_pending.end() )
                return ;

        QString path = m_pending.first();
        qWarning( "processing: %s", path.latin1() );

        m_pending.remove( path );

        QString fpath = QString( path ).replace( QRegExp( "/" ), "\\" );
        QStringList dirs = QStringList::split( "\\", fpath );
        //QPixmap pm0 = KIconLoader().loadIcon( ICON_FOLDER, KIcon::Small );

        // get or create the first item ?
        QListViewItem * item = m_view->firstChild();
        QListViewItem * next;

        // create the first item as needed
        if ( item == 0 )
        {
                item = new QListViewItem( m_view );
                item->setText( UIPageView::Col_Name, tr( "Library" ) );
                item->setOpen( true );
                item->setPixmap( UIPageView::Col_Name, m_folder );
	}

        // reset path
        QString name = item->text( UIPageView::Col_Name );

        // initialize the path
        for ( ; dirs.count() > 0; dirs.remove( dirs.begin() ) )
        {
                name += "\\" + dirs.first();
                next  = m_items->find( name );

                // if the item was not found, create a new one
                item = next == 0 ? new QListViewItem( item ) : next;

                // save the item name
                item->setText( UIPageView::Col_Name, dirs.first() );
                item->setOpen( true );
                item->setPixmap( UIPageView::Col_Name, m_folder );

                // make sure the item is in the dict
                m_items->replace( name, item );
        }

        // read mp3 info
        MP3Header mp3;

        if ( mp3.readMP3( path ) == true )
        {
                item->setText( UIPageView::Col_Bitr,
                        QString::number( mp3.bitrate ) );
                item->setText( UIPageView::Col_Freq,
                        QString::number( mp3.freq ) );
                item->setText( UIPageView::Col_Time,
                        IOSupport::timeText( QString::number( mp3.seconds ) ) );
        }

        // use file info
        QFileInfo info( path );

        item->setText( UIPageView::Col_Path, path );
        item->setText( UIPageView::Col_Size,
                IOSupport::sizeText( QString::number( info.size() ) ) );
        item->setPixmap( UIPageView::Col_Name, 0 );

        m_view->triggerUpdate();

        // set the timer again
        m_timer->start( 0, true );
}


