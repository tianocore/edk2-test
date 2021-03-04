/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2012, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  VirtualMemory.c

--*/

#include "SCRTApp.h"

#define VIRT_TO_PHYS_OFFSET       (0x80000000)     //2G

BOOLEAN     HighAddress = FALSE;
UINTN       PageTable   = 0;


VOID
ConvertRuntimeFuncPtr (
  IN OUT UINTN      *VirtualFunc
  )
/*++

Routine Description:

  Change RuntimeTestFunc physical address to virtual address

Arguments:

  VirtualFunc  - On input, RuntimeTestFunc physical address.
                 On output, RuntimeTest virtual address.

Returns:

  NONE

--*/
{
	/*Note: It is presumed that on ARM v5, V6 and V7 architectures
	 * the MMU is configured and enabled in PEI phase. As VirtualFunc
	 * is already mapped to virtual memory, don't have to do anything here.
	 */
  /* FIXME: Is it the same on ARM v8? */
}


EFI_STATUS
DoMemoryAllocation (
  IN UINTN PhysicalFunc
  )
/*++

Routine Description:

  Allocate memory and create the PageTable to set up physical-virtual map.

Arguments:

  PhysicalFunc  - Physical address where RuntimeTestFunc locates.

Returns:

  EFI_STATUS

--*/
{
  EFI_STATUS                  Status;
  EFI_PHYSICAL_ADDRESS        AllocateMemory;

  //create new page tables or use existing page tables.
  //
  // Allocate PageTable memory close to this Application image location in
  // the system memory. In this way, it is safe for page table memory.
  //
  AllocateMemory = PhysicalFunc;

  Status = tBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiRuntimeServicesData,
                  1,
                  &AllocateMemory
                  );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  PageTable = (UINTN)AllocateMemory;
  return EFI_SUCCESS;
}


VOID
PrepareVirtualAddressMap (
  IN UINTN                       MemoryMapSize,
  IN UINTN                       DescriptorSize,
  IN EFI_MEMORY_DESCRIPTOR       *MemoryMap,
  IN EFI_MEMORY_DESCRIPTOR       *VirtualMemoryMap,
  IN OUT UINTN                   *VirtualMapSize
  )
/*++

Routine Description:

  Construct VirtualAddressMap from physical address to virtual address

Arguments:

  MemoryMapSize     - The size, in bytes, of the MemoryMap buffer
  DescriptorSize    - The size, in bytes, of an individual EFI_MEMORY_DESCRIPTOR
  MemoryMap         - A pointer to the current memory map
  VirtualMemoryMap  - A pointer to the modified virtual memory map
  VirtualMapSize    - A pointer to the size, in bytes, of the VirtualMemoryMap buffer

Returns:

  NONE

--*/
{
  UINTN    Index;
  *VirtualMapSize        = 0;

  //
  // Copy entries that need runtime mapping to construct virtualMemoryMap
  //
  for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
    if ((MemoryMap->Attribute & EFI_MEMORY_RUNTIME) == EFI_MEMORY_RUNTIME) {
      SctCopyMem ((VOID *) VirtualMemoryMap, (VOID *) MemoryMap, DescriptorSize);
      VirtualMemoryMap->VirtualStart  = VirtualMemoryMap->PhysicalStart;
      *VirtualMapSize += DescriptorSize;
      VirtualMemoryMap = NextMemoryDescriptor (VirtualMemoryMap, DescriptorSize);
    }

    MemoryMap = NextMemoryDescriptor (MemoryMap, DescriptorSize);
  }
}



VOID
JumpVirtualMode(
  IN UINTN VirtualFunc,
  IN UINTN HandOffAddr
  )
/*++

Routine Description:

  Enable virtual addressing mode, and jump to RuntimeTestFunc in virtual address

Arguments:

  VirtualFunc  - RuntimeTestFunc virtual address
  HandOffAddr  - Configuration Data Address

Returns:

  NONE

--*/
{
  //
  // Note: It is assumed that the MMU and page tables are configured on ARM platforms
  // based on ARM v5 v6 and v7 architecture.
  //
  /* FIXME: Is it the same on ARM v8? */
	JumpToTestFunc(VirtualFunc, HandOffAddr);
}
