/*------------------------------------------------------------*/
/* filename -       tbkgrnd.cpp                               */
/*                                                            */
/* function(s)                                                */
/*          TBackground member functions                      */
/*------------------------------------------------------------*/

/*------------------------------------------------------------*/
/*                                                            */
/*    Turbo Vision -  Version 1.0                             */
/*                                                            */
/*                                                            */
/*    Copyright (c) 1991 by Borland International             */
/*    All Rights Reserved.                                    */
/*                                                            */
/*------------------------------------------------------------*/

#define Uses_TBackground
#define Uses_TDrawBuffer
#define Uses_opstream
#define Uses_ipstream

#include "include\tv.h"

#define cpBackground "\x01"      // background palette

TBackground::TBackground( const TRect& bounds, char aPattern ) :
    TView(bounds),
    pattern( aPattern )
{
    growMode = gfGrowHiX | gfGrowHiY;
}

void TBackground::draw()
{
    TDrawBuffer b;

    b.moveChar( 0, pattern, getColor(0x01), size.x );
    writeLine( 0, 0, size.x, size.y, b );
}

TPalette& TBackground::getPalette() const
{
    static TPalette palette( cpBackground, sizeof( cpBackground )-1 );
    return palette;
}

#ifndef NO_TV_STREAMS
TBackground::TBackground( StreamableInit ) : TView( streamableInit )
{
}

void TBackground::write( opstream& os )
{
    TView::write( os );
    os << pattern;
}

void *TBackground::read( ipstream& is )
{
    TView::read( is );
    is >> (uchar &)pattern;
    return this;
}

TStreamable *TBackground::build()
{
    return new TBackground( streamableInit );
}
#endif  // ifndef NO_TV_STREAMS


