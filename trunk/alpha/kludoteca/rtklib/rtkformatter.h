/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkformatter.h String and number formatting with locale
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

#ifndef RTKFORMATTER_H
#define RTKFORMATTER_H

#include <time.h>

#include "rtknamespace.h"
#include "rtkmoney.h"
#include "rtkvariant.h"
#include "rtkregconfig.h"

namespace RTK
{

/**
  @short Class format strings with locale info
  */
class Formatter
{

public:
        Formatter(const RegConfig &regcfg, char blank_char = ' ');
	
        String format(const String &text, const String &format, const String &mask) const;
        String format(int val, const String &format, const String &mask) const;
        String format(double val, const String &format, const String &mask) const;
        String format(const Money &val, const String &format, const String &mask) const;
        String format(const QDate &adate, const String &format, const String &mask) const;
        String format(const QTime &atime, const String &format, const String &mask) const;
        String format(const QDateTime &adatetime, const String &format, const String &mask) const;
        String format(const Variant &avalue, const String &format, 
			const String &mask, Variant::Type valuetype = Variant::Invalid) const;
	
        int unMaskInt(const String &text, const String &mask) const;
        int unFormatInt(const String &text, const String &format) const;
        double unMaskDouble(const String &text, const String &mask) const;
        double unFormatDouble(const String &text, const String &format) const;
        Money unMaskMoney(const String &text, const String &mask) const;
        Money unFormatMoney(const String &text, const String &format) const;
        QDateTime unMaskDateTime(const String &text, const String &mask, Variant::Type valuetype = Variant::tDateTime ) const;
        QDateTime unFormatDateTime(const String &text, const String &format, Variant::Type valuetype = Variant::tDateTime ) const;

        String mask(const char *text, Variant::Type valuetype, const char *mask) const;
        String mask(int val, Variant::Type valuetype, const char *mask) const;
        String mask(double valValue, Variant::Type valuetype, const char *mask) const;
        String mask(const QDateTime &adate, Variant::Type valuetype, const char *mask) const;
        String mask(const Variant &avalue, Variant::Type valuetype, const char *mask) const;

	// formatea un texto y mantiene la posicion del cursor
        String mask_inedit(const char *origtext, Variant::Type valuetype, const char *mask,
                        int start_pos, int *position) const;
	
        void setBlankChar(char blank_char);
        char getBlankChar() const;
		
#ifdef MASK_TIMET	
        String mask(time_t adate, Variant::Type valuetype, const char *mask) const;
        String format(time_t adate, Variant::Type valuetype, const char *format, const char *mask) const;
        time_t unFormatTimeT(const char *text, Variant::Type valuetype, const char *format, const char *mask) const;
        time_t unMaskTimeT(const char *text, Variant::Type valuetype, const char *mask) const;
#endif	
	
	
private:
		RegConfig mRegConfig;
        char mBlankChar;

        String formatLocaleCurrency(String text, double value) const;
	
	
        char maskalfa_nth(Variant::Type valuetype, const char *pmask, int pos) const;
        int maskalfa_len(const char *pmask) const;
        bool maskalfa_iseditable(Variant::Type valuetype, const char *pmask, int pos) const;
        int maskalfa_firsteditable(Variant::Type valuetype, const char *pmask) const;
        int maskalfa_previouseditable(Variant::Type valuetype, const char *pmask, int pos) const;
        int maskalfa_nexteditable(Variant::Type valuetype, const char *pmask, int pos) const;
        int maskalfa_lasteditable(Variant::Type valuetype, const char *pmask) const;
        char maskalfa_defaultchar(Variant::Type valuetype, const char *pmask, int pos) const;
        int maskalfa_match(Variant::Type valuetype, char text, const char *pmask, int pos) const;
        String maskalfa_mask(const char *text, Variant::Type valuetype, const char *mask,
                              int startpos=-1, int *position=NULL) const;

        String formatDate(const char *p_text, Variant::Type valuetype, const char *p_format, const char *p_mask) const;

        int masknum_match(Variant::Type valuetype, char text, char mask) const;
        char masknum_defaultchar(Variant::Type valuetype, char mask) const;
        char *masknum_dupmask(char *start, char *end, int maxlen) const;
        String masknum_mask(const char *text, Variant::Type valuetype, const char *mask, int startpos=-1, int *position=NULL) const;
};

}; // namespace

#endif // RTKFORMATTER_H

