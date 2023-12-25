////////////////////////////////////////////////////////////////////
//
//  VER_KL.H
//  Company Version definitions
//  Project AVP
//  Alexey de Mont de Rique [graf@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs.
//
////////////////////////////////////////////////////////////////////

#ifndef __VER_KL_H
#define __VER_KL_H

#include "ver_itoa.h"

#undef  VER_COMPANYNAME_STR
#undef  VER_LEGALCOPYRIGHT_STR
#undef  VER_TRADEMARKS_STR
#undef  VER_LEGALTRADEMARKS_STR

#undef  VER_PRODUCTVERSION
#undef  VER_PRODUCTVERSION_STR
#undef  VER_FILEVERSION
#undef  VER_FILEVERSION_STR
#undef  VER_COMMENTS_STR

#define VER_COMPANYNAME_STR      "Kaspersky Lab"
#define VER_LEGALCOPYRIGHT_STR   "Copyright � " VER_COMPANYNAME_STR " 1996-2006."
#define VER_TRADEMARKS_STR       "Kaspersky Anti-Virus �"
#define VER_LEGALTRADEMARKS_STR  VER_TRADEMARKS_STR " is registered trademark of " VER_COMPANYNAME_STR "."

#ifndef VER_PORTIONCOPYRIGHT_STR
#define VER_PORTIONCOPYRIGHT_STR "Portion copyright � "
#define VER_DF_STR               "F-Secure"
#define VER_LC_STR               "LanCrypto"
#endif


#ifdef _DLL

#ifndef VER_FILETYPE
#define VER_FILETYPE               VFT_DLL
#endif

#ifndef VER_INTERNALEXTENSION_STR
#define VER_INTERNALEXTENSION_STR "DLL"
#endif

#else  //not _DLL

#ifndef VER_FILETYPE
#define VER_FILETYPE               VFT_APP
#endif

#ifndef VER_INTERNALEXTENSION_STR
#define VER_INTERNALEXTENSION_STR "EXE"
#endif

#endif //not _DLL


#ifndef VER_ORIGINALFILENAME_STR
#define VER_ORIGINALFILENAME_STR VER_INTERNALNAME_STR "." VER_INTERNALEXTENSION_STR
#endif

#ifndef VER_FILEDESCRIPTION_STR
#define VER_FILEDESCRIPTION_STR            VER_ORIGINALFILENAME_STR
#endif

#ifndef VER_PRODUCTVERSION_HIGH
#define VER_PRODUCTVERSION_HIGH            1
#endif

#ifndef VER_PRODUCTVERSION_LOW
#define VER_PRODUCTVERSION_LOW             0
#endif

#ifndef VER_PRODUCTVERSION_BUILD
#define VER_PRODUCTVERSION_BUILD           0
#endif

#ifndef VER_PRODUCTVERSION_COMPILATION
#define VER_PRODUCTVERSION_COMPILATION     0
#endif


#ifndef VER_FILEVERSION_HIGH
#define VER_FILEVERSION_HIGH               VER_PRODUCTVERSION_HIGH
#endif

#ifndef VER_FILEVERSION_LOW
#define VER_FILEVERSION_LOW                VER_PRODUCTVERSION_LOW
#endif

#ifndef VER_FILEVERSION_BUILD
#define VER_FILEVERSION_BUILD              VER_PRODUCTVERSION_BUILD
#endif

#ifndef VER_FILEVERSION_COMPILATION
#define VER_FILEVERSION_COMPILATION        VER_PRODUCTVERSION_COMPILATION
#endif

#define VER_PRODUCTVERSION_HIGH_STR        VER_ITOA( VER_PRODUCTVERSION_HIGH)
#define VER_PRODUCTVERSION_LOW_STR         VER_ITOA( VER_PRODUCTVERSION_LOW)
#define VER_PRODUCTVERSION_BUILD_STR       VER_ITOA( VER_PRODUCTVERSION_BUILD)
#define VER_PRODUCTVERSION_COMPILATION_STR VER_ITOA( VER_PRODUCTVERSION_COMPILATION)

#define VER_FILEVERSION_HIGH_STR           VER_ITOA( VER_FILEVERSION_HIGH)
#define VER_FILEVERSION_LOW_STR            VER_ITOA( VER_FILEVERSION_LOW)
#define VER_FILEVERSION_BUILD_STR          VER_ITOA( VER_FILEVERSION_BUILD)
#define VER_FILEVERSION_COMPILATION_STR    VER_ITOA( VER_FILEVERSION_COMPILATION)

#define VER_PRODUCTVERSION       VER_PRODUCTVERSION_HIGH,VER_PRODUCTVERSION_LOW,VER_PRODUCTVERSION_BUILD,VER_PRODUCTVERSION_COMPILATION
#define VER_PRODUCTVERSION_STR   VER_PRODUCTVERSION_HIGH_STR "." VER_PRODUCTVERSION_LOW_STR "." VER_PRODUCTVERSION_BUILD_STR "." VER_PRODUCTVERSION_COMPILATION_STR

#define VER_FILEVERSION          VER_FILEVERSION_HIGH,VER_FILEVERSION_LOW,VER_FILEVERSION_BUILD,VER_FILEVERSION_COMPILATION
#define VER_FILEVERSION_STR      VER_FILEVERSION_HIGH_STR "." VER_FILEVERSION_LOW_STR "." VER_FILEVERSION_BUILD_STR "." VER_FILEVERSION_COMPILATION_STR

#ifdef RC_INVOKED
#include "ver_kl.ver"
#endif

#endif//__VER_KL_H
