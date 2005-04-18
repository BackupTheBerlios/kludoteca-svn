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
		KLMainPageFactory( QObject *parent = 0, const char *name = 0 );
		virtual ~KLMainPageFactory();

		static QString mainpage();
		static QString page2();
		static QString page3();
		static QString page4();
		static QString page5();

	private:
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
		 * 
		 * @param parentWidget 
		 * @param widgetName 
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		KLMainPage(QWidget *parentWidget, const char *widgetName,
		QObject *parent, const char *name );
		~KLMainPage();

		/**
		 * 
		 * @param url 
		 * @return 
		 */
		virtual bool openURL( const KURL &url );

		/**
		 * 
		 * @return 
		 */
		virtual bool openFile();

		/**
		 * 
		 * @param stream 
		 */
		virtual void saveState( QDataStream &stream );
		/**
		 * 
		 * @param stream 
		 */
		virtual void restoreState( QDataStream &stream );
		
		/**
		 * 
		 * @param name 
		 */
		void addTournament(const QString &name = QString::null);
		/**
		 * 
		 */
		void addClient();

	protected:
		/**
		 * 
		 * @param url 
		 * @param button 
		 * @param state 
		 * @param target 
		 * @param args 
		 */
		virtual void urlSelected( const QString &url, int button, int state, const QString &target, KParts::URLArgs args = KParts::URLArgs() );

	signals:
		/**
		 * 
		 * @param  
		 */
		void sendWidget(KMdiChildView *);
		
	private:
		/**
		 * 
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
		 * 
		 */
		void addClient();
		
	private:
		KLMainPage *m_mainPage;
};

#endif // _KLUDOTECAVIEW_H_
