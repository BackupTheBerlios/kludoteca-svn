/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkregconfig.cpp Regional configuration
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

#include <limits.h>
#include <locale.h>
#include <langinfo.h>
#include "rtkregconfig.h"

using namespace RTK;


#define MAX_FORMAT_BUF 255

void RegConfig::setLocale( const char *locale )
{
	setLocaleCurrencyFormat( locale );
	setLocaleNumberFormat( locale );
	setLocaleDateFormats( locale );
}

void RegConfig::setLocaleDateFormats( const char * /*locale*/ )
{
	//    printf("%s\n", nl_langinfo(T_FMT));
	//    printf("%s\n", nl_langinfo(D_FMT));
	//    printf("%s\n", nl_langinfo(D_T_FMT));
	setDateFormat( nl_langinfo( D_FMT ) );
	setTimeFormat( nl_langinfo( T_FMT ) );
	setDateTimeFormat( nl_langinfo( D_T_FMT ) );
}

void RegConfig::setLocaleCurrencyFormat( const char *locale )
{
	struct lconv * lc;
	setlocale( LC_MONETARY, locale );
	lc = localeconv();
	setCurrencyFormat(
	    lc->currency_symbol,
	    ( int ) lc->frac_digits,
	    *lc->mon_decimal_point,
	    *lc->mon_thousands_sep,
	    lc->p_cs_precedes,
	    lc->p_sep_by_space,
	    lc->p_sign_posn,
	    lc->n_cs_precedes,
	    lc->n_sep_by_space,
	    lc->n_sign_posn,
	    lc->grouping );
}

void RegConfig::setLocaleNumberFormat( const char *locale )
{
	struct lconv * lc;
	setlocale( LC_NUMERIC, locale );
	lc = localeconv();
	setNumberFormat(
	    2,
	    *lc->mon_decimal_point,
	    *lc->mon_thousands_sep,
	    lc->positive_sign,
	    lc->negative_sign,
	    lc->grouping );
}


void RegConfig::setCurrencyFormat(
    const QString &currencysymbol,
    int currencyfracdigits,
    QChar currencydecimalpoint,
    QChar currencythousandssep,
    int p_cs_precedes,
    int p_sep_by_space,
    int p_sign_posn,
    int n_cs_precedes,
    int n_sep_by_space,
    int n_sign_posn,
    const char *grouping )
{
	setCurrencySymbol( currencysymbol );
	if ( currencydecimalpoint != '\0' ) {
		setCurrencyDecimalPoint( currencydecimalpoint );
	} else if ( getDecimalPoint() != '\0' ) {
		setCurrencyDecimalPoint( getDecimalPoint() );
	} else {
		setCurrencyDecimalPoint( '.' );
	}
	if ( currencythousandssep != '\0' ) {
		setCurrencyThousandsSep( currencythousandssep );
	} else if ( getThousandsSep() != '\0' ) {
		setCurrencyThousandsSep( getThousandsSep() );
	} else {
		setCurrencyThousandsSep( ',' );
	}
	mCurrencyMask = buildNumberMask( grouping, currencyfracdigits );
	mPSignPosn = p_sign_posn;
	mPCSPrecedes = p_cs_precedes;
	mPSepBySpace = p_sep_by_space;
	mNSignPosn = n_sign_posn;
	mNCSPrecedes = n_cs_precedes;
	mNSepBySpace = n_sep_by_space;
}

void RegConfig::setNumberFormat(
    int frac_digits,
    QChar decimalpoint,
    QChar thousandssep,
    const QString& positivesign,
    const QString& negativesign,
    const char *grouping )
{
	if ( ( positivesign != "," ) && ( positivesign != "." ) )
		setPositiveSign( positivesign );
	if ( !negativesign.isEmpty() && negativesign != "," && negativesign != "." )
		setNegativeSign( negativesign );
	else
		setNegativeSign( "-" );
	if ( decimalpoint != '\0' ) {
		setDecimalPoint( decimalpoint );
	} else {
		setDecimalPoint( ',' );
	}
	if ( thousandssep != '\0' ) {
		setThousandsSep( thousandssep );
	} else {
		setThousandsSep( '.' );
	}
	mNumberMask = buildNumberMask( grouping, frac_digits );
}


/* Create default monetary/number mask. See <locale.h> for description
   Esta implementación no es exactamente la misma que sugiere man 7 locale.
   Allí, se dice que el último elemento de grouping, si es cero, indica que se
   repite solo el elemento anterior. Sin embargo, por la forma de tratar las
   mascaras en GMaskFormatter con el *, aqui se repite toda la agrupación de
   dígitos.
*/
QString RegConfig::buildNumberMask( const char *grouping, int digits )
{
	QString mask;

	if ( !grouping || !*grouping ) {
		mask = "*,###";
	} else {
		const char *grp = grouping + ( strlen( grouping ) - 1 );
		mask = '*';
		while ( grp >= grouping ) {
			if ( *grp != CHAR_MAX )  /* locale not set */
				mask += ',';
			if ( *grp >= '0' ) { // "333" en vez de "\x03\x03\x03"
				for ( int i = 0; i < ( *grp - '0' ); i++ )
					mask += '#';
			} else {
				for ( int i = 0; i < *grp; i++ )
					mask += '#';
			}
			grp--;
		}
	}
	if ( digits > 0 && digits != CHAR_MAX ) {
		mask += '.';
		while ( digits-- )
			mask += '#';
	}
	return mask;
}


void RegConfig::setDateFormat( const QString &dateformat )
{
	setDateMask( buildDateMask( D_FMT, dateformat ) );
}

void RegConfig::setTimeFormat( const QString &timeformat )
{
	setTimeMask( buildDateMask( T_FMT, timeformat ) );
}

void RegConfig::setDateTimeFormat( const QString &datetimeformat )
{
	setDateTimeMask( buildDateMask( D_T_FMT, datetimeformat ) );
}


/* Create default date/time mask. See <locale.h> for description */
QString RegConfig::buildDateMask( int wich_format, const char *nl_format )
{
	QString mask;
	char format[ MAX_FORMAT_BUF ], *pformat;
	int inpercent, embedded;
	int hasday, hasmonth, hasyear, hashour, hasminute, hassecond;


	if ( !nl_format || !*nl_format ) {
		switch ( wich_format ) {
		case D_FMT:
			mask = "dd/mm/yy";
			break;
		case T_FMT:
			mask = "HH/MM/SS";
			break;
		case D_T_FMT:
			mask = "dd/mm/yy HH/MM/SS";
			break;
		default:
			mask = "";
		}
	} else {
		/* expand embedded date or time formats %c, %x, %X and %T */
		pformat = format;
		do {
			inpercent = 0;
			embedded = 0;
			while ( *nl_format ) {
				if ( *nl_format == '%' ) {
					if ( inpercent ) {
						*pformat++ = '%';
						*pformat++ = *nl_format;
						inpercent = 0;
					} else {
						inpercent = 1;
					}
				} else if ( !inpercent ) {
					*pformat++ = *nl_format;
				} else { /* within percent */
					inpercent = 0;
					switch ( *nl_format ) {
					case 'c':  /* embedded datetime as %x %X */
						strcpy( pformat, nl_langinfo( D_FMT ) );
						strcat( pformat, " " );
						strcat( pformat, nl_langinfo( T_FMT ) );
						pformat = pformat + strlen( pformat );
						embedded = 1;
						break;
					case 'C':  /* embedded long format locale datetime */
						strcpy( pformat, nl_langinfo( D_T_FMT ) );
						pformat = pformat + strlen( pformat );
						embedded = 1;
						break;
					case 'D':  /* embedded date as %m/%d/%y */
						strcpy( pformat, "%m/%d/%y" );
						pformat = format + strlen( format );
						embedded = 1;
						break;
					case 'x':  /* embedded locale date */
						strcpy( pformat, nl_langinfo( D_FMT ) );
						pformat = pformat + strlen( pformat );
						embedded = 1;
						break;
					case 'X':  /* embedded locale time */
						strcpy( pformat, nl_langinfo( T_FMT ) );
						pformat = pformat + strlen( pformat );
						embedded = 1;
						break;
					case 'T':  /* embedded time as %H:%M:%S */
						strcpy( pformat, "%H:%M:%S" );
						pformat = format + strlen( format );
						embedded = 1;
						break;
					case 'R': 		/* GNU extension.  */
						strcpy( pformat, "%H:%M" );
						pformat = format + strlen( format );
						embedded = 1;
						break;
					case 'r': 		/* POSIX.2 extension.  */
						strcpy( pformat, "%H:%M:%S" ); /*"%I:%M:%S %p" originally */
						pformat = format + strlen( format );
						embedded = 1;
						break;
					default:
						*pformat++ = '%';
						*pformat++ = *nl_format;
					}
				}
				nl_format++;
			}
		} while ( embedded != 0 );
		*pformat = '\0';

		pformat = format;
		hasday = hasmonth = hasyear = hashour = hasminute = hassecond = 0;
		inpercent = 0;
		while ( *pformat ) {
			if ( *pformat == '%' ) {
				if ( inpercent ) {
					mask += *pformat;
					inpercent = 0;
				} else {
					inpercent = 1;
				}
			} else if ( !inpercent ) {
				mask += *pformat;
			} else { /* within percent */
				inpercent = 0;
				switch ( *pformat ) {
				case 'y':
					if ( !hasyear ) {
						mask += 'y';
						mask += 'y';
						hasyear = 1;
					}
					break;
				case 'Y':
					if ( !hasyear ) {
						mask += 'y';
						mask += 'y';
						mask += 'y';
						mask += 'y';
						hasyear = 1;
					}
					break;
				case 'm':
				case 'b':
					if ( !hasmonth ) {
						mask += 'm';
						mask += 'm';
						hasmonth = 1;
					}
					break;
				case 'd':
					if ( !hasday ) {
						mask += 'd';
						mask += 'd';
						hasday = 1;
					}
					break;
				case 'H':
				case 'I':
					if ( !hashour ) {
						mask += 'H';
						mask += 'H';
						hashour = 1;
					}
					break;
				case 'M':
					if ( !hasminute ) {
						mask += 'M';
						mask += 'M';
						hashour = 1;
					}
					break;
				case 'S':
					if ( !hassecond ) {
						mask += 'S';
						mask += 'S';
						hassecond = 1;
					}
					break;
				case 'U':
				case 'W':
				case 'w':
				case 'p':
				case 'a':
				case 'A':
				case 'j':
				case 'B':
				case 'Z':
					/* not used */
					break;
				}
			}
			pformat++;
		}
	}
	return QString( mask );
}
