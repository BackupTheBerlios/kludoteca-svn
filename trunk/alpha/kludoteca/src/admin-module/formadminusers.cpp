/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
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

#include "formadminusers.h"
#include <klocale.h>
#include <kstandarddirs.h>
#include <kmessagebox.h>
#include <qregexp.h>
#include <kseparator.h>

FormAdminUsers::FormAdminUsers(FormBase::Type t, QWidget *parent) : FormBase(t, parent, "FormAdminUsers"), m_docIdent("")
{
	setupForm();
}

FormAdminUsers::~FormAdminUsers()
{
}

void FormAdminUsers::setupForm()
{
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());
	
	m_secondCol = new QVBox(m_container);

	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2, m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(3);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10); 
	m_layout = new QGridLayout(m_container, 1, 3, 2, 2);
	m_layout->setAlignment(Qt::AlignCenter );

	setupButtonsBox();
	setupBox();

	m_layout->setColStretch(2, 10);
	
	QLabel *img = new QLabel("", m_container);
	img->setScaledContents ( true );
	img->setFrameStyle( QFrame::Panel | QFrame::Raised );
	img->setLineWidth( 2 );
	img->setPixmap(QPixmap(locate("data", "kludoteca/admin-module/pics/imgformusers.png")));
	
	m_layout->addWidget(img, 0, 0);

	m_layout->addWidget(m_secondCol, 0 , 2);
}

void FormAdminUsers::setupButtonsBox()
{
	std::cout << "Setup buttons" << std::endl;
	m_radioButtons = new QVButtonGroup(m_secondCol);
	m_radioButtons->setLineWidth(0);
			
	m_male = new QRadioButton(i18n("Male"), m_radioButtons);
	m_radioButtons->insert(m_male, 0);
	m_female = new QRadioButton(i18n("Female"), m_radioButtons);
	m_radioButtons->insert(m_female,1);
	m_female->setChecked(true);
}

void FormAdminUsers::setupBox()
{
	std::cout << "Setup box" << std::endl;
	QWidget *box = new QWidget(m_container);
	
	QStringList userLabels = QStringList() << i18n("Login") << i18n("Password");
	QStringList userdbfields = QStringList() << "login" << "password";
	
	m_userFields = this->setupGridLineEdit(box, userLabels, 600, userdbfields);
			
	QStringList personLabels = QStringList() << i18n("First name") << i18n("Last name") << i18n("Identification") << i18n("Address") << i18n("Phone") << i18n("EMail");
	
	QStringList persondbfields = QStringList() << "firstname" << "lastname" << "docident" << "address" << "phone" << "email";

	std::cout << "add lineedits"<< std::endl;
	this->addLineEdits(box, personLabels, m_personFields, 600, persondbfields);
	
	m_userFields["login"]->setValidator(new QRegExpValidator(QRegExp("[^0-9\\s]+\\c+$"), 0));
	if ( getType() == FormBase::Edit )
	{
		m_userFields["login"]->setReadOnly(true);
	}
	
			
// 	m_personFields[i18n("Permissions")]->setValidator(new QRegExpValidator(QRegExp("[0-1]{0,5}"), 0));
	
	m_userFields["password"]->setEchoMode(KLineEdit::Password);
	
// 	KSeparator *sep = new KSeparator(KSeparator::HLine, m_container);
	// 	
// 	m_layout->addWidget(sep, 1,1);
	
	setupPermissionsBox();
	
	m_layout->addWidget(box, 0, 1);
}

void FormAdminUsers::setupPermissionsBox()
{
	std::cout << "Setup permissions" << std::endl;
	m_permsBox = new QVButtonGroup(m_secondCol);
	m_permsBox->setLineWidth(0);

	m_adminp = new QCheckBox(i18n("Admin module"), m_permsBox);
	m_permsBox->insert(m_adminp, 0);
	m_clientsp = new QCheckBox(i18n("Clients module"), m_permsBox);
	m_permsBox->insert(m_clientsp, 1);
	m_gamesp = new QCheckBox(i18n("Games module"), m_permsBox);
	m_permsBox->insert(m_gamesp, 2);
	m_rentsp = new QCheckBox(i18n("Rents module"), m_permsBox);
	m_permsBox->insert(m_rentsp, 3);
	m_tournamentsp = new QCheckBox(i18n("Tournament module"), m_permsBox);
	m_permsBox->insert(m_tournamentsp, 4);
}

void FormAdminUsers::accept()
{
	if ( getLogin().length() < 3)
	{
		std::cout << "El login debe ser mayor de 3 caracteres" << std::endl;
		return;
	}
	
	switch( getType() )
	{
		case FormBase::Add:
		{
			// Primero añadimos la persona y no me importa si puede o no y luego el usuario
			KLInsert *sqlquery = new KLInsert("ldt_persons", QStringList()
				<< SQLSTR(this->getIdentification()) 
				<< SQLSTR(this->getFirstName()) 
				<< SQLSTR(this->getLastName()) 
				<< SQLSTR(this->getPhone()) 
				<< SQLSTR(this->getPhone()) // TODO: add celullar field
				<< SQLSTR(this->getEmail())
				<< SQLSTR(this->getAddress())
				<< SQLSTR(getGenre() ));
			
			emit sendQuery(sqlquery); // No importa si puede o no
			
			sqlquery = new KLInsert ("ldt_users", QStringList() << SQLSTR(this->getIdentification()) << SQLSTR(this->getLogin())  << SQLSTR(this->getPermissions()));
			
			emit sendRawQuery("CREATE USER "+ this->getLogin() + " PASSWORD "+ SQLSTR(this->getPassword()) );
			
			emit sendQuery(sqlquery);
			if ( ! this->lastQueryWasGood() )
			{
				emit sendRawQuery("DROP USER " + this->getLogin());
			}
			else
			{
				// Damos permisos necesarios
				
				emit sendRawQuery("GRANT SELECT ON ldt_users,ldt_enterprise TO "+getLogin());
				
				QString perms = this->getPermissions();
				// Admin
				if (perms.at(0).digitValue() )
				{
					emit sendRawQuery("GRANT ALL  ON ldt_users,ldt_enterprise,ldt_persons,ldt_users_view TO "+getLogin());
				}
				if (perms.at(1).digitValue()) // clientes
				{
					emit sendRawQuery("GRANT ALL  ON ldt_persons, ldt_clients, ldt_clients_view TO "+getLogin());
				}
				if(perms.at(2).digitValue()) // juegos
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games TO "+getLogin());
				}
				if (perms.at(3).digitValue()) // rentas
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games,ldt_rents,ldt_rents_view,ldt_clients,ldt_persons, ldt_clients_view TO "+getLogin());
				}
				if(perms.at(4).digitValue()) // torneos
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games,ldt_clients, ldt_clients_view,ldt_rents,ldt_rents_view, ldt_match, ldt_rounds,ldt_participates,ldt_tournament, ldt_tournament_view TO "+getLogin());
				}
				
				emit inserted(getLogin());
				
				emit message2osd(i18n("The user "+ getLogin() +" has been added"));
				clean();
			}
		}
		break;
		case FormBase::Edit:
		{
			QStringList fields, values;
			
			QDictIterator<KLineEdit> it( m_personFields );
			for( ; it.current(); ++it)
			{
				if ( it.current()->isModified() )
				{
					std::cout << "adding ." << it.current()->name() << "."<< std::endl;
					fields << it.current()->name();
					values << SQLSTR(it.current()->text());
				}
			}
			
			if ( fields.count() == values.count() && fields.count() > 0 )
			{
				KLUpdate sqlup("ldt_persons", fields, values);
				sqlup.setWhere("docIdent="+SQLSTR(m_docIdent));
				
				emit sendQuery(&sqlup);
				
				if ( this->lastQueryWasGood() )
				{
					emit inserted(getLogin());
				}
			}
			
			
			
// 			fields << "permissions";
// 			values << this->getPermissions();
			
			// Now the password!!
			if ( m_userFields["password"]->isModified() )
				emit sendRawQuery("alter user " + getLogin() + " WITH PASSWORD " + SQLSTR(getPassword()));
			
			emit message2osd(i18n("The changes to " + getLogin() + " was taken"));
			
			clean();
		}
		break;
	}
}

void FormAdminUsers::cancel()
{
	emit cancelled();
}

void FormAdminUsers::clean()
{
	QDictIterator<KLineEdit> it( m_personFields );
	for( ; it.current(); ++it)
		it.current()->setText("");
	
	QDictIterator<KLineEdit> it2( m_userFields );
	for( ; it2.current(); ++it2)
		it2.current()->setText("");
	
	for (uint i = 0; i < m_permsBox->count(); i++)
	{
		static_cast<QCheckBox *>(m_permsBox->find(i))->setChecked(false);
	}
}

QString FormAdminUsers::getIdentification()
{
	return m_personFields["docident"]->text().remove('&');
}

QString FormAdminUsers::getLogin()
{
	return m_userFields["login"]->text();
}

QString FormAdminUsers::getPassword()
{
	return m_userFields["password"]->text();
}

QString FormAdminUsers::getFirstName()
{
	return m_personFields["firstname"]->text();
}

QString FormAdminUsers::getLastName()
{
	return m_personFields["lastname"]->text();
} 

QString FormAdminUsers::getGenre()
{
	QString tsex = (static_cast<QRadioButton*>(m_radioButtons->selected()))->text();
	
	tsex.remove('&');
	return tsex.lower();
} 

QString FormAdminUsers::getAddress()
{
	return m_personFields["address"]->text();
}

QString FormAdminUsers::getPhone()
{
	return m_personFields["phone"]->text();
}

QString FormAdminUsers::getEmail()
{
	return m_personFields["email"]->text();
}

QString FormAdminUsers::getPermissions()
{
	QString perms = "";
	for (uint i = 0; i < m_permsBox->count(); i++)
	{
		if ( static_cast<QCheckBox *>(m_permsBox->find(i))->isChecked() )
		{
			perms += "1";
		}
		else
		{
			perms += "0";
		}
	}
	
	std::cout << "Getting perms: " << perms << std::endl;
	
	return perms;
}
		
void FormAdminUsers::setIdentification(const QString &ident)
{
	m_docIdent = ident;
	m_personFields["docident"]->setText(ident);
}

void FormAdminUsers::setLogin(const QString &login)
{
	m_userFields["login"]->setText(login);
}

void FormAdminUsers::setPassword(const QString &pass)
{
	m_userFields["password"]->setText(pass);
}

void FormAdminUsers::setFirstName(const QString &fname)
{
	m_personFields["firstname"]->setText(fname);
}

void FormAdminUsers::setLastName(const QString &lname)
{
	m_personFields["lastname"]->setText(lname);
}

void FormAdminUsers::setGenre(QString &sex)
{
	sex.remove('&');
	std::cout << "Sex: " << sex << std::endl;
	for (uint i = 0; i < m_radioButtons->count(); i++)
	{
		QRadioButton *btmp = static_cast<QRadioButton *>(m_radioButtons->find(i));
		std::cout << "Sexo: " << btmp->text() << std::endl;;
		if ( btmp->text().lower() == sex.lower())
		{
			btmp->setChecked(true);
			break;
		}
	}
}

void FormAdminUsers::setAddress(const QString &addrs)
{
	m_personFields["address"]->setText(addrs);
}

void FormAdminUsers::setPhone(const QString &phone)
{
	m_personFields["phone"]->setText(phone);
}

void FormAdminUsers::setEmail(const QString &email)
{
	m_personFields["email"]->setText(email);
}

void FormAdminUsers::setPermissions(const QString &perms)
{
	std::cout << "setting up perms : " << perms << std::endl;
	for(uint i = 0; i < perms.length(); i++)
	{
		if ( perms.at(i) == '1')
		{
			static_cast<QCheckBox *>(m_permsBox->find(i))->setChecked(true);
		}
		else
		{
			static_cast<QCheckBox *>(m_permsBox->find(i))->setChecked(false);
		}
	}
}

#include "formadminusers.moc"
