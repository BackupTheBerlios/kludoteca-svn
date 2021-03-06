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
#ifndef LTLISTVIEW_H
#define LTLISTVIEW_H

#include <qvbox.h>
#include <qhbuttongroup.h>
#include <kpushbutton.h>
#include <klistview.h>
#include <kmdichildview.h>


class LTListView;

/**
 * Esta clase es la base para crear un widget con una lista y un panel de botones para el manejo de la misma, de esta clase se deben sobreescribir varios metodos, los cuales son:
 * 
 * getClickedItem(): El cual recibe el item de la lista que fue clickeado.
 * 
 * xButtonClicked(): Las acciones que se realizan cuando el boton @b x fue clickeado
 * 
 * y se debe crear el signal que se llame sendWidget(KMdiChildView *), la idea es conectar este signal al slot addModulePage(KMdiChildView *), y pasar el widget construido para ponerlo como vista en la ventana principal.
 * 
 * @short Clase base para listas.
 * @author David Cuadrado
 * @todo 
 * - Agregar una forma de a�adir titulo e hijos
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
		
	public slots:
		/**
		 * Esta funcion nos da el item que fue clickeado
		 */
		virtual void getClickedItem(QListViewItem *item) = 0;
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de adicionar
		 */
		virtual void addButtonClicked()  = 0;
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de borrar
		*/
		virtual void delButtonClicked() = 0;
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de modificar
		*/
		virtual void modifyButtonClicked() = 0;
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de consultar
		*/
		virtual void queryButtonClicked() = 0;
		
	signals:
		/**
		 * Este signal envia el widget para er puesto en la ventana principal
		 */
		virtual void sendWidget(KMdiChildView *) = 0;
	
	private:
		KListView *m_listView;
		QHButtonGroup *m_buttons;
		
		KPushButton *m_buttonAdd;
		KPushButton *m_buttonDel;
		KPushButton *m_buttonModify;
		KPushButton *m_buttonQuery;
};

#endif
