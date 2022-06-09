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

  ArpServiceBindingENTSTestCase.c

Abstract:

--*/

#include "ArpServiceBindingENTSTestCase.h"

//
// ArpServiceBinding.CreateChild
//
static EFI_HANDLE *ArpServiceBindingCreateChildHandle;
static EFI_STATUS *ArpServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gArpServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &ArpServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &ArpServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpServiceBindingCreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_ARP_SERVICE_BINDING_PROTOCOL  *ArpServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  ArpServiceBinding = (EFI_ARP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *ArpServiceBindingCreateChildStatus = ArpServiceBinding->CreateChild (
                                                            ArpServiceBinding,
                                                            ArpServiceBindingCreateChildHandle
                                                            );
  if (EFI_ERROR (*ArpServiceBindingCreateChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Arp") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *ArpServiceBindingCreateChildHandle;
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
// ArpServiceBinding.DestroyChild
//
static EFI_HANDLE ArpServiceBindingDestroyChildHandle;
static EFI_STATUS *ArpServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gArpServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &ArpServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &ArpServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
EFIAPI
ArpServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ArpServiceBindingDestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_ARP_SERVICE_BINDING_PROTOCOL  *ArpServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  ArpServiceBinding = (EFI_ARP_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *ArpServiceBindingDestroyChildStatus = ArpServiceBinding->DestroyChild (
                                                              ArpServiceBinding,
                                                              ArpServiceBindingDestroyChildHandle
                                                              );
  if (EFI_ERROR (*ArpServiceBindingDestroyChildStatus)) {
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
    if (EntsStrCmp (Interface->ClientName, L"Arp") == 0) {
      //
      // find it
      //
      if (NULL == Interface->ClientHandle) {
        continue;
      }

      if (EntsCompareMem (Interface->ClientHandle, &ArpServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
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
