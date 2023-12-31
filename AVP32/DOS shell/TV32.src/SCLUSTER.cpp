/*------------------------------------------------------------*/
/* filename -       scluster.cpp                              */
/*                                                            */
/* Registeration object for the class TCluster                */
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

#define Uses_TStreamableClass
#define Uses_TCluster
#include "include\tv.h"
__link( RView )
__link( RStringCollection )

TStreamableClass RCluster( TCluster::name,
                           TCluster::build,
                           __DELTA(TCluster)
                         );

#endif  // ifndef NO_TV_STREAMS
