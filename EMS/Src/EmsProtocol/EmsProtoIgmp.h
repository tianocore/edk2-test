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
  
    EmsProtoIgmp.h
    
Abstract:

    Incude header files for protocol IGMP

--*/

#ifndef __EMS_IGMP_H__
#define __EMS_IGMP_H__

#include "EmsTclInit.h"
#include "EmsTypes.h"
#include "EmsProtoIp.h"
#include "EmsProtocols.h"

#define IGMP_MEMBERSHIP_QUERY     0x11  /* membership query */
#define IGMP_V1_MEMBERSHIP_REPORT 0x12  /* Ver1 membership report */
#define IGMP_V2_MEMBERSHIP_REPORT 0x16  /* Ver2 membership report */
#define IGMP_LEAVE_GROUP          0x17  /* Leave group message */

extern PROTOCOL_ENTRY_T IgmpProtocol;

typedef struct _IGMP_HEADER {
  UINT8   IgmpType;                     /* type */
  UINT8   IgmpCode;                     /* Max response time */
  UINT16  IgmpSum;                      /* checksum */
  UINT32  IgmpGroup;                    /* host IP */
} IGMP_HEADER;

#endif
