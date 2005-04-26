/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutput.h RTK output object
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

#ifndef RTKOUTPUT_H
#define RTKOUTPUT_H

#include "rtknamespace.h"

namespace RTK
{

class Object;
class Section;
class Report;

class Output
{
/*<<<<<OUTPUT_CONSTRUCTOR*/
public:
	Output(PaperType papertype = A4, UnitsType units = dots, 
		Measure sizex = 595, Measure sizey = 841, Measure marginleft = 0, 
		Measure marginright = 0, Measure margintop = 0, Measure marginbottom = 0, int pageorientation = 0)
	:mPaperType(papertype), mUnits(units), 
		mSizeX(sizex), mSizeY(sizey), mMarginLeft(marginleft), 
		mMarginRight(marginright), mMarginTop(margintop), mMarginBottom(marginbottom), mPageOrientation(pageorientation)
/*>>>>>OUTPUT_CONSTRUCTOR*/
        { fixPaperSize();
        }
public:
        Output()
        {}
        ;
        virtual ~Output()
        {}
        ;
        virtual int startReport(const Report &report) = 0;
        virtual int endReport(const Report &report) = 0;
        virtual Measure startPage() = 0;
        virtual Measure endPage() = 0;
        virtual Measure startSection(const Section &section) = 0;
        virtual Measure endSection(const Section &section) = 0;
        virtual Measure startObject(const Section &section, const Object &object) = 0;
        virtual Measure endObject(const Section &section, const Object &object) = 0;
        virtual Measure printObject(const Report &report, const Section &section, const Object &object) = 0;
        virtual Measure setPosX(Measure newx);
        virtual Measure setPosY(Measure newy);
        virtual bool sectionFits(const Section &, Measure /*nextsectheight*/) const { return true; }

        int getCurrentPage()
        {
                return mCurrentPage;
        }
        int getTotalPages()
        {
                return mTotalPages;
        }

        /*<<<<<OUTPUT_GETSET*/
public:
	PaperType getPaperType() const { return mPaperType; };
	void setPaperType(PaperType papertype) { mPaperType = papertype; };
	UnitsType getUnits() const { return mUnits; };
	void setUnits(UnitsType units) { mUnits = units; };
	Measure getSizeX() const { return mSizeX; };
	void setSizeX(Measure sizex) { mSizeX = sizex; };
	Measure getSizeY() const { return mSizeY; };
	void setSizeY(Measure sizey) { mSizeY = sizey; };
	Measure getMarginLeft() const { return mMarginLeft; };
	void setMarginLeft(Measure marginleft) { mMarginLeft = marginleft; };
	Measure getMarginRight() const { return mMarginRight; };
	void setMarginRight(Measure marginright) { mMarginRight = marginright; };
	Measure getMarginTop() const { return mMarginTop; };
	void setMarginTop(Measure margintop) { mMarginTop = margintop; };
	Measure getMarginBottom() const { return mMarginBottom; };
	void setMarginBottom(Measure marginbottom) { mMarginBottom = marginbottom; };
	int getPageOrientation() const { return mPageOrientation; };
	void setPageOrientation(int pageorientation) { mPageOrientation = pageorientation; };
protected:
	PaperType mPaperType;
	UnitsType mUnits;
	Measure mSizeX;
	Measure mSizeY;
	Measure mMarginLeft;
	Measure mMarginRight;
	Measure mMarginTop;
	Measure mMarginBottom;
	int mPageOrientation;
/*>>>>>OUTPUT_GETSET*/

protected:
		static PaperSize mPaperSizes[];
        int mCurrentPage, mTotalPages;
        Measure mCurrX, mCurrY, mGrowthY;

private:
        void fixPaperSize();
};

}; // namespace

#endif
