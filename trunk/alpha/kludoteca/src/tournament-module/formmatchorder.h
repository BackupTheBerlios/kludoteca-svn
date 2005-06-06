/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                              	   *
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
#ifndef FORMMATCHORDER_H
#define FORMMATCHORDER_H

#include "formbase.h"
#include "kltable.h"
#include "matchgenerator.h"

/**
 * Aqui tenemos las partidas de una ronda, con sus respectivos puntajes
 * @author David Cuadrado
*/
class FormMatchOrder : public FormBase
{
	Q_OBJECT
	public:
		FormMatchOrder(const QString &tournament, int nround, FormBase::Type t, QWidget *parent = 0);
		~FormMatchOrder();

		void setupForm();

		void accept();
		void cancel();
		void clean();
		void updateRanks(const QStringList &clients);
		
		QStringList getMatchResult(int number);
		
	private slots:
		void fillTable();
		
	private:
		QStringList getMatchClientInfo(const QStringList &sqlresults, int newpos);
		
	private:
		QString m_tournament;
		const int m_nround;
		KLTable *m_table;
		QStringList m_restParticipant;
		QStringList m_clientList;
};

#endif
