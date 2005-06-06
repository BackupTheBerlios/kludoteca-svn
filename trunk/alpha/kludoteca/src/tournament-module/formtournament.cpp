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
#include <kmessagebox.h>
#include <qregexp.h>
#include <qvalidator.h>
#include "klxmlreader.h"

#define DEBUG_FORMTOUR 0

FormTournament::FormTournament(Type t, QWidget *parent) : FormBase(t, parent, "FormTournament")
{
	setupForm();
 	this->setupButtons(FormBase::AcceptButton, FormBase::CancelButton);

	if(t == Add )
	{
		setTitle(i18n("Add a tournament"));
		setExplanation(i18n("Fill the fields with the tournament information"));
	}
	else if ( t == Edit )
	{
		setTitle(i18n("Edit a tournament"));
		setExplanation(i18n("Fill the fields with the update tournament information"));
	}
}


FormTournament::~FormTournament()
{
}

void FormTournament::setupForm()
{
	m_form = new QFrame(this);
	m_form->setMargin(60);
	m_form->setLineWidth(3);
	m_form->setFrameStyle(QFrame::Box | QFrame::Raised);
// 	m_grid = new QGridLayout(m_form,7,4,10);
	m_hbox = new QHBox(this);
	
	m_hbox->setMargin(60);
	m_hbox->setLineWidth(3);
	m_hbox->setFrameStyle(QFrame::Box | QFrame::Raised);
	
	
	m_vboxtinfo = new QVBox(m_hbox);
	m_vboxtinfo->setMargin(10);
	
	QLabel *nameTourLabel = new QLabel(i18n("Name of tournament"),m_vboxtinfo);
	KLineEdit *nameTournament = new KLineEdit(m_vboxtinfo);
	m_lineEdits.insert("name", nameTournament);
	
	QVBox *vboxDateBegin = new QVBox(m_hbox);
	vboxDateBegin->setMargin(10);
	QLabel *dateBegin = new QLabel(i18n("Date of begin of the tournament"),vboxDateBegin);
	
	m_dateTournament = new KDatePicker(vboxDateBegin, QDate::currentDate());
	
// 	m_grid->addWidget(vboxDateBegin, 0,1);
	
	setupGames();
	
// 	m_grid->addWidget(vboxDateEnd, 1,1);
	
// 	m_round = new KIntSpinBox(m_form);

// 	QLabel *roundsGame = new QLabel(i18n("Rounds for players"),m_form);
// 	m_grid->addWidget(roundsGame, 2, 0);
// 	m_grid->addWidget(m_round, 2,1);
	
	QLabel *gamesPlayers = new QLabel(i18n("Games for pairs"),m_vboxtinfo);
	m_gamesPair = new KIntSpinBox(m_vboxtinfo);
// 	m_grid->addWidget(gamesPlayers, 3, 0);
// 	m_grid->addWidget(m_gamesPair, 3,1);
	
	
	
	QLabel *valueInscripLabel = new QLabel(i18n("Value for inscription"),m_vboxtinfo);
	KLineEdit *valueInscrip = new KLineEdit(m_vboxtinfo);
	m_lineEdits.insert("price", valueInscrip);
	
	valueInscrip->setValidator(new QRegExpValidator(QRegExp("[1-9]\\d{0,8}"), 0));
	
// 	QLabel *discountLabel = new QLabel(i18n("Discount in the inscription"),m_vboxtinfo);
// 	KLineEdit *discountInscrip = new KLineEdit(m_vboxtinfo);
// 	m_lineEdits.insert("discount", discountInscrip);
// 	discountInscrip->setValidator(new QRegExpValidator(QRegExp("[1-9]\\d{0,8}"),0));
	
	QLabel *dateEnd = new QLabel(i18n("Date end of the tournament"),m_vboxtinfo);
	m_endDate = new KDateWidget(m_vboxtinfo);
	m_endDate->setDate(QDate::currentDate ());
	
	
// 	m_grid->addWidget(m_vboxtinfo, 0,0);
	
	connect(m_dateTournament, SIGNAL(dateChanged (QDate)), this, SLOT(initDateChanged(QDate)));
// 	connect (m_round, SIGNAL(valueChanged ( int )), m_gamesPair, SLOT(setValue(int)));
}

void FormTournament::fillFormulate( const QString &tname )
{
	KLSelect sqlquery(QStringList() << "name" << "gameserialreference" << "initdate" << "enddate" << "roundsforpair" << "rounds" << "price" << "discount" << "active", QStringList() << "ldt_tournament" );
	
	sqlquery.setWhere("ldt_tournament.name="+SQLSTR(tname) );
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	KLXmlReader xmlreader;
	QXmlInputSource xmlsource; xmlsource.setData(resultSet.toString());
	
	if ( ! xmlreader.analizeXml(&xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	KLSqlResults results = xmlreader.results();
	
// 	setDiscount(results["discount"]);
	setEndDate(QDate::fromString(results["enddate"], Qt::ISODate ));
	setInitDate(QDate::fromString(results["initdate"], Qt::ISODate ));
	setPrice(results["price"]);
// 	setRounds(results["price"]);
	setGames4pair(results["roundsforpair"]);
	setTournamentName(tname);
	
}

void FormTournament::initDateChanged(QDate date)
{
	m_endDate->setDate(date);
}

void FormTournament::setupGames()
{
	qDebug("Setup Games");
	QLabel *nameGameLabel = new QLabel(i18n("Name of game"),m_vboxtinfo);
	
	m_nameGame = new KComboBox(m_vboxtinfo);
	
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
	
// 	m_grid->addWidget(nameGameLabel, 3,0);
// 	m_grid->addWidget(m_nameGame, 4,0);
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
	if ( !validateFields())
	{
		return;
	}
	switch(getType())
	{
		case Add:
		{
 			KLInsert sqlquery("ldt_tournament", QStringList()
				<< SQLSTR( getTournamentName() )
				<< SQLSTR( gameName2code(m_nameGame->currentText() ))
				<< SQLSTR( this->getInitDate() )
				<< SQLSTR( this->getEndDate() )
				<< SQLSTR( this->getGames4pair() )
				<< SQLSTR( 0 )
				<< SQLSTR( getPrice() )
				<< SQLSTR( 0 )
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

bool FormTournament::validateFields()
{
	QString errors = "";
	bool conversion = false;
	int inttmp;
	
	bool ok = true;
	if ( this->getTournamentName().length() < 1)
	{
		ok = ok && false;
		errors += i18n("<li>Bad name field</li>");
	}
	
// 	inttmp = this->getRounds().toInt(&conversion);
// 	if ( ! ( conversion && inttmp > 0 )  )
// 	{
// 		ok = ok && false;
// 		errors += i18n("<li>Bad rounds field</li>");
// 	}
	
	inttmp = this->getGames4pair().toInt(&conversion);
	
	if ( !(conversion && inttmp > 0) )
	{
		ok = ok && false;
		errors += i18n("<li>Bad rounds for pair field</li>");
	}
	
	if ( m_dateTournament->date() > m_endDate->date() )
	{	
		ok = ok && false;
		errors += i18n("<li>Bad end date field</li>");
	}
	
	
	if ( !ok )
		KMessageBox::detailedSorry (0, i18n("I can't create this tournament!"), errors);//<br> %1 ").arg(errors));
	
	return ok;
}




void FormTournament::setTournamentName(const QString &name)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo nombre" << std::endl;
#endif
	m_lineEdits["name"]->setText(name);
}

// // // void FormTournament::setRounds(const QString &rounds)
// // // {
// // // #if DEBUG_FORMTOUR
// // // std::cout << "Poniendo rondas" << std::endl;
// // // #endif
// // // 	m_round->setValue(rounds.toInt());
// // // }
// // // 
void FormTournament::setGames4pair(const QString &rounds)
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
/*
void FormTournament::setDiscount(const QString &discount)
{
#if DEBUG_FORMTOUR
std::cout << "Poniendo discount" << std::endl;
#endif
	m_lineEdits["discount"]->setText(discount);
}*/

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

// QString FormTournament::getRounds()
// {
// #if DEBUG_FORMTOUR
// std::cout << "Obteniendo rounds" << std::endl;
// #endif
// 	return QString::number(m_round->value());
// }
// 
QString FormTournament::getGames4pair()
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

// QString FormTournament::getDiscount()
// {
// #if DEBUG_FORMTOUR
// std::cout << "Obteniendo discount" << std::endl;
// #endif
// 	return m_lineEdits["discount"]->text();
// }

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

void FormTournament::setGame(const QString &game)
{
	m_nameGame->setCurrentItem(game, true);
}

QString FormTournament::getGame()
{
	m_nameGame->currentText();
}

#include "formtournament.moc"

