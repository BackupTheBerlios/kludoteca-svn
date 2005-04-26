/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutputqpainter.h RTK standard qpainter output object
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

#ifndef RTKOUTPUTQPAINTER_H
#define RTKOUTPUTQPAINTER_H

#include <qpicture.h>
#include <qpainter.h>
#include <qvaluevector.h>
#include "rtkoutput.h"

namespace RTK {

typedef QValueVector<QPicture *> QPageCollection;
            
class OutputQPainter : public Output  {
/*<<<<<OUTPUTQPAINTER_CONSTRUCTOR*/
public:
	OutputQPainter(Measure unitsperinchx = 72, Measure unitsperinchy = 72,
	PaperType papertype = A4, UnitsType units = dots, 
		Measure sizex = 595, Measure sizey = 841, Measure marginleft = 0, 
		Measure marginright = 0, Measure margintop = 0, Measure marginbottom = 0, int pageorientation = 0)
	:Output(papertype, units, 
		sizex, sizey, marginleft, 
		marginright, margintop, marginbottom, pageorientation),
	mUnitsPerInchX(unitsperinchx), mUnitsPerInchY(unitsperinchy)
/*>>>>>OUTPUTQPAINTER_CONSTRUCTOR*/
	{
	  initSizes();
	};
  
    ~OutputQPainter() {};
    int startReport(const Report &report);
    int endReport(const Report &report);
    Measure startPage();
    Measure endPage();
    Measure startSection(const Section &section);
    Measure endSection(const Section &section);
    Measure startObject(const Section &section, const Object &object);
    Measure endObject(const Section &section, const Object &object);
    Measure printObject(const Report &report, const Section &section, const Object &object);
    bool sectionFits(const Section &section, Measure nextsectionheight) const;

    QPicture *getFirstPage() const;
    const QPageCollection *getPageCollection() const
      { return &mPageCollection; }

/*<<<<<OUTPUTQPAINTER_GETSET*/
public:
	Measure getUnitsPerInchX() const { return mUnitsPerInchX; };
	void setUnitsPerInchX(Measure unitsperinchx) { mUnitsPerInchX = unitsperinchx; };
	Measure getUnitsPerInchY() const { return mUnitsPerInchY; };
	void setUnitsPerInchY(Measure unitsperinchy) { mUnitsPerInchY = unitsperinchy; };
protected:
	Measure mUnitsPerInchX;
	Measure mUnitsPerInchY;
/*>>>>>OUTPUTQPAINTER_GETSET*/

private:    
    QPageCollection mPageCollection;
    QPainter mPainter;
    void initSizes();
	QBrush mSavedBrush;
};

}; // namespace

#endif // RTKOUTPUTQPAINTER

