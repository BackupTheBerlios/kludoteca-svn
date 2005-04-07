/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        *
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

#include <kapplication.h>
#include <kmainwindow.h>
#include <kmdimainfrm.h>
#include <qlabel.h>
#include <kmdichildview.h>
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

class KPrinter;
class KToggleAction;

class GamesModule;
class KMdiToolViewAccessorPrivate;

/**
 * Esta clase representa la ventana principal de KLudoteca. Aqui manejamos los toolbars, menus y demas interfaces.
 *
 * @short Ventana principal de KLudoteca
 * @author David Cuadrado \<krawek@gmail.com\>
 * @version 0.1
 */
class KLudoteca : public KMdiMainFrm
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

	protected:
		/**
	 	* Metodos sobre escritos de Qt para hacer Drag & drop (dnd)
		*/
		virtual void dragEnterEvent(QDragEnterEvent *event);
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
		void fileNew();
		void fileSave();
		void fileSaveAs();
		void filePrint();
		void optionsShowToolbar();
		void optionsShowStatusbar();
		void optionsConfigureKeys();
		void optionsConfigureToolbars();
		void optionsPreferences();
		void newToolbarConfig();
		
		void changeStatusbar(const QString& text);
		void changeCaption(const QString& text);

		/**
		 * Este slot verifica si el juego existe, en caso verdadero abre un formulario para consultar la información del juego.
		 */
		void queryGame(QString &game);
		void setFullScreen();
		
		/**
		 * Esta funcion añade una pagina de modulo
		 */
		void addModulePage(KMdiChildView *view);
		
		/**
		 * Esta funcion muestra un mensaje utilizando el OSDWidget
		 */
		void showNotice(QString message);
		
		/**
		 * Cierra la vista actual
		 */
		void closeCurrent();
		
	private:
		void setupAccel();
		void setupActions();
		void setupToolWindows();
		void setupOSD();

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
		
		OSDWidget *osd;
		QValueList<KMdiToolViewAccessor*> m_toolWindows;
};

#endif // _KLUDOTECA_H_
