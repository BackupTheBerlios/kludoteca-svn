/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkregconfig.h Regional configuration
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

#ifndef RTKREGCONFIG_H
#define RTKREGCONFIG_H

#include "rtknamespace.h"

namespace RTK {


class RegConfig {

public:
	void setLocale(const char *locale="");
	void setLocaleCurrencyFormat(const char *locale="");
	void setLocaleNumberFormat(const char *locale="");
	void setLocaleDateFormats(const char *locale="");
	void setDateFormat(const String &format);
	void setTimeFormat(const String &format);
	void setDateTimeFormat(const String &format);
	void setCurrencyFormat(const String& currencysymbol,
		int currencyfracdigits = 2,
		QChar currencydecimalpoint = ',',
		QChar currencythousandssep = '.',
        int p_cs_precedes = 0,
		int p_sep_by_space = 1,
 		int p_sign_posn = 1,
        int n_cs_precedes = 0,
		int n_sep_by_space = 1,
		int n_sign_posn = 1,
		const char *grouping="\x03");

	void setNumberFormat(	int frac_digits = 2,
		QChar decimalpoint = ',',
		QChar thousandssep = '.',
		const String& positivesign = "",
		const String& negativesign = "-",
		const char *grouping="\x03");

	const String &getCurrencyMask() const { return mCurrencyMask; }
	const String &getNumberMask() const { return mNumberMask; }

public:
	RegConfig(QChar decimalpoint = ',', QChar thousandssep = '.',
		const String& positivesign = "", const String& negativesign = "-", const String& currencysymbol = "",
		int currencyfracdigits = 2, QChar currencydecimalpoint = ',', QChar currencythousandssep = '.',
		const String& datemask = "", const String& timemask = "", const String& datetimemask = "", 
		int psignposn = 1, int pcsprecedes = 0, int psepbyspace = 0, 
		int nsignposn = 1, int ncsprecedes = 0, int nsepbyspace = 0, const String& grouping = "")
	:mDecimalPoint(decimalpoint), mThousandsSep(thousandssep), 
		mPositiveSign(positivesign), mNegativeSign(negativesign), mCurrencySymbol(currencysymbol), 
		mCurrencyFracDigits(currencyfracdigits), mCurrencyDecimalPoint(currencydecimalpoint), mCurrencyThousandsSep(currencythousandssep), 
		mDateMask(datemask), mTimeMask(timemask), mDateTimeMask(datetimemask), 
		mPSignPosn(psignposn), mPCSPrecedes(pcsprecedes), mPSepBySpace(psepbyspace), 
		mNSignPosn(nsignposn), mNCSPrecedes(ncsprecedes), mNSepBySpace(nsepbyspace), mGrouping(grouping)
	{};
	/** Gets the Separador decimal */
	QChar getDecimalPoint() const { return mDecimalPoint; };
	/** Sets the Separador decimal */
	void setDecimalPoint(QChar decimalpoint) { mDecimalPoint = decimalpoint; };
	/** Gets the Separador de miles */
	QChar getThousandsSep() const { return mThousandsSep; };
	/** Sets the Separador de miles */
	void setThousandsSep(QChar thousandssep) { mThousandsSep = thousandssep; };
	/** Gets the Signo positivo */
	const String& getPositiveSign() const { return mPositiveSign; };
	/** Sets the Signo positivo */
	void setPositiveSign(const String& positivesign) { mPositiveSign = positivesign; };
	/** Gets the Signo negativo */
	const String& getNegativeSign() const { return mNegativeSign; };
	/** Sets the Signo negativo */
	void setNegativeSign(const String& negativesign) { mNegativeSign = negativesign; };
	/** Gets the Simbolo de la moneda */
	const String& getCurrencySymbol() const { return mCurrencySymbol; };
	/** Sets the Simbolo de la moneda */
	void setCurrencySymbol(const String& currencysymbol) { mCurrencySymbol = currencysymbol; };
	/** Gets the Numero de decimales para las cantidades monetarias */
	int getCurrencyFracDigits() const { return mCurrencyFracDigits; };
	/** Sets the Numero de decimales para las cantidades monetarias */
	void setCurrencyFracDigits(int currencyfracdigits) { mCurrencyFracDigits = currencyfracdigits; };
	/** Gets the Separador de decimales en cantidades monetarias */
	QChar getCurrencyDecimalPoint() const { return mCurrencyDecimalPoint; };
	/** Sets the Separador de decimales en cantidades monetarias */
	void setCurrencyDecimalPoint(QChar currencydecimalpoint) { mCurrencyDecimalPoint = currencydecimalpoint; };
	/** Gets the Separador de miles en cantidades monetarias */
	QChar getCurrencyThousandsSep() const { return mCurrencyThousandsSep; };
	/** Sets the Separador de miles en cantidades monetarias */
	void setCurrencyThousandsSep(QChar currencythousandssep) { mCurrencyThousandsSep = currencythousandssep; };
	/** Gets the Máscara para las fechas */
	const String& getDateMask() const { return mDateMask; };
	/** Sets the Máscara para las fechas */
	void setDateMask(const String& datemask) { mDateMask = datemask; };
	/** Gets the Máscara para las horas */
	const String& getTimeMask() const { return mTimeMask; };
	/** Sets the Máscara para las horas */
	void setTimeMask(const String& timemask) { mTimeMask = timemask; };
	/** Gets the Máscara para las fechas y horas */
	const String& getDateTimeMask() const { return mDateTimeMask; };
	/** Sets the Máscara para las fechas y horas */
	void setDateTimeMask(const String& datetimemask) { mDateTimeMask = datetimemask; };
	/** Gets the El signo positivo precede a la cantidad */
	int getPSignPosn() const { return mPSignPosn; };
	/** Sets the El signo positivo precede a la cantidad */
	void setPSignPosn(int psignposn) { mPSignPosn = psignposn; };
	/** Gets the El simbolo monetario precede a la cantidad */
	int getPCSPrecedes() const { return mPCSPrecedes; };
	/** Sets the El simbolo monetario precede a la cantidad */
	void setPCSPrecedes(int pcsprecedes) { mPCSPrecedes = pcsprecedes; };
	/** Gets the El simbolo monetario se separa con un espacio de la cantidad */
	int getPSepBySpace() const { return mPSepBySpace; };
	/** Sets the El simbolo monetario se separa con un espacio de la cantidad */
	void setPSepBySpace(int psepbyspace) { mPSepBySpace = psepbyspace; };
	/** Gets the El signo negativo precede a la cantidad */
	int getNSignPosn() const { return mNSignPosn; };
	/** Sets the El signo negativo precede a la cantidad */
	void setNSignPosn(int nsignposn) { mNSignPosn = nsignposn; };
	/** Gets the El simbolo monetario precede a la cantidad */
	int getNCSPrecedes() const { return mNCSPrecedes; };
	/** Sets the El simbolo monetario precede a la cantidad */
	void setNCSPrecedes(int ncsprecedes) { mNCSPrecedes = ncsprecedes; };
	/** Gets the El simbolo monetario se separa con un espacio de la cantidad */
	int getNSepBySpace() const { return mNSepBySpace; };
	/** Sets the El simbolo monetario se separa con un espacio de la cantidad */
	void setNSepBySpace(int nsepbyspace) { mNSepBySpace = nsepbyspace; };
	const String& getGrouping() const { return mGrouping; };
	void setGrouping(const String& grouping) { mGrouping = grouping; };
protected:
	QChar mDecimalPoint;
	QChar mThousandsSep;
	String mPositiveSign;
	String mNegativeSign;
	String mCurrencySymbol;
	int mCurrencyFracDigits;
	QChar mCurrencyDecimalPoint;
	QChar mCurrencyThousandsSep;
	String mDateMask;
	String mTimeMask;
	String mDateTimeMask;
	int mPSignPosn;
	int mPCSPrecedes;
	int mPSepBySpace;
	int mNSignPosn;
	int mNCSPrecedes;
	int mNSepBySpace;
	String mGrouping;

private:
	String mCurrencyMask, mNumberMask;
	String buildNumberMask(const char *grouping, int digits);
	String buildDateMask(int wich_format, const char *nl_format);
};

}; // namespace

#endif
