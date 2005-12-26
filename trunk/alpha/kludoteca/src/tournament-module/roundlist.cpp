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
#include "formmatchorder.h"
#include <klocale.h>

RoundList::RoundList(QWidget *parent, const char *name)
	: LTListView(QStringList() << i18n("Tournament") << i18n("Ronda"), LTListView::ButtonAdd, LTListView::ButtonModify, LTListView::NoButton, LTListView::NoButton, parent, name)
{
	setButtonText(LTListView::ButtonAdd, i18n("New"));
	setButtonText(LTListView::ButtonModify, i18n("Update"));
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
	sqltour.setWhere("active");
	
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
		tourtemp->setOpen(true);
		
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
	qDebug("Adding a round");
	LTListViewItem *le = static_cast<LTListViewItem*>(m_listView->currentItem());
	if ( !le )
		return;
	
	QString tname = le->text(0);
	
	int roundNumber = 1;
	
	if ( tname.isNull() )
	{
		// Estoy sobre un hijo
		tname = le->parent()->text(0);
		roundNumber = le->parent()->childCount()+1;
		
		if ( tournamentFinished(tname, roundNumber) )
		{
			KLUpdate update("ldt_tournament", QStringList() << "active", QStringList() << SQLSTR("f"));
			KLDM->execQuery(&update);
			KMessageBox::information(this, i18n("The tournament has finished!!"));
			return;
		}
		
		LTListViewItem *nround = new LTListViewItem(le->parent());
		
		nround->setText( 1, QString::number(roundNumber));
		le->parent()->insertItem(nround);
		le->parent()->sortChildItems(1, true);
	}
	else
	{
		// Sobre el padre
		roundNumber = le->childCount() + 1;
		
		if ( tournamentFinished(tname, roundNumber))
		{
			KLUpdate update("ldt_tournament", QStringList() << "active", QStringList() << SQLSTR("f"));
			KLDM->execQuery(&update);
			KMessageBox::information(this, i18n("The tournament has finished!!"));
			return;
		}
		
		LTListViewItem *nround = new LTListViewItem(le);
		nround->setText( 1, QString::number(roundNumber));
		
		le->insertItem(nround);
		le->sortChildItems(1, true);
	}
	
	// Insertamos la ronda
	// TODO: Mensaje de advertencia que pregunta si en realidad quiere
	
	// La idea de este bloque es seguir una secuencia de rondas
	
	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	std::cout << "RONDA: " << roundNumber << std::endl;
	FormMatchOrder *formMatchs = new FormMatchOrder(tname, roundNumber, FormBase::Add, this);
	
 	connect(formMatchs, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	connect(formMatchs, SIGNAL(cancelled()), scroll, SLOT(close()));
	connect(formMatchs, SIGNAL(accepted()), this, SIGNAL(tournamentModified()));

	scroll->addChild(formMatchs);
	formMatchs->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );

	formMatchs->setTitle(i18n("Manage %1 matchs for the %2 round").arg(tname).arg(roundNumber));
	formMatchs->setExplanation(i18n("Fill the fields with the match's results"));
	
	emit sendWidget(scroll, i18n("Add matchs to %1").arg(tname));
}

void RoundList::delButtonClicked()
{
	// No es usado
}

void RoundList::getClickedItem(QListViewItem* item)
{
}

void RoundList::modifyButtonClicked()
{
	LTListViewItem *le = static_cast<LTListViewItem*>(m_listView->currentItem());
	if ( !le )
		return;
	
	QString tname = le->text(0);
	
	int roundNumber = 1;
	
	if ( tname.isNull() )
	{
		// Estoy sobre un hijo
		tname = le->parent()->text(0);
		roundNumber = le->parent()->childCount();
	}
	else
	{
		// Sobre el padre
		roundNumber = le->childCount();
	}
	
	QScrollView *scroll = new QScrollView(this, 0, Qt::WDestructiveClose);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormMatchOrder *formMatchs = new FormMatchOrder(tname, roundNumber, FormBase::Edit, this);
	
// 	connect(formMatchs, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	connect(formMatchs, SIGNAL(cancelled()), scroll, SLOT(close()));
// 	connect(formMatchs, SIGNAL(accepted()), this, SLOT(fillList()));

	scroll->addChild(formMatchs);
	formMatchs->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );
	
	emit sendWidget(scroll, i18n("Update matchs to %1").arg(tname));
}

void RoundList::queryButtonClicked()
{
	// No es usado
}

bool RoundList::tournamentFinished(const QString &tname, int round)
{
	KLSelect sqlquery (QStringList() << "rounds", QString("ldt_tournament"));
	sqlquery.setWhere("name="+SQLSTR(tname));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return false;
	}
	
	QStringList results = xmlreader.getResultsList();
	
	if ( round > results[0].toInt())
	{
		return true;
	}
	
	return false;
}


#include "roundlist.moc"
