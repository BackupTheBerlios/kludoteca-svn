## Makefile.am for kludoteca

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kludoteca

# set the include path for X, qt and KDE
INCLUDES = -I$(top_srcdir)/rtklib -I$(top_srcdir)/src/admin-module \
	-I$(top_srcdir)/src/clients-module -I$(top_srcdir)/src/games-module -I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/rents-module -I$(top_srcdir)/src/tournament-module $(all_includes)

# the library search path. 
kludoteca_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
kludoteca_LDADD = $(top_builddir)/src/clients-module/libclients-module.a \
	$(top_builddir)/src/games-module/libgames-module.a $(top_builddir)/src/tournament-module/libtournament-module.a \
	$(top_builddir)/src/admin-module/libadmin-module.a $(top_builddir)/src/lib/lib.a \
	$(top_builddir)/src/rents-module/librents-library.a $(top_builddir)/rtklib/librtklib.a $(LIB_KFILE) $(LIB_KDEPRINT) \
	$(LIB_KDECORE) -lkmdi -lkhtml

# which sources should be compiled for kludoteca
kludoteca_SOURCES = main.cpp kludoteca.cpp kludotecaview.cpp pref.cpp osd.cpp \
				ldtapp.cpp crashhandler.cpp validateuser.cpp klfirstdialog.cpp

# these are the headers for your project
noinst_HEADERS = kludoteca.h kludotecaview.h pref.h osd.h ldtapp.h \
			crashhandler.h validateuser.h klfirstdialog.h

# client stuff

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kludoteca.pot

KDE_ICON = kludoteca

# this is where the kdelnk file will go 
kdelnkdir = $(kde_appsdir)/Utilities
kdelnk_DATA = kludoteca.desktop

# this is where the XML-GUI resource file goes
rcdir = $(kde_datadir)/kludoteca
rc_DATA = kludotecaui.rc


SUBDIRS = games-module admin-module tournament-module clients-module \
	rents-module lib
kldiconsdir = $(kde_datadir)/kludoteca/icons
kldicons_DATA = adminicon.png clientsicon.png gamesicon.png tournamenticon.png \
		klicon.png rentsicon.png
kldatadirdir = $(kde_datadir)/kludoteca/data
kldatadir_DATA = box-centre-image.png klstyle.css lightning.png mainpage.html \
	page2.html page4.html page5.html top-right-image.png bar-bottom-left.png \
	bar-bottom-middle.png bar-bottom-right.png bar-middle-left.png bar-middle-right.png \
	bar-top-left.png bar-top-middle.png bar-top-right.png bottom-left.png bottom-middle.png \
	bottom-right.png box-bottom-left.png box-bottom-middle.png box-bottom-right.png \
	box-middle-left.png box-middle-right.png box-top-left.png box-top-middle.png \
	box-top-right.png kl_infopage.css kl_infopage_rtl.css top-left.png top-middle.png
