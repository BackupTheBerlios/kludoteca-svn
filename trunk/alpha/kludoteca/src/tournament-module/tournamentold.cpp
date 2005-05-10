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

#define DEBUG_TOURNAMENTOLD 0
 
#include "tournamentold.h"
#include <klocale.h>

TournamentOld::TournamentOld(QWidget *parent) : LTListView(QStringList() << i18n("Tournament name") << i18n("Game") << i18n("Date"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent = 0, "OldTournaments")
{
	setCaption(i18n("Tournament Old"));	
}


TournamentOld::~TournamentOld()
{
}

void TournamentOld::addButtonClicked()
{
#if DEBUG_TOURNAMENTOLD
	qDebug("TournamentOld: init addButtonClicked");
#endif
	KMdiChildView *view = new KMdiChildView(i18n("Add user"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
// 	FormTournament* formTournament = new FormTournament(m_db, scroll->viewport() );
// 	connect(formTournament, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
// 
// 	formTournament->setType( FormBase::Add);
// 	connect(formTournament, SIGNAL(cancelled()), view, SLOT(close()));
// 	connect(formTournament, SIGNAL(inserted(const QString& )), this, SLOT(addItem( const QString& )));
// 
// 	scroll->addChild(formTournament);
// 	formTournament->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
// 
// 	formTournament->setTitle(i18n("Admin User"));
// 	formTournament->setExplanation(i18n("Fill the fields with the user information"));
	
	emit sendWidget(view); 
#if DEBUG_TOURNAMENTOLD
	qDebug("TournamentOld: end addButtonClicked");
#endif
}

void TournamentOld::delButtonClicked()
{
}

void TournamentOld::modifyButtonClicked()
{
}

void TournamentOld::queryButtonClicked()
{
}

void TournamentOld::fillList()
{
	/*
	if ( !m_db )
	{
	qDebug("You're need set the database!!");
	return;
}
	
	KLResultSet resultSet = m_db->select(QStringList() << "firstname" << "lastname", "ldt_clients");
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.parse(m_xmlsource) )
	{
	std::cout << "No se pudo analizar!!!" << std::endl;
}
	*/
}

void TournamentOld::getClickedItem(QListViewItem *item)
{
}

#include "tournamentold.moc"
