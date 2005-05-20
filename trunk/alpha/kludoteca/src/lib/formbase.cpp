/***************************************************************************
 *   Copyright (C) 2005 by David Cuadrado                                        *
 *   krawek@gmail.com                                        	   *
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

#include "formbase.h"
#include <klocale.h>

FormBase::FormBase(Type t, QWidget *parent, const char *name) : QVBox(parent, name), m_type(t)
{
	setMargin(10);
	setFrameShape(QFrame::Box );
	setFrameShadow(QFrame::Raised);
	m_labelTitle = new QLabel(this);
	m_labelExplanation = new QLabel(this);
	m_labelExplanation->setMargin (10);
	
	connect(this, SIGNAL(sendQuery(KLQuery* )), KLDM, SLOT(execQuery(KLQuery* )));
	connect(this, SIGNAL(sendRawQuery(const QString& )), KLDM, SLOT(execRawQuery(const QString& )));
	
	connect(KLDM, SIGNAL(executed(bool )), this, SLOT(wasExecuted(bool )));
}

FormBase::FormBase(KLDatabase *db, QWidget *parent, const char *name) : QVBox(parent, name), m_type(Any)
{
	setMargin(10);
	setFrameShape(QFrame::Box );
	setFrameShadow(QFrame::Raised);
	m_labelTitle = new QLabel(this);
	m_labelExplanation = new QLabel(this);
	m_labelExplanation->setMargin (10);
	
	Q_CHECK_PTR(db);
	
	if ( db )
	{
		connect(this, SIGNAL(sendQuery(KLQuery* )), db, SLOT(execQuery(KLQuery* )));
		connect(this, SIGNAL(sendRawQuery(const QString& )), db, SLOT(execRawQuery(const QString& )));
		
		connect(db, SIGNAL(executed(bool )), this, SLOT(wasExecuted(bool )));
	}
}

FormBase::~FormBase()
{
}

void FormBase::setTitle(QString newTitle)
{
	// TODO: make a best title! with the kde's class for manipulate texts
	m_labelTitle->setText(i18n("<h1><div align=\"center\">%1</dvi></h1>").arg(newTitle));
}

void FormBase::setTitleFont(QString font, int fontsize)
{
	setFont(QFont(font, fontsize));
}

void FormBase::setupButtons(Button button1, Button button2)
{
	m_buttons = new QHButtonGroup(this);
	m_buttons->setLineWidth(0);
	m_buttons->setMidLineWidth(0);
	
	m_accept = m_cancel = 0;
	
	switch ( button1)
	{
		case AcceptButton:
		{
			m_accept = new KPushButton(i18n("Register"), m_buttons);
		}
		break;
		
		case CancelButton:
		{
			m_cancel = new KPushButton(i18n("Cancel"), m_buttons);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}
	
	switch (button2)
	{
		case AcceptButton:
		{
			m_accept = new KPushButton(i18n("Register"), m_buttons);
		}
		break;
		
		case CancelButton:
		{
			m_cancel = new KPushButton(i18n("Cancel"), m_buttons);
		}
		break;
		
		case NoButton:
		{
		}
		break;
	}

	if (m_accept)
		connect(m_accept, SIGNAL(clicked()),this, SLOT(accept()));
	if(m_cancel)
		connect(m_cancel, SIGNAL(clicked()),this, SLOT(cancel()));
}

void FormBase::setTextAcceptButton(QString newText)
{
	if (m_accept)
		m_accept->setText(newText);
}

void FormBase::setTextCancelButton(QString newText)
{
	if(m_cancel)
		m_cancel->setText(newText);
}

void FormBase::setType(Type t)
{
	m_type = t;
}

int FormBase::getType()
{
	return m_type;
}

void FormBase::setExplanation(QString newExplanation)
{
	m_labelExplanation->setText(i18n("<h3>%1</h3>").arg(newExplanation));	
}

QWidget *FormBase::setupLineEdit(QWidget *parent, QString text, int lineEditWidth)
{
	QWidget *widget = new QWidget(parent);
	(new QHBoxLayout(widget ) )->setAutoAdd(true);
	QLabel *label = new QLabel(text, widget);
	KLineEdit *lineEdit = new KLineEdit(widget);
	lineEdit->setMaximumWidth(lineEditWidth);
	return widget;
}

HashLineEdit FormBase::setupGridLineEdit(QWidget *parent, QStringList texts, int lineEditWidth, QStringList names)
{
	Q_ASSERT(names.count() == texts.count());
	
	HashLineEdit lineEdits;
	QGridLayout *layout = new QGridLayout(parent, texts.count(), 2, 5, 5);
	
	for (uint i = 0; i < texts.count(); i++)
	{
		QLabel *labTmp = new QLabel(texts[i], parent);
		KLineEdit *lineEditTmp = new KLineEdit(parent, names[i]);
		lineEditTmp->setMaximumWidth(lineEditWidth);
		lineEditTmp->resize( lineEditTmp->height(), lineEditWidth);
		labTmp->setBuddy(lineEditTmp);
		layout->addWidget(labTmp, i, 0);
		layout->addWidget(lineEditTmp, i, 1);
		
		lineEdits.insert(names[i], lineEditTmp);
	}
	
	return lineEdits;
}

void FormBase::addLineEdits(QWidget *parent, QStringList texts, HashLineEdit &hle, int lineEditWidth, QStringList names)
{
	QGridLayout *layout = static_cast<QGridLayout *>(parent->layout());
	
	for (uint i = 0; i < texts.count(); i++)
	{
		QLabel *labTmp = new QLabel(texts[i], parent);
		KLineEdit *lineEditTmp = new KLineEdit(parent, names[i]);
		lineEditTmp->setMaximumWidth(lineEditWidth);
		lineEditTmp->resize( lineEditTmp->height(), lineEditWidth);
		labTmp->setBuddy(lineEditTmp);

		int row = i + layout->numRows();
		layout->addWidget(labTmp, row, 0);
		layout->addWidget(lineEditTmp, row, 1);
		
		hle.insert(names[i], lineEditTmp);
	}
}

void FormBase::cancel()
{
	emit cancelled();
}

bool FormBase::lastQueryWasGood()
{
	return m_lastQueryGood;
}

void FormBase::wasExecuted(bool good)
{
	m_lastQueryGood = good;
	if ( !good)
	{
		
	}
}

#include "formbase.moc"
