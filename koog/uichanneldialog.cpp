/***************************************************************************
                          uichanneldialog.cpp  -  description
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

#include "iomessage.h"
#include "ionapstercodes.h"

#include "uichanneldialog.h"
#include "uiconfig.h"

UIChannelDialog::UIChannelDialog(QWidget *parent, const char *name )
                :UIChannelDialogBase(parent,name,true)
{
        // this must be called to create the listview items
        slot_ChanToggled( false );
        toggleEnabled( false );
}
UIChannelDialog::~UIChannelDialog()
{
}

void UIChannelDialog::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::ListChansReply:
                recvIO_ListChansReply( io );
                break;
        case IONapsterCodes::ListChansDone:
                recvIO_ListChansDone( io );
                break;
        case IONapsterCodes::ListAllChansReply:
                recvIO_ListAllChansReply( io );
                break;
        case IONapsterCodes::ListAllChansDone:
                recvIO_ListAllChansDone( io );
                break;
        }

        emit recvIO( io );
}

void UIChannelDialog::sendIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        }

        emit sendIO( io );
}

void UIChannelDialog::recvIO_ListChansReply( IOMessage * io )
{
        QListViewItem * item = new QListViewItem( m_itemNapster );
        item->setText( Col_Chan, io->find( "channel" ) );
        item->setText( Col_Size, io->find( "size" ) );
        item->setText( Col_Topic, io->find( "message" ) );
}

void UIChannelDialog::recvIO_ListChansDone( IOMessage * )
{
        toggleEnabled( true );
}

void UIChannelDialog::recvIO_ListAllChansReply( IOMessage * io )
{
        QListViewItem * item;

        if ( io->find( "extra" ) == "1" )
                item = new QListViewItem( m_itemOther );
        else
                item = new QListViewItem( m_itemNapster );

        item->setText( Col_Chan, io->find( "channel" ) );
        item->setText( Col_Size, io->find( "size" ) );
        item->setText( Col_Topic, io->find( "message" ) );
}

void UIChannelDialog::recvIO_ListAllChansDone( IOMessage * )
{
        toggleEnabled( true );
}

void UIChannelDialog::slot_ViewClicked( QListViewItem * )
{
}

void UIChannelDialog::slot_ViewExecuted( QListViewItem * )
{
        slot_Join();
}

void UIChannelDialog::slot_ViewMenu( QListViewItem *, const QPoint & )
{
}

void UIChannelDialog::slot_Join()
{
        m_view->firstChild();

        QListViewItemIterator it( m_view );
        QListViewItem * item;

        for ( ; ( item = it.current() ); ++it )
        {
                if ( item->text( Col_Size ).isEmpty() == true )
                        continue ;
                if ( item->isSelected() == false )
                        continue ;

                IOMessage * io = new IOMessage( 0 );
                io->setMessageType( IONapsterCodes::ChanJoinRequest );
                io->insert( "rawdata", item->text( Col_Chan ) );
                emit sendIO( io );

                delete io;
        }

        accept();
}

void UIChannelDialog::slot_ChanToggled( bool all_chans )
{
        m_view->clear();

        m_itemNapster = new QListViewItem( m_view );
        m_itemNapster->setText( Col_Chan, tr( "Napster channels" ) );
        m_itemNapster->setOpen( true );

        m_itemOther = new QListViewItem( m_view );
        m_itemOther->setText( Col_Chan, tr( "Other channels" ) );
        m_itemOther->setOpen( true );

        IOMessage * io = new IOMessage( 0 );

        if ( all_chans == true )
                io->setMessageType( IONapsterCodes::ListAllChansRequest );
        else
                io->setMessageType( IONapsterCodes::ListChansRequest );

        emit sendIO( io );
        delete io;

        toggleEnabled( false );
}

void UIChannelDialog::toggleEnabled( bool enable )
{
        m_view->setEnabled( enable );
        m_buttonJoin->setEnabled( enable );
}

