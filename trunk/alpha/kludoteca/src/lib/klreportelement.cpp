#include "klreportelement.h"

#include <qstringlist.h>
#include <qtextstream.h>

const char FIELD_SEP = ':';
const char PROPOINT_SEP = ';';
const char XY_SEP = ',';


void KLReportElement::init( double value, QColor valueColor, int valuePattern,
		    const QString& label, QColor labelColor )
{
    m_value = value;
    m_valueColor = valueColor;
    if ( valuePattern < Qt::SolidPattern || valuePattern > Qt::DiagCrossPattern )
	valuePattern = Qt::SolidPattern;
    m_valuePattern = valuePattern;
    m_label = label;
    m_labelColor = labelColor;
}


void KLReportElement::setValuePattern( int valuePattern )
{
    if ( valuePattern < Qt::SolidPattern || valuePattern > Qt::DiagCrossPattern )
	valuePattern = Qt::SolidPattern;
    m_valuePattern = valuePattern;
}


double KLReportElement::proX( int index ) const
{
    Q_ASSERT(index >= 0 && index < MAX_PROPOINTS);
    return m_propoints[2 * index];
}


double KLReportElement::proY( int index ) const
{
    Q_ASSERT(index >= 0 && index < MAX_PROPOINTS);
    return m_propoints[(2 * index) + 1];
}


void KLReportElement::setProX( int index, double value )
{
    Q_ASSERT(index >= 0 && index < MAX_PROPOINTS);
    m_propoints[2 * index] = value;
}


void KLReportElement::setProY( int index, double value )
{
    Q_ASSERT(index >= 0 && index < MAX_PROPOINTS);
    m_propoints[(2 * index) + 1] = value;
}


QTextStream &operator<<( QTextStream &s, const KLReportElement &element )
{
    s << element.value() << FIELD_SEP
      << element.valueColor().name() << FIELD_SEP
      << element.valuePattern() << FIELD_SEP
      << element.labelColor().name() << FIELD_SEP;

    for ( int i = 0; i < KLReportElement::MAX_PROPOINTS; ++i ) {
	s << element.proX( i ) << XY_SEP << element.proY( i );
	s << ( i == KLReportElement::MAX_PROPOINTS - 1 ? FIELD_SEP : PROPOINT_SEP );
    }

    s << element.label() << '\n';

    return s;
}


QTextStream &operator>>( QTextStream &s, KLReportElement &element )
{
    QString data = s.readLine();
    element.setValue( KLReportElement::INVALID );

    int errors = 0;
    bool ok;

    QStringList fields = QStringList::split( FIELD_SEP, data );
    if ( fields.count() >= 4 ) {
	double value = fields[0].toDouble( &ok );
	if ( !ok )
	    errors++;
	QColor valueColor = QColor( fields[1] );
	if ( !valueColor.isValid() )
	    errors++;
	int valuePattern = fields[2].toInt( &ok );
	if ( !ok )
	    errors++;
	QColor labelColor = QColor( fields[3] );
	if ( !labelColor.isValid() )
	    errors++;
	QStringList propoints = QStringList::split( PROPOINT_SEP, fields[4] );
	QString label = data.section( FIELD_SEP, 5 );

	if ( !errors ) {
	    element.set( value, valueColor, valuePattern, label, labelColor );
	    int i = 0;
	    for ( QStringList::iterator point = propoints.begin();
		i < KLReportElement::MAX_PROPOINTS && point != propoints.end();
		++i, ++point ) {
		errors = 0;
		QStringList xy = QStringList::split( XY_SEP, *point );
		double x = xy[0].toDouble( &ok );
		if ( !ok || x <= 0.0 || x >= 1.0 )
		    errors++;
		double y = xy[1].toDouble( &ok );
		if ( !ok || y <= 0.0 || y >= 1.0 )
		    errors++;
		if ( errors )
		    x = y = KLReportElement::NO_PROPORTION;
		element.setProX( i, x );
		element.setProY( i, y );
	    }
	}
    }

    return s;
}

