/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkobject.h RTK base object
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
#ifndef RTKOBJECT_H
#define RTKOBJECT_H

#include "rtknamespace.h"
#include "rtkvariant.h"
#include "rtkstyle.h"
#include "rtkformatter.h"
#include "rtkimage.h"

namespace RTK
{

class Object
{
        friend class Section;
/*<<<<<OBJECT_CONSTRUCTOR*/
public:
	Object(const String& name = String::null, Variant value = 0, 
		AggregateType aggregate = AggNone, String posx = 0, String posy = 0, 
		String sizex = 0, String sizey = 0, const String& style = String::null, 
		const String& url = String::null, const String& tag = String::null, const Variant &marginleft = 0, 
		const Variant &marginright = 0, const Variant &margintop = 0, const Variant &marginbottom = 0, 
		const Variant &visible = true, const Variant &supressed = false, const Variant &fontfamily = String::null, 
		const Variant &fontsize = 12, const Variant &fontweight = 0, const Variant &fontitalic = false, 
		const Variant &mask = String::null, const Variant &format = String::null, const Variant &halignment = AlignAuto, 
		const Variant &valignment = AlignTop, const Variant &maxlines = 0, const Variant &minfontsize = 8, 
		const Variant &adjustment = AdjustTrim, const Variant &textcolor = Qt::black, const Variant &backcolor = Qt::white, 
		const Variant &bordercolor = Qt::black, const Variant &borderwidth = 0, const Variant &borderstyle = BorderNone, const Variant &backgroundimage = String::null)
	:mName(name), mValue(value), 
		mAggregate(aggregate), mPosX(posx), mPosY(posy), 
		mSizeX(sizex), mSizeY(sizey), mStyle(style), 
		mUrl(url), mTag(tag), mMarginLeft(marginleft), 
		mMarginRight(marginright), mMarginTop(margintop), mMarginBottom(marginbottom), 
		mVisible(visible), mSupressed(supressed), mFontFamily(fontfamily), 
		mFontSize(fontsize), mFontWeight(fontweight), mFontItalic(fontitalic), 
		mMask(mask), mFormat(format), mHAlignment(halignment), 
		mVAlignment(valignment), mMaxLines(maxlines), mMinFontSize(minfontsize), 
		mAdjustment(adjustment), mTextColor(textcolor), mBackColor(backcolor), 
		mBorderColor(bordercolor), mBorderWidth(borderwidth), mBorderStyle(borderstyle), mBackgroundImage(backgroundimage)
/*>>>>>OBJECT_CONSTRUCTOR*/
                        , mParent(0), mIsConst(0)
        {}

        virtual ~Object() {}
		Variant::Type getType() const { return mRealValue.type(); }
        bool valueChanged() const
        {
                return mNextRealValue != mRealValue;
        }
        void setRealValue(Variant value)
        {
                mRealValue = mNextRealValue;
                mNextRealValue = value;
        };
        Object *getParent() const
        {
                return mParent;
        }
        void setReport(class Report *report)
        {
                mReport = report;
        }
        String getText() const;
        String getText(const String &mask, const String &format, const Formatter &f) const;
        void fixMeasures(UnitsType outunit, Measure outsizex, Measure outsizey,
                         UnitsType repunit, Measure repsizex, Measure repsizey);
        void calcAggregateValue(uint level);
        void resetAggregateValues(uint levels, uint level);
        Measure getFixedPosX() const
        {
                return mFixedPosX;
        };
        Measure getFixedPosY() const
        {
                return mFixedPosY;
        };
        Measure getFixedSizeX() const
        {
                return mFixedSizeX;
        };
        Measure getFixedSizeY() const
        {
                return mFixedSizeY;
        };
        Measure getFixedMarginLeft() const
        {
                return mFixedMarginLeft;
        };
        Measure getFixedMarginRight() const
        {
                return mFixedMarginRight;
        };
        Measure getFixedMarginTop() const
        {
                return mFixedMarginTop;
        };
        Measure getFixedMarginBottom() const
        {
                return mFixedMarginBottom;
        };
		bool isConst() const { return mIsConst; }
		void setConst(bool isconst) { mIsConst = isconst; }

        Variant getRealValue() const;

/*<<<<<OBJECT_GETSET*/
public:
	/** Gets Object's name */
	const String& getName() const { return mName; };
	/** Sets the Object's name */
	void setName(const String& name) { mName = name; };
	/** Gets Object's value */
	Variant getValue() const { return mValue; };
	/** Sets the Object's value */
	void setValue(Variant value) { mValue = value; };
	/** Gets Aggreate operation on the object */
	AggregateType getAggregate() const { return mAggregate; };
	/** Sets the Aggreate operation on the object */
	void setAggregate(AggregateType aggregate) { mAggregate = aggregate; };
	/** Gets Object's X position */
	String getPosX() const { return mPosX; };
	/** Sets the Object's X position */
	void setPosX(String posx) { mPosX = posx; };
	/** Gets Object's Y position */
	String getPosY() const { return mPosY; };
	/** Sets the Object's Y position */
	void setPosY(String posy) { mPosY = posy; };
	/** Gets Object's X size */
	String getSizeX() const { return mSizeX; };
	/** Sets the Object's X size */
	void setSizeX(String sizex) { mSizeX = sizex; };
	/** Gets Object's Y size */
	String getSizeY() const { return mSizeY; };
	/** Sets the Object's Y size */
	void setSizeY(String sizey) { mSizeY = sizey; };
	/** Gets Object's display style */
	String getStyle() const { return mStyle; };
	/** Sets the Object's display style */
	void setStyle(const String& style) { mStyle = style; };
	/** Gets Object's url */
	String getUrl() const { return mUrl; };
	/** Sets the Object's url */
	void setUrl(const String& url) { mUrl = url; };
	/** Gets Free text/comment for the object, not visible nor computed */
	String getTag() const { return mTag; };
	/** Sets the Free text/comment for the object, not visible nor computed */
	void setTag(const String& tag) { mTag = tag; };
	/** Gets Object's left margin */
	String getMarginLeft() const;
	bool isNullMarginLeft() const { return mMarginLeft.isNull(); }
	/** Sets the Object's left margin */
	void setMarginLeft(const Variant & marginleft) { mMarginLeft = marginleft; };
	/** Gets Object's right margin */
	String getMarginRight() const;
	bool isNullMarginRight() const { return mMarginRight.isNull(); }
	/** Sets the Object's right margin */
	void setMarginRight(const Variant & marginright) { mMarginRight = marginright; };
	/** Gets Object's top margin */
	String getMarginTop() const;
	bool isNullMarginTop() const { return mMarginTop.isNull(); }
	/** Sets the Object's top margin */
	void setMarginTop(const Variant & margintop) { mMarginTop = margintop; };
	/** Gets Object's bottom margin */
	String getMarginBottom() const;
	bool isNullMarginBottom() const { return mMarginBottom.isNull(); }
	/** Sets the Object's bottom margin */
	void setMarginBottom(const Variant & marginbottom) { mMarginBottom = marginbottom; };
	/** Gets visibility of the object (but still computed) */
	bool isVisible() const;
	bool isNullVisible() const { return mVisible.isNull(); }
	/** Sets the visibility of the object (but still computed) */
	void setVisible(const Variant & visible) { mVisible = visible; };
	/** Gets supression of the object (not computed) */
	bool isSupressed() const;
	bool isNullSupressed() const { return mSupressed.isNull(); }
	/** Sets the supression of the object (not computed) */
	void setSupressed(const Variant & supressed) { mSupressed = supressed; };
	/** Gets Object's Font family */
	String getFontFamily() const;
	bool isNullFontFamily() const { return mFontFamily.isNull(); }
	/** Sets the Object's Font family */
	void setFontFamily(const Variant & fontfamily) { mFontFamily = fontfamily; };
	/** Gets Object's Font size */
	int getFontSize() const;
	bool isNullFontSize() const { return mFontSize.isNull(); }
	/** Sets the Object's Font size */
	void setFontSize(const Variant & fontsize) { mFontSize = fontsize; };
	/** Gets Object's Font weight */
	int getFontWeight() const;
	bool isNullFontWeight() const { return mFontWeight.isNull(); }
	/** Sets the Object's Font weight */
	void setFontWeight(const Variant & fontweight) { mFontWeight = fontweight; };
	/** Gets whether the oject's font is italic */
	bool isFontItalic() const;
	bool isNullFontItalic() const { return mFontItalic.isNull(); }
	/** Sets the whether the oject's font is italic */
	void setFontItalic(const Variant & fontitalic) { mFontItalic = fontitalic; };
	/** Gets Object's mask to display the value */
	String getMask() const;
	bool isNullMask() const { return mMask.isNull(); }
	/** Sets the Object's mask to display the value */
	void setMask(const Variant & mask) { mMask = mask; };
	/** Gets Object's format to display the value */
	String getFormat() const;
	bool isNullFormat() const { return mFormat.isNull(); }
	/** Sets the Object's format to display the value */
	void setFormat(const Variant & format) { mFormat = format; };
	/** Gets Object's horizontal alignment */
	AlignmentType getHAlignment() const;
	bool isNullHAlignment() const { return mHAlignment.isNull(); }
	/** Sets the Object's horizontal alignment */
	void setHAlignment(const Variant & halignment) { mHAlignment = halignment; };
	/** Gets Object's vertical alignment */
	AlignmentType getVAlignment() const;
	bool isNullVAlignment() const { return mVAlignment.isNull(); }
	/** Sets the Object's vertical alignment */
	void setVAlignment(const Variant & valignment) { mVAlignment = valignment; };
	/** Gets Object's maximum number of lines */
	int getMaxLines() const;
	bool isNullMaxLines() const { return mMaxLines.isNull(); }
	/** Sets the Object's maximum number of lines */
	void setMaxLines(const Variant & maxlines) { mMaxLines = maxlines; };
	/** Gets Object's minimun font size */
	int getMinFontSize() const;
	bool isNullMinFontSize() const { return mMinFontSize.isNull(); }
	/** Sets the Object's minimun font size */
	void setMinFontSize(const Variant & minfontsize) { mMinFontSize = minfontsize; };
	/** Gets Object's type of adjudstment */
	AdjustmentType getAdjustment() const;
	bool isNullAdjustment() const { return mAdjustment.isNull(); }
	/** Sets the Object's type of adjudstment */
	void setAdjustment(const Variant & adjustment) { mAdjustment = adjustment; };
	/** Gets Object's text color */
	Color getTextColor() const;
	bool isNullTextColor() const { return mTextColor.isNull(); }
	/** Sets the Object's text color */
	void setTextColor(const Variant & textcolor) { mTextColor = textcolor; };
	/** Gets Object's back color */
	Color getBackColor() const;
	bool isNullBackColor() const { return mBackColor.isNull(); }
	/** Sets the Object's back color */
	void setBackColor(const Variant & backcolor) { mBackColor = backcolor; };
	/** Gets Object's border color */
	Color getBorderColor() const;
	bool isNullBorderColor() const { return mBorderColor.isNull(); }
	/** Sets the Object's border color */
	void setBorderColor(const Variant & bordercolor) { mBorderColor = bordercolor; };
	/** Gets Object's border width */
	int getBorderWidth() const;
	bool isNullBorderWidth() const { return mBorderWidth.isNull(); }
	/** Sets the Object's border width */
	void setBorderWidth(const Variant & borderwidth) { mBorderWidth = borderwidth; };
	/** Gets Object's border style */
	BorderStyle getBorderStyle() const;
	bool isNullBorderStyle() const { return mBorderStyle.isNull(); }
	/** Sets the Object's border style */
	void setBorderStyle(const Variant & borderstyle) { mBorderStyle = borderstyle; };
	/** Gets Name of the background image */
	String getBackgroundImage() const;
	bool isNullBackgroundImage() const { return mBackgroundImage.isNull(); }
	/** Sets the Name of the background image */
	void setBackgroundImage(const Variant & backgroundimage) { mBackgroundImage = backgroundimage; };
protected:
	String mName;
	Variant mValue;
	AggregateType mAggregate;
	String mPosX;
	String mPosY;
	String mSizeX;
	String mSizeY;
	String mStyle;
	String mUrl;
	String mTag;
	Variant mMarginLeft;
	Variant mMarginRight;
	Variant mMarginTop;
	Variant mMarginBottom;
	Variant mVisible;
	Variant mSupressed;
	Variant mFontFamily;
	Variant mFontSize;
	Variant mFontWeight;
	Variant mFontItalic;
	Variant mMask;
	Variant mFormat;
	Variant mHAlignment;
	Variant mVAlignment;
	Variant mMaxLines;
	Variant mMinFontSize;
	Variant mAdjustment;
	Variant mTextColor;
	Variant mBackColor;
	Variant mBorderColor;
	Variant mBorderWidth;
	Variant mBorderStyle;
	Variant mBackgroundImage;
/*>>>>>OBJECT_GETSET*/

protected:
        void setParent(Object *parent) { mParent=parent; }
		UnitsType getUnits(String value, UnitsType defaultunits);
		Measure getMeasure(String value);

#ifndef NDEBUG
public:
        virtual int debug_print() const;
#endif

private:
        Object *mParent;
        Report *mReport;

        Measure mFixedPosX;
        Measure mFixedPosY;
        Measure mFixedSizeX;
        Measure mFixedSizeY;
        Measure mFixedMarginLeft;
        Measure mFixedMarginRight;
        Measure mFixedMarginTop;
        Measure mFixedMarginBottom;
        Measure fixOneMeasure(UnitsType objunit, Measure measure,
                              UnitsType repunit, Measure repsize,
                              UnitsType outunit, Measure outsize);
        QValueList<Variant> mAggValues;
        Variant getNonAggregateValue() const;
        Variant mRealValue, mNextRealValue;
		bool mIsConst;
};

}; // namespace

#endif
