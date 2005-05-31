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

KLReportWidget::KLReportWidget(ElementVector elements, QWidget *parent, const char *name) : FormBase(FormBase::Query, parent, name)
{
	QString title = i18n("<h1/><h3><div align=center>%1</div>"
			"<div align=center>NIT. %2</div>"
			"<div align=center>Phone. %3</div>"
			"<div align=center>%4</div></h3><h1>").arg(klenterprise->getName()).arg(klenterprise->getNit()).arg(klenterprise->getPhone()).arg(QDate::currentDate().toString(Qt::ISODate));;
	
	setTitle(title, false);
	
	ElementVector elements2;
	elements2.clear();
	QValueList<QColor> colors;
	colors << Qt::red << Qt::blue << Qt::gray << Qt::green << Qt::cyan << Qt::magenta << Qt::black << Qt::red ;
	for(uint i = 0; i < 5; i++)
	{
		elements2.append( new KLReportElement((i+1)*30, colors[i], Qt::SolidPattern, QString("Val%1").arg(i)) );
		std::cout << "Append value: " << i << std::endl;
	}
	
	std::cout << "my co: " << elements2.count() << std::endl;
	
	m_view = new KLCanvasView(elements2, this);
	m_view->setBackgroundColor( backgroundColor() );
	
	setupForm();
}


KLReportWidget::~KLReportWidget()
{
}


void KLReportWidget::setupForm()
{
// 	actionPanel = new KToolBar(this);
// 	KAction *act1 = new KAction(this);
// 	act1->plug(actionPanel);
}

void KLReportWidget::accept()
{
}

void KLReportWidget::clean()
{
}


#include "klreportwidget.moc"
