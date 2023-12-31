/*------------------------------------------------------------*/
/* filename -       sstrcoll.cpp                              */
/*                                                            */
/* Registeration object for the class TStringCollection       */
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

#define Uses_TStringCollection
#define Uses_TStreamableClass
#include "include\tv.h"

TStreamableClass RStringCollection( TStringCollection::name,
                                    TStringCollection::build,
                                    __DELTA(TStringCollection)
                                  );

#endif  // ifndef NO_TV_STREAMS
