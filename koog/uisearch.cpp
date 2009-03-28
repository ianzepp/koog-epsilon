/***************************************************************************
                          uisearch.cpp  -  description
                             -------------------
    begin                : Wed Mar 7 2001
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


#include "iomessage.h"
#include "ionapstercodes.h"
#include "iosupport.h"
#include "uiconfig.h"
#include "uisearch.h"

UISearch::UISearch(QWidget *parent, const char *name )
         :UISearchBase(parent,name)
{
        loadConfig();
}
UISearch::~UISearch(){
}

void UISearch::recvIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        case IONapsterCodes::SearchDone:
                recvIO_SearchDone( io );
                break;
        }

        emit recvIO( io );
}

void UISearch::sendIOEvent( IOMessage * io )
{
        switch ( io->messageType() )
        {
        }

        emit sendIO( io );
}

void UISearch::searchCanceledEvent()
{
}

void UISearch::handleEditChanged( const QString & data )
{
        searchButton->setEnabled( ! data.isEmpty() );
}

void UISearch::handleSearchToggled( bool running )
{
        if ( ! running )
        {
                return;
        }

        // create message
        IOMessage * io = new IOMessage( 0 );
        io->setMessageType( IONapsterCodes::SearchRequest );
        io->insert( "name", searchEdit->text() );

        QString     cmp;
        QString     val;
        QStringList list;
        list.append( "FILENAME" );
        list.append( "CONTAINS" );
        list.append( searchEdit->text() );

        if ( advancedCheck->isChecked() )
        {
                if ( bitrateCheck->isChecked() )
                {
                        cmp = bitrateCompare->currentText();
                        val = bitrateCombo  ->currentText();

                        list.append( "BITRATE" );
                        list.append( convertCompare( cmp ) );
                        list.append( val );
                }

                if ( freqCheck->isChecked() )
                {
                        cmp = freqCompare->currentText();
                        val = freqCombo  ->currentText();

                        list.append( "FREQ" );
                        list.append( convertCompare( cmp ) );
                        list.append( val );
                }

                if ( speedCheck->isChecked() )
                {
                        cmp = speedCompare->currentText();
                        val = speedCombo  ->currentText();

                        list.append( "LINESPEED" );
                        list.append( convertCompare( cmp ) );
                        list.append( IOSupport::reverseSpeedText( val ) );
                }
        }

        io->insert( "rawdata", IOSupport::quoteJoin( list ) );
        emit sendIO( io );

        delete io;

        //
        // save current config
        //

        saveConfig();
}

void UISearch::handleAdvancedToggled( bool show )
{
        if ( show )
                advancedFrame->show();
        else
                advancedFrame->hide();

        // the app sometimes needs help knowing when to repaint
        qApp->processEvents();
}

void UISearch::recvIO_SearchDone( IOMessage * )
{
        searchButton->setEnabled( true );
        searchButton->setOn( false );
}

QString UISearch::convertCompare( const QString & data )
{
        QString reply;

        if      ( data == "maximum of" )
                reply = "AT BEST";
        else if ( data == "equal to" )
                reply = "EQUAL TO";
        else
                reply = "AT LEAST";

        return reply;
}

void UISearch::saveConfig()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Search - Advanced" );
        c->writeEntry( "checked", advancedCheck->isChecked() );

        c->setGroup( "Search - Advanced - Bitrate" );
        c->writeEntry( "checked", bitrateCheck->isChecked() );
        c->writeEntry( "compare", bitrateCompare->currentItem() );
        c->writeEntry( "value",   bitrateCombo->currentItem() );

        c->setGroup( "Search - Advanced - Frequency" );
        c->writeEntry( "checked", freqCheck->isChecked() );
        c->writeEntry( "compare", freqCompare->currentItem() );
        c->writeEntry( "value",   freqCombo->currentItem() );

        c->setGroup( "Search - Advanced - Speed" );
        c->writeEntry( "checked", speedCheck->isChecked() );
        c->writeEntry( "compare", speedCompare->currentItem() );
        c->writeEntry( "value",   speedCombo->currentItem() );

        c->sync();
}

void UISearch::loadConfig()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Search - Advanced" );
        advancedCheck->setChecked( c->readBoolEntry( "checked" ) );

        c->setGroup( "Search - Advanced - Bitrate" );
        bitrateCheck->setChecked( c->readBoolEntry( "checked" ) );
        bitrateCompare->setCurrentItem( c->readNumEntry( "compare" ) );
        bitrateCombo->setCurrentItem( c->readNumEntry( "value" ) );

        c->setGroup( "Search - Advanced - Frequency" );
        freqCheck->setChecked( c->readBoolEntry( "checked" ) );
        freqCompare->setCurrentItem( c->readNumEntry( "compare" ) );
        freqCombo->setCurrentItem( c->readNumEntry( "value" ) );

        c->setGroup( "Search - Advanced - Speed" );
        speedCheck->setChecked( c->readBoolEntry( "checked" ) );
        speedCompare->setCurrentItem( c->readNumEntry( "compare" ) );
        speedCombo->setCurrentItem( c->readNumEntry( "value" ) );

        handleAdvancedToggled( advancedCheck->isChecked() );
}


