/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        *
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
#include "kludotecaiface.h"

class QPainter;

/**
 * Este es el widget central que la ventana principal
 * 
 * @short Vista principal
 * @author CetiSoft \<cetis@univalle.edu.co\>
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
		
	private:
		QLabel *m_label;
};

#endif // _KLUDOTECAVIEW_H_
