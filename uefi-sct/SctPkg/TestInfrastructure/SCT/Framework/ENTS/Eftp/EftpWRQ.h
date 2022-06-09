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
 
  EftpWRQ.h
 
Abstract:

  WRQ procedure
 
--*/

#ifndef _EFI_EFTP_WRQ_H_
#define _EFI_EFTP_WRQ_H_

//
// Init a silent shutdown.
// A silent shutdown will discard any incoming packet, and send nothing
//
#define WRQ_SILENT_SHUTDOWN(Private) \
  do { \
    (Private)->State = EFTP_TIME_WAIT; \
    EftpSetTimer ((Private), 0, EFTP_TIMEWAIT_TIME); \
  } while (0)

  //
  // Init a loud shutdown
  // A loud shutdown will discard any incoming packet, and send out last control packet
  //
#define WRQ_LOUD_SHUTDOWN(Private) \
  do { \
    ASSERT ((Private)->State != EFTP_TIME_WAIT); \
    (Private)->State = EFTP_WRQ_CLOSEING; \
    EftpSetTimer ((Private), EFTP_CLOSEING_TIME, 0); \
  } while (0)


//
// Vars specific to WRQ
//
typedef struct _EFTP_WRQ_STATE {
  EFTP_PACKET_BUFFER  *LastData;  // saved for retransmission
} EFTP_WRQ_STATE;

EFTP_WRQ_STATE  *
EftpInitWrqState (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Init a Eftp instance for WRQ, or uploading

Arguments:

  Private - Eftp instance private data

Returns:

  NULL: Failed to allocate buffer for WRQ state
  Point to the newly allocated WRQ data structure: On success

--*/
;

VOID
EftpWrqRxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Callback function by UDP when it receives packets for the instance.
  It will dispatch the packet to different routines for process.

Arguments:

  Event   : Event signalled by UDP
  Context : Event's context, it is a point to EFTP_COMPLETION_TOKEN

Returns:

  None 

--*/
;

EFI_STATUS
EFIAPI
EftpBuildWrq (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Build a WRQ packet from the user info, and save it at Private->Request

Arguments:

  Private - Eftp instance private data

Returns:

  EFI_OUT_OF_RESOURCES: Failed to allocate buffer for WRQ packet
  EFI_SUCCESS : WRQ packet allocated and initialized

--*/
;

VOID
EftpWrqTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Timer function when timeout happened during uploading.
  It will either retransmit the last packet, transit the state,
  or clean up the instance
  
Arguments:

  Event   : Timer event got signaled
  Context : The event's context. It is a point to EFTP_IO_PRIVATE

Returns:

  Event callback returns nothing

--*/
;

VOID
EftpWrqCleanUp (
  IN EFTP_IO_PRIVATE*private
  )
/*++

Routine Description:

  Gracefully shutdown the Eftp instance: release various resources
  and signal the user event

Arguments:

  Private : Eftp instance private data

Returns:

  None

--*/
;

#endif
