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

  UDp6ServiceBindingENTSTestCase.h

Abstract:

--*/

#ifndef _UDP6_SERVICE_BINDING_ENTS_TESTCASE_H_
#define _UDP6_SERVICE_BINDING_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Udp6.h>
#include <Protocol/ServiceBinding.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_UDP6_SERVICE_BINDING_PROTOCOL;

EFI_STATUS
EFIAPI
Udp6ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
;

EFI_STATUS
EFIAPI
Udp6ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
;

extern CHAR16         *gUdp6ServiceBindingRuntimeInfo;
extern UINTN          gIp6ServiceBindingRuntimeInfoSize;

extern ENTS_ARG_FIELD gUdp6ServiceBindingCreateChildArgField[];
extern ENTS_ARG_FIELD gUdp6ServiceBindingDestroyChildArgField[];

#endif
