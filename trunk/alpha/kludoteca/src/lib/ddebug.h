/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado   				   *
 *   krawek@gmail.com   						   *
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

#ifndef DDEBUG_H
#define DDEBUG_H

#if QT_VERSION < 0x040000
#include <qtextstream.h>
#else
# include <QTextStream>
#endif

/**
 * @author David Cuadrado <krawek@gmail.com>
*/

#ifdef __GNUC__
#define DFUNCINFO dDebug() << "[" << __PRETTY_FUNCTION__ << "] ";
#define DCLASS_INIT dDebug() << "[Initializing " << __FUNCTION__ << "]";
#define DCLASS_END dDebug() << "[Destroying " << __FUNCTION__ << "]";
#else
#define DFUNCINFO;
#define DCLASS_INIT dDebug() << "[Initializing " << __FILE__ << ":" << __LINE__ << "] ";
#define DCLASS_END dDebug() << "[Destroying " << __FILE__ << ":" << __LINE__ << "] ";
#endif

#define DSHOW_VAR(arg) dDebug() << #arg << " = " << arg;


class QWidget;
class QDateTime;
class QDate;
class QTime;
class QPoint;
class QSize;
class QRect;
class QRegion;
class QStringList;
class QColor;
class QPen;
class QBrush;
class QVariant;
class QPixmap;
class QImage;
class QFile;

class DDebug;
class DNDebug;

#if QT_VERSION >= 0x040000
class QIcon;
template <class T> class QList;
#endif

enum DebugType
{
	DDebugMsg = 0,
	DWarningMsg,
	DErrorMsg,
	DFatalMsg 
};

enum DebugOutput
{
	DDebugShell = 0,
	DDebugFile,
	DDebugDialog
};

#if !defined(D_NODEBUG)

class DDebug;

#if QT_VERSION < 0x040000
typedef DDebug & (*DEBUG_FUNC)(DDebug &);
#endif

class DDebug
{
	public:
		class Streamer
		{
			public:
				Streamer() :
#if QT_VERSION >= 0x040000
						ts(&buffer, QIODevice::WriteOnly)
#else
						ts(&buffer, IO_WriteOnly )
#endif
						, space(true)
					{
					}
				~Streamer() {};
				QTextStream ts;
				QString buffer;
				bool space;
		} *streamer;
		
		
		DDebug(DebugType t, DebugOutput dop);
		~DDebug();

		inline DDebug& operator << (const QString &str)
		{
			streamer->ts << "\"" << str << "\"";
			return *this;
		};
		
		inline DDebug& operator << (char c)
		{
			streamer->ts << "\'" << c << "\'";
			return *this;
		};
		
		inline DDebug &operator<<(bool t) 
		{ 
			streamer->ts << (t ? "true" : "false"); 
			return *this; 
		}

		inline DDebug &operator<<(signed short t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(unsigned short t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(signed int t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(unsigned int t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(signed long t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(unsigned long t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(float t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(double t) 
		{ 
			streamer->ts << t; 
			return *this; 
		}
		inline DDebug &operator<<(const char* t) 
		{ 
			streamer->ts  << t; 
			return *this; 
		}
		DDebug& operator<<( const QPixmap& p );
		DDebug& operator<<( const QImage& p ) ;
		DDebug& operator<<( const QDateTime& );
		DDebug& operator<<( const QDate&     );
		DDebug& operator<<( const QTime&     );
		DDebug& operator<<( const QPoint & ) ;
		DDebug& operator<<( const QSize & ) ;
		DDebug& operator<<( const QRect & ) ;
		DDebug& operator<<( const QRegion & );
		DDebug& operator<<( const QStringList & );
		DDebug& operator<<( const QColor & );
		DDebug& operator<<( const QPen & );
		DDebug& operator<<( const QBrush & );
		DDebug& operator<<( const QVariant & );
		DDebug& operator << (const QWidget*);
		DDebug& operator << (const QFile &);
		
#if QT_VERSION >= 0x040000
		inline DDebug &operator<<(QTextStreamManipulator m)
		{ 
			streamer->ts << m; 
			return *this; 
		}
		
		inline DDebug &operator<<(QTextStreamFunction f) 
		{
			streamer->ts << f;
			return *this;
		}

		DDebug& operator<<( const QIcon& p );
		template <class T> DDebug& operator << ( const QList<T> &list );
#else
		inline DDebug &operator<<(DEBUG_FUNC f)
		{
			return (*f)(*this);
		}
		
#endif
	private:
		DebugType m_type;
		DebugOutput m_output;
};

#if QT_VERSION >= 0x040000
template <class T> DDebug &DDebug::operator<<( const QList<T> &list )
{
	*this << "(";
	typename QList<T>::ConstIterator it = list.begin();
	if ( !list.isEmpty() ) 
	{
		*this << *it++;
	}
	for ( ; it != list.end(); ++it ) 
	{
		*this << "," << *it;
	}
	*this << ")";
	return *this;
}
#else
inline DDebug &endl(DDebug &debug)
{
	debug << "\n";
	return debug;
}
#endif

// Global functions
inline DDebug dDebug(DebugOutput dop = DDebugShell)
{
	return DDebug(DDebugMsg, dop);
}

inline DDebug dFatal(DebugOutput dop = DDebugShell)
{
	return DDebug(DFatalMsg, dop);
}

inline DDebug dError(DebugOutput dop = DDebugShell)
{
	return DDebug(DErrorMsg, dop);
}

inline DDebug dWarning(DebugOutput dop = DDebugShell)
{
	return DDebug(DWarningMsg, dop);
}

#else // D_NODEBUG

class DNDebug;

#if QT_VERSION < 0x040000
typedef DNDebug & (*DEBUG_FUNC)(DNDebug &);
#endif

class DNDebug
{
	public:
		inline DNDebug(){}
		inline DNDebug(const DNDebug &){}
		inline ~DNDebug(){}
		inline DNDebug &space() { return *this; }
		inline DNDebug &nospace() { return *this; }
		inline DNDebug &maybeSpace() { return *this; }
		template<typename T> inline DNDebug &operator<<(const T &) { return *this; }
		
#if QT_VERSION >= 0x040000
		inline DNDebug &operator<<(QTextStreamFunction) { return *this; }
		inline DNDebug &operator<<(QTextStreamManipulator) { return *this; }
#else
		inline DNDebug &operator<<(DEBUG_FUNC f)
		{
			return (*f)(*this);
		}
#endif
};

#if QT_VERSION < 0x040000
inline DNDebug &endl(DNDebug &debug)
{
	debug << "\n";
	return debug;
}
#endif

inline DNDebug dDebug(DebugOutput = DDebugShell)
{
	return DNDebug();
}

#define dFatal dDebug
#define dError dDebug
#define dWarning dDebug

#endif // D_NODEBUG

#endif
