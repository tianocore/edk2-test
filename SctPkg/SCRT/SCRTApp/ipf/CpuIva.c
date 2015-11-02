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

  CpuIva.c

--*/
#include "SctLib.h"
#include "IpfDefines.h"
#include "CpuIva.h"



EFI_PHYSICAL_ADDRESS    mNewIva = 0;
TLB_PAGE_SIZE_MAPPING   mPageSizeMap;
MEMMAP_ENTRY            *mMemMapEntry = NULL;
UINTN                   mMemMapNumber = 0;
STORAGE_ENTRY           *mStoragePtr  = NULL ;
STORAGE_ENTRY           *mOldStoragePtr  = NULL ;
UINT64                  mStorageEntry = 0;


TLB_PAGE_SIZE_MAPPING mSupportedTlbPageSize[]= {  
  {0x1000,     PAGE_SIZE_4K   },
  {0x2000,     PAGE_SIZE_8K   },    
  {0x4000,     PAGE_SIZE_16K  },   
  {0x10000,    PAGE_SIZE_64K  },   
  {0x40000,    PAGE_SIZE_256K },  
  {0x100000,   PAGE_SIZE_1M   },    
  {0x400000,   PAGE_SIZE_4M   },    
  {0x1000000,  PAGE_SIZE_16M  },
  {0x4000000,  PAGE_SIZE_64M  },
  {0x10000000, PAGE_SIZE_256M }
  };

UINTN   mNumberOfTlbMapping = sizeof (mSupportedTlbPageSize) / sizeof (TLB_PAGE_SIZE_MAPPING);

//
// This is a list of interrupt and fault handlers that we support.
// The structure elements are (offset within the IVT, handler start label, handler end label)
//
INTERRUPT_HANDLER_ENTRY STATIC CONST  mHandler[7] = {
  OFF_ITLBFLT,
  InstructionTlbFaultHandlerBegin,
  InstructionTlbFaultHandlerEnd,
  OFF_DTLBFLT,
  DataTlbFaultHandlerBegin,
  DataTlbFaultHandlerEnd,
  OFF_ALTITLBFLT,
  InstructionTlbFaultHandlerBegin,
  InstructionTlbFaultHandlerEnd,
  OFF_ALTDTLBFLT,
  DataTlbFaultHandlerBegin,
  DataTlbFaultHandlerEnd,
  OFF_IACCESSRTFLT,
  InstructionTlbFaultHandlerBegin,
  InstructionTlbFaultHandlerEnd,
  OFF_DACCESSRTFLT,
  DataTlbFaultHandlerBegin,
  DataTlbFaultHandlerEnd,
  HANDLER_LIST_END,
  NULL,
  NULL
};


UINT8
Log2 (
  IN UINT64   Operand
  )
{
  UINT8 Bitpos;
  Bitpos = 0;

  if (Operand == 0) {
    return (0xff);
  }

  while (Operand != 0) {
    Operand >>= 1;
    Bitpos++;
  }
  return (Bitpos - 1);

}


BOOLEAN
RangeOverLapped (
  IN UINT64  Start1,
  IN UINT64  End1,
  IN UINT64  Start2,
  IN UINT64  End2
  )
/*++

Routine Description:

  Judge if the two ranges are overlapped

Arguments:

    Start1       - The Start address of range1
    End1         - The End address of range1
    Start2       - The Start address of range2
    End2         - The End address of range2

Returns:

  TRUE           - The two ranges are overlapped
  FALSE          - The two ranges are not overlapped

--*/
{  
  if (((Start1 >= Start2) && (Start1 <= End2)) || ((Start2 >= Start1) && (Start2 <= End1))) {
    return TRUE;  
  } else {
    return FALSE;
  }  
}


EFI_PHYSICAL_ADDRESS
GetFunctionAddress (
  IN  IFP_INTERRUPT_HANDLER  Handler
  )
/*++

Routine Description:

  Get the Entry pointer of the Handler

Arguments:

  Handler - The handler which be accessed

Returns:

  The EntryPointer of the handler

--*/
{
  EFI_PLABEL  *Plabel;

  Plabel  = (EFI_PLABEL *) ((VOID *) Handler);
  return Plabel->EntryPoint;
}


UINT64
GetProperTlbPageSize (
  IN UINT64   BaseAddress,
  IN UINT64   EndAddress
  )
/*++

Routine Description:

  Caculate the Proper TLB page size based on the base address and range length

Arguments:

  BaseAddress    - The memory range start address
  EndAddress     - The memory range end address
  
Returns:

  Return the proper TLB page size

--*/
{
  UINTN             Index;
  UINT64            Length;
  UINT64            TlbPageSize;
  
  TlbPageSize = PAGE_SIZE_4K;
  Length = EndAddress + 1 - BaseAddress;
  for (Index = 0; Index < mNumberOfTlbMapping; Index++) {
    if (((BaseAddress & (mSupportedTlbPageSize[Index].PageSize - 1)) == 0) && \
        ((Length & (mSupportedTlbPageSize[Index].PageSize - 1)) == 0)) {
      TlbPageSize = mSupportedTlbPageSize[Index].TlbPageSize;
    } else {
      break;
    }    
  }
  
  return TlbPageSize;
}


EFI_STATUS
BuildMemoryMapForTlbHandler (
  VOID
  )
/*++

Routine Description:

  This function sets up the memory map. This map is
  later used by Data TLB fault handler to insert TCs.
  This is the initial map, which is later fixed up
  every time some one calls SetMemoryAttributes.

Arguments:
    
  None
    
Returns:

  EFI_STATUS      - For now, always return success

--*/
{  
  MEMMAP_ENTRY                     *MemEntry; 
  UINT8                            SizeOfMemorySpace;
  
  MemEntry = mMemMapEntry;

  //
  // Hardcode memory space is 50 bit
  //
  SizeOfMemorySpace  = 50;

  //
  // Initialize the Tlb Memory Space Map
  //
  MemEntry->EndAddress = mNewIva - 1;
  MemEntry->MemAttrib  = MA_WBU;
  MemEntry->PageSize   = GetProperTlbPageSize (0, MemEntry->EndAddress);

  MemEntry++;
  
  MemEntry->BaseAddress = mNewIva;
  MemEntry->EndAddress  = mNewIva  + mPageSizeMap.PageSize - 1;
  MemEntry->MemAttrib   = MA_WBU;
  MemEntry->PageSize    = mPageSizeMap.TlbPageSize;
  
  MemEntry++;
  
  MemEntry->BaseAddress = mNewIva + mPageSizeMap.PageSize;
  MemEntry->EndAddress  = SctLShiftU64 (1, SizeOfMemorySpace) - 1;
  MemEntry->MemAttrib   = MA_WBU;
  MemEntry->PageSize    = GetProperTlbPageSize (MemEntry->BaseAddress, MemEntry->EndAddress);
 
  mMemMapNumber = 3;
  
  return EFI_SUCCESS;
}

VOID
GetIvtInfo (
  OUT UINTN                 *IvtSize,
  OUT UINTN                 *IvtAlignment
  )
/*++

Routine Description:

  This function returns the size and alignment
  requiremens for IVT and exception handlers.

Arguments:

  IvtSize       - Pointer to the size of the memory block required for IVT,
  IvtAlignment  - Pointer to the Alignment for the memory block required for IVT

Returns:

  None

--*/
{
  //
  // Since the IVT only provides 0x400 bytes for interrupt
  // handler, we will have to keep the main code somewhere else.
  // The handler entry point is inside IVT, but that jumps to the
  // actual code outside IVT.
  //
  //                 __________________________________ IVT starts here
  //                | 32k IVT                         |
  //                |                                 |
  //                |                                 |
  //                |.................................| TLB fault entry point
  //                | IVT stub                        |
  //                | offset of the handler           |------------
  //                |                                 |            |
  //                |                                 |            |
  //                |                                 |            |
  //                |                                 |            |
  //                |                                 |            |
  //                |_________________________________| IVT end    |
  //                |                                 |            |
  //                |  Memory Descriptor Table        |            |
  //                |_________________________________|            |
  //                |                                 |            |
  //                |  Storage Area                   |            |
  //                |                                 |            |    
  //                |_________________________________|            |
  //                |                                 |Handlers    |
  //                |                                 |            |
  //                |.................................|            |
  //                | Data TLB Handler    ____________|_ __________|
  //                | Self contained code             |
  //                |.................................|
  //                |                                 |
  //                |                                 |
  //                |  
  //                |                                 |
  //                |_________________________________| Handlers end
  //
  //
  // We keep a table of memorymap(0x100 in number)
  // immediately following the IVT. And Storage Area
  // immediately following the MemoryMap Table.
  //
  *IvtSize = GetFunctionAddress (LastHandlerEnd) -
    GetFunctionAddress (FirstHandlerBegin) +
    SIZEOF_STORAGE_AREA  +
    SIZEOF_MEMMAP_TABLE +
    IVT_SIZE;
  *IvtAlignment = IVT_SIZE;
}

VOID
SetupInterruptVectorTable (
  VOID
  )
/*++

Routine Description:

  This function sets up the interrupt vector table and
  programs processor registers accordingly.

Arguments:

  None 
  
Returns:

  None

--*/
{
  EFI_PHYSICAL_ADDRESS  OldIva;
  EFI_PHYSICAL_ADDRESS  Src1;
  EFI_PHYSICAL_ADDRESS  Src2;
  EFI_PHYSICAL_ADDRESS  Dest1;
  EFI_PHYSICAL_ADDRESS  Dest2;
  UINTN                 i;
  UINTN                 Count;
  UINTN                 Offset;

  //
  // Get current IVT address 
  // Copy it to the preallocated address NewIva.
  //
  OldIva = GetIva ();

  //
  // Copy the original IV table to the new RAM location
  //
  SctCopyMem ((VOID *) mNewIva, (VOID *) OldIva, IVT_SIZE);

  Dest2 = mNewIva + IVT_SIZE + SIZEOF_MEMMAP_TABLE + SIZEOF_STORAGE_AREA;
  Src1  = GetFunctionAddress (IvtStub);

  for (i = 0; mHandler[i].IvtOffset != HANDLER_LIST_END; i++) {
    //
    // Install the IVT stubs to the appropriate locations
    //
    Dest1 = mNewIva + mHandler[i].IvtOffset;
    Count = GetFunctionAddress (IvtStubEnd) - Src1;
    SctCopyMem ((VOID *) Dest1, (VOID *) Src1, Count);
    Dest1 += Count;

    //
    // Install the actual handler to the appropriate locations
    //
    Src2  = GetFunctionAddress (mHandler[i].IntrHandlerBegin);
    Count = GetFunctionAddress (mHandler[i].IntrHandlerEnd) - Src2;

    SctCopyMem ((VOID *) Dest2, (VOID *) Src2, Count);
    Offset = Dest2 - mNewIva - mHandler[i].IvtOffset;

    //
    // Patch the IVT stub with the offset of the actual handler
    //
    SctCopyMem ((VOID *) Dest1, (VOID *) (&Offset), sizeof (UINTN));

    Dest2 += Count;
  }
  //
  // The next block locations are used for storing the memory map
  // Zero that area to begin with
  //
  SctSetMem ((VOID *) (mNewIva + IVT_SIZE), SIZEOF_MEMMAP_TABLE, 0);

  
  //
  // Get current memory map and store this information in the memory map table to be used by
  // data TLB fault handler
  //
  
  mMemMapEntry  = (MEMMAP_ENTRY *)(UINTN)(mNewIva + IVT_SIZE );
  
  SetInterruptEnv ();   
  
  BuildMemoryMapForTlbHandler ();  
}

VOID 
EFIAPI
SetInterruptEnv (
  VOID
  )
/*++

Routine Description:

  This function is used to initialize the Interrupt related registers this function will be called
  by all the Processors

Arguments:

  None
  
Returns:

  None

--*/  
{
  EFI_PHYSICAL_ADDRESS  Iva;

  InitializeInterruptControlRegisters ();

  //
  // For safe, flush Iva memory from cache
  //
  Iva = GetIva ();
  FlushCache(Iva,0x10000);
  FlushCache(mNewIva,0x10000);  
  //
  // Set IVA Virtual address
  //
  SetIVA(mNewIva + VIRT_TO_PHYS_OFFSET);  

  //
  // Pin TR0 to cover SCRT new IVA
  //
  PurgeTlb(mNewIva + VIRT_TO_PHYS_OFFSET, mPageSizeMap.TlbPageSize << 2);
  SetTR(TR0, mNewIva, mPageSizeMap.TlbPageSize);
}



VOID
AllocateMemForIvt (
  VOID
  )
/*++

Routine Description:

  This function allocated a contiguous memory block for IVT. 
  These need to be contiguous so that we can pin TR[0] to
  cover. IVT and exception handler code must be anchored 
  using TR so that the SCRT can handle the TLB faults in virtual mode.
  
Arguments:

  None
  
Returns:
  
  None
  
--*/
{
  UINTN                 IvtSize;
  UINTN                 IvtAlign;
  UINTN                 Alignment;
  UINTN                 PagesRequested;
  UINTN                 NumFreePages;
  EFI_PHYSICAL_ADDRESS  FreeMemBase;
  EFI_PHYSICAL_ADDRESS  MemBase;
  EFI_STATUS            Status;
  UINT64                Length;
  UINTN                 Index;

  GetIvtInfo (&IvtSize, &IvtAlign);

  Length = IvtSize;
  
  for (Index = 0; Index < mNumberOfTlbMapping; Index++) {
    if (Length > mSupportedTlbPageSize[Index].PageSize ) {
      continue;
    } else {      
      mPageSizeMap.TlbPageSize = mSupportedTlbPageSize[Index].TlbPageSize;
      mPageSizeMap.PageSize = mSupportedTlbPageSize[Index].PageSize;
      break;      
    }    
  }
  
  //
  // Since allocatePages does not guarantee alignment, we will
  // ask for more pages so that they should contain at least one
  // properly aligned block of the requested size.
  // We will use that block and free rest
  // of the memory.
  //
  Alignment       = mPageSizeMap.PageSize;
  PagesRequested  = 2 * EFI_SIZE_TO_PAGES (Alignment) - 1;

  //
  // Allocate runtime memory 
  //
  Status =  tBS->AllocatePages (
                  AllocateAnyPages,
                  EfiRuntimeServicesData,
                  PagesRequested,
                  &MemBase
                  );

  ASSERT_EFI_ERROR (Status);

  //
  // Align Memory according to Alignment
  // and deallocate extra pages above and below.
  //
  FreeMemBase   = MemBase;

  MemBase       = (FreeMemBase + Alignment - EFI_PAGE_SIZE) & (~(Alignment - 1));

  NumFreePages  = EFI_SIZE_TO_PAGES (MemBase - FreeMemBase);

  if (NumFreePages != 0) {
    Status =  tBS->FreePages (
                    FreeMemBase,
                    NumFreePages
                    );
  }

  ASSERT_EFI_ERROR (Status);

  mNewIva      = (MemBase + IvtAlign - 1) & (~(IvtAlign - 1));
  FreeMemBase   = mNewIva + (EFI_SIZE_TO_PAGES (IvtSize)) * EFI_PAGE_SIZE;

  NumFreePages  = PagesRequested - EFI_SIZE_TO_PAGES (FreeMemBase -MemBase) - NumFreePages;

  if (NumFreePages != 0) {
    Status =  tBS->FreePages (
                    FreeMemBase,
                    NumFreePages
                    );
  }
  mOldStoragePtr = mStoragePtr  =  (STORAGE_ENTRY*)(UINTN)(mNewIva + IVT_SIZE + SIZEOF_MEMMAP_TABLE);
}


UINT64
CaculateMaxAligned2Power (
  IN UINT64     Base,
  IN UINT64     Length
  )
{
  UINTN     Index;
  UINT64    MaxAlignedValue;
  
  MaxAlignedValue = EFI_PAGE_SIZE;
  for (Index = 0; Index < mNumberOfTlbMapping; Index++) {
    if (((Base & (mSupportedTlbPageSize[Index].PageSize - 1)) == 0) && \
        (mSupportedTlbPageSize[Index].PageSize <= Length)) {
      MaxAlignedValue = mSupportedTlbPageSize[Index].PageSize;
    } else {
      break;
    }    
  } 
   
  return MaxAlignedValue;   
} 


VOID
PurgeTlbsRange (
  IN MEMMAP_ENTRY *Entry
 )
{
  UINT64      Length;
  UINT64      BitLength;
  UINT64      MaxTlbLength;
  UINT64      Start;
  
  Start = Entry->BaseAddress;
  
  Length = Entry->EndAddress - Start + 1;
  
  while (Length != 0) {
    MaxTlbLength = CaculateMaxAligned2Power (Start, Length);  
    BitLength = Log2 (MaxTlbLength);
    PurgeTlb (Start + VIRT_TO_PHYS_OFFSET, BitLength << 2);
    Start += MaxTlbLength;
    Length -= MaxTlbLength;    
  }
  
  return;
  
}


EFI_STATUS
SearchTlbMapEntry (
  IN  EFI_PHYSICAL_ADDRESS  BaseAddress,
  IN  UINT64                Length,
  OUT EFI_PHYSICAL_ADDRESS  *StartEntry,
  OUT EFI_PHYSICAL_ADDRESS  *EndEntry  
  )
/*++

Routine Description:

  Search a segment of memory space in Tlb memory map. The result is a range of Tlb entry list.

Arguments:

  BaseAddress       - The start address of the segment.  
  Length            - The length of the segment.  
  StartLink         - The first TLB entry involves this segment of memory space.  
  EndLink           - The last TLB entry involves this segment of memory space.  

Returns:

  EFI_SUCCESS       - Successfully found the entry.  
  EFI_NOT_FOUND     - Not found.

--*/
{
  UINTN              Index;
  MEMMAP_ENTRY       *Entry;
  
  ASSERT (Length != 0);
  *StartEntry = 0;
  *EndEntry   = 0;
  Entry     = mMemMapEntry;

  for (Index = 0; Index< mMemMapNumber; Index++ ,Entry++){
    if (BaseAddress >= Entry->BaseAddress && BaseAddress <= Entry->EndAddress) {
      *StartEntry = (EFI_PHYSICAL_ADDRESS)Entry;
    }
    if (*StartEntry != 0) {
      if ((BaseAddress + Length - 1) >= Entry->BaseAddress && 
          (BaseAddress + Length - 1) <= Entry->EndAddress ) {
        *EndEntry = (EFI_PHYSICAL_ADDRESS)Entry;
        return EFI_SUCCESS;
      }
    }
  }
  return EFI_NOT_FOUND;
}



EFI_STATUS
EFIAPI
InsertNewMemoryNode (
  IN EFI_PHYSICAL_ADDRESS           BaseAddress,
  IN UINT64                         Length,
  IN UINT64                         TlbMemAttributes
  )
/*++

Routine Description:

  Insert a new node into MemoryMap list, usually for IO space.

Arguments:

  BaseAddress         - The base address of the setting memory range
  Length              - The length of the setting memory range
  TlbMemAttributes    - The attributes will be set to the setting memory range

Returns: 

--*/
{
  UINTN                            Index;
  UINTN                            StartIndex;
  UINTN                            EndIndex;
  EFI_STATUS                       Status;
  BOOLEAN                          AttribChanged;
  BOOLEAN                          TopFlag;
  BOOLEAN                          BottomFlag;
  BOOLEAN                          MergeFlag;
  MEMMAP_ENTRY                     TopEntry;
  MEMMAP_ENTRY                     BottomEntry;
  MEMMAP_ENTRY                     *MapEntry;
  MEMMAP_ENTRY                     *TempMapEntry;
  MEMMAP_ENTRY                     *BackUpEntry;
  EFI_PHYSICAL_ADDRESS             StartEntry;
  EFI_PHYSICAL_ADDRESS             EndEntry;
  
  if (Length == 0) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Make sure the BaseAddress and Length is page size aligned
  //
  
  if (((BaseAddress & EFI_PAGE_MASK ) != 0) || ((Length & EFI_PAGE_MASK) != 0)) {
    return EFI_ACCESS_DENIED;
  }
  
  //
  // Don't change the memory range attributes that covers the IVT 
  // this range has been covered by itr[0].
  //
  if (RangeOverLapped (mNewIva, mNewIva + mPageSizeMap.PageSize - 1, BaseAddress, BaseAddress + Length - 1 )) {
    return EFI_ACCESS_DENIED;
  }

  if (mMemMapNumber  >= USING_MEMMAP_ENTRIES - 2) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Search for the list of descriptors that cover the range BaseAddress to BaseAddress+Length
  //
  Status = SearchTlbMapEntry (BaseAddress, Length, &StartEntry, &EndEntry);
  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
  }

  StartIndex = (StartEntry - (EFI_PHYSICAL_ADDRESS)mMemMapEntry)/sizeof(MEMMAP_ENTRY);
  EndIndex   = (EndEntry - (EFI_PHYSICAL_ADDRESS)mMemMapEntry)/sizeof(MEMMAP_ENTRY);

  //
  // Convert/Insert the list of descriptors from StartLink to EndLink
  //
  AttribChanged     = FALSE;
  TopFlag           = FALSE;
  BottomFlag        = FALSE;
  MergeFlag         = FALSE;
  MapEntry          = mMemMapEntry ;
  for (Index = 0; Index < mMemMapNumber; Index++, MapEntry++) {
    
    if (MapEntry->MemAttrib != TlbMemAttributes) {
      if (Index == StartIndex) {
        if (MapEntry->BaseAddress != BaseAddress) {
          BottomFlag = TRUE;
          SctCopyMem (&BottomEntry, MapEntry, sizeof (MEMMAP_ENTRY));
          BottomEntry.EndAddress  = BaseAddress - 1;
          BottomEntry.PageSize    = GetProperTlbPageSize (BottomEntry.BaseAddress, BottomEntry.EndAddress);
          MapEntry->BaseAddress   = BaseAddress;
          MapEntry->PageSize      = GetProperTlbPageSize (MapEntry->BaseAddress, MapEntry->EndAddress);
        } else {
          TempMapEntry = MapEntry;
          TempMapEntry--;
          if (TempMapEntry->MemAttrib == TlbMemAttributes) {
            //
            // Merge adjacent Tlb entry with the same attribute
            //
            MergeFlag =  TRUE;
            TempMapEntry->EndAddress  = BaseAddress + Length - 1;
            TempMapEntry->PageSize    = GetProperTlbPageSize (TempMapEntry->BaseAddress, TempMapEntry->EndAddress);
            TempMapEntry++;
            TempMapEntry->BaseAddress  = BaseAddress + Length;
            TempMapEntry->PageSize    = GetProperTlbPageSize (TempMapEntry->BaseAddress, TempMapEntry->EndAddress);
          } 
        }
      }
      
      if (Index == EndIndex) {
        if ((MapEntry->BaseAddress != BaseAddress + Length) && (MapEntry->EndAddress != BaseAddress + Length - 1)) {
          TopFlag  = TRUE;  
          SctCopyMem (&TopEntry, MapEntry, sizeof (MEMMAP_ENTRY));
          MapEntry->EndAddress    = BaseAddress + Length - 1;
          MapEntry->PageSize      = GetProperTlbPageSize (MapEntry->BaseAddress, MapEntry->EndAddress);
          TopEntry.BaseAddress    = BaseAddress + Length;
          TopEntry.PageSize       = GetProperTlbPageSize (TopEntry.BaseAddress, TopEntry.EndAddress);
        } 
      }

      if ((Index >= StartIndex) && (Index <= EndIndex)) {
        //
        // Change Entry attribute to UC and purge TLB
        //
        AttribChanged = TRUE;
        if (!((Index == StartIndex) && MergeFlag)) {
          MapEntry->MemAttrib = TlbMemAttributes;
          //FlushCache (MapEntry->BaseAddress, MapEntry->EndAddress - MapEntry->BaseAddress + 1);
          PurgeTlbsRange (MapEntry);
        }
      }
    }
  }

  if (AttribChanged) {
    MapEntry = mMemMapEntry;
    BackUpEntry   = MapEntry + SIZEOF_MEMMAP_USING_TABLE;
    //
    // BackUp MemoryMap Entries
    //
    SctCopyMem (BackUpEntry, MapEntry, SIZEOF_MEMMAP_USING_TABLE);
    SctSetMem (MapEntry, SIZEOF_MEMMAP_USING_TABLE, 0);

    //
    // Insert Bottom/TopEntry into MemoryMap Entries
    //
    for (Index = 0; Index < mMemMapNumber + 2; MapEntry++, Index++){
      if ((Index == StartIndex) && BottomFlag) {
        SctCopyMem (MapEntry, &BottomEntry, sizeof (MEMMAP_ENTRY));
      } else if ((Index == EndIndex + 2) && TopFlag) {
        SctCopyMem (MapEntry, &TopEntry, sizeof (MEMMAP_ENTRY));
      } else {
        SctCopyMem (MapEntry, BackUpEntry, sizeof (MEMMAP_ENTRY));
        BackUpEntry++;
      } 
    }

    BackUpEntry   = mMemMapEntry + SIZEOF_MEMMAP_USING_TABLE;
    SctSetMem (BackUpEntry, SIZEOF_MEMMAP_BACKUP_TABLE,0);
    mMemMapNumber += 2;
    AttribChanged = FALSE;
  }  
  return EFI_SUCCESS;
}


VOID
Record2StorageArea (
  EFI_PHYSICAL_ADDRESS  PhysicalAddress,
  UINT64                PageNum
  )
/*++

Routine Description:

  Save each IO entry information to Storage Area. Later be used 
  by SetMemoryAttributes to insert new nodes into MemoryMap list.

Arguments:

  PhysicalAddress      - The base address of the IO entry
  PageNum              - The page number of IO entry

Returns: 

  None
  
--*/  
{
   if (mStorageEntry + 1 > MAX_STORAGE_ENTRIES) {
     return;
   }
   
   mStoragePtr->PhysicalAddress = PhysicalAddress;
   mStoragePtr->PageNum         = PageNum;
   mStoragePtr++;
   mStorageEntry++;
}

VOID
SetMemoryAttributes (
  VOID
  )
/*++

Routine Description:

  Use IO space information saved in Storage Area to
  insert new nodes into MemoryMap list. Data TLB miss
  handler will use these MemoryMap nodes to insert TC.

Arguments:

  None
 
Returns: 

  None
  
--*/    
{
  while(mStorageEntry-- > 0) {
    InsertNewMemoryNode(mOldStoragePtr->PhysicalAddress, (mOldStoragePtr->PageNum)<< EFI_PAGE_SHIFT,MA_UC);
    mOldStoragePtr++;
  }
  //SctSetMem (mOldStoragePtr, SIZEOF_STORAGE_AREA, 0); 
}
