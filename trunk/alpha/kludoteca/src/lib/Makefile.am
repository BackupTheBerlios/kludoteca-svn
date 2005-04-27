INCLUDES = -I$(top_srcdir)/src/admin-module -I$(top_srcdir)/src/games-module \
	-I$(top_srcdir)/src/tournament-module $(all_includes)
METASOURCES = AUTO
noinst_LIBRARIES = lib.a
noinst_HEADERS = lttoolbox.h ltlistview.h formbase.h kludotecaiface.h \
				bdconnection.h kldatabase.h klresultset.h klresultsetinterpreter.h klquery.h \
	klxmlreader.h
lib_a_SOURCES = lttoolbox.cpp ltlistview.cpp formbase.cpp kludotecaiface.skel \
				bdconnection.cpp kldatabase.cpp klresultset.cpp klresultsetinterpreter.cpp klquery.cpp \
	klxmlreader.cpp
