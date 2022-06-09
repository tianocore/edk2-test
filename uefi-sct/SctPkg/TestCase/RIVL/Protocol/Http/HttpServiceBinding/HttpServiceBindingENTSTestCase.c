/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HttpServiceBindingENTSTestCase.c

Abstract:

--*/

#include "HttpServiceBindingENTSTestCase.h"

//
// HttpServiceBinding.CreateChild
//
static EFI_HANDLE *HttpServiceBindingCreateChildHandle;
static EFI_STATUS *HttpServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gHttpServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &HttpServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &HttpServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
HttpServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  HttpServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_HTTP_SERVICE_BINDING_PROTOCOL *HttpServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  HttpServiceBinding = (EFI_HTTP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *HttpServiceBindingCreateChildStatus = HttpServiceBinding->CreateChild (
                                                              HttpServiceBinding,
                                                              HttpServiceBindingCreateChildHandle
                                                              );
  if (EFI_ERROR (*HttpServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Http") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *HttpServiceBindingCreateChildHandle;
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
// HttpServiceBinding.DestroyChild
//
static EFI_HANDLE HttpServiceBindingDestroyChildHandle;
static EFI_STATUS *HttpServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gHttpServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &HttpServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &HttpServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
HttpServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  HttpServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_HTTP_SERVICE_BINDING_PROTOCOL *HttpServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  HttpServiceBinding = (EFI_HTTP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *HttpServiceBindingDestroyChildStatus = HttpServiceBinding->DestroyChild (
                                                                HttpServiceBinding,
                                                                HttpServiceBindingDestroyChildHandle
                                                                );

  if (EFI_ERROR (*HttpServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Http") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &HttpServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
