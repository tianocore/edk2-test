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

  PciRootBridgeIoBBTestMain.c

Abstract:

  BB test main source file for Pci Root Bridge Io Protocol

--*/

#include "SctLib.h"
#include "PciRootBridgeIoBBTestMain.h"
#include "PciRootBridgeIoBBTestSupport.h"


//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EXAMPLE_TEST_REVISION,
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID,
  L"PciRootBridgeIo",
  L"test Pci Root Bridge Io Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
   { 0xc7383588, 0x7a32, 0x466b, { 0xa6, 0xce, 0x75, 0x2e, 0x2f, 0xdf, 0x78, 0xee } },
   L"PollMem_Func",
   L"Test the Functionality of PollMem automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PollMem_Func
  },
  {
   { 0xaf0fba76, 0x15bb, 0x4778, { 0x8c, 0xa3, 0x71, 0x82, 0x52, 0x9c, 0x98, 0xf5 } },
   L"PollIo_Func",
   L"Test the basic functionality of PollIo automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PollIo_Func
  },
  {
   { 0x0c9ffbf8, 0xb976, 0x40fb, { 0x9e, 0xf8, 0x60, 0x0a, 0x43, 0xe7, 0x9e, 0xc5 } },
   L"MemRead_Func",
   L"test the basic functionality of Mem.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemRead_Func
  },
  {
   { 0x64b0b6d9, 0xd5fe, 0x45aa, { 0xaf, 0xe2, 0x65, 0x6f, 0x88, 0x67, 0xdd, 0x59 } },
   L"MemWrite_Func",
   L"test the basic functionality of Mem.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemWrite_Func
  },
  {
   { 0xe5dfbafc, 0xcf75, 0x4983, { 0xa6, 0x8d, 0x3c, 0x5d, 0xa9, 0x97, 0x1e, 0x40 } },
   L"IoRead_Func",
   L"Test the basic functionality of Io.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoRead_Func
  },
  {
   { 0x5475314a, 0x4851, 0x49c9, { 0x93, 0x44, 0xc5, 0xaf, 0x84, 0x07, 0x7e, 0x72 } },
   L"IoWrite_Func",
   L"test the basic functionality of Io.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoWrite_Func
  },
  {
   { 0xc9d9a56a, 0x609a, 0x4f40, { 0xb9, 0x52, 0x9e, 0xae, 0x93, 0x5d, 0x4f, 0x77 } },
   L"PciRead_Func",
   L"test the basic functionality of Pci.Read",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciRead_Func
  },
  {
   { 0xba524304, 0x521f, 0x4f19, { 0x8f, 0x0a, 0x57, 0xd0, 0x09, 0x8a, 0x7d, 0x3a } },
   L"PciWrite_Func",
   L"test the basic functionality of Pci.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciWrite_Func
  },
  {
   { 0xc513e58f, 0xe909, 0x4f71, { 0x8b, 0x48, 0x1d, 0x58, 0x20, 0x64, 0xc6, 0x95 } },
   L"CopyMem_Func",
   L"test the basic functionality of CopyMem automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   CopyMem_Func
  },
  {
   { 0x4647db6b, 0x5cd5, 0x4494, { 0x8e, 0xad, 0x47, 0x7b, 0x56, 0x2c, 0xc3, 0xdb } },
   L"AllocateBuffer_Func",
   L"test the basic functionality of AlllocateBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Func
  },
  {
   { 0x66239bab, 0xee3d, 0x4b21, { 0x8a, 0xc7, 0xc7, 0xfa, 0xdb, 0x9c, 0xa9, 0x42 } },
   L"FreeBuffer_Func",
   L"test the basic functionality of FreeBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Func
  },
  {
   { 0x55ad4514, 0x121b, 0x4ea0, { 0xb0, 0x8a, 0x25, 0x01, 0xe9, 0x6d, 0x27, 0x8c } },
   L"Flush_Func",
   L"test the basic functionality of Flush automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Flush_Func
  },
  {
   { 0x77c0df14, 0x733d, 0x4bdf, { 0xbb, 0x8c, 0x79, 0xc6, 0x3a, 0x53, 0xdc, 0xd0 } },
   L"GetAttributes_Func",
   L"test the basic functionality of GetAttributes automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetAttributes_Func
  },
  {
   { 0xaaa8db85, 0xafa5, 0x4b44, { 0x80, 0xbf, 0x14, 0x5d, 0x5f, 0x47, 0x3, 0xbb } },
   L"SetAttributes_Func",
   L"test the basic functionality of SetAttributes automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO | EFI_TEST_CASE_RESET_REQUIRED,
   SetAttributes_Func
  },
  {
   { 0xcf8b4010, 0x0a5b, 0x4b39, { 0xbc, 0xe1, 0x86, 0x3d, 0x90, 0x88, 0x3a, 0xb6 } },
   L"Configuration_Func",
   L"Test the basic functionality of Configuration automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Configuration_Func
  },
  {
   { 0xd1b7e276, 0x79d2, 0x417c, { 0x85, 0xad, 0xfc, 0x56, 0xc2, 0x1f, 0x8b, 0x29 } },
   L"PollMem_Conf",
   L"Test whether PollMem() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PollMem_Conf
  },
  {
   { 0xc3cdc5b0, 0xfefa, 0x47b5, { 0xbd, 0xb5, 0x74, 0x0e, 0x28, 0x65, 0xe4, 0xef } },
   L"PollIo_Conf",
   L"Test whether PollIo() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PollIo_Conf
  },
  {
   { 0x9e849309, 0xa871, 0x49e1, { 0xab, 0x3c, 0xde, 0xa1, 0xba, 0xeb, 0x64, 0xf2 } },
   L"MemRead_Conf",
   L"Test whether Mem.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemRead_Conf
  },
  {
   { 0xe488db01, 0x68f8, 0x4b31, { 0xa7, 0x7e, 0x3a, 0xbb, 0x8b, 0x2b, 0x32, 0xd6 } },
   L"MemWrite_Conf",
   L"Test whether Mem.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemWrite_Conf
  },
  {
   { 0x703f1616, 0x7d2f, 0x4363, { 0x89, 0xbd, 0xa1, 0xeb, 0x64, 0xe4, 0x9a, 0x15 } },
   L"IoRead_Conf",
   L"Test whether Io.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoRead_Conf
  },
  {
   { 0x178c36f0, 0xddf6, 0x43ce, { 0x86, 0x5c, 0x76, 0xc1, 0xb5, 0xcd, 0x33, 0x35 } },
   L"IoWrite_Conf",
   L"Test whether Io.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoWrite_Conf
  },
  {
   { 0x76b965da, 0xc850, 0x4049, { 0x98, 0x28, 0x4c, 0x69, 0x80, 0xba, 0xa2, 0xc1 } },
   L"PciRead_Conf",
   L"Test whether Pci.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciRead_Conf
  },
  {
   { 0x76bdf3a4, 0xe8b8, 0x4275, { 0xb7, 0x08, 0xd0, 0x61, 0x27, 0x05, 0x9c, 0x8a } },
   L"PciWrite_Conf",
   L"Test whether Pci.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciWrite_Conf
  },
  {
   { 0x69c65670, 0x2a2e, 0x427b, { 0x80, 0x8c, 0xa6, 0x66, 0x8c, 0xa5, 0x3d, 0x9c } },
   L"CopyMem_Conf",
   L"Test whether SctCopyMem () performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   CopyMem_Conf
  },
  {
   { 0x2231b12b, 0x139f, 0x40a1, { 0x99, 0xdc, 0x8b, 0x52, 0x5d, 0xba, 0xcb, 0x70 } },
   L"Map_Conf",
   L"Test whether Map() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Map_Conf
  },
  {
   { 0x0792893e, 0x82f6, 0x45e3, { 0xaf, 0x70, 0xad, 0x6d, 0xbe, 0xe2, 0x37, 0x42 } },
   L"AllocateBuffer_Conf",
   L"Test whether AllocateBuffer() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Conf
  },
  {
   { 0xa981ab75, 0x11c2, 0x44de, { 0x94, 0xfb, 0x93, 0xf0, 0x5b, 0xcd, 0xbf, 0x87 } },
   L"GetAttributes_Conf",
   L"Test whether GetAttributes() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetAttributes_Conf
  },
  {
   { 0x205a75df, 0x3957, 0x4606, { 0xb2, 0x3a, 0x75, 0xfe, 0x3c, 0x50, 0x2b, 0xe5 } },
   L"SetAttributes_Conf",
   L"Test whether SetAttributes() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   SetAttributes_Conf
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
   { 0x255ddce6, 0xfeed, 0x41cd, { 0xae, 0x80, 0xeb, 0x68, 0xda, 0x7b, 0x2c, 0x56 } },
   L"PollMem_Func_Manual",
   L"Test the Basic functionality of PollMem manually",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_MANUAL,
   PollMem_Func_Manual
  },
  {
   { 0xe93d949d, 0xe3f6, 0x4824, { 0xbc, 0x78, 0x7b, 0x01, 0xc1, 0x4c, 0xaa, 0xd2 } },
   L"PollIo_Func_Manual",
   L"Test the basic functionality of PollIo manually",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_MANUAL,
   PollIo_Func_Manual
  },
  {
   { 0x9f740734, 0x85b, 0x472a, { 0xaf, 0x34, 0x3f, 0x8e, 0x11, 0x67, 0x71, 0x9d } },
   L"SetAttributes_Stress",
   L"Stress Test for SetAttributes()",
   EFI_TEST_LEVEL_EXHAUSTIVE,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO | EFI_TEST_CASE_RESET_REQUIRED,
   SetAttributes_Stress
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;


EFI_STATUS
EFIAPI
InitializeBBTestPciRootBridgeIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  //
  //initialize all the library to be used in this driver.
  //
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  GetSystemDevicePathAndFilePath (ImageHandle);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestPciRootBridgeIoUnload,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
BBTestPciRootBridgeIoUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  if (gRootBridgeIoDevices != NULL) {
    gtBS->FreePool (gRootBridgeIoDevices);
  }

  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
  }

  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
  }

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );

}
