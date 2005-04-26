/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkobject.cpp RTK base object
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

#include <ctype.h>
#include <qimage.h>
#include "rtkobject.h"
#include "rtkreport.h"

using namespace RTK;

/**
  \class RTK::Object rtkobject.h
  \brief The RTK::Object class is the base class of all the objects that form a report definition.
 
  A report definition is a \link rtkreport.html RTK::Report object \endlink
  which contains serveral \link rtksection.html RTK::Section objects \endlink 
  which in turn contains several RTK::Object objects.

*/

Variant Object::getNonAggregateValue() const
{
	if ( getValue().type() == Variant::tCFunctionType )
		return mReport->execCFunction( *this, getValue().toString() );
	else if( isConst() )
		return mValue;
	else
		return mRealValue;
}

/**
    \relates RTK::Object

    Returns a pointer to the object named \a name that inherits \a
    type and with a given \a parent.

    Returns 0 if there is no such child.

    \code
	QListBox *c = (QListBox *) qt_find_obj_child( myWidget, "QListBox",
						      "my list box" );
	if ( c )
	    c->insertItem( "another string" );
    \endcode
*/
Variant Object::getRealValue() const
{
	if ( getAggregate() != AggNone ) {
		Section *sect = static_cast<Section *>(getParent());
#if DEBUG_RTK > 3
		qDebug( "RTK:Object::getNonAggregateValue:%s, level %d=%f",
		        ( const char * ) getName(),
		        sect->getGroupLevel(),
		        mAggValues[ sect->getGroupLevel() ].toDouble() );
#endif
		if( getAggregate() == AggAvg ) {
			return mAggValues[ sect->getGroupLevel() ].toDouble() / sect->getRecordCount();
		} else {
			return mAggValues[ ( ( Section * ) getParent() ) ->getGroupLevel() ];
		}
	} else
		return getNonAggregateValue();
}

String Object::getText() const
{
	return getRealValue().toString();
}


String Object::getText( const String &mask, const String &format, const Formatter &f ) const
{
	Variant v = getRealValue();
	return f.format( v, format, mask );
}

#ifndef NDEBUG
int Object::debug_print() const
{
	return 1;
}

#endif

//enum Units { chars=0, dots=1, inches=2, cm=3, mm=4

double scalesArray[ 5 ][ 5 ] =
    {
        { 1, 1 / dotsperchar, charsperinch, charsperinch / cmperinch, charsperinch / mmperinch },
        { dotsperchar, 1, dotsperinch, dotsperinch / cmperinch, dotsperinch / mmperinch },
        { 1 / charsperinch, 1 / dotsperinch, 1, 1 / cmperinch, 1 / mmperinch },
        { cmperinch / charsperinch, cmperinch / dotsperinch, cmperinch, 1, 10 },
        { mmperinch / charsperinch, mmperinch / dotsperinch, mmperinch, 0.1, 1 }
    };



void Object::fixMeasures( UnitsType outunit, Measure outsizex, Measure outsizey,
                          UnitsType repunit, Measure repsizex, Measure repsizey )
{
	mFixedPosX = fixOneMeasure( getUnits(getPosX(), repunit), getMeasure(getPosX()), 
		repunit, repsizex, outunit, outsizex );
	//  qDebug("PosX=%f, FixedPosX=%f", getPosX(), mFixedPosX);
	mFixedPosY = fixOneMeasure( getUnits(getPosY(), repunit), getMeasure(getPosY()), 
		repunit, repsizey, outunit, outsizey );
	//  qDebug("PosY=%f, FixedPosY=%f", getPosY(), mFixedPosY);
	if( getMeasure(getSizeX()) <= Measure(0) )
		mFixedSizeX = outsizex - mFixedPosX;
	else
		mFixedSizeX = fixOneMeasure( getUnits(getSizeX(), repunit), getMeasure(getSizeX()),
			 repunit, repsizex, outunit, outsizex );
	//  qDebug("SizeX=%f, FixedSizeX=%f", getSizeX(), mFixedSizeX);
	mFixedSizeY = fixOneMeasure( getUnits(getSizeY(), repunit), getMeasure(getSizeY()), 
		repunit, repsizey, outunit, outsizey );
	//  qDebug("SizeY=%f, FixedSizeY=%f", getSizeY(), mFixedSizeY);
	mFixedMarginLeft = fixOneMeasure( getUnits(getMarginLeft(), repunit), getMeasure(getMarginLeft()), 
		repunit, repsizex, outunit, outsizex );
	mFixedMarginRight = fixOneMeasure( getUnits(getMarginRight(), repunit), getMeasure(getMarginRight()),
		 repunit, repsizex, outunit, outsizex );
	mFixedMarginTop = fixOneMeasure( getUnits(getMarginTop(), repunit), getMeasure(getMarginTop()), 
		repunit, repsizey, outunit, outsizey );
	mFixedMarginBottom = fixOneMeasure( getUnits(getMarginBottom(), repunit), getMeasure(getMarginBottom()),
		repunit, repsizey, outunit, outsizey );
}

Measure Object::fixOneMeasure(
    UnitsType objunit, Measure measure,
    UnitsType repunit, Measure repsize,
    UnitsType /*outunit*/, Measure outsize )
{
	Q_ASSERT( repsize != 0 );
	Q_ASSERT( outsize != 0 );

	if ( objunit == p100 ) {
		// Adjust percent to report size
		objunit = repunit;
		measure *= repsize / 100;
	} else if ( objunit == defaultunit ) {
		objunit = repunit;
	}
	//  double unitsScale = scalesArray[outunit][objunit];
	return measure * ( outsize / repsize );
}




// Atención
/*
  Style no se busca en el estilo
  Visible no se busca en el estilo
  Supressed no se busca en el estilo
  BorderStyle no se busca en el padre
*/


/*<<<<<OBJECT_GET_VISIBLE*/
bool Object::isVisible() const
{
		if( !isNullVisible() )
			return mVisible.toBool();
		if( getParent() ) {
			return getParent()->isVisible();
		} else {
			return true;
		}
}
/*>>>>>OBJECT_GET_VISIBLE*/
/*<<<<<OBJECT_GET_SUPRESSED*/
bool Object::isSupressed() const
{
		if( !isNullSupressed() )
			return mSupressed.toBool();
		if( getParent() ) {
			return getParent()->isSupressed();
		} else {
			return false;
		}
}
/*>>>>>OBJECT_GET_SUPRESSED*/
/*<<<<<OBJECT_GET_HALIGNMENT*/
AlignmentType Object::getHAlignment() const
{
		if( !isNullHAlignment() )
			return mHAlignment.toAlignmentType();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullHAlignment() )
					return styledef->getHAlignment();
			}
		}
		if( getParent() ) {
			return getParent()->getHAlignment();
		} else {
			return AlignAuto;
		}
}
/*>>>>>OBJECT_GET_HALIGNMENT*/
/*<<<<<OBJECT_GET_VALIGNMENT*/
AlignmentType Object::getVAlignment() const
{
		if( !isNullVAlignment() )
			return mVAlignment.toAlignmentType();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullVAlignment() )
					return styledef->getVAlignment();
			}
		}
		if( getParent() ) {
			return getParent()->getVAlignment();
		} else {
			return AlignTop;
		}
}
/*>>>>>OBJECT_GET_VALIGNMENT*/
/*<<<<<OBJECT_GET_ADJUSTMENT*/
AdjustmentType Object::getAdjustment() const
{
		if( !isNullAdjustment() )
			return mAdjustment.toAdjustmentType();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullAdjustment() )
					return styledef->getAdjustment();
			}
		}
		if( getParent() ) {
			return getParent()->getAdjustment();
		} else {
			return AdjustTrim;
		}
}
/*>>>>>OBJECT_GET_ADJUSTMENT*/
/*<<<<<OBJECT_GET_TEXTCOLOR*/
Color Object::getTextColor() const
{
		if( !isNullTextColor() )
			return mTextColor.toColor();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullTextColor() )
					return styledef->getTextColor();
			}
		}
		if( getParent() ) {
			return getParent()->getTextColor();
		} else {
			return Qt::black;
		}
}
/*>>>>>OBJECT_GET_TEXTCOLOR*/
/*<<<<<OBJECT_GET_BACKCOLOR*/
Color Object::getBackColor() const
{
		if( !isNullBackColor() )
			return mBackColor.toColor();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullBackColor() )
					return styledef->getBackColor();
			}
		}
		if( getParent() ) {
			return getParent()->getBackColor();
		} else {
			return Qt::white;
		}
}
/*>>>>>OBJECT_GET_BACKCOLOR*/
/*<<<<<OBJECT_GET_BORDERCOLOR*/
Color Object::getBorderColor() const
{
		if( !isNullBorderColor() )
			return mBorderColor.toColor();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullBorderColor() )
					return styledef->getBorderColor();
			}
		}
		if( getParent() ) {
			return getParent()->getBorderColor();
		} else {
			return Qt::black;
		}
}
/*>>>>>OBJECT_GET_BORDERCOLOR*/
/*<<<<<OBJECT_GET_BORDERWIDTH*/
int Object::getBorderWidth() const
{
		if( !isNullBorderWidth() )
			return mBorderWidth.toInt();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullBorderWidth() )
					return styledef->getBorderWidth();
			}
		}
		if( getParent() ) {
			return getParent()->getBorderWidth();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_BORDERWIDTH*/
/*<<<<<OBJECT_GET_BORDERSTYLE*/
BorderStyle Object::getBorderStyle() const
{
	if( mBorderStyle.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mBorderStyle.toString()).toBorderStyle();
		if( !isNullBorderStyle() )
			return mBorderStyle.toBorderStyle();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullBorderStyle() )
					return styledef->getBorderStyle();
			}
		}
		return BorderNone;
}
/*>>>>>OBJECT_GET_BORDERSTYLE*/
/*<<<<<OBJECT_GET_FONTFAMILY*/
String Object::getFontFamily() const
{
		if( !isNullFontFamily() )
			return mFontFamily.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullFontFamily() )
					return styledef->getFontFamily();
			}
		}
		if( getParent() ) {
			return getParent()->getFontFamily();
		} else {
			return String::null;
		}
}
/*>>>>>OBJECT_GET_FONTFAMILY*/
/*<<<<<OBJECT_GET_FONTSIZE*/
int Object::getFontSize() const
{
		if( !isNullFontSize() )
			return mFontSize.toInt();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullFontSize() )
					return styledef->getFontSize();
			}
		}
		if( getParent() ) {
			return getParent()->getFontSize();
		} else {
			return 12;
		}
}
/*>>>>>OBJECT_GET_FONTSIZE*/
/*<<<<<OBJECT_GET_FONTWEIGHT*/
int Object::getFontWeight() const
{
		if( !isNullFontWeight() )
			return mFontWeight.toInt();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullFontWeight() )
					return styledef->getFontWeight();
			}
		}
		if( getParent() ) {
			return getParent()->getFontWeight();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_FONTWEIGHT*/
/*<<<<<OBJECT_GET_FONTITALIC*/
bool Object::isFontItalic() const
{
		if( !isNullFontItalic() )
			return mFontItalic.toBool();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullFontItalic() )
					return styledef->isFontItalic();
			}
		}
		if( getParent() ) {
			return getParent()->isFontItalic();
		} else {
			return false;
		}
}
/*>>>>>OBJECT_GET_FONTITALIC*/
/*<<<<<OBJECT_GET_FORMAT*/
String Object::getFormat() const
{
		if( !isNullFormat() )
			return mFormat.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullFormat() )
					return styledef->getFormat();
			}
		}
		if( getParent() ) {
			return getParent()->getFormat();
		} else {
			return String::null;
		}
}
/*>>>>>OBJECT_GET_FORMAT*/
/*<<<<<OBJECT_GET_MAXLINES*/
int Object::getMaxLines() const
{
		if( !isNullMaxLines() )
			return mMaxLines.toInt();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMaxLines() )
					return styledef->getMaxLines();
			}
		}
		if( getParent() ) {
			return getParent()->getMaxLines();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_MAXLINES*/
/*<<<<<OBJECT_GET_MINFONTSIZE*/
int Object::getMinFontSize() const
{
		if( !isNullMinFontSize() )
			return mMinFontSize.toInt();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMinFontSize() )
					return styledef->getMinFontSize();
			}
		}
		if( getParent() ) {
			return getParent()->getMinFontSize();
		} else {
			return 8;
		}
}
/*>>>>>OBJECT_GET_MINFONTSIZE*/


/*<<<<<OBJECT_GET_MASK*/
String Object::getMask() const
{
		if( !isNullMask() )
			return mMask.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMask() )
					return styledef->getMask();
			}
		}
		if( getParent() ) {
			return getParent()->getMask();
		} else {
			return String::null;
		}
}
/*>>>>>OBJECT_GET_MASK*/


void Object::resetAggregateValues( uint nlevels, uint level )
{
#if DEBUG_RTK > 1
	qDebug( "RTK:Object:resetAggregateValues(nlevels=%d, level=%d)", nlevels, level );
#endif

	if ( getAggregate() != AggNone ) {
		if ( level == 0 ) { // Details
			for ( uint i = 0; i <= nlevels; i++ ) {
				if ( mAggValues.size() <= i )
					mAggValues.push_back( Variant( 0.0 ) );
				else
					mAggValues[ i ] = 0.0;
			}
		} else {
			mAggValues[ level ] = 0.0;
		}
	}
}

void Object::calcAggregateValue( uint levels )
{
	if ( getAggregate() != AggNone ) {
		for ( uint i = 0; i <= levels; i++ ) {
			switch ( getAggregate() ) {
			case AggCount:
#if DEBUG_RTK > 2
				qDebug( "RTK:Object:calcAggreateValue:Count " + mAggValues[ i ].toString() );
#endif
				mAggValues[ i ] += 1;
				break;
			case AggSum:
			case AggAvg:
#if DEBUG_RTK > 2
				qDebug( "RTK:Object:calcAggreateValue: sums %s to %s=%f, level %d",
				        ( const char * ) getNonAggregateValue().toString(),
				        ( const char * ) getName(),
				        mAggValues[ i ].toDouble(), i );
#endif
				mAggValues[ i ] += getNonAggregateValue();
#if DEBUG_RTK > 2
				qDebug( "RTK:Object:calcAggreateValue:and gets %f", mAggValues[ i ].toDouble() );
#endif
				break;
			
			case AggNone:
			default:
				break;
			}
		}
	}
}

/*<<<<<OBJECT_GET_BACKGROUNDIMAGE*/
String Object::getBackgroundImage() const
{
		if( !isNullBackgroundImage() )
			return mBackgroundImage.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullBackgroundImage() )
					return styledef->getBackgroundImage();
			}
		}
		if( getParent() ) {
			return getParent()->getBackgroundImage();
		} else {
			return String::null;
		}
}
/*>>>>>OBJECT_GET_BACKGROUNDIMAGE*/
/*<<<<<OBJECT_GET_MARGINLEFT*/
String Object::getMarginLeft() const
{
		if( !isNullMarginLeft() )
			return mMarginLeft.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMarginLeft() )
					return styledef->getMarginLeft();
			}
		}
		if( getParent() ) {
			return getParent()->getMarginLeft();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_MARGINLEFT*/
/*<<<<<OBJECT_GET_MARGINRIGHT*/
String Object::getMarginRight() const
{
		if( !isNullMarginRight() )
			return mMarginRight.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMarginRight() )
					return styledef->getMarginRight();
			}
		}
		if( getParent() ) {
			return getParent()->getMarginRight();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_MARGINRIGHT*/
/*<<<<<OBJECT_GET_MARGINTOP*/
String Object::getMarginTop() const
{
		if( !isNullMarginTop() )
			return mMarginTop.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMarginTop() )
					return styledef->getMarginTop();
			}
		}
		if( getParent() ) {
			return getParent()->getMarginTop();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_MARGINTOP*/
/*<<<<<OBJECT_GET_MARGINBOTTOM*/
String Object::getMarginBottom() const
{
		if( !isNullMarginBottom() )
			return mMarginBottom.toString();
		if( !getStyle().length() == 0 ) {
			const Style *styledef = mReport->getStyle(getStyle());
			if( styledef ) {
				if( !styledef->isNullMarginBottom() )
					return styledef->getMarginBottom();
			}
		}
		if( getParent() ) {
			return getParent()->getMarginBottom();
		} else {
			return 0;
		}
}
/*>>>>>OBJECT_GET_MARGINBOTTOM*/

/**
	Extract the units from the measure string
 */
UnitsType Object::getUnits(String value, UnitsType defaultunits)
{
	const char *str = (const char *)value;
	QString units;
	if( str ) {
		for( uint i=0; i<strlen(str); i++ ) {
			if( !isdigit(str[i]) && strchr("., +-e", str[i]) == 0 ) {
				units = QString(str).stripWhiteSpace().mid(0,2).lower();
				if( units == "mm" )
					return mm;
				else if( units=="cm" )
					return cm;
				else if( units=="in" )
					return inches;
				else if( units=="px" || units=="pi" || units=="do" )
					return inches;
				else if( units=="ch" )
					return inches;
				else if( units=="p1" || units=="%" )
					return inches;
				break;
			}
		}
	}
	return defaultunits;
}
		
/**
	Extract the measure value from the measure string
 */
Measure Object::getMeasure(String value)
{
	if( value.length() == 0 )
		return 0.0;
	else 
		return atof(value);	
}
