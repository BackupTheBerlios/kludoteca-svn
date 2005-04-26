/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkformatter.cpp String and number formatting with locale
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "rtkformatter.h"

using namespace RTK;

#define MAX_FORMAT_BUF 256
#define LC_DECIMAL_POINT ( (valuetype==Variant::tMoney)?mRegConfig.getCurrencyDecimalPoint():mRegConfig.getDecimalPoint() )
#define LC_THOUSANDS_SEP ( (valuetype==Variant::tMoney)?mRegConfig.getCurrencyThousandsSep():mRegConfig.getThousandsSep() )
#define LC_NEGATIVE_SIGN ( mRegConfig.getNegativeSign().at(0).latin1() )
#define LC_POSITIVE_SIGN ( mRegConfig.getPositiveSign().at(0).latin1() )

#define LITERAL_MASK_CHAR '\\'


QString &stringReplace(QString &buffer,
  const QString &search, const QString &repl)
{
  int searchlen = search.length();
  if( searchlen == 0 )
  	return buffer;
  int repllen = repl.length();
  int match = buffer.find(search);
  while( match != -1 ) {
    buffer.remove(match, searchlen);
    buffer.insert(match, repl);
    match = buffer.find(search, match + repllen);
  }
  return buffer;
}



// Default constructor
Formatter::Formatter( const RegConfig &regcfg, char blank_char )
		: mRegConfig(regcfg), mBlankChar( blank_char )
{}

// set blank char
void Formatter::setBlankChar( char blank_char )
{
	mBlankChar = blank_char;
}

// get blank char
char Formatter::getBlankChar() const
{
	return mBlankChar;
}

/* Formats a text */
String Formatter::format( const String &text, const String &format, const String &mask ) const
{
	Q_UNUSED( mask );
	if ( format.find( '<' ) != -1 )
		return text.upper();
	if ( format.find( '>' ) != -1 )
		return text.lower();
	else
		return text;
}



String Formatter::format( int val, const String &format, const String &amask ) const
{
	if ( val == 0 && ( format.find( 'B' ) != -1 ) )
		return String();
	else
		return mask( val, Variant::tInt, amask );
}

String Formatter::format( double val, const String &format, const String &amask ) const
{
	if ( val == 0 && ( format.find( 'B' ) != -1 ) )
		return String();
	else {
		if ( format.find( '$' ) != -1 ) {
			return formatLocaleCurrency( mask( val, Variant::tMoney, 
				amask.length()==0?mRegConfig.getCurrencyMask():amask), val );
		} else {
			return mask( val, Variant::tDouble, amask );
		}
	}
}

String Formatter::format( const Money &val, const String &format, const String &amask ) const
{
	if ( val == 0L && ( format.find( 'B' ) != -1 ) )
		return String();
	else if( format.find( "!$" ) != -1 )
		return mask( val.toDouble(), Variant::tMoney, 
			amask.length()==0?mRegConfig.getCurrencyMask():amask);
	else
		return formatLocaleCurrency( mask( val.toDouble(), Variant::tMoney, 
			amask.length()==0?mRegConfig.getCurrencyMask():amask ), val.toDouble() );
}



String Formatter::format( const Variant &avalue, const String &aformat,
                            const String &mask, Variant::Type valuetype ) const
{
	if ( valuetype == Variant::Invalid )
		valuetype = avalue.type();
	switch ( valuetype ) {
	case Variant::tDate:
		return format( avalue.toDate(), aformat, mask );
	case Variant::tTime:
		return format( avalue.toTime(), aformat, mask );
	case Variant::tDateTime:
		return format( avalue.toDateTime(), aformat, mask );
	case Variant::tBool:
		return ( avalue.toBool() ? "true" : "false" );
	case Variant::tInt:
		return format( avalue.toInt(), aformat, mask );
	case Variant::tDouble:
		return format( avalue.toDouble(), aformat, mask );
	case Variant::tMoney:
		return format( avalue.toMoney(), aformat, mask );
	default:  /*  Formatter::string */
		return format( avalue.toString(), aformat, mask );
	}
}

/*
  Formatea un QDate a una cadena según una máscara o un formato.
  Si es una máscara, es del tipo dd/mm/yy
  Si es un formato, es del tipo estandard de c, %d%M%Y etc.
*/
String Formatter::format( const QDate &adate, const String &format, const String &amask ) const
{
	if ( !adate.isValid() )
		return "";
	else if ( !format.isEmpty() ) {
		char buffer[ MAX_FORMAT_BUF ];
		struct tm stm;
		stm.tm_sec = 0;
		stm.tm_min = 0;
		stm.tm_hour = 0;
		stm.tm_mday = adate.day();
		stm.tm_mon = adate.month() - 1;
		stm.tm_year = adate.year() - 1900;
		mktime( &stm ); // fix day of week, daylight saving, etc.
		strftime( buffer, MAX_FORMAT_BUF, format, &stm );
		return String( buffer );
	} else {
		return mask( QDateTime( adate ), Variant::tDate, amask );
	}
}

String Formatter::format( const QTime &atime, const String &format, const String &amask ) const
{
	if ( !atime.isValid() )
		return "";
	else if ( !format.isEmpty() ) {
		char buffer[ MAX_FORMAT_BUF ];
		struct tm stm;
		stm.tm_sec = atime.second();
		stm.tm_min = atime.minute();
		stm.tm_hour = atime.hour();
		stm.tm_mday = 0;
		stm.tm_mon = 0;
		stm.tm_year = 0;
		mktime( &stm ); // fix day of week, daylight saving, etc.
		strftime( buffer, MAX_FORMAT_BUF, format, &stm );
		return String( buffer );
	} else {
		return mask( QDateTime( QDate(), atime ), Variant::tTime, amask );
	}
}


String Formatter::format( const QDateTime &adatetime, const String &format, const String &amask ) const
{
	if ( !adatetime.isValid() )
		return "";
	else if ( !format.isEmpty() ) {
		char buffer[ MAX_FORMAT_BUF ];
		struct tm stm;
		stm.tm_sec = adatetime.time().second();
		stm.tm_min = adatetime.time().minute();
		stm.tm_hour = adatetime.time().hour();
		stm.tm_mday = adatetime.date().day();
		stm.tm_mon = adatetime.date().month() - 1;
		stm.tm_year = adatetime.date().year() - 1900;
		mktime( &stm ); // fix day of week, daylight saving, etc.
		strftime( buffer, MAX_FORMAT_BUF, format, &stm );
		return String( buffer );
	} else {
		return mask( adatetime, Variant::tDateTime, amask );
	}
}



String Formatter::mask( const char *text, Variant::Type valuetype, const char *mask ) const
{
	return maskalfa_mask( text, valuetype, mask );
}

String Formatter::mask( int val, Variant::Type valuetype, const char *mask ) const
{
	char text[ 32 ];

	sprintf( text, "%d", val );
	return masknum_mask( text, valuetype, mask );
}

String Formatter::mask( double val, Variant::Type valuetype, const char *mask ) const
{
	char buffer[ 128 ], *pbuffer = buffer;

	char *locale_save = setlocale( LC_NUMERIC, "C" );
	sprintf( buffer, "%127f", val );
	setlocale( LC_NUMERIC, locale_save );
	/* if the locale is not set, we don't know which decimal point sprintf will use */
	while ( *pbuffer ) {
		if ( *pbuffer == '.' ) {
			*pbuffer = LC_DECIMAL_POINT;
		}
		if ( *pbuffer == '-' ) {
			*pbuffer = LC_NEGATIVE_SIGN;
		}
		pbuffer++;
	}
	return masknum_mask( buffer, valuetype, mask );
}




String Formatter::mask( const QDateTime &adate, Variant::Type valuetype, const char *mask ) const
{
	const char * pmask;
	char buffer[ MAX_FORMAT_BUF ] = "", itemformat[] = "%0_d";
	int l, days, months, years, hours, minutes, seconds;
	struct tm lt;

	if ( !adate.isValid() )
		return "";
	else {
		lt.tm_sec = adate.time().second();
		lt.tm_min = adate.time().minute();
		lt.tm_hour = adate.time().hour();
		lt.tm_mday = adate.date().day();
		lt.tm_mon = adate.date().month() - 1;
		lt.tm_year = adate.date().year() - 1900;
	}

	int module = 1;

	days = months = years = hours = minutes = seconds = 0;
	if ( mask == NULL || !( *mask ) ) {
		switch ( valuetype ) {
		case Variant::tDate:
			pmask = mRegConfig.getDateMask();
			break;
		case Variant::tTime:
			pmask = mRegConfig.getTimeMask();
			break;
		default:  /* Variant::tDateTime */
			pmask = mRegConfig.getDateTimeMask();
		}
	} else
		pmask = mask;
	pmask--;
	do {
		pmask++;
		switch ( *pmask ) {
		case 'd':
		case 'D':
			days++;
			break;
		case 'm':
			months++;
			break;
		case 'y':
		case 'Y':
			years++;
			module *= 10;
			break;
		case 'h':
		case 'H':
			hours++;
			break;
		case 'M':
			minutes++;
			break;
		case 's':
		case 'S':
			seconds++;
			break;
		default:
			if ( days ) {
				itemformat[ 2 ] = ( char ) days + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_mday );
				days = 0;
			}
			if ( months ) {
				itemformat[ 2 ] = ( char ) months + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_mon + 1 );
				months = 0;
			}
			if ( years ) {
				itemformat[ 2 ] = ( char ) years + '0';
				sprintf( buffer + strlen( buffer ), itemformat, ( lt.tm_year + 1900 ) % module );
				years = 0;
			}
			if ( hours ) {
				itemformat[ 2 ] = ( char ) hours + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_hour );
				hours = 0;
			}
			if ( minutes ) {
				itemformat[ 2 ] = ( char ) minutes + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_min );
				minutes = 0;
			}
			if ( seconds ) {
				itemformat[ 2 ] = ( char ) seconds + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_sec );
				seconds = 0;
			}
			l = strlen( buffer );
			buffer[ l ] = *pmask;
			buffer[ l + 1 ] = '\0';
		}
	} while ( *pmask );
	return String( buffer );
}


String Formatter::mask( const Variant &avalue, Variant::Type valuetype, const char *amask ) const
{
	switch ( valuetype ) {
	case Variant::tDate:
	case Variant::tTime:
	case Variant::tDateTime:
		return mask( avalue.toDateTime(), valuetype, amask );
	case Variant::tInt:
		return mask( avalue.toInt(), valuetype, amask );
	case Variant::tDouble:
		return mask( avalue.toDouble(), valuetype, amask );
	case Variant::tMoney:
		return mask( avalue.toMoney(), valuetype, amask );
	default:  /*  Formatter::string */
		return mask( ( const char * ) avalue.toString(), valuetype, amask );
	}
}



int Formatter::unMaskInt( const String &text, const String &mask ) const
{
	Q_UNUSED( mask );
	return text.toInt();
}

int Formatter::unFormatInt( const String &text, const String &format ) const
{
	Q_UNUSED( format );
	return text.toInt();
}


double Formatter::unMaskDouble( const String &text, const String & /*mask*/ ) const
{
	char buffer[ 128 ], *pbuffer = buffer;
	const char *ptext = text;

	Variant::Type valuetype = Variant::tDouble; // Para las macros LC_
	/* Remove invalid characters */
	while ( *ptext ) {
		if ( isdigit( *ptext ) )
			* pbuffer++ = *ptext;
		else if ( *ptext == LC_NEGATIVE_SIGN )
			* pbuffer++ = '-';
		else if ( *ptext == LC_DECIMAL_POINT )
			* pbuffer++ = '.';
		ptext++;
	}
	*pbuffer = '\0';
	return atof( buffer );
}

double Formatter::unFormatDouble( const String &text, const String &format ) const
{
	return unMaskDouble( text, format );
}

Money Formatter::unMaskMoney( const String &text, const String & /*mask*/ ) const
{
	char buffer[ 128 ], *pbuffer = buffer;
	const char *ptext = text;

	Variant::Type valuetype = Variant::tMoney; // Para las macros LC_
	/* Remove invalid characters */
	while ( *ptext ) {
		if ( isdigit( *ptext ) )
			* pbuffer++ = *ptext;
		else if ( *ptext == LC_NEGATIVE_SIGN )
			* pbuffer++ = '-';
		else if ( *ptext == LC_DECIMAL_POINT )
			* pbuffer++ = '.';
		ptext++;
	}
	*pbuffer = '\0';
	return atof( buffer );
}

Money Formatter::unFormatMoney( const String &text, const String &format ) const
{
	return unMaskMoney( text, format );
}



QDateTime Formatter::unMaskDateTime( const String &text, const String &mask, Variant::Type valuetype ) const
{
	const char * pmask, *ptext;
	struct tm lt = {
		               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	               };
	pmask = ( const char * ) mask;
	if ( mask == NULL || !( *mask ) ) {
		switch ( valuetype ) {
		case Variant::tDate:
			pmask = mRegConfig.getDateMask();
			break;
		case Variant::tTime:
			pmask = mRegConfig.getTimeMask();
			break;
		default:  /* Variant::tDateTime */
			pmask = mRegConfig.getDateTimeMask();
		}
	}
	ptext = ( const char * ) text;
	while ( *pmask && *ptext ) {
		switch ( *pmask ) {
		case 'd':
		case 'D':
			lt.tm_mday = lt.tm_mday * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 'm':
			lt.tm_mon = lt.tm_mon * 10 + ( int ) ( *ptext - '0' );
			break;
		case 'y':
		case 'Y':
			lt.tm_year = lt.tm_year * 10 + ( int ) ( *ptext - '0' );
			break;
		case 'h':
		case 'H':
			lt.tm_hour = lt.tm_hour * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 'M':
			lt.tm_min = lt.tm_min * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 's':
		case 'S':
			lt.tm_sec = lt.tm_sec * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		}
		pmask++;
		ptext++;
	}
	if ( lt.tm_mon > 0 )
		lt.tm_mon--;
	if ( lt.tm_year == 0 )  /* Just time, nor date */
		lt.tm_year = 70;
	else if ( lt.tm_year < 30 )
		lt.tm_year += 100;
	else if ( lt.tm_year > 100 )
		lt.tm_year -= 1900;
	return QDateTime( QDate( lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday ),
	                  QTime( lt.tm_hour, lt.tm_min, lt.tm_sec ) );
}

QDateTime Formatter::unFormatDateTime( const String &text, const String &format, Variant::Type /*valuetype*/ ) const
{
	struct tm tm = {
		               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	               };
	if ( strptime( text, format, &tm ) ) {
		QDate d( tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
		QTime t( tm.tm_hour, tm.tm_min, tm.tm_sec, 0 );
		return QDateTime( d, t );
	} else // La fecha no era válida
		return QDateTime();
}




/* Formats the text of a currency or numeric type
   La implementación difiere de lo que dice man 7 locale cuando la cantidad
   se rodea con parentesis. Aqui mantengo el signo, si no, al convertir el
   formato a la cantidad, se pierde el signo
*/

String Formatter::formatLocaleCurrency( String text, double value ) const
{
	String result = "";

	int lc_p_cs_precedes = mRegConfig.getPCSPrecedes();
	int lc_p_sep_by_space = mRegConfig.getPSepBySpace();
	int lc_p_sign_posn = mRegConfig.getPSignPosn();
	int lc_n_cs_precedes = mRegConfig.getNCSPrecedes();
	int lc_n_sep_by_space = mRegConfig.getNSepBySpace();
	int lc_n_sign_posn = mRegConfig.getNSignPosn();

	stringReplace( text, mRegConfig.getNegativeSign(), "" );
	stringReplace( text, mRegConfig.getPositiveSign(), "" );
	text = text.stripWhiteSpace();
	if ( value < 0.0 ) {
		switch ( lc_n_sign_posn ) {
			/* Positive and negative sign positions:
			   0 Parentheses surround the quantity and currency_symbol.
			   1 The sign string precedes the quantity and currency_symbol.
			   2 The sign string follows the quantity and currency_symbol.
			   3 The sign string immediately precedes the currency_symbol.
			   4 The sign string immediately follows the currency_symbol.  */
		case 0:
			result = "(-";
			if ( lc_n_cs_precedes ) {
				result += mRegConfig.getCurrencySymbol();
				if ( lc_n_sep_by_space )
					result += " ";
			}
			result += text;
			if ( !lc_n_cs_precedes ) {
				if ( lc_n_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			result += ")";
			break;
		case 1:
			result = mRegConfig.getNegativeSign();
			if ( lc_n_cs_precedes ) {
				result += mRegConfig.getCurrencySymbol();
				if ( lc_n_sep_by_space )
					result += " ";
			}
			result += text;
			if ( !lc_n_cs_precedes ) {
				if ( lc_n_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			break;
		case 2:
			if ( lc_n_cs_precedes ) {
				result = mRegConfig.getCurrencySymbol();
				if ( lc_n_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_n_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			result += mRegConfig.getNegativeSign();
			break;
		case 3:
			if ( lc_n_cs_precedes ) {
				result = mRegConfig.getNegativeSign();
				result += mRegConfig.getCurrencySymbol();
				if ( lc_n_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_n_sep_by_space )
					result += " ";
				result += mRegConfig.getNegativeSign();
				result += mRegConfig.getCurrencySymbol();
			}
			break;
		case 4:
			if ( lc_n_cs_precedes ) {
				result = mRegConfig.getCurrencySymbol();
				result += mRegConfig.getNegativeSign();
				if ( lc_n_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_n_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
				result += mRegConfig.getNegativeSign();
			}
			break;
		default:
			result += "-" + text;
		}
	} else { /* positive values */
		switch ( lc_p_sign_posn ) {
			/* Positive and negative sign positions:
			   0 Parentheses surround the quantity and currency_symbol.
			   1 The sign string precedes the quantity and currency_symbol.
			   2 The sign string follows the quantity and currency_symbol.
			   3 The sign string immediately precedes the currency_symbol.
			   4 The sign string immediately follows the currency_symbol.  */
		case 0:
			result = "(";
			if ( lc_p_cs_precedes ) {
				result += mRegConfig.getCurrencySymbol();
				if ( lc_p_sep_by_space )
					result += " ";
			}
			result += text;
			if ( !lc_p_cs_precedes ) {
				if ( lc_p_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			result += ")";
			break;
		case 1:
			result = mRegConfig.getPositiveSign();
			if ( lc_p_cs_precedes ) {
				result += mRegConfig.getCurrencySymbol();
				if ( lc_p_sep_by_space )
					result += " ";
			}
			result += text;
			if ( !lc_p_cs_precedes ) {
				if ( lc_p_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			break;
		case 2:
			if ( lc_p_cs_precedes ) {
				result = mRegConfig.getCurrencySymbol();
				if ( lc_p_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_p_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
			}
			result += mRegConfig.getPositiveSign();
			break;
		case 3:
			if ( lc_p_cs_precedes ) {
				result = mRegConfig.getPositiveSign();
				result += mRegConfig.getCurrencySymbol();
				if ( lc_p_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_p_sep_by_space )
					result += " ";
				result += mRegConfig.getPositiveSign();
				result += mRegConfig.getCurrencySymbol();
			}
			break;
		case 4:
			if ( lc_p_cs_precedes ) {
				result = mRegConfig.getCurrencySymbol();
				result += mRegConfig.getPositiveSign();
				if ( lc_p_sep_by_space )
					result += " ";
				result += text;
			} else {
				result = text;
				if ( lc_p_sep_by_space )
					result += " ";
				result += mRegConfig.getCurrencySymbol();
				result += mRegConfig.getPositiveSign();
			}
			break;
		default:
			result += text;
		}
		
	}
	return result;
}



/*****************************************************************************
 * Processing of numeric masks
 *
 * #,9 -> Digit. If the first character is zero, it is replaced with a blank
 * 0 -> Digit. If the first character is zero, the zero is remained
 * . -> Decimal point position
 * , -> Thousands separator
 * + -> The number doesn't admit the negative sign
 * * -> Repeat the mask pattern
 *
 ****************************************************************************/


/* Check whether a character is valid for a mask */
/* Valuetype can be Formatter::numeric and Variant::tMoney */
int Formatter::masknum_match( Variant::Type valuetype, char text, char mask ) const
{
	switch ( mask ) {
	case '0':
		return isdigit( text );
	case '#':
	case '9':
		return isdigit( text ) || text == ' ';
	case ',':
		return text == LC_THOUSANDS_SEP;
	case '.':
		return text == LC_DECIMAL_POINT;
	default:
		return ( text == mask );
	}
}


/* Returns the default character for a mask character */
char Formatter::masknum_defaultchar( Variant::Type valuetype, char mask ) const
{
	switch ( mask ) {
	case '#':
	case '9':
		return '0';
	case ',':
		return LC_THOUSANDS_SEP;
	case '.':
		return LC_DECIMAL_POINT;
	default:
		return mask;
	}
}


/* Repeats the mask pattern up to a given length */
char *Formatter::masknum_dupmask( char *start, char *end, int maxlen ) const
{
	char * start_save, *pend;

	start_save = start;
	if ( end < start ) {
		start = end;
		end = start_save;
		start_save = start;
	} else if ( end == start ) {
		*start = '#';
		end++;
		maxlen--;
	}
	pend = end;
	while ( maxlen > 0 ) {
		start = start_save;
		while ( start < end ) {
			*pend++ = *start++;
			maxlen--;
		}
	}
	return pend;
}


/* Formats a numeric text according to a mask.
 * Tracks the position of the cursor.
*/
String Formatter::masknum_mask( const char *origtext, Variant::Type valuetype, const char *origmask,
                                  int startpos, int *position ) const
{
	const char * porig;
	char mask[ MAX_FORMAT_BUF ], *pmask, *puntomask;
	char text[ MAX_FORMAT_BUF ], *ptext, *puntotext;
	char entera[ MAX_FORMAT_BUF ], *pentera;
	char decimal[ MAX_FORMAT_BUF ], *pdecimal;
	char result[ MAX_FORMAT_BUF ];
	int yahaypunto, enelpunto, pospunto, longinsert, aborrarlen;
	int bneg, ltext, lmask, pos, decpos;
	int quitandoceros, repdec, repent, sign, ndec, borrando, dupmask;
	int autoposition;

	if ( position == NULL ) {  // No nos interesa la posición
		autoposition = ( int ) strlen( origtext );
		startpos = autoposition - 1;
		position = &autoposition;
	}
	if ( origmask == NULL )
		origmask = "";

	borrando = ( startpos >= *position );
	repdec = 0;
	repent = 0;
	ndec = 0;
	sign = 1;
	puntomask = NULL;
	pmask = mask;
	lmask = 0;
	dupmask = 0;
	while ( *origmask ) {
		if ( *origmask == '*' && puntomask == NULL )
			repent = 1;
		else if ( *origmask == '*' && puntomask != NULL ) {
			repdec = 1;
			/* Duplicar mascara hasta unos 8 decimales */
			if ( *( pmask - 1 ) == '.' )
				pmask = masknum_dupmask( pmask, pmask, 8 );
			else
				pmask = masknum_dupmask( pmask - 1, pmask, 8 - ( pmask - puntomask ) + 1 );
			lmask = strlen( mask );
		} else if ( *origmask == '+' )
			sign = 0;
		else if ( *origmask == '.' ) {
			if ( repent && !dupmask ) {
				/* Duplicar mascara hasta unos 20 digitos enteros */
				pmask = masknum_dupmask( mask, pmask, 20 );
				*pmask = '\0';
				lmask = strlen( mask );
				dupmask = 1;
			}
			puntomask = pmask;
			*pmask++ = *origmask;
			lmask++;
		} else {
			if ( puntomask != NULL )
				ndec++;
			*pmask++ = *origmask;
			lmask++;
		}
		origmask++;
	}
	if ( repent && !dupmask ) { // No se ha duplicado la mascara aún
		pmask = masknum_dupmask( mask, pmask, 20 );
		*pmask = '\0';
		lmask = strlen( mask );
	}
	*pmask = '\0';

	longinsert = *position - startpos;
	puntotext = strchr( origtext, LC_DECIMAL_POINT );
	if ( puntotext == NULL )
		pospunto = strlen( origtext );
	else
		pospunto = puntotext - origtext;
	enelpunto = *position - pospunto;
	porig = origtext;
	bneg = 0;
	// Sobreescribir, si no está en el punto y si no es un setText
	if ( enelpunto != 0
	        && !( longinsert == ( int ) strlen( origtext ) && startpos == 0 ) ) {
		porig = origtext;
		ptext = text;
		pos = 0;
		int maskpos = 0;
		aborrarlen = longinsert;
		if ( *porig == LC_NEGATIVE_SIGN ) {
			*ptext++ = *porig++; // No forma parte de la máscara
			pos++;
		}
		while ( *porig ) {
			if ( pos >= startpos && pos < *position ) {
				// Keeps track of the number of negative and positive sign that are deleted
				if ( *porig == LC_NEGATIVE_SIGN ) {
					bneg = !bneg;
					aborrarlen--;
					*position -= 1;
				} else if ( ( *porig == LC_THOUSANDS_SEP )
				            /* No sobreescribir si el caracter no va a ser valido */
				            || ( *porig == LC_DECIMAL_POINT && *( porig + 1 ) != LC_DECIMAL_POINT ) ) {
					*position -= 1;
					aborrarlen--;
				} else if ( *porig != LC_DECIMAL_POINT
				            && *porig != LC_THOUSANDS_SEP
				            && mask[ maskpos ] != ','
				            && !masknum_match( valuetype, *porig, mask[ maskpos ] ) ) {
					aborrarlen--;
					*position -= 1;
				} else {
					*ptext++ = *porig;
				}
			} else if ( ( pos >= *position && pos < *position + aborrarlen ) ) {
				if ( *porig == LC_THOUSANDS_SEP ) {
					aborrarlen++;
				}
			} else {
				*ptext++ = *porig;
			}
			pos++;
			maskpos++;
			porig++;
		}
		*ptext = '\0';
		porig = text;
	}

	decpos = 0;
	yahaypunto = 0;
	quitandoceros = 1;
	// Eliminar caracteres no validos del texto
	ptext = text;
	pos = 0;
	while ( *porig ) {
		if ( isdigit( *porig ) && !( *porig == '0' && quitandoceros ) ) {
			*ptext++ = *porig;
			quitandoceros = 0;
		} else {
			/* Se ha pulsado . en vez del punto decimal local */
			if ( *porig == '.'
			        && ( *( porig + 1 ) == LC_DECIMAL_POINT /*|| *(porig+1)=='\0'*/ ) ) {
				; //*position+=1;
			}	else
			if ( *porig == LC_DECIMAL_POINT ) {
				if ( yahaypunto == 0 ) {
					yahaypunto = 1;
					*ptext++ = LC_DECIMAL_POINT;
					quitandoceros = 0;
				}
			} else if ( *porig == LC_NEGATIVE_SIGN ) {
				bneg = !bneg;
				*position -= 1;
			} else if ( *porig == LC_POSITIVE_SIGN ) {
				bneg = 0;
				*position -= 1;
			} else {
				*position -= 1;
			}
		}
		porig++;
		pos++;
	}
	*ptext = '\0';

	if ( !mask || !*mask ) {
		if ( bneg && sign ) {
			*result = QChar( LC_NEGATIVE_SIGN );
			*position += 1;
			strncpy( result + 1, text, MAX_FORMAT_BUF - 1 );
		} else
			strncpy( result, text, MAX_FORMAT_BUF - 1 );
		result[ MAX_FORMAT_BUF - 1 ] = '\0';
		return result;
	}

	ltext = strlen( text );
	puntotext = strchr( text, LC_DECIMAL_POINT );
	puntomask = strchr( mask, '.' );
	pdecimal = decimal;
	if ( puntomask ) {
		// Formatear parte decimal
		if ( !puntotext )
			if ( borrando ) {
				ptext = text + *position;
			} else {
				ptext = text + ltext - ( ( ltext == longinsert ) ? 0 : ndec );
			}
		else
			ptext = puntotext + 1;
		pmask = puntomask + 1;
		*pdecimal++ = LC_DECIMAL_POINT;
		while ( *ptext && *pmask ) {
			if ( masknum_match( valuetype, *ptext, *pmask ) ) {
				*pdecimal++ = *ptext++;
				if ( *pmask )
					pmask++;
			} else if ( *pmask == ',' ) {
				// Raro que haya comas en parte decimal
				*pdecimal++ = LC_THOUSANDS_SEP;
				pmask++;
			} else {
				ptext++;
			}
			// creando parte decimal
		}
		while ( *pmask ) {
			if ( *pmask == '#' )
				pmask++;
			else if ( !repdec )
				* pdecimal++ = masknum_defaultchar( valuetype, *pmask++ );
		}
	}
	*pdecimal = '\0';
	// Formatear parte entera, desde el punto hacia la izquierda
	// o desde el final si no hay punto
	pentera = entera + MAX_FORMAT_BUF - 1;
	*pentera-- = '\0';
	if ( !puntomask ) {
		pmask = mask + lmask - 1;
	} else {
		pmask = puntomask - 1;
	}
	if ( !puntotext )
		//      if( borrando ) {
		//        ptext = text + *position - 1;
		//      } else {
		ptext = text + ltext - ( ( ltext == longinsert ) ? 0 : ndec ) - 1;
	//      }
	else
		ptext = puntotext - 1;
	while ( ptext >= text && pmask >= mask && pentera > entera ) {
		if ( masknum_match( valuetype, *ptext, *pmask ) ) {
			*pentera-- = *ptext--;
			pmask--;
		} else if ( *pmask == ',' ) {
			*pentera-- = LC_THOUSANDS_SEP;
			pmask--;
			*position += 1;
		} else {
			ptext--;
		}
	}
	// Anadir lo que queda de mascara
	while ( pmask >= mask && pentera > entera ) {
		if ( *pmask == '0' ) {
			*pentera-- = '0';
		} else if ( *pmask == ',' && *( pmask - 1 ) == '0' ) {
			*pentera-- = LC_THOUSANDS_SEP;
		} else if ( !repent ) {
			*pentera-- = ' ';
		} else { // Si está repitiendo máscara, ya termino
			*position -= 1;
		}
		pmask--;
		*position += 1;
	}
	// Caracteres sobrantes de text
	while ( ptext >= text ) {
		ptext--;
		*position -= 1;
	}
	pentera++;

	if ( *pentera == LC_THOUSANDS_SEP ) {
		*position -= 1;
		pentera++;
		// quitando coma inicial: position
	}
	if ( bneg && sign ) {
		*( --pentera ) = QChar( LC_NEGATIVE_SIGN );
		*position += 1;
	}
	strncpy( result, pentera, MAX_FORMAT_BUF );
	result[ MAX_FORMAT_BUF - 1 ] = '\0';
	strncat( result, decimal, MAX_FORMAT_BUF );
	result[ MAX_FORMAT_BUF - 1 ] = '\0';
	if ( *position < 0 )
		* position = 0;
	if ( result[ *position ] == ' ' ) {
		while ( result[ *position ] == ' ' )
			* position += 1;
		*position += 1;
	}
	if ( *position > ( int ) strlen( result ) )
		* position = ( int ) strlen( result );

	return String( result );
}


/*****************************************************************************
 * Processing of date and string masks
 *
 * General:
 * # -> Digit, space, + or -
 * 9 -> Digit or space
 * 0 -> Digit or zero
 * A -> Alphanumeric character
 *
 * Dates and times:
 *
 * 0   -> Digit or zero
 * d,D -> Day of the month
 * m   -> Month
 * y,Y -> Year
 * h,H -> Hour
 * M   -> Minutes
 * s,S -> Seconds
 *
 * \   -> The next character is treated as literal
 *
 * Formats:
 * Numeric:
 *     $   Currency symbol
 *     B   Blank if zero
 * Dates:
 *     same as strftime
 *
 ****************************************************************************/


/* Returns the length of a mask */
int Formatter::maskalfa_len( const char *pmask ) const
{
	int len = 0;
	while ( *pmask ) {
		if ( *pmask++ == LITERAL_MASK_CHAR )
			pmask++;
		len++;
	}
	return len;
}

/* Returns the default character for a mask character */
char Formatter::maskalfa_defaultchar( Variant::Type valuetype, const char *pmask, int pos ) const
{
	int inbackslash;

	pmask--;
	do {
		pmask++;
		if ( *pmask == LITERAL_MASK_CHAR ) {
			inbackslash = 1;
			pmask++;
		} else
			inbackslash = 0;
		pos--;
	} while ( *pmask && pos >= 0 );
	if ( inbackslash )
		return * pmask;
	else
		switch ( *pmask ) {
		case 'd':
		case 'D':
		case 'y':
		case 'Y':
		case 'h':
		case 'H':
		case 'm':
		case 'M':
		case 's':
		case 'S':
			if ( valuetype == Variant::tDate
			        || valuetype == Variant::tTime
			        || valuetype == Variant::tDateTime )
				return '0';
			else
				return *pmask;
		case '0':
			return mBlankChar;
		case '9':
		case '#':
		case 'A':
		case '>':
		case '<':
			return mBlankChar;
		default:
			return *pmask;
		}
}

/* Check whether a character is valid for a mask */
int Formatter::maskalfa_match( Variant::Type valuetype, char text, const char *pmask, int pos ) const
{
	int inbackslash;

	pmask--;
	do {
		pmask++;
		if ( *pmask == LITERAL_MASK_CHAR ) {
			inbackslash = 1;
			pmask++;
		} else
			inbackslash = 0;
		pos--;
	} while ( *pmask && pos >= 0 );
	if ( inbackslash )
		return ( text == *pmask );
	else {
		if ( text == maskalfa_defaultchar( valuetype, pmask, 0 ) )
			return 1;
		else
			switch ( *pmask ) {
			case 'd':
			case 'D':
			case 'm':
			case 'M':
			case 'y':
			case 'Y':
			case 'h':
			case 'H':
			case 's':
			case 'S':
				if ( valuetype == Variant::tDate
				        || valuetype == Variant::tTime
				        || valuetype == Variant::tDateTime )
					return isdigit( text );
				else
					return ( text == *pmask );
			case '9':
				return isdigit( text ) || text == ' ';
			case '#':
				return isdigit( text ) || text == ' '
				       || text == LC_POSITIVE_SIGN || text == LC_NEGATIVE_SIGN;
			case '0':
				return isdigit( text );
			case '>':
			case '<':
			case 'A':
				return isalpha( text );
			default:
				return ( text == *pmask );
			}
	}
}

/* gets the nth character in a mask, if it is not literal */
char Formatter::maskalfa_nth( Variant::Type /* valuetype */, const char *pmask, int pos ) const
{
	int inbackslash;

	pmask--;
	do {
		pmask++;
		if ( *pmask == LITERAL_MASK_CHAR ) {
			inbackslash = 1;
			pmask++;
		} else
			inbackslash = 0;
		pos--;
	} while ( *pmask && pos >= 0 );
	if ( inbackslash )
		return '\0';
	else
		return *pmask;
}


/* returns whether a character in a mask is editable */
bool Formatter::maskalfa_iseditable( Variant::Type valuetype, const char *pmask, int pos ) const
{
	bool inbackslash;

	pmask--;
	do {
		pmask++;
		if ( *pmask == LITERAL_MASK_CHAR ) {
			inbackslash = true;
			pmask++;
		} else
			inbackslash = false;
		pos--;
	} while ( *pmask && pos >= 0 );
	if ( inbackslash )
		return 0;
	else
		switch ( *pmask ) {
		case 'd':
		case 'D':
		case 'm':
		case 'M':
		case 'y':
		case 'Y':
		case 'h':
		case 'H':
		case 's':
		case 'S':
			if ( valuetype == Variant::tDate
			        || valuetype == Variant::tTime
			        || valuetype == Variant::tDateTime )
				return true;
			else
				return false;
		case '9':
		case '#':
		case '0':
		case 'A':
		case '<':
		case '>':
			return true;
		default:
			return false;
		}
}

/* Returns the first editable character in a mask */
int Formatter::maskalfa_firsteditable( Variant::Type valuetype, const char *pmask ) const
{
	int pos = 0;
	while ( !maskalfa_iseditable( valuetype, pmask, pos ) && pos < ( int ) strlen( pmask ) )
		pos++;
	return pos;
}

/* Returns the previous editable character in a mask */
int Formatter::maskalfa_previouseditable( Variant::Type valuetype, const char *pmask, int pos ) const
{
	while ( !maskalfa_iseditable( valuetype, pmask, pos ) && pos )
		pos--;
	return pos;
}

/* Returns the next editable character in a mask */
int Formatter::maskalfa_nexteditable( Variant::Type valuetype, const char *pmask, int pos ) const
{
	while ( !maskalfa_iseditable( valuetype, pmask, pos ) && pos < ( int ) strlen( pmask ) )
		pos++;
	return pos;
}

/* Returns the last editable character in a mask */
int Formatter::maskalfa_lasteditable( Variant::Type valuetype, const char *pmask ) const
{
	int pos = strlen( pmask );
	while ( !maskalfa_iseditable( valuetype, pmask, pos ) && pos )
		pos--;
	return pos;
}

/* Formats a text according to its type and mask(string, date and time) */
String Formatter::maskalfa_mask( const char *origtext, Variant::Type valuetype, const char *mask,
                                   int startpos, int *position ) const
{
	const char * porig;
	char *text, *ptext;
	int postext, posmask, borrandomask, borrando, endpos, masklen;
	char result[ MAX_FORMAT_BUF ], *presult;
	int autoposition = 0;

	if ( mask == NULL )
		return String( origtext );
	if ( position == NULL )
		position = &autoposition;

	text = new char[ MAX_FORMAT_BUF ];
	presult = result;
	borrandomask = ( startpos == *position && !maskalfa_iseditable( valuetype, mask, startpos ) );
	borrando = ( startpos == *position );
	porig = origtext;
	ptext = text;
	postext = 0;
	if ( borrando ) { /* desplazar a la izda solo caracteres sin mascara */
		while ( *porig && postext < startpos ) {
			*ptext++ = *porig++;
			postext++;
		}
		*ptext = '\0';
		masklen = maskalfa_len( mask );
		posmask = masklen - ( strlen( origtext ) - postext );
		while ( *porig ) {
			if ( maskalfa_iseditable( valuetype, mask, posmask ) )
				* ptext++ = *porig++;
			else
				porig++;
			posmask++;
		}
		*ptext = '\0';
		ptext = text;
	} else { /* sobreescribir */
		endpos = *position + ( *position - startpos );
		while ( *porig ) {
			/* No sobreescribir si el caracter no va a ser valido */
			if ( postext >= startpos && postext < *position ) {
				if ( !maskalfa_match( valuetype, *porig, mask, postext ) ) {
					*position -= 1;
					endpos--;
				} else {
					*ptext++ = *porig;
				}
			} else if ( postext >= *position && postext < endpos ) {}
			else {
				*ptext++ = *porig;
			}
			porig++;
			postext++;
		}
		*ptext = '\0';
		ptext = text;
	}

	postext = posmask = 0;
	while ( *ptext && maskalfa_defaultchar( valuetype, mask, posmask ) ) {
		if ( maskalfa_match( valuetype, *ptext, mask, posmask ) ) {
			if ( maskalfa_nth( valuetype, mask, posmask ) == '>' ) {
				*presult++ = toupper( *ptext );
				ptext++;
			} else if ( maskalfa_nth( valuetype, mask, posmask ) == '<' ) {
				*presult++ = tolower( *ptext );
				ptext++;
			} else
				*presult++ = *ptext++;
			postext++;
			posmask++;
		} else if ( !maskalfa_iseditable( valuetype, mask, posmask ) ) {
			*presult++ = maskalfa_defaultchar( valuetype, mask, posmask );
			posmask++;
			if ( postext <= startpos && !borrandomask ) {
				*position += 1;
			}
		} else {
			ptext++;
			postext++;
			if ( postext <= startpos && !borrandomask ) {
				*position -= 1;
			}
		}
		*presult = '\0';
	}
	while ( maskalfa_defaultchar( valuetype, mask, posmask ) ) {
		*presult++ = maskalfa_defaultchar( valuetype, mask, posmask );
		posmask++;
	}
	*presult = '\0';
	if ( *position < 0 )
		* position = 0;
	if ( borrandomask ) {
		if ( *position > 0 && !maskalfa_iseditable( valuetype, mask, *position - 1 ) )
			* position = maskalfa_previouseditable( valuetype, mask, *position ) + 1;
	} else if ( !maskalfa_iseditable( valuetype, mask, *position ) ) {
		*position = maskalfa_nexteditable( valuetype, mask, *position );
	}
	if ( *position < maskalfa_firsteditable( valuetype, mask ) ) {
		*position = maskalfa_firsteditable( valuetype, mask );
	} else if ( *position > maskalfa_lasteditable( valuetype, mask ) ) {
		*position = maskalfa_lasteditable( valuetype, mask ) + 1;
	}
	delete [] text;
	return String( result );
}



/* Generic function to format a text according to its type and mask */
String Formatter::mask_inedit( const char *origtext, Variant::Type valuetype,
                                 const char *mask, int start_pos, int *position ) const
{
	switch ( valuetype ) {
	case Variant::tDate:
		if ( !mask || !*mask )
			mask = mRegConfig.getDateMask();
		return maskalfa_mask( origtext, valuetype, mask, start_pos, position );
	case Variant::tTime:
		if ( !mask || !*mask )
			mask = mRegConfig.getTimeMask();
		return maskalfa_mask( origtext, valuetype, mask, start_pos, position );
	case Variant::tDateTime:
		if ( !mask || !*mask )
			mask = mRegConfig.getDateTimeMask();
		return maskalfa_mask( origtext, valuetype, mask, start_pos, position );
	case Variant::tInt:
		if ( !mask || !*mask )
			mask = "999999";
		return masknum_mask( origtext, valuetype, mask, start_pos, position );
	case Variant::tDouble:
		if ( !mask || !*mask )
			mask = mRegConfig.getNumberMask();
		return masknum_mask( origtext, valuetype, mask, start_pos, position );
	case Variant::tMoney:
		if ( !mask || !*mask )
			mask = mRegConfig.getCurrencyMask();
		return masknum_mask( origtext, valuetype, mask, start_pos, position );
	default:  /*  Formatter::string */
		return maskalfa_mask( origtext, valuetype, mask, start_pos, position );
	}
}



#ifdef MASK_TIMET

String Formatter::format( time_t adate, Variant::Type valuetype, const char *format, const char * /*mask*/ ) const
{
	char buffer[ MAX_FORMAT_BUF ];
	struct tm *tm = localtime( &adate );

	if ( !format || !( *format ) ) {
		switch ( valuetype ) {
		case Variant::tDate:
			format = mRegConfig.getDateMask();
			break;
		case Variant::Time:
			format = mRegConfig.getTimeMask();
			break;
		default:  /* Variant::tDateTime */
			format = mRegConfig.getDateTimeMask();
		}
	}
	strftime( buffer, MAX_FORMAT_BUF, format, tm );
	return String( buffer );
}


/* Unformats the text of a time or date entry, used in focus_in */
time_t Formatter::unFormatTimeT( const char *text, Variant::Type, const char *format, const char * /*mask*/ ) const
{
	struct tm tm = {
		               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	               };
	tm.tm_year = 30; /* Fictitious values for the date, for only-time dates */
	tm.tm_mon = 0;
	tm.tm_mday = 1;
	strptime( text, format, &tm );
	return mktime( &tm );
}


time_t Formatter::unMaskTimeT( const char *text, Variant::Type valuetype, const char *mask )
{
	const char * pmask, *ptext;
	struct tm lt = {
		               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	               };


	if ( mask == NULL || !( *mask ) ) {
		switch ( valuetype ) {
		case Variant::tDate:
			pmask = mRegConfig.getDateMask();
			break;
		case Variant::Time:
			pmask = mRegConfig.getTimeMask();
			break;
		default:  /* Variant::tDateTime */
			pmask = mRegConfig.getDateTimeMask();
		}
	} else
		pmask = mask;
	ptext = text;
	while ( *pmask && *ptext ) {
		switch ( *pmask ) {
		case 'd':
		case 'D':
			lt.tm_mday = lt.tm_mday * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 'm':
			lt.tm_mon = lt.tm_mon * 10 + ( int ) ( *ptext - '0' );
			break;
		case 'y':
		case 'Y':
			lt.tm_year = lt.tm_year * 10 + ( int ) ( *ptext - '0' );
			break;
		case 'h':
		case 'H':
			lt.tm_hour = lt.tm_hour * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 'M':
			lt.tm_min = lt.tm_min * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		case 's':
		case 'S':
			lt.tm_sec = lt.tm_sec * 10 + ( int ) ( ( *ptext ) - '0' );
			break;
		}
		pmask++;
		ptext++;
	}
	if ( lt.tm_mon > 0 )
		lt.tm_mon--;
	if ( lt.tm_year == 0 )  /* Just time, nor date */
		lt.tm_year = 70;
	else if ( lt.tm_year < 30 )
		lt.tm_year += 100;
	else if ( lt.tm_year > 100 )
		lt.tm_year -= 1900;
	return mktime( &lt );
}

String Formatter::mask( time_t adate, Variant::Type valuetype, const char *mask ) const
{
	const char * pmask;
	char buffer[ MAX_FORMAT_BUF ] = "", itemformat[] = "%0_d";
	int l, days, months, years, hours, minutes, seconds;
	struct tm lt = *localtime( &adate );
	int module = 1;

	days = months = years = hours = minutes = seconds = 0;
	if ( mask == NULL || !( *mask ) ) {
		switch ( valuetype ) {
		case Variant::tDate:
			pmask = mRegConfig.getDateMask();
			break;
		case Variant::Time:
			pmask = mRegConfig.getTimeMask();
			break;
		default:  /* Variant::tDateTime */
			pmask = mRegConfig.getDateTimeMask();
		}
	} else
		pmask = mask;
	pmask--;
	do {
		pmask++;
		switch ( *pmask ) {
		case 'd':
		case 'D':
			days++;
			break;
		case 'm':
			months++;
			break;
		case 'y':
		case 'Y':
			years++;
			module *= 10;
			break;
		case 'h':
		case 'H':
			hours++;
			break;
		case 'M':
			minutes++;
			break;
		case 's':
		case 'S':
			seconds++;
			break;
		default:
			if ( days ) {
				itemformat[ 2 ] = ( char ) days + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_mday );
				days = 0;
			}
			if ( months ) {
				itemformat[ 2 ] = ( char ) months + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_mon + 1 );
				months = 0;
			}
			if ( years ) {
				itemformat[ 2 ] = ( char ) years + '0';
				sprintf( buffer + strlen( buffer ), itemformat, ( lt.tm_year + 1900 ) % module );
				years = 0;
			}
			if ( hours ) {
				itemformat[ 2 ] = ( char ) hours + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_hour );
				hours = 0;
			}
			if ( minutes ) {
				itemformat[ 2 ] = ( char ) minutes + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_min );
				minutes = 0;
			}
			if ( seconds ) {
				itemformat[ 2 ] = ( char ) seconds + '0';
				sprintf( buffer + strlen( buffer ), itemformat, lt.tm_sec );
				seconds = 0;
			}
			l = strlen( buffer );
			buffer[ l ] = *pmask;
			buffer[ l + 1 ] = '\0';
		}
	} while ( *pmask );
	return String( buffer );
}


#endif
