/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        	   *
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
 
#include "clientswidget.h"
#include <klocale.h>
#include "klquery.h"

using namespace std;

ClientsWidget::ClientsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent, const char *name) : LTListView(QStringList() << i18n("First Name") << i18n("Last Name") << i18n("State"), button1, button2, button3, button4, parent, name)
{
	setCaption(i18n("Clients"));
}


ClientsWidget::~ClientsWidget()
{
}

void ClientsWidget::fillList()
{
	if ( !KLDM )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "state", QStringList() << "ldt_persons" << "ldt_clients");
	sqlquery.setWhere("ldt_persons.docIdent=ldt_clients.docIdent");
	
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void ClientsWidget::getClickedItem(QListViewItem *item)
{
	qDebug("Clicked item");
	modifyButtonClicked();
}

void ClientsWidget::addButtonClicked()
{
	cout << "Add button clicked" << endl;
	
	KMdiChildView *view = new KMdiChildView(i18n("Add client"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	cout << "COMIENZO DE CONFIG CLIENT" << endl;
	
	FormAdminClients *formAdminClients = new FormAdminClients(FormBase::Add, scroll->viewport() );
	
	cout << "SE CREO OBJETO ADMINCLIENT" << endl;
	connect(formAdminClients, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));

	formAdminClients->setType( FormBase::Add);
		
	connect(formAdminClients, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminClients, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
	scroll->addChild(formAdminClients);
	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);

	formAdminClients->setTitle(i18n("Admin Clients"));
	formAdminClients->setExplanation(i18n("Fill the fields with the client information"));
	cout << "ANTES DEL EMIT SENDWIDGET" << endl;
	emit sendWidget( view );
	cout << "DESPUES DEL EMIT DE SENDWIDGET" << endl;
}

void ClientsWidget::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
}

void ClientsWidget::modifyButtonClicked()
{
	
#if DEBUG_ADMINUSERS
	qDebug("init addButtonClicked");
#endif
	KMdiChildView *view = new KMdiChildView(i18n("Modify user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormAdminClients *formAdminClients = new FormAdminClients(FormBase::Edit, scroll->viewport() );
	
	KLSelect sqlquery(QStringList() << "ldt_clients.docident" << "firstname" << "lastname" << "address" << "phone" << "email", QStringList() << "ldt_clients" << "ldt_persons" );
	
	sqlquery.setWhere("ldt_persons.docIdent=ldt_clients.docIdent"); // Login in the listview
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	KLSqlResults results = m_xmlreader.results(); // deboo extraer los valores de results :-)
}

void ClientsWidget::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
}

void ClientsWidget::addItem(const QString &pkey)
{
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "state", QStringList() << "ldt_clients" << "ldt_persons");
	sqlquery.setWhere("ldt_persons.docident="+SQLSTR(pkey)+" and ldt_clients.docident="+SQLSTR(pkey));
	//SELECT firstname,lastname,state from ldt_clients,ldt_persons where ldt_persons.docIdent='005' and ldt_clients.docident='005';
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

#include "clientswidget.moc"
