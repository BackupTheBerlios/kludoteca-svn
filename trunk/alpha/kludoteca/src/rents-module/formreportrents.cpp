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
#include "formreportrents.h"
#include <klocale.h>
#include <iostream>
using namespace std;

FormReportRents::FormReportRents(FormBase::Type t, QWidget* parent): FormBase(t,parent)
{
	emit checkDate("2005-06-07");	
	connect( this, SIGNAL(checkDate(const QString&)),this,SLOT(showReport(const QString&)) );
}


FormReportRents::~FormReportRents()
{
}


void FormReportRents::setupForm()
{
    	
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());

	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2, m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(3);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10);
	m_layout = new QGridLayout(m_container, 3, 1, 10, 5);
	m_layout->setAlignment(Qt::AlignCenter );
	
	setupButtonsBox();
	setupBox();

	m_layout->setColStretch(2, 10);
	
	QHBox *dateBox = new QHBox(m_container);
	(new QLabel(i18n("Year"),dateBox));
	m_comboY = new KComboBox(false,dateBox,"comboY");
	m_comboY->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 2005; i < 2051; i++)
		m_comboY->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Month"),dateBox));
	m_comboM = new KComboBox(false,dateBox,"comboM");
	m_comboM->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 13; i++)
		m_comboM->insertItem(QString::number(i,10));
	
	(new QLabel(i18n("Day"),dateBox));
	m_comboD = new KComboBox(false,dateBox,"comboD");
	m_comboD->setInsertionPolicy(KComboBox::NoInsertion);
	for(uint i = 1; i < 32; i++)
		m_comboD->insertItem(QString::number(i,10));
	
	
	//m_scrollView->addChild(formParticipantsList);
	
	m_layout->addWidget(dateBox,0,0);
	
}

void FormReportRents::accept()
{
	QString year = m_comboY->currentText();
	QString month = m_comboM->currentText();
	QString day = m_comboD->currentText();
	emit accepted();
		
	
    	
}

void FormReportRents::cancel()
{
    
}

void FormReportRents::clean()
{
    
}

void FormReportRents::setupBox()
{}

void FormReportRents::setupButtonsBox()
{}

void FormReportRents::showReport(const QString &date)
{
	setupForm();
	
//	m_layout->addWidget(reporteRenta,1,0);
}



//#include "formreportrents.moc"