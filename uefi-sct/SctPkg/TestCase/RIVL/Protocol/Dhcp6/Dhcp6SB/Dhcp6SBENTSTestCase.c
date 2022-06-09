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

  Dhcp6SBENTSTestCase.c

Abstract:

--*/

#include "Dhcp6SBENTSTestCase.h"

//
// MnpServiceBinding.CreateChild
//
static EFI_HANDLE *Dhcp6CreateChildHandle;
static EFI_STATUS *Dhcp6CreateChildStatus;

ENTS_ARG_FIELD    gDhcp6CreateChildArgField[] = {
  {
    POINTER,
    &Dhcp6CreateChildHandle
  },
  {
    POINTER,
    &Dhcp6CreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6CreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_DHCP6_SERVICE_BINDING_PROTOCOL  *Dhcp6;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Dhcp6 = (EFI_DHCP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Dhcp6CreateChildStatus = Dhcp6->CreateChild (
                                    Dhcp6,
                                    Dhcp6CreateChildHandle
                                    );

  if (EFI_ERROR (*Dhcp6CreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Dhcp6") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Dhcp6CreateChildHandle;
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
// Dhcp6ServiceBinding.DestroyChild
//
static EFI_HANDLE Dhcp6DestroyChildHandle;
static EFI_STATUS *Dhcp6DestroyChildStatus;

ENTS_ARG_FIELD    gDhcp6DestroyChildArgField[] = {
  {
    OCTETN,
    &Dhcp6DestroyChildHandle
  },
  {
    POINTER,
    &Dhcp6DestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp6DestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp6 DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_DHCP6_SERVICE_BINDING_PROTOCOL  *Dhcp6;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Dhcp6 = (EFI_DHCP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;
  *Dhcp6DestroyChildStatus = Dhcp6->DestroyChild (
                                      Dhcp6,
                                      Dhcp6DestroyChildHandle
                                      );
  if (EFI_ERROR (*Dhcp6DestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Dhcp6") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Dhcp6DestroyChildStatus, sizeof (EFI_HANDLE))) {
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
