
/*------------------------------------------------------------*/
/* filename -       tprogram.cpp                              */
/*                                                            */
/* function(s)                                                */
/*                  TProgram member functions                 */
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

#define Uses_TKeys
#define Uses_TProgram
#define Uses_TEvent
#define Uses_TScreen
#define Uses_TStatusLine
#define Uses_TMenu
#define Uses_TGroup
#define Uses_TDeskTop
#define Uses_TEventQueue
#define Uses_TSystemError
#define Uses_TMenuBar
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TThreaded
#include "include\tv.h"
#include "include\tvhelp.h"
#include <stdlib.h>

// Public variables

TStatusLine * near TProgram::statusLine = 0;
TMenuBar * near TProgram::menuBar = 0;
TDeskTop * near TProgram::deskTop = 0;
TProgram * near TProgram::application = 0;
int near TProgram::appPalette = apColor;
TEvent near TProgram::pending;

#ifndef __MSDOS__
int near TProgram::event_delay =        // time to wait for an event
        TV_DEFAULT_EVENT_DELAY;         // in milliseconds. default: 1000
                                        // the idle() function may change
                                        // this value to lower values
                                        // and will be called more frequently
#endif

extern TPoint shadowSize;

TProgInit::TProgInit( TStatusLine *(*cStatusLine)( TRect ),
                            TMenuBar *(*cMenuBar)( TRect ),
                            TDeskTop *(*cDeskTop )( TRect )
                          ) :
    createStatusLine( cStatusLine ),
    createMenuBar( cMenuBar ),
    createDeskTop( cDeskTop )
{
}

#ifndef __MSDOS__

static int inited = 0;

#include <stdio.h>
void SystemSuspend(void)
{
  if ( inited ) {
    inited = 0;
    TSystemError::suspend();
    TEventQueue::suspend();
    TScreen::suspend();
    TThreads::suspend();
  }
}

TSystemInit::TSystemInit()
{
  resume();
  static int is_atexit_set = 0;
  if ( !is_atexit_set ) {
    atexit(SystemSuspend);
    is_atexit_set = 1;
  }
};

TSystemInit::~TSystemInit()
{
  suspend();
};

void TSystemInit::suspend()
{
  SystemSuspend();
}

void TSystemInit::resume()
{
  if ( !inited ) {
    inited = 1;
    TThreads::resume();
    TScreen::resume();
    TEventQueue::resume();
    TSystemError::resume();
  }
}
#endif  // !__MSDOS__

TProgram::TProgram() :
#ifndef __MSDOS__
    TSystemInit(),
#endif  // !__MSDOS__
    TProgInit( TProgram::initStatusLine,
                  TProgram::initMenuBar,
                  TProgram::initDeskTop
                ),
    TGroup( TRect( 0,0,TScreen::screenWidth,TScreen::screenHeight ) )
{
    application = this;
    initScreen();
    state = sfVisible | sfSelected | sfFocused | sfModal | sfExposed;
    options = 0;
    buffer = (ushort far *)TScreen::screenBuffer;

    if( createDeskTop != 0 &&
        (deskTop = createDeskTop( getExtent() )) != 0
      )
        insert(deskTop);

    if( createStatusLine != 0 &&
        (statusLine = createStatusLine( getExtent() )) != 0
      )
        insert(statusLine);

    if( createMenuBar != 0 &&
        (menuBar = createMenuBar( getExtent() )) != 0
      )
        insert(menuBar);
}

TProgram::~TProgram()
{
    application = 0;
}

void TProgram::shutDown()
{
    statusLine = 0;
    menuBar = 0;
    deskTop = 0;
    TGroup::shutDown();
}

inline Boolean hasMouse( TView *p, void *s )
{
    return Boolean( (p->state & sfVisible) != 0 &&
                     p->mouseInView( ((TEvent *)s)->mouse.where ));
}

void TProgram::getEvent(TEvent& event)
{
    if( pending.what != evNothing )
        {
        event = pending;
        pending.what = evNothing;
        }
    else
        {
#ifdef __MSDOS__
        event.getMouseEvent();
        if( event.what == evNothing )
            {
            event.getKeyEvent();
            if( event.what == evNothing )
                idle();
            }
#else   // __MSDOS__
#ifdef __OS2__
        ULONG which;
        int delay = TEventQueue::lastMouse.buttons != 0
                        ? TEventQueue::autoDelay
                        : event_delay;
        APIRET rc = DosWaitMuxWaitSem(TThreads::hmuxMaster,delay,&which);
        if (rc==0 || TEventQueue::lastMouse.buttons != 0) {
          if (which==0 || TEventQueue::lastMouse.buttons != 0) {
            event.getMouseEvent();
          } else if (which==1) {
            event.getKeyEvent();
          }
        } else {
          event.what = evNothing;
          idle();
        }
#else
#ifdef __NT__
        DWORD rc;
        int delay = TEventQueue::lastMouse.buttons != 0
                        ? TEventQueue::autoDelay
                        : event_delay;
        rc = TThreads::ispending()
                ? WAIT_OBJECT_0
                : WaitForSingleObject(TThreads::chandle[0],delay);
        switch ( rc ) {
          default:
          case WAIT_OBJECT_0:
            event.getMouseEvent();
            if ( event.what == evNothing ) {
              event.getKeyEvent();
              if ( event.what == evNothing ) idle();
            }
            break;
          case WAIT_TIMEOUT:
            event.what = evNothing;
            if ( TEventQueue::lastMouse.buttons != 0 )
              event.getMouseEvent();
            if ( event.what == evNothing ) idle();
            break;
        }
#else
#error Unknown platform!
#endif  // __NT__
#endif  // __OS2__
#endif  // __MSDOS__
        }
    if( statusLine != 0 )
        {
        if( (event.what & evKeyDown) != 0 ||
            ( (event.what & evMouseDown) != 0 &&
              firstThat( hasMouse, &event ) == statusLine
            )
          )
            statusLine->handleEvent( event );
        }
}

TPalette& TProgram::getPalette() const
{
    static TPalette color ( cpColor cHelpColor, sizeof(cpColor cHelpColor)-1 );
    static TPalette blackwhite( cpBlackWhite cHelpBlackWhite, sizeof(cpBlackWhite cHelpBlackWhite)-1 );
    static TPalette monochrome( cpMonochrome cHelpMonochrome, sizeof(cpMonochrome cHelpMonochrome)-1 );
    static TPalette *palettes[] =
        {
        &color,
        &blackwhite,
        &monochrome
        };
    return *(palettes[appPalette]);
}

void TProgram::handleEvent( TEvent& event )
{
    if( event.what == evKeyDown )
        {
        char c = getAltChar( event.keyDown.keyCode );
        if( c >= '1' && c <= '9' )
            {
            if( message( deskTop,
                         evBroadcast,
                         cmSelectWindowNum,
                         (void *)(c - '0')
                       ) != 0 )
                clearEvent( event );
            }
        }

    TGroup::handleEvent( event );
    if( event.what == evCommand && event.message.command == cmQuit )
        {
        endModal( cmQuit );
        clearEvent( event );
        }
}

void TProgram::idle()
{
    if( statusLine != 0 )
        statusLine->update();

    if( commandSetChanged == True )
        {
        message( this, evBroadcast, cmCommandSetChanged, 0 );
        commandSetChanged = False;
        }
    set_event_delay(TV_DEFAULT_EVENT_DELAY);
}

TDeskTop *TProgram::initDeskTop( TRect r )
{
    r.a.y++;
    r.b.y--;
    return new TDeskTop( r );
}

TMenuBar *TProgram::initMenuBar( TRect r )
{
    r.b.y = r.a.y + 1;
    return new TMenuBar( r, (TMenu *)0 );
}

void TProgram::initScreen()
{
#ifdef __OS2__
    short mode = TScreen::screenMode;
    if ( mode != TDisplay::smMono &&
         mode != TDisplay::smBW80 &&
         mode != TDisplay::smCO80    ) {
      VIOMODEINFO info;
      info.cb=sizeof(VIOMODEINFO);
      VioGetMode(&info,0);
      if ( info.color == COLORS_2 ) mode = TDisplay::smMono;
      else mode = TDisplay::smCO80;
    }
#else
#ifdef __NT__
    short mode = TDisplay::smCO80;
#else
#ifdef __MSDOS__
    short mode = TScreen::screenMode;
#else
#error  Unknown platform!
#endif  // !__MSDOS__
#endif  // __NT__
#endif  // __OS2__
    if( (mode & 0x00FF) != TDisplay::smMono )
        {
        if( (mode & TDisplay::smFont8x8) != 0 )
            shadowSize.x = 1;
        else
            shadowSize.x = 2;
        shadowSize.y = 1;
        showMarkers = False;
        if( (mode & 0x00FF) == TDisplay::smBW80 )
            appPalette = apBlackWhite;
        else
            appPalette = apColor;
        }
    else
        {
        shadowSize.x = 0;
        shadowSize.y = 0;
        showMarkers = True;
        appPalette = apMonochrome;
        }
}

TStatusLine *TProgram::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( exitText, kbAltX, cmQuit ) +
            *new TStatusItem( 0, kbF10, cmMenu ) +
            *new TStatusItem( 0, kbAltF3, cmClose ) +
            *new TStatusItem( 0, kbF5, cmZoom ) +
            *new TStatusItem( 0, kbCtrlF5, cmResize )
            );
}

void TProgram::outOfMemory()
{
}

void TProgram::putEvent( TEvent & event )
{
    pending = event;
}

void TProgram::run()
{
    execute();
}

void TProgram::setScreenMode( ushort mode )
{
    TRect  r;

#ifndef __NT__
    TEventQueue::mouse.hide(); //HideMouse();
#endif
    TScreen::setVideoMode( mode );
    initScreen();
    buffer = (ushort far *)TScreen::screenBuffer;
    r = TRect( 0, 0, TScreen::screenWidth, TScreen::screenHeight );
    changeBounds( r );
    setState(sfExposed, False);
//    redraw(); useless, exposure is disabled
    setState(sfExposed, True);
#ifndef __NT__
    TEventQueue::mouse.show(); //ShowMouse();
#endif
}

TView* TProgram::validView(TView* p)
{
    if( p == 0 )
        return 0;
    if( lowMemory() )
        {
        destroy( p );
        outOfMemory();
        return 0;
        }
    if( !p->valid( cmValid ) )
        {
        destroy( p );
        return 0;
        }
    return p;
}
