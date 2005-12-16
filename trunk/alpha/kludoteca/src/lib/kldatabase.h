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

#include "klquery.h"

#include "klresultset.h"

class KLDatabase;

/**
 * @short The Kludoteca Database manager (aka KLDM)
 * Esta clase manejara las conexiones a la base de datos
 * @author CetiSoft
*/
class KLDatabase : public QSqlDatabase
{
	Q_OBJECT
	protected:
    		/**
    		 * Constructor
    		 * @param parent 
    		 * @return 
    		 */
    		KLDatabase(QObject *parent = 0);
		
    		/**
    		 * Destructor
    		 * @return 
    		 */
    		~KLDatabase();
		
	public:
		static KLDatabase *instance();
		
		/**
		 * Sirve para hacer una consulta a la base de datos
		 * @param consult 
		 * @return 
		 */
		KLResultSet execQuery(const QString  &consult, QStringList fields = QStringList());
		
		/**
		 * Coloca el nombre de la base de datos
		 * @param dbname 
		 */
		void setDatabaseName ( const QString & dbname );
		/**
		 * Coloca el usuario de la base de datos
		 * @param login 
		 */
		void setUserName ( const QString & login );
		/**
		 * Coloca el password de la base de datos.
		 * @param password 
		 */
		void setPassword ( const QString & password );
		/**
		 * Coloca el hostname de la base de datos.
		 * @param host 
		 */
		void setHostName ( const QString & host );
		/**
		 * Pone el puerto.
		 * @param p 
		 */
		void setPort ( int p );
		
		/**
		 * Configura la conexion, y la deja lista para ser utilizada. 
		 * @param dbname 
		 * @param login 
		 * @param password 
		 * @param host 
		 */
		void setupConnection(const QString & dbname, const QString & login, const QString & password, const QString & host );

		/**
		 * Funcion de alto nivel para realizar consultas
		 * @b NOTA: Esta funcion esta obsoleta, use en su lugar execQuery(KLQuery *query)
		 * @param fields 
		 * @param table 
		 * @param selectparams 
		 * @return KLResultSet el cual es un documento XML con las consultas.
		 */
		KLResultSet select(QStringList fields, QString table, QString selectparams = QString::null);
		
		/**
		 * Crea las tablas de la aplicacion
		 */
		bool createTables(); // Defined in createdatabase.cpp
		
		/**
		 * Elimina las tablas
		 */
		bool dropTables(); // Defined in createdatabase.cpp
		
		/**
		 * Determina si la ultima consulta produjo error
		 */
		bool isLastError();
		
		QString getLastError();
		
	signals:
		/**
		 *  Marca el progreso de una consulta
		 * @param p 
		 */
		void progress(int p);
		
		/**
		 * Este slot se emite cuando se ha realizado una consulta y envia verdadero en caso de que la consulta sea exitosa y falso en cualquier otro caso
		 */
		void executed(bool good);
		
		
	public slots:
		/**
		 * Funcion de alto nivel para realizar consultas
		 * @param query 
		 * @return 
		 */
		KLResultSet execQuery(KLQuery *query);
		
		/**
		 * Funcion de bajo nivel para realizar consultas
		 */
		void execRawQuery(const QString &sql);
		
	private:
		static KLDatabase *m_instance;
		bool lastIsBad; 
		QString m_lastError;
};

#define KLDM KLDatabase::instance()

#endif
