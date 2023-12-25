// tree.h
//

#ifndef tree_h_INCLUDED
#define tree_h_INCLUDED

#include "treedefs.h"


// --------------------------------------------------------------------------------------------
//   ������������� / ���������������
// --------------------------------------------------------------------------------------------

// ��������� �������������
// pStorageHeapCtx	- ��������� �� ��������������������� ��������� � CALLBACK ��������� ������� ������������� ������
// ppRTCtx			- ��������� �������� ������ (Runtime Tree Context)
EXTERN_C TREE_ERR _TREE_CALL TreeInit(IN sHEAP_CTX* pStorageHeapCtx, OUT sRT_CTX** ppRTCtx);

// ��������� �������� ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
EXTERN_C TREE_ERR _TREE_CALL TreeDone(IN sRT_CTX* pRTCtx);

// �������� ���������� � ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pTreeInfo		- �������� ���������� � ������ � ��������� TREE_INFO
EXTERN_C TREE_ERR _TREE_CALL TreeGetInfo(IN sRT_CTX* pRTCtx, OUT TREE_INFO* pTreeInfo);


// --------------------------------------------------------------------------------------------
//   �������� / ��������
// --------------------------------------------------------------------------------------------

// ��� TreeLoad_xxx ������ �������������� ����������� ����� ����������� ������, ���� ��� ���� ��������� � ��������.

// ��������� ����������� ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pIOCtx			- ��������� �� ��������������������� ��������� � CALLBACK ��������� �����-������
EXTERN_C TREE_ERR _TREE_CALL TreeLoad_Static(IN sRT_CTX* pRTCtx, IN sIO_CTX* pIOCtx);

// ��������� ����������� ������ �� ����������� (�������������� ������).
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pMappedData		- ��������� �� ����������� (��������������) ������ ������
// dwMappedDataSize - ������ ����������� (��������������) ������ � ������
EXTERN_C TREE_ERR _TREE_CALL TreeLoad_StaticOnMap(IN sRT_CTX* pRTCtx, IN void* pMappedData, IN uint32_t dwMappedDataSize);

// ��������� ����������� ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
EXTERN_C TREE_ERR _TREE_CALL TreeUnload_Static(IN sRT_CTX* pRTCtx);

// ��������� ������������ ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pIOCtx			- ��������� �� ��������������������� ��������� � CALLBACK ��������� �����-������
EXTERN_C TREE_ERR _TREE_CALL TreeLoad_Dynamic(IN sRT_CTX* pRTCtx, IN sIO_CTX* pIOCtx);

// ��������� ������������ ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
EXTERN_C TREE_ERR _TREE_CALL TreeUnload_Dynamic(IN sRT_CTX* pRTCtx);

// ��������� ����������� ��� ������������ ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pIOCtx			- ��������� �� ��������������������� ��������� � CALLBACK ��������� �����-������
EXTERN_C TREE_ERR _TREE_CALL TreeLoad_Any(IN sRT_CTX* pRTCtx, IN sIO_CTX* pIOCtx);

// ��������� ����������� ��� ������������ ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
EXTERN_C TREE_ERR _TREE_CALL TreeUnload_Any(IN sRT_CTX* pRTCtx);

// ��������� ����������� ������ �� �������������, ������ � ������ �� �������� � �������� ������������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit, ������ ��������� ������������ ������
// pIOCtx			- ��������� �� ��������������������� ��������� � CALLBACK ��������� �����-������
EXTERN_C TREE_ERR _TREE_CALL TreeSave_Static(IN sRT_CTX* pRTCtx, IN sIO_CTX* pIOCtx, IN uint32_t dwHashLevel, IN uint32_t dwHashTableSizeKb);

// ��������� ������������ ������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit, ������ ��������� ������������ ������
// pIOCtx			- ��������� �� ��������������������� ��������� � CALLBACK ��������� �����-������
EXTERN_C TREE_ERR _TREE_CALL TreeSave_Dynamic(IN sRT_CTX* pRTCtx, IN sIO_CTX* pIOCtx);


// --------------------------------------------------------------------------------------------
//   �����
// --------------------------------------------------------------------------------------------

// �������� �������� ��� ������, ���������� - ������� ������� ������� ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pSeacherHeapCtx	- ��������� �� ��������������������� ��������� � CALLBACK ��������� ������� ������������� ������
//					  ����� ��������� � pStorageHeapCtx
// ppSeacherRTCtx	- ��������� ������� ������
EXTERN_C TREE_ERR _TREE_CALL TreeGetSeacherContext(IN sRT_CTX* pRTCtx, IN sHEAP_CTX* pSeacherHeapCtx, OUT sSEARCHER_RT_CTX** ppSeacherRTCtx);

// ��������� �������� ������, ���������� - ���������� ������� ������� ������.
// pSeacherRTCtx	- ������� ������, ����� ���������� �� TreeGetSeacherContext
EXTERN_C TREE_ERR _TREE_CALL TreeDoneSeacherContext(IN sSEARCHER_RT_CTX* pSeacherRTCtx);

// �������� CALLBACK �������, ���������� ��� ������ ��� ��������� ��������
// pCallbackCtx     - ��������, ���������� ��� ������ TreeSearchData
// SignatureID      - ������������� ��������� ���������
// dwPosInBuffer    - ������� ������ ��������� � ������ ������. ���� ��������� �������� � ���������� �����, �������� ����� �������������.
// qwPosLinear      - �������� ������� �� ������ ������ ���������� �� ���-�� ������
// dwSignatureLen   - ����� ���������
// ������������ ��������:
//    errOPERATION_CANCELED - ���������� ����� � ����� �� TreeSearchData
//    ������                - ���������� �����
typedef TREE_ERR (_TREE_CALL* tTreeSignatureFoundCallbackFunc)(IN CONST void* pCallbackCtx, IN tSIGNATURE_ID SignatureID, IN int32_t dwPosInBuffer, IN uint64_t qwPosLinear, IN uint32_t dwSignatureLen);

// ��������� ����� �� ������. ����� �� ������ ������ ����� ������������ ������� ����� �����, ��� ����� 
// ����� ������ ��������������� �������� TreeSearchData �������� ���-�� �������� ������.
// pSeacherRTCtx	- ������� ������, ����� ���������� �� TreeGetSeacherContext
// pbData			- ������, � ������� ������������ �����
// dwSize			- ������ ������ � ������
// dwStartPos		- ��������� ������� � ������, � ������� ���������� �����
// dwEndPos			- �������� ������� � ������, �� ������� ������������ �����. 
//                    (!) ��������� ������������ �� dwEndPos, �� ��������������� ����� ��� ����� �������.
//                    (!) ���� dwStartPos ����� dwEndPos, �� ����� ������� ��������� ������������ 
//                    ������ � ���� �������.
// TreeSignatureFoundCallbackFunc - ��������� �� CALLBACK �������, ������� ����� ���������� ��� ���������� ���������.
// pCallbackCtx		- ��������, � ������� ����� ���������� CALLBACK �������.
EXTERN_C TREE_ERR _TREE_CALL TreeSearchData(IN sSEARCHER_RT_CTX* pSearcherRTCtx,
							   IN CONST uint8_t* pbData,
							   IN uint32_t dwSize,
							   IN uint32_t dwStartPos,
							   IN uint32_t dwEndPos,
							   IN tTreeSignatureFoundCallbackFunc TreeSignatureFoundCallbackFunc,
							   IN CONST void* pCallbackCtx);

// ���������� �������� ������ ��� ���������� ������ ������
// pSearcherRTCtx	- ������� ������, ����� ���������� �� TreeGetSeacherContext
EXTERN_C TREE_ERR _TREE_CALL TreeNewSearch(IN sSEARCHER_RT_CTX* pSearcherRTCtx);


// --------------------------------------------------------------------------------------------
//   ����������� ������
// --------------------------------------------------------------------------------------------

// ��� �������� �� ����������� ����������� ������ ��� ������������� ������

// �������� ��������� � ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pSignature		- ��������� � ������� TreeSearch
// dwSignatureSize	- ����� ��������� � ������� TreeSearch
// SignatureID		- �������������, ������� ������ �������� ��������� ��� ���������� � ������
// pResultSignatureID - � ������ ������ �������� ������������� ����������� ���������. ���� ����������� 
//					  ��������� ��� �������������� � ������, ������� ���������� errOBJECT_ALREADY_EXIST
//                    � pResultSignatureID �������� ������������� ��������� ���������.
EXTERN_C TREE_ERR _TREE_CALL TreeAddSignature(IN sRT_CTX* pRTCtx, IN CONST uint8_t* pSignature, IN uint32_t dwSignatureSize, IN tSIGNATURE_ID SignatureID, OUT tSIGNATURE_ID* pResultSignatureID);

// ������� ��������� �� ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pSignature		- ��������� � ������� TreeSearch
// dwSignatureSize	- ����� ��������� � ������� TreeSearch
EXTERN_C TREE_ERR _TREE_CALL TreeDeleteSignature(IN sRT_CTX* pRTCtx, IN CONST uint8_t* pSignature, IN uint32_t dwSignatureSize);

// ��������� ������� ��������� � ������. � ������ ������ ���������� ������������� ���������
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pSignature		- ��������� � ������� TreeSearch
// dwSignatureSize	- ����� ��������� � ������� TreeSearch
// pSignatureID		- � ������ ������ �������� ������������� ���������
EXTERN_C TREE_ERR _TREE_CALL TreeIsSignature(IN sRT_CTX* pRTCtx, IN CONST uint8_t* pSignature, IN uint32_t dwSignatureSize, OUT tSIGNATURE_ID* pSignatureID);

// ����������� ��������� �� ���������� HEX ������������� � ������ TreeSearch
// pHexMask			- ��������� HEX ������������� ���������
// dwHexMaskSize	- ������ ���������� HEX ������������� � ������
// pSignature		- �����, ���������� ��������� � ������� TreeSearch
// dwBufferSize		- ������ ������ � ������
// pdwSignatureSize	- � ������ ������, ���-�� ���� ���������� � �����. ���� ������ ������ 
//					  ������������ ��� ��������� ���������, ������� ���������� errBUFFER_TOO_SMALL 
//                    � pdwSignatureSize �������� ����������� ������ ������.
EXTERN_C TREE_ERR _TREE_CALL TreeConvertHex2Signature(IN CONST uint8_t* pHexMask, IN uint32_t dwHexMaskSize, OUT uint8_t* pSignature, IN uint32_t dwBufferSize, OUT uint32_t* pdwSignatureSize);

// ����������� ��������� �� ��������� RAW ������������� � ������ TreeSearch
// pRawData			- �������� RAW ������������� ���������
// dwRawDataSize	- ������ ��������� RAW ������������� � ������
// pSignature		- �����, ���������� ��������� � ������� TreeSearch
// dwBufferSize		- ������ ������ � ������
// pdwSignatureSize	- � ������ ������, ���-�� ���� ���������� � �����. ���� ������ ������ 
//					  ������������ ��� ��������� ���������, ������� ���������� errBUFFER_TOO_SMALL 
//                    � pdwSignatureSize �������� ����������� ������ ������.
EXTERN_C TREE_ERR _TREE_CALL TreeConvertRaw2Signature(IN CONST uint8_t* pRawData, IN uint32_t dwRawDataSize, OUT uint8_t* pSignature, IN uint32_t dwBufferSize, OUT uint32_t* pdwSignatureSize);
EXTERN_C TREE_ERR _TREE_CALL TreeConvertSignature2Raw(IN CONST uint8_t* pSignature, IN uint32_t dwSignatureSize, OUT uint8_t* pRawData, IN uint32_t dwBufferSize, OUT uint32_t* pdwRawDataSize);

// --------------------------------------------------------------------------------------------
//   ����������
// --------------------------------------------------------------------------------------------

// �������� CALLBACK �������, ���������� ��� ���������� ��������
// pCallbackCtx     - ��������, ���������� ��� ������ TreeEnumSignatures
// SignatureID      - ������������� ���������
// pSignature		- ��������� � ������� TreeSearch
// dwSignatureSize	- ����� ��������� � ������� TreeSearch
// ������������ ��������:
//    errOPERATION_CANCELED - ���������� ���������� � ����� �� TreeEnumSignatures
//    ������                - ���������� ����������
typedef TREE_ERR (_TREE_CALL *tTreeEnumCallbackFunc)(CONST void* pCallbackCtx, tSIGNATURE_ID SignatureID, CONST uint8_t* pSignature, uint32_t dwSignatureSize);

// ����������� ��� ��������� � ������ � �������� CALLBACK �������  
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// TreeEnumCallbackFunc - ��������� �� CALLBACK �������, ������� ����� ���������� ��� ������ ���������.
// pCallbackCtx		- ��������, � ������� ����� ���������� CALLBACK �������.
EXTERN_C TREE_ERR _TREE_CALL TreeEnumSignatures(sRT_CTX* pRTCtx, tTreeEnumCallbackFunc TreeEnumCallbackFunc, CONST void* pCallbackCtx);


// --------------------------------------------------------------------------------------------
//   ���������� �������
// --------------------------------------------------------------------------------------------

// ������� � STDOUT ������ � ��������� ����. �� ������������ ����������� ������ ������.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
EXTERN_C TREE_ERR _TREE_CALL TreeDump(IN sRT_CTX* pRTCtx);

// �������� ���������� �� ���� ������ �� ����� �������. ������������ � Watch ����.
// pRTCtx		    - �������� ������ ����� ���������� �� TreeInit
// pNode			- ���� ������, � ������� ����� �������� ���������� 
EXTERN_C char * _TREE_CALL DbgNodeInfo(IN sRT_CTX* pRTCtx, IN NODE* pNode);

#endif // tree_h_INCLUDED

