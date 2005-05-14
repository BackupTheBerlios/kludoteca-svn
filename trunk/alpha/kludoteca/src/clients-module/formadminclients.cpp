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
	m_selectFaceClte->setPixmap( QPixmap( locate("data", "kludoteca/clients-module/icons/default3.png")) );
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
	
	QStringList clientdbFields = QStringList() << "docident";
	
	QStringList persondbFields = QStringList() << "firstname" 
						<< "lastname"
						<< "phone"
						<< "celullar"
						<< "email"
						<< "address" ;
	
	QStringList friendDbFields = QStringList() << "docident"
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
	return m_hashClient["docident"]->text();
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
	m_hashClient["docident"]->setText(id);
}

void FormAdminClients::setClientName(const QString &name)
{
	m_hashPerson["firstname"]->setText(name);
}

void FormAdminClients::setClientLastName(const QString &lastname)
{
	m_hashPerson["lastname"]->setText(lastname);
}

void FormAdminClients::setClientPhone(const QString &phone)
{
	m_hashPerson["phone"]->setText(phone);
}

void FormAdminClients::setClientCellular(const QString &cell)
{
	m_hashPerson["celullar"]->setText(cell);
}



void FormAdminClients::setClientState(const QString &state)
{
	if (state == i18n("Active"))
	{
		m_comboClte->setCurrentItem(-1);
	}
	
	if (state == i18n("Inactive"))
	{
		m_comboClte->setCurrentItem(-2);
	}
	
	if (state == i18n("Banned"))
	{
		m_comboClte->setCurrentItem(-3);
	}
	
}

void FormAdminClients::setClientEmail(const QString &email)
{
	m_hashPerson["email"]->setText(email);
}

void FormAdminClients::setClientSex(QString &sex)
{
	sex.remove('&');
	std::cout << "Sex: " << sex << std::endl;
	for (uint i = 0; i < m_radioButtonClte->count(); i++)
	{
		QRadioButton *btmp = static_cast<QRadioButton *>(m_radioButtonClte->find(i));
		std::cout << "Sexo: " << btmp->text() << std::endl;;
		if ( btmp->text().lower() == sex.lower())
		{
			btmp->setChecked(true);
			break;
		}
	}		
}

void FormAdminClients::setClientAddress(const QString &address)
{
	m_hashPerson["address"]->setText(address);
}


/******************************************************************************************
***************************INFO DE REFERENCIA *********************************************
*******************************************************************************************/
QString FormAdminClients::getFriendId()
{
	return m_hashFriend["docident"]->text();
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

void FormAdminClients::setFriendId(const QString &id)
{
	m_hashFriend["docident"]->setText(id);
}

void FormAdminClients::setFriendName(const QString &name)
{
	m_hashFriend["firstname"]->setText(name);
}

void FormAdminClients::setFriendLastName(const QString &lastname)
{
	m_hashFriend["lastname"]->setText(lastname);
}

void FormAdminClients::setFriendPhone(const QString &phone)
{
	m_hashFriend["phone"]->setText(phone);
}

void FormAdminClients::setFriendCellular(const QString &cell)
{
	m_hashFriend["celullar"]->setText(cell);
}



void FormAdminClients::setFriendState(const QString &state)
{
	if (state == i18n("Active"))
	{
		m_comboClte->setCurrentItem(-1);
	}
	
	if (state == i18n("Inactive"))
	{
		m_comboClte->setCurrentItem(-2);
	}
	
	if (state == i18n("Banned"))
	{
		m_comboClte->setCurrentItem(-3);
	}
	
}

void FormAdminClients::setFriendEmail(const QString &email)
{
	m_hashFriend["email"]->setText(email);
}

void FormAdminClients::setFriendSex(QString &sex)
{
	sex.remove('&');
	std::cout << "Sex: " << sex << std::endl;
	for (uint i = 0; i < m_radioButtonClte->count(); i++)
	{
		QRadioButton *btmp = static_cast<QRadioButton *>(m_radioButtonClte->find(i));
		std::cout << "Sexo: " << btmp->text() << std::endl;;
		if ( btmp->text().lower() == sex.lower())
		{
			btmp->setChecked(true);
			break;
		}
	}		
}

void FormAdminClients::setFriendAddress(const QString &address)
{
	m_hashFriend["address"]->setText(address);
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
			
			KLSelect queryExist(QStringList() << "docident" << "firstname",QStringList() << "ldt_persons");
			queryExist.setWhere("docident="+SQLSTR( this->getFriendId())+" and firstname="+SQLSTR( this->getFriendName()));
			
			KLResultSet resultSet = KLDM->execQuery(&queryExist);	
			
			m_xmlsource.setData(resultSet.toString());
			
			if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
			{
				std::cerr << "No se puede analizar" << std::endl;
				return;
			}
			
			KLSqlResults results = m_xmlreader.results();
			
			
			if(results["docident"] != this->getFriendId() && results["firstname"] != this->getFriendName() )
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
			cout <<"ENTRA A FORMBASE::EDIT" << endl;
			bool changedIdFriend = false,changedState = false;
			QStringList fields, values,
				    fieldsClte, 
				    fieldsPerson,
				    fieldsFriend,
				    valuesClte,
				    valuesPerson,
				    valuesFriend;
					
			QDictIterator<KLineEdit> itp2c( m_hashPerson );
			QDictIterator<KLineEdit> itf( m_hashFriend );
			QDictIterator<KLineEdit> itc( m_hashClient );
			
			for( ; itc.current(); ++itc)
			{
				if ( itc.current()->isModified() )
				{
					std::cout << "adding cliente." << itc.current()->name() << "."<< std::endl;
					fieldsClte << itc.current()->name();
					valuesClte << SQLSTR(itc.current()->text());
				}
			}
			
			for( ; itp2c.current(); ++itp2c)
			{
				if ( itp2c.current()->isModified() )
				{
					if(itf.current() == m_hashPerson["state"] )
						changedState = true;
					std::cout << "adding person." << itp2c.current()->name() << "."<< std::endl;
					fieldsPerson << itp2c.current()->name();
					valuesPerson << SQLSTR(itp2c.current()->text());
				}
			}
			
			for( ; itf.current(); ++itf)
			{
				if ( itf.current()->isModified())
				{
					if(itf.current() == m_hashFriend["docident"] )
						changedIdFriend = true;
					
					std::cout << "adding ref." << itf.current()->name() << "." << itf.current()->text() << std::endl;
					fieldsFriend+=itf.current()->name();
					cout <<"TRY FILL QSTRINGLIST fields"<< endl;
					valuesFriend+=SQLSTR(itf.current()->text());
					cout <<"TRY FILL QSTRINGLISTvalues" << endl;
				}
			}
			
// 			fields+=fieldsFriend;
// 			values+=valuesFriend;
// 			
			if ( fieldsFriend.count() == valuesFriend.count() && fieldsFriend.count() > 0 )
			{
				cout <<"TRY QUERY FRIEND" << endl;
				KLUpdate sqlup("ldt_persons", fieldsFriend, valuesFriend);
				sqlup.setWhere("docident="+SQLSTR( m_hashFriend["docident"]->text() ) );
				cout <<"TRY QUERY FRIEND" << endl;
				emit sendQuery(&sqlup);
				/*
				if ( this->lastQueryWasGood() )  AKI NO NECESITAMOS MOSTRAS LOS NUEVOS
								NUEVOS VALORES EN EL LISTVIEW
				{
					emit inserted();
				}*/
			}
			
			if ( fieldsPerson.count() == valuesPerson.count() && fieldsPerson.count() > 0 )
			{
				KLUpdate sqlup("ldt_persons", fieldsPerson, valuesPerson);
				sqlup.setWhere("docident="+SQLSTR(m_hashClient["docident"]->text()));
				cout <<"TRY QUERY PERSON" << endl;
				emit sendQuery(&sqlup);				
			}
			
			if (changedIdFriend)
			{
				fieldsClte << "idreferenceperson";
				valuesClte << this->getFriendId();
			}
			if(changedState)
			{
				fieldsClte << "state";
				valuesClte << this->getClientState();
			}
			
			if ( fieldsClte.count() == valuesClte.count() && fieldsClte.count() > 0 )
			{
				KLUpdate sqlup("ldt_clients", fieldsClte, valuesClte);
				sqlup.setWhere("docident="+SQLSTR(m_hashClient["docident"]->text()));
				cout <<"TRY QUERY CLIENT" << endl;
				emit sendQuery(&sqlup);	
				
				if ( this->lastQueryWasGood() )
				{
					emit inserted(m_hashClient["docident"]->text());
					
				}			
			}
			
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

// void FormAdminClients::setFriendLineEdits(QStringList &fields, KLSqlResults &result)
// {
// 	for ( QStringList::Iterator it = fields.begin(); it != fields.end(); ++it )
// 	{
// 		cout << (QString)*it << " en el for " << endl;
// 		if ( *it )
// 		{
// 			KLineEdit *le = m_hashFriend[*it];
// 			if ( le )
// 			{
// 				le->setText(result[*it]);
// 			}
// 		}
// 	}
// }

#include "formadminclients.moc"
