/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        *
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

#include "kludoteca.h"
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] = I18N_NOOP("System for administer a ludotec.");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
	KAboutData about( "KLudoteca",
			      I18N_NOOP( "KLudoteca" ), version,
			      I18N_NOOP( "System for administer a ludotec."), KAboutData::License_GPL,
			      I18N_NOOP( "CetiSoft\n(C) 2005" ),
			      I18N_NOOP( "IRC:\nserver: irc.freenode.net / channel: #cetis\n\nEmail::\ncetis@univalle.edu.co" ),
			      I18N_NOOP( "http://www.cetisoft.org" ) );

	
	about.addAuthor( "David Cuadrado", I18N_NOOP("Main developer"), "krawek@gmail.com" );
	about.addAuthor( "Juliana Davila", 0, "gobolindo@gmail.com" );
	about.addAuthor( "Daniel Valencia", 0, "dafevara@gmail.com" );
	
	about.addCredit( "Jorge Cuadrado", I18N_NOOP( "Thanks for your interest in this project, ideas, help and testing." ), "kuadrosxx@gmail.com" );
	
	KCmdLineArgs::init(argc, argv, &about);
	KCmdLineArgs::addCmdLineOptions(options);
	KApplication app;
	
	// registramos el cliente dcop para hacer IPC!
	app.dcopClient()->registerAs(app.name(), false);

	// Manejador de sesiones.
	if (app.isRestored())
	{
		// Restauramos la ultima sesion abierta.
		RESTORE(KLudoteca);
	}
	else
	{
		KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		if (args->count() == 0) // Lanzamos la aplicacion sin argumentos
		{
			KLudoteca *widget = new KLudoteca;
			widget->show();
		}
		else // Analizamos los argumentos
		{
			int i = 0;
			for (; i < args->count(); i++)
			{
				KLudoteca *widget = new KLudoteca;
				widget->show();
			}
		}
		args->clear();
	}
	
	return app.exec();
}
