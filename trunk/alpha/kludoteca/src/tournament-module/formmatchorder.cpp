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
#include "klxmlreader.h"
#include "klresultset.h"

#include <klocale.h>
#include <iostream>
#include <qstringlist.h>

#include <qpaintdevicemetrics.h>
#include <qstylesheet.h>

#include <qapplication.h>
#include <qsimplerichtext.h>

FormMatchOrder::FormMatchOrder(const QString &tournament, int nround, FormBase::Type t, QWidget *parent)
	: FormBase(t, parent, "FormMatchOrder"), m_tournament(tournament) ,m_nround(nround)
{
	qDebug("[Initializing FormMatchOrder]");
	switch(t)
	{
		case Add:
		{
		}
		break;
		case Edit:
		{
			setTitle(i18n("Manage %1 matchs for the %2 round").arg(tournament).arg(nround));
			setExplanation(i18n("Fill the fields with the match's results<br> <div align=center> <b>NOTE:</b> Results are respect to the first opponent </div>"));
		}
	}
	setupForm();
}


FormMatchOrder::~FormMatchOrder()
{
}

void FormMatchOrder::print( QPainter *painter, KPrinter &printer)
{
	qDebug("Printing tournament inpair");
	
	QPaintDeviceMetrics metrics(&printer);
	int LargeGap = metrics.logicalDpiY() / 2;
	
	QString str = QString(
			"<div align=center>"
			"<h3>"+m_tournament+"</h3></div>" );
	
	str += "<table width=\"100%\" border=1 cellspacing=0>\n"
			"<caption align=bottom>" + i18n("Results Table") + "</caption>\n";

	// Encabezados
	str += "<tr>";
	for(uint col = 0; col < m_table->numCols()-1; col++)
	{
		QString header = QStyleSheet::escape(m_table->getColumnTextHeader(col) );
		str += "<th>"+header+"</th>";
	}
	str += "</tr>\n";
	
	// Cuerpo
	for(uint row = 0; row < m_table->numRows(); row++)
	{
		str += "<tr>\n";
		QString opp1 = QStyleSheet::escape(m_table->text(row, 0));
		QString opp2 = QStyleSheet::escape(m_table->text(row, 1));
		
		str += "\t<td>"+opp1+"</td>\n";
		str += "\t<td>"+opp2+"</td>\n";
		
		str += "</tr>\n";
	}
	
	str += "\n</table>\n<br>\n";
	
	
	int pageHeight = painter->window().height() - 2 * LargeGap;
	QSimpleRichText richText(str, QApplication::font(), "", 0, 0, pageHeight);
	
	richText.setWidth( painter, painter->window().width() );

	
	int numPages = (int)ceil((double)richText.height() / pageHeight);
	int index;
	
	for (int i = 0; i < (int)printer.numCopies(); ++i)
	{
		for (int j = 0; j < numPages; ++j)
		{
			if (i > 0 || j > 0)
				printer.newPage();
			if (printer.pageOrder() == KPrinter::LastPageFirst)
			{
				index = numPages - j - 1;
			}
			else 
			{
				index = j;
			}
			
			QRect rect(0, index * pageHeight + LargeGap, richText.width(), pageHeight);
			painter->saveWorldMatrix();
			painter->translate(0, -rect.y());
			
			richText.draw(painter, 0, LargeGap, QRect(), QColorGroup() );
			
			painter->restoreWorldMatrix();
			painter->setFont(QApplication::font());
			painter->drawText(painter->window(), AlignHCenter | AlignBottom, QString::number(index + 1));
		}
	}
	
}


void FormMatchOrder::setupForm()
{
	// filas = participantes / 2
	m_table = new KLTable(0, 3, this, "MatchTable");
	m_table->setColumnReadOnly(0, true);
	m_table->setColumnReadOnly(1, true);
	m_table->setColumnLabels(QStringList() << i18n("Oponnent one") << i18n("Oponnent two") << i18n("Results"));
	
	for(uint i = 0; i < m_table->numRows(); i++)
	{
		QComboTableItem *tcombo = new QComboTableItem(m_table, QStringList() << i18n("Draw") << i18n("Win") << i18n("Lose"), true);
		m_table->setItem(i, 2, tcombo);
	}
	fillTable();
}

QStringList FormMatchOrder::getMatchResult(int number)
{
	// Sacamos en una lista el resultado de la partida numero "number"
	QStringList results = QStringList();
	QComboTableItem *itm = static_cast<QComboTableItem*>(m_table->item(number, 2));
	
	switch(itm->currentItem ())
	{
		case 0: // Empate
		{
			results << "1" << "1";
// 			results << itm->currentText();
		}
		break;
		case 1: // Gana
		{
			results << "3" << "0";
		}
		break;
		case 2: // Pierde
		{
			results << "0" << "3";
		}
		break;
	}
	qDebug(QString("Tamño de la lista retornada: %1").arg(results.count()));
	return results;
}

void FormMatchOrder::accept()
{
	qDebug("In accept");
	switch( getType() )
	{
		case Add:
		{
			KLDM->execQuery(new KLInsert("ldt_rounds", QStringList() << QString::number(m_nround) << SQLSTR(m_tournament)));
			
			int parts = m_table->numRows();
			if( !m_restParticipant.isEmpty() )
			{
				parts -= 1;
			}
			
			for (uint i = 0; i < parts; i++)
			{
				QStringList results = this->getMatchResult(i);
				
// 				std::cout << i << "Ronda -1: " << (m_nround-1);
// 				std::cout << " count " << results.count();
				
				QStringList values = QStringList()
						<< QString::number((m_nround-1)*parts+i)
						<< QString::number(m_nround)
						<< SQLSTR(m_tournament)
						<< SQLSTR(m_table->text(i, 0)) // Oponente 1
						<< results[0]
						<< SQLSTR(m_table->text(i, 1))
						<< results[1];
				
				KLInsert sqlins("ldt_match", values);
				KLDM->execQuery(&sqlins);
			}
			
			if ( ! m_restParticipant.isEmpty() )
			{
// 				KLUpdate update("ldt_match", QStringList() << "rest", QStringList() << SQLSTR("t") );
// 				update.setWhere(QString("nround=%1 and codtournament=%2 and opponent1=%3").arg(SQLSTR(m_nround)).arg(SQLSTR(m_tournament)).arg(SQLSTR(lastOdd)) );
// 				KLDM->execQuery(&update);
				
				QStringList values = QStringList()
				<< QString::number((m_nround-1)*m_table->numRows()*2+m_table->numRows()-1)
					<< QString::number(m_nround)
					<< SQLSTR(m_tournament)
					<< SQLSTR(m_table->text(m_table->numRows()-1, 0))
					<< "1"
					<< SQLSTR("") << SQLSTR("")
						<< SQLSTR("t");
				KLInsert sqlins("ldt_match", values);
				KLDM->execQuery(&sqlins);
			
			}
			
			emit message2osd(i18n("Results registred"));
			
			emit inserted(QString::number(m_nround));
		}
		break;
		case Edit:
		{
			int parts = m_table->numRows();
			if( !m_restParticipant.isEmpty() )
			{
				parts -= 1;
			}
			
			for (uint i = 0; i < parts; i++)
			{
				QStringList results = this->getMatchResult(i);
				QStringList values = QStringList() << results[0] << results[1];
				
				KLUpdate sqlup("ldt_match", QStringList() << "resultopp1" << "resultopp2", values);
				sqlup.setWhere(QString("number=%1").arg(i));
				KLDM->execQuery(&sqlup);
			}
		}
		break;
	}
	updateRanks(m_clientList);
	
	emit accepted();
	emit cancelled();
	qDebug("End accept");
}

void FormMatchOrder::cancel()
{
	emit accepted();
	FormBase::cancel();
}

void FormMatchOrder::clean()
{
}

void FormMatchOrder::fillTable()
{
	KLSelect sqlquery(QStringList() << "clientdocident" << "firstname" << "lastname" << "rank", QStringList() << "ldt_participates" << "ldt_clients_view");
	sqlquery.setWhere("codtournament="+SQLSTR(m_tournament));
	sqlquery.setCondition("and clientdocident");
	KLSelect subquery(QStringList() << "docIdent", QString("ldt_participates"));
	sqlquery.addSubConsult("in", subquery);
	sqlquery.setOrderBy("rank", KLSelect::Asc);
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
	}
	
 	m_clientList = getMatchClientInfo(xmlreader.getResultsList(), 4);
	
	if(getType() == Add)
	{
		MatchGenerator mg(m_clientList, m_tournament);
		
		QStringList results = mg.generate(m_nround, MatchGenerator::Ascending);
		
		for(uint i = 0; i < results.count(); i++)
		{
			std::cout << "DEBUG: " << results[i] << std::endl;
		}
		
		QString lastOdd = "";
	
		if( results.count() % 2 != 0) // TODO: Los participantes son impares, debemos dar 1/2 punto al ultimo participante y removerlo de la lista, pero no podemos repetir
		{
			lastOdd = results.last();
			results.pop_back();
		}
		
		int row = 0;
	
		for (uint i = 0; i < results.count(); i+=2) // Parejas
		{
			std::cout << "UHM: " << results[i] << std::endl;
			m_table->insertRowData(QStringList() << results[i] << results[i+1]);
			
			QComboTableItem *tcombo = new QComboTableItem(m_table, QStringList() << i18n("Draw") << i18n("Win") << i18n("Lose"), false);
			
			m_table->setItem(row, 2, tcombo);
			row++;
		}
		
		if ( !lastOdd.isEmpty() )
		{
			m_table->insertRowData(QStringList() << lastOdd << "" << i18n("Rest") );
			m_table->paintRow(m_table->numRows()-1, QColor(151,4,38) );
			m_table->setRowReadOnly(m_table->numRows()-1, true);
			m_restParticipant = lastOdd;
		}
	}
	else if (getType() == Edit)
	{
		// Sacar los ids, resultados de m_tournament y m_nround
		KLSelect sqlquery(QStringList() << "opponent1" << "opponent2" << "resultopp1", QStringList() << "ldt_match");
		sqlquery.setWhere("codtournament="+SQLSTR(m_tournament));
		sqlquery.setCondition("and nround="+SQLSTR(m_nround)+" and not rest");
		
		KLResultSet resultSet = KLDM->execQuery(&sqlquery);
		QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
		KLXmlReader xmlreader;
	
		if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
		{
			std::cerr << "No se puede analizar" << std::endl;
		}
		
		QStringList results = xmlreader.getResultsList();
		
		int row = 0;
		for (uint i = 0; i < results.count(); i+=3) // Parejas
		{
			m_table->insertRowData(QStringList() << results[i] << results[i+1]);
			
			QComboTableItem *tcombo = new QComboTableItem(m_table, QStringList() << i18n("Draw") << i18n("Win") << i18n("Lose"), false);
			
			switch(results[i+2].toInt())
			{
				case 0: // Perdio
				{
					tcombo->setCurrentItem(2);
				}
				break;
				case 1: // Empate
				{
					tcombo->setCurrentItem(0);
				}
				break;
				case 3: // Gano
				{
					tcombo->setCurrentItem(1);
				}
				break;
			}
			
			m_table->setItem(row, 2, tcombo);
			
			row++;
		}
	}
}

// La idea es que saquemos los mayores puntajes de ldt_resultstable_view y los pongamos en el rank de ldt_participates, esta vista tiene elementos nulos, por lo que primero hay que verificarlo!
void FormMatchOrder::updateRanks(const QStringList &clients)
{
	std::cout << "UPDATING RANKS" << std::endl;
	
	KLSelect query(QStringList() << "participant", QString("ldt_resultstable_view"));
	query.setWhere("tournament="+SQLSTR(m_tournament));
	query.setOrderBy("total", KLSelect::Desc);
	
	KLResultSet resultSet = KLDM->execQuery(&query);

	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;

	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = xmlreader.getResultsList();
	
	for(uint i = 0; i < results.count(); i++) // La lista viene ordenada!
	{
		KLUpdate sqlupdate("ldt_participates", QStringList() << "rank", QStringList() << SQLSTR(QString::number(i+1)) );
		sqlupdate.setWhere("clientdocident="+SQLSTR(results[i]));
		
		KLDM->execQuery(&sqlupdate);
	}
}

QStringList FormMatchOrder::getMatchClientInfo(const QStringList &results, int pos)
{
	QStringList tmp;
	for(uint i = 0; i < results.count(); i+= pos)
	{
		tmp << results[i];
	}
	return tmp;
}

#include "formmatchorder.moc"
