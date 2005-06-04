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
#include "formrentsdebts.h"

FormRentsDebts::FormRentsDebts(FormBase::Type t,QWidget* parent, const char* name): FormBase(t,parent, name)
{
	
}


FormRentsDebts::~FormRentsDebts()
{
}

void FormRentsDebts::setupForm()
{
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());
	
	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2, m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(3);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10);
	m_layout = new QGridLayout(m_container, 2, 3, 10, 5);
	m_layout->setAlignment(Qt::AlignCenter );
	
	setupButtonsBox();
	setupBox();

	m_layout->setColStretch(2, 10);
}

void FormRentsDebts::setupBox()
{
	QVBox *vbox = new QVBox(m_container);
	m_table = new KLTable(0,5,vbox);
	
	m_layout->addWidget(vbox,0,0);
}

void FormRentsDebts::setupButtonsBox()
{
}

void FormRentsDebts::accept()
{
}

void FormRentsDebts::cancel()
{
}

void FormRentsDebts::clean()
{
}


//#include "formrentsdebts.moc"
