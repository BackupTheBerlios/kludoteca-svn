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


#include "pref.h"

#include <klocale.h>
#include "ldtapp.h"

// KLudotecaPreferences

KLudotecaPreferences::KLudotecaPreferences() : KDialogBase(TreeList, i18n("Configuration..."), Help|Default|Ok|Apply|Cancel, Ok)
{
	// this is the base class for your preferences dialog.  it is now
	// a Treelist dialog.. but there are a number of other
	// possibilities (including Tab, Swallow, and just Plain)
	QVBox *frame;
	frame = addVBoxPage(i18n("Database"), i18n("Configure Database"));
	
	m_pageOne = new KLudotecaPrefPageOne(frame);
	
	frame = addVBoxPage(i18n("Apparience"), i18n("Look&feel"));
	m_pageTwo = new KLudotecaPrefPageTwo(frame);
}

// KLudotecaPrefPageOne
KLudotecaPrefPageOne::KLudotecaPrefPageOne(QWidget *parent) : QFrame(parent)
{	
	QGridLayout *glayout = new QGridLayout(this, 3, 3, 10);
	
	m_server = new KLineEdit(this);
	m_server->setText(klapp->config("Connection")->readEntry("Server", "localhost"));
	m_user = new KLineEdit(this);
	m_user->setText(klapp->config("Connection")->readEntry("Login"));

	m_database = new KLineEdit(this);
	m_database->setText(klapp->config("Connection")->readEntry("Database"));
	
	glayout->addWidget(new QLabel(i18n("Server: "), this), 0,0);
	glayout->addWidget(m_server , 0,1);
	
	glayout->addWidget(new QLabel(i18n("User"),this), 1,0);
	glayout->addWidget(m_user, 1, 1);
	
	glayout->addWidget(new QLabel(i18n("Database"),this), 2,0);
	glayout->addWidget(m_database, 2, 1);
}

KLudotecaPrefPageOne::~ KLudotecaPrefPageOne()
{
}

// KLudotecaPrefPageTwo
KLudotecaPrefPageTwo::KLudotecaPrefPageTwo(QWidget *parent) : QFrame(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setAutoAdd(true);
	
	new QLabel(i18n("Soon we have the look&feel configuration!"), this);
}

#include "pref.moc"
