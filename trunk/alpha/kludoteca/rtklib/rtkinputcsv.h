/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputcsv.h RTK standard csv input object
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
#ifndef INPUTCSV_H
#define INPUTCSV_H

class QFile;

#include "rtkinput.h"

/**
  *@author Francisco Santiago Capel Torres
  */

namespace RTK
{

class InputCsv : public Input
{
/*<<<<<INPUTCSV_CONSTRUCTOR*/
public:
	InputCsv(const String& filename = String::null, const String& delimiters = ",", 
		const String& quote = "\"", int headerlines = 1,
	const String& name = String::null, const String& driver = String::null)
	:Input(name, driver),
	mFilename(filename), mDelimiters(delimiters), 
		mQuote(quote), mHeaderLines(headerlines)
/*>>>>>INPUTCSV_CONSTRUCTOR*/
			, pFile( 0 )
	{};
	~InputCsv();

/*<<<<<INPUTCSV_GETSET*/
public:
	/** Gets The name of the CSV file */
	const String& getFilename() const { return mFilename; };
	/** Sets the The name of the CSV file */
	void setFilename(const String& filename) { mFilename = filename; };
	/** Gets The delimiter(s) of the columns */
	const String& getDelimiters() const { return mDelimiters; };
	/** Sets the The delimiter(s) of the columns */
	void setDelimiters(const String& delimiters) { mDelimiters = delimiters; };
	/** Gets The quotation simbol used for alphanumeric values */
	const String& getQuote() const { return mQuote; };
	/** Sets the The quotation simbol used for alphanumeric values */
	void setQuote(const String& quote) { mQuote = quote; };
	/** Gets The number of header lines in the CSV file */
	int getHeaderLines() const { return mHeaderLines; };
	/** Sets the The number of header lines in the CSV file */
	void setHeaderLines(int headerlines) { mHeaderLines = headerlines; };
protected:
	String mFilename;
	String mDelimiters;
	String mQuote;
	int mHeaderLines;
/*>>>>>INPUTCSV_GETSET*/

public:
	bool init();
	bool next();
	int fieldPos( const String &name ) const;
	Variant getValue(const String &fldname);

private:
	QFile *pFile;
	QTextStream *pTextStream;
	QValueList<QString> mRowValues;	
	Variant correctType(Variant::Type t, const String &value);
	
};

}; // namespace

#endif


