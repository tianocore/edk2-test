/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
                    &Interface
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
                    &Interface
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
