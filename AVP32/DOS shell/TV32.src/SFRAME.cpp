/*------------------------------------------------------------*/
/* filename -       sframe.cpp                                */
/*                                                            */
/* Registeration object for the class TFrame                  */
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

#define Uses_TFrame
#define Uses_TStreamableClass
#include "include\tv.h"

TStreamableClass RFrame( TFrame::name,
                         TFrame::build,
                         __DELTA(TFrame)
                       );

#endif  // ifndef NO_TV_STREAMS
