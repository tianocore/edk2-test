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

  Mtftp4ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Mtftp4ServiceBindingENTSTestCase.h"

//
// Mtftp4ServiceBinding.CreateChild
//
static EFI_HANDLE *Mtftp4ServiceBindingCreateChildHandle;
static EFI_STATUS *Mtftp4ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gMtftp4ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Mtftp4ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Mtftp4ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MTFTP4_SERVICE_BINDING_PROTOCOL *Mtftp4ServiceBinding;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Mtftp4ServiceBinding = (EFI_MTFTP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Mtftp4ServiceBindingCreateChildStatus = Mtftp4ServiceBinding->CreateChild (
                                                                  Mtftp4ServiceBinding,
                                                                  Mtftp4ServiceBindingCreateChildHandle
                                                                  );
  if (EFI_ERROR (*Mtftp4ServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mtftp4") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Mtftp4ServiceBindingCreateChildHandle;
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
// Mtftp4ServiceBinding.DestroyChild
//
static EFI_HANDLE Mtftp4ServiceBindingDestroyChildHandle;
static EFI_STATUS *Mtftp4ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gMtftp4ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Mtftp4ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Mtftp4ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MTFTP4_SERVICE_BINDING_PROTOCOL *Mtftp4ServiceBinding;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Mtftp4ServiceBinding = (EFI_MTFTP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Mtftp4ServiceBindingDestroyChildStatus = Mtftp4ServiceBinding->DestroyChild (
                                                                    Mtftp4ServiceBinding,
                                                                    Mtftp4ServiceBindingDestroyChildHandle
                                                                    );
  if (EFI_ERROR (*Mtftp4ServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mtftp4") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Mtftp4ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
