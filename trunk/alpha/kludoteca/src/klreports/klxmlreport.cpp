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

KLXmlReport::KLXmlReport(const QString &title, const QString &enterprise, const QString &nit, ChartType t) : QDomDocument("KLReport03")
{
	QDomProcessingInstruction header = this->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
	this->appendChild(header);
	
	QDomElement root = this->createElement( "KLReport" );
	root.setAttribute("title", title);
	
	QDomElement graphic = createElement("Graphic");
	graphic.setAttribute("type", t);
	root.appendChild(graphic);
	
	QDomElement element = createElement("KLEnterprise");
	element.setAttribute("name", enterprise);
	element.setAttribute("nit", nit );
	root.appendChild(element);
	
	this->appendChild( root );
}


KLXmlReport::~KLXmlReport()
{
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
