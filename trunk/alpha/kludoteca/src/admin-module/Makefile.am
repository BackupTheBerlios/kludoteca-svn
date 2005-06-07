INCLUDES = -I$(top_srcdir)/src/klreports -I$(top_srcdir)/src/lib \
	$(all_includes)
METASOURCES = AUTO
noinst_HEADERS = adminwidget.h adminusers.h admindatabase.h formadminusers.h \
	adminlogs.h
noinst_LIBRARIES = libadmin-module.a
libadmin_module_a_SOURCES = admindatabase.cpp adminusers.cpp adminwidget.cpp \
		formadminusers.cpp adminlogs.cpp

kladmimgsdir = $(kde_datadir)/kludoteca/admin-module/pics
kladmimgs_DATA = imgformusers.png
kladminiconsdir = $(kde_datadir)/kludoteca/admin-module/icons

dbdumpsdir = $(kde_datadir)/kludoteca/data/dumps
dbdumps_DATA = klbd.sql
