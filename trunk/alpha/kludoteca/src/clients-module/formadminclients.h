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
 
#ifndef FORMADMINCLIENTS_H
#define FORMADMINCLIENTS_H

#include <formbase.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <qhbuttongroup.h>
#include <klineedit.h>
#include <qlayout.h>

/**
 * Este es el formulario para añadir y administrar clientes
 * @short Añadir cliente
 * @author CetiSoft
*/
class FormAdminClients : public FormBase
{
	Q_OBJECT
	public:
		FormAdminClients(QWidget *parent = 0);
		~FormAdminClients();
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
		
	private:
		QGridLayout *m_layout;
		QFrame *m_container;
		QHButtonGroup *m_radioButtons;
		QRadioButton *m_male, *m_female;
		KPushButton *m_selectFace;
		
		void setupButtonsBox();
		void setupBox();
};

#endif
