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

  PciIoBBTestMain.c

Abstract:

  BB Test main source file for PciIo Protocol

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"

//
// Build Data structure
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestPciIoProtocolField = {
  PCIIO_TEST_REVISION,
  EFI_PCI_IO_PROTOCOL_GUID,
  L"PciIo",
  L"test Pci Io Protocol interface"
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

EFI_BB_TEST_ENTRY_FIELD gBBTestPciIoEntryField[] = {
  {
   { 0x667cf242, 0x78b0, 0x4a76, { 0xa1, 0x97, 0x0b, 0x79, 0x4f, 0x69, 0x3a, 0xa7 } },
   L"PollMem_Func",
   L"Test the Functionality of PciIo PollMem() automaticly",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PollMem_Func
  },
  {
   { 0x7a15fced, 0x8519, 0x438a, { 0x98, 0xfd, 0xeb, 0x31, 0xf3, 0x55, 0x11, 0xe3 } },
   L"PollIo_Func",
   L"Test the functionality of PciIo PollIo() automaticlly",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PollIo_Func
  },
  {
   { 0x459feb9b, 0x286b, 0x4626, { 0x99, 0x1d, 0x11, 0x4c, 0x7e, 0x64, 0x10, 0x4d } },
   L"MemRead_Func",
   L"test the functionality of PciIo Mem.Read() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemRead_Func
  },
  {
   { 0xebeb6a3e, 0xe554, 0x44ef, { 0x8e, 0x5b, 0x77, 0xc8, 0x63, 0xe6, 0x03, 0x8d } },
   L"MemWrite_Func",
   L"test the functionallity of PciIo Mem.Write() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   MemWrite_Func
  },
  {
   { 0x628efd6c, 0xac0c, 0x4a96, { 0xa7, 0x6f, 0xb9, 0xe4, 0xbc, 0xe0, 0xed, 0xef } },
   L"IoRead_Func",
   L"test the functionality of PciIo Io.Read() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoRead_Func
  },
  {
   { 0x96f7315c, 0xd6d8, 0x486a, { 0xbc, 0xd8, 0xea, 0xf8, 0x22, 0x24, 0x50, 0x99 } },
   L"IoWrite_Func",
   L"test the functionality of PciIo Io.Write() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   IoWrite_Func
  },
  {
   { 0xb175b36b, 0x44af, 0x4346, { 0x87, 0xff, 0xed, 0xe2, 0x92, 0xc1, 0x53, 0x84 } },
   L"PciRead_Func",
   L"test the functionality of PciIo Pci.Read() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciRead_Func
  },
  {
   { 0x7d6111a1, 0x67f0, 0x4d0a, { 0xa7, 0xe2, 0xb4, 0x46, 0x5d, 0x61, 0xbc, 0x39 } },
   L"PciWrite_Func",
   L"test the functionality of PciIo Pci.Write() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PciWrite_Func
  },
  {
   { 0x559ba279, 0x59f9, 0x4907, { 0xa6, 0x35, 0x46, 0xb8, 0x1c, 0x48, 0x71, 0x70 } },
   L"CopyMem_Func",
   L"test the functionality of PciIo CopyMem() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   CopyMem_Func
  },
  {
   { 0xca3fbc52, 0x6974, 0x4b68, { 0xb2, 0xb1, 0x55, 0x3a, 0x3d, 0x13, 0x92, 0xd6 } },
   L"AllocateBuffer_Func",
   L"tes the functionality of PciIo AllocateBuffer() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Func
  },
  {
   { 0xd6803bd4, 0xa251, 0x4270, { 0xb7, 0xad, 0xdf, 0x60, 0x7f, 0x83, 0xe1, 0x91 } },
   L"FreeBuffer_Func",
   L"tes the functionality of PciIo FreeBuffer()interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   FreeBuffer_Func
  },
  {
   { 0x28151808, 0xa723, 0x4ba4, { 0x9d, 0x48, 0x1f, 0x3f, 0xb6, 0xcd, 0x67, 0x7a } },
   L"Flush_Func",
   L"test the functionality of PciIo Flush() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Flush_Func
  },
  {
   { 0xe9fac9ce, 0x6189, 0x4792, { 0xa3, 0xf8, 0x4f, 0xc5, 0xf1, 0x7a, 0xa5, 0x53 } },
   L"GetLocation_Func",
   L"test the functionality of PciIo GetLocation() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetLocation_Func
  },
  {
   { 0x1032ef93, 0x9eac, 0x403b, { 0xb3, 0xa9, 0x97, 0x9a, 0xcb, 0xb8, 0x95, 0x9c } },
   L"GetBarAttributes_Func",
   L"test the functionality of PciIo GetBarAttributes() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetBarAttributes_Func
  },
  {
   { 0x8759704a, 0xa083, 0x41a3, { 0x9a, 0x9c, 0xc2, 0x6a, 0x87, 0x49, 0xd5, 0x48 } },
   L"SetBarAttributes_Func",
   L"test the functionality of PciIo SetBarAttributes() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   SetBarAttributes_Func
  },
  //
  //conformance test
  //
  {
   { 0x5e0e2913, 0x27ce, 0x4fd4, {  0x88, 0x46, 0x3d, 0xb, 0xe4, 0x7b, 0xf6, 0xbf }  },
   L"PollMem_Conf",
   L"do conformance test of PciIO PollMem() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PollMem_Conf
  },
  {
   { 0x55552e7b, 0xd033, 0x4143, {  0xb7, 0xfc, 0xf4, 0x89, 0x77, 0xf5, 0xf6, 0x48 }  },
   L"PollIo_Conf",
   L"do conformance test of PciIO PollIo() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   PollIo_Conf
  },
  {
   { 0xaed267ac, 0x3ad6, 0x4c09, {  0x9e, 0xbe, 0xef, 0xc8, 0x4e, 0xf, 0x52, 0xa0 }  },
   L"MemRead_Conf",
   L"do conformance test of PciIO Mem.Read() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   MemRead_Conf
  },
  {
   { 0xa272e2a4, 0x86cb, 0x4606, { 0x91, 0xa2, 0x43, 0x5a, 0xa6, 0xc3, 0xab, 0xbd }  },
   L"MemWrite_Conf",
   L"do conformance test of PciIO Mem.Write() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   MemWrite_Conf
  },
  {
   { 0xcf145e40, 0x3b31, 0x4c93, { 0xbe, 0x47, 0x9b, 0xe0, 0xf9, 0x41, 0x97, 0xe7 } },
   L"IoRead_Conf",
   L"do conformance test of PciIO Io.Read() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   IoRead_Conf
  },
  {
   { 0x298700fc, 0x9f03, 0x4801, { 0x93, 0x53, 0x9b, 0x45, 0x15, 0xd1, 0xb5, 0xf4 } },
   L"IoWrite_Conf",
   L"do conformance test of PciIO Io.Write() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   IoWrite_Conf
  },
  {
   { 0xbf5be234, 0xefa1, 0x4060, { 0x88, 0xbe, 0x4f, 0x6e, 0xd8, 0x29, 0xf6, 0x4a } },
   L"PciRead_Conf",
   L"do conformance test of PciIO Pci.Read() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PciRead_Conf
  },
  {
   { 0xe03f37fc, 0x26ca, 0x461e, { 0x85, 0xed, 0xdd, 0x2, 0x37, 0x12, 0xf5, 0x8d } },
   L"PciWrite_Conf",
   L"do conformance test of PciIO Pci.Write() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   PciWrite_Conf
  },
  {
   { 0xcd6eb235, 0x9aa5, 0x4b8c, { 0xb7, 0x13, 0x16, 0xdc, 0x16, 0xbc, 0xc6, 0x23 } },
   L"CopyMem_Conf",
   L"do conformance test of PciIO CopyMem() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   CopyMem_Conf
  },
  {
   { 0x48999dfc, 0x9b19, 0x438b, { 0xbf, 0x6b, 0xa7, 0xeb, 0xeb, 0x83, 0x11, 0x7f } },
   L"Map_Conf",
   L"do conformance test of PciIO Map() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Map_Conf
  },
  {
   { 0x3851d56e, 0xc09d, 0x4d87, { 0x88, 0xee, 0x4b, 0x9f, 0x91, 0x62, 0xcc, 0x17 } },
   L"AllocateBuffer_Conf",
   L"do conformance test of PciIO AllocateBuffer() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   AllocateBuffer_Conf
  },
  {
   { 0x97ae80d, 0xd53b, 0x4b73, { 0xb7, 0xc7, 0xa3, 0x40, 0xbb, 0x79, 0x23, 0xcb } },
   L"GetLocation_Conf",
   L"do conformance test of PciIO GetLocation() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetLocation_Conf
  },
  {
   { 0x92061b8f, 0xeb93, 0x4ad3, { 0xae, 0x5c, 0xb6, 0xcc, 0x92, 0xac, 0xf, 0x4f } },
   L"Attributes_Conf",
   L"do conformance test of PciIO Attributes() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   Attributes_Conf
  },
  {
   { 0xdb264ee7, 0xf049, 0x450b, { 0xa1, 0x5d, 0x6, 0x53, 0x11, 0xc1, 0xed, 0x27 } },
   L"GetBarAttributes_Conf",
   L"do conformance test of PciIO GetBarAttributes() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetBarAttributes_Conf
  },
  {
   { 0xd31725bc, 0xa1f0, 0x4510, { 0x92, 0x6a, 0xc2, 0x85, 0x40, 0x50, 0xd3, 0x1d } },
   L"SetBarAttributes_Conf",
   L"do conformance test of PciIO SetBarAttributes() automatically",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   SetBarAttributes_Conf
  },

  //
  //stress test
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
   { 0x7e2761a5, 0x3b79, 0x4cae, { 0xb5, 0xb7, 0xe2, 0x08, 0x98, 0x79, 0xa1, 0xba } },
   L"PollMem_Func_Manual",
   L"Test the functionality of PciIo PollMem() interface manually",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_MANUAL,
   PollMem_Func_Manual
  },
  {
   { 0x78307fd0, 0xf2c9, 0x4685, { 0xba, 0x3f, 0x99, 0x79, 0xb6, 0x3a, 0x65, 0xc3 } },
   L"PollIo_Func_Manual",
   L"Test  the functionality of PciIo PollIo() interface manually",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_MANUAL,
   PollIo_Func_Manual
  },
  {
   { 0xb899fc56, 0x86cf, 0x42f8, { 0x9e, 0xde, 0x22, 0x46, 0x7b, 0x6a, 0x75, 0xc0 } },
   L"Attributes_Func_Manual",
   L"test the functionality of PciIo Attributes() interface automatically",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_MANUAL,
   Attributes_Func
  },
  {
   { 0xdb2f3dd5, 0xdf43, 0x403d, { 0x9a, 0x3e, 0x67, 0x6c, 0x9b, 0x4e, 0xda, 0x28 } },
   L"Attributes_Stress",
   L"do stress test of PciIO Attributes() automatically",
   EFI_TEST_LEVEL_EXHAUSTIVE,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
   Attributes_Stress
  },
  {
   { 0x2e995b94, 0x34f8, 0x4aca, { 0x8c, 0x3f, 0xb, 0x26, 0xe1, 0x7c, 0x76, 0x65 } },
   L"GetAndSetBarAttributes_Stress",
   L"do stress test of PciIO GetBarAttributes() and SetBarAttributes () automatically",
   EFI_TEST_LEVEL_EXHAUSTIVE,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetAndSetBarAttributes_Stress
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestPciIoProtocolInterface;


/*
 *  the BBTest PciIo Entry point Funcion.
 *  @Param  ImageHandle the Driver Image handle.
 *  @param  SystemTable the EFI_SYSTEM_TABLE pointer.
 *  @return  EFI_SUCCESS the BBTest Interface was installed successfully.
 */
EFI_STATUS
InitializeBBTestPciIo (
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
           &gBBTestPciIoProtocolField,
           gBBTestPciIoEntryField,
           BBTestPciIoUnload,
           &gBBTestPciIoProtocolInterface
           );

}

/*
 *  The BBTest Driver Image Unload Function
 *  @param ImageHandle the Driver Image Handle.
 *  @return EFI_SUCCESS the BBTest Protocol and relative resource was cleaned successfully.
 */
EFI_STATUS
BBTestPciIoUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  if (gPciIoDevices != NULL) {
    gtBS->FreePool (gPciIoDevices);
  }
  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
  }
  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
  }


  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestPciIoProtocolInterface
           );

}

