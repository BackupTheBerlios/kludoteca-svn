/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado, juliana Davila                                     *
 *   krawek@gmail.com   julianad@univalle.edu.co                                     	   *
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
#include <qstringlist.h>

#include "formbase.h"

/**
 * Este es el formumario para añadir juegos
 * @short Formulario para añadir juegos
 * @author David Cuadrado Juliana DAvila
 * @todo - Heredar de FormBase
*/
class FormAdminGame : public FormBase
{
	Q_OBJECT
	
	public:
		/**
		* Costructor por defecto
		 */
		FormAdminGame(KLDatabase *db, QWidget *parent = 0, const char *name = 0);
		
		/**
		 * Destructor por defecto
		 */
		~FormAdminGame();
		
		/**
		* llena los campos del formulario
		 */
		void fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit);
		
		void formQuery(const QString &idGame );
		void formDelete(const QString &idGame);
		void formModify();//const QString &idGame);
		
		/**
		 *  Funcion que retorna un qstring del nombre del juego
		 * @return m_nameGame
		 */
		QString getGameName();
		
		/**
		 * Funcion que retorna un qstring de la descripcion del juego
		 * @return 
		 */
		QString getDescriptionGame();
		
		/**
		 * Funcion que retorna un qstring de las reglas del juego
		 * @return 
		 */
		QString getRulesGame();
		
		/**
		 * Funcion que retorna un qstring del tipo del juego
		 * @return 
		 */
		QString getTypeGame();
		
		QString getStateGame();
		
		/**
		 *  Funcion que retorna un qstring de la referencia del juego
		 * @return 
		 */
		QString getReferenceGame();
		
		/**
		 *  Funcion que retorna un qstring que indica la unidad de tiempo en que se van a prestar el juego
		 * @return 
		 */
		QString getTimeUnit();
		
		QString getTimeUnitAdd();
		
		/**
		 * Funcion que retorna un int del numero de jugadores minimo por ese juego
		 * @return 
		 */
		int getMinPlayers();
		
		/**
		 * Funcion que retorna un int del numero de jugadores maximo por ese juego
		 * @return 
		 */
		int getMaxPlayers();
		
		/**
		 * Funcion que retorna un double que indica el valor de la unidad de tiempo para ese juego
		 * @return 
		 */
		double getCostUnitTime();
		
		/**
		 * Funcion que retorna un double que indica el valor de la unidad de tiempo adicional para ese juego
		 * @return 
		 */
		double getCostTimeAdditional();
		
		/**
		 * Funcion encargada de colocarle un nombre al juego
		 * @param name 
		 */
		void setGameName(const QString &name);
		
		/**
		 * Funcion encargada de colocar la descripcion del juego
		 * @param description 
		 */
		void setDescriptionGame(const QString &description);
		
		/**
		 * Funcion encargada de colocar las reglas del juego
		 * @param rules 
		 */
		void setRulesGame(const QString &rules);
		
		/**
		 * Funcion encargada de colocar el tipo de juego
		 * Se pueden añadir mas tipos de juego aqui, el orden en que esta hasta el momento es:
		 * 0 - "Board"
		 * 1 - "Video"
		 * 2 - "Cards"
		 * @param type 
		 */
		void setTypeGame(const QString &type, int index);
		
		void setStateGame(const QString &state, int index);
		
		/**
		 * Funcion encargada de llenar el campo de la referencia o codigo del juego
		 * @param reference 
		 */
		void setReferenceGame(const QString &reference);
		
		/**
		 *  Funcion encargada de colocar la unidad de tiempo
		 * Se pueden añadir mas tipos de unidades de tiempo el orden hasta ahora es
		 * "minutes" - 0
		 * "hours" - 1)
		 * @param unitTime 
		 */
		void setTimeUnit(const QString &unitTime, int  index);
		
		void setUnitTimeAdd(const QString &unitTimeAdd, int index );
		
		/**
		 * Funcion encargada de colocar el numero minimo de jugadores 
		 * @param numMinPlayers 
		 */
		void setMinPlayers(const int &numMinPlayers);
		
		/**
		 * Funcion encargada de colcar el numero maximo de jugadores
		 * @param numMaxPlayers 
		 */
		void setMaxPlayers(const int &numMaxPlayers);
		
		/**
		 * Funcion encargada de colocar el costo por unidad de tiempo
		 * @param costTime 
		 */
		void setCostUnitTime(const double &costTime);
		
		/**
		 * Funcion encargada de colocar el costo por unidad de tiempo adicional
		 * @param costAditional 
		 */
		void setCostTimeAdditional(const double &costAditional);
		
		
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
		
		/**
		 * Limpia el formulario
		 */
		void clean();
		
	private:
		
		QFrame *form;
		
		QLabel *m_labelNameGame, *m_labelDescriptionGame, *m_labelrulesGame, *m_labelNMinPlayerGame,*m_labelNMaxPlayerGame,  *m_labelTypeGame, *m_labelCostUnit, *m_labelUnitTime, *m_labelTimeAdd, *m_labelReference,  *m_imagen, *m_labelStateGame;
		
		KLineEdit *m_nameGame, *m_referenceGame;
		KTextEdit *m_descriptionGame, *m_rulesGame ;
		
		//FIXME: la unidad de tiempo adicional se captura por un combobox?
		
		KComboBox *m_typeGame, *m_unitTime, *m_unitTimeAdd, *m_stateGame ;
		KIntSpinBox *m_nMinPlayerGame, *m_nMaxPlayerGame, *m_costUnit, *m_timeAdd;
		
	private:
		/**
		 * Crea el formulario
		 */
		void setupForm();
};

#endif
