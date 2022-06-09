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

  UDp4ServiceBindingENTSTestCase.h

Abstract:

--*/

#ifndef _UDP4_SERVICE_BINDING_ENTS_TESTCASE_H_
#define _UDP4_SERVICE_BINDING_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Udp4.h>
#include <Protocol/ServiceBinding.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_UDP4_SERVICE_BINDING_PROTOCOL;

EFI_STATUS
EFIAPI
Udp4ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
;

EFI_STATUS
EFIAPI
Udp4ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp4ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
;

extern CHAR16         *gUdp4ServiceBindingRuntimeInfo;
extern UINTN          gIp4ServiceBindingRuntimeInfoSize;

extern ENTS_ARG_FIELD gUdp4ServiceBindingCreateChildArgField[];
extern ENTS_ARG_FIELD gUdp4ServiceBindingDestroyChildArgField[];

#endif
