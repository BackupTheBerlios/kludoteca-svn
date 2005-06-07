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
#include <kdebug.h>

#include <iostream>

AdminDatabase::AdminDatabase(QWidget *parent) : LTListView(QStringList() << i18n("Dump Name") << i18n("Database Name") << i18n("Date"), LTListView::ButtonAdd, LTListView::ButtonModify,LTListView::ButtonDel, LTListView::NoButton, parent, "AdminDatabase")
{
	setupDatabaseTools();
	
	m_dumpDir = new QDir(locate("data", "kludoteca/data/dumps/"));
	setButtonText(LTListView::ButtonAdd, i18n("Backup"));
	setButtonText(LTListView::ButtonDel, i18n("Delete"));
	setButtonText(LTListView::ButtonModify, i18n("Restore"));
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
}

void AdminDatabase::delButtonClicked()
{
}

void AdminDatabase::getClickedItem(QListViewItem *item)
{
}

void AdminDatabase::modifyButtonClicked()
{
}

void AdminDatabase::queryButtonClicked()
{
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
