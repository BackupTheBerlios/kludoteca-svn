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

LDTApp::LDTApp() : KApplication()
{
	// Leemos el archivo de configuracion, si es la primera vez que se lanza la aplicación, mostramos el dialogo de inicio, sino continuamos con la carga normal.
	
	if ( config()->readBoolEntry( "First Run", true ) )
	{
		firstDialog();
		config()->writeEntry( "First Run", false );
		config()->sync();
	}
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

void LDTApp::applyColors()
{
}

#include "ldtapp.moc"
