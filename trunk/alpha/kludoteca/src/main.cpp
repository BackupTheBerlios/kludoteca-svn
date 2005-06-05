/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// 	QFile f("ejemplo2.xml");
// 	QString xmldoc = "";
// 	
// 	if ( f.open( IO_ReadOnly ) )
// 	{
// 		QTextStream stream( &f );
// 		while ( !stream.atEnd() ) {
// 			xmldoc += stream.readLine() + "\n";
// 		}
// 		xmldoc += "\n";
// 	}
// 	
// 	
// 	RTK::Report aReport;
// 	if ( aReport.readXmlStr ( xmldoc) ) {
// 		RTK::OutputHtml o( "salida.html" );
// 		aReport.print ( o );
// 	}
 
#include "kludoteca.h"
#include "ldtapp.h"
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include "crashhandler.h"

#include "rtk.h"

#include <kmessagebox.h> 
#include <qfile.h>
#include <qpixmap.h>
#include <qsplashscreen.h>
#include <qtextstream.h>
#include "rtkoutputopenoffice.h"

#include "klpermission.h"
#include "kllogger.h"

static const char description[] = I18N_NOOP("System for administer a game store.");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
	{ "+[URL(s)]", I18N_NOOP( "Files/URLs to Open" ), 0 },
	{ "r", 0, 0 },
	{ "reconfigure", I18N_NOOP( "Reconfigure the application" ), 0 },
	{ 0, 0, 0 }
};

int main(int argc, char **argv)
{	
	KAboutData about( /*<NOCAMBIE>*/"kludoteca" /*</NOCAMBIE>*/,
			      I18N_NOOP( "KLudoteca" ), version,
			      I18N_NOOP( "System for administer a game store."), KAboutData::License_GPL,
			      I18N_NOOP( "David Cuadrado\n(C) 2005" ),
			      I18N_NOOP( "IRC:\nserver: irc.freenode.net / channel: #cetis\n\nEmail::\ncetis@univalle.edu.co" ),
			      I18N_NOOP( "http://www.cetisoft.org" ), "krawek@gmail.com" );

	
	about.addAuthor( "David Cuadrado", I18N_NOOP("Main developer"), "krawek@gmail.com" );
	about.addAuthor( "Juliana Davila", 0, "gobolindo@gmail.com" );
	about.addAuthor( "Daniel Valencia", 0, "dafevara@gmail.com" );
	
	about.addCredit( "Jorge Cuadrado", I18N_NOOP( "Thanks for your interest in this project, ideas, help and testing." ), "kuadrosxx@gmail.com" );
	
	about.addCredit( "Lila-theme Team", I18N_NOOP( "Thanks for your artwork!"));
	about.addCredit( "Amarok Team", I18N_NOOP("The best media player on the world ;)"));
	about.addCredit( "Konqueror Team", I18N_NOOP("Your about page rules!"));
	
	about.addCredit( "GNU Community", I18N_NOOP("Many thanks to all GNU community!!"));
	
	KCmdLineArgs::init(argc, argv, &about);
	KCmdLineArgs::addCmdLineOptions(options);
	
	LDTApp app;
	
	app.applyColors();
	
	if ( app.config()->readBoolEntry( "First Run", true ) )
	{
		app.firstDialog();
		if ( app.config()->readBoolEntry( "First Run", true ) )
		{
			KMessageBox::information(0, i18n("You need first configure the system"));
			return -1;
		}
	}
	
	QString splashPath = ::locate("data", "kludoteca/pics/klsplash-0.3.png" );;
	
	QSplashScreen *splash = 0;
	
	if ( ! splashPath.isEmpty() )
		splash = new QSplashScreen(QPixmap(splashPath));
	else
	{
		splash = new QSplashScreen();
	}
	splash->show();
	
	splash->message(i18n("Initializing application") );

	// registramos el cliente dcop para hacer IPC!
	app.dcopClient()->registerAs(app.name(), false);

	// Manejador de sesiones.
	if (app.isRestored())
	{
		// Restauramos la ultima sesion abierta.
		splash->message(i18n("Restoring application") );
		RESTORE(KLudoteca);
	}
	else
	{
		KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		
		if ( args->isSet("reconfigure") )
		{
 			splash->hide();
			app.firstDialog();
			std::cout << std::flush;
		}
		
		if (args->count() == 0) // Lanzamos la aplicacion sin argumentos
		{
			KLudoteca *widget = new KLudoteca;
			widget->show();
			
			sleep(1); // FIXME: Remove this stupid line!!
			splash->message(i18n("Application is running and up!") );
			
			splash->finish(widget);
			delete splash;
			
			widget->showValidateUser();
		}
		else // Analizamos los argumentos
		{
			int i = 0;
			for (; i < args->count(); i++)
			{
				KLudoteca *widget = new KLudoteca;
				widget->show();
				splash->message(i18n("Application is running and up!") );
				splash->finish(widget);
				delete splash;
			}
		}
		args->clear();
	}

	
	// TODO: Decomment to release
	//KCrash::setCrashHandler( Crash::crashHandler );
	
	return app.exec();
}
