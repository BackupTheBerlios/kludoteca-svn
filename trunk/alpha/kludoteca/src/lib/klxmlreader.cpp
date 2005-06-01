/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                        	   	   *
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

#include "klxmlreader.h"
#include <klocale.h>

KLXmlReader::KLXmlReader() : QXmlSimpleReader(), m_interpreter(0)
{
	m_interpreter = new KLResultSetInterpreter();
	QXmlSimpleReader::setContentHandler(m_interpreter);
}


KLXmlReader::~KLXmlReader()
{
}

bool KLXmlReader::analizeXml(const QXmlInputSource * input, KLResultSetInterpreter::Type t)
{
	m_interpreter->setParseType(t);

	return QXmlSimpleReader::parse(input, true);
}

KLSqlResults KLXmlReader::results()
{
	return m_interpreter->getResults();
}

QStringList KLXmlReader::getResultsList()
{
	return m_interpreter->getResultList();
}

bool KLXmlReader::parse(const QXmlInputSource * input, bool incremental)
{
#warning "Please don't use this function!!, use analizeXml instead"
	return QXmlSimpleReader::parse(input, incremental);
}

bool KLXmlReader::parse ( const QXmlInputSource * input )
{
#warning "Please don't use this function!!, use analizeXml instead"
	return QXmlSimpleReader::parse(input);
}
