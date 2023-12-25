/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file networklistproxy.h
 * \author ����� �����������
 * \date 2005
 * \brief ������ ���������� ��� ������� � ������� �������
 */


#if !defined(KLSPLP_NETWORKLISTPROXY)
#define KLSPLP_NETWORKLISTPROXY

#include <std/base/klbase.h>
#include <srvp/csp/klcsp.h>

namespace KLNLST
{
	//\brief ������ ���������� ������������ ��������� ������ � ���������� ��������� ������

	const wchar_t c_szwListItemId[]		= L"strId";					// ������������� �������� ������ �� �����
	const wchar_t c_szwItemId[]			= L"nId";					// ���������� ������������� �������� ������� ������
	const wchar_t c_szwHosDispalyName[] = L"strHostDisplayName";	// ��� �����
	const wchar_t c_szwHosName[]		= L"strHostName";			// ������������� �����
	const wchar_t c_szwListName[]		= L"strListName";			// ��� ������
	const wchar_t c_szwCreationTime[]	= L"tmCreation";			// ����� �������� �������� ������
	const wchar_t c_szwItemParams[]		= L"params";				// ��������� �������� ��� �������� ������
	const wchar_t c_szwItemTask[]		= L"taskName";				// ��� ������, ������� ��������� �� ���������� ��� �������� ������	

	//!\brief ������ ��������� ������
	const wchar_t ITEMS_ARRAY[]				= L"KLNLST_ITEMS_RANGE_ARRAY";
	
	class KLSTD_NOVTABLE NetworkListItemsFileProxy : public KLSTD::KLBaseQI
	{
	public:
		//!\brief ��������� �������� �����
		struct ItemsFileInfo
		{
			unsigned long		lTotalSize;
			std::wstring		wstrFileName;
		};

		//!\brief ��������� �������� ������ �����
		enum FileOperationResult
		{
			NLF_Ok,					//!< ������ ����� ������� ����������	
			NLF_OkDownloaded,		//!< ������ ����� ������� ���������� � ��� ���� ��������� ������ ������� �����			
			NLF_FileNotFound,		//!< ���� �� ������			
			NLF_ErrorInOperation		//!< ������ ��� ������� ��������� ������ �����			
		};

		virtual void GetFileInfo( ItemsFileInfo& fileInfo ) = 0;

		virtual FileOperationResult GetFileChunk( unsigned long startPos, 
			void *chunkBuff, int chunkBuffSize, int &receivedChunkSize ) = 0;
	};
	
	
	class KLSTD_NOVTABLE NetworkListProxy : public KLSTD::KLBaseQI 
	{
    public:
		
		virtual void AddListItemTask (
			const std::wstring &listName,
			int					itemId,
			const std::wstring &taskName,
			KLPAR::Params*		pTaskParams
			) = 0;
		
		virtual void AddListItemTask (
			const std::wstring &listName,
			std::vector<int>	itemsIds,
			const std::wstring &taskName,
			KLPAR::Params*		pTaskParams
			) = 0;

		virtual void ResetIterator (
            const std::wstring &listName,
            KLPAR::Params* pParamsIteratorDescr,
			const std::vector<std::wstring>& vect_fields,
			const std::vector<KLCSP::field_order_t>& vect_fields_to_order,
			long  lifetime,
			std::wstring& wstrIteratorId ) = 0;

        virtual long GetRecordCount( const std::wstring& wstrIteratorId )  = 0;

        virtual void GetRecordRange(
            const std::wstring& wstrIteratorId,
            long nStart,
            long nEnd,
            KLPAR::Params** pParamsEvents ) = 0;

		virtual void ReleaseIterator( const std::wstring& wstrIteratorId ) = 0;

		virtual void GetListItemsFile( const std::wstring &listName, int itemId, 
			NetworkListItemsFileProxy **ppItemsFile ) = 0;

	};
}

#endif // !defined(KLSPLP_NETWORKLISTPROXY)