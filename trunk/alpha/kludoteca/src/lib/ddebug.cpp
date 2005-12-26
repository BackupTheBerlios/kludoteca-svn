/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                      *
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


#if !defined(D_NODEBUG)
#include "ddebug.h"

#if QT_VERSION < 0x040000
# include <qapplication.h>
# include <qfile.h>
# include <qstring.h>
# include <qdatetime.h>
# include <qpoint.h>
# include <qrect.h>
# include <qregion.h>
# include <qstringlist.h>
# include <qpen.h>
# include <qbrush.h>
# include <qsize.h>
# include <qvariant.h>
# include <qimage.h>
# include <qpixmap.h>
# include <qwidget.h>
# include <qmessagebox.h> 
#else
# include <QApplication>
# include <QFile>
# include <QString>
# include <QDateTime>
# include <QPoint>
# include <QRect>
# include <QRegion>
# include <QStringList>
# include <QPen>
# include <QBrush>
# include <QSize>
# include <QVariant>
# include <QImage>
# include <QIcon>
# include <QPixmap>
# include <QWidget>
# include <QMessageBox>
#endif

#if defined(Q_OS_UNIX)
# define SHOW_ERROR "*** \033[0;31m%s\033[0;0m ***\n"
# define SHOW_WARNING "-> \033[10;33m%s\033[0;0m\n"
# define SHOW_FATAL "***** \033[0;35m%s\033[0;0m *****\n"
#else
# define SHOW_ERROR "*** %s ***\n"
# define SHOW_WARNING "-> %s\n"
# define SHOW_FATAL "***** %s *****\n"
#endif

static void DDebutOutput(DebugType t, DebugOutput dop, const char *data)
{
	char *output = "%s\n";
	switch(t)
	{
		case DDebugMsg:
		{
// 			output = "%s\n";
		}
		break;
		case DWarningMsg:
		{
			output = SHOW_WARNING;
		}
		break;
		case DErrorMsg:
		{
			output = SHOW_ERROR;
		}
		break;
		case DFatalMsg:
		{
			output = SHOW_FATAL;
		}
		break;
	}
	
	switch(dop)
	{
		case DDebugShell:
		{
			fprintf(stderr, output, data);
		}
		break;
		case DDebugFile:
		{
			QString fileName = "output.debug";
#if QT_VERSION >= 0x040000
			if ( qApp )
			{
				fileName = qApp->applicationName()+".debug";
			}
#else
			if(qApp)
			{		
				QString fileName = qApp->name()+QString(".debug");
			}
#endif
			QFile file( fileName );
#if QT_VERSION >= 0x040000
			file.open( QIODevice::WriteOnly | QIODevice::Append);
			file.write( data, strlen(data) );
#else
			file.open( IO_WriteOnly | IO_Append | IO_Raw );
			file.writeBlock( data, strlen(data) );
#endif
			file.close();
		}
		break;
		case DDebugDialog:
		{
			if ( qApp )
			{
				QMessageBox::warning( 0L, "", data, QObject::tr("&Ok") );
			}
		}
		break;
	}
}

DDebug::DDebug(DebugType t, DebugOutput dop) : m_type(t), m_output(dop)
{
	streamer = new Streamer();
};

DDebug::~DDebug()
{
#if QT_VERSION >= 0x040000
	::DDebutOutput( m_type, m_output, streamer->buffer.toLocal8Bit().data() ); 
#else
	::DDebutOutput( m_type, m_output, streamer->buffer.local8Bit().data() ); 
#endif
	delete streamer;
}

DDebug& DDebug::operator<<( const QPixmap& p ) 
{
	*this << "[QPixmap size: (" << p.width() << ", " << p.height() << ")\n";
	*this << "Null? " << p.isNull() << "]"; 
	return *this;
}

DDebug& DDebug::operator<<( const QImage& p ) 
{
	*this << "QImage size: (" << p.width() << ", " << p.height() << ")";
	return *this;
}

DDebug& DDebug::operator<<( const QDateTime& time) 
{
	*this << time.toString();
	return *this;
}

DDebug& DDebug::operator<<( const QDate& date) 
{
	*this << date.toString();

	return *this;
}

DDebug& DDebug::operator<<( const QTime& time) 
{
	*this << time.toString();
	return *this;
}

DDebug& DDebug::operator<<( const QPoint & p)  
{
	*this << "QPoint: (" << p.x() << ", " << p.y() << ")";
	return *this;
}

DDebug& DDebug::operator<<( const QSize & s)  
{
	*this << "QSize: [" << s.width() << "x" << s.height() << "]";
	return *this;
}

DDebug& DDebug::operator<<( const QRect & r)  
{
	*this << "QRect: [" << r.x() << "," << r.y() << " - " << r.width() << "x" << r.height() << "]";
	return *this;
}

DDebug& DDebug::operator<<( const QRegion & reg) 
{
	*this<< "[QRegion: ";

#if QT_VERSION >= 0x040000
	QVector<QRect> rs = reg.rects();
#else
	QMemArray<QRect> rs = reg.rects();
#endif
	for (int i=0;i<rs.size();++i)
	{
		*this << QString("[%1,%2 - %3x%4] ").arg(rs[i].x()).arg(rs[i].y()).arg(rs[i].width()).arg(rs[i].height() ) ;
	}

	*this <<"]";
	return *this;
}

DDebug& DDebug::operator<<( const QStringList & l) 
{
	*this << "QStringList (";
	*this << l.join(",");
	*this << ")";

	return *this;
}

DDebug& DDebug::operator<<( const QColor & c) 
{
	if ( c.isValid() )
		*this << "Color: " << c.name();
	else
		*this << "Color: (invalid/default)";
	return *this;
}

DDebug& DDebug::operator<<( const QPen & p) 
{
	static const char* const s_penStyles[] = 
	{
		"NoPen", "SolidLine", "DashLine", "DotLine", "DashDotLine", "DashDotDotLine" 
	};
	static const char* const s_capStyles[] = 
	{
		"FlatCap", "SquareCap", "RoundCap" 
	};
	
	*this << "[ style:";
	*this << s_penStyles[ p.style() ];
	*this << " width:";
	*this << p.width();
	*this << " color:";
	if ( p.color().isValid() )
		*this << p.color().name();
	else
		*this <<"(invalid/default)";
	if ( p.width() > 0 ) // cap style doesn't matter, otherwise
	{
		*this << " capstyle:";
		*this << s_capStyles[ p.capStyle() >> 4 ];
	}
	*this <<" ]";
	return *this;
}

DDebug& DDebug::operator<<( const QBrush & b) 
{
	static const char* const s_brushStyles[] = 
	{
		"NoBrush", "SolidPattern", "Dense1Pattern", "Dense2Pattern", "Dense3Pattern",
		"Dense4Pattern", "Dense5Pattern", "Dense6Pattern", "Dense7Pattern",
		"HorPattern", "VerPattern", "CrossPattern", "BDiagPattern", "FDiagPattern",
		"DiagCrossPattern" 
	};

	*this <<"[ style: ";
	*this <<s_brushStyles[ b.style() ];
	*this <<" color: ";
	if ( b.color().isValid() )
		*this <<b.color().name() ;
	else
		*this <<"(invalid/default)";
#if QT_VERSION >= 0x040000
	if ( ! b.texture().isNull() )
		*this <<" has a texture";
#else
	if ( ! b.pixmap()->isNull() )
		*this <<" has a pixmap";
#endif
	*this <<" ]";
	return *this;
}

DDebug& DDebug::operator<<( const QVariant & v) 
{
	*this << "[variant: ";
	*this << v.typeName();
	*this << " toString=";
	*this << v.toString();
	*this << "]";
	return *this;
}

DDebug& DDebug::operator << (const QWidget* t) 
{
	if ( t )
	{
		*this << "[Widget geometry: " << t->width() << "x"<< t->height() << "]";
	}
	else
	{
		*this << "[Null Widget]";
	}
	return *this; 
}

DDebug& DDebug::operator << (const QFile &f)
{
#if QT_VERSION >= 0x040000
	*this << "[File: " << f.fileName() << "\n";
		*this << "Exists: " << f.exists() << "\n";
		
		QString errorString = "";
		switch(f.error())
		{
			case QFile::NoError:
			{
				errorString = QObject::tr("[No error]");
			}
			break;
			case QFile::ReadError:
			{
				errorString = QObject::tr("[Read error]");
			}
			break;
			case QFile::WriteError:
			{
				errorString = QObject::tr("[Write error]");
			}
			break;
			case QFile::FatalError:
			{
				errorString = QObject::tr("[Falta error]");
			}
			break;
			case QFile::ResourceError:
			{
				errorString = QObject::tr("[Resource error]");
			}
			break;
			case QFile::OpenError:
			{
				errorString = QObject::tr("[Open error]");
			}
			break;
			case QFile::AbortError:
			{
				errorString = QObject::tr("[Abort error]");
			}
			break;
			case QFile::TimeOutError:
			{
				errorString = QObject::tr("[Timeout error]");
			}
			break;
			case QFile::UnspecifiedError:
			{
				errorString = QObject::tr("[Unspecified error]");
			}
			break;
			case QFile::RemoveError:
			{
				errorString = QObject::tr("[Remove error]");
			}
			break;
			case QFile::RenameError:
			{
				errorString = QObject::tr("[Rename error]");
			}
			break;
			case QFile::PositionError:
			{
				errorString = QObject::tr("[Position error ]");
			}
			break;
			case QFile::ResizeError:
			{
				errorString = QObject::tr("[Resize error]");
			}
			break;
			case QFile::PermissionsError:
			{
				errorString = QObject::tr("[Permissions error]");
			}
			break;
			case QFile::CopyError:
			{
				errorString = QObject::tr("[Copy error]");
			}
			break;

		} 
		
		*this << "Error: " << errorString << "]";
		
#else
	*this << "[File: " << f.name() << "\n";
	*this << "Exists: " << f.exists() << "\n";
	*this << "Error: " << f.errorString() << "]";
#endif
	return *this;
}


#if QT_VERSION >= 0x040000

DDebug& DDebug::operator<<( const QIcon& p )
{
	*this << "QIcon: (" << p.pixmap(QSize() ).width() << ", " << p.pixmap(QSize()).height() << ")";
	return *this;
}

#endif


#endif // D_NODEBUG

