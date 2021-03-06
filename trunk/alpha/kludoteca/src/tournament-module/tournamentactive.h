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
 *************************************************************************/
 
#ifndef TOURNAMENTACTIVE_H
#define TOURNAMENTACTIVE_H

#include "ltlistview.h"
#include <qvbox.h>

#include "formtournament.h"

/**
 * En este widget tenemos los torneos activos
 * @author David Cuadrado
*/
class TournamentActive : public LTListView
{
	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
    		TournamentActive(QWidget *parent = 0);
		
		/**
		 * Destructor por defecto
		 */
    		~TournamentActive();
		
		void addItem(const QString &pkey);
		
		void slotFilter(const QString &filter);
		
		/**
	 	 * Esta funcion debe implementarse para llenar la lista.
		 */
		void fillList();
		
	signals:
		void tournamentModified();
			
	public slots:
		/**
		 * Esta funcion nos da el item que fue clickeado
		 */
		void getClickedItem(QListViewItem *item);
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de adicionar
		 */
		void addButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de borrar
		 */
		void delButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de modificar
		 */
		void modifyButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de consultar
		 */
		void queryButtonClicked();
};

#endif
