/*------------------------------------------------------------*/
/* filename -       sparamte.cpp                              */
/*                                                            */
/* Registeration object for the class TParamText              */
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

#define Uses_TParamText
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RView )
__link( RStaticText )

TStreamableClass RParamText( TParamText::name,
                              TParamText::build,
                              __DELTA(TParamText)
                            );

#endif  // ifndef NO_TV_STREAMS
