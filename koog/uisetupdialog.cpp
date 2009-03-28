/***************************************************************************
                          uisetupdialog.cpp  -  description
                             -------------------
    begin                : Fri Mar 9 2001
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

#include "uiconfig.h"
#include "uisetupdialog.h"

UISetupDialog::UISetupDialog(QWidget *parent, const char *name )
              :UISetupDialogBase(parent,name,true)
{
        loadConfig();
}
UISetupDialog::~UISetupDialog()
{
}

void UISetupDialog::saveConfig()
{
        saveConfig_User();
        saveConfig_Transfer();
}

void UISetupDialog::saveConfig_User()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Options - User" );
        c->writeEntry( "nick", userEdit->text() );
        c->writeEntry( "pass", passEdit->text() );
        c->writeEntry( "speed", speedCombo->currentItem() );
        c->writeEntry( "firewall", firewallCheck->isChecked() );
        c->writeEntry( "client", clientCombo->currentItem() );
        c->sync();
}

void UISetupDialog::saveConfig_Transfer()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Options - Transfer" );
        c->writeEntry( "recv_path", recvEdit->text() );

        QListViewItemIterator it( sendView );
        QStringList     list;

        for ( ; it.current(); ++it )
                list.append( it.current()->text( 0 ) );

        c->writeEntry( "send_path", list );
        c->sync();
}

void UISetupDialog::loadConfig()
{
        loadConfig_User();
        loadConfig_Transfer();
}

void UISetupDialog::loadConfig_User()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Options - User" );
        userEdit->setText( c->readEntry( "nick" ) );
        passEdit->setText( c->readEntry( "pass" ) );
        speedCombo->setCurrentItem( c->readNumEntry( "speed" ) );
        firewallCheck->setChecked( c->readBoolEntry( "firewall" ) );
        clientCombo->setCurrentItem( c->readNumEntry( "client" ) );

        passCheck->setChecked( ! passEdit->text().isEmpty() );
}

void UISetupDialog::loadConfig_Transfer()
{
        KSimpleConfig * c = new KSimpleConfig( KOOG_CONFIG_PATH );

        c->setGroup( "Options - Transfer" );
        recvEdit->setText( c->readEntry( "recv_path" ) );

        QStringList list = c->readListEntry( "send_path" );
        QStringList::Iterator it = list.begin();

        sendView->clear();

        for ( ; it != list.end(); ++it )
                new QListViewItem( sendView, *it );
}

void UISetupDialog::slot_Accept()
{
        saveConfig();
        accept();
}

void UISetupDialog::slot_Cancel()
{
        reject();
}

void UISetupDialog::slot_RecvReset()
{
        recvEdit->setText( QDir::homeDirPath() );
}

void UISetupDialog::slot_RecvBrowse()
{
        QString path = KFileDialog::getExistingDirectory();

        if ( path.isEmpty() == true )
                return ;

        recvEdit->setText( path );
}

void UISetupDialog::slot_SendRemove()
{
        QListViewItem * item = sendView->currentItem();

        if ( item == 0 )
                return ;

        delete item;
}

void UISetupDialog::slot_SendBrowse()
{
        QString path = KFileDialog::getExistingDirectory();

        if ( path.isEmpty() == true )
                return ;

        QListViewItem * item = sendView->firstChild();

        while ( item )
        {
                if ( item->text( 0 ) == path )
                        return ;
                item = item->nextSibling();
        }

        new QListViewItem( sendView, path );
}

void UISetupDialog::slot_SendChanged( QListViewItem * item )
{
        removeSendButton->setEnabled( item != 0 );
}




