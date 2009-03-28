####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = koog
koog_SOURCES = uichanneldialog.cpp uichanneldialogbase.ui uipagetext.cpp uipageview.cpp uipagemenu.cpp uichannelpage.cpp mp3header.cpp uipageheaderdrag.cpp uipageheaderbutton.cpp uipageheader.cpp uisetupdialog.cpp uisetupdialogbase.ui uibrowsepage.cpp uilibrarypage.cpp uilistview.cpp uisearch.cpp uisearchbase.ui uiconsolepage.cpp iosupport.cpp ionapstertransfer.cpp ionapsterconnection.cpp ionapstercodes.cpp iomessage.cpp ioconnection.cpp uitransferpage.cpp uisearchpage.cpp uipage.cpp koog.cpp main.cpp 
koog_LDADD   = -lkfile -lkdeui -lkdecore $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp koog.cpp koog.h koog.desktop lo32-app-koog.png lo16-app-koog.png uipage.cpp uipage.h uisearchpage.cpp uisearchpage.h uitransferpage.cpp uitransferpage.h ioconnection.cpp ioconnection.h iomessage.cpp iomessage.h ionapstercodes.cpp ionapstercodes.h ionapsterconnection.cpp ionapsterconnection.h ionapstertransfer.cpp ionapstertransfer.h iosupport.cpp iosupport.h uiconsolepage.cpp uiconsolepage.h uisearchbase.ui uisearch.cpp uisearch.h uilistview.cpp uilistview.h koog_question.xpm koog_cancel.xpm uilibrarypage.cpp uilibrarypage.h uiconfig.h uibrowsepage.cpp uibrowsepage.h uisetupdialogbase.ui uisetupdialog.cpp uisetupdialog.h uipageheader.cpp uipageheader.h uipageheaderbutton.cpp uipageheaderbutton.h uipageheaderdrag.cpp uipageheaderdrag.h mp3header.cpp mp3header.h napster.txt uichannelpage.cpp uichannelpage.h uipagemenu.cpp uipagemenu.h uipageview.cpp uipageview.h uipagetext.cpp uipagetext.h uichanneldialogbase.ui uichanneldialog.cpp uichanneldialog.h 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/koog.desktop $(kde_appsdir)/Applications/koog.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-koog.png $(kde_icondir)/locolor/32x32/apps/koog.png
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-koog.png $(kde_icondir)/locolor/16x16/apps/koog.png

uninstall-local:
	-rm -f $(kde_appsdir)/Applications/koog.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/koog.png
	-rm -f $(kde_icondir)/locolor/16x16/apps/koog.png

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
koog_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE´s XML GUI builing
#rcdir = $(kde_datadir)/koog
#rc_DATA = koogui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/koog.pot; \
	fi

