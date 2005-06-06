/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                            	   *
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
#include "rentswidget.h"
#include <klocale.h>
#include <iostream>

#include "klreportwidget.h"
#define DEBUG_RENTS 1

using std::cout;

RentsWidget::RentsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Game Serial") << i18n("Client")<< i18n("Rent Date") << i18n("Rent Hour"), button1, button2, button3, button4, parent, "Rents-module")
{
#if DEBUG_RENTS
qDebug("[Initializing RentsWidget]");
#endif
	setCaption(i18n("Rents"));
	m_timer = new QTimer(this);
	
	connect( m_timer,SIGNAL(timeout()),this,SLOT(slotTimer())  ); 
	/**
	 *  TIMER PARA REPORTE DE MOROSOS. VER SLOTTIMER()
	 */
	
	//m_timer->start( 15000, FALSE );
	
	m_listView->setTitle(i18n("Active Rents"));
	m_listView->setExplain(i18n("Please click in the \"Add\" button for create a new Rent"));
}


RentsWidget::~RentsWidget()
{
}


void RentsWidget::fillList()
{
#if DEBUG_RENTS
qDebug("RentsWidget: filling List");
#endif
	
	KLSelect sqlquery(QStringList() << "ldt_rents.gameserialreference"
					<< "ldt_rents.clientdocident"
					//<< "ldt_games.gamename"
					<< "ldt_rents.date"
					<< "ldt_rents.renthour"
// 					<< "ldt_rents.units"
// 					<< "ldt_rents.addunits"
					<< "ldt_rents.totalcost"
					, QStringList() << "ldt_persons"<< "ldt_rents"<<"ldt_games");
	sqlquery.setWhere("ldt_rents.active and");				
	sqlquery.setCondition("ldt_persons.docident");
	KLSelect subQuery1(QStringList() << "ldt_rents.clientdocident" ,QStringList() << "ldt_persons");
	sqlquery.addSubConsult("in",subQuery1);
	
	KLSelect subQuery2(QStringList() << "ldt_rents.gameserialreference" ,QStringList() << "ldt_games");
	sqlquery.addSubConsult("and ldt_games.serialreference in",subQuery2);
	
	
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	 
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void RentsWidget::getClickedItem(QListViewItem *item)
{
	qDebug("Clicked item");
	modifyButtonClicked();
}

void RentsWidget::addButtonClicked()
{
	std::cout << "Add button clicked" << std::endl;
	
	KMdiChildView *view = new KMdiChildView(i18n("Add rent"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminRents *formAdminRents = new FormAdminRents(FormBase::Add,scroll->viewport() );
	scroll->addChild(formAdminRents);
	
	formAdminRents->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);
	
	formAdminRents->setTitle(i18n("Admin Rents"));
	formAdminRents->setExplanation(i18n("Fill the fields with the Rent information"));
			
	connect(formAdminRents, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));

	formAdminRents->setType( FormBase::Add);
		
	connect(formAdminRents, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminRents, SIGNAL(inserted(const QStringList& )), this, SLOT(addItem( const QStringList& )));
	
	
	
	emit sendWidget( view );
}

void RentsWidget::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete this Rent ?"));
	
	if (opt == KMessageBox::Yes )
	{
		KLDM->execRawQuery("delete from ldt_rents where gameserialreference="
				+ SQLSTR(itemp->text(0))+" and date="+SQLSTR(itemp->text(2))+" and renthour="+SQLSTR(itemp->text(3)) );
		
		delete itemp;
		
		emit message2osd(i18n("The Rent has been deleted!!"));
	}
}

void RentsWidget::modifyButtonClicked()
{
	cout << "modify button clicked" << std::endl;
	KMdiChildView *view = new KMdiChildView(i18n("Modify user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormAdminRents *formAdminRents = new FormAdminRents(FormBase::Edit, scroll->viewport() );
	connect(formAdminRents, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	KLSelect sqlquerym(QStringList() << "ldt_rents.gameserialreference"
					<< "ldt_rents.clientdocident"
					<< "ldt_games.gamename"
					<< "ldt_rents.units"
					<< "ldt_rents.addunits" 
					<< "ldt_persons.firstname" 
					<< "ldt_persons.lastname" 
					<< "ldt_rents.active" 
					<< "ldt_rents.date"
					<< "ldt_rents.renthour"
					<< "ldt_games.costforunit"
					<< "ldt_games.costforunitadd"
					<< "ldt_rents.totalcost"
					, QStringList() << "ldt_persons"<< "ldt_rents"<<"ldt_games");
	sqlquerym.setWhere("ldt_persons.docident="+SQLSTR(m_listView->currentItem()->text(1)));
	sqlquerym.setCondition("and ldt_games.serialreference=ldt_rents.gameserialreference and ldt_rents.gameserialreference="+SQLSTR(m_listView->currentItem()->text(0)));
// 	KLSelect subQuery1(QStringList() << "ldt_rents.clientdocident" ,QStringList() << "ldt_persons");
// 	sqlquery.addSubConsult("in",subQuery1);
// 	
// 	KLSelect subQuery2(QStringList() << "ldt_rents.gameserialreference" ,QStringList() << "ldt_games");
// 	sqlquery.addSubConsult("and ldt_games.serialreference in",subQuery2);
	
	
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquerym);
	 
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	formAdminRents->setType( FormBase::Edit );
	connect(formAdminRents, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminRents, SIGNAL(inserted(const QStringList& )), this, SLOT(updateItem(const QStringList &)));
	
	formAdminRents->disabledSlider(true);
	formAdminRents->setCltId(results["ldt_rents.clientdocident"]);
	formAdminRents->setCltName(results["ldt_persons.firstname"]+" "+results["ldt_persons.lastname"]);
	formAdminRents->setGameName(results["ldt_games.gamename"]);
	formAdminRents->setGameSerial(results["ldt_rents.gameserialreference"]);
	formAdminRents->setActiveValue(results["ldt_rents.active"]);
	formAdminRents->setHourValue(results["ldt_rents.units"]);
	formAdminRents->setAddHourValue(results["ldt_rents.addunits"]);
	formAdminRents->rentDate(results["ldt_rents.date"]);
	formAdminRents->rentHour(results["ldt_rents.renthour"]);
	formAdminRents->costUnit(results["ldt_games.costforunit"]);
	formAdminRents->costUnitAdd(results["ldt_games.costforunitadd"]);
	formAdminRents->setCostOfRent(results["ldt_rents.totalcost"]);
	formAdminRents->totalCostOfRent(results["ldt_rents.totalcost"]);		
	
	
	scroll->addChild(formAdminRents);
	formAdminRents->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminRents->setTextAcceptButton(i18n("Modify"));
	formAdminRents->setTextCancelButton(i18n("Close"));
	formAdminRents->setTitle(i18n("Admin Rents"));
	formAdminRents->setExplanation(i18n("Modify the fields with the Rent information"));
	
	emit sendWidget(view);
}

void RentsWidget::queryButtonClicked()
{
/*	cout << "query button clicked" << std::endl;
	
	KMdiChildView *view = new KMdiChildView(i18n("Report test"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);

	KLReportWidget *formParticipantsList = new KLReportWidget( scroll->viewport() );

// 	ElementVector m_elements;
// 	m_elements.resize(12);
	
	KLXmlReport xmlreport("Reporte de prueba", "Empresa", "123456", KLXmlReport::PIE );
	
	for ( int i = 0; i < 12; ++i )
	{
		double x = (double(i) / 100) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((i * 17) % 105) + 151;
// 		m_elements[i] = KLReportElement( z, QColor( int(x), y, z, QColor::Hsv ) );
		xmlreport.createReportElement(z, "label", QColor( int(x), y, z, QColor::Hsv ));
	}
	
// 	formParticipantsList->getKLCanvasView()->setElements(m_elements);
	formParticipantsList->setXmlReport(xmlreport);
	
	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
	
	scroll->addChild(formParticipantsList);
	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
		
	emit sendWidget(view);*/ 
	
	QString quering = "";
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	quering += i18n("== query to user ") + itemp->text(2) + " == \n";
	
}

void RentsWidget::addItem(const QStringList &pkey)
{/*
	KLSelect sqlquery(QStringList() << "ldt_rents.gameserialreference"
			<< "ldt_rents.clientdocident"
			<< "ldt_games.gamename"
			//<< "ldt_rents.date"
			//<< "ldt_rents.renthour"
			<< "ldt_rents.units"
			<< "ldt_rents.addunits"
			<< "ldt_rents.totalcost"
			, QStringList() << "ldt_persons"<< "ldt_rents"<<"ldt_games");
	sqlquery.setWhere("");				
	sqlquery.setCondition("ldt_persons.docident");
	KLSelect subQuery1(QStringList() << "ldt_rents.clientdocident" ,QStringList() << "ldt_persons");
	sqlquery.addSubConsult("in",subQuery1);
	
	KLSelect subQuery2(QStringList() << "ldt_rents.gameserialreference" ,QStringList() << "ldt_games");
	sqlquery.addSubConsult("and ldt_games.serialreference in",subQuery2);
	
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}*/
	m_listView->clear();		
	//addItem(pkey);
	this->fillList();
}

void RentsWidget::updateItem(const QStringList &pkey)
{
	delete m_listView->currentItem();
	m_listView->clear();		
	//addItem(pkey);
	this->fillList();
}

void RentsWidget::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		KLSelect sqlquery(QStringList() << "gamename" << "firstname" << "lastname", QStringList() << "ldt_rents_view");
		
		sqlquery.addFilter(filter);
		
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
	}
}

void RentsWidget::slotTimer()
{
	KMdiChildView *view = new KMdiChildView(i18n("Report test"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormRentsDebts *formRentsDebts = new FormRentsDebts(FormBase::Add,scroll->viewport());
	
	formRentsDebts->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);
	/**
	 * TODO: meter un objeto de la clase RentsDebt
	 *
	 */
	emit sendWidget(view);

	/** JUEGO MAS ALKILADO EN UN DIA
	*
	* SELECT max(gameserialreference) as game,count(gameserialreference) as veces from ldt_rents where date='2005-05-25' group by gameserialreference having count(gameserialreference) > 1;
	*/
	
}


#include "rentswidget.moc"
