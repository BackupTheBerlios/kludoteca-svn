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

#include "kldatabase.h"
#include "klxmlreader.h"
		
/**
 * Esta clase se encarga de hacer el pareo de torneos, se intentara tener varios metodos para hacer pareos
 * @author David Cuadrado
*/

class MatchGenerator : public QObject
{
	Q_OBJECT
	public:
		enum Type { Any = -1, Random = 0, Ascending }; // Podemos añadir mas metodos de pareo
		
		MatchGenerator();
		MatchGenerator(const QStringList &mci, const QString &tournament);
		~MatchGenerator();
		void setMatchClientInfo(const QStringList &list, const QString &tournament);
		QStringList generate(int nround, Type t);

		void verifyPairs(int nround);
		
	private:
		/**
		 * Obtiene la informacion del torneo
		 * @return 
		 */
		void getTournamentInfo();
		
		
		/**
		 * Encuentra un orden para enfrentar las parejas, retorna true si pudo encontrarlo y false sino
		 * @param opp1 
		 * @param opp2 
		 * @return 
		 */
		bool findOrder(int first, int sec , int nround);
		
		void swap(QStringList &list, int, int);
		
	private:
		QStringList m_mci;
		QString m_tournament;
		KLSqlResults m_tournamentInfo;
};

#endif
