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
#include "rentswidget.h"
#include <klocale.h>
#include <iostream>

#define DEBUG_RENTS 1

using std::cout;

RentsWidget::RentsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Game") << i18n("First Name") << i18n("Last Name"), button1, button2, button3, button4, parent, "Rents-module")
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
	if ( !m_db )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	// SELECT gamename,firstname,lastname 
	// FROM ldt_persons,ldt_rents,ldt_games 

	KLSelect sqlquery(QStringList() << "gamename" << "firstname" << "lastname", QStringList() << "ldt_games" << "ldt_persons" << "ldt_rents");
	
	// WHERE ldt_persons.docident in 
	sqlquery.setWhere("ldt_persons.docident");
	
	//			(select ldt_rents.clientdocident from ldt_persons )
	KLSelect subquery (QStringList() << "clientdocident", QStringList() << "ldt_persons" );
	sqlquery.addSubConsult("in", subquery);
	
	//       and serialreference in 
	sqlquery.setCondition("and serialreference");
	
	//			(select ldt_rents.gameserialreference from ldt_games);
	KLSelect subquery2 ( QStringList()  << "gameserialreference", QStringList() << "ldt_games" );
	sqlquery.addSubConsult("in", subquery2);
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);

	//->select(QStringList() << "gamename" << "firstname" << "lastname", "ldt_games,ldt_clients,ldt_rents", "where ldt_rents.clientdocident=ldt_clients.docident and ldt_rents.gameserialreference=ldt_games.serialreference;");
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void RentsWidget::getClickedItem(QListViewItem *item)
{
	qDebug("Clicked item");
}

void RentsWidget::addButtonClicked()
{
	std::cout << "Add button clicked" << std::endl;
	
	KMdiChildView *view = new KMdiChildView(i18n("Add rent"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
// 	FormAdminClients *formAdminClients = new FormAdminClients( scroll->viewport() );
// 	scroll->addChild(formAdminClients);
// 	
// 	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);
// 	
// 	formAdminClients->setTitle(i18n("Admin Clients"));
// 	formAdminClients->setExplanation(i18n("Fill the fields with the client information"));
	
	emit sendWidget( view );
}

void RentsWidget::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
}

void RentsWidget::modifyButtonClicked()
{
	cout << "modify button clicked" << std::endl;
}

void RentsWidget::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
}



#include "rentswidget.moc"
