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

#include "kldatabase.h"
#include <klocale.h>
#include <iostream>

KLDatabase::KLDatabase(QObject *parent) : QSqlDatabase("QPSQL7", "KLudoteca", parent  ), lastIsBad(false)
{
}


KLDatabase::~KLDatabase()
{
}

KLDatabase *KLDatabase::instance()
{
	static KLDatabase *skdb = new KLDatabase;
	
// 	if ( !skdb->isOpen() )
// 		skdb->open();
	
	return skdb;
}

// TODO: devolveremos un documento XML con la consulta, para hacer consultas a bajo nivel utilizar exec(consulta).
KLResultSet KLDatabase::execQuery(const QString &strquery, QStringList fields)
{
	std::cout << "Consulta para hacerse: " << strquery << std::endl;
	// TODO: Verificar si esta abierta la base de datos, sino abrirla
	KLResultSet theResultSet;
	
	if ( ! isOpen() )
		open();
	
	QSqlQuery query = exec(strquery);
	
	if ( query.isActive() )
	{
		while ( query.next() )
		{
			QStringList results;
			for (uint i = 0; i < fields.count(); i++)
			{
				results << query.value(i).toString();
			}
			theResultSet.setRecord(fields, results);
		}
		lastIsBad = false;
	}
	else
	{
		// TODO: crear una paquete XML de error!.
		qDebug( tr("Error while exec query " + query.executedQuery() ));
		qDebug( lastError().text() );
		lastIsBad = true;
	}
	
	emit executed(!lastIsBad);
	
// 	if (isOpen())
// 		close();
	
	return theResultSet;
}

KLResultSet KLDatabase::select(QStringList fields, QString table, QString selectparams)
{
	QString strquery = "select ";
	
	Q_ASSERT( fields.count() != 0 );
	
	for(uint i = 0; i < fields.count(); i++)
	{
		if ( i == fields.count() - 1)
			strquery += fields[i];
		else
			strquery += fields[i] + ",";
	}
	
	strquery += " from " + table + " " + selectparams +";";
	
	return this->execQuery(strquery, fields);
}

KLResultSet KLDatabase::execQuery(KLQuery *query)
{
	switch( query->getType() )
	{
		case KLQuery::Select:
			return this->execQuery(query->getQuery(), static_cast<KLSelect*>(query)->getFields());
			break;
		case KLQuery::Insert:
			execQuery(query->getQuery());
			break;
		case KLQuery::Update:
			execQuery(query->getQuery());
			break;
		case KLQuery::Delete:
			execQuery(query->getQuery());
			break;
	}

	return KLResultSet();
}

void KLDatabase::execRawQuery(const QString &sql)
{
	exec(sql);
}

void KLDatabase::setDatabaseName(const QString &dbname)
{
	QSqlDatabase::setDatabaseName(dbname);
}

void KLDatabase::setHostName(const QString &host)
{
	QSqlDatabase::setHostName(host);
}

void KLDatabase::setPassword(const QString &password)
{
	QSqlDatabase::setPassword(password);
}

void KLDatabase::setPort(int p)
{
	QSqlDatabase::setPort(p);
}

void KLDatabase::setUserName(const QString &login )
{
	QSqlDatabase::setUserName(login);
}


void KLDatabase::setupConnection(const QString &dbname, const QString & login, const QString & password, const QString & host )
{
	std::cout << "Setting up the database with: " << dbname << " " << login << " " << host << std::endl;
	setDatabaseName(dbname);
	setHostName(host);
	setUserName(login);
	setPassword(password);
}

bool KLDatabase::isLastError()
{
	return lastIsBad;
}

QString KLDatabase::getLastError()
{
	return lastError().text();
}


#include "kldatabase.moc"
