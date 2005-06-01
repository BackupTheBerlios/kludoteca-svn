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

#include "klxmlreportparser.h"

KLXmlReportParser::KLXmlReportParser() : QXmlDefaultHandler(), m_root(QString::null), m_qname(QString::null), m_read(false)
{
}


KLXmlReportParser::~KLXmlReportParser()
{
}

bool KLXmlReportParser::startElement( const QString& , const QString& , const QString& qname, const QXmlAttributes& atts)
{
	m_qname = qname;
	m_read = true;
	if (m_root.isNull() )
	{
		m_root = qname;
		m_elements.clear();
		m_title = atts.value("title");
	}
	else if (qname == "Graphics")
	{
		m_graphicType = atts.value("type").toInt();
	}
	else if ( qname == "KLReportElement" )
	{
		m_value = atts.value("value").toDouble();
		m_color = QColor(atts.value("r").toInt(), atts.value("g").toInt(), atts.value("b").toInt());
		m_style = atts.value("style").toInt();
	}
	else if ( qname == "KLEnterprise")
	{
		m_enterprise = atts.value("name");
		m_nit = atts.value("nit");
	}
	return true;
}

bool KLXmlReportParser::endElement(const QString& ns, const QString& localname, const QString& qname)
{
	m_read = false;
	
	// Termina, creo y añado al vector
	if (qname == "KLReportElement")
	{
		m_elements.append( KLReportElement(m_value, m_color, m_style, m_label ));
	}
	else if ( qname == m_root )
	{
		m_root = QString::null;
	}
	
	return true;
}

bool KLXmlReportParser::characters(const QString &ch)
{
	bool conversion;
	if ( m_root == "KLReport" && m_read && m_qname != m_root)
	{
		m_label = ch;
	}
	
	return true;
}

ElementVector KLXmlReportParser::getElements()
{
	return m_elements;
}

int KLXmlReportParser::getGraphicType()
{
	return m_graphicType;
}

QString KLXmlReportParser::getTitle()
{
	return m_title;
}

QString KLXmlReportParser::getEnterprise()
{
	return m_enterprise;
}

QString KLXmlReportParser::getNit()
{
	return m_nit;
}
