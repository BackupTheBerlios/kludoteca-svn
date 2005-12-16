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

#include "klpermission.h"
#include <iostream>

KLPermission *KLPermission::m_instance = 0;

KLPermission::KLPermission()
{
}


KLPermission::~KLPermission()
{
	if( m_instance ) delete m_instance;
}

KLPermission *KLPermission::instance()
{
	if ( m_instance == 0 )
	{
		m_instance = new KLPermission;
	}
	return m_instance;
}

void KLPermission::string2perms(const QString &str)
{
	strperms = str;
	m_activeAdminModule = str.at(0).digitValue();
	m_activeClientsModule = str.at(1).digitValue();
	m_activeGamesModule = str.at(2).digitValue();
	m_activeRentsModule = str.at(3).digitValue();
	m_activeTournamentModule = str.at(4).digitValue();

}


bool KLPermission::activeAdminModule()
{
	return m_activeAdminModule;
}

bool KLPermission::activeClientsModule()
{
	return m_activeClientsModule;
}

bool KLPermission::activeGamesModule()
{
	return m_activeGamesModule;
}

bool KLPermission::activeTournamentModule()
{
	return m_activeTournamentModule;
}

bool KLPermission::activeRentsModule()
{
	return m_activeRentsModule;
}
