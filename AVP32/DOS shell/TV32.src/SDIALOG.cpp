/*------------------------------------------------------------*/
/* filename -       sdialog.cpp                               */
/*                                                            */
/* Registeration object for the class TDialog                 */
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

#define Uses_TDialog
#define Uses_TStreamableClass
#include "include\tv.h"

__link( RWindow )

TStreamableClass RDialog( TDialog::name,
                          TDialog::build,
                          __DELTA(TDialog)
                        );

#endif  // ifndef NO_TV_STREAMS
