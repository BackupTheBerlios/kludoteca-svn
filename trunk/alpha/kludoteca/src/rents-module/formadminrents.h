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
#include <ktextedit.h>
#include <knuminput.h>


/**
clase para el manejo de lso torneos

@author Daniel Valencia - David Cuadrado
@mail dafevara@gmail.com
*/
class FormAdminRents : public FormBase
{
	
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
		void idTextEdit(int id);
		void setTextEditContent(const QString &pkey);	
	
	signals:
		void message2osd(const QString &msg);
		void changedTextEdit(int id);
		
	private:
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
		
	private:
		
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		KComboBox *m_comboClte, *m_comboGame;
		KCompletion *m_compClte, *m_compGame;
		KLResultSetInterpreter *m_rsinterpreter;
		KLXmlReader m_xmlreader;
		QXmlInputSource m_xmlsource;
		QGroupBox *m_cltgb, *m_gamegb, *m_rentInfogb;
		KTextEdit *m_cltte,*m_gamete;
		KIntSpinBox *m_hour, *m_min, *m_seg;
		KLineEdit *m_cltName, *m_cltId;
		int m_idTextEdit;
		
		
};

#endif
