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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DeviceIoBBTestMain.c

Abstract:

  BB test main source file for Device Io protocol

--*/

#include "SctLib.h"
#include "DeviceIoBBTestMain.h"
#include "DeviceIoBBTestSupport.h"

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EXAMPLE_TEST_REVISION,
  IHV_DEVICE_IO_PROTOCOL_GUID,
  L"Device Io",
  L"test the Device Io Protocol interface"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
   { 0x319406d0, 0xf857, 0x44dc, { 0xaf, 0x5d, 0xc1, 0x9d, 0x4a, 0x68, 0x33, 0x32 } },
   L"MemRead_Func",
   L"test the basic functionality of Mem.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   MemRead_Func
  },
  {
   { 0x6ef9f333, 0xc5dd, 0x4c17, { 0x8f, 0x75, 0xf0, 0xd8, 0x40, 0xc2, 0x88, 0x8d } },
   L"MemWrite_Func",
   L"test the basic functionality of Mem.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   MemWrite_Func
  },
  {
   { 0xa5212974, 0x5013, 0x4d27, { 0x87, 0xb6, 0x63, 0xfe, 0x9f, 0x7e, 0x43, 0x4a } },
   L"IoRead_Func",
   L"test the basic functionality of Io.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   IoRead_Func
  },
  {
   { 0x476b903a, 0x59e2, 0x46a9, { 0x9b, 0x9a, 0x81, 0x13, 0x2a, 0x15, 0x4f, 0x25 } },
   L"IoWrite_Func",
   L"test the basic functionality of Io.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   IoWrite_Func
  },
  {
   { 0x6b929af1, 0x8150, 0x4a10, { 0x88, 0xb0, 0xa6, 0x37, 0x43, 0xdd, 0x53, 0xfb } },
   L"PciRead_Func",
   L"test the basic functionality of Pci.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciRead_Func
  },
  {
   { 0x8067168, 0x7c4e, 0x4e70, { 0x96, 0xb, 0x7f, 0x9a, 0xbf, 0x6f, 0x34, 0x3 } },
   L"PciWrite_Func",
   L"test the basic functionality of Pci.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciWrite_Func
  },
  {
   { 0xb2c53583, 0x5c27, 0x4c58, { 0xae, 0x1a, 0x48, 0x17, 0x77, 0x2c, 0xc7, 0x43 } },
   L"AllocateBuffer_Func",
   L"test the basic functionality of AllocateBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Func
  },
  {
   { 0x5a7da5b9, 0x4b73, 0x4e49, { 0xbd, 0xee, 0xe6, 0xa4, 0x42, 0x5d, 0xc6, 0x7e } },
   L"FreeBuffer_Func",
   L"test the basic functionality of FreeBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Func
  },
  {
   { 0xb43d8ddd, 0xdce5, 0x40b0, { 0x8a, 0x50, 0x30, 0x1a, 0xe3, 0xa0, 0xb9, 0xea } },
   L"Flush_Func",
   L"test the  basic functionality of Flush automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   Flush_Func
  },
  {
   { 0x8a607e40, 0x3284, 0x431f, { 0x8e, 0x5b, 0x7f, 0x9, 0x30, 0xa8, 0xb3, 0x18 } },
   L"PciDevicePath_Func",
   L"test the basic functionality of PciDevicePath automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciDevicePath_Func
  },
  {
   { 0xf7b89742, 0xa00c, 0x4bac, { 0x8f, 0x76, 0x8, 0x71, 0xc4, 0x40, 0x50, 0x44 } },
   L"MemRead_Conf",
   L"Test whether Mem.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   MemRead_Conf
  },
  {
   { 0x7586404d, 0x438b, 0x4eb4, { 0x9f, 0x47, 0x98, 0x2c, 0x82, 0xa1, 0xeb, 0x1c } },
   L"MemWrite_Conf",
   L"Test whether Mem.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   MemWrite_Conf
  },
  {
   { 0xb09ddd2f, 0x91ea, 0x462d, { 0xa7, 0xcb, 0xc3, 0xf7, 0xf8, 0x90, 0xad, 0x5a } },
   L"IoRead_Conf",
   L"Test whether Io.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   IoRead_Conf
  },
  {
   { 0xd2d28571, 0x4c58, 0x429a, { 0x96, 0x82, 0x53, 0x97, 0xff, 0xd5, 0xb1, 0xfe } },
   L"IoWrite_Conf",
   L"Test whether Io.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   IoWrite_Conf
  },
  {
   { 0x9cd873fe, 0xcb9c, 0x45d3, { 0xbd, 0x77, 0x96, 0xa4, 0xc2, 0x77, 0x28, 0x22 } },
   L"PciRead_Conf",
   L"Test whether Pci.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciRead_Conf
  },
  {
   { 0x5e55d7a1, 0x73c3, 0x4299, { 0x8b, 0x2c, 0x21, 0xff, 0x3b, 0x50, 0xd0, 0x32 } },
   L"PciWrite_Conf",
   L"Test whether Pci.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciWrite_Conf
  },
  {
   { 0x8fa14fea, 0x7875, 0x4da3, { 0x88, 0x65, 0x54, 0x3f, 0x3, 0xcb, 0x49, 0xc2 } },
   L"Map_Conf",
   L"Test whether Map() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   Map_Conf
  },
  {
   { 0xab76b27c, 0xd21d, 0x4b0f, { 0x99, 0x97, 0xab, 0x3a, 0xc9, 0x99, 0xe0, 0x72 } },
   L"AllocateBuffer_Conf",
   L"Test whether AllocateBuffer() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Conf
  },
  {
   { 0x7b157166, 0x798, 0x432e, { 0xb1, 0xd6, 0x23, 0x5a, 0x8d, 0x17, 0xf, 0xf6 } },
   L"FreeBuffer_Conf",
   L"Test whether FreeBuffer() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Conf
  },
  {
   { 0x74359907, 0x6178, 0x456f, { 0xa0, 0x45, 0xc9, 0x28, 0x43, 0x75, 0xc8, 0x62 } },
   L"PciDevicePath_Conf",
   L"Test whether PciDevicePath () performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid,
   EFI_TEST_CASE_AUTO,
   PciDevicePath_Conf
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;


EFI_STATUS
InitializeBBTestDeviceIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:
  Creates/installs the BlackBox Interface and eminating Entry Point node list.

Arguments:
  ImageHandle:  NULL
  *SystemTable: Pointer to System Table

Returns:
  EFI_SUCCESS:              Indicates the interface was installed.
  EFI_OUT_OF_RESOURCES:     Indicates space for the new handle could not be allocated
  EFI_INVALID_PARAMETER:    One of the parameters has an invalid value.

--*/
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  GetSystemDevicePathAndFilePath (ImageHandle);

  return  EfiInitAndInstallIHVBBTestInterface (
            &ImageHandle,
            &gBBTestProtocolField,
            gBBTestEntryField,
            BBTestDeviceIoUnload,
            &gBBTestProtocolInterface
            );

}


EFI_STATUS
BBTestDeviceIoUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  if (gDevIoDevices != NULL) {
    gtBS->FreePool (gDevIoDevices);
  }
  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
  }

  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
  }

  return EfiUninstallAndFreeIHVBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );

}

