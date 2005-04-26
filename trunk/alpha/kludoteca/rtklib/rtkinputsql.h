/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputsql.h RTK standard sql input object
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
#ifndef RTKINPUTSQL_H
#define RTKINPUTSQL_H

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>

#include "rtkinput.h"


namespace RTK
{

class InputSql : public Input
{
	/*<<<<<INPUTSQL_CONSTRUCTOR*/
public:
	InputSql(const String& sqldriver = String::null, const String& host = String::null, 
		int port = 0, const String& user = String::null, const String& password = String::null, 
		const String& database = String::null, const String& from = String::null, const String& where = String::null, const String& orderby = String::null,
	const String& name = String::null, const String& driver = String::null)
	:Input(name, driver),
	mSqlDriver(sqldriver), mHost(host), 
		mPort(port), mUser(user), mPassword(password), 
		mDatabase(database), mFrom(from), mWhere(where), mOrderBy(orderby)
/*>>>>>INPUTSQL_CONSTRUCTOR*/
			, pQuery( 0 ), mExternalQuery( false )
	{};

	~InputSql();

	virtual void setQuery( QSqlQuery *query );
	virtual bool init();
	virtual bool next();
	virtual Variant getValue( uint i );
	virtual Variant getValue( const String &/*fldname*/ );

	/*<<<<<INPUTSQL_GETSET*/
public:
	const String& getSqlDriver() const { return mSqlDriver; };
	void setSqlDriver(const String& sqldriver) { mSqlDriver = sqldriver; };
	const String& getHost() const { return mHost; };
	void setHost(const String& host) { mHost = host; };
	int getPort() const { return mPort; };
	void setPort(int port) { mPort = port; };
	const String& getUser() const { return mUser; };
	void setUser(const String& user) { mUser = user; };
	const String& getPassword() const { return mPassword; };
	void setPassword(const String& password) { mPassword = password; };
	const String& getDatabase() const { return mDatabase; };
	void setDatabase(const String& database) { mDatabase = database; };
	const String& getFrom() const { return mFrom; };
	void setFrom(const String& from) { mFrom = from; };
	const String& getWhere() const { return mWhere; };
	void setWhere(const String& where) { mWhere = where; };
	const String& getOrderBy() const { return mOrderBy; };
	void setOrderBy(const String& orderby) { mOrderBy = orderby; };
protected:
	String mSqlDriver;
	String mHost;
	int mPort;
	String mUser;
	String mPassword;
	String mDatabase;
	String mFrom;
	String mWhere;
	String mOrderBy;
/*>>>>>INPUTSQL_GETSET*/
private:
	int fieldPos( const String &name ) const;

	QSqlQuery *pQuery;
	bool mExternalQuery;
	int handleError( QSqlDatabase *db, QSqlError dberr );
	QValueList<String>mFieldNames;
	QValueList<Variant::Type>mFieldTypes;

};

}; // namespace

#endif

