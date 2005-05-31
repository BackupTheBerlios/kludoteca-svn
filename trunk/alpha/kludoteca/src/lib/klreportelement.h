#ifndef ELEMENT_H
#define ELEMENT_H

#include <qcolor.h>
#include <qnamespace.h>
#include <qstring.h>
#include <qvaluevector.h>

class KLReportElement;

typedef QValueVector<KLReportElement> ElementVector;

const double EPSILON = 0.0000001; 

class KLReportElement
{
	public:
		enum { INVALID = -1 };
		enum { NO_PROPORTION = -1 };
		enum { MAX_PROPOINTS = 3 };

		KLReportElement( double value = INVALID, QColor valueColor = Qt::gray,
				 int valuePattern = Qt::SolidPattern,
				 const QString& label = QString::null,
				 QColor labelColor = Qt::black );
		~KLReportElement();

		bool isValid() const;

		double value() const;
		QColor valueColor() const;
		int valuePattern() const;
		QString label() const;
		QColor labelColor() const;
		double proX( int index ) const;
		double proY( int index ) const;

		void set( double value, QColor valueColor,int valuePattern,const QString& label,QColor labelColor );
		void setValue( double value );
		void setValueColor( QColor valueColor );
		void setValuePattern( int valuePattern );
		void setLabel( const QString& label );
		void setLabelColor( QColor labelColor ) ;
		void setProX( int index, double value );
		void setProY( int index, double value );

#ifdef Q_FULL_TEMPLATE_INSTANTIATION
    // xlC 3.x workaround
    Q_DUMMY_COMPARISON_OPERATOR(KLReportElement)
    bool operator!=( const KLReportElement& e) const {
	return ( !(e == *this) );
    }
#endif

	private:
		void init( double value, QColor valueColor, int valuePattern,
			   const QString& label, QColor labelColor );

		double m_value;
		QColor m_valueColor;
		int m_valuePattern;
		QString m_label;
		QColor m_labelColor;
		double m_propoints[2 * MAX_PROPOINTS];
};


QTextStream &operator<<( QTextStream&, const KLReportElement& );
QTextStream &operator>>( QTextStream&, KLReportElement& );

#endif
