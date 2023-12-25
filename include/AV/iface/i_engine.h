// AVP Prague stamp begin( Interface header,  )
// -------- Wednesday,  10 August 2005,  09:55 --------
// File Name   -- (null)i_engine.c
// Copyright � Kaspersky Labs 1996-2004.
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __i_engine__3586a210_b2c2_4130_b9f4_59d900730341 )
#define __i_engine__3586a210_b2c2_4130_b9f4_59d900730341
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
// AVP Prague stamp end



#include <Prague/pr_vtbl.h>

// AVP Prague stamp begin( Interface comment,  )
// Engine interface implementation
// Short comments -- ������� ��������� ��������� ��������.//eng:Generic interface for object processing.
//    ��������� ���������� �������� ������� � ������ ��������� ������� ��������.
//    ������ ��� ���������� ��� ������������ ������������� ����, ��� � ������������ ��������.
// AVP Prague stamp end



// AVP Prague stamp begin( Interface menonic identificator,  )
#define IID_ENGINE  ((tIID)(62005))
// AVP Prague stamp end



// AVP Prague stamp begin( Interface typedefs,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface constants,  )

// npENGINE
// ���������� ����������� ������� ��������������� �������.//eng:Named property extension for object under processing.
// ����������� ��������� ���� ��������������� ������� ��� �����������
#define npENGINE_VIRTUAL_OBJECT_NAME   ((tSTRING)("npENGINE_VIRTUAL_OBJECT_NAME")) // ��� ���������� �������� "����������� ��� �������".//eng:Name of string property "Virtual object name".
#define npENGINE_INTEGRAL_PARENT_IO_hOBJECT ((tSTRING)("npENGINE_INTEGRAL_PARENT_IO")) // ��� �������� "������������ ��������"
#define npENGINE_OBJECT_READONLY_tBOOL ((tSTRING)("npENGINE_OBJECT_READONLY")) // ��� BOOL �������� "������ � ������ ����������".//eng:Name of BOOL property "Object readonly".
#define npENGINE_OBJECT_DETECT_STATE_tDWORD ((tSTRING)("npENGINE_OBJECT_DETECT_STATE")) // ��� DWORD �������� ���������������� (� ������ ������� � ��������)
#define npENGINE_OBJECT_DETECT_COUNTER_tDWORD ((tSTRING)("npENGINE_OBJECT_DETECT_COUNTER_tDWORD")) // ��� DWORD �������� �����������
#define npENGINE_OBJECT_SESSION_hOBJECT ((tSTRING)("npENGINE_OBJECT_SESSION_hOBJECT")) // ��� �������� "���������� ������"
#define npENGINE_OBJECT_READONLY_tERROR ((tSTRING)("npENGINE_OBJECT_READONLY_tERROR")) // ��� tQWORD �������� "������ � ������ ���������� �� �������...".
#define npENGINE_OBJECT_READONLY_hOBJECT ((tSTRING)("npENGINE_OBJECT_READONLY_hOBJECT")) // ��� tQWORD �������� "������ � ������ ���������� �� �������...".
#define npENGINE_OBJECT_PARAM_ACTION_CLASS_MASK_tDWORD ((tSTRING)("npENGINE_OBJECT_PARAM_ACTION_CLASS_MASK_tDWORD")) // ��� tDWORD ���������  "����� ������� ��������".
#define npENGINE_OBJECT_OBTAINED_TRANSFORMER_NAME ((tSTRING)("npENGINE_OBJECT_OBTAINED_TRANSFORMER_NAME")) // ��� ���������  "��� ������������� ���������������".
#define npENGINE_OBJECT_TRANSFORMER_NAME ((tSTRING)("npENGINE_OBJECT_TRANSFORMER_NAME")) // ��� ���������  "��� ���������������".
#define npENGINE_OBJECT_EXECUTABLE_PARENT_IO_hOBJECT ((tSTRING)("npENGINE_OBJECT_EXECUTABLE_PARENT_IO_hOBJECT")) // ��� �������� "����������� ��������".
#define npENGINE_OBJECT_SKIP_THIS_ONE_tBOOL ((tSTRING)("npENGINE_OBJECT_SKIP_THIS_ONE_tBOOL")) // ��� �������� "���������� ��������� ����� �������".
#define npENGINE_OBJECT_SET_WRITE_ACCESS_tERROR ((tSTRING)("npENGINE_OBJECT_SET_WRITE_ACCESS_tERROR")) // ��� �������� "������ ������������ �� ������".

// ENGINE_DETECT
// �������������� ������� ������, �������������� � ��������.//eng:Associated with object info IDs.
// ��������������� ������ �������� ����� ����� GetAssociatedInfo �� ����� ��������� ���������.
// //eng:Associated data are available through GetAssociatedInfo method during message processing.
#define ENGINE_DETECT_NAME             ((tDWORD)(2)) // ��� ��������������.//eng:Detection name.
#define ENGINE_DETECT_DANGER           ((tDWORD)(3)) // ����� ���������.//eng:Danger flags.
#define ENGINE_DETECT_TYPE             ((tDWORD)(4)) // ��� ��������������.//eng:Detection type.
#define ENGINE_DETECT_BEHAVIOUR        ((tDWORD)(5)) // ��� ��������������.//eng:Detection type.
#define ENGINE_DETECT_DISINFECTABILITY ((tDWORD)(6)) // ����������� ��������.//eng:Disinfectability.
#define ENGINE_DETECT_CERTANITY        ((tDWORD)(7)) // ������� ����������� ��������������.//eng:Detection certanity.
#define ENGINE_OBTAINED_OS_NAME        ((tDWORD)(100)) // ��� ������������ ��������� �������.//eng:Obtained object system name.
#define ENGINE_REOPEN_DATA             ((tDWORD)(101)) // ������ ��� ������� ���������� �������� ������� � ��������.

// ENGINE_EXT
// �������������� ������� ����������� �������.//eng:Extended info IDs.
// ���������� �������� hENGINE �������� ����� ����� GetExtendedInfo.
// //eng:Extended properties of hENGINE are available through GetExtendedInfo method.
#define ENGINE_EXT_DETECT_TYPE_BIT_NAME_ANSI ((tDWORD)(1)) // ��� ���� ��������������.//eng:Detection type name.

// ENGINE_DETECT_TYPE
// ������� ����� ����� ��� ��������������� ���������� ENGINE_DETECT_TYPE.//eng: Type bit masks for ENGINE_DETECT_TYPE.
// ��� ��������������. �������� ������� ����� ���������� �����.
// ���� ��� �������������� �� ������������� �����������������, ��� ���� �������������� ����� ��������� ����� ����� GetExtendedInfo.
// //eng:Detection type.
//
#define ENGINE_DETECT_TYPE_UNDEFINED   ((tDWORD)(0)) //
#define ENGINE_DETECT_TYPE_VIRWARE     ((tDWORD)(1)) //
#define ENGINE_DETECT_TYPE_TROJWARE    ((tDWORD)(2)) //
#define ENGINE_DETECT_TYPE_MALWARE     ((tDWORD)(3)) //
#define ENGINE_DETECT_TYPE_ADWARE      ((tDWORD)(4)) //
#define ENGINE_DETECT_TYPE_PORNWARE    ((tDWORD)(5)) //
#define ENGINE_DETECT_TYPE_RISKWARE    ((tDWORD)(6)) //
#define ENGINE_DETECT_TYPE_XFILES      ((tDWORD)(20)) //
#define ENGINE_DETECT_TYPE_SOFTWARE    ((tDWORD)(21)) //
#define ENGINE_DETECT_TYPE_UNDETECT    ((tDWORD)(30)) //

// ENGINE_DETECT_DISINFECTABILITY
// ��������� ��� ENGINE_DETECT_DISINFECTABILITY.//eng:Enum constants for ENGINE_DETECT_DISINFECTABILITY.
// ����������� ��������.//eng:Disinfectability.
#define ENGINE_DETECT_DISINFECTABILITY_UNKNOWN ((tDWORD)(0)) // ����������� �������� ���� �� ����������.//eng:Disinfectability unknown.
#define ENGINE_DETECT_DISINFECTABILITY_NO ((tDWORD)(1)) // �������� ���� ����������.//eng:Non disinfectable.
#define ENGINE_DETECT_DISINFECTABILITY_YES ((tDWORD)(2)) // �������� ���� ��������.//eng:Disinfectable.
#define ENGINE_DETECT_DISINFECTABILITY_YES_BY_DELETE ((tDWORD)(3)) // �������� ���� �������� ������ � ��������//eng:Disinfect by delete.
#define ENGINE_DETECT_DISINFECTABILITY_CLEAN ((tDWORD)(4)) // �� �����. �������� ���� �� ����� ������.

// ENGINE_DETECT_CERTANITY
// ��������� ��� ENGINE_DETECT_CERTANITY.//eng:Enum constants for ENGINE_DETECT_CERTANITY.
// ������� ����������� ��������������.//eng:Detection certanity.
#define ENGINE_DETECT_CERTANITY_SURE   ((tDWORD)(1)) // ������ ���������� ����.
#define ENGINE_DETECT_CERTANITY_PARTIAL ((tDWORD)(2)) // ��������� ���������� ����.
#define ENGINE_DETECT_CERTANITY_HEURISTIC ((tDWORD)(3)) // ����������� ������������� �������.
#define ENGINE_DETECT_CERTANITY_PROBABLY ((tDWORD)(4)) // ��������� ���������� ����.

// ENGINE_DETECT_DANGER
// ��������� ��� ENGINE_DETECT_DANGER.//eng:Enum constants for ENGINE_DETECT_DANGER.
// ����� ���������.//eng:Danger flags.
#define ENGINE_DETECT_DANGER_HIGH      ((tDWORD)(0)) // ��������� ����������� ���.
#define ENGINE_DETECT_DANGER_MEDIUM    ((tDWORD)(1)) // ��������� ���, ����������� ������������������� ������.
#define ENGINE_DETECT_DANGER_LOW       ((tDWORD)(2)) // ��������� ��� ��������� ���������, ������� ������� ������������
#define ENGINE_DETECT_DANGER_INFORMATIONAL ((tDWORD)(3)) //

//  Bitfield constants for ENGINE_DB_STATE
// ��������� ��� �������� DB_STATE.
// -
#define cENGINE_DB_STATE_FUNCTIONAL    ((tDWORD)(0x1)) // ������ ����� � ������.

// Types of ENGINE Actions
// ��������� ����� ��������
// ���� �������� ��� ��������� Action-����������. pmc_ENGINE_ACTION
#define ENGINE_ACTION_TYPE_NO_ACTION   ((tDWORD)(0)) // ��������������� ���
#define ENGINE_ACTION_TYPE_SET_OF_ACTIONS ((tDWORD)(1)) // ��������� ����� ��������
#define ENGINE_ACTION_TYPE_PROCESS_OS_ON_IO ((tDWORD)(2)) // �� ������� ������� �������� ����� OS
#define ENGINE_ACTION_TYPE_CONVERT_IO  ((tDWORD)(3)) // �� ������� ������� ���������� ������� ��������������� IO
#define ENGINE_ACTION_TYPE_SWITCH_BY_PROPERTY ((tDWORD)(4)) // ������� � �������� ���������������� �������� ���������� ��������.
#define ENGINE_ACTION_TYPE_SUBENGINE_PROCESS ((tDWORD)(5)) // ������ ������ �� ��������� ������������ ���������
#define ENGINE_ACTION_TYPE_DISINFECT   ((tDWORD)(6)) // ���������� �������� �����
#define ENGINE_ACTION_TYPE_SECTOR_OVERWRITE ((tDWORD)(7)) // ������������ ������ ������� �� ������ ��� ����������.

// Predefined Classes of ENGINE Actions
// ��������� ������� ��������
// ����� ������������ ��� ����������� ������ �������� � ���������� �����������.
#define ENGINE_ACTION_CLASS_VIRUS_SCAN ((tDWORD)(0x00010000)) // ����� �������
#define ENGINE_ACTION_CLASS_VIRUS_HEURISTIC ((tDWORD)(0x00020000)) // ����� ������� ������������� �������
#define ENGINE_ACTION_CLASS_ARCHIVE    ((tDWORD)(0x00000001)) // ��������� ������
#define ENGINE_ACTION_CLASS_MAIL_DATABASE ((tDWORD)(0x00000002)) // ��������� �������� ����.
#define ENGINE_ACTION_CLASS_MAIL_PLAIN ((tDWORD)(0x00000004)) // ��������� ��������� �������
#define ENGINE_ACTION_CLASS_ARCHIVE_SFX ((tDWORD)(0x00000008)) // ��������� ���������������������� ������
#define ENGINE_ACTION_CLASS_OLE_STREAM ((tDWORD)(0x00000010)) // ��������� OLE �������
#define ENGINE_ACTION_CLASS_OLE_EMBEDDED ((tDWORD)(0x00000020)) // ��������� OLE ��������
#define ENGINE_ACTION_CLASS_MODULES_IN_PROCESS ((tDWORD)(0x00000200)) // ��������� ������� ������� � ������ ���������
#define ENGINE_ACTION_CLASS_PACKED     ((tDWORD)(0x00001000)) // ��������� ����������� ��������
#define ENGINE_ACTION_CLASS_OBJECT_MODIFY ((tDWORD)(0x10000000)) // ���������, ��������������� ����������� �������
#define ENGINE_ACTION_CLASS_ALL_FILES  ((tDWORD)(0x08000000)) // ����������� ����� - ��� ������������� ����� � IChecker. ������ ���� ������� ���� ������������ IsProgram() ��� ����������.
#define ENGINE_ACTION_CLASS_SMART_MASK  ((tDWORD)(0x04000000)) // ����������� ����� - ��� ������������� ����� � IChecker. ������ ���� ������� ���� ������������ IsProgram() ��� ����������.

// Flags of ENGINE Actions
// Flags of ENGINE Actions
// ������������ ��������� ��������� ��������
#define ENGINE_ACTION_FLAG_NOT_REQUIRED ((tDWORD)(0x00000001)) // �������� �� ����������� ������ ���� ���������
#define ENGINE_ACTION_FLAG_ERROR_NOT_CRITICAL ((tDWORD)(0x00000002)) // ������ ���������� �������� �� �������� ���������
#define ENGINE_CONFIGURATION_REQUIRED_VERSION ((tDWORD)(3)) //  --
// AVP Prague stamp end



#define CHECK_ACTION_CLASS_EXCLUSIVE(cls,mask)  ( (cls & (mask)) && !(cls & ~(mask)) )


// AVP Prague stamp begin( Interface defined messages,  )

// message class
//    msg_id == ��� ��������
//    send-point == �������������� ������. (������� �� ����)
//    ctx == hENGINE
//    � ������� - tDWORD ����� ��������.
//
//    ���������� ������ � ��� ������, ���� �������� �� ����� ������. ��. pm_ENGINE_IO_OPTIONS_ACTION_CLASS_MASK.
//
//    ���� ���������� errENGINE_ACTION_SKIP - �������� ����� ���������.
#define pmc_ENGINE_ACTION 0xffe6a144 // ��������� Action- ����������.

	#define pm_ENGINE_ACTION_NO_ACTION 0x00000000 // (0) -- ������ �������� - ��� ���������� �� ������.
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class
	//

	#define pm_ENGINE_ACTION_SET_OF_ACTIONS 0x00000001 // (1) -- ��������� ����� ��������
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

	#define pm_ENGINE_ACTION_PROCESS_OS_ON_IO 0x00000002 // (2) -- �� ������� ������� �������� ����� OS
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

	#define pm_ENGINE_ACTION_CONVERT_IO 0x00000003 // (3) -- �� ������� ������� ���������� ������� ��������������� IO
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

	#define pm_ENGINE_ACTION_SWITCH_BY_PROPERTY 0x00000004 // (4) -- ������� � �������� ���������������� �������� ���������� ��������.
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

	#define pm_ENGINE_ACTION_SUBENGINE_PROCESS 0x00000005 // (5) -- ������ ������ �� ��������� ������������ ���������
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

	#define pm_ENGINE_ACTION_DISINFECT 0x00000006 // (6) -- ���������� �������� �����
	// context comment
	//    hENGINE
	//
	// data content comment
	//    Action class

// message class
//    ������������� �� ����� �������������.
//    � ��������� ctx - hENGINE.
#define pmc_ENGINE_OPTIONS 0x84538783 // ������ �������� ��������.//eng:General engine options request.

	#define pm_ENGINE_OPTIONS_USE_MULTITHREAD_DRIVER 0x00001000 // (4096) -- ������ ������ ������������� �������������� ��������
	// context comment
	//    hENGINE
	// data content comment
	//    tBOOL

	#define pm_ENGINE_OPTIONS_SEND_LOAD_RECORD_MESSAGE 0x00001001 // (4097) -- ������ ������ ������� �������� � ������ ����������� �������
	// context comment
	//    hENGINE
	// data content comment
	//    tBOOL

	#define pm_ENGINE_OPTIONS_SEND_MT_DEBUG_MESSAGE 0x00001002 // (4098) -- ������ �� ������� ��������� pm_ENGINE_IO_OUTPUT_MT_DEBUG
	// context comment
	//    hENGINE
	// data content comment
	//    tBOOL

	#define pm_ENGINE_OPTIONS_USE_SIGN_CHECK 0x00001003 // (4099) -- ������ ������ �������� �������
	// context comment
	//    hENGINE
	// data content comment
	//    tBOOL
	//

// message class
//    Usually hIO in obj parameter.
#define pmc_ENGINE_IO 0x688c733f // Main notification class for processing.

	#define pm_ENGINE_IO_BEGIN 0x00001001 // (4097) -- ������ ������ ��������� io.
	// context comment
	//    engine
	// data content comment
	//    -
	//

	#define pm_ENGINE_IO_DONE 0x00001002 // (4098) -- ����� ������ ��������� io.
	// context comment
	//    engine
	// data content comment
	//    � ������� - tERROR ����� ���������.
	//

	#define pm_ENGINE_IO_OS_ENTER 0x00001003 // (4099) -- Enter OS for object enumeration and processing (archives)
	// context comment
	//    engine
	// data content comment
	//    -
	//

	#define pm_ENGINE_IO_OS_LEAVE 0x00001004 // (4100) -- ����� ������ ��������� os.
	// context comment
	//    engine
	//
	// data content comment
	//    � ������� - tERROR ����� ���������.
	//

	#define pm_ENGINE_IO_SUB_IO_ENTER 0x00001005 // (4101) -- Enter Sub IO processing (packers)
	// context comment
	//    engine
	// data content comment
	//    -

	#define pm_ENGINE_IO_SUB_IO_LEAVE 0x00001006 // (4102) -- Exit Sub IO processing (packers)
	// context comment
	//    engine
	// data content comment
	//    ����� ������ ��������� ������������ io.

	#define pm_ENGINE_IO_DETECT 0x00001007 // (4103) -- ��������� �����������.
	// context comment
	//    hENGINE- ������, ������� �������� �����������
	// data content comment
	//    not used

	#define pm_ENGINE_IO_DISINFECTED 0x00001008 // (4104) -- Disinfection. Details in npENGINE_... properties.
	// context comment
	//    hENGINE- ������, ������� �������� �����������
	// data content comment
	//    not used

	#define pm_ENGINE_IO_DISINFECTION_FAILED 0x00001009 // (4105) -- Disinfection. Details in npENGINE_... properties.
	// context comment
	//    hENGINE- ������, ������� �������� �����������
	// data content comment
	//    not used

	#define pm_ENGINE_IO_DISINFECTION_IMPOSSIBLE 0x0000100a // (4106) -- Disinfection impossibility. Details in npENGINE_... properties.
	// context comment
	//    hENGINE- ������, ������� �������� �����������
	// data content comment
	//    not used

	#define pm_ENGINE_IO_CORRUPTED 0x0000100b // (4107) -- //rus:�������� ���������� ��������� ��������������� �������.//eng:Inernal structure inconsistance
	// context comment
	//    hENGINE
	// data content comment
	//    not used
	//

	#define pm_ENGINE_IO_ENCRYPTED 0x00001012 // (4114) -- ������ ����������
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_PASSWORD_PROTECTED 0x00001015 // (4117) -- ������ � ����������� ������� ������� �������
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_PROCESSING_ERROR 0x0000100c // (4108) -- ����������� ������ ��� ��������� �������
	// context comment
	//    hENGINE
	// data content comment
	//    tERROR - ������ ���������

	#define pm_ENGINE_IO_WAS_MODIFIED 0x0000100d // (4109) -- ������ IO �������//eng:IO was mofified.
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_MAKE_VIRTUAL_NAME 0x0000100e // (4110) -- ������ �� �������� ������������ �����.//eng:Request for object virtual name creation
	// context comment
	//    hENGINE
	//
	// data content comment
	//    ANSI string - forced name

	#define pm_ENGINE_IO_NAME_CHECK 0x0000100f // (4111) -- Check name for processing - should it be extracted
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_GET_ORIGINAL_BOOT 0x00001010 // (4112) -- Fill buffer with boot sector image
	// context comment
	//    hENGINE
	// data content comment
	//    ��������� �� ����������, ������� ��������� ��������� �� ������� � �������.

	#define pm_ENGINE_IO_GET_ORIGINAL_MBR 0x00001011 // (4113) -- Fill buffer with MBR sector image
	// context comment
	//    hENGINE
	// data content comment
	//    ��������� �� ����������, ������� ��������� ��������� �� ������� � �������.

	#define pm_ENGINE_IO_OUTPUT_STRING 0x00001013 // (4115) -- Output undocumented messages from engine
	// context comment
	//    hENGINE
	// data content comment
	//    char* string

	#define pm_ENGINE_IO_OUTPUT_MT_DEBUG 0x00001014 // (4116) -- Debug message for multithread mode monitoring
	// context comment
	//    hENGINE
	// data content comment
	//    4 DWORDS.

	#define pm_ENGINE_IO_HASH_FRAME_BEGIN 0x00001016 // (4118) -- ������ ������ ���������, ����������� ��� ����������� � HASH ����������.
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_HASH_FRAME_LEAVE 0x00001017 // (4119) -- ����� ������ ���������, ����������� ��� ����������� � HASH ����������.
	// context comment
	//    hENGINE
	// data content comment
	//    ��������� �� ����������, ����������� ��������� �� ���������������� ������. ��������� ����� �������� � Hash ����������.

	#define pm_ENGINE_IO_HASH_FRAME_FOUND 0x00001018 // (4120) -- ������ ������ � HASH ����������. ��������� ����� ��������� ����� ��������.
	// context comment
	//    hENGINE
	// data content comment
	//    ��������� �� ����������, ����������� �� ���������������� ������. ������� �� Hash ����������.

	#define pm_ENGINE_IO_CHANGE_ACCESS_MODE 0x00001019 // (4121) -- ������ �� ��������� ������ �������� �������
	// context comment
	//    hOBJECT
	// data content comment
	//    Dword access mode - �������� �����
	//

	#define pm_ENGINE_IO_UNSUPPORTED_COMPRESSION_METHOD 0x0000101a // (4122) -- �����������/���������������� ����� ������
	// context comment
	//    hENGINE
	// data content comment
	//    not used

	#define pm_ENGINE_IO_OS_CHECK 0x0000101b // (4123) -- ������ �� ������������� ��������� OS.
	// context comment
	//    hOS
	// data content comment
	//    not used

	#define pm_ENGINE_IO_ICHECKER_OK 0x0000101c // (4124) --

	#define pm_ENGINE_IO_OS_PRECLOSE 0x0000101d // (4125) -- ���������� ��������� OS.
	// context comment
	//    hOS
	// data content comment
	//    not used

	#define pm_ENGINE_IO_HC_CLEAN 0x0000101e // (4126) --

	#define pm_ENGINE_IO_HC_DETECT 0x0000101f // (4127) --

	#define pm_ENGINE_IO_HC_OVERWRITED 0x00001020 // (4128) --

	#define pm_ENGINE_IO_HC_OVERWRITE_FAILED 0x00001021 // (4129) --

	#define pm_ENGINE_IO_HC_MARKED_FOR_DELETE 0x00001022 // (4130) --

	#define pm_ENGINE_IO_OS_CLOSE_ERROR 0x00001023 // (4131) --
	// data content comment
	//    error code

	#define pm_ENGINE_IO_OS_RECOGNIZE 0x00001024 // (4132) --
	// data content comment
	//
	//

	#define pm_ENGINE_IO_GET_EMUL_FLAGS 0x00001025

	#define pm_ENGINE_IO_FALSE_ALARM 0x00001026



// message class
//    ��������� ����� ������ ���������� �� ����� ������������� ENGINE � ������ ������ LoadConfiguration.
#define pmc_ENGINE_LOAD 0x7f067b36 // ����� ��������� � ���� �������� ENGINE � ������������

	#define pm_ENGINE_LOAD_BASE 0x00001000 // (4096) -- ����������� � �������� ���������� ����� ����.
	// context comment
	//    hSTRING ����� ����
	// data content comment
	//    DATETIME ������� ����

	#define pm_ENGINE_LOAD_RECORD 0x00001001 // (4097) -- ����������� � �������� ��������� ������.
	// context comment
	//    hSTRING ����� �������
	// data content comment
	//    not used

	#define pm_ENGINE_LOAD_BASE_INTEGRITY_FAILED 0x00001002 // (4098) -- ����������� ������� ������/���� �� ������
	// context comment
	//    hSTRING - ��� ����/������
	// data content comment
	//    not used

	#define pm_ENGINE_LOAD_BASE_ERROR_OPEN 0x00001003 // (4099) -- ���������� ������� ����/������
	// context comment
	//    hSTRING - ��� ����/������
	// data content comment
	//    not used

	#define pm_ENGINE_LOAD_OUTPUT_STRING 0x00001004 // (4100) -- ������� ������ �� ����� �������� ���
	// context comment
	//    hSTRING
	// data content comment
	//    not used

	#define pm_ENGINE_LOAD_CONFIGURATION_OUT_OF_DATE 0x00001005 // (4101) --

	#define pm_ENGINE_LOAD_CONFIGURATION_LOADED 0x00001006 // (4102) --

	#define pm_ENGINE_LOAD_CONFIGURATION_UNLOADED 0x00001007 // (4103) --

	#define pm_ENGINE_LOAD_CONFIGURATION_ERROR 0x00001008 // (4104) --

// message class
#define pmc_ENGINE_PROCESS 0xd27b6592 // ��������� � ����������� ������� Process() � ICheck()

	#define pm_ENGINE_PROCESS_BEGIN 0x00001000 // (4096) -- ������ ��������� �������
	// context comment
	//    hEngine

	#define pm_ENGINE_PROCESS_DONE 0x00001001 // (4097) -- ����� ��������� �������
	// context comment
	//    hEngine
	// data content comment
	//    tERROR
// AVP Prague stamp end

#define pmc_ENGINE_DETECT 0xd27b6593 // ��������� � ����������� ��������� �����������
	
	#define pm_ENGINE_DETECT_WA 0x00001000 // (4096) -- ��������� � ������ ������������ ������� (cWorkArea � ���������)


#define pm_ENGINE_LOAD_BASE_UNRESOLVED_SYMBOL 0x00001100 
#define pm_ENGINE_LOAD_BASE_DUPLICATE_SYMBOL  0x00001101 

// AVP Prague stamp begin( Interface defined errors,  )
#define errENGINE_BAD_CONFIGURATION              PR_MAKE_DECL_ERR(IID_ENGINE, 0x001) // 0x8f235001,-1893511167 (1) -- ������������ ������������.
#define errENGINE_OS_STOPPED                     PR_MAKE_DECL_ERR(IID_ENGINE, 0x002) // 0x8f235002,-1893511166 (2) -- ��������� OS �����������.
#define errENGINE_IO_MODIFIED                    PR_MAKE_DECL_ERR(IID_ENGINE, 0x003) // 0x8f235003,-1893511165 (3) -- �������������� ������ ��� �������.
#define errENGINE_ACTION_SKIP                    PR_MAKE_DECL_ERR(IID_ENGINE, 0x004) // 0x8f235004,-1893511164 (4) -- ����������� ���.
#define errENGINE_CONFIGURATION_NOT_LOADED       PR_MAKE_DECL_ERR(IID_ENGINE, 0x005) // 0x8f235005,-1893511163 (5) --
#define errENGINE_BAD_ACTION_CONFIGURATION       PR_MAKE_DECL_ERR(IID_ENGINE, 0x006) // 0x8f235006,-1893511162 (6) --
#define errENGINE_BAD_REGISTRY_CONFIGURATION     PR_MAKE_DECL_ERR(IID_ENGINE, 0x007) // 0x8f235007,-1893511161 (7) --
#define errENGINE_BAD_AVP_SET                    PR_MAKE_DECL_ERR(IID_ENGINE, 0x008) // 0x8f235008,-1893511160 (8) --
#define errENGINE_MT_DRIVER_NOT_LOADED           PR_MAKE_DECL_ERR(IID_ENGINE, 0x009) // 0x8f235009,-1893511159 (9) --
#define errENGINE_BAD_AVP1_CONFIGURATION         PR_MAKE_DECL_ERR(IID_ENGINE, 0x00a) // 0x8f23500a,-1893511158 (10) --
#define errENGINE_OS_VOLUME_SET_INCOMPLETE       PR_MAKE_DECL_ERR(IID_ENGINE, 0x00b) // 0x8f23500b,-1893511157 (11) --
#define errENGINE_HC_NO_OVERWRITE                PR_MAKE_DECL_ERR(IID_ENGINE, 0x00d) // 0x8f23500d,-1893511155 (13) --
// AVP Prague stamp end



// AVP Prague stamp begin( RPC start declaration,  )
#if defined( __RPC__ )
	typedef tUINT hENGINE;
#else
// AVP Prague stamp end



// AVP Prague stamp begin( Interface forward declaration,  )
struct iEngineVtbl;
typedef struct iEngineVtbl iEngineVtbl;
// AVP Prague stamp end



// AVP Prague stamp begin( Object declaration,  )
#if defined( __cplusplus ) && !defined(_USE_VTBL)
	struct cEngine;
	typedef cEngine* hENGINE;
#else
	typedef struct tag_hENGINE {
		const iEngineVtbl* vtbl; // pointer to the "Engine" virtual table
		const iSYSTEMVtbl* sys;  // pointer to the "SYSTEM" virtual table
	} *hENGINE;
#endif // if defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( RPC_ end declaration,  )
#endif // if defined( __RPC__ )
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions begin,  )
#if !defined( Engine_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface function forward declarations,  )


	typedef   tERROR (pr_call *fnpEngine_Process)           ( hENGINE _this, hOBJECT obj );   // -- ���������� ������.//eng:Process object.;
	typedef   tERROR (pr_call *fnpEngine_GetAssociatedInfo) ( hENGINE _this, hOBJECT obj, tDWORD info_id, tDWORD param, tPTR buffer, tDWORD size, tDWORD* out_size ); // -- �������� ��������������� ������.//eng:Get associated data.;
	typedef   tERROR (pr_call *fnpEngine_GetExtendedInfo)   ( hENGINE _this, tDWORD info_id, tDWORD param, tPTR buffer, tDWORD size, tDWORD* out_size ); // -- �������� �������������� ��������.//eng:Get extended information.;
	typedef   tERROR (pr_call *fnpEngine_LoadConfiguration) ( hENGINE _this, hREGISTRY reg, tRegKey key ); // -- ��������� ������������.;


// AVP Prague stamp end



// AVP Prague stamp begin( Interface declaration,  )
struct iEngineVtbl {
	fnpEngine_Process            Process;
	fnpEngine_GetAssociatedInfo  GetAssociatedInfo;
	fnpEngine_GetExtendedInfo    GetExtendedInfo;
	fnpEngine_LoadConfiguration  LoadConfiguration;
}; // "Engine" external virtual table prototype
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions end,  )
#endif // if !defined( Engine_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface declared properties,  )
//! #define pgINTERFACE_VERSION      mPROPERTY_MAKE_GLOBAL( pTYPE_VERSION , 0x00000082 )
//! #define pgINTERFACE_COMMENT      mPROPERTY_MAKE_GLOBAL( pTYPE_STRING  , 0x00000083 )
#define pgENGINE_VERSION         mPROPERTY_MAKE_GLOBAL( pTYPE_VERSION , 0x00001001 )
#define pgENGINE_DB_NAME         mPROPERTY_MAKE_GLOBAL( pTYPE_STRING  , 0x00001002 )
#define pgENGINE_DB_COUNT        mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001003 )
#define pgENGINE_DB_TIME         mPROPERTY_MAKE_GLOBAL( pTYPE_DATETIME, 0x00001004 )
#define pgENGINE_DB_STATE        mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001005 )
#define pgENGINE_DB_LOAD_NAME    mPROPERTY_MAKE_GLOBAL( pTYPE_STRING  , 0x00001007 )
#define pgENGINE_DB_LOAD_TIME    mPROPERTY_MAKE_GLOBAL( pTYPE_DATETIME, 0x00001008 )
#define pgENGINE_SUBENGINE_COUNT mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001009 )
#define pgENGINE_SUBENGINE_TABLE mPROPERTY_MAKE_GLOBAL( pTYPE_PTR     , 0x0000100a )
#define pgENGINE_DB_VERDICTS     mPROPERTY_MAKE_GLOBAL( pTYPE_BYTE    , 0x0000100b )
// AVP Prague stamp end



// AVP Prague stamp begin( Defines to simplify interface method calls,  )
#if !defined( __cplusplus ) || defined(_USE_VTBL)
	#define CALL_Engine_Process( _this, obj )                                                              ((_this)->vtbl->Process( (_this), obj ))
	#define CALL_Engine_GetAssociatedInfo( _this, obj, info_id, param, buffer, size, out_size )            ((_this)->vtbl->GetAssociatedInfo( (_this), obj, info_id, param, buffer, size, out_size ))
	#define CALL_Engine_GetExtendedInfo( _this, info_id, param, buffer, size, out_size )                   ((_this)->vtbl->GetExtendedInfo( (_this), info_id, param, buffer, size, out_size ))
	#define CALL_Engine_LoadConfiguration( _this, reg, key )                                               ((_this)->vtbl->LoadConfiguration( (_this), reg, key ))
#else // if !defined( __cplusplus )
	#define CALL_Engine_Process( _this, obj )                                                              ((_this)->Process( obj ))
	#define CALL_Engine_GetAssociatedInfo( _this, obj, info_id, param, buffer, size, out_size )            ((_this)->GetAssociatedInfo( obj, info_id, param, buffer, size, out_size ))
	#define CALL_Engine_GetExtendedInfo( _this, info_id, param, buffer, size, out_size )                   ((_this)->GetExtendedInfo( info_id, param, buffer, size, out_size ))
	#define CALL_Engine_LoadConfiguration( _this, reg, key )                                               ((_this)->LoadConfiguration( reg, key ))
#endif // if !defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( C++ interface declaration,  )
#if defined (__cplusplus) && !defined(_USE_VTBL)
	struct pr_abstract iEngine {
		virtual tERROR pr_call Process( hOBJECT obj ) = 0; // -- ���������� ������.//eng:Process object.
		virtual tERROR pr_call GetAssociatedInfo( hOBJECT obj, tDWORD info_id, tDWORD param, tPTR buffer, tDWORD size, tDWORD* out_size ) = 0; // -- �������� ��������������� ������.//eng:Get associated data.
		virtual tERROR pr_call GetExtendedInfo( tDWORD info_id, tDWORD param, tPTR buffer, tDWORD size, tDWORD* out_size ) = 0; // -- �������� �������������� ��������.//eng:Get extended information.
		virtual tERROR pr_call LoadConfiguration( hREGISTRY reg, tRegKey key ) = 0; // -- ��������� ������������.
	};

	struct pr_abstract cEngine : public iEngine, public iObj {

		OBJ_IMPL( cEngine );

		operator hOBJECT() { return (hOBJECT)this; }
		operator hENGINE()   { return (hENGINE)this; }

		tVERSION pr_call get_pgENGINE_VERSION() { return (tVERSION)getDWord(pgENGINE_VERSION); }
		tERROR pr_call set_pgENGINE_VERSION( tVERSION value ) { return setDWord(pgENGINE_VERSION,(tDWORD)value); }

		tERROR pr_call get_pgENGINE_DB_NAME( tPTR buff, tDWORD size, tCODEPAGE cp=cCP_ANSI ) { return getStr(pgENGINE_DB_NAME,buff,size,cp); }
		tERROR pr_call set_pgENGINE_DB_NAME( tPTR buff, tDWORD size, tCODEPAGE cp=cCP_ANSI ) { return setStr(pgENGINE_DB_NAME,buff,size,cp); }

		tDWORD pr_call get_pgENGINE_DB_COUNT() { return (tDWORD)getDWord(pgENGINE_DB_COUNT); }
		tERROR pr_call set_pgENGINE_DB_COUNT( tDWORD value ) { return setDWord(pgENGINE_DB_COUNT,(tDWORD)value); }

		tERROR pr_call get_pgENGINE_DB_TIME( tDATETIME* value ) { return get(pgENGINE_DB_TIME,value,sizeof(tDATETIME)); }
		tERROR pr_call set_pgENGINE_DB_TIME( tDATETIME* value ) { return set(pgENGINE_DB_TIME,value,sizeof(tDATETIME)); }

		tDWORD pr_call get_pgENGINE_DB_STATE() { return (tDWORD)getDWord(pgENGINE_DB_STATE); }
		tERROR pr_call set_pgENGINE_DB_STATE( tDWORD value ) { return setDWord(pgENGINE_DB_STATE,(tDWORD)value); }

		tERROR pr_call get_pgENGINE_DB_LOAD_NAME( tPTR buff, tDWORD size, tCODEPAGE cp=cCP_ANSI ) { return getStr(pgENGINE_DB_LOAD_NAME,buff,size,cp); }
		tERROR pr_call set_pgENGINE_DB_LOAD_NAME( tPTR buff, tDWORD size, tCODEPAGE cp=cCP_ANSI ) { return setStr(pgENGINE_DB_LOAD_NAME,buff,size,cp); }

		tERROR pr_call get_pgENGINE_DB_LOAD_TIME( tDATETIME* value ) { return get(pgENGINE_DB_LOAD_TIME,value,sizeof(tDATETIME)); }
		tERROR pr_call set_pgENGINE_DB_LOAD_TIME( tDATETIME* value ) { return set(pgENGINE_DB_LOAD_TIME,value,sizeof(tDATETIME)); }

		tDWORD pr_call get_pgENGINE_SUBENGINE_COUNT() { return (tDWORD)getDWord(pgENGINE_SUBENGINE_COUNT); }
		tERROR pr_call set_pgENGINE_SUBENGINE_COUNT( tDWORD value ) { return setDWord(pgENGINE_SUBENGINE_COUNT,(tDWORD)value); }

		tPTR pr_call get_pgENGINE_SUBENGINE_TABLE() { return (tPTR)getPtr(pgENGINE_SUBENGINE_TABLE); }
		tERROR pr_call set_pgENGINE_SUBENGINE_TABLE( tPTR value ) { return setPtr(pgENGINE_SUBENGINE_TABLE,(tPTR)value); }

		tBYTE pr_call get_pgENGINE_DB_VERDICTS() { return (tBYTE)getByte(pgENGINE_DB_VERDICTS); }
		tERROR pr_call set_pgENGINE_DB_VERDICTS( tBYTE value ) { return setByte(pgENGINE_DB_VERDICTS,(tBYTE)value); }

	};

#endif // if defined (__cplusplus) && !defined(_USE_VTBL)
// AVP Prague stamp end



// AVP Prague stamp begin( Header endif,  )
#endif // __i_engine__3586a210_b2c2_4130_b9f4_59d900730341
// AVP Prague stamp end



