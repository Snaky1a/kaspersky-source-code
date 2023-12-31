/*------------------------------------------------------------*/
/* filename -       sdirlist.cpp                              */
/*                                                            */
/* Registeration object for the class TDirListBox             */
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

#define Uses_TDirListBox
#define Uses_TStreamableClass
#include "include\tv.h"

TStreamableClass RDirListBox( TDirListBox::name,
                              TDirListBox::build,
                              __DELTA(TDirListBox)
                            );

#endif  // ifndef NO_TV_STREAMS
