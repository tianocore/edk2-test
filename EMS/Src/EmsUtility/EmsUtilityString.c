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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsUtilityString.c
    
Abstract:

    Implementation of sting related functions

--*/

#include <stdio.h>

#include "EmsUtilityString.h"
#include "EmsProtocols.h"

UINT32
AsciiToUint32 (
  IN INT8 Ch
  )
/*++

Routine Description:

  Convert character to its integer value

Arguments:

  Ch  - a character

Returns:

  its integer value or -1, if error

--*/
{
  if (Ch >= '0' && Ch <= '9') {
    return Ch - '0';
  }

  if (Ch >= 'a' && Ch <= 'f') {
    return Ch - 'a' + 10;
  }

  if (Ch >= 'A' && Ch <= 'F') {
    return Ch - 'A' + 10;
  }

  return -1;
}

UINT32
strcmp_i (
  IN CONST INT8 *S1,
  IN CONST INT8 *S2
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
{
  while (Upper (*S1) == Upper (*S2)) {
    S2++;
    if (*S1++ == 0) {
      return 0;
    }
  }

  return * (CONST UINT8 *) S1 -*(CONST UINT8 *) S2;
}

UINT32
strncmp_i (
  IN CONST INT8   *S1,
  IN CONST INT8   *S2,
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
{
  while (Len && (Upper (*S1) == Upper (*S2))) {
    S2++;
    if (*S1++ == 0) {
      return 0;
    }

    Len--;
  }

  return Len ? (*(CONST UINT8 *) S1 -*(CONST UINT8 *) S2) : 0;
}

INT32
AsciiStringToUint32 (
  IN CONST INT8    *Str,
  IN OUT UINT32    *Value
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
{
  UINT32  Index;
  UINT32  Temp;
  BOOLEAN negative;

  Index = 0;
  Temp  = 0;

  if (Str[0] == '-') {
    negative  = TRUE;
    Index     = 1;
  } else {
    negative = FALSE;
  }

  if (Str[Index] == '0' && (Str[Index + 1] == 'x' || Str[Index + 1] == 'X')) {
    Index += 2;
    while (IsDigit (Str[Index]) || IsHexDigit (Str[Index])) {
      Temp = Temp * 16 + AsciiToUint32 (Str[Index]);
      Index += 1;
    }

    *Value = Temp;
    return Index;
  }

  while (IsDigit (Str[Index])) {
    Temp = Temp * 10 + AsciiToUint32 (Str[Index]);
    Index += 1;
  }

  if (negative) {
    Temp = (UINT32) (-Temp);
  }

  *Value = Temp;
  return Index;
}

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
{
  UINT32  Index;
  UINT64  Temp;

  Index = 0;
  Temp  = 0;

  if (Str[Index] == '0' && (Str[Index + 1] == 'x' || Str[Index + 1] == 'X')) {
    Index += 2;
    while (IsDigit (Str[Index]) || IsHexDigit (Str[Index])) {
      Temp = Temp * 16 + AsciiToUint32 (Str[Index]);
      Index += 1;
    }

    *Value = Temp;
    return Index;
  }

  while (IsDigit (Str[Index])) {
    Temp = Temp * 10 + AsciiToUint32 (Str[Index]);
    Index += 1;
  }

  *Value = Temp;
  return Index;
}

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
{
  UINT32  Index;
  UINT32  Temp;
  Index = 0;
  Temp  = 0;

  while (IsDigit (Str[Index]) || IsHexDigit (Str[Index])) {
    Temp = Temp * 16 + AsciiToUint32 (Str[Index]);
    Index += 1;
  }

  *Value = Temp;
  return Index;
}

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
{
  UINT8   Index;
  UINT32  Len;
  INT32   templen;
  CONST INT8    *s;
  UINT32  addr;
  UINT32  Temp;

  Len     = 0;
  s       = Str;
  addr    = 0;

  *Value  = 0;
  for (Index = 0; Index < 4; Index++) {
    templen = AsciiStringToUint32 (s, &Temp);
    if (templen <= 0 || Temp > 255) {
      goto ErrorExit;
    }

    addr = (addr << 8) + Temp;
    Len += templen;
    s = &Str[Len];
    if (Index == 3) {
      break;
    }

    if (s[0] != '.') {
      goto ErrorExit;
    }

    Len++;
    s = &Str[Len];
  }

  *Value = addr;
  return Len;
ErrorExit:
  return 0;
}

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
{
  UINT8   Index;
  UINT32  Len;
  INT32   templen;
  CONST INT8    *s;
  UINT32  Temp;

  Len     = 0;
  s       = Str;

  *Value  = 0;
  for (Index = 0; Index < 6; Index++) {
    templen = HexAsciiStringToUint32 (s, &Temp);
    if (templen <= 0 || Temp > 255) {
      goto ErrorExit;
    }

    Value[Index] = Temp;
    Len += templen;
    s = &Str[Len];
    if (Index == 5) {
      break;
    }

    if (s[0] != ':') {
      goto ErrorExit;
    }

    Len++;
    s = &Str[Len];
  }

  return Len;
ErrorExit:
  return 0;
}

INT32
Ipv4ToAsciiString (
  IN OUT INT8   *Str,
  IN     UINT32 ip
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
{
  INT32 Len;

  Len = sprintf (
          Str,
          "%d.%d.%d.%d",
          ip >> 24,
          ip >> 16 & 0xFF,
          ip >> 8 & 0xFF,
          ip & 0xFF
          );
  return Len;
}

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
{
  INT32 Len;

  Len = sprintf (
          Str,
          "%x:%x:%x:%x:%x:%x:%x:%x",
          Value->__u6_addr.__u6_addr16[0],
          Value->__u6_addr.__u6_addr16[1],
          Value->__u6_addr.__u6_addr16[2],
          Value->__u6_addr.__u6_addr16[3],
          Value->__u6_addr.__u6_addr16[4],
          Value->__u6_addr.__u6_addr16[5],
          Value->__u6_addr.__u6_addr16[6],
          Value->__u6_addr.__u6_addr16[7]          
          );
  return Len;
}

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
{
  INT8    Index;
  UINT32  Len;
  INT32   templen;
  INT8    pos;        //recorde the position of "::"
  INT8    posIndex;
  CONST INT8    *s;
  UINT16  Temp;
  BOOLEAN ellFlag;

  Len     = 0;
  s       = Str;
  pos     = -1;
  ellFlag = 0;
  templen = 0;
  
  for (Index = 0; Index < 8; Index++){
    Value->__u6_addr.__u6_addr16[Index] = 0;
  }
  
  Index = 0;
  while (Len <= strlen(Str)){
  	//
  	// If string begin with "::"
  	//
  	if (s[0]== ':'){
	  if (s[1] == ':') {
        if (!ellFlag) {
 		  ellFlag = 1;
		  s++;
		  Len++;
		  pos = Index;
 	    } else {
		  goto ErrorExit;
	    }
	  }	
	  s++;
	  Len++;
	}
	//
	// If the Str end with "::"
	//
	if (Len == strlen (Str)){
      break;
	}
	templen = AsciiHexStrToUint16 (s, &Temp);
	if (templen <=0 || Temp > 65535){
      goto ErrorExit;
	}
	
	Value->__u6_addr.__u6_addr16[Index] = Temp;	
	Index++;
	Len += templen;
	s = &Str[Len];
    if (Index == 8) {
      break;
	}
  }
  
  if (pos != -1){
    if (pos != Index){
      for (posIndex = Index-1 ; posIndex >= pos; posIndex--){
	  	Value->__u6_addr.__u6_addr16[posIndex + 7 - Index + 1] = Value->__u6_addr.__u6_addr16[posIndex];
	  }
	  for (posIndex = 0; posIndex <= 7 - Index; posIndex++){
	  	Value->__u6_addr.__u6_addr16[pos + posIndex] = 0;
	  }
	}
  }
  return Len;
  
ErrorExit:
  return 0;
}

INT32
MacToAsciiString (
  IN OUT INT8    *Str,
  IN CONST UINT8 *Mac
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
{
  INT32 Len;

  Len = sprintf (
          Str,
          "%02x:%02x:%02x:%02x:%02x:%02x",
          Mac[0],
          Mac[1],
          Mac[2],
          Mac[3],
          Mac[4],
          Mac[5]
          );
  return Len;
}

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
{
  INT8  ErrorBuff[512];

  if(Argc != 2)
  {
    sprintf (ErrorBuff, "Syntax of GetAsiciiString - GetAsiciiString String\n");
    goto ErrorExit;
  }

  /*
   * what is the matter? Argv[*][*] is not char type ?
   */
  if(Argv[1][0] == 0xFFFFFFEF && 
  	Argv[1][1] == 0xFFFFFFBB && 
  	Argv[1][2] == 0xFFFFFFBF)
    Tcl_AppendResult (Interp, Argv[1] + 3, (INT8 *)NULL);
  else
  	Tcl_AppendResult (Interp, Argv[1], (INT8 *)NULL);

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

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
{
  Tcl_CreateCommand (
    Interp,
    "GetValidString",
    GetValidString,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}

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
{
  UINT32  Index;
  UINT16  Temp;

  Index = 0;
  Temp  = 0;


  if (Str[Index] == '0' && (Str[Index + 1] == 'x' || Str[Index + 1] == 'X')) {
    Index += 2; 
  }
  while (IsDigit (Str[Index]) || IsHexDigit (Str[Index])) {
    Temp = Temp * 16 + AsciiToUint32 (Str[Index]);
    Index += 1;
  }
  
  *Value = Temp;
  return Index;
}

