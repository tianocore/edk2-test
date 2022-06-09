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

  Udp4ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Udp4ServiceBindingENTSTestCase.h"

//
// Udp4ServiceBinding.CreateChild
//
static EFI_HANDLE *Udp4ServiceBindingCreateChildHandle;
static EFI_STATUS *Udp4ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gUdp4ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Udp4ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Udp4ServiceBindingCreateChildStatus
  },
  0
};

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
{
  EFI_UDP4_SERVICE_BINDING_PROTOCOL *Udp4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Udp4ServiceBinding = (EFI_UDP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Udp4ServiceBindingCreateChildStatus = Udp4ServiceBinding->CreateChild (
                                                              Udp4ServiceBinding,
                                                              Udp4ServiceBindingCreateChildHandle
                                                              );
  if (EFI_ERROR (*Udp4ServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Udp4") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Udp4ServiceBindingCreateChildHandle;
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
// Udp4ServiceBinding.DestroyChild
//
static EFI_HANDLE Udp4ServiceBindingDestroyChildHandle;
static EFI_STATUS *Udp4ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gUdp4ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Udp4ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Udp4ServiceBindingDestroyChildStatus
  },
  0
};

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
{
  EFI_UDP4_SERVICE_BINDING_PROTOCOL *Udp4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Udp4ServiceBinding = (EFI_UDP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Udp4ServiceBindingDestroyChildStatus = Udp4ServiceBinding->DestroyChild (
                                                                Udp4ServiceBinding,
                                                                Udp4ServiceBindingDestroyChildHandle
                                                                );
  if (EFI_ERROR (*Udp4ServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Udp4") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Udp4ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
