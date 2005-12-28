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
#include "rentinfo.h"

RentInfo::RentInfo()
{
}


RentInfo::~RentInfo()
{
}


void RentInfo::setClientName(const QString &client)
{
	m_clientName = client;
}

void RentInfo::setClientId(const QString &id)
{
	m_clientId = id;
}

void RentInfo::setGameName(const QString &game)
{
	m_gameName = game;
}

void RentInfo::setGameSerial(const QString &serial)
{
	m_gameSerial = serial;
}

void RentInfo::setDate(const QString &date)
{
	m_date = date;
}

void RentInfo::setHour(const QString &hour)
{
	m_hour = hour;
}

QString RentInfo::clientName() const
{
	return m_clientName;
}

QString RentInfo::clientId() const
{
	return m_clientId;
}

QString RentInfo::gameName() const
{
	return m_gameName;
}

QString RentInfo::gameSerial() const
{
	return m_gameSerial;
}

QString RentInfo::date() const
{
	return m_date;
}

QString RentInfo::hour() const
{
	return m_hour;
}

