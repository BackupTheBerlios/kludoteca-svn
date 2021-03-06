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

#ifndef RENTINFO_H
#define RENTINFO_H

#include <qstring.h>

/**
 * @author CetiSoft
*/
class RentInfo
{
	public:
		RentInfo();
		~RentInfo();
		void setClientName(const QString &);
		void setClientId(const QString &);
		void setGameName(const QString &);
		void setGameSerial(const QString &);
		void setDate(const QString &date);
		void setHour(const QString &hour);
		void setActive(bool act);
		
		QString clientName() const;
		QString clientId() const;
		QString gameName() const;
		QString gameSerial() const;
		QString date() const;
		QString hour() const;
		bool isActive() const;
		
	private:
		QString m_clientName, m_clientId, m_gameName, m_gameSerial, m_date, m_hour;
		bool m_isActive;
};

#endif
