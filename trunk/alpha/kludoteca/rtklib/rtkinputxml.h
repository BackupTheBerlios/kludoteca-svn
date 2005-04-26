/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkinputxml.h RTK standard xml input object
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
#ifndef RTKINPUTXML_H
#define RTKINPUTXML_H

#ifndef RTK_H
#include "rtk.h"
#endif
#include <qxml.h>


namespace RTK
{

class InputXml : public Input
{
/*<<<<<INPUTXML_CONSTRUCTOR*/
public:
        InputXml(String name = String(), String driver = String())
                        :Input(name, driver)
/*>>>>>INPUTXML_CONSTRUCTOR*/
        {};

        ~InputXml();

        virtual bool init();
        virtual bool next();
        virtual Variant getValue(uint i) const;

/*<<<<<INPUTXML_GETSET*/
public:
/*>>>>>INPUTXML_GETSET*/
private:
        int fieldPos(const String &name) const;

        QValueList<String>mFieldNames;
        QValueList<QVariant::Type>mFieldTypes;

};

}; // namespace

#endif


