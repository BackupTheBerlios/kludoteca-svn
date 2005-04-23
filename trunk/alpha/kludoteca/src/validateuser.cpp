/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                           	   *
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
#include "validateuser.h"
#include <klocale.h>
#include <qlabel.h>
#include <kmessagebox.h>

ValidateUser::ValidateUser(KLDatabase *db, QWidget *parent, const char *name) : KDialogBase(Tabbed, QWidget::WStyle_DialogBorder,  parent, name, true, i18n("Validate dialog"), Ok | Cancel), m_db(db), m_activeAdminModule(false), m_activeRentsModule(false), m_activeTournamentModule(false), m_activeClientsModule(false), m_activeGamesModule(false)
{
	QVBox *vbox;
	 
	vbox = addVBoxPage(i18n("User"), i18n("Choose your user"));
	m_userPage = new UserPage (vbox);
	
	vbox = addVBoxPage(i18n("Database"), i18n("Setup your database connection"));
	m_databasePage = new DatabasePage(vbox);
}


ValidateUser::~ValidateUser()
{
}

void ValidateUser::slotOk()
{
// 	std::cout << "Setup database with: " << m_databasePage->getDatabaseName() << " and " << m_databasePage->getServer() << std::endl;
	
	m_db->setupConnection( m_databasePage->getDatabaseName(), m_userPage->getLogin(), m_userPage->getPassword(),m_databasePage->getServer() );
	
	if ( m_db->open() )
	{
		// El servidor pg existe y se pueden realizar conexiones!
		
		QSqlQuery q = m_db->exec("select permissions from ldt_users where login='"+m_userPage->getLogin()+"'" );
		
		if ( q.isActive() )
		{
			QString perms = "";
			if ( q.next() )
				perms = q.value(0).toString();
			
			if (perms.length() > 0 )
			{
				this->string2perms(perms);
				KDialogBase::slotOk();
				writeConfig();
			}
			else
			{
				KMessageBox::error(this, i18n("You need a kludoteca account! Talk with the system administer."));
			}
		}
		else
		{
			KMessageBox::error(this, i18n("Login or password incorrect"));
		}
	}
	else
	{
		KMessageBox::error(this, i18n("I can't connect to database server."));
	}
}

void ValidateUser::writeConfig()
{
	klapp->config("Connection")->writeEntry("Server", m_databasePage->getServer());
	klapp->config("Connection")->writeEntry("Database", m_databasePage->getDatabaseName());
	klapp->config("Connection")->writeEntry("Login", m_userPage->getLogin());
	if ( klapp->config()->readBoolEntry("Store Password", false) )
	{
		klapp->config("Connection")->writeEntry("Password", m_userPage->getPassword());
	}
}

void ValidateUser::string2perms(const QString &str)
{
	m_activeAdminModule = str.at(0).digitValue();
	m_activeClientsModule = str.at(1).digitValue();
	m_activeGamesModule = str.at(2).digitValue();
	m_activeRentsModule = str.at(3).digitValue();
	m_activeTournamentModule = str.at(4).digitValue();
	
}

bool ValidateUser::activeAdminModule()
{
	return m_activeAdminModule;
}

bool ValidateUser::activeClientsModule()
{
	return m_activeClientsModule;
}

bool ValidateUser::activeGamesModule()
{
	return m_activeGamesModule;
}

bool ValidateUser::activeRentsModule()
{
	return m_activeRentsModule;
}

bool ValidateUser::activeTournamentModule()
{
	return m_activeTournamentModule;
}

// User Page

UserPage::UserPage(QWidget *parent) : QFrame(parent)
{
	QGridLayout *glayout = new QGridLayout(this, 3, 3, 10);
	
	m_user = new KLineEdit(this);
	m_user->setText(klapp->config("Connection")->readEntry("Login"));
	m_pass = new KLineEdit(this);
	m_pass->setEchoMode( KLineEdit::Password );
	m_pass->setText(klapp->config("Connection")->readEntry("Password"));

	glayout->addWidget(new QLabel(i18n("User"),this), 0,0);
	glayout->addWidget(m_user, 0, 1);
	
	glayout->addWidget(new QLabel(i18n("Password"),this), 1,0);
	glayout->addWidget(m_pass, 1, 1);
}

UserPage::~UserPage()
{
}

QString UserPage::getLogin()
{
	return m_user->text();
}

QString UserPage::getPassword()
{
	return m_pass->text();
}


// Database Page

DatabasePage::DatabasePage(QWidget *parent) : QFrame(parent)
{
	QGridLayout *glayout = new QGridLayout(this, 3, 3, 10);
	
	m_server = new KLineEdit(this);
	
	m_server->setText(klapp->config("Connection")->readEntry("Server", "localhost"));

	m_database = new KLineEdit(this);
	m_database->setText(klapp->config("Connection")->readEntry("Database", "kludoteca"));
	
	glayout->addWidget(new QLabel(i18n("Server: "), this), 0,0);
	glayout->addWidget(m_server , 0,1);
	
	glayout->addWidget(new QLabel(i18n("Database"),this), 1,0);
	glayout->addWidget(m_database, 1, 1);
}

DatabasePage::~ DatabasePage()
{
}

QString DatabasePage::getServer()
{
	return m_server->text();
}

QString DatabasePage::getDatabaseName()
{
	return m_database->text();
}

#include "validateuser.moc"
