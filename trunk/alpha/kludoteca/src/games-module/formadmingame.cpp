/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado    Juliana Davila                *
 *   krawek@gmail.com      julianad@univalle.edu.co                        *
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
#include "klxmlreader.h"
#include "kldatabase.h"
#include "klresultsetinterpreter.h"
#include "kmessagebox.h"
#include <qradiobutton.h>


FormAdminGame::FormAdminGame(FormBase::Type t, QWidget *parent) : FormBase(t, parent, "FormAdminGame")//( KLDatabase *db, QWidget *parent, const char *name): FormBase(db, parent, name)
{
	setupForm();
}

FormAdminGame::~FormAdminGame()
{
}

void FormAdminGame::setupForm()
{
	form = new QFrame(this);
	m_grid = new QGridLayout(form,7,4,10);
	
	
	m_labelReference = new QLabel(i18n("Reference of game"), form);
	m_referenceGame = new KLineEdit(form);
	m_referenceGame->setMaxLength(8);
	m_grid->addWidget(m_labelReference,0, 0);
	m_grid->addWidget(m_referenceGame, 0 , 1);
	
	m_labelNameGame = new QLabel(i18n("Game name"),form);
	m_nameGame = new KLineEdit(form);
	m_nameGame->setMaxLength(10);
	m_grid->addWidget(m_labelNameGame, 2,0);
	m_grid->addWidget(m_nameGame, 2,1);
	
	/*m_state = new QCheckBox(i18n("Texto"), this, "cosa");
	m_grid->addWidget(m_state, 0, 2);*/
	
	m_labelTypeGame = new QLabel(i18n("Type game"), form);
	m_typeGame = new KComboBox(form);
	m_typeGame->insertItem(i18n("Board"),0);
	m_typeGame->insertItem(i18n("Video"), 1);
	m_typeGame->insertItem(i18n("Cards"), 2);
	m_grid->addWidget(m_labelTypeGame, 2,2);
	m_grid->addWidget(m_typeGame, 2,3);
	
	//m_labelStateGame = new QLabel(i18n(), form);
	//hboxState = new QVBox(this);
	m_radioButtonState = new QVButtonGroup("State of game",form, "State" );
	m_stateAvaible = new QRadioButton(i18n("Available"), m_radioButtonState,"available");
	m_stateNoAvaible = new QRadioButton(i18n("Not available"), m_radioButtonState, "Not available");
	m_stateAvaible->setChecked(true);
	m_grid->addWidget(m_radioButtonState, 0,3);
	//m_grid->addWidget(m_radioButtonState, 2,3);
	
			
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
	m_nMinPlayerGame = new KIntSpinBox(form);
	m_nMinPlayerGame->setRange (2,10);
	//FIXME:averiguar cuanto es el minimo de jugadores en un juego
		
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
	m_costUnit->setRange (1000, 20000);
	//FIXME:averiguar cual es el rango del costo por unidad de tiempo
	
	m_grid->addWidget(m_labelCostUnit, 5,2);
	m_grid->addWidget(m_costUnit, 5,3);
	
	
	m_labelTimeAdd = new QLabel(i18n("Cost aditional time unit"), form);
	m_timeAdd = new KIntSpinBox(form);
	m_timeAdd->setRange (1000, 20000);
	
	m_grid->addWidget(m_labelTimeAdd, 6, 2);
	m_grid->addWidget(m_timeAdd, 6, 3);

	
}

void FormAdminGame::accept ()
{
	
	switch( getType() )
	{
		case FormBase::Add:
		{
			if (check() ) 
			{
				if( verification(getReferenceGame() ))
				{
					KLInsert sqlquery("ldt_games", QStringList() 
						<< SQLSTR(this->getReferenceGame()) 
							<< SQLSTR(this->getGameName()) 
							<< SQLSTR(this->getDescriptionGame()) 
							<< SQLSTR(this->getRulesGame()) 
							<< QString::number(this->getMinPlayers()) 
							<< QString::number(this->getMaxPlayers()) 
							<< SQLSTR(this->getTypeGame()) 
							<< SQLSTR(this->getTimeUnit()) 
							<< SQLSTR(this->getTimeUnit()) 
							<< QString::number(this->getCostUnitTime()) 
							<< QString::number(this->getCostTimeAdditional()) 
							<< SQLSTR(QString("1")) // FIXME. Como asi?
							<< SQLSTR( this->getStateGame()));
	
					std::cout << "Consulta: " << sqlquery.getQuery() << std::endl;
					KLDM->execQuery(&sqlquery); // TODO: Si importa!!!
					
					if ( ! KLDM->isLastError() )
					{
						emit message2osd(i18n("The action was make successful"));
						emit inserted(getReferenceGame());
						clean();
					}
					else
					{
						KMessageBox::error(this, i18n("I can't add this game!\n"
								"The error was %1").arg((KLDM->lastError()).text())  , i18n("Error"));
					}
				}
				else 
				{
					KMessageBox::error( this, i18n("The code of the game realy exist, plase chage it"),QString::null) ;

				}
			}
			else 
			{
				KMessageBox::error( this, i18n("For continue, fill all the fields"),QString::null) ;
			}
			
		}
		
		break;
		case FormBase::Edit:
		{
			QStringList fields;
			QStringList values;
			if(!verification(getReferenceGame()) )
			{
				values << SQLSTR(getGameName()) << SQLSTR(getDescriptionGame())<< SQLSTR(getRulesGame() )<< SQLSTR(getStateGame()) << SQLSTR(getTypeGame())<< SQLSTR(getTimeUnit()) << SQLSTR(getTimeUnitAdd() ) << SQLSTR(getMinPlayers()) << SQLSTR(getMaxPlayers()) << SQLSTR(getCostUnitTime()) << SQLSTR(getCostTimeAdditional());
				fields << "gamename" << "description" << "rules" << "available"<< "gametype" << "timeunit"<<"timeunitadd" << "mingamers" << "maxgamers" << "costforunit" << "costforunitadd" ;
				KLUpdate sqlup("ldt_games", fields, values);
				sqlup.setWhere("serialreference ="+SQLSTR(game));
				
				KLDM->execQuery(&sqlup); // HACE RATO DIJO NO MAS SENDQUERY
				
			}
			else 
			{
				values << SQLSTR(getReferenceGame())<< SQLSTR(getGameName()) << SQLSTR(getDescriptionGame())<< SQLSTR(getRulesGame() )<< SQLSTR(getStateGame()) << SQLSTR(getTypeGame())<< SQLSTR(getTimeUnit()) << SQLSTR(getTimeUnitAdd() ) << SQLSTR(getMinPlayers()) << SQLSTR(getMaxPlayers()) << SQLSTR(getCostUnitTime()) << SQLSTR(getCostTimeAdditional());
				fields << "serialreference" << "gamename" << "description" << "rules" << "available"<< "gametype" << "timeunit"<<"timeunitadd" << "mingamers" << "maxgamers" << "costforunit" << "costforunitadd" ;
				KLUpdate sqlup("ldt_games", fields, values);
				sqlup.setWhere("serialreference ="+SQLSTR(game));
				
				KLDM->execQuery(&sqlup);
			}
			if ( ! KLDM->isLastError() )
			{
					emit inserted(game);
				emit message2osd(i18n("The changes to " + getGameName() + " was taken"));
				clean();
				cancel();
			}
			else
			{
				KMessageBox::error(this, i18n("I can't modify this game!\n"
						"The error was %1").arg((KLDM->lastError()).text()), i18n("Error"));
			}
		}
		break;
		
	}	

}

void FormAdminGame::cancel()
{
	emit cancelled();
}

void FormAdminGame::formQuery(const QString &idGame)
{
}

void FormAdminGame::formDelete(const QString &idGame)
{
}

void FormAdminGame::formModify(const QString &idGame)
{
	game = idGame;
	KLSelect sqlquery(QStringList() << "serialreference" << "gamename" << "description" << "rules" << "mingamers" << "maxgamers" << "gametype"<<"timeunitadd"<< "timeunit" << "costforunit" << "costforunitadd"<<"position" <<"available" , QString("ldt_games"));
	
	sqlquery.setWhere("serialreference="+SQLSTR(idGame)); 
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	QXmlInputSource *xmlsource = new  QXmlInputSource();
	xmlsource->setData(resultSet.toString());
	
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	KLSqlResults results = xmlreader.results();
	

	// m_referenceGame->setDisabled(true);
	setGameName(results["gamename"]  );
	setDescriptionGame(results["description"]  );
	setRulesGame(results["rules"]  );
	int index;
 	QString available = results["available"];
	setStateGame(available);
	
	available = results["gameType"]; 
	
	if(i18n("Board") == available)
	{
		index = 0;
	}
	if(i18n("Video") == available)
	{
		index = 1;
	}
	if(i18n("Cards") == available)
	{
		index = 2;
	}
	
	setTypeGame(available, index);
	setReferenceGame(results["serialreference"]);
	
	available = results["timeunit"]; 
	
	if(i18n("m") == available )
	{
		index = 0;
		available = i18n("minutes");
	}
	else if(i18n("h") == available )
	{
		index = 1;
		available = i18n("hours");
	}
	setTimeUnit(available, index );

	available = results["timeunitadd"]; 
	
	if(i18n("m") == available)
	{
		index = 0;
		available = i18n("minutes");
	}
	else if(i18n("h") == available)
	{
		index = 1;
		available = i18n("hours");
	}
	setUnitTimeAdd(available, index );
	bool ok;
	setMinPlayers(results["mingamers"].toInt( &ok, 10 ) );
	setMaxPlayers(results["maxgamers"] .toInt( &ok, 10 ));
	setCostUnitTime(results["costforunit"].toDouble() );
	setCostTimeAdditional(results["costforunitadd"] .toDouble());
	
}


void FormAdminGame::fillField(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit)
{
	//FIXME: llenar /*los*/ campos con arg de entrada de esta funcion, pesar en un orden estandar, talves este dado por la BD
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
	int state = m_radioButtonState->selectedId();
	if (state == 0)
		return QString("t");

	return QString("f");
	
}

QString FormAdminGame::getReferenceGame()
{
	return m_referenceGame->text();
}

QString FormAdminGame::getTimeUnit()
{
	if( m_unitTime->currentText() == "hours")
		return "h";
	return "m";
}

QString FormAdminGame::getTimeUnitAdd()
{
	if( m_unitTimeAdd->currentText() == "hours")
		return "h";
	return "m";
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

void FormAdminGame::setStateGame(const QString &available)
{
	if (available == i18n("true") )
		m_stateAvaible->setChecked(true);
	else if (available == i18n("false"))
		m_stateNoAvaible->setChecked(true);;
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

bool FormAdminGame::check()
{
	if(getGameName() == "" or getReferenceGame() == "" or getDescriptionGame() == "" or getRulesGame() == "")
		return false;
	else return true;
}

void FormAdminGame::clean()
{
	m_referenceGame->setDisabled(false);
	game = "";
	this->setGameName("");
	this->setDescriptionGame("");
	this->setRulesGame("");
	this->setTypeGame("Board", 0);
	this->setStateGame("t");
	this->setReferenceGame("");
	this->setTimeUnit("minutes",0);
	this->setMinPlayers(2);
	this->setMaxPlayers(2);
	this->setCostUnitTime(1000);
	this->setCostTimeAdditional(1000);
	this->setUnitTimeAdd("minutes",0);
	
}

bool FormAdminGame::verification(const QString &code)
{
	
	KLSelect sqlquery(QStringList() << "serialreference", QString("ldt_games"));
	
	sqlquery.setWhere("serialreference="+SQLSTR(code)); 
	
	KLResultSet resultSet = KLDM->execQuery(&sqlquery);
	
	QXmlInputSource *xmlsource = new  QXmlInputSource();
	xmlsource->setData(resultSet.toString());
	
	KLXmlReader xmlreader;
	
	if ( ! xmlreader.analizeXml(xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return false;
	}
	
	if( xmlreader.getResultsList().count() == 0 )
	{
		return true;	
	}
	
	return false;
}

#include "formadmingame.moc"
