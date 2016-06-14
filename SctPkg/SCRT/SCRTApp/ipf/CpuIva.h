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

  CpuIva.h

--*/

#ifndef   _CPU_IVA_H_
#define   _CPU_IVA_H_

//#include "EfiRuntimeLib.h"
//#include "EfiDebug.h"
//#include "LibSalPal.h"

extern EFI_PLABEL     mPalProcPlabel;


#define TR0    0x0
#define TR1    0x1
#define TR2    0x2

//
// Page number for supported page sizes
//
#define PAGE_NUM_4K    0x1
#define PAGE_NUM_8K    0x2
#define PAGE_NUM_16K   0x4
#define PAGE_NUM_64K   0x10
#define PAGE_NUM_256K  0x40
#define PAGE_NUM_1M    0x100
#define PAGE_NUM_4M    0x400
#define PAGE_NUM_16M   0x1000
#define PAGE_NUM_64M   0x4000
#define PAGE_NUM_256M  0x10000

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

//#define VIRT_TO_PHYS_OFFSET       (0x10000000000)  //1T, 1024G.
#define VIRT_TO_PHYS_OFFSET         (0x10000000000000)

//
// Implementation specific definitions
//
#define MAX_MEMMAP_ENTRIES        0x100
#define USING_MEMMAP_ENTRIES      (MAX_MEMMAP_ENTRIES/2)
#define BACKUP_MEMMAP_ENTRIES     (MAX_MEMMAP_ENTRIES/2)
#define HANDLER_LIST_END          0xffffffffffffffff
#define MAX_STORAGE_ENTRIES       0x80

typedef struct _MEMMAP_ENTRY{
  EFI_PHYSICAL_ADDRESS  BaseAddress;
  EFI_PHYSICAL_ADDRESS  EndAddress;
  UINT64                MemAttrib;
  UINT64                PageSize;
} MEMMAP_ENTRY;

typedef struct _STORAGE_ENTRY{
  EFI_PHYSICAL_ADDRESS  PhysicalAddress;
  UINT64                PageNum;
} STORAGE_ENTRY;



#define SIZEOF_MEMMAP_TABLE        MAX_MEMMAP_ENTRIES * sizeof (MEMMAP_ENTRY)
#define SIZEOF_MEMMAP_USING_TABLE  USING_MEMMAP_ENTRIES * sizeof (MEMMAP_ENTRY)
#define SIZEOF_MEMMAP_BACKUP_TABLE BACKUP_MEMMAP_ENTRIES * sizeof (MEMMAP_ENTRY)

#define SIZEOF_STORAGE_AREA        MAX_STORAGE_ENTRIES * sizeof(STORAGE_ENTRY)

typedef struct {
  UINT64       PageSize;
  UINT64       TlbPageSize;
} TLB_PAGE_SIZE_MAPPING;


typedef
VOID
(EFIAPI *IFP_INTERRUPT_HANDLER) (
  VOID
  );

typedef struct {
  EFI_PHYSICAL_ADDRESS  IvtOffset;
  IFP_INTERRUPT_HANDLER IntrHandlerBegin;
  IFP_INTERRUPT_HANDLER IntrHandlerEnd;
} INTERRUPT_HANDLER_ENTRY;

//
// The below declare is defined in IpfIvaHand.c
//
EFI_PHYSICAL_ADDRESS
GetFunctionAddress (
  IN IFP_INTERRUPT_HANDLER   Handler
  );

VOID
GetIvtInfo (
  OUT UINTN                 *IvtSize,
  OUT UINTN                 *IvtAlignment
  );

EFI_STATUS
BuildMemoryMapForTlbHandler (
  VOID
  );

VOID
SetupInterruptVectorTable (
  VOID
  );

VOID 
SetInterruptEnv (
  VOID
  );

VOID
AllocateMemForIvt (
  VOID
  );

UINT8
Log2 (
  IN UINT64   Operand
  );


UINT64
CaculateMaxAligned2Power (
  IN UINT64     Base,
  IN UINT64     Length
  );
VOID
PurgeTlbsRange (
  IN MEMMAP_ENTRY *Entry
 );

VOID
FlushCache (
  IN UINT64 BaseToFlush,
  IN UINT64 LengthToFlush
  );


EFI_STATUS
SearchTlbMapEntry (
  IN  EFI_PHYSICAL_ADDRESS  BaseAddress,
  IN  UINT64                Length,
  OUT EFI_PHYSICAL_ADDRESS  *StartEntry,
  OUT EFI_PHYSICAL_ADDRESS  *EndEntry  
  );

EFI_STATUS
EFIAPI
InsertNewMemoryNode (
  IN EFI_PHYSICAL_ADDRESS           BaseAddress,
  IN UINT64                         Length,
  IN UINT64                         TlbMemAttributes
  );

UINT64
GetProperTlbPageSize (
  IN UINT64   BaseAddress,
  IN UINT64   EndAddress
  );

BOOLEAN
RangeOverLapped (
  IN UINT64  Start1,
  IN UINT64  End1,
  IN UINT64  Start2,
  IN UINT64  End2
  );

//
// The below is asm file function declair
//
VOID
SetIVA (
  IN EFI_PHYSICAL_ADDRESS Iva
  );

EFI_PHYSICAL_ADDRESS
GetIva (
  VOID
  );

VOID
SetTR (
  IN UINTN                Tr,
  IN EFI_PHYSICAL_ADDRESS Base,
  IN UINTN                IpfPageSize
  );


VOID
InitializeInterruptControlRegisters (
  VOID
  );



//
// Fault handler prototypes
//
VOID
IvtStub (
  VOID
  );

VOID
IvtStubEnd (
  VOID
  );

VOID
DataTlbFaultHandlerBegin (
  VOID
  );

VOID
DataTlbFaultHandlerEnd (
  VOID
  );

VOID
InstructionTlbFaultHandlerBegin (
  VOID
  );

VOID
InstructionTlbFaultHandlerEnd (
  VOID
  );


VOID
FirstHandlerBegin (
  VOID
  );

VOID
LastHandlerEnd (
  VOID
  );

  
UINT64
GetProperTlbPageSize (
  IN UINT64   BaseAddress,
  IN UINT64   EndAddress
  );   


BOOLEAN
RangeOverLapped (
  IN UINT64  Start1,
  IN UINT64  End1,
  IN UINT64  Start2,
  IN UINT64  End2
  );

VOID
PurgeTlb (
  IN UINT64 Start, 
  IN UINT64 BitLength
  );

#endif
