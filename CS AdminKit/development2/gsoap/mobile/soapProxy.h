/* soapProxy.h
   Generated by gSOAP 2.7.0d from soapheader.h
   Copyright (C) 2001-2004 Genivia, Inc. All Rights Reserved.
   This software is released under one of the following three licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
   See README.txt for further details.
*/

#ifndef soapService_H
#define soapService_H
#include "soapH.h"
SOAP_BEGIN_NAMESPACE(soap)
class Service
{   public:
	struct soap *soap;
	const char *endpoint;
	Service()
	{ soap = soap_new(); endpoint = "http://localhost:80"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope"},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding"},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance"},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema"},
	{"param", "http://tempuri.org/param.xsd"},
	{"aklwngt", "http://tempuri.org/aklwngt.xsd"},
	{NULL, NULL}
};
	soap->namespaces = namespaces; } };
	virtual ~Service() { if (soap) { soap_destroy(soap); soap_end(soap); soap_done(soap); SOAP_FREE((void*)soap); } };
	virtual int aklwngt__SessionBegin(char *szDeviceId, char *szPassword, int nProtocolVersion, struct aklwngt__SessionBeginResponse &r) { return soap ? soap_call_aklwngt__SessionBegin(soap, endpoint, NULL, szDeviceId, szPassword, nProtocolVersion, r) : SOAP_EOM; };
	virtual int aklwngt__SessionEnd(char *szSessionId, struct aklwngt__SessionEndResponse &r) { return soap ? soap_call_aklwngt__SessionEnd(soap, endpoint, NULL, szSessionId, r) : SOAP_EOM; };
	virtual int aklwngt__Heartbeat(char *szSessionId, struct aklwngt__sync_info *oMaySynchronize, struct aklwngt__HeartbeatResponse &r) { return soap ? soap_call_aklwngt__Heartbeat(soap, endpoint, NULL, szSessionId, oMaySynchronize, r) : SOAP_EOM; };
	virtual int aklwngt__PutResult(char *szSessionId, struct aklwngt__command *result, struct aklwngt__PutResultResponse &r) { return soap ? soap_call_aklwngt__PutResult(soap, endpoint, NULL, szSessionId, result, r) : SOAP_EOM; };
	virtual int aklwngt__PutEvents(char *szSessionId, struct aklwngt__event_info_array *oEventsInfoArray, struct aklwngt__PutEventsResponse &r) { return soap ? soap_call_aklwngt__PutEvents(soap, endpoint, NULL, szSessionId, oEventsInfoArray, r) : SOAP_EOM; };
	virtual int aklwngt__klft_GetFileInfo(char *szSessionId, wchar_t *fileName, struct aklwngt__klft_GetFileInfoResponse &r) { return soap ? soap_call_aklwngt__klft_GetFileInfo(soap, endpoint, NULL, szSessionId, fileName, r) : SOAP_EOM; };
	virtual int aklwngt__klft_GetNextFileChunk(char *szSessionId, wchar_t *fileName, ULONG64 startFilePos, ULONG64 neededSize, struct aklwngt__klft_GetNextFileChunkResponse &r) { return soap ? soap_call_aklwngt__klft_GetNextFileChunk(soap, endpoint, NULL, szSessionId, fileName, startFilePos, neededSize, r) : SOAP_EOM; };
};
SOAP_END_NAMESPACE(soap)
#endif
