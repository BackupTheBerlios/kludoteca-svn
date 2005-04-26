/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkstyle.h RTK style object
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

#ifndef RTKSTYLE_H
#define RTKSTYLE_H

#include "rtknamespace.h"
#include "rtkvariant.h"

namespace RTK {

class Style {

/*<<<<<STYLE_CONSTRUCTOR*/
public:
	Style(const String& name = String::null, const Variant &marginleft = 0, 
		const Variant &marginright = 0, const Variant &margintop = 0, const Variant &marginbottom = 0, 
		const Variant &visible = true, const Variant &supressed = false, const Variant &fontfamily = String::null, 
		const Variant &fontsize = 12, const Variant &fontweight = 0, const Variant &fontitalic = false, 
		const Variant &mask = String::null, const Variant &format = String::null, const Variant &halignment = AlignAuto, 
		const Variant &valignment = AlignTop, const Variant &maxlines = 0, const Variant &minfontsize = 8, 
		const Variant &adjustment = AdjustTrim, const Variant &textcolor = Qt::black, const Variant &backcolor = Qt::white, 
		const Variant &bordercolor = Qt::black, const Variant &borderwidth = 0, const Variant &borderstyle = BorderNone, const Variant &backgroundimage = String::null)
	:mName(name), mMarginLeft(marginleft), 
		mMarginRight(marginright), mMarginTop(margintop), mMarginBottom(marginbottom), 
		mVisible(visible), mSupressed(supressed), mFontFamily(fontfamily), 
		mFontSize(fontsize), mFontWeight(fontweight), mFontItalic(fontitalic), 
		mMask(mask), mFormat(format), mHAlignment(halignment), 
		mVAlignment(valignment), mMaxLines(maxlines), mMinFontSize(minfontsize), 
		mAdjustment(adjustment), mTextColor(textcolor), mBackColor(backcolor), 
		mBorderColor(bordercolor), mBorderWidth(borderwidth), mBorderStyle(borderstyle), mBackgroundImage(backgroundimage)
/*>>>>>STYLE_CONSTRUCTOR*/
	{};
  

/*<<<<<STYLE_GETSET*/
public:
	/** Gets Style's name */
	const String& getName() const { return mName; };
	/** Sets the Style's name */
	void setName(const String& name) { mName = name; };
	/** Gets Object's left margin in 'UnitMarginLeft' units */
	String getMarginLeft() const { return mMarginLeft.toString(); }
	bool isNullMarginLeft() const { return mMarginLeft.isNull(); }
	/** Sets the Object's left margin in 'UnitMarginLeft' units */
	void setMarginLeft(const Variant & marginleft) { mMarginLeft = marginleft; };
	/** Gets Object's right margin in 'UnitMarginRight' units */
	String getMarginRight() const { return mMarginRight.toString(); }
	bool isNullMarginRight() const { return mMarginRight.isNull(); }
	/** Sets the Object's right margin in 'UnitMarginRight' units */
	void setMarginRight(const Variant & marginright) { mMarginRight = marginright; };
	/** Gets Object's top margin in 'UnitMarginTop' units */
	String getMarginTop() const { return mMarginTop.toString(); }
	bool isNullMarginTop() const { return mMarginTop.isNull(); }
	/** Sets the Object's top margin in 'UnitMarginTop' units */
	void setMarginTop(const Variant & margintop) { mMarginTop = margintop; };
	/** Gets Object's bottom margin in 'UnitMarginBottom' units */
	String getMarginBottom() const { return mMarginBottom.toString(); }
	bool isNullMarginBottom() const { return mMarginBottom.isNull(); }
	/** Sets the Object's bottom margin in 'UnitMarginBottom' units */
	void setMarginBottom(const Variant & marginbottom) { mMarginBottom = marginbottom; };
	/** Gets whether the object is visible (but still computed) */
	bool isVisible() const { return mVisible.toBool(); }
	bool isNullVisible() const { return mVisible.isNull(); }
	/** Sets the whether the object is visible (but still computed) */
	void setVisible(const Variant & visible) { mVisible = visible; };
	/** Gets whether the object is supressed (not computed) */
	bool isSupressed() const { return mSupressed.toBool(); }
	bool isNullSupressed() const { return mSupressed.isNull(); }
	/** Sets the whether the object is supressed (not computed) */
	void setSupressed(const Variant & supressed) { mSupressed = supressed; };
	/** Gets Object's Font family */
	String getFontFamily() const { return mFontFamily.toString(); }
	bool isNullFontFamily() const { return mFontFamily.isNull(); }
	/** Sets the Object's Font family */
	void setFontFamily(const Variant & fontfamily) { mFontFamily = fontfamily; };
	/** Gets Object's Font size */
	int getFontSize() const { return mFontSize.toInt(); }
	bool isNullFontSize() const { return mFontSize.isNull(); }
	/** Sets the Object's Font size */
	void setFontSize(const Variant & fontsize) { mFontSize = fontsize; };
	/** Gets Object's Font weight */
	int getFontWeight() const { return mFontWeight.toInt(); }
	bool isNullFontWeight() const { return mFontWeight.isNull(); }
	/** Sets the Object's Font weight */
	void setFontWeight(const Variant & fontweight) { mFontWeight = fontweight; };
	/** Gets whether the oject's font is italic */
	bool isFontItalic() const { return mFontItalic.toBool(); }
	bool isNullFontItalic() const { return mFontItalic.isNull(); }
	/** Sets the whether the oject's font is italic */
	void setFontItalic(const Variant & fontitalic) { mFontItalic = fontitalic; };
	/** Gets Object's mask to display the value */
	String getMask() const { return mMask.toString(); }
	bool isNullMask() const { return mMask.isNull(); }
	/** Sets the Object's mask to display the value */
	void setMask(const Variant & mask) { mMask = mask; };
	/** Gets Object's format to display the value */
	String getFormat() const { return mFormat.toString(); }
	bool isNullFormat() const { return mFormat.isNull(); }
	/** Sets the Object's format to display the value */
	void setFormat(const Variant & format) { mFormat = format; };
	/** Gets Object's horizontal alignment */
	AlignmentType getHAlignment() const { return mHAlignment.toAlignmentType(); }
	bool isNullHAlignment() const { return mHAlignment.isNull(); }
	/** Sets the Object's horizontal alignment */
	void setHAlignment(const Variant & halignment) { mHAlignment = halignment; };
	/** Gets Object's vertical alignment */
	AlignmentType getVAlignment() const { return mVAlignment.toAlignmentType(); }
	bool isNullVAlignment() const { return mVAlignment.isNull(); }
	/** Sets the Object's vertical alignment */
	void setVAlignment(const Variant & valignment) { mVAlignment = valignment; };
	/** Gets Object's maximum number of lines */
	int getMaxLines() const { return mMaxLines.toInt(); }
	bool isNullMaxLines() const { return mMaxLines.isNull(); }
	/** Sets the Object's maximum number of lines */
	void setMaxLines(const Variant & maxlines) { mMaxLines = maxlines; };
	/** Gets Object's minimun font size */
	int getMinFontSize() const { return mMinFontSize.toInt(); }
	bool isNullMinFontSize() const { return mMinFontSize.isNull(); }
	/** Sets the Object's minimun font size */
	void setMinFontSize(const Variant & minfontsize) { mMinFontSize = minfontsize; };
	/** Gets Object's type of adjudstment */
	AdjustmentType getAdjustment() const { return mAdjustment.toAdjustmentType(); }
	bool isNullAdjustment() const { return mAdjustment.isNull(); }
	/** Sets the Object's type of adjudstment */
	void setAdjustment(const Variant & adjustment) { mAdjustment = adjustment; };
	/** Gets Object's text color */
	Color getTextColor() const { return mTextColor.toColor(); }
	bool isNullTextColor() const { return mTextColor.isNull(); }
	/** Sets the Object's text color */
	void setTextColor(const Variant & textcolor) { mTextColor = textcolor; };
	/** Gets Object's back color */
	Color getBackColor() const { return mBackColor.toColor(); }
	bool isNullBackColor() const { return mBackColor.isNull(); }
	/** Sets the Object's back color */
	void setBackColor(const Variant & backcolor) { mBackColor = backcolor; };
	/** Gets Object's border color */
	Color getBorderColor() const { return mBorderColor.toColor(); }
	bool isNullBorderColor() const { return mBorderColor.isNull(); }
	/** Sets the Object's border color */
	void setBorderColor(const Variant & bordercolor) { mBorderColor = bordercolor; };
	/** Gets Object's border width */
	int getBorderWidth() const { return mBorderWidth.toInt(); }
	bool isNullBorderWidth() const { return mBorderWidth.isNull(); }
	/** Sets the Object's border width */
	void setBorderWidth(const Variant & borderwidth) { mBorderWidth = borderwidth; };
	/** Gets Object's border style */
	BorderStyle getBorderStyle() const { return mBorderStyle.toBorderStyle(); }
	bool isNullBorderStyle() const { return mBorderStyle.isNull(); }
	/** Sets the Object's border style */
	void setBorderStyle(const Variant & borderstyle) { mBorderStyle = borderstyle; };
	/** Gets Name of the background image */
	String getBackgroundImage() const { return mBackgroundImage.toString(); }
	bool isNullBackgroundImage() const { return mBackgroundImage.isNull(); }
	/** Sets the Name of the background image */
	void setBackgroundImage(const Variant & backgroundimage) { mBackgroundImage = backgroundimage; };
protected:
	String mName;
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
/*>>>>>STYLE_GETSET*/

};

}; // namespace

#endif
