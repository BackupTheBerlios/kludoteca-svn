/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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
#ifndef TOURNAMENTWIDGET_H
#define TOURNAMENTWIDGET_H

#include "lttoolbox.h"
#include "tournamentactive.h"
#include "tournamentold.h"

/**
 * Esta clase contiene un widget con la informacion que se va a gestionar de los torneos.
 * @short Widget con la informacion del los torneos
 * @author CetiSoft
*/
class TournamentWidget : public LTToolBox
{
	Q_OBJECT
	public:
		/**
		 * Constructor por defecto
		 */
    		TournamentWidget(QWidget *parent);
		/**
		 * Destructor por defecto
		 */
		~TournamentWidget();
		
		
	signals:	
		/**
		 * Este signal envia el widget para er puesto en la ventana principal
		 */
		void sendWidget(KMdiChildView *);
		
	private:
		/**
		 * Esta funcion sirve para crear los tabs del ToolBox
		 */
		void setupTabs();
		
	private:
		TournamentActive *m_tournamentActive;
		TournamentOld *m_tournamentOld;
};

#endif
