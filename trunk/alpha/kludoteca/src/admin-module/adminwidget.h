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
#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include "lttoolbox.h"
#include "adminusers.h"
#include "admindatabase.h"
#include "adminlogs.h"

/**
 * Esta clase contiene el modulo de administraci�
 * @short Modulo de administrador
 * @author David Cuadrado
*/
class AdminWidget : public LTToolBox
{
	Q_OBJECT

	public:
		/**
		 * Contructor por defecto
		 */
    		AdminWidget(QWidget *parent = 0);
		/**
		 * Destructor por defecto
		 */
		~AdminWidget();
		
		
	signals:
		/**
		 * Este signal envia el widget para er puesto en la ventana principal
		 */
		void sendWidget(QWidget *, const QString &title);
		
		void message2osd(const QString &);
		
	private:
		/**
		 * Esta funcion crea los diferentes tabs que contiene el modulo administrador
		 */
		void setupTabs();
	private:
		AdminUsers *m_adminUsers;
		AdminDatabase *m_adminDatabase;
		AdminLogs *m_adminLogs;

};

#endif
