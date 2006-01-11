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


#ifndef _KLUDOTECA_H_ 
#define _KLUDOTECA_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kmainwindow.h>
#include <kmdimainfrm.h>
#include <qlabel.h>
#include <klocale.h>
#include <qlayout.h>
#include <kiconloader.h>
#include <klistbox.h>
#include <kstatusbar.h>
#include <kactionclasses.h>
#include <qlayout.h>
#include <kiconloader.h>
#include <qvaluelist.h>
#include <kmditoolviewaccessor.h>

#include "kludotecaview.h"
#include "gamesmodule.h"
#include "gameslist.h"
#include "osd.h"
#include "tournamentwidget.h"
#include "adminwidget.h"
#include "clientswidget.h"
#include "rentswidget.h"
#include "rentsmodule.h"
#include "ldtapp.h"

#include "kldatabase.h"
#include "validateuser.h"

#include "dmainwindow.h"

#include "klreportmodule.h"

class KPrinter;
class KToggleAction;

class GamesModule;

/**
 * Esta clase representa la ventana principal de KLudoteca. Aqui manejamos los toolbars, menus y demas interfaces.
 *
 * @short Ventana principal de KLudoteca
 * @author David Cuadrado \<krawek@gmail.com\>
 * @version 0.1
 */
class KLudoteca : public DMainWindow
{
    	Q_OBJECT
	public:
		/**
		* Default Constructor
		*/
		KLudoteca();
		
		/**
		* Default Destructor
		*/
		virtual ~KLudoteca();
		
		/**
		 * Obtiene la conexion a la base de datos
		 */
		QSqlDatabase *getDatabase(const QString &bdname, bool open = false);

	protected:
		/**
	 	* Metodos sobre escritos de Qt para hacer Drag
		*/
		virtual void dragEnterEvent(QDragEnterEvent *event);
		/**
		 * Metodos sobre escritos de Qt para hacer drop
		 * @param event 
		 */
		virtual void dropEvent(QDropEvent *event);

	protected:
		/**
		* Esta funcion es llamada para guardar la sesion cuando sea necesario.
		*/
		void saveProperties(KConfig *);
		
		/**
		* Esta funcion es llamada para leer las propiedades de una sesion.
		*/
		void readProperties(KConfig *);

	private slots:
		/**
		 * 
		 */
		void newConnection();
		/**
		 * 
		 */
		void fileSave();
		/**
		 * 
		 */
		void fileSaveAs();
		/**
		 * 
		 */
		void filePrint();
		/**
		 * 
		 */
		void optionsShowToolbar();
		/**
		 * 
		 */
		void optionsShowStatusbar();
		/**
		 * 
		 */
		void optionsConfigureKeys();
		/**
		 * 
		 */
		void optionsConfigureToolbars();
		/**
		 * 
		 */
		void optionsPreferences();
		/**
		 * 
		 */
		void newToolbarConfig();
		
		/**
		 * Coloca un texto en la barra de estado
		 * @param text 
		 */
		void changeStatusbar(const QString& text);
		/**
		 * Coloca un titulo
		 * @param text 
		 */
		void changeCaption(const QString& text);

		/**
		 * Pone la ventana principal en modo pantalla completa
		 */
		void setFullScreen();
		
		/**
		 * Esta funcion muestra un mensaje utilizando el OSDWidget
		 */
		void showNotice(const QString &message);
		
		/**
		 * Cierra la vista actual
		 */
		void closeCurrent();
	

	public slots:	
		/**
		 * Muestra un dialogo de validacion de usuarios
		 */
		void showValidateUser();

		
	private:
		/**
		 * Crea y configura los aceleradores
		 */
		void setupAccel();
		/**
		 * Crea y configura las acciones
		 */
		void setupActions();
		/**
		 * Crea y configura los tools windows
		 */
		void setupToolWindows();
		/**
		 * Crea y configura el OnScreen-Display
		 */
		void setupOSD();
		
		/**
		 * Genera informacion de la empresa
		 */
		void generateEnterpriseInfo();
		
	private:
		KLudotecaView *m_view;
				
		KPrinter   *m_printer;
		
		int m_childs;
		
		KToggleAction *m_toolbarAction;
		KToggleAction *m_statusbarAction;
		
		GamesList *m_gamesList;
		TournamentWidget *m_tournamentWidget;
		AdminWidget *m_adminWidget;
		ClientsWidget *m_clientsWidget;
		//RentsWidget *m_rentsWidget;
		RentsModule *m_rentsModule;
		
		OSDWidget *m_osd;
		
		ValidateUser *m_userValidator;
};

#endif // _KLUDOTECA_H_
