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
		3.	��� ��������� ������� (� ������� Process � Train) ������������ 
			������ CObjectToCheck::SeekRead � CObjectToCheck::GetSize
		4.	��� ��������� ������� ������� (�����, ��� ��� �����������, ��� ���������� � �.�.)
			������������ ����� CObjectToCheck::PropertyGet
			��������� �������� ������������ ���� ����������� � ���������� pgMESSAGE_.
			��� �������� �������� ���������� (char*).
		5.	��� ������ ���� ������ ������������ ��������� PR_SUCC � PR_FAIL. 
		6.	��� ���������� ��������, � ����� ����������� ���������� ��������� �������
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

#ifndef _ANTISPAM_INTERFACE_H_
#define _ANTISPAM_INTERFACE_H_

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
		tPTR Allocate(tQWORD qwSize);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ReAllocate
		//! \brief			:	����� ����������������� ������
		//!						� ������ ������ ���������� 0
		//! \return			: tPTR				- ��������� �� ����� ������
		//! \param          : tPTR pObject		- �������� �����
		//! \param          : tQWORD qwNewSize	- ����� ������
		tPTR ReAllocate(tPTR pObject, tQWORD qwNewSize);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Free
		//! \brief			:	����� ������������ ������
		//! \return			: void 
		//! \param          : tPTR pObject
		void Free(tPTR pObject);
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
		tERROR PropertyGet( 
			OUT tDWORD* out_size, 
			IN tPROPID prop_id, 
			IN tPTR buffer, 
			IN tDWORD size 
			)
		{
			return errNOT_IMPLEMENTED;
		};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: SeekRead
		//! \brief			:	����� ��������� ������ �� �������
		//! \return			: tERROR				- ��� ������
		//! \param          : OUT tDWORD* out_size	- ������ ������������� ������
		//! \param          : IN tQWORD offset		- ������� ������� (� ������)
		//! \param          : IN tPTR buffer		- ��������� �� ����� ��� �����������
		//! \param          : IN tDWORD size		- ��������� ������ ������
		tERROR SeekRead( 
			OUT tDWORD* out_size, 
			IN tQWORD offset, 
			IN tPTR buffer, 
			IN tDWORD size 
			)
		{
			return errNOT_IMPLEMENTED;
		};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetSize
		//! \brief			:	��������� ������� �������
		//! \return			: tERROR				- ��� ������
		//! \param          : OUT tQWORD* out_size	- ������ �������
		tERROR GetSize( OUT tQWORD* out_size )
		{
			return errNOT_IMPLEMENTED;
		};

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetTickCount
		//! \brief			:	���������� ���������� ��, ��������� � ������� ������ 
		//!						������������ �������. ������������ ��� ������� ������� ������ 
		//!						��������� ������� � ���������� � ������� CheckTimeout
		//! \return			: tDWORD 
		tDWORD GetTickCount()
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
		tERROR CheckTimeout(tDWORD dwTimeOut, tDWORD dwProcessBegin)
		{
			return errOK;
		};
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
		CAntispamFilter();
		virtual ~CAntispamFilter();

		struct InitParams_t
		{
			//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� �������������
		};
		struct ProcessParams_t
		{
			//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� ���������������
		};
		struct ProcessStatistics_t
		{
			//TODO: ����� ���������� ����������, ����� ������ ��������-������ ����� ������� � �������� ����������
		};
		struct TrainParams_t
		{
			tBOOL bIsSpam;
			//TODO: ����� ���������� ����������, ����� ������ ����� ��������-������� ��� ��������
		};
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Init
		//! \brief			:	�������������� ��������-������ �������, ���������� � pInitData.
		//!						������������� ������ ��������� � ������������ ������.
		//! \return			: tERROR 
		//! \param          : CAntispamCaller::CMemoryAlloc* pMemoryAllocator
		//! \param          : InitParams_t* pInitParams
		tERROR Init(
			CAntispamCaller::CMemoryAlloc* pMemoryAllocator, 
			InitParams_t* pInitParams
			);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Process
		//! \brief			:	��������� ������� pObject � ������ ���������� pdwResult
		//! \return			: tERROR								- ��� ������
		//! \param          : IN  CObjectToCheck* pObject			- ������ ��� ���������������
		//! \param          : IN  ProcessParams_t* pProcessParams	- ��������� ���������������
		//! \param          : OUT long double* pdwResult			- ��������� ��������������� {0..1}
		//! \param          : IN  tDWORD dwTimeOut					- ������������ ����� ��� ��������������� (��)
		//! \param          : OUT ProcessStatistics_t* pProcessStat - ���������� ��������������� 
		tERROR Process( 
			IN  CAntispamCaller::CObjectToCheck* pObject, 
			IN  ProcessParams_t* pProcessParams, 
			OUT long double* pResult,
			IN  tDWORD dwTimeOut,
			OUT ProcessStatistics_t* pProcessStat = 0
			);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Train
		//! \brief			:	�������� ������� �� ������� pObject. 
		//!						����������� ����������� �������������� ������� � ����� 
		//!						������ bIsSpamObject
		//! \return			: tERROR						- ��� ������
		//! \param          : IN CObjectToCheck* pObject	- ������ ��� ��������
		//! \param          : IN TrainParams_t* pTrainParams - ��������� ��������
		//! \param          : IN  tDWORD dwTimeOut			- ������������ ����� ��� �������� (��)
		tERROR Train(
			IN CAntispamCaller::CObjectToCheck* pObject, 
			IN TrainParams_t* pTrainParams,
			IN  tDWORD dwTimeOut
			);
	};
}
//
//	���������� ���� ����� - �� ������ ������������� ��������-�������
//
//////////////////////////////////////////////////////////////////////////

#endif//_ANTISPAM_INTERFACE_H_


