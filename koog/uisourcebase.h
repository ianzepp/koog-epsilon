/****************************************************************************
** Form interface generated from reading ui file './uisourcebase.ui'
**
** Created: Wed Mar 7 01:39:08 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef UISOURCEBASE_H
#define UISOURCEBASE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QWidgetStack;

class UISourceBase : public QWidget
{ 
    Q_OBJECT

public:
    UISourceBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~UISourceBase();

    QListView* sourceView;
    QWidgetStack* WidgetStack1;

protected:
    QHBoxLayout* UISourceBaseLayout;
};

#endif // UISOURCEBASE_H
