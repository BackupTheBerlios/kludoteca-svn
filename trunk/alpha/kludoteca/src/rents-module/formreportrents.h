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
#ifndef FORMREPORTRENTS_H
#define FORMREPORTRENTS_H

#include <formbase.h>
#include <kcombobox.h>
#include <qscrollview.h>
#include <kcombobox.h>
#include "klxmlreader.h"
#include "klresultsetinterpreter.h"
#include "klxmlreport.h"
#include "klxmlreportparser.h"
#include "klreportwidget.h"

/**
@author Daniel Valencia dafevara@gmail.com
*/
class FormReportRents : public FormBase
{
	Q_OBJECT
	public:
		FormReportRents(FormBase::Type t ,QWidget* parent= 0);
		~FormReportRents();
		void setupForm();
		
		void setupButtonsBox();
		void setupBox();
	signals:
		void checkDate(const QString &d);
	public slots:
		void showReport(const QString &d);
		void accept();
		void cancel();
		void clean();		
	private:
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		KLResultSetInterpreter *m_rsinterpreter;
		KLXmlReader m_xmlreader;
		QXmlInputSource m_xmlsource;
		KComboBox *m_comboY,*m_comboM,*m_comboD;

};

#endif
