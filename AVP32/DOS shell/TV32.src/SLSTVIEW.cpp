/*------------------------------------------------------------*/
/* filename -       slstview.cpp                              */
/*                                                            */
/* Registeration object for the class TListViewer             */
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

#define Uses_TListViewer
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RView )
__link( RScrollBar )

TStreamableClass RListViewer( TListViewer::name,
                              TListViewer::build,
                              __DELTA(TListViewer)
                            );

#endif  // ifndef NO_TV_STREAMS
