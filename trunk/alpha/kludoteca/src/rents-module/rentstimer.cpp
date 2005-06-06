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
#include "rentstimer.h"

RentsTimer::RentsTimer(const QStringList &id,int units,TimeUnit tu): QTimer(),m_id(id)
{
	switch (tu)
	{
		case RentsTimer::Days:
		{
			int msec = units*24*60*60*1000;
			this->start(msec,FALSE);
		}
		break;
		case RentsTimer::Hour:
		{
			int msec = units*60*60*1000;
			this->start(msec,FALSE);
		}
		break;
		case RentsTimer::Min:
		{
			int msec = units*60*1000;
			this->start(msec,FALSE);
		}	
			
	}
	
	
}


RentsTimer::~RentsTimer()
{
}

QStringList RentsTimer::getId()
{
	return m_id;
}

/*
*	KLSelect query(QStringList() <<"clientdocident"
			<< "gameserialreference"
			<< "totalcost"
			<< "date"
			<< "renthour"
			<< "units"
			<< "addunits"
			<< "active"
			,QStringList() << "ldt_rents");
	query.setWhere("gamerserialreference="+SQLSTR(id[0])+" and" );
	query.setCondition("date="+SQLSTR(id[1])+" and renthour="+SQLSTR(id[2])+"and active" );
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
		
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
{
		std::cerr << "No se puede analizar" << std::endl;
}
	
	m_timerResults = m_xmlreader.results();
*
*/