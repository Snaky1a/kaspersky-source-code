/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	ds_chkbf.c
*		\brief	
*		
*		\author Victor Matioshenkov
*		\date	6/23/2005 11:26:27 AM
*		
*		Example:	
*		
*		
*		
*/		


#include "dskm.h"
#include "dskmi.h"



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
AVP_dword  	DSKMAPI DSKM_CheckObjectsUsingBufferedHashReg( HDSKM hDSKM, HDSKMLIST hObjectsList, AVP_dword dwObjectsType, void *pBuffer, AVP_dword dwBufferSize, pfnDSKM_GetBuffer_CallBack pCallBack, void *pCallBackParams ) {
	DSKM_TRY {
		if ( !DSKMAllocator || !DSKMAllocator ) {
			return DSKM_ERR_NOT_INITIALIZED;
		}
		
		if ( hObjectsList && hDSKM && pBuffer && dwBufferSize ) {
			AVP_bool bErrProcessed = 0;
			HDATA hRegData = 0;
			HDATA hCollectionData = DATA_Add( 0, 0, DSKM_OBJ_TYPES_PROP_ID, 0, 0 );
			HPROP hCollectionProp = DATA_Find_Prop( hCollectionData, 0, 0 );
			AVP_dword dwResult = DSKM_ERR_INVALID_OBJTYPE;
			dwObjectsType = DSKM_CheckObjectTypeByAssoc( hDSKM, hObjectsList, (HDATA)hObjectsList, dwObjectsType, hCollectionData );
			if ( dwObjectsType && PROP_Arr_Count(hCollectionProp) > 0 ) {
				int i = 0;
				int c = PROP_Arr_Count( hCollectionProp );
				dwResult = DSKM_ERR_REG_NOT_FOUND;
				for ( ; i<c; i++ ) {
					AVP_dword dwPropVal;
					PROP_Arr_Get_Items( hCollectionProp, i, &dwPropVal, sizeof(dwPropVal) );
					dwResult = DSKM_DeserializeRegBuffer( hDSKM, pBuffer, dwBufferSize, pCallBack, pCallBackParams, dwObjectsType, &hRegData );
					if ( DSKM_OK(dwResult) ) 
						break;
				}
			}
			if ( DSKM_OK(dwResult) ) {
				HDATA hObjects = DSKM_CopyObjectsTree( (HDATA)hObjectsList );
				dwResult = DSKM_ERR_DATA_PROCESSING;
				
				if ( hObjects ) {
					dwResult = DSKM_CheckObjectsByHashRegData( hDSKM, hObjects, hRegData );

					if ( DATA_Get_First(hObjects, 0) )
						dwResult = DSKM_ERR_NOT_ALL_OBJECTS_FOUND; 

					DSKM_ProcessObjectsError( (HDATA)hObjectsList, hObjects, 0 );
					bErrProcessed = 1;

					DATA_Remove( hObjects, 0 );
				}
				DATA_Remove( hRegData, 0 );
			}
			DATA_Remove( hCollectionData, 0 );

			if ( DSKM_NOT_OK(dwResult) && !bErrProcessed )
				DSKM_ProcessObjectsError( (HDATA)hObjectsList, 0, dwResult );
			return dwResult;
		}
		
		return DSKM_ERR_INVALID_PARAMETER;
	}
	DSKM_EXCEPT
}
