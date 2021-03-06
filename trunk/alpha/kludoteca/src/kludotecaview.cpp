/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                        		   *
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


#include "kludotecaview.h"

#include <qpainter.h>
#include <qlayout.h>

#include <kurl.h>

// #include <ktrader.h>
// #include <klibloader.h>
#include <kmessagebox.h>
#include <krun.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <qtextcodec.h>

#include <kaboutdata.h>
#include <kapplication.h>
#include <kdebug.h>
// #include <kmessagebox.h>
#include <ksavefile.h>
#include <kstandarddirs.h>
#include <kaction.h>
#include <kiconloader.h>

#include <assert.h>
#include <qfile.h>
#include <qdir.h>

// The forms
#include "formadminusers.h"
#include "formadminclients.h"
#include "formadmingame.h"
#include "formtournament.h"
#include "klpermission.h"

QString *KLMainPageFactory::s_mainpage_html = 0;
QString *KLMainPageFactory::s_page2_html = 0;
QString *KLMainPageFactory::s_page4_html = 0;
QString *KLMainPageFactory::s_page5_html = 0;
QString *KLMainPageFactory::s_page3_html = 0;

KLMainPageFactory::KLMainPageFactory( QObject *parent, const char *name )
{
}

KLMainPageFactory::~KLMainPageFactory()
{
	delete s_mainpage_html;
	s_mainpage_html = 0;
	delete s_page2_html;
	s_page2_html = 0;
	delete s_page4_html;
	s_page4_html = 0;
	delete s_page5_html;
	s_page5_html = 0;
	delete s_page3_html;
	s_page3_html = 0;
}

QString KLMainPageFactory::loadFile( const QString& file )
{
	QString res;
	if ( file.isEmpty() )
		return res;

	QFile f( file );

	if ( !f.open( IO_ReadOnly ) )
		return res;

	QTextStream t( &f );

	res = t.read();

	QString basehref = QString::fromLatin1("<BASE HREF=\"file:") +
			file.left( file.findRev( '/' )) +
			QString::fromLatin1("/\">\n");
	QRegExp reg("<head>");
	reg.setCaseSensitive(FALSE);
	res.replace(reg, "<head>\n\t" + basehref);
	return res;
}

QString KLMainPageFactory::mainpage()
{
	if ( s_mainpage_html )
		return *s_mainpage_html;

	QString res = loadFile( locate( "data", "kludoteca/data/mainpage.html" ));
	if ( res.isEmpty() )
		return res;

	KIconLoader *iconloader = KGlobal::iconLoader();
	int iconSize = iconloader->currentSize(KIcon::Desktop);
	
	QString addclients_icon_path = locate("data","kludoteca/icons/clientsicon.png");
	
	
	QString addtournament_icon_path = locate("data","kludoteca/icons/tournamenticon.png");
	
	QString rents_icon_path = locate("data","kludoteca/icons/rentsicon.png");
	
	QString games_icon_path = locate("data","kludoteca/icons/gamesicon.png");
	QString applications_icon_path = iconloader->iconPath("kmenu", KIcon::Desktop );
	QString settings_icon_path = iconloader->iconPath("kcontrol", KIcon::Desktop );
	QString home_folder = QDir::homeDirPath();
	QString continue_icon_path = QApplication::reverseLayout()?iconloader->iconPath("1leftarrow", KIcon::Small ):iconloader->iconPath("1rightarrow", KIcon::Small );

	res = res.arg( locate( "data", "kludoteca/data/kl_infopage.css" ) );
	if ( kapp->reverseLayout() )
		res = res.arg( "@import \"%1\";" ).arg( locate( "data", "kludoteca/data/kl_infopage_rtl.css" ) );
	else
		res = res.arg( "..." );

	res = res.arg( i18n("KLudoteca") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n("Administer easyly your game store") )
			.arg( i18n("KLudoteca is an application for administer a game store.") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n( "Introduction" ) )
			.arg( i18n( "Tips" ) )
			.arg( i18n( "Specifications" ) )
			.arg( addclients_icon_path )
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "Add clients" ) )
			.arg( i18n( "Click for add clients" ) )
			.arg( addtournament_icon_path )
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "Add tournament" ) )
			.arg( i18n( "Click for create a new tournamet" ) )
			.arg( games_icon_path )
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "Add a game" ) )
			.arg( i18n( "Click for add a game" ) )
			.arg( rents_icon_path)
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "Rents a game" ) )
			.arg( i18n( "Click for rents a game" ) )
			.arg( applications_icon_path )
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "New functionally" ) )
			.arg( i18n( "..." ) )
			.arg( settings_icon_path )
			.arg(iconSize).arg(iconSize)
			.arg( i18n( "View Reports" ) )
			.arg( i18n( "Click to view reports!" ) )
			.arg( continue_icon_path )
			.arg( KIcon::SizeSmall ).arg( KIcon::SizeSmall )
			.arg( i18n( "Next: An Introduction to KLudoteca" ) )
			;
	i18n("...");

	s_mainpage_html = new QString( res );

	return res;
}

QString KLMainPageFactory::page2()
{
	if ( s_page2_html )
		return *s_page2_html;

	QString res = loadFile( locate( "data", "kludoteca/data/page2.html" ));
	if ( res.isEmpty() )
		return res;

	KIconLoader *iconloader = KGlobal::iconLoader();
	QString back_icon_path = QApplication::reverseLayout()?iconloader->iconPath("forward", KIcon::Small ):iconloader->iconPath("back", KIcon::Small );
	QString goaddclients_icon_path = iconloader->iconPath("gohome", KIcon::Small );
	QString continue_icon_path = QApplication::reverseLayout()?iconloader->iconPath("1leftarrow", KIcon::Small ):iconloader->iconPath("1rightarrow", KIcon::Small );

	res = res.arg( locate( "data", "kludoteca/data/kl_infopage.css" ) );
	if ( kapp->reverseLayout() )
		res = res.arg( "@import \"%1\";" ).arg( locate( "data", "kludoteca/data/kl_infopage_rtl.css" ) );
	else
		res = res.arg( "..." );

	res = res.arg( i18n("Administer easyly your game store") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n( "Administer easyly your game store") )
			.arg( i18n( "KLudoteca is an application for administer a game store..") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n( "Introduction" ) )
			.arg( i18n( "Tips" ) )
			.arg( i18n( "Specifications" ) )
			.arg( i18n( "KLudoteca makes that administer a game store an easy work "
			"In this application you can add clients and manage your information "
			"in a way fast and easy."
				  ) )
			.arg( i18n( "KLudoteca  is your option!"
			"You can use kludoteca for many things like"
			"add a <a href=\"addclient:/\">client</A> "
			"or administer tournament of games, "
			"or simply have catalogued the games.") )
			.arg( i18n( " ") )
			.arg( i18n( " ") )
			.arg( i18n( "For more detailed documentation on KLudoteca click <a href=\"%1\">here</a>." )
			.arg("exec:/khelpcenter") )
			.arg( i18n( "<em>Additional information:</em> This software is posible thanks to "
			"- GNU Community"
			"- All our friends"
			"- and me... X )") )
			.arg( "<img width='16' height='16' src=\"%1\">" ).arg( continue_icon_path )
			.arg( i18n( "Next: Tips &amp; Tricks" ) );


	s_page2_html = new QString( res );

	return res;
}

QString KLMainPageFactory::page4()
{
	if ( s_page4_html )
		return *s_page4_html;

	KIconLoader *iconloader = KGlobal::iconLoader();
	QString res = loadFile( locate( "data", "kludoteca/data/page4.html" ));
	QString continue_icon_path = QApplication::reverseLayout()?iconloader->iconPath("1leftarrow", KIcon::Small ):iconloader->iconPath("1rightarrow", KIcon::Small );
	if ( res.isEmpty() )
		return res;

	res = res.arg( locate( "data", "kludoteca/data/kl_infopage.css" ) );
	if ( kapp->reverseLayout() )
		res = res.arg( "@import \"%1\";" ).arg( locate( "data", "kludoteca/data/kl_infopage_rtl.css" ) );
	else
		res = res.arg( "" );

	res = res.arg( i18n("Administer easyly your game store") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n("Administer easyly your game store") )
			.arg( i18n("KLudoteca is an application for administer a game store..") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n( "Introduction" ) )
			.arg( i18n( "Tips" ) )
			.arg( i18n( "Specifications" ) )
			.arg( i18n("Specifications") )
			.arg( i18n("KLudoteca is designed to make easy the work. "
			"The aim of this project is give to community a good and powerfull software for administer your bussiness") )
			.arg( i18n("Technical features") )
			.arg( i18n("Implemented") )
			.arg( i18n("Description") )
			.arg( i18n("XML") )
			.arg( i18n("built-in") )
			.arg( i18n("Postgresql") )
			.arg( i18n("built-in") )
			.arg( i18n("database-module") )
			.arg( i18n("In progress") )
			.arg( i18n("3") )
			.arg( i18n("GUI") )
			.arg( i18n("built-in") )
			.arg( i18n("Extern in progress") )
			.arg( i18n("game-module") )
			.arg( i18n("built-in") )
			.arg( i18n("clients"))
			.arg( i18n("module"))
			.arg( i18n("built-in") )
			.arg( i18n("users module") )
			.arg( i18n("built-in") )
			.arg( i18n("rents module") )
			.arg( i18n("built-in") )
			.arg( i18n("G E N E R A L") )
			.arg( i18n("Feature") )
			.arg( i18n("Details") )
			.arg( i18n("Techs") )
			.arg( i18n("Protocols") )
			.arg( "addtournament:/" )
			.arg( "addclient:/" )
			.arg( "addgame:/" )
			.arg( i18n("Database techs") )
			.arg( i18n("Triggers"))
			.arg( i18n("Special functions"))
			.arg( i18n("PL/pgSQL"))
			.arg( "<img width='16' height='16' src=\"%1\">" ).arg( continue_icon_path )
			.arg( i18n("<a href=\"%1\">Return to KLudoteca</a>").arg("mainpage.html") );

	s_page4_html = new QString( res );

	return res;
}

QString KLMainPageFactory::page5()
{
	qDebug("Page 5");
	if ( s_page5_html )
		return *s_page5_html;

	QString res = loadFile( locate( "data", "kludoteca/data/page5.html" ));
	if ( res.isEmpty() )
		return res;

	KIconLoader *iconloader = KGlobal::iconLoader();
	QString viewmag_icon_path =
			iconloader->iconPath("viewmag", KIcon::Small );
	QString history_icon_path =
			iconloader->iconPath("history", KIcon::Small );
	QString openterm_icon_path =
			iconloader->iconPath("openterm", KIcon::Small );
	QString locationbar_erase_rtl_icon_path =
			iconloader->iconPath("clear_left", KIcon::Small );
	QString locationbar_erase_icon_path =
			iconloader->iconPath("locationbar_erase", KIcon::Small );
	QString window_fullscreen_icon_path =
			iconloader->iconPath("window_fullscreen", KIcon::Small );
	QString view_left_right_icon_path =
			iconloader->iconPath("view_left_right", KIcon::Small );
	QString continue_icon_path = QApplication::reverseLayout()?iconloader->iconPath("1leftarrow", KIcon::Small ):iconloader->iconPath("1rightarrow", KIcon::Small );

	res = res.arg( locate( "data", "kludoteca/data/kl_infopage.css" ) );
	if ( kapp->reverseLayout() )
		res = res.arg( "@import \"%1\";" ).arg( locate( "data", "kludoteca/data/kl_infopage_rtl.css" ) );
	else
		res = res.arg( "" );

	res = res.arg( i18n("Administer easyly your game store") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n("Administer easyly your game store") )
			.arg( i18n("KLudoteca is an application for administer a game store..") )
			.arg( i18n( "KLudoteca" ) )
			.arg( i18n( "Introduction" ) )
			.arg( i18n( "Tips" ) )
			.arg( i18n( "Specifications" ) )
			.arg( i18n( "Tips &amp; Tricks" ) )
			.arg( i18n( "You can browse the web with kludoteca!") )
			.arg( i18n( "You can use drag and drop for add games,users and so..." ))
			.arg( i18n( "When kludoteca is crash, you can send me detailed information of the problem!"))
			.arg( i18n( "The accel keys can simplify the work" ) )
			.arg( i18n( "You can change the application idiom in kcontrol, or launch the applicacion with KDE_LANG=[lang code] e.g. KDE_LANG=es kludoteca") )
			.arg( i18n( "You can reconnect with other users: only press a new connection icon") )
			.arg( "<a href=http://www.google.com>Go to google!</a>" )
			.arg( "" )
			.arg( "" )
			.arg( "" )
			.arg( i18n( "Thanks to <a href=\"%1\">DCOP</a> you can have full control over KLudoteca using a script."
				  ).arg("exec:/kdcop") )
			.arg( i18n( "<img width='16' height='16' src=\"%1\">" ).arg( continue_icon_path ) )
			.arg( i18n( "Next: Specifications" ) )
			;


	s_page5_html = new QString( res );

	return res;
}


QString KLMainPageFactory::page3()
{
	if ( s_page3_html )
		return *s_page3_html;

	QString res = loadFile( locate( "data", kapp->reverseLayout() ? "kludoteca/data/page6.html" : "kludoteca/data/page3.html" ))
			.arg(i18n("Installed Plugins"))
			.arg(i18n("<td>Plugin</td><td>Description</td><td>File</td><td>Types</td>"))
			.arg(i18n("Installed"))
			.arg(i18n("<td>Mime Type</td><td>Description</td><td>Suffixes</td><td>Plugin</td>"));
	if ( res.isEmpty() )
		return res;

	s_page3_html = new QString( res );

	return res;
}


/*****************************
 *        KLMainPage              *
*****************************/

KLMainPage::KLMainPage( QWidget *parentWidget, const char *widgetName, QObject *parent, const char *name )
	: KHTMLPart( parentWidget, widgetName, parent, name, BrowserViewGUI ), m_parent(parentWidget)
{
	QTextCodec* codec = KGlobal::locale()->codecForEncoding();
	if (codec)
		setCharset(codec->name(), true);
	else
		setCharset("iso-8859-1", true);
        // about:blah isn't a kioslave -> disable View source
	KAction * act = actionCollection()->action("viewDocumentSource");
	if ( act )
		act->setEnabled( false );
	
	setOnlyLocalReferences(true);
	setPluginsEnabled(false);
	
	serve( KLMainPageFactory::mainpage(), "kludoteca");
}

KLMainPage::~KLMainPage()
{
}

bool KLMainPage::openURL( const KURL &u )
{
	if ( u.protocol() == "http")
	{
		qDebug("Openning google");
		KHTMLPart::openURL(u);
	}
	if ( u.protocol() == "addtournament" )
	{
		this->urlSelected("addtournament:/", 1, 0, QString::null);
	}
	else
		serve( KLMainPageFactory::mainpage(), "kludoteca" );
	return true;
}

bool KLMainPage::openFile()
{
	return true;
}

void KLMainPage::saveState( QDataStream &stream )
{
	stream << m_htmlDoc;
	stream << m_what;
}

void KLMainPage::restoreState( QDataStream &stream )
{
	stream >> m_htmlDoc;
	stream >> m_what;
	serve( m_htmlDoc, m_what );
}

void KLMainPage::serve( const QString& html, const QString& what )
{
	m_what = what;
	begin( KURL( QString("about:%1").arg(what) ) );
	write( html );
	end();
	m_htmlDoc = html;
}

void KLMainPage::addTournament(const QString &name)
{
	if ( klperm->activeTournamentModule() )
	{
		QScrollView *scroll = new QScrollView(0, 0, Qt::WDestructiveClose);
		scroll->setResizePolicy(QScrollView::AutoOneFit);
		FormTournament *formAdminTournament = new FormTournament(FormBase::Add , scroll->viewport() );
		
		connect(formAdminTournament, SIGNAL(cancelled()), scroll, SLOT(close()));
		
		scroll->addChild(formAdminTournament);
	
		formAdminTournament->setTitle(i18n("Add a tournament"));
		formAdminTournament->setExplanation(i18n("Fill the fields with the new tournament information"));
		
		emit sendWidget(scroll, i18n("Add tournament") );
	}
	else
	{
		KMessageBox::error(0, i18n("You doesn't have permissions to add tournaments, sorry!"));
	}
}

void KLMainPage::addClient() // FIXME: remove duplicate code
{
	if ( klperm->activeClientsModule() )
	{
		QScrollView *scroll = new QScrollView(0);
		scroll->setResizePolicy(QScrollView::AutoOneFit);
		FormAdminClients *formAdminClients = new FormAdminClients( FormBase::Add, scroll->viewport() );
		scroll->addChild(formAdminClients);
		
		formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);
		
		formAdminClients->setTitle(i18n("Admin Clients"));
		formAdminClients->setExplanation(i18n("Fill the fields with the client information"));
		
		emit sendWidget( scroll, i18n("Add Client") );
	}
	else
	{
		KMessageBox::error(0, i18n("You doesn't have permissions to add clients, sorry!"));
	}
}

#include <iostream>

void KLMainPage::urlSelected( const QString &url, int button, int state, const QString &target, KParts::URLArgs _args )
{
	qDebug(QString("url: %1").arg(url));
	KURL u( url );
	if ( u.protocol() == "exec" )
	{
		QStringList args = QStringList::split( QChar( ' ' ), url.mid( 6 ) );
		QString executable = args[ 0 ];
		args.remove( args.begin() );
		KApplication::kdeinitExec( executable, args );
		return;
	}

	if ( url == QString::fromLatin1("mainpage.html") )
	{
 		emit browserExtension()->openURLNotify();
		serve( KLMainPageFactory::mainpage(), "kludoteca" );
		return;
	}
	else if ( url == QString::fromLatin1("page2.html") )
	{
		emit browserExtension()->openURLNotify();
		serve( KLMainPageFactory::page2(), "kludoteca" );
		return;
	}
	else if ( url == QString::fromLatin1("page4.html") )
	{
		emit browserExtension()->openURLNotify();
		serve( KLMainPageFactory::page4(), "kludoteca" );
		return;
	}
	else if ( url == QString::fromLatin1("page5.html") )
	{
		emit browserExtension()->openURLNotify();
		serve( KLMainPageFactory::page5(), "kludoteca" );
		return;
	}
	else if ( u.protocol() == "addtournament")
	{
		addTournament();
		return;
	}
	else if (u.protocol() == "addclient")
	{
		addClient();
		return;
	}
	else if(u.protocol() == "rents")
	{
		return;
	}
	else if (u.protocol() == "unkown")
	{
		KMessageBox::information(m_parent, i18n("Cooming soon"), i18n("Information"));
		return;
	}
	else if (u.protocol() == "http")
	{
		KHTMLPart::openURL(u);
	}
	
	qDebug(QString("Protocolo: %1").arg(u.protocol()));

	KHTMLPart::urlSelected( url, button, state, target, _args );
}

/*****************************
 *        KLudotecaView      *
*****************************/

KLudotecaView::KLudotecaView(const QString &caption, QWidget *parentWidget, const char *name, WFlags f) : QHBox(caption, parentWidget, name, f), DCOPObject("KLudotecaIface")
{	
	m_mainPage = new KLMainPage(this, "MainView", this, "MainPage");
}

KLudotecaView::~KLudotecaView()
{
}

void KLudotecaView::print(QPainter *p, int height, int width)
{
	//  TODO: Hacer la impresion aqui.
}

void KLudotecaView::setMessage(const QString &texto)
{
}

KLMainPage *KLudotecaView::mainPage()
{
	return m_mainPage;
}

void KLudotecaView::addTournament(const QString &tournamentName)
{
	m_mainPage->addTournament(tournamentName);
}

void KLudotecaView::addClient()
{
	m_mainPage->addClient();
}

#include "kludotecaview.moc"
