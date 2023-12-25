//--------------------------------------------------------------------
// Kaspersky lab application info file
// Copyright (C) 2003 Kaspersky Labs.
// All rights reserved.
//
// Application Id             : 1110
// Application Name           : Kaspersky SMTP-Gateway (Windows)
// Application Version        : 
// Version type               : Release
// App info structure version : 1
//--------------------------------------------------------------------

#include <appinfo_struct.h>

static _product_info_t PRODUCTS_LIST[] =
{
	{
		135, 
		"Kaspersky Anti-Virus 5 Business Optimal", 
		"", 
		0 
	}
};



_app_info_t AppInfo = 
{
	"Kaspersky lab application info file",       // Description
	1,                                           // App info structure version
	{ 2003,  7,  9 },                            // Date create
	aitApplicationInfo,                          // application info type (app or component)
	1110,                                        // Application Id
	"Kaspersky SMTP-Gateway (Windows)",          // Application Name
	"",                                          // Application version
	1,                                           // 0 - beta, not 0 - release (app only)
	{  0, 0 },                                   // Components list (app only)
	{  0, 0 },                                   // Applications list (component only)
	{  1, PRODUCTS_LIST },                       // Products list
	{  0, 0 },                                   // Public key list
	{  0, 0 }                                    // Legacy applications compatibility info
};


