/*!
 * (C) "Kaspersky Lab"
 *
 * \file ftsoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klft_InitiateFileUploadStub(  struct soap *soap, 
						xsd__wstring	fileName,
						xsd__wstring	fileId,
						xsd__wstring	description,
						xsd__unsignedLong	dirFlag,
						xsd__unsignedLong	fullFileSize,						
						xsd__wstring	serverComponent,
						xsd__wstring	remoteClientName,
						xsd__unsignedLong	uploadDelay,
						xsd__unsignedLong	nextChunkDelay,
						xsd__int			fileType,
						xsd__unsignedLong	forUpdateAgentFlag,
						struct SOAPUpdateAgentInfosList *updatesAgents,
						struct klft_InitiateFileUploadResponse
							&r );

int klft_RegisterUpdateAgentStub(  struct soap *soap, 
						xsd__wstring	strAddress,
						xsd__wstring	strNoSSLAddress,
						xsd__wstring	strMulticastIp,
						param__params	pParOptions,
						struct klft_RegisterUpdateAgentResponse
							&r );

int klft_InitiateServerFileUploadStub(  struct soap *soap, 						
						xsd__wstring	fileId,
						xsd__unsignedLong	dirFlag,
						xsd__unsignedLong	lifeTime,
						xsd__unsignedLong	fullFileSize,
						struct klft_InitiateServerFileUploadResponse
							&r );

int klft_CancelServerFileUploadStub(  struct soap *soap, 						
						xsd__wstring	fileId,
						struct klft_CancelServerFileUploadResponse
							&r );

int klft_PutNextFileChunkStub(  struct soap *soap, 						
						xsd__wstring	fileId,						
						struct klft_file_chunk_t	chunk,
						struct klft_PutNextFileChunkResponse
							&r );

int klft_GetSyncFolderDiffStub(  struct soap *soap, 						
						xsd__wstring	fileDescription,
						struct SOAPFilesInfoList *clientFilesList,
						struct SOAPSyncFolderOptions *subfoldersOptions,
						struct klft_GetSyncFolderDiffResponse
							&r );

int klft_GetSyncFolderFileInfoStub(  struct soap *soap, 
						xsd__wstring	syncFolderFileId,
						xsd__wstring	folderFileName,						
						struct klft_GetSyncFolderFileInfoResponse
							&r );

int klft_GetSyncFolderFileChunkStub(  struct soap *soap, 
						xsd__wstring	syncFolderFileId,
						xsd__wstring	folderFileName,						
						xsd__unsignedLong	startFilePos,
						xsd__unsignedLong	neededSize,
						struct klft_GetSyncFolderFileChunkResponse
							&r );

namespace KLFT
{

	struct KLSTRT::SOAPStubFunc ft_funcs_ptrs[9]=
	{
		{ L"klft_InitiateFileUpload",		 (void*)klft_InitiateFileUploadStub },
		{ L"klft_RegisterUpdateAgent",		 (void*)klft_RegisterUpdateAgentStub },
		{ L"klft_InitiateServerFileUpload",		 (void*)klft_InitiateServerFileUploadStub },
		{ L"klft_CancelServerFileUpload",		 (void*)klft_CancelServerFileUploadStub },
		{ L"klft_PutNextFileChunk",		 (void*)klft_PutNextFileChunkStub },
		{ L"klft_GetSyncFolderDiff",		 (void*)klft_GetSyncFolderDiffStub },
		{ L"klft_GetSyncFolderFileInfo",		 (void*)klft_GetSyncFolderFileInfoStub },
		{ L"klft_GetSyncFolderFileChunk",		 (void*)klft_GetSyncFolderFileChunkStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( ft_funcs_ptrs, (sizeof(ft_funcs_ptrs)/sizeof(ft_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( ft_funcs_ptrs, (sizeof(ft_funcs_ptrs)/sizeof(ft_funcs_ptrs[0])) );
	}

} // end namespace KLFT
