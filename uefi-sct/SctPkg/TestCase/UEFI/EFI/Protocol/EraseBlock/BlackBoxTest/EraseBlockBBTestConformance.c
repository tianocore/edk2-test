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

    EraseBlockBBTestConformance.c

Abstract:

    for EFI Driver Erase Block Protocol's Conformance Test

--*/

#include "EraseBlockBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestEraseBlocksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock;
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo;
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2;  
  EFI_TEST_ASSERTION                    AssertionType;
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
  UINT32                                EraseLengthGranularity;
  UINTN                                 EraseSize;

  EFI_ERASE_BLOCK_TOKEN                 Token;

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

  Status = LocateBlockIoFromEraseBlock(EraseBlock, &BlockIo, StandardLib);
  if (Status == EFI_SUCCESS) {
    Media = BlockIo->Media;
    AssertionType = EFI_TEST_ASSERTION_PASSED;    
  } else {
    Status = LocateBlockIo2FromEraseBlock(EraseBlock, &BlockIo2, StandardLib);
    if (Status == EFI_SUCCESS) {
      Media = BlockIo2->Media;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEraseBlockBBTestConformanceAssertionGuid001,
                 L"EFI_ERASE_BLOCK_PROTOCOL - It should be installed on the same handle as the EFI_BLOCK_IO_PROTOCOL or EFI_BLOCK_IO2_PROTOCOL.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED)
    return EFI_SUCCESS;


  MediaId           = Media->MediaId;
  RemovableMedia    = Media->RemovableMedia;
  MediaPresent      = Media->MediaPresent;
  LogicalPartition  = Media->LogicalPartition;
  ReadOnly          = Media->ReadOnly;
  WriteCaching      = Media->WriteCaching;
  BlockSize         = Media->BlockSize;
  IoAlign           = Media->IoAlign;
  LastBlock         = Media->LastBlock;

  EraseLengthGranularity = EraseBlock->EraseLengthGranularity;
  EraseSize              = (UINTN)SctMultU64x32 (EraseLengthGranularity, BlockSize);

  if (MediaPresent == FALSE) {
    Status = EraseBlock->EraseBlocks(EraseBlock, MediaId, 0, &Token, EraseSize);
    if (Status == EFI_NO_MEDIA)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid002,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_NO_MEDIA should be returned if there is no media in the device.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = EraseBlock->EraseBlocks(EraseBlock, MediaId, LastBlock + 1, &Token, EraseSize);
    if (Status == EFI_NO_MEDIA)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid003,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_NO_MEDIA should be returned even if LBA is invalid.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = EraseBlock->EraseBlocks(EraseBlock, MediaId, LastBlock - 10, &Token, EraseSize + 1);
    if (Status == EFI_NO_MEDIA)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid004,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_NO_MEDIA should be returned even if Size is invalid.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
 
  } else {
    if (ReadOnly == TRUE) {
      Status = EraseBlock->EraseBlocks(EraseBlock, MediaId, 0, &Token, EraseSize);
      if (Status == EFI_WRITE_PROTECTED)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid005,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_WRITE_PROTECTED should be returned if the device cannot be erased due to write protection.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    } else {
      Status = EraseBlock->EraseBlocks(EraseBlock, MediaId + 1, 0, &Token, EraseSize);
      if (Status == EFI_MEDIA_CHANGED)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid006,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_MEDIA_CHANGED should be returned if the MediaId is not for the current media.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      Status = EraseBlock->EraseBlocks(EraseBlock, MediaId + 1, LastBlock + 1, &Token, EraseSize);
      if (Status == EFI_MEDIA_CHANGED)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid007,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_MEDIA_CHANGED should be returned even if LBA is invalid.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      Status = EraseBlock->EraseBlocks(EraseBlock, MediaId + 1, LastBlock - 10, &Token, EraseSize + 1);
      if (Status == EFI_MEDIA_CHANGED)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid008,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_MEDIA_CHANGED should be returned even if Size is invalid.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      Status = EraseBlock->EraseBlocks(EraseBlock, MediaId, LastBlock + 1, &Token, EraseSize);
      if (Status == EFI_INVALID_PARAMETER)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEraseBlockBBTestConformanceAssertionGuid009,
                     L"EFI_ERASE_BLOCK_PROTOCOL - EFI_INVALID_PARAMETER should be returned if the erase request contains LBAs that are not valid.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );  


    }
  }

  return EFI_SUCCESS;
}


