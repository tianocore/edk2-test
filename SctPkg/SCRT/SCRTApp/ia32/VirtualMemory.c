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
  //
  // if RuntimeFunc physical address >= 2G, set its virtualFunc to ( physical address - 2G )
  // if RuntimeFunc physical address < 2G, set its virtualFunc to ( physical address + 2G )
  //
  if ((UINTN) *VirtualFunc >= (UINTN)VIRT_TO_PHYS_OFFSET) {
    HighAddress = TRUE;    
    *VirtualFunc = *VirtualFunc - (UINTN)VIRT_TO_PHYS_OFFSET;
  } else {
    *VirtualFunc = *VirtualFunc + (UINTN)VIRT_TO_PHYS_OFFSET;
  }
}


EFI_STATUS
DoMemoryAllocation (
  IN UINTN PhysicalFunc
  )
/*++

Routine Description:

  Allocate memory and creat the PageTable to set up physical-virtual map. The mapping rule is:
  1) if current driver is running below 2G, map virtual address 0-2G,2-4G to physical address 0-2G identically.
  2) if current driver is running above 2G, map virtual address 0-2G,2-4G to physical address 2-4G identically.

Arguments:

  PhysicalFunc  - Physical address where RuntimeTestFunc locates.

Returns:

  EFI_STATUS

--*/  
{  
  UINT32                      IndexOfPdEntries;
  EFI_STATUS                  Status;
  EFI_PHYSICAL_ADDRESS        PageAddress;
  PAGE_DIRECTORY_ENTRY        *PageDirectoryEntry;
  EFI_PHYSICAL_ADDRESS        AllocateMemory;

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

  PageDirectoryEntry =  (PAGE_DIRECTORY_ENTRY *)(UINTN)AllocateMemory;

  if (HighAddress) {
    //
    // If current driver is running above 2G, map virtual address 0-2G, 2-4G to physical address 2-4G identically.
    //
    PageAddress = VIRT_TO_PHYS_OFFSET;
  } else {
    //
    // If current driver is running below 2G, map virtual address 0-2G, 2-4G to physical address 0-2G identically.
    //
    PageAddress = 0;
  }

  //
  // Fill first 512 Page Directory entries to establish 1:1 Virtual(0-2G) to Physical mapping with 4MBytes PageSize.
  //
  for (IndexOfPdEntries = 0; IndexOfPdEntries < 512; IndexOfPdEntries++, PageDirectoryEntry++, PageAddress += 0x400000) {
    //
    // Fill in the Page Directory entries
    //
    PageDirectoryEntry->Uint32 = (UINT32)PageAddress;
    PageDirectoryEntry->Bits.ReadWrite = 1;
    PageDirectoryEntry->Bits.Present = 1;
    PageDirectoryEntry->Bits.PageSize = 1;
  }

  if (HighAddress) {
    //
    // If current driver is running above 2G, map virtual address 0-2G, 2-4G to physical address 2-4G identically.
    //
    PageAddress = VIRT_TO_PHYS_OFFSET;
  } else {
    //
    // If current driver is running below 2G, map virtual address 0-2G, 2-4G to physical address 0-2G identically.
    //
    PageAddress = 0;
  }

  //
  // Fill later 512 Page Directory entries to establish 1:1 Virtual(2-4G) to Physical mapping with 4MBytes PageSize.
  //
  for (IndexOfPdEntries = 0; IndexOfPdEntries < 512; IndexOfPdEntries++, PageDirectoryEntry++, PageAddress += 0x400000) {
    //
    // Fill in the Page Directory entries
    //
    PageDirectoryEntry->Uint32 = (UINT32)PageAddress;
    PageDirectoryEntry->Bits.ReadWrite = 1;
    PageDirectoryEntry->Bits.Present = 1;
    PageDirectoryEntry->Bits.PageSize = 1;
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
      *VirtualMapSize += DescriptorSize;
      //
      // if (physical address >= 2G) then virtual address = (physical address - 2G)
      // if (physical address < 2G) then virtual address = (physical address + 2G)
      //
      if (VirtualMemoryMap->PhysicalStart >= VIRT_TO_PHYS_OFFSET) {
        VirtualMemoryMap->VirtualStart  = VirtualMemoryMap->PhysicalStart - VIRT_TO_PHYS_OFFSET;
      } else {
        VirtualMemoryMap->VirtualStart  = VirtualMemoryMap->PhysicalStart + VIRT_TO_PHYS_OFFSET;
      }
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
  // Enable PageTable to go to virtual mode, and jump to Virtual Function Entry Point.
  //
  EnablePageTable(HighAddress, PageTable,VirtualFunc, HandOffAddr);
}
