//=============================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03060  USA
//
// Copyright (c) 1998 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//=============================================================================

/*++

Copyright (c) 1990,91  Microsoft Corporation

Module Name:

    packon.h

Abstract:

    This file turns packing of structures on.  (That is, it disables
    automatic alignment of structure fields.)  An include file is needed
    because various compilers do this in different ways.

    The file packoff.h is the complement to this file.

Author:

    Chuck Lenzmeier (chuckl) 4-Mar-1990

Revision History:

    15-Apr-1991 JohnRo
        Created lint-able variant.
--*/

#pragma pack(1)                 // x86, MS compiler; MIPS, MIPS compiler

