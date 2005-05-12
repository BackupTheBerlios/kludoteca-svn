/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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
#include "participantslist.h"
#include <klocale.h>

#define DEBUG_PARTICIPANTS 0

ParticipantsList::ParticipantsList(QWidget *parent, const char *name) : LTListView(QStringList() << i18n("Tournament") << i18n("Client") << i18n("Rank"), LTListView::ButtonAdd, LTListView::ButtonModify, LTListView::ButtonModify, LTListView::NoButton, parent, name)
{
	setCaption(i18n("Participants"));
}


ParticipantsList::~ParticipantsList()
{
}


void ParticipantsList::fillList()
{
#if DEBUG_PARTICIPANTS
	qDebug("Fill List");
#endif
	
// 	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users_view");
// 	
// 	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
// 	
// 	m_xmlsource.setData(resultSet.toString());
// 	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
// 	{
// 		std::cout << "No se pudo analizar!!!" << std::endl;
// 	}
}

void ParticipantsList::addButtonClicked()
{
#if DEBUG_PARTICIPANTS
	qDebug("init addButtonClicked");
#endif
// 	KMdiChildView *view = new KMdiChildView(i18n("Add user"), this );
// 	( new QVBoxLayout( view ) )->setAutoAdd( true );
// 
// 	QScrollView *scroll = new QScrollView(view);
// 	scroll->setResizePolicy(QScrollView::AutoOneFit);
// 	scroll->setMargin(10);
// 	
// 	FormParticipantsList *formParticipantsList = new FormParticipantsList(FormBase::Add, scroll->viewport() );
// 	connect(formParticipantsList, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
// 
// 	formParticipantsList->setType( FormBase::Add);
// 	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
// 	connect(formParticipantsList, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
// 
// 	scroll->addChild(formParticipantsList);
// 	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
// 
// 	formParticipantsList->setTitle(i18n("Admin User"));
// 	formParticipantsList->setExplanation(i18n("Fill the fields with the user information"));
// 	
// 	emit sendWidget(view); 
#if DEBUG_PARTICIPANTS
	qDebug("end addButtonClicked");
#endif
}

void ParticipantsList::delButtonClicked()
{
// 	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
// 	
// 	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete the user ")+itemp->text(2)+ " ?");
// 	
// 	if (opt == KMessageBox::Yes )
// 	{
// 		KLDM->execRawQuery("delete from ldt_users where login="+ SQLSTR(itemp->text(2)));
// 		
// 		KLDM->execRawQuery("drop user "+itemp->text(2));
// 		
// 		delete itemp;
// 		
// 		emit message2osd(i18n("The user has been deleted!!"));
// 	}
}

void ParticipantsList::getClickedItem(QListViewItem *item)
{
	modifyButtonClicked();
}

void ParticipantsList::modifyButtonClicked()
{
#if DEBUG_PARTICIPANTS
	qDebug("init modifyButtonClicked");
#endif
// 	KMdiChildView *view = new KMdiChildView(i18n("Modify user"), this );
// 	( new QVBoxLayout( view ) )->setAutoAdd( true );
// 
// 	QScrollView *scroll = new QScrollView(view);
// 	scroll->setResizePolicy(QScrollView::AutoOneFit);
// 	scroll->setMargin(10);
// 	
// 	FormParticipantsList *formParticipantsList = new FormParticipantsList(FormBase::Edit, scroll->viewport() );
// 	
// 	connect(formParticipantsList, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
// 
// 	KLSelect sqlquery(QStringList() << "ldt_users.docident" << "login" << "firstname" << "lastname" << "genre" << "address" << "phone" << "email" << "permissions", QStringList() << "ldt_users" << "ldt_persons" );
// 	
// 	sqlquery.setWhere("ldt_persons.docIdent=ldt_users.docIdent and login="+SQLSTR(m_listView->currentItem()->text(2))); // Login in the listview
// 	
// 	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
// 	
// 	m_xmlsource.setData(resultSet.toString());
// 	
// 	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
// 	{
// 		std::cerr << "No se puede analizar" << std::endl;
// 		return;
// 	}
// 	
// 	KLSqlResults results = m_xmlreader.results();
// 	
// 	std::cout << results["login"] << std::endl;
// 
// 	formParticipantsList->setAddress( results["address"] );
// 	formParticipantsList->setEmail(results["email"]);
// 	formParticipantsList->setFirstName( results["firstname"]);
// 	formParticipantsList->setIdentification( results["ldt_users.docident"]);
// 	formParticipantsList->setLastName( results["lastname"]);
// 	formParticipantsList->setLogin( results["login"]);
// 	formParticipantsList->setPermissions( results["permissions"]);
// 	formParticipantsList->setPhone( results["phone"]);
// 	formParticipantsList->setGenre( results["genre"]);
// 	
// 	formParticipantsList->setType( FormBase::Edit );
// 	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
// 	connect(formParticipantsList, SIGNAL(inserted(const QString& )), this, SLOT(updateItem(const QString &)));
// 
// 	scroll->addChild(formParticipantsList);
// 	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
// 	formParticipantsList->setTextAcceptButton(i18n("Modify"));
// 	formParticipantsList->setTextCancelButton(i18n("Close"));
// 	formParticipantsList->setTitle(i18n("Admin User"));
// 	formParticipantsList->setExplanation(i18n("Modify the fields with the user information"));
// 	
// 	emit sendWidget(view);
#if DEBUG_PARTICIPANTS
	qDebug("end addButtonClicked");
#endif
}

void ParticipantsList::queryButtonClicked()
{
// 	QString quering = "";
// 	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
// 	
// 	quering += i18n("== query to user ") + itemp->text(2) + " == \n";
// 	// select firstname,lastname,docident,address,phone,email,permissions from ldt_users,ldt_persons where ldt_persons.docIdent=ldt_users.docIdent and login='usuario'
// 	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "ldt_users.docident" << "address" << "phone" << "email" << "permissions", QStringList() << "ldt_users" << "ldt_persons" );
// 	sqlquery.setWhere("ldt_persons.docIdent=ldt_users.docIdent and login="+SQLSTR(m_listView->currentItem()->text(2)));
// 	
// 	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
// 	
// 	m_xmlsource.setData(resultSet.toString());
// 	
// 	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total ))
// 	{
// 		std::cout << "No se pudo analizar!!!" << std::endl;
// 	}
// 	
// 	KLSqlResults results = m_xmlreader.results();
// 	
// 	quering += i18n("Real name: ") + results["firstname"] + " " + results["lastname"] + "\n";
// 	quering += i18n("Identification: ") + results["ldt_users.docident"] + "\n";
// 	quering += i18n("Address: ") + results["address"] + "\n";
// 	quering += i18n("Phone: ") + results["phone"] + "\n";
// 	quering += i18n("Email: ") + results["email"] + "\n";
// 	quering += i18n("Permissions:") + results["permissions"] + "\n\n";
// 	
// 	emit message2osd(quering);
}

void ParticipantsList::addItem(const QString &pkey)
{
// 	std::cout << "Adicionando item con pkey: " << pkey << std::endl;
// 	
// 	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users_view");
// 	sqlquery.setWhere("login="+SQLSTR(pkey) );
// 
// 	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
// 
// 	m_xmlsource.setData(resultSet.toString());
// 	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
// 	{
// 		std::cout << "No se pudo analizar!!!" << std::endl;
// 	}
}

void ParticipantsList::updateItem(const QString &pkey)
{
// 	delete m_listView->currentItem();
// 	addItem(pkey);
}

void ParticipantsList::slotFilter(const QString &filter)
{
// 	std::cout << "Filtrando filter " << filter << std::endl;
// 	
// 	if ( filter.isEmpty() )
// 	{
// 		fillList();
// 	}
// 	else
// 	{
// 		KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users_view");
// 
// 		sqlquery.addFilter(filter);
// 		
// 		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
// 	
// 		m_xmlsource.setData(resultSet.toString());
// 		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
// 		{
// 			std::cout << "No se pudo analizar!!!" << std::endl;
// 		}
// 	}
}

#include "participantslist.moc"
