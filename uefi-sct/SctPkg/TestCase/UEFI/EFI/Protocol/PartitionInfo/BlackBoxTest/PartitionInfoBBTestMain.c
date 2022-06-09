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

  PartitionInfoBBTestMain.c

Abstract:

  Test Driver of Partition Info Protocol

--*/


#include "PartitionInfoBBTestMain.h"

#define EFI_PARTITION_INFO_TEST_GUID \
  {0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0}}

//
// Global variables
//
EFI_HANDLE mImageHandle;

UINT8      EnterEvent;


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_PARTITION_INFO_PROTOCOL_TEST_REVISION,
  EFI_PARTITION_INFO_TEST_GUID,
  L"Partition Info Protocol Test",
  L"UEFI Partition Info Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_PARTITION_INFO_PROTOCOL_TEST_ENTRY_GUID0101,
    L"PartitionInfoFunction",
    L"Function auto test for Partition Info Protocol",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestPartitionInfoFunctionTest
  },
 0
};


EFI_STATUS
EFIAPI
InitializePartitionInfoBBTest (
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
             UnloadPartitionInfoBBTest,
             &gBBTestProtocolInterface
             );

}


EFI_STATUS
EFIAPI
UnloadPartitionInfoBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}



INTN
MemCmp(
  UINT8    *s1,
  UINT8    *s2,
  UINTN     n
  )
{
  UINT8    *p1, *p2;

  p1 = s1;
  p2 = s2;
  if (n != 0) {
    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return (0);
}



INTN 
GuidCmp(
  EFI_GUID    GuidGiven,
  EFI_GUID    GuidNeedToCmp
  )
{
  return MemCmp((UINT8 *)&GuidGiven,(UINT8 *)&GuidNeedToCmp,sizeof(EFI_GUID));
}
