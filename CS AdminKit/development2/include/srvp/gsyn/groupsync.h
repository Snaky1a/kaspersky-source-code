/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	GSYN/GroupSync.h
 * \author	Andrew Kazachkov
 * \date	29.11.2002 10:53:33
 * \brief	������, ���������� �� ��������� ������������� ����� SettingsStorage,
 *        ������������ �� ������� �����������������, � ������� �����.
 * 
 */

#ifndef KLGSYN_GROUPSYNC_H
#define KLGSYN_GROUPSYNC_H

#include <vector>
#include <string>

#include <std/base/klbase.h>
#include <srvp/grp/groups.h>
#include <srvp/csp/klcsp.h>

namespace KLGSYN {

	//! ��������� �������� �������������
	enum GSYN_STATUS{
		//! ������������� ��� �� ��������
		GSYNS_SCHEDULED,
		//! ������������� ��� �� �����������
		GSYNS_RUNNING,
		//! ������������� ��������� �.�. ������� ����� ��������
		GSYNS_ELAPSED,
		//! ������������� ����������� ������� �� ���� ������
		GSYNS_FINISHED,
		//! ������������� �� ������ ��-�� ������
		GSYNS_FAILED
	};

	//! ��������� ������������� �� �������� �����
	enum GSYN_HOST_STATUS{
		//! ������������� ��� �� ��������
		GSYNH_SCHEDULED,
		//! ������������� ��� �� �����������
		GSYNH_RUNNING,
		//! ������������� ����������� �������
		GSYNH_FINISHED,
		//! ������������� �� ������ ��-�� ������
		GSYNH_FAILED
	};
	
	//! ����������� �������������
	enum GSYN_DIRECTION{
		GSYND_ONEWAY,
		GSYND_TWOWAY
	};

	//! ���������, ���������� ������������� ���������� ����������.
    typedef KLCSP::host_id_t host_id_t;

	/*! ���������, ���������� ������� ������ ������������� ��� ����������
		����������.
	*/
	typedef struct {
		//! ������������� �����
		host_id_t			idHost;
		//! ������� ������ �������������.
		GSYN_HOST_STATUS	status;
		//! ������������� ������� � ��������� ������� �������������.
		std::wstring		eventId;
		//! �������� ������� � ��������� ������� �������������.
		std::wstring		eventDesc;
		//! ��������� ������������������ ������.
		long				lastSyncVersion;
	} sync_host_status_t;

	
	//! ������������� �������������
	const wchar_t c_gsyn_id[]=L"gsynId";				//INT_T
	//! ������������� ���� � ����� SettingsStorage ��� ��������� �������������.
	const wchar_t c_gsyn_path[]=L"filePath";			//STRING_T
	//! ����������� ������������� (GSYN_DIRECTION)
	const wchar_t c_gsyn_direction[]=L"gsynDirection";	//INT_T
	//! ��������� ������������� (GSYN_STATUS)
	const wchar_t c_gsyn_status[]=L"gsynStatus";		//INT_T
	//! ����� �������� �������������
	const wchar_t c_gsyn_creation[]=L"creationTime";	//DATE_TIME_T
	//! ����� ����� �������� ���������� �������������
	const wchar_t c_gsyn_elapse[]=L"elapseTime";		//DATE_TIME_T
	//! ��� �������������
	const wchar_t c_gsyn_name[]=L"name";				//STRING_T
	//! ��������� �������������
	const wchar_t c_gsyn_result[]=L"result";			//STRING_T
	//!
	const wchar_t c_gsyn_cutoff_children[]=L"cutoff_children";//BOOL_T

	//! ������ ������, ����������� � �������������
	const wchar_t c_gsyn_hosts[]=KLCSP_ITERATOR_ARRAY;			//ARRAY_T
	//! ������������� ������
	const wchar_t c_gsyn_groupId[]=L"groupId";			//INT_T

	//! ��� �����
	const wchar_t c_gsyn_hostName[]=L"hostName";		//STRING_T
    //! NetBIOS-��� �����
    const wchar_t c_gsyn_winhostName[]=L"winhostName";		//STRING_T
    //! ������������ ��� �����
    const wchar_t c_gsyn_hostDisplayName[]=L"hostDisplayName";
	//! ��� ������
	const wchar_t c_gsyn_domainName[]=L"domainName";	//STRING_T
	//! ��������� ������������� (GSYN_HOST_STATUS)
	const wchar_t c_gsyn_hostStatus[]=L"hostStatus";	//INT_T
	//! ������������� ������� � ��������� ������� �������������.
	const wchar_t c_gsyn_eventName[]=L"eventName";		//STRING_T
	//! �������� ������� � ��������� ������� �������������.
	const wchar_t c_gsyn_eventDesc[]=L"eventDesc";		//STRING_T
	//! ��������� ������������������ ������.
	const wchar_t c_gsyn_version[]=L"version";			//LONG_T	
    //! ����� ��������� �������������
    const wchar_t c_gsyn_lastsync[]=L"last_sync";			//DATE_TIME_T	    
    
    //! Time when host required sync for the last time ( since KLADMSRV_SV70 )
    const wchar_t c_gsyn_last_required[]=L"last_sync_req";			//DATE_TIME_T	   
    //! ��� ������
    const wchar_t c_gsyn_errorcode[]=L"error_code";//INT_T
    
//! �������� ������, �� ������� �������� �������������
    //! ���������� ������ ����������� ��� �������������
    const wchar_t c_gsyn_cnt_FullCount[]=L"gsyn_cnt_FullCount";    
    //! ���������� ������, ����������� � ������������� (�.�. ������������� �� ��� ��� �� ������ ��� ������, �� �� �������)
    const wchar_t c_gsyn_cnt_HostsToSyncronize[]=L"gsyn_cnt_HostsToSyncronize";
    //! ���������� ������ � ��������� GSYNH_SCHEDULED
    const wchar_t c_gsyn_cnt_Scheduled[]=L"gsyn_cnt_Scheduled";
    //! ���������� ������ � ��������� GSYNH_RUNNING
    const wchar_t c_gsyn_cnt_Running[]=L"gsyn_cnt_Running";
    //! ���������� ������ � ��������� GSYNH_FINISHED
    const wchar_t c_gsyn_cnt_Finished[]=L"gsyn_cnt_Finished";
    //! ���������� ������ � ��������� GSYNH_FAILED
    const wchar_t c_gsyn_cnt_Failed[]=L"gsyn_cnt_Failed";

/*!
	\brief ��������� ��������� ���������������� ��������� ������������� �����
	������� SettingsStorage,  ������������ �� ������� ����������������� �
	������� ��������� �����.
	������ ��������� ���������� ���� SettingsStorage, ��������� �������������
	��� ������ �����������.  ����� ������ ��������� ������������� �������
	������ ������������� ����� ��������� ������ � ���������� ������, ���������
	� ������� ���� � ������ �������������.
	������������� ����� ����������� ��� ��� ���������� ����� �������
	����������������� (��� ���� �����������, ���������� � ������), ��� � ���
	���������� ������ �����������. ������ � ���� �� ����� ����� ���������������
	��������� ������� �������������.
	���������������� ����� ����� ������.  ������������� ���������� ����� �����
	��������� ������ �����. ���������� ����������� ������ ������� ������
	������������������� ����� �� ��������� ���� (������ ��������� ��������
	�������������).
*/


    typedef KLCSP::ForwardIterator ForwardIterator;

	typedef KLCSP::ChunkAccessor ChunkAccessor;
		
    class GroupSync : public KLSTD::KLBaseQI
	{
    public:
    /*!
      \brief ����� ��������� ��� ��������� ����� SettingsStorage ���������
             ��������� �������������.

        \param wstrSyncObjPath [in]	������������� ���� � ���������� �����
								SettingsStorage ��� ��������� �������������.
								���������� �������������. 
		\param nDirection [in]	����������� �������������
        \param groupId [in]	������������� ������, ��� ������� ���������
							�������������.
		\param lElapse [in]	������������ ���� � ��������, �� ���������
							�������� ������������� ��������� �����������, ����
							���� ��� ������ �� �� ���� ������.

        \return long ������������� ��������� �������������.
						���������� �������������.
       
    */
		virtual long AddSyncObjG(
					const wchar_t*		szwName,
					const wchar_t*		szwSyncObjPath,
					GSYN_DIRECTION		nDirection,
					long				lGroup,
					long				lElapse,
					bool				bCutoffChildren=false,
                    bool                bOwnTransaction=true) = 0;

    /*!
      \brief ����� ��������� ��� ��������� ����� SettingsStorage ���������
             ��������� �������������.

        \param wstrSyncObjPath [in]	������������� ���� � ���������� �����
						SettingsStorage ��� ��������� �������������. ����������
						�������������.
		\param nDirection [in]	����������� �������������
        \param pHosts [in]	������ ��������������� ������ ��� ������� 
							��������� �������������.
		\param nHosts [in]	����� ������� ��������������� ������
		\param lElapse [in]	������������ ���� � ��������, �� ���������
							�������� ������������� ��������� �����������, ����
							���� ��� ������ �� �� ���� ������.

        \return long ������������� ��������� �������������. 
					���������� �������������.
       
    */

		virtual long AddSyncObjH(
					const wchar_t*		szwName,
					const wchar_t*		szwSyncObjPath,
					GSYN_DIRECTION		nDirection,
					host_id_t*			pHosts,
					long				nHosts,
					long				lElapse,
                    bool                bOwnTransaction=true) = 0;

	/*!
		\brief	���������� ���������� � �������������.

		\param	lSync [in] ������������� �������������.
		\param	pFields [in] ������ ��� ��������� ���������. ����� ����
				������� ��������� ��������:
					c_gsyn_path,
					c_gsyn_direction,
					c_gsyn_status,
					c_gsyn_creation,
					c_gsyn_elapse,
					c_gsyn_name,
					c_gsyn_result,
					c_gsyn_groupId,// ��� �������������, ��������� AddSyncObjG
					c_gsyn_hosts // ��� �������������, ��������� AddSyncObjH
				������ �������� ������������.
		\param	nFields [in] ���������� ��������� � ������� pFields
		\param	ppInfo [out] ��������� �� ����������, � ������� �����
				������� ��������� �� ��������� Params, ���������� ��������
				��������.
		\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
				�������.
	*/
		virtual void GetSyncInfo(
					long			lSync,
					const wchar_t**	pFields,
					int				nFields,
					KLPAR::Params**	ppInfo)=0;

		/*!
		\brief	������� ������ ������������
		\param	lSync -- ������������� �������������.
        \param  bOwnTransaction - ���� true, ����� ������� ����� ����������,
                ����� �������� ����� ������������ � ������ ������� ����������.
		\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
			�������.
		*/
		virtual void RemoveSyncObj(long	lSync, bool bOwnTransaction=true) = 0;

		/*!
			\brief	���������� ���������� � ���� ������, ����������� �
					�������������.
			\param	lSync [in] ������������� �������������.
			\param	pFields [in] ������ ��� ��������� ���������. ����� ����
					������� ��������� ��������:
						c_gsyn_hostName,
						c_gsyn_domainName,
						c_gsyn_hostStatus,
						c_gsyn_eventName,
						c_gsyn_eventDesc,
						c_gsyn_version,
                        c_gsyn_lastsync,
                        c_gsyn_last_required.
					������ �������� ������������.
			\param	nFields [in] ���������� ��������� � ������� pFields
			\param	lTimeout [in] ����� ����� ���������,�
			\param	ppIterator [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ForwardIterator.

			\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
				�������.
		*/
        virtual void GetSyncHostsInfo(
					long				lSync, 
					const wchar_t**		pFields,
					long				nFields,
					long				lTimeout,
					ForwardIterator**	ppIterator)  = 0;

		/*!
			\brief	���� ����� ��������������� ��������� �������.
			\param	lSync [in] ������������� �������������.
			\param	szwFilter [in] ������ [�������� ��� � RFC2254]. � �������
					����� ���� ��������� ��������� ��������:
							c_gsyn_hostName,
							c_gsyn_domainName,
							c_gsyn_hostStatus,
							c_gsyn_eventName,
							c_gsyn_eventDesc,
							c_gsyn_version,
                            c_gsyn_lastsync,
                            c_gsyn_last_required.
			\param	pFields [in] ������ ��� ��������� ���������. ����� ����
					������� ��������� ��������:
							c_gsyn_hostName,
							c_gsyn_domainName,
							c_gsyn_hostStatus,
							c_gsyn_eventName,
							c_gsyn_eventDesc,
							c_gsyn_version,
                            c_gsyn_lastsync,
                            c_gsyn_last_required
					������ �������� ������������.
			\param	nFields [in] ���������� ��������� � ������� pFields
			\param	lTimeout [in] ����� ����� ���������, �
			\param	ppIterator [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ForwardIterator.

			\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
				�������.
		*/
		virtual void FindHosts(
					long				lSync, 
					const wchar_t*		szwFilter,
					const wchar_t**		pFields,
					long				nFields,
					long				lTimeout,
					ForwardIterator**	ppIterator)  = 0;

        virtual AVP_qword IncrementVersion(
                            long            lSync,
                            const wchar_t*  szwSyncObjPath,
                            long            lWaitTimeout,
                            bool            bOwnTransaction=true) = 0;

        virtual void ForceGroupSync(
                            long    idSync,
                            bool    bOwnTransaction=true) = 0;

		/*!
			\brief	���������� ���������� � ���� ������, ����������� �
					�������������.
			\param	lSync [in] ������������� �������������.
			\param	vect_fields [in] ������ ��� ��������� ���������. ����� ����
					������� ��������� ��������:
						c_gsyn_hostName,
						c_gsyn_domainName,
						c_gsyn_hostStatus,
						c_gsyn_eventName,
						c_gsyn_eventDesc,
						c_gsyn_version.
					������ �������� ������������.
			\param	vect_fields_to_order [in] ������ ����� ��� ����������.
			\param	lTimeout [in] ����� ����� ���������,�
			\param	ppAccessor [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ChunkAccessor.

			\return long - ����� ��������� �������.

			\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
				�������.
		*/
        virtual long GetSyncHostsInfo2(
					long				lSync, 
					const std::vector<std::wstring>& vect_fields,
					const std::vector<KLCSP::field_order_t>& vect_fields_to_order,
					long				lTimeout,
					ChunkAccessor**		ppAccessor)  = 0;

		/*!
			\brief	���� ����� ��������������� ��������� �������.
			\param	lSync [in] ������������� �������������.
			\param	szwFilter [in] ������ [�������� ��� � RFC2254]. � �������
					����� ���� ��������� ��������� ��������:
							c_gsyn_hostName,
							c_gsyn_domainName,
							c_gsyn_hostStatus,
							c_gsyn_eventName,
							c_gsyn_eventDesc,
							c_gsyn_version.
			\param	vect_fields [in] ������ ��� ��������� ���������. ����� ����
					������� ��������� ��������:
						c_gsyn_hostName,
                        c_gsyn_hostDisplayName,
						c_gsyn_domainName,
						c_gsyn_hostStatus,
						c_gsyn_eventName,
						c_gsyn_eventDesc,
						c_gsyn_version.
					������ �������� ������������.
			\param	vect_fields_to_order [in] ������ ����� ��� ����������.
			\param	lTimeout [in] ����� ����� ���������, �
			\param	ppAccessor [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ChunkAccessor.

			\return long - ����� ��������� �������.

			\except	STDE_NOTFOUND ������������� � �������� ��������������� ��
				�������.
		*/
		virtual long FindHosts2(
					long				lSync, 
					const wchar_t*		szwFilter,
					const std::vector<std::wstring>& vect_fields,
					const std::vector<KLCSP::field_order_t>& vect_fields_to_order,
					long				lTimeout,
					ChunkAccessor**		ppAccessor)  = 0;


		virtual long AddSyncObjG2(
                    long				lGroup,
					const wchar_t*		szwSyncObjLocation,
                    const wchar_t*		szwProductName,
                    const wchar_t*		szwProductVersion,                    
                    const wchar_t*		szwGsyncName = NULL,
                    long				lElapse = 0,
                    bool                bOwnTransaction=true,
                    bool				bCutoffChildren=false,                    
					GSYN_DIRECTION		nDirection = GSYND_ONEWAY) = 0;

		virtual long AddSyncObjH2(
					host_id_t*			pHosts,
					size_t              nHosts,
                    const wchar_t*		szwSyncObjLocation,
                    const wchar_t*		szwProductName,
                    const wchar_t*		szwProductVersion,
                    const wchar_t*		szwGsyncName = NULL,
                    long				lElapse = 0,                    
                    bool                bOwnTransaction=true,                    
					GSYN_DIRECTION		nDirection = GSYND_ONEWAY) = 0;
        

        /*!
          \brief	Allows to change hosts list for global syn-tion.

          \param	lGsynId [in]
          \param	pHosts [in]
          \param	nHosts [in]
          \param	bOwnTransaction [in]
        */
        virtual void UpdateHostsSyncObjH(
                    long                lGsynId,
                    host_id_t*          pHosts,
                    size_t              nHosts,
                    bool                bOwnTransaction=true) = 0;
    };
};

/*!
  \brief ������� ������ ������ KLGSYN::GroupSync

    \param ppGS       [out] ��������� �� ����������, � ������� ����� �������
						��������� �� ��������� KLGSYN::GroupSync

*/

KLCSSRVP_DECL void KLGSYN_CreateGroupSync(
                        const wchar_t*          szwAddress,
                        KLGSYN::GroupSync**     pp,
                        const unsigned short*   pPorts = NULL,
                        bool                    bUseSsl = true);

void KLGSYN_CreateServerGroupSync(KLGSYN::GroupSync**     pp);


#endif // KLGSYN_GROUPSYNC_H

// Local Variables:
// mode: C++
// End:
