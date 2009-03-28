/***************************************************************************
                          uiconsolepage.h  -  description
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

#ifndef UICONSOLEPAGE_H
#define UICONSOLEPAGE_H

#include <qwidget.h>

// internal
#include "uipage.h"

// classes
class IOMessage;
class UIPageText;

/**
  *@author Ian Zepp
  */

class UIConsolePage : public UIPage
{
        Q_OBJECT
public: 
	UIConsolePage(QWidget *parent=0, const char *name=0);
	~UIConsolePage();

public slots:
        void recvIOEvent( IOMessage * );

protected:
        void recvIO_SocketHostFound( IOMessage * );
        void recvIO_SocketConnected( IOMessage * );
        void recvIO_SocketConnectionClosed( IOMessage * );
        void recvIO_SocketError( IOMessage * );
        void recvIO_LoginReply( IOMessage * );

        void recvIO_SystemMessageReply( IOMessage * );
        void recvIO_OpMessageReply( IOMessage * );
        void recvIO_GlobalMessageReply( IOMessage * );

        void recvIO_ServerPingRequest( IOMessage * );
        void recvIO_ClientPingRequest( IOMessage * );

private:
        UIPageText              * m_text;
};

#endif
