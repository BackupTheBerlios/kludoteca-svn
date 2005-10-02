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
#include "ldtapp.h"
#include "klfirstdialog.h"
#include <iostream>
#include <klocale.h>

LDTApp::LDTApp() : KApplication(), APPVERSION("0.2a")
{
	// Configuramos el logger
// 	LOGGER->setupLogger(QDir::homeDirPath (), QString("logfile.txt") );

	LOGGER->setupLogger(locate("data", "kludoteca/"), QString("logfile"));
}

LDTApp::~LDTApp()
{
}

void LDTApp::firstDialog()
{
	std::cout << i18n("Running 1st Dialog!") << std::endl;
	KLFirstDialog firstDialog;
	setTopWidget(&firstDialog);
	
	if( firstDialog.exec() != QDialog::Rejected )
	{
		std::cout << "Accepted" << std::endl;
	}
}

KConfig *LDTApp::config( const QString &group )
{
	kapp->config()->setGroup( group );
	return kapp->config();
}

QString LDTApp::appversion()
{
	return APPVERSION;
}

void LDTApp::applyColors()
{
	QColorGroup group = QApplication::palette().active();
	const QColor bg( 32,32,82 );
	const QColor bgAlt( 57, 64, 98 );
	
	group.setColor( QColorGroup::Text, Qt::lightGray );
	group.setColor( QColorGroup::Base, bg );
	group.setColor( QColorGroup::Foreground, 0xd7d7ef );
	group.setColor( QColorGroup::Background, bgAlt );

	group.setColor( QColorGroup::Button, bgAlt );
	group.setColor( QColorGroup::ButtonText, 0xd7d7ef );

	group.setColor( QColorGroup::Highlight, Qt::gray );
	group.setColor( QColorGroup::HighlightedText, bg );
	int h,s,v;
	bgAlt.getHsv( &h, &s, &v );
	group.setColor( QColorGroup::Midlight, QColor( h, s/3, (int)(v * 1.2),QColor::Hsv ) );
	
	QPalette pal(group, group, group);
	
	setPalette(pal);
}

#include "ldtapp.moc"
