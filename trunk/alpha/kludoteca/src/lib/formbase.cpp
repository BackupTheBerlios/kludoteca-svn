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

#include "formbase.h"
#include <klocale.h>


FormBase::FormBase( QWidget *parent, const char *name): QVBox(parent, name)
{
	
	m_labelTitle = new QLabel(this);
	m_labelExplanation = new QLabel(this);
	m_labelExplanation->setMargin (10);
	setupButtons(AcceptButton, CancelButton);
}

FormBase::FormBase( Button button1, Button button2, QWidget *parent, const char *name) : QVBox(parent, name)
{
	m_labelTitle = new QLabel(this);
	m_labelExplanation = new QLabel(this);
	m_labelExplanation->setMargin (10);
	
	setupButtons(button1, button2);
}

FormBase::~FormBase()
{
}

void FormBase::setTitle(QString newTitle)
{
	// TODO: make a best title! with the kde's class for manipulate texts
	m_labelTitle->setText(i18n("<h1><div align=\"center\">%1</dvi></h1>").arg(newTitle));
}

void FormBase::setTitleFont(QString font, int fontsize)
{
	setFont(QFont(font, fontsize));
}

void FormBase::setupButtons(Button button1, Button button2)
{
	m_buttons = new QHButtonGroup(this);
	
	switch ( button1)
	{
		case AcceptButton:
		{
			m_accept = new KPushButton(i18n("Register"), m_buttons);
		}
		break;
		
		case CancelButton:
		{
			m_cancel = new KPushButton(i18n("Cancel"), m_buttons);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch (button2)
	{
		case AcceptButton:
		{
			m_accept = new KPushButton(i18n("Register"), m_buttons);
		}
		break;
		
		case CancelButton:
		{
			m_cancel = new KPushButton(i18n("Cancel"), m_buttons);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}

	connect(m_accept, SIGNAL(clicked()),this, SLOT(accept()));
	connect(m_cancel, SIGNAL(clicked()),this, SLOT(cancel()));
}

void FormBase::setTextAcceptButton(QString newText)
{
	if (m_accept)
		m_accept->setText(newText);
}

void FormBase::setTextCancelButton(QString newText)
{
	if(m_cancel)
		m_cancel->setText(newText);
}

void FormBase::setExplanation(QString newExplanation)
{
	m_labelExplanation->setText(i18n("<h3>%1</h3>").arg(newExplanation));	
}

#include "formbase.moc"
