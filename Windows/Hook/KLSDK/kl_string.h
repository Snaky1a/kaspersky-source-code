#ifndef _KL_STRING_H_
#define _KL_STRING_H_

#include "kl_buffer.h"
#include "kl_list.h"

// ������-������� ��� ������ �� ���������

template <class T>
class CKl_SimpleString
{
public:
    T*          m_buffer;		// ������ ������.
    size_t      m_size;			// ������ ������
    size_t      m_length;		// ���-�� �������� ������ ��� ����� �������������� ����
    

    virtual T*          Find( T*  Str );        // ����� ���������
    
	size_t      Size();
    size_t      Length();

    T&  operator[] (size_t  i);

    CKl_SimpleString ( T* Str = NULL );
    virtual ~CKl_SimpleString();
};

// ansi ������
class CKl_AString : public CKl_SimpleString<unsigned char>
{
public:
	virtual unsigned char* Find( unsigned char*  Str );        // ����� ���������    

    CKl_AString( unsigned char*   Str = NULL );
    virtual ~CKl_AString();
};

// unicode ������
class CKl_UString : public CKl_SimpleString<unsigned short>
{
public:
    CKl_UString( wchar_t* Str = NULL );
    virtual ~CKl_UString();
};


#endif