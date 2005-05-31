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
 
#include <qpixmap.h>
#include <kmessagebox.h>
#include <qsqlerror.h>
#include "klfirstdialog.h"
#include <klocale.h>
#include "ldtapp.h"

KLFirstDialog::KLFirstDialog(QWidget *parent, const char *name)
	: KWizard(parent, name)
{
	m_welcome = new FDWelcome(this);
	addPage(m_welcome, i18n("Welcome !"));
	
	m_initdb = new FDInitDatabase(this);
	addPage(m_initdb, i18n("Setup database"));
	connect(m_initdb, SIGNAL(enableNext(QWidget*, bool )), this, SLOT(setNextEnabled(QWidget*, bool )));
	connect(m_initdb, SIGNAL(gotoFinish()), this, SLOT(showFinish()));
	
	m_enterprise = new FDSetupEnterprise(this);
	addPage(m_enterprise, i18n("Setup Enterprise"));
	
	m_setupAdmin = new FDSetupAdmin(this);
	addPage(m_setupAdmin, i18n("Setup admin user"));
	
	m_finish = new FDWelcome(this);
	m_finish->setMessage(i18n("<h3><b>Congratulations!</b></h3><br>" +
			i18n("You has configure the system, you can become to use it!")
			       ));
	addPage(m_finish, i18n("All is good!"));
	setFinishEnabled(m_finish, true);
	
	connect( finishButton(), SIGNAL(clicked()), this, SLOT(finished()));
	connect( cancelButton(), SIGNAL(clicked()), this, SLOT(cancel()));
}


KLFirstDialog::~KLFirstDialog()
{
}

void KLFirstDialog::cancel()
{
	// Debemos limpiar lo que se ha hecho y salir de la aplicacion
	KApplication::exit(0);
}

void KLFirstDialog::next()
{
	std::cout << "Next" << std::endl;
	
	if (currentPage() == m_welcome)
	{
		setNextEnabled(m_initdb, false);
	}
	else if ( currentPage() == m_initdb )
	{
	}
	else if (currentPage() == m_enterprise )
	{
		m_enterprise->addEnterprise();
	}
	else if ( currentPage() == m_setupAdmin)
	{
		if (! m_setupAdmin->setAdministrator())
		{
			KMessageBox::error(this, i18n("I can't create the admin account\n The error was %1").arg( KLDM->lastError().text()), i18n("Error"));
			return;
		}
	}
	KWizard::next();
}

void KLFirstDialog::finished()
{
	klapp->config()->writeEntry( "First Run", false );
	
	klapp->config("Connection")->writeEntry("Server", KLDM->hostName() );
	klapp->config("Connection")->writeEntry("Database",KLDM->databaseName() );
	klapp->config("Connection")->writeEntry("Login",KLDM->userName() );
	
	klapp->config()->sync();
}

void KLFirstDialog::showFinish()
{
	showPage(m_finish);
}

// FDWelcome
FDWelcome::FDWelcome(QWidget *parent, const char *name) : QHBox(parent, name)
{
	m_text = "<h3><b>" + QString(klapp->name()) + " " + klapp->appversion() + "</b></h3><br><br>" +
			i18n("<p>KLudoteca is a program that lets administer a gamestore easyly and fastly, thanks to choose it!</p>") +
			i18n("<p>In this dialog, you can initialize the system in a easy way, you need fill some information and you can get the system work!</p>") +
			i18n("<p>Please press the next button and complete the fields</p>") +
			i18n("<br><br><em>-- KLudoteca Team</em>");
	
	m_message= new QLabel(m_text, this);
	m_message->setMargin(10);

	(new QLabel(this))->setPixmap(QPixmap( locate("data", "kludoteca/icons/klicon.png" )) );
}

FDWelcome::~FDWelcome()
{
}

void FDWelcome::setMessage(const QString &text)
{
	m_message->setText(text);
}

// FDInitDatabase

FDInitDatabase::FDInitDatabase(QWidget *parent, const char *name) : QVBox(parent, name) 
{
	setMargin(5);
	(new QLabel( i18n("<p>In this section, you must be fill the information in the fields, for create the application database</p>"), this))->setMargin(5);
	
	m_dataBox = new QGroupBox(this);
	m_dataBox->setMargin(10);
	QGridLayout *layout = new QGridLayout(m_dataBox, 4,2,10);
	
	layout->addWidget(new QLabel(i18n("Server"), m_dataBox), 0,0);
	m_server = new KLineEdit(m_dataBox);
	layout->addWidget(m_server, 0,1);
	
	layout->addWidget(new QLabel(i18n("Database"), m_dataBox), 1,0);
	m_dbname = new KLineEdit(m_dataBox);
	m_dbname->setText("kludoteca");
	layout->addWidget(m_dbname, 1,1);
	
	
	layout->addWidget(new QLabel(i18n("Login"), m_dataBox), 2,0);
	m_login = new KLineEdit(m_dataBox);
	layout->addWidget(m_login, 2,1);
	
	
	layout->addWidget(new QLabel(i18n("Password"), m_dataBox), 3,0);
	m_passwd = new KLineEdit(m_dataBox);
	m_passwd->setEchoMode(KLineEdit::Password);
	layout->addWidget(m_passwd, 3,1);
	
	m_createButton = new KPushButton(i18n("Create the database!"), this);
	connect(m_createButton, SIGNAL(clicked()), this, SLOT(createDatabase()));
	
	m_pbar = new KProgress(this);
	
// 	KLDM = new KLDatabase();
}

FDInitDatabase::~ FDInitDatabase()
{
}

void FDInitDatabase::createDatabase()
{
	KLDM->setHostName(m_server->text());
	KLDM->setDatabaseName("template1");
	KLDM->setUserName(m_login->text());
	KLDM->setPassword(m_passwd->text());
	if ( KLDM->open() )
	{
		if ( ! checkAccount() )
		{
			KMessageBox::error(this, i18n("Your account is invalid, you need a user which can create users and databases"));
			return;
		}
		
		QSqlQuery q;
		
		q = KLDM->exec("CREATE DATABASE "+m_dbname->text());
		if ( ! q.isActive() )
		{
			int opt = KMessageBox::questionYesNo(this, i18n("I can't create %1\n The error was %2\ntry remove it?").arg(m_dbname->text()).arg((KLDM->lastError()).text()), i18n("Error"));
			
			switch( opt )
			{
				case KMessageBox::Yes:
				{
					KLDM->dropTables();
					KLDM->exec("DROP DATABASE "+m_dbname->text());
					KLDM->exec("CREATE DATABASE "+m_dbname->text()); 
					KLDM->dropTables();
				}
				break;
				case KMessageBox::No:
				{
					m_createButton->setEnabled(false);
					KLDM->setDatabaseName(m_dbname->text());
					emit gotoFinish();
					return;
				}
				break;
			}
		}
		
		KLDM->setDatabaseName(m_dbname->text());
		
		KLDM->close();
	
		if ( ! KLDM->open() )
		{
			qDebug("I can't open database: "+m_dbname->text());
		}
		
		m_pbar->setTotalSteps(7);
		connect(KLDM, SIGNAL(progress(int)), m_pbar, SLOT(setProgress(int)));
		
		if ( ! KLDM->createTables() )
		{
			KMessageBox::error(this, i18n("I can't create (all) tables in database %1").arg(KLDM->databaseName()), i18n("Error"));
			//KLDM->dropTables();
		}
		else
		{
			KMessageBox::information(this, i18n("The database %1 was create succesfully!\n").arg(KLDM->databaseName())+	i18n("You can continue to next step"));
			m_createButton->setEnabled(false);
			emit enableNext(this, true);
		}
	}
	else
	{
		KMessageBox::error(this, i18n("I can't open the database!\n"
				"The error was %1").arg( (KLDM->lastError()).text())  , i18n("Error"));
	}
	
// 	if ( KLDM->isOpen())
// 		KLDM->close();
}

bool FDInitDatabase::checkAccount()
{
	if ( ! KLDM->isOpen() )
	{
		KLDM->open();
	}
	
	KLDM->exec("CREATE USER kltestuser");
	QSqlQuery q = KLDM->exec("DROP USER kltestuser");
	
	if ( q.isActive() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Class FDSetupEnterprise
FDSetupEnterprise::FDSetupEnterprise(QWidget *parent, const char *name) : QVBox(parent, name)
{
	(new QLabel( i18n("<p>In this dialog, you must be fill the information in the fields, for setup your bussyness.</p>"), this))->setMargin(5);
	m_dataBox = new QGroupBox(this);
	
	m_dataBox->setMargin(10);
	QGridLayout *layout = new QGridLayout(m_dataBox, 4, 3,10);
	
	layout->addWidget(new QLabel(i18n("Name"), m_dataBox), 0, 0);
	m_name = new KLineEdit(m_dataBox);
	layout->addWidget(m_name, 0,1);
	
	layout->addWidget(new QLabel(i18n("NIT"), m_dataBox), 1,0);
	m_nit = new KLineEdit(m_dataBox);
	layout->addWidget(m_nit, 1,1);
	
	
	layout->addWidget(new QLabel(i18n("City"), m_dataBox), 2,0);
	m_city = new KLineEdit(m_dataBox);
	layout->addWidget(m_city, 2,1);

	layout->addWidget(new QLabel(i18n("Address"), m_dataBox),3,0);
	m_address = new KLineEdit(m_dataBox);
	layout->addWidget(m_address, 3,1);
	
	layout->addWidget(new QLabel(i18n("Phone"), m_dataBox), 4,0);
	m_phone = new KLineEdit(m_dataBox);
	m_phone->setText("");
	layout->addWidget(m_phone, 4,1);
}


FDSetupEnterprise::~FDSetupEnterprise()
{
}

void FDSetupEnterprise::addEnterprise()
{
	QStringList data = QStringList() << SQLSTR(m_nit->text()) << SQLSTR(m_address->text()) << SQLSTR(m_name->text()) << SQLSTR(m_phone->text()) << SQLSTR(m_city->text());
	KLInsert sql("ldt_enterprise", data);
	
	KLDM->execQuery(&sql);
	
	if ( KLDM->isLastError() )
	{
		KMessageBox::detailedSorry (0, i18n("I create your enterprise :("), KLDM->getLastError() );
	}
}


// Class FDSetupAdmin

FDSetupAdmin::FDSetupAdmin(QWidget *parent, const char *name) : QVBox(parent, name)
{
	(new QLabel( i18n("<p>In this dialog, you must be fill the information in the fields, for setup your admin account.</p>"), this))->setMargin(5);
	
	m_dataBox = new QGroupBox(this);
	m_dataBox->setMargin(10);
	QGridLayout *layout = new QGridLayout(m_dataBox, 4, 3,10);
	
	layout->addWidget(new QLabel(i18n("First name"), m_dataBox), 0, 0);
	m_fname = new KLineEdit(m_dataBox);
	layout->addWidget(m_fname, 0,1);
	
	m_sexBox= new QHButtonGroup(m_dataBox);
	m_malesex = new QRadioButton(i18n("male"), m_sexBox);
	
	m_femalesex = new QRadioButton(i18n("female"), m_sexBox);
	m_femalesex->setChecked(true);
	
	layout->addWidget(m_sexBox, 0,2);
	
	layout->addWidget(new QLabel(i18n("Last name"), m_dataBox), 1,0);
	m_lname = new KLineEdit(m_dataBox);
	layout->addWidget(m_lname, 1,1);
	
	layout->addWidget(new QLabel(i18n("Identification"), m_dataBox), 2,0);
	m_docident = new KLineEdit(m_dataBox);
	layout->addWidget(m_docident, 2,1);

	layout->addWidget(new QLabel(i18n("Address"), m_dataBox),3,0);
	m_address = new KLineEdit(m_dataBox);
	layout->addWidget(m_address, 3,1);
	
	layout->addWidget(new QLabel(i18n("Phone"), m_dataBox), 4,0);
	m_phone = new KLineEdit(m_dataBox);
	m_phone->setText("");
	layout->addWidget(m_phone, 4,1);
	
	
	layout->addWidget(new QLabel(i18n("Email"), m_dataBox), 5,0);
	m_email = new KLineEdit(m_dataBox);
	layout->addWidget(m_email, 5,1);
}

FDSetupAdmin::~FDSetupAdmin()
{
}

bool FDSetupAdmin::setAdministrator()
{
	std::cout << KLDM->databaseName() << std::endl;
	
	QString sex;
	
	if ( m_sexBox->selectedId() == 0)
		sex = 'm';
	else
		sex = 'f';
	
	KLDM->execQuery(new KLInsert( "ldt_persons", 
		      QStringList() << SQLSTR(m_docident->text()) 
				      << SQLSTR(m_fname->text()) 
				      << SQLSTR(m_lname->text()) 
				      << SQLSTR(m_phone->text()) 
				      << SQLSTR(m_phone->text()) 
				      << SQLSTR(m_email->text())  
				      << SQLSTR(m_address->text()) 
				      << SQLSTR(sex)));
	
	KLDM->execQuery(new KLInsert("ldt_users", QStringList()  << SQLSTR(m_docident->text()) << SQLSTR(KLDM->userName()) << SQLSTR("11111")));

	if ( KLDM->isLastError())
	{
		return false;
	}
	return true;
}

#include "klfirstdialog.moc"
