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
#ifndef RENTSCONTROLLIST_H
#define RENTSCONTROLLIST_H

#include <ltlistview.h>
#include <qvaluelist.h>
#include "rentstimer.h"
#include <qdatetime.h>
#include "klquery.h"
#include "klxmlreader.h"
#include "klresultsetinterpreter.h"
#include <klresultset.h>

/**
@author Daniel Valencia 
@e-mail dafevara@gmail.com
*/

typedef QPtrList<RentsTimer> ListRentsTimer;

class RentsControlList : public LTListView
{
	Q_OBJECT
	public:
		RentsControlList(QWidget* parent = 0, const char* name = 0);
		~RentsControlList();
		void fillList();
		void queryButtonClicked();
		void addButtonClicked();
		void delButtonClicked();
		void modifyButtonClicked();
		void getClickedItem(QListViewItem *item);
		//RentsTimer *findRentsTimer()
	
			
	public slots:
		void addRentsTimer(RentsTimer *rt);
		void checkRentsTimer();
		
	private:
		ListRentsTimer m_listRentsTimer;
		KLXmlReader m_xmlreader;		
		QXmlInputSource m_xmlsource;
		KLSqlResults m_timerResults;
};

#endif
