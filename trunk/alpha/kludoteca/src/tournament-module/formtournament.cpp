/***************************************************************************
 *   Copyright (C) 2005 by Juliana Davila - David Cuadrado                 *
 *   krawek@gmail.com                                                      *
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
#include "klxmlreader.h"

#define DEBUG_FORMTOUR 0

FormTournament::FormTournament(Type t, QWidget *parent) : FormBase(t, parent, "FormTournament")
{
	setupForm();
 	this->setupButtons(FormBase::AcceptButton, FormBase::CancelButton);
}


FormTournament::~FormTournament()
{
}

void FormTournament::setupForm()
{
	m_form = new QFrame(this);
	m_form->setLineWidth(3);
	m_form->setFrameShape(QFrame::Box);
	m_grid = new QGridLayout(m_form,7,4,10);
	
	QLabel *nameTourLabel = new QLabel(i18n("Name of tournament"),m_form);
	KLineEdit *nameTournament = new KLineEdit(m_form);
	m_lineEdits.insert("name", nameTournament);
	
	m_grid->addWidget(nameTourLabel, 0,0);
	m_grid->addWidget(nameTournament, 0,1);
	
	QLabel *dateBegin = new QLabel(i18n("Date of begin of the tournament"),m_form);
	
	m_grid->addWidget(dateBegin, 0,3);
	m_dateTournament = new KDatePicker(m_form, QDate::currentDate());
	
	m_grid->addWidget(m_dateTournament, 1,3);
	
	setupGames();
	
	QLabel *dateEnd = new QLabel(i18n("Date end of the tournament"),m_form);
	m_grid->addWidget(dateEnd,2, 3);
	m_endDate = new KDateWidget(m_form);
	m_endDate->setDate(QDate::currentDate ());
	m_grid->addWidget(m_endDate, 3,3);
	
	m_round = new KIntSpinBox(m_form);

	QLabel *roundsGame = new QLabel(i18n("Rounds for players"),m_form);
	m_grid->addWidget(roundsGame, 2, 0);
	m_grid->addWidget(m_round, 2,1);
	
	m_gamesPair = new KIntSpinBox(m_form);
	QLabel *gamesPlayers = new QLabel(i18n("Games for pairs"),m_form);
	m_grid->addWidget(gamesPlayers, 3, 0);
	m_grid->addWidget(m_gamesPair, 3,1);
	
	
	
	QLabel *valueInscripLabel = new QLabel(i18n("Value for inscription"),m_form);
	KLineEdit *valueInscrip = new KLineEdit(m_form);
	m_lineEdits.insert("price", valueInscrip);
	m_grid->addWidget(valueInscripLabel, 4,0);
	m_grid->addWidget(valueInscrip, 4,1);
	
	QLabel *discountLabel = new QLabel(i18n("Discount in the inscription"),m_form);
	KLineEdit *discountInscrip = new KLineEdit(m_form);
	m_lineEdits.insert("discount", discountInscrip);
	m_grid->addWidget(discountLabel, 4,2);
	m_grid->addWidget(discountInscrip, 4,3);
	
	connect(m_dateTournament, SIGNAL(dateChanged (QDate)), this, SLOT(initDateChanged(QDate)));
	connect (m_round, SIGNAL(valueChanged ( int )), m_gamesPair, SLOT(setValue(int)));
}

void FormTournament::initDateChanged(QDate date)
{
	m_endDate->setDate(date);
}

void FormTournament::setupGames()
{
	// TODO: Consultar la base de datos para sacar los nombres de los juegos
	QLabel *nameGameLabel = new QLabel(i18n("Name of game"),m_form);
	
	m_nameGame = new KComboBox(m_form);
	
	KLSelect sqlquery(QStringList() << "gamename", QString("ldt_games"));
	sqlquery.setWhere("available");
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	m_nameGame->insertStringList(xmlreader.getResultsList());
	
	m_grid->addWidget(nameGameLabel, 1,0);
	m_grid->addWidget(m_nameGame, 1,1);
}

QString FormTournament::gameName2code(const QString &gamename)
{
	KLSelect sqlquery(QStringList() << "serialreference", QString("ldt_games") );
	sqlquery.setWhere("gamename="+SQLSTR(gamename));
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	KLXmlReader xmlreader;
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return "";
	}
	return xmlreader.getResultsList()[0];
}

void FormTournament::accept ()
{
	switch(getType())
	{
		case Add:
		{
 			KLInsert sqlquery("ldt_tournament", QStringList()
				<< SQLSTR( getTournamentName() )
				<< SQLSTR( gameName2code(m_nameGame->currentText() ))
				<< SQLSTR( this->getInitDate() )
				<< SQLSTR( this->getEndDate() )
				<< SQLSTR( getRounds4pair() )
				<< SQLSTR( getRounds() )
				<< SQLSTR( getPrice() )
				<< SQLSTR( getDiscount() )
				<< SQLSTR( "t" ));
			
			m_nameGame->removeItem(m_nameGame->currentItem ());
			
 			KLDM->execQuery(&sqlquery);
			
			emit inserted(getTournamentName());
			clean();
		}
		break;
		case Edit:
		{
		}
		break;	
	}
}

void FormTournament::cancel()
{
	emit cancelled();
}


void FormTournament::clean()
{
	QDictIterator<KLineEdit> it( m_lineEdits );
	for( ; it.current(); ++it)
		it.current()->setText("");
}

void FormTournament::setTournamentName(const QString &name)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo nombre" << std::endl;
#endif
	m_lineEdits["name"]->setText(name);
}

void FormTournament::setRounds(const QString &rounds)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo rondas" << std::endl;
#endif
	m_round->setValue(rounds.toInt());
}

void FormTournament::setRounds4pair(const QString &rounds)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo rounds4pair" << std::endl;
#endif
	m_gamesPair->setValue(rounds.toInt());
}

void FormTournament::setPrice(const QString &price)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo price" << std::endl;
#endif
	m_lineEdits["price"]->setText(price);
}

void FormTournament::setDiscount(const QString &discount)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo discount" << std::endl;
#endif
	m_lineEdits["discount"]->setText(discount);
}

void FormTournament::setInitDate(const QDate &date)
{
#if DEBUG_FORMTOUR
std::cout << "Opniendo initdate" << std::endl;
#endif
	m_dateTournament->setDate(date);
}

void FormTournament::setEndDate(const QDate &date)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo endate" << std::endl;
#endif
	m_endDate->setDate(date);
}

QString FormTournament::getTournamentName()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo nombre " << m_lineEdits.count() << std::endl;
#endif

	return m_lineEdits["name"]->text();
}

QString FormTournament::getRounds()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo rounds" << std::endl;
#endif
	return QString::number(m_round->value());
}

QString FormTournament::getRounds4pair()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo rounds4pair" << std::endl;
#endif
	return QString::number(m_gamesPair->value());
}

QString FormTournament::getPrice()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo price" << std::endl;
#endif
	return m_lineEdits["price"]->text();	
}

QString FormTournament::getDiscount()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo discount" << std::endl;
#endif
	return m_lineEdits["discount"]->text();
}

QString FormTournament::getInitDate()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo initdate" << std::endl;
#endif
	return m_dateTournament->date().toString(Qt::ISODate);
}

QString FormTournament::getEndDate()
{
#if DEBUG_FORMTOUR
std::cout << "Obteniendo enddate" << std::endl;
#endif
	return m_endDate->date().toString(Qt::ISODate);
}

#include "formtournament.moc"

