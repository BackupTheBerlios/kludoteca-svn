/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputfield.h RTK input field object
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

#ifndef RTKINPUTFIELD_H
#define RTKINPUTFIELD_H

#include "rtknamespace.h"

namespace RTK {

class InputField
{
/*<<<<<INPUTFIELD_CONSTRUCTOR*/
public:
	InputField(const String& name, const String& source = String::null, RTK::Variant::Type type = Variant::Invalid)
	:mName(name), mSource(source), mType(type)
/*>>>>>INPUTFIELD_CONSTRUCTOR*/
	{};
  
/*<<<<<INPUTFIELD_GETSET*/
public:
	const String& getName() const { return mName; };
	void setName(const String& name) { mName = name; };
	const String& getSource() const { return mSource; };
	void setSource(const String& source) { mSource = source; };
	RTK::Variant::Type getType() const { return mType; };
	void setType(RTK::Variant::Type type) { mType = type; };
protected:
	String mName;
	String mSource;
	RTK::Variant::Type mType;
/*>>>>>INPUTFIELD_GETSET*/
};

}; // namespace

#endif
