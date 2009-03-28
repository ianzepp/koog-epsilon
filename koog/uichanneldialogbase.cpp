#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './uichanneldialogbase.ui'
**
** Created: Wed Mar 14 12:43:57 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uichanneldialogbase.h"

#include <qcheckbox.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a UIChannelDialogBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UIChannelDialogBase::UIChannelDialogBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "UIChannelDialogBase" );
    resize( 371, 407 ); 
    setCaption( i18n( "MyDialog" ) );
    setSizeGripEnabled( TRUE );
    UIChannelDialogBaseLayout = new QVBoxLayout( this ); 
    UIChannelDialogBaseLayout->setSpacing( 6 );
    UIChannelDialogBaseLayout->setMargin( 11 );

    m_title = new QLabel( this, "m_title" );
    m_title->setText( i18n( "Choose a channel below:" ) );
    UIChannelDialogBaseLayout->addWidget( m_title );

    m_view = new QListView( this, "m_view" );
    m_view->addColumn( i18n( "Channel" ) );
    m_view->addColumn( i18n( "Users" ) );
    m_view->addColumn( i18n( "Title" ) );
    m_view->setVScrollBarMode( QListView::AlwaysOn );
    m_view->setHScrollBarMode( QListView::AlwaysOff );
    m_view->setSelectionMode( QListView::Extended );
    m_view->setAllColumnsShowFocus( TRUE );
    m_view->setRootIsDecorated( TRUE );
    UIChannelDialogBaseLayout->addWidget( m_view );

    Layout2 = new QHBoxLayout; 
    Layout2->setSpacing( 6 );
    Layout2->setMargin( 0 );

    m_viewCheck = new QCheckBox( this, "m_viewCheck" );
    m_viewCheck->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, m_viewCheck->sizePolicy().hasHeightForWidth() ) );
    m_viewCheck->setText( i18n( "View all channels" ) );
    Layout2->addWidget( m_viewCheck );

    m_buttonJoin = new QPushButton( this, "m_buttonJoin" );
    m_buttonJoin->setText( i18n( "&Join" ) );
    m_buttonJoin->setAutoDefault( TRUE );
    m_buttonJoin->setDefault( TRUE );
    Layout2->addWidget( m_buttonJoin );

    m_buttonCancel = new QPushButton( this, "m_buttonCancel" );
    m_buttonCancel->setText( i18n( "&Cancel" ) );
    m_buttonCancel->setAutoDefault( TRUE );
    Layout2->addWidget( m_buttonCancel );
    UIChannelDialogBaseLayout->addLayout( Layout2 );

    // signals and slots connections
    connect( m_buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( m_view, SIGNAL( rightButtonClicked(QListViewItem*,const QPoint&,int) ), this, SLOT( slot_ViewMenu( QListViewItem *, const QPoint & ) ) );
    connect( m_view, SIGNAL( currentChanged(QListViewItem*) ), this, SLOT( slot_ViewClicked( QListViewItem * ) ) );
    connect( m_view, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slot_ViewClicked( QListViewItem * ) ) );
    connect( m_view, SIGNAL( doubleClicked(QListViewItem*) ), this, SLOT( slot_ViewExecuted( QListViewItem * ) ) );
    connect( m_view, SIGNAL( returnPressed(QListViewItem*) ), this, SLOT( slot_ViewExecuted( QListViewItem * ) ) );
    connect( m_viewCheck, SIGNAL( toggled(bool) ), this, SLOT( slot_ChanToggled( bool ) ) );
    connect( m_buttonJoin, SIGNAL( clicked() ), this, SLOT( slot_Join() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UIChannelDialogBase::~UIChannelDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void UIChannelDialogBase::slot_Join()
{
    qWarning( "UIChannelDialogBase::slot_Join(): Not implemented yet!" );
}

void UIChannelDialogBase::slot_ChanToggled( bool )
{
    qWarning( "UIChannelDialogBase::slot_ChanToggled( bool ): Not implemented yet!" );
}

void UIChannelDialogBase::slot_ViewClicked( QListViewItem * )
{
    qWarning( "UIChannelDialogBase::slot_ViewClicked( QListViewItem * ): Not implemented yet!" );
}

void UIChannelDialogBase::slot_ViewExecuted( QListViewItem * )
{
    qWarning( "UIChannelDialogBase::slot_ViewExecuted( QListViewItem * ): Not implemented yet!" );
}

void UIChannelDialogBase::slot_ViewMenu( QListViewItem *, const QPoint & )
{
    qWarning( "UIChannelDialogBase::slot_ViewMenu( QListViewItem *, const QPoint & ): Not implemented yet!" );
}

#include "uichanneldialogbase.moc"
