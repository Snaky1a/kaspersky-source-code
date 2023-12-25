/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	AntispamOUSupportClass.h
*		\brief	����� ��������� ��������-������� � Outlook
*		
*		\author Vitaly DVi Denisov
*		\date	07.09.2004 14:43:56
*		
*		
*/		


#ifndef _ANTISPAMOUSUPPORTCLASS_H_
#define _ANTISPAMOUSUPPORTCLASS_H_

#include <Prague/prague.h>
#include <Prague/pr_cpp.h>
#include <Mail/structs/s_mcou_antispam.h>
#include <stuff/thread.h>
#include <Prague/iface/i_objptr.h>
#include <Mail/iface/i_as_trainsupport.h>
#include <Prague/iface/i_csect.h>
#include <string>
#include <Prague/pr_wrappers.h>

#include "../mapiedk/mapiedk.h"
extern CMAPIEDK* g_pMAPIEDK;

#include "backgroundscan/backgroundscan.h"

//! ������������� ������������ ����� ��� ������������� ������
#ifndef PR_MESSAGE_PARENT_FOLDER
	#define	PR_MESSAGE_PARENT_FOLDER	PROP_TAG(PT_BINARY, 0x646A)
#endif

//! ��������� � ���� �������� ���������� � ���, ��� �� ��������� ��� ���������
//! ��� �������� ��� ������ �������� ������������� ���������
#ifndef PR_MESSAGE_AS_PROCESSED
	#define	PR_MESSAGE_AS_PROCESSED		PROP_TAG(PT_LONG, 0x646B)
#endif


#ifdef ULRELEASE
#undef ULRELEASE
#define ULRELEASE(x) \
	if (x)	\
	{                    \
		g_pMAPIEDK->pUlRelease((x));  \
		(x) = NULL;      \
	}
#endif

#ifdef MAPIFREEBUFFER
#undef MAPIFREEBUFFER
#define MAPIFREEBUFFER(x) \
	if (x)	\
	{                         \
		g_pMAPIEDK->pMAPIFreeBuffer((x));  \
		(x) = NULL;           \
	}
#endif

#ifdef FREEPADRLIST
#undef FREEPADRLIST
#define FREEPADRLIST(x) \
	if (x)	\
	{                       \
		g_pMAPIEDK->pFreePadrlist((x));  \
		(x) = NULL;         \
	}
#endif

#ifdef FREEPROWS
#undef FREEPROWS
#define FREEPROWS(x)    \
	if (x)	\
	{                       \
		g_pMAPIEDK->pFreeProws((x));     \
		(x) = NULL;         \
	}
#endif

namespace AntispamOUSupport
{
	class CAntispamOUSupportClass; //!< forward declaration
	extern CAntispamOUSupportClass* g_pAntispamOUSupportClass;

	//! ��������� ��� ���������� ��������
	typedef TrainFolderInfoList_t AntispamPluginTrainSettings_t;
	

	//! �������� � ���������� ������� (� ������ ActionOnMessage)
	enum Action_t
	{ 
		TrainAsSpam,	//! ��� - ����
		TrainAsHam,		//! ��� - �� ����
		RemoveFromSpam, //! ������� ��� ������ �� ���� �����
		RemoveFromHam,	//! ������� ��� ������ �� ���� ��_�����
		Process			//! �������������� ������
	};

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: TrainStatusCallback_t
	//! \brief			:	Callback, ������� ����� ���������� �� ��������� 
	//!						�������� ������� ������.
	//!						���� �� ������ E_FAIL, ��� ����� �������� �� ���������
	//!						��������.
	//! \return			: HRESULT 
	//! \param          : void* _context - �������� ����������
	//! \param          : tULONG ulMessagesCount - ������� ����� ����� � ������� �� ����������
	//! \param          : tULONG ulMessagesProcessed - ������� ����� ��������������
	//! \param          : cStringObj szCurrentFolder - ������� �����
	//! \param          : cStringObj szCurrentMessage - ������� ���������
	typedef HRESULT (*TrainStatusCallback_t) (
		void* _context,
		tULONG ulMessagesCount, 
		tULONG ulMessagesProcessed, 
		cStringObj szCurrentFolder, 
		cStringObj szCurrentMessage
		);

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: AntispamTaskStatus
	//! \brief			:	��� ������� ����� ���������� ��� ��������� �������.
	//!						�� ���������� ����� �������� ��������.
	//! \return			: void 
	//! \param          : tTaskState taskState
	void AntispamTaskStatus( tTaskState taskState );
	
	class CAntispamOUSupportClass
	{
	public:
		CAntispamOUSupportClass();
		virtual ~CAntispamOUSupportClass();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: IsTaskExist
		//! \brief			:	check existance of the <sProfileName> task
		//! \return			: tBOOL 
		static tBOOL IsTaskExist(LPCSTR sProfileName);
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ShowProductASSettings
		//! \brief			:	��������� �������� �������� ��������� � ��������
		//! \return			: tERROR 
		static tERROR ShowProductASSettings();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: IsAVPTaskManagerEnabled
		//! \brief			:	����������, �������� �� AVP
		//! \return			: static bool 
		static bool IsAVPTaskManagerEnabled();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: IsAntispamEngineEnabled
		//! \brief			:	����������, �������� �� ���� ���������
		//! \return			: static bool 
		static bool IsAntispamEngineEnabled();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: IsAntispamEngineEnabled
		//! \brief			:	����������, �������� �� ���� ���������
		//! \return			: static check_algorithm_t 
		check_algorithm_t GetCheckAlgorithm();

		inline static CAntispamOUSupportClass* GetInstance(IN HINSTANCE hModule)
		{
			static PRLocker cs;
			PRAutoLocker _cs_(cs);
			CAntispamOUSupportClass*& This = g_pAntispamOUSupportClass;
			if ( !This )
			{
				This = new CAntispamOUSupportClass();
				if ( This && FAILED(This->Init(hModule)) )
				{
					delete This;
					This = NULL;
				}
			}
			return This;
		}
		inline static void ReleaseInstance()
		{
			if ( g_pAntispamOUSupportClass )
				delete g_pAntispamOUSupportClass;
			g_pAntispamOUSupportClass = NULL;
		}
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Init
		//! \brief			:	�������������
		//! \param          : IN HINSTANCE hModule
		//! \return			: HRESULT 
		HRESULT Init(IN HINSTANCE hModule);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetSettings
		//! \brief			:	���������� ������� ���������
		//! \return			: HRESULT 
		//! \param          : OUT AntispamPluginSettings_t* pAntispamPluginSettings
		HRESULT GetSettings( OUT AntispamPluginSettings_t* pAntispamPluginSettings );

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: SetSettings
		//! \brief			:	��������� ��������
		//! \return			: HRESULT 
		//! \param          : IN AntispamPluginSettings_t* pAntispamPluginSettings
		HRESULT SetSettings( IN AntispamPluginSettings_t* pAntispamPluginSettings );

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: SaveSettings
		//! \brief			:	��������� ��������� � ����
		//! \return			: HRESULT 
		HRESULT SaveSettings();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: LoadSettings
		//! \brief			:	������ ��������� �� �����
		//! \return			: HRESULT 
		HRESULT LoadSettings();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CheckPluginSettings
		//! \brief			:	��������� ������������ ��������. ����� �������� ������ ��������
		//! \return			: void
		bool CheckPluginSettings();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ShowPluginSettings
		//! \brief			:	���������� ������ ��������
		//! \return			: int
		int ShowPluginSettings(bool bAskOnCancel = false, bool bAdvansedSettings = true);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: GetFolderInfoList
		//! \brief			:	������ ������ ��������. ���� RecoursiveFolderInfo* == 0 - ������������ ������ ������� �����
		//! \return			: HRESULT 
		//! \param          : IN FolderInfo_t* pFolderInfo
		//! \param          : OUT FolderInfoList_t* pFolderInfoList
		HRESULT GetFolderInfoList( IN FolderInfo_t* pFolderInfo, OUT FolderInfoList_t* pFolderInfoList );

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CreateSubFolder
		//! \brief			:	�������� ����� ����� 
		//! \return			: HRESULT 
		//! \param          : IN FolderInfo_t* pFolderInfo
		//! \param          : IN OUT FolderInfo_t* pNewFolderInfo
		HRESULT CreateSubFolder( FolderInfo_t* pFolderInfo, FolderInfo_t* pNewFolderInfo );

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: TrainEx
		//! \brief			:	��������� �������� ��������� �� �������� ���������� (�����������)
		//!						���������� ����� ������
		//! \return			: HANDLE 
		//! \param          : IN AntispamPluginTrainSettings_t* pAntispamPluginTrainSettings
		//! \param          : IN TrainStatusCallback_t TrainStatusCallback
		//! \param          : IN void* _context - �������� ����������
		HANDLE TrainEx( 
			IN AntispamPluginTrainSettings_t* pAntispamPluginTrainSettings, 
			IN TrainStatusCallback_t TrainStatusCallback,
			IN void* _context
			);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: Train
		//! \brief			:	��������� �������� ��������� �� �������� ����������
		//! \return			: HRESULT 
		//! \param          : IN AntispamPluginTrainSettings_t* pAntispamPluginTrainSettings
		//! \param          : IN TrainStatusCallback_t TrainStatusCallback
		//! \param          : IN void* _context - �������� ����������
		HRESULT Train( 
			IN AntispamPluginTrainSettings_t* pAntispamPluginTrainSettings, 
			IN TrainStatusCallback_t TrainStatusCallback,
			IN void* _context
			);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: CompareEntryID
		//! \brief			:	���������� ��� EntryID
		//! \return			: bool 
		//! \param          : IN const EntryID_t* pEntry1
		//! \param          : IN const EntryID_t* pEntry2
		bool CompareEntryID( IN const EntryID_t* pEntry1, IN const EntryID_t* pEntry2);


		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ActionOnMessage
		//! \brief			:	���������� �������� ��� �������, �������� ������� ��������
		//!						����� ����������� pMessage ���������� ���������� - ��� ���� ������ ����������
		//! \return			: HRESULT 
		//! \param          : IN LPMESSAGE pMessage
		//! \param          : IN Action_t Action
		HRESULT ActionOnMessage( 
			IN LPMESSAGE pMessage,
			IN Action_t Action
			);
		
		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ProcessOnMessage
		//! \brief			:	���������� ���������� ��� ������������� �� ������
		//! \return			: HRESULT 
		//! \param          : IN LPMESSAGE pMessage
		//! \param          : IN Action_t Action
		HRESULT ProcessOnMessage( 
			IN LPMESSAGE pMessage,
			IN Action_t Action,
			OUT tDWORD* result
			);

		tERROR MassTrainingStart();
		tERROR MassTrainingFinish();

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: ScanNewMessages
		//! \brief			:	��������� ����� ���������, ������� ������ � �������� ������
		//! \return			: bool 
		bool ScanNewMessages();

		// ��� ��������� � ������� � ����� ��������
		struct TrainAsinch_t
		{
			CAntispamOUSupportClass* _this;
			AntispamPluginTrainSettings_t* pAntispamPluginTrainSettings;
			TrainStatusCallback_t TrainStatusCallback;
			void* _context;
		};

	private:
		AntispamPluginSettings_t* m_pAntispamPluginSettings;
		tBOOL m_bPluginHasSettings;
		cCriticalSection* m_lock; //!< ����������� ������ ��� ����������� ���������� m_pAntispamPluginSettings
		LPMAPISESSION	m_pMAPISession;
		std::string m_szProfileName; //!< ��� �������� �������� � ���� ������������ ��� �������� ��������
		struct MDB_t : public EntryID_t
		{
			LPMDB lpMDB;
			MDB_t() : EntryID_t(), lpMDB(0)
			{;};
			MDB_t(LPMAPISESSION session, EntryID_t& entry) : EntryID_t(entry), lpMDB(0)
			{
				HRESULT hr = S_OK;
				ULONG ulObjType = 0;
				if ( cb && session )
					hr = session->OpenEntry(
						cb,
						reinterpret_cast<LPENTRYID>(get_lpb()),
						&IID_IMsgStore,
						MAPI_BEST_ACCESS,
						&ulObjType,
						reinterpret_cast<LPUNKNOWN *>(&lpMDB)
						);
				if ( FAILED(hr) )
					lpMDB = NULL;
			}
			virtual ~MDB_t();
		};
		MDB_t*	m_pMDB;
		cVector<MDB_t*> m_pMDBs;
		HRESULT Train(
			LPMDB lpMDB, 
			LPMAPIFOLDER lpFolder, 
			bool bIsSpam, 
			TrainStatusCallback_t TrainStatusCallback,
			void* _context,
		    tUINT ulFolderNumber,
		    tUINT ulFolderCount
			);
		bool HasSubfolders(FolderInfo_t* pFolderInfo);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: MoveMessage
		//! \brief			:	���������� �������� ������ � ����� ��� �����
		//!						����� ����������� pMessage ���������� ���������� - ��� ���� ������ ����������
		//! \return			: HRESULT 
		//! \param          : LPMESSAGE pMessage
		HRESULT MoveMessage(LPMESSAGE pMessage, AntispamPluginRule_t* pRule);

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: RemoveMessage
		//! \brief			:	���������� ������ �� ����� ��� ����� � �������� �����
		//!						���� � �������� ����� �� ���������.
		//!						����� ����������� pMessage ���������� ���������� - ��� ���� ������ ����������
		//! \return			: HRESULT 
		//! \param          : LPMESSAGE pMessage
		HRESULT RemoveMessage(LPMESSAGE pMessage);

		CBackgroundScan* m_hBackgroundScan; //!< ����� �������� ������������ �������� �����
		hAS_TRAINSUPPORT m_pTrainSupport;

		///////////////////////////////////////////////////////////////////////////
		//! \fn				: InitNotifyWnd
		//! \brief			:	���������� ������������������ �������
		//! \return			: void 
		//! \param          : HINSTANCE hModule
		void InitNotifyWnd(HINSTANCE hModule);
		HWND m_hNotifyWnd;                  //!< ��������� ���� ��� ���������� ������������������ �������


		//////////////////////////////////////////////////////////////////////////
		//
		//	����� ������ � "����� �������"
		//
			///////////////////////////////////////////////////////////////////////////
			//! \fn				: IsMessageReRequest
			//! \brief			:	���������� TRUE, ���� ��������� �������� ������� �� Request
			//! \return			: bool 
			//! \param          : LPMESSAGE pMessage
			bool IsMessageReRequest( LPMESSAGE pMessage, bool bRemoveFound );

			HRESULT SendMessageRequestEx( LPMESSAGE pMessage, bool bIsThanks = false );
			
			///////////////////////////////////////////////////////////////////////////
			//! \fn				: SendMessageRequest
			//! \brief			:	�������� Request �� pMessage
			//! \return			: HRESULT 
			//! \param          : LPMESSAGE pMessage
			HRESULT SendMessageRequest( LPMESSAGE pMessage );

			///////////////////////////////////////////////////////////////////////////
			//! \fn				: SendMessageThanks
			//! \brief			:	�������� Thanks �� pMessage
			//! \return			: HRESULT 
			//! \param          : LPMESSAGE pMessage
			HRESULT SendMessageThanks( LPMESSAGE pMessage );

			///////////////////////////////////////////////////////////////////////////
			//! \fn				: RemoveMessages
			//! \brief			:	���������� ��� ��������� �� ����������� pMessage 
			//						� ������������ �����
			//! \return			: HRESULT 
			//! \param          : LPMESSAGE pMessage
			HRESULT RemoveMessages( LPMESSAGE pMessage );
		//
		//	����� ������ � "����� �������"
		//
		//////////////////////////////////////////////////////////////////////////
		
		HRESULT ReopenMDBs();
		HRESULT OpenEntryForFolder(IN FolderInfo_t* pFolderInfo, OUT LPMAPIFOLDER* ppFolder);
	};

}	//AntispamOUSupport

#endif//_ANTISPAMOUSUPPORTCLASS_H_