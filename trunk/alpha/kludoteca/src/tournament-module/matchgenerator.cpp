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

MatchGenerator::MatchGenerator()
	: QObject(), heapsize(0)
{
	
}

MatchGenerator::MatchGenerator(const MatchClientInfo &mci)
	: QObject(), m_mci(mci), heapsize(0)
{
	
}


MatchGenerator::~MatchGenerator()
{
}

void MatchGenerator::setMatchClientInfo(const MatchClientInfo &mci)
{
	m_mci = mci;
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
		}
		break;
	}
	return res;
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
