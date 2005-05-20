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
#include "klquery.h"
#include <klocale.h>
#include <iostream>

// KLQuery

KLQuery::KLQuery(Type t) : m_type(t), m_cwhere("")
{
}


KLQuery::~KLQuery()
{
}

QString KLQuery::getQuery() const
{
	return m_query + " " + m_cwhere;
}

int KLQuery::getType()
{
	return m_type;
}

void KLQuery::setWhere(const QString &w)
{
	m_cwhere = " where " + w;
}

void KLQuery::setCondition(const QString &condition)
{
	if ( m_cwhere.isNull() )
		setWhere("'t'");
	m_cwhere += " " + condition + " ";
}


// KLSelect
KLSelect::KLSelect(QStringList fields, QStringList tables, bool dist) : KLQuery(KLQuery::Select), m_fields(fields), m_filter("")
{
	if ( dist )
		m_query = "select distinct ";
	else
		m_query = "select ";
	
	if ( fields.count() == 0 )
	{
		qDebug(i18n("You need specify the fields"));
	}
	for(uint i = 0; i < fields.count(); i++)
	{
		if ( i == fields.count() - 1)
			m_query += fields[i];
		else
			m_query += fields[i] + ",";
	}
	m_query += " from ";
	for(uint i = 0; i < tables.count(); i++)
	{
		if ( i == tables.count() - 1)
			m_query += tables[i];
		else
			m_query += tables[i] + ",";
	}

}

KLSelect::KLSelect(QStringList fields, const QString &table, bool dist) : KLQuery(KLQuery::Select), m_fields(fields), m_filter("")
{
	if ( dist )
		m_query = "select distinct ";
	else
		m_query = "select ";
	
	if ( fields.count() == 0 )
	{
		qDebug(i18n("You need specify the fields"));
	}
	for(uint i = 0; i < fields.count(); i++)
	{
		if ( i == fields.count() - 1)
			m_query += fields[i];
		else
			m_query += fields[i] + ",";
	}
	m_query += " from " + table;
}

KLSelect::~ KLSelect()
{
}

QString KLSelect::getQuery() const
{
	return m_query + m_cwhere + m_subquery + m_filter;
}

QStringList KLSelect::getFields()
{
	return m_fields;
}

void KLSelect::addSubConsult(QString connector, const KLSelect &subconsult)
{
	m_subquery += " " + connector + " ( " + subconsult.getQuery() + " ) ";
}

void KLSelect::addFilter( const QString& filter, QStringList fields )
{
	std::cout << "FILTER: " << filter << std::endl;
	if ( !filter.isEmpty() )
	{
		if ( m_cwhere.isEmpty() )
			m_cwhere = " where 't'";
		m_filter = " and 'f' ";
		
		QStringList filters = QStringList::split( " ", filter );
		
		
		for ( uint f = 0; f < filters.count(); f++)
		{
			std::cout << "FILTRO : " << filters[f] << std::endl;
			if ( fields.count() > 0)
			{
				for (uint i = 0; i < fields.count(); i++)
				{
					m_filter += " OR " + fields[i]  + " ~* "+ SQLSTR(filters[f]);
				}
			}
			else
			{
				for (uint i = 0; i < m_fields.count(); i++)
				{
					m_filter += " OR " + m_fields[i]  + " ~* "+ SQLSTR(filters[f]);
				}
			}
		}
	}
}


// KLUpdate

KLUpdate::KLUpdate(QString table, QStringList fields, QStringList values) : KLQuery(KLQuery::Update)
{
	Q_ASSERT(fields.count() == values.count());
	
	m_query = " UPDATE " + table + " set ";
	for (uint i = 0; i < fields.count(); i++)
	{
		if ( i == values.count() - 1)
			m_query += fields[i] + " = " + values[i];
		else
			m_query += fields[i] + " = " + values[i] + ",";
	}
}

KLUpdate::~KLUpdate()
{
}

KLInsert::KLInsert(QString table, QStringList values) : KLQuery(KLQuery::Insert)
{
	m_query = "insert into " + table + " values ( ";
	
	for (uint i = 0; i < values.count(); i++)
	{
		if ( i == values.count() - 1)
			m_query += values[i];
		else
			m_query += values[i] + ",";
	}
	
	m_query += " )";
}

KLInsert::~KLInsert()
{
}

// KLDelete
KLDelete::KLDelete(QString table) : KLQuery(KLQuery::Delete)
{
	m_query = "delete from " + table + " ";
}

KLDelete::~KLDelete()
{
}


#include "klquery.moc"
