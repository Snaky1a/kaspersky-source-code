/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	AgentBusinessLogic.h
 * \author	Andrew Kazachkov
 * \date	06.02.2003 13:36:41
 * \brief	
 * 
 */

#ifndef __AGENTBUSINESSLOGIC_H__bR49iSQI7uKcEdBS3DcmQ3
#define __AGENTBUSINESSLOGIC_H__bR49iSQI7uKcEdBS3DcmQ3

#include <kca/prcp/componentproxy.h>

#define KLBLAG_ERROR_BUSY       L"KLBLAG_ERROR_BUSY"
#define KLBLAG_ERROR_INFO		L"KLBLAG_ERROR_INFO"
#define KLBLAG_ERROR_MODULE		L"KLBLAG_ERROR_MODULE";
#define KLBLAG_ERROR_CODE		L"KLBLAG_ERROR_CODE";
#define KLBLAG_ERROR_SUBCODE	L"KLBLAG_ERROR_SUBCODE";
#define KLBLAG_ERROR_MSG		L"KLBLAG_ERROR_MSG";
#define KLBLAG_ERROR_FNAME		L"KLBLAG_ERROR_FNAME";
#define KLBLAG_ERROR_LNUMBER	L"KLBLAG_ERROR_LNUMBER";

#define KLBLAG_ERROR_LOCDATA    L"KLBLAG_ERROR_LOCDATA";    //PARAMS_T
#define KLBLAG_ERROR_FORMATID   L"KLBLAG_ERROR_FORMATID";   //INT_T
#define KLBLAG_ERROR_FORMAT     L"KLBLAG_ERROR_FORMAT";     //STRING_T
#define KLBLAG_ERROR_FORMATARGS L"KLBLAG_ERROR_FORMATARGS"; //ARRAY_T|STRING_T

namespace KLBLAG
{
    typedef std::vector<KLSTD::KLAdapt<KLSTD::CAutoPtr<KLPRCP::ComponentProxy> > > proxies_t;

	/*!
		\brief	��� ���������� ������-������. ������ ���������� ����������
				���������� � ��������� SS_PRODINFO � ���������� ��������
                (������� ��������������� �������� KLPRSS_RegisterProduct).
    */
    const wchar_t c_szwBusinessLogicName[]=L"KLBLAG_BL_COMPONENT";//STRING_T

	/*!
		\brief	��� ���������� ������������, ����� ������� ������� �����������
                ������ ����� �� ��������� �����.
                ����� ����� ����������� ������ ����������������, �������
                ���������� ������ ����������� � ��������� SS_PRODINFO �
                ���������� �������� (������� ��������������� ��������
                KLPRSS_RegisterProduct). 
	*/
    const wchar_t c_szwStartTasksThroushBL[]=L"KLBLAG_USE_BL";//STRING_T

	/*!
		\brief	��������������� ������������ ���������� ������ ��� ��
                ������ ���������� ������������ � ������
                KLPRSS_COMPONENT_PRODUCT (��������� SS_PRODINFO). �������
                ��������������� �������� KLPRSS_RegisterProduct.
    */
    const wchar_t c_szwBusinessLogicProxyLocation[]=L"KLBLAG_BL_PROXY_LOCATION";//STRING_T

	/*!
		\brief	������-������ ����� �������� � ����� ���������� ���������
                ������ � ������� �������, ��� �������� ������������� � ������
                KLPRSS_COMPONENT_PRODUCT (��������� SS_PRODINFO) � ����������
                c_szwEventReady, �������� ���������� -- ��� �������.
                ���� ���������� �� ����������, �� ������-������ ���������
                ������� ��������� ������, ���� � � ����� ��������� RUNNING.
	*/
    const wchar_t c_szwEventReady[]=L"KLBLAG_EVENT_READY";//STRING_T


/*!
    ���������� ������� ������� �������� ����� ��������.
*/
const wchar_t c_szwEv_OnAppStart[]=L"KLBLAG_EV_ONAPPSTART";

	
	//! ��������� ���������� ������
const wchar_t c_szwStartScheduledTask[]=L"KLBLAG_START_SCHEDULED_TASK";	
	/*! ��������� ����� ��������� ���������.			
			c_szwServerProduct
			c_szwServerVersion
			c_szwServerComponent
			c_szwServerInstance
			c_szwClientProduct
			c_szwClientVersion
			c_szwClientComponent
			c_szwClientInstance
			c_szwServerTaskName
			c_szwServerTaskParams
			c_szwServerTaskTimeout
			c_szwUser
			c_szwDomain
			c_szwPassword
	*/

/*!
	���������� ���������� ������ ����� ��������� ���������:
		- � ������ ������
			c_szwServerProduct		- ��� �������� 
			c_szwServerVersion		- ������ �������� 
			c_szwServerComponent	- ��� ����������
			c_szwServerInstance		- ��� ���������� ����������, �� ������� ���� �������� ������
            c_szwServerTaskName     - ��� ���� ���������� ������
			�_szwTaskId				- ������������� ���������� ������
		- � ������ �������
			c_szwErrorInfo			- 
				c_szwErrorModule	- ��� ������, � ������� ��������� ������
				c_szwErrorCode		- ��� ������
				c_szwErrorMsg		- ��������� �� ������
				c_szwErrorFileName	- ��� �����, � ������� �������� ������
				c_szwErrorLineNumber	- ������, �� ������� ��������� ������
*/
	
		//!���������� � ����������-�������
const wchar_t c_szwServerProduct[]=L"KLBLAG_SERVER_PRODUCT";//< ��� ��������
const wchar_t c_szwServerVersion[]=L"KLBLAG_SERVER_VERSION";//< ������ ��������
const wchar_t c_szwServerComponent[]=L"KLBLAG_SERVER_COMPONENT";//< ��� ����������
const wchar_t c_szwServerInstance[]=L"KLBLAG_SERVER_INSTANCE";//< ������������� �����

		//!���������� � ����������-�������
const wchar_t c_szwClientProduct[]=L"KLBLAG_CLIENT_PRODUCT";//< ��� ��������
const wchar_t c_szwClientVersion[]=L"KLBLAG_CLIENT_VERSION";//< ������ ��������
const wchar_t c_szwClientComponent[]=L"KLBLAG_CLIENT_COMPONENT";//< ��� ����������
const wchar_t c_szwClientInstance[]=L"KLBLAG_CLIENT_INSTANCE";//< ������������� �����

		//!���������� � ������
const wchar_t c_szwServerTaskName[]=L"KLBLAG_SERVER_TASKNAME";//< ��� ������
const wchar_t c_szwServerTaskParams[]=L"KLBLAG_SERVER_TASKPARAMS";//< �������� ������
const wchar_t c_szwServerTaskTimeout[]=L"KLBLAG_SERVER_TASKTIMEOUT";//< ������� ������
const wchar_t c_szwTaskId[]=L"KLBLAG_TASK_ID";			//< INT_T 

		//!���������� � ������������, ��� ������ ������ �������� ������
const wchar_t c_szwUser[]=L"KLBLAG_TASK_USER";			//< STRING_T
const wchar_t c_szwDomain[]=L"KLBLAG_TASK_DOMAIN";		//< STRING_T
const wchar_t c_szwPassword[]=L"KLBLAG_TASK_PASSWORD";	//< STRING_T

		//!���������� �� ������
const wchar_t c_szwErrorInfo[]=KLBLAG_ERROR_INFO;
const wchar_t c_szwErrorModule[]=KLBLAG_ERROR_MODULE;
const wchar_t c_szwErrorCode[]=KLBLAG_ERROR_CODE;
const wchar_t c_szwErrorMsg[]=KLBLAG_ERROR_MSG;
const wchar_t c_szwErrorFileName[]=KLBLAG_ERROR_FNAME;
const wchar_t c_szwErrorLineNumber[]=KLBLAG_ERROR_LNUMBER;

} // namespace KLBLAG

#endif //__AGENTBUSINESSLOGIC_H__bR49iSQI7uKcEdBS3DcmQ3

// Local Variables:
// mode: C++
// End:
