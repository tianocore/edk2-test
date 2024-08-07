/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Tcp6ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Tcp6ServiceBindingENTSTestCase.h"

//
// Tcp6ServiceBinding.CreateChild
//
static EFI_HANDLE *Tcp6ServiceBindingCreateChildHandle;
static EFI_STATUS *Tcp6ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gTcp6ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Tcp6ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Tcp6ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_TCP6_SERVICE_BINDING_PROTOCOL *Tcp6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Tcp6ServiceBinding = (EFI_TCP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Tcp6ServiceBindingCreateChildStatus = Tcp6ServiceBinding->CreateChild (
                                                              Tcp6ServiceBinding,
                                                              Tcp6ServiceBindingCreateChildHandle
                                                              );
  if (EFI_ERROR (*Tcp6ServiceBindingCreateChildStatus)) {
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
                    (VOID **) &Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Tcp6") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Tcp6ServiceBindingCreateChildHandle;
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
// Tcp6ServiceBinding.DestroyChild
//
static EFI_HANDLE Tcp6ServiceBindingDestroyChildHandle;
static EFI_STATUS *Tcp6ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gTcp6ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Tcp6ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Tcp6ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Tcp6ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp6ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_TCP6_SERVICE_BINDING_PROTOCOL *Tcp6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Tcp6ServiceBinding = (EFI_TCP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Tcp6ServiceBindingDestroyChildStatus = Tcp6ServiceBinding->DestroyChild (
                                                                Tcp6ServiceBinding,
                                                                Tcp6ServiceBindingDestroyChildHandle
                                                                );

  if (EFI_ERROR (*Tcp6ServiceBindingDestroyChildStatus)) {
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
                    (VOID **) &Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Tcp6") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Tcp6ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
