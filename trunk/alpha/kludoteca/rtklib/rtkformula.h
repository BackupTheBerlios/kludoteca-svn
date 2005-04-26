/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkformula.h formulae and/or scripts
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

#ifndef RTKFORMULA_H
#define RTKFORMULA_H

#include "rtknamespace.h"
#include "rtkvariant.h"

namespace RTK {

class Formula {
/*<<<<<FORMULA_CONSTRUCTOR*/
public:
	Formula(const String& name = String::null, const String& code = String::null)
	:mName(name), mCode(code)
/*>>>>>FORMULA_CONSTRUCTOR*/
	{};
  
	~Formula();
//   Variant ValueToVariant(KJS::ExecState* exec, const KJS::Value &val);

/*<<<<<FORMULA_GETSET*/
public:
	const String& getName() const { return mName; };
	void setName(const String& name) { mName = name; };
	const String& getCode() const { return mCode; };
	void setCode(const String& code) { mCode = code; };
protected:
	String mName;
	String mCode;
/*>>>>>FORMULA_GETSET*/
#ifndef NDEBUG
    void debug_print();
#endif    
};

}; // namespace

#endif // RTKFORMULA_H
