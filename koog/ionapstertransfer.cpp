/***************************************************************************
                          ionapstertransfer.cpp  -  description
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

#include <ctype.h> // for size reading

#include "iomessage.h"
#include "ionapstercodes.h"
#include "ionapstertransfer.h"
#include "uiconfig.h"

IONapsterTransfer::IONapsterTransfer(QObject *parent, const char *name)
                  :IOConnection(parent, name)
{
        __io    = new IOMessage( this );

        CHECK_PTR( __io );

        __xfer_timer = new QTimer( this );

        CHECK_PTR( __xfer_timer );

        connect( __xfer_timer, SIGNAL(timeout()),
                 this, SLOT(transferTimout()) );

        __rio   = 0;    // read io
        __sio   = 0;    // send io

        __xfer_bytes    = 0;
        __xfer_size     = 0;
        __xfer_state    = Offline;
        __is_updated    = false;
        __is_upload     = false;

        __error         = "";
        __usr_local     = "anonymous";
        __usr_remote    = "anonymous";
        __file_local    = "";
        __file_remote   = "";

        __rate_avg      = 0.0;
        __percent       = 0;
}
IONapsterTransfer::~IONapsterTransfer()
{
}

void IONapsterTransfer::recvIOEvent( IOMessage * io )
{
        if ( io == 0 )
                return ;

        switch ( io->messageType() )
        {
        }

        emit recvIO( io );
}

void IONapsterTransfer::sendIOEvent( IOMessage * io )
{
        if ( io == 0 )
                return ;

        switch ( io->messageType() )
        {
        }

        emit sendIO( io );
}

void IONapsterTransfer::handleHostFound()
{
        setTransferState( HostFound );
        triggerUpdateAvailable();
}

void IONapsterTransfer::handleConnected()
{
        setTransferState( Login );
        triggerUpdateAvailable();
}

void IONapsterTransfer::handleConnectionClosed()
{
        // force transfer the rest of the data
        while ( bytesAvailable() && transferBlock( true ) )
                ;

        finalizeTransferState();
        triggerUpdateAvailable();
}

void IONapsterTransfer::handleError( int )
{
        finalizeTransferState();
        triggerUpdateAvailable();
}

// Steps to download a file
//
// 1. Connect outgoing
// 2. Read '1' char
// 3. Send GET command, wait for flush
// 4. Send source user, name, and offset, wait for flush
// 5. Read size or "FILE NOT SHARED" or "INVALID REQUEST"
// 6. Read transfer block

// Steps to download a file (firewalled)
// 1. Accept incoming connection
// 2. Send '1' char, wait for flush
// 3. Read SEND command
// 4. Send source user, name and offset, wait for flush
// 5. Read size or "FILE NOT SHARED" or "INVALID REQUEST"
// 6. Read transfer block

void IONapsterTransfer::handleReadyRead()
{
        switch ( transferState() )
        {
        case Login:
                if ( ! transferReadLogin() )
                        break ;
                if ( ! transferSendCommand() )
                        break ;
                break;

        case Size:
                if ( ! transferReadSize() )
                        break ;
                break;

        case Block:
                if ( ! transferReadBlock() )
                        break ;
                break;
        }
}

void IONapsterTransfer::handleBytesWritten( int )
{
        switch ( transferState() )
        {
        // function transferSendCommand() puts us into the Name state,
        // so as soon as the command is sent, sent the name as well
        case Name:
                if ( ! transferSendName() )
                        break ;
                break;
        }
}

void IONapsterTransfer::triggerUpdateAvailable()
{
        __is_updated = true;
        emit updateAvailable( this );
        emit updateAvailable( this->connectionID() );
}

void IONapsterTransfer::appendTransferRate( double rate, uint max )
{
        if ( __rate.count() >= max )
                __rate.remove( __rate.first() );
        __rate.append( rate );

        // recalc rate

        QValueList<double>::Iterator it = __rate.begin();
        double value = 0.0;

        for ( ; it != __rate.end(); it++ )
                value += *it;

        __rate_avg = __rate.count() >= 3 ? value / __rate.count() : 0.0;

        // recalc percent

        if ( transferSize() == 0 )
                __percent = 100;   // default is always completed
        else
                __percent = ( totalTransferBytes() * 100 ) / transferSize();
}

bool IONapsterTransfer::transferReadLogin()
{
        char chr = '1';
        int xfer = readBlock ( &chr, 1 );

        if ( ( xfer < 1 ) || ( chr != '1' ) )
        {
                qWarning( "IONapsterTransfer::transferReadLogin(): "
                          "invalid xfer, aborting connection." );

                close();
                setTransferState( Error );
                triggerUpdateAvailable();
                return false;
        }
        else
        {
                qDebug( "IONapsterTransfer::transferReadLogin(): "
                        "read login" );

                setTransferState( Command );
                triggerUpdateAvailable();
                return true;
        }

}

bool IONapsterTransfer::transferSendCommand()
{
        int xfer = writeBlock( "GET", 3 );

        if ( xfer < 1 )
        {
                qWarning( "IONapsterTransfer::transferSendCommand(): "
                          "invalid xfer, aborting connection." );

                close();
                setTransferState( Error );
                triggerUpdateAvailable();
                return false;
        }
        else
        {
                qDebug( "IONapsterTransfer::transferSendCommand(): "
                        "sent: 'GET'" );
                setTransferState( Name );
                triggerUpdateAvailable();
                return true;
        }
}

bool IONapsterTransfer::transferSendName()
{
        QString data = "%1 \"%2\" %3";
        data = data.arg( localUser() );
        data = data.arg( remoteFile() );
        data = data.arg( "0" );

        int xfer = writeBlock( data.latin1(), data.length() );

        if ( xfer < 1 )
        {
                qWarning( "IONapsterTransfer::transferSendName(): "
                          "invalid xfer, aborting connection." );

                close();
                setTransferState( Error );
                triggerUpdateAvailable();
                return false;
        }
        else
        {
                qDebug( "IONapsterTransfer::transferSendName(): "
                        "sent: " + data );

                setTransferState( Size );
                triggerUpdateAvailable();
                return true;
        }
}

bool IONapsterTransfer::transferReadSize()
{
        char chr  = 0;
        int  left = bytesAvailable();
        int  xfer = 0;

        QString size;
        QString error;

        while ( left > 0 )
        {
                chr  = 0;
                xfer = readBlock( &chr, 1 );

                if ( xfer < 1 )
                {
                        error = "INVALID SIZE";
                        break;
                }

                left--;

                if ( isalpha( chr ) || isspace( chr ) )
                {
                        if ( ! size.isEmpty() ) // start of ID3 tag ?
                                break;
                        error += QChar( chr );
                }
                else if ( isdigit( chr ) )
                {
                        size  += QChar( chr );
                }
                else
                {
                        break;
                }
        }

        if ( size.isEmpty() || size.toInt() == 0 )
        {
                if ( ! error.isEmpty() )
                        __error = error.lower();
                else
                        __error = "zero file size";

                qWarning( "IONapsterTransfer::transferReadSize(): "
                          "invalid xfer, aborting connection." );

                close();
                setTransferState( Error );
                triggerUpdateAvailable();
                return false;
        }
        else
        {
                qDebug( "IONapsterTransfer::transferReadSize(): "
                        "read: " + size );
        }

        // setup io devices
        if ( uploadTransfer() )
        {
                __sio = this;
                __rio = new QFile( localFile() );

                if ( ! __rio->open( IO_ReadOnly ) )
                {
                        qWarning( "IONapsterTransfer::transferReadSize(): "
                                  "aborting connection: "
                                  "unable to open file read-only: " +
                                  localFile() );

                        close();
                        setTransferState( Error );
                        triggerUpdateAvailable();
                        return false;
                }
        }
        else
        {
                __rio = this;
                __sio = new QFile( localFile() );

                if ( ! __sio->open( IO_WriteOnly ) )
                {
                        qWarning( "IONapsterTransfer::transferReadSize(): "
                                  "aborting connection: "
                                  "unable to open file write-only: " +
                                  localFile() );

                        close();
                        setTransferState( Error );
                        triggerUpdateAvailable();
                        return false;
                }
        }

        // write leftover character?
        if ( chr != 0 )
        {
                if ( __sio->writeBlock( &chr, 1 ) == -1 )
                {
                        qWarning( "IONapsterTransfer::transferReadSize(): "
                                  "unable to write data output" );
                }
                else
                {
                        __xfer_bytes += 1;
                }
        }

        // reset rate time for first transfer
        __rate_time.restart();
        __block_time.restart();

        setTransferState( Block );
        setTransferSize( size.toInt() );
        triggerUpdateAvailable();
        return true;
}

bool IONapsterTransfer::transferBlock( bool force_xfer )
{
        // startup a block read timer to read data in larger chunks.
        // essentially we delay all reads at least 'x' millisecs here
        // and read them them. This allows larger blocks of data to
        // build up and read it all at once.
        //
        // another side effect is we can delay screen updates this same
        // amount of time, so the listview doesn't get crushed with all
        // these repaint events.

        if ( ! force_xfer && __xfer_timer->isActive() )
                return false;
        __xfer_timer->start( 1000, true );

        // read blocks
        QByteArray block;

        if ( __rio == 0 || __sio == 0 )
        {
                qWarning( "IONapsterTransfer::transferBlock(): "
                          "no IODevice setup, aborting connection." );

                close();
                setTransferState( Error );
                triggerUpdateAvailable();
                return false;
        }

        if ( uploadTransfer() )
                block.resize( 16384 );
        else
                block.resize( bytesAvailable() );

        // cleanup.. may affect performance
        block.fill( 0 );

        // can we read ?
        int read = __rio->readBlock ( block.data(), block.size() );

        if ( read < 0 )
        {
                qWarning( "IONapsterTransfer::transferBlock(): "
                          "invalid xfer, skipping to try later. "
                          "Read %i bytes.", read );
                return false;
        }

        int sent = __sio->writeBlock( block.data(), read );

        if ( sent < read )
        {
                qWarning( "IONapsterTransfer::transferBlock(): "
                          "certain data corruption: "
                          "read " + QString::number( read ) + "bytes, "
                          "sent " + QString::number( sent ) + "bytes." );
                qWarning( "IONapsterTransfer::transferBlock(): "
                          "no builtin correction. Please fix me!" );
        }

        __xfer_bytes += read;

        // average a new rate
        int    time = __rate_time.restart();
        double rate = (double) sent / time;
        appendTransferRate( rate, 20 ); // max rates

        // only update every 'x' millisecs
        triggerUpdateAvailable();
        return true;
}

void IONapsterTransfer::finalizeTransferState()
{
        // Is the transfer a success or not?
        //
        // 1. If there were 0 bytes sent/recv'd then we failed.
        // 2. If we don't know how many to sent/recv in total but we
        //    transfered at least a few bytes, it was a success.
        // 3. If we transfered all of the data, it was a success.
        // 4. Otherwise we failed.
        //

        qWarning( "finalize: size=%i bytes=%i", transferSize(),
                totalTransferBytes() );

        if ( transferSize() == 0 )
                setTransferState( Success );
        else if ( totalTransferBytes() >= transferSize() )
                setTransferState( Success );
        else
                setTransferState( Error );

        triggerUpdateAvailable();
}

