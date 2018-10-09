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

  SCRTApp.h

--*/

#ifndef _SCRTAPP_H_
#define _SCRTAPP_H_

#include "SctLib.h"
//#include "EfiDebug.h"
#include EFI_GUID_DEFINITION(GlobalVariable)




#define SCRT_STUB_TABLE_SIGNATURE          0x5AA55AA5
#define SCRTFuncName       L"Runtime Test Function"
#define RUNTIME_FUNC_ADDRESS_GUID \
  { \
    0x8BA20E61, 0x92AA, 0x11d2, {0x07, 0x0E, 0x02, 0xE0, 0x98, 0x03, 0x2B, 0x8C } \
  }


typedef
EFI_STATUS
(EFIAPI *EFI_SCRT_TEST_FUNCTION) ();

typedef struct {
  UINT64                 Signature;
  EFI_PHYSICAL_ADDRESS   FuncAddr; 
} SCRT_STUB_TABLE;

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
;

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

  EFI_STATUS

--*/ 
;

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

  Change VirtualAddressMap to virtual address

Arguments:

  MemoryMapSize     - The size, in bytes, of the MemoryMap buffer
  DescriptorSize    - The size, in bytes, of an individual EFI_MEMORY_DESCRIPTOR
  MemoryMap         - A pointer to the current memory map
  VirtualMemoryMap  - A pointer to the modified virtual memory map
  VirtualMapSize    - A pointer to the size, in bytes, of the VirtualMemoryMap buffer

Returns:

  NONE

--*/ 
;


VOID
SetIVTable(
  VOID
  )
;


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
;



//
// IA32 Local  Function
// 
VOID
EnablePageTable (BOOLEAN HighAddress, UINTN  PageTables, UINTN FuncPointer, UINTN ConfInfo);

//
// x64 Local Function
// 
VOID
LoadNewPageTable (UINTN  FuncPointer, UINTN ConfigInfo);

//
// IA64 Local Function
// 
VOID
Virtual2PhysicalAddressMap (
  VOID
  );

VOID
JumpToTestFunc (UINTN FuncPointer, UINTN ConfInfo);

VOID
GoVirtual (
  UINTN                 VirtToPhysOffset,
  UINTN                 ContinuationFunction,
  UINTN                 ConfigInfo
  );

VOID
AddTranslation (
  UINTN                   VirtToPhysOffset,
  EFI_PHYSICAL_ADDRESS    PhysicalBase,
  UINTN                   TrNum,
  UINTN                   Attributes,
  UINTN                   PS
  );

VOID
AllocateMemForIvt (
  VOID
  );

VOID
SetupInterruptVectorTable (
  VOID
  );

VOID
SetMemoryAttributes (
  VOID
  );

VOID
Record2StorageArea (
  EFI_PHYSICAL_ADDRESS  PhysicalAddress,
  UINT64                PageNum
  );

EFI_STATUS
SCRTLogProcess(
  CHAR16  *InfFileName
);

typedef
VOID
(EFIAPI *Go_VIRTUAL_FUNC) (
  UINTN                 VirtToPhysOffset,
  UINTN                 ContinuationFunction,
  UINTN                 ConfigInfo
  );


//
// Page size encoding for supported page sizes
//
#define PAGE_SIZE_4K    0x0c
#define PAGE_SIZE_8K    0x0d
#define PAGE_SIZE_16K   0x0e
#define PAGE_SIZE_64K   0x10
#define PAGE_SIZE_256K  0x12
#define PAGE_SIZE_1M    0x14
#define PAGE_SIZE_4M    0x16
#define PAGE_SIZE_16M   0x18
#define PAGE_SIZE_64M   0x1a
#define PAGE_SIZE_256M  0x1c

#define LENGTH_4K      0x1000
#define LENGTH_8K      0x2000
#define LENGTH_16K     0x4000
#define LENGTH_64K     0x10000
#define LENGTH_256K    0x40000
#define LENGTH_1M      0x100000
#define LENGTH_4M      0x400000
#define LENGTH_16M     0x1000000
#define LENGTH_64M     0x4000000
#define LENGTH_256M    0x10000000

#pragma pack(1)
//
// IA32 Page-Directory Entry(4MB Page)
//
typedef union {
  struct {
    UINT32  Present:1;                // 0 = Not present in memory, 1 = Present in memory
    UINT32  ReadWrite:1;              // 0 = Read-Only, 1= Read/Write
    UINT32  UserSupervisor:1;         // 0 = Supervisor, 1=User
    UINT32  WriteThrough:1;           // 0 = Write-Back caching, 1=Write-Through caching
    UINT32  CacheDisabled:1;          // 0 = Cached, 1=Non-Cached
    UINT32  Accessed:1;               // 0 = Not accessed, 1 = Accessed (set by CPU)
    UINT32  Dirty:1;                  // 0 = Not Dirty, 1 = written by processor on access to page
    UINT32  PageSize:1;               // 1 indicates 4MBytes.
    UINT32  Global:1;                 // 0 = Not global page, 1 = global page TLB not cleared on CR3 write
    UINT32  Available:3;              // Available for use by system software
    UINT32  PAT:1;                    // Page Attribute table index.
    UINT32  Reserved:9;               // Reserved bits.
    UINT32  PageBaseAddress:10;       // Page Base Address
  } Bits;
  UINT32    Uint32;
} PAGE_DIRECTORY_ENTRY;
#pragma pack()

#endif
