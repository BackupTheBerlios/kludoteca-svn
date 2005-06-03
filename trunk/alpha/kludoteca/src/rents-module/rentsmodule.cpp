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
#include "rentsmodule.h"
#include <klocale.h>

RentsModule::RentsModule(QWidget *parent) : LTToolBox(parent,"rents")
{
	setCaption(i18n("Rents"));
	setupTabs();
}


RentsModule::~RentsModule()
{
}

void RentsModule::setupTabs()
{
	m_rentsTBar = new RentsTBar(this);
	addItem(m_rentsTBar, i18n("Rents"));
}

ListLTListView RentsModule::listViews()
{
	for (uint i = 0; i < m_rentsTBar->count(); i++)
	{
		LTListView *ltlv = static_cast<LTListView *>( m_rentsTBar->page(i) );
		if ( ltlv )
		{
			m_listViews.append(ltlv);
		}
	}
	return m_listViews;
}


#include "rentsmodule.moc"

