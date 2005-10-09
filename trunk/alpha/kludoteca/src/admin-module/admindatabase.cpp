/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        	   *
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

#define DEBUG_ADMINDB 0
#include "admindatabase.h"
#include <klocale.h>
#include <kstandarddirs.h>
#include <kmessagebox.h>
#include <kdebug.h>
#include <kprocess.h>


#include "ldtapp.h"

#include <iostream>

#include <ktrader.h>
#include <klibloader.h>

AdminDatabase::AdminDatabase(QWidget *parent) : LTListView(QStringList() << i18n("Dump Name") << i18n("Database Name") << i18n("Date"), LTListView::ButtonAdd, LTListView::ButtonModify,LTListView::ButtonQuery, LTListView::ButtonDel, parent, "AdminDatabase")
{
	setupDatabaseTools();
	
	m_dumpDir = new QDir(locate("data", "kludoteca/data/dumps/"));
	setButtonText(LTListView::ButtonAdd, i18n("Backup"));
	setButtonText(LTListView::ButtonDel, i18n("Delete"));
	setButtonText(LTListView::ButtonModify, i18n("Restore"));
	setButtonText(LTListView::ButtonQuery, i18n("See file"));
}


AdminDatabase::~AdminDatabase()
{
}

void AdminDatabase::setupDatabaseTools()
{
	QProcess proc(this);
	proc.addArgument("psql");
	
	if (! proc.start() )
	{
		m_havePsql = false;
	}
	else
	{
		kdDebug() << "Command psql find it = )" << endl;
		m_havePsql = true;
		proc.tryTerminate();
	}

	proc.clearArguments();
	
	proc.addArgument("pg_dump");
	
	if (! proc.start() )
	{
		m_havePgDump = false;
	}
	else
	{
		m_havePgDump = true;
		kdDebug() << "Command pg_dump find it = )" << endl;
		proc.tryTerminate();
	}
	
}

void AdminDatabase::fillList()
{
	m_listView->clear();
	const QFileInfoList *files = m_dumpDir->entryInfoList("*.sql");
	
	if ( files )
	{
		QFileInfoListIterator it( *files );
		QFileInfo * fi = 0;
		while( (fi=it.current()) != 0 )
		{
			++it;
			KListViewItem *item = new KListViewItem(m_listView);
			
			item->setText(0, fi->baseName().section('.', 0,0) );
			
			QFile tmp(fi->absFilePath());
			tmp.open(IO_ReadOnly);
			QTextStream stream( &tmp );
			item->setText(1, stream.readLine().section("--",1,1));
			tmp.close();
			item->setText(2, fi->created().toString(Qt::ISODate));
		}
		
	}
}

void AdminDatabase::addButtonClicked()
{
	// pg_dump -h localhost -U kladmin kludoteca
	std::cout << "Making backup..." << std::endl;
	if ( m_havePgDump )
	{
		KProcess *proc = new KProcess(this);
		
		*proc << "pg_dump";
		*proc << "-h" << klapp->config("Connection")->readEntry("Server", "localhost");
		*proc << "-U" << klapp->config("Connection")->readEntry("Login");
		*proc << klapp->config("Connection")->readEntry("Database");
		
		connect(proc, SIGNAL(receivedStdout (KProcess *, char *, int )), this, SLOT(makeDump(KProcess *, char *, int ) ));
		connect(proc, SIGNAL(processExited(KProcess *)), this, SLOT(saveBackup(KProcess *)));
		
		LOGGER->log(i18n("Making backup"), KLLogger::Inf);
		
		proc->start(KProcess::NotifyOnExit , KProcess::Stdout);
	}
	else
	{
		QString error = "";
		if ( ! m_havePgDump )
			error += "You doesn't have the command pg_dump\n";
// 		if ( !m_havePsql)
// 			error += "You doesn't have the command psql\n";
		
		KMessageBox::detailedSorry (0, i18n("I can't backup the database!"), error);
	}
}

void AdminDatabase::makeDump(KProcess *p, char *b, int fd)
{
// 	std::cout << "Leido: " << b << std::endl;
	m_backup += QString(b);
}

void AdminDatabase::saveBackup(KProcess *proc)
{
	if (proc->normalExit() )
	{
		QFile file(m_dumpDir->absPath()+"/"+"backup-"+QDate::currentDate().toString(Qt::ISODate)+".sql");
		
		if ( file.open(IO_WriteOnly) )
		{
			QTextStream stream( &file );
			
			stream << "-- KLudoteca-"+QDate::currentDate().toString(Qt::ISODate) << endl;
			stream << m_backup;
			
			file.close();
			
			fillList();
		}
	}
	else
	{
		LOGGER->log(i18n("Error making backup"),KLLogger::Err);
	}
}

void AdminDatabase::delButtonClicked()
{
	if ( ! m_listView->currentItem() )
		return;
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete this file ?"));
	
	if (opt == KMessageBox::Yes )
	{
		if ( m_dumpDir->remove(m_listView->getText(0)+".sql") )
			delete m_listView->currentItem();
		else
		{
			KMessageBox::error(this, i18n("I can't delete this file!\n"));;
		}
	}
}

void AdminDatabase::getClickedItem(QListViewItem *item)
{
	queryButtonClicked();
}

void AdminDatabase::modifyButtonClicked() // RESTORE
{
	std::cout << "Restoring backup..." << std::endl;
	if ( m_havePsql )
	{
		KProcess *proc = new KProcess(this);
		
		*proc << "psql";
		*proc << "-h" << klapp->config("Connection")->readEntry("Server", "localhost");
		*proc << "-U" << klapp->config("Connection")->readEntry("Login");
		*proc << klapp->config("Connection")->readEntry("Database");
		*proc << "-f" << m_dumpDir->absPath()+"/"+"backup-"+QDate::currentDate().toString(Qt::ISODate)+".sql"; // TODO: Cambiar esto
		
// 		connect(proc, SIGNAL(receivedStdout (KProcess *, char *, int )), this, SLOT(makeDump(KProcess *, char *, int ) ));
// 		connect(proc, SIGNAL(processExited(KProcess *)), this, SLOT(saveBackup(KProcess *)));
		
		LOGGER->log(i18n("Making backup"), KLLogger::Inf);
		
		proc->start(/*KProcess::NotifyOnExit , KProcess::Stdout*/);
	}
	else
	{
		QString error = "";
		if ( ! m_havePsql )
			error += "You doesn't have the command psql\n";
// 		if ( !m_havePsql)
// 			error += "You doesn't have the command psql\n";
		
		KMessageBox::detailedSorry (0, i18n("I can't restore the database!"), error);
	}
}

void AdminDatabase::queryButtonClicked()
{
	if ( ! m_listView->currentItem() )
		return;
	
	QVBox *widget = new QVBox(this);

	KTrader::OfferList offers = KTrader::self()->query("text/plain", "'KParts/ReadOnlyPart' in ServiceTypes");
	
	KLibFactory *factory = 0;

	KTrader::OfferList::Iterator it(offers.begin());
	for( ; it != offers.end(); ++it)
	{
		KService::Ptr ptr = (*it);
		factory = KLibLoader::self()->factory( ptr->library() );
		if (factory)
		{
			m_part = static_cast<KParts::ReadOnlyPart *>(factory->create(widget, ptr->name(), "KParts::ReadOnlyPart"));
			m_part->openURL("file://"+m_dumpDir->absPath()+"/"+m_listView->getText(0)+".sql");
			break;
		}
	}
	
	if (!factory)
	{
		KMessageBox::error(this, i18n("Could not find a suitable  component"));
		return;
	}
	
	emit sendWidget(widget,i18n("View dump")); 
}

void AdminDatabase::addItem(const QString &pkey)
{
}

void AdminDatabase::updateItem(const QString &pkey)
{
}

void AdminDatabase::slotFilter(const QString &filter)
{
}

void AdminDatabase::showEvent(QShowEvent *e)
{
	QVBox::showEvent(e);
	fillList();
}

#include "admindatabase.moc"
