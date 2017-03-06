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

    EraseBlockBBTestFunction.c

Abstract:

    for EFI Driver Erase Block Protocol's Function Test

--*/

#include "EraseBlockBBTestMain.h"

extern UINT8 EnterEvent;

EFI_STATUS
BBTestEraseBlocksFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            EraseStatus;
  EFI_STATUS                            ReadStatus;
  EFI_STATUS                            WriteStatus;
  EFI_STATUS                            FlushStatus;  
  EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock;
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo;
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2;  
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                EraseLengthGranularity;

  EFI_BLOCK_IO_MEDIA                    *Media;
  UINT32                                MediaId;
  BOOLEAN                               RemovableMedia;
  BOOLEAN                               MediaPresent;
  BOOLEAN                               LogicalPartition;
  BOOLEAN                               ReadOnly;
  BOOLEAN                               WriteCaching;
  UINT32                                BlockSize;
  UINT32                                IoAlign;
  EFI_LBA                               LastBlock;
  EFI_LBA                               Lba;

  UINTN                                 BufferSize;
  UINT8                                 *Buffer1 = NULL;
  UINT8                                 *Buffer2 = NULL;
  BOOLEAN                               IsZero = TRUE;

  UINT64                                Index;
  UINTN                                 Index1;
  UINTN                                 Remainder;

  EFI_ERASE_BLOCK_TOKEN                 Token;
  EFI_BLOCK_IO2_TOKEN                   BlockIo2Token;

  EraseBlock = (EFI_ERASE_BLOCK_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  EraseLengthGranularity = EraseBlock->EraseLengthGranularity;

  Status = LocateBlockIoFromEraseBlock(EraseBlock, &BlockIo, StandardLib);
  if (Status == EFI_SUCCESS) {
    Media = BlockIo->Media;

    MediaId           = Media->MediaId;
    RemovableMedia    = Media->RemovableMedia;
    MediaPresent      = Media->MediaPresent;
    LogicalPartition  = Media->LogicalPartition;
    ReadOnly          = Media->ReadOnly;
    WriteCaching      = Media->WriteCaching;
    BlockSize         = Media->BlockSize;
    IoAlign           = Media->IoAlign;
    LastBlock         = Media->LastBlock;

    BufferSize        = (UINTN)SctMultU64x32 (EraseLengthGranularity, BlockSize);
    Index             = SctDivU64x32 (LastBlock, EraseLengthGranularity, &Remainder);

    if (Index > MAX_NUMBER_OF_READ_BLOCK_BUFFER)
      Lba = SctMultU64x32 (EraseLengthGranularity, (MAX_NUMBER_OF_READ_BLOCK_BUFFER - 2));
    else
      Lba = 0;

    //
    // allocate aligned buffer
    //
    Buffer1 = AllocateAlignedPool(
                EfiBootServicesData, 
                BufferSize, 
                IoAlign
                );
    if (Buffer1 == NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocateAlignedPool - Allocate aligned buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_OUT_OF_RESOURCES
                     );
      return EFI_OUT_OF_RESOURCES;
    }

    Buffer2 = AllocateAlignedPool(
                EfiBootServicesData, 
                BufferSize, 
                IoAlign
                );
    if (Buffer2 == NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocateAlignedPool - Allocate aligned buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_OUT_OF_RESOURCES
                     );
      FreeAlignedPool(Buffer1);
      return EFI_OUT_OF_RESOURCES;
    }

    if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) { 
      //
      // Read the data at first with ReadBlocks
      //
      Status = BlockIo->ReadBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer1);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"ReadBlocks - ReadBlocks for testing fail",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        FreeAlignedPool(Buffer1);
        FreeAlignedPool(Buffer2);
        goto BlockIo2;
      }

      //
      // Erase Blocks
      //
      Token.Event = NULL;
      Token.TransactionStatus = EFI_NOT_READY;
      EraseStatus = EraseBlock->EraseBlocks (EraseBlock, MediaId, Lba, &Token, BufferSize);

      //
      // Read the data with 0
      //
      ReadStatus = BlockIo->ReadBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer2);      
      for (Index1 = 0; Index1 < BufferSize; Index1++) {
        if (Buffer2[Index1] != 0) {
          IsZero = FALSE;
          break;
        }
      }

      //
      // Restore the data with WriteBlocks and FlushBlocks
      //
      WriteStatus = BlockIo->WriteBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer1);  
      FlushStatus = EFI_SUCCESS;
      if (WriteCaching == TRUE)
        FlushStatus = BlockIo->FlushBlocks(BlockIo);

      if ((EraseStatus == EFI_SUCCESS) && (IsZero == TRUE))
       	AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gEraseBlockBBTestFunctionAssertionGuid001,
                       L"EraseBlocks - EraseBlocks for testing",
                       L"%a:%d:EraseBlocks Status - %r, IsZero - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IsZero
                       );      

      if ((WriteStatus != EFI_SUCCESS) || (FlushStatus != EFI_SUCCESS))
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"WriteBlocks/FlushBlocks - Restore for testing fail",
                       L"%a:%d: WriteStatus - %r, FlushStatus - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       WriteStatus,
                       FlushStatus
                       );

      FreeAlignedPool(Buffer1);
      FreeAlignedPool(Buffer2);
    }   
  } 

BlockIo2:

  Status = LocateBlockIo2FromEraseBlock(EraseBlock, &BlockIo2, StandardLib);
  if (Status == EFI_SUCCESS) {
    Media = BlockIo2->Media;

    MediaId           = Media->MediaId;
    RemovableMedia    = Media->RemovableMedia;
    MediaPresent      = Media->MediaPresent;
    LogicalPartition  = Media->LogicalPartition;
    ReadOnly          = Media->ReadOnly;
    WriteCaching      = Media->WriteCaching;
    BlockSize         = Media->BlockSize;
    IoAlign           = Media->IoAlign;
    LastBlock         = Media->LastBlock;

    BufferSize        = (UINTN)SctMultU64x32 (EraseLengthGranularity, BlockSize);
    Index             = SctDivU64x32 (LastBlock, EraseLengthGranularity, &Remainder);

    if (Index > MAX_NUMBER_OF_READ_BLOCK_BUFFER)
      Lba = SctMultU64x32 (EraseLengthGranularity, (MAX_NUMBER_OF_READ_BLOCK_BUFFER - 2));
    else
      Lba = 0;

    //
    // allocate aligned buffer
    //
    Buffer1 = AllocateAlignedPool(
                EfiBootServicesData, 
                BufferSize, 
                IoAlign
                );
    if (Buffer1 == NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocateAlignedPool - Allocate aligned buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_OUT_OF_RESOURCES
                     );
      return EFI_OUT_OF_RESOURCES;
    }

    Buffer2 = AllocateAlignedPool(
                EfiBootServicesData, 
                BufferSize, 
                IoAlign
                );
    if (Buffer2 == NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocateAlignedPool - Allocate aligned buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_OUT_OF_RESOURCES
                     );
      FreeAlignedPool(Buffer1);
      return EFI_OUT_OF_RESOURCES;
    }

    if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) { 
      BlockIo2Token.Event = NULL;
      BlockIo2Token.TransactionStatus = EFI_NOT_READY;

      //
      // Read the data at first with ReadBlocks
      //
      Status = BlockIo2->ReadBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer1);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"ReadBlocks - ReadBlocks for testing fail",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        FreeAlignedPool(Buffer1);
        FreeAlignedPool(Buffer2);
        goto End;
      }

      //
      // Erase Blocks
      //
      Token.Event             = NULL;
      Token.TransactionStatus = EFI_NOT_READY;

      EnterEvent = 0;

      Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunction,
                   NULL,
                   &Token.Event
                   );

      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"CreateEvent - CreateEvent for testing fail",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        FreeAlignedPool(Buffer1);
        FreeAlignedPool(Buffer2);
        goto End;
      }

      EraseStatus = EraseBlock->EraseBlocks (EraseBlock, MediaId, Lba, &Token, BufferSize);

      while(Token.TransactionStatus == EFI_NOT_READY);

      //
      // Read the data with 0
      //
      ReadStatus = BlockIo2->ReadBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer2);      

      for (Index1 = 0; Index1 < BufferSize; Index1++) {
        if (Buffer2[Index1] != 0) {
          IsZero = FALSE;
          break;
        }
      }

      //
      // Restore the data with WriteBlocks and FlushBlocks
      //
      WriteStatus = BlockIo2->WriteBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer1);  
      FlushStatus = EFI_SUCCESS;
      if (WriteCaching == TRUE)
        FlushStatus = BlockIo2->FlushBlocksEx (BlockIo2, &BlockIo2Token);

      if ((EraseStatus == EFI_SUCCESS) && (IsZero == TRUE) && (EnterEvent == 1))
       	AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gEraseBlockBBTestFunctionAssertionGuid002,
                       L"EraseBlocks - EraseBlocks for testing",
                       L"%a:%d:EraseBlocks Status - %r, IsZero - %d, EnterEvent - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IsZero,
                       EnterEvent
                       );      

      if ((WriteStatus != EFI_SUCCESS) || (FlushStatus != EFI_SUCCESS))
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"WriteBlocks/FlushBlocks - Restore for testing fail",
                       L"%a:%d: WriteStatus - %r, FlushStatus - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       WriteStatus,
                       FlushStatus
                       );

      FreeAlignedPool(Buffer1);
      FreeAlignedPool(Buffer2);
    }

End:
    if (Token.Event != NULL)
      gtBS->CloseEvent(Token.Event);

  }

   return EFI_SUCCESS;
}

