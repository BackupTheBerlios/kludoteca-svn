#include <qcursor.h>
#include <qpoint.h>
#include <qpopupmenu.h>
#include <qstatusbar.h>


#include <qbrush.h>
#include <qcanvas.h>

#include <cmath> // sin, cos

#ifndef M_PI
#define M_PI 3.1415
#endif

#include "klcanvasview.h"
#include <iostream>

class KLCanvasView::CanvasText : public QCanvasText
{
	public:
		enum { CANVAS_TEXT = 1100 };

		CanvasText( int index, QCanvas *canvas )
	: QCanvasText( canvas ), m_index( index ) {}
		CanvasText( int index, const QString& text, QCanvas *canvas )
	: QCanvasText( text, canvas ), m_index( index ) {}
		CanvasText( int index, const QString& text, QFont font, QCanvas *canvas )
	: QCanvasText( text, font, canvas ), m_index( index ) {}

		int index() const { return m_index; }
		void setIndex( int index ) { m_index = index; }

		int rtti() const { return CANVAS_TEXT; }

	private:
		int m_index;
};

KLCanvasView::KLCanvasView( QWidget* parent , const char* name, WFlags f) : QCanvasView( parent, name, f ), m_movingItem(0), m_chartType(VERTICAL_BAR), m_addValues(YES), m_decimalPlaces(0)
{
// 	std::cout << "interno: " << elements->count() << std::endl;
// 	std::cout << "interno: " << m_elements.count() << std::endl;
	m_canvas = new QCanvas(300, 300);
	setCanvas (m_canvas);
	
	m_elements.resize(MAX_ELEMENTS);
	m_font = font();
	initElements();
	drawElements();
// 	show();
}

KLCanvasView::~ KLCanvasView()
{
}

void KLCanvasView::initElements()
{
	for ( int i = 0; i < MAX_ELEMENTS; ++i )
	{
		double x = (double(i) / MAX_ELEMENTS) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((i * 17) % 105) + 151;
		m_elements[i] = KLReportElement( KLReportElement::INVALID, QColor( int(x), y, z, QColor::Hsv ) );
	}
	
	m_elements[0]  = KLReportElement( KLReportElement::INVALID, red );
	m_elements[1]  = KLReportElement( KLReportElement::INVALID, cyan );
	m_elements[2]  = KLReportElement( KLReportElement::INVALID, blue );
	m_elements[3]  = KLReportElement( KLReportElement::INVALID, yellow );
	m_elements[4]  = KLReportElement( KLReportElement::INVALID, green );
	m_elements[5]  = KLReportElement( KLReportElement::INVALID, magenta );
	m_elements[6]  = KLReportElement( KLReportElement::INVALID, darkYellow );
	m_elements[7]  = KLReportElement( KLReportElement::INVALID, darkRed );
	m_elements[8]  = KLReportElement( KLReportElement::INVALID, darkCyan );
	m_elements[9]  = KLReportElement( KLReportElement::INVALID, darkGreen );
	m_elements[10] = KLReportElement( KLReportElement::INVALID, darkMagenta );
	m_elements[11] = KLReportElement( KLReportElement::INVALID, darkBlue );
	
// 	double value = INVALID, QColor valueColor = Qt::gray,
// 	int valuePattern = Qt::SolidPattern,
// 	const QString& label = QString::null,
// 	QColor labelColor = Qt::black 
	for ( int i = 0; i < 12; ++i ) 
	{
		double x = (double(i) / MAX_ELEMENTS) * 360;
		int y = (int(x * 256) % 105) + 151;
		int z = ((i * 17) % 105) + 151;
		m_elements[i] = KLReportElement( (i+1)*2, QColor( int(x), y, z, QColor::Hsv ),Qt::SolidPattern, "label" );
	}
}

void KLCanvasView::setChartType(ChartType t)
{
	m_chartType = t;
}

void KLCanvasView::addValues(AddValuesType av)
{
	m_addValues = av;
}

void KLCanvasView::setDecimalPlaces(uint dp)
{
	m_decimalPlaces = dp;
}

void KLCanvasView::setBackgroundPixmap(const QPixmap &bg)
{
	m_canvas->setBackgroundPixmap(bg);
}

void KLCanvasView::setBackgroundColor ( const QColor & c )
{
	m_canvas->setBackgroundColor(c);
}
	
void KLCanvasView::viewportResizeEvent( QResizeEvent *e )
{
	canvas()->resize( e->size().width(), e->size().height() );
	drawElements();
}


void KLCanvasView::contentsMousePressEvent( QMouseEvent *e )
{
	QCanvasItemList list = canvas()->collisions( e->pos() );
	for ( QCanvasItemList::iterator it = list.begin(); it != list.end(); ++it )
	{
		if ( (*it)->rtti() == CanvasText::CANVAS_TEXT ) 
		{
			m_movingItem = *it;
			m_pos = e->pos();
			return;
		}
	}
	m_movingItem = 0;
}


void KLCanvasView::contentsMouseMoveEvent( QMouseEvent *e )
{
    if ( m_movingItem )
    {
	QPoint offset = e->pos() - m_pos;
	m_movingItem->moveBy( offset.x(), offset.y() );
	m_pos = e->pos();
		
	CanvasText *item = (CanvasText*)m_movingItem;
	int i = item->index();

	m_elements[i].setProX( m_chartType, item->x() / canvas()->width() );
	m_elements[i].setProY( m_chartType, item->y() / canvas()->height() );

	canvas()->update();
    }
}

void KLCanvasView::drawElements()
{
	QCanvasItemList list = m_canvas->allItems();
	for ( QCanvasItemList::iterator it = list.begin(); it != list.end(); ++it )
		delete *it;

	// 360 * 16 for pies; Qt works with 16ths of degrees
    	int scaleFactor = m_chartType == PIE ? 5760 :
			m_chartType == VERTICAL_BAR ? m_canvas->height() :
			m_canvas->width();
	
	double biggest = 0.0;
	int count = 0;
	double total = 0.0;
	static double scales[MAX_ELEMENTS];

	for ( int i = 0; i < MAX_ELEMENTS; ++i )
	{
		if ( m_elements[i].isValid() )
		{
			double value = m_elements[i].value();
			count++;
			total += value;
			if ( value > biggest )
				biggest = value;
			scales[i] = m_elements[i].value() * scaleFactor;
		}
	}

	if ( count ) 
	{
	    // 2nd loop because of total and biggest
		for ( int i = 0; i < MAX_ELEMENTS; ++i )
		{
			if ( m_elements[i].isValid() )
			{
				if ( m_chartType == PIE )
					scales[i] = (m_elements[i].value() * scaleFactor) / total;
				else
					scales[i] = (m_elements[i].value() * scaleFactor) / biggest;
			}
		}

		switch ( m_chartType ) 
		{
			case PIE:
				drawPieChart( scales, total, count );
				break;
			case VERTICAL_BAR:
				drawVerticalBarChart( scales, total, count );
				break;
			case HORIZONTAL_BAR:
				drawHorizontalBarChart( scales, total, count );
				break;
		}
		m_canvas->update();
	}

	m_canvas->update();
}

void KLCanvasView::drawPieChart( const double scales[], double total, int )
{
	double width = m_canvas->width();
	double height = m_canvas->height();
	int size = int(width > height ? height : width);
	int x = int(width / 2);
	int y = int(height / 2);
	int angle = 0;

	for ( int i = 0; i < MAX_ELEMENTS; ++i ) {
		if ( m_elements[i].isValid() ) {
			int extent = int(scales[i]);
			QCanvasEllipse *arc = new QCanvasEllipse(
					size, size, angle, extent, m_canvas );
			arc->setX( x );
			arc->setY( y );
			arc->setZ( 0 );
			arc->setBrush( QBrush( m_elements[i].valueColor(),
				       BrushStyle(m_elements[i].valuePattern()) ) );
			arc->show();
			angle += extent;
			QString label = m_elements[i].label();
			if ( !label.isEmpty() || m_addValues != NO ) {
				label = valueLabel( label, m_elements[i].value(), total );
				CanvasText *text = new CanvasText( i, label, m_font, m_canvas );
				double proX = m_elements[i].proX( PIE );
				double proY = m_elements[i].proY( PIE );
				if ( proX < 0 || proY < 0 ) {
		    // Find the centre of the pie segment
					QRect rect = arc->boundingRect();
					proX = ( rect.width() / 2 ) + rect.x();
					proY = ( rect.height() / 2 ) + rect.y();
		    // Centre text over the centre of the pie segment
					rect = text->boundingRect();
					proX -= ( rect.width() / 2 );
					proY -= ( rect.height() / 2 );
		    // Make proportional
					proX /= width;
					proY /= height;
				}
				text->setColor( m_elements[i].labelColor() );
				text->setX( proX * width );
				text->setY( proY * height );
				text->setZ( 1 );
				text->show();
				m_elements[i].setProX( PIE, proX );
				m_elements[i].setProY( PIE, proY );
			}
		}
	}
}


void KLCanvasView::drawVerticalBarChart(
		const double scales[], double total, int count )
{
	double width = m_canvas->width();
	double height = m_canvas->height();
	int prowidth = int(width / count);
	int x = 0;
	QPen pen;
	pen.setStyle( NoPen );

	for ( int i = 0; i < MAX_ELEMENTS; ++i ) {
		if ( m_elements[i].isValid() ) {
			int extent = int(scales[i]);
			int y = int(height - extent);
			QCanvasRectangle *rect = new QCanvasRectangle(
					x, y, prowidth, extent, m_canvas );
			rect->setBrush( QBrush( m_elements[i].valueColor(),
					BrushStyle(m_elements[i].valuePattern()) ) );
			rect->setPen( pen );
			rect->setZ( 0 );
			rect->show();
			QString label = m_elements[i].label();
			if ( !label.isEmpty() || m_addValues != NO ) {
				double proX = m_elements[i].proX( VERTICAL_BAR );
				double proY = m_elements[i].proY( VERTICAL_BAR );
				if ( proX < 0 || proY < 0 ) {
					proX = x / width;
					proY = y / height;
				}
				label = valueLabel( label, m_elements[i].value(), total );
				CanvasText *text = new CanvasText( i, label, m_font, m_canvas );
				text->setColor( m_elements[i].labelColor() );
				text->setX( proX * width );
				text->setY( proY * height );
				text->setZ( 1 );
				text->show();
				m_elements[i].setProX( VERTICAL_BAR, proX );
				m_elements[i].setProY( VERTICAL_BAR, proY );
			}
			x += prowidth;
		}
	}
}


void KLCanvasView::drawHorizontalBarChart(
		const double scales[], double total, int count )
{
	double width = m_canvas->width();
	double height = m_canvas->height();
	int proheight = int(height / count);
	int y = 0;
	QPen pen;
	pen.setStyle( NoPen );

	for ( int i = 0; i < MAX_ELEMENTS; ++i ) {
		if ( m_elements[i].isValid() ) {
			int extent = int(scales[i]);
			QCanvasRectangle *rect = new QCanvasRectangle(
					0, y, extent, proheight, m_canvas );
			rect->setBrush( QBrush( m_elements[i].valueColor(),
					BrushStyle(m_elements[i].valuePattern()) ) );
			rect->setPen( pen );
			rect->setZ( 0 );
			rect->show();
			QString label = m_elements[i].label();
			if ( !label.isEmpty() || m_addValues != NO ) {
				double proX = m_elements[i].proX( HORIZONTAL_BAR );
				double proY = m_elements[i].proY( HORIZONTAL_BAR );
				if ( proX < 0 || proY < 0 ) {
					proX = 0;
					proY = y / height;
				}
				label = valueLabel( label, m_elements[i].value(), total );
				CanvasText *text = new CanvasText( i, label, m_font, m_canvas );
				text->setColor( m_elements[i].labelColor() );
				text->setX( proX * width );
				text->setY( proY * height );
				text->setZ( 1 );
				text->show();
				m_elements[i].setProX( HORIZONTAL_BAR, proX );
				m_elements[i].setProY( HORIZONTAL_BAR, proY );
			}
			y += proheight;
		}
	}
}


QString KLCanvasView::valueLabel(const QString& label, double value, double total )
{
	if ( m_addValues == NO )
		return label;

	QString newLabel = label;
	if ( !label.isEmpty() )
		if ( m_chartType == VERTICAL_BAR )
			newLabel += '\n';
	else
		newLabel += ' ';
	if ( m_addValues == YES )
		newLabel += QString::number( value, 'f', m_decimalPlaces );
	else if ( m_addValues == AS_PERCENTAGE )
		newLabel += QString::number( (value / total) * 100, 'f', m_decimalPlaces )
				+ '%';
	return newLabel;
}

