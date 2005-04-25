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

#ifndef FORMBASE_H
#define FORMBASE_H

#include <qvbox.h>
#include <qhbuttongroup.h>
#include <qlabel.h>
#include <qstring.h>
#include <qframe.h> 
#include <qlayout.h>
#include <klineedit.h>

#include <kpushbutton.h>
#include <qobject.h>
#include <qscrollview.h>
#include <qdict.h>

#include "kldatabase.h"

typedef QDict<KLineEdit> HashLineEdit;

/**
 * Esta clase esta diseñada para estandarizar los formularios de las aplicaciones, para realizar cualquier fomulario de la aplicacion es necesario heredar de esta clase, y sobreescribir algunos metodos:
 * 
 * setupForm(): Este metodo se sobreescribe con la implementación de la forma
 * 
 * accept(): Esta funcion se sobreescribe con las acciones que se desean hacer cuando el boton de aceptar sea presionado.
 * 
 * cancel(): El comportamiento de esta funcion es similar a accept(), pero las acciones se realizan cuando se presiona el boton cancelar.
 * 
 * Ademas, para agregar los botones se debe invocar al metodo setupButtons() con los botones que se desean, las opciones son las siguientes:
 * - NoButton
 * - AcceptButton
 * - CancelButton
 * 
 * Por otro lado, se incluyen funciones para crear formas, como:
 * 
 * setupLineEdit(): Esta funcion recibe un padre, un texto y una tamaño y retorna un widget con una etiqueta y una linea de lectura (KLineEdit) con un tamaño.  
 * 
 * setupGridLineEdit(): Esta funcion recibe un padre y una lista de texto y un tamaño y retorna un widget con un bloque de etiquetas y su respectiva linea de lectura (KLineEdit) con el tamaño definido y retorna una tabla hash donde las llaves son el texto de las etiquetas y guardan los KLineEdit
 * 
 * @short Clase base para crear formularios
 * @author David Cuadrado
*/
class FormBase : public QVBox
{
	Q_OBJECT
		
	public:
		enum Button { NoButton = 0, AcceptButton, CancelButton };
		enum Type { Any = 0, Add, Edit, Query };
		
		/**
		 * Construye la forma con una base de datos, para comunicarse con ella se emite un objeto KLQuery con la consulta necesaria para hacerlo.
		 * @param db 
		 * @param parent 
		 * @param name 
		 * @return 
		 */
		FormBase ( KLDatabase *db, QWidget *parent = 0, const char *name = 0);
		
		
		/**
		 * Construye la forma con un orden en los botones
		 */
		FormBase( Button button1 = NoButton, Button button2 =  NoButton, QWidget *parent = 0, const char *name = 0);
		
		
		/**
		 * Destructor por defecto.
		 */
		~FormBase();
		/**
		* Cambia el titulo del formulario.
		 */
		void setTitle(QString newTitle);
		
		/**
		 * Coloca el tipo del formulario
		 * @param t 
		 */
		void setType(Type t);
		
		/**
		 * Obtiene el tipo del formulario
		 */
		int getType();
		
		/**
		 * Cambia el tipo de letra del titulo
		 */
		void setTitleFont(QString font, int fontsize);
		/**
		 * Cambia la explicaion del formulario.
		 */
		void setExplanation(QString newExplanation);
		/**
		 * Crea el formulario.
		 */
		virtual void setupForm() = 0;
		
		/**
		 * Crea el panel de los botones con texto por defecto.
		 */
		void setupButtons(Button button1, Button button2);
		
		/**
		* Cambia el texto del primer boton
		 */
		void setTextAcceptButton(QString newText);
		/**
		 * Cambia el texto del segundo boton
		 */
		void setTextCancelButton(QString newText);
		
		/**
		 * Esta funcion toma un texto y hace un label con un line edit
		 */
		QWidget *setupLineEdit(QWidget *parent, QString text, int lineEditWidth = 200);
		
		/**
		 * Esta funcion crea un formulario cuadrado con etiqueta y captador de texto
		 */
		HashLineEdit setupGridLineEdit(QWidget *parent, QStringList texts, int lineEditWidth = 200); 
		
		/**
		 * Esta funcion agrega un formulario cuadrado con etiqueta y captador de texto
		 */
		void addLineEdits(QWidget *parent, QStringList texts, HashLineEdit &hle, int lineEditWidth); 
		
		
		/**
		 * Retorna verdadero si la ultima consulta fue exitosa
		 * @return 
		 */
		bool lastQueryWasGood();
		
		
	public slots:
		/**
		 * Esta es la accion predeterminada cuando se presiona el boton aceptar
		 */
		virtual void accept() = 0;
		/**
		 * Esta es la accion predeterminada cuando se presiona el boton cancelar
		 */
		virtual void cancel() = 0;
		
		
		/**
		 * Este slot recibe verdadero en caso de que la consulta haya sido exitosa.
		 * @param good 
		 */
		void wasExecuted(bool good);
		
		
		/**
		 * Esta funcion se usa para limpiar el formulario
		 */
		virtual void clean() = 0;
		
	signals:
		/**
		 * Emita esto si quiere enviar consultas a la base de datos.
		 * @param  
		 */
		virtual void sendQuery(KLQuery *);
		
		/**
		 * Emite una consulta a bajo nivel
		 */
		virtual void sendRawQuery(const QString &sql);
		
		/**
		 * Emita esto cuando quiera informar que se ha aceptado
		 */
		virtual void accepted(); 
		
		/**
		 * Emita esto cuando quiera informar que ha cancelado
		 */
		virtual void cancelled();
		
		/**
		 * Emita esto cuando quiera emitir la llave primaria que ha insertado, se usa para conectar con el LTListView y actualizar la lista, sin leer de nuevo todos los registros.
		 */
		virtual void inserted(const QString &pkey);
		
		
	private:
		QHButtonGroup *m_buttons;
		QLabel *m_labelTitle, *m_labelExplanation;
		KPushButton *m_accept, *m_cancel;
		Type m_type;
		bool m_lastQueryGood;
};

#endif



