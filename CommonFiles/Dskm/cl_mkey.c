/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	cl_mkey.c
*		\brief	
*		
*		\author Victor Matioshenkov
*		\date	6/15/2005 1:36:48 PM
*		
*		Example:	
*		
*		
*		
*/		

#include "dskm.h"
#include "dskmi.h"
#include "cl_util.h"

#if defined( _WIN32 ) && !defined( _WIN64 )
#pragma data_seg(".text")
#endif

#ifdef DSKM_EMUL
AVP_byte DSKM[96] = {
	0x4B, 0x4C, 0x72, 0x67, 0x01, 0x00, 0xFE, 0x7F, 0x4B, 0x4C, 0x73, 0x77, 0x02, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0xF9, 0x35, 0xDD, 0x1B, 0x46, 0x00, 0x4B, 0x4C, 0x73, 0x77, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE1, 0x4B, 0x4C, 0x73, 0x77, 0x00, 0x00, 0xAD, 0xAD,
	0x01, 0xFB, 0x00, 0xFC, 0x80, 0xE3, 0x03, 0xFC, 0xFD, 0x00, 0x01, 0xF3, 0x09, 0x1F, 0xFF, 0x01,
	0xDC, 0x3D, 0x1E, 0x2A, 0x0A, 0xF3, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xF0, 0x11, 0x08, 0xEF,
	0x00, 0x1E, 0x09, 0xFC, 0x7F, 0xEF, 0x5F, 0x00, 0xE3, 0xB4, 0x71, 0xD6, 0x18, 0xFF, 0x00, 0x00,
};
#else
/*
AVP_byte DSKM[159] = {
	0x4B, 0x4C, 0x72, 0x67, 0x01, 0xFE, 0xFF, 0x7F, 0x4B, 0x4C, 0x73, 0x77, 0x02, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x8A, 0xE0, 0x4A, 0xC7, 0x85, 0x00, 0x4B, 0x4C, 0x73, 0x77, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE1, 0x4B, 0x4C, 0x73, 0x77, 0x00, 0x00, 0xAD, 0xAD,
	0x01, 0xFB, 0x00, 0xFC, 0x80, 0xE3, 0x03, 0xFC, 0xFD, 0x16, 0x01, 0xF3, 0x09, 0xFF, 0xFF, 0x01,
	0xD9, 0x2E, 0x1E, 0x2A, 0x40, 0x00, 0x78, 0x41, 0x41, 0x65, 0xA5, 0x78, 0xDF, 0x45, 0x92, 0xFF,
	0xFF, 0x78, 0xFD, 0x2E, 0x98, 0x07, 0x90, 0x6C, 0x37, 0xFB, 0x18, 0x6A, 0x5D, 0xC0, 0xC8, 0xA9,
	0x82, 0xFF, 0xFF, 0x23, 0x15, 0x17, 0xC0, 0x06, 0x45, 0x20, 0x11, 0xEA, 0x54, 0x4F, 0x1A, 0xCF,
	0xC0, 0x3E, 0x54, 0xFF, 0xFF, 0xC8, 0x37, 0x8F, 0x31, 0x12, 0x9F, 0xDD, 0x9A, 0x6F, 0x2D, 0x1F,
	0xA8, 0x18, 0xEF, 0x5F, 0x38, 0x3F, 0xFC, 0xB6, 0x5C, 0x15, 0xE1, 0xAA, 0x6B, 0xC4, 0xB5, 0x1E,
	0x09, 0xFC, 0xFF, 0x7F, 0xF4, 0x02, 0x00, 0xAD, 0x51, 0x8D, 0xE7, 0x11, 0xFF, 0x00, 0x00
};
*/
AVP_byte DSKM[120] = {
	0x4B, 0x4C, 0x72, 0x67, 0x01, 0xFE, 0xFF, 0x7F, 0x4B, 0x4C, 0x73, 0x77, 0x00, 0x00, 0xAD, 0xAD,
	0x01, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x16, 0x01, 0x01, 0x00, 0x00,
	0x09, 0x01, 0x48, 0x53, 0x1E, 0x2A, 0x40, 0x00, 0x53, 0xED, 0xEF, 0x76, 0x98, 0xE0, 0xAB, 0xD9,
	0x1F, 0x95, 0xB3, 0x30, 0x2F, 0xE8, 0x77, 0x35, 0x85, 0x11, 0x9A, 0x21, 0x37, 0x7D, 0x0A, 0x15,
	0x15, 0x88, 0x62, 0x87, 0xE6, 0x46, 0x1F, 0x65, 0x44, 0x6C, 0xED, 0xD2, 0x8B, 0x7F, 0xF4, 0x79,
	0x32, 0x94, 0x87, 0x96, 0x8A, 0x6A, 0xCD, 0xA8, 0xC8, 0x45, 0x6B, 0x52, 0xEE, 0xDA, 0x6A, 0x0D,
	0x09, 0xD9, 0x3A, 0xB7, 0x6D, 0xB1, 0xA0, 0x21, 0x01, 0x00, 0x1E, 0x09, 0xFC, 0xFF, 0x7F, 0x00,
	0x01, 0x00, 0x00, 0x09, 0xB0, 0x49, 0xCE, 0xF5
};

#endif

void      *g_pDSKMData = DSKM;
AVP_dword g_dwDSKMDataSize = sizeof(DSKM);

AVP_byte DSKM_E[] = {
	0x4B, 0x4C, 0x72, 0x67, 0x01, 0x00, 0x00, 0x00, 0x4B, 0x4C, 0x73, 0x77, 0x02, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x75, 0x98, 0xDB, 0x3F, 0x9F, 0x00, 0x4B, 0x4C, 0x73, 0x77, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE1, 0x4B, 0x4C, 0x73, 0x77, 0x00, 0x00, 0xAD, 0xAD,
	0x01, 0xFB, 0x00, 0xFC, 0x10, 0xC6, 0x03, 0xFC, 0x03, 0xF7, 0x28, 0x09, 0xF4, 0x38, 0xC0, 0x00,
	0xEF, 0x09, 0x05, 0xFC, 0xF3, 0x70, 0x53, 0x7A, 0x57, 0xBA, 0xE9, 0xF3, 0x01, 0xE6, 0x71, 0x12,
	0xF6, 0xA0, 0x2E, 0xC0, 0xF3, 0x02, 0xF3, 0xF8, 0x0B, 0xC8, 0xF3, 0x02, 0x73, 0x01, 0x1C, 0x8B,
	0x40, 0xF3, 0x04, 0xE6, 0xF8, 0x0B, 0xBE, 0x9E, 0xDB, 0xF3, 0x2D, 0x54, 0xF3, 0x38, 0xF3, 0x06,
	0xE6, 0xF8, 0x0B, 0x07, 0xF3, 0xF8, 0x0B, 0x82, 0xF1, 0x08, 0xF3, 0xF8, 0x0B, 0x81, 0xF3, 0xF8,
	0x0A, 0x0A, 0xF3, 0xBD, 0x07, 0x39, 0x3E, 0x05, 0x3D, 0xF3, 0x0B, 0xF3, 0xBE, 0xB8, 0x6E, 0xFD,
	0xB7, 0x8D, 0xF3, 0x0C, 0xF3, 0xF8, 0x0B, 0x0D, 0xCC, 0xF8, 0x0B, 0x0E, 0xF3, 0xF8, 0x0B, 0x0F,
	0xCF, 0xF1, 0xF3, 0xE0, 0xEA, 0xAE, 0x5A, 0xF3, 0x10, 0xF3, 0xF6, 0xF3, 0xE9, 0x0B, 0xAB, 0xDE,
	0xF3, 0xFF, 0xCA, 0x33, 0x78, 0x11, 0xFF, 0x00, 0x00
};

void      *g_pDSKMEData = DSKM_E;
AVP_dword g_dwDSKMEDataSize = sizeof(DSKM_E);


#if defined( _WIN32 )
#pragma data_seg()
#endif
