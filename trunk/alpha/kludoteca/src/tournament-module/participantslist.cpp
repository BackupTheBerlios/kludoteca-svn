/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                 	   *
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

#define DEBUG_PARTICIPANTS 1

ParticipantsList::ParticipantsList(QWidget *parent, const char *name) : LTListView(QStringList() << i18n("Tournament") << i18n("Client") << i18n("Rank"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent, name)
{
	setCaption(i18n("Participants"));
	m_listView->setRootIsDecorated(true);
	this->setButtonText(LTListView::ButtonAdd, i18n("Manage"));
}


ParticipantsList::~ParticipantsList()
{
}

// Debo llenar la lista separada por torneo.
void ParticipantsList::fillList()
{
#if DEBUG_PARTICIPANTS
	qDebug("Fill List");
#endif
	m_listView->clear();
	// SELECT codtournament from ldt_participates where codtournament in (select name from ldt_tournament );
	KLSelect sqltour (QStringList()  << "name", QString("ldt_tournament"));
	
	KLResultSet tourResults = KLDM->execQuery(&sqltour);
	m_xmlsource.setData(tourResults.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	QStringList tournaments = m_xmlreader.getResultsList();
	
	// Es hora de adicionar los elementos a la lista
	for (uint i = 0; i < tournaments.count(); i++)
	{
		KListViewItem *tourtemp = new KListViewItem(m_listView);
		tourtemp->setText(0, tournaments[i]);
// 		tourtemp->setOpen(true);
		
		KLSelect sqlquery(QStringList() << "clientdocident" << "rank", QStringList() << "ldt_participates");
		sqlquery.setWhere("codtournament="+SQLSTR(tournaments[i]));
	
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
		
		QStringList participants = m_xmlreader.getResultsList();
		
		for (uint j = 0; j < participants.count(); j+=2)
		{
			std::cout << "Adicionando: " << participants[j] << std::endl;
			KListViewItem *parttemp = new KListViewItem(tourtemp);

			parttemp->setText(1, participants[j]);
			parttemp->setText(2, participants[j+1]);
			tourtemp->insertItem(parttemp);
		}
	}
}

void ParticipantsList::addButtonClicked()
{
#if DEBUG_PARTICIPANTS
	qDebug("init addButtonClicked");
#endif

	QListViewItem *le = m_listView->currentItem();
	if ( !le )
		return;
	
	QString tname = le->text(0);
	if ( tname.isNull() )
		tname = le->parent()->text(0);
	
	std::cout << "Adicionando participantes torneo: " << tname << std::endl;
	
	

	KMdiChildView *view = new KMdiChildView(i18n("Add participants to %1").arg(tname), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormParticipants *formParticipantsList = new FormParticipants(tname, FormBase::Any, scroll->viewport() );
	formParticipantsList->fillTableInformation();
	connect(formParticipantsList, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formParticipantsList, SIGNAL(accepted()), this, SLOT(fillList()));

	scroll->addChild(formParticipantsList);
	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );

	formParticipantsList->setTitle(i18n("Admin %1 Participants").arg(tname));
	formParticipantsList->setExplanation(i18n("Fill the fields with the participants information"));
	
	emit sendWidget(view); 
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

// 	QListViewItem *le = m_listView->currentItem();
// 	if ( !le )
// 		return;
// 	
// 	QString tname = le->text(0);
// 	if ( tname.isNull() )
// 		tname = le->parent()->text(0);
// 	std::cout << "Adicionando participantes torneo: " << tname << std::endl;
// 	
// 	KMdiChildView *view = new KMdiChildView(i18n("Modify participants"), this );
// 	( new QVBoxLayout( view ) )->setAutoAdd( true );
// 
// 	QScrollView *scroll = new QScrollView(view);
// 	scroll->setResizePolicy(QScrollView::AutoOneFit);
// 	scroll->setMargin(10);
// 	
// 	FormParticipants *formParticipantsList = new FormParticipants(tname, FormBase::Edit, scroll->viewport() );
// 	formParticipantsList->fillTableInformation();
// 	connect(formParticipantsList, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
// 	
// 	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
// 	connect(formParticipantsList, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
// 
// 	scroll->addChild(formParticipantsList);
// 	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
// 
// 	formParticipantsList->setTitle(i18n("Modify Participants of the tournament %1").arg(tname));
// 	formParticipantsList->setExplanation(i18n("Fill the fields with the participants information"));
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
	std::cout << "Adicionando item con pkey: " << pkey << std::endl;
	
	fillList();
}

void ParticipantsList::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}

void ParticipantsList::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		m_listView->clear();
		KLSelect sqltour (QStringList()  << "name", QString("ldt_tournament"));
	
		KLResultSet tourResults = KLDM->execQuery(&sqltour);
		m_xmlsource.setData(tourResults.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
	
		QStringList tournaments = m_xmlreader.getResultsList();
	
		// Es hora de adicionar los elementos a la lista
		for (uint i = 0; i < tournaments.count(); i++)
		{
			KListViewItem *tourtemp = new KListViewItem(m_listView);
			tourtemp->setText(0, tournaments[i]);
		
			KLSelect sqlquery(QStringList() << "clientdocident" << "rank", QStringList() << "ldt_participates");
			sqlquery.setWhere("codtournament="+SQLSTR(tournaments[i]));
// 			sqlquery.addFilter(filter, QStringList() << "clientdocident");
			sqlquery.setCondition("and clientdocident ~* "+SQLSTR(filter) );
	
			KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
			m_xmlsource.setData(resultSet.toString());
			if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
			{
				std::cout << "No se pudo analizar!!!" << std::endl;
			}
		
			QStringList participants = m_xmlreader.getResultsList();
		
			std::cout << "Tamaño participantes: " << participants.count() << std::endl;
			for (uint j = 0; j < participants.count(); j+=2)
			{
				std::cout << "Adicionando: " << participants[j] << std::endl;
				KListViewItem *parttemp = new KListViewItem(tourtemp);

				parttemp->setText(1, participants[j]);
				parttemp->setText(2, participants[j+1]);
				tourtemp->insertItem(parttemp);
			}
			
			tourtemp->setOpen(true);
		}
	}
}

#include "participantslist.moc"
