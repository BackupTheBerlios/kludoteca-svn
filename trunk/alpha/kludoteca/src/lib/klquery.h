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

#define SQLSTR(s) QString("\'"+((QString("%1").arg(s)).replace('\'', "\\\'"))+"\'")

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
		
	protected:
		/**
		 * Construye una consulta con un tipo t, si t no es definido se asumira que sera una consulta Select
		 * @param t 
		 * @return 
		 */
		KLQuery(Type t = Select);
		
	public:
		/**
		 * Destructor
		 * @return 
		 */
		~KLQuery();
		/**
		 * Obtiene la consulta
		 * @return 
		 */
		virtual QString getQuery() const;
		
		
		/**
		 * Coloca la clausula where
		 * @param cwhere 
		 */
		virtual void setWhere(const QString &w);
		
		virtual void setCondition(const QString &condition);
		
		/**
		 * Obtiene el tipo de consulta
		 * @return 
		 */
		int getType();
		
	protected:
		QString m_query;
		QString m_cwhere;
		
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
		enum Order { NoOrder = 0, Asc, Desc };
		enum JoinConnector { On = 0, Using };
		
		/**
		 * Construye una consulta select
		 * @param fields 
		 * @param tables 
		 * @return 
		 */
		KLSelect(QStringList fields, QStringList tables, bool dist = false);
		
		/**
		 * Construye una consulta select que afecta a una sola tabla
		 * @param fields 
		 * @param table 
		 * @return 
		 */
		KLSelect(QStringList fields, const QString &table, bool dist = false);
		
		/**
		 * Destructor
		 * @return 
		 */
		~KLSelect();
		/**
		 * Añade una subconsulta a la consulta, se debe primero colocar la clausula where por medio de setWhere, y pasar a la funcion el conector y la subconsulta.
		 * @param connector 
		 * @param subconsult 
		 */
		void addSubConsult(QString connector, const KLSelect &subconsult);

		/**
		 * Obtiene la lista de campos afectados
		 * @return 
		 */
		QStringList getFields();
		
		/**
		 * Obtiene la consulta (Reimplementado de KLQuery)
		 * @return 
		 */
		QString getQuery() const;
		
		void addFilter( const QString& filter, QStringList fields = QStringList() );
		
		void setOrderBy(const QString &field, Order o);
		void setOrderBy(int field, Order o);
		
		void setJoin(const QString &link, JoinConnector jc, const QStringList & rest);
		
	private:
		QStringList m_fields;
		QString m_subquery;
		QString m_from;
		QString m_filter;
		QString m_orderby;
		QString m_join;
};

/**
 * Esta clase encapsula clausulas UPDATE
 * @author David Cuadrado
 */
class KLUpdate : public KLQuery
{
	Q_OBJECT
	public:
		/**
		 * Construye una consulta UPDATE, se debe pasar la tabla que se quiere afectar y los campos con sus respectivos valores.
		 * @param table 
		 * @param fields 
		 * @param values 
		 * @return 
		 */
		KLUpdate(QString table, QStringList fields, QStringList values );
		/**
		 * Destructor
		 * @return 
		 */
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
		/**
		 * Construye una consulta INSERT INTO, se debe pasar la tabla que se quiere afectar y la lista de valores para cada campo en orden.
		 * @param table 
		 * @param values 
		 * @return 
		 */
		KLInsert(QString table, QStringList values);
		/**
		 * Destructor
		 * @return 
		 */
		~KLInsert();
};

/**
 * Esta clase encapsula clausulas INSERT
 * @author David Cuadrado
 */
class KLDelete : public KLQuery
{
	Q_OBJECT
	public:
		/**
		 * Construye una consulta INSERT INTO, se debe pasar la tabla que se quiere afectar y la lista de valores para cada campo en orden.
		 * @param table 
		 * @param values 
		 * @return 
		 */
		KLDelete(QString table);
		/**
		 * Destructor
		 * @return 
		 */
		~KLDelete();
};

#endif
