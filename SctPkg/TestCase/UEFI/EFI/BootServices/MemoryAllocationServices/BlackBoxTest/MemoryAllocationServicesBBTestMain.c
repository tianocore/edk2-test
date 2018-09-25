/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MemoryAllocationServicesBBTestMain.c

Abstract:

  Test Driver of Memory Allocation Boot Services

--*/

#include "SctLib.h"
#include "MemoryAllocationServicesBBTestMain.h"

UINT8                                *MemoryMap = NULL;
UINTN                                MemoryMapSizeNeeded = 0;

EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  TPL_APPLICATION,
  TPL_CALLBACK,
  TPL_NOTIFY
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  MEMORY_ALLOCATION_SERVICES_TEST_REVISION,
  MEMORY_ALLOCATION_SERVICES_TEST_GUID,
  L"Memory Allocation Services Test",
  L"UEFI Memory Allocation Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_CONSISTENCY_GUID,
    L"GetMemoryMap_Conf",
    L"Consistency Test for GetMemoryMap",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetMemoryMapConsistencyTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_ALLOCATEPAGES_CONSISTENCY_GUID,
    L"AllocatePages_Conf",
    L"Consistency Test for AllocatePages",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestAllocatePagesConsistencyTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_FREEPAGES_CONSISTENCY_GUID,
    L"FreePages_Conf",
    L"Consistency Test for FreePages",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFreePagesConsistencyTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_ALLOCATEPOOL_CONSISTENCY_GUID,
    L"AllocatePool_Conf",
    L"Consistency Test for AllocatePool",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestAllocatePoolConsistencyTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_FREEPOOL_CONSISTENCY_GUID,
    L"FreePool_Conf",
    L"Consistency Test for FreePool",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFreePoolConsistencyTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_INTERFACE_GUID,
    L"GetMemoryMap_Func",
    L"Interface Test for GetMemoryMap",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetMemoryMapInterfaceTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_ALLOCATEPAGES_INTERFACE_GUID,
    L"AllocatePages_Func",
    L"Interface Test for AllocatePages",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestAllocatePagesInterfaceTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_FREEPAGES_INTERFACE_GUID,
    L"FreePages_Func",
    L"Interface Test for FreePages",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFreePagesInterfaceTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_ALLOCATEPOOL_INTERFACE_GUID,
    L"AllocatePool_Func",
    L"Interface Test for AllocatePool",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestAllocatePoolInterfaceTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_FREEPOOL_INTERFACE_GUID,
    L"FreePool_Func",
    L"Interface Test for FreePool",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFreePoolInterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_STRESS_TEST_GUID,
    L"GetMemoryMap_Stress",
    L"Stress Test for GetMemoryMap",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetMemoryMapStressTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_PAGES_STRESS_TEST_GUID,
    L"Allocate/FreePages_Stress",
    L"Stress Test for AllocatePages and FreePages",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPagesStressTest
  },
  {
    MEMORY_ALLOCATION_SERVICES_POOL_STRESS_TEST_GUID,
    L"Allocate/FreePool_Stress",
    L"Stress Test for AllocatePool and FreePool",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPoolStressTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestMemoryAllocationServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Memory Allocation Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestMemoryAllocationServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestMemoryAllocationServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestMemoryAllocationServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  Allocate memory map buffer.
 *  @return EFI_SUCCESS allocate memory map buffer successfully.
*/
EFI_STATUS
InitMemoryMap (
  )
{
  EFI_STATUS                           Status;
  UINT8                                TmpMemoryMap[1];
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;

  MemoryMapSizeNeeded = 1;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSizeNeeded,
                   (EFI_MEMORY_DESCRIPTOR *)TmpMemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  MemoryMapSizeNeeded += EFI_PAGE_SIZE;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MemoryMapSizeNeeded,
                   (VOID**)&MemoryMap
                   );
  return Status;
}

/**
 *  Free memory map buffer.
 *  @return EFI_SUCCESS free memory map buffer successfully.
*/
EFI_STATUS
FreeMemoryMap (
  )
{
  gtBS->FreePool ((VOID*)MemoryMap);
  MemoryMap = NULL;
  MemoryMapSizeNeeded = 0;
  return EFI_SUCCESS;
}

/**
 *  Get the biggest free memory descriptor which is less than EFI_MAX_ADDRESS.
 *  @param MemoryDescriptor the memory descriptor to be returned.
 *  @return EFI_SUCCESS get the descriptor successfully.
 */
EFI_STATUS
GetMaxFreeMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  )
{
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                Index;
  EFI_MEMORY_DESCRIPTOR                *Descriptor;
  EFI_MEMORY_DESCRIPTOR                *DescriptorNeeded;

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                 );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  DescriptorNeeded = NULL;
  for (Index = 0; Index < MemoryMapSize; Index += DescriptorSize) {
    Descriptor = (EFI_MEMORY_DESCRIPTOR *) (MemoryMap + Index);
    if ((Descriptor->Type == EfiConventionalMemory) && 
		(Descriptor->PhysicalStart + SctLShiftU64 (Descriptor->NumberOfPages, EFI_PAGE_SHIFT) < MAX_ADDRESS)) {
      if (DescriptorNeeded == NULL) {
        DescriptorNeeded = Descriptor;
      } else if (Descriptor->NumberOfPages > DescriptorNeeded->NumberOfPages) {
        DescriptorNeeded = Descriptor;
      }
    }
  }

  *MemoryDescriptor = *DescriptorNeeded;

  return EFI_SUCCESS;
}

/**
 *  Get the highest address memory descriptor.
 *  @param MemoryDescriptor the memory descriptor to be returned.
 *  @return EFI_SUCCESS get the descriptor successfully.
 */
EFI_STATUS
GetMaxAddressMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  )
{
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                Index;
  EFI_MEMORY_DESCRIPTOR                *Descriptor;
  EFI_MEMORY_DESCRIPTOR                *DescriptorNeeded;

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                 );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  DescriptorNeeded = NULL;
  for (Index = 0; Index < MemoryMapSize; Index += DescriptorSize) {
    Descriptor = (EFI_MEMORY_DESCRIPTOR *) (MemoryMap + Index);
    if (DescriptorNeeded == NULL) {
      DescriptorNeeded = Descriptor;
    } else if (Descriptor->PhysicalStart > DescriptorNeeded->PhysicalStart) {
      DescriptorNeeded = Descriptor;
    }
  }

  *MemoryDescriptor = *DescriptorNeeded;

  return EFI_SUCCESS;
}

/**
 *  Get the highest address memory descriptor.
 *  @param MemoryDescriptor the memory descriptor to be returned.
 *  @return EFI_SUCCESS get the descriptor successfully.
 */
EFI_STATUS
GetAllocatedMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  )
{
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                Index;
  EFI_MEMORY_DESCRIPTOR                *Descriptor;
  EFI_MEMORY_DESCRIPTOR                *DescriptorNeeded;

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                 );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  DescriptorNeeded = NULL;
  for (Index = 0; Index < MemoryMapSize; Index += DescriptorSize) {
    Descriptor = (EFI_MEMORY_DESCRIPTOR *) (MemoryMap + Index);
    if (Descriptor->Type != EfiConventionalMemory) {
      DescriptorNeeded = Descriptor;
      break;
    }
  }

  *MemoryDescriptor = *DescriptorNeeded;

  return EFI_SUCCESS;
}

/**
 *  Get the second biggest free memory descriptor.
 *  @param MemoryDescriptor the memory descriptor to be returned.
 *  @return EFI_SUCCESS get the descriptor successfully.
 */
EFI_STATUS
GetSecondMaxFreeMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  )
{
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                Index;
  EFI_MEMORY_DESCRIPTOR                *Descriptor;
  EFI_MEMORY_DESCRIPTOR                *MaxDescriptor;
  EFI_MEMORY_DESCRIPTOR                *DescriptorNeeded;

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                 );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  DescriptorNeeded = NULL;
  MaxDescriptor = NULL;
  for (Index = 0; Index < MemoryMapSize; Index += DescriptorSize) {
    Descriptor = (EFI_MEMORY_DESCRIPTOR *) (MemoryMap + Index);
    if (Descriptor->Type == EfiConventionalMemory) {
      if (MaxDescriptor == NULL) {
        MaxDescriptor = Descriptor;
      } else if (DescriptorNeeded == NULL) {
        if (Descriptor->NumberOfPages > MaxDescriptor->NumberOfPages) {
          DescriptorNeeded = MaxDescriptor;
          MaxDescriptor = Descriptor;
        } else {
          DescriptorNeeded = Descriptor;
        }
      } else if (Descriptor->NumberOfPages > MaxDescriptor->NumberOfPages) {
        DescriptorNeeded = MaxDescriptor;
        MaxDescriptor = Descriptor;
      } else if (Descriptor->NumberOfPages > DescriptorNeeded->NumberOfPages) {
        DescriptorNeeded = Descriptor;
      }
    }
  }

  *MemoryDescriptor = *DescriptorNeeded;

  return EFI_SUCCESS;
}
