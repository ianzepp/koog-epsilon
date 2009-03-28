#include "ionapsterconnection.h"
#include "ionapstercodes.h"
#include "iomessage.h"
#include "iosupport.h"
#include "uiconfig.h"

IONapsterConnection::IONapsterConnection(QObject *parent, const char *name)
                    :IOConnection(parent, name)
{
        __stream.setDevice( this );
        __stream.setByteOrder( QDataStream::LittleEndian );

        __size          = 0;
        __type          = 0;
        __data.fill( 0 );
        __io            = new IOMessage( this );

        __num_rio       = 0;
        __num_sio       = 0;

        __num_rbytes    = 0;
        __num_sbytes    = 0;

        __reading       = false;
        __redirect      = false;
}

IONapsterConnection::~IONapsterConnection()
{
}

void IONapsterConnection::recvIOEvent( IOMessage * io )
{
        // verbose ?
        if ( verboseIO() )
                qWarning( "IONapsterConnection::recvIOEvent(IOMessage *): "
                          "type " + QString::number( io->messageType() ) +
                          ": " + io->find( "rawdata" ) );

        switch ( io->messageType() )
        {
        case IONapsterCodes::RegisteredReply:
                recvIO_RegisteredReply( io );
                break;
        case IONapsterCodes::RegisteredError:
                recvIO_RegisteredError( io );
                break;
        case IONapsterCodes::RegisteredInvalid:
                recvIO_RegisteredInvalid( io );
                break;

        case IONapsterCodes::LoginReply:
                recvIO_LoginReply( io );
                break;
        }

        //
        // relay the message
        //

        emit recvIO( io );

        __num_rio++;
}

void IONapsterConnection::sendIOEvent( IOMessage * io )
{
        QStringList list;
        QString     data;

        switch ( io->messageType() )
        {
        case IONapsterCodes::RegisteredRequest:
                list.append( io->find( "nick" ) );
                data = IOSupport::quoteJoin( list );
                break;

        case IONapsterCodes::LoginRequest:
                list.append( io->find( "nick" ) );
                list.append( io->find( "pass" ) );
                list.append( io->find( "port" ) );
                list.append( io->find( "client" ) );
                list.append( io->find( "speed" ) );
                data = IOSupport::quoteJoin( list );
                break;

        case IONapsterCodes::LoginCreate:
                list.append( io->find( "nick" ) );
                list.append( io->find( "pass" ) );
                list.append( io->find( "port" ) );
                list.append( io->find( "client" ) );
                list.append( io->find( "speed" ) );
                list.append( io->find( "email" ) );
                data = IOSupport::quoteJoin( list );
                break;

        case IONapsterCodes::DownloadRequest:
                list.append( io->find( "nick" ) );
                list.append( io->find( "path" ) );
                data = IOSupport::quoteJoin( list );
                break;

        case IONapsterCodes::BrowseRequest:
                list.append( io->find( "nick" ) );
                data = IOSupport::quoteJoin( list );
                break;

        default:
                data = io->find( "rawdata" );
                break;
        }

        // verbose ?
        if ( verboseIO() )
                qWarning( "IONapsterConnection::sendIOEvent(IOMessage *): "
                          "type " + QString::number( io->messageType() ) +
                          ": " + data );

        //
        // relay the message
        //

        emit sendIO( io );

        //
        // send the message out
        //

        __stream << (Q_UINT16) data.length();
        __stream << (Q_UINT16) io->messageType();
        __stream.writeRawBytes( data.latin1(), data.length() );

        __num_sio++;
}

void IONapsterConnection::handleHostFound()
{
        __io->clear();
        __io->setMessageType( IONapsterCodes::SocketHostFound );
        __io->insert( "host", peerName() );
        __io->insert( "port", QString::number( peerPort() ) );
        recvIOEvent( __io );
}

void IONapsterConnection::handleConnected()
{
        __io->clear();
        __io->setMessageType( IONapsterCodes::SocketConnected );
        __io->insert( "host", peerName() );
        __io->insert( "port", QString::number( peerPort() ) );
        recvIOEvent( __io );

        if ( ! __redirect )
                sendRegisteredRequest();
}

void IONapsterConnection::handleConnectionClosed()
{
        __io->clear();
        __io->setMessageType( IONapsterCodes::SocketConnectionClosed );
        __io->insert( "host",   peerName() );
        __io->insert( "port",   QString::number( peerPort() ) );
        __io->insert( "rio",    totalReadMessagesString() );
        __io->insert( "sio",    totalSentMessagesString() );
        __io->insert( "rbytes", totalReadBytesString() );
        __io->insert( "sbytes", totalSentBytesString() );
        recvIOEvent( __io );

        __num_rio = 0;
        __num_sio = 0;

        __num_rbytes = 0;
        __num_sbytes = 0;
}

void IONapsterConnection::handleError( int errno )
{
        __io->clear();
        __io->setMessageType( IONapsterCodes::SocketConnected );
        __io->insert( "host",   peerName() );
        __io->insert( "port",   QString::number( peerPort() ) );
        __io->insert( "error",  QString::number( errno ) );
        __io->insert( "rio",    totalReadMessagesString() );
        __io->insert( "sio",    totalSentMessagesString() );
        __io->insert( "rbytes", totalReadBytesString() );
        __io->insert( "sbytes", totalSentBytesString() );
        recvIOEvent( __io );

        __num_rio = 0;
        __num_sio = 0;

        __num_rbytes = 0;
        __num_sbytes = 0;
}

void IONapsterConnection::handleReadyRead()
{
        // is this a pure best host redirection ?
        if ( __redirect )
        {
                handleReadBestHost();
                return;
        }

        // otherwise handle event normally
        if ( __reading )
                return ;
        __reading = true;

        for ( int i = 1; handleReadOnce() ; i++ ) ;
//                if ( i % 100 == 0 )
//                        qApp->processEvents();

        __reading = false;
}

void IONapsterConnection::handleBytesWritten( int num )
{
        __num_sbytes += num ;
}

void IONapsterConnection::recvIO_RegisteredReply( IOMessage * io )
{
        if ( verboseIO() )
                qWarning( "IONapsterConnection::handleRegisteredReply()" );
        sendLoginRequest( io );
}

void IONapsterConnection::recvIO_RegisteredError( IOMessage * io )
{
        if ( verboseIO() )
                qWarning( "IONapsterConnection::handleRegisteredError()" );
        sendLoginRequest( io );
}

void IONapsterConnection::recvIO_RegisteredInvalid( IOMessage * )
{
        if ( verboseIO() )
                qWarning( "IONapsterConnection::handleRegisteredInvalid()" );
}

void IONapsterConnection::recvIO_LoginReply( IOMessage * )
{
        if ( verboseIO() )
                qWarning( "IONapsterConnection::handleLoginReply()" );
}

void IONapsterConnection::sendRegisteredRequest()
{
        if ( verboseIO() )
                qWarning( "IONapsterConnection::sendRegisteredRequest()" );

        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
	c->setGroup( "Options - User" );

        // we have to create a new iomessage inside this class
        IOMessage * newio = new IOMessage();
        newio->setMessageType( IONapsterCodes::RegisteredRequest );
        newio->insert( "nick", c->readEntry( "nick" ) );
        sendIOEvent( newio );

        delete newio;
}

void IONapsterConnection::sendLoginRequest( IOMessage * )
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
	c->setGroup( "Options - User" );

        // create the list data
        QString nick   = c->readEntry( "nick" );
        QString pass   = c->readEntry( "pass" );
        QString speed  = c->readEntry( "speed" );
        QString client = c->readEntry( "client" );
        bool firewall  = c->readBoolEntry( "firewall" );
        QString port   = QString::null;
        QString email  = "anon@napster.com";

        if ( firewall )
                port = "0";
        else
                port = "0";

        // we have to create a new iomessage inside this class
        IOMessage * newio = new IOMessage( 0 );
        newio->setMessageType( IONapsterCodes::LoginRequest );
        newio->insert( "nick", nick );
        newio->insert( "pass", pass );
        newio->insert( "port", port );
        newio->insert( "client", nick );
        newio->insert( "speed", speed );
        newio->insert( "email", email );
        sendIOEvent( newio );

        delete newio;
}

void IONapsterConnection::napsterBestHost()
{
        __redirect = true;

        connectToHost( "server.napster.com", 8875 );
}

void IONapsterConnection::napsterConnect()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
	c->setGroup( "Options - Server" );

        QUrl url( c->readEntry( "current" ) );

        connectToHost( url.host(), url.port() );
}

void IONapsterConnection::napsterDisconnect()
{
        __io->clear();
        __io->setMessageType( IONapsterCodes::SocketConnectionClosed );
        __io->insert( "host",   peerName() );
        __io->insert( "port",   QString::number( peerPort() ) );
        __io->insert( "rio",    totalReadMessagesString() );
        __io->insert( "sio",    totalSentMessagesString() );
        __io->insert( "rbytes", totalReadBytesString() );
        __io->insert( "sbytes", totalSentBytesString() );
        recvIOEvent( __io );

        __num_rio = 0;
        __num_sio = 0;

        __num_rbytes = 0;
        __num_sbytes = 0;

        if ( state() != Idle )
                close();
}

void IONapsterConnection::handleReadBestHost()
{
        int avail = bytesAvailable();

        if ( ! avail )
                return ;

        __data.resize( avail );
        int recv = readBlock( __data.data(), avail );

        if ( recv < 1 )
                return ;

        QString read = __data.data();
        read.truncate( recv );

        if ( verboseIO() )
                qWarning( "IONapsterConnection::handleReadBestHost(): "
                          "found best host: %s", read.latin1() );

        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );
	c->setGroup( "Options - Server" );
        c->writeEntry( "current", "napster://" + read );
        c->sync();

        // reset, connect normally
        __redirect = false;

        napsterDisconnect();
        napsterConnect();
}

bool IONapsterConnection::handleReadOnce()
{
        if ( ( __size == 0 ) && ( __type == 0 ) )
        {
                if ( bytesAvailable() < 4 )
                        return false ;

                __stream >> __size ;
                __stream >> __type ;
        }

        if ( bytesAvailable() < __size )
                return false ;

        __data.resize( __size ) ;
        __stream.readRawBytes( __data.data(), __size ) ;

        __num_rbytes += 4;
        __num_rbytes += __size;

        // parse the message
        __io->clear();
        __io->setMessageType( __type );

        // the reason splitting the list is not done first is that
        // some messages (ie channel text) will often have an invalid
        // number of quotes. So in some cases it is better to read
        // from a stream than dequote directly.

	QString data = __data;
        data.truncate( __size );

	QStringList list;
        QString     temp;
	QTextStream stream( &data, IO_ReadOnly );

        // save the original message
        __io->insert( "rawdata", data );

	switch ( __type )
	{

        //
        // login and system stuff we mostly ignore
        //

	case IONapsterCodes::LoginReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "email", list[0] );
                break;

	case IONapsterCodes::RegisteredReply:
                break;

	case IONapsterCodes::RegisteredError:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                break;

	case IONapsterCodes::RegisteredInvalid:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                break;

	case IONapsterCodes::SystemMessageReply:
                temp = stream.read();
                __io->insert( "message", IOSupport::replaceCarets( temp ) );
                __io->insert( "message.orig", temp );
                break;

	case IONapsterCodes::ServerStats:
		stream >> temp;
                __io->insert( "users", temp );

		stream >> temp;
                __io->insert( "files", temp );

		stream >> temp;
                __io->insert( "size", temp );
                break;

	case IONapsterCodes::GeneralError:
                temp = stream.read();
                __io->insert( "message", IOSupport::replaceCarets( temp ) );
                __io->insert( "message.orig", temp );
                break;

        //
        // search codes
        //

	case IONapsterCodes::SearchRequest:
		break;

	case IONapsterCodes::SearchReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "path", list[0] );
                __io->insert( "directory", IOSupport::stripFile( list[0] ) );
                __io->insert( "name", IOSupport::stripDir( list[0] ) );
                __io->insert( "md5sum", list[1] );
                __io->insert( "size", IOSupport::sizeText( list[2] ) );
                __io->insert( "bitrate", list[3] );
                __io->insert( "freq", list[4] );
                __io->insert( "time", IOSupport::timeText( list[5] ) );
                __io->insert( "nick", list[6] );
                __io->insert( "host", IOSupport::networkToAscii( list[7] ) );
                __io->insert( "speed", IOSupport::speedText( list[8] ) );
                __io->insert( "weight", list[9] );

                // original values
                __io->insert( "size.orig", list[2] );
                __io->insert( "time.orig", list[5] );
                __io->insert( "speed.orig", list[8] );
		break;

	case IONapsterCodes::SearchDone:
		break;

        //
        // Download / queued codes
        //

	case IONapsterCodes::DownloadReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "host", IOSupport::networkToAscii( list[1] ) );
                __io->insert( "port", list[2] );
                __io->insert( "path", list[3] );
                __io->insert( "directory", IOSupport::stripFile( list[3] ) );
                __io->insert( "name", IOSupport::stripDir( list[3] ) );
                __io->insert( "speed", IOSupport::speedText( list[5] ) );

                // original values
                __io->insert( "host.orig", list[1] );
                __io->insert( "speed.orig", list[5] );
		break;

	case IONapsterCodes::DownloadError:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "path", list[1] );
                __io->insert( "directory", IOSupport::stripFile( list[1] ) );
                __io->insert( "name", IOSupport::stripDir( list[1] ) );
		break;

	case IONapsterCodes::QueueLimitReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "path", list[1] );
                __io->insert( "directory", IOSupport::stripFile( list[1] ) );
                __io->insert( "name", IOSupport::stripDir( list[1] ) );
                __io->insert( "size", IOSupport::sizeText( list[5] ) );
                __io->insert( "limit", list[3] );

                // original values
                __io->insert( "size.orig", list[5] );
		break;

        //
        // hotlist codes
        //

	case IONapsterCodes::HotlistAddReply:
                __io->insert( "nick", data );
                break;

	case IONapsterCodes::HotlistAddError:
                __io->insert( "nick", data );
                break;

	case IONapsterCodes::HotlistLogon:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "speed", IOSupport::speedText( list[2] ) );
                __io->insert( "speed.orig", list[2] );
		break;

	case IONapsterCodes::HotlistLogoff:
                __io->insert( "nick", data );
                break;

        //
        // channel codes
        //

	case IONapsterCodes::ChanPartRequest:
                __io->insert( "channel", data );
                break;

	case IONapsterCodes::ChanJoinReply:
                __io->insert( "channel", data );
                break;

	case IONapsterCodes::ChanList:
		list = IOSupport::quoteSplit( data );

                __io->insert( "channel", list[0] );
                __io->insert( "nick", list[1] );
                __io->insert( "size", list[2] );
                __io->insert( "speed", IOSupport::speedText( list[3] ) );
                __io->insert( "speed.orig", list[3] );
                break;

	case IONapsterCodes::ChanListDone:
                __io->insert( "channel", data );
                break;

	case IONapsterCodes::ChanJoin:
		list = IOSupport::quoteSplit( data );

                __io->insert( "channel", list[0] );
                __io->insert( "nick", list[1] );
                __io->insert( "size", list[2] );
                __io->insert( "speed", IOSupport::speedText( list[3] ) );
                __io->insert( "speed.orig", list[3] );
                break;

	case IONapsterCodes::ChanPart:
		list = IOSupport::quoteSplit( data );

                __io->insert( "channel", list[0] );
                __io->insert( "nick", list[1] );
                __io->insert( "size", list[2] );
                __io->insert( "speed", IOSupport::speedText( list[3] ) );
                __io->insert( "speed.orig", list[3] );
                break;

	case IONapsterCodes::ChanMessage:
		stream >> temp;
                __io->insert( "channel", temp );

		stream >> temp;
                __io->insert( "nick", temp );

                temp = stream.read();
                __io->insert( "message", IOSupport::replaceCarets( temp ) );
                __io->insert( "message.orig", temp );
                break;

	case IONapsterCodes::ChanEmote:
		stream >> temp;
                __io->insert( "channel", temp );

		stream >> temp;
                __io->insert( "nick", temp );

                temp = stream.read();
                __io->insert( "message", IOSupport::replaceCarets( temp ) );
                __io->insert( "message.orig", temp );
                break;

	case IONapsterCodes::ChanTopic:
		stream >> temp;
                __io->insert( "channel", temp );

                temp = stream.read();
                __io->insert( "message", IOSupport::replaceCarets( temp ) );
                __io->insert( "message.orig", temp );
                break;

	case IONapsterCodes::ChanMotd:
		list = IOSupport::quoteSplit( data );

                __io->insert( "channel", list[0] );
                __io->insert( "message", IOSupport::replaceCarets( list[1] ) );
                __io->insert( "message.orig", list[1] );
                break;

        //
        // private messages
        //

	case IONapsterCodes::UserMessageReply:
		stream >> temp;
                __io->insert( "nick", temp );
                __io->insert( "message", stream.read() );
                break;

	case IONapsterCodes::OpMessageReply:
		stream >> temp;
                __io->insert( "nick", temp );
                __io->insert( "message", stream.read() );
                break;

	case IONapsterCodes::GlobalMessageReply:
		stream >> temp;
                __io->insert( "nick", temp );
                __io->insert( "message", stream.read() );
                break;

        //
        // browse codes
        //

	case IONapsterCodes::BrowseReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "path", list[1] );
                __io->insert( "directory", IOSupport::stripFile( list[1] ) );
                __io->insert( "name", IOSupport::stripDir( list[1] ) );
                __io->insert( "md5sum", list[2] );
                __io->insert( "size", IOSupport::sizeText( list[3] ) );
                __io->insert( "bitrate", list[4] );
                __io->insert( "freq", list[5] );
                __io->insert( "time", IOSupport::timeText( list[6] ) );

                __io->insert( "size.orig", list[3] );
                __io->insert( "time.orig", list[6] );
		break;

	case IONapsterCodes::BrowseDone:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "host", IOSupport::networkToAscii( list[1] ) );
                __io->insert( "host.orig", list[1] );
		break;

        //
        // list of active channels
        //

	case IONapsterCodes::ListChansReply:
		stream >> temp;
                __io->insert( "channel", temp );

		stream >> temp;
                __io->insert( "size", temp );

                __io->insert( "message", stream.read() );
                break;

	case IONapsterCodes::ListChansDone:
                break;

	case IONapsterCodes::ListAllChansReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "channel", list[0] );
                __io->insert( "size", list[1] );
                __io->insert( "extra", list[2] );
                __io->insert( "level", list[3] );
                __io->insert( "limit", list[4] );
                __io->insert( "message", list[5] );
                break;

	case IONapsterCodes::ListAllChansDone:
                break;


        //
        // whois codes
        //

	case IONapsterCodes::WhoisReply:
		list = IOSupport::quoteSplit( data );

                __io->insert( "nick", list[0] );
                __io->insert( "level", list[1] );
                __io->insert( "time", IOSupport::timeText( list[2] ) );
                __io->insert( "channels", list[3] );
                __io->insert( "status", list[4] );
                __io->insert( "shared", list[5] );
                __io->insert( "downloads", list[6] );
                __io->insert( "uploads", list[7] );
                __io->insert( "speed", IOSupport::speedText( list[8] ) );
                __io->insert( "client", list[9] );

                __io->insert( "time.orig", list[2] );
                __io->insert( "speed.orig", list[8] );
		break;

	default:
		qDebug( "parse(): "
			"unknown code %d: %s",
                        __type, data.latin1() );
		break;
	}

        // always add the host and port
        __io->insert( "napster.host", peerName() );
        __io->insert( "napster.port", QString::number( peerPort() ) );

        //
        // handle the message
        //

        recvIOEvent( __io );

        // reset the message
        __size = 0;
        __type = 0;
        __data.fill( 0 );

        // try to read again
        return true;
}

void IONapsterConnection::handleAutoConnect()
{
}





