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

  SimpleNetworkENTSTestCase.h

Abstract:

--*/

#ifndef _SIMPLENETWORK_ENTS_TESTCASE_H_
#define _SIMPLENETWORK_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/SimpleNetwork.h>

EFI_STATUS
EFIAPI
SimpleNetworkStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkInitialize_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Initialize Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkReset_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Reset Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkShutdown_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Shutdown Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkReceiveFilters_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork ReceiveFilters Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkStationAddress_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork StationAddress Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkStatistics_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Statistics Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkMCastIPToMAC_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork MCastIPToMAC Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkNvData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork NvData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkGetStatus_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork GetStatus Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkTransmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkMode_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Mode Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkTransmitPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkTransmitPattern2_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern2 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
SimpleNetworkReceivePattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern3 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gSimpleNetworkEntsRuntimeInfo;
extern UINTN          gSimpleNetworkEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gSimpleNetworkStartArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkStopArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkInitializeArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkResetArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkShutdownArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkReceiveFiltersArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkStationAddressArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkStatisticsArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkMCastIPToMACArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkNvDataArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkGetStatusArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkTransmitArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkReceiveArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkModeArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkTransmitPattern1ArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkTransmitPattern2ArgField[];
extern ENTS_ARG_FIELD gSimpleNetworkReceivePattern1ArgField[];

#endif // _SIMPLENETWORK_ENTS_TESTCASE_H_
