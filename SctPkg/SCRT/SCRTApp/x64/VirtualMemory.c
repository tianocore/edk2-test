/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   

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

#define VIRT_TO_PHYS_OFFSET       (0x800000000)    //32G


EFI_STATUS
DoMemoryAllocation (
  IN UINTN PhysicalFunc
  )
/*++

Routine Description:

  Allocate memory and creat the PageTable to set up physical-virtual map. 

Arguments:

  PhysicalFunc  - Physical address where RuntimeTestFunc locates.

Returns:

  EFI_SUCCESS

--*/    
{  
  //
  // Nothing to do here since 64-bit mode has been with its PageTable mechanism.
  //
  return EFI_SUCCESS;
}



VOID
ConvertRuntimeFuncPtr (
  IN OUT UINTN   *VirtualFunc
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
  //
  // Change RuntimeFunc virtual address to (physical address + 32G).
  //
  *VirtualFunc = *VirtualFunc + (UINTN)VIRT_TO_PHYS_OFFSET;
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
  UINTN             Index;
  *VirtualMapSize   = 0;
  //
  // Copy entries that need runtime mapping to construct virtualMemoryMap
  //
  for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
    //
    // Virtual address = (Physical address + 32G)
    //
    if ((MemoryMap->Attribute & EFI_MEMORY_RUNTIME) == EFI_MEMORY_RUNTIME) {
      SctCopyMem ((VOID *) VirtualMemoryMap, (VOID *) MemoryMap, DescriptorSize);
      *VirtualMapSize += DescriptorSize;
      VirtualMemoryMap->VirtualStart  = VirtualMemoryMap->PhysicalStart + VIRT_TO_PHYS_OFFSET;
      VirtualMemoryMap  = NextMemoryDescriptor (VirtualMemoryMap, DescriptorSize);
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
  // Enable PageTable to go to virtual mode, and jump to Virtual Function Entry Point.
  //
  LoadNewPageTable (VirtualFunc, HandOffAddr);
}
