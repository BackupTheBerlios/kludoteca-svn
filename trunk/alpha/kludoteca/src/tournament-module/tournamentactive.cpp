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

#define DEBUG_TOURNAMENT 1
 
#include "tournamentactive.h"
#include "formquerytournament.h"
#include <klocale.h>

TournamentActive::TournamentActive(QWidget *parent) : LTListView(QStringList() << i18n("Tournament name") << i18n("Game") << i18n("Date"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::ButtonModify, LTListView::ButtonDel, parent = 0, "ActiveTournaments")
{
	setCaption(i18n("Tournament"));
	m_listView->setTitle(i18n("Active Tournaments"));
	m_listView->setExplain(i18n("Please click in the \"Add\" button for add a tournament"));
}

TournamentActive::~TournamentActive()
{
}

void TournamentActive::addButtonClicked()
{
#if DEBUG_TOURNAMENT
	qDebug("TournamentActive: init addButtonClicked");
#endif
	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormTournament* formTournament = new FormTournament(FormBase::Add, scroll->viewport() );
	connect(formTournament, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));

	formTournament->setType( FormBase::Add);
	connect(formTournament, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formTournament, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));

	scroll->addChild(formTournament);
	
	emit sendWidget(scroll, i18n("Add tournament")); 
#if DEBUG_TOURNAMENT
	qDebug("TournamentActive: end addButtonClicked");
#endif
}

void TournamentActive::delButtonClicked()
{
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete the tournament %1 ?").arg(itemp->text(0)));
	
	if (opt == KMessageBox::Yes )
	{
		KLDelete del("ldt_tournament");
		del.setWhere("name="+SQLSTR(itemp->text(0)));
		
		KLDM->execQuery(&del);
		
		if ( ! KLDM->isLastError() )
		{
			delete itemp;
			
			emit message2osd(i18n("The tournament has been deleted!!"));
			emit tournamentModified();
		}
		else
		{
			KMessageBox::error(this, i18n("I can't delete this tournament!\n"
					"The error was %1").arg(KLDM->lastError().text())  , i18n("Error"));
		}
	}
}

void TournamentActive::modifyButtonClicked()
{
	if( ! m_listView->currentItem() )
		return;

	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormTournament* formTournament = new FormTournament(FormBase::Edit, scroll->viewport() );
	connect(formTournament, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	formTournament->fillFormulate( m_listView->currentItem()->text(0));
	formTournament->setGame( m_listView->currentItem()->text(1));


	connect(formTournament, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formTournament, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));

	scroll->addChild(formTournament);
	
	
	emit sendWidget(scroll,i18n("Add tournament")); 
}

void TournamentActive::queryButtonClicked()
{
	QListViewItem *current = m_listView->currentItem();
	
	if ( ! current )
		return;
	
	QString tname = current->text(0);
	
	if( tname.isEmpty() || tname.isNull())
		return;

	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormQueryTournament* formQueryTournament = new FormQueryTournament(tname ,scroll->viewport() );

	formQueryTournament->setType( FormBase::Add);
	connect(formQueryTournament, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formQueryTournament, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));

	scroll->addChild(formQueryTournament);
	
	emit sendWidget(scroll,i18n("Query tournament")); 
}

void TournamentActive::fillList()
{
	m_listView->clear();
	KLSelect sqlquery(QStringList() << "name" << "gamename" << "initdate", QStringList() << "ldt_tournament_view");
	sqlquery.setWhere("active");
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void TournamentActive::getClickedItem(QListViewItem *item)
{
}

void TournamentActive::addItem(const QString &pkey)
{
	std::cout << "Adicionando item con pkey: " << pkey << std::endl;
	
	KLSelect sqlquery(QStringList() << "name" << "gamename" << "initdate", QStringList() << "ldt_tournament_view");
	sqlquery.setWhere("active");
	
	sqlquery.setWhere("name="+SQLSTR(pkey));

	KLResultSet resultSet = KLDM->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	else
	{
		emit tournamentModified();
	}
}

void TournamentActive::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		KLSelect sqlquery(QStringList() << "name" << "gamename" << "initdate", QStringList() << "ldt_tournament_view");
		sqlquery.setWhere("active");

		sqlquery.addFilter(filter);
		
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
	}
}

#include "tournamentactive.moc"
