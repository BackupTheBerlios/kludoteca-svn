/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                        	           *
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
 
#ifndef FORMADMINUSERS_H
#define FORMADMINUSERS_H

#include <formbase.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <qhbuttongroup.h>
#include <qvbuttongroup.h>
#include <qvgroupbox.h>
#include <klineedit.h>
#include <qlayout.h>
#include <qscrollview.h>
#include <qvalidator.h>
#include <qhbox.h>
#include <qcheckbox.h>

class QRegExp;

/**
 * Este es el formulario para añadir y administrar usuarios de la aplicacion
 * @short Añadir usuarios
 * @author David Cuadrado
*/
class FormAdminUsers : public FormBase
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param parent 
		 * @return 
		 */
		FormAdminUsers(KLDatabase *db, QWidget *parent = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~FormAdminUsers();
		/**
		 * Crea la forma
		 */
		void setupForm();
		
		QString getIdentification();
		QString getLogin(); 
		QString getPassword(); 
		QString getFirstName(); 
		QString getLastName(); 
		QString getSex(); 
		QString getAddress(); 
		QString getPhone(); 
		QString getEmail(); 
		QString getPermissions();
		
		void setIdentification(const QString &ident);
		void setLogin(const QString &login); 
		void setPassword(const QString &pass); 
		void setFirstName(const QString &fname); 
		void setLastName(const QString &lname); 
		void setSex(const QString &sex); 
		void setAddress(const QString &addrs); 
		void setPhone(const QString &phone); 
		void setEmail(const QString &email); 
		void setPermissions(const QString &perms);
		
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
		QVBox *m_secondCol;
		
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		QVButtonGroup *m_radioButtons;
		QRadioButton *m_male, *m_female;
		HashLineEdit m_lineEdits;
		
		QVButtonGroup *m_permsBox;
		QCheckBox  *m_adminp, *m_gamesp, *m_clientsp, *m_rentsp, *m_tournamentsp;
	
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
};

#endif
