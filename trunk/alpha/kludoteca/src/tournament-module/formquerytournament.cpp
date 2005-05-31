/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                           	   *
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

#include <klocale.h>
#include <qvgroupbox.h>
#include <kpassivepopup.h>
#include <qpainter.h>
#include <qsimplerichtext.h>

#include "klxmlreader.h"
#include "formquerytournament.h"

FormQueryTournament::FormQueryTournament(const QString &tournament, QWidget *parent)
	: FormBase(FormBase::Query, parent), m_tournament(tournament)
{
	setTitle(i18n("Query tournament %1").arg(tournament));
	setExplanation(i18n("This is the ranking of the tournament"));
	setupForm();
	setupButtons(FormBase::AcceptButton, FormBase::NoButton);
	
	this->setTextAcceptButton(i18n("Accept"));
// 	this->setTextCancelButton(i18n("Cancel"));
	KPassivePopup::message( "Tournament", this );
}


FormQueryTournament::~FormQueryTournament()
{
}


void FormQueryTournament::setupForm()
{
	setupTournamentInfo();
	
	new QLabel("<div align=center><h1>Results Table</h1></div>", this);
	
	m_resultTable = new KLTable(0,5, this);
	m_resultTable->setColumnLabels(QStringList() << i18n("Participant") << i18n("Win") << i18n("Draw") << i18n("Lost") << i18n("Total"));
 	fillTable();
}

void FormQueryTournament::setupTournamentInfo()
{
	QGroupBox *box = new QGroupBox(this);
	box->setMargin(10);
	
	//SELECT gamename,initdate,enddate,rounds,price from ldt_tournament join ldt_games on gameserialreference=serialreference where name='klthor';
	
	KLSelect sqlquery(QStringList() << "gamename" << "initdate" << "enddate" << "rounds" << "price", QStringList() << "ldt_tournament"); 
	sqlquery.setWhere("name="+SQLSTR(m_tournament));
	sqlquery.setJoin(QString("ldt_games"), KLSelect::On, QStringList() << "gameserialreference" << "serialreference");
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	KLSqlResults results = xmlreader.results();
	
	
	QGridLayout *layout = new QGridLayout(box, 7, 2, 5,2);
	
	layout->addWidget(new QLabel(i18n("Tournament:"), box), 0,0);
	layout->addWidget((new QLabel(m_tournament, box)), 0, 1);
	
	layout->addWidget(new QLabel(i18n("Init date:"), box), 1,0);
	layout->addWidget((new QLabel(results["initdate"], box)), 1, 1);
	
	layout->addWidget(new QLabel(i18n("End date:"), box), 2,0);
	layout->addWidget((new QLabel(results["enddate"], box)), 2, 1);
	
	layout->addWidget(new QLabel(i18n("Rounds:"), box), 3,0);
	layout->addWidget((new QLabel(results["rounds"], box)), 3, 1);
	
	layout->addWidget(new QLabel(i18n("Game:"), box), 4,0);
	layout->addWidget((new QLabel(results["gamename"], box)), 4, 1);
	
	layout->addWidget(new QLabel(i18n("Price:"), box), 5,0);
	layout->addWidget((new QLabel(results["price"], box)), 5, 1);
}

void FormQueryTournament::fillTable()
{
	if ( !m_resultTable)
		return;
	KLSelect sqlquery(QStringList() << "participant" << "win" << "draw" << "lost" << "total", QStringList() << "ldt_resultstable_view");
	sqlquery.setWhere("tournament="+SQLSTR(m_tournament));
	sqlquery.setOrderBy("total", KLSelect::Desc);
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	QStringList results = xmlreader.getResultsList();
	
	std::cout << "Tamaño: " << results.count() << std::endl;
	
	int count = 0;
	for(uint i = 0; i < results.count(); i+=5 )
	{
		std::cout << "LEIDO: "+results[count] << std::endl;
		
		QStringList data = QStringList() << results[i] << results[i+1] << results[i+2] << results[i+3] << results[i+4];
		
		m_resultTable->insertRowData(data);
		count++;
	}
	
	std::cout << "filas: " << m_resultTable->numRows() << std::endl;
}

void FormQueryTournament::accept()
{
	emit accepted();
}

void FormQueryTournament::clean()
{
}

#include "formquerytournament.moc"
