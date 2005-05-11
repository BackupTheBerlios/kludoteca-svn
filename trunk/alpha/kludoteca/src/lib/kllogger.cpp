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
#include "kllogger.h"
#include <iostream>
#include <klocale.h>

KLLogger::KLLogger() : QObject(0, "Logger"), m_file(0)
{
}


KLLogger::~KLLogger()
{
}

KLLogger *KLLogger::instance()
{
	static KLLogger *inst = new KLLogger;
	return inst;
}

void KLLogger::setupLogger(const QString &directory, const QString &filename )
{
	QDir dirBase(directory);
	if ( ! dirBase.exists() )
	{
		if ( ! dirBase.mkdir(directory) )
		{
			qDebug(i18n("Error: I can't create %").arg(directory));
			return;
		}
	}
	
	setFile(directory+"/"+filename);
}

void KLLogger::setFile(const QString &filename)
{
	std::cout << "set file: " << filename << std::endl;
	m_file = new QFile(filename);
}

void KLLogger::log(const QString &message, LogType t)
{
	// TODO: Escribir esto en un XML
	if ( m_file )
	{
		if ( m_file->open(IO_WriteOnly | IO_Append) )
		{
			QTextStream stream( m_file );
			QString msg = QDate::currentDate().toString(Qt::ISODate) + " " + message;
			
			switch ( t )
			{
				case Warn:
				{
					msg = "WARNING: " + msg;
				}
				break;
				case Inf:
				{
					msg = "INFO: " + msg;
				}
				break;
				case Crit:
				{
					msg = "CRITICAL: " + msg;
				}
				break;
				case Err:
				{
					msg = "ERROR: " + msg;
				}
				break;
			}
			
			stream << msg << endl;
			
			m_file->close();
		}
		else
		{
			qDebug(i18n("I can't open %1 to write!").arg(m_file->name()));
		}
	}
	else
	{
		qDebug(i18n("You need setup the logger first"));
	}
}

#include "kllogger.moc"
