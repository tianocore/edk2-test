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

  Mtftp6ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Mtftp6ServiceBindingENTSTestCase.h"

//
// Mtftp6ServiceBinding.CreateChild
//
static EFI_HANDLE *Mtftp6ServiceBindingCreateChildHandle;
static EFI_STATUS *Mtftp6ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gMtftp6ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Mtftp6ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Mtftp6ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp6ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MTFTP6_SERVICE_BINDING_PROTOCOL *Mtftp6ServiceBinding;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Mtftp6ServiceBinding = (EFI_MTFTP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Mtftp6ServiceBindingCreateChildStatus = Mtftp6ServiceBinding->CreateChild (
                                                                  Mtftp6ServiceBinding,
                                                                  Mtftp6ServiceBindingCreateChildHandle
                                                                  );
  if (EFI_ERROR (*Mtftp6ServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mtftp6") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Mtftp6ServiceBindingCreateChildHandle;
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
// Mtftp6ServiceBinding.DestroyChild
//
static EFI_HANDLE Mtftp6ServiceBindingDestroyChildHandle;
static EFI_STATUS *Mtftp6ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gMtftp6ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Mtftp6ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Mtftp6ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp6ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MTFTP6_SERVICE_BINDING_PROTOCOL *Mtftp6ServiceBinding;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Mtftp6ServiceBinding = (EFI_MTFTP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Mtftp6ServiceBindingDestroyChildStatus = Mtftp6ServiceBinding->DestroyChild (
                                                                    Mtftp6ServiceBinding,
                                                                    Mtftp6ServiceBindingDestroyChildHandle
                                                                    );
  if (EFI_ERROR (*Mtftp6ServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mtftp6") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Mtftp6ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
