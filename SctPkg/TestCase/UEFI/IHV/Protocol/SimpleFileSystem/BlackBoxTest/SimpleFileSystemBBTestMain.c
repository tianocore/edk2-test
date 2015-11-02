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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    SimpleFileSystemBBTestMain.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol Black Box Test

--*/

#include "SimpleFileSystemBBTest.h"

EFI_EVENT TimerEvent = NULL;

//
// global variable for this test driver's image handle
//
EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  TPL_APPLICATION,
  TPL_CALLBACK
};

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_FILE_SYSTEM_TEST_REVISION,
  IHV_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
  L"Testing For Simple File System Protocol and EFI_FILE Protocol",
  L"Total # test cases for the Simple File System Protocol and EFI_FILE Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0101,
    L"OpenVolume_Func",
    L"Function Test for OpenVolume",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenVolumeBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0102,
    L"Open_Func",
    L"Function Test for Open",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0103,
    L"Close_Func",
    L"Function Test for Close",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCloseBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0104,
    L"Delete_Func",
    L"Function Test for Delete",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDeleteBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0105,
    L"Read_Func",
    L"Function Test for Read",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0106,
    L"Write_Func",
    L"Function Test for Write",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0107,
    L"Flush_Func",
    L"Function Test for Flush",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0108,
    L"SetPosition_Func",
    L"Function Test for SetPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetPositionBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0109,
    L"GetPosition_Func",
    L"Function Test for GetPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetPositionBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0110,
    L"GetInfo_Func",
    L"Function Test for GetInfo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetInfoBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0111,
    L"SetInfo_Func",
    L"Function Test for SetInfo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetInfoBasicTest
  },
 
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0112,
    L"OpenEx_Func",
    L"Function Test for OpenEx",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenExBasicTest
  },

  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0113,
    L"ReadEx_Func",
    L"Function Test for ReadEx",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadExBasicTest
  },
  
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0114,
    L"WriteEx_Func",
    L"Function Test for WriteEx",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteExBasicTest
  },
  
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0115,
    L"FlushEx_Func",
    L"Function Test for FlushEx",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushExBasicTest
  },
  
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0201,
    L"Open_Conf",
    L"Conformance Test for Open",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenConformanceTest
  },
  
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0202,
    L"Delete_Conf",
    L"Conformance Test for Delete",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDeleteConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0203,
    L"Write_Conf",
    L"Conformance Test for Write",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0204,
    L"Flush_Conf",
    L"Conformance Test for Flush",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0205,
    L"SetPosition_Conf",
    L"Conformance Test for SetPosition",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetPositionConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0206,
    L"GetPosition_Conf",
    L"Conformance Test for GetPosition",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetPositionConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0207,
    L"GetInfo_Conf",
    L"Conformance Test for GetInfo",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetInfoConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0208,
    L"SetInfo_Conf",
    L"Conformance Test for SetInfo",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetInfoConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0209,
    L"OpenEx_Conf",
    L"Conformance Test for OpenEx",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenExConformanceTest
  }, 
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0210,
    L"WriteEx_Conf",
    L"Conformance Test for WriteEx",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteExConformanceTest
   }, 
   {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0211,
     L"FlushEx_Conf",
     L"Conformance Test for FlushEx",
     EFI_TEST_LEVEL_MINIMAL,
     gSupportProtocolGuid1,
     EFI_TEST_CASE_AUTO,
     BBTestFlushExConformanceTest
   }, 
   {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0212,
     L"ReadEx_Conf",
     L"Conformance Test for ReadEx",
     EFI_TEST_LEVEL_MINIMAL,
     gSupportProtocolGuid1,
     EFI_TEST_CASE_AUTO,
     BBTestReadExConformanceTest
   }, 


#ifdef EFI_TEST_EXHAUSTIVE
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0301,
    L"Change Media Test (Manual)",
    L"Extensive Test 1",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest1
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0302,
    L"Remove Media Test (Manual)",
    L"Extensive Test 2",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest2
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0303,
    L"Write Protected Test (Manual)",
    L"Extensive Test 3",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest3
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0304,
    L"Volume Full Test (Manual)",
    L"Extensive Test 4",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest4
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0305,
    L"File Access after File Deleted",
    L"Extensive Test 5",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemExtensiveTest5
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0306,
    L"File Read/Write Stress Test",
    L"Extensive Test 6",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemExtensiveTest6
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0307,
    L"Open_Stress",
    L"Stress test for Open",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemOpenStress
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0308,
    L"GetInfo_Stress",
    L"Stress test for GetInfo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemGetInfoStress
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0309,
    L"SetInfo_Stress",
    L"Stress test for SetInfo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemSetInfoStress
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
InitializeBBTestSimpleFileSystem (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  gtBS->CreateEvent (EFI_EVENT_TIMER, 0, NULL, NULL, &TimerEvent);
  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSimpleFileSystemUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BBTestSimpleFileSystemUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  gtBS->CloseEvent (TimerEvent);
  
  return EfiUninstallAndFreeIHVBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
