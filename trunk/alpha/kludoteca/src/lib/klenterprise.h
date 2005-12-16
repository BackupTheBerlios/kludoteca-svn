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
#ifndef KLENTERPRISE_H
#define KLENTERPRISE_H

#include <qobject.h>

class KLEnterprise;

/**
 * @author CetiSoft
*/

class KLEnterprise : public QObject
{
	Q_OBJECT
	protected:
		KLEnterprise(QObject *parent = 0, const char *name = 0);
		~KLEnterprise();
		
	public:
		static KLEnterprise *instance();
		void setName(const QString &);
		void setNit(const QString &);
		void setPhone(const QString &);
		void setAddress(const QString &);
		void setCity(const QString &);
		
		QString getName();
		QString getNit();
		QString getPhone();
		QString getAddress();
		QString getCity();

	private:
		static KLEnterprise *m_instance;
		QString m_name, m_nit, m_phone, m_address, m_city;
};

#define klenterprise KLEnterprise::instance()

#endif
