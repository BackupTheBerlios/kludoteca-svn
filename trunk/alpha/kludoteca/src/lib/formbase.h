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
#ifndef FORMBASE_H
#define FORMBASE_H

#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qstring.h>
#include <qframe.h> 
#include <qlayout.h>

#include <kpushbutton.h>

/**
 * Clase base para crear formularios
 * @author CetiSoft
*/
class FormBase : public QVBox
{
	Q_OBJECT
		
	public:
		/**
		* Costructor por defecto.
		 */
		FormBase( QWidget *parent = 0, const char *name = 0);
		/**
		 * Destructor por defecto.
		 */
		~FormBase();
		/**
		* Cambia el titulo del formulario.
		 */
		void setTitle(QString newTitle);
		/**
		 * Cambia la explicaion del formulario.
		 */
		void setExplanation(QString newExplanation);
		/**
		 * Crea el formulario.
		 */
		virtual void setupForm() = 0;
		/**
		 * Crea el panel de los botones con texto por defecto.
		 */
		void setupButton();
		/**
		* Cambia el texto del primer boton
		 */
		void setTextButtonOne(QString newText);
		/**
		 * Cambia el texto del segundo boton
		 */
		void setTextButtonTwo(QString newText);
		
		/**
		 * Cambia el texto del tercer boton
		 */
		void setTextButtonThree(QString newText);
		
	public slots:
		virtual void accept() = 0;
		virtual void cancle() = 0;
		virtual void modify() = 0;
		
	private:
		QHBox *m_buttons;
		QLabel *m_labelTitle, *m_labelExplanation;
		KPushButton *m_accept, *m_cancel, *m_modify;
};

#endif
