/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado    juliana Davila                                   *
 *   krawek@gmail.com      julianad@univalle.edu.co                                  	   *
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

#include "formadmingame.h"
#include <klocale.h>
#include <iostream>
#include <kstandarddirs.h>


FormAdminGame::FormAdminGame( KLDatabase *db, QWidget *parent, const char *name): FormBase(db, parent, name)
{
	this->setupForm();
}

FormAdminGame::~FormAdminGame()
{
}

void FormAdminGame::setupForm()
{
	form = new QFrame(this);
	m_grid = new QGridLayout(form,7,4,10);
	
	m_labelNameGame = new QLabel(i18n("Game name"),form);
	m_nameGame = new KLineEdit(form);
	m_grid->addWidget(m_labelNameGame, 0,0);
	m_grid->addWidget(m_nameGame, 0,1);
	
	m_imagen = new QLabel("", form );
	m_imagen->setPixmap( QPixmap( locate("data", "kludoteca/games-module/game1.png" )) );
	m_grid->addWidget(m_imagen, 0,2);
	
	m_labelTypeGame = new QLabel(i18n("Type game"), form);
	m_typeGame = new KComboBox(form);
	m_typeGame->insertItem(i18n("Board"),0);
	m_typeGame->insertItem(i18n("Video"), 1);
	m_typeGame->insertItem(i18n("Cards"), 2);
	m_grid->addWidget(m_labelTypeGame, 2,0);
	m_grid->addWidget(m_typeGame, 2,1);
	
	m_labelStateGame = new QLabel(i18n("State of game"), form);
	m_stateGame = new KComboBox(form);
	m_stateGame->insertItem(i18n("Active"),0);
	m_stateGame->insertItem(i18n("Inactive"), 1);
	m_stateGame->insertItem(i18n("Fixing"), 2);
	m_grid->addWidget(m_labelStateGame, 2,2);
	m_grid->addWidget(m_stateGame, 2,3);
	
	m_labelReference = new QLabel(i18n("Reference of game"), form);
	m_referenceGame = new KLineEdit(form);
	m_grid->addWidget(m_labelReference, 1, 0);
	m_grid->addWidget(m_referenceGame, 1 , 1);
		
	m_labelDescriptionGame = new QLabel(i18n("Description game"),form);
	m_descriptionGame = new KTextEdit(form);
	m_descriptionGame->setCheckSpellingEnabled (true);
	
	m_grid->addWidget(m_labelDescriptionGame, 3,0);
	m_grid->addWidget(m_descriptionGame, 3,1);
	
	m_labelrulesGame = new QLabel(i18n("rules"), form);
	m_rulesGame = new KTextEdit(form);
	m_rulesGame->setCheckSpellingEnabled (true);
	m_grid->addWidget(m_labelrulesGame, 3,2);
	m_grid->addWidget(m_rulesGame, 3,3);
	
	m_labelNMinPlayerGame = new QLabel(i18n("Minimus number of player"), form);
	//FIXME:averiguar cuanto es el maximo de jugadores en un juego
	m_nMinPlayerGame = new KIntSpinBox(form);
	m_nMinPlayerGame->setRange (2,10);
	//FIXME:averiguar cuanto es el maximo de jugadores en un juego
		
	m_grid->addWidget(m_labelNMinPlayerGame, 4,0);
	m_grid->addWidget(m_nMinPlayerGame, 4,1);
	
	m_labelNMaxPlayerGame = new QLabel(i18n("Maximus number of player"), form);
	//FIXME:averiguar cuanto es el maximo de jugadores en un juego
	m_nMaxPlayerGame = new KIntSpinBox(form);
	m_nMaxPlayerGame->setRange (2, 10);
	
	m_grid->addWidget(m_labelNMaxPlayerGame, 4,2);
	m_grid->addWidget(m_nMaxPlayerGame, 4,3);
	
	m_labelUnitTime = new QLabel(i18n("unit of time"), form);
	m_unitTime = new KComboBox(form);
	m_unitTime->insertItem(i18n("minutes"), 0);
	m_unitTime->insertItem(i18n("hours"), 1);
	
	m_grid->addWidget(m_labelUnitTime, 5, 0);
	m_grid->addWidget(m_unitTime, 5, 1);
	
	m_labelTimeAdd = new QLabel(i18n("unit of time additional"), form);
	m_unitTimeAdd = new KComboBox(form);
	m_unitTimeAdd ->insertItem(i18n("minutes"), 0);
	m_unitTimeAdd ->insertItem(i18n("hours"), 1);
	
	m_grid->addWidget(m_labelTimeAdd, 6, 0);
	m_grid->addWidget(m_unitTimeAdd, 6, 1);
	
	m_labelCostUnit = new QLabel(i18n("cost for time unit"), form);
	m_costUnit = new KIntSpinBox(form);
	m_costUnit->setRange (1000.0, 20000);
	//FIXME:averiguar cual es el rango del costo por unidad de tiempo
	
	m_grid->addWidget(m_labelCostUnit, 5,2);
	m_grid->addWidget(m_costUnit, 5,3);
	
	
	m_labelTimeAdd = new QLabel(i18n("Cost aditional time unit"), form);
	m_timeAdd = new KIntSpinBox(form);
	m_timeAdd->setRange (1000.0, 20000);
	
	m_grid->addWidget(m_labelTimeAdd, 6, 2);
	m_grid->addWidget(m_timeAdd, 6, 3);
	
}

void FormAdminGame::accept ()
{
	//FIXME: tomar los datos de los campos validarlos y tratarlos
	/*std::cout << "Nombre juego " <<getGameName()<< std::endl;
	std::cout << "Descripcion juego " <<getDescriptionGame()<< std::endl;
	std::cout << "Reglas juego " <<getRulesGame()<< std::endl;
	std::cout << "tipo juego " <<getTypeGame()<< std::endl;
	std::cout << "Unidad tiempo " <<getTimeUnit()<< std::endl;
	std::cout << "max jugadores " <<getMaxPlayers()<< std::endl;
	*/

		
	KLInsert sqlquery("ldt_games", QStringList() << SQLSTR(this->getReferenceGame()) << SQLSTR(this->getGameName()) << SQLSTR(this->getDescriptionGame()) << SQLSTR(this->getRulesGame()) << QString::number(this->getMinPlayers()) << QString::number(this->getMaxPlayers()) << SQLSTR(this->getTypeGame()) << SQLSTR(this->getTimeUnit()) << SQLSTR(this->getTimeUnit()) << QString::number(this->getCostUnitTime()) << QString::number(this->getCostTimeAdditional()) << SQLSTR(QString("1")) << SQLSTR( this->getStateGame()));
	
	std::cout << "Consulta: " << sqlquery.getQuery() << std::endl;
	
	emit sendQuery( &sqlquery );
	
	this->clean();
	
	emit accepted();
}

void FormAdminGame::formQuery(const QString &idGame)
{
	//KLResultSet *result
}

void FormAdminGame::formDelete(const QString &idGame)
{
}

void FormAdminGame::formModify()
{
}


void FormAdminGame::cancel()
{
	emit cancelled();
}


void FormAdminGame::fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit)
{
	//FIXME: llenar los campos con arg de entrada de esta funcion, pesar en un orden estandar, talves este dado por la BD
}


QString FormAdminGame::getGameName()
{
	return m_nameGame->text();

}

QString FormAdminGame::getDescriptionGame()
{
	return m_descriptionGame->text();
}

QString FormAdminGame::getRulesGame()
{
	return m_rulesGame->text();
}

QString FormAdminGame::getTypeGame()
{
	return m_typeGame->currentText();
}

QString FormAdminGame::getStateGame()
{
	return m_stateGame->currentText();
}

QString FormAdminGame::getReferenceGame()
{
	return m_referenceGame->text();
}

QString FormAdminGame::getTimeUnit()
{
	return m_unitTime->currentText();
}

QString FormAdminGame::getTimeUnitAdd()
{
	return m_unitTimeAdd->currentText();
}

int FormAdminGame::getMaxPlayers()
{
	return m_nMaxPlayerGame->text().toInt();
}

int FormAdminGame::getMinPlayers()
{
	return m_nMinPlayerGame->text().toInt();
}

double FormAdminGame::getCostTimeAdditional()
{
	return m_timeAdd->text().toDouble();
}

double FormAdminGame::getCostUnitTime()
{
	return m_costUnit->text().toDouble();
}

void FormAdminGame::setGameName(const QString &name)
{
	m_nameGame->setText(name);
}

void FormAdminGame::setDescriptionGame(const QString &description)
{
	m_descriptionGame->setText(description);
}

void FormAdminGame::setRulesGame(const QString &rules)
{
	m_rulesGame->setText(rules);
}

void FormAdminGame::setStateGame(const QString &state, int index)
{
	m_stateGame->changeItem( state,  index ) ;
}

void FormAdminGame::setTypeGame(const QString &type, int index)
{
	m_typeGame->changeItem( type,  index ) ;
}

void FormAdminGame::setReferenceGame(const QString &reference)
{
	m_referenceGame->setText(reference);
}

void FormAdminGame::setTimeUnit(const QString &unitTime, int index )
{
	m_unitTime->changeItem(unitTime, index);
}

void FormAdminGame::setUnitTimeAdd(const QString &unitTimeAdd, int index )
{
	m_unitTimeAdd->changeItem(unitTimeAdd, index);
}

void FormAdminGame::setMinPlayers(const int &numMinPlayers)
{
	m_nMinPlayerGame->setValue(numMinPlayers);
}

void FormAdminGame::setMaxPlayers(const int &numMaxPlayers)
{
	m_nMaxPlayerGame->setValue(numMaxPlayers);
}

void FormAdminGame::setCostUnitTime(const double &costTime)
{
	m_costUnit->setValue(costTime);
}

void FormAdminGame::setCostTimeAdditional(const double &costAditional)
{
	m_timeAdd->setValue(costAditional);
}

void FormAdminGame::clean()
{
	this->setGameName("");
	this->setDescriptionGame("");
	this->setRulesGame("");
	this->setTypeGame("Board", 0);
	this->setStateGame("Active", 0);
	this->setReferenceGame("");
	this->setTimeUnit("minutes",0);
	this->setMinPlayers(2);
	this->setMaxPlayers(2);
	this->setCostUnitTime(1000);
	this->setCostTimeAdditional(1000);
	this->setUnitTimeAdd("minutes",0);
	
}

#include "formadmingame.moc"
