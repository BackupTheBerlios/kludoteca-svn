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

#include "gameslist.h"
#include <klocale.h>
#include  <kmessagebox.h>

#define DEBUG_GAMESLIST 0

using namespace std;

GamesList::GamesList(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Code")<<i18n("Name") << i18n("available"),button1, button2, button3, button4, parent, "Games")
{
	setCaption(i18n("Games"));
	m_listView->setTitle(i18n("Games"));
	m_listView->setExplain(i18n("Please click in the \"Add\" button for add a game"));
	setupListView();
	
}


GamesList::~GamesList()
{
}

void GamesList::fillList()
{	
#if DEBUG_GAMESLIST
	qDebug("Fill List");
#endif
	m_listView->clear();
	KLSelect sqlquery(QStringList() <<"serialreference"<< "gamename" << "available", QStringList() << "ldt_games");
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void GamesList::setupListView()
{
}

void GamesList::addGame(const QString &game)
{
}

void GamesList::getClickedItem(QListViewItem *item)
{
	QString game = item->text(1);
	modifyButtonClicked();
}

void GamesList::addButtonClicked()
{
#if DEBUG_GAMESLIST 
	qDebug("init addButtonClicked");
#endif
	cout << "Add button clicked" << std::endl;
	
	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	FormAdminGame *formAdminGame = new FormAdminGame(FormBase::Add, scroll->viewport() );
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->addChild(formAdminGame);
	formAdminGame->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminGame->setTitle(i18n("Admin game"));
	formAdminGame->setExplanation(i18n("fill the fields for add a new game"));
	
	connect(formAdminGame, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formAdminGame, SIGNAL(inserted(const QString& )), this, SLOT(addItem(const QString &)));
	connect(formAdminGame, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	emit sendWidget(scroll, i18n("Add Game"));
	
// 	addItem( formAdminGame->getReferenceGame() );	
	
#if DEBUG_GAMESLIST
	qDebug("end addButtonClicked");
#endif
}

void GamesList::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	int opt = KMessageBox::questionYesNo(this, i18n("Are you sure to delete the game ")+itemp->text(1)+ " ?");
	
	if (opt == KMessageBox::Yes )
	{
		KLDM->execRawQuery("delete from ldt_games where serialreference="+ SQLSTR(itemp->text(0))); // FIXME: Usar KLDelete y KLDM
		
		
		
		delete itemp;
		
		emit message2osd(i18n("The game has been deleted!!"));
	}
	
}

void GamesList::modifyButtonClicked()
{
#if DEBUG_GAMESLIST 
	qDebug("init modifyButtonClicked");
#endif
	cout << "modify button clicked" << std::endl;
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());

	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminGame *formAdminGame = new FormAdminGame( FormBase::Edit, scroll->viewport() );
	scroll->addChild(formAdminGame);
	formAdminGame->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminGame->setTitle(i18n("Admin game"));
	formAdminGame->setExplanation(i18n("Change the fields for modify the game"));
	formAdminGame->formModify(itemp->text(0));
	
	connect(formAdminGame, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formAdminGame, SIGNAL(inserted(const QString& )), this, SLOT(updateItem(const QString &)));
	connect(formAdminGame, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	emit sendWidget(scroll, i18n("Modify game"));

#if DEBUG_GAMESLIST
	qDebug("end modifyButtonClicked");
#endif
}

void GamesList::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
	QString quering = "";
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	quering += i18n("== query  game ") + itemp->text(0) + " == \n";
	
	KLSelect sqlquery(QStringList() << "gamename" << "serialreference" << "description" << "rules" << "mingamers" << "maxgamers" << "costforunit"<<"available" , QString("ldt_games"));
	
	sqlquery.setWhere("serialreference ="+SQLSTR( m_listView->currentItem()->text(0)));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total ))
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	quering += i18n("Game  name:   ") + results["gamename"]  + "\n";
	quering += i18n("Code game:   ") + results["serialreference"] + "\n";
	quering += i18n("Description:   ") + results["description"] + "\n";
	quering += i18n("Rules:   ") + results["rules"] + "\n";
	quering += i18n("Mininus of gamers:   ") + results["mingamers"] + "\n";
	quering += i18n("Maximus of gamers:   ") + results["maxgamers"] + "\n";
	quering += i18n("Cost unit time:   ") + results["costforunit"] + "\n";
	quering += i18n("available of gamers:   ") + results["available"] + "\n\n";
	
	emit message2osd(quering);
}

void GamesList::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		KLSelect sqlquery(QStringList() << "serialreference" << "gamename" << "available", QStringList() << "ldt_games");

		sqlquery.addFilter(filter, QStringList() << "serialreference" << "gamename");
		
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
	}
}

void GamesList::addItem(const QString &pkey)
{
	std::cout << "Adicionando item con pkey: " << pkey << std::endl;
	
	KLSelect sqlquery(QStringList() << "serialreference" << "gamename" << "available", QStringList() << "ldt_games");
	sqlquery.setWhere("serialreference="+SQLSTR(pkey) );

	KLResultSet resultSet = KLDM->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void GamesList::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}



/*
void GamesList::addItem(const QString &pkey)
{
	
	KLSelect sqlquery(QStringList() << "serialreference" << "namegame" << "available", QStringList() << "ldt_users");
	sqlquery.setWhere("serialference = "+SQLSTR( pkey));
		
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void GamesList::updateItem(const QString &pkey)
{
	//delete m_listView->currentItem();
	addItem(pkey);
}
*/
#include "gameslist.moc"
