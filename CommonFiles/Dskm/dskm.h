/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	dskm.h
*		\brief	
*		
*		\author Victor Matioshenkov
*		\date	6/15/2005 11:26:24 AM
*		
*		Example:	
*		
*		
*		
*/		


#ifndef __dskm_h__
#define __dskm_h__

#include "../AVP_data.h"

#ifndef DSKMAPI
#if defined (__unix__)
#define DSKMAPI
#else
#define DSKMAPI __cdecl
#endif /* __unix__ */
#endif /* DSKMAPI */


#if defined( __cplusplus )
extern "C" {
#endif

#define DSKM_OTYPE_KEY_KL_MASTER_PRIVATE	(0x7fffff)
#define DSKM_OTYPE_KEY_KL_MASTER_PUBLIC		(0x7ffffe)
#define DSKM_OTYPE_KEY_KL_PRIVATE					(0x7ffffd)
#define DSKM_OTYPE_KEY_KL_PUBLIC					(0x7ffffc)
#define DSKM_OTYPE_KEY_OPERABLE_PRIVATE		(0x7ffffb)
#define DSKM_OTYPE_KEY_OPERABLE_PUBLIC		(0x7ffffa)

#define DSKM_OTYPE_LICENCE_KEY            (0x7ffff9)  
#define DSKM_OTYPE_LICENCE_KEY_ORDER      (0x7ffff8)  

#define DSKM_OTYPE_ASSOC_FILE             (0x7ffff7)

#define DSKM_OTYPE_USER_MIN               (0x000001)
#define DSKM_OTYPE_USER_MAX               (0x7ffff6)

#define DSKM_ERR_OK												0xe9ba5770 /*is a crc32 for "DSKM_ERR_OK"*/                       // (0x0)
#define DSKM_ERR_NOT_INITIALIZED					0xd10cc37a /*is a crc32 for "DSKM_ERR_NOT_INITIALIZED"*/					// (0x1)
#define DSKM_ERR_IO_NOT_LOADED						0x48097982 /*is a crc32 for "DSKM_ERR_IO_NOT_LOADED"*/						// (0x2)
#define DSKM_ERR_CANNOT_CREATE_REG_FILE		0x68b0acf0 /*is a crc32 for "DSKM_ERR_CANNOT_CREATE_REG_FILE"*/		// (0x3)
#define DSKM_ERR_CANNOT_WRITE_REG_FILE		0x308015e7 /*is a crc32 for "DSKM_ERR_CANNOT_WRITE_REG_FILE"*/		// (0x4)
#define DSKM_ERR_CANNOT_WRITE_REG_TOMEM		0xdab8d467 /*is a crc32 for "DSKM_ERR_CANNOT_WRITE_REG_TOMEM"*/		// (0x5)
#define DSKM_ERR_CANNOT_OPEN_REG_FILE			0x3d0507bd /*is a crc32 for "DSKM_ERR_CANNOT_OPEN_REG_FILE"*/			// (0x6)
#define DSKM_ERR_CANNOT_READ_REG_FILE			0xfd6eb8be /*is a crc32 for "DSKM_ERR_CANNOT_READ_REG_FILE"*/			// (0x7)
#define DSKM_ERR_INVALID_REG_FILE					0xc2fef413 /*is a crc32 for "DSKM_ERR_INVALID_REG_FILE"*/					// (0x8)
#define DSKM_ERR_INVALID_REG_FILE_VERSION 0x2a592774 /*is a crc32 for "DSKM_ERR_INVALID_REG_FILE_VERSION"*/ // (0x9)
#define DSKM_ERR_INVALID_REG_FILE_OBJTYPE 0x4ef35e4d /*is a crc32 for "DSKM_ERR_INVALID_REG_FILE_OBJTYPE"*/	// (0xa)
#define DSKM_ERR_KEY_NOT_FOUND						0x408b1c02 /*is a crc32 for "DSKM_ERR_KEY_NOT_FOUND"*/						// (0xb)
#define DSKM_ERR_REG_NOT_FOUND						0x8f995ffd /*is a crc32 for "DSKM_ERR_REG_NOT_FOUND"*/						// (0xc)
#define DSKM_ERR_CANNOT_CALC_OBJ_HASH			0x7d11f7e2 /*is a crc32 for "DSKM_ERR_CANNOT_CALC_OBJ_HASH"*/			// (0xd)
#define DSKM_ERR_NOT_ALL_OBJECTS_FOUND		0xc58506ed /*is a crc32 for "DSKM_ERR_NOT_ALL_OBJECTS_FOUND"*/		// (0xe)
#define DSKM_ERR_INVALID_SIGN							0x38f3542d /*is a crc32 for "DSKM_ERR_INVALID_SIGN"*/							// (0xf)
#define DSKM_ERR_INVALID_BUFFER						0xdeabf3f6 /*is a crc32 for "DSKM_ERR_INVALID_BUFFER"*/						// (0x10)
#define DSKM_ERR_INVALID_PARAMETER				0x5aaeeae0 /*is a crc32 for "DSKM_ERR_INVALID_PARAMETER"*/				// (0x11)
#define DSKM_ERR_INVALID_OBJTYPE					0xe75abf28 /*is a crc32 for "DSKM_ERR_INVALID_OBJTYPE"*/  				// (0x12)
#define DSKM_ERR_DATA_PROCESSING					0x6eb9a4a4 /*is a crc32 for "DSKM_ERR_DATA_PROCESSING"*/					// (0x13)
#define DSKM_ERR_HASH_NOT_FOUND						0x9cef5380 /*is a crc32 for "DSKM_ERR_HASH_NOT_FOUND"*/						// (0x14)
#define DSKM_ERR_ANOTHER_BASE_REG_FOUND		0xdec30ebe /*is a crc32 for "DSKM_ERR_ANOTHER_BASE_REG_FOUND"*/		// (0x15)
#define DSKM_ERR_LIB_CODE_HACKED					0x7051b0ac /*is a crc32 for "DSKM_ERR_LIB_CODE_HACKED"*/				  // (0x16)
#define DSKM_ERR_CANNOT_CREATE_SIGN				0x5b118908 /*is a crc32 for "DSKM_ERR_CANNOT_CREATE_SIGN"*/				// (0x17)
#define DSKM_ERR_CRIPTO_LIB								0xa0f61271 /*is a crc32 for "DSKM_ERR_CRIPTO_LIB"*/								// (0x18)
#define DSKM_ERR_OBJECT_NOT_FOUND         0xa200485b /*is a crc32 for "DSKM_ERR_OBJECT_NOT_FOUND"*/         // (0x19)
#define DSKM_ERR_CALLBACK_READ_ERROR			0x96bdea9f /*is a crc32 for "DSKM_ERR_CALLBACK_READ_ERROR"*/			// (0x1a)
#define DSKM_ERR_CANNOT_OPEN_FILE					0x14064f2a /*is a crc32 for "DSKM_ERR_CANNOT_OPEN_FILE"*/					// (0x1b)
#define DSKM_ERR_IO_NOT_INITIALIZED       0x04529da3 /*is a crc32 for "DSKM_ERR_IO_NOT_INITIALIZED"*/				// (0x1c)
#define DSKM_ERR_REGS_NOT_INITIALIZED			0xeb529c3d /*is a crc32 for "DSKM_ERR_REGS_NOT_INITIALIZED"*/			// (0x1d)
#define DSKM_ERR_MORE_THAN_ONE_KEY        0xc9098782 /*is a crc32 for "DSKM_ERR_MORE_THAN_ONE_KEY"*/				// (0x1e)
#define DSKM_ERR_SIGN_NOT_FOUND						0x08cd9bac /*is a crc32 for "DSKM_ERR_SIGN_NOT_FOUND"*/						// (0x1f)
#define DSKM_ERR_ANOTHER_SIGN_FOUND				0xde3346ac /*is a crc32 for "DSKM_ERR_ANOTHER_SIGN_FOUND"*/				// (0x20)
#define DSKM_ERR_INVALID_SIZE							0x504de1b9 /*is a crc32 for "DSKM_ERR_INVALID_SIZE"*/							// (0x21)
#define DSKM_ERR_PROP_NOT_FOUND						0xddee3e3d /*is a crc32 for "DSKM_ERR_PROP_NOT_FOUND"*/						// (0x22)
#define DSKM_ERR_OBJECTS_NOT_EQUAL				0x2ba71ba6 /*is a crc32 for "DSKM_ERR_OBJECTS_NOT_EQUAL"*/				// (0x23)
#define DSKM_UNKNOWN_ERROR								0x9f1e269c /*is a crc32 for "DSKM_UNKNOWN_ERROR"*/                // (0xffff) 

#define DSKM_OK(a)												(!((a)^DSKM_ERR_OK))
#define DSKM_NOT_OK(a)										(((a)^DSKM_ERR_OK))

#define DSKM_OBJ_SIGN_INREG								(0x0001)
#define DSKM_OBJ_SIGN_INOBJ								(0x0002)

#define DSKM_OBJ_EXTERNAL_BUFFER_PTR      (0x0001)	// the size is "sizeof(void *)"
#define DSKM_OBJ_EXTERNAL_PARAM_PTR       (0x0002)	// the size is "sizeof(void *)"
#define DSKM_OBJ_PROCESSING_ERROR					(0x0003)	// the size is "sizeof(AVP_dword)"
#define DSKM_OBJ_SIGNED_BY								(0x0004)	// the size is "sizeof(AVP_dword)"; value is one of DSKM_OBJ_SIGN_*
#define DSKM_OBJ_USERDATA_MIN             (0x0010)
#define DSKM_OBJ_USERDATA_MAX             (0xffff)



typedef struct tagDSKM {
	AVP_byte _;
} *HDSKM;
	

typedef struct tagDSKMLIST {
	AVP_byte _;
	} *HDSKMLIST;


typedef struct tagDSKMLISTOBJ {
	AVP_byte _;
} *HDSKMLISTOBJ;


	
#define DSKM_CB_OPEN  1	
#define DSKM_CB_READ  2
#define DSKM_CB_WRITE 3	
#define DSKM_CB_CLOSE 4

//! \fn				: 	DSKMAPI* pfnDSKM_GetBuffer_CallBack
//! \brief			:	Callback �������� ������ �������
//! \return			: typedef int - ���������� ���������� ����
//! \param          : void *pParams - ��������� �������
//! \param          : void *pvBuffer	- ��������� �� ����� ������
//! \param          : AVP_dword dwBufferSize - ������ ������ ������
//! \param          : AVP_dword dwCommand - ��� ������� (DSKM_CB_*)
typedef int (DSKMAPI* pfnDSKM_GetBuffer_CallBack)( void *pParams, void *pvBuffer, AVP_dword dwBufferSize, AVP_dword dwCommand );



// ---
typedef struct DSKM_Io {									
	struct DSKM_Io_Vtbl *lpVtbl;
	unsigned int	       m_cRef;				
} DSKM_Io;											

typedef struct DSKM_Io_Vtbl DSKM_Io_Vtbl; 

// ---
struct DSKM_Io_Vtbl {
	unsigned int (*AddRef)( DSKM_Io *This );
	unsigned int (*Release) ( DSKM_Io *This );
	void * (*CreateFile)(
		DSKM_Io *This,
    const char   *lpFileName,									// pointer to name of the file
    unsigned long dwDesiredAccess,						// access (read-write) mode
    unsigned long dwShareMode,								// share mode
    void*  lpSecurityAttributes,							// pointer to security descriptor SECURITY_ATTRIBUTES FAR
    unsigned long  dwCreationDistribution,		// how to create
    unsigned long  dwFlagsAndAttributes,			// file attributes
    void *hTemplateFile												// HANDLE handle to file with attributes to copy
	);
	int (*CloseHandle)(
		DSKM_Io *This,
    void *  hObject														// HANDLE handle to object to close
	);
	int (*ReadFile )(
		DSKM_Io *This,
    void*  hFile,															// HANDLE handle of file to read
    void*  lpBuffer,													// address of buffer that receives data
    unsigned long  nNumberOfBytesToRead,			// number of bytes to read
    unsigned long*  lpNumberOfBytesRead,			// address of number of bytes read
    void*  lpOverlapped												// OVERLAPPED FAR * address of structure for data BYTE Disk, WORD Sector ,BYTE Head ,LPBYTE Buffer)
	);
	int (*WriteFile )(
		DSKM_Io *This,
    void*  hFile,															// HANDLE handle to file to write to
    const void*  lpBuffer,										// pointer to data to write to file
    unsigned long  nNumberOfBytesToWrite,     // number of bytes to write
    unsigned long*  lpNumberOfBytesWritten,   // pointer to number of bytes written
    void*  lpOverlapped												// OVERLAPPED FAR * addr. of structure needed for overlapped I/O
	);
	unsigned long (*SetFilePointer)(
		DSKM_Io *This,
    void*  hFile,															// HANDLE handle of file
    long  lDistanceToMove,										// number of bytes to move file pointer
    long*  lpDistanceToMoveHigh,							// address of high-order word of distance to move
    unsigned long  dwMoveMethod								// how to move
	);
	unsigned long (*GetFileSize)(
		DSKM_Io *This,
    void*  hFile,															// HANDLE handle of file
    unsigned long*  lpHigh
	);
	void* (*FindFirstFile)(
		DSKM_Io *This,
		const char* lpFileFolder,									// file folder
		char*  lpFoundFileName,										// found file
		unsigned long   dwFileNameSize						// found file name size
	);
	int (*FindNextFile)(
		DSKM_Io *This,
		void*	hFindFile,													// HANDLE search handle 
		char*  lpFoundFileName,										// found file
		unsigned long   dwFileNameSize						// found file name size
	);
	int (*FindClose)(
		DSKM_Io *This,
		void*	hFindFile														// HANDLE search handle 
	); 
};


//---------------------------------------------------------------------------------------------------------------------------
// ������� �������������/������������ ����������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_InitLibrary
//! \brief			:	������������� ����������.
//! \return			: �������� ����������. 0 - �������� ���������. 
//! \param          : (*pfnAlloc)(AVP_uint) - ��������� �� ������� ������������� ������
//! \param          : void (*pfnFree((void *)	- ��������� �� ������� ������������ ������
//! \param          : AVP_bool bInitSubLib - ����� �� ������������ ��������������� ���������� (Property.lib)
HDSKM	    DSKMAPI DSKM_InitLibrary( void* (DSKMAPI *pfnAlloc)(AVP_size_t), void (DSKMAPI *pfnFree)(void*), AVP_bool bInitSubLib );


//! \fn				: DSKM_InitLibraryEx
//! \brief			:	������������� ����������.
//! \return			: �������� ����������. 0 - �������� ���������. 
//! \param          : (*pfnAlloc)(AVP_uint) - ��������� �� ������� ������������� ������
//! \param          : void (*pfnFree((void *)	- ��������� �� ������� ������������ ������
//! \param          : DSKM_Io *pIo - ��������� �� ��������� �����/������ (�� ����� ���� 0)
//! \param          : AVP_bool bInitSubLib - ����� �� ������������ ��������������� ���������� (Property.lib)
HDSKM	    DSKMAPI DSKM_InitLibraryEx( void* (DSKMAPI *pfnAlloc)(AVP_size_t), void (DSKMAPI *pfnFree)(void*), DSKM_Io *pIo, AVP_bool bInitSubLib );


//! \fn				: DSKM_DeInitLibrary
//! \brief			:	���������� ������ ���������� 
//! \return			: ��� ������ 
//! \param          : HDSKM hDSKM - �������� ����������
//! \param          : AVP_bool bDeInitSubLib - ����� �� ��-������������ ��������������� ���������� (Property.lib)
AVP_dword	DSKMAPI DSKM_DeInitLibrary( HDSKM hDSKM, AVP_bool bDeInitSubLib );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ������ � �������� �������� � ����������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_Create
//! \brief			:	�������� ������ ���������� ��������
//! \return			: ��� ������ 
//! \param          : HDSKMLIST *hParList - ��������� �� ����������� ������
AVP_dword		DSKMAPI DSKM_ParList_Create( HDSKMLIST *hParList );



//! \fn				: DSKM_ParList_Delete
//! \brief			:	������� ������ ���������� ��������
//! \return			: ��� ������
//! \param          : HDSKMLIST hList - ������ ��� ��������
AVP_dword 	DSKMAPI DSKM_ParList_Delete( HDSKMLIST hList );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ���������� � ������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_AddStrParam
//! \brief			:	�������� ��������� �������� ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwParamId - ������������� ��������� (������ ���� ����������)
//! \param          : const AVP_char* pszStrParam	- �������� ��� ���������� (������ ����������)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddStrParam( HDSKMLIST hList, AVP_dword dwParamId, const AVP_char* pszStrParam );


//! \fn				: DSKM_ParList_AddDWordParam
//! \brief			:	�������� ������������� ��������	������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwParamId - ������������� ���������	(������ ���� ����������)
//! \param          : AVP_dword dwParam	- �������� ��� ����������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddDWordParam( HDSKMLIST hList, AVP_dword dwParamId, AVP_dword dwParam );


//! \fn				: DSKM_ParList_AddBinaryPtrParam
//! \brief			:	�������� �������� �������� ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwParamId - ������������� ���������	(������ ���� ����������)
//! \param          : void *pvParamPtr	- ����� ��� ���������� (����������)
//! \param          : AVP_dword dwBinarySize - ������ ������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddBinaryPtrParam( HDSKMLIST hList, AVP_dword dwParamId, void *pvParamPtr, AVP_dword dwBinarySize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ���������� � ������ �������� (���������� ������ � ����� DSKM_PrepareRegsSet/DSKM_CheckObjectsUsingRegsSet)
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_AddObjectStrParam
//! \brief			:	�������� ��������� �������� ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : AVP_dword dwParamId - ������������� ��������� (������ ���� ����������)
//! \param          : const AVP_char* pszStrParam	- �������� ��� ���������� (������ ����������)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectStrParam( HDSKMLIST hList, HDSKMLISTOBJ hListObject, AVP_dword dwParamId, const AVP_char* pszStrParam );


//! \fn				: DSKM_ParList_AddObjectDWordParam
//! \brief			:	�������� ������������� ��������	������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : AVP_dword dwParamId - ������������� ���������	(������ ���� ����������)
//! \param          : AVP_dword dwParam	- �������� ��� ����������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectDWordParam( HDSKMLIST hList, HDSKMLISTOBJ hListObject, AVP_dword dwParamId, AVP_dword dwParam );


//! \fn				: DSKM_ParList_AddObjectBinaryPtrParam
//! \brief			:	�������� �������� �������� ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : AVP_dword dwParamId - ������������� ���������	(������ ���� ����������)
//! \param          : void *pvParamPtr	- ����� ��� ���������� (����������)
//! \param          : AVP_dword dwBinarySize - ������ ������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectBinaryPtrParam( HDSKMLIST hList, HDSKMLISTOBJ hListObject, AVP_dword dwParamId, void *pvParamPtr, AVP_dword dwBinarySize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ���������� 
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_ParList_AddFileAssociation
//! \brief			:	�������� ���������� ������ ��������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwObjectsType - ��� ������� (DSKM_OTYPE_KEY_* ��� ����������������)
//! \param          : const AVP_char* pObjRegFileName - ��� ����� � ��������� 
//! \param          : AVP_dword dwObjRegFileNameSize - ������ ����� � ������ (c ������� ������)
//! \param          : (���� 0 - ������ ��������� ANSI � ������ ��������� �� 0-�����)
//! \param          : const AVP_char* dwObjRegFileName	- ��� ����� � �������
//! \param          : AVP_dword dwKeyRegFileNameNameSize - ������ ����� � ������ (c ������� ������)
//! \param          : (���� 0 - ������ ��������� ANSI � ������ ��������� �� 0-�����)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddFileAssociation( HDSKMLIST hList, AVP_dword dwObjectsType, const AVP_char* pszObjRegFileName, AVP_dword dwObjRegFileNameSize, const AVP_char* pszKeyRegFileName, AVP_dword dwKeyRegFileNameNameSize );



//! \fn				:  DSKMAPI DSKM_ParList_AddObjectTypeAssociationFile
//! \brief			:	�������� ���� ���������� �����
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : const AVP_char* pszAssocFileName - ��� �����
//! \param          : AVP_dword dwAssocFileNameSize - ������ ����� � ������ (c ������� ������)
//! \param          : (���� 0 - ������ ��������� ANSI � ������ ��������� �� 0-�����)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectTypeAssociationFile( HDSKMLIST hList, const AVP_char* pszAssocFileName, AVP_dword dwAssocFileNameSize );



//! \fn				:  DSKMAPI DSKM_ParList_AddObjectTypeAssociationBufferedObject
//! \brief			:	�������� �������������� ������ ���������� �����
//! 							(����� ����� ����������� ��� ���������� �������� ������������/��������)
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : void *pvBuffer - ��������� �� ����� (�� ����� ���� �������)
//! \param          : AVP_dword dwBufferSize - ������ ������ (�� ����� ���� �������)
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������ 
//!										(����� ���� ������� - ������������ ����������� �����)
//! \param          : void *pvCallBackParams - ��������� ������� ��������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectTypeAssociationBufferedObject( HDSKMLIST hList, const void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ��������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_AddNamedObject
//! \brief			:	�������� ����������� ������ �������� (����)
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwObjectId - ������������� �������. ��������� ������ � ��������. ������ ���� ����������.
//! \param          : const AVP_char* pszObjectName	- ��� ������� (�����)
//! \param          : AVP_dword dwObjectNameSize - ������ ����� � ������ (c ������� ������)
//! \param          : (���� 0 - ������ ��������� ANSI � ������ ��������� �� 0-�����)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddNamedObject( HDSKMLIST hList, AVP_dword dwObjectId, const AVP_char* pszObjectName, AVP_dword dwObjectNameSize );


//! \fn				: DSKM_ParList_AddBufferedObject
//! \brief			:	�������� �������������� ������ ��������	(����� �� ����������)
//! 							(����� ����� ����������� ��� ���������� �������� ������������/��������)
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwObjectId - ������������� �������. ��������� ������ � ��������. ������ ���� ����������.
//! \param          : void *pvBuffer - ��������� �� ����� (�� ����� ���� �������)
//! \param          : AVP_dword dwBufferSize - ������ ������ (�� ����� ���� �������)
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������ 
//!												(����� ���� ������� - ������������ ����������� �����)
//! \param          : void *pvCallBackParams - ��������� ������� ��������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddBufferedObject( HDSKMLIST hList, AVP_dword dwObjectId, void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams );


//! \fn				: DSKM_ParList_AddObjectHash
//! \brief			:	�������� ������ �������� � ���� ��������������� ����� ����
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwObjectId - ������������� �������. ��������� ������ � ��������. ������ ���� ����������.
//! \param          : void *pvHashPtr - ��������� �� ���
//! \param          : AVP_dword dwHashSize - ������ ����
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddObjectHash( HDSKMLIST hList, AVP_dword dwObjectId, void *pvHashPtr, AVP_dword dwHashSize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ��������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_AddNamedReg
//! \brief			:	�������� ����������� ������ (����)
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwRegId - ������������� �������. ��������� ������ � ��������. ������ ���� ���������� (������ � ���������).
//! \param          : const AVP_char* pszRegName	- ��� ������� (�����)
//! \param          : AVP_dword dwRegNameSize - ������ ����� � ������ (c ������� ������)
//! \param          : (���� 0 - ������ ��������� ANSI � ������ ��������� �� 0-�����)
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddNamedReg( HDSKMLIST hList, AVP_dword dwRegId, const AVP_char* pszRegName, AVP_dword dwRegNameSize );


//! \fn				: DSKM_ParList_AddBufferedReg
//! \brief			:	�������� �������������� ������	(����� �� ����������)
//! 							(����� ����� ����������� ��� ���������� �������� ������������/��������)
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ ��� ����������
//! \param          : AVP_dword dwRegId - ������������� �������. ��������� ������ � ��������. ������ ���� ����������  (������ � ���������).
//! \param          : void *pvBuffer - ��������� �� ����� (�� ����� ���� �������)
//! \param          : AVP_dword dwBufferSize - ������ ������ (�� ����� ���� �������)
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������ 
//!												(����� ���� ������� - ������������ ����������� �����)
//! \param          : void *pvCallBackParams - ��������� ������� ��������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_AddBufferedReg( HDSKMLIST hList, AVP_dword dwRegId, void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams );



//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� ���������� �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_RemoveObjectById
//! \brief			:	������� ������ �� ������ ����� ID
//! \return			: ��� ������ 
//! \param          :  HDSKMLIST hList - ������ ��������
//! \param          : AVP_dword dwObjectId - ������������� ���������� (�� ����� ���� 0)
AVP_dword 	DSKMAPI DSKM_ParList_RemoveObjectById( HDSKMLIST hList, AVP_dword dwObjectId );


//! \fn				: DSKM_ParList_RemoveObjectByH
//! \brief			:	������� ������ �� ������
//! \return			: ��� ������ 
//! \param          :  HDSKMLIST hList - ������ ��������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��� ��������
AVP_dword 	DSKMAPI DSKM_ParList_RemoveObjectByH( HDSKMLIST hList, HDSKMLISTOBJ hListObject );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ������ � �������� ��������� �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_ParList_GetFirstObjectError
//! \brief			:	�������� ������ ������ � ������� ��������� ��� 0, ���� �������� ���
//! \return			: ������������� �������   
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : AVP_dword *pdwErrorCode	- ��������� �� ��� ������. ����� ���� 0.
AVP_dword   DSKMAPI DSKM_ParList_GetFirstObjectError( HDSKMLIST hList, AVP_dword *pdwErrorCode );


//! \fn				:  DSKMAPI DSKM_ParList_GetNextObjectError
//! \brief			:	�������� ��������� ������ � ������� ���������
//! \return			: ������������� ������� ��� 0, ���� �������� ������ ���.  
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : AVP_dword dwObjectId - ������������� ����������� �������. �� ����� ���� 0.
//! \param          : AVP_dword *pdwErrorCode	- ��������� �� ��� ������. ����� ���� 0.
AVP_dword   DSKMAPI DSKM_ParList_GetNextObjectError( HDSKMLIST hList, AVP_dword dwObjectId, AVP_dword *pdwErrorCode );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ��������� ���������� �� �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_ParList_GetObject
//! \brief			:	������ ���������� �� �������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : AVP_dword dwObjectId - ������������� �������
//! \param          : void *pvObject	- ��������� �� ����� ���������� 
//! \param          : AVP_dword *pdwObjectSize - ��������� �� ������ ������ ����������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_GetObject( HDSKMLIST hList, AVP_dword dwObjectId, void *pvObject, AVP_dword *pdwObjectSize );


//! \fn				:  DSKMAPI DSKM_ParList_GetObjectId
//! \brief			:	������ ������������� �������
//! \return			: ������������� ������� ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
AVP_dword   DSKMAPI DSKM_ParList_GetObjectId( HDSKMLIST hList, HDSKMLISTOBJ hListObject );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ������ �� ���������� �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_SetObjectProp
//! \brief			:	���������� �������� ������� �������� (DSKM_OBJ_*)
//! \return			: ��� ������
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : AVP_dword dwPropId - ������������� ��������
//! \param          : void *pvData - ����� � �������
//! \param          : AVP_dword dwDataSize - ������ ������
AVP_dword 	DSKMAPI DSKM_ParList_SetObjectProp( HDSKMLIST hList, HDSKMLISTOBJ hListObject, AVP_dword dwPropId, void *pvData, AVP_dword dwDataSize );



//! \fn				: DSKM_ParList_GetObjectProp
//! \brief			:	�������� �������� ������� �������� (DSKM_OBJ_*)
//! \return			: ��� ������
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : AVP_dword dwPropId - ������������� ��������
//! \param          : void *pvData	- ��������� �� ����� ����������
//! \param          : AVP_dword *pdwDataSize - ��������� �� ������ ������ ����������
AVP_dword 	DSKMAPI DSKM_ParList_GetObjectProp( HDSKMLIST hList, HDSKMLISTOBJ hListObject, AVP_dword dwPropId, void *ppvData, AVP_dword *pdwDataSize );


//! \fn				: DSKM_ParList_SetObjectProp
//! \brief			:	���������� �������� �������, ���������� ����������� � ��� �������
//!               ����� ������� ����� ���� ����������� ����� ����������. 
//!               ����������� ����������� ��������������� (� ������� ����������)
//!               �����! ������� ���������� ������� ��� ������������ � �������� ������ ���������!
//! \return			: ��� ������
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hListObject - ������ ��������
//! \param          : void *pvData - ����� � �������
//! \param          : AVP_dword dwDataSize - ������ ������
AVP_dword 	DSKMAPI DSKM_ParList_SetObjectHashingProp( HDSKMLIST hList, HDSKMLISTOBJ hListObject, void *pvData, AVP_dword dwDataSize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� ��������
//---------------------------------------------------------------------------------------------------------------------------


//! \fn				: DSKM_ParList_GetFirstObject
//! \brief			:	�������� ������ ������ ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_GetFirstObject( HDSKMLIST hList );


//! \fn				: DSKM_ParList_GetNextObject
//! \brief			:	�������� ��������� ������ ������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hCurrObject - ������� ������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_GetNextObject( HDSKMLIST hList, HDSKMLISTOBJ hCurrObject );


//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� ���������� �����
//---------------------------------------------------------------------------------------------------------------------------


//! \fn				: DSKM_ParList_GetFirstParam
//! \brief			:	�������� ������ �������� ������/�������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          :  HDSKMLISTOBJ hListObject - ������ ��������, ��������� �������� ����� ���������
//                     ���� 0 - ������������ ��������� ������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_GetFirstParam( HDSKMLIST hList, HDSKMLISTOBJ hListObject );


//! \fn				: DSKM_ParList_GetNextParam
//! \brief			:	�������� ��������� �������� ������/�������
//! \return			: ������ ������ (0 � ����� ��������). ��� ������ ���������� ����� DSKM_ParList_GetLastError
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : HDSKMLISTOBJ hCurrParam - ������� ��������
HDSKMLISTOBJ 	DSKMAPI DSKM_ParList_GetNextParam( HDSKMLIST hList, HDSKMLISTOBJ hCurrParam );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ������ � �������� ������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_ParList_GetLastError
//! \brief			:	������ ��� ��������� ������ �� ������
//! \return			: ��� ������
//! \param          :  HDSKMLIST hList - ������ �������� ��������
AVP_dword DSKMAPI DSKM_ParList_GetLastError( HDSKMLIST hList );


//! \fn				: DSKM_ParList_SetLastError
//! \brief			:	���������� ��� ��������� ������ �� ������
//! \return			: void DSKMAPI 
//! \param          :  HDSKMLIST hList - ������ �������� ��������
//! \param          : AVP_dword dwResult - ��� ������
void DSKMAPI DSKM_ParList_SetLastError( HDSKMLIST hList, AVP_dword dwResult );



//---------------------------------------------------------------------------------------------------------------------------
// ������� ��������� �������� ��� � ������ �������� ������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_GenerateKeyPair
//! \brief			:	������������ �������� ���� - �������� � �������� ����
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  void **ppPrivateKey - ��������� �� �������������� ����� ��������� ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwPrivateKeySize - ��������� �� �������������� ������ ������ ��������� �����
//! \param          : void **ppvPublicKey - ��������� �� �������������� ����� ��������� ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwPublicKeySize - ��������� �� �������������� ������ ������ ��������� �����
AVP_dword   DSKMAPI DSKM_GenerateKeyPair( HDSKM hDSKM, void **ppPrivateKey, AVP_dword *pdwPrivateKeySize, void **ppvPublicKey, AVP_dword *pdwPublicKeySize );


//! \fn				:  DSKMAPI DSKM_SaveKeyToKeyReg
//! \brief			:	�������� ���� � ������ ������ (������ �� �������������). 
//!       				��� ������� ������� ���������� DSKM_SignOneObjectTo*
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ���������� ��������, ��� ������� ������������ ����
//! \param          : AVP_dword dwObjectsType	- ��� ��������, ��� ������� ������������ ����
//!                   (����� ���� = 0 - ����� ������ ���� ����� ���� ����������)
//! \param          : AVP_dword dwKeyType - ��� ����� (DSKM_OTYPE_KEY_*)
//! \param          : void *pvKey - ��������� �� ����� �����
//! \param          : AVP_dword dwKeySize	- ������ ������ �����
//! \param          : const AVP_char* pszKeyRegFileName - ��� ����� �������
AVP_dword   DSKMAPI DSKM_SaveKeyToKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_dword dwKeyType, void *pvKey, AVP_dword dwKeySize, const AVP_char* pszKeyRegFileName );



//! \fn				:  DSKMAPI DSKM_RemoveKeyFromKeyReg
//! \brief			:	������� ���� �� ������� ������ (������ �� �������������). 
//!       				��� ������� ������� ����� ������� DSKM_SignOneObjectTo*
//!               ��� ������ ����� � ������� ������������ ��������� �������� �� ������ ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ���������� ��������, ��� ������� ������������ ����
//! \param          : AVP_dword dwObjectsType	- ��� ��������, ��� ������� ������������ ����
//!                   (����� ���� = 0 - ����� ������ ���� ����� ���� ����������)
//! \param          : AVP_dword dwKeyType - ��� ����� (DSKM_OTYPE_KEY_*)
//! \param          : const AVP_char* pszKeyRegFileName - ��� ����� �������
AVP_dword   DSKMAPI DSKM_RemoveKeyFromKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_dword dwKeyType, const AVP_char* pszKeyRegFileName );


//! \fn				:  DSKMAPI DSKM_GetKeyFromKeyReg
//! \brief			:	�������� ����� �� ������� ������. 
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : HDSKMLIST hObjectsList - ������ ���������� ��������, ��� ������� ������������ ����
//! \param          : AVP_dword dwObjectsType	- ��� ��������, ��� ������� ������������ ����
//!                   (����� ���� = 0 - ����� ������ ���� ����� ���� ����������)
//! \param          : AVP_dword dwKeyType - ��� ����� (DSKM_OTYPE_KEY_*)
//! \param          : void **ppvKey - ��������� �� �������������� ����� ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwKeySize - ��������� �� �������������� ������ ������ �����
//! \param          : AVP_dword *pdwKeyCount - ��������� �� ���������� ������
//! \param          : const AVP_char* pszKeyRegFileName - ��� ����� �������
AVP_dword   DSKMAPI DSKM_GetKeyFromKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_dword dwKeyType, void **ppvKey, AVP_dword *pdwKeySize, AVP_dword *pdwKeyCount, const AVP_char* pszKeyRegFileName );

//---------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ���-�������� 
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_HashObjectByName
//! \brief			:	��������� ��� �����
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  const AVP_char* pszObjectFileName - ��� ����� ��� ��������
//! \param          : void **ppvObjectHash - �������������� ���	(�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwObjectHashSize - ��������� �� �������������� ������ ����
AVP_dword	DSKMAPI DSKM_HashObjectByName( HDSKM hDSKM, const AVP_char* pszObjectFileName, void **ppvObjectHash, AVP_dword *pdwObjectHashSize );

//! \fn				: DSKM_HashObjectByBuffer
//! \brief			:	��������� ��� ��������������� �������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  void *pvBuffer - ��������� �� �����
//! \param          : AVP_dword dwBufferSize - ������ ������
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������
//                    ����� ���� 0 - ����� ���������, ��� ����� ��� ��������
//! \param          : void *pvCallBackParams	- ��������� ������� ��������
//! \param          : void **ppvObjectHash - �������������� ���	(�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwObjectHashSize - ��������� �� �������������� ������ ����
AVP_dword	DSKMAPI DSKM_HashObjectByBuffer( HDSKM hDSKM, void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams, void **ppvObjectHash, AVP_dword *pdwObjectHashSize );


//! \fn				: DSKM_HashObjectByNameUsingGivenHashBuffer
//! \brief			:	��������� ��� �����
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  const AVP_char* pszObjectFileName - ��� ����� ��� ��������
//! \param          : void *pvObjectHash - ����� ��� �������������� ���
//! \param          : AVP_dword *pdwObjectHashSize - ��������� �� �������������� ������ ����
AVP_dword	DSKMAPI DSKM_HashObjectByNameUsingGivenHashBuffer( HDSKM hDSKM, const AVP_char* pszObjectFileName, void *pvObjectHash, AVP_dword *pdwObjectHashSize );

//! \fn				: DSKM_HashObjectByBufferGivenHashBuffer
//! \brief			:	��������� ��� ��������������� �������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  void *pvBuffer - ��������� �� �����
//! \param          : AVP_dword dwBufferSize - ������ ������
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������
//                    ����� ���� 0 - ����� ���������, ��� ����� ��� ��������
//! \param          : void *pvCallBackParams	- ��������� ������� ��������
//! \param          : void *ppvObjectHash - ����� ��� �������������� ���
//! \param          : AVP_dword *pdwObjectHashSize - ��������� �� �������������� ������ ����
AVP_dword	DSKMAPI DSKM_HashObjectByBufferGivenHashBuffer( HDSKM hDSKM, void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams, void *pvObjectHash, AVP_dword *pdwObjectHashSize );


//! \fn				: DSKM_HashObjectByList
//! \brief			:	��������� ��� ������� �� ������ (�������!)
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : void **ppvObjectHash - �������������� ���	(�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwObjectHashSize - ��������� �� �������������� ������ ����
AVP_dword	DSKMAPI DSKM_HashObjectByList( HDSKM hDSKM, HDSKMLIST hObjectsList, void **ppvObjectHash, AVP_dword *pdwObjectHashSize );


//! \fn				: DSKM_HashObjectsToRegBuffer
//! \brief			:	��������� ���� �������� � ������� � ������.
//!               ������ �������������, �� �� �������������.
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType	- ��� �������� (���������������� 1-32758)
//! \param          : AVP_bool bSpecialReg - ������� ������������ �������
//! \param          : void **ppvHashRegBuffer - �������������� ��������������� ������ ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwHashRegBufferSize	- ��������� �� �������������� ������ ������� �����
AVP_dword	DSKMAPI DSKM_HashObjectsToRegBuffer( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_bool bSpecialReg, void **ppvHashRegBuffer, AVP_dword *pdwHashRegBufferSize );

//---------------------------------------------------------------------------------------------------------------------------
// ������� ������������ ������ ��������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_SignObjectsToRegFileByKey
//! \brief			:	������� ����� ������� ����� ��������, ��������� ��� ������� ���������� �������� ����
//! \return			: ��� ������  
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType	- ��� �������� (���������������� 1-32758)
//! \param          : AVP_bool bSpecialReg - ������� ������������ �������
//! \param          : void *pvPrivateKey	- �������� ���� ��� ������������ �������
//! \param          : AVP_dword dwKeySize - ������ ��������� �����
//! \param          : const AVP_char* pszObjsRegFileName - ��� ��������� ����� ������� �����
AVP_dword   DSKMAPI DSKM_SignObjectsToRegFileByKey( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_bool bSpecialReg, void *pvPrivateKey, AVP_dword dwKeySize, const AVP_char* pszObjsRegFileName );


//! \fn				:  DSKMAPI DSKM_SignObjectsToRegBufferByKey
//! \brief			:	������� ����� ������� ����� ��������, ��������� ��� ������� ���������� �������� ����
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType	- ��� �������� (���������������� 1-32758)
//! \param          : AVP_bool bSpecialReg - ������� ������������ �������
//! \param          : void *pvPrivateKey	- �������� ���� ��� ������������ �������
//! \param          : AVP_dword dwKeySize - ������ ��������� �����
//! \param          : void **ppvRegBuffer - �������������� �����	(�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwRegBufferSize - ��������� �� �������������� ������ ������
AVP_dword   DSKMAPI DSKM_SignObjectsToRegBufferByKey( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_bool bSpecialReg, void *pvPrivateKey, AVP_dword dwKeySize, void **ppvRegBuffer, AVP_dword *pdwRegBufferSize );


//! \fn				:  DSKMAPI DSKM_SignObjectsToRegFileByKeyReg
//! \brief			:	������� ����� ������� ����� ��������, ��������� ��� ������� ������ �������� ������
//!               ��� ������ ����� � ������� ������������ ��������� �������� �� ������ ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType	- ��� �������� (���������������� 1-32758)
//! \param          : AVP_bool bSpecialReg - ������� ������������ �������
//! \param          : const AVP_char* pszKeyRegFileName - ��� ����� ������� �������� ������
//! \param          : const AVP_char* pszObjsRegFileName - ��� ��������� ����� ������� �����
AVP_dword   DSKMAPI DSKM_SignObjectsToRegFileByKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_bool bSpecialReg, const AVP_char* pszKeyRegFileName, const AVP_char* pszObjsRegFileName );


//! \fn				:  DSKMAPI DSKM_SignObjectsToRegBufferByKeyReg
//! \brief			:	������� ����� ������� ����� ��������, ��������� ��� ������� ������ �������� ������
//!               ��� ������ ����� � ������� ������������ ��������� �������� �� ������ ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType	- ��� �������� (���������������� 1-32758)
//! \param          : AVP_bool bSpecialReg - ������� ������������ �������
//! \param          : const AVP_char* pszKeyRegFileName - ��� ����� ������� �������� ������
//! \param          : void **ppvRegBuffer - �������������� ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwRegBufferSize - ��������� �� �������������� ������ ������
AVP_dword   DSKMAPI DSKM_SignObjectsToRegBufferByKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, AVP_bool bSpecialReg, const AVP_char* pszKeyRegFileName, void **ppvRegBuffer, AVP_dword *pdwRegBufferSize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ������������ ������ �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_SignOneObjectToObjectByKey
//! \brief			:	��������� ���� ������ (������ � ������ ����), �������� ������� ��������������� � ���� 
//!               ��� ������������ ������������ ���������� �������� ���� 
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType - ��� ������� (DSKM_OTYPE_KEY_* ��� ����������������)
//! \param          : void *pvPrivateKey	- �������� ���� ��� ������������ �������
//! \param          : AVP_dword dwKeySize - ������ ��������� �����
AVP_dword   DSKMAPI DSKM_SignOneObjectToObjectByKey( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, void *pvPrivateKey, AVP_dword dwKeySize );


//! \fn				:  DSKMAPI DSKM_SignOneObjectToObjectByKeyReg
//! \brief			:	��������� ���� ������ (������ � ������ ����), �������� ������� ��������������� � ���� 
//!               ��� ������������ ������������ ����, ��������� � ������� �������� ������ 
//!               ��� ������ ����� � ������� ������������ ��������� �������� �� ������ ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType - ��� ������� (DSKM_OTYPE_KEY_* ��� ����������������)
//! \param          : const AVP_char* pszKeyRegFileName	- ��� ����� ������� �������� ������
AVP_dword   DSKMAPI DSKM_SignOneObjectToObjectByKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszKeyRegFileName );


//! \fn				:  DSKMAPI DSKM_SignOneObjectToSignBufferByKey
//! \brief			:	��������� ���� ������ (������ � ������), �������� ������� � �������� ����� 
//!               ��� ������������ ������������ ���������� �������� ���� 
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType - ��� ������� (DSKM_OTYPE_KEY_* ��� ����������������)
//! \param          : void *pvPrivateKey	- �������� ���� ��� ������������ �������
//! \param          : AVP_dword dwKeySize - ������ ��������� ����� 
//! \param          : void **ppvSignBuffer - �������������� ����� � �������� ������� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwSignBufferSize - ��������� �� �������������� ������ ������ � ��������
AVP_dword   DSKMAPI DSKM_SignOneObjectToSignBufferByKey( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, void *pvPrivateKey, AVP_dword dwKeySize, void **ppvSignBuffer, AVP_dword *pdwSignBufferSize );


//! \fn				:  DSKMAPI DSKM_SignOneObjectToObjectByKeyReg
//! \brief			:	��������� ���� ������ (������ � ������), �������� ������� � �������� ����� 
//!               ��� ������������ ������������ ����, ��������� � ������� �������� ������ 
//!               ��� ������ ����� � ������� ������������ ��������� �������� �� ������ ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : AVP_dword dwObjectsType - ��� ������� (DSKM_OTYPE_KEY_* ��� ����������������)
//! \param          : const AVP_char* pszKeyRegFileName	- ��� ����� ������� �������� ������
//! \param          : void **ppvSignBuffer - �������������� ����� � �������� ������� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwSignBufferSize - �������������� ������ ������ � ��������
AVP_dword   DSKMAPI DSKM_SignOneObjectToSignBufferByKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszKeyRegFileName, void **ppvSignBuffer, AVP_dword *pdwSignBufferSize );



//! \fn				:  DSKMAPI DSKM_SignOneObjectToObjectBySignBuffer
//! \brief			:	��������� ���� ������ (������ � ������), ��������� ���������� �������.
//!               ������������ ������� � ������� �� ��������������
//!               ���� ������ �������� ������, �� ������� � ���� ������������
//!               ���� ������ �������� �������, �� �������� ����� �����, ��� "������+�������"
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
//! \param          : void *pvSignBuffer - ����� � �������� ������� 
//! \param          : AVP_dword dwSignBufferSize - ������ ������ � ��������
//! \param          : void **ppvSignedBuffer - ����������� ����� (�������������� ����� pfnAlloc)
//! \param          : AVP_dword *pdwSignedBufferSize - ������ ������������ ������
AVP_dword   DSKMAPI DSKM_SignOneObjectToObjectBySignBuffer( HDSKM hDSKM, HDSKMLIST hObjectsList, void *pvSignBuffer, AVP_dword dwSignBufferSize, void **ppvSignedBuffer, AVP_dword *pdwSignedBufferSize );


//---------------------------------------------------------------------------------------------------------------------------
// ������� ��������� ��������, �������� ������� ������ �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				:  DSKMAPI DSKM_CompareObjectsIgnoreSign
//! \brief			:	�������� ������ ��� ������� �� ������
//                C����������� ��� ������ ������, ����� ������� � ��������� �����
//! \return			: ��� ������ - DSKM_ERR_OBJECTS_NOT_EQUAL, ���� ������� �� ���������  
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ ��������
AVP_dword   DSKMAPI DSKM_CompareObjectsIgnoreSign( HDSKM hDSKM, HDSKMLIST hObjectsList );


//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� �������� ����� ������� ���-��������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_CheckObjectsUsingHashRegsFolder
//! \brief			:	��������� ������� ����� ������� �����, ����������� � �������� �����
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� �������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszRegFilesFolder	- ����� ���������� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingHashRegsFolder( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszRegFilesFolder );


//! \fn				: DSKM_CheckObjectsUsingHashRegFile
//! \brief			:	��������� ������� ����� ���������� ������ �����
//                ������� ������� ������ ���� ��� ��������� (����� DSKM_CheckObjectsUsingInsideSign*)
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� �������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszRegFileName	- ���� �������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingHashRegFile( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszRegFileName );


//! \fn				: DSKM_CheckObjectsUsingHashRegsAssoc
//! \brief			:	��������� ������� ����� ������� �����, �������� ����� ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� ��������, ���������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingHashRegsAssoc( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType );


//! \fn				: DSKM_CheckObjectsUsingBufferedHashReg
//! \brief			:	��������� �������, ��������� �������������� ������.
//                ������� ������� ������ ���� ��� ��������� (����� DSKM_CheckObjectsUsingInsideSign*)
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : HDSKMLIST hObjectsList - ������ �������� ��� �������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : void *pvBuffer - ��������� �� �����
//! \param          : AVP_dword dwBufferSize - ������ ������
//! \param          : pfnDSKM_GetBuffer_CallBack pfnCallBack - ������� �������� ������
//                    ����� ���� 0 - ����� ���������, ��� ����� ��� ��������
//! \param          : void *pvCallBackParams	- ��������� ������� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingBufferedHashReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, void *pvBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pfnCallBack, void *pvCallBackParams );


//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� �������� ����� �������� ����� ��������
//---------------------------------------------------------------------------------------------------------------------------


//! \fn				: DSKM_PrepareRegsSet
//! \brief			:	��������� ����� �������� (�������� ����� ������� DSKM_ParList_Add * Reg)
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� ��������, ���������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
AVP_dword  	DSKMAPI DSKM_PrepareRegsSet( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType );


//! \fn				: DSKM_CheckObjectsUsingRegsSet
//! \brief			:	��������� �������, ��������� �������������� ����� �������� (DSKM_PrepareRegsSet)
//! \return			: ��� ������ 
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� ��������, ���������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingRegsSet( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType );


//! \fn				:  DSKMAPI DSKM_IsRegsSetPrepared
//! \brief			:	��������� - ����������� �� ����� �������� � ��������
//! \return			: ��� ������ 
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : HDSKMLIST hObjectsList - ������ �������� ��� ��������, ���������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//!										���� dwObjectsType == 0 - ��� ������������ ����� ���������� (���� ������)
//!										���� dwObjectsType != 0 - ������ �������������� ������ ��� ������� ���� 
//!										���� dwObjectsType == 0 - ������ ������ �������������� ������ ������ ���� 
AVP_dword   DSKMAPI DSKM_IsRegsSetPrepared( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType );

//---------------------------------------------------------------------------------------------------------------------------
// ������� �������� �������� ����� ������� � ����� �������
//---------------------------------------------------------------------------------------------------------------------------

//! \fn				: DSKM_CheckObjectsUsingInsideSignAndKeysFolder
//! \brief			:	��������� ������� � �������� � ����� ����, ��������� ��� ������ ������ ���������� �����
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : HDSKMLIST hObjectsList - ������ �������� ��� �������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszRegFilesFolder	- ����� ���������� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingInsideSignAndKeysFolder( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszRegFilesFolder );



//! \fn				: DSKM_CheckObjectsUsingInsideSignAndKeysAssoc
//! \brief			:	��������� ������� � �������� � ����� ����, ��������� ��� ������ ������ �������� ����������
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� ��������, ���������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszRegFilesFolder	- ����� ���������� ��������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingInsideSignAndKeysAssoc( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType );



//! \fn				: DSKM_CheckObjectsUsingInsideSignAndKeyReg
//! \brief			:	��������� ������� � �������� � ����� ����, ��������� ���������� ���� ������� ������.
//! \return			: ��� ������
//! \param          :  HDSKM hDSKM - �������� ����������. 
//! \param          :  HDSKMLIST hObjectsList - ������ �������� ��� �������� � ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszKeyRegFileName	- ���� ������� ������
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingInsideSignAndKeyReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszKeyRegFileName );


//---------------------------------------------------------------------------------------------------------------------------
// ��������������� �������
//---------------------------------------------------------------------------------------------------------------------------


//! \fn				: DSKM_SaveTypeAssociationToFile
//! \brief			:	��������� ���������� "object/key params => objects type" � ����
//! \return			: DSKMAPI 
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : HDSKMLIST hObjectsList - ������ ����������
//! \param          : AVP_dword dwObjectsType	- ��� ��������
//! \param          : const AVP_char* pszAssocFileName - ��� ����� ���������� (���� �� �������������)
AVP_dword  	DSKMAPI DSKM_SaveTypeAssociationToFile(  HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, const AVP_char* pszAssocFileName );



//! \fn				:  DSKMAPI DSKM_DumpReg
//! \brief			:	������� ������ � ��������� ����.
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : const AVP_char* pszRegFileName - ��� ����� �������
//! \param          : const AVP_char* pszOutFileName - ��� ��������� �����
AVP_dword   DSKMAPI DSKM_DumpReg( HDSKM hDSKM, const AVP_char* pszRegFileName, const AVP_char* pszOutFileName );



//! \fn				: DSKM_RandomFillBuffer
//! \brief			:	��������� ����� ���������� �������
//! \return			: ��� ������
//! \param          : HDSKM hDSKM - �������� ����������. 
//! \param          : void *pBuffer - ����� ��� ����������
//! \param          : AVP_dword dwBufferSize - ������ ������
AVP_dword	DSKMAPI DSKM_RandomFillBuffer( HDSKM hDSKM, void *pBuffer, AVP_dword dwBufferSize );



//! \fn				: * DSKM_Alloc
//! \brief			:	����������� ������, ��������� ������� ������������� ������ ���������� ��� �������������
//! \return			: ��������� �� ������������� �����
//! \param          : AVP_int iSize - ������
void * DSKMAPI DSKM_Alloc( AVP_int iSize );


//! \fn				: DSKM_Free
//! \brief			:	������� ������, ��������� ������� ������������� ������ ���������� ��� ������������� 
//! \return			: void
//! \param          : void *pvBuffer - ����� ��� ��������
void DSKMAPI DSKM_Free( void *pvBuffer );

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
#if defined( __cplusplus )
}
#endif


#endif //__dskm_h__
