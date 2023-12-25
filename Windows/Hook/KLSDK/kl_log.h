#ifndef _KL_LOG_H_
#define _KL_LOG_H_

#include "kl_object.h"
#include "kldef.h"
#include "klstatus.h"
#include "g_thread.h"
#include "kl_list.h"

class CKl_LogItem : public CKl_Object
{
public:
	QUEUE_ENTRY;    
	virtual KLSTATUS	Process() = 0;
    
    CKl_LogItem() {};
	virtual ~CKl_LogItem(){};
};


/*
 *	����� ������������ �������. 
 *  ��������� ��������� ����� � ������� ������ ������� CKl_LogItem
 *  ����� ����������� �������, �� ��������� ����� m_LogEvent.
 *  ����� ��������� ������� ��-������ � ��������� ������� SaveData ��� �������.
 *  ����� ������� ���, �� ����� ���� �� WaitForSingleObject
 *  ����� �����������, �� ���� ����� ������ �� ������ � ����������� �������.

 
 */
class CKl_Log   : public CKl_Object
{
public:    
    CKl_Log(void* LogMethod);
    virtual ~CKl_Log();

	bool        m_Continue;
    void*		m_LogMethod;	// ��������, � ������� �������� ���������� ��������� Item.
    CKl_Thread* m_LogThread;	// �����, ������� ������������ ���������
    KL_EVENT    m_LogEvent;		// �����, ���������, ��� ���� �������
	KL_EVENT	m_StopEvent;
	
    CKl_List<CKl_LogItem>* m_LogList;		// ������ �������
        
    KLSTATUS    OnThreadStart	( PVOID Context		);
    KLSTATUS    AddItem			( CKl_LogItem* Item	);
    
    static void LogRoutine		( PVOID    Context	);
};







#endif