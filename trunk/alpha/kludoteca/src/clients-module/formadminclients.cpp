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
#include "formadminclients.h"
#include <klocale.h>

FormAdminClients::FormAdminClients(QWidget *parent) : FormBase(parent, "FormAdminClient")
{
	setupForm();
}

FormAdminClients::~FormAdminClients()
{
}

void FormAdminClients::setupForm()
{
	m_container = new QFrame(this);
	m_layout = new QGridLayout(m_container, 2, 2);
// 	QWidget *widget = this->setupLineEdit(m_container, "Name", 130);
	
// 	m_layout->addWidget(widget, 0, 0);
	
	m_radioButtons = new QHButtonGroup(m_container);
	m_male = new QRadioButton(i18n("Male"), m_radioButtons);
	m_female = new QRadioButton(i18n("Female"), m_radioButtons);
	m_layout->addWidget(m_radioButtons, 0 , 1);
	
	QStringList labels = QStringList() << i18n("Name") << i18n("Identification") << i18n("Phone") << i18n("Celular") << i18n("E-Mail");
	QWidget *box = new QWidget(m_container);
	this->setupGridLineEdit(box, labels);
	m_layout->addWidget(box, 0, 0);
}

void FormAdminClients::accept()
{
}

void FormAdminClients::cancel()
{
}

#include "formadminclients.moc"
