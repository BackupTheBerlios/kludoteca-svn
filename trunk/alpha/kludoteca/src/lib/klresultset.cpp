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
#include "klresultset.h"

KLResultSet::KLResultSet() : QDomDocument()
{
	QDomProcessingInstruction cabecera = this->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
	this->appendChild(cabecera);
	
	QDomElement raiz = this->createElement( "RESULTS" );
	this->appendChild( raiz );
}


KLResultSet::~KLResultSet()
{
}

void KLResultSet::setRecord(QStringList &fields, QStringList &results)
{
	QDomElement recordElement = this->createElement("record");
	
	for (uint i = 0; i < results.count(); i++)
	{
		QDomElement fieldElement = this->createElement(fields[i].remove('(').remove(')'));
		QDomText resultText = this->createTextNode(results[i]);
		fieldElement.appendChild(resultText);
		recordElement.appendChild(fieldElement);
	}
	
	documentElement().appendChild(recordElement);
}
