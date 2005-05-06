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

GamesList::GamesList(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Code")<<i18n("Name") << i18n("State"),button1, button2, button3, button4, parent, "Games")
{
	setCaption(i18n("Games"));
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
	if ( !m_db )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	KLSelect sqlquery(QStringList() <<"serialreference"<< "gamename" << "state", QStringList() << "ldt_games");
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void GamesList::setupListView()
{
	/*m_gameList = new LTListView(this, "ListOfGames");
	connect ( m_gameList, SIGNAL(executed(QListViewItem* )), this, SLOT(makeQuery(QListViewItem* )));
	
	m_gameList->setColumnWidthMode(0, QListView::Maximum);
	m_gameList->setRootIsDecorated(true);
	m_gameList->addColumn(i18n("Games"));
	m_gameList->setAutoOpen(true);
	
	// FIXME: esto es un ejemplo, los siguientes datos deben llenarse desde la base de datos.
	KListViewItem *itemBoard = new KListViewItem(m_gameList, "Board");
	m_gameList->insertItem(itemBoard);
	KListViewItem *itemChess = new KListViewItem(itemBoard, "Chess");
	itemBoard->insertItem(itemChess);
	KListViewItem *itemParkes = new KListViewItem(itemBoard, "Parkes");
	itemBoard->insertItem(itemParkes);
	
	KListViewItem *itemVideo = new KListViewItem(m_gameList, "Video");
	m_gameList->insertItem(itemVideo);
	KListViewItem *itemTetris = new KListViewItem(itemVideo, "Tetris");
	itemVideo->insertItem(itemTetris);
	
	KListViewItem *itemField = new KListViewItem(m_gameList, "Field");
	m_gameList->insertItem(itemField);
	KListViewItem *itemTennis = new KListViewItem(itemField, "Tennis");
	itemField->insertItem(itemTennis);
	
	m_gameCategories << "Board" << "Video" << "Field" ;
	
	m_gameList->show();*/
}

void GamesList::addGame(const QString &game)
{
}

void GamesList::getClickedItem(QListViewItem *item)
{
	QString game = item->text(1);
	
	if ( m_gameCategories.find(game) == m_gameCategories.end() )
		emit message2osd(i18n("The game ") + game + i18n(" is good!"));
}

void GamesList::addButtonClicked()
{
#if DEBUG_GAMESLIST 
	qDebug("init addButtonClicked");
#endif
	cout << "Add button clicked" << std::endl;
	KMdiChildView *view = new KMdiChildView(i18n("Add game"), this );
	
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminGame *formAdminGame = new FormAdminGame( m_db, scroll->viewport() );
	scroll->addChild(formAdminGame);
	formAdminGame->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminGame->setTitle(i18n("Admin game"));
	formAdminGame->setExplanation(i18n("fill the fields for add a new game"));
	emit sendWidget(view);
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
		m_db->execRawQuery("delete from ldt_games where serialreference="+ SQLSTR(itemp->text(0)));
		
		
		
		delete itemp;
		
		emit message2osd(i18n("The game has been deleted!!"));
	}
}

void GamesList::modifyButtonClicked()
{
	cout << "modify button clicked" << std::endl;
	
}

void GamesList::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
	QString quering = "";
	KListViewItem *itemp = static_cast<KListViewItem*>(m_listView->currentItem());
	
	quering += i18n("== query  game ") + itemp->text(0) + " == \n";
	
	KLSelect sqlquery(QStringList() << "gamename" << "serialreference" << "description" << "rules" << "mingamers" << "maxgamers" << "costtm"<<"state" , QString("ldt_users"));
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);
	
	m_xmlsource.setData(resultSet.toString());
	
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total ))
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	KLSqlResults results = m_xmlreader.results();
	
	quering += i18n("Game  name: ") + results["gamename"]  + "\n";
	quering += i18n("Code game: ") + results["serialreference"] + "\n";
	quering += i18n("Description: ") + results["description"] + "\n";
	quering += i18n("Rules: ") + results["rules"] + "\n";
	quering += i18n("Mininus of gamers: ") + results["mingamers"] + "\n";
	quering += i18n("Maximus of gamers:") + results["maxgamers"] + "\n";
	quering += i18n("Cost unit time: ") + results["costtm"] + "\n";
	quering += i18n("State of gamers:") + results["state"] + "\n\n";
	
	emit message2osd(quering);
}

/*void AdminUsers::addItem(const QString &pkey)
{
	KLSelect sqlquery(QStringList() << "firstname" << "lastname" << "login", QStringList() << "ldt_users");
	sqlquery.setWhere("login="+SQLSTR(pkey));
	
	KLResultSet resultSet = m_db->execQuery(&sqlquery);

	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Partial) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
}
}

void AdminUsers::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}*/
#include "gameslist.moc"
