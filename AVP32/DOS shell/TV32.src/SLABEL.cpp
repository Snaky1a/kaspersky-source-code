/*------------------------------------------------------------*/
/* filename -       slabel.cpp                                */
/*                                                            */
/* Registeration object for the class TLabel                  */
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

#ifndef NO_TV_STREAMS

#ifdef __WATCOMC__
#pragma off(unreferenced)
#endif

#define Uses_TLabel
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RStaticText )

TStreamableClass RLabel( TLabel::name,
                         TLabel::build,
                         __DELTA(TLabel)
                       );

#endif  // ifndef NO_TV_STREAMS
