/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        	   *
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
#include "tournamentwidget.h"
#include <klocale.h>
#include <qscrollview.h>

TournamentWidget::TournamentWidget(QWidget *padre) : LTToolBox(padre, "Tournament")
{
	setCaption(i18n("Tournament"));
	setupTabs();
}


TournamentWidget::~TournamentWidget()
{
}

void TournamentWidget::setupTabs()
{
	m_adminTournament = new AdminTournament(this);
	addItem(m_adminTournament, i18n("Admin"));
	
	KPushButton *buttonAdd = new KPushButton(i18n("Add a tournament"), this);
	this->addItem(buttonAdd, i18n("Add"));
	connect(buttonAdd, SIGNAL(clicked()), this, SLOT(addTournament()));
	
	m_tournamentActive = new TournamentActive(this);
	this->addItem(m_tournamentActive, i18n("Active"));
	
	m_tournamentOld = new TournamentOld(this);
	this->addItem(m_tournamentOld, i18n("Old"));
}

void TournamentWidget::addTournament()
{
	KMdiChildView *view = new KMdiChildView(i18n("Add tournament"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	FormTournament *formAdminTournament = new FormTournament( scroll->viewport() );
	scroll->addChild(formAdminTournament);

	formAdminTournament->setTitle(i18n("Add a tournament"));
	formAdminTournament->setExplanation(i18n("Fill the fields with the new tournament information"));
	
	emit sendWidget(view);
}

#include "tournamentwidget.moc"
