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

  DevicePathToTextBBTestConformance.c

Abstract:

  Interface Function Test Cases of Device Path To Text Protocol

--*/

#include "DevicePathToTextBBTestMain.h"

#define PCINodeType         1
#define PCINodeSubType      1
#define PCINodeLength       6

#define PCIRootNodeType     2
#define PCIRootNodeSubType  1
#define PCIRootNodeLength   12

#define USBNodeType         3
#define USBNodeSubType      5
#define USBNodeLength       6

//
// TDS 3.6.1
//
EFI_STATUS
DevicePathToTextConvertDeviceNodeToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;

  CHAR16                              *text1;
  CHAR16                              *text2;
  CHAR16                              *text3;
  CHAR16                              *text4;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.6.1.2.1
  //
  text1 = DevicePathToText->ConvertDeviceNodeToText (NULL, FALSE, FALSE);
  text2 = DevicePathToText->ConvertDeviceNodeToText (NULL, TRUE, FALSE);
  text3 = DevicePathToText->ConvertDeviceNodeToText (NULL, FALSE, TRUE);
  text4 = DevicePathToText->ConvertDeviceNodeToText (NULL, TRUE, TRUE);

  if ((text1 == NULL) && (text2 == NULL) && (text3 == NULL) && (text4 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid072,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText should return NULL with DeviceNode set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.6.2
//
EFI_STATUS
DevicePathToTextConvertDevicePathToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;

  CHAR16                              *text1;
  CHAR16                              *text2;
  CHAR16                              *text3;
  CHAR16                              *text4;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.6.2.2.1
  //
  text1 = DevicePathToText->ConvertDevicePathToText (NULL, FALSE, TRUE);
  text2 = DevicePathToText->ConvertDevicePathToText (NULL, TRUE, FALSE);
  text3 = DevicePathToText->ConvertDevicePathToText (NULL, FALSE, TRUE);
  text4 = DevicePathToText->ConvertDevicePathToText (NULL, TRUE, TRUE);

  if ((text1 == NULL) && (text2 == NULL) && (text3 == NULL) && (text4 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid074,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDevicePathToText should return NULL with DevicePath set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
