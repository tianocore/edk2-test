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

  MemoryAllocationENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "MemoryAllocationENTSTestCase.h"

//
// tBS.AllocatePages
//
static EFI_ALLOCATE_TYPE    BSAllocatePagesType;
static EFI_MEMORY_TYPE      BSAllocatePagesMemoryType;
static UINTN                BSAllocatePagesPages;
static EFI_PHYSICAL_ADDRESS *BSAllocatePagesMemory;
static EFI_STATUS           *BSAllocatePagesStatus;

ENTS_ARG_FIELD              BSAllocatePagesArgField[] = {
  {
    OCTETN,
    &BSAllocatePagesType
  },
  {
    OCTETN,
    &BSAllocatePagesMemoryType
  },
  {
    OCTETN,
    &BSAllocatePagesPages
  },
  {
    POINTER,
    &BSAllocatePagesMemory
  },
  {
    POINTER,
    &BSAllocatePagesStatus
  },
  0
};

EFI_STATUS
BS_AllocatePages_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 AllocatePages Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSAllocatePagesStatus = BootService->AllocatePages (
                                          BSAllocatePagesType,
                                          BSAllocatePagesMemoryType,
                                          BSAllocatePagesPages,
                                          BSAllocatePagesMemory
                                          );
  return EFI_SUCCESS;
}

//
// tBS.FreePages
//
static EFI_PHYSICAL_ADDRESS BSFreePagesMemory;
static UINTN                BSFreePagesPages;
static EFI_STATUS           *BSFreePagesStatus;

ENTS_ARG_FIELD              BSFreePagesArgField[] = {
  {
    OCTETN,
    &BSFreePagesMemory
  },
  {
    OCTETN,
    &BSFreePagesPages
  },
  {
    POINTER,
    &BSFreePagesStatus
  },
  0
};

EFI_STATUS
BS_FreePages_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 FreePages Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSFreePagesStatus = BootService->FreePages (
                                      BSFreePagesMemory,
                                      BSFreePagesPages
                                      );
  return EFI_SUCCESS;
}

//
// tBS.AllocatePool
//
static EFI_MEMORY_TYPE  BSAllocatePoolPoolType;
static UINTN            BSAllocatePoolSize;
static VOID             **BSAllocatePoolBuffer;
static EFI_STATUS       *BSAllocatePoolStatus;

ENTS_ARG_FIELD              BSAllocatePoolArgField[] = {
  {
    OCTETN,
    &BSAllocatePoolPoolType
  },
  {
    OCTETN,
    &BSAllocatePoolSize
  },
  {
    POINTER,
    &BSAllocatePoolBuffer
  },
  {
    POINTER,
    &BSAllocatePoolStatus
  },
  0
};

EFI_STATUS
BS_AllocatePool_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 AllocatePool Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSAllocatePoolStatus = BootService->AllocatePool (
                                        BSAllocatePoolPoolType,
                                        BSAllocatePoolSize,
                                        BSAllocatePoolBuffer
                                        );
  return EFI_SUCCESS;
}

//
// tBS.FreePool
//
static VOID       *BSFreePoolBuffer;
static EFI_STATUS *BSFreePoolStatus;

ENTS_ARG_FIELD    BSFreePoolArgField[] = {
  {
    POINTER,
    &BSFreePoolBuffer
  },
  {
    POINTER,
    &BSFreePoolStatus
  },
  0
};

EFI_STATUS
BS_FreePool_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 FreePool Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService       = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSFreePoolStatus = BootService->FreePool (BSFreePoolBuffer);
  return EFI_SUCCESS;
}
