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
 
#include "clientswidget.h"
#include <klocale.h>

using namespace std;

ClientsWidget::ClientsWidget(Button button1, Button button2, Button button3, Button button4,QWidget *parent, const char *name) : LTListView(button1, button2, button3, button4, parent, name)
{
	setCaption(i18n("Clients"));
}


ClientsWidget::~ClientsWidget()
{
}

void ClientsWidget::getClickedItem(QListViewItem *item)
{
}

void ClientsWidget::addButtonClicked()
{
	cout << "Add button clicked" << std::endl;
	KMdiChildView *view = new KMdiChildView(i18n("Add client"), this );
	
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	FormAdminClients *formAdminClients = new FormAdminClients( view );
	formAdminClients->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminClients->setTitle(i18n("Admin Clients"));
	formAdminClients->setExplanation(i18n("Fill the fields with the client information"));
	
	emit sendWidget(view);
}

void ClientsWidget::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
}

void ClientsWidget::modifyButtonClicked()
{
	cout << "modify button clicked" << std::endl;
}

void ClientsWidget::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
}


#include "clientswidget.moc"
