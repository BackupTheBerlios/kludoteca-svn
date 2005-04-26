/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtknamespace.cpp RTK namespace
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

#include <qstringlist.h>
#include <qfile.h>

#include "rtknamespace.h"

/**
    \class RTK rtknamespace.h

    \brief The RTK class is a namespace for miscellaneous identifiers that need to be global-like.
	
	@author Santiago Capel Torres

    \ingroup misc
*/


int RTK::tokenize( QStringList& tokens, const QString& str, const QString& delim )
{
    int len = str.length();
    QString token = "";
    for( int index = 0; index < len; index++)
    {
        if ( delim.find( str[ index ] ) >= 0 )
        {
            tokens.append( token );
            token = "";
        }
        else
        {
            token += str[ index ];
        }
    }
    if ( token.length() > 0 )
    {
        tokens.append( token );
    }
    return tokens.count();
}

#include <qdir.h>
QString RTK::findInPath(const QString &path, const QString &file, const QString &cwd)
{
	if( QFile::exists(file) )
		return file;
	else {
		QStringList paths;
		if( RTK::tokenize(paths, path, ":") == 0 ) {
			if( !cwd.isEmpty() ) {
				QString subpath = cwd;
				if ( subpath[(int)subpath.length()-1] != '/' )
                	subpath += '/';
				subpath += file;
           		if( QFile::exists(subpath) )
					return subpath;
			}
		} else {
			for( QStringList::iterator it = paths.begin(); it!=paths.end(); ++it ) {
				QString subpath = *it;
				if( subpath[0] != '/' ) { // absolute dir
					if ( cwd[(int)cwd.length()-1] != '/' )
						subpath = cwd + "/" + subpath;
					else
						subpath = cwd + subpath;
				}
				if ( subpath[(int)subpath.length()-1] != '/' )
                	subpath += '/';
				subpath += file;
            	if( QFile::exists(subpath) )
					return subpath;
			}
		}
	}
	return file;
}	
