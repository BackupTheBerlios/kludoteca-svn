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
	
	m_labelTitle = new QLabel(this,"title of form");
	m_labelExplanation = new QLabel(this,"Explanation of form");
	m_labelExplanation->setMargin (10);
}

FormBase::~FormBase()
{
}

void FormBase::setTitle(QString newTitle)
{
	// TODO: make a best title! with the kde's class for manipulate texts
	m_labelTitle->setText(i18n("<h1><div align=\"center\">%1</dvi></h1>").arg(newTitle));
}

void FormBase::setupButton()
{
	m_buttons = new QHBox(this);
	m_accept = new KPushButton(i18n("register"), m_buttons);
	m_cancel = new KPushButton(i18n("cancel"), m_buttons);
	m_modify = new KPushButton(i18n("modify"), m_buttons);
	connect(m_accept, SIGNAL(clicked()),this, SLOT(accept()));
	connect(m_cancel, SIGNAL(clicked()),this, SLOT(cancel()));
	connect(m_modify, SIGNAL(clicked()),this, SLOT(modify()));
}

void FormBase::setTextButtonOne(QString newText)
{
	m_accept->setText(newText);
}

void FormBase::setTextButtonTwo(QString newText)
{
	m_cancel->setText(newText);
}

void FormBase::setTextButtonThree(QString newText)
{
	m_modify->setText(newText);
}

void FormBase::setExplanation(QString newExplanation)
{
	m_labelExplanation->setText(i18n("<h3>%1</h3>").arg(newExplanation));	
}

#include "formbase.moc"
