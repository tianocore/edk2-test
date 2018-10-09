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
  
    EmsProtoTcp.h
    
Abstract:

    Incude header files for protocol TCP

--*/

#ifndef __EMS_TCP_H__
#define __EMS_TCP_H__

#include "EmsTypes.h"
#include "EmsProtocols.h"

extern PROTOCOL_ENTRY_T TcpProtocol;

typedef struct _TCP_HEADER {
  UINT16  TcpSrcPort;
  UINT16  TcpDstPort;
  UINT32  TcpSeq;
  UINT32  TcpAck;
  UINT8   TcpDataOffset;
  UINT8   TcpCtrlFlag;
  UINT16  TcpWinSize;
  UINT16  TcpChecksum;
  UINT16  TcpUrgent;
} TCP_HEADER;

#endif
