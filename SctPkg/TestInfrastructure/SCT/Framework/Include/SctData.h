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

  SctData.h

Abstract:

  This file provides the services to load, save, and manage all kind of test
  data.

--*/

#ifndef _EFI_SCT_DATA_H_
#define _EFI_SCT_DATA_H_

//
// External functions declaration
//

//
// Application test services
//

EFI_STATUS
LoadApTest (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  );

EFI_STATUS
FreeApTest (
  IN EFI_AP_TEST_INTERFACE        *ApTest
  );

//
// Configuration data services
//

EFI_STATUS
LoadConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_CONFIG_DATA         *ConfigData
  );

EFI_STATUS
SaveConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  );

EFI_STATUS
FreeConfigData (
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  );

//
// Category data services
//

EFI_STATUS
LoadCategoryData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *CategoryList
  );

EFI_STATUS
FreeCategoryData (
  IN SCT_LIST_ENTRY               *CategoryList
  );

EFI_STATUS
FindCategoryByGuid (
  IN  EFI_GUID                    *Guid,
  OUT EFI_SCT_CATEGORY_DATA       **Category
);

//
// Test case services
//

EFI_STATUS
LoadTestCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *TestCaseList
  );

EFI_STATUS
SaveTestCases (
  VOID
  );

EFI_STATUS
LoadTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN OUT SCT_LIST_ENTRY           *TestCaseList
  );

EFI_STATUS
SaveTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN SCT_LIST_ENTRY               *TestCaseList
  );

EFI_STATUS
FreeTestCases (
  IN SCT_LIST_ENTRY               *TestCaseList
  );

EFI_STATUS
CreateTestCases (
  OUT SCT_LIST_ENTRY              *TestCaseList
  );

EFI_STATUS
MergeTestCases (
  IN OUT SCT_LIST_ENTRY           *DstTestCaseList,
  IN SCT_LIST_ENTRY               *SrcTestCaseList
  );

EFI_STATUS
FindTestCaseByGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

EFI_STATUS
SaveCaseTree (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN SCT_LIST_ENTRY               *TestNodeList
  );

EFI_STATUS
GenerateCaseTreeFile(
  VOID
  );

//
// Test node services
//

EFI_STATUS
CreateTestNodes (
  OUT SCT_LIST_ENTRY              *TestNodeList
  );

EFI_STATUS
FreeTestNodes (
  IN SCT_LIST_ENTRY               *TestNodeList
  );

//
// Skipped Case Services
//

EFI_STATUS
RecordSkippedCases (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
FreeSkippedCases (
  IN SCT_LIST_ENTRY               *SkippedCaseList
  );

EFI_STATUS
SaveSkippedCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
LoadSkippedCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT SCT_LIST_ENTRY              *SkippedCaseList
  );

#endif
