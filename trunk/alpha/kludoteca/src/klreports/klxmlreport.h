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

#ifndef KLXMLREPORT_H
#define KLXMLREPORT_H

#include <qdom.h>
#include <qcolor.h>
#include <qstring.h>

/**
 * @author David Cuadrado
*/

class KLXmlReport : public QDomDocument
{
	public:
		enum ChartType { PIE, VERTICAL_BAR, HORIZONTAL_BAR };
		KLXmlReport(const QString &title = QString::null, const QString &enterprise= QString::null, const QString &nit= QString::null, ChartType t = PIE);
		~KLXmlReport();
		
		void createReportElement(double value, const QString &label, const QColor &color, Qt::BrushStyle t = Qt::SolidPattern);

};

#endif
