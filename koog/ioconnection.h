#ifndef IOCONNECTION_H
#define IOCONNECTION_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qsocket.h>
#include <qdatetime.h>

class IOConnection : public QSocket
{
        Q_OBJECT
public:
        IOConnection(QObject *parent=0, const char *name=0);
        virtual ~IOConnection();

        Q_INT32 connectionState()               { return __conn_state;  };
        void setConnectionState( Q_INT32 num )  { __conn_state = num;   };

        Q_INT32 connectionID()                  { return __conn_id;     };
        void setConnectionID( Q_INT32 num )     { __conn_id = num;      };

        const QTime & connectionTime()          { return __conn_time;   };
        const QTime & lastReadTime()            { return __last_read;   };
        const QTime & lastWriteTime()           { return __last_write;  };

        bool verboseIO()                        { return __verbose;     };
        void setVerboseIO( bool set )           { __verbose = set;      };

protected:
        virtual void handleHostFound()          {};
        virtual void handleConnected()          {};
        virtual void handleConnectionClosed()   {};
        virtual void handleError( int )         {};
        virtual void handleReadyRead()          {};
        virtual void handleBytesWritten( int )  {};

private slots:
        void internalHostFound();
        void internalConnected();
        void internalConnectionClosed();
        void internalError( int );
        void internalReadyRead();
        void internalBytesWritten( int );

private:
        Q_INT32 __conn_state;
        Q_INT32 __conn_id;
        QTime   __conn_time;
        QTime   __last_read;
        QTime   __last_write;
        bool    __verbose;
};

#endif

