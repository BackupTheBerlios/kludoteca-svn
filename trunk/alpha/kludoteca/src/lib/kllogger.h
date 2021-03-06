/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                                	   *
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
#ifndef KLLOGGER_H
#define KLLOGGER_H

#include <qobject.h>
#include <qstring.h>
#include <qfile.h>
#include <qdatetime.h>
#include <qdir.h>

class KLLogger;

/**
 * Este es el logger de la aplicacion
 * @author David Cuadrado
*/
class KLLogger : public QObject
{
	Q_OBJECT	
	protected:
		KLLogger();
		~KLLogger();
	public:
		enum LogType { Err, Warn, Crit, Inf };
		
		void setFile(const QString &filename);
		static KLLogger *instance();
		void log(const QString &message, LogType t = Inf);
		void setupLogger(const QString &directory, const QString &filename );
		QString getFilePath();

	private:
		static KLLogger *m_instance;
		QFile *m_file;
};

#define LOGGER KLLogger::instance()

#endif
