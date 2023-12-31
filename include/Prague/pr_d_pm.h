// This file has been generated automatically on ��.29.11.05 17:03:12

// FILE: O:\Prague\avp4\AVP4DB.H
DEF_IDENTIFIER( pm_REQUEST_DB_LOAD_PATH, 0xA8E994BF ) // 0xA8E994BF // 0xA8E994BF

// FILE: O:\Prague\Include\pr_msg.h
DEF_IDENTIFIER( pm_PROCESSING_YIELD, 0x62C12165 ) // 0x62C12165 // 0x62c12165
DEF_IDENTIFIER( pm_EXPAND_ENVIRONMENT_STRING, 0x4EED86CA ) // 0x4EED86CA // 0x4eed86ca

// FILE: O:\Prague\Include\iface\i_avpg.h
DEF_IDENTIFIER( pm_AVPG_NOTIFY_THREAD_STARTED, 0x000000C9 ) // 0x000000C9 // ((tDWORD)(201))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_THREAD_STOPPED, 0x000000CA ) // 0x000000CA // ((tDWORD)(202))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_MISSED_OBJECT, 0x000000CB ) // 0x000000CB // ((tDWORD)(203))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_FOREACHTHREAD, 0x000000CC ) // 0x000000CC // ((tDWORD)(204))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_VOLUME_MOUNTED, 0x000000CD ) // 0x000000CD // ((tDWORD)(205))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_DRIVER_CONNECTION_IS_BROKEN, 0x000000CE ) // 0x000000CE // ((tDWORD)(206))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_WRITEBOOT_DETECTED, 0x000000CF ) // 0x000000CF // ((tDWORD)(207))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_CACHESIZE_CHANGED, 0x000000D0 ) // 0x000000D0 // ((tDWORD)(208))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_TERMINATE_PROCESS_DETECTED, 0x000000D1 ) // 0x000000D1 // ((tDWORD)(209))
DEF_IDENTIFIER( pm_AVPG_NOTIFY_FORMAT_TRACK, 0x000000D2 ) // 0x000000D2 // ((tDWORD)(210))
DEF_IDENTIFIER( pm_AVPG_PROCEED_OBJECT, 0x0000012D ) // 0x0000012D // ((tDWORD)(301))
DEF_IDENTIFIER( pm_AVPG_CONTROL_PROCESS_PROTECTION_ON, 0x00000191 ) // 0x00000191 // ((tDWORD)(401))
DEF_IDENTIFIER( pm_AVPG_CONTROL_PROCESS_PROTECTION_OFF, 0x00000192 ) // 0x00000192 // ((tDWORD)(402))
DEF_IDENTIFIER( pm_AVPG_CONTROL_PROCESS_PROTECTION_QUERY, 0x00000193 ) // 0x00000193 // ((tDWORD)(403))
DEF_IDENTIFIER( pm_AVPG_CONTROL_INCREASEUNSAFE, 0x00000194 ) // 0x00000194 // ((tDWORD)(404))
DEF_IDENTIFIER( pm_AVPG_CONTROL_DECREASEUNSAFE, 0x00000195 ) // 0x00000195 // ((tDWORD)(405))
DEF_IDENTIFIER( pm_AVPG_CONTROL_SET_STAT_LOGFILENAME, 0x000001F5 ) // 0x000001F5 // ((tDWORD)(501))
DEF_IDENTIFIER( pm_AVPG_CONTROL_SET_PREVERDICT, 0x00000259 ) // 0x00000259 // ((tDWORD)(601))
DEF_IDENTIFIER( pm_AVPG_CONTROL_GETEVENT_THREAD_ID, 0x0000025A ) // 0x0000025A // ((tDWORD)(602))
DEF_IDENTIFIER( pm_AVPG_CONTROL_PREFETCH, 0x0000025B ) // 0x0000025B // ((tDWORD)(603))

// FILE: O:\Prague\Include\iface\i_decodeio.h
DEF_IDENTIFIER( pm_IO_DELETE_ON_CLOSE_SUCCEED, 0x00000001 ) // 0x00000001 // 0x00000001
DEF_IDENTIFIER( pm_IO_DELETE_ON_CLOSE_FAILED, 0x00000002 ) // 0x00000002 // 0x00000002
DEF_IDENTIFIER( pm_IO_PASSWORD_REQUEST, 0x00000003 ) // 0x00000003 // 0x00000003
DEF_IDENTIFIER( pm_IO_CLOSE_ERROR, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_IO_CREATE_FAILED, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_IO_REOPEN_FAILED, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_IO_SET_ATTRIBUTES_FAILED, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pm_IO_RESORE_ATTRIBUTES_FAILED, 0x00001004 ) // 0x00001004 // 0x00001004

// FILE: O:\Prague\Include\iface\i_engine.h
DEF_IDENTIFIER( pm_ENGINE_ACTION_NO_ACTION, 0x00000000 ) // 0x00000000 // 0x00000000
DEF_IDENTIFIER( pm_ENGINE_ACTION_SET_OF_ACTIONS, 0x00000001 ) // 0x00000001 // 0x00000001
DEF_IDENTIFIER( pm_ENGINE_ACTION_PROCESS_OS_ON_IO, 0x00000002 ) // 0x00000002 // 0x00000002
DEF_IDENTIFIER( pm_ENGINE_ACTION_CONVERT_IO, 0x00000003 ) // 0x00000003 // 0x00000003
DEF_IDENTIFIER( pm_ENGINE_ACTION_SWITCH_BY_PROPERTY, 0x00000004 ) // 0x00000004 // 0x00000004
DEF_IDENTIFIER( pm_ENGINE_ACTION_SUBENGINE_PROCESS, 0x00000005 ) // 0x00000005 // 0x00000005
DEF_IDENTIFIER( pm_ENGINE_ACTION_DISINFECT, 0x00000006 ) // 0x00000006 // 0x00000006
DEF_IDENTIFIER( pm_ENGINE_OPTIONS_USE_MULTITHREAD_DRIVER, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_ENGINE_OPTIONS_SEND_LOAD_RECORD_MESSAGE, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_ENGINE_OPTIONS_SEND_MT_DEBUG_MESSAGE, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_ENGINE_OPTIONS_USE_SIGN_CHECK, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pm_ENGINE_IO_BEGIN, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_ENGINE_IO_DONE, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_ENGINE_IO_OS_ENTER, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pm_ENGINE_IO_OS_LEAVE, 0x00001004 ) // 0x00001004 // 0x00001004
DEF_IDENTIFIER( pm_ENGINE_IO_SUB_IO_ENTER, 0x00001005 ) // 0x00001005 // 0x00001005
DEF_IDENTIFIER( pm_ENGINE_IO_SUB_IO_LEAVE, 0x00001006 ) // 0x00001006 // 0x00001006
DEF_IDENTIFIER( pm_ENGINE_IO_DETECT, 0x00001007 ) // 0x00001007 // 0x00001007
DEF_IDENTIFIER( pm_ENGINE_IO_DISINFECTED, 0x00001008 ) // 0x00001008 // 0x00001008
DEF_IDENTIFIER( pm_ENGINE_IO_DISINFECTION_FAILED, 0x00001009 ) // 0x00001009 // 0x00001009
DEF_IDENTIFIER( pm_ENGINE_IO_DISINFECTION_IMPOSSIBLE, 0x0000100A ) // 0x0000100A // 0x0000100a
DEF_IDENTIFIER( pm_ENGINE_IO_CORRUPTED, 0x0000100B ) // 0x0000100B // 0x0000100b
DEF_IDENTIFIER( pm_ENGINE_IO_ENCRYPTED, 0x00001012 ) // 0x00001012 // 0x00001012
DEF_IDENTIFIER( pm_ENGINE_IO_PASSWORD_PROTECTED, 0x00001015 ) // 0x00001015 // 0x00001015
DEF_IDENTIFIER( pm_ENGINE_IO_PROCESSING_ERROR, 0x0000100C ) // 0x0000100C // 0x0000100c
DEF_IDENTIFIER( pm_ENGINE_IO_WAS_MODIFIED, 0x0000100D ) // 0x0000100D // 0x0000100d
DEF_IDENTIFIER( pm_ENGINE_IO_MAKE_VIRTUAL_NAME, 0x0000100E ) // 0x0000100E // 0x0000100e
DEF_IDENTIFIER( pm_ENGINE_IO_NAME_CHECK, 0x0000100F ) // 0x0000100F // 0x0000100f
DEF_IDENTIFIER( pm_ENGINE_IO_GET_ORIGINAL_BOOT, 0x00001010 ) // 0x00001010 // 0x00001010
DEF_IDENTIFIER( pm_ENGINE_IO_GET_ORIGINAL_MBR, 0x00001011 ) // 0x00001011 // 0x00001011
DEF_IDENTIFIER( pm_ENGINE_IO_OUTPUT_STRING, 0x00001013 ) // 0x00001013 // 0x00001013
DEF_IDENTIFIER( pm_ENGINE_IO_OUTPUT_MT_DEBUG, 0x00001014 ) // 0x00001014 // 0x00001014
DEF_IDENTIFIER( pm_ENGINE_IO_HASH_FRAME_BEGIN, 0x00001016 ) // 0x00001016 // 0x00001016
DEF_IDENTIFIER( pm_ENGINE_IO_HASH_FRAME_LEAVE, 0x00001017 ) // 0x00001017 // 0x00001017
DEF_IDENTIFIER( pm_ENGINE_IO_HASH_FRAME_FOUND, 0x00001018 ) // 0x00001018 // 0x00001018
DEF_IDENTIFIER( pm_ENGINE_IO_CHANGE_ACCESS_MODE, 0x00001019 ) // 0x00001019 // 0x00001019
DEF_IDENTIFIER( pm_ENGINE_IO_UNSUPPORTED_COMPRESSION_METHOD, 0x0000101A ) // 0x0000101A // 0x0000101a
DEF_IDENTIFIER( pm_ENGINE_IO_OS_CHECK, 0x0000101B ) // 0x0000101B // 0x0000101b
DEF_IDENTIFIER( pm_ENGINE_IO_ICHECKER_OK, 0x0000101C ) // 0x0000101C // 0x0000101c
DEF_IDENTIFIER( pm_ENGINE_IO_OS_PRECLOSE, 0x0000101D ) // 0x0000101D // 0x0000101d
DEF_IDENTIFIER( pm_ENGINE_IO_HC_CLEAN, 0x0000101E ) // 0x0000101E // 0x0000101e
DEF_IDENTIFIER( pm_ENGINE_IO_HC_DETECT, 0x0000101F ) // 0x0000101F // 0x0000101f
DEF_IDENTIFIER( pm_ENGINE_IO_HC_OVERWRITED, 0x00001020 ) // 0x00001020 // 0x00001020
DEF_IDENTIFIER( pm_ENGINE_IO_HC_OVERWRITE_FAILED, 0x00001021 ) // 0x00001021 // 0x00001021
DEF_IDENTIFIER( pm_ENGINE_IO_HC_MARKED_FOR_DELETE, 0x00001022 ) // 0x00001022 // 0x00001022
DEF_IDENTIFIER( pm_ENGINE_IO_OS_CLOSE_ERROR, 0x00001023 ) // 0x00001023 // 0x00001023
DEF_IDENTIFIER( pm_ENGINE_IO_OS_RECOGNIZE, 0x00001024 ) // 0x00001024 // 0x00001024
DEF_IDENTIFIER( pm_ENGINE_LOAD_BASE, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_ENGINE_LOAD_RECORD, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_ENGINE_LOAD_BASE_INTEGRITY_FAILED, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_ENGINE_LOAD_BASE_ERROR_OPEN, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pm_ENGINE_LOAD_OUTPUT_STRING, 0x00001004 ) // 0x00001004 // 0x00001004
DEF_IDENTIFIER( pm_ENGINE_LOAD_CONFIGURATION_OUT_OF_DATE, 0x00001005 ) // 0x00001005 // 0x00001005
DEF_IDENTIFIER( pm_ENGINE_LOAD_CONFIGURATION_LOADED, 0x00001006 ) // 0x00001006 // 0x00001006
DEF_IDENTIFIER( pm_ENGINE_LOAD_CONFIGURATION_UNLOADED, 0x00001007 ) // 0x00001007 // 0x00001007
DEF_IDENTIFIER( pm_ENGINE_LOAD_CONFIGURATION_ERROR, 0x00001008 ) // 0x00001008 // 0x00001008
DEF_IDENTIFIER( pm_ENGINE_PROCESS_BEGIN, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_ENGINE_PROCESS_DONE, 0x00001001 ) // 0x00001001 // 0x00001001

// FILE: O:\Prague\Include\iface\i_insider.h
DEF_IDENTIFIER( pm_INSIDER_EVENT, 0x3D823B1E ) // 0x3D823B1E // 0x3d823b1e
DEF_IDENTIFIER( pm_INSIDER_STATISTIC, 0xC78FEB04 ) // 0xC78FEB04 // 0xc78feb04
DEF_IDENTIFIER( pm_INSIDER_REQUEST_MESSAGE, 0xE8D00B00 ) // 0xE8D00B00 // 0xe8d00b00
DEF_IDENTIFIER( pm_INSIDER_REQUEST_DISINFECT, 0x02F4D8D1 ) // 0x02F4D8D1 // 0x02f4d8d1
DEF_IDENTIFIER( pm_INSIDER_REQUEST_DELETE, 0x89D00DDF ) // 0x89D00DDF // 0x89d00ddf
DEF_IDENTIFIER( pm_INSIDER_REQUEST_DELETE_FAILED, 0x6FF165E8 ) // 0x6FF165E8 // 0x6ff165e8
DEF_IDENTIFIER( pm_INSIDER_REQUEST_CURE_LOCKED_COPY_FAILED, 0x62A6442B ) // 0x62A6442B // 0x62a6442b
DEF_IDENTIFIER( pm_INSIDER_REQUEST_PASSWORD, 0xCE48678B ) // 0xCE48678B // 0xce48678b
DEF_IDENTIFIER( pm_INSIDER_REQUEST_QUARANTINE, 0x616FFF40 ) // 0x616FFF40 // 0x616fff40
DEF_IDENTIFIER( pm_INSIDER_REQUEST_BACKUP, 0x8C32A0F4 ) // 0x8C32A0F4 // 0x8c32a0f4
DEF_IDENTIFIER( pm_INSIDER_REQUEST_SECTOR_OVERWRITE, 0xB8C540A2 ) // 0xB8C540A2 // 0xb8c540a2
DEF_IDENTIFIER( pm_INSIDER_REQUEST_INSERTNEXTDISK, 0xF1D509EF ) // 0xF1D509EF // 0xf1d509ef
DEF_IDENTIFIER( pm_INSIDER_REQUEST_DELAYASK, 0x49B37E0C ) // 0x49B37E0C // 0x49b37e0c
DEF_IDENTIFIER( pm_INSIDER_REQUEST_WARNDISINFECT, 0x32CC04CC ) // 0x32CC04CC // 0x32cc04cc

// FILE: O:\Prague\Include\iface\i_ipresolver.h
DEF_IDENTIFIER( pm_RESOLVE_INFO, 0x00001000 ) // 0x00001000 // 0x00001000

// FILE: O:\Prague\Include\iface\i_kavwin.h
DEF_IDENTIFIER( pm_CONFIGURATOR_GET_PATTERN, 0x000003E9 ) // 0x000003E9 // ((tDWORD)(1001))
DEF_IDENTIFIER( pm_CONFIGURATOR_GET_DATA, 0x000003EA ) // 0x000003EA // ((tDWORD)(1002))
DEF_IDENTIFIER( pm_CONFIGURATOR_GET_DATA_TREE, 0x000003EB ) // 0x000003EB // ((tDWORD)(1003))
DEF_IDENTIFIER( pm_CONFIGURATOR_SET_DATA, 0x000003EC ) // 0x000003EC // ((tDWORD)(1004))
DEF_IDENTIFIER( pm_CONFIGURATOR_GET_STATUS, 0x000003ED ) // 0x000003ED // ((tDWORD)(1005))
DEF_IDENTIFIER( pm_CONFIGURATOR_WHO_IS_RUNNING, 0x000003EE ) // 0x000003EE // ((tDWORD)(1006))
DEF_IDENTIFIER( pm_CONFIGURATOR_RUNNING, 0x000003EF ) // 0x000003EF // ((tDWORD)(1007))
DEF_IDENTIFIER( pm_CONFIGURATOR_RUN_STATISTIC, 0x000007D1 ) // 0x000007D1 // ((tDWORD)(2001))
DEF_IDENTIFIER( pm_CONFIGURATOR_STOP_STATISTIC, 0x000007D2 ) // 0x000007D2 // ((tDWORD)(2002))
DEF_IDENTIFIER( pm_CONFIGURATOR_RESET_STATISTIC, 0x000007D3 ) // 0x000007D3 // ((tDWORD)(2003))
DEF_IDENTIFIER( pm_CONFIGURATOR_UPDATE_STATISTIC, 0x000007D4 ) // 0x000007D4 // ((tDWORD)(2004))

// FILE: O:\Prague\Include\iface\i_os.h
DEF_IDENTIFIER( pm_OS_VOLUME_HASH, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_OS_VOLUME_SET_INCOMPLETE, 0x00001001 ) // 0x00001001 // 0x00001001

// FILE: O:\Prague\Include\iface\i_root.h
DEF_IDENTIFIER( pm_OBJECT_CREATE_FAILED_IFACE_NOT_FOUND, 0xE00C8DB6 ) // 0xE00C8DB6 // 0xe00c8db6
DEF_IDENTIFIER( pm_INTERFACE_REGISTERED, 0x8ECD164C ) // 0x8ECD164C // 0x8ecd164c
DEF_IDENTIFIER( pm_INTERFACE_VERSION_CONFILCT, 0x9D1CFCBF ) // 0x9D1CFCBF // 0x9d1cfcbf
DEF_IDENTIFIER( pm_OBJECT_CHILD_CLOSE_FAILED, 0x03EBEA51 ) // 0x03EBEA51 // 0x03ebea51
DEF_IDENTIFIER( pm_OBJECT_PRECLOSE_FAILED, 0x2EB0221B ) // 0x2EB0221B // 0x2eb0221b
DEF_IDENTIFIER( pm_OBJECT_CLOSE_FAILED, 0xB49ECF7C ) // 0xB49ECF7C // 0xb49ecf7c
DEF_IDENTIFIER( pm_INTERFACE_LOAD_ERROR, 0x6C8B097A ) // 0x6C8B097A // 0x6c8b097a
DEF_IDENTIFIER( pm_OBJECT_HAS_BEEN_CREATED, 0x1E7A5976 ) // 0x1E7A5976 // 0x1e7a5976
DEF_IDENTIFIER( pm_OBJECT_HAS_BEEN_FREED, 0xCEED40F0 ) // 0xCEED40F0 // 0xceed40f0
DEF_IDENTIFIER( pm_OBJECT_IS_LOCKED_ON_CLOSE, 0x5464D13C ) // 0x5464D13C // 0x5464d13c

// FILE: O:\Prague\Include\iface\i_sfdb.h
DEF_IDENTIFIER( pmUPDATE_CLUSTER_FULL, 0x5FDB5FDC ) // 0x5FDB5FDC // 0x5fdb5fdc

// FILE: O:\Prague\Include\iface\m_dmap.h
DEF_IDENTIFIER( pm_DMAP_IO_RESIZE, 16641 ) // 0x00004101 // 0x4101
DEF_IDENTIFIER( pm_DMAP_IO_OMODE_CHANGE, 16386 ) // 0x00004002 // 0x4002
DEF_IDENTIFIER( pm_DMAP_IO_AMODE_CHANGE, 16387 ) // 0x00004003 // 0x4003

// FILE: O:\Prague\Include\plugin\p_avpg.h
DEF_IDENTIFIER( pm_AVPG_NOTIFY_STARTED, 0x000000FB ) // 0x000000FB // ((tDWORD)(251))

// FILE: O:\Prague\Include\plugin\p_avpmgr.h
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_PROCESS, 0x00002000 ) // 0x00002000 // 0x00002000
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_PROCESS_ARCHIVE, 0x00002001 ) // 0x00002001 // 0x00002001
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_OS_OFFSET_REGISTER, 0x00002002 ) // 0x00002002 // 0x00002002
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_OS_OFFSET_FLUSH, 0x00002003 ) // 0x00002003 // 0x00002003
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_HASH_FRAME_CHECK, 0x00002004 ) // 0x00002004 // 0x00002004
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_HASH_CONT_DELETE, 0x00002005 ) // 0x00002005 // 0x00002005
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_HASH_FRAME_LEAVE, 0x00002006 ) // 0x00002006 // 0x00002006
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_REGISTER_FOR_POSTPROCESS, 0x00002007 ) // 0x00002007 // 0x00002007
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_DISINFECT_REQUEST, 0x00002008 ) // 0x00002008 // 0x00002008
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_SECTOR_OVERWRITE_REQUEST, 0x00002009 ) // 0x00002009 // 0x00002009
DEF_IDENTIFIER( pm_AVPMGR_INTERNAL_IO_REGISTER_PASSWORD, 0x0000200A ) // 0x0000200A // 0x0000200a

// FILE: O:\Prague\Include\plugin\p_klavcore.h
DEF_IDENTIFIER( pm_KLAVPMGR_REQUEST_PROCESS_ACTION, 0x00002000 ) // 0x00002000 // 0x00002000

// FILE: O:\Prague\Include\plugin\p_mdb.h
DEF_IDENTIFIER( pm_OS_CHANGE, 0x00002000 ) // 0x00002000 // 0x00002000

// FILE: O:\Prague\Include\plugin\p_memmod.h
DEF_IDENTIFIER( pm_MEMORY_PROCESS_REQUEST_DELETE, 0x28CEDCA3 ) // 0x28CEDCA3 // ((tDWORD)(0x28cedca3))

// FILE: O:\Prague\kernel\receiver.h
DEF_IDENTIFIER( pm_MR_OBJECT_PRECLOSE, 0x45FAC119 ) // 0x45FAC119 // 0x45fac119

// FILE: O:\Prague\morda\morda.h
DEF_IDENTIFIER( pm_IO_MSG_CLS_ID, 20 ) // 0x00000014 // 20
DEF_IDENTIFIER( pm_OS_MSG_CLS_ID, 21 ) // 0x00000015 // 21

// FILE: O:\Prague\Scripts\Common\scrmsgs.h
DEF_IDENTIFIER( msg_OFFSETS_STREAM, 0x8671C2C4 ) // 0x8671C2C4 // 0x8671C2C4
DEF_IDENTIFIER( msg_DATA_STREAM, 0x7BAC2E70 ) // 0x7BAC2E70 // 0x7BAC2E70

// FILE: O:\Prague\Signatures\Plugin\srch_ds.h
DEF_IDENTIFIER( pm_SIGNATURE_SEARCHER_FOUND, 0x00000000 ) // 0x00000000 // 0x00000000

// FILE: O:\Prague\SubstIO\io.h
DEF_IDENTIFIER( pm_SUBST_IO_SAVE_CONTEXT, 0x00002000 ) // 0x00002000 // 0x00002000
DEF_IDENTIFIER( pm_SUBST_IO_RESTORE_CONTEXT, 0x00002001 ) // 0x00002001 // 0x00002001
DEF_IDENTIFIER( pm_SUBST_IO_SET_COMMENT, 0x00002002 ) // 0x00002002 // 0x00002002

// FILE: O:\Prague\tempfile\io.h
DEF_IDENTIFIER( pm_TEMPFILE_GETPATH, 0x00000001 ) // 0x00000001 // 0x00000001
DEF_IDENTIFIER( pm_TEMPFILE_GETNAME, 0x00000002 ) // 0x00000002 // 0x00000002

// FILE: O:\Prague\tempfile\tempfile.h
DEF_IDENTIFIER( pm_TEMPFILE_GETPATH, 1 ) // 0x00000001 // 1
DEF_IDENTIFIER( pm_TEMPFILE_GETNAME, 2 ) // 0x00000002 // 2

// FILE: O:\PPP\basegui\ItemBase.h
DEF_IDENTIFIER( pmTEST_GUI, 0x164EEB39 ) // 0x164EEB39 // 0x164eeb39

// FILE: O:\PPP\Include\iface\i_avs.h
DEF_IDENTIFIER( pm_SETTINGS_CHANGED, 0x00001000 ) // 0x00001000 // 0x00001000
//DEF_IDENTIFIER( pm_BASES_UPDATED, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_BASES_LOADED, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_THREATS_STATUS_CHANGED, 0x00001003 ) // 0x00001003 // 0x00001003

// FILE: O:\PPP\Include\iface\i_avssession.h
DEF_IDENTIFIER( pm_PROCESS_BEGIN, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_PROCESS_END, 0x00001001 ) // 0x00001001 // 0x00001001

// FILE: O:\PPP\Include\iface\i_licensing.h
DEF_IDENTIFIER( pm_INITING, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_POSTING_DATA, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_SAVING_TMP, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pm_VERIFYING, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pm_RETRYING, 0x00001004 ) // 0x00001004 // 0x00001004
DEF_IDENTIFIER( pm_SAVING_DST, 0x00001005 ) // 0x00001005 // 0x00001005
DEF_IDENTIFIER( pm_POSTING_STAT, 0x00001006 ) // 0x00001006 // 0x00001006
DEF_IDENTIFIER( pm_DOWNLOAD_COMPLETED, 0x00001007 ) // 0x00001007 // 0x00001007
DEF_IDENTIFIER( pm_CONNECTING, 0x00001008 ) // 0x00001008 // 0x00001008
DEF_IDENTIFIER( pm_RESOLVING, 0x00001009 ) // 0x00001009 // 0x00001009
DEF_IDENTIFIER( pm_SENDING, 0x0000100A ) // 0x0000100A // 0x0000100a
DEF_IDENTIFIER( pm_SENT, 0x0000100B ) // 0x0000100B // 0x0000100b
DEF_IDENTIFIER( pm_RECEIVING, 0x0000100C ) // 0x0000100C // 0x0000100c
DEF_IDENTIFIER( pm_RECEIVED, 0x0000100D ) // 0x0000100D // 0x0000100d
DEF_IDENTIFIER( pm_REDIRECTING, 0x0000100E ) // 0x0000100E // 0x0000100e
DEF_IDENTIFIER( pm_COMPLETED, 0x0000100F ) // 0x0000100F // 0x0000100f
DEF_IDENTIFIER( pm_GET_PASS_FOR_PROXY, 0x00001010 ) // 0x00001010 // 0x00001010
DEF_IDENTIFIER( pm_DATA_CHANGED, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_LICENSE_REPLACE, 0x6124E181 ) // 0x6124E181 // 0x6124e181

// FILE: O:\PPP\Include\iface\i_productlogic.h
DEF_IDENTIFIER( pm_REMOTE_GLOBAL_SELFPROT_ENABLED, 0xF39B5E52 ) // 0xF39B5E52 // 0xf39b5e52
DEF_IDENTIFIER( pm_REMOTE_GLOBAL_SERVICECONTROL_ENABLED, 0x27CE7C62 ) // 0x27CE7C62 // 0x27ce7c62
DEF_IDENTIFIER( pm_PRODUCT_STATE_CHANGED, 0xC1D5EFA5 ) // 0xC1D5EFA5 // 0xc1d5efa5
DEF_IDENTIFIER( pm_PRODUCT_STATISTICS_CHANGED, 0xD51F059B ) // 0xD51F059B // 0xd51f059b
DEF_IDENTIFIER( pm_PRODUCT_TRUSTEDAPPS_CHANGED, 0xBAA5CC18 ) // 0xBAA5CC18 // 0xbaa5cc18
DEF_IDENTIFIER( pm_PRODUCT_REQUEST_TRUSTEDAPPS, 0xAF7F7D63 ) // 0xAF7F7D63 // 0xaf7f7d63
DEF_IDENTIFIER( pm_PRODUCT_REQUEST_APPHASH, 0x9D378A56 ) // 0x9D378A56 // 0x9d378a56
DEF_IDENTIFIER( pm_REBOOT_APPLICATION, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pm_REBOOT_OS, 0x00001001 ) // 0x00001001 // 0x00001001
DEF_IDENTIFIER( pm_REBOOT_REQUEST_APPLICATION, 0xFC108998 ) // 0xFC108998 // 0xfc108998
DEF_IDENTIFIER( pm_REBOOT_REQUEST_OS, 0x48D429AD ) // 0x48D429AD // 0x48d429ad
DEF_IDENTIFIER( pm_UPDATE_EXECUTABLES, 0x047452EC ) // 0x047452EC // 0x047452ec
DEF_IDENTIFIER( pm_PRODUCT_STARTUP_CHANGE, 0x00001000 ) // 0x00001000 // 0x00001000

// FILE: O:\PPP\Include\iface\i_taskmanager.h
DEF_IDENTIFIER( pmPROFILE_STATE_CHANDED, 0x00001000 ) // 0x00001000 // 0x00001000
DEF_IDENTIFIER( pmPROFILE_CREATE, 0x00001002 ) // 0x00001002 // 0x00001002
DEF_IDENTIFIER( pmPROFILE_DELETE, 0x00001003 ) // 0x00001003 // 0x00001003
DEF_IDENTIFIER( pmPROFILE_MODIFIED, 0x00001004 ) // 0x00001004 // 0x00001004
DEF_IDENTIFIER( pmPROFILE_SETTINGS_MODIFIED, 0x00001005 ) // 0x00001005 // 0x00001005
DEF_IDENTIFIER( pmPROFILE_TASK_DISABLED_ON_RUN, 0x00001006 ) // 0x00001006 // 0x00001006
DEF_IDENTIFIER( pmPROFILE_LICENCE_CHECK_ERR, 0x00001007 ) // 0x00001007 // 0x00001007
DEF_IDENTIFIER( pmPROFILE_TASK_DISABLED_IN_SAFE_MODE, 0x00001008 ) // 0x00001008 // 0x00001008
DEF_IDENTIFIER( pmTM_EVENT_START, 0x384E7D1C ) // 0x384E7D1C // 0x384e7d1c
DEF_IDENTIFIER( pmTM_EVENT_STARTUP_TASKS_GOING_TO_START, 0xFFFF2A49 ) // 0xFFFF2A49 // 0xffff2a49
DEF_IDENTIFIER( pmTM_EVENT_STARTUP_TASKS_STARTED, 0xF927D6D6 ) // 0xF927D6D6 // 0xf927d6d6
DEF_IDENTIFIER( pmTM_EVENT_OS_SAFE_MODE, 0x208AD891 ) // 0x208AD891 // 0x208ad891
DEF_IDENTIFIER( pmTM_EVENT_GUI_CONNECTED, 0x506E3AE5 ) // 0x506E3AE5 // 0x506e3ae5
DEF_IDENTIFIER( pmTM_EVENT_GUI_DISCONNECTED, 0x387E4B05 ) // 0x387E4B05 // 0x387e4b05
DEF_IDENTIFIER( pmTM_EVENT_INET_CONNECTED, 0xF647945A ) // 0xF647945A // 0xf647945a
DEF_IDENTIFIER( pmTM_EVENT_INET_DISCONNECTED, 0x844AFB85 ) // 0x844AFB85 // 0x844afb85
DEF_IDENTIFIER( pmTM_EVENT_TASK_SETTINGS_CHANGED, 0x5A2B81F1 ) // 0x5A2B81F1 // 0x5a2b81f1
DEF_IDENTIFIER( pmTM_EVENT_GOING_TO_STOP, 0xCDF441E7 ) // 0xCDF441E7 // 0xcdf441e7
DEF_IDENTIFIER( pmTM_EVENT_INSTALL, 0xFFFF2A4A ) // 0xFFFF2A4A // 0xffff2a4a
DEF_IDENTIFIER( pmTM_EVENT_IDLE, 0xFFFF2A4B ) // 0xFFFF2A4B // 0xffff2a4b
DEF_IDENTIFIER( pmTM_EVENT_CHECK_STOP_ALLOWED, 0xFFFF2A4C ) // 0xFFFF2A4C // 0xffff2a4c

// FILE: O:\PPP\Include\plugin\p_antidial.h
DEF_IDENTIFIER( msg_ANTIDIAL_CHECK_NUMBER, 0x9D2E2B24 ) // 0x9D2E2B24 // 0x9d2e2b24

// FILE: O:\PPP\Include\plugin\p_antiphishing.h
DEF_IDENTIFIER( msg_ANTI_PHISHING_CHECK_URL, 0xD369D708 ) // 0xD369D708 // 0xd369d708
DEF_IDENTIFIER( msg_ANTI_PHISHING_BAD_DATABASE, 0xD369D709 ) // 0xD369D709 // 0xd369d709
DEF_IDENTIFIER( msg_ANTI_PHISHING_CHECK_DATABASE, 0xD369D70A ) // 0xD369D70A // 0xd369d70a

// FILE: O:\PPP\Include\plugin\p_as_trainsupport.h
DEF_IDENTIFIER( pm_AS_BEGIN_TRAINING, 0xAD91AFC7 ) // 0xAD91AFC7 // 0xad91afc7
DEF_IDENTIFIER( pm_AS_TRAIN_STATUS, 0x405D3A3C ) // 0x405D3A3C // 0x405d3a3c
DEF_IDENTIFIER( pm_AS_FINISH_TRAINING, 0xBD3ECAF8 ) // 0xBD3ECAF8 // 0xbd3ecaf8
DEF_IDENTIFIER( pm_AS_CANCEL_TRAINING, 0x187F2CD6 ) // 0x187F2CD6 // 0x187f2cd6
DEF_IDENTIFIER( pm_AS_SKIP_TRAINING, 0x6E16989B ) // 0x6E16989B // 0x6e16989b
DEF_IDENTIFIER( pm_AS_APPLY_RESULTS, 0x9B7BCDEA ) // 0x9B7BCDEA // 0x9b7bcdea
DEF_IDENTIFIER( pm_AS_MERGE_RESULTS, 0x7F021DAE ) // 0x7F021DAE // 0x7f021dae
DEF_IDENTIFIER( pm_AS_CANCEL_RESULTS, 0x25032EC1 ) // 0x25032EC1 // 0x25032ec1

// FILE: O:\PPP\Include\plugin\p_mailwasher.h
DEF_IDENTIFIER( pm_SESSION_NEEDED, 0x1E998E5A ) // 0x1E998E5A // 0x1e998e5a
DEF_IDENTIFIER( pm_SESSION_BEGIN, 0x731EDC5A ) // 0x731EDC5A // 0x731edc5a
DEF_IDENTIFIER( pm_SESSION_CLOSE, 0x1A9AC88B ) // 0x1A9AC88B // 0x1a9ac88b
DEF_IDENTIFIER( pm_SESSION_END, 125276782 ) // 0x0777926E // 0x777926e
DEF_IDENTIFIER( pm_MESSAGE_FOUND, 0x7DCED504 ) // 0x7DCED504 // 0x7dced504
DEF_IDENTIFIER( pm_MESSAGE_GETLIST, 0xB6C14DAE ) // 0xB6C14DAE // 0xb6c14dae
DEF_IDENTIFIER( pm_MESSAGE_REMOVE, 0xEDC86DE6 ) // 0xEDC86DE6 // 0xedc86de6
DEF_IDENTIFIER( pm_MESSAGE_DECODE, 0xA06C8B80 ) // 0xA06C8B80 // 0xa06c8b80
DEF_IDENTIFIER( pm_MESSAGE_DELETED, 0xBF60516A ) // 0xBF60516A // 0xbf60516a
DEF_IDENTIFIER( pm_CANCEL_REQUEST, 0xD9F725DD ) // 0xD9F725DD // 0xd9f725dd

// FILE: O:\PPP\Include\plugin\p_ods.h
DEF_IDENTIFIER( pm_MEMORY_SCANNED, 0x16D822B4 ) // 0x16D822B4 // 0x16d822b4

// FILE: O:\PPP\Include\plugin\p_offguard.h
DEF_IDENTIFIER( pm_TRANSFER, 0xB27A5013 ) // 0xB27A5013 // 0xb27a5013

// FILE: O:\PPP\Include\plugin\p_popupchk.h
DEF_IDENTIFIER( msg_POPUP_CHECK_URL, 0xBC10A322 ) // 0xBC10A322 // 0xbc10a322
DEF_IDENTIFIER( msg_POPUP_ALLOWED, 0xBC10A323 ) // 0xBC10A323 // 0xbc10a323
DEF_IDENTIFIER( msg_POPUP_ADD_TRUSTED_SITE, 0xBC10A324 ) // 0xBC10A324 // 0xbc10a324
DEF_IDENTIFIER( msg_POPUP_TEMPORARY_ALLOW_CB, 0xBC10A325 ) // 0xBC10A325 // 0xbc10a325
DEF_IDENTIFIER( msg_POPUP_TEMPORARY_ALLOW_CB2, 0xBC10A326 ) // 0xBC10A326 // 0xbc10a326

// FILE: O:\PPP\Include\plugin\p_processmonitor.h
DEF_IDENTIFIER( pm_PROCESS_MONITOR_SCHEDULE_GET_PREFETCH, 0xCC540337 ) // 0xCC540337 // 0xCC540337
DEF_IDENTIFIER( pm_PROCESS_MONITOR_ADD_ACTIVE_IMAGE, 0xCC540338 ) // 0xCC540338 // 0xCC540338
DEF_IDENTIFIER( pm_PROCESS_MONITOR_IS_ACTIVE_IMAGE, 0xCC540339 ) // 0xCC540339 // 0xCC540339

// FILE: O:\PPP\Include\plugin\p_qb.h
DEF_IDENTIFIER( pm_QB_IO_DELETE, 0xA47443A9 ) // 0xA47443A9 // 0xa47443a9
DEF_IDENTIFIER( pm_QB_IO_RESTORE, 0xA4744310 ) // 0xA4744310 // 0xa4744310
DEF_IDENTIFIER( pm_IO_MODIFIED, 0xF8A3CB85 ) // 0xF8A3CB85 // 0xf8a3cb85

// FILE: O:\PPP\Include\plugin\p_report.h
DEF_IDENTIFIER( pm_ADD_RECORD, 0xB879EC6A ) // 0xB879EC6A // 0xb879ec6a
DEF_IDENTIFIER( pm_BEFORE_DELETE_RECORD, 0xB879EC6D ) // 0xB879EC6D // 0xb879ec6d

// FILE: O:\PPP\Include\plugin\p_sc.h
DEF_IDENTIFIER( msg_SC_SCAN, 0xAB6D0BB0 ) // 0xAB6D0BB0 // 0xab6d0bb0

// FILE: O:\PPP\Include\plugin\p_spamtest.h
DEF_IDENTIFIER( msg_ISSPAMMESSAGE, 0x00002000 ) // 0x00002000 // 0x00002000

// FILE: O:\PPP\Include\plugin\p_updater2005.h
DEF_IDENTIFIER( pm_CATEGORY_UPDATED, 0x00002000 ) // 0x00002000 // 0x00002000
DEF_IDENTIFIER( pm_UPDATE_LOADED, 0x00002001 ) // 0x00002001 // 0x00002001
DEF_IDENTIFIER( pm_UPDATE_INSTALLED, 0x00002002 ) // 0x00002002 // 0x00002002
DEF_IDENTIFIER( pm_ROLLBACK_ACCESSIBLE, 0x00002003 ) // 0x00002003 // 0x00002003
DEF_IDENTIFIER( pm_REP_UPDATE_BEGIN, 0x00002000 ) // 0x00002000 // 0x00002000
DEF_IDENTIFIER( pm_REP_UPDATE_END, 0x00002001 ) // 0x00002001 // 0x00002001
DEF_IDENTIFIER( pm_REP_CONNECTED_TO_URL, 0x00002002 ) // 0x00002002 // 0x00002002
DEF_IDENTIFIER( pm_REP_FILE_LOAD_BEGIN, 0x00002003 ) // 0x00002003 // 0x00002003
DEF_IDENTIFIER( pm_REP_FILE_LOAD_END, 0x00002004 ) // 0x00002004 // 0x00002004
DEF_IDENTIFIER( pm_REP_FILE_ADDED, 0x00002005 ) // 0x00002005 // 0x00002005
DEF_IDENTIFIER( pm_REP_FILE_REPLACED, 0x00002006 ) // 0x00002006 // 0x00002006
DEF_IDENTIFIER( pm_REP_FILE_DELETED, 0x00002007 ) // 0x00002007 // 0x00002007
DEF_IDENTIFIER( pm_REP_ROLLBACK_BEGIN, 0x00002008 ) // 0x00002008 // 0x00002008
DEF_IDENTIFIER( pm_REP_ROLLBACK_END, 0x00002009 ) // 0x00002009 // 0x00002009
DEF_IDENTIFIER( pm_REP_RELAY_BEGIN, 0x0000200A ) // 0x0000200A // 0x0000200a
DEF_IDENTIFIER( pm_REP_RELAY_END, 0x0000200B ) // 0x0000200B // 0x0000200b
DEF_IDENTIFIER( pm_REP_UPDATE_DONT_REQUIRED, 0x0000200C ) // 0x0000200C // 0x0000200c
DEF_IDENTIFIER( pm_REP_RELAY_DONT_REQUIRED, 0x0000200D ) // 0x0000200D // 0x0000200d
DEF_IDENTIFIER( pm_REP_FILE_DOWNLOADED, 0x00002000 ) // 0x00002000 // 0x00002000
DEF_IDENTIFIER( pm_REP_PROXY_AUTH_FAILED, 0x00002002 ) // 0x00002002 // 0x00002002
DEF_IDENTIFIER( pm_REP_SELECT_UPDATE_SOURCE, 0x00002003 ) // 0x00002003 // 0x00002003
DEF_IDENTIFIER( pm_REP_FILE_INSTALLED, 0x00002004 ) // 0x00002004 // 0x00002004
DEF_IDENTIFIER( pm_REP_REJECT_CATEGORY, 0x00002005 ) // 0x00002005 // 0x00002005
DEF_IDENTIFIER( pm_REP_INFO_DIFF_APPLY, 0x00002000 ) // 0x00002000 // 0x00002000

// FILE: O:\PPP\Include\structs\s_gui.h
DEF_IDENTIFIER( pm_PROCPROTECTION_IFNO, 0x00000001 ) // 0x00000001 // 0x00000001

// FILE: O:\PPP\Include\structs\s_pdm.h
DEF_IDENTIFIER( pm_PDM_REPORT, 0x3041F582 ) // 0x3041F582 // 0x3041f582

// FILE: O:\PPP\Include\structs\s_urlflt.h
DEF_IDENTIFIER( msg_URL_FILTER_CHECK_URL, 0xD369D708 ) // 0xD369D708 // 0xd369d708

// FILE: O:\PPP\kav50\hostmsgs.h
DEF_IDENTIFIER( pm_CHECK_SERVICE_ACCESS_RIGHTS, 0xA3066AD3 ) // 0xA3066AD3 // 0xa3066ad3

// FILE: O:\PPP\MailCommon\Interceptors\outlookplugin\mcou_antispam\pmcMCOU_ANTISPAM.h
DEF_IDENTIFIER( pmMCOU_ANTISPAM_ENABLED, 0x40587C05 ) // 0x40587C05 // 0x40587c05

// FILE: O:\PPP\MailCommon\Interceptors\TrafficMonitor2\TrafficProtocoller.h
DEF_IDENTIFIER( pmSESSION_START, 0x80388A31 ) // 0x80388A31 // 0x80388a31
DEF_IDENTIFIER( pmDETECT, 0xA2A5A26A ) // 0xA2A5A26A // 0xa2a5a26a
DEF_IDENTIFIER( pmDETECT_EX, 265426241 ) // 0x0FD21541 // 0xfd21541
DEF_IDENTIFIER( pmPROCESS, 0x79705BE3 ) // 0x79705BE3 // 0x79705be3
DEF_IDENTIFIER( pmSESSION_STOP, 0x220AC645 ) // 0x220AC645 // 0x220ac645
DEF_IDENTIFIER( pmSESSION_PSEUDO_STOP, 0xF01B6B48 ) // 0xF01B6B48 // 0xf01b6b48
DEF_IDENTIFIER( pmPROCESS_FINISHED, 0x850EAC8C ) // 0x850EAC8C // 0x850eac8c
DEF_IDENTIFIER( pmKEEP_ALIVE, 0xA8BDD659 ) // 0xA8BDD659 // 0xa8bdd659
DEF_IDENTIFIER( pmSESSION_PSEUDO_STOP_REQUEST, 0x2276F3BA ) // 0x2276F3BA // 0x2276f3ba

// FILE: O:\Prague\Include\pr_sys.h
// ???: DEF_IDENTIFIER( msg_clsBROADCAST, (0x00000002l) ) // ERR: Cannot resolve 0x00000002l

