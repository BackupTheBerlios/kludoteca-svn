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


#ifndef _KLUDOTECAVIEW_H_
#define _KLUDOTECAVIEW_H_

#include <kmdichildview.h>
#include <qlabel.h>
#include <khtml_part.h>
#include "kldatabase.h"


#include "kludotecaiface.h"

/**
 * Esta es la fabrica de la pagina principal
 * @b NOTA: Esta clase esta basada en KonqAboutPageFactory del proyecto konqueror.
 * 
 * @short Fabrica de KLMainPage
 * @author David Cuadrado \<krawek@gmail.com\>
 * @version 0.1
 */
class KLMainPageFactory //: public KParts::Factory
{
	public:
		/**
		 * Construye la fabrica de paginas
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		KLMainPageFactory( QObject *parent = 0, const char *name = 0 );
		virtual ~KLMainPageFactory();

		/**
		 * Construye la pagina principal
		 * @return 
		 */
		static QString mainpage();
		/**
		 * Construye la pagina 2
		 * @return 
		 */
		static QString page2();
		/**
		 * Construye la pagina 3
		 * @return 
		 */
		static QString page3();
		/**
		 * Construye la pagina 4
		 * @return 
		 */
		static QString page4();
		/**
		 * Construye la pagina 5
		 * @return 
		 */
		static QString page5();

	private:
		/**
		 * Carga un archivo
		 * @param file 
		 * @return 
		 */
		static QString loadFile( const QString& file );
		
		static QString *s_mainpage_html, *s_page2_html, *s_page4_html, *s_page5_html, *s_page3_html;
};

/**
 * Este es el widget que contiene la pagina principal de la aplicación.
 * @b NOTA: Esta clase esta basada en KonqAboutPage del proyecto Konqueror
 * 
 * @short Pagina principal
 * @author David Cuadrado \<krawek@gmail.com\>
 * @version 0.1
 */
class KLMainPage : public KHTMLPart
{
	Q_OBJECT
	public:
		/**
		 * Crea una pagina
		 * @param parentWidget 
		 * @param widgetName 
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		KLMainPage(QWidget *parentWidget, const char *widgetName,
		QObject *parent, const char *name );
		/**
		 * Destructor
		 * @return 
		 */
		~KLMainPage();

		/**
		 * Abre una url, esta funcion es reimplementada de KHTMLPart
		 * @param url 
		 * @return 
		 */
		virtual bool openURL( const KURL &url );

		/**
		 * Abre un archivo
		 * @return 
		 */
		virtual bool openFile();

		/**
		 * Guarda el estado de la pagina
		 * @param stream 
		 */
		virtual void saveState( QDataStream &stream );
		/**
		 * restaura el estado de la pagina
		 * @param stream 
		 */
		virtual void restoreState( QDataStream &stream );
		
		/**
		 * Abre el formulario para añadir torneos
		 * @param name 
		 */
		void addTournament(const QString &name = QString::null);
		/**
		 * Abre el formulario para añadir clientes
		 */
		void addClient();

	protected:
		/**
		 * Realiza acciones sobre URL's seleccionadas
		 * @param url 
		 * @param button 
		 * @param state 
		 * @param target 
		 * @param args 
		 */
		virtual void urlSelected( const QString &url, int button, int state, const QString &target, KParts::URLArgs args = KParts::URLArgs() );

	signals:
		/**
		 * Envia el widget para ponerlo en la interfaz
		 * @param  
		 */
		void sendWidget(KMdiChildView *);
		
	private:
		/**
		 * Crea una pagina
		 * @param  
		 * @param  
		 */
		void serve( const QString&, const QString& );

		KHTMLPart *m_doc;
		QString m_htmlDoc;
		QString m_what;
		QWidget *m_parent;
};

class QPainter;

/**
 * Este es el widget central que la ventana principal
 * 
 * @short Vista principal
 * @author David Cuadrado \<krawek@gmail.com\>
 * @version 0.1
 */
class KLudotecaView : public KMdiChildView, public KLudotecaIface
{
    	Q_OBJECT
	public:
		/**
		* Constructor por defecto
		*/
		KLudotecaView(const QString &caption, QWidget *parentWidget=0L, const char *name=0L, WFlags f=0);
	
		/**
		* Destructor por defecto
		*/
   	 	virtual ~KLudotecaView();

		/**
		* Imprime esta vista
		*/
		void print(QPainter *, int height, int width);
		
		/**
		 * Coloca un texto
		 */
		void setMessage(const QString &texto);
		
		/**
		 * Retorna la pagina
		 */
		KLMainPage *mainPage();
		
		/**
		 * Adiciona un torneo, reeimplementado de KLudotecaIface especialmente para dcop!.
		 */
		void addTournament(const QString &texto = QString::null);
		
		/**
		 * Agrega un cliente, reimplementado de KLudotecaIface especialmente para dcop
		 */
		void addClient();
		
	private:
		KLMainPage *m_mainPage;
};

#endif // _KLUDOTECAVIEW_H_
