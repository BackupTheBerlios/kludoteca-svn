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

#include "kludoteca.h"
#include "ldtapp.h"
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include "crashhandler.h"

#include "bdconnection.h"

#include <kstandarddirs.h>

static const char description[] = I18N_NOOP("System for administer a game store.");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
    KCmdLineLastOption
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
	
	about.addCredit( "GNU Community", I18N_NOOP("Many thanks to all GNU community!!"));
	
	// FIXME: Esto produce una violacion de segmento!
	//about.setProgramLogo( QPixmap( locate("data", "kludoteca/icons/klicon.png" )).convertToImage() );
	
	KCmdLineArgs::init(argc, argv, &about);
	KCmdLineArgs::addCmdLineOptions(options);
	
	LDTApp app;
	
	QColorGroup group = QApplication::palette().active();
	const QColor bg( 32,32,82 );
	const QColor bgAlt( 57, 64, 98 );

	group.setColor( QColorGroup::Text, Qt::white );
	group.setColor( QColorGroup::Base, bg );
	group.setColor( QColorGroup::Foreground, 0xd7d7ef );
	group.setColor( QColorGroup::Background, bgAlt );

	group.setColor( QColorGroup::Button, bgAlt );
	group.setColor( QColorGroup::ButtonText, 0xd7d7ef );

	group.setColor( QColorGroup::Highlight, Qt::white );
	group.setColor( QColorGroup::HighlightedText, bg );
	int h,s,v;
	bgAlt.getHsv( &h, &s, &v );
	group.setColor( QColorGroup::Midlight, QColor( h, s/3, (int)(v * 1.2),QColor::Hsv ) );
	QPalette pal(group, group, group);
	app.setPalette(pal);
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
			widget->showValidateUser();
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
	
	KCrash::setCrashHandler( Crash::crashHandler );
	
	return app.exec();
}
