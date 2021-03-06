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
#include "formadminrents.h"
#include <klocale.h>
#include <iostream>
#include <kmessagebox.h>
#include <qpaintdevicemetrics.h>
#include <qstylesheet.h>

#include <qapplication.h>
#include <qsimplerichtext.h>

#include <cmath>

#include "klenterprise.h"
#include "rentstimer.h"

#include <kdebug.h>

using namespace std;

FormAdminRents::FormAdminRents(FormBase::Type t, QWidget* parent): FormBase(t, parent)
{
	setupForm();
}


FormAdminRents::~FormAdminRents()
{
}

void FormAdminRents::setupForm()
{
	m_scrollView = new QScrollView(this);
	m_container = new QFrame(m_scrollView->viewport());
	m_scrollView->addChild(m_container, m_scrollView->viewport()->x() / 2,
			       m_scrollView->viewport()->y() / 2 );
	m_scrollView->setResizePolicy( QScrollView::AutoOneFit);
	m_container->setLineWidth(5);
	m_container->setMidLineWidth(20);
	m_container->setFrameShape(QFrame::Box);
	
	//m_container->setMargin(10); 
	m_layout = new QGridLayout(m_container, 1, 3, 10, 10);
	m_layout->setAlignment(Qt::AlignCenter );

	
	setupButtonsBox();
	setupBox();
	setCltTable();
	setGameTable();

}

void FormAdminRents::setupBox()	
{
	KLSelect queryClte(QStringList() <<"docident",QStringList() << "ldt_clients");
	queryClte.setWhere("not banned");
	
	KLResultSet resultSetClte = KLDM->execQuery(&queryClte);	
	
	m_xmlsource.setData(resultSetClte.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
		
	QStringList resultsClte = m_xmlreader.getResultsList();
	
	/**********************************************************************/
	
	KLSelect queryGame(QStringList() << "serialreference",QStringList() << "ldt_games");
	queryGame.setWhere("available='t'");
	
	KLResultSet resultSetGame = KLDM->execQuery(&queryGame);	
	
	m_xmlsource.setData(resultSetGame.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
		
	QStringList resultsGame = m_xmlreader.getResultsList();
		
	/****************************************************************************/
	
	m_gamegb = new QVGroupBox(i18n("Game's Info"),m_container);
	QHBox *gameBox = new QHBox(m_gamegb);
	QLabel *games = new QLabel(i18n("Available Games"),gameBox);
	
	m_gameTable = new KLTable(0,8,m_gamegb);
	m_gameTable->verticalHeader()->hide();
	
	m_gameTable->setReadOnly(true);
	m_gameTable->setColumnLabels(QStringList() << i18n("Reference")
			<< i18n("Name")
			<< i18n("Min")
			<< i18n("Max")
			<< i18n("Type")
			<< i18n("Value for Unit")
			<< i18n("Value for Additional Unit") << i18n("Time units"));
	
	

	m_cltgb = new QVGroupBox(i18n("Client's Info"),m_container);
	QHBox *cltBox = new QHBox(m_cltgb);
	QLabel *client = new QLabel(i18n("Available Clients"),cltBox);
	m_cltTable= new KLTable(0,3,m_cltgb);
	m_cltTable->verticalHeader()->hide();
	m_cltTable->setReadOnly(true);
	m_cltTable->setColumnLabels(QStringList() << i18n("Identification") << i18n("Name") << i18n("Last Name"));
	
	/******************************************************************************/
	
	/********************************************************************************/
	
	
	
	m_rentInfogb = new QGroupBox(5,Qt::Horizontal,i18n("Rent's Info"),m_container);
	
	QLabel *cltId = new QLabel(i18n("Client ID"),m_rentInfogb);
	m_cltId = new KLineEdit(m_rentInfogb,"clientdocident");
	cltId->setBuddy(m_cltId);
	m_cltId->setMinimumWidth(100);
	
	QLabel *timeUnits= new QLabel(i18n("Time Units"),m_rentInfogb);
	m_timeUnits = new QSlider(m_rentInfogb);
	m_timeUnits->setRange (00,100);
	m_timeUnits->setTickmarks(QSlider::Above);
	m_timeUnits->setTickInterval(2);
	m_timeUnits->setOrientation(Qt::Horizontal);
	m_timeUnits->setValue(0);
	m_hourValue = new KLineEdit("0",m_rentInfogb,"units");
	
	
		
	QLabel *cltName = new QLabel(i18n("Client Name"),m_rentInfogb);
	m_cltName = new KLineEdit(m_rentInfogb,"firstname");
	cltName->setBuddy(m_cltName);
	m_cltName->setMinimumWidth(100);
	
	QLabel *addTimeUnits = new QLabel(i18n("Additional Time"),m_rentInfogb);
	m_addTimeUnits = new QSlider(m_rentInfogb);
	m_addTimeUnits->setRange (00,100);
	m_addTimeUnits->setTickmarks(QSlider::Above);
	m_addTimeUnits->setTickInterval(2);
	m_addTimeUnits->setOrientation(Qt::Horizontal);
	m_addTimeUnits->setValue(0);
	m_addHourValue = new KLineEdit("0",m_rentInfogb,"addunits");
	
	QLabel *gameName = new QLabel(i18n("Game Name"),m_rentInfogb);
	m_gameName = new KLineEdit(m_rentInfogb,"gamename");
	
	QLabel *gameSerial = new QLabel(i18n("Game Serial"),m_rentInfogb);
	m_gameSerial = new KLineEdit(m_rentInfogb,"gameserialreference");
	
	connect( m_timeUnits,SIGNAL(sliderMoved ( int ) ), this, SLOT(setUnits(int))  );
	connect( m_addTimeUnits,SIGNAL(sliderMoved ( int ) ), this, SLOT(setAddUnits(int))  );
	
	connect( m_hourValue,SIGNAL(textChanged(const QString&)),this,SLOT(setHourValue(const QString&)) );
	connect( m_addHourValue,SIGNAL(textChanged(const QString&)),this,SLOT(setAddHourValue(const QString&)));
	connect( m_cltTable, SIGNAL( clicked(int,int,int,const QPoint&)  ) , this , SLOT(clickedItemClte(int, int) ) );
	connect( m_gameTable, SIGNAL( clicked(int,int,int,const QPoint&)  ) , this , SLOT(clickedItemGame(int, int) ) );
	
	QHBox *activeInfo = new QHBox(m_rentInfogb);
// 	QLabel *active = new QLabel(i18n("Active"),activeInfo);
// 	m_active = new KLineEdit(activeInfo);
	(new QLabel(i18n("Active"),activeInfo));
	QVBox *vboxRButton = new QVBox(activeInfo);
	
	m_radioButtons = new QHButtonGroup(vboxRButton);
	m_rbNotBanned = new QRadioButton(i18n("no"), m_radioButtons);
	m_radioButtons->insert(m_rbNotBanned, 0);
	m_rbBanned = new QRadioButton(i18n("yes"), m_radioButtons);
	m_radioButtons->insert(m_rbBanned, 1);
	m_rbNotBanned ->setChecked(true);
	
	(new QLabel(i18n("Cost of Rent"),m_rentInfogb));
	m_costRent= new KLineEdit(m_rentInfogb,"totalcost");
	
	m_layout->addWidget(m_gamegb,0,0);
	m_layout->addWidget(m_cltgb,1,0);
	m_layout->addWidget(m_rentInfogb, 2,0);
	
	m_hashRentFields.insert("clientdocident",m_cltId);
	m_hashRentFields.insert("gameserialreference",m_gameSerial);
	m_hashRentFields.insert("units",m_hourValue);
	m_hashRentFields.insert("addunits",m_addHourValue);
	m_hashRentFields.insert("gamename",m_gameName);
	m_hashRentFields.insert("totalcost",m_costRent);
		
}

void FormAdminRents::setupButtonsBox()
{
}

void FormAdminRents::accept()
{ 
	if ( !validateFields()) 
	{                       
		return;         
	}
	
	switch( getType() )
	{
		case FormBase::Add:
		{
			
			KLInsert insertQuery("ldt_rents",QStringList() << SQLSTR(getCltId())
					<< SQLSTR(getGameSerial())
							<< SQLSTR(getSystemDateTime())
							<< SQLSTR(getHourValue())
							<< SQLSTR(getAddHourValue())
							<< SQLSTR(getSystemDate())
							<< SQLSTR(getCostOfRent())
							<< SQLSTR(getActiveValue()) );
			KLResultSet resultSet = KLDM->execQuery(&insertQuery);
			m_xmlsource.setData(resultSet.toString());
			if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
			{
				std::cerr << "No se puede analizar" << std::endl;
				return;
			}
			
			if ( this->lastQueryWasGood() )
			{
				emit accepted();
				emit inserted(QStringList() << getGameSerial() << getSystemDate() << m_time);
#if 1
				QString timeUnit = m_gameTable->text(selectedGameRow, 7);
				
				RentsTimer::TimeUnit tu;
				
				if ( timeUnit == "m" )
				{
					tu = RentsTimer::Min;
				}
				else if ( timeUnit == "d")
				{
					tu = RentsTimer::Days;
				}
				else if ( timeUnit == "h")
				{
					tu = RentsTimer::Hour;
				}
				
				RentInfo rentInfo;
				rentInfo.setGameName(getGameName());
				rentInfo.setClientId(getCltId());
				rentInfo.setClientName(getCltName());
				
				RentsTimer *rt = new RentsTimer(rentInfo, m_timeUnits->value(), tu );
				emit sendTimer(rt);
#endif
				clean();
			}
		}
		break;
		case FormBase::Edit:
		{
			QStringList fields, values;
			QDictIterator<KLineEdit> it( m_hashRentFields);
			for( ; it.current(); ++it)
			{
				if (it.current() )
				{
					if ( it.current()->isModified() )
					{
						std::cout << "adding ." << it.current()->name() << "."<< std::endl;
						fields << it.current()->name();
						values << SQLSTR(it.current()->text());
					}
				}
			}
			
			if (m_actValueChanged)
			{
				fields << "active";
				values << SQLSTR(this->getActiveValue());
			}
			
			if (m_costRentChanged)
			{
				fields << "totalcost";
				values << SQLSTR(this->getCostOfRent());
			}
			
			if(m_addedUnits)
			{
				fields << "addunits";
				values << SQLSTR(this->getAddHourValue());
			}	
					
			if ( fields.count() == values.count() && fields.count() > 0 )
			{
				KLUpdate sqlup("ldt_rents", fields, values);
				sqlup.setWhere( "ldt_rents.gameserialreference="+SQLSTR(m_setGameSerial)+
						" and ldt_rents.date="+SQLSTR(m_rentDate)+
						" and ldt_rents.renthour="+SQLSTR(m_rentHour));
				
				KLDM->execQuery(&sqlup);
				if ( this->lastQueryWasGood() )
				{
					emit inserted(QStringList() << getGameSerial() << m_rentDate << m_rentHour);
					
					if ( m_radioButtons->selectedId() == 0 )
					{
						int res = KMessageBox::questionYesNo(this, i18n("Do you want print rent report?"), i18n("Print report"));
						
						if ( res == KMessageBox::Yes )
						{
							KPrinter *m_printer = new KPrinter;
							if (m_printer->setup(this))
							{
								QPainter p;
								p.begin(m_printer);
								
								printReport(&p, *m_printer);
							}
						}
					}
				}
			}
			
			
		}
		break;
	}
}

void FormAdminRents::cancel()
{	
	emit cancelled();
}

void FormAdminRents::clean()
{
	
	m_gameSerial->setText("");
	m_cltName->setText(QString(""));
	
	QDictIterator<KLineEdit> it( m_hashRentFields);
	for( ; it.current(); ++it)
	{
		it.current()->setText("");
	}
	m_hourValue->setText("0");
	m_addHourValue->setText("0");
	cout << "fila borrar: " << selectedClteRow << endl;
	m_gameTable->removeRow(selectedClteRow);
	
			
}

void FormAdminRents::setCltTable()
{
	KLSelect query(QStringList() << "docident"
			<< "firstname"
			<< "lastname"
			,QStringList() << "ldt_clients_view");

	KLResultSet resultSet = KLDM->execQuery(&query);	
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	int count = 0;
	for(uint i = 0; i < results.count() / 3; i++)
	{
		QStringList data = QStringList() << results[count++] << results[count++]<< results[count++];
		m_cltTable->insertRowData(data);
	}
}
	
void FormAdminRents::setGameTable()
{
	KLSelect query(QStringList() << "serialreference"
			<<"gamename"
			<< "mingamers"
			<< "maxgamers"
			<< "gametype"
			<< "costforunit"
			<< "costforunitadd" << "timeunit"
			,QStringList() << "ldt_games");
	query.setWhere("available='t'");
	KLResultSet resultSet = KLDM->execQuery(&query);	
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	int count = 0;
	for(uint i = 0; i < results.count() / 8; i++)
	{
		QStringList data = QStringList() << results[count++] 
				<< results[count++]
				<< results[count++] 
				<< results[count++]
				<< results[count++] 
				<< results[count++]
				<< results[count++]
				<< results[count++];
		m_gameTable->insertRowData(data);
	}
			
	
}

void FormAdminRents::clickedItemClte(int row,int col)
{
	selectedClteRow = row;
	QTableItem *itemId = m_cltTable->item(row,0);
	QTableItem *itemName = m_cltTable->item(row,1);
		
		
	if(itemId)
		m_cltId->setText((QString)itemId->text());
		
	if(itemName)
		m_cltName->setText((QString)itemName->text());
		
}	

void FormAdminRents::clickedItemGame(int row,int col)
{
// 	m_gameTable->setColumnLabels(QStringList() << i18n("Reference")
// 			<< i18n("Name")
// 			<< i18n("Min")
// 			<< i18n("Max")
// 			<< i18n("Type")
// 			<< i18n("Value for Unit")
// 			<< i18n("Value for Additional Unit") << i18n("Time units"));
	selectedGameRow = row;
	QTableItem *itemId = m_gameTable->item(row,0);
	QTableItem *itemName = m_gameTable->item(row,1);
	
	QTableItem *costforunit = m_gameTable->item(row,5);
	QTableItem *costforunitadd = m_gameTable->item(row,6);
		
	if(costforunit)
		m_costForUnit = (QString)costforunit->text();
		
	if(costforunit)
		m_costForUnitAdd = (QString)costforunitadd->text();
		
	if(itemId)
		m_gameSerial->setText((QString)itemId->text());
		
	if(itemName)
		m_gameName->setText((QString)itemName->text());
		
}	


void FormAdminRents::setUnits(int value)
{
	QString v;
	v = QString::number(value);
	
	switch (getType())
	{
		case FormBase::Add:
		{
			m_hourValue->setText(v);
			bool ok = 0;
			int cost = m_costForUnit.toInt(&ok,10);
			cout << "COSTO RENTA: " << cost  << endl;
			setCostOfRent(QString::number(cost*value));
			m_totalCost = (cost*value);
		}
		break;
		
		case FormBase::Edit:
		{
			return;	
		}
	}
	
}

void FormAdminRents::setAddUnits(int value)
{
	sliderCount++;
	m_addedUnits = TRUE;
	QString v;
	v = QString::number(value);
	m_addHourValue->setText(v);
/*	
	switch(getType())
	{
			
	case FormBase::Add:
	{*/
	
	if (sliderCount >= 1)
	{
		bool ok = 0;
		int cost = m_costForUnitAdd.toInt(&ok,10);
		value = (m_addHourValue->text()).toInt(&ok,10)  ;
		cout << "COSTO RENTA unidad adicional: " << cost  << endl;
		setCostOfRent(QString::number(m_totalCost+(cost*value) ));
	}
	else
	{
		bool ok = 0;
		int cost = m_costForUnitAdd.toInt(&ok,10);
		value = (m_addHourValue->text()).toInt(&ok,10)  ;
		cout << "COSTO RENTA unidad adicional: " << cost  << endl;
		setCostOfRent(QString::number(m_totalCost+=(cost*value) ));
	}
	
}

QString FormAdminRents::getCltName()
{
	return m_cltName->text();
}

QString FormAdminRents::getCltId()
{
	return (QString)m_cltId->text();
}

QString FormAdminRents::getHourValue()
{
	return (QString)m_hourValue->text();
}
		
QString FormAdminRents::getAddHourValue()
{
	return (QString)m_addHourValue->text();
} 
		
QString	FormAdminRents::getGameSerial()
{
	return (QString)m_gameSerial->text();
} 
		
QString FormAdminRents::getGameName()
{
	return (QString)m_gameName->text();
}

QString FormAdminRents::getSystemDateTime()
{
	m_time = QString( QDateTime::currentDateTime(Qt::LocalTime).toString("hh:mm:ss") );
	return m_time;
}

QString FormAdminRents::getActiveValue()
{
	QString active = m_radioButtons->selected()->text();
	active.remove('&');
	if (active == i18n("yes"))
		return QString("t");
// 	else if (active == i18n("no"))
	return QString("f");
}

QString FormAdminRents::getCostOfRent()
{
	return (QString) m_costRent->text();
}

/***********FUNCIONES SET***************************/
void FormAdminRents::setCltName(const QString &name)
{
	m_cltName->setText(name);
} 

void FormAdminRents::setCltId(const QString &id)
{
	m_cltId->setText(id);
}

void FormAdminRents::setHourValue(const QString &value)
{

	m_hourValue->setText(value);
}

void FormAdminRents::setAddHourValue(const QString &value)
{
	m_addHourValue->setText(value);	
}

void FormAdminRents::setGameSerial(const QString &serial)
{
	m_setGameSerial = serial;
	m_gameSerial->setText(serial);
}

void FormAdminRents::setGameName(const QString &gamename)
{
	m_gameName->setText(gamename);
}

void FormAdminRents::setActiveValue(const QString &value)
{
	cout << "Active Value: " << value << endl;
	
	m_actValueChanged = true;
	if( value == "true")
	{
		(static_cast<QRadioButton *>(m_radioButtons->find(1)))->setChecked(true);
	}
	else
	{
		(static_cast<QRadioButton *>(m_radioButtons->find(0)))->setChecked(true);
	}
}

void FormAdminRents::setCostOfRent(const QString &cost)
{
	m_costRentChanged = TRUE;
	bool ok = 0;
	m_costRent->setText(cost);
	
}
void FormAdminRents::rentDate(const QString &date)
{
	m_rentDate = date;
}

void FormAdminRents::rentHour(const QString &hour)
{
	m_rentHour = hour;	
}

void FormAdminRents::costUnit(const QString &cost)
{
	m_costForUnit = cost;
}

void FormAdminRents::costUnitAdd(const QString &cost)
{
	m_costForUnitAdd = cost;
}

void FormAdminRents::disabledSlider(bool value)
{
	disableSlider = value;
}

int FormAdminRents::totalCostOfRent(const QString &cost)
{
	bool ok = 0;
	m_totalCost = cost.toInt(&ok,10);
	return m_totalCost;
}		

bool FormAdminRents::validateFields()
{
	QString errors = "";
	bool ok = true;
	
	if ( getGameName().length() <= 1 )
	{
		ok = ok && false;
		errors += i18n("<li>Bad name field</li>");
	} 
	
	
	if ( getGameSerial().length() <= 1 )
	{
		ok = ok && false;
		errors += i18n("<li>Bad name field</li>");
	} 
	
	bool convertion = false;
	getCltId().toInt(&convertion);
	ok = ok && convertion;
	if ( !convertion)
	{
		errors += i18n("<li>Bad client identification field</li>");
	}
	if ( getCltId().isEmpty()  )
	{
		ok = ok && false;
		errors += i18n("<li>Bad id field</li>");
	}
	
	
	getHourValue().toInt(&convertion);
	ok = ok && convertion;
	if ( !convertion)
	{
		errors += i18n("<li>Bad units field</li>");
	}
	
// 	getGameSerial().toInt(&convertion);
// 	ok = ok && convertion;
// 	
// 	if ( !convertion)
// 	{
// 		errors += i18n("<li>Bad game serial field</li>");
// 	}
	
	getCostOfRent().toInt(&convertion);
	if ( !convertion)
	{
		errors += i18n("<li>Bad total cost field</li>");
	}
	
	if ( !ok )
		KMessageBox::detailedSorry (0, i18n("I can't insert or modify this Rent!"), errors);//<br> %1 ").arg(errors));
	
	return ok;
}		


void FormAdminRents::printReport(QPainter *painter, KPrinter &printer)
{
	QPaintDeviceMetrics metrics(&printer);
	int LargeGap = metrics.logicalDpiY() / 2;
	
	QString str = QString(
			"<div align=center>"
			"<h3>"+klenterprise->getName()+"</h3><br>Nit: "+klenterprise->getNit()+"</div>" );
	
	str += "<table width=\"100%\" border=1 cellspacing=0>\n"
			"<caption align=bottom>" + i18n("Results Table") + "</caption>\n";

	// Encabezados
	str += "<tr>";
	
	str += i18n("<th><center><b>Detail</b></center></th>");
	str += i18n("<th><center><b>Cost</b></center></th>");
	
	str += "</tr>\n";
	
	// Cuerpo
	
	str += "<tr>\n";
	str += "\t<td>Rents game "+ m_gameName->text() +"</td>\n";
	str += "\t<td>"+ m_costRent->text() +"</td>\n";
	str += "</tr>\n";
	
	for(int row = 0; row < 10; row++)
	{
		str += "<tr>\n";
		
		str += "\t<td></td>\n";
		str += "\t<td></td>\n";
		
		str += "</tr>\n";
	}
	
	str += "<tr>\n";
	str += "\t<td><center>TOTAL</center></td>\n";
	str += "\t<td><center>"+ m_costRent->text() +"</center></td>\n";
	str += "</tr>\n";
	
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


#include "formadminrents.moc"