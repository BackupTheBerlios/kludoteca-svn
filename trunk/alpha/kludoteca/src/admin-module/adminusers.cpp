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

#include "adminusers.h"
#include <klocale.h>
#include <kpushbutton.h>
#include <qwidget.h>

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
	
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users");
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.parse(m_xmlsource) )
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
}

void AdminUsers::getClickedItem(QListViewItem *item)
{
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
	
	//docident |  login  | firstname | lastname |  sex   | address | phone  |      email       | permissions

	KLSelect sqlquery(QStringList() << "docident" << "login" << "firstname" << "lastname" << "sex" << "address" << "phone" << "email" << "permissions", QStringList() << "ldt_users");
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}

	formAdminUsers->setType( FormBase::Edit );
	connect(formAdminUsers, SIGNAL(cancelled()), view, SLOT(close()));

	scroll->addChild(formAdminUsers);
	formAdminUsers->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminUsers->setTextAcceptButton(i18n("Modify"));
	formAdminUsers->setTitle(i18n("Admin User"));
	formAdminUsers->setExplanation(i18n("Modify the fields with the user information"));
	
	emit sendWidget(view); 
#if DEBUG_ADMINUSERS
	qDebug("end addButtonClicked");
#endif
}

void AdminUsers::queryButtonClicked()
{
}

void AdminUsers::addItem(const QString &pkey)
{
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users");
	sqlquery.setWhere("login="+SQLSTR(pkey));
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.parse(m_xmlsource) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

#include "adminusers.moc"
