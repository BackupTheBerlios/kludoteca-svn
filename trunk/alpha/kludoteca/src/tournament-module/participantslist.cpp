/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                                 	   *
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
#include "participantslist.h"
#include <klocale.h>

#define DEBUG_PARTICIPANTS 1

ParticipantsList::ParticipantsList(QWidget *parent, const char *name) : LTListView(QStringList() << i18n("Tournament") << i18n("Client") << i18n("Rank"), LTListView::ButtonAdd, LTListView::ButtonQuery, LTListView::NoButton, LTListView::NoButton, parent, name)
{
	setCaption(i18n("Participants"));
	m_listView->setRootIsDecorated(true);
	this->setButtonText(LTListView::ButtonAdd, i18n("Manage"));
}


ParticipantsList::~ParticipantsList()
{
}

// Debo llenar la lista separada por torneo.
void ParticipantsList::fillList()
{
#if DEBUG_PARTICIPANTS
	qDebug("Fill List");
#endif
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
		KListViewItem *tourtemp = new KListViewItem(m_listView);
		tourtemp->setText(0, tournaments[i]);
// 		tourtemp->setOpen(true);
		
		KLSelect sqlquery(QStringList() << "clientdocident" << "rank", QStringList() << "ldt_participates");
		sqlquery.setWhere("codtournament="+SQLSTR(tournaments[i]));
		sqlquery.setOrderBy("rank", KLSelect::Asc);
	
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
		m_xmlsource.setData(resultSet.toString());
		if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
		{
			std::cout << "No se pudo analizar!!!" << std::endl;
		}
		
		QStringList participants = m_xmlreader.getResultsList();
		
		for (uint j = 0; j < participants.count(); j+=2)
		{
			std::cout << "Adicionando: " << participants[j] << std::endl;
			m_participants << participants[j];
			KListViewItem *parttemp = new KListViewItem(tourtemp);

			parttemp->setText(1, participants[j]);
			parttemp->setText(2, participants[j+1]);
			tourtemp->insertItem(parttemp);
		}
	}
}

void ParticipantsList::addButtonClicked()
{
	QListViewItem *le = m_listView->currentItem();
	if ( !le )
		return;
	
	QString tname = le->text(0);
	if ( tname.isNull() )
		tname = le->parent()->text(0);
	
	std::cout << "Adicionando participantes torneo: " << tname << std::endl;
	
	

	KMdiChildView *view = new KMdiChildView(i18n("Add participants to %1").arg(tname), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );

	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);
	
	FormParticipants *formParticipantsList = new FormParticipants(tname, FormBase::Any, scroll->viewport() );
	formParticipantsList->fillTableInformation();
	connect(formParticipantsList, SIGNAL(message2osd(const QString& )) , this, SIGNAL(message2osd(const QString& )));
	
	connect(formParticipantsList, SIGNAL(cancelled()), view, SLOT(close()));
	connect(formParticipantsList, SIGNAL(accepted()), this, SIGNAL(tournamentModified()));

	scroll->addChild(formParticipantsList);
	formParticipantsList->setupButtons( FormBase::AcceptButton, FormBase::CancelButton );

	formParticipantsList->setTitle(i18n("Admin %1 Participants").arg(tname));
	formParticipantsList->setExplanation(i18n("Fill the fields with the participants information"));
	
	emit sendWidget(view); 
}

void ParticipantsList::delButtonClicked()
{
}

void ParticipantsList::getClickedItem(QListViewItem *item)
{
	modifyButtonClicked();
}

void ParticipantsList::modifyButtonClicked()
{
}

#include "klreportwidget.h"

void ParticipantsList::queryButtonClicked()
{
	QListViewItem *le = m_listView->currentItem();
	if ( !le )
		return;
	
	QString tname = le->text(0);
	if ( tname.isNull() )
		tname = le->parent()->text(0);

	KMdiChildView *view = new KMdiChildView(i18n("Gamers reports"), this );
	( new QVBoxLayout( view ) )->setAutoAdd( true );
	
	QScrollView *scroll = new QScrollView(view);
	scroll->setResizePolicy(QScrollView::AutoOneFit);
	scroll->setMargin(10);

	KLReportWidget *reportRanks = new KLReportWidget( scroll->viewport() );
	
	KLSelect sqlquery(QStringList() << "participant" << "total", QStringList() << "ldt_resultstable_view");
	sqlquery.setWhere("tournament="+SQLSTR(tname));
	sqlquery.setOrderBy("total", KLSelect::Desc);
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	QStringList results = xmlreader.getResultsList();
	
	KLXmlReport xmlreport(i18n("Report ranking"), klenterprise->getName(), klenterprise->getNit(), KLXmlReport::PIE );
	
	for ( int i = 0; i < results.count(); i+=2 )
	{
		double x = (double(i) / 100) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((i * 17) % 105) + 151;
		
		xmlreport.createReportElement( results[i+1].toDouble(), results[i], QColor( int(x), y, z, QColor::Hsv ));
	}
	
	reportRanks->setXmlReport(xmlreport);
	
	connect(reportRanks, SIGNAL(cancelled()), view, SLOT(close()));
	
	scroll->addChild(reportRanks);
		
	emit sendWidget(view); 
}

void ParticipantsList::addItem(const QString &pkey)
{
	std::cout << "Adicionando item con pkey: " << pkey << std::endl;
	
	fillList();
}

void ParticipantsList::updateItem(const QString &pkey)
{
	delete m_listView->currentItem();
	addItem(pkey);
}

void ParticipantsList::slotFilter(const QString &filter)
{
	std::cout << "Filtrando filter " << filter << std::endl;
	
	if ( filter.isEmpty() )
	{
		fillList();
	}
	else
	{
		m_listView->clear();
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
			KListViewItem *tourtemp = new KListViewItem(m_listView);
			tourtemp->setText(0, tournaments[i]);
		
			KLSelect sqlquery(QStringList() << "clientdocident" << "rank", QStringList() << "ldt_participates");
			sqlquery.setWhere("codtournament="+SQLSTR(tournaments[i]));
// 			sqlquery.addFilter(filter, QStringList() << "clientdocident");
			sqlquery.setCondition("and clientdocident ~* "+SQLSTR(filter) );
	
			KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
			m_xmlsource.setData(resultSet.toString());
			if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) ) // Necesito adicionar manualemente los elementos
			{
				std::cout << "No se pudo analizar!!!" << std::endl;
			}
		
			QStringList participants = m_xmlreader.getResultsList();
		
			std::cout << "Tamaño participantes: " << participants.count() << std::endl;
			for (uint j = 0; j < participants.count(); j+=2)
			{
				std::cout << "Adicionando: " << participants[j] << std::endl;
				KListViewItem *parttemp = new KListViewItem(tourtemp);

				parttemp->setText(1, participants[j]);
				parttemp->setText(2, participants[j+1]);
				tourtemp->insertItem(parttemp);
			}
			
			tourtemp->setOpen(true);
		}
	}
}

#include "participantslist.moc"
