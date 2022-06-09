/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Dhcp6ENTSTestCase.h

Abstract:

--*/

#ifndef _DHCP6_ENTS_TESTCASE_H_
#define _DHCP6_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Dhcp6.h>

EFI_STATUS
EFIAPI
Dhcp6Config_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6Start_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6InfoRequest_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 InfoRequest Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6RenewRebind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 RenewRebind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6Decline_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Decline Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6Release_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Release Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6Stop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp6Parse_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 Parse Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gEntsRuntimeInfo;
extern UINTN          gEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gDhcp6ConfigArgField[];
extern ENTS_ARG_FIELD gDhcp6GetModeDataArgField[];
extern ENTS_ARG_FIELD gDhcp6StartArgField[];
extern ENTS_ARG_FIELD gDhcp6InfoRequestArgField[];
extern ENTS_ARG_FIELD gDhcp6RenewRebindArgField[];
extern ENTS_ARG_FIELD gDhcp6DeclineArgField[];
extern ENTS_ARG_FIELD gDhcp6ReleaseArgField[];
extern ENTS_ARG_FIELD gDhcp6StopArgField[];
extern ENTS_ARG_FIELD gDhcp6ParseArgField[];
#endif // _MANAGEDNETWORK_ENTS_TESTCASE_H_
