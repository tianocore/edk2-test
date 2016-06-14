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

  Category.c

Abstract:

  This file provides the services to manage the category data.

--*/

#include "Sct.h"

//
// Internal definitions
//

#define EFI_SCT_SECTION_CATEGORY            L"Category Data"

//
// Internal functions declaration
//

EFI_STATUS
InsertSingleCategoryData (
  IN OUT SCT_LIST_ENTRY           *CategoryList,
  IN EFI_SCT_CATEGORY_DATA        *Category
  );

EFI_STATUS
LoadSingleCategoryData (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_CATEGORY_DATA       **Category
  );

EFI_STATUS
CreateSingleCategoryData (
  OUT EFI_SCT_CATEGORY_DATA       **Category
  );

EFI_STATUS
FreeSingleCategoryData (
  IN EFI_SCT_CATEGORY_DATA        *Category
  );

EFI_STATUS
CategoryGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  );

EFI_STATUS
CategoryGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  );

EFI_STATUS
CategorySetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  );


//
// External functions implementation
//

EFI_STATUS
LoadCategoryData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *CategoryList
  )
/*++

Routine Description:

  Load the category data list from a file.

Arguments:

  DevicePath    - Device path of the file.
  FileName      - Name of the file.
  CategoryList  - Pointer to the category data list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  UINT32                  Index;
  UINT32                  NumberOfCategories;
  EFI_INI_FILE_HANDLE     IniFile;
  EFI_SCT_CATEGORY_DATA   *Category;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (CategoryList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load category data from <%s>", FileName));

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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open category file - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // If the category file does not exist, use the empty setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Category file doesn't exist"));
    return EFI_SUCCESS;
  }

  //
  // Get the number of categories
  //
  Status = CategoryGetOrderNum (
             IniFile,
             &NumberOfCategories
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get order number - %r", Status));
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, IniFile);
    return Status;
  }

  //
  // Walk through all categories
  //
  for (Index = 0; Index < NumberOfCategories; Index ++) {
    //
    // Load a single category data
    //
    Status = LoadSingleCategoryData (
               IniFile,
               Index,
               &Category
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load a category (#%d) - %r", Index, Status));
      continue;
    }

    //
    // Add this category data into the list
    //
    InsertSingleCategoryData (CategoryList, Category);
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
FreeCategoryData (
  IN SCT_LIST_ENTRY               *CategoryList
  )
/*++

Routine Description:

  Free the category data list.

Arguments:

  CategoryList  - Pointer to the category data list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_CATEGORY_DATA   *Category;

  //
  // Check parameters
  //
  if (CategoryList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all categories
  //
  while (!SctIsListEmpty (CategoryList)) {
    Category = CR (CategoryList->ForwardLink, EFI_SCT_CATEGORY_DATA, Link, EFI_SCT_CATEGORY_DATA_SIGNATURE);

    SctRemoveEntryList (&Category->Link);
    FreeSingleCategoryData (Category);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FindCategoryByGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_CATEGORY_DATA       **Category
  )
/*++

Routine Description:

  Find the category data based on the GUID.

Arguments:

  Guid          - Specifies the GUID to search by.
  Category      - The category data is returned.

Returns:

  EFI_SUCCESS   - Successfully.
  EFI_NOT_FOUND - Not found.
  Other value   - Something failed.

--*/
{
  SCT_LIST_ENTRY          *CategoryList;
  SCT_LIST_ENTRY          *Link;
  EFI_SCT_CATEGORY_DATA   *TempCategory;

  //
  // Check parameters
  //
  if ((Guid == NULL) || (Category == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  CategoryList = &gFT->CategoryList;

  //
  // Walk through all categories
  //
  for (Link = CategoryList->ForwardLink; Link != CategoryList; Link = Link->ForwardLink) {
    TempCategory = CR (Link, EFI_SCT_CATEGORY_DATA, Link, EFI_SCT_CATEGORY_DATA_SIGNATURE);

    if (SctCompareGuid (Guid, &TempCategory->CategoryGuid) == 0) {
      *Category = TempCategory;
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
InsertSingleCategoryData (
  IN OUT SCT_LIST_ENTRY           *CategoryList,
  IN EFI_SCT_CATEGORY_DATA        *Category
  )
/*++

Routine Description:

  Insert a category data into list.

--*/
{
  SCT_LIST_ENTRY          *Link;
  EFI_SCT_CATEGORY_DATA   *OldCategory;

  //
  // Check whether there are duplicate category data. If yes, remove the old
  // data
  //
  for (Link = CategoryList->ForwardLink; Link != CategoryList; Link = Link->ForwardLink) {
    OldCategory = CR (Link, EFI_SCT_CATEGORY_DATA, Link, EFI_SCT_CATEGORY_DATA_SIGNATURE);

    if (SctCompareGuid (&OldCategory->CategoryGuid, &Category->CategoryGuid) == 0) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Found duplicate category data (GUID = %g)", &Category->CategoryGuid));

      SctRemoveEntryList (&OldCategory->Link);
      FreeSingleCategoryData (OldCategory);

      break;
    }
  }

  //
  // Add this category data into the list
  //
  SctInsertTailList (CategoryList, &Category->Link);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
LoadSingleCategoryData (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  OUT EFI_SCT_CATEGORY_DATA       **Category
  )
/*++

Routine Description:

  Load a category data.

--*/
{
  EFI_STATUS              Status;
  CHAR16                  Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINT32                  Revision;
  EFI_SCT_CATEGORY_DATA   *TempCategory;

  //
  // Check parameters
  //
  if (Category == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a category data
  //
  Status = CreateSingleCategoryData (&TempCategory);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a category - %r", Status));
    return Status;
  }

  //
  // Initialize the items of category data
  //
  TempCategory->Index = Order;

  //
  // Check the revision info
  //
  Status = CategoryGetString (IniFile, Order, L"Revision", Buffer);
  if (EFI_ERROR (Status)) {
    //
    // Without the revision info, ignore this category data
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without revision"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  Status = SctHexStrToShort (Buffer, &Revision);
  if (EFI_ERROR (Status) || (Revision != TempCategory->Revision)) {
    //
    // With unsupported revision info, ignore this category data
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid revision"));
    FreeSingleCategoryData (TempCategory);
    return EFI_UNSUPPORTED;
  }

  //
  // Load the category GUID
  //
  Status = CategoryGetString (IniFile, Order, L"CategoryGuid", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without category GUID"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempCategory->CategoryGuid);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid category GUID"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  //
  // Load the interface GUID
  //
  Status = CategoryGetString (IniFile, Order, L"InterfaceGuid", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without interface GUID"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  Status = SctStrToGuid (Buffer, &TempCategory->InterfaceGuid);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Invalid interface GUID"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  //
  // Load the name
  //
  Status = CategoryGetString (IniFile, Order, L"Name", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without name"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  TempCategory->Name = SctStrDuplicate (Buffer);

  //
  // Load the description
  //
  Status = CategoryGetString (IniFile, Order, L"Description", Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Without description"));
    FreeSingleCategoryData (TempCategory);
    return Status;
  }

  TempCategory->Description = SctStrDuplicate (Buffer);

  //
  // Check error
  //
  if ((TempCategory->Name        == NULL) ||
      (TempCategory->Description == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeSingleCategoryData (TempCategory);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  *Category = TempCategory;
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleCategoryData (
  OUT EFI_SCT_CATEGORY_DATA       **Category
  )
/*++

Routine Description:

  Create a category data.

--*/
{
  EFI_STATUS              Status;
  EFI_SCT_CATEGORY_DATA   *TempCategory;

  //
  // Check parameters
  //
  if (Category == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the category data
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_CATEGORY_DATA),
                 (VOID **)&TempCategory
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (TempCategory, sizeof(EFI_SCT_CATEGORY_DATA));

  //
  // Initialize the items of category data
  //
  TempCategory->Signature = EFI_SCT_CATEGORY_DATA_SIGNATURE;
  TempCategory->Revision  = EFI_SCT_CATEGORY_DATA_REVISION;

  //
  // Done
  //
  *Category = TempCategory;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeSingleCategoryData (
  IN EFI_SCT_CATEGORY_DATA        *Category
  )
/*++

Routine Description:

  Free a category data.

--*/
{
  //
  // Check parameters
  //
  if (Category == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of category data
  //
  if (Category->Name != NULL) {
    tBS->FreePool (Category->Name);
    Category->Name = NULL;
  }

  if (Category->Description != NULL) {
    tBS->FreePool (Category->Description);
    Category->Description = NULL;
  }

  //
  // Free the category data itself
  //
  tBS->FreePool (Category);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CategoryGetOrderNum (
  IN EFI_INI_FILE_HANDLE          IniFile,
  OUT UINT32                      *OrderNum
  )
/*++

Routine Description:

  Get the number of category sections.

--*/
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_CATEGORY,
                    OrderNum
                    );
}


EFI_STATUS
CategoryGetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  OUT CHAR16                      *Buffer
  )
/*++

Routine Description:

  Get a string from the category file.

--*/
{
  UINT32      BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_CATEGORY,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}


EFI_STATUS
CategorySetString (
  IN EFI_INI_FILE_HANDLE          IniFile,
  IN UINT32                       Order,
  IN CHAR16                       *Key,
  IN CHAR16                       *Buffer
  )
/*++

Routine Description:

  Set a string to the category file.

--*/
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_CATEGORY,
                    Key,
                    Buffer
                    );
}
