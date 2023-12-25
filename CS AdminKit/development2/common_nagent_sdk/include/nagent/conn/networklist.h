/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file conn/networklist.h
 * \author �����
 * \date 2006
 * \brief ���������, ���������� �� ������ ���������� � �������� ��������
 *
 */

#ifndef KLCONN_NETWORKLIST_H
#define KLCONN_NETWORKLIST_H

#include "./conn_types.h"

namespace KLCONN_NLST
{
	/*!
	\brief ��������� �������� ������� �������
	*/

	//!\brief ��� ������ ��������
	const wchar_t QUARANTINE_LIST_NAME[]	= L"Quarantine";

	//!\brief ��� ������ backup'�
	const wchar_t BACKUP_LIST_NAME[]		= L"Backup";

	//!\brief ��� ������ TIF'�
	const wchar_t TIF_LIST_NAME[]			= L"TIF";

	/*!
	\brief ���� ��������� �������� ������, ������������ �������� GetItemInfo.
		��� ������� Quarantine � Backup ������ ����������.
	*/

	const wchar_t c_szwItemId[]		= L"ListItemId";	// ������������� �������� ������ ( KLPAR::Value::STRING_T )
	const wchar_t c_szwFileTitle[]	= L"szFileTitle";	// ��� ����� (��� ����) ( KLPAR::Value::STRING_T )
	const wchar_t c_szwiStatus[]	= L"iObjStatus";	// ������ (WARNING,SUSP. � �.�.) ( KLPAR::Value::INT_T enum _OBJ_STATUS )

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

	const wchar_t c_szwStoreTime[]	= L"Q&B: StoreTime";	// ����� ��������� � �������� ( KLPAR::Value::DATE_TIME_T )

	const wchar_t c_szwVirusName[]	= L"VirusName";			// ��� �������������� ������ ( KLPAR::Value::STRING_T )
	const wchar_t c_szwObjSize[]	= L"Q&B: ObjSize";		// ������ ������� ( KLPAR::Value::INT_T )
	const wchar_t c_szwRestorePath[]= L"szRestorePath";		// ���� �������������� ������� (�.�. ������) ( KLPAR::Value::STRING_T )
	const wchar_t c_szwUser[]		= L"szUser";			// ��� ������������ ( KLPAR::Value::STRING_T )
	const wchar_t c_szwDescription[]= L"szDescription";			// �������������� ���� (����. ��� �����-����������) ( KLPAR::Value::STRING_T )
	const wchar_t c_szwLastCheckBaseDate[] = L"Q&B: sz_LastCheckBaseDate";	// ���� �������� ����, �� ������� ������ ���������� ��������� ��� ( KLPAR::Value::DATE_TIME_T )
	const wchar_t c_szwSentDate[]	= L"SentToKLDate";		// ���� ������� ������� � KL ( KLPAR::Value::DATE_TIME_T )

	/*!
	\brief file info, see NetworkListItemsFile 
	*/

    //! file name (without path) as it will be shown to the security administrator 
    const wchar_t c_szwNliFile_Name[]	= L"KLCONN_NLST_FNAME"; //STRING_T

    //! file size, 64-bit int
    const wchar_t c_szwNliFile_Size[]	= L"KLCONN_NLST_FIZE"; //LONG_T

	/*!
	\brief ���� �������� ��� ���������� ������� Quarantine � Backup	
	*/

	const wchar_t c_szwActionScan[]			= L"NLAction: Scan";

	const wchar_t c_szwActionDelete[]		= L"NLAction: Delete";
	
	const wchar_t c_szwActionRestore[]		= L"NLAction: Restore";

	const wchar_t c_szwActionScanExclude[]	= L"NLAction: ScanExclude";
	
	
}

namespace KLCONN
{	

	const wchar_t c_szwListName[]	= L"ListName";		// ��� �������� ������
	const wchar_t c_szwItemId[]		= L"ListItemId";	// ������������� �������� ������
	const wchar_t c_szwItemsIds[]	= L"ListItemsIds";	// ������ ��������������� ��������� ������


	/*!
	\brief ������ �������, ����������� ����������� � ������ ��������� �������� ������
		������ ������� ����������� ����������� ���������� ��������� ������� Notifier::Event

		������ ���� ������� ��� ���� ������� �����:

			c_szwListName - ��� �������� ������ ( KLPAR::Value::STRING_T )
			�_szwItemsId - ������������� ����������� �������� ������ ( KLPAR::Value::STRING_T )
		��� 
			c_szwListName - ��� �������� ������ ( KLPAR::Value::STRING_T )
			c_szwItemsIds - ������ ��������������� ��������� ������ ( KLPAR::Value::ARRAY_T ) 
	*/

	//!\brief ���������� �������� � ������� ������
	const wchar_t c_ev_ListItemAdded[]		= L"NLST: ItemAdded";

	//!\brief �������� �������� �� �������� �������
	const wchar_t c_ev_ListItemDeleted[]	= L"NLST: ItemDeleted";

	//!\brief ��������� �������� �������� �������
	const wchar_t c_ev_ListItemModified[]	= L"NLST: ItemModified";
	


	/*!
     \brief ���������, ���������� �� ������ ���������� � �������� ��������

    */

	class KLSTD_NOVTABLE NetworkList : public KLSTD::KLBaseQI
    {
    public:

		/*!
        \brief ���������� �������� ����������� �������� ������
			� ������ ������ ������������� ���������� ���� KLERR::Error*

        \param szwListName		[in]	��� �������� ������.
		\param szwListItemId	[in]	������������� �������� ������ ( ������ ������������� ������ ���� 
				�������� � ������ ���������� ( ����� ) )

		\param ppItemParams		[out]	��������� ��������. ���� ��������� ������� �� ������ � ������ 
				������ �������� �������������� NULL.
				������ ��������� ���������� � ����������� �� 
				��������������� ������. ( ��. ��������� � ������ ����� ).

		
		*/
        virtual void GetItemInfo( 
				const wchar_t*  szwListName,
				const wchar_t*  szwListItemId,
			    KLPAR::Params **ppItemParams ) = 0;

		/*!
        \brief ���������� ������ ��������������� ��������� ������
			� ������ ������ ������������� ���������� ���� KLERR::Error*

        \param szwListName		[in]	��� �������� ������.
		\param nItemsStartPos	[in]	��������� ������� ������
		\param nItemsCount		[in]	����������� ���������� ��������������� ( ���� <=0 ������������ ���� ����� � ��������� ������� )
		\param vecItemsIds		[out]	������ ��������������� ������
		*/

		virtual void GetItemsList( 
				const wchar_t*		szwListName,
				int					nItemsStartPos, 
				int					nItemsCount,
				KLSTD::AKWSTRARR&	vecItemsIds ) = 0;

		/*!
        \brief ��������� ��������� �������� ��� ��������� ( ���������� ) ������.
			����� ���������� �������� ��� ��������� ������, ��� ������� ��������, ���� ���� �� �� ���������,
			������ ���� ������������� ������� 
			� ������ ������ ������������� ���������� ���� KLERR::Error*

        \param szwListName		[in]	��� �������� ������.
		\param szwActionName	[in]	��������� ��� �������� ( ����� �������� ������������ ��� ����������� ������ ) 
				( ��. ��������� � ������ ����� ).		
		\param vecItemsIds		[in]	������ ��������������� ������, ��� �������� ���� ���������� ��������� �������� 
				( ���� ������ ������, �� ��� ����� ����������� ������ )
		*/

		virtual void DoItemsAction( 
				const wchar_t*			szwListName,
				const wchar_t*			szwActionName,
				const KLSTD::AKWSTRARR&	vecItemsIds ) = 0;

	};

	/*!
     \brief ���������, ���������� �� ������ � ������ ������, ���������������� � ��������� ������

    */
	class KLSTD_NOVTABLE NetworkListItemsFile : public KLSTD::KLBaseQI
	{
    public:
		/*!
		\brief ��������� �������� ������ �����
		*/
		enum FileOperationResult
		{
			NLF_Ok,					//!< ������ ����� ������� ����������	
			NLF_OkDownloaded,		//!< ������ ����� ������� ���������� � ��� ���� ��������� ������ ������� �����			
			NLF_FileNotFound,		//!< ���� �� ������			
			NLF_ErrorInOperation		//!< ������ ��� ������� ��������� ������ �����			
		};

		/*!
		\brief ������� ��������� �������� ���������� � ����� , 
                    +-c_szwNliFile_Name, 
                    +-c_szwNliFile_Size
		*/
        virtual void GetFileInfo( KLPAR::Params** ppFileInfo ) = 0;


		/*!
		\brief ������� ��������� �������� ������ ����� ������ ���������������� � ��������� ������		
		
		\param startPos [in] ������� ����� � ������� ���������� ��������� ������			
		\param chunkBuff [in,out] ����� ��� ������ ����� 
		\param chunkBuffSize [in] P����� ���������� ������
		\param receivedChunkSize [out] ������ ���������� ������
		*/
		virtual FileOperationResult GetFileChunk( 
                                        AVP_qword startPos, 
			                            void *chunkBuff, 
                                        size_t chunkBuffSize, 
                                        size_t &receivedChunkSize ) = 0;
	};


	class KLSTD_NOVTABLE NetworkList2 : public NetworkList
    {
    public:

		/*!
		\brief ������� ��������� �������� �������� ��� ������ � ������ ������,
				���������������� � ��������� ������

		\param szwListName		[in]	��� �������� ������.
		\param szwListItemId	[in]	������������� �������� ������
		\param ppListFile		[out]	��������� ��� ������ � ������
		*/
		virtual void GetItemFile( 
				const wchar_t*  szwListName,
				const wchar_t*  szwListItemId,
			    NetworkListItemsFile **ppListFile ) = 0;
		
	};
	
} // end namespace KLCONN

#endif // KLCONN_NETWORKLIST_H
