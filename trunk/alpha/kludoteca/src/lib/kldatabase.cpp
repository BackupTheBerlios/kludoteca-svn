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

bool KLDatabase::createTables()
{
	// Aqui debemos crear las tablas, falta quitar todos los privilegios!! y crear indices
	QSqlQuery q;
	bool wasgood = true;
	int p = 1;
	
	q = exec("CREATE TABLE ldt_games ("
			"serialReference character varying(8) NOT NULL,"
			"gameName character varying(10) NOT NULL,"
			"description text NOT NULL,"
			"rules text NOT NULL,"
			"minGamers smallint NOT NULL,"
			"maxGamers smallint NOT NULL,"
			"gameType character varying(10) NOT NULL,"
			"timeUnitAdd character varying(10) NOT NULL,"
			"timeUnit character varying(10) NOT NULL,"
			"costTM real NOT NULL,"
			"costTMA real NOT NULL,"
			"position character varying(10) NOT NULL,"
			"state character varying (10) NOT NULL,"
			"primary key(serialReference));");
	
	if ( ! q.isActive() ) 
	{
		std::cout << "Fails to create ldt_games" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_clients ("
			"docIdent character varying(10) NOT NULL,"
			"inscriptionDate date NOT NULL,"
			"firstName character varying(10) NOT NULL,"
			"lastName character varying(10) NOT NULL,"
			"phone character varying(15),"
			"celular character varying(15),"
			"email character varying(50),"
			"sex character varying(10),"
			"state character varying(10),"
			"address character varying(20),"
			"namereference character varying(15),"
			"phonereference character varying(15),"
			"addressreference character varying(20),"
			"primary key(docIdent));");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_clients" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_tournament ("
			"codTournament character varying(10) NOT NULL,"
			"gameReference character varying(8) NOT NULL,"
			"name character varying(10) NOT NULL,"
			"initDate date NOT NULL,"
			"endDate date NOT NULL,"
			"roundsForPair integer NOT NULL,"
			"rounds integer NOT NULL,"
			"price real NOT NULL,"
			"discount real NOT NULL,"
			"state character varying(10) NOT NULL,"
			"primary key(codTournament),"
			"foreign key(gameReference) references ldt_games(serialReference));");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_tournament" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_enterprise ("
			"nit character varying(10) NOT NULL,"
			"address character varying(20) NOT NULL,"
			"name character varying(10) NOT NULL,"
			"phone character varying(10) NOT NULL,"
			"city character varying(8) NOT NULL,"
			"primary key(nit));");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_enterprise" << lastError().text() << std::endl;
		wasgood = false;
	}
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_users ("
			"docIdent character varying(10) NOT NULL,"
			"login character varying(20) NOT NULL,"
			"firstName character varying(10) NOT NULL,"
			"lastName character varying(10) NOT NULL,"
			"sex character varying(10),"
			"address character varying(20),"
			"phone character varying(10),"
			"email character varying(50),"
			"permissions character varying(10) NOT NULL," // Hay que revisar cuantos modulos son y ajustar esto a un numero de caracteres fijos
			"primary key(login));");
	
	if ( ! q.isActive() ) 
	{
		std::cout << "Fails to create ldt_users" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_participates ("
			"clientDocIdent character varying(15),"
			"codTournament character varying(10),"
			"foreign key (clientDocIdent) references ldt_clients(docIdent),"
			"foreign key (codTournament) references ldt_tournament(codTournament));");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_participates" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	q = exec("CREATE TABLE ldt_rents ("
			"clientDocIdent character varying(10) NOT NULL,"
			"gameSerialReference character varying(10) NOT NULL,"
			"returnHour time without time zone NOT NULL,"
			"date date NOT NULL,"
			"foreign key (clientDocIdent) references ldt_clients(docIdent),"
			"foreign key (gameSerialReference) references ldt_games(serialReference));");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_rents error is " << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	return wasgood;
}

bool KLDatabase::dropTables()
{
	std::cout << "Dropping tables" << std::endl;
	exec("drop table ldt_users cascade");
	exec("drop table ldt_enterprise cascade");
	exec("drop table ldt_participates cascade");
	exec("drop table ldt_rents cascade");
	exec("drop table ldt_tournament cascade");
	exec("drop table ldt_clients cascade");
	exec("drop table ldt_games cascade");
	
	return true;
}

#include "kldatabase.moc"
