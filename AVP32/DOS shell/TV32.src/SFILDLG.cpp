/*------------------------------------------------------------*/
/* filename -       sfildlg.cpp                               */
/*                                                            */
/* Registeration object for the class TFileDialog             */
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

#define Uses_TFileDialog
#define Uses_TStreamableClass
#include "include\tv.h"
__link( RDialog )
__link( RFileInputLine )
__link( RFileList )

TStreamableClass RFileDialog( TFileDialog::name,
                              TFileDialog::build,
                              __DELTA(TFileDialog)
                            );

#endif  // ifndef NO_TV_STREAMS
