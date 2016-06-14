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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  BlockIo2BBTestMain.c

Abstract:

  Test Driver of Block I/O 2 Protocol

--*/

#include "SctLib.h"
#include "BlockIo2BBTestMain.h"

EFI_EVENT TimerEvent = NULL;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  BLOCK_IO2_PROTOCOL_TEST_REVISION,
  IHV_BLOCK_IO2_PROTOCOL_GUID,
  L"Block I/O 2 Protocol Test",
  L"UEFI Block I/O 2 Protocol Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  //
  // Conformance test section
  //
  {
    BLOCK_IO2_PROTOCOL_READBLOCKSEX_CONFORMANCE_AUTO_GUID,
    L"ReadBlocksEx_Conf",
    L"Perform auto consistency checkes on the ReadBlocksEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadBlocksExConformanceAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_FLUSHBLOCKSEX_CONFORMANCE_AUTO_GUID,
    L"FlushBlocksEx_Conf",
    L"Perform auto consistency checkes on the FlushBlocksEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushBlocksExConformanceAutoTest
  },
  //
  // Function test section
  //
  {
    BLOCK_IO2_PROTOCOL_RESET_FUNCTION_AUTO_GUID,
    L"Reset_Func",
    L"Invoke Reset and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_READBLOCKSEX_FUNCTION_AUTO_GUID,
    L"ReadBlocksEx_Func",
    L"Invoke ReadBlocksEx and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadBlocksExFunctionAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_FLUSHBLOCKSEX_FUNCTION_AUTO_GUID,
    L"FlushBlocksEx_Func",
    L"Invoke FlushBlocksEx and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushBlocksExFunctionAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_WRITEBLOCKSEX_CONFORMANCE_AUTO_GUID,
    L"WriteBlocksEx_Conf",
    L"Perform auto consistency checkes on the WriteBlocksEx interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteBlocksExConformanceAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_WRITEBLOCKSEX_FUNCTION_AUTO_GUID,
    L"WriteBlocksEx_Func",
    L"Invoke WriteBlocksEx and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteBlocksExFunctionAutoTest
  },
  {
    BLOCK_IO2_PROTOCOL_MEDIAINFO_INTEGRITY_AUTO_GUID,
    L"MediaInfo_Integrity",
    L"Check BlockIo2 Media Info Integrity within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMediaInfoCheckAutoTest
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestBlockIo2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Entry Point Declaration
//

/**
 *  Block I/O 2 Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestBlockIo2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  gtBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestBlockIo2ProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestBlockIo2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS          Status;
  
  gtBS->CloseEvent (TimerEvent);

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

/**
 *  assistant function to verify two buffer
 *  @param  Buffer1 first buffer
 *  @param  Buffer2 second buffer
 *  @param  BufferSize size of the buffer
 *  @return Count of the different byte of two buffers
*/
UINTN
VerifyBuffer (
  IN UINT8            *Buffer1,
  IN UINT8            *Buffer2,
  IN UINTN            BufferSize
  )
{
  UINTN               Loop;
  UINTN               Count;

  Count = 0;
  for (Loop = 0; Loop < BufferSize; Loop++) {
    if (Buffer1[Loop] != Buffer2[Loop]) {
      Count++;
    }
  }

  return Count;
}

/**
 *  assistant function to locate DevicePath Protocol from BlockIo2 Protocol
 *  @param  BlockIo2 protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromBlockIo2 (
  IN EFI_BLOCK_IO2_PROTOCOL               *BlockIo2,
  IN OUT EFI_DEVICE_PATH_PROTOCOL          **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     NoHandles;
  EFI_HANDLE                *HandleBuffer;
  EFI_BLOCK_IO2_PROTOCOL    *OtherBlockIo2;

  //
  // Locate the Handle that the BlockIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - Locate Block IO 2 protocol",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // Find the exact handle that BlockIo2 bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiBlockIo2ProtocolGuid,
                     &OtherBlockIo2
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - Locate Block IO 2 protocol from handle",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    if (OtherBlockIo2 == BlockIo2) {
      break;
    }
  }

  if (Index >= NoHandles) {
    //
    // No Handle Found!!
    //
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate the DevicePath Protocol bound to BlockIo Protocol
  //
  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   DevicePath
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Locate Device Path protocol from handle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Free resource
  //
  Status = gtBS->FreePool (HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free handle buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  assistant function to locate BlockIo2 Protocol from DevicePath Protocol
 *  @param  BlockIo2 protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateBlockIo2FromDevicePath (
  IN OUT EFI_BLOCK_IO2_PROTOCOL           **BlockIo2,
  IN EFI_DEVICE_PATH_PROTOCOL             *DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     NoHandles;
  EFI_HANDLE                *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL  *OtherDevicePath;

  //
  // Locate the Handle that the DevicePath interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiDevicePathProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - Locate Device Path protocol",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    return EFI_NOT_FOUND;
  }

  //
  // Find the exact handle that blockIo2 bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiDevicePathProtocolGuid,
                     &OtherDevicePath
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - Locate Device Path protocol from handle",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    if (OtherDevicePath == DevicePath) {
      break;
    }
  }

  if (Index >= NoHandles) {
    //
    // No Handle Found!!
    //
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate the BlockIo Protocol bound to DevicePath Protocol
  //
  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   BlockIo2
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Locate Block IO 2 protocol from handle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Free resource
  //
  Status = gtBS->FreePool (HandleBuffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free handle buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?
 *  @param  Seconds time inteval
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
AutoJudge (
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   WaitIndex;
  EFI_INPUT_KEY           Key;
  BOOLEAN                 PressYes;
  BOOLEAN                 IsWait;

  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //
  WaitList[0] = TimerEvent;
  WaitList[1] = gtST->ConIn->WaitForKey;

  PressYes = Default;
  IsWait   = TRUE;

  //
  // Wait for either
  //
  SctPrint (Message);

  while (IsWait) {
    if (Default) {
      SctPrint (L"\rYes/No?(Auto judge as Yes in %d seconds)", Seconds);
    } else {
      SctPrint (L"\rYes/No?(Auto judge as No in %d seconds)", Seconds);
    }

    Status = gtBS->WaitForEvent (2, WaitList, &WaitIndex);

    switch (WaitIndex) {
    case 0:
      Seconds--;
      if (Seconds <= 0) {
        //
        // To stop loop
        //
        IsWait = FALSE;
      }
      break;

    case 1:
      //
      // Read the key
      //
      Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
      SctAPrint ((char*)(&Key.UnicodeChar));
      switch (Key.UnicodeChar) {
        case 'Y':
        case 'y':
          IsWait = FALSE;
          PressYes = TRUE;
          break;
        case 'N':
        case 'n':
          IsWait = FALSE;
          PressYes = FALSE;
          break;
        default :
          SctPrint (L"\n");
          break;
      }
      break;

    default:
      break;
    }
  }

  SctPrint (L"\r\n");

  //
  // Cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return PressYes;
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

  Status = gtBS->AllocatePool (PoolType, RealAllocationSize, &RawAddress);
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
