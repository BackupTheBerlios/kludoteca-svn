## Makefile.am for kludoteca

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kludoteca

# set the include path for X, qt and KDE
INCLUDES = -I$(top_srcdir)/src/admin-module -I$(top_srcdir)/src/clients-module \
	-I$(top_srcdir)/src/games-module -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/tournament-module \
	$(all_includes)

# the library search path. 
kludoteca_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
kludoteca_LDADD = $(top_builddir)/src/bd-module/libbd-module.a \
	$(top_builddir)/src/clients-module/libclients-module.a $(top_builddir)/src/games-module/libgames-module.a \
	$(top_builddir)/src/tournament-module/libtournament-module.a $(top_builddir)/src/admin-module/libadmin-module.a \
	$(top_builddir)/src/lib/lib.a $(LIB_KFILE) $(LIB_KDEPRINT) -lkmdi

# which sources should be compiled for kludoteca
kludoteca_SOURCES = main.cpp kludoteca.cpp kludotecaview.cpp pref.cpp osd.cpp \
	ldtapp.cpp

# these are the headers for your project
noinst_HEADERS = kludoteca.h kludotecaview.h pref.h osd.h ldtapp.h

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


SUBDIRS = games-module admin-module tournament-module clients-module lib \
	bd-module
kldiconsdir = $(kde_datadir)/kludoteca/icons
kldicons_DATA = adminicon.png clientsicon.png gamesicon.png tournamenticon.png
