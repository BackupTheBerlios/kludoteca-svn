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

	connect(m_comboClte,SIGNAL(activated(const QString&)),this,SLOT( setCltTable(const QString&)) );
	connect(m_comboGame,SIGNAL(activated(const QString&)),this,SLOT( setGameTable(const QString&)) );
}

void FormAdminRents::setupButtonsBox()	
{
	KLSelect queryClte(QStringList() <<"gamename"<< "firstname",QStringList() << "ldt_rents_view");
	KLSelect subQuery(QStringList() << "gameserialreference", QStringList() << "ldt_rents");	
	subQuery.setWhere("active='t'");
	
	queryClte.setWhere("gameserialreference");	
	queryClte.addSubConsult(QString("in"), subQuery);
	
	KLResultSet resultSet = KLDM->execQuery(&queryClte);	
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
		
	m_gamegb = new QVGroupBox(i18n("Game's Info"),m_container);
	QHBox *gameBox = new QHBox(m_gamegb);
	QLabel *games = new QLabel(i18n("Available Games"),gameBox);
	m_comboGame = new KComboBox(true,gameBox,"game_combo");
	m_comboGame->setDuplicatesEnabled ( FALSE); 
	games->setBuddy(m_comboGame);
	m_gameTable = new KLTable(0,8,m_gamegb);
	m_gameTable->setReadOnly(true);
	m_gameTable->setColumnLabels(QStringList() << i18n("Reference")
						<< i18n("Name")
						<< i18n("Description")
						<< i18n("Rules")
						<< i18n("Mingamers")
						<< i18n("Maxgamers")
						<< i18n("Type")
						<< i18n("Cost for Unit") );
	
	

	m_cltgb = new QVGroupBox(i18n("Client's Info"),m_container);
	QHBox *cltBox = new QHBox(m_cltgb);
	QLabel *client = new QLabel(i18n("Available Clients"),cltBox);
	m_comboClte = new KComboBox(true,cltBox,"game_combo");
	m_comboClte->setDuplicatesEnabled ( FALSE); 
	client->setBuddy(m_comboClte);
	m_cltTable= new KLTable(0,4,m_cltgb);
	m_cltTable->setReadOnly(true);
	m_cltTable->setColumnLabels(QStringList() << i18n("Identification")
			<< i18n("Name")
			<< i18n("Last Name")
			<< i18n("Mail"));
	
	QStringList::Iterator it;
	uint i = 0;
	
        for ( it = results.begin(); it != results.end(); ++it) 
	{
		++i ;
		m_comboGame->insertItem(i18n(*it), i*(-1));  
		it++;
        	m_comboClte->insertItem(i18n(*it), i*(-1));    
        }
	
	m_rentInfogb = new QGroupBox(6,Qt::Horizontal,i18n("Rent's Info"),m_container);
	
	QLabel *cltId = new QLabel(i18n("Client ID"),m_rentInfogb);
	m_cltId = new KLineEdit(m_rentInfogb);
	cltId->setBuddy(m_cltId);
	m_cltId->setMinimumWidth(100);
	
	QLabel *rentHour = new QLabel(i18n("Rent Hour"),m_rentInfogb);
	m_hour = new KIntSpinBox(m_rentInfogb);
	m_hour->setRange (00,23);
	
	m_min = new KIntSpinBox(m_rentInfogb);
	m_min->setRange (00,59);
	
	m_seg = new KIntSpinBox(m_rentInfogb);
	m_seg->setRange (00,59);
	
	QLabel *cltName = new QLabel(i18n("Client Name"),m_rentInfogb);
	m_cltName = new KLineEdit(m_rentInfogb);
	cltName->setBuddy(m_cltName);
	m_cltName->setMinimumWidth(100);
	
	
	m_layout->addWidget(m_gamegb,0,0);
	m_layout->addWidget(m_cltgb,1,0);
	m_layout->addWidget(m_rentInfogb, 2,0);
}

void FormAdminRents::setupBox()
{
}

void FormAdminRents::accept()
{
    
}

void FormAdminRents::cancel()
{	connect( this,SIGNAL(changedTextEdit(int )),this,SLOT(idTextEdit(int )) );
    
}

void FormAdminRents::clean()
{
    
}

void FormAdminRents::idTextEdit(int id)
{

}

void FormAdminRents::setCltTable(const QString &pkey)
{
	KLSelect query(QStringList() << "ldt_persons.docident"
					<< "ldt_persons.firstname"
					<< "ldt_persons.lastname"
					<< "ldt_persons.email"
					,QStringList() << "ldt_persons");
	query.setWhere("ldt_persons.firstname="+SQLSTR(pkey));
	KLResultSet resultSet = KLDM->execQuery(&query);	
	
	m_xmlsource.setData(resultSet.toString());
	if ( ! m_xmlreader.analizeXml(&m_xmlsource, KLResultSetInterpreter::Total) )
	{
		std::cerr << "No se puede analizar" << std::endl;
		return;
	}
	
	QStringList results = m_xmlreader.getResultsList();
	
	for ( QStringList::Iterator it = results.begin(); it != results.end(); ++it ) {
		cout << *it << ":";
	}
	cout << endl;
	
	int count = 0;
	for(uint i = 0; i < results.count() / 4; i++)
	{
		QStringList data = QStringList() << results[count++] << results[count++]<< results[count++] << results[count++];
		m_cltTable->insertRowData(data);
	}
}
	
void FormAdminRents::setGameTable(const QString &pkey)
{
	
}	

#include "formadminrents.moc"