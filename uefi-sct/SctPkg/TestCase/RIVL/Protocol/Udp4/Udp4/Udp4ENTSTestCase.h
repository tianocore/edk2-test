/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Udp4ENTSTestCase.h

Abstract:

--*/

#ifndef _UDP4_ENTS_TESTCASE_H_
#define _UDP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Udp4.h>

EFI_STATUS
EFIAPI
Udp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp4SignalRecycleEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4 SignalRecycleEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gUdp4EntsRuntimeInfo;
extern UINTN          gUdp4EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gUdp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gUdp4ConfigureArgField[];
extern ENTS_ARG_FIELD gUdp4GroupsArgField[];
extern ENTS_ARG_FIELD gUdp4RoutesArgField[];
extern ENTS_ARG_FIELD gUdp4PollArgField[];
extern ENTS_ARG_FIELD gUdp4ReceiveArgField[];
extern ENTS_ARG_FIELD gUdp4TransmitArgField[];
extern ENTS_ARG_FIELD gUdp4CancelArgField[];
extern ENTS_ARG_FIELD gUdp4SignalRecycleEventArgField[];

#endif // _UDP4_ENTS_TESTCASE_H_
