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
/****************** CLIENT *****************************************************/
	QVBox *vboxClient = new QVBox(m_container);
	m_radioButtonClte = new QHButtonGroup(vboxClient);
	m_maleClte = new QRadioButton(i18n("Male"), m_radioButtonClte);
	m_femaleClte = new QRadioButton(i18n("Female"), m_radioButtonClte);
	m_femaleClte->setChecked(true);
	
	// TODO: dar la opcion de colocar otra figura en el boton al presionarlo!.
	m_selectFaceClte = new KPushButton("", vboxClient );
	m_selectFaceClte->setPixmap( QPixmap( locate("data", "kludoteca/clients-module/icons/default3.png" )) );
	m_selectFaceClte->resize(64, 64);
	m_layout->addWidget(vboxClient, 0 , 1);

	m_comboClte = new KComboBox(true,m_container, "m_combo");
	m_comboClte->insertItem(i18n("Active"), -1);
	m_comboClte->insertItem(i18n("Inactive"), -2);
	m_comboClte->insertItem(i18n("Banned"), -3);
	
	m_compClte = m_comboClte->completionObject();
	connect(m_comboClte,SIGNAL(returnPressed(const QString&)),m_compClte,SLOT(addItem(const QString&)));
	m_layout->addWidget(m_comboClte,1,1);

/***************** REFERENCE *********************************/

	QVBox *vboxFriend = new QVBox(m_container);
	m_radioButtonFrd = new QHButtonGroup(vboxFriend);
	m_maleFrd = new QRadioButton(i18n("Male"), m_radioButtonFrd);
	m_femaleFrd = new QRadioButton(i18n("Female"), m_radioButtonFrd);
	m_femaleFrd->setChecked(true);
	
	// TODO: dar la opcion de colocar otra figura en el boton al presionarlo!.
	m_selectFaceFrd = new KPushButton("", vboxFriend );
	m_selectFaceFrd->setPixmap( QPixmap( locate("data", "kludoteca/clients-module/icons/default3.png" )) );
	m_selectFaceFrd->resize(64, 64);
	m_layout->addWidget(vboxFriend, 0 , 3);

	m_comboFrd = new KComboBox(true,m_container, "m_comboFrd");
	m_comboFrd->insertItem(i18n("Active"), -1);
	m_comboFrd->insertItem(i18n("Inactive"), -2);
	m_comboFrd->insertItem(i18n("Banned"), -3);
	
	m_compFrd = m_comboFrd->completionObject();
	connect(m_comboFrd,SIGNAL(returnPressed(const QString&)),m_compFrd,SLOT(addItem(const QString&)));
	m_layout->addWidget(m_comboFrd,1,3);
}

void FormAdminClients::setupBox()
{
	QStringList clientLabels = QStringList() << i18n("Identification");
		
	QStringList personLabels = QStringList() << i18n("Name") 
						<< i18n("Last name")
						<< i18n("Phone")
						<< i18n("Cellular")
						<< i18n("Email")
						<< i18n("Address");
	
	

	QStringList FriendLabels = QStringList() << i18n("Friend Id")
						<< i18n("Friend Name") 
						<< i18n("Friend Last name")
						<< i18n("Friend Phone")
						<< i18n("Friend Cellular")
						<< i18n("Friend Email")
						<< i18n("Friend Address");
	
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
	
	m_hashClient = this->setupGridLineEdit(box1, clientLabels, 300, clientdbFields);
	
	this->addLineEdits(box1, personLabels, m_hashPerson, 300 ,persondbFields);
	
	m_hashFriend = this->setupGridLineEdit(box2, FriendLabels, 300, friendDbFields);
	
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
	return m_radioButtonClte->selected()->text();
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
	return i18n( m_comboClte->currentText() );
}

QString FormAdminClients::getClientEmail()
{
	return m_hashPerson["email"]->text();
}

QString FormAdminClients::getClientAddress()
{
	return m_hashPerson["address"]->text();
}

void FormAdminClients::setClientId(const QString &id)
{
}

void FormAdminClients::setClientName(const QString &name)
{
}

void FormAdminClients::setClientLastName(const QString &lastname)
{
}

void FormAdminClients::setClientPhone(const QString &phone)
{
}

void FormAdminClients::setClientCellular(const QString &cell)
{
}

void FormAdminClients::setClientState(const QString &state)
{
}

void FormAdminClients::setClientEmail(const QString &email)
{
}

void FormAdminClients::setClientSex(const QString &sex)
{
}

void FormAdminClients::setClientAddress(const QString &address)
{
}


/******************************************************************************************
***************************INFO DE REFERENCIA *********************************************
*******************************************************************************************/
QString FormAdminClients::getFriendId()
{
	return m_hashFriend["docIdent"]->text();
}

QString FormAdminClients::getFriendName()
{
	return m_hashFriend["firstname"]->text();
}

QString FormAdminClients::getFriendLastName()
{
	return m_hashFriend["lastname"]->text();
}

QString FormAdminClients::getFriendPhone()
{
	return m_hashFriend["phone"]->text();
}

QString FormAdminClients::getFriendCellular()
{
	return m_hashFriend["celullar"]->text();
}

QString FormAdminClients::getFriendAddress()
{
	return m_hashFriend["address"]->text();
}

// QString FormAdminClients::getFriendState()
// {
// 	
// }

QString FormAdminClients::getFriendEmail()
{
	return m_hashFriend["email"]->text();
}

QString FormAdminClients::getFriendSex()
{
	return m_radioButtonFrd->selected()->text();
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
			if ( !KLDM )
			{
				qDebug("You're need set the database!!");
				
				return;
			}
			
			KLSelect queryExist(QStringList() << "docIdent" << "firstname",QStringList() << "ldt_persons");
			queryExist.setWhere("docIdent="+SQLSTR( this->getFriendId())+" and firstname="+SQLSTR( this->getFriendName()));
			
			KLResultSet resultSet = KLDM->execQuery(&queryExist);	
			
			m_xmlsource.setData(resultSet.toString());
			
			if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
			{
				std::cerr << "No se puede analizar" << std::endl;
				return;
			}
			
			KLSqlResults results = m_xmlreader.results();
			
			
			if(results["docIdent"] != this->getFriendId() && results["firstname"] != this->getFriendName() )
			{
				cout << "ENTRO A FORMBASE::ADD" << endl;
				KLInsert *queryFrd = new KLInsert("ldt_persons", QStringList()
							<< SQLSTR( this->getFriendId() )
							<< SQLSTR( this->getFriendName() )
							<< SQLSTR( this->getFriendLastName() )
							<< SQLSTR( this->getFriendPhone() )					
							<< SQLSTR( this->getFriendCellular() )
							<< SQLSTR( this->getFriendEmail() )
							<< SQLSTR( this->getFriendAddress() )
							<< SQLSTR( this->getFriendSex() ) );
				emit sendQuery(queryFrd);				
			}
			else
			{
				cout << "NO SE PUEDE CREAR DOS VECES LA MISMA PERSONA" << endl;

				KLInsert *queryClt2Person = new KLInsert("ldt_persons", QStringList()
							<< SQLSTR( this->getClientId() )
							<< SQLSTR( this->getClientName() )
							<< SQLSTR( this->getClientLastName() )
							<< SQLSTR( this->getClientPhone() )					
							<< SQLSTR( this->getClientCellular() )
							<< SQLSTR( this->getClientEmail() )
							<< SQLSTR( this->getClientAddress() )
							<< SQLSTR( this->getClientSex() ) );
				
				emit sendQuery(queryClt2Person);
				
				KLInsert *cliente = new KLInsert("ldt_clients", QStringList()
										<< SQLSTR( this->getClientId() )
										<< SQLSTR( this->getInscriptionDate() )
										<< SQLSTR( this->getClientState() ) 
										<< SQLSTR( this->getFriendId() ) );
				emit sendQuery(cliente);
				
				if ( this->lastQueryWasGood() )
				{
					emit accepted();
					emit inserted(this->getClientId());
					clean();
				}
			}
		}
		break;
		case FormBase::Edit:
		{
			
		}
		break;
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
	QDictIterator<KLineEdit> it3( m_hashClient );

	for( ; it1.current(); ++it1)
		it1.current()->setText("");

	for(;it2.current();++it2)
		it2.current()->setText("");

	for(;it3.current();++it3)
		it3.current()->setText("");
}

#include "formadminclients.moc"
