#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './uisourcebase.ui'
**
** Created: Wed Mar 7 01:49:36 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uisourcebase.h"

#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qwidgetstack.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


/* 
 *  Constructs a UISourceBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
UISourceBase::UISourceBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "UISourceBase" );
    resize( 592, 480 ); 
    setCaption( i18n( "Form1" ) );
    UISourceBaseLayout = new QHBoxLayout( this ); 
    UISourceBaseLayout->setSpacing( 6 );
    UISourceBaseLayout->setMargin( 11 );

    sourceView = new QListView( this, "sourceView" );
    sourceView->addColumn( i18n( "Source" ) );
    sourceView->addColumn( i18n( "Type" ) );
    sourceView->addColumn( i18n( "Id" ) );
    QListViewItem * item_2 = new QListViewItem( sourceView, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_2, 0 );
    item->setText( 0, i18n( "Browsing" ) );
    item->setText( 1, i18n( "napster::browsing" ) );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, i18n( "Searches" ) );
    item->setText( 1, i18n( "napster::searches" ) );
    item_2->setText( 0, i18n( "Napster" ) );
    item_2->setText( 1, i18n( "napster" ) );

    item = new QListViewItem( sourceView, item_2 );
    item->setText( 0, i18n( "Transfers" ) );
    item->setText( 1, i18n( "transfers" ) );

    sourceView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, sourceView->sizePolicy().hasHeightForWidth() ) );
    sourceView->setMinimumSize( QSize( 170, 0 ) );
    sourceView->setMaximumSize( QSize( 170, 32767 ) );
    UISourceBaseLayout->addWidget( sourceView );

    WidgetStack1 = new QWidgetStack( this, "WidgetStack1" );
    UISourceBaseLayout->addWidget( WidgetStack1 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UISourceBase::~UISourceBase()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "uisourcebase.moc"
