/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkreport.cpp RTK report object
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


#include <exception>
#include <cctype>      // toupper, isdigit
#include <cmath>
#include <locale>

#include <qimage.h>

#include "rtkinput.h"
#include "rtkinputsql.h"
#include "rtkreport.h"

using namespace RTK;

/**
  \class RTK::Report rtkreport.h
  \brief The RTK::Report class holds a Report definition.
  
  A report definition contains several Section objects which
  in turn contain several Object objects.
 
  The fact that the Report itself is an Object, implies that it inherits all the
  properties of the Object class, and are considered as global properties. For instance,
  the BackColor property of a Report is considered the global BackColor of the report
  which can be overrided by the BackColor property of a Section or an Object.
 
  To create a report definition, call the Report constructor with the appropiate arguments,
  taking into account that all of them have default values. Then, read the definition
  from an xml file with readXml. The definition of the report has its Input implicit,
  but you can override it with setInput. Then, you print the report to a given Output.
  Here is an example of how to do this:
 
  \code
	Report aReport;
	if ( aReport.readXml ( filename ) ) {
		OutputOpenOffice o( ArgOutputFileName );
		r.print ( o );
	}
  \endcode
 
 
  You can create a Report definition on the fly by creating Sections
  and Objects. Once you have created a Section, insert it in the Report
  with \a insertSection.
 
*/

void Report::initLocale()
{
	mLocalRegConfig.setLocale(setlocale(LC_ALL, NULL));
	pLocalFormatter = new Formatter(mLocalRegConfig);
#if DEBUG_RTK > 0
	qDebug("RTK:Report:Reading the locale %s", setlocale(LC_ALL, NULL));
#endif	
}


/** Borra el objeto Input y la definición del informe (secciones y estilos) */
Report::~Report()
{
	if ( pInput )
		delete pInput;
	uint i;
	for ( i = 0; i < mSections.size(); i++ )
		delete mSections[ i ];
	for ( i = 0; i < mStyles.size(); i++ )
		delete mStyles[ i ];
	for ( i = 0; i < mFormulas.size(); i++ )
		delete mFormulas[ i ];
	for ( i = 0; i < mImages.size(); i++ )
		delete mImages[ i ];
}

/**
  @param input Pointer to the input to set
 
  Just one input at a time can be used by a Report
  */
void Report::setInput( Input *input )
{
	if ( pInput )
		delete pInput;
	pInput = input;
}

/**
  @param section Pointer to the section to insert. The report takes ownership of the section
  @return The number of sections in the report
  */
int Report::insertSection( Section *section )
{
	mSections.push_back( section );
	section->setParent( this );
	return mSections.size();
}

/**
  @return The number of sections in the report
  */
/*<<<<<REPORT_INSERTSECTION*/
int Report::insertSection(SectionType type, String groupname, Variant groupvalue, uint grouplevel, bool pagebefore, bool pageafter, bool resetnpage, bool supifblank, bool repeatheader)
{
	Section* section = new Section(
		type,groupname,groupvalue,grouplevel,pagebefore,pageafter,resetnpage,supifblank,repeatheader);
/*>>>>>REPORT_INSERTSECTION*/
	section->setParent( this );
/*<<<<<REPORT_INSERTSECTION_END*/
	mSections.push_back(section);
	return mSections.size();
}
/*>>>>>REPORT_INSERTSECTION_END*/

/**
  @param style Pointer to the style to insert. The report takes ownership of the style
  @return The number of styles in the report
  */
int Report::insertStyle( Style *style )
{
	eraseStyle(style->getName());
	mStyles.push_back( style );
	return mStyles.size();
}

bool Report::eraseStyle( const String &name )
{
	QValueList<Style *>::iterator it;
	for( it=mStyles.begin(); it != mStyles.end(); ++it ) {
		if ( (*it)->getName() == name ) {
			mStyles.erase(it);
			return true;
		}
	}
	return false;
}


/**
  @param All the propierties of the style 
  @return The number of styles in the report
*/ 
/*<<<<<REPORT_INSERTSTYLE*/
int Report::insertStyle(String name, String marginleft, String marginright, String margintop, String marginbottom, bool visible, bool supressed, String fontfamily, int fontsize, int fontweight, bool fontitalic, String mask, String format, AlignmentType halignment, AlignmentType valignment, int maxlines, int minfontsize, AdjustmentType adjustment, Color textcolor, Color backcolor, Color bordercolor, int borderwidth, BorderStyle borderstyle, String backgroundimage)
{
	Style* style = new Style(
		name,marginleft,marginright,margintop,marginbottom,visible,supressed,fontfamily,fontsize,fontweight,fontitalic,mask,format,halignment,valignment,maxlines,minfontsize,adjustment,textcolor,backcolor,bordercolor,borderwidth,borderstyle,backgroundimage);
/*>>>>>REPORT_INSERTSTYLE*/
	eraseStyle(name);
/*<<<<<REPORT_INSERTSTYLE_END*/
	mStyles.push_back(style);
	return mStyles.size();
}
/*>>>>>REPORT_INSERTSTYLE_END*/


/**
  @param image Pointer to the image to insert. The report takes ownership of the image
  @return The number of images in the report
  */
int Report::insertImage( Image *image )
{
	mImages.push_back( image );
	return mImages.size();
}

/*<<<<<REPORT_INSERTIMAGE*/
int Report::insertImage(String name, String url, String mimetype, String imagestyle)
{
	Image* image = new Image(
		name,url,mimetype,imagestyle);
/*>>>>>REPORT_INSERTIMAGE*/
	eraseImage(name);
/*<<<<<REPORT_INSERTIMAGE_END*/
	mImages.push_back(image);
	return mImages.size();
}
/*>>>>>REPORT_INSERTIMAGE_END*/

/**
	Returns a RTK::Image object by its name
	Call the getImage method to get the underlying QImage object.
 */

Image *Report::findImage( const String &name ) const
{
	QValueList<Image *>::const_iterator it;
	for( it=mImages.begin(); it != mImages.end(); ++it ) {
		if ( (*it)->getName() == name ) {
			return *it;
		}
	}
	return 0;
}

bool Report::eraseImage( const String &name )
{
	QValueList<Image *>::iterator it;
	for( it=mImages.begin(); it != mImages.end(); ++it ) {
		if ( (*it)->getName() == name ) {
			delete (*it);
			mImages.erase(it);
			return true;
		}
	}
	return false;
}


/**
  @param formula Pointer to the formula to insert. The report takes ownership of the formula
  @return The number of formulae in the report
  */
int Report::insertFormula( Formula *formula )
{
	mFormulas.push_back( formula );
	return mFormulas.size();
}

/**
  @return The number of formulas in the report
  */ 
/*<<<<<REPORT_INSERTFORMULA*/
int Report::insertFormula(String name, String code)
{
	Formula* formula = new Formula(
		name,code);
/*>>>>>REPORT_INSERTFORMULA*/
/*<<<<<REPORT_INSERTFORMULA_END*/
	mFormulas.push_back(formula);
	return mFormulas.size();
}
/*>>>>>REPORT_INSERTFORMULA_END*/



/**
	\relates RTK::Report
	
  	\brief Gets a section by its name
  	\param name The name of the section to find
  	\return A pointer to the section or 0 if not found
  */
Section *Report::getSection( const String &name ) const
{
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( mSections[ i ] ->getName() == name )
			return mSections[ i ];
	}
	return 0;
}

/**
  @param nsection The index of the section to find
  @return A pointer to the section or 0 if not found
  */
Section *Report::getSection( uint nsection ) const
{
	if ( nsection < mSections.size() )
		return mSections[ nsection ];
	else
		return 0;
}

/**
  @param name The name of the style to find
  @return A pointer to the style or 0 if not found
  */
Style *Report::getStyle( const String &name ) const
{
	for ( uint i = 0; i < mStyles.size(); i++ ) {
		if ( mStyles[ i ] ->getName() == name )
			return mStyles[ i ];
	}
	return 0;
}

/**
  @param nstyle The position of the style to get
  @return A pointer to the style or 0 if not found
  */
Style *Report::getStyle( uint nstyle ) const
{
	if ( nstyle < mStyles.size() )
		return mStyles[ nstyle ];
	else
		return 0;
}


void Report::calcConstValues()
{
#if DEBUG_RTK > 1
	qDebug( "RTK:Report:calcConstValues" );
#endif
	Variant vr = calcConstValue( getValue() );
	if( vr.isValid() ) {
		setValue( vr );
		setConst(true);
	}
	for ( uint ns = 0; ns < mSections.size(); ns++ ) {
		Section *sect = mSections[ns];
		Variant vs( calcConstValue(sect->getValue() ) );
		if( vs.isValid() ) {
			sect->setValue( vs );
			sect->setConst(true);
#if DEBUG_RTK > 2
			qDebug( "RTK:Report:calcConstValues:Group value of section %d, level %d, %s",
		        ns, sect->getGroupLevel(), ( const char * ) vs.toString() );
#endif
		}
		for ( uint no = 0; no < sect->getNObjects(); no++ ) {
			Object *object = sect->getObject( no );
			Variant vo( calcConstValue( object->getValue()) );
			if( vo.isValid() ) {
				object->setValue( vo );
				object->setConst(true);
#if DEBUG_RTK > 3
				qDebug( "RTK:Report:calcConstValues: Object %d value of section %d, level %d, %s",
			        no, ns, sect->getGroupLevel(), ( const char * ) vo.toString());
#endif
			}
		}
	}
}


/*
	TODO: This function is called for every record, but it should be called just once.
*/

Variant Report::calcConstValue( const Variant &value )
{
	if ( mFinished )
		return Variant(); // Para que los ultimos nextvalues se copien a values
	if ( value.type() == Variant::tString ) {
		QStringList tokens;
		tokenize( tokens, value.toString(), " \t\n" );
		if ( tokens.size() == 1 ) {
			if ( tokens[ 0 ].lower() == "reportdate()" ) {
				return Variant( mReportDate );
			} else if ( tokens[ 0 ].lower() == "reporttitle()" ) {
				return Variant( mTitle );
			} else if ( tokens[ 0 ].lower() == "recordcount()" ) {
				return Variant( );
			} else if ( tokens[ 0 ].lower() == "recordnumber()" ) {
				return Variant(  );
			} else if ( tokens[ 0 ].lower() == "pagecount()" ) {
				return Variant(  );
			} else if ( tokens[ 0 ].lower() == "pagenumber()" ) {
				return Variant(  );
			} else if ( tokens[ 0 ].lower().startsWith( "input." ) ) {
				return Variant(  );
			} else {
				if ( tokens[ 0 ].at( 0 ) >= '0' && tokens[ 0 ].at( 0 ) <= '9' ) {
					return Variant( tokens[ 0 ].toInt() );
				}
			}
		}
	}
	// Any other type of the value is considered constant
	return value;
}


void Report::calcNonConstValues( Input &in )
{
#if DEBUG_RTK > 1
	qDebug( "RTK:Report:calcNonConstValues" );
#endif
	if( !isConst() )
		setRealValue( calcNonConstValue( getValue(), in ) );
	for ( uint ns = 0; ns < mSections.size(); ns++ ) {
		Section *sect = mSections[ns];
		if( !sect->isConst() )
			sect->setRealValue( calcNonConstValue( sect->getValue(), in ) );
		sect->setRealGroupValue( calcNonConstValue( sect->getGroupValue(), in ) );
#if DEBUG_RTK > 2
		qDebug( "RTK:Report:calcNonConstValues:Group value of section %d, level %d, %s",
		        ns, sect->getGroupLevel(), ( const char * ) sect->getRealGroupValue().toString() );
#endif
		for ( uint no = 0; no < sect->getNObjects(); no++ ) {
			Object *object = sect->getObject( no );
			if( ! object->isConst() ) {
				object->setRealValue( calcNonConstValue( object->getValue(), in ) );
#if DEBUG_RTK > 3
				qDebug( "RTK:Report:calcNonConstValues: Object %d value of section %d, level %d, %s",
			        no, ns, sect->getGroupLevel(),
			        ( const char * ) object->getValue().toString());
#endif
			}
		}
	}
}


Variant Report::calcNonConstValue( const Variant &value, Input &in )
{
	if ( mFinished )
		return Variant(); // Para que los ultimos nextvalues se copien a values
	if ( value.type() == Variant::tString ) {
		QStringList tokens;
		tokenize( tokens, value.toString(), " \t\n" );
		if ( tokens.size() == 1 ) {
			if ( tokens[ 0 ].lower() == "reportdate()" ) {
				return Variant( mReportDate );
			} else if ( tokens[ 0 ].lower() == "reporttitle()" ) {
				return Variant( mTitle );
			} else if ( tokens[ 0 ].lower() == "recordcount()" ) {
				return Variant( &mRecordCount );
			} else if ( tokens[ 0 ].lower() == "recordnumber()" ) {
				return Variant( &mRecordNumber );
			} else if ( tokens[ 0 ].lower() == "pagecount()" ) {
				return Variant( &mPageCount );
			} else if ( tokens[ 0 ].lower() == "pagenumber()" ) {
				return Variant( mPageNumber );
			} else if ( tokens[ 0 ].lower().startsWith( "input." ) ) {
				String inputfield = tokens[ 0 ].mid( 6 );
				return in.getValue( inputfield );
			} else if ( tokens[ 0 ].lower().startsWith( "cfunction" ) ) {
				Variant v = tokens[ 1 ];
				// Ojo v.setCFunctionType();
				return v;
			} else {
				if ( tokens[ 0 ].at( 0 ) >= '0' && tokens[ 0 ].at( 0 ) <= '9' ) {
					return Variant( tokens[ 0 ].toInt() );
				}
			}
		}
	}
	return value;
}


Measure Report::calcSizeYSections( SectionType type ) const
{
	Measure h = 0.0;
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( mSections[ i ] ->getType() == type )
			h += mSections[ i ] ->getFixedSizeY();
	}
	return h;
}

// Transform all the report's measures to match the output's measures
// The right and left margins make the report scale, (encuadernacion)
//   but the top and bottom margins crop the report
void Report::fixReportMeasures( const Output &out )
{
	uint ns;
	fixMeasures( out.getUnits(),
	             out.getSizeX(),  //-out.getMarginLeft()-out.getMarginRight(),
	             out.getSizeY(),  //-out.getMarginTop()-out.getMarginBottom(),
	             getUnits(),  // do not scale
	             out.getSizeX(),  //-out.getMarginLeft()-out.getMarginRight(),
	             out.getSizeY() ); //-out.getMarginTop()-out.getMarginBottom());
	for ( ns = 0; ns < mSections.size(); ns++ ) {
		Section *sect = mSections[ns];
        if( sect->getMeasure(getSizeX()) == 0 ) {
        	setSizeX(getParent()->getSizeX());
        }
		sect->fixMeasures(
		    out.getUnits(),
		    out.getSizeX() - out.getMarginLeft() - out.getMarginRight(),
		    out.getSizeY(),  //-out.getMarginTop()-out.getMarginBottom(),
		    getUnits(), getFixedSizeX(), getFixedSizeY() );
		sect->fixObjectsMeasures(
		    out.getUnits(),
		    out.getSizeX() - out.getMarginLeft() - out.getMarginRight(),
		    out.getSizeY(),  //-out.getMarginTop()-out.getMarginBottom(),
		    getUnits(), getFixedSizeX(), getFixedSizeY() );
	}
	return ;
}

void Report::calcAggregateValues( uint level )
{
	for ( uint i = 0; i < mSections.size(); i++ )
		mSections[ i ] ->calcAggregateValues( level );
}

Variant Report::execCFunction( const Object &obj, const String &code )
{
	return mCFunction( *this, obj, code );
}


Variant Report::mCFunction( const Report &r, const Object &, const String &code )
{
#if DEBUG_RTK > 3
	qDebug( "RTK:Report:mCFunction(%s)", (const char *)code );
#endif	
	if ( code == "alternate_color_white_grey" ) {
		int rc = r.getRecordNumber();
		if ( rc % 2 == 1 )
			return Qt::white;
		else
			return Qt::gray;
	}
	return Variant();
}



int Report::printPageHeaders( Output &out )
{
	int ret = 0;
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( isPageHeader( i ) )
			ret = printSection( out, *mSections[ i ] );
	}
	return ret;
}

/**
	Prints all the visible footer sections.
	The position is calculated from the bottom of the page, adding the sizeys of all the page footers
 */
	
int Report::printPageFooters( Output &out )
{
	int ret = 0;
	Measure totalsizey = 0.0;
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( isPageFooter( i ) ) {
			if( mSections[i]->isVisible() )
				totalsizey += mSections[ i ] ->getFixedSizeY();
		}
	}
	out.setPosY( out.getSizeY() - out.getMarginBottom() - totalsizey );
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( isPageFooter( i ) ) {
				ret = printSection( out, *mSections[ i ] );
		}
	}
	return ret;
}


bool Report::changedGroupValue( uint level )
{
	for ( uint i = 0; i < mSections.size(); i++ ) {
		if ( mSections[ i ] ->getGroupLevel() == level ) {
			return mSections[ i ] ->groupChanged();
		}
	}
	return false;
}

int Report::readNext( Input &in )
{
	if ( !mStarted ) {
		if ( !in.init() )
			return false;
		mStarted = true;
		mFinished = false;
		mPageNumber = mPageCount = mRecordNumber = mRecordCount = 1;
		mReportDate = Date::currentDate();
		mGroupLevels = 0;
		for ( uint ns = 0; ns < mSections.size(); ns++ ) {
			Section *sect = mSections[ns];
			if ( sect->getGroupLevel() > mGroupLevels )  // TODO
				mGroupLevels = sect->getGroupLevel();
		}
		resetAggregateValues( 0 );
		calcConstValues();
		if ( in.next() ) {
			calcNonConstValues(in);
		}
	}
#if DEBUG_RTK > 0
	qDebug("Report::readNext:RecordNumber=%d", mRecordNumber.toInt());
#endif		
	if ( in.next() ) {
		calcNonConstValues(in);
		return true;
	} else {
		if ( !mFinished ) {
			mFinished = true;
			calcNonConstValues(in);
			return true;
		} else {
			return false;
		}
	}
}




/**
    \relates RTK::Report
	\brief Prints this report to the given output object using the given input object
	
	Before printing the report, adapt the report measures to the output ones.
	
	\todo Print the report-header and report-footer 
	\todo Define the return value
 */
int Report::print( Input &in, Output &out )
{
#if DEBUG_RTK > 0
	qDebug( "RTK:Report:print start" );
#endif
	int ret = 0;
	if ( readNext( in ) ) {
		fixReportMeasures( out );
		mFootersHeight = calcSizeYSections( SectionPageFooter );
		if( (ret = out.startReport( *this )) >= 0 ) {
			out.startPage();
			printPageHeaders( out );
			printGroup( in, out, 1 );
			printPageFooters( out );
			out.endPage();
			out.endReport( *this );
			ret = 1;
		}
	}
#if DEBUG_RTK > 0
	qDebug( "RTK:Report:print end:(%d)", ret );
#endif
	return ret;
}

/**
	\overload
	
    \relates RTK::Report
	Prints the report to the given Output object using the internal Input read or set previously.
 */
int Report::print( Output &out )
{
	if( pInput ) 
		return print( *pInput, out );
	else {
		qDebug("RTK:print:no input defined");
		return 0;
	}
}


int Report::printGroup( Input &in, Output &out, uint level )
{
#if DEBUG_RTK > 1
	qDebug( "RTK:Report:printGroup(level=%d) start", level );
#endif
	// Print group header section(s)
	int ret = 0;
	bool existslevel = false;
	bool changedgroup = false;
	uint i;
	resetRecordCount( level );
	do {
		for ( i = 0; i < mSections.size(); i++ ) {
			if ( isGroupHeader( i ) && mSections[ i ] ->getGroupLevel() == level ) {
				existslevel = true;
#if DEBUG_RTK > 1
				qDebug( "RTK:Report:printGroup:New group level=%d: Group value=%s", mSections[ i ] ->getGroupLevel(), ( const char * ) mSections[ i ] ->getRealGroupValue().toString() );
#endif
				ret += printSection( out, *mSections[ i ] );
			}
		}
		if ( existslevel ) {
			// Print nested group
			ret += printGroup( in, out, level + 1 );
			// Print group footer section(s)
			for ( i = 0; i < mSections.size(); i++ ) {
				if ( isGroupFooter( i ) && mSections[ i ] ->getGroupLevel() == level ) {
					ret += printSection( out, *mSections[ i ] );
				}
			}
			resetAggregateValues( level );
			changedgroup = false;
			if ( readNext( in ) ) {
				mRecordNumber = mRecordNumber.toInt() + 1;
				mRecordCount = mRecordCount.toInt() + 1;
				incRecordCount( level );
			}
		} else {
			// If the level doesn't exist, there are no more groups
			// Print details section(s)
			while ( !mFinished ) {
				bool firstdetailssection = true;
				for ( i = 0; i < mSections.size(); i++ ) {
					if ( isDetails( i ) ) {
						if ( firstdetailssection == true ) {
							// Calcular los valores agregados de todas las secciones solo en la
							// primera seccion de los detalles
							calcAggregateValues( mGroupLevels );
							firstdetailssection = false;
						}
						ret += printSection( out, *mSections[ i ] );
					}
				}
				if ( changedGroupValue( level - 1 ) ) {
					changedgroup = true;
					break; // No leer de la entrada hasta que se imprima el pie
				}
				if ( readNext( in ) ) {
					mRecordNumber = mRecordNumber.toInt() + 1;
					mRecordCount = mRecordCount.toInt() + 1;
					incRecordCount( level );
				}
			}
		}
	} while ( !mFinished && !changedgroup /*&& !changedGroupValue(level-1)*/ );
#if DEBUG_RTK > 1
	qDebug( "RTK:printGroup(level=%d) end", level );
#endif
	return ret;
}

int Report::printPageFooterIfNeeded( Output &out, Section &section )
{
	// Ver si cabe la sección
	int ret = 0;
	if ( !isPageFooter( section ) && !out.sectionFits( section, mFootersHeight ) ) {
		Q_ASSERT( !isPageHeader( section ) ); // Imposible
		ret += printPageFooters( out );
		out.endPage();
		mPageNumber = mPageNumber.toInt() + 1;
		mPageCount = mPageCount.toInt() + 1;
		out.startPage();
		ret += printPageHeaders( out );
	}
	return ret;
}

int Report::printSection( Output &out, Section &section )
{
	// Imprimir los objetos
	if ( !section.isVisible() )
		return 0;
	printPageFooterIfNeeded( out, section );
	out.startSection( section );
	printObject( out, section, section ); // Imprimir la sección
	uint i;
	for ( i = 0; i < section.mObjects.size(); i++ ) {
		printObject( out, section, *section.getObject( i ) );
	}
	out.endSection( section );
	return i;
}

int Report::printObject( Output &out, const Section &section,
                         const Object &object )
{
	if ( !object.isVisible() )
		return 0;
	out.startObject( section, object );
	out.printObject( *this, section, object );
	out.endObject( section, object );
	return 1;
}


int Report::resetAggregateValues( uint level )
{
	for ( uint ns = 0; ns < mSections.size(); ns++ ) {
		for ( uint no = 0; no < mSections[ns]->getNObjects(); no++ ) {
			mSections[ns]->getObject(no)->resetAggregateValues( mGroupLevels, level );
		}
	}
	return mGroupLevels;
}


int Report::incRecordCount( uint level )
{
	int ret = 0;
	for ( uint ns = 0; ns < mSections.size(); ns++ ) {
		if( mSections[ns]->getGroupLevel() <= level )
			ret = ++mSections[ns]->mRecordCount;
	}
	return ret;
}

void Report::resetRecordCount( uint level )
{
	for ( uint ns = 0; ns < mSections.size(); ns++ ) {
		if( mSections[ns]->getGroupLevel() >= level )
			mSections[ns]->mRecordCount = 0;
	}
}


bool Report::applyStyle( Object *object )
{
	if ( object ) {
		const Style * styledef = getStyle( object->getStyle() );
		if ( !styledef ) {
			Object * parent = object->getParent();
			while ( parent ) {
				styledef = getStyle( parent->getStyle() );
				if ( styledef )
					break;
				else
					parent = parent->getParent();
			}
		}
		if ( styledef ) {
			// FontFamily
			if ( object->getFontFamily().length() == 0 )
				object->setFontFamily( styledef->getFontFamily() );
			// FontSize
			if ( object->getFontSize() == 0 )
				object->setFontSize( styledef->getFontSize() );
			// FontWeight
			if ( object->getFontWeight() == 0 )
				object->setFontWeight( styledef->getFontWeight() );
			// FontItalic
			if ( object->isFontItalic() == false )
				object->setFontItalic( styledef->isFontItalic() );
			// Format
			if ( object->getFormat().length() == 0 )
				object->setFormat( styledef->getFormat() );
			// HAlignment
			if ( object->getHAlignment() == AlignAuto )
				object->setHAlignment( styledef->getHAlignment() );
			// VAlignment
			if ( object->getVAlignment() == AlignAuto )
				object->setVAlignment( styledef->getVAlignment() );
			// MaxLines
			if ( object->getMaxLines() == 0 )
				object->setMaxLines( styledef->getMaxLines() );
			// MinFontSize
			if ( object->getMinFontSize() == 0 )
				object->setMinFontSize( styledef->getMinFontSize() );
			// Adjustment
			if ( object->getAdjustment() == AdjustTrim )
				object->setAdjustment( styledef->getAdjustment() );
			// TextColor
			if ( object->getTextColor() == Color(0,0,0) )
				object->setTextColor( styledef->getTextColor() );
			// TextColor
			if ( object->getBackColor() == Color(0,0,0) )
				object->setBackColor( styledef->getBackColor() );
			// BorderColor
			if ( object->getBorderColor() == Color(0,0,0) )
				object->setBorderColor( styledef->getBorderColor() );
			// BorderWidth
			if ( object->getBorderWidth() == 0 )
				object->setBorderWidth( styledef->getBorderWidth() );
			// BorderStyle
			if ( object->getBorderStyle() == 0 )
				object->setBorderStyle( styledef->getBorderStyle() );
		} else {
			qDebug( "RTK:Report::applyStyle:Style not found %s", (const char *)object->getStyle() );
		}
		return true;
	}
	return false;
}



#ifndef NDEBUG

int Report::debug_print() const
{
	int ret = 0;
	unsigned int it;
	printf( "Report='%s'\n", ( const char * ) mName );
	//  TODO
	//    for( it=0; it<mStyles.size(); it++ )
	//        ret += mStyles[it].debug_print();
	for ( it = 0; it < mSections.size(); it++ )
		ret += mSections[ it ] ->debug_print();
	printf( "\n" );
	return ret;
}

#endif

QMap<String, Report::InputCreatorFuncPtr> Report::mRegisteredInputs;	
/** 
	Adds an Input plugin to the report engine
 */
int Report::registerInput(const String &name, InputCreatorFuncPtr creator)
{
	mRegisteredInputs.insert(name, creator, true);
	return mRegisteredInputs.size();
}


Input *Report::createRegisteredInput(const String &name, const String &driver)
{
	InputCreatorFuncPtr creator = mRegisteredInputs[driver];
	if( creator )
		return creator(name, driver);
	else
		return 0;
}



void Report::setStylesPath(const QString &path)
{
	if( path.length() != 0 ) {
		if( mStylesPath.length() != 0 )
			mStylesPath += ":";
		mStylesPath += path;
	}
}

void Report::setImagesPath(const QString &path)
{
	if( path.length() != 0 ) {
		if( mImagesPath.length() != 0 )
			mImagesPath += ":";
		mImagesPath += path;
	}
}
