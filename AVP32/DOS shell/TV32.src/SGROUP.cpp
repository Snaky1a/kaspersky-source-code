/*------------------------------------------------------------*/
/* filename -       sgroup.cpp                                */
/*                                                            */
/* Registeration object for the class TGroup                  */
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

#define Uses_TGroup
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RView )

TStreamableClass RGroup( TGroup::name,
                         TGroup::build,
                         __DELTA(TGroup)
                       );

#endif  // ifndef NO_TV_STREAMS
