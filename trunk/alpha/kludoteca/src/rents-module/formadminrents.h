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
#ifndef FORMADMINRENTS_H
#define FORMADMINRENTS_H

#include "formbase.h"
#include <qradiobutton.h>
#include <qhbuttongroup.h>
#include <qvbuttongroup.h>
#include <qvgroupbox.h>
#include <qscrollview.h>
#include <qcheckbox.h>
#include <kcombobox.h>
#include <kcompletion.h>
#include "klxmlreader.h"
#include "kldatabase.h"
#include "klresultsetinterpreter.h"
#include "kltable.h"
#include <knuminput.h>
#include "klquery.h"
#include <qslider.h>
#include "klcalc.h"


/**
clase para el manejo de los torneos

@author Daniel Valencia - David Cuadrado
@mail dafevara@gmail.com
*/
class FormAdminRents : public FormBase
{
	Q_OBJECT
	public:
		FormAdminRents(FormBase::Type t, QWidget* parent = 0);
		~FormAdminRents();
		void setupForm();
		
	public slots: 
		/**
	 	 * Esta es la accion predeterminada cuando se presiona el boton aceptar
		 */
		void accept();
		/**
		 * Esta es la accion predeterminada cuando se presiona el boton cancelar
		 */
		void cancel();
		
		/**
		 * Limpia el formulario
		 */
		void clean();
		void setCltTable(const QString &pkey);	
		void setGameTable(const QString &pkey);
		void clickedItemClte(int row, int col);
		void clickedItemGame(int row, int col);
		void setUnits(int value);
		void setAddUnits(int value);
		void setHourValue(const QString &value);
		void setAddHourValue(const QString &value);
		
	signals:
		void message2osd(const QString &msg);
		void changedTextEdit(int id);
		void inserted(const QStringList &qsl);
		
	public:
		/**
		 * Crea los botones
		 */
		void setupButtonsBox();
		
		/**
		 * Crea la caja principal
		 */
		void setupBox();
		
		/**
		 * Crea la caja de permisos
		 */
		
		void setupPermissionsBox();
		QString getSystemDateTime();
		
		QString getCltName(); 
		QString getCltId(); 
		QString getHourValue();
		QString getAddHourValue(); 
		QString	getGameSerial(); 
		QString getGameName();
		QString getActiveValue();
		QString getCostOfRent();
		
		void setCltName(const QString &name); 
		void setCltId(const QString &id); 
		 
		void setGameSerial(const QString &serial); 
		void setGameName(const QString &gamename);
		void setActiveValue(const QString &value);
		void setCostOfRent(const QString &cost);
		void rentDate(const QString &date);
		void rentHour(const QString &hour);
		void costUnit(const QString &cost);
		void costUnitAdd(const QString &cost);
		
		
	private:
		
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		KComboBox 	*m_comboClte,
				*m_comboGame;
		
		KCompletion 	*m_compClte, 
				*m_compGame;
		
		KLResultSetInterpreter *m_rsinterpreter;
		
		KLXmlReader m_xmlreader;
		
		QXmlInputSource m_xmlsource;
		
		QVGroupBox 	*m_cltgb, 
				*m_gamegb;
		QGroupBox *m_rentInfogb;
		
		KLTable *m_cltTable,
			*m_gameTable;
		
		QSlider *m_timeUnits, 
			*m_addTimeUnits;
		
		KLineEdit 	*m_cltName, 
				*m_cltId, 
				*m_hourValue,
				*m_addHourValue, 
				*m_gameSerial, 
				*m_gameName,
				*m_costRent;
		QString m_time,
			m_setGameSerial,
			m_rentDate,
			m_rentHour,
			m_costForUnit,
			m_costForUnitAdd;
		
		HashLineEdit m_hashRentFields;
		QHButtonGroup *m_radioButtons;
		QRadioButton *m_rbNotBanned, *m_rbBanned;
		bool m_actValueChanged, m_costRentChanged;
		KLCalc m_calc;
		
};

#endif
