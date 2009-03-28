/***************************************************************************
                          uiconsolepage.cpp  -  description
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

#include "iomessage.h"
#include "ionapstercodes.h"
#include "uiconsolepage.h"
#include "uipagetext.h"

UIConsolePage::UIConsolePage(QWidget *parent, const char *name )
              :UIPage(parent,name)
{
        //
        // text
        //

        m_text = new UIPageText( this, "Console Text" );

        //
        // setup page
        //

        layout()->setStretchFactor( m_text, 10 );
}
UIConsolePage::~UIConsolePage()
{
}

void UIConsolePage::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::SocketHostFound:
                recvIO_SocketHostFound( io );
                break;
        case IONapsterCodes::SocketConnected:
                recvIO_SocketConnected( io );
                break;
        case IONapsterCodes::SocketConnectionClosed:
                recvIO_SocketConnectionClosed( io );
                break;
        case IONapsterCodes::SocketError:
                recvIO_SocketError( io );
                break;
        case IONapsterCodes::LoginReply:
                recvIO_LoginReply( io );
                break;

        case IONapsterCodes::SystemMessageReply:
                recvIO_SystemMessageReply( io );
                break;
        case IONapsterCodes::OpMessageReply:
                recvIO_OpMessageReply( io );
                break;
        case IONapsterCodes::GlobalMessageReply:
                recvIO_GlobalMessageReply( io );
                break;

        case IONapsterCodes::ServerPingRequest:
                recvIO_ServerPingRequest( io );
                break;
        case IONapsterCodes::ClientPingRequest:
                recvIO_ClientPingRequest( io );
                break;
        }

        emit recvIO( io );
}

void UIConsolePage::recvIO_SocketHostFound( IOMessage * io )
{
        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** Host found (napster://$host): connecting" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_SocketConnected( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** Connected, sending login" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_SocketConnectionClosed( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** Closed (napster://$host): " );
        text += tr( "read $rbytes bytes, sent $sbytes bytes" );
        text += "</font>";
        text += "<font color=\"dark green\">";
        text += tr( "-" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_SocketError( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** Error (napster://$host:$port): " );
        text += tr( "read $rbytes bytes, sent $sbytes bytes" );
        text += "</font>";
        text += "<font color=\"dark green\">";
        text += tr( "*** Error message: $error" );
        text += "</font>";
        text += "<font color=\"dark green\">";
        text += tr( "-" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_LoginReply( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** Login successfull" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
        m_text->append( "-" );
}

void UIConsolePage::recvIO_SystemMessageReply( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark green\">";
        text += tr( "*** $message" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_OpMessageReply( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark blue\">";
        text += tr( "*** (OPS) &lt;<strong>$nick<strong>&gt; $message" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_GlobalMessageReply( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark blue\">";
        text += tr( "*** (GLOBAL) &lt;<strong>$nick</strong>&gt; $message" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_ServerPingRequest( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark red\">";
        text += tr( "*** (SPING) The server is pinging you" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

void UIConsolePage::recvIO_ClientPingRequest( IOMessage * io )
{
        ASSERT( io );
        ASSERT( m_text );

        QString text;
        text += "<font color=\"dark red\">";
        text += tr( "*** (CPING) $nick is pinging you" );
        text += "</font>";
        m_text->append( io->formatVariables( text ) );
}

