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

  ArpENTSTestCase.h

Abstract:

--*/

#ifndef _ARP_ENTS_TESTCASE_H_
#define _ARP_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Arp.h>

EFI_STATUS
EFIAPI
ArpConfig_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpConfig Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpAdd_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpAdd Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpFind_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpFind Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpDelete_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpDelete Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpFlush_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpFlush Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpRequest_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpRequest Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
ArpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpCancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gArpRuntimeInfo;
extern UINTN          gArpRuntimeInfoSize;

extern ENTS_ARG_FIELD gArpConfigArgField[];
extern ENTS_ARG_FIELD gArpAddArgField[];
extern ENTS_ARG_FIELD gArpFindArgField[];
extern ENTS_ARG_FIELD gArpDeleteArgField[];
extern ENTS_ARG_FIELD gArpFlushArgField[];
extern ENTS_ARG_FIELD gArpRequestArgField[];
extern ENTS_ARG_FIELD gArpCancelArgField[];

#endif
