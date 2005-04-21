/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                        	  	   *
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
#include "tournamentactive.h"
#include <klocale.h>

TournamentActive::TournamentActive(QWidget *parent) : LTListView(QStringList() << i18n("Tournament name") << i18n("Game")<< i18n("Date"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent = 0, "ActiveTournaments")
{
	
}


TournamentActive::~TournamentActive()
{
}

void TournamentActive::addButtonClicked()
{
}

void TournamentActive::delButtonClicked()
{
	
}

void TournamentActive::modifyButtonClicked()
{
}

void TournamentActive::queryButtonClicked()
{
}

void TournamentActive::fillList()
{
	/*
	if ( !m_db )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	KLResultSet resultSet = m_db->select(QStringList() << "firstname" << "lastname", "ldt_clients");
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.parse(m_xmlsource) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	*/
}

void TournamentActive::getClickedItem(QListViewItem *item)
{
}

#include "tournamentactive.moc"
