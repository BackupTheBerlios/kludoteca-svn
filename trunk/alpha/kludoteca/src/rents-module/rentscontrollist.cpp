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
#include "formreportrents.h"
#include <qmessagebox.h>
#define DEBUG_RENTSCONTROLIST 1
using namespace std;

RentsControlList::RentsControlList(Button button1, 
				   Button button2, 
				   Button button3, 
				   Button button4,
				   QWidget* parent): LTListView(QStringList() << i18n("Game Serial") << i18n("Client ID") << i18n("Rent Date") << i18n("Rent Hour"), LTListView::NoButton, LTListView::NoButton, LTListView::NoButton, LTListView::NoButton, parent)
{
	setCaption(i18n("Rents"));
	
	m_listView->setTitle(i18n("Active Rents"));
	m_listView->setExplain(i18n("Please click in the \"Add\" button for create a new Rent"));
	(new QLabel(i18n("Chose a year,month and day for make a rents report"),this));
	QHBox *dateBox = new QHBox(this);
	dateBox->setMargin(10);
	(new QLabel(i18n("Year"),dateBox));
	m_comboY = new KComboBox(false,dateBox,"comboY");
	m_comboY->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 2005; i < 2051; i++)
		m_comboY->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Month"),dateBox));
	m_comboM = new KComboBox(false,dateBox,"comboM");
	m_comboM->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 13; i++)
		m_comboM->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Day"),dateBox));
	m_comboD = new KComboBox(false,dateBox,"comboD");
	m_comboD->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 32; i++)
		m_comboD->insertItem(QString::number(i,10));
	
	
	
	/*************************************/
	(new QLabel(i18n("Chose a Week for make a rents report"),this));
	QHBox *dateBoxr2 = new QHBox(this);
	(new QLabel(i18n("Year"),dateBoxr2));
	m_comboYB = new KComboBox(false,dateBoxr2,"comboY");
	m_comboYB->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 2005; i < 2051; i++)
		m_comboYB->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Month"),dateBoxr2));
	m_comboMB = new KComboBox(false,dateBoxr2,"comboM");
	m_comboMB->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 13; i++)
		m_comboMB->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Day"),dateBoxr2));
	m_comboDB = new KComboBox(false,dateBoxr2,"comboDb");
	m_comboDB->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 32; i++)
		m_comboDB->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Day"),dateBoxr2));
	m_comboDE = new KComboBox(false,dateBoxr2,"comboDe");
	m_comboDE->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 32; i++)	
		m_comboDE->insertItem(QString::number(i,10));
	(new QLabel(i18n("Chose a Game"),this));
	m_comboGames = new KComboBox(false,this,"combogame");
	m_comboGames->setInsertionPolicy(KComboBox::NoInsertion);
	
	KLSelect query(QStringList() << "gameserialreference",QStringList() << "ldt_rents" );
	//
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	int count = 0;
	for(uint i = 1; i < results.count() ; i++)
	{
		m_comboGames->insertItem(results[count++]);
	}
	this->fillList();
	this->makeButtons(LTListView::ButtonAdd,LTListView::ButtonQuery,
			LTListView::NoButton,LTListView::NoButton);
}


RentsControlList::~RentsControlList()
{
}
void RentsControlList::addButtonClicked()
{
	KMdiChildView *view = new KMdiChildView(i18n("Report test"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(50);
	/*
	*/
	
	QString year = m_comboYB->currentText();
	QString month = m_comboMB->currentText();
	QString daybegin = m_comboDB->currentText();
	QString dayend = m_comboDE->currentText();
	QString serial = m_comboGames->currentText();
	
	
	KLReportWidget *reporteRenta = new KLReportWidget(scroll->viewport());

	ElementVector m_elements;
	m_elements.resize(12);
	/*select date ,gameserialreference,count(gameserialreference) as veces from ldt_rents where date between '2005-06-06' and '2005-06-09' and gameserialreference='001' group by date,gameserialreference;
	*/
	KLDM->execRawQuery("drop view R2");
	KLDM->execRawQuery("CREATE VIEW R2 AS (select date ,gameserialreference,count(gameserialreference) as veces from ldt_rents where date between "+SQLSTR(year+"-"+month+"-"+daybegin)+" and "+SQLSTR(year+"-"+month+"-"+dayend)+" and gameserialreference="+SQLSTR(serial)+" group by date,gameserialreference)");
	
	KLSelect query(QStringList() <<"veces" << "date",
			QStringList() << "R2");
	//query.setWhere("date='2005-06-7'group by gameserialreference having count(gameserialreference) >= 1");
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	KLXmlReport xmlreport("Reporte estadistico de dia de la semana con mas afluencia para determinado juego", "Cetisoft", "00-6", KLXmlReport::PIE );
	bool ok = 0;
	int count = 0;
	for ( int i = 0; i < results.count() / 2; ++i )
	{
		double x = (double(i) / 100) * 100;
		int y = (int(x * 256) % 105) + 151;
		int z = ((( ((results[count++]).toInt(&ok,10)) * 17) % 105) + 151)+((results[count]).toInt(&ok,10));
		
		cout << "veces: " << ((results[count]).toInt(&ok,10)) << endl;
		m_elements[i] = KLReportElement( z, QColor( int(x), y, z, QColor::Hsv ) );
		xmlreport.createReportElement(((results[count]).toInt(&ok,10)), results[count++], QColor( int(x), y, z, QColor::Hsv ));
		cout << "veces: " << ((results[count]).toInt(&ok,10)) << endl;
	}
	
	reporteRenta->getKLCanvasView()->setElements(m_elements);
	reporteRenta->setXmlReport(xmlreport);
// 	FormReportRents *reporte = new FormReportRents(FormBase::Query,this);
	
	scroll->addChild(reporteRenta);
		
	emit sendWidget(view);

}
void RentsControlList::delButtonClicked(){}
void RentsControlList::modifyButtonClicked(){}
void RentsControlList::getClickedItem(QListViewItem *item){}

void RentsControlList::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
	QString year = m_comboY->currentText();
	QString month = m_comboM->currentText();
	QString day = m_comboD->currentText();
	cout << "fecha a check: " << year+month+day << endl;
	KMdiChildView *view = new KMdiChildView(i18n("Report test"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(50);
	/*
	*/
	
	KLReportWidget *reporteRenta = new KLReportWidget(scroll->viewport());

	ElementVector m_elements;
	m_elements.resize(12);
	/** JUEGO MAS ALKILADO EN UN DIA
	*
	* SELECT max(gameserialreference) as game,count(gameserialreference) as veces from ldt_rents where date='2005-05-25' group by gameserialreference having count(gameserialreference) > 1;
	select count(gameserialreference) as veces from ldt_rents where date in between '2005-06-06' and '2005-06-09';	
	*/
	
	
	/*select date ,gameserialreference,count(gameserialreference) as veces from ldt_rents where date between '2005-06-06' and '2005-06-09' and gameserialreference='001' group by date,gameserialreference;
	*/
	KLDM->execRawQuery("drop view R1");
	KLDM->execRawQuery("CREATE VIEW R1 AS (SELECT max(gameserialreference) as game,count(gameserialreference) as veces from ldt_rents where date="+SQLSTR(year+"-"+month+"-"+day)+" group by gameserialreference having count(gameserialreference) >= 1)");
	
	KLSelect query(QStringList() <<"veces" << "game",
			QStringList() << "R1");
	//query.setWhere("date='2005-06-7'group by gameserialreference having count(gameserialreference) >= 1");
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	KLXmlReport xmlreport("Reporte de Juegos mas alquilados por dia", "Cetisoft", "00-6", KLXmlReport::PIE );
	bool ok = 0;
	int count = 0;
	for ( int i = 0; i < results.count() / 2; ++i )
	{
		double x = (double(i) / 100) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((( ((results[count++]).toInt(&ok,10)) * 17) % 105) + 151)+((results[count]).toInt(&ok,10));
		
		cout << "veces: " << ((results[count]).toInt(&ok,10)) << endl;
		m_elements[i] = KLReportElement( z, QColor( int(x), y, z, QColor::Hsv ) );
		xmlreport.createReportElement(((results[count]).toInt(&ok,10)), results[count++], QColor( int(x), y, z, QColor::Hsv ));
		cout << "veces: " << ((results[count]).toInt(&ok,10)) << endl;
	}
	
	reporteRenta->getKLCanvasView()->setElements(m_elements);
	reporteRenta->setXmlReport(xmlreport);
// 	FormReportRents *reporte = new FormReportRents(FormBase::Query,this);
	
	scroll->addChild(reporteRenta);
		
	emit sendWidget(view);

	
}

void RentsControlList::fillList()
{
#if DEBUG_RENTSCONTROLIST
qDebug("RentsCONTROLLISTt: filling List");
#endif
	KLSelect sqlquery(QStringList() << "gameserialreference"
					<< "clientdocident"
					<< "date"
					<< "renthour",
			QStringList() << "ldt_rents");
			
	sqlquery.setWhere("active = 't'");
	 
	
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	 
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void RentsControlList::addRentsTimer(RentsTimer *rt)
{
	m_listRentsTimer.append(rt);
	cout << "RT:size: " << m_listRentsTimer.count() << endl;
	
	QStringList rtId = rt->getId();
	/*KLSelect query(QStringList() << "units",QStringList() << "ldt_rents");
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
	connect( rt ,SIGNAL( timeout() ), this , SLOT( checkRentsTimer() ) );
	addItem(rtId);
			
	/*
	cout << "serial: "<< (tr->getId())[0] 
			<<"date: "<< (tr->getId())[1] 
			<< "hour: " << (tr->getId())[2] << endl;*/
}

void RentsControlList::checkRentsTimer()
{
	//cout << "[[[[  TIMER CORRIENDO :)  ]]]]" << endl;
	RentsTimer *rt;
	rt = m_listRentsTimer.last();
	QStringList id = rt->getId();
	
	KLSelect query(QStringList() << "clientdocident"<< "gameserialreference"<<"renthour"
				<<"units"<<"addunits"<<"date"<< "totalcost"<< "active",
			QStringList() << "ldt_rents");
	query.setWhere("gameserialreference="+SQLSTR(id[0])+" and date="+SQLSTR(id[1])+" and renthour="+SQLSTR(id[2]));
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	QMessageBox::information( this, i18n("Checking th Rents"),"client identification: \t"+results["clientdocident"]+"\n ." 
	"Game Serial: \t"+results["gameserialreference"]+"\n."
	"Rent Hour: \t"+results["renthour"]+"\n"
	"Units: \t"+results["units"]+" \n"
	"Aditional Units: \t"+results["addunits"]+"\n"
	"Rent Date: \t"+results["date"]+"\n"
	"Total Cost: \t"+results["totalcost"]+"\n"
	"Active: \t"+results["active"]+"\n");
	
}


void RentsControlList::addItem(const QStringList &l)
{
	m_listView->clear();		
	//addItem(pkey);
	this->fillList();
}

void RentsControlList::makeButtons(Button b1,Button b2,Button b3,Button b4)
{
	m_buttons = new QHButtonGroup(this);
	switch ( b1 )
	{
		case ButtonAdd:
		{
			m_buttonAdd = new KPushButton(i18n("Rented for Week"), m_buttons);
			m_buttons->insert( m_buttonAdd, b1);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, b1);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Most Rented"), m_buttons);
			m_buttons->insert( m_buttonModify, b1);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Most Rented"), m_buttons);
			m_buttons->insert( m_buttonQuery, b1);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch (b2)
	{
		case ButtonAdd:
		{
			m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, b2);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, b2);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, b2);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Most Rented for Day"), m_buttons);
			m_buttons->insert( m_buttonQuery, b2);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch(b3)
	{
		case ButtonAdd:
		{
			KPushButton *m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, b3);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, b3);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, b3);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, b3);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch(b4)
	{
		case ButtonAdd:
		{
			m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, b4);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, b4);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, b4);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, b4);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	if ( m_buttonAdd )
		connect(m_buttonAdd, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	if (m_buttonDel )
		connect(m_buttonDel, SIGNAL(clicked()), this, SLOT(delButtonClicked()));
	if (m_buttonModify)
		connect(m_buttonModify, SIGNAL(clicked()), this, SLOT(modifyButtonClicked()));
	if(m_buttonQuery)
		connect(m_buttonQuery, SIGNAL(clicked()), this, SLOT(queryButtonClicked()));	
}


#include "rentscontrollist.moc"

