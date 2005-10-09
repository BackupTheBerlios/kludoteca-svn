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

ClientsWidget::ClientsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent, const char *name) : LTListView(QStringList() << i18n("ID") << i18n("First Name") << i18n("Last Name") << i18n("Comment"), button1, button2, button3, button4, parent, name)
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
	
	KLSelect sqlquery(QStringList() << "ldt_clients.docIdent" << "firstname" << "lastname" << "comment", QStringList() << "ldt_persons" << "ldt_clients");
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
	
	QScrollView *scroll = new QScrollView(this);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	
	FormAdminClients *formAdminClients = new FormAdminClients(FormBase::Add, scroll->viewport() );
	
	scroll->addChild(formAdminClients);
	
	connect(formAdminClients, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	connect(formAdminClients, SIGNAL(cancelled()), scroll, SLOT(close()));

	formAdminClients->setType( FormBase::Add);
	
	connect(formAdminClients, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
	
	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton);

	formAdminClients->setTitle(i18n("Admin Clients"));
	formAdminClients->setExplanation(i18n("Fill the fields with the client information"));

	emit sendWidget( scroll, i18n("Add a client") );
}

void ClientsWidget::delButtonClicked()
{
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete the Client ")+itemp->text(2)+ " ?");
	
	if (opt == KMessageBox::Yes )
	{
		KLDM->execRawQuery("delete from ldt_clients where docident="+ SQLSTR(itemp->text(1)));
		
		delete itemp;
		
		emit message2osd(i18n("The Client has been deleted!!"));
	}
}

void ClientsWidget::modifyButtonClicked()
{
	QScrollView *scroll = new QScrollView(this);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormAdminClients *formAdminClients = new FormAdminClients(FormBase::Edit, scroll->viewport() );
	connect(formAdminClients, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	QStringList clientFields;
	clientFields 	<< "ldt_clients.docident"
			<< "firstname" 
			<< "lastname" 
			<< "phone" 
			<< "cellular" 
			<< "email"
			<< "address"
			<< "genre"
			<< "ldt_clients.idreferenceperson"
			<< "ldt_clients.comment"
			<< "ldt_clients.banned";
			
	KLSelect queryClte(clientFields, 
			  QStringList() << "ldt_clients" 
					<< "ldt_persons" );
	
	queryClte.setWhere("ldt_clients.docIdent=ldt_persons.docIdent and ldt_persons.docident="+SQLSTR( m_listView->currentItem()->text(0)) ); // Login in the listview
	
	QStringList friendFields;
	friendFields << "docident" << "firstname" << "lastname" << "phone" << "cellular" << "email" << "address" << "genre";
	
	
	KLResultSet resultSetClte = KLDM->execQuery(&queryClte);
	
	
	m_xmlsource.setData(resultSetClte.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
		
	KLSqlResults resultsClte = m_xmlreader.results(); // primero para el cliente luego para la referencia
/**********************************************************************************************************************/	
	KLSelect queryRef(friendFields,
			  QStringList() << "ldt_persons" );
	
	queryRef.setWhere("docIdent="+SQLSTR(resultsClte["ldt_clients.idreferenceperson"]) );
	
	KLResultSet resultSetRef = KLDM->execQuery(&queryRef);
	
	m_xmlsource.setData(resultSetRef.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
		
	KLSqlResults resultsRef = m_xmlreader.results(); // deboo extraer los valores de resultsClte :-)
	
	formAdminClients->setClientId(resultsClte["ldt_clients.docident"]);
	formAdminClients->setClientName(resultsClte["firstname"]);
	formAdminClients->setClientLastName(resultsClte["lastname"]);
	formAdminClients->setClientPhone(resultsClte["phone"]);
	formAdminClients->setClientCellular(resultsClte["cellular"]);
	formAdminClients->setClientEmail(resultsClte["email"]);
	formAdminClients->setClientAddress(resultsClte["address"]);
	formAdminClients->setClientSex(resultsClte["genre"]);
	formAdminClients->setClientComment(resultsClte["ldt_clients.comment"]);
	formAdminClients->setClientState(resultsClte["ldt_clients.banned"]);
	
	formAdminClients->setFriendId(resultsRef["docident"]);
	formAdminClients->setFriendName(resultsRef["firstname"]);
	formAdminClients->setFriendLastName(resultsRef["lastname"]);
	formAdminClients->setFriendPhone(resultsRef["phone"]);
	formAdminClients->setFriendCellular(resultsRef["cellular"]);
	formAdminClients->setFriendEmail(resultsRef["email"]);
	formAdminClients->setFriendAddress(resultsRef["address"]);
	formAdminClients->setFriendSex(resultsRef["genre"]);
	

	//formAdminClients->setFriendLineEdits(friendFields,resultsRef);
	
	formAdminClients->setType( FormBase::Edit );
	connect(formAdminClients, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formAdminClients, SIGNAL(inserted(const QString& )), this, SLOT(updateItem(const QString &)));

	scroll->addChild(formAdminClients);
	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminClients->setTextAcceptButton(i18n("Modify"));
	formAdminClients->setTextCancelButton(i18n("Close"));
	formAdminClients->setTitle(i18n("Admin Clients"));
	formAdminClients->setExplanation(i18n("Modify the fields with the Clients an his personal reference information"));
	
	emit sendWidget(scroll,i18n("Modify user"));
}

void ClientsWidget::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
}

void ClientsWidget::addItem(const QString &pkey)
{
	KLSelect sqlquery(QStringList() << "ldt_clients.docIdent" << "firstname" << "lastname" << "comment", QStringList() << "ldt_clients" << "ldt_persons");
	sqlquery.setWhere("ldt_persons.docident="+SQLSTR(pkey)+" and ldt_clients.docident="+SQLSTR(pkey));
	//SELECT firstname,lastname,comment from ldt_clients,ldt_persons where ldt_persons.docIdent='005' and ldt_clients.docident='005';
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void ClientsWidget::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}

#include "clientswidget.moc"
