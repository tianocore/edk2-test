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

  Udp6ENTSTestCase.h

Abstract:

--*/

#ifndef _UDP6_ENTS_TESTCASE_H_
#define _UDP6_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Udp6.h>

EFI_STATUS
EFIAPI
Udp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Udp6SignalRecycleEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6 SignalRecycleEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gUdp6EntsRuntimeInfo;
extern UINTN          gUdp6EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gUdp6GetModeDataArgField[];
extern ENTS_ARG_FIELD gUdp6ConfigureArgField[];
extern ENTS_ARG_FIELD gUdp6GroupsArgField[];
extern ENTS_ARG_FIELD gUdp6RoutesArgField[];
extern ENTS_ARG_FIELD gUdp6PollArgField[];
extern ENTS_ARG_FIELD gUdp6ReceiveArgField[];
extern ENTS_ARG_FIELD gUdp6TransmitArgField[];
extern ENTS_ARG_FIELD gUdp6CancelArgField[];
extern ENTS_ARG_FIELD gUdp6SignalRecycleEventArgField[];

#endif // _UDP6_ENTS_TESTCASE_H_
