/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputqpainter.cpp RTK standard qpainter output object
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


#include <math.h>  // Debian, round()
#include <qimage.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include "rtknamespace.h"
#include "rtkoutputqpainter.h"
#include "rtkobject.h"
#include "rtksection.h"
#include "rtkreport.h"

using namespace RTK;


/*
  Warning: A QApplication object must be instantiated before using
  a QPainter
*/


void OutputQPainter::initSizes()
{
  if( getUnitsPerInchX()<=0 || getUnitsPerInchY()<=0 ) {
    QPaintDevice *dev = mPainter.device();
#if DEBUG_RTKOUTPUT > 1
	qDebug( "RTK:OutputQPainter::initSizes:dpix%d,dpiy%d", dev->x11AppDpiX(), dev->x11AppDpiY() );
#endif
	setUnitsPerInchX( dev->x11AppDpiX() );
	setUnitsPerInchY( dev->x11AppDpiY() );
  }

  // Convert papersize(mm) to output units
  setSizeX(mPaperSizes[getPaperType()].sizex * getUnitsPerInchX() / mmperinch);
  setSizeY(mPaperSizes[getPaperType()].sizey * getUnitsPerInchY() / mmperinch);
}


int OutputQPainter::startReport( const Report & )
{
#if DEBUG_RTKOUTPUT > 0
	qDebug( "RTK:OutputQPainter::startReport" );
#endif
	mCurrentPage = 0;
	mTotalPages = 0;
	mPageCollection.clear();
	return 0;
}

int OutputQPainter::endReport( const Report & )
{
#if DEBUG_RTKOUTPUT > 0
	qDebug( "RTK:OutputQPainter::endReport" );
#endif
	return 0;
}

Measure OutputQPainter::startPage()
{
#if DEBUG_RTKOUTPUT > 1
	qDebug( "RTK:OutputQPainter::startPage" );
#endif
	QPicture *aPicture = new QPicture();
#if DEBUG_RTKOUTPUT > 3
	QPaintDeviceMetrics pdm( aPicture );
	qDebug( "RTK:OutputQPainter::DeviceMetrics:w%d,h%d,wMM%d,hMM%d,dpix%d,dpiy%d",
	        pdm.width(), pdm.height(), pdm.widthMM(), pdm.heightMM(),
	        pdm.logicalDpiX(), pdm.logicalDpiY() );
	QFontMetrics fm( QFont( "", 12 ) );
	qDebug( "RTK:OutputQPainter::FontMetrics:w%d,h%d", fm.width( 'W' ), fm.height() );
#endif
	if ( mPainter.begin( aPicture ) == 0 ) {
		delete aPicture;
		return 0;
	}
	mCurrY = getMarginTop();
	mCurrX = 0;
	mCurrentPage++;
	mTotalPages++;
	mPageCollection.push_back( aPicture );
	mSavedBrush = mPainter.brush();
	return 0;
}


Measure OutputQPainter::endPage()
{
#if DEBUG_RTKOUTPUT > 1
	qDebug( "RTK:OutputQPainter::endPage" );
#endif

	mPainter.end();
	return 0;
}


Measure OutputQPainter::startSection( const Section &section )
{
	mGrowthY = 0;
	mCurrY += section.getFixedPosY() + section.getFixedMarginTop();
	mCurrX += section.getFixedPosX() + section.getFixedMarginLeft();
	return 0;
}


Measure OutputQPainter::endSection( const Section &section )
{
#if DEBUG_RTKOUTPUT > 3
	qDebug( "RTK:OutputQPainter:endSection:mCurry before endSection=%f, and after=%f", mCurrY, mCurrY + section.getFixedSizeY() );
#endif
	mPainter.setBrush( mSavedBrush );
	mCurrY += section.getFixedSizeY() + section.getFixedMarginBottom() + mGrowthY;
	mCurrX -= ( section.getFixedPosX() + section.getFixedMarginLeft() );
	return 0;
}


Measure OutputQPainter::startObject( const Section & /*section*/, const Object & /*object*/ )
{
	return 0;
}


Measure OutputQPainter::endObject( const Section & /*section*/, const Object & /*object*/ )
{
	return 0;
}

/** prints the object using the specificed painter & x/y-offsets */
Measure OutputQPainter::printObject( const Report &r, const Section &section, const Object &object )
{
	Measure realPosX =  mCurrX + object.getFixedPosX() + object.getFixedMarginLeft() + getMarginLeft();
	Measure realPosY = mCurrY + object.getFixedPosY() + object.getFixedMarginTop();
	Measure realSizeX = object.getFixedSizeX() - object.getFixedMarginRight();
	// Problem: If the section has grown
	Measure realSizeY = object.getFixedSizeY() - object.getFixedMarginBottom();

#if DEBUG_RTKOUTPUT > 2
	qDebug( "RTK:OutputQPainter:printing field(curry=%d), %s='%s' at %d,%d size:%d,%d", int( mCurrY ), ( const char * ) object.getName(),
	        ( const char * ) object.getText( object.getMask(), object.getFormat(), r.getFormatter() ), int( realPosX ), int( realPosY ), int( realSizeX ), int( realSizeY ) );
#endif
	if ( realPosX > getSizeX() - getMarginRight()
	        || realPosY > getSizeY() - getMarginBottom() ) {
#if DEBUG_RTKOUTPUT > 2
		qDebug( "RTK:OutputQPainter:Field extends beyond the margin" );
#endif
		return 0; // Out of the page
	}
	if ( realPosX + realSizeX > getSizeX() - getMarginRight() ) {
		realSizeX = getSizeX() - getMarginRight() - realPosX;
#if DEBUG_RTKOUTPUT > 2
		qDebug( "RTK:OutputQPainter:Width cropped to %f", realSizeX );
#endif

	}
	if ( realPosY + realSizeY > getSizeY() - getMarginBottom() ) {
		realSizeY = int( getSizeY() - getMarginBottom() - realPosY );
#if DEBUG_RTKOUTPUT > 2
		qDebug( "RTK:OutputQPainter:Height cropped to %f", realSizeY );
#endif
	}

	// Draw the border
	Color bc = object.getBackColor();
	if ( object.getBorderStyle() != BorderNone
	        || mPainter.brush().color() != bc ) {
		QPen linePen( object.getBorderColor(), object.getBorderWidth(),
		              ( QPen::PenStyle ) object.getBorderStyle() );
		mPainter.setPen( linePen );
		if ( realSizeX == 0 || realSizeY == 0 ) {
			mPainter.drawLine( int(round(realPosX - object.getFixedMarginLeft())),
			                   int(round(realPosY - object.getFixedMarginTop())),
			                   int(round(realPosX + realSizeX)),
			                   int(round(realPosY + realSizeY)) );
		} else {
			QBrush backBrush( bc );
			mPainter.setBrush( backBrush );
			mPainter.drawRect( int(round(realPosX - object.getFixedMarginLeft())),
			                   int(round(realPosY - object.getFixedMarginTop())),
			                   int(round(realSizeX + object.getFixedMarginLeft() + object.getFixedMarginRight())),
			                   int(round(realSizeY + object.getFixedMarginTop() + object.getFixedMarginBottom())) );
		}
	}

	if( object.getBackgroundImage().length() ) {
		const QImage *i;
		RTK::Image *rtkimage = r.findImage(object.getBackgroundImage());
		if( rtkimage && (i = rtkimage->getImage(r.getImagesPath())) ) {
			qDebug( "RTK:OutputQPainter:Printing background image %s ", (const char *)object.getBackgroundImage() );
			mPainter.drawImage( int(round(realPosX)),
		                    int(round(realPosY)),
							*i,
		                    0, 0,
		                    int(round(realSizeX)),
		                    int(round(realSizeY)) );
		}
	}

    // Optimization: getRealValue is called twice, the other in object.getText()
	Variant value = object.getRealValue();
	if ( value.type() == Variant::tImage && value.toImage() != 0 ) {
		// Draw the Image
		mPainter.drawImage( int(round(realPosX)),
		                    int(round(realPosY)),
		                    *value.toImage(),
		                    0, 0,
		                    int(round(realSizeX)),
		                    int(round(realSizeY)) );
	} else {
		QString text( object.getText( object.getMask(), object.getFormat(), r.getFormatter() ) );
		if ( text.isEmpty() )
			return realSizeY;

		// Set the font
		QFont font( object.getFontFamily(), 
					object.getFontSize() == 0 ? 10 : object.getFontSize(),
					object.getFontWeight(), object.isFontItalic() );
		mPainter.setFont( font );
		QFontMetrics fm = mPainter.fontMetrics();
		QPen textPen( object.getTextColor(), 0, QPen::NoPen );
		mPainter.setPen( textPen );

		// Set the text alignment flags
		// Horizontal
		int tf = QPainter::AlignLeft;
		switch ( object.getHAlignment() ) {
		case RTK::AlignAuto:
			if ( RTK::Variant::isNumeric( value.type() ) )
				tf = QPainter::AlignRight;
			break;
		case RTK::AlignLeft:
		case RTK::AlignTop:
		case RTK::AlignJustify:  // TODO
			tf = QPainter::AlignLeft;
			break;
		case RTK::AlignCenter:
		case RTK::AlignMiddle:
			tf = QPainter::AlignHCenter;
			break;
		case RTK::AlignRight:
		case RTK::AlignBottom:
			tf = QPainter::AlignRight;
		}

		// Vertical
		switch ( object.getVAlignment() ) {
		case RTK::AlignJustify:  // ???
		case RTK::AlignAuto:   // TODO AlignNone y AlignAuto
		case RTK::AlignLeft:
		case RTK::AlignTop:
			tf = tf | QPainter::AlignTop;
			break;
		case RTK::AlignBottom:
		case RTK::AlignRight:
			tf = tf | QPainter::AlignBottom;
			break;
		case RTK::AlignMiddle:
		case RTK::AlignCenter:
			tf = tf | QPainter::AlignVCenter;
		}

		switch ( object.getAdjustment() ) {
		case RTK::AdjustGrow: 
			{
				tf = tf | QPainter::WordBreak;
				QRect outrect = mPainter.boundingRect( int(round(realPosX)),
		                   int(round(realPosY)),
		                   int(round(realSizeX)),
		                   -1,
		                   tf,
		                   text);
				mPainter.drawText( int(round(realPosX)),
		                   int(round(realPosY)),
		                   int(round(realSizeX)),
		                   10000,
		                   tf,
		                   text);
				Measure excess = outrect.height() - realSizeY;
				if( excess > mGrowthY )
					mGrowthY = excess;
				/** \todo redraw section's background and borders */
			}
			break;
		case RTK::AdjustTrim:
		case RTK::AdjustNone:
			mPainter.drawText( int(round(realPosX)),
		                   int(round(realPosY)),
		                   int(round(realSizeX)),
		                   int(round(realSizeY)),  // el text por debajo de baseline no se imprime
		                   tf,
		                   text );
			break;
		}
	}
	return realSizeY;
}


bool OutputQPainter::sectionFits( const Section &section,
                                  Measure nextsectionheight ) const
{
#if DEBUG_RTKOUTPUT > 2
	qDebug( "RTK:OutputQPainter:sectionFits:curry=%f, section.fixedsizey=%f, mSizeY=%f, mMarginBottom=%f",
	        mCurrY, section.getFixedSizeY(), mSizeY, mMarginBottom );
#endif
	return mCurrY + section.getFixedSizeY() + nextsectionheight <= mSizeY - mMarginBottom;
}

QPicture *OutputQPainter::getFirstPage() const
{
	Q_ASSERT( mTotalPages > 0 );
	return *mPageCollection.begin();
}

