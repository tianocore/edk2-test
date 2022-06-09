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

  PXEBaseCodeENTSTestCase.h

Abstract:

--*/

#ifndef _PXEBASECODE_ENTS_TESTCASE_H_
#define _PXEBASECODE_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
PXEBaseCodeStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStart Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeDhcp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDhcp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeDiscover_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDiscover Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeMtftp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMtftp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeUdpWrite_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWrite Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeUdpRead_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpRead Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeSetIpFilter_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetIpFilter Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeArp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeArp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeSetParameters_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetParameters Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeSetStationIp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetStationIp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeSetPackets_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetPackets Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeMode_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMode Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeUdpWritePattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWritePattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
PXEBaseCodeUdpReadPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpReadPattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gPXEBaseCodeEntsRuntimeInfo;
extern UINTN          gPXEBaseCodeEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gPXEBaseCodeStartArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeStopArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeDhcpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeDiscoverArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeMtftpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpWriteArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpReadArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetIpFilterArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeArpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetParametersArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetStationIpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetPacketsArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeModeArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpWritePattern1ArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpReadPattern1ArgField[];

#endif // _PXEBASECODE_ENTS_TESTCASE_H_
