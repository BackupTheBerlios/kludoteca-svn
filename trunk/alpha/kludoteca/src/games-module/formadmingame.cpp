/***************************************************************************
 *   Copyright (C) 2005 by CetiSoft                                        *
 *   cetis@univalle.edu.co                                        	   *
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


FormAdminGame::FormAdminGame(QString title, QWidget *parent, const char *name): QVBox(parent, name)
{
	setupForm();
	setupButton();
	setTitle(title);
}

FormAdminGame::~FormAdminGame()
{
}

void FormAdminGame::setTitle(QString title)
{
	m_labelTitle->setText(i18n("<h1><div align=\"center\">%1</dvi></h1>").arg(title));
}

void FormAdminGame::setupForm()
{
	
	m_labelTitle = new QLabel(/*i18n("<h1><div align=\"center\">%1</dvi></h1>").arg(title),*/ this,"Title");
	//m_grid->addWidget(m_labelTitle,0,1);
	
	m_labelExplanation = new QLabel(i18n("<h3>fill the fields for add a new game</h3>"), this);
	//m_grid->addWidget(m_labelExplanation,1,0);
	m_labelExplanation->setMargin (10);
	
	form = new QFrame(this);
	m_grid = new QGridLayout(form,7,4,10);
	
	m_labelNameGame = new QLabel(i18n("name"),form);
	m_nameGame = new KLineEdit(form);
	m_grid->addWidget(m_labelNameGame, 0,0);
	m_grid->addWidget(m_nameGame, 0,1);
	
	m_labelDescriptionGame = new QLabel(i18n("Description game"),form);
	m_descriptionGame = new KTextEdit(form);
	m_descriptionGame->setCheckSpellingEnabled (true);
	m_grid->addWidget(m_labelDescriptionGame, 1,0);
	m_grid->addWidget(m_descriptionGame, 1,1);
	
	m_labelrulesGame = new QLabel(i18n("rules"), form);
	m_rulesGame = new KTextEdit(form);
	m_rulesGame->setCheckSpellingEnabled (true);
	m_grid->addWidget(m_labelrulesGame, 2,0);
	m_grid->addWidget(m_rulesGame, 2,1);
	
	m_labelNPlayerGame = new QLabel(i18n("number player"), form);
	//FIXME:averiguar cuanto es el maximo de jugadores en un juego
	m_nPlayerGame = new KIntSpinBox(form);
	m_nPlayerGame->setRange (1, 6);
	//FIXME:averiguar cuanto es el maximo de jugadores en un juego
	
	m_grid->addWidget(m_labelNPlayerGame, 1,2);
	m_grid->addWidget(m_nPlayerGame, 1,3);
	
	m_labelTypeGame = new QLabel(i18n("type game"), form);
	m_typeGame = new KComboBox(form);
	m_typeGame->insertItem(i18n("Board"));
	m_typeGame->insertItem(i18n("Video"));
	m_grid->addWidget(m_labelTypeGame, 0,2);
	m_grid->addWidget(m_typeGame, 0,3);
	
	m_labelCostUnit = new QLabel(i18n("cost for time unit"), form);
	m_costUnit = new KDoubleNumInput(form);
	m_costUnit->setRange (0.1, 10000);
	//FIXME:averiguar cual es el rango del costo por unidad de tiempo
	
	m_grid->addWidget(m_labelCostUnit, 5,2);
	m_grid->addWidget(m_costUnit, 5,3);
	
	m_labelUnitTime = new QLabel(i18n("unit of time"), form);
	m_unitTime = new KComboBox(form);
	m_unitTime->insertItem(i18n("second"));
	m_unitTime->insertItem(i18n("hours"));
	
	m_grid->addWidget(m_labelUnitTime, 5, 0);
	m_grid->addWidget(m_unitTime, 5, 1);
	
	m_labelTimeAdd = new QLabel(i18n("unit of time additional"), form);
	m_timeAdd = new KComboBox(form);
	
	m_grid->addWidget(m_labelTimeAdd, 2, 2);
	m_grid->addWidget(m_timeAdd, 2, 3);
	
}

void FormAdminGame::setupButton()
{
	buttons = new QHBox(this);
	m_done = new KPushButton(i18n("register"), buttons);
	connect(m_done, SIGNAL(clicked()),this, SLOT(done()));
}


void FormAdminGame::done()
{
	//FIXME: tomar los datos de los campos validarlos y tratarlos
	
	m_nameGame->setText("");
	m_descriptionGame->setText("");
	m_rulesGame->setText("");
	m_nPlayerGame->setValue(m_nPlayerGame->minValue());
	//m_typeGame
	m_costUnit->setValue(m_costUnit->minValue());
	//m_labelUnitTime
}

void FormAdminGame::fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit)
{
	//FIXME: llenar los campos con arg de entrada de esta funcion, pesar en un orden estandar, talves este dado por la BD
}


#include "formadmingame.moc"
