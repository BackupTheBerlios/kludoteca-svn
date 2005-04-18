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

using namespace std;

GamesList::GamesList(Button button1, Button button2, Button button3, Button button4,QWidget *parent) : LTListView(QStringList() << i18n("Name") << i18n("State"),button1, button2, button3, button4, parent, "Games")
{
	setCaption(i18n("Games"));
	setupListView();
}


GamesList::~GamesList()
{
}

void GamesList::fillList()
{
	if ( !m_db )
	{
		qDebug("You're need set the database!!");
		return;
	}
	
	KLResultSet resultSet = m_db->select(QStringList() << "gamename" << "state", "ldt_games");
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.parse(m_xmlsource) )
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
}

void GamesList::setupListView()
{
// 	m_gameList = new LTListView(this, "ListOfGames");
// 	connect ( m_gameList, SIGNAL(executed(QListViewItem* )), this, SLOT(makeQuery(QListViewItem* )));
// 	
// 	m_gameList->setColumnWidthMode(0, QListView::Maximum);
// 	m_gameList->setRootIsDecorated(true);
// 	m_gameList->addColumn(i18n("Games"));
// 	m_gameList->setAutoOpen(true);
// 	
// 	// FIXME: esto es un ejemplo, los siguientes datos deben llenarse desde la base de datos.
// 	KListViewItem *itemBoard = new KListViewItem(m_gameList, "Board");
// 	m_gameList->insertItem(itemBoard);
// 	KListViewItem *itemChess = new KListViewItem(itemBoard, "Chess");
// 	itemBoard->insertItem(itemChess);
// 	KListViewItem *itemParkes = new KListViewItem(itemBoard, "Parkes");
// 	itemBoard->insertItem(itemParkes);
// 	
// 	KListViewItem *itemVideo = new KListViewItem(m_gameList, "Video");
// 	m_gameList->insertItem(itemVideo);
// 	KListViewItem *itemTetris = new KListViewItem(itemVideo, "Tetris");
// 	itemVideo->insertItem(itemTetris);
// 	
// 	KListViewItem *itemField = new KListViewItem(m_gameList, "Field");
// 	m_gameList->insertItem(itemField);
// 	KListViewItem *itemTennis = new KListViewItem(itemField, "Tennis");
// 	itemField->insertItem(itemTennis);
// 	
// 	m_gameCategories << "Board" << "Video" << "Field" ;
// 	
// 	m_gameList->show();
}

void GamesList::addGame(const QString &game)
{
}

void GamesList::getClickedItem(QListViewItem *item)
{
	QString game = item->text(0);
	
	if ( m_gameCategories.find(game) == m_gameCategories.end() )
		emit query(game);
}

void GamesList::addButtonClicked()
{
	cout << "Add button clicked" << std::endl;
	KMdiChildView *view = new KMdiChildView(i18n("Add game"), this );
	
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormAdminGame *formAdminGame = new FormAdminGame( scroll->viewport() );
	scroll->addChild(formAdminGame);
	formAdminGame->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	formAdminGame->setTitle(i18n("Admin game"));
	formAdminGame->setExplanation(i18n("fill the fields for add a new game"));
	emit sendWidget(view);
}

void GamesList::delButtonClicked()
{
	cout << "del button clicked" << std::endl;
}

void GamesList::modifyButtonClicked()
{
	cout << "modify button clicked" << std::endl;
}

void GamesList::queryButtonClicked()
{
	cout << "query button clicked" << std::endl;
}

#include "gameslist.moc"
