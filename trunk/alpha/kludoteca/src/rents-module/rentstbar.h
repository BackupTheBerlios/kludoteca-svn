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
#ifndef RENTSTBAR_H
#define RENTSTBAR_H

#include <ktabwidget.h>
#include "rentswidget.h"



/**
@author Daniel Valencia
*/
class RentsTBar : public KTabWidget
{
	Q_OBJECT
	public:
		RentsTBar(QWidget *parent = 0, const char *name = 0);
		~RentsTBar();
	public slots:
		void applyChangesToLists();
		
	private:
		void setupTabs();
	private:
		RentsWidget *m_rentsWidget;
			

};

#endif
