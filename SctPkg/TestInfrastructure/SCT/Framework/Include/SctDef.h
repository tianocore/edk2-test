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
                                                                
  Copyright 2006 - 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SctDef.h

Abstract:

  This file defines the global definitions and variables.

--*/

#ifndef _EFI_SCT_DEF_H_
#define _EFI_SCT_DEF_H_

//
// Global definitions
//
#if (EFI_SPECIFICATION_VERSION == EFI_1_10_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"EFI Self Certification Test"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_00_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.0 Self Certification Test"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_10_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.1 Self Certification Test"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_30_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.3 Self Certification Test"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_31_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.3.1C Self Certification Test"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_40_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.4B Self Certification Test(SCT2)"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_50_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.5 Self Certification Test(SCT2)"
#elif (EFI_SPECIFICATION_VERSION == EFI_2_60_SYSTEM_TABLE_REVISION)
#define EFI_SCT_NAME                        L"UEFI2.6 Self Certification Test(SCT2)"
#else
#error Unknown EFI_SPECIFICATION_VERSION
#endif

#define EFI_SCT_SHORT_NAME                  L"SCT"

//
// The global directory and file names
//

#define EFI_SCT_PATH_DATA                   L"Data"
#define EFI_SCT_PATH_LOG                    L"Log"
#define EFI_SCT_PATH_OVERALL                L"Overall"
#define EFI_SCT_PATH_REPORT                 L"Report"
#define EFI_SCT_PATH_SEQUENCE               L"Sequence"
#define EFI_SCT_PATH_SUPPORT                L"Support"
#define EFI_SCT_PATH_PROXY                  L"Proxy"
#define EFI_SCT_PATH_TEST                   L"Test"
#define EFI_SCT_PATH_VERBOSE                L".verbose.mode"

#define EFI_SCT_FILE_LOG                    L"Sct.log"
#define EFI_SCT_FILE_CFG                    L"Sct.cfg"

#define EFI_SCT_FILE_CONFIG                 L"Data\\Config.ini"
#define EFI_SCT_FILE_CATEGORY               L"Data\\Category.ini"
#define EFI_SCT_FILE_GUID_DATABASE          L"Data\\GuidFile.txt"
#define EFI_SCT_FILE_RECOVERY               L"Data\\Recovery.dat"
#define EFI_SCT_FILE_TEST_CASE              L"Data\\TestCase.ini"
#define EFI_SCT_FILE_SKIPPED_CASE           L"Data\\SkippedCase.ini"
#define EFI_SCT_FILE_DEVICE_CONFIG          L"Data\\DeviceConfig.ini"
#define EFI_SCT_SYNC_FILE_CASE_TREE         L"Data\\CaseTree.ini"

#define EFI_SCT_FILE_SUMMARY_LOG            L"Overall\\Summary.log"
#define EFI_SCT_FILE_SUMMARY_EKL            L"Overall\\Summary.ekl"

//
// Maximum buffer size in the SCT
//
#define EFI_SCT_MAX_BUFFER_SIZE             512
#define MAX_STRING_LEN                      250

//
// Instance Num in single directory 
//
#define MaxInstanceNumInSingleDirectory     100

//
// System hang assertion
//
#define EFI_SYSTEM_HANG_ASSERTION_GUID      \
  { 0xde687a18, 0x0bbd, 0x4396, { 0x85, 0x09, 0x49, 0x8f, 0xf2, 0x32, 0x34, 0xf1 }}

//
// Global variables
//

extern EFI_SCT_FRAMEWORK_TABLE *gFT;

extern EFI_GUID gEfiSystemHangAssertionGuid;

extern UINTN gTestCaseMaxRunTimeMax;

extern BOOLEAN gForceExecution;
#endif
