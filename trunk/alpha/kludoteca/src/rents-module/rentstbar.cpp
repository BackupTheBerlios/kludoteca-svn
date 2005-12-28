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
#include "rentstbar.h"
#include <klocale.h>

#define DEBUG_RENTSTBAR 1
RentsTBar::RentsTBar(QWidget *parent, const char *name): KTabWidget(parent,name)
{
	setupTabs();
}


RentsTBar::~RentsTBar()
{
}

void RentsTBar::setupTabs()
{
	m_rentsWidget = new RentsWidget(LTListView::ButtonAdd, 
					LTListView::ButtonDel, 
					LTListView::ButtonModify, 
					LTListView::ButtonQuery, 
					this);
	insertTab(m_rentsWidget, i18n("Rents"));
	
	m_controlist = new RentsControlList(LTListView::ButtonAdd, 
					    LTListView::ButtonDel, 
					    LTListView::ButtonModify, 
					    LTListView::ButtonQuery,
					    this);
	insertTab(m_controlist, i18n("TimeOut Rents"));
	
	connect(m_rentsWidget, SIGNAL(sendTimer(RentsTimer* )), m_controlist, SLOT(addRentsTimer(RentsTimer* )));
	connect(m_rentsWidget, SIGNAL( rentModified()),this, SLOT(applyChangesToLists())  );
	m_controlist->fillList();

}

void RentsTBar::applyChangesToLists()
{
	m_rentsWidget->fillList();
	m_controlist->fillList();
}


#include "rentstbar.moc"