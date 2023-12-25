// BinaryQueue.h: interface for the CBinaryQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYQUEUE_H__89F52F54_29C9_11D6_8540_006052067816__INCLUDED_)
#define AFX_BINARYQUEUE_H__89F52F54_29C9_11D6_8540_006052067816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Class name		: CBinaryElements
// Description		:	������ �������� ��������.
//						��� �������� ������� ������ ����������� ��������� �� ����������� ������,
//						� ��� ������������ ����� ������ ������� ��� ������ ������������� ��� 
//						������� � �������� �� ������ �������.
class CBinaryElement  
{
public:
	CBinaryElement(PVOID pData);
	virtual ~CBinaryElement();
	enum enumOtherMember {First, Prev, Next, Last};

	/*
	// Function name	: GetOtherMember
	// Description	    :	���������� ������� pOtherMember ������������ �������� 
	//						(��� ���������� pMember)
	// Return type		: BOOL 
	// Argument         : CBinaryQueue * pMember
	// Argument         : CBinaryQueue * pOtherMember
	// Argument         : enumOtherMember OtherMember
	BOOL GetOtherMember(
		CBinaryElement * pMember, 
		CBinaryElement * pOtherMember, 
		enumOtherMember OtherMember,
		CRITICAL_SECTION * pcsMemberAccess);
	*/

	// Function name	: GetData
	// Description	    :	���������� pData �������� ��������
	// Return type		: PVOID 
	PVOID GetData() {return m_pData;};

	// Function name	: InsertMember
	// Description	    :	������� ������ �������� � ����� �������
	// Return type		: BOOL 
	// Argument         : CBinaryElement * pMember
	BOOL InsertMember( CBinaryElement * pMember );

	// Function name	: DeleteMember
	// Description	    :	�������� ��������. 
	//						������������ ��������� �� ��������� �� ��� ��������
	// Return type		: CBinaryElement *
	CBinaryElement * DeleteMember();
	
	// Function name	: GetMemberPrev
	// Description	    :	������������ ��������� ������� ������� 
	//						(������ ������� �� �������� ��� ���������� � pMember)
	// Return type		: CBinaryElement * 
	// Argument         : CBinaryElement * pMember
	CBinaryElement * GetMemberPrev( CBinaryElement * pMember = NULL );

	// Function name	: GetMemberNext
	// Description	    :	������������ ���������� ������� �������
	//						(������ ������� �� �������� ��� ���������� � pMember)
	// Return type		: CBinaryElement * 
	// Argument         : CBinaryElement * pMember
	CBinaryElement * GetMemberNext( CBinaryElement * pMember = NULL );

	// Function name	: GetMemberFirst
	// Description	    :	���������� ������ ������� �������
	// Return type		: CBinaryElement * 
	CBinaryElement * GetMemberFirst();

	// Function name	: GetMemberLast
	// Description	    :	���������� ��������� ������� �������
	// Return type		: CBinaryElement * 
	CBinaryElement * GetMemberLast();
	
	CBinaryElement * m_pMemberPrev;
	CBinaryElement * m_pMemberNext;

private:
	PVOID m_pData;
};

////////////////////////////////////////////////////////////////////
class CBinaryQueue
{
public:
	CBinaryQueue();
	virtual ~CBinaryQueue();

	// Function name	: GetElementCount
	// Description	    :	
	// Return type		: ULONG 
	ULONG GetElementCount();
	
	// Function name	: GetElement
	// Description	    :	���������� pData ������� � ������ ��������
	// Return type		: PVOID 
	PVOID GetElement();

	// Function name	: InsertElement
	// Description	    :	��������� pElement � ������� ���������
	// Return type		: BOOL 
	// Argument         : PVOID pElement
	BOOL InsertElement(PVOID pElement);

	// Function name	: InsertElement
	// Description	    :	��������� pElement � ������� ��������� �� ������ �����
	// Return type		: BOOL 
	// Argument         : PVOID pElement
	BOOL InsertFirstElement(PVOID pElement);

	// Function name	: DeleteElement
	// Description	    :	����������� ������ ������� �� �������.
	//						���������� ��� pData
	// Return type		: PVOID 
	PVOID DeleteElement();

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: DeleteElement
	//! \brief			:	����������� ��������� ������� �� �������
	//!						���������� FALSE, ���� ������� � ������� �����������
	//! \return			: PVOID 
	//! \param          : PVOID pData
	BOOL DeleteElement(PVOID pData);

private:
	CBinaryElement * volatile pMembers;
	CRITICAL_SECTION m_csElementAccess;
};

#endif // !defined(AFX_BINARYQUEUE_H__89F52F54_29C9_11D6_8540_006052067816__INCLUDED_)
