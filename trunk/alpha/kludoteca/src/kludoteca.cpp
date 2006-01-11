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
#include "pref.h"

#include <qdragobject.h>
#include <kprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>

#include <kglobal.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kdeversion.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <kkeydialog.h>
#include <kaccel.h>
#include <kfiledialog.h>
#include <kconfig.h>

#include <kedittoolbar.h>

#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>
#include <ktoolbarbutton.h>
#include <kstandarddirs.h>

#include <qobjectlist.h>

#include "klpermission.h"
#include "klenterprise.h"

KLudoteca::KLudoteca() : DMainWindow( 0, "KLudoteca-main"), m_printer(0), m_childs(0), m_view(0), m_userValidator(0)
{
	std::cout << "Inicializando " << klapp->name() << std::endl;
	// accept dnd
	setAcceptDrops(true);
	
 	setIcon( QPixmap( locate("data", "kludoteca/icons/klicon.png" )) );
	
	// then, setup our actions
	setupActions();
	
	// and a status bar
	statusBar()->show();
	
	// apply the saved mainwindow settings, if any, and ask the mainwindow
	// to automatically save settings if changed: window size, toolbar
	// position, icon size, etc.
	setAutoSaveSettings();
	
	//setupToolWindows();
	setupOSD();
	
	m_userValidator = new ValidateUser(this, "UserValidator");
	
	LOGGER->log(i18n("Application initialized"));
	
// 	KToolBar *bar = new KToolBar( tabWidget() );
// 	KAction *closeCurrentTab = new KAction(bar);
// 	closeCurrentTab->setIconSet(SmallIcon("tab_remove"));
// 	closeCurrentTab->plug(bar);
// 	
// 	tabWidget()->setCornerWidget( bar, KToolBarButton::TopRight);
// 	tabWidget()->show();
// 	connect(closeCurrentTab, SIGNAL(activated()), SLOT(closeCurrent()));
}

KLudoteca::~KLudoteca()
{
	LOGGER->log(i18n("Application closed"));
}

void KLudoteca::setupOSD()
{
	m_osd = new OSDWidget("KLudoteca", this, "OSD");
	m_osd->setDuration( 2000 );
	m_osd->setEnabled( true );
	//osd->setOffset( 400,400 );
	//osd->setAlignment( OSDWidget::Right );
	m_osd->setScreen( 0 );
	m_osd->setShadow( true );
	m_osd->setBackgroundColor( QColor(65,56,115) );
	m_osd->setTextColor(Qt::yellow);
	m_osd->setFont( QFont("Arial", 22) );
}

void KLudoteca::setupActions()
{
	KStdAction::openNew(this, SLOT(newConnection()), actionCollection());
	//KStdAction::open(this, SLOT(fileOpen()), actionCollection());
	KStdAction::save(this, SLOT(fileSave()), actionCollection());
	KStdAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
	KStdAction::print(this, SLOT(filePrint()), actionCollection());
	
	KStdAction::close( this, SLOT( closeCurrent() ), actionCollection() );
	
	KStdAction::quit(kapp, SLOT(quit()), actionCollection());
	
	m_toolbarAction = KStdAction::showToolbar(this, SLOT(optionsShowToolbar()), actionCollection());
	m_statusbarAction = KStdAction::showStatusbar(this, SLOT(optionsShowStatusbar()), actionCollection());
	
	KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
	KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
	KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());
	
	// this doesn't do anything useful.  it's just here to illustrate
	// how to insert a custom menu and menu item
// 	KAction *custom = new KAction(i18n("Cus&tom Menuitem"), 0,
// 					this, SLOT(optionsPreferences()),
// 					actionCollection(), "custom_action");
	createGUI(0);
}

void KLudoteca::generateEnterpriseInfo()
{
	KLSelect sql(QStringList() <<   "nit" << "address"<< "name" << "phone" << "city", QString("ldt_enterprise"));
	
	KLResultSet resultSet = KLDM->execQuery(&sql);
	
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		LOGGER->log(i18n("I can't generate enterprise information"), KLLogger::Err);
		return;
	}
	
	KLSqlResults results = xmlreader.results();
	
	klenterprise->setName(results["name"]);
	klenterprise->setNit(results["nit"]);
	klenterprise->setPhone(results["phone"]);
	klenterprise->setCity(results["city"]);
	
	LOGGER->log(i18n("Open enterprise %1").arg(results["name"]), KLLogger::Inf);
}

void KLudoteca::setFullScreen()
{
	if ( ! this->isFullScreen() )
		this->showFullScreen();
	else
		this->showNormal();
}

void KLudoteca::setupToolWindows()
{
	removeAll();
	
	// Add the main view!
	m_view = new KLudotecaView(i18n("Welcome"), this);
	connect(m_view->mainPage(), SIGNAL(sendWidget(QWidget*, const QString & )) , this, SLOT(addWidget(QWidget*, const QString & )));
	// tell the KMainWindow that this is indeed the main widget

	addWidget(m_view, i18n("Welcome") );
	
	// Add the admin module
	if( klperm->activeAdminModule() )
	{
		m_adminWidget = new AdminWidget(this);
		m_adminWidget->setIcon( QPixmap( locate("data", "kludoteca/icons/adminicon.png" )) );
// 		m_toolWindows << addToolWindow( m_adminWidget, KDockWidget::DockLeft, getMainDockWidget() );
		toolWindow(DDockWindow::Left)->addWidget(i18n("Administer"), m_adminWidget);
		
		
		QObjectList* const list = m_adminWidget->queryList("LTListView");
		for( QObject *o = list->first(); o; o = list->next() )
		{
			if ( o )
			{
				LTListView *itempTmp = static_cast<LTListView*>(o);
				connect(itempTmp, SIGNAL(sendWidget(QWidget*, const QString& )), this, SLOT(addWidget(QWidget*, const QString& )));
				connect(itempTmp,SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
				itempTmp->fillList();
			}
		}
		delete list;
	}
	
	// Add the clients module
	if ( klperm->activeClientsModule())
	{
		m_clientsWidget = new ClientsWidget(LTListView::ButtonAdd, LTListView::ButtonDel, LTListView::ButtonModify, LTListView::ButtonQuery, this);
		m_clientsWidget->setIcon( QPixmap(  locate("data", "kludoteca/icons/clientsicon.png" )) );

		m_clientsWidget->fillList();

		toolWindow(DDockWindow::Left)->addWidget(i18n("Clients"), m_clientsWidget);
		connect(m_clientsWidget, SIGNAL(sendWidget(QWidget *, const QString & )), this, SLOT(addWidget(QWidget*, const QString & )));
		
		connect(m_clientsWidget, SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
	}
	
	// Add the game module
	if( klperm->activeGamesModule() )
	{
		m_gamesList = new GamesList(LTListView::ButtonAdd, LTListView::ButtonDel, LTListView::ButtonModify, LTListView::ButtonQuery, this);
		m_gamesList->setIcon( QPixmap(  locate("data", "kludoteca/icons/gamesicon.png" )) );
		m_gamesList->fillList();
		
		connect(m_gamesList, SIGNAL(sendWidget(QWidget*, const QString&  )), this, SLOT(addWidget(QWidget*, const QString& )));
		connect(m_gamesList, SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
		
// 		m_toolWindows << addToolWindow( m_gamesList, KDockWidget::DockLeft, getMainDockWidget() );
		toolWindow(DDockWindow::Left)->addWidget(i18n("Games"), m_gamesList);
	}
	
	// Add rents module
	if ( klperm->activeRentsModule() )
	{	
		m_rentsModule = new RentsModule(this);
		connect(m_rentsModule, SIGNAL(sendWidget(QWidget*, const QString& )), this, SLOT(addWidget(QWidget*, const QString& )));
		m_rentsModule->setIcon( QPixmap(  locate("data", "kludoteca/icons/rentsicon.png" )) );
// 		m_toolWindows << addToolWindow( m_rentsModule, KDockWidget::DockLeft, getMainDockWidget() );
		toolWindow(DDockWindow::Left)->addWidget(i18n("Rents"), m_rentsModule);
		
		ListLTListView listViews = m_rentsModule->listViews();
		
		for (uint i = 0; i < listViews.count(); i++)
		{
			LTListView *ltlv = static_cast<LTListView *>( listViews.at(i) );
			
			connect(ltlv, SIGNAL(sendWidget(QWidget*, const QString& )), this, SLOT(addWidget(QWidget*, const QString& )));
		
			connect(ltlv,SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
		
			ltlv->fillList();
		}
	}
	
	
	// Add tournament module
	if ( klperm->activeTournamentModule() )
	{
		m_tournamentWidget = new TournamentWidget(this);
		connect(m_tournamentWidget, SIGNAL(sendWidget(QWidget*, const QString& )), this, SLOT(addWidget(QWidget*, const QString&  )));
		
		m_tournamentWidget->setIcon( QPixmap(  locate("data", "kludoteca/icons/tournamenticon.png" )) );
		
		toolWindow(DDockWindow::Left)->addWidget(i18n("Tournaments"), m_tournamentWidget);
		
		ListLTListView listViews = m_tournamentWidget->listViews();
		
		for (uint i = 0; i < listViews.count(); i++)
		{
			LTListView *ltlv = static_cast<LTListView *>( listViews.at(i) );
			
			connect(ltlv, SIGNAL(sendWidget(QWidget*, const QString&  )), this, SLOT(addWidget(QWidget*, const QString&  )));
		
			connect(ltlv,SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
		
			ltlv->fillList();
		}
	}
	
	
	KLReportModule *reportWidget = new KLReportModule(this);
	
	connect(reportWidget, SIGNAL(sendWidget(QWidget*, const QString&  )), this, SLOT(addWidget(QWidget*, const QString&  )));
		
	connect(reportWidget,SIGNAL(message2osd(const QString& )), this, SLOT(showNotice(const QString& )));
	
	toolWindow(DDockWindow::Right)->addWidget(i18n("Reports"), reportWidget);
}

void KLudoteca::showValidateUser()
{
	if ( m_userValidator->exec() == KDialog::Accepted )
	{
		setupToolWindows();
		generateEnterpriseInfo();
	}
}

QSqlDatabase *KLudoteca::getDatabase(const QString &bdname, bool open)
{
	return KLDatabase::database(bdname, open);
}

void KLudoteca::saveProperties(KConfig *config)
{
	// the 'config' object points to the session managed
	// config file.  anything you write here will be available
	// later when this app is restored
	if (config)
	{
		std::cout << "Config exists!" << std::endl;
	}
}

void KLudoteca::readProperties(KConfig *config)
{
	// the 'config' object points to the session managed
	// config file.  this function is automatically called whenever
	// the app is being restored.  read in here whatever you wrote
	// in 'saveProperties'
}

void KLudoteca::dragEnterEvent(QDragEnterEvent *event)
{
	qDebug("Dragg!!");
	event->accept(QTextDrag::canDecode(event) || QImageDrag::canDecode(event));
}

void KLudoteca::dropEvent(QDropEvent *event)
{
	event->accept();
	qDebug("Droppp!!");
}

void KLudoteca::newConnection()
{
	if ( m_userValidator /*&& ! m_view*/)
	{
		showValidateUser();
	}
}

void KLudoteca::fileSave()
{
	// this slot is called whenever the File->Save menu is selected,
	// the Save shortcut is pressed (usually CTRL+S) or the Save toolbar
	// button is clicked
	
	// save the current file
}

void KLudoteca::fileSaveAs()
{
}

void KLudoteca::filePrint()
{
	// this slot is called whenever the File->Print menu is selected,
	// the Print shortcut is pressed (usually CTRL+P) or the Print toolbar
	// button is clicked
	if (!m_printer) m_printer = new KPrinter;
	if (m_printer->setup(this))
	{
		// setup the printer.  with Qt, you always "print" to a
		// QPainter.. whether the output medium is a pixmap, a screen,
		// or paper
		QPainter p;
		p.begin(m_printer);
		
// 		if( m_pCurrentWindow ) // FIXME
// 		{
// 			QObjectList* const list = m_pCurrentWindow->queryList("FormBase");
// 			for( QObject *o = list->first(); o; o = list->next() )
// 			{
// 				if ( o )
// 				{
// 					static_cast<FormBase*>(o)->print(&p, *m_printer);
// 				}
// 			}
// 			delete list;
// 		}
	
		// we let our view do the actual printing
// 		QPaintDeviceMetrics metrics(m_printer);
// 		m_view->print(&p, metrics.height(), metrics.width());
	
		// and send the result to the printer
		p.end();
	}
}

void KLudoteca::closeCurrent()
{
   	 // If there's a current view, close it
// 	if ( m_pCurrentWindow != 0 ) 
// 	{
// 		removeWidget( m_pCurrentWindow );
// 	}
}

void KLudoteca::optionsShowToolbar()
{
	// this is all very cut and paste code for showing/hiding the
	// toolbar
	if (m_toolbarAction->isChecked())
		toolBar()->show();
	else
		toolBar()->hide();
}

void KLudoteca::optionsShowStatusbar()
{
	// this is all very cut and paste code for showing/hiding the
	// statusbar
	if (m_statusbarAction->isChecked())
		statusBar()->show();
	else
		statusBar()->hide();
}

void KLudoteca::optionsConfigureKeys()
{
	KKeyDialog::configure(actionCollection());
}

void KLudoteca::optionsConfigureToolbars()
{
	saveMainWindowSettings(KGlobal::config(), autoSaveGroup());
}

void KLudoteca::newToolbarConfig()
{
	// this slot is called when user clicks "Ok" or "Apply" in the toolbar editor.
	// recreate our GUI, and re-apply the settings (e.g. "text under icons", etc.)
	createGUI(0);
	
	#if defined(KDE_MAKE_VERSION)
		# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
			applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
		# else
			applyMainWindowSettings(KGlobal::config());
		# endif
	#else
		applyMainWindowSettings(KGlobal::config());
	#endif
}

void KLudoteca::optionsPreferences()
{
	// popup some sort of preference dialog, here
	KLudotecaPreferences dlg;
	if (dlg.exec())
	{
		// redo your settings
	}
}

void KLudoteca::changeStatusbar(const QString& text)
{
	// display the text on the statusbar
	statusBar()->message(text);
}

void KLudoteca::changeCaption(const QString& text)
{
	// display the text on the caption
	setCaption(text);
}

void KLudoteca::showNotice(const QString &message)
{
	// necesito calcular el largo del mensaje para poner un tiempo prudente para leerlo... -krawek
	
	m_osd->setDuration( message.length() * 70 );
	m_osd->show(message, false, false);
}

#include "kludoteca.moc"
