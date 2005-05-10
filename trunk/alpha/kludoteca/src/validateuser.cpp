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
#include "klpermission.h"
#include "kllogger.h"

ValidateUser::ValidateUser(/*KLDatabase *db, */QWidget *parent, const char *name) : KDialogBase(Tabbed, QWidget::WStyle_DialogBorder,  parent, name, true, i18n("Validate dialog"), Ok | Cancel) //, m_db(db)
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
	
	if ( KLDM->isOpen() )
		KLDM->close();
	
	KLDM->setupConnection( m_databasePage->getDatabaseName(), m_userPage->getLogin(), m_userPage->getPassword(),m_databasePage->getServer() );
	
	if ( KLDM->open() )
	{
		// El servidor pg existe y se pueden realizar conexiones!
		
		QSqlQuery q = KLDM->exec("select permissions from ldt_users where login='"+m_userPage->getLogin()+"'" );
		
		if ( q.isActive() )
		{
			QString perms = "";
			if ( q.next() )
				perms = q.value(0).toString();
			
			if (perms.length() > 0 )
			{
				klperm->string2perms(perms);
				
				LOGGER->log(i18n("The user %1 is online").arg(m_userPage->getLogin()));
				
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
	
	klapp->config("Connection")->writeEntry("Store Password", m_userPage->storePassword());
	
	if ( klapp->config("Connection")->readBoolEntry("Store Password", false) )
	{
		klapp->config("Connection")->writeEntry("Password", m_userPage->getPassword());
	}
	else
	{
		klapp->config("Connection")->writeEntry("Password", "");
	}

	klapp->config("Connection")->sync();
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

	m_storepass = new QCheckBox(i18n("Store password"), this);
	m_storepass->setChecked(klapp->config("Connection")->readBoolEntry("Store Password", false));
	
	glayout->addWidget(new QLabel(i18n("User"),this), 0,0);
	glayout->addWidget(m_user, 0, 1);
	
	glayout->addWidget(new QLabel(i18n("Password"),this), 1,0);
	glayout->addWidget(m_pass, 1, 1);
	
	glayout->addWidget(m_storepass, 2,1);
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

bool UserPage::storePassword()
{
	return m_storepass->isChecked();
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
