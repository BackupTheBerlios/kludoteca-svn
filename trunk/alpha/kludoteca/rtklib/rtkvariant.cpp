/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkvariant.cpp RTK Variant like QVariant
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

#include <float.h>
#include <stdio.h> // sprintf
#include <stdlib.h> // atoi
#include "rtkvariant.h"
#include <qimage.h>

using namespace RTK;


bool Variant::isNumeric( Type type )
{
	return ( type == tInt || type == tUInt
	         || type == tDouble || type == tMoney
	         || type == tBool );
}


Variant::Variant( const Variant &other)
{
#ifdef FRENETIC_DEBUG
	qDebug("Copio el variant en %x al variant en %x", &other, this);
#endif	
	mType = other.mType;
	if ( mType == tVariantRef ) {
		value.pv = const_cast<Variant *>( &other );
	} else
		switch ( mType ) {
		case Invalid:
			break;
		case tBool:
			value.b = other.toBool();
			break;
		case tInt:
			value.i = other.toInt();
			break;
		case tUInt:
			value.u = other.toUInt();
			break;
		case tDouble:
			value.d = other.toDouble();
			break;
		case tString:
			value.ps = new QString( other.toString() );
			break;
		case tDate:
			value.pd = new QDate( other.toDate() );
			break;
		case tTime:
			value.pt = new QTime( other.toTime() );
			break;
		case tDateTime:
			value.pdt = new QDateTime( other.toDateTime() );
			break;
		case tColor:
			value.pc = new QColor( other.toColor() );
			break;
		case tImage:
			value.pi = new QImage(  ); // OJO
			break;
		case tByteArray:
			value.pba = new QByteArray( other.toByteArray() );
			break;
		case tMoney:
			value.pm = new Money( other.toMoney() );
			break;
		default:
			break;
		}
}

/*
    Constructs a new variant which is a pointer to another variant
*/
Variant::Variant( Variant *val )
{
#ifdef FRENETIC_DEBUG
	qDebug("Construyo un variant a partir de un puntero a variant", val);
#endif	
	mType = tVariantRef;
	value.pv = val;
}

Variant::Variant( bool val )
{
#ifdef FRENETIC_DEBUG
	qDebug("Construyo un variant en %x a partir de un bool con valor %d", this, val);
#endif	
	mType = tBool;
	value.b = val;
}

Variant::Variant( int val )
{
#ifdef FRENETIC_DEBUG
	qDebug("Construyo un variant en %x a partir de un entero con valor %d", this, val);
#endif	
	mType = tInt;
	value.i = val;
}

Variant::Variant( uint val )
{
	mType = tUInt;
	value.i = val;
}

Variant::Variant( long val )
{
	mType = tInt;
	value.i = val;
}

Variant::Variant( double val )
{
	mType = tDouble;
	value.d = val;
}

Variant::Variant( const QString &val )
{
#ifdef FRENETIC_DEBUG
	qDebug("Construyo un variant en %x a partir de un QString con valor %s", this, (const char *)val);
#endif	
	mType = tString;
	value.ps = new QString( val );
}

Variant::Variant( const char *val )
{
#ifdef FRENETIC_DEBUG
	qDebug("Construyo un variant a partir de un char * con valor %s", (const char *)val);
#endif	
	mType = tString;
	value.ps = new QString( val );
}

Variant::Variant( const QDate &val )
{
	mType = tDate;
	value.pd = new QDate( val );
}

Variant::Variant( const QTime &val )
{
	mType = tTime;
	value.pt = new QTime( val );
}

Variant::Variant( const QDateTime &val )
{
	mType = tDateTime;
	value.pdt = new QDateTime( val );
}

Variant::Variant( const QColor &val )
{
	mType = tColor;
	value.pc = new QColor( val );
}

Variant::Variant( const QImage &val )
{
	mType = tImage;
	value.pi = new QImage( val );
}

Variant::Variant( const QByteArray &val )
{
	mType = tByteArray;
	value.pba = new QByteArray( val );
}

Variant::Variant( const Money &val )
{
	mType = tMoney;
	value.pm = new Money( val );
}

Variant::Variant( const QVariant &val ) 
{
	switch ( val.type() ) {
	case QVariant::Bool:
		mType = tBool;
		value.i = val.toBool();
		break;
	case QVariant::Int:
		mType = tInt;
		value.i = val.toInt();
		break;
	case QVariant::UInt:
		mType = tUInt;
		value.u = val.toUInt();
		break;
	case QVariant::Double:
		mType = tDouble;
		value.d = val.toDouble();
		break;
	case QVariant::Date: 
		mType = tDate;
		value.pd = new QDate(val.toDate());
		break;
	case QVariant::Time:
		mType = tTime;
		value.pt = new QTime(val.toTime());
		break;
	case QVariant::DateTime:
		mType = tDateTime;
		value.pdt = new QDateTime(val.toDateTime());
		break;
	case QVariant::String:
	case QVariant::CString:
		mType = tString;
		value.ps = new QString(val.toString());
		break;
	case QVariant::ByteArray:   // Text fields
		mType = tByteArray;
		value.pba = new QByteArray(val.toByteArray());
		break;
	case QVariant::Color:		
		mType = tColor;
		value.pc = new QColor(val.toColor());
		break;
	default:
		qFatal( "RTK:Variant(QVariant):Tipo de variant desconocido %d, %s", val.type(), val.typeToName(val.type()) );
	}
}



/*******************************************************************************************************/

/*!
    Returns the variant as a bool if the variant can be cast to tBool;
    otherWise returns FALSE.
 
    Returns TRUE if the variant has a numeric type and its value is
    non-zero, or if the variant has type tString, tByteArray or CString
    and its lower-case content is not empty, "0" or "false"; otherwise
    returns FALSE.
 
    \sa asBool(), canCast()
*/
bool Variant::toBool() const
{
	switch ( mType ) {
	case tBool:
		return value.b;
	case tDouble:
		return value.d != 0.0;
	case tInt:
		return value.i != 0;
	case tUInt:
		return value.u != 0;
	case tString:
	case tByteArray: {
			QString str = toString().lower();
			return !( str == "0" || str == "false" || str.isEmpty() );
		}
	case tMoney:
		return ( value.pm->toInt() != 0 );
	case tVariantRef:
		return value.pv->toBool();
	default:
		return false;
	}
}



/*!
    Returns the variant as an unsigned int if the variant can be cast
    to tUInt; otherwise returns 0.
 
    If \a ok is non-null: \a *ok is set to TRUE if the value could be
    converted to an unsigned int; otherwise \a *ok is set to FALSE.
 
    \sa asUInt(), canCast()
*/
uint Variant::toUInt( bool * ok ) const
{
	if ( ok )
		* ok = canCast( tUInt );

	switch ( mType ) {
	case tString:
		return value.ps->toUInt( ok );
	case tByteArray:
		return QString( *value.pba ).toUInt( ok );
	case tInt:
		return ( uint ) value.i;
	case tUInt:
		return value.u;
	case tDouble:
		return ( uint ) value.d;
	case tBool:
		return ( uint ) value.b;
	case tMoney:
		return ( uint ) value.pm->toInt();
	case tVariantRef:
		return value.pv->toUInt();
	default:
		return 0;
	}
}

/*!
    Returns the variant as an int if the variant can be cast to tInt;
    otherwise returns 0.
 
    If \a ok is non-null: \a *ok is set to TRUE if the value could be
    converted to an int; otherwise \a *ok is set to FALSE.
 
    \sa asInt(), canCast()
*/
int Variant::toInt( bool * ok ) const
{
	if ( ok )
		* ok = canCast( tInt );

	switch ( mType ) {
	case tString:
		return value.ps->toInt( ok );
	case tByteArray:
		return QString( *value.pba ).toInt( ok );
	case tInt:
		return value.i;
	case tUInt:
		return ( int ) value.u;
	case tDouble:
		return ( int ) value.d;
	case tBool:
		return ( int ) value.b;
	case tMoney:
		return value.pm->toInt();
	case tVariantRef:
		return value.pv->toInt();
	default:
		return 0;
	}
}



/*!
    Returns the variant as a double if the variant can be cast to
    tDouble; otherwise returns 0.0.
 
    If \a ok is non-null: \a *ok is set to TRUE if the value could be
    converted to a double; otherwise \a *ok is set to FALSE.
 
    \sa asDouble(), canCast()
*/
double Variant::toDouble( bool * ok ) const
{
	if ( ok )
		* ok = canCast( tDouble );

	switch ( mType ) {
	case tString:
		return value.ps ->toDouble( ok );
	case tByteArray:
		return QString( *value.pba ).toDouble( ok );
	case tDouble:
		return value.d;
	case tInt:
		return ( double ) value.i;
	case tBool:
		return ( double ) value.b;
	case tUInt:
		return ( double ) value.u;
	case tMoney:
		return value.pm->toDouble();
	case tVariantRef:
		return value.pv->toDouble();
	default:
		return 0.0;
	}
}


/*!
    Returns the variant as a QString if the variant can be cast to
    tString, otherwise returns QString::null.
 
    \sa asString(), canCast()
*/
const QString Variant::toString() const
{
	switch ( mType ) {
	case tInt:
		return QString::number( toInt() );
	case tUInt:
		return QString::number( toUInt() );
	case tDouble:
		return QString::number( toDouble(), 'g', DBL_DIG );
	case tDate:
		return toDate().toString( Qt::ISODate );
	case tTime:
		return toTime().toString( Qt::ISODate );
	case tDateTime:
		return toDateTime().toString( Qt::ISODate );
	case tBool:
		return toInt() ? "true" : "false";
	case tByteArray:
		return QString( *value.pba );
	case tColor:
		return toColor().name();
	case tString:
		return *value.ps;
	case tMoney:
		return value.pm->toString();
	case tVariantRef:
		return value.pv->toString();
	default:
		return QString::null;
	}
}


/*!
    Returns the variant as a QDate if the variant can be cast to tDate;
    otherwise returns an invalid date.
 
    Note that if the type() is tString, CString or tByteArray an invalid
    date will be returned if the string cannot be parsed as a
    Qt::ISODate format date.
 
    \sa asDate(), canCast()
*/
const QDate Variant::toDate() const
{
	switch ( mType ) {
	case tDate:
		return * ( value.pd );
	case tDateTime:
		return value.pdt->date();
	case tString:
		return QDate::fromString( *value.ps, Qt::ISODate );
	case tByteArray:
		return QDate::fromString( toString(), Qt::ISODate );
	case tVariantRef:
		return value.pv->toDate();
	default:
		return QDate();
	}
}

/*!
    Returns the variant as a QTime if the variant can be cast to tTime;
    otherwise returns an invalid date.
 
    Note that if the type() is tString, CString or tByteArray an invalid
    time will be returned if the string cannot be parsed as a
    Qt::ISODate format time.
 
    \sa asTime()
*/
const QTime Variant::toTime() const
{
	switch ( mType ) {
	case tTime:
		return * ( value.pt );
	case tDateTime:
		return value.pdt->time();
	case tString:
		return QTime::fromString( *value.ps, Qt::ISODate );
	case tByteArray:
		return QTime::fromString( toString(), Qt::ISODate );
	case tVariantRef:
		return value.pv->toTime();
	default:
		return QTime();
	}
}

/*!
    Returns the variant as a QDateTime if the variant can be cast to
    tDateTime; otherwise returns an invalid QDateTime.
 
    Note that if the type() is tString, CString or tByteArray an invalid
    QDateTime will be returned if the string cannot be parsed as a
    Qt::ISODate format date/time.
 
    \sa asDateTime()
*/
const QDateTime Variant::toDateTime() const
{
	switch ( mType ) {
	case tDateTime:
		return * value.pdt;
	case tString:
		return QDateTime::fromString( *value.ps, Qt::ISODate );
	case tByteArray:
		return QDateTime::fromString( toString(), Qt::ISODate );
	case tDate:
		return QDateTime( *value.pd );
	case tVariantRef:
		return value.pv->toDateTime();
	default:
		return QDateTime();
	}
}

/*!
    Returns the variant as a QByteArray if the variant can be cast to
    a tByteArray; otherwise returns an empty bytearray.
 
    \sa asByteArray(), canCast()
*/
const QByteArray Variant::toByteArray() const
{
	switch ( mType ) {
	case tByteArray:
		return * ( value.pba );
	case tVariantRef:
		return value.pv->toByteArray();
	default: {
			QByteArray ret;
			if ( canCast( tString ) ) {
				QString c = toString();
				ret.duplicate( c.latin1(), c.length() );
			}
			return ret;
		}
	}
}


/*!
    Returns the variant as a QColor if the variant can be cast to tColor;
    otherwise returns an invalid color.
 
    \sa asColor(), canCast()
*/
const QColor Variant::toColor() const
{
	switch ( mType ) {
	case tByteArray:
	case tString: {
			QColor col;
			col.setNamedColor( toString() );
			return col;
		}
	case tColor:
		return *value.pc;
	case tVariantRef:
		return value.pv->toColor();
	default:
		return QColor();
	}
}


/*!
    Returns the variant as a Image if the variant has type() Image;
    otherwise returns a null image.
 
    \sa asImage()
*/
const QImage *Variant::toImage() const
{
	if ( mType == tVariantRef )
		return value.pv->toImage();
	else if ( mType != tImage )
		return 0;
	else
		return value.pi;
}


const Money Variant::toMoney( bool * ok ) const
{
	if ( ok )
		* ok = canCast( tMoney );

	switch ( mType ) {
	case tMoney:
		return * value.pm;
	case tVariantRef:
		return value.pv->toMoney();
	case tString:
		return Money( toDouble( ok ) );
	case tInt:
		return Money( ( long ) toInt() );
	case tUInt:
		return Money( ( long ) toUInt() );
	case tDouble:
		return Money( ( double ) toDouble() );
	case tBool:
		return Money( ( long ) toBool() );
	default:
		return Money();
	}
}


/*!
    Compares this Variant with \a v and returns TRUE if they are
    equal; otherwise returns FALSE.
*/

bool Variant::operator==( const Variant &v ) const
{
	if ( mType == tVariantRef )
		return *value.pv == v;
	else if ( isNumeric( v.type() ) && canCast( v.type() ) ) {
		bool ok;
		switch ( v.type() ) {
		case tBool:
			return toBool() == v.toBool();
		case tInt: {
				int val = toInt( &ok );
				return ( ok && val == v.toInt() );
			}
		case tUInt: {
				uint val = toUInt( &ok );
				return ( ok && val == v.toUInt() );
			}

		case tDouble: {
				double val = toDouble( &ok );
				return ( ok && val == v.toDouble() );
			}
		case tMoney: {
				Money val = toMoney( &ok );
				return ( ok && val == v.toMoney() );
			}
		default:
			Q_ASSERT( false );
		}
	}

	if ( !v.canCast( mType ) ) {
		return false;
	}

	switch ( mType ) {
	case tString:
		return v.toString() == toString();
	case tImage:
		return v.toImage() == toImage();
	case tColor:
		return v.toColor() == toColor();
	case tInt:
		return v.toInt() == toInt();
	case tUInt:
		return v.toUInt() == toUInt();
	case tBool:
		return v.toBool() == toBool();
	case tDouble:
		return v.toDouble() == toDouble();
	case tMoney:
		return v.toMoney() == toMoney();
	case tDate:
		return v.toDate() == toDate();
	case tTime:
		return v.toTime() == toTime();
	case tDateTime:
		return v.toDateTime() == toDateTime();
	case tByteArray:
		return v.toByteArray() == toByteArray();
	case Invalid:
		break;
	default:
		break;
	}
	return false;
}

/*!
    Compares this Variant with \a v and returns TRUE if they are not
    equal; otherwise returns FALSE.
*/

bool Variant::operator!=( const Variant &v ) const
{
	return !( v == *this );
}

/*!
    Returns TRUE if the variant's type can be cast to the requested
    type, \a t. Such casting is done automatically when calling the
    toInt(), toBool(), ... or asInt(), asBool(), ... methods.
*/

bool Variant::canCast( Type t ) const
{
	Type mytype = type();
	if ( mytype == t )
		return true;
	switch ( t ) {
	case tBool:
	case tDouble:
	case tInt:
	case tUInt:
	case tMoney:
		switch ( mytype ) {
		case tBool:
		case tByteArray:
		case tDouble:
		case tInt:
		case tString:
		case tUInt:
		case tMoney:
			return true;
		default:
			break;
		}
		break;

	case tByteArray:
	case tString:
		switch ( mytype ) {
		case tBool:
		case tByteArray:
		case tColor:
		case tDate:
		case tDateTime:
		case tDouble:
		case tInt:
		case tString:
		case tTime:
		case tUInt:
		case tMoney:
			return TRUE;
		default:
			break;
		}
		break;

	case tTime:
		if ( mytype == tDate )
			break;
	case tDate:
	case tDateTime:
		switch ( mytype ) {
		case tByteArray:
		case tDate:
		case tDateTime:
		case tString:
			return TRUE;
		default:
			break;
		}
		break;

	case tColor:
		switch ( mytype ) {
		case tByteArray:
		case tString:
			return true;
		default:
			break;
		}
		break;

	case Invalid:
	case tImage:
	default:
		break;
	}
	return false;
}


void Variant::clear()
{
#ifdef FRENETIC_DEBUG
	qDebug("Destruyo el variant en %x", this);
#endif	
	switch ( mType ) {
	case tString:
		delete value.ps;
		break;
	case tDate:
		delete value.pd;
		break;
	case tTime:
		delete value.pt;
		break;
	case tDateTime:
		delete value.pdt;
		break;
	case tColor:
		delete value.pc;
		break;
	case tByteArray:
		delete value.pba;
		break;
	case tMoney:
		delete value.pm;
		break;
	case tImage:
		delete value.pi;
		break;
	default:
		break;
	}
}


Variant& Variant::operator= ( const Variant& other )
{
#ifdef FRENETIC_DEBUG
	qDebug("Asigno el variant en %x al variant en %x", &other, this);
#endif	
	if ( this == &other )
		return * this;
	clear();
	mType = other.mType;
	if ( mType == tVariantRef ) {
		value.pv = const_cast<Variant *>( &other );
	} else
		switch ( mType ) {
		case Invalid:
			break;
		case tBool:
			value.b = other.toBool();
			break;
		case tInt:
			value.i = other.toInt();
			break;
		case tUInt:
			value.u = other.toUInt();
			break;
		case tDouble:
			value.d = other.toDouble();
			break;
		case tString:
			value.ps = new QString( other.toString() );
			break;
		case tDate:
			value.pd = new QDate( other.toDate() );
			break;
		case tTime:
			value.pt = new QTime( other.toTime() );
			break;
		case tDateTime:
			value.pdt = new QDateTime( other.toDateTime() );
			break;
		case tColor:
			value.pc = new QColor( other.toColor() );
			break;
		case tImage:
			value.pi = new QImage( /* Ojo other.toImage() */ );
			break;
		case tByteArray:
			value.pba = new QByteArray( other.toByteArray() );
			break;
		case tMoney:
			value.pm = new Money( other.toMoney() );
			break;
		default:
			break;
		}
	return *this;		
}

Variant& Variant::operator+= ( const Variant& other )
{
	switch ( mType ) {
	case Invalid:
		break;
	case tBool:
		value.b |= other.toBool();
		break;
	case tInt:
		value.i += other.toInt();
		break;
	case tUInt:
		value.u += other.toUInt();
		break;
	case tDouble:
		value.d += other.toDouble();
		break;
	case tString:
		value.ps->operator+=( other.toString() );
		break;
	case tDate:
//		value.pd->operator+=( other.toInt() );
		break;
	case tTime:
//		value.pt->operator+=( other.toInt() );
		break;
	case tDateTime:
//		value.pdt->operator+=( other.toInt() );
		break;
	case tColor:
		break;
	case tImage:
		break;
	case tByteArray:
		break;
	case tMoney:
		value.pm->operator+= ( other.toMoney() );
		break;
	default:
		break;
	}
	return *this;
}



Variant::Type Variant::QVariantTypeToVariantType( QVariant::Type val )
{
	switch ( val ) {
	case QVariant::Int:
		return Variant::tInt;
	case QVariant::UInt:
		return Variant::tUInt;
	case QVariant::Double:
		return Variant::tDouble;
	case QVariant::Date: 
		return Variant::tDate;
	case QVariant::Time:
		return Variant::tTime;
	case QVariant::DateTime:
		return Variant::tDateTime;
	case QVariant::Bool:
		return Variant::tBool;
	case QVariant::String:
	case QVariant::CString:
		return Variant::tString;
	case QVariant::ByteArray:  
		return Variant::tByteArray;
	case QVariant::Image:
		return Variant::tImage;
	case QVariant::Color:
		return Variant::tColor;
	default:
		qFatal( "RTK:Variant:QVariantTypeToVariantType:Tipo de variant desconocido %d", val );
		return Variant::Invalid;
	}
}

Variant::Type Variant::nameToType( const char* name )
{
	if( qstricmp( name, "int" ) == 0  || qstricmp( name, "integer" ) == 0 
	 || qstricmp( name, "number" ) == 0)  
		return tInt;
	else if( qstricmp( name, "bool" ) == 0  || qstricmp( name, "boolean" ) == 0 )  
		return tBool;
	else if( qstricmp( name, "unsigned" ) == 0  || qstricmp( name, "uint" ) == 0 )  
		return tUInt;
	else if( qstricmp( name, "float" ) == 0  || qstricmp( name, "double" ) == 0 )  
		return tDouble;
	else if( qstricmp( name, "date" ) == 0  )  
		return tDate;
	else if( qstricmp( name, "time" ) == 0 )
		return tTime;
	else if( qstricmp( name, "datetime" ) == 0  || qstricmp( name, "timestamp" ) == 0 )  
		return tDateTime;
	else if( qstricmp( name, "color" ) == 0 )  
		return tColor;
	else if( qstricmp( name, "image" ) == 0  || qstricmp( name, "picture" ) == 0 )  
		return tImage;
	else if( qstricmp( name, "bytearray" ) == 0  || qstricmp( name, "blob" ) == 0 )  
		return tByteArray;
	else if( qstricmp( name, "currency" ) == 0  || qstricmp( name, "money" ) == 0 )  
		return tMoney;
	else if( qstricmp( name, "cfunction" ) == 0 )  
		return tCFunctionType;
	else if( qstricmp( name, "reference" ) == 0 || qstricmp( name, "ref" ) == 0 )  
	    return tVariantRef;
	else
		return tString;
}

