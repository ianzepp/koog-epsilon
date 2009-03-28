#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './uisearchbase.ui'
**
** Created: Wed Mar 14 12:43:58 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uisearchbase.h"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

static const char* const image0_data[] = { 
"16 16 2 1",
". c None",
"# c #000000",
"................",
"................",
"................",
"................",
"................",
".......##.......",
"......####......",
".....######.....",
"....########....",
"...##########...",
"..############..",
"................",
"................",
"................",
"................",
"................"};

static const char* const image1_data[] = { 
"16 16 7 1",
". c None",
"# c #000000",
"c c #c50000",
"a c #c5c2c5",
"e c #ff0000",
"d c #ffc2c5",
"b c #ffffff",
"................",
".......#........",
"......###.......",
".....#a##.......",
"..###aba##......",
"##abbbac##......",
"#bbbbdcec##.....",
"#bbddcecc##.....",
".#deeecc####....",
".#eeecc#..##....",
"..#ec##....##...",
"...##......##...",
"............##..",
"............##..",
".............##.",
".............##."};

static const char* const image2_data[] = { 
"16 16 2 1",
". c None",
"# c #000000",
"................",
"................",
"................",
"................",
"................",
"..############..",
"...##########...",
"....########....",
".....######.....",
"......####......",
".......##.......",
"................",
"................",
"................",
"................",
"................"};


/* 
 *  Constructs a UISearchBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
UISearchBase::UISearchBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    QPixmap image0( ( const char** ) image0_data );
    QPixmap image1( ( const char** ) image1_data );
    QPixmap image2( ( const char** ) image2_data );
    if ( !name )
	setName( "UISearchBase" );
    resize( 581, 147 ); 
    setCaption( i18n( "Form1" ) );
    UISearchBaseLayout = new QVBoxLayout( this ); 
    UISearchBaseLayout->setSpacing( 6 );
    UISearchBaseLayout->setMargin( 6 );

    searchGroup = new QGroupBox( this, "searchGroup" );
    searchGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, searchGroup->sizePolicy().hasHeightForWidth() ) );
    searchGroup->setFrameShape( QGroupBox::Box );
    searchGroup->setFrameShadow( QGroupBox::Sunken );
    searchGroup->setTitle( i18n( "Search the Napster network" ) );
    searchGroup->setColumnLayout(0, Qt::Vertical );
    searchGroup->layout()->setSpacing( 0 );
    searchGroup->layout()->setMargin( 0 );
    searchGroupLayout = new QVBoxLayout( searchGroup->layout() );
    searchGroupLayout->setAlignment( Qt::AlignTop );
    searchGroupLayout->setSpacing( 6 );
    searchGroupLayout->setMargin( 11 );

    Layout7 = new QHBoxLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    searchLabel = new QLabel( searchGroup, "searchLabel" );
    searchLabel->setText( i18n( "Search keywords:" ) );
    Layout7->addWidget( searchLabel );

    searchEdit = new QLineEdit( searchGroup, "searchEdit" );
    searchEdit->setMinimumSize( QSize( 100, 0 ) );
    Layout7->addWidget( searchEdit );

    searchButton = new QPushButton( searchGroup, "searchButton" );
    searchButton->setEnabled( FALSE );
    searchButton->setText( i18n( "&Search" ) );
    searchButton->setToggleButton( TRUE );
    searchButton->setToggleButton( TRUE );
    Layout7->addWidget( searchButton );

    cancelButton = new QPushButton( searchGroup, "cancelButton" );
    cancelButton->setEnabled( FALSE );
    cancelButton->setText( i18n( "&Cancel" ) );
    Layout7->addWidget( cancelButton );

    advancedCheck = new QCheckBox( searchGroup, "advancedCheck" );
    advancedCheck->setEnabled( TRUE );
    advancedCheck->setText( i18n( "Enable options" ) );
    advancedCheck->setChecked( FALSE );
    Layout7->addWidget( advancedCheck );
    searchGroupLayout->addLayout( Layout7 );

    advancedFrame = new QFrame( searchGroup, "advancedFrame" );
    advancedFrame->setEnabled( TRUE );
    advancedFrame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, advancedFrame->sizePolicy().hasHeightForWidth() ) );
    advancedFrame->setFrameShape( QFrame::StyledPanel );
    advancedFrame->setFrameShadow( QFrame::Sunken );
    advancedFrameLayout = new QGridLayout( advancedFrame ); 
    advancedFrameLayout->setSpacing( 6 );
    advancedFrameLayout->setMargin( 11 );

    bitrateCheck = new QCheckBox( advancedFrame, "bitrateCheck" );
    bitrateCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, bitrateCheck->sizePolicy().hasHeightForWidth() ) );
    bitrateCheck->setText( i18n( "Bitrate:" ) );

    advancedFrameLayout->addWidget( bitrateCheck, 0, 0 );

    bitrateCompare = new QComboBox( FALSE, advancedFrame, "bitrateCompare" );
    bitrateCompare->insertItem( image0, i18n( "minimum of" ) );
    bitrateCompare->insertItem( image1, i18n( "equal to" ) );
    bitrateCompare->insertItem( image2, i18n( "maximum of" ) );
    bitrateCompare->setEnabled( FALSE );
    bitrateCompare->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, bitrateCompare->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( bitrateCompare, 0, 1 );

    bitrateCombo = new QComboBox( FALSE, advancedFrame, "bitrateCombo" );
    bitrateCombo->insertItem( i18n( "320" ) );
    bitrateCombo->insertItem( i18n( "256" ) );
    bitrateCombo->insertItem( i18n( "224" ) );
    bitrateCombo->insertItem( i18n( "192" ) );
    bitrateCombo->insertItem( i18n( "160" ) );
    bitrateCombo->insertItem( i18n( "128" ) );
    bitrateCombo->insertItem( i18n( "112" ) );
    bitrateCombo->insertItem( i18n( "96" ) );
    bitrateCombo->setEnabled( FALSE );
    bitrateCombo->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, bitrateCombo->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( bitrateCombo, 0, 2 );

    speedCheck = new QCheckBox( advancedFrame, "speedCheck" );
    speedCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, speedCheck->sizePolicy().hasHeightForWidth() ) );
    speedCheck->setText( i18n( "Speed:" ) );

    advancedFrameLayout->addWidget( speedCheck, 1, 0 );

    speedCompare = new QComboBox( FALSE, advancedFrame, "speedCompare" );
    speedCompare->insertItem( image0, i18n( "minimum of" ) );
    speedCompare->insertItem( image1, i18n( "equal to" ) );
    speedCompare->insertItem( image2, i18n( "maximum of" ) );
    speedCompare->setEnabled( FALSE );
    speedCompare->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, speedCompare->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( speedCompare, 1, 1 );

    speedCombo = new QComboBox( FALSE, advancedFrame, "speedCombo" );
    speedCombo->insertItem( i18n( "T3+" ) );
    speedCombo->insertItem( i18n( "T1" ) );
    speedCombo->insertItem( i18n( "DSL" ) );
    speedCombo->insertItem( i18n( "Cable" ) );
    speedCombo->insertItem( i18n( "128k" ) );
    speedCombo->insertItem( i18n( "64k" ) );
    speedCombo->insertItem( i18n( "56.7" ) );
    speedCombo->insertItem( i18n( "33.6" ) );
    speedCombo->insertItem( i18n( "14.4" ) );
    speedCombo->insertItem( i18n( "Unknown" ) );
    speedCombo->setEnabled( FALSE );
    speedCombo->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, speedCombo->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( speedCombo, 1, 2 );

    freqCheck = new QCheckBox( advancedFrame, "freqCheck" );
    freqCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, freqCheck->sizePolicy().hasHeightForWidth() ) );
    freqCheck->setText( i18n( "Frequency:" ) );

    advancedFrameLayout->addWidget( freqCheck, 0, 3 );

    resultsCheck = new QCheckBox( advancedFrame, "resultsCheck" );
    resultsCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, resultsCheck->sizePolicy().hasHeightForWidth() ) );
    resultsCheck->setText( i18n( "Maximum number of results:" ) );

    advancedFrameLayout->addMultiCellWidget( resultsCheck, 1, 1, 3, 4 );

    freqCompare = new QComboBox( FALSE, advancedFrame, "freqCompare" );
    freqCompare->insertItem( image0, i18n( "minimum of" ) );
    freqCompare->insertItem( image1, i18n( "equal to" ) );
    freqCompare->insertItem( image2, i18n( "maximum of" ) );
    freqCompare->setEnabled( FALSE );
    freqCompare->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, freqCompare->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( freqCompare, 0, 4 );

    freqCombo = new QComboBox( FALSE, advancedFrame, "freqCombo" );
    freqCombo->insertItem( i18n( "44100" ) );
    freqCombo->insertItem( i18n( "22050" ) );
    freqCombo->insertItem( i18n( "11025" ) );
    freqCombo->setEnabled( FALSE );
    freqCombo->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, freqCombo->sizePolicy().hasHeightForWidth() ) );

    advancedFrameLayout->addWidget( freqCombo, 0, 5 );

    resultsSpin = new QSpinBox( advancedFrame, "resultsSpin" );
    resultsSpin->setEnabled( FALSE );
    resultsSpin->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, resultsSpin->sizePolicy().hasHeightForWidth() ) );
    resultsSpin->setMaxValue( 100 );
    resultsSpin->setMinValue( 1 );
    resultsSpin->setValue( 100 );

    advancedFrameLayout->addWidget( resultsSpin, 1, 5 );
    searchGroupLayout->addWidget( advancedFrame );
    UISearchBaseLayout->addWidget( searchGroup );

    // signals and slots connections
    connect( searchButton, SIGNAL( toggled(bool) ), advancedFrame, SLOT( setDisabled(bool) ) );
    connect( searchButton, SIGNAL( toggled(bool) ), searchEdit, SLOT( setDisabled(bool) ) );
    connect( searchButton, SIGNAL( toggled(bool) ), cancelButton, SLOT( setEnabled(bool) ) );
    connect( searchButton, SIGNAL( toggled(bool) ), this, SLOT( handleSearchToggled( bool ) ) );
    connect( searchEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( handleEditChanged( const QString & ) ) );
    connect( searchEdit, SIGNAL( returnPressed() ), searchButton, SLOT( animateClick() ) );
    connect( cancelButton, SIGNAL( clicked() ), searchButton, SLOT( toggle() ) );
    connect( advancedCheck, SIGNAL( toggled(bool) ), this, SLOT( handleAdvancedToggled( bool ) ) );
    connect( bitrateCheck, SIGNAL( toggled(bool) ), bitrateCompare, SLOT( setEnabled(bool) ) );
    connect( bitrateCheck, SIGNAL( toggled(bool) ), bitrateCombo, SLOT( setEnabled(bool) ) );
    connect( speedCheck, SIGNAL( toggled(bool) ), speedCompare, SLOT( setEnabled(bool) ) );
    connect( speedCheck, SIGNAL( toggled(bool) ), speedCombo, SLOT( setEnabled(bool) ) );
    connect( freqCheck, SIGNAL( toggled(bool) ), freqCompare, SLOT( setEnabled(bool) ) );
    connect( freqCheck, SIGNAL( toggled(bool) ), freqCombo, SLOT( setEnabled(bool) ) );
    connect( resultsCheck, SIGNAL( toggled(bool) ), resultsSpin, SLOT( setEnabled(bool) ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UISearchBase::~UISearchBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void UISearchBase::handleEditChanged( const QString & )
{
    qWarning( "UISearchBase::handleEditChanged( const QString & ): Not implemented yet!" );
}

void UISearchBase::handleSearchToggled( bool )
{
    qWarning( "UISearchBase::handleSearchToggled( bool ): Not implemented yet!" );
}

void UISearchBase::handleAdvancedToggled( bool )
{
    qWarning( "UISearchBase::handleAdvancedToggled( bool ): Not implemented yet!" );
}

#include "uisearchbase.moc"
