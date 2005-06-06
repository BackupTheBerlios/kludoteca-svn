/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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
#ifndef FORMQUERYRENT_H
#define FORMQUERYRENT_H

#include "formbase.h"
#include "kltable.h"
//#include <klsqlresults.h>
#include "klresultsetinterpreter.h"
/**
@author Daniel Valencia.
*/
class FormQueryRent : public FormBase
{
	Q_OBJECT
	public:
		FormQueryRent(const QString &serial, const QString &date, const QString &hour, QWidget* parent, const char* name);
		~FormQueryRent();
		void setupForm();

		void accept();
		void clean();
		void fillTable();

		void print(QPainter *p, KPrinter &printer);

	private:
		void setupRentInfo();

	private:
		QString m_serial,m_date,m_hour;
		KLTable *m_resultTable;
		KLSqlResults m_rentInfo;

};

#endif
