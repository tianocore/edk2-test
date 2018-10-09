/** @file
 
  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsProtoDhcp.h
    
Abstract:

    Incude header files for protocol DHCP

--*/

#ifndef __EMS_DHCP_H__
#define __EMS_DHCP_H__

#include "EmsTclInit.h"
#include "EmsTypes.h"
#include "EmsProtoIp.h"
#include "EmsProtocols.h"

extern PROTOCOL_ENTRY_T DhcpProtocol;

typedef struct _DHCP_HEADER {
  UINT8   DhcpOp;         // opcode
  UINT8   DhcpHType;      // hardware address type
  UINT8   DhcpHLen;       // hardware address length
  UINT8   DhcpHops;       // used by proxy servers
  UINT32  DhcpXid;        // transaction ID
  UINT16  DhcpSecs;       // number of seconds since trying to bootstrap
  UINT16  DhcpFlags;      // flags for DHCP, unused for BOOTP
  UINT32  DhcpCIaddr;     // client's IP
  UINT32  DhcpYIaddr;     // your IP
  UINT32  DhcpSIaddr;     // server's IP
  UINT32  DhcpGIaddr;     // gateway IP
  UINT8   DhcpChAddr[16]; // client hardware address
  UINT8   DhcpSName[64];  // server host name
  UINT8   DhcpFile[128];  // boot file name
  UINT32  DhcpMagic;      // BOOTP magic header
} DHCP_HEADER;

typedef
UINT32
VALIDATE_OPTIONS_T (
  INT8          *Value,   // value to validate
  INT8          *StripValue
  );

typedef
BOOLEAN
PARSE_OPTIONS_T (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  );

typedef struct _DHCP_OPTION {
  INT8                *Name;
  INT8                Code;
  INT8                Len;
  VALIDATE_OPTIONS_T  *Validate;
  PARSE_OPTIONS_T     *Parse;
} DHCP_OPTION;

typedef struct _DHCP_OPTION_TLV {
  INT8  Type;
  INT8  Len;
  UINT8 *Value;
} DHCP_OPTION_TLV;

INT8
DhcpBuildOption (
  INT8 *Type,
  INT8 *Value,
  INT8 **Options
  )
/*++

Routine Description:

  Build DHCP option

Arguments:

  Type    - The type of the DHCP option
  Value   - The value of the option
  Options - Return the option result

Returns:

  The size of the option

--*/
;

#endif
