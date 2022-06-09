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

  MnpSBENTSTestCase.c

Abstract:

--*/

#include "MnpSBENTSTestCase.h"

//
// MnpServiceBinding.CreateChild
//
static EFI_HANDLE *MnpCreateChildHandle;
static EFI_STATUS *MnpCreateChildStatus;

ENTS_ARG_FIELD    gMnpCreateChildArgField[] = {
  {
    POINTER,
    &MnpCreateChildHandle
  },
  {
    POINTER,
    &MnpCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  MnpServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MNP_SERVICE_BINDING_PROTOCOL  *Mnp;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Mnp = (EFI_MNP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *MnpCreateChildStatus = Mnp->CreateChild (
                                Mnp,
                                MnpCreateChildHandle
                                );

  if (EFI_ERROR (*MnpCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mnp") == 0) {
      Interface->ClientHandle = *MnpCreateChildHandle;
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
static EFI_HANDLE MnpDestroyChildHandle;
static EFI_STATUS *MnpDestroyChildStatus;

ENTS_ARG_FIELD    gMnpDestroyChildArgField[] = {
  {
    OCTETN,
    &MnpDestroyChildHandle
  },
  {
    POINTER,
    &MnpDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  MnpServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_MNP_SERVICE_BINDING_PROTOCOL  *Mnp;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Mnp = (EFI_MNP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *MnpDestroyChildStatus = Mnp->DestroyChild (
                                  Mnp,
                                  MnpDestroyChildHandle
                                  );
  if (EFI_ERROR (*MnpDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Mnp") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &MnpDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
