/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkxmlreport.cpp RTK XML Report definition reader
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


#include <qnamespace.h>
#include <qxml.h>
#include <qfileinfo.h>

#include "rtkinput.h"
#include "rtkinputcsv.h"
#include "rtkinputsql.h"
#include "rtkreport.h"


/*
	TODO
	Has the name property of the report to match the filename?

*/


namespace RTK
{

class XmlParser: public QXmlDefaultHandler
{
public:
	XmlParser( Report *report );
	bool read( const String &xmlfilename, const String &defaultinput );
	bool readStr( const String &xmldoc, const String &defaultinput );

private:
	bool startDocument();
	bool startElement( const QString&, const QString&, const QString& ,
	                   const QXmlAttributes& );
	bool endElement( const QString&, const QString&, const QString& );
	bool characters( const QString& );
	bool error ( const QXmlParseException &exception );
	bool warning( const QXmlParseException& );
	bool fatalError( const QXmlParseException& );
	bool resolveEntity( const QString & publicId, const QString & systemId, QXmlInputSource *& ret );

	bool toBool( const String &sbool );
	Measure stringToMeasure( const String &svalue );
	String stringToFormula( const String &formula );
	UnitsType stringToUnits( const String &sunit );
	SectionType stringToSectionType( const String &stype );
	AggregateType stringToAggregate( const String &sadj );
	const Image *stringToImage( const String &simage );
	PaperType stringToPaperType( const String &spaper );

	Variant stringToFontWeight( const String &sfw );
	Variant stringToBorderStyle( const String &sbt );
	Variant stringToColor( const String &scolor );
	Variant stringToAdjustment( const String &sadj );
	Variant stringToAlignment( const String &salignment );
	Variant stringToVariant( const String &text );
	Variant stringToTrue( const String &sb );
	Variant stringToFalse( const String &sb );
	Variant stringToString( const String &sb );
	Variant stringToInt( const String &si );
	Variant stringToCFunction( const String &fuction );

	Report *pReport;
	Section *pSection;
	Object *pObject;
	Style *pStyle;
	Formula *pFormula;
	Image *pImage;
	Input *pInput;
	InputField *pInputField;
	String pReportName;
	String mFileName;
	String mDefaultInput;
};

}; // namespace

using namespace RTK;

XmlParser::XmlParser( Report *report )
{
	pReport = report;
	pSection = 0;
	pObject = 0;
	pStyle = 0;
	pFormula = 0;
	pImage = 0;
	pInput = 0;
	pInputField = 0;
}

bool XmlParser::readStr( const String &xmldoc, const String &defaultinput )
{
	bool ret;
	
	mDefaultInput = defaultinput;

	QXmlInputSource source;
	source.setData(xmldoc);
	
	QXmlSimpleReader reader;
	reader.setContentHandler( this );
	reader.setErrorHandler( this );
	reader.setEntityResolver( this );

	if ( !( ret = reader.parse( &source ) ) )
		fprintf( stderr, "RTK:ReadXML:Error reading\n" );
	return ret;
}

bool XmlParser::read( const String &xmlfilename, const String &defaultinput )
{
	bool ret;
	QFile xmlfile( mFileName = xmlfilename );
	mDefaultInput = defaultinput;
#if DEBUG_RTK > 0	
	qDebug("RTK:ReadXML:Reading %s\n", ( const char * ) xmlfilename );
#endif	
	QXmlInputSource source( &xmlfile );
	QXmlSimpleReader reader;
	reader.setContentHandler( this );
	reader.setErrorHandler( this );
	reader.setEntityResolver( this );

	if ( !( ret = reader.parse( source ) ) )
		fprintf( stderr, "RTK:ReadXML:Error reading %s\n", ( const char * ) xmlfilename );
	return ret;
}


bool XmlParser::resolveEntity( const QString & publicId, const QString & systemId, QXmlInputSource *& ret )
{
#if DEBUG_RTK > 0
	qDebug( "RTK:ReadXML:resolveEntity %s %s", ( const char * ) publicId, ( const char * ) systemId );
#endif	
	QString entitypath = RTK::findInPath(pReport->getStylesPath(), systemId, pReport->getCWD());
	QFile entityfile( entitypath );
	if( !entityfile.exists() )
		qWarning("RTK:ReadXML:resolveEntity:Unable to find pub:'%s',sys:'%s' in path:'%s'", 
		(const char *)publicId, (const char *)systemId, (const char *)pReport->getStylesPath());
	ret = new QXmlInputSource( &entityfile );
	return true;
}


bool XmlParser::toBool( const String &sbool )
{
	const char * csbool = ( const char * ) sbool;
	return sbool.isEmpty() ||
	       ( qstricmp( csbool, "false" ) != 0
	         && qstricmp( csbool, "no" ) != 0
	         && qstrcmp( csbool, "0" ) != 0 );
}


Variant XmlParser::stringToTrue( const String &sb )
{
	if ( sb.isEmpty() )
		return Variant(); // Null value
	else
		return toBool( sb );
}

Variant XmlParser::stringToFalse( const String &sb )
{
	if ( sb.isEmpty() )
		return Variant(); // Null value
	else
		return toBool( sb );
}



Variant XmlParser::stringToString( const String &s )
{
	if ( s.isEmpty() )
		return Variant();
	else
		return s;
}


Variant XmlParser::stringToInt( const String &s )
{
	if ( s.isEmpty() )
		return Variant();
	else
		return s.toInt();
}

String XmlParser::stringToFormula( const String &formula )
{
	return formula;
}

Variant XmlParser::stringToVariant( const String &text )
{
	return Variant( text );
}

Variant XmlParser::stringToCFunction( const String & sfunction )
{
	QStringList tokens;
	tokenize( tokens, sfunction, " \t\n" );
	if ( tokens.size() > 1 ) {
		if ( tokens[ 0 ] == "cfunction" ) {
			Variant v = tokens[ 1 ];
			// Ojo      v.setCFunctionType();
			return v;
		}
	}
	return Variant();
}


Variant XmlParser::stringToAlignment( const String &sal )
{
	const char *csal = ( const char * ) sal;
	if ( qstricmp( csal, "left" ) == 0 )
		return AlignLeft;
	else if ( qstricmp( csal, "right" ) == 0 )
		return AlignRight;
	else if ( qstricmp( csal, "center" ) == 0 )
		return AlignCenter;
	else if ( qstricmp( csal, "justify" ) == 0 || qstricmp( csal, "justified" ) == 0 )
		return AlignJustify;
	else if ( qstricmp( csal, "top" ) == 0 || qstricmp( csal, "up" ) == 0 )
		return AlignTop;
	else if ( qstricmp( csal, "middle" ) == 0 )
		return AlignMiddle;
	else if ( qstricmp( csal, "nowordwrap" ) == 0 )
		return AlignNoWordWrap;
	else if ( qstricmp( csal, "bottom" ) == 0 || qstricmp( csal, "down" ) == 0 )
		return AlignBottom;
	else if ( qstricmp( csal, "auto" ) == 0 )
		return AlignAuto;
	else
		return Variant();
}

AggregateType XmlParser::stringToAggregate( const String &sagg )
{
	const char * csagg = ( const char * ) sagg;
	if ( qstricmp( csagg, "AggNone" ) == 0 || qstricmp( csagg, "None" ) == 0 )
		return AggNone;
	else if ( qstricmp( csagg, "AggCount" ) == 0 || qstricmp( csagg, "Count" ) == 0 )
		return AggCount;
	else if ( qstricmp( csagg, "AggSum" ) == 0 || qstricmp( csagg, "Sum" ) == 0 )
		return AggSum;
	else if ( qstricmp( csagg, "AggAvg" ) == 0 || qstricmp( csagg, "Avg" ) == 0 || qstricmp( csagg, "Average" ) == 0 )
		return AggAvg;
	else if ( qstricmp( csagg, "AggStdDv" ) == 0 || qstricmp( csagg, "StdDv" ) == 0 )
		return AggStdDv;
	else if ( qstricmp( csagg, "AggVariance" ) == 0 || qstricmp( csagg, "Variance" ) == 0 )
		return AggVariance;
		
	else if ( qstricmp( csagg, "AggDistinctCount" ) == 0 || qstricmp( csagg, "DistinctCount" ) == 0 )
		return AggDistinctCount;
	else if ( qstricmp( csagg, "AggDistinctSum" ) == 0 || qstricmp( csagg, "DistinctSum" ) == 0 )
		return AggDistinctSum;
	else if ( qstricmp( csagg, "AggDistinctAvg" ) == 0 || qstricmp( csagg, "DistinctAvg" ) == 0 || qstricmp( csagg, "DistinctAverage" ) == 0 )
		return AggDistinctAvg;
	else if ( qstricmp( csagg, "AggDistinctStdDv" ) == 0 || qstricmp( csagg, "DistinctStdDv" ) == 0 )
		return AggDistinctStdDv;
	else if ( qstricmp( csagg, "AggDistinctVariance" ) == 0 || qstricmp( csagg, "DistinctVariance" ) == 0 )
		return AggDistinctVariance;
	else // There is no invalid value
		return AggNone;
}


UnitsType XmlParser::stringToUnits( const String &sunit )
{
	const char * csunit = ( const char * ) csunit;
	if ( qstricmp( sunit, "chars" ) == 0 || qstricmp( sunit, "char" ) == 0 || sunit.length() == 0 )
		return RTK::chars;
	else if ( qstricmp( sunit, "pixel" ) == 0 || qstricmp( sunit, "pixels" ) == 0
	          || qstricmp( sunit, "dot" ) == 0 || qstricmp( sunit, "dots" ) == 0 )
		return RTK::dots;
	else if ( qstricmp( sunit, "inch" ) == 0 || qstricmp( sunit, "inches" ) == 0 )
		return RTK::inches;
	else if ( qstricmp( sunit, "cm" ) == 0 || qstricmp( sunit, "cms" ) == 0 )
		return RTK::cm;
	else if ( qstricmp( sunit, "mm" ) == 0 || qstricmp( sunit, "mms" ) == 0 )
		return RTK::mm;
	else if ( qstricmp( sunit, "p100" ) == 0 || qstricmp( sunit, "%" ) == 0 )
		return RTK::p100;
	else
		Q_ASSERT( 1 ==       /*Invalid unit type*/0 );
	return RTK::chars;
}

Measure XmlParser::stringToMeasure( const String & )
{
	Q_ASSERT( 0 );
	return 0.0;
}

PaperType stringToPaperType( const String &s )
{
	if ( s == "A4" )
		return A4;
	else if ( s == "B5" )
		return B5;
	else if ( s == "Letter" )
		return B5;
	else if ( s == "Legal" )
		return Legal;
	else if ( s == "Executive" )
		return Executive;
	else if ( s == "A0" )
		return A0;
	else if ( s == "A1" )
		return A1;
	else if ( s == "A2" )
		return A2;
	else if ( s == "A3" )
		return A3;
	else if ( s == "A4" )
		return A4;
	else if ( s == "A5" )
		return A5;
	else if ( s == "A6" )
		return A6;
	else if ( s == "A7" )
		return A7;
	else if ( s == "A8" )
		return A8;
	else if ( s == "A9" )
		return A9;
	else if ( s == "B0" )
		return B0;
	else if ( s == "B1" )
		return B1;
	else if ( s == "B10" )
		return B10;
	else if ( s == "B2" )
		return B2;
	else if ( s == "B3" )
		return B3;
	else if ( s == "B4" )
		return B4;
	else if ( s == "B5" )
		return B5;
	else if ( s == "B6" )
		return B6;
	else if ( s == "B7" )
		return B7;
	else if ( s == "B8" )
		return B8;
	else if ( s == "B9" )
		return B9;
	else if ( s == "C5E" )
		return C5E;
	else if ( s == "Comm10E" )
		return Comm10E;
	else if ( s == "DLE" )
		return DLE;
	else if ( s == "Folio" )
		return Folio;
	else if ( s == "Ledger" )
		return Ledger;
	else if ( s == "Tabloid" )
		return Tabloid;
	else
		return Custom;
}



Variant XmlParser::stringToFontWeight( const String &sfw )
{
	if ( sfw.isEmpty() )
		return Variant(); // Null value
	const char *csfw = ( const char * ) sfw;
	if ( qstricmp( csfw, "Light" ) == 0 )
		return 25;
	else if ( qstricmp( csfw, "Normal" ) == 0 )
		return 50;
	else if ( qstricmp( csfw, "DemiBold" ) == 0 )
		return 63;
	else if ( qstricmp( csfw, "Bold" ) == 0 )
		return 75;
	else if ( qstricmp( csfw, "Black" ) == 0 )
		return 87;
	else {
		int w = sfw.toInt();
		if ( w == 0 )
			return Variant();
		else
			return w;
	}
}


SectionType XmlParser::stringToSectionType( const String &stype )
{
	const char * cstype = ( const char * ) stype;
	if ( qstricmp( cstype, "REPORT-HEADER" ) == 0 )
		return ::SectionReportHeader;
	else if ( qstricmp( cstype, "REPORT-FOOTER" ) == 0 )
		return ::SectionReportFooter;
	else if ( qstricmp( cstype, "PAGE-HEADER" ) == 0 )
		return ::SectionPageHeader;
	else if ( qstricmp( cstype, "PAGE-FOOTER" ) == 0 )
		return ::SectionPageFooter;
	else if ( qstricmp( cstype, "GROUP-HEADER" ) == 0 )
		return ::SectionGroupHeader;
	else if ( qstricmp( cstype, "GROUP-FOOTER" ) == 0 )
		return ::SectionGroupFooter;
	else if ( qstricmp( cstype, "DETAILS" ) == 0 )
		return ::SectionDetails;
	else {
		qFatal( "Unknown section type: %s", ( const char * ) stype );
	}
	return ::SectionDetails;
}

Variant XmlParser::stringToAdjustment( const String &sadj )
{
	if ( sadj.isEmpty() )
		return Variant();
	const char *csadj = ( const char * ) sadj;
	if ( qstricmp( csadj, "TRIM" ) == 0 )
		return ::AdjustTrim;
	else if ( qstricmp( csadj, "NONE" ) == 0 )
		return ::AdjustNone;
	else if ( qstricmp( csadj, "GROW" ) == 0 )
		return ::AdjustGrow;
	else if ( qstricmp( csadj, "REDUCEFONT" ) == 0 )
		return ::AdjustReduceFont;
	else if ( qstricmp( csadj, "SHRINK" ) == 0 )
		return ::AdjustShrink;
	else
		return Variant(); // Undefined
}

/*!
    Sets the RGB value to \a name, which may be in one of these
    formats:
    \list
    \i #RGB (each of R, G and B is a single hex digit)
    \i #RRGGBB
    \i #RRRGGGBBB
    \i #RRRRGGGGBBBB
    \i A name from the X color database (rgb.txt) (e.g.
    "steelblue" or "gainsboro"). These color names also work
    under Windows.
    \endlist

    The color is invalid if \a name cannot be parsed.
*/

Variant XmlParser::stringToColor( const String &scolor )
{
	if ( scolor.isEmpty() )
		return Variant(); // Null value
	else {
		QColor c(scolor);
		if( !c.isValid() )
			return Variant(); // It can be a formula.
		else
			return c; 
	}
}


Variant XmlParser::stringToBorderStyle( const String &sbt )
{
	if ( sbt.isEmpty() )
		return Variant();
	const char *csbt = ( const char * ) sbt;
	if ( qstricmp( csbt, "None" ) == 0 || sbt.isEmpty() )
		return RTK::BorderNone;
	else if ( qstricmp( csbt, "Solid" ) == 0 )
		return RTK::BorderSolid;
	else if ( qstricmp( csbt, "Dash" ) == 0 )
		return RTK::BorderDash;
	else if ( qstricmp( csbt, "Dot" ) == 0 )
		return RTK::BorderDot;
	else if ( qstricmp( csbt, "DashDot" ) == 0 )
		return RTK::BorderDashDot;
	else if ( qstricmp( csbt, "DashDotDot" ) == 0 )
		return RTK::BorderDashDotDot;
	else 	
		return Variant();
}

const Image *XmlParser::stringToImage( const String &simage )
{
	Q_UNUSED(simage);
	return 0;
}




bool XmlParser::startDocument()
{
	return TRUE;
}

bool XmlParser::characters( const QString& )
{
	return TRUE;
}


bool XmlParser::startElement( const QString&, const QString&,
                              const QString& qName,
                              const QXmlAttributes& attrs )
{
	const QString & tagname = qName.upper();
	if ( tagname == "REPORT" ) {     
#if DEBUG_RTK > 1
		qDebug("RTK:ReadXml:Report:%s", (const char *)attrs.value("filename"));
#endif
		pReport->setName( attrs.value( "filename" ) );
/*<<<<<REPORT_READXML*/
		pReport->setTitle(attrs.value("title"));
		pReport->setUnits(stringToUnits(attrs.value("units")));
		pReport->setStylesPath(attrs.value("stylespath"));
		pReport->setImagesPath(attrs.value("imagespath"));
		pReport->setName(attrs.value("name"));
		pReport->setValue(stringToVariant(attrs.value("value")));
		pReport->setAggregate(stringToAggregate(attrs.value("aggregate")));
		pReport->setPosX(attrs.value("posx"));
		pReport->setPosY(attrs.value("posy"));
		pReport->setSizeX(attrs.value("sizex"));
		pReport->setSizeY(attrs.value("sizey"));
		pReport->setStyle(String(attrs.value("style")));
		pReport->setUrl(String(attrs.value("url")));
		pReport->setTag(String(attrs.value("tag")));
		pReport->setMarginLeft(attrs.value("marginleft"));
		pReport->setMarginRight(attrs.value("marginright"));
		pReport->setMarginTop(attrs.value("margintop"));
		pReport->setMarginBottom(attrs.value("marginbottom"));
		pReport->setVisible(stringToTrue(attrs.value("visible")));
		pReport->setSupressed(stringToFalse(attrs.value("supressed")));
		pReport->setFontFamily(stringToString(attrs.value("fontfamily")));
		pReport->setFontSize(stringToInt(attrs.value("fontsize")));
		pReport->setFontWeight(stringToFontWeight(attrs.value("fontweight")));
		pReport->setFontItalic(stringToFalse(attrs.value("fontitalic")));
		pReport->setMask(stringToString(attrs.value("mask")));
		pReport->setFormat(stringToString(attrs.value("format")));
		pReport->setHAlignment(stringToAlignment(attrs.value("halignment")));
		pReport->setVAlignment(stringToAlignment(attrs.value("valignment")));
		pReport->setMaxLines(stringToInt(attrs.value("maxlines")));
		pReport->setMinFontSize(stringToInt(attrs.value("minfontsize")));
		pReport->setAdjustment(stringToAdjustment(attrs.value("adjustment")));
		pReport->setTextColor(stringToColor(attrs.value("textcolor")));
		pReport->setBackColor(stringToColor(attrs.value("backcolor")));
		pReport->setBorderColor(stringToColor(attrs.value("bordercolor")));
		pReport->setBorderWidth(stringToInt(attrs.value("borderwidth")));
		pReport->setBorderStyle(stringToBorderStyle(attrs.value("borderstyle")));
		pReport->setBackgroundImage(attrs.value("backgroundimage"));
/*>>>>>REPORT_READXML*/
	} else if ( tagname == "STYLE" ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:Style:%s", (const char *)attrs.value("name"));
#endif
/*<<<<<STYLE_READXML*/
		pStyle= new Style(
				attrs.value("name"),
				attrs.value("marginleft"),
				attrs.value("marginright"),
				attrs.value("margintop"),
				attrs.value("marginbottom"),
				stringToTrue(attrs.value("visible")),
				stringToFalse(attrs.value("supressed")),
				stringToString(attrs.value("fontfamily")),
				stringToInt(attrs.value("fontsize")),
				stringToFontWeight(attrs.value("fontweight")),
				stringToFalse(attrs.value("fontitalic")),
				stringToString(attrs.value("mask")),
				stringToString(attrs.value("format")),
				stringToAlignment(attrs.value("halignment")),
				stringToAlignment(attrs.value("valignment")),
				stringToInt(attrs.value("maxlines")),
				stringToInt(attrs.value("minfontsize")),
				stringToAdjustment(attrs.value("adjustment")),
				stringToColor(attrs.value("textcolor")),
				stringToColor(attrs.value("backcolor")),
				stringToColor(attrs.value("bordercolor")),
				stringToInt(attrs.value("borderwidth")),
				stringToBorderStyle(attrs.value("borderstyle")),
				attrs.value("backgroundimage")	);
/*>>>>>STYLE_READXML*/
	} else if ( tagname == "FORMULA" ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:Formula:%s", (const char *)attrs.value("name"));
#endif
/*<<<<<FORMULA_READXML*/
		pFormula= new Formula(
				attrs.value("name"),
				attrs.value("code")	);
/*>>>>>FORMULA_READXML*/
	} else if ( tagname == "IMAGE" ) {
/*<<<<<IMAGE_READXML*/
		pImage= new Image(
				attrs.value("name"),
				attrs.value("url"),
				attrs.value("mimetype"),
				attrs.value("imagestyle")	);
/*>>>>>IMAGE_READXML*/
	} else if ( tagname == "INPUT" ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:Input:%s", (const char *)attrs.value("name"));
#endif
		if ( pInput == 0 ) { // If an input already exists, do not overwrite it
			// If there is no explicit input to use or the name matches the explicit one, choose this
			if ( mDefaultInput.length() == 0 || mDefaultInput.lower() == attrs.value( "name" ).lower() ) {
				QString driver = attrs.value( "driver" ).lower();
				QString name = attrs.value( "name" ).lower();
				if ( driver == "sql" ) {
/*<<<<<INPUTSQL_READXML*/
		pInput= new InputSql(
				attrs.value("sqldriver"),
				attrs.value("host"),
				attrs.value("port").toInt(),
				attrs.value("user"),
				attrs.value("password"),
				attrs.value("database"),
				attrs.value("from"),
				attrs.value("where"),
				attrs.value("orderby"),
				attrs.value("name"),
				attrs.value("driver")	);
/*>>>>>INPUTSQL_READXML*/
				} else if ( driver == "csv" ) {
/*<<<<<INPUTCSV_READXML*/
		pInput= new InputCsv(
				attrs.value("filename"),
				attrs.value("delimiters"),
				attrs.value("quote"),
				attrs.value("headerlines").toInt(),
				attrs.value("name"),
				attrs.value("driver")	);
/*>>>>>INPUTCSV_READXML*/
				InputCsv *pInputCsv = static_cast<InputCsv *>(pInput);
				if( pInputCsv->getQuote() == "" )
					pInputCsv->setQuote("\"");
				// Locate the csv file in the same dir than the report
				QString csvfile = RTK::findInPath("", attrs.value("filename"), pReport->getCWD());
				if( csvfile != attrs.value("filename") ) 
					pInputCsv->setFilename(csvfile);
				} else if ( driver == "text" ) {
					;
				} else {
					// Look up the registered inputs table for this driver
					pInput = Report::createRegisteredInput( name, driver );
					if ( pInput ) {
						pInput->parseAttrs( attrs );
					} else {
						fprintf(stderr, "RTK:ReadXML:Driver '%s' not registered for the input '%s'", ( const char * ) driver, ( const char * ) name );
						return false;
					}
				}
			}
		}
	} else if ( tagname == "INPUTFIELD" ) {
		if ( pInput ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:InputField:%s", (const char *)attrs.value("name"));
#endif
/*<<<<<INPUTFIELD_READXML*/
		pInputField= new InputField(
				attrs.value("name"),
				attrs.value("source"),
				Variant::nameToType(attrs.value("type"))	);
/*>>>>>INPUTFIELD_READXML*/
		}
	} else if ( tagname == "OUTPUT" ) {
		;
	} else if ( tagname == "SECTION" ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:Section:%s", (const char *)attrs.value("name"));
#endif
/*<<<<<SECTION_READXML*/
		pSection= new Section(
				stringToSectionType(attrs.value("type")),
				String(attrs.value("groupname")),
				stringToVariant(attrs.value("groupvalue")),
				attrs.value("grouplevel").toUInt(),
				stringToFalse(attrs.value("pagebefore")),
				stringToFalse(attrs.value("pageafter")),
				stringToFalse(attrs.value("resetnpage")),
				stringToFalse(attrs.value("supifblank")),
				stringToFalse(attrs.value("repeatheader")),
				attrs.value("name"),
				stringToVariant(attrs.value("value")),
				stringToAggregate(attrs.value("aggregate")),
				attrs.value("posx"),
				attrs.value("posy"),
				attrs.value("sizex"),
				attrs.value("sizey"),
				String(attrs.value("style")),
				String(attrs.value("url")),
				String(attrs.value("tag")),
				attrs.value("marginleft"),
				attrs.value("marginright"),
				attrs.value("margintop"),
				attrs.value("marginbottom"),
				stringToTrue(attrs.value("visible")),
				stringToFalse(attrs.value("supressed")),
				stringToString(attrs.value("fontfamily")),
				stringToInt(attrs.value("fontsize")),
				stringToFontWeight(attrs.value("fontweight")),
				stringToFalse(attrs.value("fontitalic")),
				stringToString(attrs.value("mask")),
				stringToString(attrs.value("format")),
				stringToAlignment(attrs.value("halignment")),
				stringToAlignment(attrs.value("valignment")),
				stringToInt(attrs.value("maxlines")),
				stringToInt(attrs.value("minfontsize")),
				stringToAdjustment(attrs.value("adjustment")),
				stringToColor(attrs.value("textcolor")),
				stringToColor(attrs.value("backcolor")),
				stringToColor(attrs.value("bordercolor")),
				stringToInt(attrs.value("borderwidth")),
				stringToBorderStyle(attrs.value("borderstyle")),
				attrs.value("backgroundimage")	);
/*>>>>>SECTION_READXML*/
	} else if ( tagname == "OBJECT" ) {
		if ( pSection ) {
#if DEBUG_RTK > 1
			qDebug("RTK:ReadXml:Object:%s", (const char *)attrs.value("name"));
#endif
/*<<<<<OBJECT_READXML*/
		pObject= new Object(
				attrs.value("name"),
				stringToVariant(attrs.value("value")),
				stringToAggregate(attrs.value("aggregate")),
				attrs.value("posx"),
				attrs.value("posy"),
				attrs.value("sizex"),
				attrs.value("sizey"),
				String(attrs.value("style")),
				String(attrs.value("url")),
				String(attrs.value("tag")),
				attrs.value("marginleft"),
				attrs.value("marginright"),
				attrs.value("margintop"),
				attrs.value("marginbottom"),
				stringToTrue(attrs.value("visible")),
				stringToFalse(attrs.value("supressed")),
				stringToString(attrs.value("fontfamily")),
				stringToInt(attrs.value("fontsize")),
				stringToFontWeight(attrs.value("fontweight")),
				stringToFalse(attrs.value("fontitalic")),
				stringToString(attrs.value("mask")),
				stringToString(attrs.value("format")),
				stringToAlignment(attrs.value("halignment")),
				stringToAlignment(attrs.value("valignment")),
				stringToInt(attrs.value("maxlines")),
				stringToInt(attrs.value("minfontsize")),
				stringToAdjustment(attrs.value("adjustment")),
				stringToColor(attrs.value("textcolor")),
				stringToColor(attrs.value("backcolor")),
				stringToColor(attrs.value("bordercolor")),
				stringToInt(attrs.value("borderwidth")),
				stringToBorderStyle(attrs.value("borderstyle")),
				attrs.value("backgroundimage")	);
/*>>>>>OBJECT_READXML*/
		} else {
			qWarning( "RTK:ReadXML:There is no section\n" );
			return false;
		}
	} else {
		qWarning( "RTK:ReadXML:unexpected start tag:%s\n", ( const char * ) tagname );
		return false;
	}
	return true;
}


bool XmlParser::endElement( const QString&, const QString&,
                            const QString & qName )
{
	const String tagname = qName.upper();

	if ( tagname == "OBJECT" ) {
		if ( pSection ) {
			pObject->setReport( pReport );
			pSection->insertObject( pObject );
			pObject = 0;

		} else {
			qWarning( "RTK:ReadXML:There is no section\n" );
		}
	} else if ( tagname == "STYLE" ) {
		pReport->insertStyle( pStyle );
		pStyle = 0;
	} else if ( tagname == "FORMULA" ) {
		pReport->insertFormula( pFormula );
		pFormula = 0;
	} else if ( tagname == "IMAGE" ) {
		pReport->insertImage( pImage );
		pImage = 0;
	} else if ( tagname == "SECTION" ) {
		if ( pSection ) {
			pSection->setReport( pReport );
			pReport->insertSection( pSection );
			//            pReport->applyStyle(pSection);
			pSection = 0;
		} else {
			qWarning( "RTK:ReadXML:There is no section\n" );
		}
	} else if ( tagname == "DEFINITION" ) {
		;
	} else if ( tagname == "INPUT" ) {
		if ( pInput ) {
			pReport->setInput( pInput );
			pInput = 0;
		}
	} else if ( tagname == "INPUTFIELD" ) {
		if ( pInput ) {
			pInput->insertInputField( pInputField );
		}
	} else if ( tagname == "REPORT" ) {
		;
	} else {
		qWarning( "RTK:ReadXML:unexpected end tag:%s\n", ( const char * ) tagname );
		return FALSE;
	}
	return TRUE;
}

bool XmlParser::error ( const QXmlParseException & exception )
{
	fprintf( stderr, "%d,%d:%s:%s:%s\n", exception.lineNumber(),
	         exception.columnNumber(), ( const char * ) exception.publicId(),
	         ( const char * ) exception.systemId(), ( const char * ) exception.message() );
	return TRUE;
}

bool XmlParser::warning ( const QXmlParseException & exception )
{
	return error( exception );
}

bool XmlParser::fatalError ( const QXmlParseException & exception )
{
	return error( exception );
}

// Report

/**
	\relates RTK::Report

	\brief Reads a Report definition from a file in xml format. 
	\param xmlname The name of the report definition file (.rtk)
	\param defaultinput	The name of the input to use
	
	Reads the report definition file named \a xmlname into this report. 
	If \a defaultinput is null (default), reads the input named 'default' 
	in the definition file, otherwise, reads the input definition named 
	\a defaultinput
	
	Returns true if the xml file contains a correct RTK definition. 
	Note that it returns true even if the input couldn't be found.
	
	\todo delete the previous report definition
 */	
bool Report::readXml( const String & xmlname, const String & defaultinput )
{
	setParent( 0 );
	setInput( 0 );
	XmlParser xmlparser( this );
	QFileInfo fi(xmlname);
	mCWD = fi.dirPath();
	return xmlparser.read( xmlname, defaultinput );
}

bool Report::readXmlStr( const String & xmldoc, const String & defaultinput )
{
	setParent( 0 );
	setInput( 0 );
	XmlParser xmlparser( this );
// 	QFileInfo fi(xmlname);
// 	mCWD = fi.dirPath();
	return xmlparser.readStr( xmldoc, defaultinput );
}

