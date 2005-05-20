/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                               	   *
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
#include "formmatchorder.h"
#include <klocale.h>

FormMatchOrder::FormMatchOrder(FormBase::Type t, QWidget *parent)
 : FormBase(t, parent, "FormMatchOrder")
{
	setupForm();
}


FormMatchOrder::~FormMatchOrder()
{
}


void FormMatchOrder::setupForm()
{
	// filas = participantes / 2
	m_table = new KLTable(30, 3, this, "MatchTable");
	m_table->setColumnLabels(QStringList() << i18n("Oponnent one") << i18n("Oponnent two") << i18n("Results"));
	
	for(uint i = 0; i < m_table->numRows(); i++)
	{
		QComboTableItem *tcombo = new QComboTableItem(m_table, QStringList() << i18n("Draw") << i18n("Win") << i18n("Lose"), false);
		m_table->setItem(i, 2, tcombo);
	}
}

void FormMatchOrder::accept()
{
}

void FormMatchOrder::cancel()
{
    FormBase::cancel();
}

void FormMatchOrder::clean()
{
}

#include "formmatchorder.moc"
