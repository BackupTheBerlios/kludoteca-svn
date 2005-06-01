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

#ifndef KLXMLREPORTPARSER_H
#define KLXMLREPORTPARSER_H

#include <qxml.h>
#include "klreportelement.h"

/**
 * @author David Cuadrado
*/

class KLXmlReportParser : public QXmlDefaultHandler
{
	public:
		KLXmlReportParser();
		~KLXmlReportParser();
		
		bool startElement(const QString& , const QString& , const QString& qname, const QXmlAttributes& atts);
		
		/**
		 * Elementos al final
		 * @param ns 
		 * @param localname 
		 * @param qname 
		 * @return 
		 */
		bool endElement( const QString& ns, const QString& localname, const QString& qname);
		
		/**
		 * Caracteres entre TAGS.
		 * @param ch 
		 * @return 
		 */
		bool characters ( const QString & ch );
		
		ElementVector getElements();
		
		int getGraphicType();
		
		QString getTitle();
		QString getEnterprise();
		QString getNit();
		
	private:
		QString m_root, m_qname;
		ElementVector m_elements;
		bool m_read;
		
		double m_value;
		int m_graphicType; 
		int m_style;
		QColor m_color;
		QString m_label;
		QString m_title;
		QString m_enterprise;
		QString m_nit;
};

#endif
