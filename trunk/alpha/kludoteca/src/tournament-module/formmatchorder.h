/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                  *
 *   krawek@gmail.com                                              	   *
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
#ifndef FORMMATCHORDER_H
#define FORMMATCHORDER_H

#include "formbase.h"
#include "kltable.h"

/**
Aqui tenemos las partidas de una ronda, con sus respectivos puntajes

@author CetiSoft
*/
class FormMatchOrder : public FormBase
{
	Q_OBJECT
	public:
		FormMatchOrder(FormBase::Type t, QWidget *parent = 0);

		~FormMatchOrder();

		void setupForm();

		void accept();
		void cancel();
		void clean();
		
	private:
		KLTable *m_table;
};

#endif
