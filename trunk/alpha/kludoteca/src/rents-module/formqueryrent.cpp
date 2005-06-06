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
#include "formqueryrent.h"
#include <klocale.h>
#include "klxmlreader.h"


FormQueryRent::FormQueryRent(const QString &serial, const QString &date, const QString &hour, QWidget *parent,const char* name): FormBase(FormBase::Query,parent),m_serial(serial), m_date(date),m_hour(hour)
{
}


FormQueryRent::~FormQueryRent()
{
}

void FormQueryRent::setupForm()
{
	setupRentInfo();
	
	new QLabel("<div align=center><h1>Results Table</h1></div>", this);
	
	m_resultTable = new KLTable(0,5, this);
	m_resultTable->setColumnLabels(QStringList() << i18n("Game") << i18n("Elapsed Time") << i18n("Remain Time") << i18n("Cost"));
	fillTable();
}

void FormQueryRent::setupRentInfo()
{

}


