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

#include "klxmlreport.h"

KLXmlReport::KLXmlReport(ChartType t) : QDomDocument("KLReport03")
{
	QDomProcessingInstruction header = this->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
	this->appendChild(header);
	
	QDomElement root = this->createElement( "KLReport" );
	
	QDomElement graphic = createElement("Graphic");
	graphic.setAttribute("type", t);
	root.appendChild(graphic);
	
	this->appendChild( root );
}


KLXmlReport::~KLXmlReport()
{
// 	delete m_graphic;
}

void KLXmlReport::createReportElement(double value, const QString &label, const QColor &color, Qt::BrushStyle t)
{
	QDomElement element = createElement("KLReportElement");
	element.setAttribute("value", value);
	element.setAttribute("r", color.red() );
	element.setAttribute("g", color.green() );
	element.setAttribute("b", color.blue() );
	element.setAttribute("style", t);
	QDomText resultText = this->createTextNode(label);
	element.appendChild(resultText);

	documentElement().firstChild().appendChild(element);
}

// void KLResultSet::setRecord(QStringList &fields, QStringList &results)
// {
// 	QDomElement recordElement = this->createElement("record");
// 	
// 	for (uint i = 0; i < results.count(); i++)
// 	{
// 		QDomElement fieldElement = this->createElement(fields[i].remove('(').remove(')'));
// 		QDomText resultText = this->createTextNode(results[i]);
// 		fieldElement.appendChild(resultText);
// 		recordElement.appendChild(fieldElement);
// 	}
// 	
// 	documentElement().appendChild(recordElement);
// }
