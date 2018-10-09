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
  
    EmsPktCapture.h
    
Abstract:

    Data definition for packet capture function

--*/

#ifndef __EMS_CAPTURE_H__
#define __EMS_CAPTURE_H__

#include <EmsTypes.h>
#include <EmsTclInit.h>
#include <EmsNet.h>

#include "EmsVtcpNamedList.h"

extern
VOID_P
CaptureTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet capture related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
;

//
// This struct is used for capturing one packet.
// Transfer between the parent and child processes
//
typedef struct {
  BOOLEAN         GotOne;   // Capture one packet?
  UINT8           *Packet;  // Packet content
  UINT32          Len;      // The length of the packet
  struct timeval  Time;     // When got the packet?
} CAP_INFO;

//
// This struct is used for capturing multiple packets
// Transfer between the parent and child processes
// Generally, we captures multiple packets only in performance test.
//
typedef struct {
  UINT32  Count;  // Only the number will be return from chile process
} MULTI_CAP_INFO;

#define MAX_FILTER_LEN  256

//
// This struct is used for defining the capture control block
//
typedef struct {
  UINT32          Received;     // Received
  UINT8           *ReceiveBuff; // Buffer the lasted packet received
  UINT32          ReceiveLen;   // the length of the received packet
  pcap_t          *Capturer;    //
  UINT8           CaptureFilter[MAX_FILTER_LEN];
  struct timeval  Time;
} CCB;

extern NL_LIST  CcbList;

VOID
EmsCaptureEndAll(
  VOID
  )
/*++

Routine Description:

  Close all the EMS capture

Arguments:

  None

Returns:

  None

--*/
;

#endif // _EMS_CAPTURE_H_
