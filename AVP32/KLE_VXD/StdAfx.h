// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FEF9B514_2968_4469_BED4_175909CE1329__INCLUDED_)
#define AFX_STDAFX_H__FEF9B514_2968_4469_BED4_175909CE1329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <Version/ver_avp.h>
#include "kle_vxd.h"
#include <Stuff/_carray.h>
#include <ScanAPI/BaseAPI.h>
#include <ScanAPI/RetFlags.h>
#include <ScanAPI/avp_msg.h>
#include <Sign/sign.h>
#include <serialize/kldtser.h>
#include <AvpVndID.h>
#include "file_io.h"

#include "../KLE/KLEapi.h"
#include "../KLE/KLE_IPL.h"


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FEF9B514_2968_4469_BED4_175909CE1329__INCLUDED_)
