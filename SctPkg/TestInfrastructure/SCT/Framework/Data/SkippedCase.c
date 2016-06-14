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

  SkippedCase.c

Abstract:

  This file provides the services to manage the skipped case.

  In the SCT execution process, some selected cases are skipped.
  In order to reminder user, SCT provide a file named as 
  '.\data\SkippedCase.ini'to record them.

--*/

#include "Sct.h"

#define EFI_SCT_SECTION_SKIPPED_CASE    L"Skipped Case"

EFI_STATUS
FreeSingleSkippedCase (
  IN EFI_SCT_SKIPPED_CASE            *SkippedCase
  );

EFI_STATUS
CreateSkippedCase (
  OUT EFI_SCT_SKIPPED_CASE           **SkippedCase,
  IN  UINT32                         Order
  );
EFI_STATUS
SkippedCaseSetStringByOrder (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );

EFI_STATUS
SkippedCaseGetStringByOrder (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
LoadSingleSkippedCase (
  IN EFI_INI_FILE_HANDLE      IniFile,
  IN UINT32                   Order,
  OUT EFI_SCT_SKIPPED_CASE    **SkippedCase
  );

EFI_STATUS
SkippedCaseGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  );

EFI_STATUS
RecordSkippedCases (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Record the skipped cases into list.

Arguments:

  SkippedCaseList  - Pointer to the skipped test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_SKIPPED_CASE    *TempSkippedCase;
  EFI_SCT_SKIPPED_CASE    *SkippedCase;
  SCT_LIST_ENTRY          *SkippedCaseList;
  SCT_LIST_ENTRY          *Link;
  EFI_STATUS              Status;
  UINT32                  Order = 0;

  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through skipped Case List
  //
  SkippedCaseList = &gFT->SkippedCaseList;

  for (Link = SkippedCaseList->ForwardLink; Link != SkippedCaseList; Link = Link->ForwardLink) {
    TempSkippedCase = CR (Link, EFI_SCT_SKIPPED_CASE, Link, EFI_SCT_SKIPPED_CASE_SIGNATURE);

	if ( (SctStrCmp (TempSkippedCase->CaseName, ExecuteInfo->TestCase->Name) == 0) && \
		(SctStrCmp (TempSkippedCase->ProtocolName, ExecuteInfo->Category->Name) == 0) )
      return EFI_ABORTED;

	Order++;
  }

  Status = CreateSkippedCase(&SkippedCase, Order);
  if ( !EFI_ERROR(Status) ) {
    SkippedCase->CaseName = SctStrDuplicate (ExecuteInfo->TestCase->Name);
    SkippedCase->ProtocolName = SctStrDuplicate (ExecuteInfo->Category->Name);
  }

  ExecuteInfo->SkippedCase = SkippedCase;

  SctInsertTailList (SkippedCaseList, &SkippedCase->Link);
  
  return Status;
}


EFI_STATUS
CreateSkippedCase (
  OUT EFI_SCT_SKIPPED_CASE           **SkippedCase,
  IN  UINT32                         Order
  )
/*++

Routine Description:

  Allocate memory to create a skipped case structure.

--*/
{
  EFI_STATUS             Status;
  EFI_SCT_SKIPPED_CASE   *TempSkippedCase;

  //
  // Check parameters
  //
  if (SkippedCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the skipped case
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_SKIPPED_CASE),
                 (VOID **)&TempSkippedCase
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempSkippedCase, sizeof(EFI_SCT_SKIPPED_CASE));

  //
  // Initialize the items of skipped case
  //
  TempSkippedCase->Signature  = EFI_SCT_SKIPPED_CASE_SIGNATURE;
  TempSkippedCase->Revision   = EFI_SCT_SKIPPED_CASE_REVISION;

  TempSkippedCase->Order = Order;

  //
  // Done
  //
  *SkippedCase = TempSkippedCase;
  return EFI_SUCCESS;
}

EFI_STATUS
FreeSkippedCases (
  IN SCT_LIST_ENTRY               *SkippedCaseList
  )
/*++

Routine Description:

  Free the skipped cases list.

Arguments:

  SkippedCaseList  - Pointer to the skipped test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_SKIPPED_CASE   *SkippedCase;

  //
  // Check parameters
  //
  if (SkippedCaseList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes
  //
  while (!SctIsListEmpty (SkippedCaseList)) {
    SkippedCase = CR (SkippedCaseList->ForwardLink, EFI_SCT_SKIPPED_CASE, Link, EFI_SCT_SKIPPED_CASE_SIGNATURE);

    SctRemoveEntryList (&SkippedCase->Link);
    FreeSingleSkippedCase (SkippedCase);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
FreeSingleSkippedCase (
  IN EFI_SCT_SKIPPED_CASE            *SkippedCase
  )
/*++

Routine Description:

  Free a skipped case.

--*/
{
  //
  // Check parameters
  //
  if (SkippedCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Free Item of Skipped Case 
  if (SkippedCase->CaseName != NULL) {
    tBS->FreePool (SkippedCase->CaseName);
    SkippedCase->CaseName = NULL;
  }

  if (SkippedCase->ProtocolName != NULL) {
    tBS->FreePool (SkippedCase->ProtocolName);
    SkippedCase->ProtocolName = NULL;
  }
  
  //
  // Free the Skipped Case itself
  //
  tBS->FreePool (SkippedCase);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
SaveSkippedCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Save the skipped case list into a file.

Arguments:

  DevicePath       - Device path of the file.
  FileName         - Name of the file.
  SkippedCaseList  - Pointer to the test case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS               Status;
  EFI_INI_FILE_HANDLE      IniFile;
  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (ExecuteInfo == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Save skipped cases into <%s>", FileName));

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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open skipped case file - %r", Status));
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
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create skipped case file - %r", Status));
      return Status;
    }
  }

  //
  // Save the name
  //
  SkippedCaseSetStringByOrder (IniFile, ExecuteInfo->SkippedCase->Order, L"CaseName", ExecuteInfo->TestCase->Name);
  SkippedCaseSetStringByOrder (IniFile, ExecuteInfo->SkippedCase->Order, L"ProtocolName", ExecuteInfo->Category->Name);
  

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
SkippedCaseSetStringByOrder (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string into the skipped case file.

--*/
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_SKIPPED_CASE,
                    Key,
                    Buffer
                    );
}


EFI_STATUS
LoadSkippedCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *SkippedCaseList
  )
/*++

Routine Description:

  Load the skipped case list from a file.

Arguments:

  DevicePath       - Device path of the file.
  FileName         - Name of the file.
  SkippedCaseList  - Pointer to the skipped case list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  UINT32                  Index;
  UINT32                  NumberOfSkippedCases;
  EFI_INI_FILE_HANDLE     IniFile;
  EFI_SCT_SKIPPED_CASE    *SkippedCase;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (SkippedCaseList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load skipped cases from <%s>", FileName));

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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open skipped case file - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // If the test case file doesn't exist, use the empty setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Skipped case file doesn't exist"));
    return EFI_SUCCESS;
  }

  //
  // Get the number of test cases
  //
  Status = SkippedCaseGetOrderNum (
             IniFile,
             &NumberOfSkippedCases
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get order number - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test cases
  //
  for (Index = 0; Index < NumberOfSkippedCases; Index ++) {
    //
    // Load a single test case
    //
    Status = LoadSingleSkippedCase (
               IniFile,
               Index,
               &SkippedCase
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load a skipped case (#%d) - %r", Index, Status));
      continue;
    }

    //
    // Add this skipped case into the skipped case list
    //
    SctInsertTailList (SkippedCaseList, &SkippedCase->Link);
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
LoadSingleSkippedCase (
  IN EFI_INI_FILE_HANDLE      IniFile,
  IN UINT32                   Order,
  OUT EFI_SCT_SKIPPED_CASE    **SkippedCase
  )
/*++

Routine Description:

  Load a skipped case.

--*/
{
  EFI_STATUS              Status;
  CHAR16                  Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  EFI_SCT_SKIPPED_CASE    *TempSkippedCase;

  //
  // Check parameters
  //
  if (SkippedCase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a single test case
  //
  Status = CreateSkippedCase (&TempSkippedCase, Order);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test case - %r", Status));
    return Status;
  }

  SkippedCaseGetStringByOrder (IniFile, Order, L"CaseName", Buffer);
  TempSkippedCase->CaseName = SctStrDuplicate (Buffer);
  
  SkippedCaseGetStringByOrder (IniFile, Order, L"ProtocolName", Buffer);
  TempSkippedCase->ProtocolName = SctStrDuplicate (Buffer);
  //
  // Done
  //
  *SkippedCase = TempSkippedCase;
  return EFI_SUCCESS;
}

EFI_STATUS
SkippedCaseGetStringByOrder (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from the skipped case file.

--*/
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_SKIPPED_CASE,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}

EFI_STATUS
SkippedCaseGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  )
/*++

Routine Description:

  Get the number of skipped case section.

--*/
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_SKIPPED_CASE,
                    OrderNum
                    );
}
