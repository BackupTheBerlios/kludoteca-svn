/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkreport.h RTK report object
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
#ifndef RTKREPORT_H
#define RTKREPORT_H

#include "rtknamespace.h"
#include "rtkvariant.h"
#include "rtkformatter.h"
#include "rtkregconfig.h"
#include "rtkstyle.h"
#include "rtkformula.h"
#include "rtkoutput.h"
#include "rtkinput.h"
#include "rtkobject.h"
#include "rtksection.h"

#include <qmap.h>

namespace RTK
{

typedef Variant ( CFunction ) ( const class Report &, const class Object &, const String & );
typedef CFunction *CFunctionPtr;


class Report: public Object
{

	friend class Section;
	friend class Object;

/*<<<<<REPORT_CONSTRUCTOR*/
public:
	Report(const String& title = String::null, UnitsType units = chars, 
		String stylespath = String::null, String imagespath = String::null,
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
	mTitle(title), mUnits(units), 
		mStylesPath(stylespath), mImagesPath(imagespath)
/*>>>>>REPORT_CONSTRUCTOR*/
			, pInput( 0 ), pOutput( 0 ), mGroupLevels( uint( -1 ) )
			, mFinished( false ), mStarted( false )
	{ initLocale(); }
	~Report();
	bool readXml( const String &filename, const String &defaultinput = String::null );
	bool readXmlStr( const String &xmldoc, const String &defaultinput = String::null );
	int print( Input &in, Output &out );
	int print( Output &out );

	/** \brief Gets a pointer to the input associated to this Report */
	Input *getInput() const { return pInput; }
	/** \brief Sets the input that will be used with this Report */
	void setInput( Input *input );

	/** \brief Finds an Image in the Report by name*/
	Image *findImage( const String &name ) const;
	/** \brief Deletes an Image from the Report */
	bool eraseImage( const String &name );
	/** \brief Inserts an Image in the Report */
	int insertImage( Image *image );
/*<<<<<REPORT_INSERTIMAGE*/
	int insertImage(String name = String::null, String url = String::null, String mimetype = String::null, String imagestyle = String::null);
/*>>>>>REPORT_INSERTIMAGE*/

	/** \brief Inserts an existing Section in the Report */
	int insertSection( Section *section );
	/** \brief Creates and inserts a Section in the Report */
	/*<<<<<REPORT_INSERTSECTION*/
	int insertSection(SectionType type = SectionDetails, String groupname = "", Variant groupvalue = Variant(), uint grouplevel = 0, bool pagebefore = false, bool pageafter = false, bool resetnpage = false, bool supifblank = false, bool repeatheader = false);
/*>>>>>REPORT_INSERTSECTION*/
	/** \brief Inserts a Style in the Report */
	int insertStyle( Style *style );
	/** \brief Deletes a Style from the Report */
	bool eraseStyle( const String &name );
	/** \brief Creates and inserts a Style in the Report */
	/*<<<<<REPORT_INSERTSTYLE*/
	int insertStyle(String name = String::null, String marginleft = 0, String marginright = 0, String margintop = 0, String marginbottom = 0, bool visible = true, bool supressed = false, String fontfamily = String::null, int fontsize = 12, int fontweight = 0, bool fontitalic = false, String mask = String::null, String format = String::null, AlignmentType halignment = AlignAuto, AlignmentType valignment = AlignTop, int maxlines = 0, int minfontsize = 8, AdjustmentType adjustment = AdjustTrim, Color textcolor = Qt::black, Color backcolor = Qt::white, Color bordercolor = Qt::black, int borderwidth = 0, BorderStyle borderstyle = BorderNone, String backgroundimage = String::null);
/*>>>>>REPORT_INSERTSTYLE*/
	/** \brief Inserts a Formula in the Report */
	int insertFormula( Formula *formula );
	/** \brief Creates and inserts a Formula in the Report */
	/*<<<<<REPORT_INSERTFORMULA*/
	int insertFormula(String name = String::null, String code = String::null);
/*>>>>>REPORT_INSERTFORMULA*/

	
	Section *getSection( const String &name ) const;
	/** \brief Gets a section by its index */
	Section *getSection( uint nsection ) const;
	/** \brief Gets a style by its name */
	Style *getStyle( const String &name ) const;
	/** \brief Gets a style by its index */
	Style *getStyle( uint nstyle ) const;

	const Formatter &getFormatter() const { return *pLocalFormatter; }
	
	void setImagesPath(const QString &path);
	void setStylesPath(const QString &path);
	const QString &getCWD() const { return mCWD; }
	/*<<<<<REPORT_GETSET*/
public:
	/** Gets Report title */
	const String& getTitle() const { return mTitle; };
	/** Sets the Report title */
	void setTitle(const String& title) { mTitle = title; };
	/** Gets Report units */
	UnitsType getUnits() const { return mUnits; };
	/** Sets the Report units */
	void setUnits(UnitsType units) { mUnits = units; };
	/** Gets Path to the xml style files */
	String getStylesPath() const { return mStylesPath; };
	/** Gets Path to the image files */
	String getImagesPath() const { return mImagesPath; };
protected:
	String mTitle;
	UnitsType mUnits;
	String mStylesPath;
	String mImagesPath;
/*>>>>>REPORT_GETSET*/

private:
	int readNext( Input &in );
	bool applyStyle( Object *object );
	uint getGroupLevels() const
	{
		return mGroupLevels;
	}
	void calcAggregateValues( uint level );
	void fixReportMeasures( const Output &out );
	bool isPageHeader( unsigned int nsect )
	{
		return mSections[ nsect ] ->getType() == SectionPageHeader;
	}
	bool isPageHeader( const Section &section )
	{
		return section.getType() == SectionPageHeader;
	}
	bool isPageFooter( unsigned int nsect )
	{
		return mSections[ nsect ] ->getType() == SectionPageFooter;
	}
	bool isPageFooter( const Section &section )
	{
		return section.getType() == SectionPageFooter;
	}
	bool isGroupHeader( unsigned int nsect )
	{
		return mSections[ nsect ] ->getType() == SectionGroupHeader;
	}
	bool isGroupHeader( const Section &section )
	{
		return section.getType() == SectionPageFooter;
	}
	bool isGroupFooter( unsigned int nsect )
	{
		return mSections[ nsect ] ->getType() == SectionGroupFooter;
	}
	bool isGroupFooter( const Section &section )
	{
		return section.getType() == SectionGroupFooter;
	}
	bool isDetails( unsigned int nsect )
	{
		return mSections[ nsect ] ->getType() == SectionDetails;
	}
	bool isDetails( const Section &section )
	{
		return section.getType() == SectionDetails;
	}
	int printPageHeaders( Output &out );
	int printPageFooters( Output &out );
	int printPageFooterIfNeeded( Output &out, Section &section );
	int printGroup( Input &in, Output &out, uint nsection = 0 );
	int printSection( Output &out, Section & );
	int printObject( Output &out, const Section &section,
	                 const Object &object );
	Measure calcSizeYSections( SectionType type ) const;
	Variant calcConstValue( const Variant& );
	void calcConstValues();
	Variant calcNonConstValue( const Variant&, Input &in );
	void calcNonConstValues( Input &in );
	bool changedGroupValue( uint level );
	int resetAggregateValues( uint level );
	int incRecordCount( uint level );
	void resetRecordCount( uint level );
	virtual CFunction mCFunction;
	Variant execCFunction( const Object &, const String &code );
	// { return Variant(); }

	Input *pInput;
	Output *pOutput;
	uint mGroupLevels;
	Measure mFootersHeight;
	String mInputName;
	QValueList<Section *>mSections;
	QValueList<Style *>mStyles;
	QValueList<BorderStyle *>mBorderStyles;
	QValueList<Formula *>mFormulas;
	QValueList<Image *>mImages;
	bool mFinished;
	bool mStarted;

	// Report variables
public:
	const QDateTime getReportDate() const
	{
		return mReportDate.toDateTime();
	}
	unsigned int getRecordCount() const
	{
		return mRecordCount.toUInt();
	}
	unsigned int getRecordNumber() const
	{
		return mRecordNumber.toUInt();
	}
	unsigned int getPageCount() const
	{
		return mPageCount.toUInt();
	}
	unsigned int getPageNumber() const
	{
		return mPageNumber.toUInt();
	}
private:
	Variant mReportDate;
	Variant mPageNumber, mPageCount;
	Variant mRecordNumber, mRecordCount;
	String mReportTitle;

#ifndef NDEBUG
public:
	int debug_print() const;
#endif

public:
	typedef Input* ( *InputCreatorFuncPtr ) ( const String &name, const String &driver );
	static int registerInput( const String &name, InputCreatorFuncPtr creator );
	static Input *createRegisteredInput( const String &name, const String &driver );
private:
	void initLocale();
	static QMap<String, InputCreatorFuncPtr> mRegisteredInputs;
	RegConfig mLocalRegConfig;
	Formatter *pLocalFormatter;
	QString mCWD;
};

}; // namespace

#endif // RTKREPORT_H


