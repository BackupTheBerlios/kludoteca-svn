/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/

/*
  osd.cpp  -  Provides an interface to a plain QWidget, which is independent of KDE (bypassed to X11)
  begin:     Fre Sep 26 2003
  copyright: (C) 2003 by Christian Muehlhaeuser, 2004 by Seb Ruiz
  email:     chris@chris.de; seb100@optusnet.com.au
*/

#include "osd.h"

#include <qapplication.h>
#include <qbitmap.h>
#include <qpainter.h>

#include <X11/Xlib.h>   


OSDWidget::OSDWidget( const QString &appName, QWidget *parent, const char *name )
        : QWidget( parent, name, WType_TopLevel | WNoAutoErase | WStyle_Customize | WX11BypassWM | WStyle_StaysOnTop )
        , m_appName( appName )
        , m_duration( 5000 )
        , m_shadow( true )
        , m_alignment( Middle )
        , m_screen( 0 )
        , m_y( MARGIN )
        , m_dirty( true )
{
	qDebug("[Construyendo OSDWidget]");
	setFocusPolicy( NoFocus );
	setBackgroundMode( Qt::PaletteDark /*NoBackground */);
	unsetColors();
	
	connect( &timer,     SIGNAL( timeout() ), SLOT( hide() ) );
	connect( &timerMin,  SIGNAL( timeout() ), SLOT( minReached() ) );
}


void OSDWidget::renderOSDText( const QString &text )
{
	static QBitmap mask;
	
	// Set a sensible maximum size, don't cover the whole desktop or cross the screen
	QSize max = QApplication::desktop() ->screen( m_screen ) ->size() - QSize( MARGIN*2 + 20, 100 );
	QFont titleFont( "Arial", 12, QFont::Bold );
	QFontMetrics titleFm( titleFont );
	
	// The title cannnot be taller than one line
	QRect titleRect = titleFm.boundingRect( 0, 0, max.width(), titleFm.height(), AlignLeft, m_appName );
	// The osd cannot be larger than the screen
	QRect textRect = fontMetrics().boundingRect( 0, 0, max.width(), max.height(), AlignLeft | WordBreak, text );
	
	if ( textRect.width() < titleRect.width() )
		textRect.setWidth( titleRect.width() );
	
	int imageSize = textRect.height() + titleRect.height() - 10;
	
	if ( !m_image.isNull() && m_useImage )
		textRect.addCoords( 0, 0, imageSize + 40, titleRect.height() + 10 );
	else
		textRect.addCoords( 0, 0, 20, titleRect.height() );
	
	osdBuffer.resize( textRect.size() );
	mask.resize( textRect.size() );
	
	// Start painting!
	QPainter bufferPainter( &osdBuffer );
	QPainter maskPainter( &mask );
	
	// Draw backing rectangle
	bufferPainter.setPen( Qt::black );
	bufferPainter.setBrush( backgroundColor() );
	
	//QBrush brush;
	//brush.setPixmap( createGradient( textRect.size() ) );
	//brush.setColor( );
	
	//bufferPainter.setBrush( brush );
	bufferPainter.drawRoundRect( textRect, 1500 / textRect.width(), 1500 / textRect.height() );
	bufferPainter.setFont( font() );
	
	const uint w = textRect.width()  - 1;
	const uint h = textRect.height() - 1;
	//text position in Rect.
	int textPosition = 0;
	//shadow offset.
	int shadowOffset = 0;
	//image position.
	int imagePosition = 0;
	
	// Paint the album cover if existant
	if ( !m_image.isNull() && m_useImage )
	{
		m_image = m_image.smoothScale( imageSize, imageSize, QImage::ScaleMin );
		if ( text.isRightToLeft() )
		{
		imagePosition = -10;
		bufferPainter.drawImage( textRect.width() - imageSize - 10, -imagePosition, m_image );
		imagePosition -= imageSize;
		}
		else
		{
		imagePosition = 10;
		bufferPainter.drawImage( imagePosition, imagePosition, m_image );
		imagePosition += imageSize;
		}
	}
	
	//text position
	if ( text.isRightToLeft() )
	{
		textPosition = imagePosition - 10;
		shadowOffset = -2;
	}
	else
	{
		textPosition = imagePosition + 10;
		shadowOffset = 2;
	}
	// Draw the text shadow
	if ( m_shadow )
	{
		bufferPainter.setPen( backgroundColor().dark( 175 ) );
		bufferPainter.drawText( textPosition+shadowOffset, titleFm.height() + 1, w, h, AlignAuto | WordBreak, text );
	}
	// Draw the text
	bufferPainter.setPen( foregroundColor() );
	bufferPainter.drawText( textPosition, titleFm.height() - 1, w, h, AlignAuto | WordBreak, text );
	// Draw the title text
	bufferPainter.setFont( titleFont );
	bufferPainter.drawText( textPosition, 3, w, h, AlignLeft, m_appName );
	// Masking for transparency
	mask.fill( Qt::black );
	maskPainter.setBrush( Qt::white );
	maskPainter.drawRoundRect( textRect, 1500 / textRect.width(), 1500 / textRect.height() );
	setMask( mask );
	// Do last to reduce noticeable change when showing multiple OSDs in succession
	reposition( textRect.size() );
	m_currentText = text;
	m_dirty = false;
	update();
}

void OSDWidget::show( const QString &text, bool preemptive, bool useImage )
{
    m_useImage = useImage;

    if ( isEnabled() && !text.isEmpty() )
    {
        if ( preemptive || !timerMin.isActive() )
        {
            m_currentText = text;
            m_dirty = true;

            show();
        } else {
            textBuffer.append( text ); //queue
            imageBuffer.append( m_image ); //queue
        }
    }
}


void OSDWidget::minReached() //SLOT
{
    if ( !textBuffer.isEmpty() )
    {
        m_image = imageBuffer.front();
        renderOSDText( textBuffer.front() );
        textBuffer.pop_front();
        imageBuffer.pop_front();

        if( m_duration )
            //timerMin is still running
            timer.start( m_duration, TRUE );
    } else
        timerMin.stop();
}


void OSDWidget::setDuration( int ms )
{
    m_duration = ms;

    if( !m_duration )
        timer.stop();
}


void OSDWidget::setFont(const QFont &newFont )
{
    QWidget::setFont( newFont );
    refresh();
}


void OSDWidget::setShadow( bool shadow )
{
    m_shadow = shadow;
    refresh();
}


void OSDWidget::setTextColor( const QColor &newColor )
{
    setPaletteForegroundColor( newColor );
    refresh();
}


void OSDWidget::setBackgroundColor( const QColor &newColor )
{
    setPaletteBackgroundColor( newColor );
    refresh();
}


void OSDWidget::unsetColors()
{
    //setPaletteForegroundColor( KGlobalSettings::activeTextColor() );
    //setPaletteBackgroundColor( KGlobalSettings::activeTitleColor() );

    refresh();
}


void OSDWidget::setOffset( int /*x*/, int y )
{
    //m_offset = QPoint( x, y );
    m_y = y;
    reposition();
}


void OSDWidget::setAlignment( Alignment a )
{
    m_alignment = a;
    reposition();
}


void OSDWidget::setScreen( int screen )
{
    const int n = QApplication::desktop()->numScreens();
    m_screen = (screen >= n) ? n-1 : screen;
    reposition();
}


bool OSDWidget::event( QEvent *e )
{
    switch( e->type() )
    {
        case QEvent::Paint:
            bitBlt( this, 0, 0, &osdBuffer );
            return TRUE;

        case QEvent::ApplicationPaletteChange:
            //if ( !AmarokConfig::osdUseCustomColors() ) //FIXME not portable!
            //    unsetColors(); //updates colors for new palette
            return TRUE;

        default:
            return QWidget::event( e );
    }
}


void OSDWidget::mousePressEvent( QMouseEvent* )
{
    hide();
}


void OSDWidget::show()
{
    if ( m_dirty )
        renderOSDText( m_currentText );

    QWidget::show();

    if ( m_duration ) //duration 0 -> stay forever
    {
        timer.start( m_duration, TRUE ); //calls hide()
        timerMin.start( 150 ); //calls minReached()
    }
}


void OSDWidget::refresh()
{
    if ( isVisible() )
    {
        //we need to update the buffer
        renderOSDText( m_currentText );
    } else
        m_dirty = true; //ensure we are re-rendered before we are shown
}


void OSDWidget::reposition( QSize newSize )
{
    if( !newSize.isValid() ) newSize = size();

    QPoint newPos( MARGIN, m_y );
    const QRect screen = QApplication::desktop()->screenGeometry( m_screen );

    //TODO m_y is the middle of the OSD, and don't exceed screen margins

    switch ( m_alignment )
    {
        case Left:
            break;

        case Right:
            newPos.rx() = screen.width() - MARGIN - newSize.width();
            break;

        case Center:
            newPos.ry() = (screen.height() - newSize.height()) / 2;

            //FALL THROUGH

        case Middle:
            newPos.rx() = (screen.width() - newSize.width()) / 2;
            break;
    }

    //ensure we don't dip below the screen
    if ( newPos.y() + newSize.height() > screen.height() - MARGIN )
        newPos.ry() = screen.height() - MARGIN - newSize.height();

    // correct for screen position
    newPos += screen.topLeft();

    //ensure we are painted before we move
    if( isVisible() ) paintEvent( 0 );

    //fancy X11 move+resize, reduces visual artifacts
    XMoveResizeWindow( x11Display(), winId(), newPos.x(), newPos.y(), newSize.width(), newSize.height() );
}

void OSDWidget::loadImage( QString &location )
{
    QImage image = QImage::QImage();

    if ( image.load( location ) )
        m_image = image;
    else
        m_image = QImage::QImage(); //null image

}

QPixmap OSDWidget::createGradient( QSize size )
{
	QColor gradient = paletteBackgroundColor();

    //QImage image = KImageEffect::gradient( size , gradient, gradient.light(), KImageEffect::PipeCrossGradient, 3 );

   	return QPixmap( 0 );
}
