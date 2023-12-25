/*
 * uuid.h -- private header file for uuids
 * 
 * Copyright (C) 1996, 1997 Theodore Ts'o.
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the GNU 
 * Library General Public License.
 * %End-Header%
 */

#include <sys/types.h>
#ifdef WIN32
//#include <afxwin.>
typedef unsigned long __u32;
typedef unsigned short __u16;
typedef unsigned char __u8;
#endif
#if defined(__unix) && !defined(__FreeBSD__)
	#include <asm/types.h>
#endif

#if defined(N_PLAT_NLM) || defined(__FreeBSD__)
//#include <afxwin.>
 typedef unsigned long __u32;
 typedef unsigned short __u16;
 typedef unsigned char __u8;
#endif

#include "uuid.h"

/*
 * Offset between 15-Oct-1582 and 1-Jan-70
 */
#define TIME_OFFSET_HIGH 0x01B21DD2
#define TIME_OFFSET_LOW  0x13814000

struct uuid {
	__u32	time_low;
	__u16	time_mid;
	__u16	time_hi_and_version;
	__u16	clock_seq;
	__u8	node[6];
};


/*
 * prototypes
 */
extern "C" {
void uuid_pack(const struct uuid *uu, uuid_t& ptr);
void uuid_unpack(uuid_t& in, struct uuid *uu);
}



