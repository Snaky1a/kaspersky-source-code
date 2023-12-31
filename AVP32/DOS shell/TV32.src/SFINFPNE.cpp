/*------------------------------------------------------------*/
/* filename -       sfinfpne.cpp                              */
/*                                                            */
/* Registeration object for the class TFileInfoPane           */
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

#define Uses_TFileInfoPane
#define Uses_TStreamableClass
#include "include\tv.h"

TStreamableClass RFileInfoPane( TFileInfoPane::name,
                                TFileInfoPane::build,
                                __DELTA(TFileInfoPane)
                              );

#endif  // ifndef NO_TV_STREAMS
