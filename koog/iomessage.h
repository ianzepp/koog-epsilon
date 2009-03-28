#ifndef IOMESSAGE_H
#define IOMESSAGE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qdict.h>
#include <qstring.h>
#include <qregexp.h>
#include <qobject.h>

class IOMessage : public QDict<QString>
{
public:
        IOMessage( QObject *parent=0, const char *name=0 );
        ~IOMessage();

        Q_INT32 messageType()                   { return __msg_type; };
        void setMessageType( Q_INT32 num )      { __msg_type = num;  };

        const QString & find( const QString & );
        void insert ( const QString &, const QString & );
        void replace( const QString &, const QString & );

        /** format a variable list */
        QString formatVariables( const QString & );

        /** print the tree and message type */
        void debugMessage();

private:
        Q_INT32 __msg_type;
};

#endif

