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
  
    EmsProtoEth.h
    
Abstract:

    Incude header files for protocol ETHER

--*/

#ifndef __EMS_ETH_H__
#define __EMS_ETH_H__

extern UINT8            RemoteEthaddr[6];
extern UINT8            LocalEthaddr[6];

extern PROTOCOL_ENTRY_T EthProtocol;

typedef struct _ETH_HEADER {
  UINT8   Dst[6];
  UINT8   Src[6];
  UINT16  Type;
} ETH_HEADER;

#endif
