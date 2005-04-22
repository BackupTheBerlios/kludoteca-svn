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
#include "klquery.h"
#include <klocale.h>
#include <iostream>

// KLQuery

KLQuery::KLQuery(Type t) : m_type(t)
{
}


KLQuery::~KLQuery()
{
}

QString KLQuery::getQuery() const
{
	return m_query;
}

int KLQuery::getType()
{
	return m_type;
}


// KLSelect
KLSelect::KLSelect(QStringList fields, QStringList tables) : KLQuery(KLQuery::Select), m_fields(fields), m_cwhere("")
{
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

KLSelect::~ KLSelect()
{
}

QString KLSelect::getQuery() const
{
	return m_query + m_cwhere;
}

QStringList KLSelect::getFields()
{
	return m_fields;
}

void KLSelect::addSubConsult(QString connector, const KLSelect &subconsult)
{
	m_query += getQuery() + " " + connector + " ( " + subconsult.getQuery() + " ) ";
	m_cwhere = "";
}

void KLSelect::setWhere(QString cwhere)
{
	m_cwhere += " where " + cwhere;
}


// KLUpdate

KLUpdate::KLUpdate(QString table, QStringList fields, QStringList values) : KLQuery(KLQuery::Update), m_cwhere("")
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

void KLUpdate::setWhere(QString cwhere)
{
	m_cwhere = " where " + cwhere;
}

QString KLUpdate::getQuery() const
{
	return m_query + m_cwhere;
}


// KLDelete
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

#include "klquery.moc"