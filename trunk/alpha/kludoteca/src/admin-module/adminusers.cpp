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

AdminUsers::AdminUsers(Button button1, Button button2, Button button3, Button button4,QWidget *parent, const char *name) : LTListView(QStringList() << i18n("First Name") << i18n("Last Name") << i18n("State"), button1, button2, button3, button4, parent, name)
{
	setCaption(i18n("Users"));
	
}


AdminUsers::~AdminUsers()
{
}

void AdminUsers::fillList()
{
}

void AdminUsers::addButtonClicked()
{
// 	cout << "Add button clicked" << std::endl;
// 	KMdiChildView *view = new KMdiChildView(i18n("Add client"), this );
// 	( new QVBoxLayout( view ) )->setAutoAdd( true );
// 
// 	FormAdminUsers *formAdminUsers = new FormAdminUsers(QWidget *w);
// 	formAdminUsers->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
//  	formAdminUsers->setTitle(i18n("Admin Users"));
//  	formAdminUsers->setExplanation(i18n("Fill the fields with the client information"));
// 	
// 	emit sendWidget(view);
// 	
	KMdiChildView *view = new KMdiChildView(i18n("Add client"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminUsers *formAdminClients = new FormAdminUsers( scroll->viewport() );
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


#include "adminusers.moc"
