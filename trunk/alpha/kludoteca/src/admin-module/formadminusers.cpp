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

#include "formadminusers.h"
#include <klocale.h>
#include <kstandarddirs.h>
#include <kmessagebox.h>
#include <qregexp.h>

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
}

void FormAdminUsers::setupButtonsBox()
{
	m_radioButtons = new QHButtonGroup(m_container);
	m_radioButtons->setLineWidth(0);
			
	m_male = new QRadioButton(i18n("Male"), m_radioButtons);
	m_female = new QRadioButton(i18n("Female"), m_radioButtons);
	m_female->setChecked(true);

	m_layout->addWidget(m_radioButtons, 0 , 2);
}

void FormAdminUsers::setupBox()
{
	QWidget *box = new QWidget(m_container);
	
	QStringList labels = QStringList() << i18n("Login") << i18n("Password")  << i18n("First name") << i18n("Last name") << i18n("Identification") << i18n("Address") << i18n("Phone") << i18n("EMail") << i18n("Permissions");

	m_lineEdits = this->setupGridLineEdit(box, labels, 600);
	
	m_lineEdits[i18n("Login")]->setValidator(new QRegExpValidator(QRegExp("[^0-9\\s]+\\c+$"), 0));
	
	m_lineEdits[i18n("Permissions")]->setValidator(new QRegExpValidator(QRegExp("[0-1]{0,5}"), 0));
	
	m_lineEdits[i18n("Password")]->setEchoMode(KLineEdit::Password);
	
	m_layout->addWidget(box, 0, 1);
}

void FormAdminUsers::accept()
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
	}
}

void FormAdminUsers::cancel() 
{
	emit cancelled();
}

QString FormAdminUsers::getIdentification()
{
	return m_lineEdits[i18n("Identification")]->text();
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
	bool ok = false;
	QString prms = m_lineEdits[i18n("Permissions")]->text();
	prms.toInt(&ok);
	
	if (! ok )
		prms = "00000";
	return prms;
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
	m_lineEdits[i18n("Email")]->setText(email);
}

void FormAdminUsers::setPermissions(const QString &perms)
{
	m_lineEdits[i18n("Permissions")]->setText(perms);
}

#include "formadminusers.moc"
