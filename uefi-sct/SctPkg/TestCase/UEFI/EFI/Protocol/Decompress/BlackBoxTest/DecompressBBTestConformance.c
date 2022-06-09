/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DecompressBBTestConformance.c

Abstract:

  conformance test case source file for Decompress protocol

--*/

#include "SctLib.h"
#include "DecompressBBTestMain.h"
#include "DecompressBBTestSupport.h"

#define SECTION_NAME_DECOMPRESS_CONFORM_TEST L"Decompress_Conf"
#define SECTION_NAME_DECOMPRESS_BASIC_TEST   L"Decompress_Func"



/**
 *  test if GetInfo make enough parameter checking.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.1
//
EFI_STATUS
EFIAPI
GetInfo_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  EFI_DECOMPRESS_PROTOCOL                 *Decompress;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL       *ProfileLib;
  UINT32                                  DestinationSize;
  UINT32                                  ScratchSize;
  UINT32                                  Index;
  VOID                                    *Buffer;
  EFI_TEST_ASSERTION                      AssertionType;


  //
  //get tested interface.
  //
  Decompress = (EFI_DECOMPRESS_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //check point call GetInfo with SourceSize < 8.
  //
  Buffer = NULL;
  for (Index = 0; Index < 8; Index++) {
    Status = Decompress->GetInfo (
                           Decompress,
                           Buffer,
                           Index,
                           &DestinationSize,
                           &ScratchSize
                           );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDecompressBBTestConformanceAssertionGuid001,
                   L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - with SourceSize < 8 return Status should be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Source Size - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  test if Decompress make enough parameter checking.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.2
//
EFI_STATUS
EFIAPI
Decompress_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  EFI_DECOMPRESS_PROTOCOL                 *Decompress;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  UINT32                                  CompressedFileSize;
  UINT32                                  DestinationSize;
  UINT32                                  ScratchSize;
  UINTN                                   Index;
  UINT32                                  SubIndex;
  UINT8                                   *CompressedFileBuffer;
  UINT8                                   *DecompressBuffer;
  VOID                                    *ScratchBuffer;
  UINTN                                   BufferSize;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  EFI_FILE_HANDLE                         CompressedFHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *CompressedFileName;

  //
  //get tested interface.
  //
  Decompress = (EFI_DECOMPRESS_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompress() -not found the profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  //
  //we initialize this variable because it was taken as UINT32 type, in fact it
  //is UINT64 value in ipf platform.
  //

  //
  // Test incorrect compressed file.
  //
  MaxOrder = 0;

  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_DECOMPRESS_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompress() -no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //process the incorrect compress file
  //
  for (Index = 0; Index < MaxOrder; Index++) {

    CompressedFileBuffer   = NULL;
    DecompressBuffer       = NULL;
    ScratchBuffer          = NULL;

    //
    //get Incorrect compress File Name and file size.
    //
    Status = GetInvalidCompressedFileName (
               FileHandle,
               SECTION_NAME_DECOMPRESS_CONFORM_TEST,
               Index,
               &CompressedFileName
               );

    if (EFI_ERROR(Status)) {
      SctPrint (L"Get InvalidCompressedFileName Error\r\n");
      continue;
    }

    //
    //Open the Compressed file and get file size.
    //
    Status = OpenFileAndGetSize (
               CompressedFileName,
               &CompressedFHandle,
               &CompressedFileSize
               );

    if (EFI_ERROR(Status)) {
      SctPrint (L"Can not open the File :%s\r\n", CompressedFileName);
      gtBS->FreePool (CompressedFileName);
      continue;
    }
    gtBS->FreePool (CompressedFileName);

    //
    //then read the Compresed File into memory.
    //
    CompressedFileBuffer = SctAllocatePool (CompressedFileSize);

    if (CompressedFileBuffer == NULL) {
      CompressedFHandle->Close (CompressedFHandle);
      SctPrint (L"Can not allocate %xh buffer.\r\n", CompressedFileSize);
      continue;
    }

    BufferSize = CompressedFileSize;

    Status = CompressedFHandle->Read (
                                  CompressedFHandle,
                                  &BufferSize,
                                  CompressedFileBuffer
                                  );

    CompressedFHandle->Close (CompressedFHandle);

    if (EFI_ERROR(Status)) {
      gtBS->FreePool (CompressedFileBuffer);
      SctPrint (L"File Read Error Status %r\r\n", Status);
      continue;
    }

    DestinationSize = 0;
    ScratchSize     = 0;
	
    //
    //now verify the check points.
    //
    Status = Decompress->GetInfo (
                           Decompress,
                           CompressedFileBuffer,
                           CompressedFileSize,
                           &DestinationSize,
                           &ScratchSize
                           );

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - return Status Should be EFI_SUCCESS",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //allocate decompress buffer and scratch buffer
    //
    DecompressBuffer = SctAllocatePool ((DestinationSize == 0) ? 128 : DestinationSize);

    if (DecompressBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      SctPrint (L"Can not allocate %xh buffer.\r\n", DestinationSize);
      continue;
    }

    ScratchBuffer = SctAllocatePool (ScratchSize);

    if (ScratchBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (DecompressBuffer);
      SctPrint (L"Can not allocate %xh buffer.\r\n", ScratchSize);
      continue;
    }

    //
    //call Decompress with the invalid compress format buffer.
    //
    Status = Decompress->Decompress (
                           Decompress,
                           CompressedFileBuffer,
                           CompressedFileSize,
                           DecompressBuffer,
                           DestinationSize,
                           ScratchBuffer,
                           ScratchSize
                           );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDecompressBBTestConformanceAssertionGuid003,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompess() - with invalid compressed file return Status Should be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    //
    //free the resources.
    //
    gtBS->FreePool (CompressedFileBuffer);
    gtBS->FreePool (DecompressBuffer);
    gtBS->FreePool (ScratchBuffer);
  }

  //
  //Test normal compressed file with incorrect SourceSize
  //
  MaxOrder = 0;

  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_DECOMPRESS_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompress() - no item found for this test case.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    CompressedFileBuffer   = NULL;
    DecompressBuffer       = NULL;
    ScratchBuffer          = NULL;

    //
    //get compressed FileName and file size.
    //
    Status = GetCompressedFileName (
               FileHandle,
               SECTION_NAME_DECOMPRESS_BASIC_TEST,
               Index,
               &CompressedFileName
               );

    if (EFI_ERROR(Status)) {
      SctPrint (L"Get CompressedFileName Error\r\n");
      continue;
    }

    //
    //Open the Compressed file and get file size.
    //
    Status = OpenFileAndGetSize (
               CompressedFileName,
               &CompressedFHandle,
               &CompressedFileSize
               );

    if (EFI_ERROR(Status)) {
      SctPrint (L"Can not open the File :%s\r\n", CompressedFileName);
      gtBS->FreePool (CompressedFileName);
      continue;
    }
    gtBS->FreePool (CompressedFileName);

    //
    //then read the Compressed File into memory.
    //
    CompressedFileBuffer = SctAllocatePool (CompressedFileSize);

    if (CompressedFileBuffer == NULL) {
      CompressedFHandle->Close (CompressedFHandle);
      SctPrint (L"Can not allocate %xh buffer.\r\n", CompressedFileSize);
      continue;
    }

    BufferSize = CompressedFileSize;

    Status = CompressedFHandle->Read (
                                  CompressedFHandle,
                                  &BufferSize,
                                  CompressedFileBuffer
                                  );

    CompressedFHandle->Close (CompressedFHandle);

    if (EFI_ERROR(Status)) {
      SctPrint (L"File Read Error Status %r\r\n", Status);
      gtBS->FreePool (CompressedFileBuffer);
      continue;
    }

    //
    // read the destinationSize and scratchSize information
    //
    Status = Decompress->GetInfo (
                           Decompress,
                           CompressedFileBuffer,
                           CompressedFileSize,
                           &DestinationSize,
                           &ScratchSize
                           );

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - return Status Should be EFI_SUCCESS",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //allocate Decompess buffer and Decompress the compessed data.
    //
    DecompressBuffer = SctAllocatePool ((DestinationSize == 0) ? 128 : DestinationSize);
    if (DecompressBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      SctPrint (L"Can not allocate %xh buffer.\r\n", DestinationSize);
      continue;
    }

    ScratchBuffer = SctAllocatePool (ScratchSize);
    if (ScratchBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (DecompressBuffer);
      SctPrint (L"Can not allocate %xh buffer.\r\n", ScratchSize);
      continue;
    }

    if (DestinationSize != 0) {
      Status = Decompress->Decompress (
                             Decompress,
                             CompressedFileBuffer,
                             CompressedFileSize - 1,
                             DecompressBuffer,
                             DestinationSize,
                             ScratchBuffer,
                             ScratchSize
                             );

      if (Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDecompressBBTestConformanceAssertionGuid004,
                     L"EFI_DECOMPRESS_PROTOCOL.Decompess() - with incorrect SourceSize ( SourceSize - 1 ), return Status should be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    for (SubIndex = 0; SubIndex < 8; SubIndex++) {
        Status = Decompress->Decompress (
                               Decompress,
                               CompressedFileBuffer,
                               SubIndex,
                               DecompressBuffer,
                               DestinationSize,
                               ScratchBuffer,
                               ScratchSize
                               );

        if (Status == EFI_INVALID_PARAMETER) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        //
        //record assertion
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gDecompressBBTestConformanceAssertionGuid005,
                       L"EFI_DECOMPRESS_PROTOCOL.Decompess() - with SourceSize < 8, return Status should be EFI_INVALID_PARAMETER",
                       L"%a:%d:Status - %r, Source Size - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SubIndex
                       );
    }

    //
    //free the resources
    //
    gtBS->FreePool (CompressedFileBuffer);
    gtBS->FreePool (DecompressBuffer);
    gtBS->FreePool (ScratchBuffer);
  }

  CloseTestIniFile (ProfileLib, FileHandle);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
