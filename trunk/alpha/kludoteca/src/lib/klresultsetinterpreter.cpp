/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                             	   *
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

#include "klresultsetinterpreter.h"
#include <iostream>

KLResultSetInterpreter::KLResultSetInterpreter() : QXmlDefaultHandler(), m_root(QString::null), m_qname(QString::null), m_read(false),m_type(Partial)
{
}

KLResultSetInterpreter::~KLResultSetInterpreter()
{
}

bool KLResultSetInterpreter::startElement( const QString& , const QString& , const QString& qname, const QXmlAttributes& atts)
{
	m_qname = qname;
	m_read = true;
	if (m_root.isNull() )
	{
		m_root = qname;
		m_results.clear();
		m_sqlresults.clear();
		//std::cout << "Rooting to " << qname << std::endl;
	}
	else if (qname == "record")
	{
		if ( m_type == Partial )
			m_results.clear();
		m_read = false;
	}
	return true;
}

bool KLResultSetInterpreter::endElement(const QString& ns, const QString& localname, const QString& qname)
{
	m_read = false;
	
	if (qname == "record")
	{
		//qDebug("Emitiendo resultados");
		if ( m_type == Partial )
			emit readRecord(m_results);
	}
	else if ( qname== m_root )
	{
		m_root = QString::null;
	}
	
	return true;
}

bool KLResultSetInterpreter::characters(const QString &ch)
{
	bool conversion;
	if ( m_root == "RESULTS" && m_read && m_qname != m_root)
	{
		//std::cout << m_qname << " " << ch << std::endl;
		m_results << ch;
// 		std::cout << "Añadiendo: " << m_qname << std::endl;
		m_sqlresults.insert(m_qname, ch);
	}
	
	return true;
}

void KLResultSetInterpreter::setParseType(Type type)
{
	m_type = type;
}

KLSqlResults KLResultSetInterpreter::getResults()
{
	return m_sqlresults;
}

QStringList KLResultSetInterpreter::getResultList()
{
	return m_results;
}

#include "klresultsetinterpreter.moc"

