/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtknamespace.h RTK namespace
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
#ifndef RTKNAMESPACE_H
#define RTKNAMESPACE_H

#include <qdatetime.h>
#include <qcolor.h>
#include <qstringlist.h>
#include <qvaluelist.h>

#include "rtkconfig.h"


namespace RTK
{

typedef QDate Date;
typedef QTime Time;
typedef QDateTime DateTime;
typedef QString String;
typedef QColor Color;

typedef double Measure;

enum SectionType {
        SectionReportHeader,
        SectionReportFooter,
        SectionPageHeader,
        SectionPageFooter,
        SectionGroupHeader,
        SectionGroupFooter,
        SectionDetails
};

enum AggregateType {
        AggNone,
        AggCount,
        AggDistinctCount,
        AggSum,
        AggDistinctSum,
		AggAvg,
		AggDistinctAvg,
        AggStdDv,
        AggDistinctStdDv,
        AggDistinctVariance,
        AggVariance
};

enum AlignmentType {
        AlignAuto=0,
        AlignLeft,
        AlignCenter,
        AlignRight,
        AlignJustify,
		AlignNoWordWrap,
        AlignTop,
        AlignMiddle,
        AlignBottom
};

enum BorderStyle {
        BorderNone = 0,
        BorderSolid,
        BorderDash,
        BorderDot,
        BorderDashDot,
        BorderDashDotDot,
        Raised3D,
        Lowered3D
};

enum AdjustmentType {
        AdjustTrim =       0,
        AdjustGrow =       1 << 1,
        AdjustNone =       1 << 2,
        AdjustReduceFont = 1 << 3,
        AdjustShrink     = 1 << 4
};


const Measure dotsperinch = 81;
const Measure charsperinch = 10;
const Measure cmperinch = 2.545;
const Measure mmperinch = cmperinch*10;
const Measure dotspercm = dotsperinch/cmperinch;
const Measure dotsperchar = dotsperinch/charsperinch;

typedef struct {
        const char *name;
        Measure sizex;
        Measure sizey;
} PaperSize;


enum UnitsType {
        chars=0,
        dots=1,
        inches=2,
        cm=3,
        mm=4,
        p100=5,
        defaultunit /*always the last one*/
};

enum PaperType {
        A4, B5, Letter, Legal, Executive,
        A0, A1, A2, A3, A5, A6, A7, A8, A9, B0, B1,
        B10, B2, B3, B4, B6, B7, B8, B9, C5E, Comm10E,
        DLE, Folio, Ledger, Tabloid, Custom, NPageSize = Custom
};

int tokenize( QStringList& tokens, const QString& str, const QString& delim );
QString findInPath(const QString &path, const QString &file, const QString &cwd = QString::null);

}; 
#endif // RTKNAMESPACE_H
