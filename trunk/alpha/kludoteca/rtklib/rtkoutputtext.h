/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputtext.h RTK standard text output object
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

#ifndef RTKOUTPUTFILE_H
#define RTKOUTPUTFILE_H

#include <qfile.h>

#include "rtkoutput.h"

namespace RTK {
    
class OutputText : public Output  {
/*<<<<<OUTPUTFILE_CONSTRUCTOR*/
public:
	OutputText(const String& filename = String::null,
	PaperType papertype = A4, UnitsType units = dots, 
		Measure sizex = 595, Measure sizey = 841, Measure marginleft = 0, 
		Measure marginright = 0, Measure margintop = 0, Measure marginbottom = 0, int pageorientation = 0)
	:Output(papertype, units, 
		sizex, sizey, marginleft, 
		marginright, margintop, marginbottom, pageorientation),
	mFileName(filename)
/*>>>>>OUTPUTFILE_CONSTRUCTOR*/
	{};
  
    ~OutputText() {};
    int startReport(const Report &report);
    int endReport(const Report &report);
    Measure startPage();
    Measure endPage();
    Measure startSection(const Section &section);
    Measure endSection(const Section &section);
    Measure startObject(const Section &section, const Object &object);
    Measure endObject(const Section &section, const Object &object);
    Measure printObject(const Report &report, const Section &section, const Object &object);
    Measure setPosX(Measure newx);
    Measure setPosY(Measure newy);
    bool sectionFits(const Section &section, Measure nextsectionheight) const;

/*<<<<<OUTPUTFILE_GETSET*/
public:
	/** Gets Output's file name */
	const String& getFileName() const { return mFileName; };
	/** Sets the Output's file name */
	void setFileName(const String& filename) { mFileName = filename; };
protected:
	String mFileName;
/*>>>>>OUTPUTFILE_GETSET*/

private:
    char *mPageBuf;
    int mIntSizeX, mIntSizeY;
    void internal_print(const char *text, int x, int y, int len);
    QFile *pFile;
};

}; // namespace

#endif

