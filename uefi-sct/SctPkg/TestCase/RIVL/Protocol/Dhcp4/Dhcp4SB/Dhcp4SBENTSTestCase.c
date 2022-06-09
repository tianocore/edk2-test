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

  Dhcp4SBENTSTestCase.c

Abstract:

--*/

#include "Dhcp4SBENTSTestCase.h"

//
// MnpServiceBinding.CreateChild
//
static EFI_HANDLE *Dhcp4CreateChildHandle;
static EFI_STATUS *Dhcp4CreateChildStatus;

ENTS_ARG_FIELD    gDhcp4CreateChildArgField[] = {
  {
    POINTER,
    &Dhcp4CreateChildHandle
  },
  {
    POINTER,
    &Dhcp4CreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp4CreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_DHCP4_SERVICE_BINDING_PROTOCOL  *Dhcp4;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Dhcp4 = (EFI_DHCP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Dhcp4CreateChildStatus = Dhcp4->CreateChild (
                                    Dhcp4,
                                    Dhcp4CreateChildHandle
                                    );

  if (EFI_ERROR (*Dhcp4CreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Dhcp4") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Dhcp4CreateChildHandle;
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
// MnpServiceBinding.DestroyChild
//
static EFI_HANDLE Dhcp4DestroyChildHandle;
static EFI_STATUS *Dhcp4DestroyChildStatus;

ENTS_ARG_FIELD    gDhcp4DestroyChildArgField[] = {
  {
    OCTETN,
    &Dhcp4DestroyChildHandle
  },
  {
    POINTER,
    &Dhcp4DestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
Dhcp4DestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Dhcp4 DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_DHCP4_SERVICE_BINDING_PROTOCOL  *Dhcp4;
  UINTN                               NoHandles;
  UINTN                               HandleIndex;
  EFI_HANDLE                          *HandleBuffer;
  EFI_ENTS_PROTOCOL                   *Interface;
  EFI_STATUS                          Status;

  Dhcp4 = (EFI_DHCP4_SERVICE_BINDING_PROTOCOL *) ClientInterface;
  *Dhcp4DestroyChildStatus = Dhcp4->DestroyChild (
                                      Dhcp4,
                                      Dhcp4DestroyChildHandle
                                      );
  if (EFI_ERROR (*Dhcp4DestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Dhcp4") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Dhcp4DestroyChildStatus, sizeof (EFI_HANDLE))) {
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
