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

  MnpENTSTestCase.h

Abstract:

--*/

#ifndef _MANAGEDNETWORK_ENTS_TESTCASE_H_
#define _MANAGEDNETWORK_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/ManagedNetwork.h>

EFI_STATUS
EFIAPI
MnpConfig_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpGetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpMCastIpToMac_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp MCastIpToMac Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpGroup_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Group Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpTransmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpPoll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpTransmitMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp TransmitMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_DEVICE_ERROR - Some error happens.

--*/
;

EFI_STATUS
EFIAPI
MnpReceiveMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp ReceiveMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpPollPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Pattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
MnpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gEntsRuntimeInfo;
extern UINTN          gEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gMnpConfigArgField[];
extern ENTS_ARG_FIELD gMnpGetModeDataArgField[];
extern ENTS_ARG_FIELD gMnpMCastIpToMacArgField[];
extern ENTS_ARG_FIELD gMnpGroupArgField[];
extern ENTS_ARG_FIELD gMnpTransmitArgField[];
extern ENTS_ARG_FIELD gMnpReceiveArgField[];
extern ENTS_ARG_FIELD gMnpReceiveMultiArgField[];
extern ENTS_ARG_FIELD gMnpPollArgField[];
extern ENTS_ARG_FIELD gMnpTransmitMultiPacketArgField[];
extern ENTS_ARG_FIELD gMnpPollPattern1ArgField[];
extern ENTS_ARG_FIELD gMnpCancelArgField[];
#endif // _MANAGEDNETWORK_ENTS_TESTCASE_H_
