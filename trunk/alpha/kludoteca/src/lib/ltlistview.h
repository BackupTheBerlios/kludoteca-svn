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
#ifndef LTLISTVIEW_H
#define LTLISTVIEW_H

#include <qvbox.h>
#include <qhbuttongroup.h>
#include <kpushbutton.h>
#include <klistview.h>

class LTListView;

/**
 * Esta clase es la base de una lista
 * @short Clase base para listas.
 * @author CetiSoft
 * @todo 
 * - Agregar una forma de añadir titulo e hijos
*/
class LTListView : public QVBox
{
	Q_OBJECT
	public:
		enum Button { NoButton = 0, ButtonAdd, ButtonDel, ButtonModify, ButtonQuery };
    		
		
		/**
		 * Constructor por defecto
		 */
		LTListView(QWidget *parent = 0, const char *name = 0);
		
		/**
		 * Constructor que recibe como argumentos los botones que se desean. (en orden)
		 */
		LTListView(Button button1 = NoButton, Button button2 = NoButton, Button button3 = NoButton, Button button4 = NoButton, QWidget *parent = 0, const char *name = 0);
		~LTListView();
		
		/**
		 * Esta funcion crea los botones
		 */
		void makeButtons(Button button1, Button button2, Button button3, Button button4);
		
		/**
		 * Esta funcion crea la lista
		 */
		void makeList();
		
		/**
		 * Obtiene el listview
		 */
		KListView *getListView();
		
	private:
		KListView *m_listView;
		QHButtonGroup *m_buttons;

};

#endif
