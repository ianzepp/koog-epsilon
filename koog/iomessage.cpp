#include "iomessage.h"

IOMessage::IOMessage( QObject *, const char * )
          :QDict<QString>()
{
        setAutoDelete( true );
}

IOMessage::~IOMessage()
{}

const QString & IOMessage::find( const QString & key )
{
        QString * value = QDict<QString>::find( key );
        return value ? *value : QString::null;
}

void IOMessage::insert( const QString & key, const QString & value )
{
        QDict<QString>::insert( key, new QString( value ) );
}

void IOMessage::replace( const QString & key, const QString & value )
{
        QDict<QString>::replace( key, new QString( value ) );
}

QString IOMessage::formatVariables( const QString & fmt )
{
        QString data = fmt;

        // no variables? bail out here ..
        if ( data.contains( QRegExp( "\\$" ) ) <= 0 )
                return data;

        QDictIterator<QString> it( *this );
        QString find;

        for ( ; it.current(); ++it )
        {
                find = "\\$" + it.currentKey();
                data.replace( QRegExp( find ), *it.current() );
        }

//        qWarning( "IOMessage::formatVariables(): from: " + fmt );
//        qWarning( "IOMessage::formatVariables():   to: " + data );

        return data;
}

void IOMessage::debugMessage()
{
        QDictIterator<QString> it( *this );
        QString data;

        qDebug( "IOMessage::debugMessage(): "
                "message type: %i", messageType() );

        for ( ; it.current(); ++it )
        {
                qDebug( "  +- %-12s: %s", it.currentKey().latin1(),
                        it.current()->latin1() );
        }

        qDebug( "  '- end of message distribution" );
}

