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
#include "rentstimer.h"
#include <kdebug.h>

RentsTimer::RentsTimer(const QStringList &rentInfo,int units,TimeUnit tu): QTimer(),m_rentInfo(rentInfo)
{
	kdDebug() << "Timer: Units " << units << " TimeUnits "<< tu << endl;;
	switch (tu)
	{
		case RentsTimer::Days:
		{
			int msec = units*24*60*60*1000;
			this->start(msec,true);
		}
		break;
		case RentsTimer::Hour:
		{
			int msec = units*60*60*1000;
			this->start(msec,true);
		}
		break;
		case RentsTimer::Min:
		{
			int msec = units*60*1000;
			this->start(msec,true);
		}
		break;
	}
	connect(this, SIGNAL(timeout()), this, SLOT(emitActivated()));
}


RentsTimer::~RentsTimer()
{
}

void RentsTimer::emitActivated()
{
	// Avisamos cada 5 minutos una vez terminado el tiempo
	
	this->start(5*60*1000,true);
	emit activated();
}

QStringList RentsTimer::getRentInfo()  const
{
	return m_rentInfo;
}
