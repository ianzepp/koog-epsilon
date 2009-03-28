#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './uisetupdialogbase.ui'
**
** Created: Wed Mar 14 12:43:58 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uisetupdialogbase.h"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a UISetupDialogBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UISetupDialogBase::UISetupDialogBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "UISetupDialogBase" );
    resize( 360, 453 ); 
    setCaption( i18n( "Setup options" ) );
    UISetupDialogBaseLayout = new QVBoxLayout( this ); 
    UISetupDialogBaseLayout->setSpacing( 6 );
    UISetupDialogBaseLayout->setMargin( 11 );

    generalTab = new QTabWidget( this, "generalTab" );

    tab = new QWidget( generalTab, "tab" );
    tabLayout = new QVBoxLayout( tab ); 
    tabLayout->setSpacing( 6 );
    tabLayout->setMargin( 11 );

    GroupBox1 = new QGroupBox( tab, "GroupBox1" );
    GroupBox1->setTitle( i18n( "Login settings" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QGridLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    TextLabel2 = new QLabel( GroupBox1, "TextLabel2" );
    TextLabel2->setText( i18n( "My user name is:" ) );

    GroupBox1Layout->addWidget( TextLabel2, 0, 0 );

    userEdit = new QLineEdit( GroupBox1, "userEdit" );

    GroupBox1Layout->addMultiCellWidget( userEdit, 0, 0, 1, 2 );

    TextLabel3 = new QLabel( GroupBox1, "TextLabel3" );
    TextLabel3->setText( i18n( "My password is:" ) );

    GroupBox1Layout->addWidget( TextLabel3, 1, 0 );

    passEdit = new QLineEdit( GroupBox1, "passEdit" );
    passEdit->setEnabled( FALSE );
    passEdit->setEchoMode( QLineEdit::Password );

    GroupBox1Layout->addMultiCellWidget( passEdit, 1, 1, 1, 2 );

    passCheck = new QCheckBox( GroupBox1, "passCheck" );
    passCheck->setText( i18n( "Save password" ) );

    GroupBox1Layout->addWidget( passCheck, 2, 1 );

    userCheck = new QCheckBox( GroupBox1, "userCheck" );
    userCheck->setEnabled( FALSE );
    userCheck->setText( i18n( "Create user" ) );

    GroupBox1Layout->addWidget( userCheck, 2, 2 );
    tabLayout->addWidget( GroupBox1 );

    GroupBox3 = new QGroupBox( tab, "GroupBox3" );
    GroupBox3->setTitle( i18n( "Connection" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QGridLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    TextLabel1 = new QLabel( GroupBox3, "TextLabel1" );
    TextLabel1->setText( i18n( "Send client version as:" ) );

    GroupBox3Layout->addWidget( TextLabel1, 1, 0 );

    TextLabel4 = new QLabel( GroupBox3, "TextLabel4" );
    TextLabel4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, TextLabel4->sizePolicy().hasHeightForWidth() ) );
    TextLabel4->setText( i18n( "My internet connection is:" ) );

    GroupBox3Layout->addWidget( TextLabel4, 0, 0 );

    speedCombo = new QComboBox( FALSE, GroupBox3, "speedCombo" );
    speedCombo->insertItem( i18n( "Unknown" ) );
    speedCombo->insertItem( i18n( "14.4" ) );
    speedCombo->insertItem( i18n( "28.8" ) );
    speedCombo->insertItem( i18n( "33.6" ) );
    speedCombo->insertItem( i18n( "56.7" ) );
    speedCombo->insertItem( i18n( "64 ISDN" ) );
    speedCombo->insertItem( i18n( "128 ISDN" ) );
    speedCombo->insertItem( i18n( "Cable" ) );
    speedCombo->insertItem( i18n( "DSL" ) );
    speedCombo->insertItem( i18n( "T1" ) );
    speedCombo->insertItem( i18n( "T3+ or faster" ) );
    speedCombo->setMinimumSize( QSize( 100, 0 ) );
    speedCombo->setCurrentItem( 4 );

    GroupBox3Layout->addWidget( speedCombo, 0, 1 );

    firewallCheck = new QCheckBox( GroupBox3, "firewallCheck" );
    firewallCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, firewallCheck->sizePolicy().hasHeightForWidth() ) );
    firewallCheck->setText( i18n( "I am behind a firewall" ) );

    GroupBox3Layout->addMultiCellWidget( firewallCheck, 2, 2, 0, 1 );

    clientCombo = new QComboBox( FALSE, GroupBox3, "clientCombo" );
    clientCombo->insertItem( i18n( "Koog Epsilon" ) );
    clientCombo->insertItem( i18n( "Napster BETA 6" ) );
    clientCombo->insertItem( i18n( "Napster BETA 9.2" ) );
    clientCombo->insertItem( i18n( "Gnapster " ) );

    GroupBox3Layout->addWidget( clientCombo, 1, 1 );
    tabLayout->addWidget( GroupBox3 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout->addItem( spacer );
    generalTab->insertTab( tab, i18n( "&General" ) );

    tab_2 = new QWidget( generalTab, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2 ); 
    tabLayout_2->setSpacing( 6 );
    tabLayout_2->setMargin( 11 );

    GroupBox7 = new QGroupBox( tab_2, "GroupBox7" );
    GroupBox7->setTitle( i18n( "Existing servers" ) );
    GroupBox7->setColumnLayout(0, Qt::Vertical );
    GroupBox7->layout()->setSpacing( 0 );
    GroupBox7->layout()->setMargin( 0 );
    GroupBox7Layout = new QVBoxLayout( GroupBox7->layout() );
    GroupBox7Layout->setAlignment( Qt::AlignTop );
    GroupBox7Layout->setSpacing( 6 );
    GroupBox7Layout->setMargin( 11 );

    TextLabel6 = new QLabel( GroupBox7, "TextLabel6" );
    TextLabel6->setText( i18n( "My default server is:" ) );
    GroupBox7Layout->addWidget( TextLabel6 );

    currentLabel = new QLabel( GroupBox7, "currentLabel" );
    currentLabel->setFrameShape( QLabel::StyledPanel );
    currentLabel->setFrameShadow( QLabel::Sunken );
    currentLabel->setText( i18n( "no server set" ) );
    currentLabel->setAlignment( int( QLabel::AlignCenter ) );
    GroupBox7Layout->addWidget( currentLabel );

    TextLabel7 = new QLabel( GroupBox7, "TextLabel7" );
    TextLabel7->setText( i18n( "My available servers are:" ) );
    GroupBox7Layout->addWidget( TextLabel7 );

    serverView = new QListView( GroupBox7, "serverView" );
    serverView->addColumn( i18n( "Type" ) );
    serverView->addColumn( i18n( "Server" ) );
    serverView->addColumn( i18n( "Port" ) );
    serverView->setVScrollBarMode( QListView::AlwaysOn );
    serverView->setAllColumnsShowFocus( TRUE );
    GroupBox7Layout->addWidget( serverView );

    Layout3 = new QHBoxLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout3->addItem( spacer_2 );

    defaultServerButton = new QPushButton( GroupBox7, "defaultServerButton" );
    defaultServerButton->setEnabled( FALSE );
    defaultServerButton->setText( i18n( "Make &default" ) );
    Layout3->addWidget( defaultServerButton );

    removeServerButton = new QPushButton( GroupBox7, "removeServerButton" );
    removeServerButton->setEnabled( FALSE );
    removeServerButton->setText( i18n( "&Remove" ) );
    Layout3->addWidget( removeServerButton );
    GroupBox7Layout->addLayout( Layout3 );
    tabLayout_2->addWidget( GroupBox7 );

    GroupBox1_2 = new QGroupBox( tab_2, "GroupBox1_2" );
    GroupBox1_2->setTitle( i18n( "Create a new server" ) );
    GroupBox1_2->setColumnLayout(0, Qt::Vertical );
    GroupBox1_2->layout()->setSpacing( 0 );
    GroupBox1_2->layout()->setMargin( 0 );
    GroupBox1_2Layout = new QGridLayout( GroupBox1_2->layout() );
    GroupBox1_2Layout->setAlignment( Qt::AlignTop );
    GroupBox1_2Layout->setSpacing( 6 );
    GroupBox1_2Layout->setMargin( 11 );

    serverTypeCombo = new QComboBox( FALSE, GroupBox1_2, "serverTypeCombo" );
    serverTypeCombo->insertItem( i18n( "napster" ) );
    serverTypeCombo->setEnabled( TRUE );

    GroupBox1_2Layout->addWidget( serverTypeCombo, 1, 3 );

    TextLabel5_2 = new QLabel( GroupBox1_2, "TextLabel5_2" );
    TextLabel5_2->setText( i18n( "Server port:" ) );
    TextLabel5_2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    GroupBox1_2Layout->addWidget( TextLabel5_2, 1, 0 );

    TextLabel4_2 = new QLabel( GroupBox1_2, "TextLabel4_2" );
    TextLabel4_2->setText( i18n( "Server address:" ) );
    TextLabel4_2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    GroupBox1_2Layout->addWidget( TextLabel4_2, 0, 0 );

    serverHostEdit = new QLineEdit( GroupBox1_2, "serverHostEdit" );
    serverHostEdit->setEnabled( TRUE );

    GroupBox1_2Layout->addMultiCellWidget( serverHostEdit, 0, 0, 1, 3 );

    serverPortEdit = new QLineEdit( GroupBox1_2, "serverPortEdit" );
    serverPortEdit->setEnabled( TRUE );
    serverPortEdit->setMinimumSize( QSize( 50, 0 ) );
    serverPortEdit->setMaximumSize( QSize( 50, 32767 ) );
    serverPortEdit->setText( QString::null );

    GroupBox1_2Layout->addWidget( serverPortEdit, 1, 1 );

    TextLabel6_2 = new QLabel( GroupBox1_2, "TextLabel6_2" );
    TextLabel6_2->setText( i18n( "Type of server:" ) );
    TextLabel6_2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    GroupBox1_2Layout->addWidget( TextLabel6_2, 1, 2 );

    createServerButton = new QPushButton( GroupBox1_2, "createServerButton" );
    createServerButton->setEnabled( FALSE );
    createServerButton->setText( i18n( "&Create" ) );

    GroupBox1_2Layout->addWidget( createServerButton, 2, 3 );

    serverDefaultCheck = new QCheckBox( GroupBox1_2, "serverDefaultCheck" );
    serverDefaultCheck->setEnabled( FALSE );
    serverDefaultCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, serverDefaultCheck->sizePolicy().hasHeightForWidth() ) );
    serverDefaultCheck->setText( i18n( "Save as default server" ) );

    GroupBox1_2Layout->addMultiCellWidget( serverDefaultCheck, 2, 2, 0, 2 );
    tabLayout_2->addWidget( GroupBox1_2 );
    generalTab->insertTab( tab_2, i18n( "&Servers" ) );

    tab_3 = new QWidget( generalTab, "tab_3" );
    tabLayout_3 = new QVBoxLayout( tab_3 ); 
    tabLayout_3->setSpacing( 6 );
    tabLayout_3->setMargin( 11 );

    GroupBox6 = new QGroupBox( tab_3, "GroupBox6" );
    GroupBox6->setTitle( i18n( "Downloading" ) );
    GroupBox6->setColumnLayout(0, Qt::Vertical );
    GroupBox6->layout()->setSpacing( 0 );
    GroupBox6->layout()->setMargin( 0 );
    GroupBox6Layout = new QGridLayout( GroupBox6->layout() );
    GroupBox6Layout->setAlignment( Qt::AlignTop );
    GroupBox6Layout->setSpacing( 6 );
    GroupBox6Layout->setMargin( 11 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    GroupBox6Layout->addItem( spacer_3, 1, 0 );

    resetRecvButton = new QPushButton( GroupBox6, "resetRecvButton" );
    resetRecvButton->setText( i18n( "&Reset" ) );

    GroupBox6Layout->addWidget( resetRecvButton, 1, 1 );

    browseRecvButton = new QPushButton( GroupBox6, "browseRecvButton" );
    browseRecvButton->setText( i18n( "&Browse" ) );

    GroupBox6Layout->addWidget( browseRecvButton, 1, 2 );

    Layout8 = new QHBoxLayout; 
    Layout8->setSpacing( 6 );
    Layout8->setMargin( 0 );

    TextLabel8 = new QLabel( GroupBox6, "TextLabel8" );
    TextLabel8->setText( i18n( "Download directory:" ) );
    Layout8->addWidget( TextLabel8 );

    recvEdit = new QLineEdit( GroupBox6, "recvEdit" );
    Layout8->addWidget( recvEdit );

    GroupBox6Layout->addMultiCellLayout( Layout8, 0, 0, 0, 2 );
    tabLayout_3->addWidget( GroupBox6 );

    GroupBox13 = new QGroupBox( tab_3, "GroupBox13" );
    GroupBox13->setTitle( i18n( "Uploading" ) );
    GroupBox13->setColumnLayout(0, Qt::Vertical );
    GroupBox13->layout()->setSpacing( 0 );
    GroupBox13->layout()->setMargin( 0 );
    GroupBox13Layout = new QGridLayout( GroupBox13->layout() );
    GroupBox13Layout->setAlignment( Qt::AlignTop );
    GroupBox13Layout->setSpacing( 6 );
    GroupBox13Layout->setMargin( 11 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    GroupBox13Layout->addItem( spacer_4, 1, 0 );

    sendView = new QListView( GroupBox13, "sendView" );
    sendView->addColumn( i18n( "Directory" ) );
    sendView->setEnabled( TRUE );
    sendView->setVScrollBarMode( QListView::AlwaysOn );
    sendView->setSelectionMode( QListView::Single );
    sendView->setAllColumnsShowFocus( TRUE );
    sendView->setShowSortIndicator( TRUE );

    GroupBox13Layout->addMultiCellWidget( sendView, 0, 0, 0, 2 );

    removeSendButton = new QPushButton( GroupBox13, "removeSendButton" );
    removeSendButton->setEnabled( FALSE );
    removeSendButton->setText( i18n( "&Remove" ) );

    GroupBox13Layout->addWidget( removeSendButton, 1, 1 );

    browseSendButton = new QPushButton( GroupBox13, "browseSendButton" );
    browseSendButton->setEnabled( TRUE );
    browseSendButton->setText( i18n( "&Browse" ) );

    GroupBox13Layout->addWidget( browseSendButton, 1, 2 );
    tabLayout_3->addWidget( GroupBox13 );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_3->addItem( spacer_5 );
    generalTab->insertTab( tab_3, i18n( "&Transfers" ) );

    tab_4 = new QWidget( generalTab, "tab_4" );
    tabLayout_4 = new QVBoxLayout( tab_4 ); 
    tabLayout_4->setSpacing( 6 );
    tabLayout_4->setMargin( 11 );

    GroupBox20 = new QGroupBox( tab_4, "GroupBox20" );
    GroupBox20->setTitle( i18n( "Channels" ) );
    GroupBox20->setColumnLayout(0, Qt::Vertical );
    GroupBox20->layout()->setSpacing( 0 );
    GroupBox20->layout()->setMargin( 0 );
    GroupBox20Layout = new QGridLayout( GroupBox20->layout() );
    GroupBox20Layout->setAlignment( Qt::AlignTop );
    GroupBox20Layout->setSpacing( 6 );
    GroupBox20Layout->setMargin( 11 );

    showMotdCheck = new QCheckBox( GroupBox20, "showMotdCheck" );
    showMotdCheck->setText( i18n( "Show channel MOTD" ) );

    GroupBox20Layout->addWidget( showMotdCheck, 0, 0 );

    showSpeedCheck = new QCheckBox( GroupBox20, "showSpeedCheck" );
    showSpeedCheck->setText( i18n( "Show connection speed" ) );

    GroupBox20Layout->addWidget( showSpeedCheck, 1, 1 );

    showJoinCheck = new QCheckBox( GroupBox20, "showJoinCheck" );
    showJoinCheck->setText( i18n( "Show joins / parts" ) );

    GroupBox20Layout->addWidget( showJoinCheck, 1, 0 );

    showSharedCheck = new QCheckBox( GroupBox20, "showSharedCheck" );
    showSharedCheck->setText( i18n( "Show shared files" ) );

    GroupBox20Layout->addWidget( showSharedCheck, 0, 1 );

    autoCloseCheck = new QCheckBox( GroupBox20, "autoCloseCheck" );
    autoCloseCheck->setText( i18n( "Close window when parting channel" ) );

    GroupBox20Layout->addMultiCellWidget( autoCloseCheck, 2, 2, 0, 1 );
    tabLayout_4->addWidget( GroupBox20 );

    GroupBox32 = new QGroupBox( tab_4, "GroupBox32" );
    GroupBox32->setTitle( i18n( "Messaging" ) );
    GroupBox32->setColumnLayout(0, Qt::Vertical );
    GroupBox32->layout()->setSpacing( 0 );
    GroupBox32->layout()->setMargin( 0 );
    GroupBox32Layout = new QVBoxLayout( GroupBox32->layout() );
    GroupBox32Layout->setAlignment( Qt::AlignTop );
    GroupBox32Layout->setSpacing( 6 );
    GroupBox32Layout->setMargin( 11 );

    popupMsgsCheck = new QCheckBox( GroupBox32, "popupMsgsCheck" );
    popupMsgsCheck->setText( i18n( "Popup a new window when messaged" ) );
    GroupBox32Layout->addWidget( popupMsgsCheck );

    rememberMsgsCheck = new QCheckBox( GroupBox32, "rememberMsgsCheck" );
    rememberMsgsCheck->setText( i18n( "Remember the previous messages" ) );
    GroupBox32Layout->addWidget( rememberMsgsCheck );
    tabLayout_4->addWidget( GroupBox32 );
    QSpacerItem* spacer_6 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_4->addItem( spacer_6 );
    generalTab->insertTab( tab_4, i18n( "&Chat" ) );

    tab_5 = new QWidget( generalTab, "tab_5" );
    tabLayout_5 = new QVBoxLayout( tab_5 ); 
    tabLayout_5->setSpacing( 6 );
    tabLayout_5->setMargin( 11 );

    GroupBox10 = new QGroupBox( tab_5, "GroupBox10" );
    GroupBox10->setTitle( i18n( "Transferring" ) );
    GroupBox10->setColumnLayout(0, Qt::Vertical );
    GroupBox10->layout()->setSpacing( 0 );
    GroupBox10->layout()->setMargin( 0 );
    GroupBox10Layout = new QVBoxLayout( GroupBox10->layout() );
    GroupBox10Layout->setAlignment( Qt::AlignTop );
    GroupBox10Layout->setSpacing( 6 );
    GroupBox10Layout->setMargin( 11 );

    Layout13 = new QHBoxLayout; 
    Layout13->setSpacing( 6 );
    Layout13->setMargin( 0 );

    maxUploadCheck = new QCheckBox( GroupBox10, "maxUploadCheck" );
    maxUploadCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, maxUploadCheck->sizePolicy().hasHeightForWidth() ) );
    maxUploadCheck->setText( i18n( "Max allowed upload speed in kbps:" ) );
    Layout13->addWidget( maxUploadCheck );

    maxUploadEdit = new QLineEdit( GroupBox10, "maxUploadEdit" );
    maxUploadEdit->setEnabled( FALSE );
    maxUploadEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, maxUploadEdit->sizePolicy().hasHeightForWidth() ) );
    maxUploadEdit->setMinimumSize( QSize( 60, 0 ) );
    maxUploadEdit->setMaximumSize( QSize( 60, 32767 ) );
    Layout13->addWidget( maxUploadEdit );
    GroupBox10Layout->addLayout( Layout13 );

    autoCleanupCheck = new QCheckBox( GroupBox10, "autoCleanupCheck" );
    autoCleanupCheck->setText( i18n( "Automatically cleanup finished downloads" ) );
    GroupBox10Layout->addWidget( autoCleanupCheck );
    tabLayout_5->addWidget( GroupBox10 );
    QSpacerItem* spacer_7 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_5->addItem( spacer_7 );
    generalTab->insertTab( tab_5, i18n( "&Misc" ) );
    UISetupDialogBaseLayout->addWidget( generalTab );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );

    setupLabel = new QLabel( this, "setupLabel" );
    setupLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, setupLabel->sizePolicy().hasHeightForWidth() ) );
    setupLabel->setText( QString::null );
    Layout1->addWidget( setupLabel );

    acceptButton = new QPushButton( this, "acceptButton" );
    acceptButton->setText( i18n( "&Accept" ) );
    Layout1->addWidget( acceptButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setText( i18n( "&Cancel" ) );
    Layout1->addWidget( cancelButton );
    UISetupDialogBaseLayout->addLayout( Layout1 );

    // signals and slots connections
    connect( acceptButton, SIGNAL( clicked() ), this, SLOT( slot_Accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( slot_Cancel() ) );
    connect( passCheck, SIGNAL( clicked() ), passEdit, SLOT( clear() ) );
    connect( passCheck, SIGNAL( toggled(bool) ), passEdit, SLOT( setEnabled(bool) ) );
    connect( resetRecvButton, SIGNAL( clicked() ), this, SLOT( slot_RecvReset() ) );
    connect( browseRecvButton, SIGNAL( clicked() ), this, SLOT( slot_RecvBrowse() ) );
    connect( browseSendButton, SIGNAL( clicked() ), this, SLOT( slot_SendBrowse() ) );
    connect( removeSendButton, SIGNAL( clicked() ), this, SLOT( slot_SendRemove() ) );
    connect( sendView, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slot_SendChanged(QListViewItem *) ) );
    connect( sendView, SIGNAL( currentChanged(QListViewItem*) ), this, SLOT( slot_SendChanged(QListViewItem *) ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UISetupDialogBase::~UISetupDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void UISetupDialogBase::slot_SendChanged(QListViewItem *)
{
    qWarning( "UISetupDialogBase::slot_SendChanged(QListViewItem *): Not implemented yet!" );
}

void UISetupDialogBase::slot_Accept()
{
    qWarning( "UISetupDialogBase::slot_Accept(): Not implemented yet!" );
}

void UISetupDialogBase::slot_Cancel()
{
    qWarning( "UISetupDialogBase::slot_Cancel(): Not implemented yet!" );
}

void UISetupDialogBase::slot_RecvBrowse()
{
    qWarning( "UISetupDialogBase::slot_RecvBrowse(): Not implemented yet!" );
}

void UISetupDialogBase::slot_RecvReset()
{
    qWarning( "UISetupDialogBase::slot_RecvReset(): Not implemented yet!" );
}

void UISetupDialogBase::slot_SendBrowse()
{
    qWarning( "UISetupDialogBase::slot_SendBrowse(): Not implemented yet!" );
}

void UISetupDialogBase::slot_SendRemove()
{
    qWarning( "UISetupDialogBase::slot_SendRemove(): Not implemented yet!" );
}

#include "uisetupdialogbase.moc"
