/*------------------------------------------------------------*/
/* filename - tfiledtr.cpp                                    */
/*                                                            */
/* function(s)                                                */
/*            TFileEditor member functions                    */
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

#define Uses_TGroup
#define Uses_TEditor
#define Uses_TFileEditor
#define Uses_TEvent
#define Uses_opstream
#define Uses_ipstream
#include "include\tv.h"
#include "include\tvdir.h"

#include <Limits.h>
#include <string.h>
#include <fstream.h>
#include <io.h>
#include <stdio.h>

inline ushort min( size_t u1, size_t u2 )
{
    return u1 < u2 ? u1 : u2;
}

TFileEditor::TFileEditor( const TRect& bounds,
                          TScrollBar *aHScrollBar,
                          TScrollBar *aVScrollBar,
                          TIndicator *aIndicator,
                          const char *aFileName
                        ) :
    TEditor( bounds, aHScrollBar, aVScrollBar, aIndicator, 0 )
{
    if( aFileName == 0 )
        fileName[0] = EOS;
    else
        {
        strcpy( fileName, aFileName );
        fexpand( fileName );
        if( isValid )
            isValid = loadFile();
        }
}

void TFileEditor::doneBuffer()
{
    delete buffer;
}

void TFileEditor::handleEvent( TEvent& event )
{
    TEditor::handleEvent(event);
    switch( event.what )
        {
        case evCommand:
            switch( event.message.command )
                {
                case cmSave:
                    save();
                    break;
                case cmSaveAs:
                    saveAs();
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    clearEvent(event);
}

void TFileEditor::initBuffer()
{
    buffer = new char[bufSize];
}

Boolean TFileEditor::loadFile()
{
    ifstream f( fileName, ios::in | ios::binary );
    if( !f )
        {
        setBufLen( 0 );
        return True;
        }
    else
        {
        long fSize = filelength( f.rdbuf()->fd() );
        if( fSize > (UINT_MAX-0x1F) || setBufSize(ushort(fSize)) == False )
            {
            editorDialog( edOutOfMemory );
            return False;
            }
        else
            {
            if ( fSize > INT_MAX )
            {
               f.read( &buffer[bufSize - size_t(fSize)], INT_MAX );
               f.read( &buffer[bufSize - size_t(fSize) + INT_MAX],
                                size_t(fSize - INT_MAX) );

            }
            else
               f.read( &buffer[bufSize - size_t(fSize)], size_t(fSize) );
            if( !f )
                {
                editorDialog( edReadError, fileName );
                return False;
                }
            else
                {
                setBufLen(size_t(fSize));
                return True;
                }
            }
        }
}

Boolean TFileEditor::save()
{
    if( *fileName == EOS )
        return saveAs();
    else
        return saveFile();
}

Boolean TFileEditor::saveAs()
{
    Boolean res = False;
    if( editorDialog( edSaveAs, fileName ) != cmCancel )
        {
        fexpand( fileName );
        message( owner, evBroadcast, cmUpdateTitle, 0 );
        res = saveFile();
        if( isClipboard() == True )
            *fileName = EOS;
        }
    return res;
}

static void writeBlock( ofstream& f, char *buf, unsigned len )
{
    while( len > 0 )
        {
        int l = len < INT_MAX ? len : INT_MAX;
        f.write( buf, l );
        buf += l;
        len -= l;
        }
}

Boolean TFileEditor::saveFile()
{
    char drive[MAXDRIVE];
    char dir[MAXDIR];
    char file[MAXFILE];
    char ext[MAXEXT];

    if( (editorFlags & efBackupFiles) != 0 )
        {
        fnsplit( fileName, drive, dir, file, ext );
        char backupName[MAXPATH];
        fnmerge( backupName, drive, dir, file, backupExt );
        unlink( backupName );
        rename( fileName, backupName );
        }

    ofstream f( fileName, ios::out | ios::binary );

    if( !f )
        {
        editorDialog( edCreateError, fileName );
        return False;
        }
    else
        {
        writeBlock( f, buffer, curPtr );
        writeBlock( f, buffer+curPtr+gapLen, bufLen-curPtr );

        if( !f )
            {
            editorDialog( edWriteError, fileName );
            return False;
            }
        else
            {
            modified = False;
            update(ufUpdate);
            }
        }
    return True;
}

Boolean TFileEditor::setBufSize( size_t newSize )
{
#ifdef __DOS16__
    if( newSize > 0xF000 )
        newSize = 0xFFE0;
    else
        newSize = (newSize + 0x0FFF) & 0xF000;
#else
    newSize = (newSize + 0x0FFF) & (UINT_MAX-0x0FFF);
#endif
    if( newSize != bufSize )
        {
        char *temp = buffer;
        if( (buffer = new char[newSize]) == 0 )
            {
            delete temp;
            return False;
            }
        size_t n = bufLen - curPtr + delCount;
        memcpy( buffer, temp, min( newSize, bufSize ) );
        memmove( &buffer[newSize - n], &temp[bufSize - n], n );
        delete temp;
        bufSize = newSize;
        gapLen = bufSize - bufLen;
        }
    return True;
}

void TFileEditor::shutDown()
{
    setCmdState(cmSave, False);
    setCmdState(cmSaveAs, False);
    TEditor::shutDown();
}

void TFileEditor::updateCommands()
{
    TEditor::updateCommands();
    setCmdState(cmSave, True);
    setCmdState(cmSaveAs, True);
}

Boolean TFileEditor::valid( ushort command )
{
    if( command == cmValid )
        return isValid;
    else
        {
        if( modified == True )
            {
            int d;
            if( *fileName == EOS )
                d = edSaveUntitled;
            else
                d = edSaveModify;

            switch( editorDialog( d, fileName ) )
                {
                case cmYes:
                    return save();
                case cmNo:
                    modified = False;
                    return True;
                case cmCancel:
                    return False;
                }
            }
        }
    return True;
}

#ifndef NO_TV_STREAMS
void TFileEditor::write( opstream& os )
{
    TEditor::write( os );
    os.writeString( fileName );
    os << selStart << selEnd << curPtr;
}

void *TFileEditor::read( ipstream& is )
{
    TEditor::read( is );
    is.readString( fileName, sizeof( fileName ) );
    if( isValid )
        {
        isValid = loadFile();
        size_t sStart, sEnd, curs;
        is >> sStart >> sEnd >> curs;
        if( isValid && sEnd <= bufLen )
            {
            setSelect( sStart, sEnd, Boolean(curs == sStart) );
            trackCursor( True );
            }
        }
    return this;
}

TStreamable *TFileEditor::build()
{
    return new TFileEditor( streamableInit );
}

TFileEditor::TFileEditor( StreamableInit ) : TEditor( streamableInit )
{
}
#endif  // ifndef NO_TV_STREAMS

