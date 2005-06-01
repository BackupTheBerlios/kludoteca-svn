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
	
// 	QString doctype = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n";
	QString header = "<html><head><title>"+parser.getTitle() +"</title>";
	
	
	QString style = "<style type=\"text/css\">"
			"TD {"
			"text-align:center;"
			"font-family:\"Verdana\",\"Courier New\";"
			"font-size: 12px: }"
			"TD.title {"
			"font-size:20px;"
			"font-weight:bold;"
			"color:orange; } </style></head>";
	
	QString body = "<body><center>"
	"<div align=center><h1>"+parser.getTitle()+"</h1></div>"
	"<div align=center><h4>"+parser.getEnterprise()+"</h4></div>"
	"<div align=center><h4>Nit. "+parser.getNit()+"</h4></div><br><br>";	
	
	QString footer = i18n("<br><br><div align=center><em>Date:")+QDate::currentDate().toString(Qt::ISODate)+"</em></div></center></body>";
	
	
	ElementVector elements = parser.getElements();
	
	if ( file.open(IO_WriteOnly) )
	{
		QTextStream stream( &file );
		// Escribir el html
// 		stream << doctype << endl;
		stream << header << endl;
		stream << style << endl;
		stream << body;
// 		stream << "<div align=center><table border><caption align=\"bottom\">REPORTS<caption>  ";
		
// 		stream << "<tr>";
// 		for(uint i = 0; i < elements.count(); i++)
// 		{
// 			stream << "<th>" << elements[i].label() << "</th>";
// 		}
// 		stream << "</tr>";
// 		
// 		stream << "<tr>";
// 		for(uint i = 0; i < elements.count(); i++)
// 		{
// 			stream << "<td>" << elements[i].value() << "</td>" << endl;
// 		}
// 		stream << "</tr>";
// 		
// 		stream << "</table></div>";
		
		// Dibuja la grafica
		stream << "<table border=0>";
		stream << "<tr><td class='title'>" << parser.getTitle() << "</td></tr><tr><td></td></tr>" ;
		
		stream << "<tr><td><div>" << endl;
		
		QString columnwidth = "30";
		
		for(uint i = 0; i < elements.count(); i++)
		{
			stream << "<span style='";
			stream << "width:" << elements[i].label().length()*10 << "; ";
			stream << "height:"<< elements[i].value() << "; ";
			stream << "background-color:" << elements[i].valueColor().name() << ";";
			stream << "'>"<< elements[i].value() << "</span> " << endl;
// 			stream << "<tr><td><div><br>" << endl;
		}
		
		stream << "</div></td></tr>" << endl;
		stream << "<tr><td><hr></td></tr>" << endl;
		stream << "<tr><td class='label' >";
		stream << "<div>" << endl;
		
		for(uint i = 0; i < elements.count(); i++)
		{
			stream << "<span style='";
			stream << "width: " << elements[i].label().length()*10 << ";'>";
			stream << elements[i].label() << "</span>" << endl;
		}
		
		stream << "</div></td></tr></table><br>";
		
		stream << footer << endl;
	}
}

