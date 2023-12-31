/*******************************************************************************
  Proj: libosr (Optical Symbols Recognition library)
  --------------------------------------------------------------------------- 
  File: osr_version.h
  Created: 2006/09/08
  Desc: libosr version info
  --------------------------------------------------------------------------- 
  Evgeny P. Smirnov, Evgeny.Smirnov@kaspersky.com
********************************************************************************/
//--------------------------------------------------------------------------------------------------------------------//
#ifndef OSR_VER
//--------------------------------------------------------------------------------------------------------------------//

#define OSR_VER 3.6

#define OSR_VAL_TO_TEXT_0(s) #s
#define OSR_VAL_TO_TEXT(s) OSR_VAL_TO_TEXT_0(s)

#define OSR_VER_TXT OSR_VAL_TO_TEXT(OSR_VER)
//--------------------------------------------------------------------------------------------------------------------//
#endif // OSR_VER
//--------------------------------------------------------------------------------------------------------------------//
