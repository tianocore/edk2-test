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

  ApTest.c

Abstract:

  This file provides the services to manage the Application Test or Script Test
  data.

  Since the Application Test and Script Test cannot describe the test related
  information by themselves. In the EFI SCT, we used an INI file to describe
  this kind of information for each Application Test or Script Test.

--*/

#include "Sct.h"

//
// Internal definitions
//

#define EFI_SCT_SECTION_AP_TEST_INTERFACE   L"Test Interface"
#define EFI_SCT_SECTION_AP_TEST_ENTRY       L"Test Entry"

//
// Internal functions declaration
//

EFI_STATUS
LoadApTestInterface (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  );

EFI_STATUS
CreateApTestInterface (
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  );

EFI_STATUS
FreeApTestInterface (
  IN EFI_AP_TEST_INTERFACE        *ApTest
  );

EFI_STATUS
LoadApTestEntryList (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT EFI_AP_TEST_ENTRY           **ApEntryList
  );

EFI_STATUS
FreeApTestEntryList (
  IN EFI_AP_TEST_ENTRY            *ApEntryList
  );

EFI_STATUS
LoadSingleApTestEntry (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_AP_TEST_ENTRY           **ApEntry
  );

EFI_STATUS
CreateSingleApTestEntry (
  OUT EFI_AP_TEST_ENTRY           **ApEntry
  );

EFI_STATUS
FreeSingleApTestEntry (
  IN EFI_AP_TEST_ENTRY            *ApEntry
  );

EFI_STATUS
ApTestInterfaceGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
ApTestInterfaceSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );

EFI_STATUS
ApTestEntryGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  );

EFI_STATUS
ApTestEntryGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
ApTestEntrySetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );


//
// External functions implementation
//

EFI_STATUS
LoadApTest (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  )
/*++

Routine Description:

  Load the application test from a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  ApTest        - Pointer to the application test interface.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_INI_FILE_HANDLE     IniFile;
  EFI_AP_TEST_INTERFACE   *TempApTest;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (ApTest == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load AP test from <%s>", FileName));

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
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open AP test file - %r", Status));
    return Status;
  }

  //
  // Load the application test interface
  //
  Status = LoadApTestInterface (
             IniFile,
             &TempApTest
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load AP test interface - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Load the application test entry list
  //
  Status = LoadApTestEntryList (
             IniFile,
             &TempApTest->EntryList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load AP test entry list - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    FreeApTest (TempApTest);
    return Status;
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
  *ApTest = TempApTest;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeApTest (
  IN EFI_AP_TEST_INTERFACE        *ApTest
  )
/*++

Routine Description:

  Free the application test.

Arguments:

  ApTest        - Pointer to the application test interface.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  //
  // Check parameters
  //
  if (ApTest == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the application test entry list
  //
  if (ApTest->EntryList != NULL) {
    FreeApTestEntryList (ApTest->EntryList);
    ApTest->EntryList = NULL;
  }

  //
  // Free the application test interface
  //
  FreeApTestInterface (ApTest);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
LoadApTestInterface (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  )
/*++

Routine Description:

  Load an application test interface.

--*/
{
  EFI_STATUS              Status;
  CHAR16                  Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINT32                  Revision;
  EFI_AP_TEST_INTERFACE   *TempApTest;

  //
  // Check parameters
  //
  if (ApTest == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create an application test interface
  //
  Status = CreateApTestInterface (&TempApTest);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create AP test interface - %r", Status));
    return Status;
  }

  //
  // Load the test revision
  //
  Status = ApTestInterfaceGetString (IniFile, L"TestRevision", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without test revision"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &Revision);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid test revision"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  TempApTest->TestRevision = (UINT64) Revision;

  //
  // Load the category GUID
  //
  Status = ApTestInterfaceGetString (IniFile, L"CategoryGuid", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without category GUID"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempApTest->CategoryGuid);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid category GUID"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  //
  // Load the name
  //
  Status = ApTestInterfaceGetString (IniFile, L"Name", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without name"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  TempApTest->Name = SctStrDuplicate (Buffer);

  //
  // Load the description
  //
  Status = ApTestInterfaceGetString (IniFile, L"Description", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without description"));
    FreeApTestInterface (TempApTest);
    return Status;
  }

  TempApTest->Description = SctStrDuplicate (Buffer);

  //
  // Check error
  //
  if ((TempApTest->Name        == NULL) ||
      (TempApTest->Description == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeApTestInterface (TempApTest);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  *ApTest = TempApTest;
  return EFI_SUCCESS;
}


EFI_STATUS
CreateApTestInterface (
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  )
/*++

Routine Description:

  Create an application test interface.

--*/
{
  EFI_STATUS              Status;
  EFI_AP_TEST_INTERFACE   *TempApTest;

  //
  // Check parameters
  //
  if (ApTest == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the application test interface
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_AP_TEST_INTERFACE),
                 &TempApTest
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempApTest, sizeof(EFI_AP_TEST_INTERFACE));

  //
  // Done
  //
  *ApTest = TempApTest;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeApTestInterface (
  IN EFI_AP_TEST_INTERFACE        *ApTest
  )
/*++

Routine Description:

  Free an application test interface.

--*/
{
  //
  // Check parameters
  //
  if (ApTest == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of application test interface
  //
  if (ApTest->Name != NULL) {
    tBS->FreePool (ApTest->Name);
    ApTest->Name = NULL;
  }

  if (ApTest->Description != NULL) {
    tBS->FreePool (ApTest->Description);
    ApTest->Description = NULL;
  }

  //
  // Free the application test interface itself
  //
  tBS->FreePool (ApTest);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadApTestEntryList (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT EFI_AP_TEST_ENTRY           **ApEntryList
  )
/*++

Routine Description:

  Load an application test entry list.

--*/
{
  EFI_STATUS          Status;
  UINT32              Index;
  UINT32              NumberOfApEntries;
  EFI_AP_TEST_ENTRY   *TempApEntryList;
  EFI_AP_TEST_ENTRY   *Last;
  EFI_AP_TEST_ENTRY   *ApEntry;

  //
  // Check parameter
  //
  if (ApEntryList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the application test entry list
  //
  TempApEntryList = NULL;
  Last            = NULL;

  //
  // Get the number of application test entries
  //
  Status = ApTestEntryGetOrderNum (
             IniFile,
             &NumberOfApEntries
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get order number - %r", Status));
    return Status;
  }

  //
  // Walk through all test entries
  //
  for (Index = 0; Index < NumberOfApEntries; Index ++) {
    //
    // Load a single application test entry
    //
    Status = LoadSingleApTestEntry (
               IniFile,
               Index,
               &ApEntry
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load AP test entry (#%d) - %r", Index, Status));
      continue;
    }

    //
    // Add this test entry into the test entry list
    //
    if (Last == NULL) {
      TempApEntryList = ApEntry;
      Last            = ApEntry;
    } else {
      Last->Next      = ApEntry;
      Last            = ApEntry;
    }
  }

  //
  // At least one test entry is required for an application test
  //
  if (TempApEntryList == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"No AP test entry"));
    return EFI_UNSUPPORTED;
  }

  //
  // Done
  //
  *ApEntryList = TempApEntryList;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeApTestEntryList (
  IN EFI_AP_TEST_ENTRY            *ApEntryList
  )
/*++

Routine Description:

  Free an application test entry list.

--*/
{
  EFI_AP_TEST_ENTRY   *Next;
  EFI_AP_TEST_ENTRY   *ApEntry;

  //
  // Check parameters
  //
  if (ApEntryList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test entries
  //
  ApEntry = ApEntryList;

  while (ApEntry != NULL) {
    Next = ApEntry->Next;
    FreeSingleApTestEntry (ApEntry);
    ApEntry = Next;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadSingleApTestEntry (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_AP_TEST_ENTRY           **ApEntry
  )
/*++

Routine Description:

  Load an application test entry.

--*/
{
  EFI_STATUS          Status;
  CHAR16              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  EFI_AP_TEST_ENTRY   *TempApEntry;

  //
  // Check parameters
  //
  if (ApEntry == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create an application test entry
  //
  Status = CreateSingleApTestEntry (&TempApEntry);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create an AP test entry - %r", Status));
    return Status;
  }

  //
  // Load the entry ID
  //
  Status = ApTestEntryGetString (IniFile, Order, L"EntryId", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without entry ID"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempApEntry->EntryId);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid entry ID"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  //
  // Load the name
  //
  Status = ApTestEntryGetString (IniFile, Order, L"Name", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without name"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  TempApEntry->Name = SctStrDuplicate (Buffer);

  //
  // Load the description
  //
  Status = ApTestEntryGetString (IniFile, Order, L"Description", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without description"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  TempApEntry->Description = SctStrDuplicate (Buffer);

  //
  // Load the test level
  //
  Status = ApTestEntryGetString (IniFile, Order, L"TestLevel", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without test level"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  Status = SctStrToTestLevel (Buffer, &TempApEntry->TestLevelSupportMap);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid test level"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  //
  // Load the support protocols
  //
  Status = ApTestEntryGetString (IniFile, Order, L"SupportProtocols", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without support protocols"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  Status = SctStrToGuidArray (Buffer, &TempApEntry->SupportProtocols);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid support protocols"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  //
  // Load the case attribute
  //
  Status = ApTestEntryGetString (IniFile, Order, L"CaseAttribute", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without case attribute"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  Status = SctStrToCaseAttribute (Buffer, &TempApEntry->CaseAttribute);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid case attribute"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  //
  // Load the parameters
  //
  Status = ApTestEntryGetString (IniFile, Order, L"Parameters", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without parameters"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  TempApEntry->Parameters = SctStrDuplicate (Buffer);

  //
  // Check error
  //
  if ((TempApEntry->Name        == NULL) ||
      (TempApEntry->Description == NULL) ||
      (TempApEntry->Parameters  == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeSingleApTestEntry (TempApEntry);
    return Status;
  }

  //
  // Done
  //
  *ApEntry = TempApEntry;
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleApTestEntry (
  OUT EFI_AP_TEST_ENTRY           **ApEntry
  )
/*++

Routine Description:

  Create an application test entry.

--*/
{
  EFI_STATUS          Status;
  EFI_AP_TEST_ENTRY   *TempApEntry;

  //
  // Check parameters
  //
  if (ApEntry == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the test entry
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_AP_TEST_ENTRY),
                 (VOID **)&TempApEntry
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempApEntry, sizeof(EFI_AP_TEST_ENTRY));

  //
  // Done
  //
  *ApEntry = TempApEntry;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeSingleApTestEntry (
  IN EFI_AP_TEST_ENTRY            *ApEntry
  )
/*++

Routine Description:

  Free an application test entry.

--*/
{
  //
  // Free the items of application test entry
  //
  if (ApEntry->Name != NULL) {
    tBS->FreePool (ApEntry->Name);
    ApEntry->Name = NULL;
  }

  if (ApEntry->Description != NULL) {
    tBS->FreePool (ApEntry->Description);
    ApEntry->Description = NULL;
  }

  if (ApEntry->SupportProtocols != NULL) {
    tBS->FreePool (ApEntry->SupportProtocols);
    ApEntry->SupportProtocols = NULL;
  }

  if (ApEntry->Parameters != NULL) {
    tBS->FreePool (ApEntry->Parameters);
    ApEntry->Parameters = NULL;
  }

  //
  // Free the application test entry itself
  //
  tBS->FreePool (ApEntry);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ApTestInterfaceGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from a test interface section.

--*/
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetString (
                    IniFile,
                    EFI_SCT_SECTION_AP_TEST_INTERFACE,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}


EFI_STATUS
ApTestInterfaceSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string into a test interface section.

--*/
{
  return IniFile->SetString (
                    IniFile,
                    EFI_SCT_SECTION_AP_TEST_INTERFACE,
                    Key,
                    Buffer
                    );
}


EFI_STATUS
ApTestEntryGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  )
/*++

Routine Description:

  Get the number of test entry sections.

--*/
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_AP_TEST_ENTRY,
                    OrderNum
                    );
}


EFI_STATUS
ApTestEntryGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from a test entry section.

--*/
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_AP_TEST_ENTRY,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}


EFI_STATUS
ApTestEntrySetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string into a test entry section.

--*/
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_AP_TEST_ENTRY,
                    Key,
                    Buffer
                    );
}
