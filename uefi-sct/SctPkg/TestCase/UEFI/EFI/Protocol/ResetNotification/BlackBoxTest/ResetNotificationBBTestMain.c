/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ResetNotificationBBTestMain.c

Abstract:

  Test Driver of Reset Notification Protocol

--*/


#include "ResetNotificationBBTestMain.h"

#define EFI_RESET_NOTIFICATION_TEST_GUID \
{ 0x9da34ae0, 0xeaf9, 0x4bbf, { 0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe } }

//
// Global variables
//
EFI_HANDLE mImageHandle;

CHAR16     *VariableName = L"ResetNotificationTest";
EFI_GUID   gTestVendorGuid = TEST_VENDOR_GUID;
UINT32     Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_RESET_NOTIFICATION_PROTOCOL_TEST_REVISION,
  EFI_RESET_NOTIFICATION_TEST_GUID,
  L"Reset Notification Protocol Test",
  L"UEFI Reset Notification Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0101,
    L"RegisterResetNotifyFunction",
    L"Function auto test for Reset Notification Protocol RegisterResetNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterResetNotifyFunctionTest
  },

  {
    EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0102,
    L"UnregisterResetNotifyFunction",
    L"Function auto test for Reset Notification Protocol UnregisterResetNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterResetNotifyFunctionTest
  },
    
  {
    EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0201,
    L"RegisterResetNotifyConformance",
    L"Conformance auto test for Reset Notification Protocol RegisterResetNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterResetNotifyConformanceTest
  },

  {
    EFI_RESET_NOTIFICATION_PROTOCOL_TEST_ENTRY_GUID0202,
    L"UnregisterResetNotifyConformance",
    L"Conformance auto test for Reset Notification Protocol UnregisterResetNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterResetNotifyConformanceTest
  },

 0
};


EFI_STATUS
EFIAPI
InitializeResetNotificationBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
             &ImageHandle,
             &gBBTestProtocolField,
             gBBTestEntryField,
             UnloadResetNotificationBBTest,
             &gBBTestProtocolInterface
             );

}


EFI_STATUS
UnloadResetNotificationBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param RecoveryLib    A pointer to Test Recovery Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  *StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test recovery support library interface
  //
  *RecoveryLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **) RecoveryLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test logging support library interface
  //
  *LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) LoggingLib
                   );
  // Test logging support library is optional

  //
  // Done
  //
  return EFI_SUCCESS;
}

VOID
EFIAPI
TestOnReset (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  EFI_STATUS        Status;

  UINTN             Index;
  UINT8             Data[MAX_BUFFER_SIZE];

  for (Index = 0; Index < 10; Index++) {
    Data[Index] = (UINT8)Index;
  }

  Status = gtRT->SetVariable (
                     VariableName,                // VariableName
                     &gTestVendorGuid,            // VendorGuid
                     Attributes,                  // Attributes
                     10,                          // DataSize
                     Data                         // Data
                     );  

}

