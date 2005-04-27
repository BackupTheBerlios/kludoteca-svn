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
#include <iostream>
#include <qdatetime.h>

using namespace std;

FormAdminClients::FormAdminClients(KLDatabase *db,QWidget *parent) : FormBase(db,parent, "FormAdminClient")
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
	m_female->setChecked(true);
	
	// TODO: dar la opcion de colocar otra figura en el boton al presionarlo!.
	m_selectFace = new KPushButton("", vbox );
	m_selectFace->setPixmap( QPixmap( locate("data", "kludoteca/clients-module/icons/default3.png" )) );
	m_selectFace->resize(64, 64);
	m_layout->addWidget(vbox, 0 , 1);
/*********************************************************************************/
	m_combo = new KComboBox(true,m_container, "m_combo");
	m_combo->insertItem(i18n("Active"), -1);
	m_combo->insertItem(i18n("Inactive"), -2);
	m_combo->insertItem(i18n("Banned"), -3);
	
	m_comp = m_combo->completionObject();
	connect(m_combo,SIGNAL(returnPressed(const QString&)),m_comp,SLOT(addItem(const QString&)));
	m_layout->addWidget(m_combo,1,1);
}

void FormAdminClients::setupBox()
{
	QStringList labels = QStringList() << i18n("Name") << i18n("Last name") << i18n("Identification") << i18n("Address") << i18n("Phone") << i18n("Celular") << i18n("EMail");
	QWidget *box = new QWidget(m_container);
	QStringList labels2 = QStringList() << i18n("Friend name") << i18n("Friend last name") << i18n("Friend address") << i18n("Friend phone");
	
	QWidget *box2 = new QWidget(m_container);
	
	m_hashBox1 = this->setupGridLineEdit(box, labels, 500);
	m_hashBox2 = this->setupGridLineEdit(box2, labels2, 200);
	
	m_layout->addWidget(box, 0, 0);
	m_layout->addWidget(box2, 0, 2);
}

QString FormAdminClients::getClientId()
{
	return m_hashBox1[i18n("Identification")]->text();
}

QString FormAdminClients::getClientName()
{
	return m_hashBox1[i18n("Name")]->text();
}

QString FormAdminClients::getInscriptionDate()
{
	return QString( QDate::currentDate().toString(Qt::ISODate) );
}

QString FormAdminClients::getClientLastName()
{
	return m_hashBox1[i18n("Last name")]->text();
}

QString FormAdminClients::getClientSex()
{
	return m_radioButtons->selected()->text();
}

QString FormAdminClients::getClientPhone()
{
	return m_hashBox1[i18n("Phone")]->text();
}

QString FormAdminClients::getClientCellular()
{
	return m_hashBox1[i18n("Celular")]->text();
}

QString FormAdminClients::getClientState()
{
	/*hacer el combobox*/
	return i18n( m_combo->currentText() );
}

QString FormAdminClients::getClientEmail()
{
	return m_hashBox1[i18n("EMail")]->text();
}

QString FormAdminClients::getClientAddress()
{
	return m_hashBox1[i18n("Address")]->text();
}

QString FormAdminClients::getClientFriendName()
{
	return m_hashBox2[i18n("Friend name")]->text();
}


QString FormAdminClients::getClientFriendPhone()
{
	return m_hashBox2[i18n("Friend phone")]->text();
}

QString FormAdminClients::getClientFriendAddress()
{
	return m_hashBox2[i18n("Friend address")]->text();
}

/*
* Este metodo toma los valores de los klineedits a traves de dos tablas hash (m_hashBox1 y m_hashBox2)
*/
void FormAdminClients::accept()
{

	KLInsert sqlquery("ldt_clients", QStringList() 
			<< SQLSTR( this->getClientId() ) 
			<< SQLSTR( this->getInscriptionDate() )
			<< SQLSTR( this->getClientName() )
			<< SQLSTR( this->getClientLastName() )
			<< SQLSTR( this->getClientPhone() )
			<< SQLSTR( this->getClientCellular() )
			<< SQLSTR( this->getClientEmail() )
			<< SQLSTR( this->getClientSex() )
			<< SQLSTR( this->getClientState() )
			<< SQLSTR( this->getClientAddress() )
			<< SQLSTR( this->getClientFriendName() )
			<< SQLSTR( this->getClientFriendPhone() )
			<< SQLSTR( this->getClientFriendAddress() ) );

	cout << "consulta fue: " << sqlquery.getQuery() << endl;
	
	emit sendQuery(&sqlquery);
	
	if ( this->lastQueryWasGood() )
	{
		emit accepted();
		emit inserted(this->getClientId());
		clean();
	}
}

void FormAdminClients::cancel()
{
	emit cancelled();
}

void FormAdminClients::clean()
{
	QDictIterator<KLineEdit> it1( m_hashBox1 );
	QDictIterator<KLineEdit> it2( m_hashBox2 );
	for( ; it1.current(); ++it1)
		it1.current()->setText("");
	for(;it2.current();++it2)
		it2.current()->setText("");
}

#include "formadminclients.moc"
