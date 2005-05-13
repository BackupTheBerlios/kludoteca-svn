/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                 	   *
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
#ifndef PARTICIPANTSLIST_H
#define PARTICIPANTSLIST_H

#include <ltlistview.h>
#include "formparticipants.h"

/**
 * En este widget manejamos la lista de participantes en torneos
 * @author David Cuadrado
*/
class ParticipantsList : public LTListView
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		ParticipantsList( QWidget *parent = 0, const char *name = 0);

		/**
		 * Destructor
		 * @return 
		 */
		~ParticipantsList();
		
		/**
		 * Llena la lista, esta funcion es reimplementada de LTListView
		 */
		void fillList();
		
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
		
		/**
		 * Adiciona un item a la lista consultando la base de datos.
		 * @param table 
		 * @param pkey 
		 */
		void addItem(const QString &pkey);
		
		
		/**
		 * Filtra ( reimplementado )
		 * @param filter 
		 */
		void slotFilter(const QString &filter);
		
		
		/**
		 * Actualiza un item de la lista basandose en la llave recibida
		 * @param  
		 */
		void updateItem(const QString &pkey);
		
};

#endif
