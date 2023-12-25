// klav_version.h
//

#ifndef klav_version_h_INCLUDED
#define klav_version_h_INCLUDED

#include <version/ver_product.h>

#ifndef KLAV_SDK_DATE_DAY
#define KLAV_SDK_DATE_DAY    0
#endif

#ifndef KLAV_SDK_DATE_MONTH
#define KLAV_SDK_DATE_MONTH  0
#endif

#ifndef KLAV_SDK_DATE_YEAR
#define KLAV_SDK_DATE_YEAR   0
#endif

#ifndef KLAV_SDK_DATE_HOUR
#define KLAV_SDK_DATE_HOUR   0
#endif

#ifndef KLAV_SDK_DATE_MINUTE
#define KLAV_SDK_DATE_MINUTE 0
#endif

#ifndef KLAV_SDK_DATE_SECOND
#define KLAV_SDK_DATE_SECOND 0
#endif

#define KLAV_SDK_DATE_DAY_STR    VER_ITOA(KLAV_SDK_DATE_DAY)
#define KLAV_SDK_DATE_MONTH_STR  VER_ITOA(KLAV_SDK_DATE_MONTH)
#define KLAV_SDK_DATE_YEAR_STR   VER_ITOA(KLAV_SDK_DATE_YEAR)
#define KLAV_SDK_DATE_HOUR_STR   VER_ITOA(KLAV_SDK_DATE_HOUR)
#define KLAV_SDK_DATE_MINUTE_STR VER_ITOA(KLAV_SDK_DATE_MINUTE)
#define KLAV_SDK_DATE_SECOND_STR VER_ITOA(KLAV_SDK_DATE_SECOND)

#define KLAV_SDK_DATE_STR \
	KLAV_SDK_DATE_DAY_STR "." \
	KLAV_SDK_DATE_MONTH_STR "." \
	KLAV_SDK_DATE_YEAR_STR " " \
	KLAV_SDK_DATE_HOUR_STR ":" \
	KLAV_SDK_DATE_MINUTE_STR

#define KLAV_SDK_VERSION_STR VER_PRODUCTVERSION_STR

#endif // klav_version_h_INCLUDED
