/***************************************************************************
                          mp3header.h  -  description
                             -------------------
    begin                : Sat Mar 10 2001
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

#ifndef MP3HEADER_H
#define MP3HEADER_H

#include <qfile.h>

/**
  *@author Ian Zepp
  */

class MP3Header
{
public: 
	MP3Header();
	MP3Header( const QString & );
	~MP3Header();

public:
        Q_UINT16        sync;
        Q_INT32         version;
        Q_INT32         layer;
        Q_INT32         bitrate;
        Q_INT32         freq;
        Q_INT32         channels;
        Q_INT32         ext;
        Q_INT32         emphasis;

        bool            protect;
        bool            padding;
        bool            copyright;
        bool            original;

        unsigned long   seconds;

public:
        void reset();
        bool readMP3( const QString & );
};

#endif
