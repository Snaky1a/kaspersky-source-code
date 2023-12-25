#ifndef _KL_DEBUG_H
#define _KL_DEBUG_H

#include "kl_object.h"
#include "kl_list.h"
#include "klstatus.h"
#include "kl_DebugMask.h"

#define DISPATCHER_ID_LOG   0x1
#define DISPATCHER_ID_TRACE 0x2

#ifndef USER_MODE
#define LOG_API __stdcall
#else
#define LOG_API __cdecl
#endif

KLSTATUS
DbgMessage(char* message, ...);

// ������� ����� ��� ������ ���������� ����������
class CKl_DebugInfo : public CKl_Object 
{    
    unsigned long   m_nLevel;
    unsigned long   m_nMask;
    unsigned long   m_nOutput;
public:
    ULONG           m_ID;
    char            m_DrvTag[10];
    bool            m_Disabled;     // ���� true, �� ���� �����������
    
    CKl_DebugInfo( char* DrvTag, unsigned long Level = 0, unsigned long Mask = 0 );
    ~CKl_DebugInfo();

    void            SetDebugLevel(unsigned long Level);
    void            SetDebugMask(unsigned long  Mask);
    unsigned long   DebugLevel();
    unsigned long   DebugMask();
    void            Enable();
    void            Disable();
    bool            isMatched(unsigned long Level, unsigned long    Mask);
    virtual void    Print(unsigned long Mask, unsigned long Level, char* message, ...);
    virtual void    Stop(char* message, ...);
};

/*
 *	����� ��� ������ ���������� ���������� � ���� trace-��
 */
class CKl_TraceDebugInfo : public CKl_DebugInfo
{
public:
    CKl_TraceDebugInfo(char* DrvTag);
    CKl_TraceDebugInfo(char* DrvTag, unsigned long Level, unsigned long Mask);
    ~CKl_TraceDebugInfo();
    virtual void    Print(unsigned long Mask, unsigned long Level, char* message, ...);
    virtual void    Stop(char* message, ...);
};

class CKl_LogMessage : public CKl_Object
{
public :
    char*           m_message;      // ��������� � ANSI �������
    size_t          m_size;         // ������ ������, ���������� ��� ���������.
    LIST_ENTRY      m_ListEntry;        // ����� � ������.
    CKl_LogMessage( char*    message, size_t Size = 0);
    ~CKl_LogMessage();
};

/*
 *	����� ��� ������ ���������� ���������� � ���� ����� � ������
 */
class CKl_LogDebugInfo : public CKl_DebugInfo
{
    CKl_List<CKl_LogMessage>*   m_LogList;
    KL_EVENT                    m_LogListEvent;
    char*                       m_OutputFile;
public:
    CKl_LogDebugInfo(char* DrvTag);
    CKl_LogDebugInfo(char* DrvTag, unsigned long Level, unsigned long Mask);
    ~CKl_LogDebugInfo();    
    virtual void    Print(unsigned long Mask, unsigned long Level, char* message, ...);
    virtual void    Stop(char* message, ...);

    void            SetOutputFile(char* FileName);
    static  void  LOG_API  LogFlushRoutine(void*   Context);
};

extern CKl_DebugInfo*  Dbg;
static bool MemTrackEnable = false;

#endif // _KL_DEBUG_H