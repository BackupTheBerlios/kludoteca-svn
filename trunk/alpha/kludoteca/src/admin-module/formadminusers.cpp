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

FormAdminUsers::FormAdminUsers(KLDatabase *db, QWidget *parent) : FormBase(db, parent, "FormAdminUsers")
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
	
	QStringList labels = QStringList() << i18n("Login") << i18n("Password")  << i18n("First name") << i18n("Last name") << i18n("Identification") << i18n("Address") << i18n("Phone") << i18n("EMail");
	
	QStringList dbfields = QStringList() << "login" << "password"  << "firstname" << "lastname" << "docident" << "address" << "phone" << "email";

	m_lineEdits = this->setupGridLineEdit(box, labels, 600, dbfields);
	
	m_lineEdits[i18n("Login")]->setValidator(new QRegExpValidator(QRegExp("[^0-9\\s]+\\c+$"), 0));
	
// 	m_lineEdits[i18n("Permissions")]->setValidator(new QRegExpValidator(QRegExp("[0-1]{0,5}"), 0));
	
	m_lineEdits[i18n("Password")]->setEchoMode(KLineEdit::Password);
	
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
			KLInsert sqlquery("ldt_users", QStringList() << SQLSTR(this->getIdentification()) << SQLSTR(this->getLogin()) << SQLSTR(this->getFirstName()) << SQLSTR(this->getLastName()) << SQLSTR(getSex() ) << SQLSTR(this->getAddress()) << SQLSTR(this->getPhone()) << SQLSTR(this->getEmail()) << SQLSTR(this->getPermissions()));
			
			emit sendRawQuery("CREATE USER "+ this->getLogin() + " PASSWORD "+ SQLSTR(this->getPassword()) );
			
			emit sendQuery(&sqlquery);
			if ( ! this->lastQueryWasGood() )
			{
				emit sendRawQuery("DROP USER " + this->getLogin());
			}
			else
			{
				// Damos permisos necesarios
				QString perms = this->getPermissions();
				if (perms.at(0).digitValue() )
				{
					emit sendRawQuery("GRANT ALL  ON ldt_users,ldt_enterprise TO "+getLogin());
				}
				if (perms.at(1).digitValue())
				{
					emit sendRawQuery("GRANT ALL  ON ldt_clients TO "+getLogin());
				}
				if(perms.at(2).digitValue())
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games TO "+getLogin());
				}
				if (perms.at(3).digitValue())
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games,ldt_clients TO "+getLogin());
				}
				if(perms.at(4).digitValue())
				{
					emit sendRawQuery("GRANT ALL  ON ldt_games,ldt_clients,ldt_rents,ldt_participates TO "+getLogin());
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
			
			QDictIterator<KLineEdit> it( m_lineEdits );
			for( ; it.current(); ++it)
			{
				if ( it.current()->name() != QString("password")  )
				if ( it.current()->isModified() )
				{
					std::cout << "adding ." << it.current()->name() << "."<< std::endl;
					fields << it.current()->name();
					values << SQLSTR(it.current()->text());
				}
			}
			
			fields << "permissions";
			values << this->getPermissions();
			
			if ( fields.count() == values.count() && fields.count() > 0 )
			{
				KLUpdate sqlup("ldt_users", fields, values);
				sqlup.setWhere("login="+SQLSTR(getLogin()));
				
				emit sendQuery(&sqlup);
				
				if ( this->lastQueryWasGood() )
				{
					emit inserted(getLogin());
				}
			}
			
			// Now the password!!
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
	QDictIterator<KLineEdit> it( m_lineEdits );
	for( ; it.current(); ++it)
		it.current()->setText("");
}

QString FormAdminUsers::getIdentification()
{
	return m_lineEdits[i18n("Identification")]->text().remove('&');
}

QString FormAdminUsers::getLogin()
{
	return m_lineEdits[i18n("Login")]->text();
}

QString FormAdminUsers::getPassword()
{
	return m_lineEdits[i18n("Password")]->text();
}

QString FormAdminUsers::getFirstName()
{
	return m_lineEdits[i18n("First name")]->text();
}

QString FormAdminUsers::getLastName()
{
	return m_lineEdits[i18n("Last name")]->text();
} 

QString FormAdminUsers::getSex()
{
	return (static_cast<QRadioButton*>(m_radioButtons->selected()))->text();
} 

QString FormAdminUsers::getAddress()
{
	return m_lineEdits[i18n("Address")]->text();
}

QString FormAdminUsers::getPhone()
{
	return m_lineEdits[i18n("Phone")]->text();
}

QString FormAdminUsers::getEmail()
{
	return m_lineEdits[i18n("EMail")]->text();
}

QString FormAdminUsers::getPermissions()
{
	QString perms = "";
	for (uint i = 0; i < 5; i++)
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
	m_lineEdits[i18n("Identification")]->setText(ident);
}

void FormAdminUsers::setLogin(const QString &login)
{
	m_lineEdits[i18n("Login")]->setText(login);
}

void FormAdminUsers::setPassword(const QString &pass)
{
	m_lineEdits[i18n("Password")]->setText(pass);
}

void FormAdminUsers::setFirstName(const QString &fname)
{
	m_lineEdits[i18n("First name")]->setText(fname);
}

void FormAdminUsers::setLastName(const QString &lname)
{
	m_lineEdits[i18n("Last name")]->setText(lname);
}

void FormAdminUsers::setSex(const QString &sex)
{
	std::cout << "Sex: " << sex << std::endl;
	for (uint i = 0; i < 2; i++)
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
	m_lineEdits[i18n("Address")]->setText(addrs);
}

void FormAdminUsers::setPhone(const QString &phone)
{
	m_lineEdits[i18n("Phone")]->setText(phone);
}

void FormAdminUsers::setEmail(const QString &email)
{
	m_lineEdits[i18n("EMail")]->setText(email);
}

void FormAdminUsers::setPermissions(const QString &perms)
{
	std::cout << "setting up perms : " << perms << std::endl;
	for(uint i = 0; i< perms.length(); i++)
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
