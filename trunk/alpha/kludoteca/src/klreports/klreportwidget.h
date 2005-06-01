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

#ifndef KLREPORTWIDGET_H
#define KLREPORTWIDGET_H

#include <formbase.h>
#include <qhbox.h>
#include <ktoolbar.h>
#include "klcanvasview.h"
#include "klxmlreport.h"
#include "klxmlreportparser.h"

/**
 * @author David Cuadrado
*/

class KLReportWidget : public FormBase // TODO: Tratar de remover esta dependencia
{
	Q_OBJECT
			
	private:
		KLCanvasView *m_view;
		KToolBar *m_actionPanel;
		ElementVector m_elements;
		void initElements();
		KLXmlReport m_report;
		
	private slots:
		void setPieChart();
		void setHorizChart();
		void setVertChart();
		void toggleValues();
		void saveReport();
		void exportReport();
		
	public:
		KLReportWidget(QWidget *parent = 0, const char *name = 0);
		KLReportWidget(const KLXmlReport &report, QWidget *parent = 0, const char *name = 0);

		~KLReportWidget();

		void setupForm();
		void accept();
		void clean();

		KLCanvasView *getKLCanvasView();
		void setXmlReport(const KLXmlReport &report);
};

#endif
