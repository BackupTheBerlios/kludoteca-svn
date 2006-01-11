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

#ifndef KLREPORTMODULE_H
#define KLREPORTMODULE_H

#include <qvbox.h>

#include <kdatepicker.h>
#include <kdatewidget.h>
#include <qpushbutton.h>
#include <kcombobox.h>

#include "klxmlreader.h"

/**
 * @author CetiSoft
*/
class KLReportModule : public QVBox
{
	Q_OBJECT
	public:
		KLReportModule(QWidget *parent = 0, const char *name = 0);
		~KLReportModule();
		
	public slots:
		void setInitialDate(QDate);
		void setEndDate(QDate );
		
	private:
		void setupGamesSerial();
		
	signals:
		virtual void message2osd(const QString &);
		virtual void sendWidget(QWidget *widget, const QString &title);
		
	private slots:
		void makeDailyReport();
		void makeRangeReport();
		
	private:
		KLXmlReader m_xmlreader;
		KDatePicker *m_initialDate;
		KDateWidget *m_endDate;
		
		KComboBox *m_gameSerial;
		
		QPushButton *m_dailyReportButton;
		QPushButton *m_rangeReportButton;
		

};

#endif
