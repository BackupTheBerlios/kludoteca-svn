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

#include "formtournament.h"
#include <klocale.h>

FormTournament::FormTournament(QWidget *parent) : FormBase(parent, "FormTournament") 
{
	setupForm();
	this->setupButtons(FormBase::AcceptButton, FormBase::CancelButton);
}


FormTournament::~FormTournament()
{
}

void FormTournament::setupForm()
{
	form = new QFrame(this);
	m_grid = new QGridLayout(form,7,4,10);
	
	m_nameTourLabel = new QLabel(i18n("Name of tournament"),form);
	m_nameTournament = new KLineEdit(form);
	m_grid->addWidget(m_nameTourLabel, 0,0);
	m_grid->addWidget(m_nameTournament, 0,1);
	
	m_dateBegin = new QLabel(i18n("Date of begin of the tournament"),form);
	m_grid->addWidget(m_dateBegin, 0,3);
	m_dateTournament = new KDatePicker(form);
	m_grid->addWidget(m_dateTournament, 1,3);
	
	m_nameGameLabel = new QLabel(i18n("Name of game"),form);
	m_nameGame = new KLineEdit(form);
	m_grid->addWidget(m_nameGameLabel, 1,0);
	m_grid->addWidget(m_nameGame, 1,1);
	
	m_dateEnd = new QLabel(i18n("Date end of the tournament"),form);
	m_grid->addWidget(m_dateEnd,2, 3);
	m_endDate = new KDateWidget(form);
	m_grid->addWidget(m_endDate, 3,3);
	
	m_round = new KIntSpinBox(form);
	m_roundsGame = new QLabel(i18n("Rounds for players"),form);
	m_grid->addWidget(m_roundsGame, 2, 0);
	m_grid->addWidget(m_round, 2,1);
	
	m_gamesPair = new KIntSpinBox(form);
	m_gamesPlayers = new QLabel(i18n("Games for pairs"),form);
	m_grid->addWidget(m_gamesPlayers, 3, 0);
	m_grid->addWidget(m_gamesPair, 3,1);
	
	
	
	m_valueInscripLabel = new QLabel(i18n("Value for inscription"),form);
	m_valueInscrip = new KLineEdit(form);
	m_grid->addWidget(m_valueInscripLabel, 4,0);
	m_grid->addWidget(m_valueInscrip, 4,1);
	
	m_discountLabel = new QLabel(i18n("Discount in the inscription"),form);
	m_discountInscrip = new KLineEdit(form);
	m_grid->addWidget(m_discountLabel, 4,2);
	m_grid->addWidget(m_discountInscrip, 4,3);
	
}

void FormTournament::accept ()
{
	
}

void FormTournament::cancel()
{
}


void FormTournament::fillField(QString nameTournament, QString nameGame, double inscription, double discount)
{

}


#include "formtournament.moc"

