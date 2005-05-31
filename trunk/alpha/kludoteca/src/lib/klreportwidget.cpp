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

#include <klocale.h>
#include <kaction.h>
 
#include "klreportwidget.h"
#include "klenterprise.h"

static const char *options_piechart[] = {
"20 20 6 1",
"  c white",
"! c None",
"# c black",
"$ c #00C900",
"% c #E9FF00",
"& c red1",
"!!!!!!#######!!!!!!!",
"!!!!##$$$$$$$##!!!!!",
"!!!#%$$$$$$$$$$#!!!!",
"!!#%%%$$$$$$$$$$#!!!",
"!#%%%%%$$$$$$$$$$#!!",
"!#%%%%%$$$$$$$$$$#!!",
"#%%%%%%%$$$$$$$$$$#!",
"#%%%%%%%%$$$$$$$$$#!",
"#%%%%%%%%$$$$$$$$$#!",
"#%%%%%%%%%$$$$$$$$#!",
"#%%%%%%%%&&$$$$$$$#!",
"#%%%%%%%&&&&$$$$$$#!",
"#%%%%%%&&&&&&&$$$$#!",
"#%%%%%&&&&&&&&&$$$#!",
"!#%%%&&&&&&&&&&&&#!!",
"!#%%&&&&&&&&&&&&&#!!",
"!!#&&&&&&&&&&&&&#!!!",
"!!!#&&&&&&&&&&&#!!!!",
"!!!!##&&&&&&&##!!!!!",
"!!!!!!#######!!!!!!!"
};

static const char *options_horizontalbarchart[] = {
	"20 20 7 1",
	"( c #A500FF",
	"  c white",
	"! c red1",
	"# c None",
	"$ c #E9FF00",
	"% c #00C900",
	"& c #002EFF",
	"!!!!!!!!!!!!!!######",
	"!!!!!!!!!!!!!!######",
	"!!!!!!!!!!!!!!######",
	"!!!!!!!!!!!!!!######",
	"$$$$$$$$$$$$$$$$$###",
	"$$$$$$$$$$$$$$$$$###",
	"$$$$$$$$$$$$$$$$$###",
	"$$$$$$$$$$$$$$$$$###",
	"%%%%%%%%%%%%%%%%%%%%",
	"%%%%%%%%%%%%%%%%%%%%",
	"%%%%%%%%%%%%%%%%%%%%",
	"%%%%%%%%%%%%%%%%%%%%",
	"&&&&&&&&&&&&&&######",
	"&&&&&&&&&&&&&&######",
	"&&&&&&&&&&&&&&######",
	"&&&&&&&&&&&&&&######",
	"(((((((((((#########",
	"(((((((((((#########",
	"(((((((((((#########",
	"(((((((((((#########"
};

static const char *options_verticalbarchart[] = {
	"20 20 7 1",
	"( c #A500FF",
	"  c white",
	"! c None",
	"# c #00C900",
	"$ c #E9FF00",
	"% c red1",
	"& c #002EFF",
	"!!!!!!!!####!!!!!!!!",
	"!!!!!!!!####!!!!!!!!",
	"!!!!!!!!####!!!!!!!!",
	"!!!!$$$$####!!!!!!!!",
	"!!!!$$$$####!!!!!!!!",
	"!!!!$$$$####!!!!!!!!",
	"%%%%$$$$####&&&&!!!!",
	"%%%%$$$$####&&&&!!!!",
	"%%%%$$$$####&&&&!!!!",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&((((",
	"%%%%$$$$####&&&&(((("
};

KLReportWidget::KLReportWidget(QWidget *parent, const char *name) : FormBase(FormBase::Query, parent, name)
{
	QString title = i18n("<h1/><h3><div align=center>%1</div>"
			"<div align=center>NIT. %2</div>"
			"<div align=center>Phone. %3</div>"
			"<div align=center>%4</div></h3><h1>").arg(klenterprise->getName()).arg(klenterprise->getNit()).arg(klenterprise->getPhone()).arg(QDate::currentDate().toString(Qt::ISODate));
	
	setTitle(title, false);
	
	m_view = new KLCanvasView( this, "Reporter");
	setFrameStyle(QFrame::GroupBoxPanel | QFrame::Raised);
	setLineWidth( 2 );
	setMidLineWidth ( 2 ) ;
	
	m_view->setBackgroundColor( backgroundColor() );
	
	m_view->show();
	
	setupForm();
}


KLReportWidget::~KLReportWidget()
{
}

KLCanvasView *KLReportWidget::getKLCanvasView()
{
	return m_view;
}

void KLReportWidget::setElements(const ElementVector &vect)
{
	m_view->setElements(vect);
// 	m_view->drawElements();
}

void KLReportWidget::setupForm()
{
	m_actionPanel = new KToolBar(this);
	
	KAction *pieAct = new KAction(this);
	pieAct->plug(m_actionPanel);
	pieAct->setIconSet( QIconSet(QPixmap(options_piechart)));
	
	connect(pieAct, SIGNAL(activated()), this, SLOT(setPieChart()));
	
	KAction *verAct = new KAction(this);
	verAct->plug(m_actionPanel);
	verAct->setIconSet( QIconSet(QPixmap(options_verticalbarchart)));
	
	connect(verAct, SIGNAL(activated()), this, SLOT(setVertChart()));
	
	KAction *horAct = new KAction(this);
	horAct->plug(m_actionPanel);
	horAct->setIconSet( QIconSet(QPixmap(options_horizontalbarchart)));
	
	connect(horAct, SIGNAL(activated()), this, SLOT(setHorizChart()));
}

void KLReportWidget::setPieChart()
{
	m_view->setChartType(KLCanvasView::PIE);
	m_view->drawElements();
}

void KLReportWidget::setHorizChart()
{
	m_view->setChartType(KLCanvasView::HORIZONTAL_BAR);
	m_view->drawElements();
}

void KLReportWidget::setVertChart()
{
	m_view->setChartType(KLCanvasView::VERTICAL_BAR);
	m_view->drawElements();
}

void KLReportWidget::toggleValues()
{
}

void KLReportWidget::accept()
{
}

void KLReportWidget::clean()
{
}


#include "klreportwidget.moc"
