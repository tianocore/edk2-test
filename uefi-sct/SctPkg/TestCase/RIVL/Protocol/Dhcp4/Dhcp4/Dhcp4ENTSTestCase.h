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

  Dhcp4ENTSTestCase.h

Abstract:

--*/

#ifndef _DHCP4_ENTS_TESTCASE_H_
#define _DHCP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Dhcp4.h>

EFI_STATUS
EFIAPI
Dhcp4Config_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4Start_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4RenewRebind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 RenewRebind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4Release_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Release Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4Stop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4Build_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Build Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4TransmitReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 TransmitReceive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Dhcp4Parse_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 Parse Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gEntsRuntimeInfo;
extern UINTN          gEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gDhcp4ConfigArgField[];
extern ENTS_ARG_FIELD gDhcp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gDhcp4StartArgField[];
extern ENTS_ARG_FIELD gDhcp4RenewRebindArgField[];
extern ENTS_ARG_FIELD gDhcp4ReleaseArgField[];
extern ENTS_ARG_FIELD gDhcp4StopArgField[];
extern ENTS_ARG_FIELD gDhcp4BuildArgField[];
extern ENTS_ARG_FIELD gDhcp4TransmitReceiveArgField[];
extern ENTS_ARG_FIELD gDhcp4ParseArgField[];
#endif // _MANAGEDNETWORK_ENTS_TESTCASE_H_
