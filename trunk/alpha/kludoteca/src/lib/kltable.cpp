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

#include "kltable.h"

KLTable::KLTable(int rows, int cols, QWidget *parent, const char *name)
 : QTable(rows, cols, parent, name)
{
	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	expandTableSize();
}

KLTable::~KLTable()
{
}

void KLTable::resizeEvent(QResizeEvent * e )
{
	expandTableSize();
	QFrame::resizeEvent(e);
}

void KLTable::expandTableSize()
{
	QWidget *vp = viewport();
	
	int totalWidth = sizeHint().width();
	int colWidth = totalWidth / (numCols() - 1);
	
	for(uint i = 0; i < numCols(); i++)
	{
		setColumnWidth(i, colWidth-30);
	}
}

void KLTable::fixSize()
{
	for (uint i = 0; i < numCols(); i++)
	{
		adjustColumn(i);
	}
	this->adjustSize();
	this->resize(this->sizeHint());
}

void KLTable::setHeaderHText(int col, const QString &text)
{
	if ( col > numCols() )
		return;
	QHeader *header = this->horizontalHeader();
	header->setLabel(col, text);
	adjustColumn(col);
}

void KLTable::insertRowData(const QStringList &data, int row)
{
	if( data.count() > numCols() || row < -1 )
		return;
	
	if(row == -1)
	{
		row = numRows();
		redimensionTable(numRows()+1);
	}
	
	for(uint i = 0; i < data.count(); i++)
	{
		setText(row, i, data[i]);
	}
}

void KLTable::redimensionTable(int rows)
{
	int cRows = numRows();
	if (rows > cRows)
	{
		insertRows(cRows, rows-cRows);
	}
	else if (rows < cRows)
	{
		int size = cRows-rows;
		if (size >= 0)
		{
			QMemArray<int> remove(size);

			int cont = 0;
			for(int i = rows; i < cRows; i++)
			{
				remove[cont] = i;
				cont++;
			}
			removeRows(remove);
		}
	}
}

#include "kltable.moc"
