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
 
#include <klocale.h>
#include <qxml.h>

#include "formparticipants.h"
#include "kldatabase.h"
#include "klxmlreader.h"


FormParticipants::FormParticipants(const QString &tournament, FormBase::Type t, QWidget *parent)
	: FormBase(t, parent, "FormParticipants"), m_tournament(tournament)
{
	setupForm();
}

FormParticipants::~FormParticipants()
{
}

void FormParticipants::setupForm()
{
	m_clientBox = new QVGroupBox(this);
	QHBox *hbox = new QHBox(m_clientBox);
	
	(new QLabel(i18n("Client identification"), hbox))->setMargin(2);
	
	m_clientIdent = new KComboBox(true, hbox);
	m_clientIdent->setInsertionPolicy(KComboBox::NoInsertion);
	
	connect(m_clientIdent, SIGNAL(returnPressed(const QString &)), this, SLOT(fillClientInformation(const QString &)));
	connect(m_clientIdent, SIGNAL(activated(const QString &)), this, SLOT(fillClientInformation(const QString &)));
	
	m_clientIdent->setAutoCompletion(true);
	
	m_identsList = getAllClients();
	m_clientIdent->completionObject()->setItems(m_identsList);
	m_clientIdent->insertStringList(m_identsList);	
	m_clientIdent->setCompletionMode (KGlobalSettings::CompletionPopupAuto  );
	
	(new QLabel(i18n("Name"), hbox))->setMargin(2);
	m_clientName = new KLineEdit(hbox);
	m_clientName->setReadOnly(true);
	
	(new QLabel(i18n("Last name"), hbox))->setMargin(2);
	m_clientLastName = new KLineEdit(hbox);
	m_clientLastName->setReadOnly(true);
	
	QHBox *hbox2 = new QHBox(m_clientBox);
	
	m_add = new KPushButton(i18n("Add participant"),hbox2);
	connect(m_add, SIGNAL(clicked()), this, SLOT(addParticipant()));
	m_del = new KPushButton(i18n("Remove participant"), hbox2);
	connect(m_del, SIGNAL(clicked()), this, SLOT(removeParticipant()));
	
// 	connect(m_clientIdent,SIGNAL(returnPressed(const QString&)),m_clientIdent->completionObject(),SLOT(addItem(const QString&)));
	
	m_table = new KLTable(0,3,this);
	m_table->setReadOnly(true);
	m_table->setColumnLabels(QStringList() << i18n("Identification") << i18n("Name") << i18n("Rank") );
	
	m_table->setViewportText(i18n("ADD PARTICIPANTS"));
	
	m_clientIdent->clearEdit();
}

QStringList FormParticipants::getAllClients()
{
	// Sacamos los ids de clientes
	KLSelect sqlquery(QStringList() << "docident", QString("ldt_clients"));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	return xmlreader.getResultsList();
}

void FormParticipants::setTournament(const QString &tournament)
{
	m_tournament = tournament;
}

void FormParticipants::fillClientInformation(const QString &key)
{
	KLSelect sqlquery(QStringList() << "firstname" << "lastname", QString("ldt_clients_view"));
	sqlquery.setWhere("docident="+SQLSTR(key));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	KLSqlResults results = xmlreader.results();
	m_clientName->setText(results["firstname"]);
	m_clientLastName->setText(results["lastname"]);
}

void FormParticipants::accept()
{
	QStringList added;
	for(uint i = 0; i < m_table->numRows(); i++)
	{
		QStringList values = QStringList() << SQLSTR(m_table->text(i, 0)) << SQLSTR(m_tournament) << SQLSTR(m_table->text(i, 2));
		KLInsert sqlins("ldt_participates", values);
		KLDM->execQuery(&sqlins);
		added << SQLSTR(m_table->text(i, 0));
	}
	
	for(uint i = 0; i < m_delList.count(); i++)
	{
		if( added.findIndex(m_delList[i]) == -1 )
		{
			KLDelete sqldel(QString("ldt_participates"));
			sqldel.setWhere("clientdocident="+m_delList[i]);
			sqldel.setCondition("and codTournament="+SQLSTR(m_tournament));
			KLDM->execQuery(&sqldel);
		}
	}
	
	m_delList.clear();
	added.clear();
	emit accepted();
}

void FormParticipants::cancel()
{
	emit cancelled();
}

void FormParticipants::clean()
{
}

void FormParticipants::addParticipant()
{
	if( m_clientIdent->currentText().isEmpty() )
		return;
	QStringList data = QStringList() << m_clientIdent->currentText() << QString("%1 %2").arg(m_clientName->text()).arg(m_clientLastName->text()) << "1";
	m_table->insertRowData(data);
	m_table->viewport()->repaint();
	
	m_clientIdent->removeItem(m_clientIdent->currentItem());
	m_clientIdent->clearEdit();
	m_clientName->setText("");
	m_clientLastName->setText("");
}

void FormParticipants::removeParticipant()
{
	m_clientIdent->insertItem(m_table->text(m_table->currentRow(), 0));
	
	m_delList << SQLSTR(m_table->text(m_table->currentRow(), 0));
	
	m_clientIdent->clearEdit();
	m_table->removeRow(m_table->currentRow());
}

void FormParticipants::fillTableInformation()
{
	KLSelect sqlquery(QStringList() << "clientdocident" << "firstname" << "lastname" << "rank", QStringList() << "ldt_participates" << "ldt_clients_view");
	sqlquery.setWhere("codtournament="+SQLSTR(m_tournament));
	sqlquery.setCondition("and clientdocident");
	KLSelect subquery(QStringList() << "docIdent", QString("ldt_participates"));
	sqlquery.addSubConsult("in", subquery);
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
	QStringList results = xmlreader.getResultsList();
	
	int count = 0;
	for(uint i = 0; i < results.count() / 4; i++)
	{
		QStringList data = QStringList() << results[count++] << results[count++]+" " +results[count++] << results[count++];
		
		int indexL = m_identsList.findIndex(data[0]);
		if ( indexL != -1)
		{
			m_clientIdent->removeItem(indexL);
			m_identsList.remove(data[0]);
		}
		
		m_table->insertRowData(data);
	}
	m_clientIdent->clearEdit();
}

#include "formparticipants.moc"
