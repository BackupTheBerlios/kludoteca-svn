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

#include "adminwidget.h"
#include <klocale.h>

AdminWidget::AdminWidget(QWidget *parent) : LTToolBox(parent, "AdminModule")
{
	setCaption(i18n("Admin"));
	
	setupTabs();
}

AdminWidget::~AdminWidget()
{
}

void AdminWidget::setupTabs()
{
	m_adminUsers = new AdminUsers(	LTListView::ButtonAdd, 
					LTListView::ButtonDel, 
					LTListView::ButtonModify, 
					LTListView::ButtonQuery, 
					this,
					"list view admin users");
					
	this->addItem(m_adminUsers, i18n("Users"));
	
	m_adminDatabase = new AdminDatabase(this);
	this->addItem(m_adminDatabase, i18n("Database"));
}


#include "adminwidget.moc"
