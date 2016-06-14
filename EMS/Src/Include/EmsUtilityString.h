/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
