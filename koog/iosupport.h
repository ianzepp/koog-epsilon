#ifndef IOSUPPORT_H
#define IOSUPPORT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qobject.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qregexp.h>

/**
  *@author Ian Zepp
  */

class IOSupport : public QObject
{
        Q_OBJECT
public:
	IOSupport( QObject *parent=0, const char *name=0 );
	~IOSupport();

public:
        static QStringList quoteSplit( const QString & );
        static QString     quoteJoin( const QStringList & );

        static QString speedText( const QString & );
        static QString reverseSpeedText( const QString & );
        static QString timeText( const QString & );
        static QString sizeText( const QString & );
        static QString stripDir( const QString & );
        static QString stripFile( const QString & );
        static QString networkToAscii( const QString & );

        static QString floatToString( float, const char * fmt = "%2.2d" );

        const QPixmap & speedPixmap( const QString & );
        const QPixmap & ratePixmap( const QString & );
        const QPixmap & bitratePixmap( const QString & );
        const QPixmap & sizePixmap( const QString & );

        static QString replaceCarets( const QString & );

public:
        QPixmap pm_16x16_Circle_Green;
        QPixmap pm_16x16_Circle_Yellow;
        QPixmap pm_16x16_Circle_Black;
        QPixmap pm_16x16_Circle_Red;

        QPixmap pm_16x16_Sock_Connecting;
        QPixmap pm_16x16_Sock_Connected;
        QPixmap pm_16x16_Sock_Closed;
        QPixmap pm_16x16_Sock_Error;

        QPixmap pm_16x16_Size_0;
        QPixmap pm_16x16_Size_1;
        QPixmap pm_16x16_Size_2;
        QPixmap pm_16x16_Size_3;
        QPixmap pm_16x16_Size_4;
        QPixmap pm_16x16_Size_5;
};

#endif

