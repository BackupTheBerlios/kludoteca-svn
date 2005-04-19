/***************************************************************************
 *   Copyright (C) 2005 by Juliana Davila - David Cuadrado                                        *
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

#ifndef FORMTOURNAMENT_H
#define FORMTOURNAMENT_H

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
#include <knuminput.h>
#include <kdatepicker.h>
#include <kdatewidget.h>

#include "formbase.h"

class FormBase;

/**
@author Juliana Davila - David Cuadrado
*/
class FormTournament : public FormBase
{	
	Q_OBJECT

	public:
		/**
		 * Constructor por defecto
		 * @param parent 
		 * @return 
		 */
		FormTournament(QWidget *parent = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~FormTournament();
		/**
		 * Crea la forma
		 */
		void setupForm();
		/**
		 * Llena los campos del formulario
		 * @param nameTournament 
		 * @param nameGame 
		 * @param inscription 
		 * @param discount 
		 */
		void fillField(QString nameTournament, QString nameGame, double inscription, double discount);
	
	public slots:
		/**
		 * Reimplementado de LTListView, se activa cuando se presiona el boton de aceptar la accion
		 */
		void accept();
		/**
		 * Reimplementado de LTListview, se activa cuando se presiona el boton de cancelar la accion
		 */
		void cancel();
	
	private:
		
		QFrame *form;
		QGridLayout *m_grid;
		KLineEdit 	*m_nameTournament, 
				*m_nameGame,
				*m_valueInscrip,
				*m_discountInscrip;
		
		QLabel		
			*m_nameTourLabel,
			*m_nameGameLabel,
			*m_valueInscripLabel,
			*m_discountLabel,
			*m_roundsGame,
			*m_gamesPlayers,
			*m_dateBegin,
			*m_dateEnd;
		
		QGridLayout	*m_maingridLayout;
		KComboBox	*m_combox;
		
		KIntSpinBox *m_round, *m_gamesPair;//partidas por pareja
		KDatePicker *m_dateTournament;
		KDateWidget *m_endDate;
		
	private:		
		/**
		 * Crea el cuadro de botones
		 */
		void setupButtonsBox();
		/**
		 * Crea la caja
		 */
		void setupBox();	

};

#endif
