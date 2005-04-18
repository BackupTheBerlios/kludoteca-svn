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

#include "klresultsetinterpreter.h"
#include <iostream>

KLResultSetInterpreter::KLResultSetInterpreter() : QXmlDefaultHandler(), m_root(QString::null), m_qname(QString::null), m_read(false)
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
		std::cout << "Rooting to " << qname << std::endl;
	}
	else if (qname == "record")
	{
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
		qDebug("Emitiendo resultados");
		emit readRecord(m_results);
	}
	
	return true;
}

bool KLResultSetInterpreter::characters(const QString &ch)
{
	bool conversion;
	if ( m_root == "RESULTS" && m_read)
	{
		std::cout << m_qname << " " << ch << std::endl;
		m_results << ch;
	}
	
	return true;
}

#include "klresultsetinterpreter.moc"

