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
#ifndef KLQUERY_H
#define KLQUERY_H

#include <qobject.h>
#include <qstringlist.h>

class KLSelect;

/**
 * Esta clase se utiliza para encapsular consultas a la base de datos, la idea es proporcionar una interfaz sencilla al programador para hacer consultas y subconsultas a la base de datos
 * @author David Cuadrado
 */
class KLQuery : public QObject
{
	Q_OBJECT
	public:
		enum Type { Select = 0, Insert, Update, Delete };
		KLQuery(Type t = Select);
		~KLQuery();
		virtual QString getQuery() const;
		int getType();
		
	protected:
		QString m_query;
		
	private:
		Type m_type;

};

/**
 * Esta clase encapsula clausulas SELECT-FROM-WHERE
 * @author David Cuadrado
 */
class KLSelect : public KLQuery
{
	Q_OBJECT
	public:
		KLSelect(QStringList fields, QStringList tables);
		~KLSelect();
		void addSubConsult(QString connector, const KLSelect &subconsult);
		void setWhere(QString cwhere);
		
		QStringList getFields();
		
		QString getQuery() const;
		
	private:
		QStringList m_fields;
		QString m_cwhere;
};

/**
 * Esta clase encapsula clausulas UPDATE
 * @author David Cuadrado
 */
class KLUpdate : public KLQuery
{
	Q_OBJECT
	public:
		KLUpdate();
		~KLUpdate();
};

/**
 * Esta clase encapsula clausulas INSERT
 * @author David Cuadrado
 */
class KLInsert : public KLQuery
{
	Q_OBJECT
	public:
		KLInsert();
		~KLInsert();
};


#endif
