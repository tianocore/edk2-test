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

  TestNode.c

Abstract:

  This file provides the services to manage the test nodes.

  Test Node is the basic test element in the user interface of EFI SCT. It can
  be used to describe the test category information and test case information.

--*/

#include "Sct.h"
#include "ReportSupport.h"

#define EFI_SCT_SECTION_TEST_NODE           L"Test Node"

STATIC UINT32         TempIndex = 0;
STATIC UINT32         TempLevel = 0;
//
// Internal functions declaration
//
EFI_STATUS
InsertEntryListToTestNode (
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *EntryList,
  OUT EFI_SCT_TEST_NODE           *RootNode
  );

EFI_STATUS
CreateSingleTestNode (
  OUT EFI_SCT_TEST_NODE           **TestNode
  );

EFI_STATUS
FreeSingleTestNode (
  IN EFI_SCT_TEST_NODE            *TestNode
  );

EFI_STATUS
AddRootTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_GUID                     *Guid,
  IN OUT SCT_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **RootNode
  );

EFI_STATUS
AddTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_SCT_TEST_NODE_TYPE       Type,
  IN EFI_GUID                     *Guid,
  IN OUT SCT_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  );

EFI_STATUS
FindTestNodeByName (
  IN CHAR16                       *Name,
  IN SCT_LIST_ENTRY               *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  );

EFI_STATUS
SaveSingleCaseNode (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_NODE            *TestNode,
  IN CHAR16                       *FullName
  );

EFI_STATUS
TestNodeSetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );

EFI_STATUS
WalkThroughSave (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN SCT_LIST_ENTRY               *Root,
  IN SCT_LIST_ENTRY               *Head
  );
  
//
// External functions implementation
//

EFI_STATUS
CreateTestNodes (
  OUT SCT_LIST_ENTRY              *TestNodeList
  )
/*++

Routine Description:

  Create the test node list from the category list and the test file list.

Arguments:

  TestNodeList  - Pointer to the test node list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  SCT_LIST_ENTRY          *CategoryList;
  SCT_LIST_ENTRY          *TestFileList;
  SCT_LIST_ENTRY          *Link;
  EFI_SCT_CATEGORY_DATA   *Category;
  EFI_SCT_TEST_FILE       *TestFile;
  EFI_BB_TEST_PROTOCOL    *BbTest;
  EFI_WB_TEST_PROTOCOL    *WbTest;
  EFI_AP_TEST_INTERFACE   *ApTest;
  VOID                    *EntryList;
  UINTN                   Index;
  EFI_GUID                *CategoryGuid;
  CHAR16                  *CategoryName;
  CHAR16                  *CategoryDescription;
  CHAR16                  CategoryGuidStr[EFI_SCT_GUID_LEN];
  EFI_SCT_TEST_NODE       *RootNode;

  //
  // Check parameters
  //
  if (TestNodeList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test files
  //
  CategoryList = &gFT->CategoryList;
  TestFileList = &gFT->TestFileList;

  for (Link = TestFileList->ForwardLink; Link != TestFileList; Link = Link->ForwardLink) {
    TestFile = CR (Link, EFI_SCT_TEST_FILE, Link, EFI_SCT_TEST_FILE_SIGNATURE);

    //
    // Deal with the different types of test files
    //
    switch (TestFile->Type) {
	case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
    case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
      //
      // Black-box test file
      //
      BbTest       = (EFI_BB_TEST_PROTOCOL *) TestFile->Context;
      EntryList    = BbTest->EntryList;
      CategoryGuid = &BbTest->CategoryGuid;
      break;

    case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
      //
      // White-box test file
      //
      WbTest       = (EFI_WB_TEST_PROTOCOL *) TestFile->Context;
      EntryList    = WbTest->EntryList;
      CategoryGuid = &WbTest->CategoryGuid;
      break;

    case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
    case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
      //
      // Application or script test file
      //
      ApTest       = (EFI_AP_TEST_INTERFACE *) TestFile->Context;
      EntryList    = ApTest->EntryList;
      CategoryGuid = &ApTest->CategoryGuid;
      break;

    default:
      //
      // Unsupported test file
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupport test file"));
      return EFI_UNSUPPORTED;
    }

    //
    // Skip the empty entry list
    //
    if (EntryList == NULL) {
      continue;
    }

    //
    // Find the category data
    //
    Status = FindCategoryByGuid (
               CategoryGuid,
               &Category
               );
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find category by GUID - %r", Status));
      continue;
    }

    if (Status == EFI_NOT_FOUND) {
      Index               = (UINTN) -1;
      SctGuidToStr (CategoryGuid, CategoryGuidStr);
      CategoryName        = SctPoolPrint (L"Unknown\\%s", CategoryGuidStr);
      CategoryDescription = SctStrDuplicate (L"");
    } else {
      Index               = Category->Index;
      CategoryName        = SctStrDuplicate (Category->Name);
      CategoryDescription = SctStrDuplicate (Category->Description);
    }

    if ((CategoryName        == NULL) ||
        (CategoryDescription == NULL)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Output of resources"));
      continue;
    }

    //
    // Add the root test node from the category name
    //
    Status = AddRootTestNode (
               Index,
               CategoryName,
               CategoryDescription,
               CategoryGuid,
               TestNodeList,
               &RootNode
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add root test node - %r", Status));
      tBS->FreePool (CategoryName);
      tBS->FreePool (CategoryDescription);
      continue;
    }

    //
    // Insert the test entry list into the test node list
    //
    Status = InsertEntryListToTestNode (
               TestFile->Type,
               EntryList,
               RootNode
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Insert entry list to test node - %r", Status));
      tBS->FreePool (CategoryName);
      tBS->FreePool (CategoryDescription);
      continue;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeTestNodes (
  IN SCT_LIST_ENTRY               *TestNodeList
  )
/*++

Routine Description:

  Free the test node list.

Arguments:

  TestNodeList  - Pointer to the test node list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_TEST_NODE   *TestNode;

  //
  // Check parameters
  //
  if (TestNodeList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes
  //
  while (!SctIsListEmpty (TestNodeList)) {
    TestNode = CR (TestNodeList->ForwardLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    SctRemoveEntryList (&TestNode->Link);

    if (!SctIsListEmpty (&TestNode->Child)) {
      FreeTestNodes (&TestNode->Child);
    }

    FreeSingleTestNode (TestNode);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
InsertEntryListToTestNode (
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *EntryList,
  OUT EFI_SCT_TEST_NODE           *RootNode
  )
/*++

Routine Description:

  Insert a entry list into the test node.

--*/
{
  EFI_STATUS          Status;
  EFI_BB_TEST_ENTRY   *BbEntry;
  EFI_WB_TEST_ENTRY   *WbEntry;
  EFI_AP_TEST_ENTRY   *ApEntry;
  EFI_SCT_TEST_NODE   *TestNode;

  //
  // Check parameters
  //
  if ((EntryList == NULL) || (RootNode == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Deal with different kinds of test files
  //
  switch (Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    BbEntry = (EFI_BB_TEST_ENTRY *) EntryList;

    while (BbEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 BbEntry->Name,
                 BbEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &BbEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      BbEntry = BbEntry->Next;
    }

    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    WbEntry = (EFI_WB_TEST_ENTRY *) EntryList;

    while (WbEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 WbEntry->Name,
                 WbEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &WbEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      WbEntry = WbEntry->Next;
    }

    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    ApEntry = (EFI_AP_TEST_ENTRY *) EntryList;

    while (ApEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 ApEntry->Name,
                 ApEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &ApEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      ApEntry = ApEntry->Next;
    }

    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleTestNode (
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Create a test node.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if (TestNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the test node
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_TEST_NODE),
                 (VOID **) &TempTestNode
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempTestNode, sizeof(EFI_SCT_TEST_NODE));

  //
  // Initiailize the items of test node
  //
  TempTestNode->Signature = EFI_SCT_TEST_NODE_SIGNATURE;
  TempTestNode->Revision  = EFI_SCT_TEST_NODE_REVISION;

  SctInitializeListHead (&TempTestNode->Child);

  //
  // Done
  //
  *TestNode = TempTestNode;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeSingleTestNode (
  IN EFI_SCT_TEST_NODE            *TestNode
  )
/*++

Routine Description:

  Free a test node.

--*/
{
  //
  // Check parameters
  //
  if (TestNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of test node
  //
  if (TestNode->Name != NULL) {
    tBS->FreePool (TestNode->Name);
    TestNode->Name = NULL;
  }

  if (TestNode->Description != NULL) {
    tBS->FreePool (TestNode->Description);
    TestNode->Description = NULL;
  }

  //
  // Free the test node itself
  //
  tBS->FreePool (TestNode);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AddRootTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_GUID                     *Guid,
  IN OUT SCT_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **RootNode
  )
/*++

Routine Description:

  Add a root test node from the category name.

--*/
{
  EFI_STATUS          Status;
  BOOLEAN             IsEnd;
  CHAR16              *TempName;
  CHAR16              *Token;
  CHAR16              *End;
  SCT_LIST_ENTRY      *SubList;
  EFI_SCT_TEST_NODE   *TempRootNode;

  //
  // Check parameters
  //
  if ((Name         == NULL) || (Description == NULL) || (Guid == NULL) ||
      (TestNodeList == NULL) || (RootNode    == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  IsEnd    = FALSE;
  TempName = SctStrDuplicate (Name);
  Token    = TempName;
  End      = TempName;
  SubList  = TestNodeList;
  TempRootNode = NULL;

  //
  // Walk through all tokens in the name
  //
  while (!IsEnd) {
    //
    // Find the token
    //
    while ((*End != L'\0') && (*End != L'\\') && (*End != L'/')) {
      End ++;
    }

    if (*End == L'\0') {
      IsEnd = TRUE;
    } else {
      *End = L'\0';
      End ++;
    }

    if (SctStrLen (Token) == 0) {
      continue;
    }

    //
    // Find the test node
    //
    Status = FindTestNodeByName (Token, SubList, &TempRootNode);
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find node by name - %r", Status));
      break;
    }

    if (Status == EFI_NOT_FOUND) {
      if (!IsEnd) {
        Status = AddTestNode (
                   Index,
                   Token,
                   L"",
                   EFI_SCT_TEST_NODE_TYPE_CATEGORY,
                   &gEfiNullGuid,
                   SubList,
                   &TempRootNode
                   );
      } else {
        Status = AddTestNode (
                   Index,
                   Token,
                   Description,
                   EFI_SCT_TEST_NODE_TYPE_CATEGORY,
                   Guid,
                   SubList,
                   &TempRootNode
                   );
      }

      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }
    }

    //
    // Recursive
    //
    Token   = End;
    SubList = &TempRootNode->Child;
  }

  //
  // Free resources
  //
  tBS->FreePool (TempName);

  //
  // Done
  //
  *RootNode = TempRootNode;
  return EFI_SUCCESS;
}


EFI_STATUS
AddTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_SCT_TEST_NODE_TYPE       Type,
  IN EFI_GUID                     *Guid,
  IN OUT SCT_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Add a test node.

--*/
{
  EFI_STATUS          Status;
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_NODE   *Last;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if ((Name         == NULL) || (Description == NULL) || (Guid == NULL) ||
      (TestNodeList == NULL) || (TestNode    == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a test node
  //
  Status = CreateSingleTestNode (&TempTestNode);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test node - %r", Status));
    return Status;
  }

  //
  // Set the items of test node
  //
  TempTestNode->Index       = Index;
  TempTestNode->Name        = SctStrDuplicate (Name);
  TempTestNode->Description = SctStrDuplicate (Description);
  TempTestNode->Type        = Type;
  SctCopyMem (&TempTestNode->Guid, Guid, sizeof(EFI_GUID));

  //
  // Add the test node into the test node list
  //
  for (Link = TestNodeList->ForwardLink; Link != TestNodeList; Link = Link->ForwardLink) {
    Last = CR (Link, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    if (Last->Index > Index) {
      break;
    }

    if ((Last->Index == Index) && (SctStriCmp (Last->Name, Name) > 0)) {
      break;
    }
  }

  SctInsertTailList (Link, &TempTestNode->Link);

  //
  // Done
  //
  *TestNode = TempTestNode;
  return EFI_SUCCESS;
}


EFI_STATUS
FindTestNodeByName (
  IN CHAR16                       *Name,
  IN SCT_LIST_ENTRY               *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Seach a test node based on the name.

--*/
{
  SCT_LIST_ENTRY      *Link;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if ((Name == NULL) || (TestNodeList == NULL) || (TestNode == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes on one layer
  //
  for (Link = TestNodeList->ForwardLink; Link != TestNodeList; Link = Link->ForwardLink) {
    TempTestNode = CR (Link, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    if (SctStriCmp (TempTestNode->Name, Name) == 0) {
      //
      // Got it!
      //
      *TestNode = TempTestNode;
      return EFI_SUCCESS;
    }
  }

  //
  // Not found
  //
  return EFI_NOT_FOUND;
}

EFI_STATUS
SaveCaseTree (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN SCT_LIST_ENTRY               *Root
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
  EFI_INI_FILE_HANDLE   IniFile;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (Root == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Save test cases into <%s>", FileName));

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
    // Not exist, create the file
    //
    Status = gFT->TplProtocol->EfiIniCreate (
                                 gFT->TplProtocol,
                                 DevicePath,
                                 FileName,
                                 &IniFile
                                 );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test case file - %r", Status));
      return Status;
    }
  }

  //
  // Remove the original test cases
  //
  Status = IniFile->RmSection (
                      IniFile,
                      EFI_SCT_SECTION_TEST_NODE
                      );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove section - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all test case nodes layer by layer
  //
  WalkThroughSave (IniFile, Root, NULL);

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
GenerateCaseTreeFile(
  VOID
  )
{
  EFI_STATUS                       Status;
  CHAR16                           *FileName;

  Status = DoPreOperationAll ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation ALL - %r", Status));
    return Status;
  }

  //
  // Prepare CaseTree file for test case sychronization with EMS
  //
  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_SYNC_FILE_CASE_TREE
               );
  if (FileName == NULL) {
    EFI_ENTS_DEBUG(( EFI_ENTS_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the test nodes
  //
  Status = SaveCaseTree (
             gFT->DevicePath,
             FileName,
             &gFT->TestNodeList
             );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG(( EFI_ENTS_D_ERROR, L"Save cases tree - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }
    
  tBS->FreePool (FileName);
  return EFI_SUCCESS;
}

EFI_STATUS
SaveSingleCaseNode (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN EFI_SCT_TEST_NODE            *TestNode,
  IN CHAR16                       *FullName
  )
/*++

Routine Description:

  Save a test case node.

--*/
{
  EFI_STATUS  Status;
  CHAR16      Buffer[EFI_SCT_MAX_BUFFER_SIZE];

  //
  // Check parameters
  //
  if (TestNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Save revision
  //
  Status = SctShortToHexStr (TestNode->Revision, Buffer);
  if (!EFI_ERROR (Status)) {
    TestNodeSetString (IniFile, Order, L"Revision", Buffer);
  }

  //
  // Save the GUID
  //
  Status = SctGuidToStr (&TestNode->Guid, Buffer);
  if (!EFI_ERROR (Status)) {
    TestNodeSetString (IniFile, Order, L"Guid", Buffer);
  }

  //
  // Save the name
  //
  TestNodeSetString (IniFile, Order, L"Name", FullName);

  //
  // Save the order
  //
  Status = SctShortToHexStr (TestNode->Type, Buffer);
  if (!EFI_ERROR (Status)) {
    TestNodeSetString (IniFile, Order, L"Type", Buffer);
  }

  //
  // Save the name
  //
  TestNodeSetString (IniFile, Order, L"Description", TestNode->Description);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
TestNodeSetString (
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
                    EFI_SCT_SECTION_TEST_NODE,
                    Key,
                    Buffer
                    );
}


EFI_STATUS
WalkThroughSave (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN SCT_LIST_ENTRY               *Root,
  IN SCT_LIST_ENTRY               *Head
  )
/*++

Routine Description:

  Save a test case node.

--*/
{
  EFI_STATUS            Status;
  UINT32                LoopIndex;
  EFI_SCT_TEST_NODE     *TempNode;
  SCT_LIST_ENTRY        *TempLink;
  SCT_LIST_ENTRY        *TempLink1;
  STATIC CHAR16         PathName[10][1024];
  CHAR16                TempFullName[1024];
  
  Status = EFI_SUCCESS;
  SctStrCpy (TempFullName, L"");

  if (Root == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Head == NULL) {
    Head = Root;
  }
  TempLink = Root->ForwardLink;

  //
  // Get current node.
  //
  if (TempLink != Head) {
    TempNode = CR (TempLink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);
    
    if (TempNode->Name != NULL) {
      //
      // Record the node path
      //
      for (LoopIndex = 0; LoopIndex < TempLevel; LoopIndex++) {
        SctStrCat (TempFullName, PathName[LoopIndex]);
        SctStrCat (TempFullName, L"\\");
      }
      
      SctStrCat (TempFullName, TempNode->Name);
      
      //
      // Save a single test case node
      //
      Status = SaveSingleCaseNode (
                 IniFile,
                 TempIndex,
                 TempNode,
                 TempFullName
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Save a test case node (#%d) - %r", TempIndex, Status));
        return Status;
      }
      TempIndex++;
            
      TempLink1 = &TempNode->Child;
      
      //
      // Recusion on vertical node (right node)
      //
      if (!SctIsListEmpty (TempLink1)){
        SctCopyMem (PathName[TempLevel], TempNode->Name, SctStrSize (TempNode->Name));
        TempLevel++;
        
        Status = WalkThroughSave (
                   IniFile,
                   TempLink1,
                   NULL
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"WalkThroughSave case node (#%d) - %r", TempIndex, Status));
          return Status;
        }
        
        TempLevel--;
      }    

      //
      // Recusion on pararrel node (left node)
      //
      Status = WalkThroughSave (
                 IniFile,
                 TempLink,
                 Head
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"WalkThroughSave case node (#%d) - %r", TempIndex, Status));
        return Status;
      }
    }
  }
  
  return Status;
}
