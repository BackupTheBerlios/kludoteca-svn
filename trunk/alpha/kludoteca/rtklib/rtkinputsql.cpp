/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputsql.cpp RTK standard sql input object
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*>>>>>COPYRIGHT*/


//#include <stdio.h>

#include <qdatetime.h>
#include "qsqldriver.h"
#include "rtkinputsql.h"

using namespace RTK;

/*
	The InputSql class provides the data from a SQL Database query.
	The conexion to the database is done with the values defined in the INPUT section of the RTK file and
	the query is constructed based upon the INPUTFIELDS.
	One can use another Query already initialized by calling setQuery(). In that case, the info in the RTK
	file is discarded.
	You can also let RTK read the conexion info from the RTK file and then call setDatabse, setDriver, setUser
	and setPassword to set the conexion before printing the report.
*/
bool InputSql::init()
{
	QSqlDatabase *db;
	if ( !mExternalQuery ) { // The query has not been set programmatically
		db = QSqlDatabase::addDatabase( getSqlDriver(), "rtk" );
		db->setDatabaseName( getDatabase() );
		db->setUserName( getUser() );
		db->setPassword( getPassword() );
		db->setHostName( getHost() );
		if ( !db->open() ) {
			handleError( db, db->lastError() );
			return false;
		}
		pQuery = new QSqlQuery( 0, db );
	} else {
		// We assume the query we have received is from the default connection
		db = QSqlDatabase::database();
		setSqlDriver(db->driverName());
	}
	if( !pQuery->isActive() ) {
		String delim = ((getSqlDriver()=="QPSQL7")?"\"":"`");
		qDebug("(%s,%s)", (const char *) delim, (const char *)getSqlDriver() );
		String select = "SELECT ";
		if ( mInputFields.size() == 0 ) {
			qWarning( "RTK:InputSql:init:There are no inputfields defined. We assume all" );
			select += "* ";
		} else
			for ( uint i = 0; i < mInputFields.size(); i++ ) {
				if ( i > 0 )
					select += ",";
				select += mInputFields[ i ] ->getSource() + " AS " + delim + mInputFields[ i ] ->getName() + delim;
			}
		select += " FROM " + getFrom();
		if ( getWhere().length() != 0 )
			select += " WHERE " + getWhere();
		if ( getOrderBy().length() != 0 )
			select += " ORDER BY " + getOrderBy();
#if DEBUG_RTKINPUT > 0
		qDebug("RTK:InputSql:init:Executing query: %s", (const char *)select);
#endif			
		if ( !pQuery->exec( select ) ) {
			handleError( db, pQuery->lastError() );
			fprintf(stderr, select);
			return false;
		}
#if DEBUG_RTKINPUT > 0
		qDebug("RTK:InputSql:init:Returned %d rows", pQuery->size());
#endif		
	}
	QSqlRecordInfo infoBuffer;
	infoBuffer = pQuery->driver() ->recordInfo( *pQuery );
#if DEBUG_RTKINPUT > 1
	qDebug( "RTK:InputSql:init:Lista de campos de la consulta:" );
#endif

	for ( uint i = 0; i < infoBuffer.size(); ++i ) {
		QSqlFieldInfo &fldinfo = infoBuffer[ i ];
		mFieldNames.push_back( fldinfo.name() );
		InputField *inpf = getInputField(fldinfo.name());
		if( inpf ) {
			if( inpf->getType() != Variant::Invalid ) {
				mFieldTypes.push_back( inpf->getType() );
			} else {
				mFieldTypes.push_back( Variant::QVariantTypeToVariantType(fldinfo.type()) );
			}
		} else {
			mFieldTypes.push_back( Variant::tString );
		}
#if DEBUG_RTKINPUT > 1
		qDebug( "%d:'%s'", i, ( const char * ) fldinfo.name() );
#endif

	}
	return true;
}

InputSql::~InputSql()
{
	setQuery( 0 );
}


bool InputSql::next()
{
	if ( !pQuery->isActive() )
		return false;
	return pQuery->next();
}

Variant InputSql::getValue( const String &fldname )
{
	for( uint i=0; i<mFieldNames.size(); i++ ) {
		if( mFieldNames[i] == fldname ) {
			return getValue(i);
		}
	}
	qWarning("InputSql::getValue(%s): Field not found", (const char *)fldname);
	return Variant();
}

Variant InputSql::getValue( uint i )
{
	if ( i < mFieldNames.size() )
		// Warning:
		// QSqlQuery doesn't return value as Double if the type of the field in the
		// database is numeric with decimals
		if ( mFieldTypes[ i ] == Variant::tDouble )
			return pQuery->value( i ).toDouble();
		else if ( mFieldTypes[ i ] == Variant::tMoney )
			return Money(pQuery->value( i ).toDouble());
		else if ( mFieldTypes[ i ] == Variant::tInt )
			return pQuery->value( i ).toInt();
		else if ( mFieldTypes[ i ] == Variant::tUInt )
			return pQuery->value( i ).toUInt();
		else if ( mFieldTypes[ i ] == Variant::tDate )
			return pQuery->value( i ).toDate();
		else if ( mFieldTypes[ i ] == Variant::tDateTime )
			return pQuery->value( i ).toDateTime();
		else if ( mFieldTypes[ i ] == Variant::tTime )
			return pQuery->value( i ).toTime();
		else
			return pQuery->value( i );
	else
		return Variant();
}


int InputSql::handleError( QSqlDatabase *db, QSqlError dberr )
{
	const char * stype;
	switch ( dberr.type() ) {
	case QSqlError::Connection:
		stype = "Connect";
		break;
	case QSqlError::Statement:
		stype = "Statement";
		break;
	case QSqlError::Transaction:
		stype = "Transaction";
		break;
	case QSqlError::Unknown:
	default:
		stype = "Unknown";
	}
	fprintf( stderr, "RTK:InputSql:init:Error opening database:%s(%d):'%s':%s@%s\nRTK:InputSql:init:%s\nRTK:InputSql:init:%s\n", stype,
	         dberr.number(),
	         ( const char * ) db->databaseName(),
	         ( const char * ) db->userName(),
	         ( const char * ) db->hostName(),
	         ( const char * ) dberr.databaseText(),
	         ( const char * ) dberr.driverText() );
	return dberr.number();
}

int InputSql::fieldPos( const String &name ) const
{
	for ( uint i = 0; i < mFieldNames.size(); i++ )
		if ( mFieldNames[ i ] == name )
			return i;
	return -1;
}



/* 
	Sets an external query. Deletes the previous one if it was internal
*/
void InputSql::setQuery( QSqlQuery *query )
{
	if ( !mExternalQuery ) {
		if ( pQuery )
			delete pQuery;
		mExternalQuery = true;
	}
	pQuery = query;
}
