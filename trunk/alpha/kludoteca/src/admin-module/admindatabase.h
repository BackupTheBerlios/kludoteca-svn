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

#ifndef ADMINDATABASE_H
#define ADMINDATABASE_H

#include "ltlistview.h"

#include <qprocess.h>
#include <qdir.h>

#include <kparts/part.h>

class KProcess;

/**
Esta clase nos sirve para administrar la base de datos

@author David Cuadrado
*/
class AdminDatabase : public LTListView
{
	Q_OBJECT
	public:
	    	/**
	    	 * Constructor por defecto
	    	 * @param parent 
	    	 * @return 
	    	 */
	    	AdminDatabase(QWidget *parent = 0);
    		/**
    		 * Destructor por defecto
    		 * @return 
    		 */
    		~AdminDatabase();
		
		void setupDatabaseTools();
		
		
		/**
		 * Llena la lista, esta funcion es reimplementada de LTListView
		 */
		void fillList();
		
		void showEvent ( QShowEvent *e);
		
	public slots:
		/**
	 	 * Esta funcion nos da el item que fue clickeado
		 */
		void getClickedItem(QListViewItem *item);
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de adicionar
		 */
		void addButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de borrar
		 */
		void delButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de modificar
		 */
		void modifyButtonClicked();
		
		/**
		 * Esta funcion debe sobreescribirse con la accion que se debe ejecutar cuando se presiona el boton de consultar
		 */
		void queryButtonClicked();
		
		/**
		 * Adiciona un item a la lista consultando la base de datos.
		 * @param table 
		 * @param pkey 
		 */
		void addItem(const QString &pkey);
		
		
		void slotFilter(const QString &filter);
		
		
		/**
		 * Actualiza un item de la lista basandose en la llave recibida
		 * @param  
		 */
		void updateItem(const QString &pkey);
		
		
	private slots:
		void makeDump(KProcess *, char *, int );
		void saveBackup(KProcess *);
		void makeBackup();
		
	private:
		KLSelect *m_sqlquery;
		bool m_havePsql;
		bool m_havePgDump;
		QDir *m_dumpDir;
		KParts::ReadOnlyPart *m_part;
		
		QString m_backup;
};

#endif
