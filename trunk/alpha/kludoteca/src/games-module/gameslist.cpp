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

#include "gameslist.h"
#include <klocale.h>

GamesList::GamesList(QWidget *parent) : QVBox(parent, "Games")
{
	setCaption(i18n("Games"));
	setupListView();
	setupButtons();
}


GamesList::~GamesList()
{
}

void GamesList::setupListView()
{
	m_gameList = new KListView(this, "ListOfGames");
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
	
	m_gameList->show();
}

void GamesList::setupButtons()
{
	m_buttonBox = new QHBox(this);
	m_addGame = new KPushButton(i18n("Add"), m_buttonBox);
	m_delGame = new KPushButton(i18n("Delete"), m_buttonBox);
	m_queryGame = new KPushButton(i18n("Query"), m_buttonBox);
	m_editGame = new KPushButton(i18n("Edit"), m_buttonBox);
}

void GamesList::addGame(const QString &game)
{
}

void GamesList::makeQuery(QListViewItem *item)
{
	QString game = item->text(0);
	
	if ( m_gameCategories.find(game) == m_gameCategories.end() )
		emit query(game);
}

#include "gameslist.moc"
