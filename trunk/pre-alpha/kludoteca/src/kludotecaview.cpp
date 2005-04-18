/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        *
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


#include "kludotecaview.h"

#include <qpainter.h>
#include <qlayout.h>

#include <kurl.h>

#include <ktrader.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <krun.h>
#include <klocale.h>

KLudotecaView::KLudotecaView(const QString &caption, QWidget *parentWidget, const char *name, WFlags f) : KMdiChildView(caption, parentWidget, name, f), DCOPObject("KLudotecaIface")
{
	// setup our layout manager to automatically add our widgets
	QHBoxLayout *top_layout = new QHBoxLayout(this);
	top_layout->setAutoAdd(true);
	
	// we want to look for all components that satisfy our needs.  the
	// trader will actually search through *all* registered KDE
	// applications and components -- not just KParts.  So we have to
	// specify two things: a service type and a constraint
	//
	// the service type is like a mime type.  we say that we want all
	// applications and components that can handle HTML -- 'text/html'
	//
	// however, by itself, this will return such things as Netscape..
	// not what we wanted.  so we constrain it by saying that the
	// string 'KParts/ReadOnlyPart' must be found in the ServiceTypes
	// field.  with this, only components of the type we want will be
	// returned.
	
	// in theory, we only care about the first one.. but let's try all
	// offers just in case the first can't be loaded for some reason
	// if our factory is invalid, then we never found our component
	// and we might as well just exit now
	
	m_label = new QLabel( i18n( "Welcome to the matrix" ), this );
}

KLudotecaView::~KLudotecaView()
{
}

void KLudotecaView::print(QPainter *p, int height, int width)
{
	// Hacer la impresion aqui.
}

void KLudotecaView::setMessage(const QString &texto)
{
	m_label->setText(texto);
}

#include "kludotecaview.moc"
