/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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

#ifndef GAMESLIST_H
#define GAMESLIST_H

#include <qvbox.h>
#include <qhbuttongroup.h>
#include <klistview.h>
#include <kpushbutton.h>
#include <qlayout.h>
#include <kmdichildview.h>

// Std lib
#include <iostream>

// Own lib!
#include "ltlistview.h"
#include "formadmingame.h"

class LTListView;

/**
 * Esta clase es un toolWindow que visualiza los juegos que hay en la ludoteca, esta provee un mecanismo para gestionar los juegos, permite añadir y eliminar los juegos, asi como consultar la información de un juego determinado.
 * @short Lista de juegos
 * @author CetiSoft
*/
class GamesList : public LTListView
{
	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
		GamesList(Button button1 = NoButton, Button button2 = NoButton, Button button3 = NoButton, Button button4 = NoButton, QWidget *parent = 0);
		
		/**
		 * Destructor por defecto.
		 */
		~GamesList();

		/**
		 * Crea la lista
		 */
		void setupListView();
		
	public slots:
		/**
		 * Agrega un juego a la lista.
		 */
		void addGame(const QString &game);
		
		/**
		 * Este slot se encarga de emitir el signal query(QString name)
		 */
		void getClickedItem(QListViewItem *item);
		
		/**
		 * Este es la accion que se realiza cuando se pulsa el primer boton
		 */
		void addButtonClicked();
		
		/**
		 * Este es la accion que se realiza cuando se pulsa el segundo boton
		 */
		void delButtonClicked();
		
		/**
		 * Este es la accion que se realiza cuando se pulsa el tercer boton
		 */
		void modifyButtonClicked();
		
		/**
		 * Este es la accion que se realiza cuando se pulsa el cuarto boton
		 */
		void queryButtonClicked();
		
	signals:
		/**
		 * Este signal envia el string del item que se desea consultar
		 */
		void query(QString &name);
		
		/**
		 * Este signal envia el widget para er puesto en la ventana principal
		 */
		void sendWidget(KMdiChildView *);
		
	private:
		QStringList m_gameCategories;
		
};

#endif
