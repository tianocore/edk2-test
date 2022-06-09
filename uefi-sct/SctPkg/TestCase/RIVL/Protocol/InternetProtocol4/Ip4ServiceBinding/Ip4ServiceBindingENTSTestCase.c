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

  Ip4ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Ip4ServiceBindingENTSTestCase.h"

//
// Ip4ServiceBinding.CreateChild
//
static EFI_HANDLE *Ip4ServiceBindingCreateChildHandle;
static EFI_STATUS *Ip4ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gIp4ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Ip4ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Ip4ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip4ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_IP4_SERVICE_BINDING_PROTOCOL  *Ip4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Ip4ServiceBinding = (EFI_IP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Ip4ServiceBindingCreateChildStatus = Ip4ServiceBinding->CreateChild (
                                                            Ip4ServiceBinding,
                                                            Ip4ServiceBindingCreateChildHandle
                                                            );
  if (EFI_ERROR (*Ip4ServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Ip4") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Ip4ServiceBindingCreateChildHandle;
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
// Ip4ServiceBinding.DestroyChild
//
static EFI_HANDLE Ip4ServiceBindingDestroyChildHandle;
static EFI_STATUS *Ip4ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gIp4ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Ip4ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Ip4ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Ip4ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Ip4ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_IP4_SERVICE_BINDING_PROTOCOL  *Ip4ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Ip4ServiceBinding = (EFI_IP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Ip4ServiceBindingDestroyChildStatus = Ip4ServiceBinding->DestroyChild (
                                                              Ip4ServiceBinding,
                                                              Ip4ServiceBindingDestroyChildHandle
                                                              );
  if (EFI_ERROR (*Ip4ServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Ip4") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Ip4ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
