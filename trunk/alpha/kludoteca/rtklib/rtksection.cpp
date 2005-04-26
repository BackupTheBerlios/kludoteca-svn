/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtksection.cpp RTK section object
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

#include "rtksection.h"
#include "rtkreport.h"

using namespace RTK;

Object *Section::getObject(const String &name) const
{
        for( uint i=0; i<mObjects.size(); i++ )
                if( mObjects[i]->getName() == name )
                        return mObjects[i];
        return 0;
}

Object *Section::getObject(int i) const
{
        return mObjects[i];
}


int Section::insertObject(Object *object)
{
        object->setParent(this);
        mObjects.push_back(object);
        return mObjects.size();
}

/*<<<<<SECTION_INSERTOBJECT*/
int Section::insertObject(String name, Variant value, AggregateType aggregate, String posx, String posy, String sizex, String sizey, String style, String url, String tag, String marginleft, String marginright, String margintop, String marginbottom, bool visible, bool supressed, String fontfamily, int fontsize, int fontweight, bool fontitalic, String mask, String format, AlignmentType halignment, AlignmentType valignment, int maxlines, int minfontsize, AdjustmentType adjustment, Color textcolor, Color backcolor, Color bordercolor, int borderwidth, BorderStyle borderstyle, String backgroundimage)
{
	Object* object = new Object(
		name,value,aggregate,posx,posy,sizex,sizey,style,url,tag,marginleft,marginright,margintop,marginbottom,visible,supressed,fontfamily,fontsize,fontweight,fontitalic,mask,format,halignment,valignment,maxlines,minfontsize,adjustment,textcolor,backcolor,bordercolor,borderwidth,borderstyle,backgroundimage);
/*>>>>>SECTION_INSERTOBJECT*/
	 object->setParent(this); 
/*<<<<<SECTION_INSERTOBJECT_END*/
	mObjects.push_back(object);
	return mObjects.size();
}
/*>>>>>SECTION_INSERTOBJECT_END*/


#ifndef NDEBUG

int Section::debug_print() const
{
        printf("\tSection='%s'("
               "PageBefore='%d',"
               "PageAfter='%d',"
               "ResetNPage='%d',"
               "SupIfBlank='%d',"
               "RepeatHeader='%d')\n",
               (const char *)mName,
               mPageBefore.toInt(),
               mPageAfter.toInt(),
               mResetNPage.toInt(),
               mSupIfBlank.toInt(),
               mRepeatHeader.toInt());

        int ret=0;
        unsigned int it;
        for( it=0; it<mObjects.size(); it++ )
                ret += mObjects[it]->debug_print();
        return ret;
}

#endif

void Section::fixObjectsMeasures(UnitsType outunit, Measure outsizex, Measure outsizey,
                                 UnitsType repunit, Measure repsizex, Measure repsizey)
{
        uint nobj;
        for( nobj=0; nobj<mObjects.size(); nobj++ ) {
                mObjects[nobj]->fixMeasures(outunit, outsizex, outsizey,
                                            repunit, repsizex, repsizey);
        }
        return;
}

void Section::calcAggregateValues(uint level)
{
        for( uint i=0; i<mObjects.size(); i++ ) {
                mObjects[i]->calcAggregateValue(level);
        }
}

/*<<<<<SECTION_GET_PAGEBEFORE*/
bool Section::isPageBefore() const
{
	if( mPageBefore.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mPageBefore.toString()).toBool();
		if( !isNullPageBefore() )
			return mPageBefore.toBool();
		return false;
}
/*>>>>>SECTION_GET_PAGEBEFORE*/

/*<<<<<SECTION_GET_PAGEAFTER*/
bool Section::isPageAfter() const
{
	if( mPageAfter.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mPageAfter.toString()).toBool();
		if( !isNullPageAfter() )
			return mPageAfter.toBool();
		return false;
}
/*>>>>>SECTION_GET_PAGEAFTER*/
/*<<<<<SECTION_GET_RESETNPAGE*/
bool Section::isResetNPage() const
{
	if( mResetNPage.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mResetNPage.toString()).toBool();
		if( !isNullResetNPage() )
			return mResetNPage.toBool();
		return false;
}
/*>>>>>SECTION_GET_RESETNPAGE*/
/*<<<<<SECTION_GET_SUPIFBLANK*/
bool Section::isSupIfBlank() const
{
	if( mSupIfBlank.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mSupIfBlank.toString()).toBool();
		if( !isNullSupIfBlank() )
			return mSupIfBlank.toBool();
		return false;
}
/*>>>>>SECTION_GET_SUPIFBLANK*/
/*<<<<<SECTION_GET_REPEATHEADER*/
bool Section::isRepeatHeader() const
{
	if( mRepeatHeader.type() == Variant::tCFunctionType )
		return mReport->execCFunction(*this, mRepeatHeader.toString()).toBool();
		if( !isNullRepeatHeader() )
			return mRepeatHeader.toBool();
		return false;
}
/*>>>>>SECTION_GET_REPEATHEADER*/

