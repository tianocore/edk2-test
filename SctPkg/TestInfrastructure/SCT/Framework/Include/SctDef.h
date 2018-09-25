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
