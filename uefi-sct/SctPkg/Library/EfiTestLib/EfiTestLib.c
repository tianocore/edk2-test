/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EfiTestLib.c

Abstract:

  EFI common test library.

--*/
#include "Efi.h"
#include <Library/EfiTestLib.h>
#include "SctLib.h"
#include EFI_GUID_DEFINITION (DxeServices)

//
// Global IDs
//

EFI_GUID gTestGenericFailureGuid = TEST_GENERIC_FAILURE_GUID;
EFI_GUID gTestDummyGuid          = TEST_DUMMY_GUID;

//
// Global variables
//

EFI_SYSTEM_TABLE          *gtST = NULL;
EFI_BOOT_SERVICES         *gtBS = NULL;
EFI_RUNTIME_SERVICES      *gtRT = NULL;
EFI_DXE_SERVICES          *gtDS = NULL;

//
// Module variables
//

BOOLEAN     mTestLibInitialized = FALSE;


//
// Internal functions declaration
//

STATIC
EFI_BB_TEST_PROTOCOL *
BuildBBTestInterface (
  IN UINT64                 TestRevision,
  IN EFI_GUID               *CategoryGuid,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description
  );

STATIC
EFI_STATUS
AddBBTestEntry (
  IN EFI_BB_TEST_PROTOCOL   *BBTestProtocolInterface,
  IN EFI_GUID               EntryId,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description,
  IN EFI_TEST_LEVEL         TestLevelSupportMap,
  IN EFI_GUID               *SupportProtocols,
  IN UINT32                 CaseAttribute,
  IN EFI_BB_ENTRY_POINT     EntryPoint
  );

STATIC
EFI_WB_TEST_PROTOCOL *
BuildWBTestInterface (
  IN UINT64                 TestRevision,
  IN EFI_GUID               *CategoryGuid,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description
  );

STATIC
EFI_STATUS
AddWBTestEntry (
  IN EFI_WB_TEST_PROTOCOL   *WBTestProtocolInterface,
  IN EFI_GUID               EntryId,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description,
  IN EFI_TEST_LEVEL         TestLevelSupportMap,
  IN EFI_GUID               *SupportProtocols,
  IN UINT32                 CaseAttribute,
  IN EFI_WB_ENTRY_POINT     EntryPoint
  );

BOOLEAN
CheckBBTestCanRunAndRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN CHAR16                              *AssertionString,
  IN CHAR8                               *FILE,
  IN UINT32                              LINE
  );

//
// External functions implementation
//

EFI_STATUS
EFIAPI
EfiInitializeTestLib (
  IN  EFI_HANDLE                  ImageHandle,
  IN  EFI_SYSTEM_TABLE            *SystemTable
  )
{
  UINTN       Index;

  if (!mTestLibInitialized) {
    mTestLibInitialized = TRUE;

    gtST = SystemTable;
    gtBS = gtST->BootServices;
    gtRT = gtST->RuntimeServices;

    //
    // Search DXE services table.
    //
    for (Index = 0; Index < gtST->NumberOfTableEntries; Index++) {
      if (SctCompareGuid (&gEfiDxeServicesTableGuid, &gtST->ConfigurationTable[Index].VendorGuid) == 0) {
        gtDS = gtST->ConfigurationTable[Index].VendorTable;
        break;
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiInitAndInstallBBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_BB_TEST_PROTOCOL_FIELD  *BBTestProtocolField,
  IN  EFI_BB_TEST_ENTRY_FIELD     *BBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_BB_TEST_PROTOCOL        **BBTestProtocolInterface
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_BB_TEST_ENTRY_FIELD     *EntryField;

  //
  // Check parameters
  //
  if ((Handle                  == NULL) ||
      (BBTestProtocolField     == NULL) ||
      (BBTestEntryField        == NULL) ||
      (BBTestProtocolInterface == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Set the unload function
  //
  Status = gtBS->HandleProtocol (
                   *Handle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **)&LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return EFI_INVALID_PARAMETER;
  }

  LoadedImage->Unload = UnloadFunction;

  //
  // Build the test protocol interface
  //
  *BBTestProtocolInterface = BuildBBTestInterface (
                               BBTestProtocolField->TestRevision,
                               &BBTestProtocolField->CategoryGuid,
                               BBTestProtocolField->Name,
                               BBTestProtocolField->Description
                               );
  if (*BBTestProtocolInterface == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Add all test entries
  //
  EntryField = BBTestEntryField;

  while (SctCompareGuid (&EntryField->EntryId, &gEfiNullGuid) != 0) {
    Status = AddBBTestEntry (
               *BBTestProtocolInterface,
               EntryField->EntryId,
               EntryField->Name,
               EntryField->Description,
               EntryField->TestLevelSupportMap,
               EntryField->SupportProtocols,
               EntryField->CaseAttribute,
               EntryField->EntryPoint
               );
    if (EFI_ERROR (Status)) {
      EfiUninstallAndFreeBBTestInterface (Handle, *BBTestProtocolInterface);
      return Status;
    }

    EntryField ++;
  }

  //
  // Install the test protocol interface
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   Handle,
                   &gEfiBbTestGuid,
                   *BBTestProtocolInterface,
                   NULL
                   );
  if (EFI_ERROR (Status)) {
    EfiUninstallAndFreeBBTestInterface (Handle, *BBTestProtocolInterface);
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiInitAndInstallIHVBBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_BB_TEST_PROTOCOL_FIELD  *BBTestProtocolField,
  IN  EFI_BB_TEST_ENTRY_FIELD     *BBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_BB_TEST_PROTOCOL        **BBTestProtocolInterface
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_BB_TEST_ENTRY_FIELD     *EntryField;

  //
  // Check parameters
  //
  if ((Handle                  == NULL) ||
      (BBTestProtocolField     == NULL) ||
      (BBTestEntryField        == NULL) ||
      (BBTestProtocolInterface == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Set the unload function
  //
  Status = gtBS->HandleProtocol (
                   *Handle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **)&LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return EFI_INVALID_PARAMETER;
  }

  LoadedImage->Unload = UnloadFunction;

  //
  // Build the test protocol interface
  //
  *BBTestProtocolInterface = BuildBBTestInterface (
                               BBTestProtocolField->TestRevision,
                               &BBTestProtocolField->CategoryGuid,
                               BBTestProtocolField->Name,
                               BBTestProtocolField->Description
                               );
  if (*BBTestProtocolInterface == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Add all test entries
  //
  EntryField = BBTestEntryField;

  while (SctCompareGuid (&EntryField->EntryId, &gEfiNullGuid) != 0) {
    Status = AddBBTestEntry (
               *BBTestProtocolInterface,
               EntryField->EntryId,
               EntryField->Name,
               EntryField->Description,
               EntryField->TestLevelSupportMap,
               EntryField->SupportProtocols,
               EntryField->CaseAttribute,
               EntryField->EntryPoint
               );
    if (EFI_ERROR (Status)) {
      EfiUninstallAndFreeBBTestInterface (Handle, *BBTestProtocolInterface);
      return Status;
    }

    EntryField ++;
  }

  //
  // Install the test protocol interface
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   Handle,
                   &gEfiIHVBbTestGuid,
                   *BBTestProtocolInterface,
                   NULL
                   );
  if (EFI_ERROR (Status)) {
    EfiUninstallAndFreeBBTestInterface (Handle, *BBTestProtocolInterface);
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiUninstallAndFreeBBTestInterface (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_BB_TEST_PROTOCOL        *BBTestProtocolInterface
  )
{
  EFI_BB_TEST_ENTRY   *CurrentEntry;
  EFI_BB_TEST_ENTRY   *NextEntry;

  //
  // Check parameters
  //
  if (BBTestProtocolInterface == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Uninstall the test protocol interface
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &gEfiBbTestGuid,
          BBTestProtocolInterface,
          NULL
          );

  //
  // Free all test entries
  //
  CurrentEntry = BBTestProtocolInterface->EntryList;

  while (CurrentEntry != NULL) {
    NextEntry = CurrentEntry->Next;

    gtBS->FreePool (CurrentEntry->SupportProtocols);
    gtBS->FreePool (CurrentEntry);

    CurrentEntry = NextEntry;
  }

  //
  // Free the test protocol interface
  //
  gtBS->FreePool (BBTestProtocolInterface);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiUninstallAndFreeIHVBBTestInterface (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_BB_TEST_PROTOCOL        *BBTestProtocolInterface
  )
{
  EFI_BB_TEST_ENTRY   *CurrentEntry;
  EFI_BB_TEST_ENTRY   *NextEntry;

  //
  // Check parameters
  //
  if (BBTestProtocolInterface == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Uninstall the test protocol interface
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &gEfiIHVBbTestGuid,
          BBTestProtocolInterface,
          NULL
          );

  //
  // Free all test entries
  //
  CurrentEntry = BBTestProtocolInterface->EntryList;

  while (CurrentEntry != NULL) {
    NextEntry = CurrentEntry->Next;

    gtBS->FreePool (CurrentEntry->SupportProtocols);
    gtBS->FreePool (CurrentEntry);

    CurrentEntry = NextEntry;
  }

  //
  // Free the test protocol interface
  //
  gtBS->FreePool (BBTestProtocolInterface);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiInitAndInstallWBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_WB_TEST_PROTOCOL_FIELD  *WBTestProtocolField,
  IN  EFI_WB_TEST_ENTRY_FIELD     *WBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_WB_TEST_PROTOCOL        **WBTestProtocolInterface
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_WB_TEST_ENTRY_FIELD     *EntryField;

  //
  // Check parameters
  //
  if ((Handle                  == NULL) ||
      (WBTestProtocolField     == NULL) ||
      (WBTestEntryField        == NULL) ||
      (WBTestProtocolInterface == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Set the unload function
  //
  Status = gtBS->HandleProtocol (
                   *Handle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **)&LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return EFI_INVALID_PARAMETER;
  }

  LoadedImage->Unload = UnloadFunction;

  //
  // Build the test protocol interface
  //
  *WBTestProtocolInterface = BuildWBTestInterface (
                               WBTestProtocolField->TestRevision,
                               &WBTestProtocolField->CategoryGuid,
                               WBTestProtocolField->Name,
                               WBTestProtocolField->Description
                               );
  if (*WBTestProtocolInterface == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Add all test entries
  //
  EntryField = WBTestEntryField;

  while (SctCompareGuid (&EntryField->EntryId, &gEfiNullGuid) != 0) {
    Status = AddWBTestEntry (
               *WBTestProtocolInterface,
               EntryField->EntryId,
               EntryField->Name,
               EntryField->Description,
               EntryField->TestLevelSupportMap,
               EntryField->SupportProtocols,
               EntryField->CaseAttribute,
               EntryField->EntryPoint
               );
    if (EFI_ERROR (Status)) {
      EfiUninstallAndFreeWBTestInterface (Handle, *WBTestProtocolInterface);
      return Status;
    }

    EntryField ++;
  }

  //
  // Install the test protocol interface
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   Handle,
                   &gEfiWbTestGuid,
                   *WBTestProtocolInterface,
                   NULL
                   );
  if (EFI_ERROR (Status)) {
    EfiUninstallAndFreeWBTestInterface (Handle, *WBTestProtocolInterface);
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EfiUninstallAndFreeWBTestInterface (
  IN EFI_HANDLE                   Handle,
  IN EFI_WB_TEST_PROTOCOL         *WBTestProtocolInterface
  )
{
  EFI_WB_TEST_ENTRY   *CurrentEntry;
  EFI_WB_TEST_ENTRY   *NextEntry;

  //
  // Check parameters
  //
  if (WBTestProtocolInterface == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Uninstall the test protocol interface
  //
  gtBS->UninstallMultipleProtocolInterfaces (
          Handle,
          &gEfiWbTestGuid, WBTestProtocolInterface,
          NULL
          );

  //
  // Free all test entries
  //
  CurrentEntry = WBTestProtocolInterface->EntryList;

  while (CurrentEntry != NULL) {
    NextEntry = CurrentEntry->Next;

    gtBS->FreePool (CurrentEntry->SupportProtocols);
    gtBS->FreePool (CurrentEntry);

    CurrentEntry = NextEntry;
  }

  //
  // Free the test protocol interface
  //
  gtBS->FreePool (WBTestProtocolInterface);

  //
  // Done
  //
  return EFI_SUCCESS;
}

//
// Internal functions implementation
//

STATIC
EFI_BB_TEST_PROTOCOL *
BuildBBTestInterface (
  IN UINT64                 TestRevision,
  IN EFI_GUID               *CategoryGuid,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description
  )
{
  EFI_STATUS            Status;
  EFI_BB_TEST_PROTOCOL  *BBTest;

  //
  // Allocate memory for the test protocol interface
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_BB_TEST_PROTOCOL),
                  (VOID **) &BBTest
                   );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //
  // Set the items of the test protocol interface
  //
  gtBS->CopyMem (&BBTest->CategoryGuid, CategoryGuid, sizeof(EFI_GUID));

  BBTest->TestRevision = TestRevision;
  BBTest->Name         = Name;
  BBTest->Description  = Description;

  BBTest->EntryList    = NULL;

  //
  // Done
  //
  return BBTest;
}

STATIC
EFI_STATUS
AddBBTestEntry (
  IN EFI_BB_TEST_PROTOCOL   *BBTestProtocolInterface,
  IN EFI_GUID               EntryId,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description,
  IN EFI_TEST_LEVEL         TestLevelSupportMap,
  IN EFI_GUID               *SupportProtocols,
  IN UINT32                 CaseAttribute,
  IN EFI_BB_ENTRY_POINT     EntryPoint
  )
{
  EFI_STATUS          Status;
  EFI_BB_TEST_ENTRY   *BBTestEntry;
  EFI_BB_TEST_ENTRY   *CurrentEntry;
  UINT32              GuidCount;
  EFI_GUID            *Guid;

  //
  // Allocate memory for the test entry
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_BB_TEST_ENTRY),
                   (VOID **)&BBTestEntry
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Count the test support protocols
  //
  GuidCount = 0;
  Guid      = SupportProtocols;

  while (SctCompareGuid (Guid, &gEfiNullGuid) != 0) {
    GuidCount ++;
    Guid ++;
  }

  //
  // Allocate memory for the support protocol GUIDs
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_GUID) * (GuidCount + 1),
                   (VOID **)&BBTestEntry->SupportProtocols
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (BBTestEntry);
    return Status;
  }

  gtBS->CopyMem (
          BBTestEntry->SupportProtocols,
          SupportProtocols,
          sizeof(EFI_GUID) * (GuidCount + 1)
          );

  //
  // Set the items of the test entry
  //
  gtBS->CopyMem (&BBTestEntry->EntryId, &EntryId, sizeof(EFI_GUID));

  BBTestEntry->Name                = Name;
  BBTestEntry->Description         = Description;
  BBTestEntry->TestLevelSupportMap = TestLevelSupportMap;
  BBTestEntry->CaseAttribute       = CaseAttribute;
  BBTestEntry->EntryPoint          = EntryPoint;

  BBTestEntry->Next                = NULL;

  //
  // Insert the test entry into the test protocol interface
  //
  if (BBTestProtocolInterface->EntryList == NULL) {
    BBTestProtocolInterface->EntryList = BBTestEntry;
  } else {
    CurrentEntry = BBTestProtocolInterface->EntryList;
    while (CurrentEntry->Next != NULL) {
      CurrentEntry = CurrentEntry->Next;
    }

    CurrentEntry->Next = BBTestEntry;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
EFI_WB_TEST_PROTOCOL *
BuildWBTestInterface (
  IN UINT64                 TestRevision,
  IN EFI_GUID               *CategoryGuid,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description
  )
{
  EFI_STATUS            Status;
  EFI_WB_TEST_PROTOCOL  *WBTest;

  //
  // Allocate memory for the test protocol interface
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_WB_TEST_PROTOCOL),
                   (VOID **)&WBTest
                   );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //
  // Set the items of the test protocol interface
  //
  gtBS->CopyMem (&WBTest->CategoryGuid, CategoryGuid, sizeof(EFI_GUID));

  WBTest->TestRevision = TestRevision;
  WBTest->Name         = Name;
  WBTest->Description  = Description;
  WBTest->ClientHandle = NULL;

  WBTest->EntryList    = NULL;

  //
  // Done
  //
  return WBTest;
}

STATIC
EFI_STATUS
AddWBTestEntry (
  IN EFI_WB_TEST_PROTOCOL   *WBTestProtocolInterface,
  IN EFI_GUID               EntryId,
  IN CHAR16                 *Name,
  IN CHAR16                 *Description,
  IN EFI_TEST_LEVEL         TestLevelSupportMap,
  IN EFI_GUID               *SupportProtocols,
  IN UINT32                 CaseAttribute,
  IN EFI_WB_ENTRY_POINT     EntryPoint
  )
{
  EFI_STATUS          Status;
  EFI_WB_TEST_ENTRY   *WBTestEntry;
  EFI_WB_TEST_ENTRY   *CurrentEntry;
  UINT32              GuidCount;
  EFI_GUID            *Guid;

  //
  // Allocate memory for the test entry
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_WB_TEST_ENTRY),
                   (VOID **)&WBTestEntry
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Count the test support protocols
  //
  GuidCount = 0;
  Guid      = SupportProtocols;

  while (SctCompareGuid (Guid, &gEfiNullGuid) != 0) {
    GuidCount ++;
    Guid ++;
  }

  //
  // Allocate memory for the support protocol GUIDs
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_GUID) * (GuidCount + 1),
                   (VOID **)&WBTestEntry->SupportProtocols
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (WBTestEntry);
    return Status;
  }

  gtBS->CopyMem (
          WBTestEntry->SupportProtocols,
          SupportProtocols,
          sizeof(EFI_GUID) * (GuidCount + 1)
          );

  //
  // Set the items of the test entry
  //
  gtBS->CopyMem (&WBTestEntry->EntryId, &EntryId, sizeof(EFI_GUID));

  WBTestEntry->Name                = Name;
  WBTestEntry->Description         = Description;
  WBTestEntry->TestLevelSupportMap = TestLevelSupportMap;
  WBTestEntry->CaseAttribute       = CaseAttribute;
  WBTestEntry->EntryPoint          = EntryPoint;

  WBTestEntry->Next                = NULL;

  //
  // Insert the test entry into the test protocol interface
  //
  if (WBTestProtocolInterface->EntryList == NULL) {
    WBTestProtocolInterface->EntryList = WBTestEntry;
  } else {
    CurrentEntry = WBTestProtocolInterface->EntryList;
    while (CurrentEntry->Next != NULL) {
      CurrentEntry = CurrentEntry->Next;
    }

    CurrentEntry->Next = WBTestEntry;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)

BOOLEAN
CheckBBTestCanRunAndRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN CHAR16                              *AssertionString,
  IN CHAR8                               *FILE,
  IN UINT32                              LINE
  )
{
  if (gtBS->Hdr.Revision < EFI_SPECIFICATION_VERSION) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  AssertionString,
                  L"%a:%d",
                  FILE,
                  LINE
                  );
    return FALSE;
  }

  return TRUE;
}
#else

BOOLEAN
CheckBBTestCanRunAndRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN CHAR16                              *AssertionString,
  IN CHAR8                               *FILE,
  IN UINT32                              LINE
  )
{
  return TRUE;
}

#endif
