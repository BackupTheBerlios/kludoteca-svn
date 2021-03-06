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
#ifndef RENTSTIMER_H
#define RENTSTIMER_H

#include <qtimer.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qstring.h>
#include <qdatetime.h>
#include "klquery.h"
#include "klxmlreader.h"
#include "klresultsetinterpreter.h"
#include <klresultset.h>
#include "kldatabase.h"

#include "rentinfo.h"

/**
@author Daniel Valencia dafevara@gmail.com
*/
class RentsTimer : public QTimer
{
	Q_OBJECT
	public:
		enum TimeUnit { Days = 0,Hour, Min};
		RentsTimer(const RentInfo &rentInfo,int units, TimeUnit tu);
		~RentsTimer();
		RentInfo getRentInfo() const;
		
	private slots:
		void emitActivated();
		
	signals:
		void activated();
		
	private:
		RentInfo m_rentInfo;
};

#endif
