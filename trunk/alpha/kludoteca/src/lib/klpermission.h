/***************************************************************************
 *   Copyright (C) 2005 by David CUadrado                                  *
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
#ifndef KLPERMISSION_H
#define KLPERMISSION_H

#include <qstring.h>

class KLPermission;

/**
 * Esta clase mantiene una instancia de los permisos
 * @author David Cuadrado
*/
class KLPermission
{
	protected:
		KLPermission();
		~KLPermission();
		
	public:
		static KLPermission* instance();
		
		void string2perms(const QString &str);
		bool activeAdminModule();
		bool activeClientsModule();
		bool activeGamesModule();
		bool activeTournamentModule();
		bool activeRentsModule();
		
	private:
		static KLPermission *m_instance;
		QString strperms;
		bool m_activeAdminModule;
		bool m_activeClientsModule;
		bool m_activeGamesModule;
		bool m_activeRentsModule;
		bool m_activeTournamentModule;
};

#define klperm KLPermission::instance()

#endif
