INCLUDES = -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/klreports \
	$(all_includes)
METASOURCES = AUTO
noinst_HEADERS = tournamentwidget.h tournamentmodule.h tournamentold.h \
							tournamentactive.h formtournament.h tournamenttabbar.h participantslist.h \
					formparticipants.h roundlist.h formmatchorder.h matchgenerator.h formquerytournament.h
noinst_LIBRARIES = libtournament-module.a
libtournament_module_a_SOURCES = tournamentactive.cpp tournamentmodule.cpp \
							tournamentold.cpp tournamentwidget.cpp formtournament.cpp tournamenttabbar.cpp \
						participantslist.cpp formparticipants.cpp roundlist.cpp formmatchorder.cpp \
		matchgenerator.cpp formquerytournament.cpp
kldtournamenticonsdir = $(kde_datadir)/kludoteca/tournament-module/icons
kldtournamentpicsdir = $(kde_datadir)/kludoteca/tournament-module/pics


