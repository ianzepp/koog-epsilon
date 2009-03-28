/***************************************************************************
                          ionapstertransfer.h  -  description
                             -------------------
    begin                : Mon Feb 12 2001
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


#ifndef IONAPSTERTRANSFER_H
#define IONAPSTERTRANSFER_H

#include <qobject.h>
#include <qsocket.h>
#include <qstring.h>
#include <qcstring.h>
#include <qregexp.h>
#include <qdatastream.h>
#include <qtextstream.h>
#include <qvaluelist.h>
#include <qiodevice.h>
#include <qfile.h>
#include <qdatetime.h>
#include <qtimer.h>

// kde
#include <ksimpleconfig.h>

// internal
#include "ioconnection.h"

/**
  *@author Ian Zepp
  */

class IOMessage;

class IONapsterTransfer : public IOConnection  {
   Q_OBJECT
public: 
	IONapsterTransfer(QObject *parent=0, const char *name=0);
	virtual ~IONapsterTransfer();

        enum { Offline, HostFound, Login, Command,
               Name, Size, Block, Success, Error, Cancelled };

        Q_INT32 transferState()                 { return __xfer_state;  };
        void setTransferState( Q_INT32 num )    { __xfer_state = num;   };

        /** returns the last error, if available */
        const QString & transferError()         { return __error;       };

        Q_INT32 totalTransferBytes()            { return __xfer_bytes;  };
        QString totalTransferBytesString()
                { return QString::number( __xfer_bytes ); };

        Q_INT32 transferSize()                  { return __xfer_size;    };
        QString transferSizeString()
                { return QString::number( __xfer_size ); };

        /** set the total transfer size */
        void setTransferSize( Q_INT32 num )     { __xfer_size = num;     };

        /** returns whether an update is available or not */
        bool updateAvailable()                  { return __is_updated;  };
        /** set the update available flag */
        void triggerUpdateAvailable();

        /** returns the transfer read rate as a float value */
        double  transferRate()                  { return __rate_avg; };
        QString transferRateString()
                { return QString().sprintf( "%2.2f", __rate_avg ); };

        /** returns the percentage complete */
        Q_INT32 transferPercent()               { return __percent;     };
        QString transferPercentString()
                { return QString::number( __percent ); };

        const QString & localUser()             { return __usr_local;   };
        void setLocalUser( const QString & s )  { __usr_local = s;      };

        const QString & localFile()             { return __file_local;  };
        void setLocalFile( const QString & s )  { __file_local = s;     };

        const QString & remoteUser()            { return __usr_remote;  };
        void setRemoteUser( const QString & s ) { __usr_remote = s;     };

        const QString & remoteFile()            { return __file_remote; };
        void setRemoteFile( const QString & s ) { __file_remote = s;    };

        bool uploadTransfer()                   { return __is_upload;   };
        void setUploadTransfer( bool b )        { __is_upload = b;      };

public slots:
        void recvIOEvent( IOMessage * );
        void sendIOEvent( IOMessage * );
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

protected:
        virtual void handleHostFound();
        virtual void handleConnected();
        virtual void handleConnectionClosed();
        virtual void handleError( int );
        virtual void handleReadyRead();
        virtual void handleBytesWritten( int );

protected:
        bool transferReadLogin();
        bool transferSendCommand();
        bool transferSendName();
        bool transferReadSize();
        bool transferReadBlock()        { return transferBlock(); };
        bool transferSendBlock()        { return transferBlock(); };

private:
        bool transferBlock( bool force_xfer = false );

        /** add a new rate, update avg and percetage */
        void appendTransferRate( double, uint max );

        /** decide if the transfer was a success or not */
        void finalizeTransferState();

private slots:
        void transferTimeout()          { transferBlock();      };

private:
        IOMessage       * __io;
        Q_INT32           __xfer_bytes;
        Q_INT32           __xfer_size;
        Q_INT32           __xfer_state;
        bool              __is_updated;
        bool              __is_upload;
        QString           __usr_local;
        QString           __usr_remote;
        QString           __file_local;
        QString           __file_remote;
        QString           __error;

        QValueList<double> __rate;
        double            __rate_avg;
        QTime             __rate_time;
        Q_INT32           __percent;

        QIODevice       * __rio;
        QIODevice       * __sio;

        QTime             __block_time;
        QTimer          * __xfer_timer;

signals:
        /** update signal: using this pointer */
        void updateAvailable( IONapsterTransfer * );
        /** update signal: using this->connectionID() value */
        void updateAvailable( Q_INT32 );
};

#endif
