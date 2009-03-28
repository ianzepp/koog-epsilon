#ifndef IONAPSTERCONNECTION_H
#define IONAPSTERCONNECTION_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qapp.h>
#include <qcstring.h>
#include <qdatastream.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qtimer.h>
#include <qurl.h>

// kde
#include <ksimpleconfig.h>

// internal
#include "ioconnection.h"

class IOMessage;

class IONapsterConnection : public IOConnection
{
        Q_OBJECT
public:
        IONapsterConnection(QObject *parent=0, const char *name=0);
        ~IONapsterConnection();

        Q_UINT32 totalReadMessages();
        QString  totalReadMessagesString();

        Q_UINT32 totalSentMessages();
        QString  totalSentMessagesString();

        Q_UINT32 totalReadBytes();
        QString  totalReadBytesString();

        Q_UINT32 totalSentBytes();
        QString  totalSentBytesString();

        /** find the best host */
        void napsterBestHost();
        /** start a connection */
        void napsterConnect();
        /** close a connection */
        void napsterDisconnect();

public slots:
        void recvIOEvent( IOMessage * );
        void sendIOEvent( IOMessage * );
signals:
        void recvIO( IOMessage * );
        void sendIO( IOMessage * );

protected:
        void recvIO_RegisteredReply( IOMessage * );
        void recvIO_RegisteredError( IOMessage * );
        void recvIO_RegisteredInvalid( IOMessage * );
        void recvIO_LoginReply( IOMessage * );

protected:
        /** method called when the hostFound() signal is received */
        virtual void handleHostFound();
        /** method called when the connected() signal is received */
        virtual void handleConnected();
        /** method called when the connectionClosed() signal is received */
        virtual void handleConnectionClosed();
        /** method called when the error(int) signal is received */
        virtual void handleError( int );
        /** method called when the readyRead(int) signal is received */
        virtual void handleReadyRead();
        /** method called when the bytesWritten(int) signal is received */
        virtual void handleBytesWritten( int );

protected:
        /** read a message and handle. Returns whether to read again */
        bool handleReadOnce();

        /** reads the best host, resets, reconnects */
        void handleReadBestHost();

        /** connect automatically on startup? */
        void handleAutoConnect();

        void sendRegisteredRequest();
        void sendLoginRequest( IOMessage * );
        void saveBestHost( const QString & );

private:
        QDataStream __stream;

        Q_UINT16    __size;
        Q_UINT16    __type;
        QByteArray  __data;

        IOMessage * __io;

        Q_UINT32    __num_rio;          // read io messages
        Q_UINT32    __num_sio;          // sent io messages
        Q_UINT32    __num_rbytes;       // read bytes
        Q_UINT32    __num_sbytes;       // sent bytes

        bool        __reading;
        bool        __redirect;
};

inline Q_UINT32 IONapsterConnection::totalReadMessages()
{
        return __num_rio;
}

inline QString IONapsterConnection::totalReadMessagesString()
{
        return QString::number( __num_rio );
}

inline Q_UINT32 IONapsterConnection::totalSentMessages()
{
        return __num_sio;
}

inline QString IONapsterConnection::totalSentMessagesString()
{
        return QString::number( __num_sio );
}

inline Q_UINT32 IONapsterConnection::totalReadBytes()
{
        return __num_rbytes;
}

inline QString IONapsterConnection::totalReadBytesString()
{
        return QString::number( __num_rbytes );
}

inline Q_UINT32 IONapsterConnection::totalSentBytes()
{
        return __num_sbytes;
}

inline QString IONapsterConnection::totalSentBytesString()
{
        return QString::number( __num_sbytes );
}

#endif

