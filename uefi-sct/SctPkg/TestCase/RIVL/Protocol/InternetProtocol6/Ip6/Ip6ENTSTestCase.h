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

  Ip6ENTSTestCase.h

Abstract:

--*/

#ifndef _IP6_ENTS_TESTCASE_H_
#define _IP6_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Ip6.h>

EFI_STATUS
EFIAPI
Ip6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Neighbors_EntsTest (
  VOID *ClientInterface
  );

EFI_STATUS
EFIAPI
Ip6Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gIp6RuntimeInfo;
extern UINTN          gIp6RuntimeInfoSize;

extern ENTS_ARG_FIELD gIp6GetModeDataArgField[];
extern ENTS_ARG_FIELD gIp6ConfigureArgField[];
extern ENTS_ARG_FIELD gIp6GroupsArgField[];
extern ENTS_ARG_FIELD gIp6RoutesArgField[];
extern ENTS_ARG_FIELD gIp6NeighborsArgField[];
extern ENTS_ARG_FIELD gIp6TransmitArgField[];
extern ENTS_ARG_FIELD gIp6ReceiveArgField[];
extern ENTS_ARG_FIELD gIp6CancelArgField[];
extern ENTS_ARG_FIELD gIp6PollArgField[];

#endif
