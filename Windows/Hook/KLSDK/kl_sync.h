#ifndef _SYNC_OBJECTS_H_
#define _SYNC_OBJECTS_H_

#include "kl_object.h"
#include "kldef.h"

#define KL_STATE_NONSIGNALLED   0x0
#define KL_STATE_SIGNALLED      0x1

// ������� ����� ��� ��������, �� ������� ����� ��������� �������� Wait.
class CKl_SyncObject :public CKl_Object
{
public:
    ULONG   m_State;
    PVOID*  m_pSyncObject;

    CKl_SyncObject();
    virtual ~CKl_SyncObject();

    virtual 
        ULONG
                Wait( KL_TIME WaitTime );
};


class CKl_Event : public CKl_SyncObject
{
public:
    KL_EVENT    m_Event;
    CKl_Event();
    virtual ~CKl_Event();

    void        Set();
    void        Clear();
    void        isSignalled();
};

// ��������� � ���������� ���������, ����� m_SemCount == 0
// ����� ������������. ������ ����� Wait ��������� m_SemCount �� 1
class CKl_Semaphore : public CKl_SyncObject
{
public:
    KL_EVENT    m_Event;
    ULONG       m_SemCount;
    
    CKl_Semaphore(ULONG Count);
    virtual ~CKl_Semaphore();
    
    ULONG       Release();
    virtual 
        ULONG
                Wait( KL_TIME WaitTime );
};

#endif