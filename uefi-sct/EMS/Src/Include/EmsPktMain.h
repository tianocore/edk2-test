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
  
    EmsPktMain.h
    
Abstract:

    Data definition for packet related functions

--*/

#ifndef __EMS_PACKET_H__
#define __EMS_PACKET_H__

#include "EmsTypes.h"
#include "EmsNet.h"

#define PACKET_NAME_SIZE  32

typedef struct _PACKET_T {
  INT8              Name[PACKET_NAME_SIZE]; // packet name
  UINT8             *Data;                  // packet content
  UINT32            DataLen;                // packet length
  struct timeval    Time;                   // time when captured the packet
  struct _PACKET_T  *Next;                  // next
} PACKET_T;

extern PACKET_T *PacketQueue;               /* Global packet queue */

PACKET_T        *
EmsPacketCreate (
  CONST INT8       *Name,
  UINT8            *Data,
  UINT32           Len,
  struct timeval   *Time
  )
/*++

Routine Description:

  Create a packet_t structure.

Arguments:

  Name  - packet name
  Data  - packet content
  Len   - packet length
  Time  - time when captured the packet

Returns:

  the pointer to packet created

--*/
;

PACKET_T        *
EmsPacketFindByName (
  CONST INT8 *Name
  )
/*++

Routine Description:

  Remove packet according to name

Arguments:

  Name  - Packet name

Returns:

  None

--*/
;

VOID_P
EmsPacketRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove packet according to name

Arguments:

  Name  - Packet name

Returns:

  None

--*/
;

VOID_P
EmsPacketRemove (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Remove packet from the queue of packet

Arguments:

  Packet  - The pointer to the packet

Returns:

  None

--*/
;

VOID_P
EmsPacketAdd (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Add a packet to the packet queue

Arguments:

  Packet  - The packet

Returns:

  None

--*/
;

VOID_P
EmsPacketDestroy (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Destroy a packet

Arguments:

  Packet  - The pointer to the packet

Returns:

  None

--*/
;

VOID_P
EmsPacketDump (
  INT8     *Buff,
  PACKET_T *Packet
  )
/*++

Routine Description:

  Dump the content of a packet

Arguments:

  Buff    - The data buffer for the packet
  Packet  - The pointer to the packet

Returns:

  None

--*/
;

PACKET_T        *
EmsPacketCreateAdd (
  CONST INT8      *Name,
  UINT8           *Data,
  UINT32          Len
  )
/*++

Routine Description:

  Create a packet and add it to packet queue

Arguments:

  Name  - Packet name
  Data  - The data of the packet
  Len   - The size of the packet data

Returns:

  The pointer to the new packet

--*/
;

VOID_P
EmsPacketQueueDestroy (
  VOID_P
  )
/*++

Routine Description:

  Destroy the packet queue

Arguments:

  None

Returns:

  None

--*/
;

#endif
