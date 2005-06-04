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
#ifndef FORMRENTSDEBTS_H
#define FORMRENTSDEBTS_H

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
@author Daniel Valencia
*/
class FormRentsDebts : public FormBase
{
	Q_OBJECT
	public:
		FormRentsDebts(FormBase::Type t,QWidget* parent=0, const char* name=0);
		
		~FormRentsDebts();
		void setupBox();
		void setupButtonsBox();
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
	signals:
		void message2osd(const QString &msg);
		
	private:	
		void setupForm();
	private:
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		KLTable *m_table;
	
};

#endif
