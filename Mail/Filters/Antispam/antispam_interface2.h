/*!
*		
*		
*		\file	antispam_interface.h
*		\brief	��������� ������ ��������
*		
*		\author Vitaly DVi Denisov
*		
		��� ���������� ��������-������� ����������:
		1.	���������� ���� ������ �������������, ���������������, ��������, 
			� ����� ���������� ������������ ����������
		2.	��� ������ � ������� ������������ ������ ������ CMemoryAlloc
		3.	��� ��������� ��������� �� ����� ������ (� ������� Process � Train) ������������ 
			CObjectSystemToCheck::PtrCreate
		4.	��� ��������� ��������� ����� ������ � ���� ������� ������������ �����
			CObjectSystemToCheck::ObjectCreate
		5.	��� ��������� ������, ��������������� � ��������, ������� ������ CObjectIOToCheck �� ������ 
			CObjectToCheck � ������������ ������ CObjectToIOCheck::SeekRead � CObjectIOToCheck::GetSize
		6.	������ ���� CObjectSystemToCheck ����� ����� ������� �� ������ CObjectToCheck
		7.	��� ������������ ��������, ������� ��������-������ ������, ������������
			CObjectSystemToCheck::ObjectClose
		8.	��� ������������ ��������� ������������
			CObjectSystemToCheck::PtrClose
		9.	��� ��������� ������� ������� (�����, ��� ��� �����������, ��� ���������� � �.�.)
			������������ ����� CObjectToCheck::PropertyGet
			��������� �������� ������������ ���� ����������� � ���������� pgMESSAGE_.
			��� �������� �������� ���������� (char*).
			��������� � ���������� pgMESSAGE_ �������� ��� ������.
			��������� � ���������� pgMESSAGE_PART_ �������� ��� ����� ������.
		10.	��� ������ ���� ������ ������������ ��������� PR_SUCC � PR_FAIL. 
		11.	��� ���������� ��������, � ����� ����������� ���������� ��������� �������
			�� ������� ������������, ������������ ������ CObjectToCheck::GetTickCount ���
			������� ������ ��������� ������� � CObjectToCheck::CheckTimeOut ��� ������
			������������� ���������� ���������.
			����� CObjectToCheck::CheckTimeOut ������� �������� �� � ����� �������� 
			��������� ��������. ������������ ��� PR_FAIL �������������
			� ������������� ����������� ��������� ���������.
*		
*		
*		
*/		

#ifndef _ANTISPAM_INTERFACE2_H_
#define _ANTISPAM_INTERFACE2_H_

#ifndef IN
#define IN   // ��������������� ������: ������� �������� �������
#endif
#ifndef OUT
#define OUT  // ��������������� ������: �������� �������� �������
#endif

#ifndef PRAGUE_DEFINED
	//////////////////////////////////////////////////////////////////////////
	//
	//	������������ ���� ������ (����� �� Prague)
	//
	typedef long tERROR;
	#define PR_SUCC(e) (((tERROR)(e)) >= 0)
	#define PR_FAIL(e) (((tERROR)(e)) < 0)
	typedef unsigned int tDWORD;
	typedef double tQWORD;
	typedef unsigned int tPROPID;
	typedef void* tPTR;
	typedef unsigned int tBOOL;
	typedef unsigned int tUINT;
	//
	//	������������ ���� ������
	//
	//////////////////////////////////////////////////////////////////////////

	#define errOK 0 
	#define errNOT_IMPLEMENTED  -1 

	/* global Mail Message properties */

	#define pgMESSAGE_FROM						0x00001000 
	#define pgMESSAGE_ORIGINAL_FROM				0x00001001 
	#define pgMESSAGE_DISPLAY_FROM				0x00001002 
	#define pgMESSAGE_ORIGINAL_DISPLAY_FROM		0x00001003 
	#define pgMESSAGE_TO						0x00001004 
	#define pgMESSAGE_DISPLAY_TO				0x00001005 
	#define pgMESSAGE_CC						0x00001006 
	#define pgMESSAGE_DISPLAY_CC				0x00001007 
	#define pgMESSAGE_SUBJECT					0x00001008 
	#define pgMESSAGE_DATE						0x00001009 
	#define pgMESSAGE_MAILID					0x0000100a 
	#define pgMESSAGE_INTERNET_HEADERS			0x0000100b 
	#define pgMESSAGE_MIME_VERSION				0x0000100c 
	#define pgMESSAGE_RETURN_PATH				0x0000100d 


	/* global Mail Message Part properties */

	#define pgMESSAGE_PART_CONTENT_TYPE			0x00001020 
	#define pgMESSAGE_PART_TRANSFER_ENCODING	0x00001021 
	#define pgMESSAGE_PART_FILE_NAME			0x00001022 
	#define pgMESSAGE_PART_DISPLAY_NAME			0x00001023 
	#define pgMESSAGE_PART_CONTENT_ID			0x00001024 
	#define pgMESSAGE_PART_CONTENT_DESCRIPTION	0x00001025 
	#define pgMESSAGE_PART_CHARSET				0x00001026 
	#define pgMESSAGE_PART_CONTENT_LENGTH		0x00001027 

#endif//PRAGUE_DEFINED

//////////////////////////////////////////////////////////////////////////
//
//	���������� ���� ����� - �� ������ ������������ ��������-�������
//
namespace CAntispamCaller
{
	// �����, ��������������� ������ ������ � �������
	struct CMemoryAlloc 
	{
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Allocate
		//! \brief			:	����� ��������� ������.
		//!						� ������ ������ ���������� 0
		//! \return			: tPTR				- ��������� �� ����� ������
		//! \param          : tQWORD qwSize		- ��������� ������ ������
		virtual tPTR Allocate(tQWORD qwSize);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ReAllocate
		//! \brief			:	����� ����������������� ������
		//!						� ������ ������ ���������� 0
		//! \return			: tPTR				- ��������� �� ����� ������
		//! \param          : tPTR pObject		- �������� �����
		//! \param          : tQWORD qwNewSize	- ����� ������
		virtual tPTR ReAllocate(tPTR pObject, tQWORD qwNewSize);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Free
		//! \brief			:	����� ������������ ������
		//! \return			: void 
		//! \param          : tPTR pObject
		virtual void Free(tPTR pObject);
	};

	// �����, ��������������� ������ ������ � ��������
	struct CObjectToCheck
	{
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: PropertyGet
		//! \brief			:	����� ��������� ������ ���������� �������� �� �������
		//!						��� ���������� ���������� ������ ������������ �����������
		//!						��� ������ � ��������� ������ ������������ ������
		//! \return			: tERROR				- ��� ������
		//! \param          : OUT tDWORD* out_size	- ������ ������������� ������
		//! \param          : IN tPROPID prop_id	- ������������� ��������
		//! \param          : IN tPTR buffer		- ��������� �� ����� ��� �����������
		//! \param          : IN tDWORD size		- ��������� ������ ������
		virtual tERROR PropertyGet( 
			OUT tDWORD* out_size, 
			IN tPROPID prop_id, 
			IN tPTR buffer, 
			IN tDWORD size 
			)
		{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetTickCount
		//! \brief			:	���������� ���������� ��, ��������� � ������� ������ 
		//!						������������ �������. ������������ ��� ������� ������� ������ 
		//!						��������� ������� � ���������� � ������� CheckTimeout
		//! \return			: tDWORD 
		virtual tDWORD GetTickCount()
		{
			return GetTickCount();
		};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CheckTimeout
		//! \brief			:	�������� ��������� ��������.
		//! \return			: tERROR 
		//! \param          : tDWORD dwTimeOut		- ����������� �������
		//! \param          : tDWORD dwProcessBegin	- �������� GetTickCount, ����������� 
		//!											� ������ ������ ���������
		virtual tERROR CheckTimeout(tDWORD dwTimeOut, tDWORD dwProcessBegin)
		{
			return errOK;
		};
	};

	// �����, ��������������� ������ ������ � ��������� ��������
	struct CObjectSystemToCheck : public CObjectToCheck
	{

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CObjectSystemToCheck
		//! \brief			:	�����������, ��������� ������ CObjectSystemToCheck �� CObjectToCheck
		//! \param          : CObjectToCheck* pObject
		CObjectSystemToCheck(CObjectToCheck* pObject){};
		CObjectSystemToCheck(){};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: PtrCreate
		//! \brief			:	��������� ��������� �� ������ � �������
		//! \return			: tERROR 
		//! \param          : OUT tUINT* pObjPtr
		virtual tERROR PtrCreate(OUT tUINT* pObjPtr)
		{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetNextObject
		//! \brief			:	��������� ���������� ������� �� ������� ���������
		//!						������ ����� ���� ���������� ������ ������� ObjectClose
		//! \return			: tERROR 
		//! \param          : IN tUINT pObjPtr
		//! \param          : OUT CObjectToCheck** ppObject
		virtual tERROR ObjectCreate(IN tUINT pObjPtr, OUT CObjectToCheck** ppObject)
		{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ObjectClose
		//! \brief			:	������������ ������� �� ��������� pObjPtr
		//! \return			: tERROR 
		//! \param          : IN tUINT pObjPtr
		//! \param          : IN CObjectToCheck* pObject
		virtual tERROR ObjectClose(IN tUINT pObjPtr, IN CObjectToCheck* pObject)
		{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: PtrClose
		//! \brief			:	������������ ��������� �� ������ � �������
		//! \return			: tERROR 
		//! \param          : IN tUINT pObjPtr
		virtual tERROR PtrClose(IN tUINT pObjPtr)
		{return errNOT_IMPLEMENTED;};
	};

	struct CObjectIOToCheck : public CObjectToCheck
	{
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CObjectSystemToCheck
		//! \brief			:	�����������, ��������� ������ CObjectIOToCheck �� CObjectToCheck
		//! \param          : CObjectToCheck* pObject
		CObjectIOToCheck(CObjectToCheck* pObject){};
		CObjectIOToCheck(){};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: SeekRead
		//! \brief			:	����� ��������� ������ �� �������
		//! \return			: tERROR				- ��� ������
		//! \param          : OUT tDWORD* out_size	- ������ ������������� ������
		//! \param          : IN tQWORD offset		- ������� ������� (� ������)
		//! \param          : IN tPTR buffer		- ��������� �� ����� ��� �����������
		//! \param          : IN tDWORD size		- ��������� ������ ������
		virtual tERROR SeekRead( 
			OUT tDWORD* out_size, 
			IN tQWORD offset, 
			IN tPTR buffer, 
			IN tDWORD size 
			)
		{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetSize
		//! \brief			:	��������� ������� �������
		//! \return			: tERROR				- ��� ������
		//! \param          : OUT tQWORD* out_size	- ������ �������
		virtual tERROR GetSize( OUT tQWORD* out_size )
		{return errNOT_IMPLEMENTED;};
	};
}
//
//	���������� ���� ����� - �� ������ ������������ ��������-�������
//
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//
//	���������� ���� ����� - �� ������ ������������� ��������-�������
//
namespace CAntispamImplementer
{
	
	class CAntispamFilter
	{
	public:
		CAntispamFilter(){};
		virtual ~CAntispamFilter(){};
		
		//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� �������������
		struct InitParams_t;
		//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� ���������������
		struct ProcessParams_t;
		//TODO: ����� ���������� ����������, ����� ������ ��������-������ ����� ������� � �������� ����������
		struct Statistics_t;
		//TODO: ����� ���������� ����������, ����� ������ ��������-������ ����� ������� � �������� ���������� ��� ��������� �������
		struct ProcessStatistics_t;
		//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� ��������
		struct TrainParams_t;
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Init
		//! \brief			:	�������������� ��������-������ �������, ���������� � pInitData.
		//!						������������� ������ ��������� � ������������ ������.
		//! \return			: tERROR 
		//! \param          : CAntispamCaller::CMemoryAlloc* pMemoryAllocator
		//! \param          : InitParams_t* pInitParams
		virtual tERROR Init(
			CAntispamCaller::CMemoryAlloc* pMemoryAllocator, 
			InitParams_t* pInitParams
			)
			{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetStatistics
		//! \brief			:	������ ����������� ���������� 
		//! \return			: virtual tERROR 
		//! \param          : IN Statistics_t* p_Statistics
		virtual tERROR GetStatistics( IN Statistics_t* p_Statistics )
			{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Process
		//! \brief			:	��������� ������� pObject � ������ ���������� pdwResult
		//! \return			: tERROR								- ��� ������
		//! \param          : IN  CObjectSystemToCheck* pObject		- ������ ��� ���������������
		//! \param          : IN  ProcessParams_t* pProcessParams	- ��������� ���������������
		//! \param          : OUT long double* pdwResult			- ��������� ��������������� {0..1}
		//! \param          : IN  tDWORD dwTimeOut					- ������������ ����� ��� ��������������� (��)
		//! \param          : OUT ProcessStatistics_t* pProcessStat - ���������� ��������������� 
		virtual tERROR Process( 
			IN  CAntispamCaller::CObjectSystemToCheck* pObject, 
			IN  ProcessParams_t* pProcessParams, 
			OUT long double* pResult,
			IN  tDWORD dwTimeOut,
			OUT ProcessStatistics_t* pProcessStat = 0
			)
			{return errNOT_IMPLEMENTED;};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Train
		//! \brief			:	�������� ������� �� ������� pObject. 
		//!						����������� ����������� �������������� ������� � ����� 
		//!						������ bIsSpamObject
		//! \return			: tERROR						- ��� ������
		//! \param          : IN CObjectSystemToCheck* pObject	- ������ ��� ��������
		//! \param          : IN TrainParams_t* pTrainParams - ��������� ��������
		//! \param          : IN  tDWORD dwTimeOut			- ������������ ����� ��� �������� (��)
		virtual tERROR Train(
			IN CAntispamCaller::CObjectSystemToCheck* pObject, 
			IN TrainParams_t* pTrainParams,
			IN  tDWORD dwTimeOut
			)
			{return errNOT_IMPLEMENTED;};
	};
}
//
//	���������� ���� ����� - �� ������ ������������� ��������-�������
//
//////////////////////////////////////////////////////////////////////////

#endif//_ANTISPAM_INTERFACE2_H_


