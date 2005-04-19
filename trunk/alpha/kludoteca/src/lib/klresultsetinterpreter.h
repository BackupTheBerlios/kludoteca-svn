/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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

#ifndef KLRESULTSETINTERPRETER_H
#define KLRESULTSETINTERPRETER_H

#include <qobject.h>
#include <qxml.h>

/**
 * Esta clase representa al interprete de las consultas XML.
 * @author CetiSoft
*/

class KLResultSetInterpreter : public QObject, public QXmlDefaultHandler
{
	Q_OBJECT
	public:
    		/**
    		 * Constructor por defecto
    		 * @return 
    		 */
		KLResultSetInterpreter();
		
    		/**
    		 * Destructor
    		 * @return 
    		 */
    		~KLResultSetInterpreter();
		/**
		 * Elementos de inicio
		 * @param  
		 * @param  
		 * @param qname 
		 * @param atts 
		 * @return 
		 */
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
		
		
	signals:
		/**
		 * Se emite cuando un record es leido
		 * @param results 
		 */
		void readRecord(QStringList results);
		
	private:
		QString m_root, m_qname;
		bool m_read;
		QStringList m_results;
};

#endif
