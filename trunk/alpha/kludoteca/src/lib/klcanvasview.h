#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "klreportelement.h"
#include <qcanvas.h>


class QPoint;

class KLCanvasView : public QCanvasView
{
	Q_OBJECT
	public:
		enum { MAX_ELEMENTS = 100 };
		enum ChartType { PIE, VERTICAL_BAR, HORIZONTAL_BAR };
		enum AddValuesType { NO, YES, AS_PERCENTAGE };
		
		KLCanvasView( ElementVector elements, QWidget* parent = 0, const char* name = "KLCanvasView", WFlags f = 0 );

	protected:
		void viewportResizeEvent( QResizeEvent *e );
		void contentsMousePressEvent( QMouseEvent *e );
		void contentsMouseMoveEvent( QMouseEvent *e );
		void drawElements();
		
	public:
		void drawPieChart( const double scales[], double total, int );
		void drawVerticalBarChart(const double scales[], double total, int count );
		void drawHorizontalBarChart(const double scales[], double total, int count );
		QString valueLabel(const QString& label, double value, double total );
		void setChartType(ChartType t);
		void addValues(AddValuesType av);
		void setDecimalPlaces(uint dp);
		
		void setBackgroundPixmap(const QPixmap &bg);
		void setBackgroundColor ( const QColor & c );

	private:
		QCanvasItem *m_movingItem;
		QPoint m_pos;
		const ElementVector *m_elements;
		QFont m_font;
		QCanvas *m_canvas;
		ChartType m_chartType;
		AddValuesType m_addValues;
		int m_decimalPlaces;
		class CanvasText;
};


#endif
