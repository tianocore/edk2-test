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
