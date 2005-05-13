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
#include "formparticipants.h"

FormParticipants::FormParticipants(FormBase::Type t, QWidget *parent)
    : FormBase(t, parent, "FormParticipants")
{
	setupForm();
}


FormParticipants::~FormParticipants()
{
}

void FormParticipants::setupForm()
{
	QTable *table = new QTable(10,3,this);
}

void FormParticipants::accept()
{
}

void FormParticipants::cancel()
{
	emit cancelled();
}

void FormParticipants::clean()
{
}

#include "formparticipants.moc"
