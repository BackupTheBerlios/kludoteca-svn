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

/**
 * Este es el formumario para añadir juegos
 * @short Formulario para añadir juegos
 * @author CetiSoft
 * @todo - Heredar de FormBase
*/
class FormAdminGame : public QVBox
{
	Q_OBJECT
	
	public:
		/**
		* Costructor por defecto
		 */
		FormAdminGame(QString title, QWidget *parent = 0, const char *name = 0);
		/**
		 * Destructor por defecto
		 */
		~FormAdminGame();
		
		/**
		* Cambia el titulo del formulario
		 */
		void setTitle(QString newTitle);
		
		/**
		* llena los campos del formulario
		 */
		void fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit);
		
	protected:
		QGridLayout *m_grid;
		
	public slots:
		//void clearFields();
		void done();
		
	private:
		
		QFrame *form;
		QHBox *buttons;
		
		QLabel *m_labelTitle, *m_labelExplanation, *m_labelNameGame, *m_labelDescriptionGame, *m_labelrulesGame, *m_labelNPlayerGame, *m_labelTypeGame, *m_labelCostUnit, *m_labelUnitTime, *m_labelTimeAdd;
		
		KLineEdit *m_nameGame;
		KTextEdit *m_descriptionGame, *m_rulesGame ;
		
		//FIXME: la unidad de tiempo adicional se captura por un combobox?
		
		KComboBox *m_typeGame, *m_unitTime, *m_timeAdd;
		KIntSpinBox *m_nPlayerGame;
		KDoubleNumInput *m_costUnit;
		KPushButton *m_done, *m_cancel;
		
		/**
		 * Crea el formulario
		 */
		void setupForm();
		
		/**
		 * Crea el el panel de los botones
		 */
		void setupButton();
};

#endif
