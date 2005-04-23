/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
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
#ifndef LDTAPP_H
#define LDTAPP_H

#include <kapplication.h>
#include <kconfig.h>
#include <klocale.h>

/**
 * Esta clase simboliza la aplicación
 * @author David Cuadrado
*/

class LDTApp : public KApplication
{
	Q_OBJECT
	
	public:
		/**
		 * Constructor por defecto
		 */
    		LDTApp();
		
    		/**
		 * Destructor por defecto
		 */
		~LDTApp();
		
		/**
		 * Muestra el dialogo de inicializacion y configuracion del sistema.
		 */
		void firstDialog();
		
		/**
		 * Retorna el objeto de configuracion de session
		 * @param group 
		 * @return 
		 */
		KConfig *config(const QString &group = "General");
		
	private:
		/**
		 * Coloca los colores de la aplicacion
		 */
		void applyColors();
};

#define klapp static_cast<LDTApp*>(kapp)

#endif
