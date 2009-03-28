#include "ioconnection.h"

IOConnection::IOConnection(QObject *parent, const char *name)
             :QSocket(parent, name)
{
        __conn_state    = 0;
        __conn_id       = 0;
        __verbose       = true;

        connect( this, SIGNAL(hostFound()),
                 this, SLOT(internalHostFound()) );
        connect( this, SIGNAL(connected()),
                 this, SLOT(internalConnected()) );
        connect( this, SIGNAL(connectionClosed()),
                 this, SLOT(internalConnectionClosed()) );
        connect( this, SIGNAL(error(int)),
                 this, SLOT(internalError(int)) );
        connect( this, SIGNAL(readyRead()),
                 this, SLOT(internalReadyRead()) );
        connect( this, SIGNAL(bytesWritten(int)),
                 this, SLOT(internalBytesWritten(int)) );
}

IOConnection::~IOConnection()
{}

void IOConnection::internalHostFound()
{
        if ( verboseIO() )
                qWarning( "IOConnection::internalHostFound(): "
                          "hostname " + peerName() + ":" +
                          QString::number( peerPort() ) );

        handleHostFound();
}

void IOConnection::internalConnected()
{
        if ( verboseIO() )
                qWarning( "IOConnection::internalConnected(): "
                          "hostname " + peerName() + ":" +
                          QString::number( peerPort() ) );

        // reset to last time connected
        __conn_time.restart();

        handleConnected();
}

void IOConnection::internalConnectionClosed()
{
        if ( verboseIO() )
                qWarning( "IOConnection::internalConnectionClosed(): "
                          "hostname " + peerName() + ":" +
                          QString::number( peerPort() ) );

        // reset to last time disconnected
        __conn_time.restart();

        handleConnectionClosed();
}

void IOConnection::internalError( int num )
{
        if ( verboseIO() )
                qWarning( "IOConnection::internalError(int): "
                          "hostname " + peerName() + ":" +
                          QString::number( peerPort() ) + ":" +
                          "error = " + QString::number( num ) );

        handleError( num );
}

void IOConnection::internalReadyRead()
{
        __last_read.restart();

        handleReadyRead();
}

void IOConnection::internalBytesWritten( int num )
{
        __last_write.restart();

        handleBytesWritten( num );
}






