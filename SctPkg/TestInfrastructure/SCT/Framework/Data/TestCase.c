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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestCase.c

Abstract:

  This file provides the services to manage the test cases.

--*/

#include "Sct.h"

//
// Internal definitions
//

#define EFI_SCT_SECTION_TEST_CASE           L"Test Case"

//
// Internal function declaration
//

EFI_STATUS
InsertSingleTestCase (
  IN OUT SCT_LIST_ENTRY           *TestCaseList,
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
LoadSingleTestCase (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

EFI_STATUS
SaveSingleTestCase (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
LoadSingleTestSequence (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

EFI_STATUS
SaveSingleTestSequence (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
CreateSingleTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

EFI_STATUS
FreeSingleTestCase (
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
TestCaseGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  );

EFI_STATUS
TestCaseGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
TestCaseSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );

//
// External functions implementation
//

EFI_STATUS
LoadTestCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *TestCaseList
  )
/*++

Routine Description:

  Load the test case list from a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  UINT32                Index;
  UINT32                NumberOfTestCases;
  EFI_INI_FILE_HANDLE   IniFile;
  EFI_SCT_TEST_CASE     *TestCase;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestCaseList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load test cases from <%s>", FileName));

  //
  // Open the file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open test case file - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // If the test case file doesn't exist, use the empty setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Test case file doesn't exist"));
    return EFI_SUCCESS;
  }

  //
  // Get the number of test cases
  //
  Status = TestCaseGetOrderNum (
             IniFile,
             &NumberOfTestCases
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get order number - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test cases
  //
  for (Index = 0; Index < NumberOfTestCases; Index ++) {
    //
    // Load a single test case
    //
    Status = LoadSingleTestCase (
               IniFile,
               Index,
               &TestCase
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load a test case (#%d) - %r", Index, Status));
      continue;
    }

    //
    // Add this test case into the test case list
    //
    SctInsertTailList (TestCaseList, &TestCase->Link);
  }

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SaveTestCases (
  VOID
  )
/*++

Routine Description:

  Save the test case list into a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  UINT32                Index;
  EFI_INI_FILE_HANDLE   IniFile;
  SCT_LIST_ENTRY        *Link;
  EFI_SCT_TEST_CASE     *TestCase;
  SCT_LIST_ENTRY        *TestCaseList;

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Save test cases into <%s>", gFT->TestCaseFileName));

  //
  // Open/Create the TestCase file if not done yet
  //
  if (gFT->TestCaseIniFile == NULL) {
    Status = gFT->TplProtocol->EfiIniOpen (
                                 gFT->TplProtocol,
                                 gFT->DevicePath,
                                 gFT->TestCaseFileName,
                                 &gFT->TestCaseIniFile
                                 );
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      return Status;
    }

    // Not exist, create the file
    if (Status == EFI_NOT_FOUND) {
      Status = gFT->TplProtocol->EfiIniCreate (
                                   gFT->TplProtocol,
                                   gFT->DevicePath,
                                   gFT->TestCaseFileName,
                                   &gFT->TestCaseIniFile
                                   );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  // Initial variables
  TestCaseList = &gFT->TestCaseList;
  IniFile      = gFT->TestCaseIniFile;

  //
  // Remove the original test cases
  //
  Status = IniFile->RmSection (
                      IniFile,
                      EFI_SCT_SECTION_TEST_CASE
                      );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove section - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test cases
  //
  Index = 0;

  for (Link = TestCaseList->ForwardLink; Link != TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    //
    // Save a single test case
    //
    Status = SaveSingleTestCase (
               IniFile,
               Index,
               TestCase
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Save a test case (#%d) - %r", Index, Status));
      continue;
    }

    Index ++;
  }

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniFlush (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN OUT SCT_LIST_ENTRY           *TestCaseList
  )
/*++

Routine Description:

  Load test sequence from a file. The difference between test sequence and test
  case is that the test sequence does not include the test result information.

  One thing should be noticed is this function also merges the test sequence
  list with the input test case list.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  UINT32                Index;
  UINT32                NumberOfTestCases;
  EFI_INI_FILE_HANDLE   IniFile;
  SCT_LIST_ENTRY        SequenceList;
  EFI_SCT_TEST_CASE     *TestCase;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestCaseList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load test sequence from <%s>", FileName));

  SctInitializeListHead (&SequenceList);

  //
  // Open the file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open test sequence file - %r", Status));
    return Status;
  }

  //
  // Get the number of test cases
  //
  Status = TestCaseGetOrderNum (
             IniFile,
             &NumberOfTestCases
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get order number - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test cases
  //
  for (Index = 0; Index < NumberOfTestCases; Index ++) {
    //
    // Load a single test sequence
    //
    Status = LoadSingleTestSequence (
               IniFile,
               Index,
               &TestCase
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load a test sequence (#%d) - %r", Index, Status));
      continue;
    }

    //
    // Add this test case into the test sequence list
    //
    SctInsertTailList (&SequenceList, &TestCase->Link);
  }

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Merge the test sequence list into the input test case list
  //
  Status = MergeTestCases (
             TestCaseList,
             &SequenceList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge test cases - %r", Status));
    FreeTestCases (&SequenceList);
    return Status;
  }

  FreeTestCases (&SequenceList);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SaveTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN SCT_LIST_ENTRY               *TestCaseList
  )
/*++

Routine Description:

  Save the test sequence into a file. The difference between test sequence and
  test case is that the test sequence does not include the test result
  information.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  UINT32                Index;
  EFI_INI_FILE_HANDLE   IniFile;
  SCT_LIST_ENTRY        *Link;
  EFI_SCT_TEST_CASE     *TestCase;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestCaseList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Save test sequence into <%s>", FileName));

  //
  // Open the file
  //
  Status = gFT->TplProtocol->EfiIniOpen (
                               gFT->TplProtocol,
                               DevicePath,
                               FileName,
                               &IniFile
                               );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open test sequence file - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // Not exist, create the file
    //
    Status = gFT->TplProtocol->EfiIniCreate (
                                 gFT->TplProtocol,
                                 DevicePath,
                                 FileName,
                                 &IniFile
                                 );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test sequence file - %r", Status));
      return Status;
    }
  }

  //
  // Remove the original test cases
  //
  Status = IniFile->RmSection (
                      IniFile,
                      EFI_SCT_SECTION_TEST_CASE
                      );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove section - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test cases
  //
  Index = 0;

  for (Link = TestCaseList->ForwardLink; Link != TestCaseList; Link = Link->ForwardLink) {
    TestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    //
    // Save a single test sequence
    //
    Status = SaveSingleTestSequence (
               IniFile,
               Index,
               TestCase
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Save a test sequence (#%d) - %r", Index, Status));
      continue;
    }

    Index ++;
  }

  //
  // Close the file
  //
  gFT->TplProtocol->EfiIniClose (
                      gFT->TplProtocol,
                      IniFile
                      );

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeTestCases (
  IN SCT_LIST_ENTRY               *TestCaseList
  )
/*++

Routine Description:

  Free the test case list.

Arguments:

  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (TestCaseList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test cases
  //
  while (!SctIsListEmpty (TestCaseList)) {
    TestCase = CR (TestCaseList->ForwardLink, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    SctRemoveEntryList (&TestCase->Link);
    FreeSingleTestCase (TestCase);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateTestCases (
  OUT SCT_LIST_ENTRY              *TestCaseList
  )
/*++

Routine Description:

  Create the test case list from a test file list (That is all test drivers).

Arguments:

  TestCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  SCT_LIST_ENTRY          *TestFileList;
  SCT_LIST_ENTRY          *Link;
  EFI_SCT_TEST_CASE       *TestCase;
  EFI_SCT_TEST_FILE       *TestFile;
  EFI_BB_TEST_PROTOCOL    *BbTest;
  EFI_BB_TEST_ENTRY       *BbEntry;
  EFI_WB_TEST_PROTOCOL    *WbTest;
  EFI_WB_TEST_ENTRY       *WbEntry;
  EFI_AP_TEST_INTERFACE   *ApTest;
  EFI_AP_TEST_ENTRY       *ApEntry;

  //
  // Check parameters
  //
  if (TestCaseList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Create test cases"));

  //
  // Walk through all test files
  //
  TestFileList = &gFT->TestFileList;

  for (Link = TestFileList->ForwardLink; Link != TestFileList; Link = Link->ForwardLink) {
    TestFile = CR (Link, EFI_SCT_TEST_FILE, Link, EFI_SCT_TEST_FILE_SIGNATURE);

    //
    // Deal with the different kinds of test files
    //
    switch (TestFile->Type) {
    case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
    case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
      //
      // Black-box test file
      //
      BbTest = (EFI_BB_TEST_PROTOCOL *) TestFile->Context;

      for (BbEntry = BbTest->EntryList; BbEntry != NULL; BbEntry = BbEntry->Next) {
        //
        // Create a single test case
        //
        Status = CreateSingleTestCase (&TestCase);
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
          return Status;
        }

        //
        // Initialize the items of test case
        //
        SctCopyMem (&TestCase->Guid, &BbEntry->EntryId, sizeof(EFI_GUID));
        TestCase->Name = SctStrDuplicate (BbEntry->Name);

        //
        // Insert the test case into the test case list
        //
        InsertSingleTestCase (TestCaseList, TestCase);
      }

      break;

    case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
      //
      // White-box test file
      //
      WbTest = (EFI_WB_TEST_PROTOCOL *) TestFile->Context;

      for (WbEntry = WbTest->EntryList; WbEntry != NULL; WbEntry = WbEntry->Next) {
        //
        // Create a single test case
        //
        Status = CreateSingleTestCase (&TestCase);
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
          return Status;
        }

        //
        // Initialize the items of test case
        //
        SctCopyMem (&TestCase->Guid, &WbEntry->EntryId, sizeof(EFI_GUID));
        TestCase->Name = SctStrDuplicate (WbEntry->Name);

        //
        // Insert the test case into the test case list
        //
        InsertSingleTestCase (TestCaseList, TestCase);
      }

      break;

    case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
    case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
      //
      // Application or script test file
      //
      ApTest = (EFI_AP_TEST_INTERFACE *) TestFile->Context;

      for (ApEntry = ApTest->EntryList; ApEntry != NULL; ApEntry = ApEntry->Next) {
        //
        // Create a single test case
        //
        Status = CreateSingleTestCase (&TestCase);
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
          return Status;
        }

        //
        // Initialize the items of test case
        //
        SctCopyMem (&TestCase->Guid, &ApEntry->EntryId, sizeof(EFI_GUID));
        TestCase->Name = SctStrDuplicate (ApEntry->Name);

        //
        // Insert the test case into the test case list
        //
        InsertSingleTestCase (TestCaseList, TestCase);
      }

      break;

    default:
      //
      // Unsupported test file
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
MergeTestCases (
  IN OUT SCT_LIST_ENTRY           *DstTestCaseList,
  IN SCT_LIST_ENTRY               *SrcTestCaseList
  )
/*++

Routine Description:

  Merge two test case lists. Overwrite the order and results of destination
  test case list with of source test case list.

Arguments:

  DstTestCaseList   - The destination test case list.
  SrcTestCaseList   - The source test case list.

Returns:

  EFI_SUCCESS       - Successfully.
  Other value       - Something failed.

--*/
{
  SCT_LIST_ENTRY      *DstLink;
  SCT_LIST_ENTRY      *SrcLink;
  EFI_SCT_TEST_CASE   *DstTestCase;
  EFI_SCT_TEST_CASE   *SrcTestCase;

  //
  // Check parameters
  //
  if ((DstTestCaseList == NULL) || (SrcTestCaseList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test cases in the source test case list
  //
  for (SrcLink = SrcTestCaseList->ForwardLink; SrcLink != SrcTestCaseList; SrcLink = SrcLink->ForwardLink) {
    SrcTestCase = CR (SrcLink, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    //
    // Walk through all test cases in the destination test case list
    //
    for (DstLink = DstTestCaseList->ForwardLink; DstLink != DstTestCaseList; DstLink = DstLink->ForwardLink) {
      DstTestCase = CR (DstLink, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

      if (SctCompareGuid (&DstTestCase->Guid, &SrcTestCase->Guid) == 0) {
        if (SrcTestCase->Order != EFI_SCT_TEST_CASE_INVALID) {
          DstTestCase->Order = SrcTestCase->Order;
        }

        if (SrcTestCase->Iterations != EFI_SCT_TEST_CASE_INVALID) {
          DstTestCase->Iterations = SrcTestCase->Iterations;
        }

        if (SrcTestCase->Passes != EFI_SCT_TEST_CASE_INVALID) {
          DstTestCase->Passes = SrcTestCase->Passes;
        }

        if (SrcTestCase->Failures != EFI_SCT_TEST_CASE_INVALID) {
          DstTestCase->Failures = SrcTestCase->Failures;
        }

        break;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FindTestCaseByGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Search a test case based on the GUID.

Arguments:

  Guid          - Specifies GUID to search by.
  TestCase      - Pointer to the test case structure.

Returns:

  EFI_SUCCESS   - Successfully.
  EFI_NOT_FOUND - Not found.
  Other value   - Something failed.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *TempTestCase;

  //
  // Check parameters
  //
  if ((Guid == NULL) || (TestCase == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test cases
  //
  for (Link = gFT->TestCaseList.ForwardLink; Link != &gFT->TestCaseList; Link = Link->ForwardLink) {
    TempTestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&TempTestCase->Guid, Guid) == 0) {
      //
      // Got it!
      //
      *TestCase = TempTestCase;
      return EFI_SUCCESS;
    }
  }

  //
  // Not found
  //
  return EFI_NOT_FOUND;
}


//
// Internal functions implementation
//

EFI_STATUS
InsertSingleTestCase (
  IN OUT SCT_LIST_ENTRY           *TestCaseList,
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Insert a test case into list.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_CASE   *OldTestCase;

  //
  // Check whether there are duplicate test cases. If yes, record a debug
  // message
  //
  for (Link = TestCaseList->ForwardLink; Link != TestCaseList; Link = Link->ForwardLink) {
    OldTestCase = CR (Link, EFI_SCT_TEST_CASE, Link, EFI_SCT_TEST_CASE_SIGNATURE);

    if (SctCompareGuid (&OldTestCase->Guid, &TestCase->Guid) == 0) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Found duplicate test cases (GUID = %g)", &TestCase->Guid));
      break;
    }
  }

  SctInsertTailList (TestCaseList, &TestCase->Link);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadSingleTestCase (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Load a test case.

--*/
{
  EFI_STATUS          Status;
  CHAR16              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINT32              Revision;
  EFI_SCT_TEST_CASE   *TempTestCase;

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a single test case
  //
  Status = CreateSingleTestCase (&TempTestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
    return Status;
  }

  //
  // Check revision
  //
  Status = TestCaseGetString (IniFile, Order, L"Revision", Buffer);
  if (EFI_ERROR (Status)) {
    //
    // Without revision info, ignore this test case
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without revision"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &Revision);
  if (EFI_ERROR (Status) || (Revision != TempTestCase->Revision)) {
    //
    // With unsupported revision info, ignore this test case
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid revision"));
    FreeSingleTestCase (TempTestCase);
    return EFI_UNSUPPORTED;
  }

  //
  // Load the GUID
  //
  Status = TestCaseGetString (IniFile, Order, L"Guid", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without GUID"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempTestCase->Guid);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid GUID"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the name
  //
  Status = TestCaseGetString (IniFile, Order, L"Name", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without name"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  TempTestCase->Name = SctStrDuplicate (Buffer);

  //
  // Load the order
  //
  Status = TestCaseGetString (IniFile, Order, L"Order", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without order"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Order);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid order"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the iterations
  //
  Status = TestCaseGetString (IniFile, Order, L"Iterations", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without iterations"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Iterations);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid iterations"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the passes
  //
  Status = TestCaseGetString (IniFile, Order, L"Passes", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without passes"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Passes);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid passes"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the failures
  //
  Status = TestCaseGetString (IniFile, Order, L"Failures", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without failures"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Failures);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid failures"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Check error
  //
  if (TempTestCase->Name == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeSingleTestCase (TempTestCase);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  *TestCase = TempTestCase;
  return EFI_SUCCESS;
}


EFI_STATUS
SaveSingleTestCase (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Save a test case.

--*/
{
  EFI_STATUS  Status;
  CHAR16      Buffer[EFI_SCT_MAX_BUFFER_SIZE];

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Save revision
  //
  Status = SctShortToHexStr (TestCase->Revision, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Revision", Buffer);
  }

  //
  // Save the GUID
  //
  Status = SctGuidToStr (&TestCase->Guid, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Guid", Buffer);
  }

  //
  // Save the name
  //
  TestCaseSetString (IniFile, Order, L"Name", TestCase->Name);

  //
  // Save the order
  //
  Status = SctShortToHexStr (TestCase->Order, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Order", Buffer);
  }

  //
  // Save the iterations
  //
  Status = SctShortToHexStr (TestCase->Iterations, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Iterations", Buffer);
  }

  //
  // Save the passes
  //
  Status = SctShortToHexStr (TestCase->Passes, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Passes", Buffer);
  }

  //
  // Save the failures
  //
  Status = SctShortToHexStr (TestCase->Failures, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Failures", Buffer);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadSingleTestSequence (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Load a test sequence.

--*/
{
  EFI_STATUS          Status;
  CHAR16              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINT32              Revision;
  EFI_SCT_TEST_CASE   *TempTestCase;

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a single test case
  //
  Status = CreateSingleTestCase (&TempTestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
    return Status;
  }

  //
  // Check revision
  //
  Status = TestCaseGetString (IniFile, Order, L"Revision", Buffer);
  if (EFI_ERROR (Status)) {
    //
    // Without revision info, ignore this test case
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without revision"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &Revision);
  if (EFI_ERROR (Status) || (Revision != TempTestCase->Revision)) {
    //
    // With unsupported revision info, ignore this test case
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid revision"));
    FreeSingleTestCase (TempTestCase);
    return EFI_UNSUPPORTED;
  }

  //
  // Load the GUID
  //
  Status = TestCaseGetString (IniFile, Order, L"Guid", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without GUID"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempTestCase->Guid);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid GUID"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the name
  //
  Status = TestCaseGetString (IniFile, Order, L"Name", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without name"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  TempTestCase->Name = SctStrDuplicate (Buffer);

  //
  // Load the order
  //
  Status = TestCaseGetString (IniFile, Order, L"Order", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without order"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Order);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid order"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Load the iterations
  //
  Status = TestCaseGetString (IniFile, Order, L"Iterations", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without iterations"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &TempTestCase->Iterations);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid iterations"));
    FreeSingleTestCase (TempTestCase);
    return Status;
  }

  //
  // Skip the passes and failures
  //

  //
  // Check error
  //
  if (TempTestCase->Name == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeSingleTestCase (TempTestCase);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  *TestCase = TempTestCase;
  return EFI_SUCCESS;
}


EFI_STATUS
SaveSingleTestSequence (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Save a test sequence.

--*/
{
  EFI_STATUS  Status;
  CHAR16      Buffer[EFI_SCT_MAX_BUFFER_SIZE];

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Save revision
  //
  Status = SctShortToHexStr (TestCase->Revision, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Revision", Buffer);
  }

  //
  // Save the GUID
  //
  Status = SctGuidToStr (&TestCase->Guid, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Guid", Buffer);
  }

  //
  // Save the name
  //
  TestCaseSetString (IniFile, Order, L"Name", TestCase->Name);

  //
  // Save the order
  //
  Status = SctShortToHexStr (TestCase->Order, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Order", Buffer);
  }

  //
  // Save the iterations
  //
  Status = SctShortToHexStr (TestCase->Iterations, Buffer);
  if (!EFI_ERROR (Status)) {
    TestCaseSetString (IniFile, Order, L"Iterations", Buffer);
  }

  //
  // Skip the passes and failures
  //

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  )
/*++

Routine Description:

  Allocate memory to create a test case.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_CASE   *TempTestCase;

  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the test case
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_TEST_CASE),
                 (VOID **)&TempTestCase
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempTestCase, sizeof(EFI_SCT_TEST_CASE));

  //
  // Initialize the items of test case
  //
  TempTestCase->Signature  = EFI_SCT_TEST_CASE_SIGNATURE;
  TempTestCase->Revision   = EFI_SCT_TEST_CASE_REVISION;

  TempTestCase->Order      = EFI_SCT_TEST_CASE_INVALID;
  TempTestCase->Iterations = EFI_SCT_TEST_CASE_INVALID;
  TempTestCase->Passes     = EFI_SCT_TEST_CASE_INVALID;
  TempTestCase->Failures   = EFI_SCT_TEST_CASE_INVALID;

  //
  // Done
  //
  *TestCase = TempTestCase;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeSingleTestCase (
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Free a test case.

--*/
{
  //
  // Check parameters
  //
  if (TestCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of test case
  //
  if (TestCase->Name != NULL) {
    tBS->FreePool (TestCase->Name);
    TestCase->Name = NULL;
  }

  //
  // Free the test case itself
  //
  tBS->FreePool (TestCase);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
TestCaseGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  )
/*++

Routine Description:

  Get the number of test case section.

--*/
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_TEST_CASE,
                    OrderNum
                    );
}


EFI_STATUS
TestCaseGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from the test case file.

--*/
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_TEST_CASE,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}


EFI_STATUS
TestCaseSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string into the test case file.

--*/
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_TEST_CASE,
                    Key,
                    Buffer
                    );
}
