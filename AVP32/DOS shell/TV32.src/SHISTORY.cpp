/*------------------------------------------------------------*/
/* filename -       shistory.cpp                              */
/*                                                            */
/* Registeration object for the class THistory                */
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

#define Uses_THistory
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RView )
__link( RInputLine )

TStreamableClass RHistory( THistory::name,
                           THistory::build,
                           __DELTA(THistory)
                         );

#endif  // ifndef NO_TV_STREAMS
