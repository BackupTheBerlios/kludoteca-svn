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
#ifndef KLDATABASE_H
#define KLDATABASE_H

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <iostream>

#include "klresultset.h"

class KLDatabase;

/**
 * @short The Kludoteca Database manager (aka KLDM)
 * Esta clase manejara las conexiones a la base de datos
 * @author CetiSoft
*/
class KLDatabase : public QSqlDatabase
{
	public:
    		/**
    		 * 
    		 * @param parent 
    		 * @return 
    		 */
    		KLDatabase(QObject *parent = 0);
    		/**
    		 * 
    		 * @return 
    		 */
    		~KLDatabase();
		
		/**
		 * 
		 * @param consult 
		 * @return 
		 */
		QSqlQuery query(const QString  &consult);
		
		/**
		 * 
		 * @param dbname 
		 */
		void setDatabaseName ( const QString & dbname );
		/**
		 * 
		 * @param login 
		 */
		void setUserName ( const QString & login );
		/**
		 * 
		 * @param password 
		 */
		void setPassword ( const QString & password );
		/**
		 * 
		 * @param host 
		 */
		void setHostName ( const QString & host );
		/**
		 * 
		 * @param p 
		 */
		void setPort ( int p );
		
		/**
		 * 
		 * @param dbname 
		 * @param login 
		 * @param password 
		 * @param host 
		 */
		void setupConnection(const QString & dbname, const QString & login, const QString & password, const QString & host );

		/**
		 * 
		 * @param fields 
		 * @param table 
		 * @param selectparams 
		 * @return 
		 */
		KLResultSet select(QStringList fields, QString table, QString selectparams = QString::null);
};

#endif
