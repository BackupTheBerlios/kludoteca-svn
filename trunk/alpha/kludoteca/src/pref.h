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

#ifndef _KLUDOTECAPREF_H_
#define _KLUDOTECAPREF_H_ 

#include <kdialogbase.h>
#include <qframe.h>
#include <qlayout.h>
#include <qlabel.h>
#include <klineedit.h>
#include <qgroupbox.h>
#include <qvbox.h>

class KLudotecaPrefPageOne;
class KLudotecaPrefPageTwo;

/**
 * @short Preferencias de la aplicacion
 * @author David Cuadrado
 */
class KLudotecaPreferences : public KDialogBase
{
    	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
    		KLudotecaPreferences();

	private:
    		KLudotecaPrefPageOne *m_pageOne;
    		KLudotecaPrefPageTwo *m_pageTwo;
};

/**
 * @short Pagina uno de configuracion
 * @author David Cuadrado
 */
class KLudotecaPrefPageOne : public QFrame
{
    	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
    		KLudotecaPrefPageOne(QWidget *parent = 0);
		
		/**
		 * Destructor
		 * @return 
		 */
		~KLudotecaPrefPageOne();
		
	private:
		KLineEdit *m_server,*m_user,*m_database;
};

/**
 * @short Pagina dos de configuracion
 * @author David Cuadrado
 */
class KLudotecaPrefPageTwo : public QFrame
{
    	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
   	 	KLudotecaPrefPageTwo(QWidget *parent = 0);
};

#endif // _KLUDOTECAPREF_H_
