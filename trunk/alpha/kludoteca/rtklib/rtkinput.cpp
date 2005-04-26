/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinput.cpp RTK input object
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

#include "rtkinput.h"
#include "rtkmoney.h"

using namespace RTK;

InputField *Input::getInputField(const String &name) const
{
  for( uint i=0; i<mInputFields.size(); i++ ) {
    if( mInputFields[i]->getName() == name )
      return mInputFields[i];
  }
  return 0;
}

int Input::insertInputField(InputField *inputfield)
{
    mInputFields.push_back(inputfield);
    return mInputFields.size();
}


