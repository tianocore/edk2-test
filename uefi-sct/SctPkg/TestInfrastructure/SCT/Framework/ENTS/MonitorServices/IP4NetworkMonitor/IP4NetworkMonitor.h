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

  IP4NetworkMonitor.h

Abstract:

  NetworkTest Ip4 Monitor services declarations.

--*/

#ifndef _IP4_NETWORK_MONITOR_H_
#define _IP4_NETWORK_MONITOR_H_

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)
#include EFI_PROTOCOL_DEFINITION(Ip4)

#define ENTS_VENDOR_GUID \
  { \
    0x868b4f16, 0xc83a, 0x4205, 0xa9, 0x3c, 0x3f, 0x51, 0xcf, 0x7f, 0x61, 0xc0 \
  }

#define ENTS_SERVER_IPV4_ADDRESS_NAME L"ServerIp"

#define ENTS_LINK_SEQUENCE_NAME       L"LinkSequence"
#define ENTS_IP4_MONITOR_NAME         L"Ip4"

extern EFI_GUID gEntsVendorGuid;

#pragma pack(1)
typedef union {
  struct {
    UINT32  SeqId : 32;
    UINT32  Offset : 16;
    UINT32  OpCode : 8;
    UINT32  Rsvd : 7;
    UINT32  MF : 1;
  } Flag;
  UINT64  LLFlag;
} EAS_IP4_FRAG_FLAG;
#pragma pack()

#define LINK_OPERATION_PROBE      0x01
#define LINK_OPERATION_PROBE_ACK  0x02

#define LINK_OPERATION_DATA       0x11
#define LINK_OPERATION_DATA_ACK   0x12

#define LL_TIMEOUT                1000000 // uSecond
typedef enum {
  WaitForPacket,
  SendoutPacket,
} LINK_LAYER_STATUS;

EFI_STATUS
EFIAPI
IP4NetworkSaveContext(
  EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  This func is to save the communcation context into flash 
    (now, will save ServerMacAddr, LastSendSequence & AppSequence).

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  Others               - Some failure happened.
  
--*/
;

EFI_STATUS
EFIAPI
IP4NetworkRestoreContext(
  IN EFI_ENTS_MONITOR_PROTOCOL *This
  )
/*++

Routine Description:

  This func is to load the communcation context from flash to local variable
    (now, will load ServerMacAddr, LastSendSequence & AppSequence from flash).

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  Others               - Some failure happened.
  
--*/
;

//
// External functions declarations
//
EFI_STATUS
EFIAPI
IP4NetworkListener (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN OUT UINTN                     *Size,
  OUT CHAR16                       **Buffer
  )
/*++

Routine Description:

  This func is to read data from IP4 network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Size    - To indicate buffer length
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EFIAPI
IP4NetworkSender (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN CHAR16                        *Buffer
  )
/*++

Routine Description:

  This func is to write data to IP4 network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_ACCESS_DENIED    - Cannot send out packet in state SendOutPacket.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.
  
--*/
;

EFI_STATUS
EFIAPI
InitIP4Network (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Initialize IP4 Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EFIAPI
ResetIP4Network (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Reset IP4 Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

#endif
