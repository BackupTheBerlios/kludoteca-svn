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
#include "klcalc.h"
#include "qdatetime.h"

using namespace std;

FormQueryRent::FormQueryRent(const QString &serial, const QString &date, const QString &hour, QWidget *parent,const char *name): FormBase(FormBase::Query,parent,name),m_serial(serial), m_date(date),m_hour(hour)
{
	setTitle(i18n("Query Rent"));
	setExplanation(i18n("This is the basic information about Rents"));
	setupForm();
	setupButtons(FormBase::AcceptButton, FormBase::NoButton);
}


FormQueryRent::~FormQueryRent()
{
}

void FormQueryRent::setupForm()
{
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());
	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2,
					m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(5);
	m_container->setMidLineWidth(20);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10); 
	m_layout = new QGridLayout(m_container, 4, 1, 10, 10);
	m_layout->setAlignment(Qt::AlignCenter );
	setupRentInfo();
	
	;
	m_layout->addWidget(m_box,2,0);
	m_resultTable = new KLTable(0,4, m_container);
	m_resultTable->setColumnLabels(QStringList() << i18n("Game") << i18n("Elapsed Time") << i18n("Remain Time") << i18n("Cost"));
	m_layout->addWidget((new QLabel("<div align=center><h1>Results Table</h1></div>", m_container)),0,0);
	m_layout->addWidget(m_resultTable,1,0);
	
	fillTable();
}

void FormQueryRent::setupRentInfo()
{
	m_box = new QGroupBox(m_container);
	m_box->setMargin(10);
	
	/**
	*  create view V1 as (SELECT * from ldt_rents join ldt_games on gameserialreference=serialreference);
	*
	* SELECT * from ldt_clients join V1 on docident=clientdocident where gameserialreference='002'and date='2005-05-25' and renthour='13:00:00';
	*
	*/
	KLDM->execRawQuery("create view V1 as (SELECT * from ldt_rents join ldt_games on gameserialreference=serialreference)");
	
	KLSelect query(QStringList() << "gameserialreference" 
					<< "gamename"
					<< "clientdocident"
					<< "costforunit"
					<< "costforunitadd"
					<< "totalcost"
					<< "date"
					<< "renthour"
					<< "units"
					<< "addunits"
				,QStringList() << "ldt_clients");
	query.setWhere("gameserialreference="+SQLSTR(m_serial)+
			" and date="+SQLSTR(m_date)+" and renthour="+SQLSTR(m_hour));
	//sqlquery.setJoin(QString("ldt_games"), KLSelect::On, QStringList() << "gameserialreference" << "serialreference");
	query.setJoin(QString("V1"), KLSelect::On,QStringList() << "docident" << "clientdocident");
	KLResultSet resultSet = KLDM->execQuery(&query);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	m_rentInfo = xmlreader.results();
	QGridLayout *layout = new QGridLayout(m_box, 10, 2, 5,2);
	layout->addWidget(new QLabel(i18n("Game Serial:"),m_box), 0,0);
	layout->addWidget((new QLabel(m_rentInfo["gameserialreference"],m_box)), 0,1);
	
	layout->addWidget(new QLabel(i18n("Game Name:"),m_box), 1,0);
	layout->addWidget((new QLabel(m_rentInfo["gamename"],m_box)), 1,1);
	
	layout->addWidget(new QLabel(i18n("Client's Identification:"),m_box), 2,0);
	layout->addWidget((new QLabel(m_rentInfo["clientdocident"],m_box)), 2,1);
	
	layout->addWidget(new QLabel(i18n("Client's Name:"),m_box), 3,0);
	layout->addWidget((new QLabel(m_rentInfo["clientdocident"],m_box)), 3,1);
	
	layout->addWidget(new QLabel(i18n("Cost for Time Unit:"),m_box), 4,0);
	layout->addWidget((new QLabel(m_rentInfo["costforunit"],m_box)), 4,1);
	
	layout->addWidget(new QLabel(i18n("Cost for Aditional Time Unit:"),m_box), 5,0);
	layout->addWidget((new QLabel(m_rentInfo["costforunitadd"],m_box)), 5,1);
	
	layout->addWidget(new QLabel(i18n("Rent Date:"),m_box), 6,0);
	layout->addWidget((new QLabel(m_rentInfo["date"],m_box)), 6,1);
	
	layout->addWidget(new QLabel(i18n("Rent Hour:"),m_box), 7,0);
	layout->addWidget((new QLabel(m_rentInfo["renthour"],m_box)), 7,1);
	
	layout->addWidget(new QLabel(i18n("Time Units:"),m_box), 8,0);
	layout->addWidget((new QLabel(m_rentInfo["units"],m_box)), 8,1);
	
	layout->addWidget(new QLabel(i18n("Aditional Time Units:"),m_box), 9,0);
	layout->addWidget((new QLabel(m_rentInfo["addunits"],m_box)), 9,1);
	
	//FIXME: modificar BD para ke ldt_rents tenga un campo de fecha esperada de entrega o hacer ke alguna clase maneje esto
	
	
	
	
	
}

void FormQueryRent::accept()
{
}

void FormQueryRent::cancel()
{
	emit cancelled();
}

void FormQueryRent::clean()
{
	
}
void FormQueryRent::print(QPainter *p, KPrinter &printer)
{
}

void FormQueryRent::fillTable()
{
	if ( !m_resultTable)
		return;
	bool ok = 0;
	QString costo;
	if (this->remainTime() <= 0)
	{
		int au = QString(m_rentInfo["addunits"]).toInt(&ok,10);
		int cfua = QString(m_rentInfo["costforunitadd"]).toInt(&ok,10);
		int tc = QString(m_rentInfo["totalcost"]).toInt(&ok,10);
		costo = QString::number(tc+=(cfua*au),10);
		QStringList data = QStringList() << m_rentInfo["gameserialreference"] 
					<< QString::number(this->elapsedTime(),10)
					<< QString::number(this->remainTime(),10)
					<< costo;
		m_resultTable->insertRowData(data);
	}
	else
	{
		QStringList data = QStringList() << m_rentInfo["gameserialreference"] 
					<< QString::number(this->elapsedTime(),10)
					<< QString::number(this->remainTime(),10)
					<< m_rentInfo["totalcost"];
		m_resultTable->insertRowData(data);
	}
		

}

int FormQueryRent::elapsedTime()
{
	bool ok = 0;
	QDateTime time = QDateTime::fromString(m_rentInfo["date"]+"T"+m_rentInfo["renthour"],Qt::ISODate);
	//time = time.addSecs(  (QString(m_rentInfo["units"]).toInt(&ok,10))*60*60   );
	int test = time.secsTo( QDateTime::currentDateTime(Qt::LocalTime) );
	int hour;
	
	if ((test/60)%60 <= 0)
		hour = 1;	
	else
	{
		hour = (test/60)/60;   //horas transcurridas
		return hour;
	}
}

int FormQueryRent::remainTime()
{
	bool ok = 0;
	QDateTime time = QDateTime::fromString(m_rentInfo["date"]+"T"+m_rentInfo["renthour"],Qt::ISODate);
	int esperada = time.secsTo(time.addSecs(  (QString(m_rentInfo["units"]).toInt(&ok,10))*60*60   ));
	int current = time.secsTo( QDateTime::currentDateTime(Qt::LocalTime) );
	int hour = esperada - current;
	int hourOk;
	if ((hour/60)%60 <= 0)
		hourOk = 1;	
	else
	{
		hourOk = (hour/60)/60;   //horas transcurridas
		return hourOk;
	}
	
	//cout << hourOk << endl;
}
//#include "formqueryrent.moc"
