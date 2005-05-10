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

#include "ltlistview.h" 
#include <klocale.h>
#include <kapplication.h>
#include <klineedit.h>
#include <ktoolbarbutton.h>

LTListView::LTListView(QWidget *parent, const char *name) : QVBox(parent, name), m_buttonAdd(0), m_buttonDel(0), m_buttonModify(0), m_buttonQuery(0), m_db(0)
{
}

LTListView::LTListView(QStringList colsText, Button button1, Button button2, Button button3, Button button4, QWidget *parent, const char *name) : QVBox(parent, name), m_buttonAdd(0), m_buttonDel(0), m_buttonModify(0), m_buttonQuery(0), m_db(0), m_filterText(i18n("Filter here..." ))
{
	m_timer = new QTimer(this);
	
	KToolBar *searchToolBar = new KToolBar( this );
	
	KToolBarButton *button = new KToolBarButton( "locationbar_erase", 0, searchToolBar );
	m_searchEdit = new KLineEdit(m_filterText, searchToolBar );
	searchToolBar->setStretchableWidget( m_searchEdit );
	m_searchEdit->setFrame( QFrame::Sunken );
	
	connect( m_searchEdit, SIGNAL( textChanged( const QString& ) ), SLOT( slotSetFilterTimeout() ) );
	connect( m_searchEdit, SIGNAL( returnPressed() ), SLOT( slotSetFilter() ) );
	connect( button, SIGNAL( clicked() ), m_searchEdit, SLOT( clear() ) );
	connect( m_timer, SIGNAL( timeout() ), SLOT( slotSetFilter() ) );
	
 	makeList(colsText);
	makeButtons(button1, button2, button3, button4);
	
	connect(static_cast<KLResultSetInterpreter *>(m_xmlreader.contentHandler()), SIGNAL(readRecord(QStringList )), this, SLOT(putItems(QStringList )));
	
}


LTListView::~LTListView()
{
}

void LTListView::setDatabase(KLDatabase *db)
{
#warning "Por favor no use esta funcion, use KLDM en su lugar"
	qDebug("Por favor no use esta funcion, use KLDM en su lugar");
	if ( db )
	{
		m_db = db;
	}
	else
	{
		m_db = new KLDatabase(this);
	}
	
	if ( ! m_db->open() )
	{
		qDebug("La base de datos no pudo abrirse!!");
	}
}

void LTListView::makeList(QStringList colsText)
{
	m_listView = new KListView(this);
	QColor c; c.setRgb( 57, 64, 98 );
	m_listView->setAlternateBackground( c );
	m_listView->setSelectionMode( QListView::Extended );
	m_listView->setAllColumnsShowFocus( true );
	
#if KDE_IS_VERSION( 3, 3, 91 )
    	m_listView->setShadeSortColumn( true );
#endif

	for (uint i = 0; i < colsText.count(); i++)
	{
		m_listView->addColumn( colsText[i] );
	}
	
	connect( m_listView, SIGNAL(executed(QListViewItem* )), this, SLOT(getClickedItem(QListViewItem* )));
}

void LTListView::makeButtons(Button button1, Button button2, Button button3, Button button4)
{
	m_buttons = new QHButtonGroup(this);
	switch ( button1 )
	{
		case ButtonAdd:
		{
			m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, button1);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, button1);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, button1);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, button1);
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
			m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, button2);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, button2);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, button2);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, button2);
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
			KPushButton *m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, button3);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, button3);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, button3);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, button3);
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
			m_buttonAdd = new KPushButton(i18n("Add"), m_buttons);
			m_buttons->insert( m_buttonAdd, button4);
		}
		break;
		
		case ButtonDel:
		{
			m_buttonDel = new KPushButton(i18n("Delete"), m_buttons);
			m_buttons->insert( m_buttonDel, button4);
		}
		break;
		
		case ButtonModify:
		{
			m_buttonModify = new KPushButton(i18n("Modify"), m_buttons);
			m_buttons->insert( m_buttonModify, button4);
		}
		break;
		
		case ButtonQuery:
		{
			m_buttonQuery = new KPushButton(i18n("Query"), m_buttons);
			m_buttons->insert( m_buttonQuery, button4);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	if ( m_buttonAdd )
		connect(m_buttonAdd, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	if (m_buttonDel )
		connect(m_buttonDel, SIGNAL(clicked()), this, SLOT(delButtonClicked()));
	if (m_buttonModify)
		connect(m_buttonModify, SIGNAL(clicked()), this, SLOT(modifyButtonClicked()));
	if(m_buttonQuery)
		connect(m_buttonQuery, SIGNAL(clicked()), this, SLOT(queryButtonClicked()));
}

void LTListView::putItems(QStringList items)
{
	KListViewItem *itemp = new KListViewItem(m_listView);
	for (uint i = 0; i < items.count(); i++)
	{
		itemp->setText(i, items[i]);
	}
	m_listView->insertItem(itemp);
}

void LTListView::addItem(const QString &pkey)
{
	// TODO: Esto sera virtual puro
	qDebug("Por favor reimplemente la funcion \"addItem\" en su respectivo modulo!!");
}

KListView* LTListView::getListView()
{
	return m_listView;
}

void LTListView::slotSetFilterTimeout()
{
	if ( m_searchEdit->text() != m_filterText )
		m_timer->start( 280, true );
}

void LTListView::slotSetFilter()
{
	m_timer->stop();
	m_listView->clear();
	
	slotFilter( m_searchEdit->text() );
	
	m_listView->repaint();
}

void LTListView::slotFilter(const QString &filter)
{
	std::cout << "LTListView filter: " << filter << std::endl;
	
	qDebug("Por favor reimplemente la funcion \"slotFilter\" en su respectivo modulo!!");
	if ( filter.isEmpty() )
	{
		fillList();
	}
}


#include "ltlistview.moc"
