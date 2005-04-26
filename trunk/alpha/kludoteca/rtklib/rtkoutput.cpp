/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkoutput.cpp RTK output object
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

#include "rtkoutput.h"
#include <qstring.h>

using namespace RTK;

PaperSize Output::mPaperSizes[] = {
                       {"A4", 210, 297},
                       {"B5", 182, 257},
                       {"Letter", 216, 279},
                       {"Legal", 216, 356},
                       {"Executive", 191, 254},
                       {"A0", 841, 1189},
                       {"A1", 594, 841},
                       {"A2", 420, 594},
                       {"A3", 297, 420},
                       {"A5", 148, 210},
                       {"A6", 105, 148},
                       {"A7", 74, 105},
                       {"A8", 52, 74},
                       {"A9", 37, 52},
                       {"B0", 1030, 1456},
                       {"B1", 728, 1030},
                       {"B10", 32, 45},
                       {"B2", 515, 728},
                       {"B3", 364, 515},
                       {"B4", 257, 364},
                       {"B6", 128, 182},
                       {"B7", 91, 128},
                       {"B8", 64, 91},
                       {"B9", 45, 64},
                       {"C5E", 163, 229},
                       {"Comm10E", 105, 241}, // US Common #10 Envelope
                       {"DLE", 110, 220},
                       {"Folio", 210, 330},
                       {"Ledger", 432, 279},
                       {"Tabloid", 279, 432}
               };

void Output::fixPaperSize()
{
        if( getPaperType() >= Custom && (getSizeX()<=0 || getSizeY()<=0) )
                setPaperType(A4);
#if DEBUG_RTKOUTPUT > 0		
        qDebug("RTK:Output:Setting paper size:%f, %f", getSizeX(), getSizeY());
#endif		
}

Measure Output::setPosX(Measure newx)
{
        Measure oldx = mCurrX;
        mCurrX = newx;
        return oldx;
}

Measure Output::setPosY(Measure newy)
{
        Measure oldy = mCurrY;
        mCurrY = newy;
        return oldy;
}
