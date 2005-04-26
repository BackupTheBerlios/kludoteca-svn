/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtksection.h RTK section object
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
#ifndef RTKSECTION_H
#define RTKSECTION_H

#include <vector>

#include "rtkobject.h"

namespace RTK {

class Section: public Object
{
    friend class Report;
/*<<<<<SECTION_CONSTRUCTOR*/
public:
	Section(SectionType type = SectionDetails, const String& groupname = "", 
		Variant groupvalue = Variant(), uint grouplevel = 0, Variant pagebefore = false, 
		Variant pageafter = false, Variant resetnpage = false, Variant supifblank = false, Variant repeatheader = false,
	const String& name = String::null, Variant value = 0, 
		AggregateType aggregate = AggNone, String posx = 0, String posy = 0, 
		String sizex = 0, String sizey = 0, const String& style = String::null, 
		const String& url = String::null, const String& tag = String::null, Variant marginleft = 0, 
		Variant marginright = 0, Variant margintop = 0, Variant marginbottom = 0, 
		Variant visible = true, Variant supressed = false, Variant fontfamily = String::null, 
		Variant fontsize = 12, Variant fontweight = 0, Variant fontitalic = false, 
		Variant mask = String::null, Variant format = String::null, Variant halignment = AlignAuto, 
		Variant valignment = AlignTop, Variant maxlines = 0, Variant minfontsize = 8, 
		Variant adjustment = AdjustTrim, Variant textcolor = Qt::black, Variant backcolor = Qt::white, 
		Variant bordercolor = Qt::black, Variant borderwidth = 0, Variant borderstyle = BorderNone, Variant backgroundimage = String::null)
	:Object(name, value, 
		aggregate, posx, posy, 
		sizex, sizey, style, 
		url, tag, marginleft, 
		marginright, margintop, marginbottom, 
		visible, supressed, fontfamily, 
		fontsize, fontweight, fontitalic, 
		mask, format, halignment, 
		valignment, maxlines, minfontsize, 
		adjustment, textcolor, backcolor, 
		bordercolor, borderwidth, borderstyle, backgroundimage),
	mType(type), mGroupName(groupname), 
		mGroupValue(groupvalue), mGroupLevel(grouplevel), mPageBefore(pagebefore), 
		mPageAfter(pageafter), mResetNPage(resetnpage), mSupIfBlank(supifblank), mRepeatHeader(repeatheader)
/*>>>>>SECTION_CONSTRUCTOR*/
	, mRecordCount(0)
    {};

    bool groupChanged() const { return mNextRealGroupValue != mRealGroupValue; }
	void setRealGroupValue(Variant value) { mRealGroupValue = mNextRealGroupValue; mNextRealGroupValue = value; };
	Variant getRealGroupValue() { return mRealGroupValue; }
    
  uint getNObjects() const { return mObjects.size(); }
  Object *getObject(const String &name) const;
  Object *getObject(int i) const;
  int insertObject(Object *object);
/*<<<<<SECTION_INSERTOBJECT*/
	int insertObject(String name = String::null, Variant value = 0, AggregateType aggregate = AggNone, String posx = 0, String posy = 0, String sizex = 0, String sizey = 0, String style = String::null, String url = String::null, String tag = String::null, String marginleft = 0, String marginright = 0, String margintop = 0, String marginbottom = 0, bool visible = true, bool supressed = false, String fontfamily = String::null, int fontsize = 12, int fontweight = 0, bool fontitalic = false, String mask = String::null, String format = String::null, AlignmentType halignment = AlignAuto, AlignmentType valignment = AlignTop, int maxlines = 0, int minfontsize = 8, AdjustmentType adjustment = AdjustTrim, Color textcolor = Qt::black, Color backcolor = Qt::white, Color bordercolor = Qt::black, int borderwidth = 0, BorderStyle borderstyle = BorderNone, String backgroundimage = String::null);
/*>>>>>SECTION_INSERTOBJECT*/
  void fixObjectsMeasures(UnitsType outunit, Measure outsizex, Measure outsizey,
      UnitsType repunit, Measure repsizex, Measure repsizey);
  void calcAggregateValues(uint level);
	int getRecordCount() const { return mRecordCount; }
/*<<<<<SECTION_GETSET*/
public:
	/** Gets Section's type */
	SectionType getType() const { return mType; };
	/** Sets the Section's type */
	void setType(SectionType type) { mType = type; };
	/** Gets Section's group name */
	const String& getGroupName() const { return mGroupName; };
	/** Sets the Section's group name */
	void setGroupName(const String& groupname) { mGroupName = groupname; };
	/** Gets Section's group value */
	Variant getGroupValue() const { return mGroupValue; };
	/** Sets the Section's group value */
	void setGroupValue(Variant groupvalue) { mGroupValue = groupvalue; };
	/** Gets Section's group level */
	uint getGroupLevel() const { return mGroupLevel; };
	/** Sets the Section's group level */
	void setGroupLevel(uint grouplevel) { mGroupLevel = grouplevel; };
	/** Gets whether an end of page is printed before this section */
	bool isPageBefore() const;
	bool isNullPageBefore() const { return mPageBefore.isNull(); }
	/** Sets the whether an end of page is printed before this section */
	void setPageBefore(const Variant & pagebefore) { mPageBefore = pagebefore; };
	/** Gets whether an end of page is printed after this section */
	bool isPageAfter() const;
	bool isNullPageAfter() const { return mPageAfter.isNull(); }
	/** Sets the whether an end of page is printed after this section */
	void setPageAfter(const Variant & pageafter) { mPageAfter = pageafter; };
	/** Gets whether this section reset de page counter to 0 */
	bool isResetNPage() const;
	bool isNullResetNPage() const { return mResetNPage.isNull(); }
	/** Sets the whether this section reset de page counter to 0 */
	void setResetNPage(const Variant & resetnpage) { mResetNPage = resetnpage; };
	/** Gets whether this section is supressed if contains no data */
	bool isSupIfBlank() const;
	bool isNullSupIfBlank() const { return mSupIfBlank.isNull(); }
	/** Sets the whether this section is supressed if contains no data */
	void setSupIfBlank(const Variant & supifblank) { mSupIfBlank = supifblank; };
	/** Gets whether the section's header is repeated on every page */
	bool isRepeatHeader() const;
	bool isNullRepeatHeader() const { return mRepeatHeader.isNull(); }
	/** Sets the whether the section's header is repeated on every page */
	void setRepeatHeader(const Variant & repeatheader) { mRepeatHeader = repeatheader; };
protected:
	SectionType mType;
	String mGroupName;
	Variant mGroupValue;
	uint mGroupLevel;
	Variant mPageBefore;
	Variant mPageAfter;
	Variant mResetNPage;
	Variant mSupIfBlank;
	Variant mRepeatHeader;
/*>>>>>SECTION_GETSET*/
    
    QValueList<Object *> mObjects;
    Variant mRealGroupValue, mNextRealGroupValue;
	int mRecordCount;
    
#ifndef NDEBUG
public:
    int debug_print() const;
#endif
    
};

}; // namespace

#endif

