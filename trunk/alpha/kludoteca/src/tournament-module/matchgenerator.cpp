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
#include <kldatabase.h>

MatchGenerator::MatchGenerator()
	: QObject(), heapsize(0)
{
	
}

MatchGenerator::MatchGenerator(const MatchClientInfo &mci, const QString &tournament)
	: QObject(), m_mci(mci), heapsize(0), m_tournament(tournament)
{
	
}


MatchGenerator::~MatchGenerator()
{
}

void MatchGenerator::setMatchClientInfo(const MatchClientInfo &mci, const QString &tournament)
{
	m_mci = mci;
	m_tournament = tournament;
}

StringVector MatchGenerator::generate(Type t)
{
	StringVector res(m_mci.count());
	
	switch(t)
	{
		case Random:
		{
			return qstringlist2stringvector(m_mci.keys());
		}
		break;
		case Ascending:
		{
			// Ordenamos por puesto y enfrentamos en ese orden
			// TODO: Verificar que los jugadores no hayan jugado en este mismo orden!!
			QValueList<int> values = m_mci.values();
			
			qHeapSort(values);
			MatchClientInfo::const_iterator it;
			
			for(uint i = 0; i < values.count(); i++)
			{
				QString key = m_mci.keys()[i];
				int index = values.findIndex(m_mci[key]);
				res[index] = key;
				values[index] = -1;
			}
			
			verifyPairs(res);
		}
		break;
	}
	return res;
}

void MatchGenerator::verifyPairs(StringVector &sv)
{
	int r4p = this->rounds4pair();
	QValueList<int> imps;
	for(uint i = 0; i < sv.count(); i+=2)
	{
		if( whatTimes(sv[i], sv[i+1]) > r4p)
		{
			if ( whatTimes(sv[i+1], sv[i]) > r4p )
			{
				imps << i << i+1;
			}
			else
			{
				// swap
				QString sv1 = sv[i];
				QString sv2 = sv[i+1];
				sv[i] = sv2;
				sv[i+1] = sv1;
			}
		}
	}
	
	for(uint i = 0; i < imps.count(); i++)
	{
		std::cout << "No puedo elegir: " << sv[imps[i]] << std::endl;
	}
}

int MatchGenerator::whatTimes(const QString &opp1, const QString &opp2)
{
	//SELECT count(number) from ldt_match where opponent1='002' and opponent2='004';
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
	
	return results["countopponent1"].toInt();
}

StringVector MatchGenerator::qstringlist2stringvector(const QStringList &list)
{
	StringVector vec(list.count());
	for(uint i = 0; i < list.count(); i++)
	{
		vec[i] = list[i];
	}
	return vec;
}

int MatchGenerator::rounds4pair()
{
	KLSelect sqlquery(QStringList() << "roundsforpair", QString("ldt_tournament"));
	sqlquery.setWhere("name="+SQLSTR(m_tournament));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	KLSqlResults results = xmlreader.results();
	
	return results["roundsforpair"].toInt();
}

// HEAPSORT

/**
Funcion auxiliar del procedimiento heapsort, esta funcion nos retorna un padre
 */
int MatchGenerator::parent(int i)
{
	return (int) floor((i-1)/2);
}

/**
Funcion auxiliar del procedimiento heapsort, esta funcion nos retorna la poscicion a la izquierda del nodo i en el arbol del heap.
 */
int MatchGenerator::rigth(int i)
{
	return 2*i+2;
}

/**
Funcion auxiliar del procedimiento heapsort, esta funcion nos retorna la poscicion a la derecha del nodo i en el arbol del heap.
 */
int MatchGenerator::left(int i)
{
	return 2*i+1;
}

/**
Funcion auxiliar del procedimiento heapsort, esta funcion mantiene la propiedad de heap para un nodo i.
 */
void MatchGenerator::maxHeapify(QStringList &list, int i)
{
	int l = left(i);
	int r = rigth(i);

	int max = 0;

	if ( l <= heapsize && m_mci[list[l]] > m_mci[list[i]] )
		max = l;
	else
		max = i;

	if (r <= heapsize && m_mci[list[r]] > m_mci[list[max]])
		max = r;
	
	if (max != i)
	{
		swap(list, max, i);
		maxHeapify(list, max);
	}
}

/**
Funcion auxiliar del procedimiento heapsort, esta funcion construye el heap.
 */
void MatchGenerator::buildMaxHeap(QStringList &list)
{
	heapsize = list.count()-1;
	for(int i = (int) floor((list.count()-1)/2); i >= 0; i--)
	{
		maxHeapify(list, i);
	}
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

/**
Funcion muy conocida de ordenamiento, su complejidad es O(nlgn), en esta implementacion organiza una lista de procesos depediendo del campo, por ejemplo se puede ordenar por campo 0 (tiempo inicial).
 */
void MatchGenerator::heapsort(QStringList &list)
{
	buildMaxHeap(list);
	for(int i = list.count()-1; i >= 1; i--)
	{
		swap(list, i, 0);
		heapsize--;
		maxHeapify(list, 0);
	}
}


#include "matchgenerator.moc"
