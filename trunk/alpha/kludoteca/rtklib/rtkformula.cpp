/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkformula.cpp formulae and/or scripts
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

#include "rtkformula.h"

using namespace RTK;

Formula::~Formula()
{
}


#if 0
// Aun no hay nada que hacer con las fórmulas

#include <qstring.h>
#include <kjs/ustring.h>

#include "rtkformula.h"

using namespace RTK;

QString KJS::UString::qstring() const
{
  return QString((QChar*) data(), size());
}

QConstString KJS::UString::qconststring() const
{
  return QConstString((QChar*) data(), size());
}




Variant Formula::ValueToVariant(KJS::ExecState* exec, const KJS::Value &val)
{
  Variant res;
  switch (val.type()) {
  case KJS::BooleanType:
    res = Variant(val.toBoolean(exec), 0);
    break;
  case KJS::NumberType:
    res = Variant(val.toNumber(exec));
    break;
  case KJS::StringType:
    res = Variant(String(val.toString(exec).qstring()));
    break;
  default:
    // everything else will be 'invalid'
    break;
  }
  return res;
}

#ifndef NDEBUG
void Formula::debug_print()
{

    printf("Formula:("
/*<<<<<FORMULA_DEBUGPRINT*/
	"Name='%s'"","
	"Code='%s'"
	")",
	(const char *)mName,
	(const char *)mCode	);
/*>>>>>FORMULA_DEBUGPRINT*/
}

#endif


#endif
