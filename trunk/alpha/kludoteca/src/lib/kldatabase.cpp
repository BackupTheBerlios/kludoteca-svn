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
	// TODO: Aqui debemos crear las tablas, falta quitar todos los privilegios!! y crear indices
	QSqlQuery q;
	bool wasgood = true;
	int p = 1;
	
	
	// JUEGOS
	q = exec("CREATE TABLE ldt_games ("
		"serialReference character varying(8) primary key,"
		"gameName character varying(50) NOT NULL,"
		"description text NOT NULL,"
		"rules text NOT NULL,"
		"minGamers int NOT NULL,"
		"maxGamers int NOT NULL,"
		"gameType character varying(10) NOT NULL,"
		"timeUnitAdd character varying(10) NOT NULL,"
		"timeUnit character varying(10) NOT NULL,"
		"costTM real NOT NULL,"
		"costTMA real NOT NULL,"
		"position character varying(10) NOT NULL,"
		"state character varying (10) NOT NULL,"
		"available boolean DEFAULT 't' NOT NULL"
		");");
	
	if ( ! q.isActive() ) 
	{
		std::cout << "Fails to create ldt_games" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	
	// PERSONAS
	q = exec("CREATE TABLE ldt_persons ("
		"docIdent character varying(10)  primary key,"
		"firstName character varying(50) NOT NULL,"
		"lastName character varying(50) NOT NULL,"
		"phone character varying(15),"
		"celullar character varying(15),"
		"email character varying(60),"
		"address character varying(40),"
		"genre character varying (10)"
		");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_persons" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// CLIENTES 
	q = exec("CREATE TABLE ldt_clients ("
			"docIdent character varying(10) references ldt_persons(docIdent)  on delete cascade on update cascade,"
			"inscriptionDate date NOT NULL,"
			"state character varying(10),"
			"idReferencePerson character varying(10) references ldt_persons(docIdent),"
			"primary key(docIdent)"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_clients" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// USUARIOS 
	
	q = exec("CREATE TABLE ldt_users ("
			"docIdent character varying(10) references ldt_persons(docIdent) on delete cascade on update cascade,"
			"login character varying(20) primary key,"
			"permissions character varying(10) NOT NULL"
			");");
	
	if ( ! q.isActive() ) 
	{
		std::cout << "Fails to create ldt_users" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// TORNEO
	q = exec("CREATE TABLE ldt_tournament ("
			"name character varying(50) PRIMARY KEY,"
			"gameReference character varying(8) references ldt_games(serialReference) on delete cascade on update cascade,"
			"initDate date NOT NULL,"
			"endDate date NOT NULL,"
			"roundsForPair integer NOT NULL,"
			"rounds integer NOT NULL,"
			"price real NOT NULL,"
			"discount real,"
			"active boolean DEFAULT 't' NOT NULL"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_tournament" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// PARTICIPA
	
	q = exec("CREATE TABLE ldt_participates ("
			"clientDocIdent character varying(15) references ldt_clients(docIdent) on delete cascade on update cascade,"
			"codTournament character varying(50) references ldt_tournament(name) on delete cascade on update cascade,"
			"rank integer,"
			"primary key(clientDocIdent, codTournament)"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_participates" << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// ALQUILA
	q = exec("CREATE TABLE ldt_rents ("
			"clientDocIdent character varying(10) NOT NULL,"
			"gameSerialReference character varying(10) NOT NULL,"
			"returnHour time without time zone NOT NULL,"
			"date date NOT NULL,"
			"foreign key (clientDocIdent) references ldt_clients(docIdent) on delete cascade on update cascade,"
			"foreign key (gameSerialReference) references ldt_games(serialReference) on delete cascade on update cascade"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_rents error is " << lastError().text() << std::endl;
		wasgood = false;
	}
	
	emit progress(p++);
	
	// RONDAS
	q = exec("CREATE TABLE ldt_rounds ("
			"nRound integer NOT NULL,"
			"codTournament character varying(50) references ldt_tournament(name) on delete cascade on update cascade,"
	
			"primary key(nRound, codTournament)"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_rounds" << lastError().text() << std::endl;
		wasgood = false;
	}
	emit progress(p++);
	
	// PARTIDA
	q = exec("CREATE TABLE ldt_match ("
			"number integer primary key,"
			"nRound integer,"
			"codTournament character varying(50),"
			"opponent1 character varying(10),"
			"resultOpp1 integer NOT NULL,"
			"opponent2 character varying(10),"
			"resultOpp2 integer NOT NULL,"
			"foreign key (nRound, codTournament) references ldt_rounds(nRound, codTournament) on delete cascade on update cascade,"
			"foreign key (opponent1,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade,"
			"foreign key (opponent2,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_match" << lastError().text() << std::endl;
		wasgood = false;
	}
	emit progress(p++);
	
	
	// EMPRESA
	q = exec("CREATE TABLE ldt_enterprise ("
			"nit character varying(10) NOT NULL,"
			"address character varying(40) NOT NULL,"
			"name character varying(50) NOT NULL,"
			"phone character varying(10) NOT NULL,"
			"city character varying(15) NOT NULL,"
			"primary key(nit)"
			");");
	
	if ( ! q.isActive() )
	{
		std::cout << "Fails to create ldt_enterprise" << lastError().text() << std::endl;
		wasgood = false;
	}
	emit progress(p++);
	
	// Por ultimo creamos las vistas
	if ( wasgood )
	{
		exec("create view ldt_users_view as SELECT firstname,lastname,login from ldt_users,ldt_persons where ldt_persons.docident in (select ldt_users.docident from ldt_persons )");
		exec("create view ldt_tournament_view as select name,gamename,initdate,active from ldt_tournament,ldt_games where ldt_games.serialreference in ( select gamereference from ldt_games )");
		exec("create view ldt_clients_view as SELECT ldt_clients.docIdent,firstname,lastname,state from ldt_clients,ldt_persons where ldt_persons.docIdent in (select ldt_clients.docident from ldt_persons );");
		exec("create view ldt_rents_view as select gameserialreference,clientdocident, gamename,firstname,lastname from ldt_games,ldt_persons,ldt_rents where ldt_persons.docident in ( select clientdocident from ldt_persons )  and serialreference  in ( select gameserialreference from ldt_games );");
	}
	return wasgood;
}

bool KLDatabase::dropTables()
{
	std::cout << "Dropping tables" << std::endl;
	exec("drop table ldt_users cascade");
	exec("drop table ldt_participates cascade");
	exec("drop table ldt_rents cascade");
	exec("drop table ldt_tournament cascade");
	exec("drop table ldt_clients cascade");
	exec("drop table ldt_games cascade");
	exec("drop table ldt_rounds cascade");
	exec("drop table ldt_match cascade");
	exec("drop table ldt_enterprise cascade");
	exec("drop table ldt_persons cascade");
	
	// Quitamos las vistas
	exec("drop view ldt_users_view cascade");
	exec("drop table ldt_clients_view cascade");
	exec("drop table ldt_tournament_view cascade");
	return true;
}

#include "kldatabase.moc"
