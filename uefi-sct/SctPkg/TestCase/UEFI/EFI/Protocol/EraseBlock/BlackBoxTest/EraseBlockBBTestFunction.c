/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    EraseBlockBBTestFunction.c

Abstract:

    for EFI Driver Erase Block Protocol's Function Test

--*/

#include "EraseBlockBBTestMain.h"

extern UINT8 EnterEvent;

EFI_STATUS
EFIAPI
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
  BOOLEAN                               IsZero  = TRUE;
  BOOLEAN                               IsZero1 = TRUE;
  BOOLEAN                               IsZero2 = TRUE;
  BOOLEAN                               IsZero3 = TRUE;

  UINT64                                Index;
  UINTN                                 Index1;
  UINTN                                 Remainder;
  UINT64                                EraseCounter;

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
      // Write 1
      //
      for (Index1 = 0; Index1 < BufferSize; Index1++) {
        Buffer2[Index1] = 1;
      }

      Status = BlockIo->WriteBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer2);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"WriteBlocks - WriteBlocks for testing fail",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        FreeAlignedPool(Buffer1);
        FreeAlignedPool(Buffer2);
        goto BlockIo2;
      }

      // Erase Blocks with non-EraseLengthGranularity blocks
      if (BufferSize > 2 * BlockSize) {
        Token.Event = NULL;
        Token.TransactionStatus = EFI_NOT_READY;

        EraseStatus = EraseBlock->EraseBlocks (EraseBlock, MediaId, Lba+1, &Token, BufferSize - 2 * BlockSize);

        // Read the data with 0, the first/last block should not be erased
        ReadStatus = BlockIo->ReadBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer2);
        if (ReadStatus == EFI_SUCCESS) {
          for (Index1 = 0, EraseCounter = 0; Index1 < BlockSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero1 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=BlockSize) {
            IsZero1 = FALSE;
          }

          for (Index1 = BlockSize, EraseCounter = 0; Index1 < BufferSize - BlockSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero2 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=(BufferSize - (BlockSize*2))) {
            IsZero2 = FALSE;
          }

          for (Index1 = BufferSize - BlockSize, EraseCounter = 0; Index1 < BufferSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero3 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=BlockSize) {
            IsZero3 = FALSE;
          }

          if ((EraseStatus == EFI_SUCCESS) && (IsZero1 == FALSE) && (IsZero2 == TRUE) && ((IsZero3 == FALSE)))
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          else
            AssertionType = EFI_TEST_ASSERTION_FAILED;


          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gEraseBlockBBTestFunctionAssertionGuid003,
                         L"EraseBlocks - EraseBlocks for testing, the first/last block should not be erased",
                         L"%a:%d:EraseBlocks Status - %r, IsZero1 - %d, IsZero2 - %d, IsZero3 - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         EraseStatus,
                         IsZero1, IsZero2, IsZero3
                         );

        }
      }
      //
      // Erase Blocks with the EraseLengthGranularity blocks
      //
      Token.Event = NULL;
      Token.TransactionStatus = EFI_NOT_READY;
      EraseStatus = EraseBlock->EraseBlocks (EraseBlock, MediaId, Lba, &Token, BufferSize);

      //
      // Read the data with 0
      //
      ReadStatus = BlockIo->ReadBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer2);
      if (ReadStatus == EFI_SUCCESS) {

        for (Index1 = 0; Index1 < BufferSize; Index1++) {
          if (Buffer2[Index1] != 0) {
            IsZero = FALSE;
            break;
          }
        }

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


      }

      //
      // Restore the data with WriteBlocks and FlushBlocks
      //
      WriteStatus = BlockIo->WriteBlocks (BlockIo, MediaId, Lba, BufferSize, (VOID*)Buffer1);
      FlushStatus = EFI_SUCCESS;
      if (WriteCaching == TRUE)
        FlushStatus = BlockIo->FlushBlocks(BlockIo);

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

  IsZero  = TRUE;
  IsZero1 = TRUE;
  IsZero2 = TRUE;
  IsZero3 = TRUE;

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
      // Write 1
      //

      for (Index1 = 0; Index1 < BufferSize; Index1++) {
        Buffer2[Index1] = 1;
      }

      Status = BlockIo2->WriteBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer2);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"WriteBlocks - WriteBlocks for testing fail",
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
      // Erase Blocks with non EraseLengthGranularity blocks
      //
      if (BufferSize > 2 * BlockSize) {
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

        EraseStatus = EraseBlock->EraseBlocks (EraseBlock, MediaId, Lba+1, &Token, BufferSize - 2 * BlockSize);

        while(Token.TransactionStatus == EFI_NOT_READY);

        // Read the data with 0, the first/last block should not be erased
        ReadStatus = BlockIo2->ReadBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer2);
        if (ReadStatus == EFI_SUCCESS) {
          for (Index1 = 0, EraseCounter = 0; Index1 < BlockSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero1 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=BlockSize) {
            IsZero1 = FALSE;
          }

          for (Index1 = BlockSize, EraseCounter = 0; Index1 < BufferSize - BlockSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero2 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=(BufferSize - (BlockSize*2))) {
            IsZero2 = FALSE;
          }

          for (Index1 = BufferSize - BlockSize, EraseCounter = 0; Index1 < BufferSize; Index1++) {
            if (Buffer2[Index1] != 0x00 && Buffer2[Index1] != 0xFF) {
              IsZero3 = FALSE;
              break;
            } else if (Buffer2[Index1] == 0x00) {
              EraseCounter++;
            }
          }
          if (EraseCounter!=0 && EraseCounter!=BlockSize) {
            IsZero3 = FALSE;
          }

          if ((EraseStatus == EFI_SUCCESS) && (IsZero1 == FALSE) && (IsZero2 == TRUE) && ((IsZero3 == FALSE)))
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          else
            AssertionType = EFI_TEST_ASSERTION_FAILED;


          StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gEraseBlockBBTestFunctionAssertionGuid004,
                       L"EraseBlocks - EraseBlocks for testing, the first/last block should not be erased",
                       L"%a:%d:EraseBlocks Status - %r, IsZero1 - %d, IsZero2 - %d, IsZero3 - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       EraseStatus,
                       IsZero1, IsZero2, IsZero3
                       );   

        }
      }
      //
      // Erase Blocks with the EraseLengthGranularity blocks
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
      if (ReadStatus == EFI_SUCCESS) {
        for (Index1 = 0; Index1 < BufferSize; Index1++) {
          if (Buffer2[Index1] != 0) {
            IsZero = FALSE;
            break;
          }
        }

        if ((EraseStatus == EFI_SUCCESS) && (IsZero == TRUE) && (EnterEvent == 1))
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        else
          AssertionType = EFI_TEST_ASSERTION_FAILED;

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gEraseBlockBBTestFunctionAssertionGuid004,
                       L"EraseBlocks - EraseBlocks for testing",
                       L"%a:%d:EraseBlocks Status - %r, IsZero - %d, EnterEvent - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IsZero,
                       EnterEvent
                       );

      }

      //
      // Restore the data with WriteBlocks and FlushBlocks
      //
      WriteStatus = BlockIo2->WriteBlocksEx (BlockIo2, MediaId, Lba, &BlockIo2Token, BufferSize, (VOID*)Buffer1);
      FlushStatus = EFI_SUCCESS;
      if (WriteCaching == TRUE)
        FlushStatus = BlockIo2->FlushBlocksEx (BlockIo2, &BlockIo2Token);

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

