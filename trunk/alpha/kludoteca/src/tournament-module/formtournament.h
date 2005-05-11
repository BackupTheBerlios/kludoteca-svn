/***************************************************************************
 *   Copyright (C) 2005 by Juliana Davila - David Cuadrado                 *
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
 * Esta clase representa el formulario de torneos
 * @author Juliana Davila - David Cuadrado
 * @TODO
 * - Verificar que la fecha de inicio sea al menos la actual
 * - Verificar que la fecha de fin sea obligatoriamente mayour que la de inicio
 * - Verificar que el juego elegido este disponible
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
		FormTournament(Type t, QWidget *parent = 0);
		
		/**
		 * Destructor
		 * @return 
		 */
		~FormTournament();
		/**
		 * Crea la forma
		 */
		void setupForm();
		
		void setTournamentName(const QString &name);
		void setRounds(const QString &rounds);
		void setRounds4pair(const QString &rounds);
		void setPrice(const QString &price);
		void setDiscount(const QString &discount);
		void setInitDate(const QDate &date);
		void setEndDate(const QDate &date);
		
		QString getTournamentName();
		QString getRounds();
		QString getRounds4pair();
		QString getPrice();
		QString getDiscount();
		QString getInitDate();
		QString getEndDate();
		
	
	public slots:
		/**
		 * Reimplementado de LTListView, se activa cuando se presiona el boton de aceptar la accion
		 */
		void accept();
		/**
		 * Reimplementado de LTListview, se activa cuando se presiona el boton de cancelar la accion
		 */
		void cancel();
		
		/**
		 * Limpia el formulario
		 */
		void clean();
		
	private slots:
		void initDateChanged(QDate date);
		
	signals:
		void message2osd(const QString &osd);
	
	private:
		QFrame *m_form;
		QGridLayout *m_grid;
		
		QGridLayout	*m_maingridLayout;
		KComboBox	*m_combox, *m_nameGame;
		
		KIntSpinBox *m_round, *m_gamesPair;//partidas por pareja
		KDatePicker *m_dateTournament;
		KDateWidget *m_endDate;
		
		HashLineEdit m_lineEdits;
		
	private:		
		/**
		 * Crea el cuadro de botones
		 */
		void setupButtonsBox();
		
		/**
		 * Crea la caja
		 */
		void setupBox();
		
		/**
		 * Busca en la base de datos los nombres de los juegos disponibles
		 */
		void setupGames();
		
		
		/**
		 * Retorna el codigo del juego dependiendo de su nombre
		 * @return 
		 */
		QString gameName2code(const QString &gamename);

};

#endif
