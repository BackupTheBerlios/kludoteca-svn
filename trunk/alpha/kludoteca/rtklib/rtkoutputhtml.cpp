/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputhtml.cpp RTK HTML output object
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
#include "rtkoutputhtml.h"

using namespace RTK;

#define HTML_HEADER "<HTML><BODY><TABLE>"
#define HTML_FOOTER "</BODY></HTML></TABLE>"
#define HTML_SECTION_START "<TR>"
#define HTML_SECTION_END "</TR>"
#define HTML_OBJECT_START "<TD>"
#define HTML_OBJECT_END "</TD>"

/*
  This format is a plain text file
  The writing is done on a page buffer and each page is writed to the file
  The coordinates are in columns and lines, so a cast must be done from
    Measure to int in every Measure of Output
*/

int OutputHtml::startReport( const Report & )
{
	pFile = new QFile( mFileName );
	if( !pFile->open(IO_WriteOnly) ) {
		delete pFile;
		pFile = 0;
		return -1;
	}
	return 0;
}

int OutputHtml::endReport( const Report & )
{
	if ( pFile ) {
		pFile->close();
		delete pFile;
	}
	pFile = 0;
	return 0;
}

Measure OutputHtml::startPage()
{
	mCurrX = mMarginLeft;
	mCurrY = mMarginTop;
	pFile->writeBlock(HTML_HEADER, strlen(HTML_HEADER));
	return mSizeY;
}


Measure OutputHtml::endPage()
{
	pFile->writeBlock(HTML_FOOTER, strlen(HTML_FOOTER));
	return 0;
}

Measure OutputHtml::startSection( const Section & /*section*/ )
{
	pFile->writeBlock(HTML_SECTION_START, strlen(HTML_SECTION_START));
	return mSizeY - mCurrY;
}


Measure OutputHtml::endSection( const Section &section )
{
	pFile->writeBlock(HTML_SECTION_END, strlen(HTML_SECTION_END));
	mCurrY += section.getFixedSizeY();
	mCurrX = mMarginLeft;
	return mSizeY - mCurrY;
}


Measure OutputHtml::startObject( const Section & /*section*/, const Object & /*object*/ )
{
	pFile->writeBlock(HTML_OBJECT_START, strlen(HTML_OBJECT_START));
	return mSizeY - mCurrY;
}


Measure OutputHtml::endObject( const Section & /*section*/, const Object & /*object*/ )
{
	pFile->writeBlock(HTML_OBJECT_END, strlen(HTML_OBJECT_END));
	return mSizeY - mCurrY;
}

Measure OutputHtml::printObject( const Report &r, const Section & /*section*/, const Object &object )
{
	qDebug( "RTK:OutputHtml:Printing field %s='%s' at %f+%d,%f+%d", ( const char * ) object.getName(),
	        ( const char * ) object.getText(), mCurrX, ( int ) object.getFixedPosX(), mCurrY, ( int ) object.getFixedPosY() );
			
	QString text( object.getText( object.getMask(), object.getFormat(), r.getFormatter() ) );
	const char *c_text = (const char *)text;
	if( c_text && strlen(c_text) )
		pFile->writeBlock(c_text, strlen(c_text));
	return mSizeY - mCurrY;
}

