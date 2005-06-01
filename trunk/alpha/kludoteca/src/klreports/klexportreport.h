/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                            	   *
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

#ifndef KLEXPORTREPORT_H
#define KLEXPORTREPORT_H

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>

#include "klxmlreportparser.h"
#include "klxmlreport.h"


/**
 * @author David Cuadrado
*/

class KLExportReport
{
	public:
		enum Type { HTML = 0 };
		KLExportReport(const KLXmlReport &report, const QString file, int t);
		KLExportReport(const QString file, int t);
		~KLExportReport();
		void exportToHtml(const KLXmlReport &report);
		
	private:
		QString m_file;
		int m_type;
};

#endif
