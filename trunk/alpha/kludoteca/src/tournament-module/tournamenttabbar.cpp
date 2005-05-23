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
#include "tournamenttabbar.h"
#include <klocale.h>

TournamentTabBar::TournamentTabBar(QWidget *parent, const char *name) : KTabWidget(parent, name)
{
	setupTabs();
}


TournamentTabBar::~TournamentTabBar()
{
}

void TournamentTabBar::setupTabs()
{
	m_tactive = new TournamentActive(this);
	insertTab(m_tactive, i18n("Active"));
	
	m_participants = new ParticipantsList(this);
	insertTab(m_participants, i18n("Participants"));
	
	m_rounds = new RoundList(this);	
	insertTab(m_rounds, i18n("Rounds"));
	
	m_told = new TournamentOld(this);
	insertTab(m_told, i18n("Old"));
	
	connect(m_tactive, SIGNAL(tournamentModified()), this, SLOT(applyChangesToLists()));
}

void TournamentTabBar::applyChangesToLists()
{
	m_participants->fillList();
	m_rounds->fillList();
	m_told->fillList();
}


#include "tournamenttabbar.moc"
