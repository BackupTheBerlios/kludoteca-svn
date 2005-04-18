/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        	   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GAMESMODULE_H
#define GAMESMODULE_H

#include <kmdichildview.h>

/**
 * Esta clase contiene el widget principal del modulo de juegos
 * @short Widget principal de Games-Module
 * @author David Cuadrado
*/
class GamesModule : public KMdiChildView
{
	Q_OBJECT
	public:
		GamesModule(QWidget *parentWidget=0L, const char *name=0L, WFlags f=0);
		~GamesModule();
};

#endif
