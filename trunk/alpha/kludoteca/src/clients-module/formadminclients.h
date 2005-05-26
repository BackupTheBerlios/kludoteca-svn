/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                        	           *
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
 
#ifndef FORMADMINCLIENTS_H
#define FORMADMINCLIENTS_H

#include <formbase.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <qhbuttongroup.h>
#include <klineedit.h>
#include <qlayout.h>
#include <qscrollview.h>
#include <qdict.h>
#include <kcombobox.h>
#include <kcompletion.h>
#include "klxmlreader.h"
#include "kldatabase.h"
#include "klresultsetinterpreter.h"

/**
 * Este es el formulario para añadir y administrar clientes
 * @short Añadir cliente
 * @author David Cuadrado - Daniel Valencia
 * @todo 
 * - Actualizar el listview
 * - Funciones para obtener y colocar datos
 * - Tomar la fecha actual y meterla a la base de datos
 * - Un ComboBox para seleccionar el estado
 * - Setear por defecto alguna opcion del combobox y los radio buttons
 * - Retornar el sexo del cliente para añadirlo a la base de datos
 * 
*/
class FormAdminClients : public FormBase
{
	Q_OBJECT
	public:
		/**
		 * Constructor
		 * @param parent 
		 * @return 
		 */
		FormAdminClients (FormBase::Type t,QWidget *parent = 0);
		/**
		 * Destructor
		 * @return 
		 */
		~FormAdminClients();
		
		/**
		 * Crea la forma
		 */
		void setupForm();
		/**
		 * Identificacion de cliente
		 */
		QString getClientId();
		QString getClientName();
		QString getSystemDate();
		QString getClientLastName();
		QString getClientPhone();
		QString getClientCellular();
		QString getClientState();
		QString getClientEmail();
		QString getClientSex();
		QString getClientAddress();
		
		QString getFriendId();
		QString getFriendLastName();
		QString getFriendName();
		QString getFriendPhone();
		QString getFriendCellular();
		QString getFriendAddress();
		QString getFriendState();
		QString getFriendEmail();
		QString getFriendSex();
		
		void setClientId(const QString &id);
		void setClientName(const QString &name);
		void setClientLastName(const QString &lastname);
		void setClientPhone(const QString &phone);
		void setClientCellular(const QString &cell);
		void setClientState(const QString &state);
		void setClientEmail(const QString &email);
		void setClientSex(QString &sex);
		void setClientAddress(const QString &address);

		void setFriendId(const QString &id);
		void setFriendName(const QString &name);
		void setFriendLastName(const QString &lastname);
		void setFriendPhone(const QString &phone);
		void setFriendCellular(const QString &cell);
		void setFriendState(const QString &state);
		void setFriendEmail(const QString &email);
		void setFriendSex(QString &sex);
		void setFriendAddress(const QString &address);
// 		
		//void setFriendLineEdits(QStringList &fields,KLSqlResults &result);
		

	public slots:
		/**
	 	 * Esta es la accion predeterminada cuando se presiona el boton aceptar
		 */
		void accept();
		/**
		 * Esta es la accion predeterminada cuando se presiona el boton cancelar
		 */
		void cancel();
		
		/**
		 * Limpia el formulario
		 */
		void clean();
	signals:
		void message2osd(const QString &msg);
		
	private:
		QScrollView *m_scrollView;
		QGridLayout *m_layout;
		QFrame *m_container;
		QHButtonGroup *m_radioButtonClte, *m_radioButtonFrd;
		QRadioButton *m_maleClte, *m_femaleClte, *m_maleFrd, *m_femaleFrd;
		KPushButton *m_selectFaceClte, *m_selectFaceFrd;
		HashLineEdit m_hashClient, m_hashPerson, m_hashFriend;
		KComboBox *m_comboClte, *m_comboFrd;
		KCompletion *m_compClte, *m_compFrd;
		
		KLResultSetInterpreter *m_rsinterpreter;
		KLXmlReader m_xmlreader;
		QXmlInputSource m_xmlsource;
		QString m_pkey, m_fpkey; // clientId;
		bool cltStateChanged , frdStateChanged ;
	
	private:
		/**
		 * Crea los botones
		 */
		void setupButtonsBox();
		/**
		 * Crea la caja principal
		 */
		void setupBox();
};

#endif
