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

  DecompressBBTestMain.c

Abstract:

  BB test Main source file for Decompress protocol

--*/

#include "SctLib.h"
#include "DecompressBBTestMain.h"
#include "DecompressBBTestSupport.h"

//
// Build Data structure here
//



EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EXAMPLE_TEST_REVISION,
  EFI_DECOMPRESS_PROTOCOL_GUID,
  L"DecompressProtocol",
  L"Test the functionality of Decompress Prococol "
};

EFI_GUID gSupportProtocolGuid1[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid3[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid4[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};



EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
   { 0xdd5d932b, 0x237b, 0x4cac, { 0xa5, 0x7a, 0xe6, 0x28, 0xe9, 0xdd, 0x9c, 0x89 } },
   L"GetInfo_Func",
   L"test the basic functionality of GetInfo()",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid1,
   EFI_TEST_CASE_AUTO,
   GetInfo_Func
  },
  {
   { 0x02869a3b, 0xbfea, 0x4c42, { 0xb6, 0xca, 0x76, 0xfc, 0xf1, 0xe1, 0xf6, 0x9d } },
   L"Decompress_Func",
   L"Test the basic functionality of Decompress()",
   EFI_TEST_LEVEL_DEFAULT,
   gSupportProtocolGuid2,
   EFI_TEST_CASE_AUTO,
   Decompress_Func
  },
#if 0
  {
   { 0xedeedbe3, 0xfdd1, 0x4273, { 0x8f, 0x0e, 0x8c, 0xfb, 0x6e, 0x19, 0x55, 0x5c } },
   L"GetInfo_Conf",
   L"Test whether GetInfo() performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid3,
   EFI_TEST_CASE_AUTO,
   GetInfo_Conf
  },
#endif
  {
   { 0x3a22bc1a, 0x7936, 0x46cd, { 0x90, 0x57, 0x3c, 0x46, 0xe4, 0x32, 0x0b, 0x22 } },
   L"Decompress_Conf",
   L"Test whether Decompress () performs enough parameter checking",
   EFI_TEST_LEVEL_MINIMAL,
   gSupportProtocolGuid4,
   EFI_TEST_CASE_AUTO,
   Decompress_Conf
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;


EFI_STATUS
InitializeDecompressProtocolBBTest (
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


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           DecompressProtocolBBTestUnload,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
DecompressProtocolBBTestUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
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
