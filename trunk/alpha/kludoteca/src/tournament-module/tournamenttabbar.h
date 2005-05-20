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
#ifndef TOURNAMENTTABBAR_H
#define TOURNAMENTTABBAR_H

#include <ktabwidget.h>
#include "formtournament.h"
#include "tournamentactive.h"
#include "tournamentold.h"
#include "participantslist.h"
#include "roundlist.h"

/**
 * Este es el tab bar con la informacion del torneo
 * @author CetiSoft
*/
class TournamentTabBar : public KTabWidget
{
	Q_OBJECT
	public:
		TournamentTabBar(QWidget *parent = 0, const char *name = 0);
		~TournamentTabBar();
		
	private:
		void setupTabs();
		
	private:
		TournamentActive *m_tactive;
		TournamentOld *m_told;
		ParticipantsList *m_participants;
		RoundList *m_rounds;

};

#endif
