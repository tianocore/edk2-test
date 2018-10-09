/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    iScsiInitiatorNameBBTestMain.c

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec )

Revision History

--*/

#include "SctLib.h"
#include "iScsiInitiatorNameBBTestMain.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  ISCSI_INITIATOR_NAME_PROTOCOL_TEST_REVISION,
  IHV_ISCSI_INITIATOR_NAME_PROTOCOL_GUID,
  L"ISCSI Initiator Name Protocol", 
  L"UEFI ISCSI Initiator Name protocol"
};

EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    ISCSI_INITIATORNAME_PROTOCOL_GET_FUNCTION_GUID,
    L"Get_Func",
    L"Invoke Get() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetFunctionTest
  },

  {
    ISCSI_INITIATORNAME_PROTOCOL_SET_FUNCTION_GUID,
    L"Set_Func",
    L"Invoke Set() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetFunctionTest
  },

  {
    ISCSI_INITIATORNAME_PROTOCOL_GET_CONFORMANCE_GUID,
    L"Get_Conf",
    L"Test whether Get() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetConformanceTest
  },

  {
    ISCSI_INITIATORNAME_PROTOCOL_SET_CONFORMANCE_GUID,
    L"Set_Conf",
    L"Test whether Set() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetConformanceTest
  },

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestiScsiInitiatorNameProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeBBTestiScsiInitiatorName (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestiScsiInitiatorNameProtocolUnload,
           &gBBTestProtocolInterface
           );
}

EFI_STATUS
EFIAPI
BBTestiScsiInitiatorNameProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

