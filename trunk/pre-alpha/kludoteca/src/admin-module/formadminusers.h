/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
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
#ifndef FORMADMINUSERS_H
#define FORMADMINUSERS_H

#include <formbase.h>
#include <klineedit.h>
#include <kcombobox.h>
#include <qhgroupbox.h>
#include <qlayout.h>

/**
@author David Cuadrado
*/
class FormAdminUsers : public FormBase
{
	Q_OBJECT

	public:
		FormAdminUsers(QWidget *parent = 0);
		~FormAdminUsers();
		void setupForm();
	
	public slots:
		void accept();
		void cancel();
	
	private:
		
		KLineEdit	*m_loginLineEdit, 
				*m_passwdLineEdit,
				*m_repasswdLineEdit,
				*m_nameLineEdit,
				*m_idLineEdit,
				*m_addresLineEdit,
				*m_phoneLineEdit,
				*m_mailLineEdit;
		
		QLabel		*m_loginLabel,
				*m_passwdLabel,
				*m_repasswdLabel,
				*m_nameLabel,
				*m_idLabel,
				*m_addresLabel,
				*m_phoneLabel,
				*m_mailLabel;
		
		QGridLayout	*m_maingridLayout
				/**m_gridPersonal,
				*m_grid*/;
		KComboBox	*m_combox;
		
		QHGroupBox	*m_hbgPersonal,
				*m_hbgSysInfo,
				*m_hbgPermissions;
				
		void setupButtonsBox();
		void setupBox();
};

#endif
