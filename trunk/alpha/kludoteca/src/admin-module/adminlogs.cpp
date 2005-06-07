/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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

#include "adminlogs.h"
#include <klocale.h>:

AdminLogs::AdminLogs(QWidget *parent) : LTListView(QStringList() << i18n("Date") << i18n("Priority") << i18n("Message"), LTListView::ButtonAdd, LTListView::ButtonDel, LTListView::ButtonModify, LTListView::NoButton, parent, "AdminLogs")
{
}


AdminLogs::~AdminLogs()
{
}


void AdminLogs::fillList()
{
	m_listView->clear();
	QFile file(LOGGER->getFilePath());
	
	if( file.open(IO_ReadOnly) )
	{
		QTextStream stream( &file );
		QString line;
		while ( !stream.atEnd() )
		{
			line = stream.readLine(); 
			QStringList items; // = QStringList::split(" ", line);
			
			items << line.section(' ', 1, 1)  << line.section( ": ", 0, 0) << line.section(' ', 2);
			
			LTListViewItem *log = new LTListViewItem(m_listView);
			for(uint i = 0; i < items.count(); i++)
			{
				log->setText(i, items[i]);
			}
		}
		file.close();
	}
}

void AdminLogs::addButtonClicked()
{
}

void AdminLogs::delButtonClicked()
{
}

void AdminLogs::getClickedItem(QListViewItem* item)
{
}

void AdminLogs::modifyButtonClicked()
{
}

void AdminLogs::queryButtonClicked()
{
}

void AdminLogs::showEvent(QShowEvent *e)
{
	QVBox::showEvent(e);
	fillList();
}


#include "adminlogs.moc"
