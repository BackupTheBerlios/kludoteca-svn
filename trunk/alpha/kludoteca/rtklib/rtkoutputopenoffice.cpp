/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputopenoffice.cpp RTK openoffice output object
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

#include <stdio.h>
#include <fstream>
#include "rtkobject.h"
#include "rtksection.h"
#include "rtkreport.h"
#include "rtkoutputopenoffice.h"

#include <qstring.h>  // qDebug


using namespace RTK;

/*

	Add newlines to help debug errors.

*/


inline QString XMLProtect( const QString& string )
{
    QString s = string;
    s.replace( "&", "&amp;" );
    s.replace( ">", "&gt;" );
    s.replace( "<", "&lt;" );
    s.replace( "\"", "&quot;" );
    s.replace( "\'", "&apos;" );
    return s;
}


static const char *xml0 = "<?xml version=\"1.0\" encoding=\"";
static const char *xml1 = "\"?>";

static const char *doctype =
"<!DOCTYPE office:document-content PUBLIC \"-//OpenOffice.org//DTD OfficeDocument 1.0//EN\" \"office.dtd\">"
"<office:document-content xmlns:office=\"http://openoffice.org/2000/office\" xmlns:style=\"http://openoffice.org/2000/style\" xmlns:text=\"http://openoffice.org/2000/text\" xmlns:table=\"http://openoffice.org/2000/table\" xmlns:draw=\"http://openoffice.org/2000/drawing\" xmlns:fo=\"http://www.w3.org/1999/XSL/Format\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:number=\"http://openoffice.org/2000/datastyle\" xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns:chart=\"http://openoffice.org/2000/chart\" xmlns:dr3d=\"http://openoffice.org/2000/dr3d\" xmlns:math=\"http://www.w3.org/1998/Math/MathML\" xmlns:form=\"http://openoffice.org/2000/form\" xmlns:script=\"http://openoffice.org/2000/script\" office:class=\"spreadsheet\" office:version=\"1.0\">"
"<office:script/>"
"<office:font-decls>"
"<style:font-decl style:name=\"Lucida\" fo:font-family=\"Lucida\" style:font-pitch=\"variable\"/>"
"<style:font-decl style:name=\"Tahoma\" fo:font-family=\"Tahoma, Lucidasans, &apos;Lucida Sans&apos;, &apos;Arial Unicode MS&apos;\" style:font-pitch=\"variable\"/>"
"<style:font-decl style:name=\"Arial\" fo:font-family=\"Arial\" style:font-family-generic=\"swiss\" style:font-pitch=\"variable\"/>"
"</office:font-decls>\n";

static const char *automatic_styles = 
"<office:automatic-styles>"
"<style:style style:name=\"co1\" style:family=\"table-column\">"
"<style:properties fo:break-before=\"auto\" style:column-width=\"2.267cm\"/>"
"</style:style>"
"<style:style style:name=\"ro1\" style:family=\"table-row\">"
"<style:properties style:row-height=\"0.427cm\" fo:break-before=\"auto\" style:use-optimal-row-height=\"true\"/>"
"</style:style>"
"<style:style style:name=\"ro2\" style:family=\"table-row\">"
"<style:properties style:row-height=\"0.446cm\" fo:break-before=\"auto\" style:use-optimal-row-height=\"true\"/>"
"</style:style>"
"<style:style style:name=\"ta1\" style:family=\"table\" style:master-page-name=\"Default\">"
"<style:properties table:display=\"true\"/>"
"</style:style>"
"<style:style style:name=\"ce1\" style:family=\"table-cell\" style:parent-style-name=\"Default\">"
"<style:properties fo:font-weight=\"bold\"/>"
"</style:style>"
"<style:style style:name=\"T1\" style:family=\"text\">"
"<style:properties fo:font-weight=\"bold\"/>"
"</style:style>"
"</office:automatic-styles>\n";

static const char *body =
"<office:body><table:table table:name=\"Sheet1\" table:style-name=\"ta1\">\n";

static const char *body_end = 
"</table:table></office:body></office:document-content>";


/*
	TODO
*/

int OutputOpenOffice::startReport( const Report & )
{
	mIntSizeX = ( int ) mSizeX;
	mIntSizeY = ( int ) mSizeY;
	switch( mReplaceContent ) {
	case CREATE:
		if( QFile::exists( mFileName ) ) {
			if( !QFile::remove( mFileName ) ) {
				qWarning("RTK:OutputOpenOffice:startReport:unable to remove file %s", (const char *)mFileName);
			}
		}
		break;
	case REPLACE_CONTENT:
		if( !QFile::exists( mFileName ) ) {
			qWarning("RTK:OutputOpenOffice:startReport:file doesn't exists: %s", (const char *)mFileName);
		}
		break;
	case ADD_FIRST_SHEET:
	case ADD_LAST_SHEET:
	case REPLACE_FIRST_SHEET:
	case REPLACE_LAST_SHEET:
		qWarning("RTK:OutputOpenOffice:startReport:CreateOption %d not supported yet", mReplaceContent);
		return -1;
	default:
		qWarning("RTK:OutputOpenOffice:startReport:CreateOption %d invalid", mReplaceContent);
		return -1;
	}		
	
	
	pFile = new QFile( "/tmp/content.xml" );
	if( !pFile->open( IO_WriteOnly ) ) {
		qWarning("RTK:OutputOpenOffice:startReport:unable to create contents file /tmp/contents.xml");
		return -1;
	}
	pFile->writeBlock(xml0, strlen(xml0));
	pFile->writeBlock(mEncoding, mEncoding.length());
	pFile->writeBlock(xml1, strlen(xml1));
	pFile->writeBlock(doctype, strlen(doctype));
	pFile->writeBlock(automatic_styles, strlen(automatic_styles));
	pFile->writeBlock(body, strlen(body));
	mDetailsFieldCount = 5;
	return 0;
}

int OutputOpenOffice::endReport( const Report & )
{
	if ( pFile ) {
		pFile->writeBlock(body_end, strlen(body_end));
		pFile->close();
		delete pFile;
	}
	
	FILE *f = NULL;
	QString cmd;
	switch( mReplaceContent ) {
	case CREATE:
		if( mFileName.at(0) == '/' ) {
			cmd = "TMPPWD=`pwd`;"
				"cd " + mTemplatePath + ";"
				"zip -r " + mFileName + " *;"
				"cd $TMPPWD;"
				"zip -rj " + mFileName + " /tmp/content.xml";
		} else {
			cmd = "TMPPWD=`pwd`;"
				"cd " + mTemplatePath + ";"
				"zip -r $TMPPWD/" + mFileName + " *;"
				"cd $TMPPWD;"
				"zip -rj $TMPPWD/" + mFileName + " /tmp/content.xml";
		}
		break;
	case REPLACE_CONTENT:
		cmd = "zip -rj " + mFileName + " /tmp/content.xml";
		break;
	case ADD_FIRST_SHEET:
	case ADD_LAST_SHEET:
	case REPLACE_FIRST_SHEET:
	case REPLACE_LAST_SHEET:
	default:
		return 0;
	}
	// I should use QProcess, shouldn't I?
   	qDebug( "RTK:OutputOpenOffice::command: [%s]\n", (const char *)cmd);
	if((f = popen((const char *)cmd, "r")) == NULL)
	{
   		qWarning( "RTK:OutputOpenOffice::Can't open command: [%s]\n", (const char *)cmd);
	} else {
   		int c            = 0;
   		char buffer[255] = { '\0' };

   		while((c = fgetc(f)) != EOF)
   		{
      		ungetc(c, f);
      		fgets(buffer, sizeof(buffer), f);
		}
		fprintf( stderr, "RTK:OutputOpenOffice::endReport:%s\n", buffer);
	} 
	pclose(f);
	pFile = 0;
	return 0;
}

Measure OutputOpenOffice::startPage()
{
	return mSizeY;
}


Measure OutputOpenOffice::endPage()
{
	return 0;
}

Measure OutputOpenOffice::startSection( const Section & /*section*/ )
{
	QString text = "<table:table-row table:style-name=\"ro1\">\n";
	pFile->writeBlock((const char *)text, text.length() );
	return mSizeY - mCurrY;
}


Measure OutputOpenOffice::endSection( const Section &section )
{
	QString text = "</table:table-row>\n";
	pFile->writeBlock((const char *)text, text.length() );
	mCurrY += section.getFixedSizeY();
	mCurrX = mMarginLeft;
	return mSizeY - mCurrY;
}


Measure OutputOpenOffice::startObject( const Section & /*section*/, const Object & /*object*/ )
{
	return mSizeY - mCurrY;
}


Measure OutputOpenOffice::endObject( const Section & /*section*/, const Object & /*object*/ )
{
	return mSizeY - mCurrY;
}

Measure OutputOpenOffice::printObject( const Report & /*report*/, const Section & /*section*/, const Object &object )
{
#if DEBUG_RTKOUTPUT > 3
	qDebug( "RTK:OutputOpenOffice:Printing field %s='%s' at %f+%d,%f+%d\n", ( const char * ) object.getName(),
	        ( const char * ) object.getText(), mCurrX, ( int ) object.getPosX(), mCurrY, ( int ) object.getPosY() );
#endif			
	// table:value-type=\"float\" table:value=\"1\"
	QString text = "<table:table-cell table:style-name=\"ce1\"><text:p>";
	text += XMLProtect(object.getText());
	text += "</text:p></table:table-cell>\n";
	pFile->writeBlock((const char *)text, text.length() );
	return mSizeY - mCurrY;
}

Measure OutputOpenOffice::setPosX( Measure newx )
{
	int oldx = mIntSizeX;
	mIntSizeX = ( int ) newx;
	return oldx;
}

Measure OutputOpenOffice::setPosY( Measure newy )
{
	int oldy = mIntSizeY;
	mIntSizeY = ( int ) newy;
	return oldy;
}


