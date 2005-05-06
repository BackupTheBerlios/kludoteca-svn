/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
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

#include "adminusers.h"
#include <klocale.h>
#include <kpushbutton.h>
#include <qwidget.h>
#include <kmessagebox.h>

#define DEBUG_ADMINUSERS 0

using namespace std;

AdminUsers::AdminUsers(Button button1, Button button2, Button button3, Button button4,QWidget *parent, const char *name) : LTListView(QStringList() << i18n("First Name") << i18n("Last Name") << i18n("login"), button1, button2, button3, button4, parent, name)
{
	setCaption(i18n("Users"));
	
}


AdminUsers::~AdminUsers()
{
}

void AdminUsers::fillList()
{
#if DEBUG_ADMINUSERS
	qDebug("Fill List");
#endif
	if ( !m_db )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	m_sqlquery = new KLSelect(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users");
	
	KLResultSet resultSet = m_db->execQuery(m_sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void AdminUsers::addButtonClicked()
{
#if DEBUG_ADMINUSERS
	qDebug("init addButtonClicked");
#endif
	KMdiChildView *view = new KMdiChildView(i18n("Add user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormAdminUsers *formAdminUsers = new FormAdminUsers(m_db, scroll->viewport() );
	connect(formAdminUsers, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));

	formAdminUsers->setType( FormBase::Add);
	connect(formAdminUsers, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminUsers, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));

	scroll->addChild(formAdminUsers);
	formAdminUsers->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );

	formAdminUsers->setTitle(i18n("Admin User"));
	formAdminUsers->setExplanation(i18n("Fill the fields with the user information"));
	
	emit sendWidget(view); 
#if DEBUG_ADMINUSERS
	qDebug("end addButtonClicked");
#endif
}

void AdminUsers::delButtonClicked()
{
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete the user ")+itemp->text(2)+ " ?");
	
	if (opt == KMessageBox::Yes )
	{
		m_db->execRawQuery("delete from ldt_users where login="+ SQLSTR(itemp->text(2)));
		
		m_db->execRawQuery("drop user "+itemp->text(2));
		
		delete itemp;
		
		emit message2osd(i18n("The user has been deleted!!"));
	}
}

void AdminUsers::getClickedItem(QListViewItem *item)
{
	modifyButtonClicked();
}

void AdminUsers::modifyButtonClicked()
{
#if DEBUG_ADMINUSERS
	qDebug("init modifyButtonClicked");
#endif
	KMdiChildView *view = new KMdiChildView(i18n("Modify user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormAdminUsers *formAdminUsers = new FormAdminUsers(m_db, scroll->viewport() );
	
	connect(formAdminUsers, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));

	KLSelect sqlquery(QStringList() << "docident" << "login" << "firstname" << "lastname" << "sex" << "address" << "phone" << "email" << "permissions", QStringList() << "ldt_users");
	
	sqlquery.setWhere("login="+SQLSTR(m_listView->currentItem()->text(2))); // Login in the listview
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	std::cout << results["login"] << std::endl;

	formAdminUsers->setAddress( results["address"] );
	formAdminUsers->setEmail(results["email"]);
	formAdminUsers->setFirstName( results["firstname"]);
	formAdminUsers->setIdentification( results["docident"]);
	formAdminUsers->setLastName( results["lastname"]);
	formAdminUsers->setLogin( results["login"]);
	formAdminUsers->setPermissions( results["permissions"]);
	formAdminUsers->setPhone( results["phone"]);
	std::cout << "here" << std::endl;
	formAdminUsers->setSex( results["sex"]);
	
	formAdminUsers->setType( FormBase::Edit );
	connect(formAdminUsers, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminUsers, SIGNAL(inserted(const QString& )), this, SLOT(updateItem(const QString &)));

	scroll->addChild(formAdminUsers);
	formAdminUsers->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminUsers->setTextAcceptButton(i18n("Modify"));
	formAdminUsers->setTextCancelButton(i18n("Close"));
	formAdminUsers->setTitle(i18n("Admin User"));
	formAdminUsers->setExplanation(i18n("Modify the fields with the user information"));
	
	emit sendWidget(view); 
#if DEBUG_ADMINUSERS
	qDebug("end addButtonClicked");
#endif
}

void AdminUsers::queryButtonClicked()
{
	QString quering = "";
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	quering += i18n("== query to user ") + itemp->text(2) + " == \n";
	
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "docident" << "address" << "phone" << "email" << "permissions", QString("ldt_users"));
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total ))
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	quering += i18n("Real name: ") + results["firstname"] + " " + results["lastname"] + "\n";
	quering += i18n("Identification: ") + results["docident"] + "\n";
	quering += i18n("Address: ") + results["address"] + "\n";
	quering += i18n("Phone: ") + results["phone"] + "\n";
	quering += i18n("Email: ") + results["email"] + "\n";
	quering += i18n("Permissions:") + results["permissions"] + "\n\n";
	
	emit message2osd(quering);
}

void AdminUsers::addItem(const QString &pkey)
{
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users");
	sqlquery.setWhere("login="+SQLSTR(pkey));
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void AdminUsers::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}

void AdminUsers::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		m_sqlquery->addFilter(filter);
		KLResultSet resultSet = m_db->execQuery(m_sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
	}
}

#include "adminusers.moc"
