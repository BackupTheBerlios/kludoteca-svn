/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinput.h RTK input object
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
#ifndef RTKINPUT_H
#define RTKINPUT_H

#include "rtknamespace.h"
#include "rtkvariant.h"
#include "rtkinputfield.h"

//#include <qxml.h>
class QXmlAttributes;

namespace RTK {

class Input {
/*<<<<<INPUT_CONSTRUCTOR*/
public:
	Input(const String& name = String::null, const String& driver = String::null)
	:mName(name), mDriver(driver)
/*>>>>>INPUT_CONSTRUCTOR*/
    {};
    virtual ~Input() {};
    virtual bool init() = 0;
    virtual bool next() = 0;
    virtual Variant getValue(uint /*i*/) { return Variant(); }
    virtual Variant getValue(const String &/*fldname*/) { return Variant(); }
    virtual bool parseAttrs(const QXmlAttributes&) { return true; };
	
    InputField *getInputField(const String &name) const;
    InputField *getInputField(int i) const { return mInputFields[i]; }
    int insertInputField(InputField *inputfield);

/*<<<<<INPUT_GETSET*/
public:
	/** Gets Input's name */
	const String& getName() const { return mName; };
	/** Sets the Input's name */
	void setName(const String& name) { mName = name; };
	/** Gets Input's driver */
	const String& getDriver() const { return mDriver; };
protected:
	String mName;
	String mDriver;
/*>>>>>INPUT_GETSET*/

protected:
    QValueList<InputField *> mInputFields;
};

}; // namespace

#endif
