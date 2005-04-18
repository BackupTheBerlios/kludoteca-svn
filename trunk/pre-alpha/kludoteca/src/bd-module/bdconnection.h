/********************************************************************************
 *   Copyright (C) 2004 by David Cuadrado                                        	*
 *   cetisoft@linuxmail.org                                                	*
 *                                                                         	*
 *   This program is free software; you can redistribute it and/or modify  	*
 *   it under the terms of the GNU General Public License as published by  	*
 *   the Free Software Foundation; either version 2 of the License, or     	*
 *   (at your option) any later version.                                   	*
 *                                                                         	*
 *   This program is distributed in the hope that it will be useful,       	*
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        	*
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        	*
 *   GNU General Public License for more details.                          	*
 *                                                                         	*
 *   You should have received a copy of the GNU General Public License     	*
 *   along with this program; if not, write to the                         	*
 *   Free Software Foundation, Inc.,                                       	*
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             	*
 *******************************************************************************/

#ifndef SBBDCONEXION_H
#define SBBDCONEXION_H

#include <iostream>
#include <qsqldatabase.h>
#include <qsqlquery.h>

/**
 * Esta clase maneja la configuracion  y conexion de la base de datos.
 * @author David Cuadrado
 */

class BDConnection
{
	private:
		QSqlDatabase *cnx;
		QString bdname, bduser, bdpasswd, bdhost;
	
	public:
		BDConnection(/*QString bddriver, QString name*/);
		~BDConnection();
		void loadDB(const QString bddriver, const QString bdname, const QString bduser, const QString bdpassword, const QString bdhost );
		
		void loadDB(const QString bduser, const QString bdpassword, const QString bdhost);
		QSqlDatabase *getDB(const QString &key) const;
		bool openConnection();
		QSqlQuery query(const QString  &consult = QString::null ) const;
		QString dbName () const;
		QString userName () const;
		QString passwd () const;
		QString host () const;
		
		void setDatabaseName ( const QString & name );
		void setUserName ( const QString & name );
		void setPassword ( const QString & password );
		void setHostName ( const QString & host );
};

#endif
