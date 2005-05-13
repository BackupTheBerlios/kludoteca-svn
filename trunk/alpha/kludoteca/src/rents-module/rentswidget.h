/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                           	   *
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
#ifndef RENTSWIDGET_H
#define RENTSWIDGET_H

#include "ltlistview.h"

/**
 * Esta clase contiene el widget principal del modulo de prestamos
 * @author David Cuadrado
*/
class RentsWidget : public LTListView
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param button1 
		 * @param button2 
		 * @param button3 
		 * @param button4 
		 * @param parent 
		 * @return 
		 */
		RentsWidget(Button button1 = NoButton, Button button2 = NoButton, Button button3 = NoButton, Button button4 = NoButton, QWidget *parent = 0);
    		~RentsWidget();
		/**
		 * Reimplementado de LTListView, sirve para llenar la lista
		 */
		void fillList();
		
		void slotFilter(const QString &filter);
		
		void addItem(const QString &pkey);
		
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
