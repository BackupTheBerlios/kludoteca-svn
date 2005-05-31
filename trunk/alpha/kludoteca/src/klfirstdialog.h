/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
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
 
#ifndef KLFIRSTDIALOG_H
#define KLFIRSTDIALOG_H

#include <kwizard.h>
#include <qlabel.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlayout.h>
#include <klineedit.h>
#include <qgroupbox.h>
#include <kpushbutton.h>
#include <kprogress.h>
#include <qradiobutton.h>
#include <qhbuttongroup.h>

#include "kldatabase.h"

class FDWelcome;
class FDInitDatabase;
class FDSetupAdmin;
class FDSetupEnterprise;

/**
 * Esta clase es utilizada para inicializar el sistema, se lanzara la primera vez que se ejecute la aplicación y permitira configurar todo el sistema.
 * @todo - Crear base de datos
 * 		- Capturar informacion necesaria para configurar la empresa
 * 		- Informacion necesaria acerca del usuario administrador
 * 		- Una tabla para añadir juegos
 * 		- Una tabla para añadir usuarios
 * @author David Cuadrado
*/
class KLFirstDialog : public KWizard
{
	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		KLFirstDialog(QWidget *parent = 0, const char *name = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~KLFirstDialog();
		
				
	public slots:
		void next();
		void finished();
		void showFinish();
		void cancel();
		
	private:
		FDWelcome *m_welcome, *m_finish;
		FDInitDatabase *m_initdb;
		FDSetupEnterprise *m_enterprise;
		FDSetupAdmin *m_setupAdmin;

};

/**
 * Esta clase es utilizada para intanciar un mensaje de bienvenida a la aplicacion, ademas de una explicacion del proceso de inicialización y una muestra del logo de la aplicacion.
 * @author David Cuadrado
 */
class FDWelcome : public QHBox
{
	public: 
		/**
		 * Crea un widget de bienvenida al primer dialogo
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		FDWelcome(QWidget *parent = 0, const char *name = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~FDWelcome();
		
		/**
		 * Pone un mensaje en el widget
		 * @param text 
		 */
		void setMessage(const QString &text);
		
	private:
		QString m_text;
		QLabel *m_message;
};

/**
 * Esta clase es utilizada para inicializar la base de datos, pide la informacion necesaria para tal operacion y procede a crear la base de datos
 * @author David Cuadrado
 */
class FDInitDatabase : public QVBox
{
	Q_OBJECT
	public:
		/**
		 * Crea un objeto de configuracion de la base de datos
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		FDInitDatabase(QWidget *parent = 0, const char *name = 0);
		
		/**
		 * Destructor
		 * @return 
		 */
		~FDInitDatabase();
		
		bool checkAccount();
		
	public slots:
		/**
		 * Este slot se encarga de crear la base de datos!
		 */
		void createDatabase();
		
	signals:
		void enableNext(QWidget *widget, bool e);
		void gotoFinish();
		
	private:
		QGroupBox *m_dataBox;
		KLineEdit *m_server, *m_dbname, *m_login, *m_passwd;
		KPushButton *m_createButton;
		KProgress *m_pbar;
};

class FDSetupEnterprise : public QVBox
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		FDSetupEnterprise(QWidget *parent = 0, const char *name = 0);
		
		/**
		 * Destructor
		 * @return 
		 */
		~FDSetupEnterprise();
		
		void addEnterprise();
		
	private:
		QGroupBox *m_dataBox;
		KLineEdit *m_name, *m_nit, *m_address, *m_phone, *m_city;
};

/**
 * Esta clase es utilizada para configurar la cuenta de administrador de la aplicacion
 * @author David Cuadrado
 */
class FDSetupAdmin : public QVBox
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		FDSetupAdmin(QWidget *parent = 0, const char *name = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~FDSetupAdmin();
		
		/**
		 * Envia la consulta a la base de datos, si todo sale bien retorna verdadero, en caso contrario falso
		 * @param db 
		 * @return 
		 */
		bool setAdministrator();
		
	private:
		QGroupBox *m_dataBox;
		KLineEdit *m_fname, *m_lname;
		QRadioButton *m_malesex, *m_femalesex;
		KLineEdit *m_address, *m_phone, *m_email, *m_docident;
		QHButtonGroup *m_sexBox;
};

#endif
