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
#include "klenterprise.h"

KLEnterprise::KLEnterprise(QObject *parent, const char *name)
 : QObject(parent, name)
{
}


KLEnterprise::~KLEnterprise()
{
}

KLEnterprise *KLEnterprise::instance()
{
	static KLEnterprise *skdb = new KLEnterprise;
	
	return skdb;
}


void KLEnterprise::setName(const QString &t)
{
	m_name = t;
}

void KLEnterprise::setNit(const QString &t)
{
	m_nit = t;
}

void KLEnterprise::setPhone(const QString &t)
{
	m_phone = t;
}

void KLEnterprise::setAddress(const QString &t)
{
	m_address = t;
}

void KLEnterprise::setCity(const QString &t)
{
	m_city = t;
}


QString KLEnterprise::getName()
{
	return m_name;
}

QString KLEnterprise::getNit()
{
	return m_nit;
}

QString KLEnterprise::getPhone()
{
	return m_phone;
}

QString KLEnterprise::getAddress()
{
	return m_address;
}

QString KLEnterprise::getCity()
{
	return m_city;
}

#include "klenterprise.moc"
