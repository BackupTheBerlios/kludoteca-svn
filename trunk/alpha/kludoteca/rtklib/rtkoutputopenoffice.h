/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputopenoffice.h RTK openoffice output object
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

#ifndef RTKOUTPUTOPENOFFICE_H
#define RTKOUTPUTOPENOFFICE_H

#include <qfile.h>

#include "rtkoutput.h"

namespace RTK
{

class OutputOpenOffice : public Output
{
public:
	enum OOCreateOptions { CREATE, REPLACE_CONTENT, ADD_FIRST_SHEET, ADD_LAST_SHEET, REPLACE_FIRST_SHEET, REPLACE_LAST_SHEET };
/*<<<<<OUTPUTOPENOFFICE_CONSTRUCTOR*/
public:
	OutputOpenOffice(const String& filename = String::null, const String& encoding = String::null, 
		const String& templatedir = String::null, const OOCreateOptions& replacecontent = CREATE,
	PaperType papertype = A4, UnitsType units = dots, 
		Measure sizex = 595, Measure sizey = 841, Measure marginleft = 0, 
		Measure marginright = 0, Measure margintop = 0, Measure marginbottom = 0, int pageorientation = 0)
	:Output(papertype, units, 
		sizex, sizey, marginleft, 
		marginright, margintop, marginbottom, pageorientation),
	mFileName(filename), mEncoding(encoding), 
		mTemplatePath(templatedir), mReplaceContent(replacecontent)
/*>>>>>OUTPUTOPENOFFICE_CONSTRUCTOR*/
	, mDetailsFieldCount(0) {}

	~OutputOpenOffice() {}
	int startReport( const Report &report );
	int endReport( const Report &report );
	Measure startPage();
	Measure endPage();
	Measure startSection( const Section &section );
	Measure endSection( const Section &section );
	Measure startObject( const Section &section, const Object &object );
	Measure endObject( const Section &section, const Object &object );
	Measure printObject( const Report &report, const Section &section, const Object &object );
	Measure setPosX( Measure newx );
	Measure setPosY( Measure newy );

/*<<<<<OUTPUTOPENOFFICE_GETSET*/
public:
	/** Gets Output's file name */
	const String& getFileName() const { return mFileName; };
	/** Sets the Output's file name */
	void setFileName(const String& filename) { mFileName = filename; };
	/** Gets Encoding of the file */
	const String& getEncoding() const { return mEncoding; };
	/** Sets the Encoding of the file */
	void setEncoding(const String& encoding) { mEncoding = encoding; };
	/** Gets Dir containing the template of an empty OpenOffice document */
	const String& getTemplatePath() const { return mTemplatePath; };
	/** Sets the Dir containing the template of an empty OpenOffice document */
	void setTemplatePath(const String& templatedir) { mTemplatePath = templatedir; };
	/** Gets Flag to set what to do if the file exists */
	const OOCreateOptions& getReplaceContent() const { return mReplaceContent; };
	/** Sets the Flag to set what to do if the file exists */
	void setReplaceContent(const OOCreateOptions& replacecontent) { mReplaceContent = replacecontent; };
protected:
	String mFileName;
	String mEncoding;
	String mTemplatePath;
	OOCreateOptions mReplaceContent;
/*>>>>>OUTPUTOPENOFFICE_GETSET*/

private:
	int mDetailsFieldCount;
	int mIntSizeX, mIntSizeY;
	QFile *pFile;
};

}; // namespace

#endif

