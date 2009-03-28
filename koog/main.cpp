/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Mar  7 00:47:09 EST 2001
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "koog.h"

static const char *description =
	I18N_NOOP("Koog");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "koog", I18N_NOOP("Koog"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2001, Ian Zepp", 0, 0, "iszepp@bulldog.unca.edu");
  aboutData.addAuthor("Ian Zepp",0, "iszepp@bulldog.unca.edu");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;
  Koog *koog = new Koog();
  a.setMainWidget(koog);
  koog->show();  

  return a.exec();
}
