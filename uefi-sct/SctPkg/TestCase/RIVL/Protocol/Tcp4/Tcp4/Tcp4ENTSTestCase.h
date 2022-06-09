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

  Tcp4ENTSTestCase.h

Abstract:

--*/

#ifndef _TCP4_ENTS_TESTCASE_H_
#define _TCP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Tcp4.h>

EFI_STATUS
EFIAPI
Tcp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Connect_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Connect Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Accept_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Accept Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Close_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Close Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gTcp4EntsRuntimeInfo;
extern UINTN          gTcp4EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gTcp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gTcp4ConfigureArgField[];
extern ENTS_ARG_FIELD gTcp4RoutesArgField[];
extern ENTS_ARG_FIELD gTcp4ConnectArgField[];
extern ENTS_ARG_FIELD gTcp4AcceptArgField[];
extern ENTS_ARG_FIELD gTcp4TransmitArgField[];
extern ENTS_ARG_FIELD gTcp4ReceiveArgField[];
extern ENTS_ARG_FIELD gTcp4CloseArgField[];
extern ENTS_ARG_FIELD gTcp4CancelArgField[];
extern ENTS_ARG_FIELD gTcp4PollArgField[];

#endif // _TCP4_ENTS_TESTCASE_H_
