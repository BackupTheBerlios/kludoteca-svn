/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                           	   *
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
#ifndef VALIDATEUSER_H
#define VALIDATEUSER_H

#include <kdialogbase.h>
#include <qlayout.h>
#include <qvbox.h>
#include <klineedit.h>

#include "kldatabase.h"
#include "ldtapp.h"

class UserPage;
class DatabasePage;

/**
 * Esta clase valida los usuarios.
 * En esta clase se definen los niveles de permisos sobre modulos dependiendo de la cadena que se encuentre en el atributo permissions de la tabla ldt_users.
 * 
 * Esta cadena se compone de 5 digitos binarios, cada digito se refiere a un modulo, 1 para activarlo y 0 para desactivarlo
 * 
 * El orden de estos modulos es el siguiente:
 * 
 * 1. Modulo de Administracion
 * 2. Modulo de clientes
 * 3. Modulo de juegos
 * 4. Modulo de alquiler
 * 5. Modulo de torneos
 * 
 * Por ejemplo si tenemos la cadena 11111, estaremos dando permisos sobre todos los modulos, si tenemos la cadena 10100, se tendra solo permisos sobre administracion y juego.
 * 
 * Para retornar los permisos se utilizan las funciones que retornan booleanos.
 * 
 * @author David Cuadrado
*/
class ValidateUser : public KDialogBase
{
	Q_OBJECT

	public:
    		/**
    		 * 
    		 * @param db 
    		 * @param parent 
    		 * @param name 
    		 * @return 
    		 */
    		ValidateUser(KLDatabase *db, QWidget *parent = 0, const char *name = 0);
    		~ValidateUser();
		
		/**
		 * Este slot se activa cuando el presion de aceptar es presionado.
		 */
		void slotOk();
		
		/**
		 * Escribe la configuracion
		 */
		void writeConfig();
		
		/**
		 * Toma la cadena de permisos y la traduce a permisos para la aplicacion
		 * @param str 
		 */
		void string2perms(const QString &str);
		
		/**
		 * 
		 * @return 
		 */
		bool activeAdminModule();
		/**
		 * 
		 * @return 
		 */
		bool activeRentsModule();
		/**
		 * 
		 * @return 
		 */
		bool activeTournamentModule();
		/**
		 * 
		 * @return 
		 */
		bool activeClientsModule();
		/**
		 * 
		 * @return 
		 */
		bool activeGamesModule();
		
	private:
		UserPage *m_userPage;
		DatabasePage *m_databasePage;
		KLDatabase *m_db;
		bool m_activeAdminModule, m_activeRentsModule, m_activeTournamentModule, m_activeClientsModule, m_activeGamesModule;

};

#include <qcheckbox.h>

class UserPage : public QFrame
{
	public:
		/**
		 * 
		 * @param parent 
		 * @return 
		 */
		UserPage(QWidget *parent);
		/**
		 * 
		 * @return 
		 */
		~UserPage();
		/**
		 * 
		 * @return 
		 */
		QString getLogin();
		/**
		 * 
		 * @return 
		 */
		QString getPassword();
		
		/**
		 * 
		 * @return 
		 */
		bool storePassword();
		
	private:
		KLineEdit *m_user;
		KLineEdit *m_pass;
		QCheckBox *m_storepass;
};

class DatabasePage : public QFrame
{
	public:
		/**
		 * 
		 * @param parent 
		 * @return 
		 */
		DatabasePage(QWidget *parent);
		/**
		 * 
		 * @return 
		 */
		~DatabasePage();
		/**
		 * 
		 * @return 
		 */
		QString getServer();
		/**
		 * 
		 * @return 
		 */
		QString getDatabaseName();
		
	private:
		KLineEdit *m_server, *m_database;
};

#endif
