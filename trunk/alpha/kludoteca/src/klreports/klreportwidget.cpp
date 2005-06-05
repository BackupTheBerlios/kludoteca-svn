/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                            	   *
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
#include <kiconloader.h>
#include <kfiledialog.h>

#include "klreportwidget.h"
#include "klenterprise.h"
#include "klexportreport.h"

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

KLReportWidget::KLReportWidget(const KLXmlReport &report, QWidget *parent, const char *name): FormBase(FormBase::Query, parent, name)
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
	
	setXmlReport(report);
	
	m_view->show();
	
	setupForm();
}


KLReportWidget::~KLReportWidget()
{
}

void KLReportWidget::print( QPainter *p )
{
	qDebug("Printing report");
	
	p->drawText( m_view->canvas()->width() / 2, m_view->canvas()->height(), "KLudoteca Report" );
	
	m_view->canvas()->drawArea(QRect(0,0,m_view->canvas()->width(),m_view->canvas()->height()), p,FALSE);

}

KLCanvasView *KLReportWidget::getKLCanvasView()
{
	return m_view;
}

void KLReportWidget::setupForm()
{
	m_actionPanel = new KToolBar(this);
	
	KAction *saveAct = new KAction(this);
	saveAct->setToolTip(i18n("Save this report"));
	saveAct->plug(m_actionPanel);
	saveAct->setIconSet(SmallIconSet( "filesave" ) );
	
	connect(saveAct, SIGNAL(activated()), this, SLOT(saveReport()));
	
	KAction *exportAct = new KAction(this);
	exportAct->setToolTip(i18n("Export this report"));
	exportAct->plug(m_actionPanel);
	exportAct->setIconSet(SmallIconSet( "document" ) );
	
	connect(exportAct, SIGNAL(activated()), this, SLOT(exportReport()));
	
	m_actionPanel->addSeparator();
	
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

void KLReportWidget::saveReport()
{
	QString filepath = KFileDialog::getSaveFileName(QString::null, "*.klr|KLudoteca report", this, i18n("Save report") );
	
	QFile file(filepath);
	if ( file.open(IO_WriteOnly) )
	{
		QTextStream stream( &file );
		stream << m_report.toString() << endl;
	}
}

void KLReportWidget::exportReport()
{
	QString filepath = KFileDialog::getSaveFileName(QString::null, "*.html", this, i18n("Export report") );
	
	KLExportReport(m_report, filepath, KLExportReport::HTML);
}

void KLReportWidget::setXmlReport(const KLXmlReport &report)
{
	m_report = report;
	QXmlInputSource source;
	source.setData(report.toString() );
	
	KLXmlReportParser parser;
	QXmlSimpleReader reader;
	reader.setContentHandler(&parser);
	
	if ( ! reader.parse(&source ) )
	{
		qDebug("I can't analice this report, sorry!");
		return;
	}
	
	m_view->setElements( parser.getElements()  );
	m_view->setChartType(parser.getGraphicType());
	m_view->drawElements();
}

void KLReportWidget::accept()
{
}

void KLReportWidget::clean()
{
	emit cancelled();
}


#include "klreportwidget.moc"
