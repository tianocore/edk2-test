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

  Ip4ENTSTestCase.h

Abstract:

--*/

#ifndef _IP4_ENTS_TESTCASE_H_
#define _IP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Ip4.h>

EFI_STATUS
EFIAPI
Ip4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Groups_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Groups Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Routes_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Routes Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Transmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Receive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Cancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Ip4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gIp4RuntimeInfo;
extern UINTN          gIp4RuntimeInfoSize;

extern ENTS_ARG_FIELD gIp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gIp4ConfigureArgField[];
extern ENTS_ARG_FIELD gIp4GroupsArgField[];
extern ENTS_ARG_FIELD gIp4RoutesArgField[];
extern ENTS_ARG_FIELD gIp4TransmitArgField[];
extern ENTS_ARG_FIELD gIp4ReceiveArgField[];
extern ENTS_ARG_FIELD gIp4CancelArgField[];
extern ENTS_ARG_FIELD gIp4PollArgField[];

#endif
