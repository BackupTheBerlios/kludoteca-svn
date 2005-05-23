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
#ifndef MATCHGENERATOR_H
#define MATCHGENERATOR_H

#include <qobject.h>
#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qvaluevector.h>

typedef QMap<QString, int> MatchClientInfo;
typedef QValueVector<QString> StringVector;
		
/**
 * Esta clase se encarga de hacer el pareo de torneos, se intentara tener varios metodos para hacer pareos
 * @author David Cuadrado
*/

class MatchGenerator : public QObject
{
	Q_OBJECT
	public:
		enum Type { Random = 0, Ascending }; // Podemos añadir mas metodos
		
		MatchGenerator();
		MatchGenerator(const MatchClientInfo &mci);
		~MatchGenerator();
		void setMatchClientInfo(const MatchClientInfo &mci);
		StringVector generate(Type t);
		StringVector qstringlist2stringvector(const QStringList &);
		
	protected:
		// <heapsort>
		inline int parent(int i);
		inline int left(int i);
		inline int rigth(int i);
		void maxHeapify(QStringList &list, int i);
		void buildMaxHeap(QStringList &list);
		void heapsort(QStringList &list);
		void swap(QStringList &list, int i1, int i2);
		// </heapsort>
		
	private:
		MatchClientInfo m_mci;
		int heapsize;
};

#endif
