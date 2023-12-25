/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   EDITORS.H                                                             */
/*                                                                         */
/*   Copyright (c) Borland International 1991                              */
/*   All Rights Reserved.                                                  */
/*                                                                         */
/*   defines the classes TIndicator, TEditor, TMemo, TFileEditor,          */
/*   and TEditWindow                                                       */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifdef __BORLANDC__
#if !defined( __DIR_H )
#include <dir.h>
#endif  // __DIR_H
#endif

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

#if !defined( __LIMITS_H )
#include <limits.h>
#endif  // __LIMITS_H

#include "tvvo.h"

#if !defined( __EDIT_COMMAND_CODES )
#define __EDIT_COMMAND_CODES

const
  ufUpdate = 0x01,
  ufLine   = 0x02,
  ufView   = 0x04;

const
  smExtend = 0x01,
  smDouble = 0x02;

const unsigned
  sfSearchFailed = UINT_MAX; // 0xFFFF;

const
  cmSave        = 80,
  cmSaveAs      = 81,
  cmFind        = 82,
  cmReplace     = 83,
  cmSearchAgain = 84;

const
  cmCharLeft    = 500,
  cmCharRight   = 501,
  cmWordLeft    = 502,
  cmWordRight   = 503,
  cmLineStart   = 504,
  cmLineEnd     = 505,
  cmLineUp      = 506,
  cmLineDown    = 507,
  cmPageUp      = 508,
  cmPageDown    = 509,
  cmTextStart   = 510,
  cmTextEnd     = 511,
  cmNewLine     = 512,
  cmBackSpace   = 513,
  cmDelChar     = 514,
  cmDelWord     = 515,
  cmDelStart    = 516,
  cmDelEnd      = 517,
  cmDelLine     = 518,
  cmInsMode     = 519,
  cmStartSelect = 520,
  cmHideSelect  = 521,
  cmIndentMode  = 522,
  cmUpdateTitle = 523;

const
  edOutOfMemory   = 0,
  edReadError     = 1,
  edWriteError    = 2,
  edCreateError   = 3,
  edSaveModify    = 4,
  edSaveUntitled  = 5,
  edSaveAs        = 6,
  edFind          = 7,
  edSearchFailed  = 8,
  edReplace       = 9,
  edReplacePrompt = 10;

const
  efCaseSensitive   = 0x0001,
  efWholeWordsOnly  = 0x0002,
  efPromptOnReplace = 0x0004,
  efReplaceAll      = 0x0008,
  efDoReplace       = 0x0010,
  efBackupFiles     = 0x0100;

const
  maxLineLength = 256;

#endif  // __EDIT_COMMAND_CODES

typedef ushort (*TEditorDialog)( int, ... );
ushort defEditorDialog( int dialog, ... );

#if defined( Uses_TIndicator ) && !defined( __TIndicator )
#define __TIndicator

class far TRect;

class TIndicator : public TView
{

public:

    TIndicator( const TRect& );

    virtual void draw();
    virtual TPalette& getPalette() const;
    virtual void setState( ushort, Boolean );
    void setValue( const TPoint&, Boolean );

protected:

    TPoint location;
    Boolean modified;

private:

    static const char near dragFrame;
    static const char near normalFrame;

#ifndef NO_TV_STREAMS
    virtual const char *streamableName() const
        { return name; }

protected:

    TIndicator( StreamableInit );

public:

    static const char * const near name;
    static TStreamable *build();
#endif  // ifndef NO_TV_STREAMS

};

#ifndef NO_TV_STREAMS
inline ipstream& operator >> ( ipstream& is, TIndicator& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TIndicator*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TIndicator& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TIndicator* cl )
    { return os << (TStreamable *)cl; }
#endif  // ifndef NO_TV_STREAMS

#endif  // Uses_TIndicator


#if defined( Uses_TEditor ) && !defined( __TEditor )
#define __TEditor

class far TRect;
class far TScrollBar;
class far TIndicator;
class far TEvent;

class TEditor : public TView
{

public:

    friend void genRefs();

    TEditor( const TRect&, TScrollBar *, TScrollBar *, TIndicator *, size_t );
    virtual ~TEditor();

    virtual void shutDown();

    char TV_CDECL bufChar( size_t );
    size_t TV_CDECL bufPtr( size_t );
    virtual void changeBounds( const TRect& );
    virtual void convertEvent( TEvent& );
    Boolean cursorVisible();
    void deleteSelect();
    virtual void doneBuffer();
    virtual void draw();
    virtual TPalette& getPalette() const;
    virtual void handleEvent( TEvent& );
    virtual void initBuffer();
    Boolean insertBuffer( char *, size_t, size_t, Boolean, Boolean );
    virtual Boolean insertFrom( TEditor * );
    Boolean insertText( const void *, size_t, Boolean );
    void scrollTo( int, int );
    Boolean search( const char *, ushort );
    virtual Boolean setBufSize( size_t );
    void setCmdState( ushort, Boolean );
    void setSelect( size_t, size_t, Boolean);
    virtual void setState( ushort, Boolean );
    void trackCursor( Boolean );
    void undo();
    virtual void updateCommands();
    virtual Boolean valid( ushort );

    int charPos( size_t, size_t );
    size_t charPtr( size_t, int );
    Boolean clipCopy();
    void clipCut();
    void clipPaste();
    void deleteRange( size_t, size_t, Boolean );
    void doUpdate();
    void doSearchReplace();
    void drawLines( int, int, size_t );
    void TV_CDECL formatLine(void *, size_t, int, ushort );
    void find();
    size_t getMousePtr( TPoint );
    Boolean hasSelection();
    void hideSelect();
    Boolean isClipboard();
    size_t TV_CDECL lineEnd( size_t );
    size_t lineMove( size_t, int );
    size_t TV_CDECL lineStart( size_t );
    void lock();
    void newLine();
    size_t TV_CDECL nextChar( size_t );
    size_t nextLine( size_t );
    size_t nextWord( size_t );
    size_t TV_CDECL prevChar( size_t );
    size_t prevLine( size_t );
    size_t prevWord( size_t );
    void replace();
    void setBufLen( size_t );
    void setCurPtr( size_t, uchar );
    void startSelect();
    void toggleInsMode();
    void unlock();
    void update( uchar );
    void checkScrollBar( const TEvent&, TScrollBar *, int& );

    TScrollBar *hScrollBar;
    TScrollBar *vScrollBar;
    TIndicator *indicator;
    char *buffer;
    size_t bufSize;
    size_t bufLen;
    size_t gapLen;
    size_t selStart;
    size_t selEnd;
    size_t curPtr;
    TPoint curPos;
    TPoint delta;
    TPoint limit;
    int drawLine;
    size_t drawPtr;
    size_t delCount;
    size_t insCount;
    Boolean isValid;
    Boolean canUndo;
    Boolean modified;
    Boolean selecting;
    Boolean overwrite;
    Boolean autoIndent;

    static TEditorDialog near editorDialog;
    static ushort near editorFlags;
    static char near findStr[maxFindStrLen];
    static char near replaceStr[maxReplaceStrLen];
    static TEditor * near clipboard;
    uchar lockCount;
    uchar updateFlags;
    int keyState;

private:

#ifndef NO_TV_STREAMS
    virtual const char *streamableName() const
        { return name; }

protected:

    TEditor( StreamableInit );
    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const near name;
    static TStreamable *build();
#endif  // ifndef NO_TV_STREAMS

};

#ifndef NO_TV_STREAMS
inline ipstream& operator >> ( ipstream& is, TEditor& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TEditor*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TEditor& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TEditor* cl )
    { return os << (TStreamable *)cl; }
#endif  // ifndef NO_TV_STREAMS

#endif  // Uses_TEditor

#if defined( Uses_TMemo ) && !defined( __TMemo )
#define __TMemo

class far TEvent;

struct TMemoData
{
    size_t length;
    char buffer[INT_MAX];
};

class TMemo : public TEditor
{

public:

    TMemo( const TRect&, TScrollBar *, TScrollBar *, TIndicator *, size_t );
    virtual void getData( void *rec );
    virtual void setData( void *rec );
    virtual size_t dataSize();
    virtual TPalette& getPalette() const;
    virtual void handleEvent( TEvent& );

private:

#ifndef NO_TV_STREAMS
    virtual const char *streamableName() const
        { return name; }

protected:

    TMemo( StreamableInit );
    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const near name;
    static TStreamable *build();
#endif  // ifndef NO_TV_STREAMS

};

#ifndef NO_TV_STREAMS
inline ipstream& operator >> ( ipstream& is, TMemo& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TMemo*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TMemo& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TMemo* cl )
    { return os << (TStreamable *)cl; }
#endif  // ifndef NO_TV_STREAMS

#endif  // Uses_TMemo


#if defined( Uses_TFileEditor ) && !defined( __TFileEditor )
#define __TFileEditor

#ifdef __WATCOMC__
#  include <direct.h>
#  define MAXPATH 260
#else
#  if !defined( __DIR_H )
#    include <Dir.h>
#  endif  // __DIR_H
#endif

class far TRect;
class far TScrollBar;
class far TIndicator;
class far TEvent;

class TFileEditor : public TEditor
{

public:

    char fileName[MAXPATH];
    TFileEditor( const TRect&,
                 TScrollBar *,
                 TScrollBar *,
                 TIndicator *,
                 const char *
               );
    virtual void doneBuffer();
    virtual void handleEvent( TEvent& );
    virtual void initBuffer();
    Boolean loadFile();
    Boolean save();
    Boolean saveAs();
    Boolean saveFile();
    virtual Boolean setBufSize( size_t );
    virtual void shutDown();
    virtual void updateCommands();
    virtual Boolean valid( ushort );

private:

    static const char * near backupExt;

#ifndef NO_TV_STREAMS
    virtual const char *streamableName() const
        { return name; }

protected:

    TFileEditor( StreamableInit );
    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const near name;
    static TStreamable *build();
#endif  // ifndef NO_TV_STREAMS

};

#ifndef NO_TV_STREAMS
inline ipstream& operator >> ( ipstream& is, TFileEditor& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TFileEditor*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TFileEditor& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TFileEditor* cl )
    { return os << (TStreamable *)cl; }
#endif  // ifndef NO_TV_STREAMS

#endif  // Uses_TFileEditor


#if defined( Uses_TEditWindow ) && !defined( __TEditWindow )
#define __TEditWindow

class far TFileEditor;

class TEditWindow : public TWindow
{

public:

    TEditWindow( const TRect&, const char *, int );
    virtual void close();
    virtual const char *getTitle( short );
    virtual void handleEvent( TEvent& );
    virtual void sizeLimits( TPoint& min, TPoint& max );

    TFileEditor *editor;

private:

    static const char * near clipboardTitle;
    static const char * near untitled;

#ifndef NO_TV_STREAMS
    virtual const char *streamableName() const
        { return name; }

protected:

    TEditWindow( StreamableInit );
    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const near name;
    static TStreamable *build();
#endif  // ifndef NO_TV_STREAMS

};

#ifndef NO_TV_STREAMS
inline ipstream& operator >> ( ipstream& is, TEditWindow& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TEditWindow*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TEditWindow& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TEditWindow* cl )
    { return os << (TStreamable *)cl; }
#endif  // ifndef NO_TV_STREAMS

#endif  // Uses_TEditWindow


#if defined( Uses_TFindDialogRec ) && !defined( __TFindDialogRec )
#define __TFindDialogRec

#if !defined( __STRING_H )
#include <String.h>
#endif  // __STRING_H

struct TFindDialogRec
{
    TFindDialogRec( const char *str, ushort flgs )
        {
        strcpy( find, str );
        options = flgs;
        }
    char find[maxFindStrLen];
    ushort options;
};

#endif  // Uses_TFindDialogRec

#if defined( Uses_TReplaceDialogRec ) && !defined( __TReplaceDialogRec )
#define __TReplaceDialogRec

#if !defined( __STRING_H )
#include <String.h>
#endif  // __STRING_H

struct TReplaceDialogRec
{
    TReplaceDialogRec( const char *str, const char *rep, ushort flgs )
        {
        strcpy( find, str );
        strcpy( replace, rep );
        options = flgs;
        }
    char find[maxFindStrLen];
    char replace[maxReplaceStrLen];
    ushort options;
};

#endif  // Uses_TReplaceDialogRec

#include "tvvo2.h"

