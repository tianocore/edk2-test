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

  Tcp4ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Tcp4ServiceBindingENTSTestCase.h"

//
// Tcp4ServiceBinding.CreateChild
//
static EFI_HANDLE *Tcp4ServiceBindingCreateChildHandle;
static EFI_STATUS *Tcp4ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gTcp4ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Tcp4ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Tcp4ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Tcp4ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_TCP4_SERVICE_BINDING_PROTOCOL *Tcp4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Tcp4ServiceBinding = (EFI_TCP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Tcp4ServiceBindingCreateChildStatus = Tcp4ServiceBinding->CreateChild (
                                                              Tcp4ServiceBinding,
                                                              Tcp4ServiceBindingCreateChildHandle
                                                              );
  if (EFI_ERROR (*Tcp4ServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Tcp4") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Tcp4ServiceBindingCreateChildHandle;
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
// Tcp4ServiceBinding.DestroyChild
//
static EFI_HANDLE Tcp4ServiceBindingDestroyChildHandle;
static EFI_STATUS *Tcp4ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gTcp4ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Tcp4ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Tcp4ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Tcp4ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Tcp4ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_TCP4_SERVICE_BINDING_PROTOCOL *Tcp4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Tcp4ServiceBinding = (EFI_TCP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Tcp4ServiceBindingDestroyChildStatus = Tcp4ServiceBinding->DestroyChild (
                                                                Tcp4ServiceBinding,
                                                                Tcp4ServiceBindingDestroyChildHandle
                                                                );

  if (EFI_ERROR (*Tcp4ServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Tcp4") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Tcp4ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
