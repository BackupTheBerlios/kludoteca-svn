/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkconfig.h Config include
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
#ifndef RTKCONFIG_H
#define RTKCONFIG_H


#define RTK_VERSION "0.1-beta"

// Increase the value of the following constants to increase the debug output
#ifdef QT_NO_DEBUG
# define DEBUG_RTK 0
# define DEBUG_RTKINPUT 0
# define DEBUG_RTKOUTPUT 0
#else
# define DEBUG_RTK 1
# define DEBUG_RTKINPUT 0
# define DEBUG_RTKOUTPUT 0
#endif
#endif // RTKCONFIG_H

