/***************************************************************************
                          mp3header.cpp  -  description
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

#include "mp3header.h"


const int bitrate_tbl[2][3][16] = {
{
 //MPEG 2 & 2.5
 {0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer III
 {0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer II
 {0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256,0}  //Layer I
},
{
 //MPEG 1
 {0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,0}, //Layer III
 {0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384,0}, //Layer II
 {0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448,0}  //Layer I
}
};

static int freq_tbl[4][3] = {
  {32000, 16000,  8000}, //MPEG 2.5
  {    0,     0,     0}, //reserved
  {22050, 24000, 16000}, //MPEG 2
  {44100, 48000, 32000}  //MPEG 1
};

MP3Header::MP3Header()
{
        reset();
}
MP3Header::MP3Header( const QString & path )
{
        reset();
        readMP3( path );
}
MP3Header::~MP3Header()
{
}

void MP3Header::reset()
{
        sync            = 0;
        version         = 0;
        layer           = 0;
        bitrate         = 0;
        freq            = 0;
        channels        = 0;
        ext             = 0;
        emphasis        = 0;

        protect         = false;
        padding         = false;
        copyright       = false;
        original        = false;

        seconds         = 0;
}

bool MP3Header::readMP3( const QString & path )
{
        QFile afile( path );

        if ( afile.open( IO_ReadOnly ) == false )
                return false;

        //  0000 0000 0000 0000 0000 0000 0000 0000
        char tmp[14];
        unsigned long bithdr;
        int trycnt = 0;

        afile.readBlock( &tmp[1], 3 );

        do {
                tmp[0]=tmp[1];
                tmp[1]=tmp[2];
                tmp[2]=tmp[3];
                afile.readBlock(&tmp[3],1);

                if ( trycnt == 0 && tmp[0] == 'I' && tmp[1] == 'D' &&
                     tmp[2] == '3' && tmp[3] <= 0x3 )
                {
                        // some mp3 seem to have the tag at the start of the file
                        // - starts with ID3\0003

                        // look for the possible header

                        while( tmp[0] != -1 )
                        {
                                if ( afile.atEnd() )
                                        return false;
                                afile.readBlock( &tmp[0], 1 );
                        }

                        afile.readBlock( &tmp[1], 3 );
                }

                bithdr = (unsigned long) (
                         ( (tmp[0] & 255) << 24) | ( (tmp[1] & 255) << 16) |
                         ( (tmp[2] & 255) <<  8) | ( (tmp[3] & 255)      )
                        );

                this->sync      = ( bithdr >> 21 ) & 0x7ff;
                this->version   = ( bithdr >> 19 ) & 0x3;
                this->layer     = ( bithdr >> 17 ) & 0x3;
                this->bitrate   = ( bithdr >> 12 ) & 0xf;
                this->freq      = ( bithdr >> 10 ) & 0x3;

                trycnt++;

                if ( trycnt >= 500 )
                        return false;

                }
        while ( this->sync != 0x7ff  ||
                this->version == 1   ||
                this->layer == 0     ||
                this->bitrate == 0xf ||
                this->freq == 3 );

        this->protect = ( bithdr >> 16 ) & 0x1;

        // get index & calc brate from it
        this->bitrate =
                bitrate_tbl[this->version & 1][this->layer - 1][this->bitrate];

        this->freq =
                freq_tbl[this->version][this->freq];

        this->padding   = ( bithdr >> 9 ) & 0x1;
        this->channels  = ( bithdr >> 6 ) & 0x3;
        this->ext       = ( bithdr >> 4 ) & 0x3;
        this->copyright = ( bithdr >> 3 ) & 0x1;
        this->original  = ( bithdr >> 2 ) & 0x1;
        this->emphasis  = ( bithdr & 0x3 );

        int skip = 0;

        // is there a variable bit rate bit
        if ( this->version == 3 )
        {  // mpeg version 1
                if ( this->channels == 3 )
                        skip = 17; // Single Channel
                else
                        skip = 32;
  }
  else { // mpeg version 2 or 2.5
   if(this->channels==3 ) skip = 9; // Single Channel
   else skip = 17;
  }

  // read next twelve bits in
  for(int i=0;i<skip;i++) afile.readBlock(tmp,1);

  afile.readBlock (tmp, 12);

  if(strncmp("Xing",tmp,4)==0) {
     bithdr = (unsigned long)(
        (tmp[4] << 24) |
        (tmp[5] << 16) |
        (tmp[6] <<  8) |
        (tmp[7]      )
     );
     if(bithdr &  1) { // there is frame data
      // get the num of frames
       bithdr = (unsigned long)(
        (tmp[8] << 24) |
        (tmp[9] << 16) |
        (tmp[10] <<  8) |
        (tmp[11]      )
       );

       float framesize = (float)afile.size() / (float)bithdr;
       this->bitrate =
         (int)(( framesize * (float)this->freq)
              /( 1000.0 * ( (this->layer==3) ? 12.0 : 144.0)) );
     }
  }

  this->seconds = (8 * afile.size() ) / 1000;
  if(this->bitrate) this->seconds=this->seconds/this->bitrate;
  else this->seconds=0;

  return true;
}
