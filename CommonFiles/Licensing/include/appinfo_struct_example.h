/*

  Application info autogenerated file

  Application id             : 87
  Application name           : Application name
  App info structure version : 1
  Application version        : 5.0
  Version type               : release

*/

#include "appinfo_struct.h"

static component_info_t COMPONENTS_LIST[] = {{23, 20}, {45, 10}, {67, 30}};

static product_info_t   PRODUCTS_LIST[] = 
{
  {
    55,
    "Product name 1",
    "5",
    1234
  },

  {
    77,
    "Product name 2",
    "5",
    5678
  }
};


static pub_key_GUID_t PUBLIC_KEY_GUIDS_LIST[] =
{
  {
    34,
    "Developer account 1",
    "Developer GUID1",
    "PubStr1",
    "PubStr2",
    "PubStr3",
    "PubStr4"
  }
};

static app_compat_info_t APP_COMPAT_LIST[] =
{
  {
    99,
    "Legacy application name 1"
  },
  {
    88,
    "Legacy application name 2"
  }
};

struct app_info_t AppInfo =
{
  "Kaspersky Lab application info",   // description
  1,                                  // app info structure version
  {2003, 07, 01},                     // MyAppInfo creation date
  87,                                 // application id 
  "Application name",                 // application name
  "5.0",                              // application version 
  1,                                  // release
  {3, COMPONENTS_LIST},               // components list
  {2, PRODUCTS_LIST},                 // products list 
  {1, PUBLIC_KEY_GUIDS_LIST}          // public key GUIDs list
  {2, APP_COMPAT_LIST}                // legacy applications compatibility info
};
