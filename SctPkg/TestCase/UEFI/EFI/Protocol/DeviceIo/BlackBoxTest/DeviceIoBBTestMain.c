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
  EFI_DEVICE_IO_PROTOCOL_GUID,
  L"Device Io",
  L"test the Device Io Protocol interface"
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
   { 0x1f5a4219, 0xef3f, 0x4064, { 0xbf, 0xe3, 0xc7, 0x2e, 0x47, 0xca, 0xf2, 0x37 } },
   L"MemRead_Func",
   L"test the basic functionality of Mem.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemRead_Func
  },
  {
  { 0xaa4b526d, 0xbaf4, 0x4922, { 0x8d, 0x32, 0x6e, 0x16, 0xe2, 0x97, 0xb7, 0x3 } },
   L"MemWrite_Func",
   L"test the basic functionality of Mem.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemWrite_Func
  },
  {
   { 0x9e72d727, 0x59d1, 0x4211, { 0xa1, 0xe4, 0xbb, 0xf5, 0x11, 0x91, 0xb6, 0xc1 } },
   L"IoRead_Func",
   L"test the basic functionality of Io.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoRead_Func
  },
  {
   { 0xc2684fa9, 0x4abe, 0x4699, { 0x83, 0xf6, 0x19, 0xa3, 0x11, 0x6d, 0x8c, 0x1c } },
   L"IoWrite_Func",
   L"test the basic functionality of Io.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoWrite_Func
  },
  {
   { 0x898fed19, 0x6d7e, 0x4c81, { 0x80, 0x0d, 0x9f, 0xf9, 0xf2, 0xc6, 0xc3, 0xd2 } },
   L"PciRead_Func",
   L"test the basic functionality of Pci.Read automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciRead_Func
  },
  {
   { 0xb10f7d85, 0x5f8f, 0x4975, { 0xb8, 0x17, 0x56, 0x82, 0x21, 0xdc, 0x7a, 0xd4 } },
   L"PciWrite_Func",
   L"test the basic functionality of Pci.Write automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciWrite_Func
  },
  {
   { 0xbb7a6cbd, 0xab28, 0x4d94, { 0x97, 0x26, 0x98, 0xad, 0xa2, 0x97, 0x05, 0xe7 } },
   L"AllocateBuffer_Func",
   L"test the basic functionality of AllocateBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Func
  },
  {
   { 0xc9be34fc, 0x59ae, 0x456d, { 0x81, 0xfa, 0x40, 0xf8, 0xc4, 0x19, 0x1a, 0xa1 } },
   L"FreeBuffer_Func",
   L"test the basic functionality of FreeBuffer automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Func
  },
  {
   { 0xd42ac3b8, 0xf4bb, 0x4a0e, { 0x9d, 0x8d, 0x9d, 0xd1, 0x53, 0x08, 0xb8, 0x9d } },
   L"Flush_Func",
   L"test the  basic functionality of Flush automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Flush_Func
  },
  {
   { 0xac437ca6, 0xb310, 0x430d, { 0xac, 0x00, 0xfb, 0xeb, 0x96, 0xed, 0x22, 0xb9 } },
   L"PciDevicePath_Func",
   L"test the basic functionality of PciDevicePath automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PciDevicePath_Func
  },
  {
   { 0xd66a3560, 0xd08a, 0x4da6, { 0x90, 0xb7, 0xdd, 0xa0, 0x02, 0x35, 0x4a, 0x23 } },
   L"MemRead_Conf",
   L"Test whether Mem.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemRead_Conf
  },
  {
   { 0xa6a26b3c, 0x6710, 0x44ff, { 0xa8, 0x25, 0x8f, 0xe0, 0x8d, 0xf6, 0xc4, 0x01 } },
   L"MemWrite_Conf",
   L"Test whether Mem.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemWrite_Conf
  },
  {
   { 0x03a40b64, 0xb932, 0x488d, { 0x82, 0x19, 0x56, 0xd0, 0x35, 0x9b, 0xe5, 0x48 } },
   L"IoRead_Conf",
   L"Test whether Io.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoRead_Conf
  },
  {
   { 0x3331efab, 0xbfe0, 0x4dbd, { 0x8a, 0xa2, 0xcf, 0xcb, 0x36, 0xfd, 0x7a, 0x8e } },
   L"IoWrite_Conf",
   L"Test whether Io.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoWrite_Conf
  },
  {
   { 0xe771e53c, 0x1407, 0x43fa, { 0xbc, 0x36, 0xab, 0xfd, 0x3f, 0xa3, 0x93, 0x9a } },
   L"PciRead_Conf",
   L"Test whether Pci.Read() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciRead_Conf
  },
  {
   { 0xa8e3a0ce, 0x54b8, 0x4aa2, { 0xa6, 0x80, 0xe6, 0xfd, 0xac, 0x4e, 0x86, 0xfe } },
   L"PciWrite_Conf",
   L"Test whether Pci.Write() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciWrite_Conf
  },
  {
   { 0x475910ee, 0x0812, 0x43dc, { 0x99, 0x75, 0x1f, 0x79, 0x5d, 0x01, 0x8b, 0xbd } },
   L"Map_Conf",
   L"Test whether Map() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Map_Conf
  },
  {
   { 0x696e0a95, 0x5b45, 0x4b0e, { 0x97, 0x66, 0x10, 0xf9, 0xb9, 0x11, 0x88, 0x64 } },
   L"AllocateBuffer_Conf",
   L"Test whether AllocateBuffer() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Conf
  },
  {
   { 0x7671b91c, 0x6f0a, 0x4ca5, { 0x81, 0x7d, 0xe7, 0xa1, 0x6d, 0x14, 0x95, 0x9f } },
   L"FreeBuffer_Conf",
   L"Test whether FreeBuffer() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Conf
  },
  {
   { 0xe80adef0, 0x73bd, 0x4711, { 0xa1, 0x9a, 0x73, 0xf4, 0xee, 0x14, 0xb1, 0x89 } },
   L"PciDevicePath_Conf",
   L"Test whether PciDevicePath () performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
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

  return  EfiInitAndInstallBBTestInterface (
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

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );

}

