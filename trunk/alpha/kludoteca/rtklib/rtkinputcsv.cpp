/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputcsv.cpp RTK standard csv input object
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

#include <qfile.h>
#include "rtkinputcsv.h"

using namespace RTK;


/**
  \class RTK::InputCsv rtkinputcsv.h
  \brief This is an RTK::Input derived class for reading CVS files

*/


bool InputCsv::init()
{
	pFile = new QFile( getFilename() );
	if( !pFile->open(IO_ReadOnly) ) {
		qWarning("RTK:InputCSV:init:unable to open file %s for reading", (const char *)mFilename);
		return false;
	}
	pTextStream = new QTextStream( pFile );
	for( int hl = mHeaderLines; hl>0; hl-- ) // skip them
		pTextStream->readLine();
	return true;
}

InputCsv::~InputCsv()
{
	delete pFile;
}


// Fills the vector of values with the column values
bool InputCsv::next()
{
	if( pTextStream->atEnd() )
		return false;
	QString line = pTextStream->readLine();
	if( line == QString::null )
		return false;
    QString token = "";
	int len = line.length();
	mRowValues.clear();
	QChar quoted = '\0';
	bool escaped = false;
    for( int i = 0; i < len; i++)
    {
		if( !escaped && line[i] == '\\' ) {
			escaped = true;
			continue;
		}
		if( escaped ) {
            token += line[ i ];
			continue;
		}
		if( !quoted	&& (token.length()==0) && getQuote().find( line[ i ] ) >= 0 ) {
			quoted = line[i];
			continue;
		}
		if( quoted && (line[i] == quoted ) ) {
			quoted = '\0';
			continue;
		}
        if ( !quoted && getDelimiters().find( line[ i ] ) >= 0 )
        {
            mRowValues.push_back( token );
            token = "";
        }
        else
        {
            token += line[ i ];
        }
    }
    if ( token.length() > 0 )
    {
        mRowValues.push_back( token );
    }
	return mRowValues.size();
}


Variant InputCsv::getValue(const String &fldname)
{
	InputField *ifld = getInputField(fldname);
	if( ifld ) {
		return correctType( ifld->getType(), mRowValues[ifld->getSource().toInt()] );
	} else
		return Variant();
}

Variant InputCsv::correctType(Variant::Type t, const String &value)
{
	switch( t ) {
		case Variant::Invalid:
			return Variant();
		case Variant::tInt:
		case Variant::tUInt:
			return value.toInt();
		case Variant::tDouble:
			return value.toDouble();
		case Variant::tMoney:
			return Money(value.toDouble());
		case Variant::tDate:
			return Date::fromString(value);
		case Variant::tTime:
			return Time::fromString(value);
		case Variant::tDateTime:
			return DateTime::fromString(value);
		case Variant::tString:
		default:
			return value;
	}
}

