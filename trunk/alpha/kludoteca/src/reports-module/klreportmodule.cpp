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

#include "klreportmodule.h"
#include <kseparator.h>
#include <qlabel.h>
#include <klocale.h>
#include <kdebug.h>
#include <qlayout.h>
#include <qhbox.h>
#include <qxml.h>

#include "klreportwidget.h"
#include "klquery.h"
#include "kldatabase.h"

KLReportModule::KLReportModule(QWidget *parent, const char *name) : QVBox(parent, name)
{
	layout()->setSpacing(5);
	layout()->setMargin(5);
	new QLabel(i18n("Please choose the initial date"), this);
	m_initialDate = new KDatePicker(this);
	connect(m_initialDate, SIGNAL(dateChanged(QDate )), this, SLOT(setEndDate(QDate)));
	
	new KSeparator(this);
	new QLabel(i18n("Please choose the end date"), this);
	m_endDate = new KDateWidget(this);
	connect(m_endDate, SIGNAL(changed(QDate )), this, SLOT(setInitialDate(QDate )));
	m_endDate->setDate(m_initialDate->date());
	
	new KSeparator(this);
	
	new QLabel(i18n("Game"), this);
	m_gameSerial = new KComboBox(this);
	setupGamesSerial();
	
	QHBox *buttonPanel = new QHBox(this);
	m_dailyReportButton = new QPushButton(i18n("Most rented"), buttonPanel);
	
	connect( m_dailyReportButton, SIGNAL(clicked()), this, SLOT(makeDailyReport()));
	
	m_rangeReportButton = new QPushButton(i18n("Most rented in a range"), buttonPanel);
	connect( m_rangeReportButton, SIGNAL(clicked()), this, SLOT(makeRangeReport()));
	
}


KLReportModule::~KLReportModule()
{

}

void KLReportModule::setupGamesSerial()
{
	m_gameSerial->clear();
	KLSelect sqlquery(QStringList() << "serialreference", QString("ldt_games"));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	m_gameSerial->insertStringList(xmlreader.getResultsList());
}

void KLReportModule::makeRangeReport()
{
	kdDebug() << k_funcinfo << endl;
	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(50);
	
	KLReportWidget *rentReport = new KLReportWidget(scroll->viewport());

	ElementVector m_elements;
	m_elements.resize(12);
	/*select date ,gameserialreference,count(gameserialreference) as times from ldt_rents where date between '2005-06-06' and '2005-06-09' and gameserialreference='001' group by date,gameserialreference;
	*/
	
	QString serial = m_gameSerial->currentText() ;
	
	KLDM->execRawQuery("SET DateStyle TO ISO ");
	
	KLDM->execRawQuery("drop view R2");
// 	KLDM->execRawQuery("CREATE VIEW R2 AS (select date ,gameserialreference,count(gameserialreference) as times from ldt_rents where date between "+SQLSTR( m_initialDate->date().toString(Qt::ISODate) )+" and "+SQLSTR(m_endDate->date().toString(Qt::ISODate) )+" and gameserialreference="+SQLSTR(serial)+" group by date,gameserialreference)");
	
	KLDM->execRawQuery("CREATE VIEW R2 AS (select gameserialreference,count(gameserialreference) as times from ldt_rents where date between "+SQLSTR( m_initialDate->date().toString(Qt::ISODate) )+" and "+SQLSTR(m_endDate->date().toString(Qt::ISODate) )+" group by gameserialreference)");
	
	kdDebug() << KLDM->getLastError() << endl;
	
	KLSelect query(QStringList() <<"times" << "gameserialreference",
		       QStringList() << "R2");
	//query.setWhere("date='2005-06-7'group by gameserialreference having count(gameserialreference) >= 1");
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	QXmlInputSource m_xmlsource;
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
		int z = ((( ((results[count]).toInt(&ok,10)) * 17) % 105) + 151)+((results[count]).toInt(&ok,10));

		m_elements[i] = KLReportElement( z, QColor( int(x), y, z, QColor::Hsv ) );
		xmlreport.createReportElement(((results[count]).toInt(&ok,10)), results[count+1], QColor( int(x), y, z, QColor::Hsv ));
		count += 2;
	}
	
	rentReport->getKLCanvasView()->setElements(m_elements);
	rentReport->setXmlReport(xmlreport);
	
// 	FormReportRents *reporte = new FormReportRents(FormBase::Query,this);
	
	scroll->addChild(rentReport);
		
	emit sendWidget(scroll,i18n("Report"));
}

void KLReportModule::makeDailyReport()
{
	QScrollView *scroll = new QScrollView(this);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(50);
	
	KLReportWidget *rentReport = new KLReportWidget(scroll->viewport());

	/** JUEGO MAS ALKILADO EN UN DIA
	 *
	 * SELECT max(gameserialreference) as game,count(gameserialreference) as times from ldt_rents where date='2005-05-25' group by gameserialreference having count(gameserialreference) > 1;
	select count(gameserialreference) as times from ldt_rents where date in between '2005-06-06' and '2005-06-09';	
	 */
	
	
	/*select date ,gameserialreference,count(gameserialreference) as times from ldt_rents where date between '2005-06-06' and '2005-06-09' and gameserialreference='001' group by date,gameserialreference;
	*/
	
	KLDM->execRawQuery("SET DateStyle TO ISO ");
	KLDM->execRawQuery("drop view R1");
	KLDM->execRawQuery("CREATE VIEW R1 AS (SELECT max(gameserialreference) as game,count(gameserialreference) as times from ldt_rents where date="+SQLSTR(m_initialDate->date().toString(Qt::ISODate) )+" group by gameserialreference having count(gameserialreference) >= 1)");
	
	KLSelect query(QStringList() <<"times" << "game",
		       QStringList() << "R1");
	//query.setWhere("date='2005-06-7'group by gameserialreference having count(gameserialreference) >= 1");
	
	KLResultSet resultSet = KLDM->execQuery(&query);
	QXmlInputSource m_xmlsource;
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	KLXmlReport xmlreport("Reporte de Juegos mas alquilados por dia", "Cetisoft", "006", KLXmlReport::PIE );
	bool ok = false;
	int count = 0;
	
	ElementVector m_elements;
	int nelem = results.count() / 2;
	m_elements.resize(nelem);
	for ( int i = 0; i < nelem; ++i )
	{
		double x = (double(i) / 100) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((( ((results[count]).toInt(&ok,10)) * 17) % 105) + 151)+((results[count]).toInt(&ok,10));
		
		m_elements[i] = KLReportElement( z, QColor( int(x), y, z, QColor::Hsv ) );
		xmlreport.createReportElement(((results[count]).toInt(&ok,10)), results[count+1], QColor( int(x), y, z, QColor::Hsv ));
		
		count += 2;
	}
	
	rentReport->getKLCanvasView()->setElements(m_elements);
	rentReport->setXmlReport(xmlreport);
// 	FormReportRents *reporte = new FormReportRents(FormBase::Query,this);
	
	scroll->addChild(rentReport);
		
	emit sendWidget(scroll,i18n("Report"));
}

void KLReportModule::setInitialDate(QDate date)
{
	if ( m_initialDate->date() > date )
	{
		m_initialDate->setDate(date);
	}
}

void KLReportModule::setEndDate(QDate date)
{
	if ( m_endDate->date() < date )
	{
		m_endDate->setDate(date);
	}
}

#include "klreportmodule.moc"
