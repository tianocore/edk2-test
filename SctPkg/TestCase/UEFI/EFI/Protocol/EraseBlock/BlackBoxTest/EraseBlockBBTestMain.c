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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EraseBlockBBTestMain.c

Abstract:

  Test Driver of Erase Block Protocol

--*/


#include "EraseBlockBBTestMain.h"

#define EFI_ERASE_BLOCK_TEST_GUID \
  {0x95A9A93E, 0xA86E, 0x4926, {0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87}}


//
// Global variables
//
EFI_HANDLE mImageHandle;

UINT8      EnterEvent;


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_ERASE_BLOCK_PROTOCOL_TEST_REVISION,
  EFI_ERASE_BLOCK_TEST_GUID,
  L"Erase Block Protocol Test",
  L"UEFI Erase Block Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0101,
    L"EraseBlocksFunction",
    L"Function auto test for ERASE BLOCK Protocol EraseBlocks().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEraseBlocksFunctionTest
  },
	
  {
    EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0201,
    L"EraseBlocksConformance",
    L"Conformance auto test for ERASE BLOCK Protocol EraseBlocks().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEraseBlocksConformanceTest
  },
 0
};


EFI_STATUS
InitializeEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
             &ImageHandle,
             &gBBTestProtocolField,
             gBBTestEntryField,
             UnloadEraseBlockBBTest,
             &gBBTestProtocolInterface
             );

}


EFI_STATUS
UnloadEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


EFI_STATUS
LocateBlockIoFromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO_PROTOCOL             **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  )
{
  EFI_STATUS                  Status;
  UINTN                       NoHandles, Index;
  EFI_HANDLE                  *HandleBuffer;
  EFI_ERASE_BLOCK_PROTOCOL    *OtherEraseBlock;

  //
  // Locate the Handles that the EraseBlock interface is bound to
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiEraseBlockProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (NoHandles <= 0 || HandleBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Device Error",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that EraseBlock bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiEraseBlockProtocolGuid,
                       (VOID **) &OtherEraseBlock
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - HandleProtocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      gtBS->FreePool (HandleBuffer);
      return Status;
      }
    if (OtherEraseBlock == EraseBlock) {
      break;
    }
  }

  //
  // Locate the BlockIo Protocol bound to EraseBlock Protocol
  //
  if (Index >= NoHandles) {
    //
    // No Handle Found!!
    //
    gtBS->FreePool (HandleBuffer);
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiBlockIoProtocolGuid,
                   (VOID **) BlockIo
                   ); 

  gtBS->FreePool (HandleBuffer);
  return Status;
}


EFI_STATUS
LocateBlockIo2FromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO2_PROTOCOL            **BlockIo2,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  )
{
  EFI_STATUS                  Status;
  UINTN                       NoHandles, Index;
  EFI_HANDLE                  *HandleBuffer;
  EFI_ERASE_BLOCK_PROTOCOL    *OtherEraseBlock;

  //
  // Locate the Handles that the EraseBlock interface is bound to
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiEraseBlockProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (NoHandles <= 0 || HandleBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Device Error",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that EraseBlock bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiEraseBlockProtocolGuid,
                       (VOID **) &OtherEraseBlock
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - HandleProtocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      gtBS->FreePool (HandleBuffer);
      return Status;
      }
    if (OtherEraseBlock == EraseBlock) {
      break;
    }
  }

  //
  // Locate the BlockIo2 Protocol bound to EraseBlock Protocol
  //
  if (Index >= NoHandles) {
    //
    // No Handle Found!!
    //
    gtBS->FreePool (HandleBuffer);
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   (VOID **) BlockIo2
                   ); 

  gtBS->FreePool (HandleBuffer);
  return Status;
}


/**
  Allocates a buffer of a certain pool type at a specified alignment.

  Allocates the number bytes specified by AllocationSize of a certain pool type with an alignment
  specified by Alignment.  The allocated buffer is returned.  If AllocationSize is 0, then a valid
  buffer of 0 size is returned.  If there is not enough memory at the specified alignment remaining
  to satisfy the request, then NULL is returned.
  If Alignment is not a power of two and Alignment is not zero, then ASSERT().

  @param  PoolType              The type of pool to allocate.
  @param  AllocationSize        The number of bytes to allocate.
  @param  Alignment             The requested alignment of the allocation.  Must be a power of two.                            If Alignment is zero, then byte alignment is used.
                                If Alignment is zero, then byte alignment is used.

  @return A pointer to the allocated buffer or NULL if allocation fails.

**/
VOID *
AllocateAlignedPool (
  IN EFI_MEMORY_TYPE  PoolType,
  IN UINTN            AllocationSize,
  IN UINTN            Alignment
  )
{
  EFI_STATUS  Status;
  VOID        *RawAddress;
  UINTN       AlignedAddress;
  UINTN       AlignmentMask;
  UINTN       OverAllocationSize;
  UINTN       RealAllocationSize;
  VOID        **FreePointer;

  //
  // Alignment must be a power of two or zero.
  //
  ASSERT ((Alignment & (Alignment - 1)) == 0);
  
  if (Alignment == 0) {
    AlignmentMask = Alignment;
  } else {
    AlignmentMask = Alignment - 1;
  }
  //
  // Calculate the extra memory size, over-allocate memory pool and get the aligned memory address. 
  //
  OverAllocationSize  = sizeof (RawAddress) + AlignmentMask;
  RealAllocationSize  = AllocationSize + OverAllocationSize;
  //
  // Make sure that AllocationSize plus OverAllocationSize does not overflow. 
  //
  ASSERT (RealAllocationSize > AllocationSize); 

  Status = gtBS->AllocatePool (PoolType, RealAllocationSize, (VOID **) &RawAddress);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  AlignedAddress      = ((UINTN) RawAddress + OverAllocationSize) & ~AlignmentMask;
  //
  // Save the original memory address just before the aligned address.
  //
  FreePointer         = (VOID **)(AlignedAddress - sizeof (RawAddress));
  *FreePointer        = RawAddress;

  return (VOID *) AlignedAddress;
}


/**
  Frees a buffer that was previously allocated with one of the aligned pool allocation functions 
  in the Memory Allocation Library.

  Frees the buffer specified by Buffer.  Buffer must have been allocated on a previous call to the
  aligned pool allocation services of the Memory Allocation Library.
  If Buffer was not allocated with an aligned pool allocation function in the Memory Allocation
  Library, then ASSERT().

  @param  Buffer                Pointer to the buffer to free.

  @return free aligned pool function status

**/
EFI_STATUS
FreeAlignedPool (
  IN VOID   *Buffer
  )
{
  VOID        *RawAddress;
  VOID        **FreePointer;
  EFI_STATUS  Status;

  //
  // Get the pre-saved original address in the over-allocate pool.
  //
  FreePointer = (VOID **)((UINTN) Buffer - sizeof (RawAddress));
  RawAddress  = *FreePointer;

  Status = gtBS->FreePool (RawAddress);

  return Status;
}

VOID
NotifyFunction (
  EFI_EVENT    Event,
  VOID         *Context
  )
{
  EnterEvent = 1;
  return;
}

