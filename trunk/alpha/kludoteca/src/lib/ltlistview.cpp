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

#include "ltlistview.h"
#include <klocale.h>

LTListView::LTListView(QWidget *parent, const char *name) : QVBox(parent, name)
{
}

LTListView::LTListView(Button button1, Button button2, Button button3, Button button4, QWidget *parent, const char *name) : QVBox(parent, name)
{
	makeList();
	makeButtons(button1, button2, button3, button4);
}


LTListView::~LTListView()
{
}

void LTListView::makeList()
{
	m_listView = new KListView(this);
}

void LTListView::makeButtons(Button button1, Button button2, Button button3, Button button4)
{
	m_buttons = new QHButtonGroup(this);
	switch ( button1 )
	{
		case ButtonAdd:
		{
			KPushButton *buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( buttonAdd, button1);
		}
		break;
		
		case ButtonDel:
		{
			KPushButton *buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( buttonDel, button1);
		}
		break;
		
		case ButtonModify:
		{
			KPushButton *buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( buttonModify, button1);
		}
		break;
		
		case ButtonQuery:
		{
			KPushButton *buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( buttonQuery, button1);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch (button2)
	{
		case ButtonAdd:
		{
			KPushButton *buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( buttonAdd, button2);
		}
		break;
		
		case ButtonDel:
		{
			KPushButton *buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( buttonDel, button2);
		}
		break;
		
		case ButtonModify:
		{
			KPushButton *buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( buttonModify, button2);
		}
		break;
		
		case ButtonQuery:
		{
			KPushButton *buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( buttonQuery, button2);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch(button3)
	{
		case ButtonAdd:
		{
			KPushButton *buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( buttonAdd, button3);
		}
		break;
		
		case ButtonDel:
		{
			KPushButton *buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( buttonDel, button3);
		}
		break;
		
		case ButtonModify:
		{
			KPushButton *buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( buttonModify, button3);
		}
		break;
		
		case ButtonQuery:
		{
			KPushButton *buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( buttonQuery, button3);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch(button4)
	{
		case ButtonAdd:
		{
			KPushButton *buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( buttonAdd, button4);
		}
		break;
		
		case ButtonDel:
		{
			KPushButton *buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( buttonDel, button4);
		}
		break;
		
		case ButtonModify:
		{
			KPushButton *buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( buttonModify, button4);
		}
		break;
		
		case ButtonQuery:
		{
			KPushButton *buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( buttonQuery, button4);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
}

KListView* LTListView::getListView()
{
	return m_listView;
}

#include "ltlistview.moc"
