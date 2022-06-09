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
 
  EftpRRQ.h
 
Abstract:

  Common defination for eftp RRQ client
 
--*/

#ifndef _EFI_EFTP_RRQ_H_
#define _EFI_EFTP_RRQ_H_

#define RRQ_LOST_SIZE_LIMIT   (4 * 1024 * 1024)

#define RRQ_LOST_THRESH       3

#define RRQ_LOST_THRESH_BYTES (500 * 1024 * 1024)

#define RRQ_PASSIVE_BACKOFF   20

//
// Init a silent shutdown for RRQ. When silent shutdown,
// the instance will discard all the received packets, and
// send out nothing.
//
#define RRQ_SILENT_SHUTDOWN(Private) \
  do { \
    (Private)->State = EFTP_TIME_WAIT; \
    EftpSetTimer ((Private), 0, EFTP_TIMEWAIT_TIME); \
  } while (0)

  //
  // Init a loud shutdown for RRQ. When loud shutdown, the instance will
  // discard any received packet, then send out last control packet.
  //
#define RRQ_LOUD_SHUTDOWN(Private) \
  do { \
    ASSERT (Private->State != EFTP_TIME_WAIT); \
    (Private)->State = EFTP_RRQ_CLOSEING; \
    EftpSetTimer ((Private), EFTP_CLOSEING_TIME, 0); \
  } while (0)

//
// EFTP Roles for RRQ. WRQ doesn't has roles
//
typedef enum {
  EFTP_RRQ_ROLE_INIT,	           // Every Mftp4 downloading instance starts here
  EFTP_RRQ_ROLE_ACTIVE,      // Eftp instance is doing unicast download or is the active client in multicast download	
} EFTP_RRQ_ROLE_TYPE;

typedef struct _EFTP_LOSTBLOCK_ENTRY {
  UINT64          Start;
  UINT64          End;
  NET_LIST_ENTRY  Entry;
} EFTP_LOSTBLOCK_ENTRY;

typedef
EFI_STATUS
(*EFTP_RRQ_RCV_DATA) (
  EFTP_IO_PRIVATE * Private,
  EFI_EFTP_PACKET * Packet,
  UINT32          PacketLen
  );

typedef
EFI_STATUS
(*EFTP_RRQ_RCV_CTRL) (
  EFTP_IO_PRIVATE * Private,
  EFI_EFTP_PACKET * Packet,
  UINT32          PacketLen
  );

typedef struct _EFTP_RRQ_ROLE {
  EFTP_RRQ_ROLE_TYPE  Type;
  EFTP_RRQ_RCV_DATA   EftpRrqRcvData;
  EFTP_RRQ_RCV_CTRL   EftpRrqRcvError;
  EFTP_RRQ_RCV_CTRL   EftpRrqRcvOack;
  EFI_EVENT_NOTIFY    EftpRrqTimer;
} EFTP_RRQ_ROLE;

typedef struct _EFTP_RRQ_STATE {
  NET_LIST_ENTRY  LostPacketList; // all the lost packet when passive
  UINT32          LostListSize;

  EFTP_RRQ_ROLE   Role;           // current role, being init, active, passive or smart
} EFTP_RRQ_STATE;

//
// Vars specific to EftpGetInfo. GetInfo is implemented using RRQ.
//
typedef struct _EFTP_GETINFO_STATE {
  UINTN           *GetInfoPacketLen;
  EFI_EFTP_PACKET **GetInfoPacket;
  EFI_STATUS      Status;
} EFTP_GETINFO_STATE;

EFTP_RRQ_STATE  *
EftpInitRrqState (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Init the Eftp instance for download

Arguments:

  Private : Eftp instance private data

Returns:

  NULL : Failed to allocate buffer for RRQ state
  Point to EFTP_RRQ_STATE: RRQ state allocated and initialized

--*/
;

EFI_STATUS
EFIAPI
EftpBuildRrq (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT16           OpCode
  )
/*++

Routine Description:

  Build a RRQ packet from the user info, and save it at Private->Request

Arguments:

  Private  : Eftp instance private data
  OpCode : OpCode to use when build request packet. It can be a RRQ or ReadDirectory

Returns:

  EFI_OUT_OF_RESOURCES : Failed to build the request packet
  EFI_SUCCESS                  :  Successfully build the request packet

--*/
;

VOID
EftpRrqRxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Receive callback function called by UDP when packet is available.
  It dispatches the packet according to it type.

Arguments:

  Event    : Event signaled by UDP 
  Context : The event's context, it is a point to EFTP_COMPLETION_TOKEN

Returns:

  None

--*/
;

VOID EftpRrqTimer (IN EFI_EVENT Event, IN VOID *Context)
/*++

Routine Description:

  Timer function to deal with download timeout

Arguments:

  Event     : Event signaled 
  Context  : The context of the event, it is a point to EFTP_IO_PRIVATE

Returns:

  None

--*/

;

VOID
EftpRrqCleanUp (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Gracefully shutdown the eftp instance. It releases the various resources
  then signal the user event.

Arguments:

  Private  : Eftp instance private data

Returns:

  None
--*/
;

VOID
EftpRrqChangeRole (
  IN EFTP_RRQ_ROLE_TYPE Type,
  IN EFTP_RRQ_STATE     *State
  )
/*++

Routine Description:

  Change the role of RRQ client

Arguments:

  Type  : The role to change to
  State : The Eftp instance's RRQ specific data

Returns:

  None

--*/
;

#endif
