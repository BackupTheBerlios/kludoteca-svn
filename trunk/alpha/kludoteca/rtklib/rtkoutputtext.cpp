/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputtext.cpp RTK standard text output object
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

#include "rtkobject.h"
#include "rtksection.h"
#include "rtkreport.h"
#include "rtkoutputtext.h"

using namespace RTK;

/*
  This format is a plain text file
  The writing is done on a page buffer and each page is writed to the file
  The coordinates are in columns and lines, so a cast must be done from
    Measure to int in every Measure of Output
*/

int OutputText::startReport( const Report & )
{
	mIntSizeX = ( int ) mSizeX;
	mIntSizeY = ( int ) mSizeY;
	mPageBuf = new char[ ( ( mIntSizeX + 1 ) * mIntSizeY ) + 1 ];
	pFile = new QFile( mFileName );
	if( !pFile->open(IO_WriteOnly) ) {
		delete pFile;
		pFile = 0;
		return -1;
	}
	return 0;
}

int OutputText::endReport( const Report & )
{
	if ( mPageBuf ) {
		delete [] mPageBuf;
	}
	if ( pFile ) {
		pFile->close();
		delete pFile;
	}
	pFile = 0;
	mPageBuf = 0;
	return 0;
}

Measure OutputText::startPage()
{
	mCurrX = mMarginLeft;
	mCurrY = mMarginTop;
	memset( mPageBuf, ' ', ( ( mIntSizeX + 1 ) * mIntSizeY ) );
	for ( int i = 1; i < mIntSizeY; i++ )
		mPageBuf[ i * ( mIntSizeX + 1 ) - 1 ] = '\n';
	mPageBuf[ ( mIntSizeX + 1 ) * mIntSizeY ] = '\0';
	return mSizeY;
}


Measure OutputText::endPage()
{
	if ( pFile )
		pFile->writeBlock( mPageBuf, ( ( mIntSizeX + 1 ) * mIntSizeY ) );
#if DEBUG_RTKOUTPUT > 0
	qDebug( "RTKOutputText::endPage:write(((((" );
	qDebug( mPageBuf );
	qDebug( "RTKOutputText::endPage:write)))))" );
#endif
	return 0;
}

Measure OutputText::startSection( const Section & /*section*/ )
{
	return mSizeY - mCurrY;
}


Measure OutputText::endSection( const Section &section )
{
	mCurrY += section.getFixedSizeY();
	mCurrX = mMarginLeft;
	return mSizeY - mCurrY;
}


Measure OutputText::startObject( const Section & /*section*/, const Object & /*object*/ )
{
	return mSizeY - mCurrY;
}


Measure OutputText::endObject( const Section & /*section*/, const Object & /*object*/ )
{
	return mSizeY - mCurrY;
}

Measure OutputText::printObject( const Report & /*report*/, const Section & /*section*/, const Object &object )
{
	qDebug( "RTK:OutputText:Printing field %s='%s' at %f+%d,%f+%d", ( const char * ) object.getName(),
	        ( const char * ) object.getText(), mCurrX, ( int ) object.getFixedPosX(), mCurrY, ( int ) object.getFixedPosY() );
	internal_print( object.getText(),
	                ( int ) ( object.getFixedPosX() + mCurrX ),
	                ( int ) ( object.getFixedPosY() + mCurrY ),
	                ( int ) object.getFixedSizeX() );
	return mSizeY - mCurrY;
}

void OutputText::internal_print( const char *text, int x, int y, int len )
{
	if ( !text )
		return ;
	qDebug("mIntSizeX=%d", (int) mIntSizeX);
	char *pbuff = mPageBuf + ( ( ( ( int ) mCurrY + y ) * ( mIntSizeX + 1 ) ) + ( ( int ) mCurrX + x ) );
	const char *ptext;
	for ( ptext = text; ( *ptext != 0 ) && ( mCurrX + x + mMarginRight < mSizeX ) && ( len > 0 ); ptext++, pbuff++, x++, len-- )
		*pbuff = *ptext;
}


Measure OutputText::setPosX( Measure newx )
{
	Measure oldx = mCurrX;
	mCurrX = newx;
	return oldx;
}

Measure OutputText::setPosY( Measure newy )
{
	Measure oldy = mCurrY;
	mCurrY = newy;
	return oldy;
}


bool OutputText::sectionFits( const Section &section,
                              Measure nextsectionheight ) const
{
	Q_UNUSED(section);
	Q_UNUSED(nextsectionheight);
	return true;
//	Measure height = section.getFixedSizeY();
//	return mCurrY + height + nextsectionheight <= mSizeY - mMarginBottom;
}


