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
	KMdiChildView *view = new KMdiChildView(i18n("Add user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminUsers *formAdminClients = new FormAdminUsers(m_db, scroll->viewport() );
	formAdminClients->setType( FormBase::Add);
	connect(formAdminClients, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formAdminClients, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
	
	scroll->addChild(formAdminClients);
	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminClients->setTitle(i18n("Admin User"));
	formAdminClients->setExplanation(i18n("Fill the fields with the user information"));
	
	emit sendWidget(view); 
}

void AdminUsers::delButtonClicked()
{
}

void AdminUsers::getClickedItem(QListViewItem *item)
{
}

void AdminUsers::modifyButtonClicked()
{
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
