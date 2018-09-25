/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsUtilityString.h
    
Abstract:

    Incude header files for string related functions

--*/

#ifndef __EMS_STRING_H__
#define __EMS_STRING_H__

#include "stdlib.h"
#include "EmsTypes.h"
#include <string.h>
#include "tcl.h"

#define Upper(c)      (((c <= 'z') && (c >= 'a')) ? c + 'A' - 'a' : c)
#define IsDigit(c)    (c >= '0' && c <= '9')
#define IsHexDigit(c) ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))

extern
UINT32
AsciiToUint32 (
  IN INT8 c
  )
/*++

Routine Description:

  Convert character to its integer value

Arguments:

  Ch  - a character

Returns:

  its integer value or -1, if error

--*/
;

extern
UINT32
strcmp_i (
  IN CONST INT8 *s1,
  IN CONST INT8 *s2
  )
/*++

Routine Description:

  Case insensitive string compare routine.

Arguments:

  S1  - string 1
  S2  - string 2

Returns:

  0, if same

--*/
;

extern
UINT32
strncmp_i (
  IN CONST INT8   *s1,
  IN CONST INT8   *s2,
  IN UINT32       Len
  )
/*++

Routine Description:

  Case insensitive string compare routine.

Arguments:

  S1  - string 1
  S2  - string 2
  Len - length to compare

Returns:

  0, if same

--*/
;

extern
INT32
AsciiStringToUint32 (
  IN CONST INT8   *Str,
  IN OUT UINT32   *Value
  )
/*++

Routine Description:

  Convert a sting to integer value.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
AsciiStringToUint64 (
  IN CONST INT8   *Str,
  IN OUT UINT64   *Value
  )
/*++

Routine Description:

  Convert a sting to integer value.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
HexAsciiStringToUint32 (
  IN CONST INT8   *Str,
  IN OUT UINT32   *Value
  )
/*++

Routine Description:

  Convert a hex sting to integer value.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
AsciiStringToIpv4 (
  IN CONST INT8   *Str,
  IN OUT UINT32   *Value
  )
/*++

Routine Description:

  Convert a sting to IP address.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
AsciiStringToMac (
  IN CONST INT8  *Str,
  IN OUT UINT8   *Value
  )
/*++

Routine Description:

  Convert a sting to MAC address.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
Ipv4ToAsciiString (
  IN OUT  INT8   *Str,
  IN      UINT32 ip
  )
/*++

Routine Description:

  Convert IP address to a string.

Arguments:

  Str - string to convert
  ip  - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
Ipv6ToAsciiString (
  IN OUT INT8   *Str,
  IN     EMS_IPV6_ADDR *Value
  )
/*++

Routine Description:

  Convert IPv6 address to a string.

Arguments:

  Str - converse result
  Value  - IPv6 struct to be conversed

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
AsciiStringToIpv6 (
  IN CONST INT8   *Str,
  IN OUT EMS_IPV6_ADDR *Value
  )
/*++

Routine Description:

  Convert a sting to IPV6 address.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

extern
INT32
MacToAsciiString (
  IN OUT INT8    *Str,
  IN CONST UINT8 *mac
  )
/*++

Routine Description:

  Convert MAC address to a string.

Arguments:

  Str - string to convert
  Mac - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;

STATIC Tcl_CmdProc  GetValidString;

STATIC
INT32
GetValidString (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetValidString" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
;

VOID_P
StringUtilityInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS string related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

INT32
AsciiHexStrToUint16 (
  IN CONST INT8    *Str,
  IN OUT UINT16    *Value
  )
/*++

Routine Description:

  Convert a sting to integer value.

Arguments:

  Str   - string to convert
  Value - the converse result

Returns:

  the count of the bytes converted in the string.

--*/
;
#endif
