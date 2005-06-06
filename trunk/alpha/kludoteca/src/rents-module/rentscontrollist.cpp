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
#include "rentscontrollist.h"
#include <klocale.h>
#include <iostream>

using namespace std;

RentsControlList::RentsControlList(QWidget* parent, const char* name): LTListView(QStringList() << i18n("Tournament") << i18n("Client") << i18n("Rank"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent, name)
{
	
	
}


RentsControlList::~RentsControlList()
{
}
void RentsControlList::addButtonClicked(){}
void RentsControlList::delButtonClicked(){}
void RentsControlList::modifyButtonClicked(){}
void RentsControlList::getClickedItem(QListViewItem *item){}

void RentsControlList::queryButtonClicked()
{
}

void RentsControlList::fillList()
{
}

void RentsControlList::addRentsTimer(RentsTimer *tr)
{
	m_listRentsTimer.append(tr);
	cout << "RT:size: " << m_listRentsTimer.count() << endl;
	/*
	QStringList rtId = rt->getId();
	KLSelect query(QStringList() << "units",QStringList() << "ldt_rents");
	query.setWhere("gameserialreference="+SQLSTR(rtId[0])+" and");
	query.setCondition(" date="+SQLSTR(rtId[1])+" and renthour"+SQLSTR(rtId[2]));
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
		
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	m_timerResults = m_xmlreader.results();
	bool ok = 0;
	int msec = m_timerResults["units"]
	rtemp->start(30000,FALSE);*/
	connect( tr ,SIGNAL( timeout() ), this , SLOT( checkRentsTimer() ) );
	
	/*
	cout << "serial: "<< (tr->getId())[0] 
			<<"date: "<< (tr->getId())[1] 
			<< "hour: " << (tr->getId())[2] << endl;*/
}

void RentsControlList::checkRentsTimer()
{
	cout << "[[[[  TIMER CORRIENDO :)  ]]]]" << endl;
}



#include "rentscontrollist.moc"

