/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file nagent/nlst/productslists.h
 * \author ����� �����������
 * \date 2005
 * \brief ��������� ��� ������ ����������� ������� �������
 */

#if !defined(KLNLST_PRODUCTSLISTS)
#define KLNLST_PRODUCTSLISTS

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif // WIN32

#include <nagent/conn/networklist.h>


namespace KLNLST_PRODUCT
{
	/*
		!\brief ��� ������ ��������
	*/
	const wchar_t KLNLST_PRODUCT_QUARANTINE_LIST_NAME[]			= L"Quarantine";

	/*
		!\brief ��� ������ backup'�
	*/
	const wchar_t KLNLST_PRODUCT_BACKUP_LIST_NAME[]				= L"Backup";

	/*
		!\brief ��� ������ backup'�
	*/
	const wchar_t KLNLST_PRODUCT_TIF_LIST_NAME[]				= L"TIF";

} // end namespace KLNLST_PRODUCT

namespace KLNAGNLST {

const wchar_t sz_ItemsIdsList[] = L"ItemsIdsList";			

} // end namespace KLNAGNLST

namespace KLNLST_QB
{

	
	/*
		!\brief ������������� �������� �� ������� �� ��������� ������ Q&B
	*/
	const wchar_t KLNLST_Q_CHANGE_SUBS_ID[]			=	L"Q_CHANGE_SUBS";
	const wchar_t KLNLST_B_CHANGE_SUBS_ID[]			=	L"B_CHANGE_SUBS";

	// ��� ���������� Q&B
	const wchar_t KLNLST_QBACKUP_COMPONENT_NAME[]		=	L"Quarantine & Backup";


	// ������������ �� KAVQBackup.h
	///////////////////////////////////////////////////////////////////////////////

	// ����� ����� � ���������� �������� ������ 'Quarantine'
	const wchar_t sz_ObjName[]	= L"ObjName";			// ��� ������� � ���������
	const wchar_t sz_RestorePath[] = L"szRestorePath";	// ���� �������������� ������� (�.�. ������)
	const wchar_t sz_Description[] = L"szDescription";	// �������������� ���� (����. ��� �����-����������)
	const wchar_t sz_FileTitle[] = L"szFileTitle";		// ��� ����� (��� ����)
	const wchar_t sz_Domain[] = L"szDomain";			// �����
	const wchar_t sz_Computer[] = L"szComputer";		// ��� ����������
	const wchar_t sz_User[] = L"szUser";				// ��� ������������
	const wchar_t sz_VirusName[] = L"VirusName";		// ��� �������������� ������ 
	const wchar_t sz_iStatus[]  = L"iObjStatus";		// ������ (WARNING,SUSP. � �.�.)
	const wchar_t sz_StoreTime[] = L"Q&B: StoreTime";	// ����� ��������� � ��������
	const wchar_t sz_ObjSize[] = L"Q&B: ObjSize";		// ������ ������� � ���������
	const wchar_t sz_OriginalSize[] = L"Q&B: OriginalSize"; // ������� ������ �������
	const wchar_t sz_SentDate[] = L"SentToKLDate";		// ���� ������� ������� � KL
	const wchar_t sz_LastCheckBaseDate[] = L"Q&B: sz_LastCheckBaseDate";	// ���� �������� ����, �� ������� ������ ���������� ��������� ���
	const wchar_t sz_FilesArray[] = L"FilesArray";		// ������ � ������� ������ (��� �������� ���������)
	const wchar_t sz_iAskUser[] = L"Q&B: Ask User";		// ���������� �� ������������?
	const wchar_t sz_iReplace[] = L"Q&B: Replace";

	const wchar_t sz_StorageType[]= L"StorageType";		// �������� ��� �����?
	const int	  c_StorageTypeQuarantine = 1;
	const int	  c_StorageTypeBackup = 2;

	typedef enum _OBJ_STATUS {
		OBJ_STATUS_INFECTED = 1,
		OBJ_STATUS_WARNING = 2,
		OBJ_STATUS_SUSPICIOUS = 3,
		OBJ_STATUS_BY_USER = 4,
		OBJ_STATUS_FALSEALARM = 5,
		OBJ_STATUS_CURED = 6,
		OBJ_STATUS_CLEAN = 7,
		OBJ_STATUS_PASSWORD_PROTECTED = 8
	} OBJ_STATUS;

	// ���������������� ������ ��� ��������� ������ 
	///////////////////////////////////////////////////////////////////////////////
	// 1. ������������ ������ �� ���������
	//	- sz_ObjName - (!)��� ������� ���������
	//	- sz_StorageType - ��� ��������� (�������� ��� �����)
	//	- sz_RestorePath - ���� ��� ��������������
	//	- sz_iAskUser - ���������� �� ���� � ������������ 
	//	- sz_iReplace - ���� ����� ���� ��� ����������, ��������.
	const wchar_t szQBT_Restore[] = L"RestoreObj";
	///////////////////////////////////////////////////////////////////////////////
	// 2. ������� ������ �� ���������
	//	- sz_StorageType - ��� ��������� (�������� ��� �����)
	//	- sz_FilesArray  - ������ ���� �������� ��� ��������
	const wchar_t szQBT_Delete[] = L"DeleteObj";
	///////////////////////////////////////////////////////////////////////////////
	// 3. ��������� ������ �� ���������
	//	- sz_FilesArray  - ������ ���� �������� ��� ��������. ��� ���������� ����� ��������� ����������� ���� ��������.
	const wchar_t szQBT_ScanQuarantine[] = L"ScanQuarantine";
	///////////////////////////////////////////////////////////////////////////////
	// 4. ���������� � ������������� ����
	//	- sz_FilesArray  - ������ ���� �������� ��� ����������.
	const wchar_t sz_AddInTrusted[] = L"AddInTrust";
	
	
	
	
	///////////////////////////////////////////////////////////////////////////////
	// ������ �������:
	// 
	// ��� ������������ ��������� ������ �������
	// ��������� �������
	//	��� ���� ��������� ODS
	//		KLODSCN::c_szwTask_ObjectType
	//		KLODSCN::c_szwTask_ObjectName
	//		KLODSCN::c_szwTask_InfectionType
	//		KLODSCN::c_szwTask_DetectionType
	//		KLODSCN::c_szwTask_Disinfectability
	//		KLODSCN::c_szwTask_VirusName
	//		KLODSCN::c_szwTask_DefaultResult
	//		KLODSCN::c_szwTask_ResultArray
	//		KLODSCN::c_szwDelay_ProcessInfo
	//	��� ���� ��������� Q&B
	//		sz_ObjName			- ��� ������� ���������
	//		sz_EmbeddedObj		- ��� ���������� ������� (���� ����)
	//		KLQB::sz_iStatus	- ������ ������ ����� ��������
	const wchar_t c_szwEvent_ObjStatusChanged[] = L"Q&B: Object Detected";
	///////////////////////////////////////////////////////////////////////////////
	// ������ ������� � ��������
	//	KLQB::sz_FullObjName	- ������ ���� � ����� ����� ���������
	//	KLQB::sz_ObjName		- ��� ����� ���������
	//	KLQB::sz_FileName		- ������ ��� ��������� �����
	const wchar_t c_szwEvent_ObjQuarantined[] = L"Q&B: Object Quarantined";
	///////////////////////////////////////////////////////////////////////////////
	// ��������� �������� �������� ������� (��������)
	// sz_FilesArray - ������ � ������� ��������
	const wchar_t c_szwEvent_ObjQuarDeleted[] = L"Q&B: QuarObject Deleted";
	///////////////////////////////////////////////////////////////////////////////
	// ��������� �������� �������������� ������� (��������)
	const wchar_t c_szwEvent_ObjQuarRestored[] = L"Q&B: QuarObject Restored";


	

	const wchar_t sz_ErrorCode[] = L"iErrorCode";	// ��� ������ (������������ ��������)
	const wchar_t sz_ObjectIds[] = L"ObjectIds";		// ������ ��������������� �������	

	// �������� �������� �� �������
	const wchar_t c_szwEvent_ObjectInfo[] = L"Q&B: Object Info Obtained";

	

	// 11. ( Task ) �������� �������� �� �������	
	const wchar_t szQBT_GetObject[] = L"GetObject";

	// 7. ( Task ) �������� ������ �������� � ���������
	const wchar_t szQBT_GetObjectsList[] = L"GetObjectsList";

	const wchar_t sz_StartPos[] = L"StartPos";			// ��� ��������� ������ ������
	const wchar_t sz_Count[] = L"Count";

	const wchar_t c_szwTaskODSLogical[] = L"KLODS_TA_SCAN_TASK";
	const wchar_t BL_SCANQUARANTINE_ASYNC_ID[]	= L"ods-scanquar-async-id";

	inline bool CheckTaskName( const std::wstring &listName, 			
			const std::wstring				&taskName,
			KLPAR::Params					*pTaskParams,
			bool							&forAllItemsFromHost )
	{
		forAllItemsFromHost = false;
		if ( taskName==szQBT_ScanQuarantine ) forAllItemsFromHost = true;
		return true;
	}


#ifdef _WIN32
	////////////////////////////////////////////////////////
	// ����������� �� ����� ..\ak_plugin\shared\StorageObj.h

	#define OBJ_HDR_SIGN_SIZE			4

	// ��������� ������������ �����
	typedef struct _typeQFileHeaderStr
	{
		char cSignature[OBJ_HDR_SIGN_SIZE];		// ��������� KLQF
		int iVersion;			// ������ ������������ �����
		int iObjType;			// ��� ������� ���������
		int iObjStatus;			// ������ �������
		time_t tSentToKL;		// ���� ������� ������� � KL
		DWORD dwFlags;
		time_t tBaseDate;		// ���� �������� ����, �� ������� ������ ���������� ��������� ���

	// ����������� �������� ��������� �����
		FILETIME tCreateTime;	// ����� �������� �����
		FILETIME tLastAccess;	// ����� ���������� ������� � �����
		FILETIME tLastWrite;	// 
		DWORD dwAttributes;		// ��������

		DWORD dwReserved[4];	// �� �������

		DWORD dwStringSize;			// ������ ���������� ����� ��������� (� ������)

		_typeQFileHeaderStr()
		{
			memset(this,0,sizeof(_typeQFileHeaderStr));
		}

	} typeQFileHeaderStr;

	// ������ �� ������� � ����������� ����
	typedef struct _typeObjInfoSerializedHeader
	{
		typeQFileHeaderStr Hdr;
		FILETIME ftPlaceTime;
		int iNewStatus;
		wchar_t szObjName[MAX_PATH];

		_typeObjInfoSerializedHeader() {memset(this,0,sizeof(typeObjInfoSerializedHeader));}
	
	} typeObjInfoSerializedHeader;	

	// ����������� �� ����� ..\ak_plugin\shared\StorageObj.h
	////////////////////////////////////////////////////////
#endif

} // end namespace KLNLST_QB

#endif // !defined(KLNLST_PRODUCTSLISTS)
