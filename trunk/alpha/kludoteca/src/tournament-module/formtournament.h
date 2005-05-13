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
		
		/**
		 * Pone el nombre del torneo
		 * @param name 
		 */
		void setTournamentName(const QString &name);
		/**
		 * Pone el numero de rondas
		 * @param rounds 
		 */
		void setRounds(const QString &rounds);
		/**
		 * Pone las rondas por pareja
		 * @param rounds 
		 */
		void setRounds4pair(const QString &rounds);
		/**
		 * Pone el precio del inscripcion
		 * @param price 
		 */
		void setPrice(const QString &price);
		/**
		 * Pone el posible descuento
		 * @param discount 
		 */
		void setDiscount(const QString &discount);
		/**
		 * Pone la fecha de inicio del torneo
		 * @param date 
		 */
		void setInitDate(const QDate &date);
		/**
		 * Pone la fecha de finalizacion del torneo
		 * @param date 
		 */
		void setEndDate(const QDate &date);
		
		/**
		 * Obtiene el nombre del torneo
		 * @return 
		 */
		QString getTournamentName();
		/**
		 * Obtiene las rondas
		 * @return 
		 */
		QString getRounds();
		/**
		 * Obtiene las rondas por pareja
		 * @return 
		 */
		QString getRounds4pair();
		/**
		 * Obtiene el precio del incripcion
		 * @return 
		 */
		QString getPrice();
		/**
		 * Obtiene el posible descuento
		 * @return 
		 */
		QString getDiscount();
		/**
		 * Obtiene la fecha de inicio del torneo
		 * @return 
		 */
		QString getInitDate();
		/**
		 * Obtiene la fecha de finalizacion del torneo
		 * @return 
		 */
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
		/**
		 * Indica que la fecha de inicio fue cambiada
		 * @param date 
		 */
		void initDateChanged(QDate date);
		
	signals:
		/**
		 * Envia un mensaje para ser puesto en el OSD
		 * @param osd 
		 */
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
