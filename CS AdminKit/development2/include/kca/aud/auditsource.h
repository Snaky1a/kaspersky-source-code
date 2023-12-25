/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file auditsource.h
 * \author ����� �����������
 * \date 2005
 * \brief ������� ��������� ������ ����������
 * 
 */

#ifndef KLAUD_AUDITSOURCE_H
#define KLAUD_AUDITSOURCE_H

#include <string>

#include <std/base/kldefs.h>
#include <std/base/klbase.h>
#include <std/thr/sync.h>

#include <transport/wat/common.h>

namespace KLAUD
{
	/*
		\brief ��� ��������������� �������
	*/
	enum AuditObjectType
	{
		AuditObjectTask,
		AuditObjectGroupTask,
		AuditObjectGlobalTask,
		AuditObjectPolicy,			
		AuditObjectProduct,
		AuditObjectServer,
		AuditObjectHost,
		AuditObjectAdministrationGroup,
		AuditObjectIPDiapason,
		AuditObjectReport,
		AuditObjectNetworkLst,
		AuditObjectSecurityPolicy
	};

	enum ActionType
	{
		ActionConnect,			// ����������� � ������� �����������������
		ActionAdded,			// ���������� ������� ( ������, ��������, ����� � ������ � �.�. )
		ActionDeleted,			// �������� ������� ( -//- )			
		ActionModified,			// ����������� ������� ������� ( -//- )
		ActionRun,				// ������ ������ ��� ����������
		ActionStop,				// ��������� ������ ��� ����������
		ActionSuspend,			// ������������ ���������� ������ ��� ������ ����������
		ActionResume,			// ������������� ���������� ������ ��� ������ ����������
		ActionHostAdded,		// ���������� ����� � ������ �����������������
		ActionHostDeleted,		// �������� ����� �� ������ �����������������
		ActionGroupAdded, 		// ���������� ������ � ������ �����������������
		ActionGroupDeleted,		// �������� ������ �� ������ �����������������
		ActionNetworkListTask,	// ���������� ������ ��� �������� �������� ������
		ActionNetworkListHostTask	// ���������� ������ ��� ���� �������� �������� ������ ���������� �����
	};

	/*
			\brief Callback ����� ��� ��������� �����������
	*/
	class ObjectLocalization : public KLSTD::KLBaseQI
	{
	public:
		virtual std::wstring LocalizeProductName( const std::wstring &productName ) = 0;
	};



	class AuditSource : public KLSTD::KLBase
	{
	public:		

		/*
			\brief ���������� ������� �� ����� ��� ������� ���� ��������				
			
		*/
		virtual bool IsAuditActive( AuditObjectType objectType ) = 0;

		/*
			\brief ������� ����������� �� ������������ ��������
				������ ������� ��������� ������� ������
				
			���������� � ������� ������������ ������� ����� �� ThreadStore � ������ 
			  KLWAT_SEC_CONTEXT. ���� ���������� � ������������� �����������, �� ������� 
			  �� �����������

		*/
		virtual void NotifyAction( AuditObjectType objectType, ActionType actionType,
			const std::wstring &objectName, 
			const std::wstring param1 =	L"", const std::wstring param2 = L"" ) = 0;

		/*
			\brief ������� ����������� �� ������������ ��������
				������ ������� ��������� ������� ������
				
			���������� � ������� ������������ ������� ����� �� ThreadStore � ������ 
			  KLWAT_SEC_CONTEXT. ���� ���������� � ������������� �����������, �� ������� 
			  �� �����������

		*/
		virtual void NotifyAction( AuditObjectType objectType, ActionType actionType,
			const int &objectNameLocId, const std::wstring &defObjectName, 
			const int param1LocId =	(-1), const std::wstring defParam1 =	L"",
			const int param2LocId = (-1), const std::wstring defParam2 =	L"" ) = 0;

		/*
			\brief ������� ����������� �� ����������� ������ ������������
				������ ������� ��������� ������� ������
		*/
		virtual void NotifyUserConnectAction( struct soap* soap ) = 0;

		/*
			\brief ������� ����������� �� ������������ ��������
				������ ������� ��������� ������� ������
		*/
		virtual void NotifyAction( KLWAT::ClientContext *pClientContext, AuditObjectType objectType, ActionType actionType,
			const std::wstring &objectName, 
			const std::wstring param1 =	L"", const std::wstring param2 = L"" ) = 0;

		/*
			\brief ������� ����������� �� ��������� ������ SetingsStorage
		*/
		virtual void NotifySSChanged( 
			const std::wstring &szwProduct, 
			const std::wstring &szwVersion,
            const std::wstring &szwSection  ) = 0;

		/*
			\brief ������������� callback ����� ��� �����������

			\param pLoc [in] ��������� �� �����
		*/
		virtual void SetLocalization( ObjectLocalization *pLoc ) = 0;
	};

	/*
		\brief ������� ��������� �������� ���������� ���������� ������� ������
		�� ������� ������. ������������ ��� ���������� ��������� �������� 
	*/
	KLCSKCA_DECL void StopThreadAudit();
	KLCSKCA_DECL void StartThreadAudit();

	//\brief ����� ��������������� ���������/���������� ������ ��� �������� ������
	class AuditThreadAutoStopper
	{
	public:
		AuditThreadAutoStopper()
		{
			StopThreadAudit();
		}

		~AuditThreadAutoStopper()
		{
			StartThreadAudit();
		}
	};


} // end namespace KLAUD

//!\brief ��������������� �������
#define KLAUD_NOTIFY_SERVER_CONNECT(soap) KLAUD_GetAuditSource()->NotifyUserConnectAction( soap );
//#define KLAUD_NOTIFY_SERVER_CONNECT() KLAUD_GetAuditSource()->NotifyAction(\
//	KLAUD::AuditObjectServer, KLAUD::ActionConnect, L"" );

#define KLAUD_NOTIFY_TASK_MODIFIED( action, taskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectTask, action, taskName, product, version );\
}

#define KLAUD_NOTIFY_GROUPTASK_MODIFIED( action, groupTaskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectGroupTask, action, groupTaskName, product, version );\
}

#define KLAUD_NOTIFY_GLOBALTASK_MODIFIED( action, globalTaskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectGlobalTask, action, globalTaskName, product, version );\
}

#define KLAUD_NOTIFY_POLICY_MODIFIED( action, policyName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectPolicy, action, policyName, product, version );\
}

#define KLAUD_NOTIFY_POLICY_STATE_CHANGED( action, policyName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectPolicy, action, policyName, product, version );\
}

#define KLAUD_NOTIFY_PRODUCT_MODIFIED( product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectProduct, KLAUD::ActionModified, L"", product, version );\
}

#define KLAUD_NOTIFY_HOST_MODIFIED( action, hostName )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectHost, action, hostName );\
}

#define KLAUD_NOTIFY_SERVER_MODIFIED()\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectServer, KLAUD::ActionModified, L"" );\
}

#define KLAUD_NOTIFY_TASK_STATE_CHANGED( action, taskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectTask, action, taskName, product, version );\
}

#define KLAUD_NOTIFY_GROUPTASK_STATE_CHANGED( action, groupTaskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectGroupTask, action, groupTaskName, product, version );\
}

#define KLAUD_NOTIFY_GLOBALTASK_STATE_CHANGED( action, globalTaskName, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectGlobalTask, action, globalTaskName, product, version );\
}

#define KLAUD_NOTIFY_PRODUCT_STATE_CHANGED( action, product, version )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectProduct, action, product, version );\
}

#define KLAUD_NOTIFY_ADMGROUP_CHANGED( groupName, action, hostOrGroupName )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectAdministrationGroup, action, groupName, hostOrGroupName );\
}

#define KLAUD_NOTIFY_IPDIAPASON_CHANGED( diapasonName, action )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectIPDiapason, action, diapasonName );\
}

#define KLAUD_NOTIFY_REPORT_CHANGED( reportOrStencilName, action )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectReport, action, reportOrStencilName );\
}

#define KLAUD_NOTIFY_NETWORKLIST_ADD_TASK( networkListLocId, networkListName, taskNameLocId, taskName, hostName )\
{\
	KLAUD_GetAuditSource()->NotifyAction	(\
		KLAUD::AuditObjectNetworkLst, KLAUD::ActionRun, networkListLocId, networkListName, taskNameLocId, taskName, (-1), hostName );\
}

#define KLAUD_NOTIFY_SPL_CHANGED( szwGroupName )\
{\
	KLAUD_GetAuditSource()->NotifyAction(\
		KLAUD::AuditObjectSecurityPolicy, KLAUD::ActionModified, szwGroupName );\
}

#define KLAUD_NOTIFY_SS_CHANGED( szwProduct, szwVersion, szwSection )\
{\
	KLAUD_GetAuditSource()->NotifySSChanged(\
		szwProduct, szwVersion, szwSection );\
}


KLCSKCA_DECL KLAUD::AuditSource *KLAUD_GetAuditSource();

/*
	\brief ������� ������������/��������������� ����������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSKCA_DECL, KLAUD );

#endif // KLAUD_AUDITSOURCE_H
