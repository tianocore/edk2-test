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

  Tcp6ENTSTestCase.h

Abstract:

--*/

#ifndef _TCP6_ENTS_TESTCASE_H_
#define _TCP6_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/SimpleNetwork.h>
#include <UEFI/Protocol/ManagedNetwork.h>
#include <UEFI/Protocol/Ip6.h>
#include <UEFI/Protocol/Tcp6.h>

EFI_STATUS
EFIAPI
Tcp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Connect_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Connect Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Accept_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Accept Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Close_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Close Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Tcp6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gTcp6EntsRuntimeInfo;
extern UINTN          gTcp6EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gTcp6GetModeDataArgField[];
extern ENTS_ARG_FIELD gTcp6ConfigureArgField[];
extern ENTS_ARG_FIELD gTcp6ConnectArgField[];
extern ENTS_ARG_FIELD gTcp6AcceptArgField[];
extern ENTS_ARG_FIELD gTcp6TransmitArgField[];
extern ENTS_ARG_FIELD gTcp6ReceiveArgField[];
extern ENTS_ARG_FIELD gTcp6CloseArgField[];
extern ENTS_ARG_FIELD gTcp6CancelArgField[];
extern ENTS_ARG_FIELD gTcp6PollArgField[];

#endif // _TCP6_ENTS_TESTCASE_H_
