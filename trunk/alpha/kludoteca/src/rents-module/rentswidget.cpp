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

#define DEBUG_RENTS 1

using std::cout;

RentsWidget::RentsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Game Code") << i18n("Client")<< i18n("Game") << i18n("Rent Date") << i18n("Rent Hour") << i18n("Time Units") << i18n("Aditional Time"), button1, button2, button3, button4, parent, "Rents-module")
{
#if DEBUG_RENTS
qDebug("[Initializing RentsWidget]");
#endif
	setCaption(i18n("Rents"));
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
					<< "ldt_games.gamename"
					<< "ldt_rents.date"
					<< "ldt_rents.renthour"
					<< "ldt_rents.units"
					<< "ldt_rents.addunits"
					, QStringList() << "ldt_persons"<< "ldt_rents"<<"ldt_games");
	sqlquery.setWhere("");				
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
		KLDM->execRawQuery("delete from ldt_rents where ="+ SQLSTR(itemp->text(1)));
		
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
					, QStringList() << "ldt_persons"<< "ldt_rents"<<"ldt_games");
	sqlquerym.setWhere("ldt_persons.docident="+SQLSTR(m_listView->currentItem()->text(1)));
// 	sqlquery.setWhere("");				
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
	
	formAdminRents->setCltId(results["ldt_rents.clientdocident"]);
	formAdminRents->setCltName(results["ldt_persons.firstname"]+" "+results["ldt_persons.lastname"]);
	formAdminRents->setGameName(results["ldt_games.gamename"]);
	formAdminRents->setGameSerial(results["ldt_rents.gameserialreference"]);
	formAdminRents->setActiveValue(results["ldt_rents.active"]);
	formAdminRents->setHourValue(results["ldt_rents.units"]);
	formAdminRents->setAddHourValue(results["ldt_rents.addunits"]);
	formAdminRents->rentDate(results["ldt_rents.date"]);
	formAdminRents->rentHour(results["ldt_rents.renthour"]);
			
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
	cout << "query button clicked" << std::endl;
}

void RentsWidget::addItem(const QStringList &pkey)
{
	//std::cout << "Adicionando item con pkey: " << pkey << std::endl;	
	KLSelect sqlquery(QStringList() << "ldt_rents.gameserialreference"
					<< "ldt_rents.clientdocident"				
					<< "ldt_rents_view.gamename"
					<< "ldt_rents.date"
					<< "ldt_rents.renthour"
					<< "ldt_rents.units"
					<< "ldt_rents.addunits"
					, QStringList() << "ldt_rents_view"<< "ldt_rents");
	
	// WHERE ldt_persons.docident in 
	sqlquery.setWhere("ldt_rents.gameserialreference="+SQLSTR(pkey[0])+" and ldt_rents.date="+SQLSTR(pkey[1])+" and ldt_rents.renthour="+SQLSTR(pkey[2])+" and ldt_rents_view.gameserialreference="+SQLSTR(pkey[0]));

	KLResultSet resultSet = KLDM->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void RentsWidget::updateItem(const QStringList &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
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

#include "rentswidget.moc"
