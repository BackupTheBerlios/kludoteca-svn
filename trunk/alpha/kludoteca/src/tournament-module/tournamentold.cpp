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

#define DEBUG_TOURNAMENTOLD 0
 
#include "tournamentold.h"
#include <klocale.h>
#include "formquerytournament.h"

TournamentOld::TournamentOld(QWidget *parent) : LTListView(QStringList() << i18n("Tournament name") << i18n("Game") << i18n("Date"), LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, LTListView::NoButton, parent = 0, "OldTournaments")
{
	setCaption(i18n("Tournament Old"));	
}


TournamentOld::~TournamentOld()
{
}

void TournamentOld::addButtonClicked()
{
}

void TournamentOld::delButtonClicked()
{
}

void TournamentOld::modifyButtonClicked()
{
}

void TournamentOld::queryButtonClicked()
{
#if DEBUG_TOURNAMENTOLD
	qDebug("TournamentOld: init addButtonClicked");
#endif
	QListViewItem *current = m_listView->currentItem();
	
	if ( ! current )
		return;
	
	QString tname = current->text(0);
	
	if( tname.isEmpty() || tname.isNull())
		return;

	QScrollView *scroll = new QScrollView(this);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormQueryTournament* formQueryTournament = new FormQueryTournament(tname ,scroll->viewport() );

	formQueryTournament->setType( FormBase::Add);
	connect(formQueryTournament, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formQueryTournament, SIGNAL(accepted()), scroll, SLOT(close()));

	scroll->addChild(formQueryTournament);
	
	emit sendWidget(scroll,i18n("Query tournament")); 
#if DEBUG_TOURNAMENTOLD
	qDebug("TournamentOld: end addButtonClicked");
#endif
}

void TournamentOld::fillList()
{
	m_listView->clear();
	KLSelect sqlquery(QStringList() << "name" << "gamename" << "initdate", QStringList() << "ldt_tournament_view");
	sqlquery.setWhere("not active");
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void TournamentOld::getClickedItem(QListViewItem *item)
{
}

#include "tournamentold.moc"
