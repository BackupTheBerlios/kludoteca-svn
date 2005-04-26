/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkvariant.h RTK Variant like QVariant
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
#ifndef RTKVARIANT_H
#define RTKVARIANT_H

#include <qcolor.h>
#include <qvariant.h>
#include "rtknamespace.h"
#include "rtkmoney.h"

namespace RTK
{


/**
    \brief The Variant object is similar to QVariant, but simpler and with the adition of some basic types 
    as Money, the Reference to Variant type, and some form of Script.
    
    This is not the definitive release of variant and is subject to change.
 */

class Variant
{
public:
	enum Type {
	    Invalid,
	    tBool,
	    tInt,
		tUInt,
	    tDouble,
	    tString,
	    tDate,
	    tTime,
	    tDateTime,
	    tColor,
	    tImage,
	    tByteArray,
	    tMoney,
		tCFunctionType, // OJO, remove
	    tVariantRef
	};

	Variant() : mType( Invalid ) {}
	Variant( Variant *val );
	Variant( const Variant &val);
	Variant( bool val );
	Variant( int val );
	Variant( uint val );
	Variant( long val );
	Variant( double val );
	Variant( const QString &val );
	Variant( const char *val );
	Variant( const QDate &val );
	Variant( const QTime &val );
	Variant( const QDateTime &val );
	Variant( const QColor &val );
	Variant( const QImage &val );
	Variant( const QByteArray &val );
	Variant( const Money &val );
	Variant( const QVariant &val );
	~Variant() { clear(); }

	bool toBool() const;
	int toInt ( bool * ok = 0 ) const;
	uint toUInt( bool * ok = 0 ) const;
	double toDouble( bool * ok = 0 ) const;
	Measure toMeasure( bool * ok = 0 ) const { return toDouble(ok); }
	const QString toString() const;
	const QDate toDate() const;
	const QTime toTime() const;
	const QDateTime toDateTime() const;
	const QColor toColor() const;
	const QImage *toImage() const;
	const QByteArray toByteArray() const;
	const Money toMoney( bool *ok = 0 ) const;
	const BorderStyle toBorderStyle() const { return BorderStyle(toInt()); }
	const AlignmentType toAlignmentType() const { return AlignmentType(toInt()); }
	const AdjustmentType toAdjustmentType() const { return AdjustmentType(toInt()); }

	Type type() const { return mType == tVariantRef ? value.pv->type() : mType; }

	Variant& operator+=( const Variant& );
	Variant& operator= ( const Variant &val );
	bool operator==( const Variant& ) const;
	bool operator!=( const Variant& ) const;

	const char* typeName() const;
	bool canCast( Type ) const;

	bool isValid() const { return ( mType != Invalid ); }
	bool isNull() const { return !isValid(); }
	static const char* typeToName( Type typ );
	static Type nameToType( const char* name );
	static bool isNumeric(Type type);
	static Type QVariantTypeToVariantType( QVariant::Type val );


private:
	void clear();
	Type mType;

	union {
		bool b;
		unsigned long u;
		long i;
		double d;
		QString *ps;
		QDate *pd;
		QTime *pt;
		QDateTime *pdt;
		QColor *pc;
		QImage *pi;
		QByteArray *pba;
		Money *pm;
		Variant *pv;
	} value;

}; // class QVariant

}; // Namespace
#endif // RTKVARIANT_H

