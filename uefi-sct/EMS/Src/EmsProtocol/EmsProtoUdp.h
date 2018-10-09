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
  
    EmsProtoUdp.h
    
Abstract:

    Incude header files for protocol UD

--*/

#ifndef __EMS_UDP_H__
#define __EMS_UDP_H__

#include "EmsTypes.h"
#include "EmsProtocols.h"

extern PROTOCOL_ENTRY_T UdpProtocol;
typedef struct _UDP_HEADER {
  UINT16  UdpSrcPort;
  UINT16  UdpDstPort;
  UINT16  UdpLength;
  UINT16  UdpChecksum;
} UDP_HEADER;

#endif
