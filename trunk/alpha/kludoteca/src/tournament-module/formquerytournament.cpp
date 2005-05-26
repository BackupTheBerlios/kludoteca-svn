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
#include "formquerytournament.h"
#include <klocale.h>
#include "klxmlreader.h"

FormQueryTournament::FormQueryTournament(const QString &tournament, QWidget *parent)
	: FormBase(FormBase::Query, parent), m_tournament(tournament)
{
	setTitle(i18n("Query tournament %1").arg(tournament));
	setExplanation(i18n("This is the ranking of the tournament"));
	setupForm();
	setupButtons(FormBase::AcceptButton, FormBase::CancelButton);
}


FormQueryTournament::~FormQueryTournament()
{
}


void FormQueryTournament::setupForm()
{
	m_resultTable = new KLTable(0,5, this);
	m_resultTable->setColumnLabels(QStringList() << i18n("Participant") << i18n("Win") << i18n("Draw") << i18n("Lost") << i18n("Total"));
 	fillTable();
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
	
	std::cout << resultSet.toString() << std::endl;
	
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
}

void FormQueryTournament::clean()
{
}

#include "formquerytournament.moc"
