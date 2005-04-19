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

#ifndef FORMADMINGAME_H
#define FORMADMINGAME_H

#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qstring.h>
#include <qframe.h> 
#include <qlayout.h>

#include <klineedit.h>
#include <ktextedit.h>
#include <kcombobox.h>
#include <knuminput.h>
#include <kpushbutton.h>

#include "formbase.h"

/**
 * Este es el formumario para añadir juegos
 * @short Formulario para añadir juegos
 * @author David Cuadrado
 * @todo - Heredar de FormBase
*/
class FormAdminGame : public FormBase
{
	Q_OBJECT
	
	public:
		/**
		* Costructor por defecto
		 */
		FormAdminGame(QWidget *parent = 0, const char *name = 0);
		
		/**
		 * Destructor por defecto
		 */
		~FormAdminGame();
		
		/**
		* llena los campos del formulario
		 */
		void fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit);
		
	protected:
		QGridLayout *m_grid;
		
	public slots:
		/**
		 * Reimplementado de LTListView, se activa cuando se presiona el boton de aceptar la accion
		 */
		void accept ();
		/**
		 * Reimplementado de LTListview, se activa cuando se presiona el boton de cancelar la accion
		 */
		void cancel ();
		
	private:
		
		QFrame *form;
		
		QLabel *m_labelNameGame, *m_labelDescriptionGame, *m_labelrulesGame, *m_labelNPlayerGame, *m_labelTypeGame, *m_labelCostUnit, *m_labelUnitTime, *m_labelTimeAdd;
		
		KLineEdit *m_nameGame;
		KTextEdit *m_descriptionGame, *m_rulesGame ;
		
		//FIXME: la unidad de tiempo adicional se captura por un combobox?
		
		KComboBox *m_typeGame, *m_unitTime, *m_timeAdd;
		KIntSpinBox *m_nPlayerGame;
		KDoubleNumInput *m_costUnit;
		
	private:
		/**
		 * Crea el formulario
		 */
		void setupForm();
};

#endif
