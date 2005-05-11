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


FormAdminClients::FormAdminClients(FormBase::Type t,QWidget *parent) : FormBase(t,parent,"FormAdminClient")
{
	setupForm();
}
FormAdminClients::~FormAdminClients()
{
}

void FormAdminClients::setupForm()
{
	cout << "CREANDO FORMADMINWIDGET DESDE SETUPFORM" << endl;
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());

	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2, m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(3);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10);
	m_layout = new QGridLayout(m_container, 1, 2, 10, 5);
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
	QStringList clientLabels = QStringList() << i18n("Identification");
		
	QStringList personLabels = QStringList() << i18n("Name") 
						<< i18n("Last name")
						<< i18n("Address")
						<< i18n("Phone")
						<< i18n("Celular")
						<< i18n("EMail");
	
	

	QStringList FriendLabels = QStringList() << i18n("Friend Id")
						<< i18n("Friend Name") 
						<< i18n("Friend Last name")
						<< i18n("Friend Address")
						<< i18n("Friend Phone")
						<< i18n("Friend Celular")
						<< i18n("Friend EMail");
	
	QStringList clientdbFields = QStringList() << "docIdent";
	
	QStringList persondbFields = QStringList() << "firstname" 
						<< "lastname"
						<< "phone"
						<< "celullar"
						<< "email"
						<< "address" ;
	
	QStringList friendDbFields = QStringList() << "docIdent"
						<< "firstname" 
						<< "lastname"
						<< "phone"
						<< "celullar"
						<< "email"
						<< "address" ;
						
	QWidget *box1 = new QWidget(m_container);
	QWidget *box2 = new QWidget(m_container);
	
	m_hashClient = this->setupGridLineEdit(box1, clientLabels, 400, clientdbFields);
	
	this->addLineEdits(box1, personLabels, m_hashPerson, 400 ,persondbFields);
	
	m_hashFriend = this->setupGridLineEdit(box2, FriendLabels, 200, friendDbFields);
	
	m_layout->addWidget(box1, 0, 0);
 	m_layout->addWidget(box2, 0, 2);

}

QString FormAdminClients::getClientId()
{
	return m_hashClient["docIdent"]->text();
}

QString FormAdminClients::getClientName()
{
	return m_hashPerson["firstname"]->text();
}

QString FormAdminClients::getInscriptionDate()
{
	return QString( QDate::currentDate().toString(Qt::ISODate) );
}

QString FormAdminClients::getClientLastName()
{
	return m_hashPerson["lastname"]->text();
}

QString FormAdminClients::getClientSex()
{
	return m_radioButtons->selected()->text();
}

QString FormAdminClients::getClientPhone()
{
	return m_hashPerson["phone"]->text();
}

QString FormAdminClients::getClientCellular()
{
	return m_hashPerson["celullar"]->text();
}

QString FormAdminClients::getClientState()
{
	/*hacer el combobox*/
	return i18n( m_combo->currentText() );
}

QString FormAdminClients::getClientEmail()
{
	return m_hashPerson["email"]->text();
}

QString FormAdminClients::getClientAddress()
{
	return m_hashPerson["address"]->text();
}

void FormAdminClients::setClientId()
{
}

void FormAdminClients::setClientName()
{
}

void FormAdminClients::setClientLastName()
{
}

void FormAdminClients::setClientPhone()
{
}

void FormAdminClients::setClientCellular()
{
}

void FormAdminClients::setClientState()
{
}

void FormAdminClients::setClientEmail()
{
}

void FormAdminClients::setClientSex()
{
}

void FormAdminClients::setClientAddress()
{
}


/******************************************************************************************
***************************INFO DE REFERENCIA *********************************************
*******************************************************************************************/
QString FormAdminClients::getFriendId()
{
}

QString FormAdminClients::getFriendName()
{
	return m_hashFriend["firstname"]->text();
}

QString FormAdminClients::getFriendLastName()
{
	
}

QString FormAdminClients::getFriendPhone()
{
	return m_hashFriend["phone"]->text();
}

QString FormAdminClients::getFriendCellular()
{

}

QString FormAdminClients::getFriendAddress()
{
	return m_hashFriend["address"]->text();
}

QString FormAdminClients::getFriendState()
{
}

QString FormAdminClients::getFriendEmail()
{
}

QString FormAdminClients::getFriendSex()
{
}


/*
* Este metodo toma los valores de los klineedits a traves de dos tablas hash (m_hashPerson y m_hashFriend)
*/
void FormAdminClients::accept()
{
	switch( getType() )
	{
		case FormBase::Add:
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
							<< SQLSTR( this->getFriendName() )
							<< SQLSTR( this->getFriendPhone() )
							<< SQLSTR( this->getFriendAddress() ) );

			cout << "consulta fue: " << sqlquery.getQuery() << endl;
	
			emit sendQuery(&sqlquery);
	
			if ( this->lastQueryWasGood() )
			{
				emit accepted();
				emit inserted(this->getClientId());
				clean();
			}
		}
		break;
		case FormBase::Edit:
		{
			
		}
	}		
}
void FormAdminClients::cancel()
{
	emit cancelled();
}

void FormAdminClients::clean()
{
	QDictIterator<KLineEdit> it1( m_hashPerson );
	QDictIterator<KLineEdit> it2( m_hashFriend );
	for( ; it1.current(); ++it1)
		it1.current()->setText("");
	for(;it2.current();++it2)
		it2.current()->setText("");
}

#include "formadminclients.moc"
