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

  Ip6ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Ip6ServiceBindingENTSTestCase.h"

//
// Ip6ServiceBinding.CreateChild
//
static EFI_HANDLE *Ip6ServiceBindingCreateChildHandle;
static EFI_STATUS *Ip6ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gIp6ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Ip6ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Ip6ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_IP6_SERVICE_BINDING_PROTOCOL  *Ip6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Ip6ServiceBinding = (EFI_IP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Ip6ServiceBindingCreateChildStatus = Ip6ServiceBinding->CreateChild (
                                                            Ip6ServiceBinding,
                                                            Ip6ServiceBindingCreateChildHandle
                                                            );
  if (EFI_ERROR (*Ip6ServiceBindingCreateChildStatus)) {
    return EFI_SUCCESS;
  }

  Status = tBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiEntsProtocolGuid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }
  //
  // Walk through each instance need to be tested
  //
  for (HandleIndex = 0; HandleIndex < NoHandles; HandleIndex++) {
    Status = tBS->HandleProtocol (
                    HandleBuffer[HandleIndex],
                    &gEfiEntsProtocolGuid,
                    (VOID **)&Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Ip6") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Ip6ServiceBindingCreateChildHandle;
      Status = EFI_SUCCESS;
	  goto Done;
    }
  }

  Status = EFI_NOT_FOUND;
Done:
  if (HandleBuffer != NULL) {
    tBS->FreePool(HandleBuffer);
  }
  return Status;
}

//
// Ip6ServiceBinding.DestroyChild
//
static EFI_HANDLE Ip6ServiceBindingDestroyChildHandle;
static EFI_STATUS *Ip6ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gIp6ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Ip6ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Ip6ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip6ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip6ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_IP6_SERVICE_BINDING_PROTOCOL  *Ip6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Ip6ServiceBinding = (EFI_IP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Ip6ServiceBindingDestroyChildStatus = Ip6ServiceBinding->DestroyChild (
                                                              Ip6ServiceBinding,
                                                              Ip6ServiceBindingDestroyChildHandle
                                                              );
  if (EFI_ERROR (*Ip6ServiceBindingDestroyChildStatus)) {
    return EFI_SUCCESS;
  }

  Status = tBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiEntsProtocolGuid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }
  //
  // Walk through each instance need to be tested
  //
  for (HandleIndex = 0; HandleIndex < NoHandles; HandleIndex++) {
    Status = tBS->HandleProtocol (
                    HandleBuffer[HandleIndex],
                    &gEfiEntsProtocolGuid,
                    (VOID **)&Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Ip6") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Ip6ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
        Interface->ClientHandle = NULL;
      }
      Status = EFI_SUCCESS;
	  goto Done;
    }
  }

  Status = EFI_NOT_FOUND;
Done:
  if (HandleBuffer != NULL) {
    tBS->FreePool(HandleBuffer);
  }
  return Status;
}
