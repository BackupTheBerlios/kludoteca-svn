/***************************************************************************
 *   Copyright (C) 2005 Max Howell <max.howell@methylblue.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CRASH_H
#define CRASH_H

#include <kcrash.h> //for main.cpp
#include <iostream>

/**
* @author Max Howell (Adaptado a KLudoteca por David Cuadrado)
* @short The KLudoteca crash-handler
*
* I'm not entirely sure why this had to be inside a class, but it
* wouldn't work otherwise *shrug*
*/
class Crash
{
	public:
		/**
		 * Funcion que maneja las excepciones cuando estas se producen
		 * @param signal 
		 */
		static void crashHandler( int signal );
};

#endif
