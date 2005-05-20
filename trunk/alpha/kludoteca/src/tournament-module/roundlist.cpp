/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                           	   *
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

#include "roundlist.h"
#include "formmatchorder.h"s
#include <klocale.h>

RoundList::RoundList(QWidget *parent, const char *name)
	: LTListView(QStringList() << i18n("Tournament") << i18n("Ronda"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent, name)
{
	setButtonText(LTListView::ButtonAdd, i18n("New"));
	setButtonText(LTListView::ButtonQuery, i18n("Update"));
	m_listView->setRootIsDecorated(true);
	m_listView->setSorting(1);
}


RoundList::~RoundList()
{}


void RoundList::fillList()
{
	m_listView->clear();
	// SELECT codtournament from ldt_participates where codtournament in (select name from ldt_tournament );
	KLSelect sqltour (QStringList()  << "name", QString("ldt_tournament"));
	
	KLResultSet tourResults = KLDM->execQuery(&sqltour);
	m_xmlsource.setData(tourResults.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
	{
		std::cout << "No se pudo analizar!!!" << std::endl;
	}
	
	QStringList tournaments = m_xmlreader.getResultsList();
	
	// Es hora de adicionar los elementos a la lista
	for (uint i = 0; i < tournaments.count(); i++)
	{
		LTListViewItem *tourtemp = new LTListViewItem(m_listView);
		tourtemp->setText(0, tournaments[i]);
// 		tourtemp->setOpen(true);
		
 		KLSelect sqlquery(QStringList() << "nround", QStringList() << "ldt_rounds");
 		sqlquery.setWhere("codtournament="+SQLSTR(tournaments[i]));
	
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
		
		QStringList nrounds = m_xmlreader.getResultsList();
		
		for (uint j = 0; j < nrounds.count(); j++)
		{
			LTListViewItem *parttemp = new LTListViewItem(tourtemp);

			parttemp->setText(1, nrounds[j]);
			tourtemp->insertItem(parttemp);
		}
	}
}

void RoundList::addButtonClicked()
{
	LTListViewItem *le = static_cast<LTListViewItem*>(m_listView->currentItem());
	if ( !le )
		return;
	
	QString tname = le->text(0);
	
	int roundNumber = 0;
	
	if ( tname.isNull() )
	{
		// Estoy sobre un hijo
		tname = le->parent()->text(0);
		LTListViewItem *nround = new LTListViewItem(le->parent());
		
		roundNumber = le->parent()->childCount();
		
		nround->setText( 1, QString::number(roundNumber));
		le->parent()->insertItem(nround);
		le->parent()->sortChildItems(1, true);
	}
	else
	{
		// Sobre el padre
		LTListViewItem *nround = new LTListViewItem(le);
		roundNumber = le->childCount();
		nround->setText( 1, QString::number(roundNumber));
		
		le->insertItem(nround);
		le->sortChildItems(1, true);
	}
	
	// La idea de este bloque es seguir una secuencia de rondas
	
	KMdiChildView *view = new KMdiChildView(i18n("Add matchs to %1").arg(tname), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormMatchOrder *formMatchs = new FormMatchOrder(FormBase::Add, this);
	
// 	connect(formMatchs, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	connect(formMatchs, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formMatchs, SIGNAL(accepted()), this, SLOT(fillList()));

	scroll->addChild(formMatchs);
	formMatchs->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );

	formMatchs->setTitle(i18n("Manage %1 matchs for the %2 round").arg(tname).arg(roundNumber));
	formMatchs->setExplanation(i18n("Fill the fields with the match's results"));
	
	emit sendWidget(view); 
}

void RoundList::delButtonClicked()
{
}

void RoundList::getClickedItem(QListViewItem* item)
{
}

void RoundList::modifyButtonClicked()
{
}

void RoundList::queryButtonClicked()
{
}

#include "roundlist.moc"
