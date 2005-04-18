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

#include "bdconnection.h"

/**
 * Constructor
 */
BDConnection::BDConnection() : QObject()
{
}

/**
 * Destructor
 */
BDConnection::~BDConnection()
{
}

/**
 * Retorna una instanacia de la conexion
 */
BDConnection *BDConnection::instance()
{
	static BDConnection bd;
	return &bd;
}

/**
 * Esta funcion carga la base de datos
 * @param bddriver: Driver SQL usado para la conexion.
 * @param bdname: Mombre de la base de datos.
 * @param bduser: Usuario de la base de datos
 * @param bdpassword: Password del bduser
 * @param bdhost: Servidor donde esta alojada la base de datos.
 * @see cargarBD(const QString bduser, const QString bdpassword, const QString bdhost)
 */
void BDConnection::loadDB(const QString bddriver, const QString bdname, const QString bduser, const QString bdpassword, const QString bdhost)
{
	std::cout << "Cargando DB: " << bdname << " en " << bdhost << std::endl;
	this->bdname = bdname;
	this->bduser = bduser;
	this->bdpasswd = bdpassword;
	this->bdhost = bdhost;
	
	cnx = QSqlDatabase::addDatabase( bddriver,bdname ); // TODO: Revisar esto!!
	cnx->setDatabaseName ( bdname );
	cnx->setUserName ( bduser );
	cnx->setPassword ( bdpassword );
	cnx->setHostName ( bdhost );
}

/**
 * Esta funcion retorna la conexion configurada pero no abierta, con la base de datos
 * @param key: es el codigo (nombre de la base de datos) que identifica la base de datos.
 * @param open: Abre la conexion y la retorna
 */
QSqlDatabase *BDConnection::getDB(const QString &key, bool open ) const
{
	return QSqlDatabase::database(key, open);
}

/**
 * Esta funcion sobrecargada carga la base de datos
 * @param bduser: Usuario de la base de datos
 * @param bdpassword: Password del bduser
 * @param bdhost: Servidor donde esta alojada la base de datos.
 * @see cargarBD(const QString bddriver, const QString bdname, const QString bduser, const QString bdpassword, const QString bdhost)
 */
void BDConnection::loadDB(const QString bduser, const QString bdpassword, const QString bdhost)
{
	std::cout << "Cargando DB: " << bdname << " en " << bdhost << std::endl;
	this->bdhost = bdhost;
	this->bduser = bduser;
	this->bdpasswd = bdpassword;

	cnx->setUserName ( bduser );
	cnx->setPassword ( bdpassword );
	cnx->setHostName ( bdhost );
}

/**
 * Funcion encargada de abrir la conexion (obsoleta)
 */
bool BDConnection::openConnection()
{
	return cnx->open();
}

/**
 * Funcion encargada de realizar una consulta (obsoleta)
 */
QSqlQuery BDConnection::query(const QString &consulta) const
{
	QSqlQuery queryTmp = cnx->exec(consulta);
	if ( ! queryTmp.isValid() )
		qDebug( queryTmp.lastError().text() );
	return queryTmp;
}

/**
 * Esta funcion retorna el nombre de la base de datos.
 */
QString BDConnection::dbName() const
{
	return bdname;
}

