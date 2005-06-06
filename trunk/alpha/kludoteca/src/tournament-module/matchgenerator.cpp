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

#include "matchgenerator.h"
#include <qvaluevector.h>
#include <iostream>
#include <klxmlreader.h>


MatchGenerator::MatchGenerator()
	: QObject()
{
	qDebug("[Initializing MatchGenerator]");
}

MatchGenerator::MatchGenerator(const QStringList &mci, const QString &tournament)
	: QObject(), m_mci(mci), m_tournament(tournament)
{
	qDebug("[Initializing MatchGenerator]");
	getTournamentInfo();
}


MatchGenerator::~MatchGenerator()
{
}

void MatchGenerator::setMatchClientInfo(const QStringList &mci, const QString &tournament)
{
	m_mci = mci;
	m_tournament = tournament;
}

QStringList MatchGenerator::generate(int nround, Type t)
{
	std::cout << "Generating pairs for round " << nround << std::endl;
	
	if( nround == 0 )
	{
		t = Random;
	}
	
	switch(t)
	{
		case Random:
		{
			std::cout << "RANDOM" << std::endl;
			return m_mci;
		}
		break;
		case Ascending:
		{
			// Ordenamos por puesto y enfrentamos en ese orden
			// TODO: Verificar que los jugadores no hayan jugado en este mismo orden!!
			
			verifyPairs(nround);
		}
		break;
	}
	return m_mci;
}

void MatchGenerator::verifyPairs(int nround)
{
	std::cout << "Verifing pairs" << " vect: " << m_mci.count() << std::endl;
	QValueList<int> imps;
	for(uint i = 0; i < m_mci.count(); i+=2 )
	{
		std::cout << "FOR" << std::endl;
		if( ! findOrder(i, i+1, nround) )
		{
			imps << i << i+1;
		}
	}
	
	for(uint i = 0; i < imps.count(); i++)
	{
		std::cout << "*******************************************" << std::endl;
		std::cout << "NO PUEDO ENCONTRAR ORDEN: " << m_mci[imps[i]] << std::endl;
		std::cout << "*******************************************" << std::endl;
	}
}

bool MatchGenerator::findOrder(int first, int sec, int nround)
{
	//SELECT count(number) from ldt_match where opponent1='002' and opponent2='004';
	std::cout << "INIT " << first << " " << sec << std::endl;
	
	QString opp1 = m_mci[first];
	QString opp2 = m_mci[sec];
	
	std::cout << "Finding order for " << m_mci[first] << " and " << m_mci[sec] << std::endl;
	
	KLSelect sqlquery(QStringList() << "count(opponent1)", QString("ldt_match"));
	
	sqlquery.setWhere("codtournament="+SQLSTR(m_tournament));

	sqlquery.setCondition(QString("and opponent1='%1' and opponent2='%2'").arg(opp1).arg(opp2));

	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	KLSqlResults results = xmlreader.results();
	
	std::cout << "HERE" << std::endl;
	std::cout << "Count: " << results["countopponent1"] << std::endl;
	
	if ( results["countopponent1"].toInt() < m_tournamentInfo["roundsforpair"].toInt() && results["countopponent1"].toInt() / nround <= m_tournamentInfo["rounds"].toInt() )
	{
		std::cout << "*******************************************" << std::endl;
		std::cout << "Find order: " << opp1 << " " << opp2 << std::endl;
		std::cout << "*******************************************" << std::endl;
		return true;
	}
	else
	{
		if ( findOrder(sec, first, nround ) )
		{
			std::cout << "swapping" << std::endl;
			
			swap(m_mci, first, sec);
			
			std::cout << "Next" << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void MatchGenerator::getTournamentInfo()
{
	KLSelect sqlquery(QStringList() << "rounds" << "roundsforpair", QString("ldt_tournament"));
	
	sqlquery.setWhere("name="+SQLSTR(m_tournament));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	m_tournamentInfo = xmlreader.results();
}

/**
Esta funcion intercambia de poscicion dos procesos en una lista.
 */
void MatchGenerator::swap(QStringList &list, int i1, int i2)
{
	QString s1 = list[i1];
	QString s2 = list[i2];
	list[i1] = s2;
	list[i2] = s1;
}


#include "matchgenerator.moc"
