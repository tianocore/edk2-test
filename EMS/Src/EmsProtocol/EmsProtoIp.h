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
  
    EmsProtoIp.h
    
Abstract:

    Incude header files for protocol IP

--*/

#ifndef __EMS_IP_H__
#define __EMS_IP_H__

#include "EmsTclInit.h"
#include "EmsTypes.h"
#include "EmsProtocols.h"

extern PROTOCOL_ENTRY_T IpProtocol;
extern UINT32           LocalIp;
extern UINT32           RemoteIp;

typedef struct _IP_HEADER {
  UINT8   IpIhl : 4,  /* Internet header length */
  IpVer : 4;          /* version */
  UINT8   IpTos;      /* type of service */
  UINT16  IpLen;      /* total length */
  UINT16  IpId;       /* identification */
  UINT16  IpFrag;     /* fragment information */
  UINT8   IpTtl;      /* time to live */
  UINT8   IpProto;    /* next level protocol */
  UINT16  IpSum;      /* checksum on header */
  UINT32  IpSrc;      /* source ip address */
  UINT32  IpDst;      /* destination ip address */
} IP_HEADER;

UINT16
GetIpId (
  VOID_P
  )
/*++

Routine Description:

  Get a IP Id

Arguments:

  None

Returns:

  Return the IP Id

--*/
;

#endif
