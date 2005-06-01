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
 
#include "klexportreport.h"
#include <klocale.h>
#include <qdatetime.h>

KLExportReport::KLExportReport(const KLXmlReport &report, const QString file, int t) : m_file(file), m_type(t)
{
	switch(t)
	{
		case HTML:
		{
			exportToHtml(report);
		}
		break;
	}
}

KLExportReport::KLExportReport(const QString file, int t) : m_file(file), m_type(t)
{
}

KLExportReport::~KLExportReport()
{
}

void KLExportReport::exportToHtml(const KLXmlReport &report)
{
	QXmlInputSource source;
	source.setData(report.toString() );
	
	KLXmlReportParser parser;
	QXmlSimpleReader reader;
	reader.setContentHandler(&parser);
	
	if ( ! reader.parse(&source ) )
	{
		qDebug("I can't analice this report, sorry!");
		return;
	}
	
	QFile file(m_file);
	
	QString header = "<html><head><title>"+parser.getTitle() +"</title></head><body>"
	"<div align=center><h1>"+parser.getTitle()+"</h1></div>"
	"<div align=center><h4>"+parser.getEnterprise()+"</h4></div>"
	"<div align=center><h4>Nit. "+parser.getNit()+"</h4></div><br><br>";	
	
	QString footer = i18n("<br><br><div align=center><emphasis>Date:")+QDate::currentDate().toString(Qt::ISODate)+"</emphasis></div></body>";
	
	
	ElementVector elements = parser.getElements();
	
	if ( file.open(IO_WriteOnly) )
	{
		QTextStream stream( &file );
		// Escribir el html
		
		stream << header << endl;
		stream << "<div align=center><table border><caption align=\"bottom\">REPORTS<caption>  ";
		
		stream << "<tr>";
		for(uint i = 0; i < elements.count(); i++)
		{
			stream << "<th>" << elements[i].label() << "</th>";
		}
		stream << "</tr>";
		
		stream << "<tr>";
		for(uint i = 0; i < elements.count(); i++)
		{
			stream << "<td>" << elements[i].value() << "</td>" << endl;
		}
		stream << "</tr>";
		
		stream << "</table></div>";
		stream << footer << endl;
	}
}

