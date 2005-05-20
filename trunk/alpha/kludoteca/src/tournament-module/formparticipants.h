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
#ifndef FORMPARTICIPANTS_H
#define FORMPARTICIPANTS_H

#include <klineedit.h>
#include <qvgroupbox.h>
#include <qhbox.h>
#include <kcombobox.h>
#include <qstringlist.h>

#include "formbase.h"
#include "kltable.h"

/**
 * Formulario para la gestion de participantes de torneos
 * @author CetiSoft
*/
class FormParticipants : public FormBase
{
	Q_OBJECT
	public:
		FormParticipants(const QString &tournament, FormBase::Type t, QWidget *parent = 0);

		~FormParticipants();
		
		void setTournament(const QString &tournament);

		virtual void setupForm();

		virtual void accept();
		virtual void cancel();
		virtual void clean();
		
		QStringList getAllClients();
		
		
	signals:
		void message2osd(const QString &);
		
		
	public slots:
		void fillClientInformation(const QString &key);
		void addParticipant();
		void removeParticipant();
		void fillTableInformation();
		
	private:
		QString m_tournament;
		QVGroupBox *m_clientBox;
		KComboBox *m_clientIdent;
		KLineEdit *m_clientName, *m_clientLastName;
		
		KPushButton *m_add;
		KPushButton *m_del;
		
		KLTable *m_table;
		QStringList m_identsList, m_delList;
};

#endif
