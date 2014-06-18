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

  ReportDatabase.c

Abstract:

  This file provides the services to deal with the GUID database for test report
  generation.

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// Modular variables
//

EFI_SCT_GUID_DATABASE   *mGuidDatabase          = NULL;
UINTN                   mGuidDatabaseMaxSize   = 0;
UINTN                   mGuidDatabaseUsedSize  = 0;

EFI_SCT_GUID_ASSERTION  *mGuidAssertion         = NULL;
UINTN                   mGuidAssertionMaxSize  = 0;
UINTN                   mGuidAssertionUsedSize = 0;

EFI_SCT_REPORT_INFOR    mReportInfor;


//
// Internal functions declaration
//

EFI_STATUS
InsertGuidDatabase (
  IN CHAR16                           *GuidStr,
  IN CHAR16                           *TitleStr,
  IN CHAR16                           *IndexStr
  );

EFI_STATUS
InsertGuidAssertion (
  IN CHAR16                           *GuidStr,
  IN UINTN                            AssertionType,
  IN BOOLEAN                          Duplicate,
  OUT EFI_SCT_GUID_ASSERTION_STATE    *AssertionState
  );

EFI_STATUS
InsertReportInfor (
  IN CHAR16                           *CaseIndexStr,
  IN CHAR16                           *CaseIterationStr,
  IN CHAR16                           *TestNameStr,
  IN CHAR16                           *TestCategoryStr,
  IN CHAR16                           *GuidStr,
  IN UINTN                            AssertionType,
  IN CHAR16                           *TitleStr OPTIONAL,
  IN CHAR16                           *RuntimeInforStr OPTIONAL,
  IN CHAR16                           *DevicePathStr OPTIONAL,
  IN CHAR16                           *CaseRevisionStr OPTIONAL,
  IN CHAR16                           *CaseGuidStr OPTIONAL,
  IN CHAR16                           *FileName OPTIONAL
  );


//
// Module functions implementation
//

EFI_STATUS
LoadGuidDatabase (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Load the GUID database from a file.

--*/
{
  EFI_STATUS  Status;
  UINTN       BufferSize;
  CHAR16      *Buffer;
  CHAR16      *LineBuffer;
  CHAR16      *GuidStr;
  CHAR16      *TitleStr;
  CHAR16      *IndexStr;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Read the database file
  //
  Status = ReadFileToBuffer (
             DevicePath,
             FileName,
             &BufferSize,
             (VOID **)&Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file to buffer - %r", Status));
    return Status;
  }

  //
  // Skip the first unicode char 0xFEFF
  //
  if (Buffer[0] != 0xFEFF) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Unsupported GUID database file"));
    tBS->FreePool (Buffer);
    return EFI_SUCCESS;
  }

  LineBuffer = StrTokenLine (Buffer + 1, L"\n\r");

  //
  // Walk through the GUID database file
  //
  while (LineBuffer != NULL) {
    if (LineBuffer[0] == L'#') {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // Get the GUID string
    //
    GuidStr = LineBuffer;

    //
    // Get the Title string
    //
    TitleStr = StrTokenLine (NULL, L"\n\r");
    if (TitleStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // Get the Index string
    //
    IndexStr = StrTokenLine (NULL, L"\n\r");
    if (IndexStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // Insert the entry into the GUID database
    //
    Status = InsertGuidDatabase (GuidStr, TitleStr, IndexStr);
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Next line
    //
    LineBuffer = StrTokenLine (NULL, L"\n\r");
  }

  tBS->FreePool (Buffer);
  return EFI_SUCCESS;
}


EFI_STATUS
UnloadGuidDatabase (
  VOID
  )
/*++

Routine Description:

  Unload the GUID database.

--*/
{
  mGuidDatabaseMaxSize  = 0;
  mGuidDatabaseUsedSize = 0;

  if (mGuidDatabase != NULL) {
    tBS->FreePool (mGuidDatabase);
    mGuidDatabase = NULL;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
SearchGuidDatabase (
  IN CHAR16                       *GuidStr,
  OUT CHAR16                      *TitleStr,
  OUT CHAR16                      *IndexStr
  )
/*++

Routine Description:

  Search the database based on a GUID.

--*/
{
  UINTN   Index;

  if ((GuidStr == NULL) || (TitleStr == NULL) || (IndexStr == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Search the GUID database
  //
  for (Index = 0; Index < mGuidDatabaseUsedSize; Index ++) {
    if (SctStrCmp (GuidStr, mGuidDatabase[Index].Guid) == 0) {
      SctStrnCpy (TitleStr, mGuidDatabase[Index].Title, EFI_SCT_TITLE_LEN);
      SctStrnCpy (IndexStr, mGuidDatabase[Index].Index, EFI_SCT_INDEX_LEN);
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}


EFI_STATUS
LoadGuidAssertion (
  IN CHAR16                       *Buffer,
  IN BOOLEAN                      Duplicate,
  OUT EFI_SCT_LOG_STATE           *FileState
  )
/*++

Routine Description:

  Load the GUID assertion from a buffer.

--*/
{
  EFI_STATUS                    Status;
  CHAR16                        *LineBuffer;
  CHAR16                        *GuidStr;
  CHAR16                        *AssertionStr;
  UINTN                         AssertionType;
  CHAR16                        GenericGuidStr[EFI_SCT_GUID_LEN];
  EFI_SCT_GUID_ASSERTION_STATE  AssertionState;

  //
  // Check parameters
  //
  if ((Buffer == NULL) || (FileState == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  SctZeroMem (GenericGuidStr, EFI_SCT_GUID_LEN * sizeof(CHAR16));
  SctGuidToStr (&gTestGenericFailureGuid, GenericGuidStr);

  *FileState = EFI_SCT_LOG_STATE_EMPTY;

  //
  // Skip the first unicode char 0xFEFF
  //
  if (Buffer[0] != 0xFEFF) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Unsupported GUID assertion buffer"));
    return EFI_SUCCESS;
  }

  LineBuffer = StrTokenLine (Buffer + 1, L"\n\r");

  //
  // Walk through the GUID assertion buffer
  //
  while (LineBuffer != NULL) {
    if (LineBuffer[0] == L'|') {
      if (LineBuffer[1] == L'H') {
        //
        // The head line
        //
        *FileState = EFI_SCT_LOG_STATE_RUNNING;

      } else if (LineBuffer[1] == L'T') {
        //
        // The terminate line
        //
        *FileState = EFI_SCT_LOG_STATE_FINISHED;
      }

      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // The item line
    //

    //
    // Get the assertion's GUID
    //
    GuidStr = StrTokenField (LineBuffer, L":");
    if (GuidStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    if (!Duplicate) {
      //
      // Ignore the generic GUID
      //
      if (SctStrCmp (GuidStr, GenericGuidStr) == 0) {
        LineBuffer = StrTokenLine (NULL, L"\n\r");
        continue;
      }
    }

    //
    // Get the assertion's type
    //
    AssertionStr = StrTokenField (NULL, L"|");
    if (AssertionStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    if (SctStrCmp (AssertionStr, L"PASS") == 0) {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_PASS;
    } else if (SctStrCmp (AssertionStr, L"FAILURE") == 0) {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_FAIL;
    } else {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_WARN;
    }

    //
    // Skip the reset fields
    //

    //
    // Insert it into GUID assertion
    //
    Status = InsertGuidAssertion (
               GuidStr,
               AssertionType,
               Duplicate,
               &AssertionState
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Insert GUID assertion - %r", Status));
      return Status;
    }

    //
    // Next line
    //
    LineBuffer = StrTokenLine (NULL, L"\n\r");
  }

  return EFI_SUCCESS;
}


EFI_STATUS
UnloadGuidAssertion (
  VOID
  )
/*++

Routine Description:

  Unload the GUID assertion.

--*/
{
  mGuidAssertionMaxSize  = 0;
  mGuidAssertionUsedSize = 0;

  if (mGuidAssertion != NULL) {
    tBS->FreePool (mGuidAssertion);
    mGuidAssertion = NULL;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
GetAssertionNumber (
  IN OUT UINT32                   *PassNumber,
  IN OUT UINT32                   *WarnNumber,
  IN OUT UINT32                   *FailNumber
  )
/*++

Routine Description:

  Get the assertion number.

--*/
{
  UINTN   Index;

  //
  // Check parameters
  //
  if ((PassNumber == NULL) || (WarnNumber == NULL) || (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Search the GUID assertions
  //
  for (Index = 0; Index < mGuidAssertionUsedSize; Index ++) {
    switch (mGuidAssertion[Index].AssertionType) {
    case EFI_SCT_GUID_ASSERTION_TYPE_PASS:
      (*PassNumber) ++;
      break;
    case EFI_SCT_GUID_ASSERTION_TYPE_WARN:
      (*WarnNumber) ++;
      break;
    case EFI_SCT_GUID_ASSERTION_TYPE_FAIL:
      (*FailNumber) ++;
      break;
    default:
      break;
    }
  }

  //
  // Clear the GUID assertion
  //
  UnloadGuidAssertion ();

  return EFI_SUCCESS;
}


EFI_STATUS
LoadReportInfor (
  IN CHAR16                       *CaseIndexStr,
  IN CHAR16                       *CaseIterationStr,
  IN CHAR16                       *Buffer,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Load the report information from a buffer.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *LineBuffer;
  CHAR16      *GuidStr;
  CHAR16      *AssertionStr;
  UINTN       AssertionType;
  CHAR16      *TestNameStr;
  CHAR16      *TestCategoryStr;
  CHAR16      *DevicePathStr;
  CHAR16      *TitleStr;
  CHAR16      *RuntimeInforStr;
  CHAR16      *CaseRevisionStr;
  CHAR16      *CaseGuidStr;
  CHAR16      *CaseNameStr;
  CHAR16      GenericGuidStr[EFI_SCT_GUID_LEN];
  CHAR16      SystemHangGuidStr[EFI_SCT_GUID_LEN];

  //
  // Check parameters
  //
  if ((CaseIndexStr == NULL) || (CaseIterationStr == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  SctZeroMem (GenericGuidStr, EFI_SCT_GUID_LEN * sizeof(CHAR16));
  SctGuidToStr (&gTestGenericFailureGuid, GenericGuidStr);

  SctZeroMem (SystemHangGuidStr, EFI_SCT_GUID_LEN * sizeof(CHAR16));
  SctGuidToStr (&gEfiSystemHangAssertionGuid, SystemHangGuidStr);

  CaseGuidStr      = NULL;
  CaseRevisionStr  = NULL;
  CaseNameStr      = NULL;
  TestNameStr      = NULL;
  TestCategoryStr  = NULL;
  DevicePathStr    = NULL;

  //
  // Start to deal with the ekl file data
  //
  if (Buffer[0] != 0xFEFF) {
    return EFI_SUCCESS;
  }

  LineBuffer = StrTokenLine (Buffer + 1, L"\n\r");

  while (LineBuffer != NULL) {
    if (LineBuffer[0] == L'|') {
      if (LineBuffer[1] == L'H') {
        //
        // The head line
        //

        StrTokenField (LineBuffer, L"|");

        //
        // Skip the HEAD characters
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the first empty string
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the second empry string
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the configuration number
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the scenario string
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the execution date
        //
        StrTokenField (NULL, L"|");

        //
        // Skip the execution time
        //
        StrTokenField (NULL, L"|");

        //
        // Get the case's GUID
        //
        CaseGuidStr = StrTokenField (NULL, L"|");

        //
        // Get the case's revision
        //
        CaseRevisionStr = StrTokenField (NULL, L"|");

        //
        // Get the case's name
        //
        CaseNameStr = StrTokenField (NULL, L"|");

        //
        // Get the test name
        //
        TestNameStr = StrTokenField (NULL, L"|");

        //
        // Get the test category
        //
        TestCategoryStr = StrTokenField (NULL, L"|");

        //
        // Get the device path
        //
        // Note: Don't use "|" to split the device path token, some device path
        //  include that. And from the other way, the device path token should
        //  be the last token in the .ekl header.
        //
        DevicePathStr = StrTokenField (NULL, L"\n");

      } else if (LineBuffer[1] == L'T') {
        //
        // The terminate line, do nothing
        //
      }

      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // The item line
    //

    //
    // Get the assertion's GUID
    //
    GuidStr = StrTokenField (LineBuffer, L":");
    if (GuidStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // Ignore the generic GUID
    //
    if (SctStrCmp (GuidStr, GenericGuidStr) == 0) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    //
    // Get the assertion's type
    //
    AssertionStr = StrTokenField (NULL, L"|");
    if (AssertionStr == NULL) {
      LineBuffer = StrTokenLine (NULL, L"\n\r");
      continue;
    }

    if (SctStrCmp (AssertionStr, L"PASS") == 0) {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_PASS;
    } else if (SctStrCmp (AssertionStr, L"FAILURE") == 0) {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_FAIL;
    } else {
      AssertionType = EFI_SCT_GUID_ASSERTION_TYPE_WARN;
    }

    //
    // Get the Title
    //
    TitleStr = StrTokenField (NULL, L":");
    if (SctStrCmp (GuidStr, SystemHangGuidStr) == 0) {
      TitleStr = SctStrDuplicate (L"System hangs or stops abnormally.");
    }

    //
    // Get the runtime information
    //
    RuntimeInforStr = StrTokenField (NULL, L"\n\r");
    if (SctStrCmp (GuidStr, SystemHangGuidStr) == 0) {
      RuntimeInforStr = SctPoolPrint (L"System hang in %s - %s", TestCategoryStr, CaseNameStr);
    }

    //
    // Set the report item
    //
    Status = InsertReportInfor (
               CaseIndexStr,
               CaseIterationStr,
               TestNameStr,
               TestCategoryStr,
               GuidStr,
               AssertionType,
               TitleStr,
               RuntimeInforStr,
               DevicePathStr,
               CaseRevisionStr,
               CaseGuidStr,
               FileName
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Set report item - %r", Status));
      if (SctStrCmp (GuidStr, SystemHangGuidStr) == 0) {
        tBS->FreePool (TitleStr);
        tBS->FreePool (RuntimeInforStr);
      }
      return Status;
    }

    if (SctStrCmp (GuidStr, SystemHangGuidStr) == 0) {
      tBS->FreePool (TitleStr);
      tBS->FreePool (RuntimeInforStr);
    }

    //
    // Next line
    //
    LineBuffer = StrTokenLine (NULL, L"\n\r");
  }

  return EFI_SUCCESS;
}


EFI_STATUS
UnloadReportInfor (
  VOID
  )
/*++

Routine Description:

  Unload report information.

--*/
{
  EFI_SCT_REPORT_ITEM       *ReportItem;
  EFI_SCT_REPORT_ITEM       *NextReportItem;
  EFI_SCT_ASSERTION_INFOR   *AssertionInfor;
  EFI_SCT_ASSERTION_INFOR   *NextAssertionInfor;

  //
  // For each report item
  //
  ReportItem     = mReportInfor.ReportItem;
  NextReportItem = NULL;

  while (ReportItem != NULL) {
    //
    // For each passed assertion
    //
    AssertionInfor     = ReportItem->PassAssertion;
    NextAssertionInfor = NULL;

    while (AssertionInfor != NULL) {
      NextAssertionInfor = AssertionInfor->Next;
      tBS->FreePool (AssertionInfor);
      AssertionInfor = NextAssertionInfor;
    }

    //
    // For each failed assertion
    //
    AssertionInfor     = ReportItem->FailAssertion;
    NextAssertionInfor = NULL;

    while (AssertionInfor != NULL) {
      NextAssertionInfor = AssertionInfor->Next;
      tBS->FreePool (AssertionInfor);
      AssertionInfor = NextAssertionInfor;
    }

    NextReportItem = ReportItem->Next;
    tBS->FreePool (ReportItem);
    ReportItem = NextReportItem;
  }

  mReportInfor.ReportItem = NULL;
  return EFI_SUCCESS;
}


EFI_STATUS
GetReportInfor (
  OUT CHAR16                      **Buffer
  )
/*++

Routine Description:

  Get the report information into a buffer.

--*/
{
  EFI_SCT_REPORT_ITEM       *ReportItem;
  EFI_SCT_ASSERTION_INFOR   *AssertionInfor;
  CHAR16                    *TempBuffer;

  //
  // Check parameters
  //
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  *Buffer = NULL;

  //
  // Add summary head:
  // "Self Certification Test Report"
  // "Service\Protocol Name", "Total", "Failed", "Passed"
  //
  AutoStrCat (
    Buffer,
    L"\"Self Certification Test Report\"\n"
    L"\"Service\\Protocol Name\",\"Total\",\"Failed\",\"Passed\"\n"
    );

  //
  // For each report item, from the last one
  //
  ReportItem = mReportInfor.ReportItem;

  while ((ReportItem != NULL) && (ReportItem->Next != NULL)) {
    ReportItem = ReportItem->Next;
  }

  while (ReportItem != NULL) {
    TempBuffer = SctPoolPrint (
                   L"\"%s\",\"%d\",\"%d\",\"%d\"\n",
                   ReportItem->TestCategory,
                   ReportItem->PassNumber + ReportItem->FailNumber,
                   ReportItem->FailNumber,
                   ReportItem->PassNumber
                   );
    if (TempBuffer == NULL) {
      break;
    }

    AutoStrCat (Buffer, TempBuffer);
    tBS->FreePool (TempBuffer);

    ReportItem = ReportItem->Prev;
  }

  //
  // Total summary
  //
  TempBuffer = SctPoolPrint (
                 L"\"Total service\\Protocol\",\"%d\",\"%d\",\"%d\"\n",
                 mReportInfor.TotalPass + mReportInfor.TotalFail,
                 mReportInfor.TotalFail,
                 mReportInfor.TotalPass
                 );
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  AutoStrCat (Buffer, TempBuffer);

  //
  // Add fail head:
  // "Service\Protocol Name", "Index","Instance","Iteration","Guid","Result","Title","Runtime Information","Case Revision","Case GUID","Device Path","Logfile Name"
  //
  AutoStrCat (
    Buffer,
    L"\n\"Service\\Protocol Name\",\"Index\",\"Instance\",\"Iteration\",\"Guid\",\"Result\",\"Title\",\"Runtime Information\",\"Case Revision\",\"Case GUID\",\"Device Path\",\"Logfile Name\"\n"
    );

  //
  // For each report item, from the last one
  //
  ReportItem = mReportInfor.ReportItem;

  while ((ReportItem != NULL) && (ReportItem->Next != NULL)) {
    ReportItem = ReportItem->Next;
  }

  while (ReportItem != NULL) {
    //
    // For each failed assertion, from the last one
    //
    AssertionInfor = ReportItem->FailAssertion;

    while ((AssertionInfor != NULL) && (AssertionInfor->Next != NULL)) {
      AssertionInfor = AssertionInfor->Next;
    }

    while (AssertionInfor != NULL) {
      TempBuffer = SctPoolPrint (
                     L"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"FAIL\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                     ReportItem->TestCategory,
                     AssertionInfor->Index,
                     AssertionInfor->CaseIndex,
                     AssertionInfor->CaseIteration,
                     AssertionInfor->Guid,
                     AssertionInfor->Title,
                     AssertionInfor->RuntimeInfor,
                     AssertionInfor->CaseRevision,
                     AssertionInfor->CaseGuid,
                     AssertionInfor->DevicePath,
                     AssertionInfor->FileName
                     );
      if (TempBuffer == NULL) {
        break;
      }

      AutoStrCat (Buffer, TempBuffer);
      tBS->FreePool (TempBuffer);

      AssertionInfor = AssertionInfor->Prev;
    }

    ReportItem = ReportItem->Prev;
  }

  //
  // Add pass head:
  // "Service\Protocol Name","Index","Instance","Iteration","Guid","Result","Title","Runtime Information","Case Revision","Case GUID"  //
  //
  AutoStrCat (
    Buffer,
    L"\n\"Service\\Protocol Name\",\"Index\",\"Instance\",\"Iteration\",\"Guid\",\"Result\",\"Title\",\"Runtime Information\",\"Case Revision\",\"Case GUID\"\n"
    );

  //
  // For each report item, from the last one
  //
  ReportItem = mReportInfor.ReportItem;

  while ((ReportItem != NULL) && (ReportItem->Next != NULL)) {
    ReportItem = ReportItem->Next;
  }

  while (ReportItem != NULL) {
    //
    // For each passed assertion, from the last one
    //
    AssertionInfor = ReportItem->PassAssertion;

    while ((AssertionInfor != NULL) && (AssertionInfor->Next != NULL)) {
      AssertionInfor = AssertionInfor->Next;
    }

    while (AssertionInfor != NULL) {
      TempBuffer = SctPoolPrint (
                     L"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"PASS\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                     ReportItem->TestCategory,
                     AssertionInfor->Index,
                     AssertionInfor->CaseIndex,
                     AssertionInfor->CaseIteration,
                     AssertionInfor->Guid,
                     AssertionInfor->Title,
                     AssertionInfor->RuntimeInfor,
                     AssertionInfor->CaseRevision,
                     AssertionInfor->CaseGuid
                     );
      if (TempBuffer == NULL) {
        break;
      }

      AutoStrCat (Buffer, TempBuffer);
      tBS->FreePool (TempBuffer);

      AssertionInfor = AssertionInfor->Prev;
    }

    ReportItem = ReportItem->Prev;
  }

  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
InsertGuidDatabase (
  IN CHAR16                       *GuidStr,
  IN CHAR16                       *TitleStr,
  IN CHAR16                       *IndexStr
  )
/*++

Routine Description:

  Insert a GUID entry.

--*/
{
  EFI_STATUS              Status;
  EFI_SCT_GUID_DATABASE   *TempGuidDatabase;

  //
  // Check parameters
  //
  if ((GuidStr == NULL) || (TitleStr == NULL) || (IndexStr == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Need to create a new buffer?
  //
  if (mGuidDatabaseMaxSize == 0) {
    mGuidDatabaseMaxSize  = EFI_SCT_GUID_DATABASE_SIZE;
    mGuidDatabaseUsedSize = 0;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mGuidDatabaseMaxSize * sizeof(EFI_SCT_GUID_DATABASE),
                   (VOID **)&mGuidDatabase
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mGuidDatabaseMaxSize = 0;
      return Status;
    }

    SctZeroMem (mGuidDatabase, mGuidDatabaseMaxSize * sizeof(EFI_SCT_GUID_DATABASE));
  }

  //
  // Need to enlarge a new buffer?
  //
  if (mGuidDatabaseUsedSize + 1 >= mGuidDatabaseMaxSize) {
    mGuidDatabaseMaxSize = mGuidDatabaseMaxSize * 2;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mGuidDatabaseMaxSize * sizeof(EFI_SCT_GUID_DATABASE),
                   (VOID **)&TempGuidDatabase
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mGuidDatabaseMaxSize = mGuidDatabaseMaxSize / 2;
      return Status;
    }

    SctZeroMem (TempGuidDatabase, mGuidDatabaseMaxSize * sizeof(EFI_SCT_GUID_DATABASE));

    //
    // Copy the original data
    //
    SctCopyMem (TempGuidDatabase, mGuidDatabase, mGuidDatabaseUsedSize * sizeof(EFI_SCT_GUID_DATABASE));

    //
    // Free the original buffer
    //
    tBS->FreePool (mGuidDatabase);
    mGuidDatabase = TempGuidDatabase;
  }

  //
  // Append the GUID entry to the GUID database
  //
  SctStrnCpy (mGuidDatabase[mGuidDatabaseUsedSize].Guid, GuidStr, EFI_SCT_GUID_LEN);
  SctStrnCpy (mGuidDatabase[mGuidDatabaseUsedSize].Title, TitleStr, EFI_SCT_TITLE_LEN);
  SctStrnCpy (mGuidDatabase[mGuidDatabaseUsedSize].Index, IndexStr, EFI_SCT_INDEX_LEN);
  mGuidDatabaseUsedSize ++;

  return EFI_SUCCESS;
}


EFI_STATUS
InsertGuidAssertion (
  IN CHAR16                           *GuidStr,
  IN UINTN                            AssertionType,
  IN BOOLEAN                          Duplicate,
  OUT EFI_SCT_GUID_ASSERTION_STATE    *AssertionState
  )
/*++

Routine Description:

  Insert a GUID assertion.

--*/
{
  EFI_STATUS              Status;
  INTN                    Index;
  UINTN                   OldAssertionType;
  CHAR16                  SystemHangGuidStr[EFI_SCT_GUID_LEN];
  EFI_SCT_GUID_ASSERTION  *TempGuidAssertion;
  //
  // Check parameters
  //
  if ((GuidStr == NULL) || (AssertionState == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Skip warning assertion in non-duplicate condition
  //
//  if (!Duplicate && (AssertionType == EFI_SCT_GUID_ASSERTION_TYPE_WARN)) {
//    return EFI_SUCCESS;
//  }

  //
  // Initialize
  //
  SctZeroMem (SystemHangGuidStr, EFI_SCT_GUID_LEN);
  SctGuidToStr (&gEfiSystemHangAssertionGuid, SystemHangGuidStr);

  *AssertionState = EFI_SCT_GUID_ASSERTION_STATE_NOT_FOUND;

  //
  // Remove the duplicate GUID assertion
  //
  if (!Duplicate && (SctStrCmp (SystemHangGuidStr, GuidStr) != 0)) {
    //
    // Seach the GUID assertion, from the last one for performance
    //
    for (Index = (INTN)mGuidAssertionUsedSize - 1; Index >= 0; Index --) {
      if (SctStrCmp (mGuidAssertion[Index].Guid, GuidStr) != 0) {
        continue;
      }

      //
      // Find it.
      // Set the worst assertion type (Pass = 0x01, Warn = 0x03, Fail = 0x07)
      //
      OldAssertionType = mGuidAssertion[Index].AssertionType;
      if ((OldAssertionType | AssertionType) == OldAssertionType) {
        *AssertionState = EFI_SCT_GUID_ASSERTION_STATE_FOUND;
        return EFI_SUCCESS;
      }

      mGuidAssertion[Index].AssertionType |= AssertionType;
      *AssertionState = EFI_SCT_GUID_ASSERTION_STATE_OVERRIDE;
      return EFI_SUCCESS;
    }
  }

  //
  // Need to create a new buffer?
  //
  if (mGuidAssertionMaxSize == 0) {
    mGuidAssertionMaxSize  = EFI_SCT_GUID_ASSERTION_SIZE;
    mGuidAssertionUsedSize = 0;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mGuidAssertionMaxSize * sizeof(EFI_SCT_GUID_ASSERTION),
                   (VOID **)&mGuidAssertion
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mGuidAssertionMaxSize = 0;
      return Status;
    }

    SctZeroMem (mGuidAssertion, mGuidAssertionMaxSize * sizeof(EFI_SCT_GUID_ASSERTION));
  }

  //
  // Need to enlarge a new buffer?
  //
  if (mGuidAssertionUsedSize + 1 >= mGuidAssertionMaxSize) {
    mGuidAssertionMaxSize = mGuidAssertionMaxSize * 2;

    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   mGuidAssertionMaxSize * sizeof(EFI_SCT_GUID_ASSERTION),
                   (VOID **)&TempGuidAssertion
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      mGuidAssertionMaxSize = mGuidAssertionMaxSize / 2;
      return Status;
    }

    SctZeroMem (mGuidAssertion, mGuidAssertionMaxSize * sizeof(EFI_SCT_GUID_ASSERTION));

    //
    // Copy the original data
    //
    SctCopyMem (TempGuidAssertion, mGuidAssertion, mGuidAssertionUsedSize * sizeof(EFI_SCT_GUID_ASSERTION));

    //
    // Free the original buffer
    //
    tBS->FreePool (mGuidAssertion);
    mGuidAssertion = TempGuidAssertion;
  }

  //
  // Append the GUID entry to the GUID assertion
  //
  SctStrnCpy (mGuidAssertion[mGuidAssertionUsedSize].Guid, GuidStr, EFI_SCT_GUID_LEN);
  mGuidAssertion[mGuidAssertionUsedSize].AssertionType = AssertionType;
  mGuidAssertionUsedSize ++;

  return EFI_SUCCESS;
}


EFI_STATUS
InsertReportInfor (
  IN CHAR16                       *CaseIndexStr,
  IN CHAR16                       *CaseIterationStr,
  IN CHAR16                       *TestNameStr,
  IN CHAR16                       *TestCategoryStr,
  IN CHAR16                       *GuidStr,
  IN UINTN                        AssertionType,
  IN CHAR16                       *TitleStr OPTIONAL,
  IN CHAR16                       *RuntimeInforStr OPTIONAL,
  IN CHAR16                       *DevicePathStr OPTIONAL,
  IN CHAR16                       *CaseRevisionStr OPTIONAL,
  IN CHAR16                       *CaseGuidStr OPTIONAL,
  IN CHAR16                       *FileName OPTIONAL
  )
/*++

Routine Description:

  Insert a report item.

--*/
{
  EFI_STATUS                    Status;
  EFI_SCT_REPORT_ITEM           *ReportItem;
  EFI_SCT_REPORT_ITEM           *NewReportItem;
  EFI_SCT_ASSERTION_INFOR       *AssertionInfor;
  EFI_SCT_ASSERTION_INFOR       *LastAssertionInfor;
  EFI_SCT_ASSERTION_INFOR       *NewAssertionInfor;
  EFI_SCT_GUID_ASSERTION_STATE  AssertionState;

  if ((CaseIndexStr == NULL) || (CaseIterationStr == NULL) ||
      (TestNameStr  == NULL) || (TestCategoryStr  == NULL) ||
      (GuidStr      == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Skip the warning assertions
  //
  if (AssertionType == EFI_SCT_GUID_ASSERTION_TYPE_WARN) {
    return EFI_SUCCESS;
  }

  //
  // Insert the GUID assertion
  //
  Status = InsertGuidAssertion (
             GuidStr,
             AssertionType,
             FALSE,                     // Without duplicate
             &AssertionState
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Insert GUID assertion - %r", Status));
    return Status;
  }

  //
  // Skip the duplicate assertions
  //
  if (AssertionState == EFI_SCT_GUID_ASSERTION_STATE_FOUND) {
    return EFI_SUCCESS;
  }

  //
  // Search the report category
  //
  ReportItem = mReportInfor.ReportItem;
  while (ReportItem != NULL) {
    if (SctStrCmp (ReportItem->TestName, TestNameStr) != 0) {
      ReportItem = ReportItem->Next;
      continue;
    }

    //
    // Override the pass assertion
    //
    if (AssertionState == EFI_SCT_GUID_ASSERTION_STATE_OVERRIDE) {
      mReportInfor.TotalPass --;
      ReportItem->PassNumber --;

      //
      // Search the passed assertion and remove it
      //
      AssertionInfor = ReportItem->PassAssertion;
      LastAssertionInfor = NULL;

      while (AssertionInfor != NULL) {
        if (SctStrCmp (AssertionInfor->Guid, GuidStr) == 0) {
          //
          // Found it
          //
          if (LastAssertionInfor == NULL) {
            ReportItem->PassAssertion  = AssertionInfor->Next;
          } else {
            LastAssertionInfor->Next   = AssertionInfor->Next;
          }

          if (AssertionInfor->Next != NULL) {
            AssertionInfor->Next->Prev = LastAssertionInfor;
          }

          tBS->FreePool (AssertionInfor);
          break;
        }

        LastAssertionInfor = AssertionInfor;
        AssertionInfor     = AssertionInfor->Next;
      }
    }
    break;
  }

  if (ReportItem == NULL) {
    //
    // Not found, create a new report item
    //
    Status = tBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_SCT_REPORT_ITEM),
                   (VOID **)&NewReportItem
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
      return EFI_OUT_OF_RESOURCES;
    }

    SctZeroMem (NewReportItem, sizeof(EFI_SCT_REPORT_ITEM));

    SctStrnCpy (NewReportItem->TestName, TestNameStr, EFI_SCT_NAME_LEN);
    SctStrnCpy (NewReportItem->TestCategory, TestCategoryStr, EFI_SCT_NAME_LEN);

    //
    // Add the report item into the list
    //
    ReportItem = mReportInfor.ReportItem;
    mReportInfor.ReportItem = NewReportItem;

    NewReportItem->Next = ReportItem;
    if (ReportItem != NULL) {
      ReportItem->Prev = NewReportItem;
    }

    ReportItem = NewReportItem;
  }

  //
  // Update the assertion number
  //
  if (AssertionType == EFI_SCT_GUID_ASSERTION_TYPE_PASS) {
    mReportInfor.TotalPass ++;
    ReportItem->PassNumber ++;
  } else {
    mReportInfor.TotalFail ++;
    ReportItem->FailNumber ++;
  }

  //
  // Allocate a buffer for the new assertion info
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_ASSERTION_INFOR),
                 (VOID **)&NewAssertionInfor
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (NewAssertionInfor, sizeof(EFI_SCT_ASSERTION_INFOR));

  //
  // Get the Title and Index from GUID database
  //
  Status = SearchGuidDatabase (
             GuidStr,
             NewAssertionInfor->Title,
             NewAssertionInfor->Index
             );
  if (EFI_ERROR (Status)) {
    //
    // Cannot find the related entry in the GUID database. It is not a fatal
    // error
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Search GUID database - %r", Status));
  }

  //
  // Set the items of assertion info
  //
  SctStrnCpy (NewAssertionInfor->CaseIndex, CaseIndexStr, EFI_SCT_CASE_INDEX_LEN);
  SctStrnCpy (NewAssertionInfor->CaseIteration, CaseIterationStr, EFI_SCT_CASE_ITERATION_LEN);
  SctStrnCpy (NewAssertionInfor->Guid, GuidStr, EFI_SCT_GUID_LEN);

  if ((NewAssertionInfor->Title[0] == L'\0') && (TitleStr != NULL)) {
    SctStrnCpy (NewAssertionInfor->Title, TitleStr, EFI_SCT_TITLE_LEN);
  }
  if (RuntimeInforStr != NULL) {
    SctStrnCpy (NewAssertionInfor->RuntimeInfor, RuntimeInforStr, EFI_SCT_RUNTIME_INFOR_LEN);
  }
  if (DevicePathStr != NULL) {
    SctStrnCpy (NewAssertionInfor->DevicePath, DevicePathStr, EFI_SCT_DEVICE_PATH_LEN);
  }
  if (CaseRevisionStr != NULL) {
    SctStrnCpy (NewAssertionInfor->CaseRevision, CaseRevisionStr, EFI_SCT_CASE_REVISION_LEN);
  }
  if (CaseGuidStr != NULL) {
    SctStrnCpy (NewAssertionInfor->CaseGuid, CaseGuidStr, EFI_SCT_CASE_GUID_LEN);
  }
  if (FileName != NULL) {
    SctStrnCpy (NewAssertionInfor->FileName, FileName, EFI_SCT_NAME_LEN);
  }

  //
  // Add this assertion info to the list
  //
  if (AssertionType == EFI_SCT_GUID_ASSERTION_TYPE_PASS) {
    AssertionInfor = ReportItem->PassAssertion;
    ReportItem->PassAssertion = NewAssertionInfor;
  } else {
    AssertionInfor = ReportItem->FailAssertion;
    ReportItem->FailAssertion = NewAssertionInfor;
  }

  NewAssertionInfor->Next = AssertionInfor;
  if (AssertionInfor != NULL) {
    AssertionInfor->Prev = NewAssertionInfor;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
