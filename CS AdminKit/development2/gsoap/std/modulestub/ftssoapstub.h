/*!
 * (C) "Kaspersky Lab"
 *
 * \file ftssoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klft_GetNextFileChunkStub(  struct soap *soap, 
						xsd__wstring	remoteClientName,
						xsd__wstring	fileName,
						xsd__wstring	fileId,
						xsd__unsignedLong	startFilePos,
						xsd__unsignedLong	neededSize,
						xsd__boolean		useUpdaterFolder,	
						xsd__boolean		forUpdateAgent,
						struct klft_GetNextFileChunkOptions *options,
						struct klft_GetNextFileChunkResponse
							&r );

int klft_GetServerFilesListStub(  struct soap *soap, 
						xsd__wstring clientName,
						struct klft_GetServerFilesListResponse
							&r );

int klft_GetUpdaterFolderFileInfoStub(  struct soap *soap, 
						xsd__wstring	fileName,
						struct klft_GetUpdaterFolderFileInfoOptions *options,
						struct klft_GetUpdaterFolderFileInfoResponse
							&r );

int klft_GetFullFileInfoStub(  struct soap *soap, 
						xsd__wstring	fileId,						
						struct klft_GetFullFileInfoResponse
							&r );

int klft_GetHostUpdateAgentInfoStub(  struct soap *soap, 
						xsd__wstring	hostId,
						struct klft_GetHostUpdateAgentInfoResponse
							&r );

int klft_SendToClientFullSyncArchiveStub(  struct soap *soap, 
						xsd__wstring	remoteClientName,
						xsd__wstring	syncFolderFileId,
						xsd__boolean	fileNamesHashed,
						struct SOAPFilesInfoList *filesList,
						struct SOAPSyncFolderOptions *syncFolderOptions,
						struct klft_SendToClientFullSyncArchiveResponse
							&r );

int klfts_RegisterUpdateAgentStub(  struct soap *soap, 
						klfts_update_agent_info			updateAgentInfo,
						xsd__boolean					checkExisting,
						struct klfts_RegisterUpdateAgentResponse
						&r);

int klfts_ModifyUpdateAgentStub(  struct soap *soap, 
						klfts_update_agent_info			updateAgentInfo,
						struct klfts_ModifyUpdateAgentResponse
						&r);

int klfts_UnregisterUpdateAgentStub(  struct soap *soap, 
						xsd__wstring					strAgentHostId,
						struct klfts_UnregisterUpdateAgentResponse
						&r);

int klfts_GetDefaultUpdateAgentRegistrationInfoStub(  struct soap *soap, 
						int								nGroupId,
						struct klfts_GetDefaultUpdateAgentRegistrationInfoResponse
						&r);

int klfts_GetUpdateAgentsForGroupStub(  struct soap *soap, 
						int								nGroupId,
						struct klfts_GetUpdateAgentsForGroupResponse
						&r);

int klfts_GetUpdateAgentInfoStub(  struct soap *soap, 
						xsd__wstring					strAgentHostId,
						struct klfts_GetUpdateAgentInfoResponse
						&r);

int klfts_UseUAForSyncFolderStub(  struct soap *soap, 
						xsd__wstring			strAgentHostId,
						xsd__wstring			strSyncFolderName,
						xsd__boolean			bUse,
						struct klfts_UseUAForSyncFolderResponse
						&r);

int klfts_GetUseUAForSyncFolderStub(  struct soap *soap, 
						xsd__wstring			strAgentHostId,
						xsd__wstring			strSyncFolderName,						
						struct klfts_GetUseUAForSyncFolderResponse
						&r);

namespace KLFTS
{

	struct KLSTRT::SOAPStubFunc fts_funcs_ptrs[15]=
	{
		{ L"klft_GetNextFileChunk",		 (void*)klft_GetNextFileChunkStub },
		{ L"klft_GetServerFilesList",		 (void*)klft_GetServerFilesListStub },
		{ L"klft_GetUpdaterFolderFileInfo",		 (void*)klft_GetUpdaterFolderFileInfoStub },
		{ L"klft_GetFullFileInfo",		 (void*)klft_GetFullFileInfoStub },
		{ L"klft_GetHostUpdateAgentInfo",		 (void*)klft_GetHostUpdateAgentInfoStub },
		{ L"klft_SendToClientFullSyncArchive",		 (void*)klft_SendToClientFullSyncArchiveStub },
		{ L"klfts_RegisterUpdateAgent",		 (void*)klfts_RegisterUpdateAgentStub },
		{ L"klfts_ModifyUpdateAgent",		 (void*)klfts_ModifyUpdateAgentStub },
		{ L"klfts_UnregisterUpdateAgent",		 (void*)klfts_UnregisterUpdateAgentStub },
		{ L"klfts_GetDefaultUpdateAgentRegistrationInfo",		 (void*)klfts_GetDefaultUpdateAgentRegistrationInfoStub },
		{ L"klfts_GetUpdateAgentsForGroup",		 (void*)klfts_GetUpdateAgentsForGroupStub },
		{ L"klfts_GetUpdateAgentInfo",		 (void*)klfts_GetUpdateAgentInfoStub },
		{ L"klfts_UseUAForSyncFolder",		 (void*)klfts_UseUAForSyncFolderStub },
		{ L"klfts_GetUseUAForSyncFolder",		 (void*)klfts_GetUseUAForSyncFolderStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( fts_funcs_ptrs, (sizeof(fts_funcs_ptrs)/sizeof(fts_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( fts_funcs_ptrs, (sizeof(fts_funcs_ptrs)/sizeof(fts_funcs_ptrs[0])) );
	}

} // end namespace KLFTS
