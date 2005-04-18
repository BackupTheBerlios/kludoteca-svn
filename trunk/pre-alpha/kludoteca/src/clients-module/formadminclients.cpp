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
#include "formadminclients.h"
#include <klocale.h>
#include <kstandarddirs.h>

FormAdminClients::FormAdminClients(QWidget *parent) : FormBase(parent, "FormAdminClient")
{
	setupForm();
}

FormAdminClients::~FormAdminClients()
{
}

void FormAdminClients::setupForm()
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

void FormAdminClients::setupButtonsBox()
{
	QVBox *vbox = new QVBox(m_container);
	m_radioButtons = new QHButtonGroup(vbox);
	m_male = new QRadioButton(i18n("Male"), m_radioButtons);
	m_female = new QRadioButton(i18n("Female"), m_radioButtons);
	
	// TODO: dar la opcion de colocar otra figura en el boton al presionarlo!.
	m_selectFace = new KPushButton("", vbox );
	m_selectFace->setPixmap( QPixmap( locate("data", "kludoteca/clients-module/icons/default3.png" )) );
	m_selectFace->resize(64, 64);
	m_layout->addWidget(vbox, 0 , 1);
}

void FormAdminClients::setupBox()
{
	QStringList labels = QStringList() << i18n("Name") << i18n("Last name") << i18n("Identification") << i18n("Phone") << i18n("Celular") << i18n("E-Mail");
	QWidget *box = new QWidget(m_container);
	this->setupGridLineEdit(box, labels, 500);
	m_layout->addWidget(box, 0, 0);
}

void FormAdminClients::accept()
{
}

void FormAdminClients::cancel()
{
}

#include "formadminclients.moc"
