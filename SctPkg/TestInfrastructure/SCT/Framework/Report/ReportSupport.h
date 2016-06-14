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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ReportSupport.h

Abstract:

  This file provides the support services for test report generation.

--*/

#ifndef _EFI_REPORT_SUPPORT_H_
#define _EFI_REPORT_SUPPORT_H_

//
// Definitions
//

#define EFI_SCT_GUID_DATABASE_SIZE          5000
#define EFI_SCT_GUID_ASSERTION_SIZE         5000

#define EFI_SCT_LOG_BUFFER_SIZE             5000

#define EFI_SCT_GUID_LEN                    60
#define EFI_SCT_TITLE_LEN                   300
#define EFI_SCT_INDEX_LEN                   20
#define EFI_SCT_CASE_INDEX_LEN              20
#define EFI_SCT_CASE_ITERATION_LEN          20
#define EFI_SCT_CASE_REVISION_LEN           20
#define EFI_SCT_CASE_GUID_LEN               60
#define EFI_SCT_RUNTIME_INFOR_LEN           600
#define EFI_SCT_DEVICE_PATH_LEN             300
#define EFI_SCT_NAME_LEN                    256

//
// EFI_SCT_GUID_ASSERTION_STATE
//

typedef UINTN EFI_SCT_GUID_ASSERTION_STATE;
#define EFI_SCT_GUID_ASSERTION_STATE_NOT_FOUND    0x00
#define EFI_SCT_GUID_ASSERTION_STATE_FOUND        0x01
#define EFI_SCT_GUID_ASSERTION_STATE_OVERRIDE     0x02

//
// EFI_SCT_GUID_ASSERTION_TYPE
//

#define EFI_SCT_GUID_ASSERTION_TYPE_EMPTY         0x00
#define EFI_SCT_GUID_ASSERTION_TYPE_PASS          0x01
#define EFI_SCT_GUID_ASSERTION_TYPE_WARN          0x03
#define EFI_SCT_GUID_ASSERTION_TYPE_FAIL          0x07

//
// EFI_SCT_GUID_DATABASE
//

typedef struct {
  CHAR16                          Guid[EFI_SCT_GUID_LEN];
  CHAR16                          Title[EFI_SCT_TITLE_LEN];
  CHAR16                          Index[EFI_SCT_INDEX_LEN];
} EFI_SCT_GUID_DATABASE;

//
// EFI_SCT_GUID_ASSERTION
//

typedef struct {
  CHAR16                          Guid[EFI_SCT_GUID_LEN];
  UINTN                           AssertionType;
} EFI_SCT_GUID_ASSERTION;

//
// EFI_SCT_ASSERTION_INFOR
//

typedef struct _EFI_SCT_ASSERTION_INFOR EFI_SCT_ASSERTION_INFOR;

struct _EFI_SCT_ASSERTION_INFOR {
  EFI_SCT_ASSERTION_INFOR         *Next;
  EFI_SCT_ASSERTION_INFOR         *Prev;
  CHAR16                          Index[EFI_SCT_INDEX_LEN];
  CHAR16                          CaseIndex[EFI_SCT_CASE_INDEX_LEN];
  CHAR16                          CaseIteration[EFI_SCT_CASE_ITERATION_LEN];
  CHAR16                          CaseRevision[EFI_SCT_CASE_REVISION_LEN];
  CHAR16                          CaseGuid[EFI_SCT_CASE_GUID_LEN];
  CHAR16                          Guid[EFI_SCT_GUID_LEN];
  CHAR16                          Title[EFI_SCT_TITLE_LEN];
  CHAR16                          RuntimeInfor[EFI_SCT_RUNTIME_INFOR_LEN];
  CHAR16                          DevicePath[EFI_SCT_DEVICE_PATH_LEN];
  CHAR16                          FileName[EFI_SCT_NAME_LEN];
};

//
// EFI_SCT_REPORT_ITEM
//

typedef struct _EFI_SCT_REPORT_ITEM EFI_SCT_REPORT_ITEM;

struct _EFI_SCT_REPORT_ITEM {
  EFI_SCT_REPORT_ITEM             *Next;
  EFI_SCT_REPORT_ITEM             *Prev;
  UINT32                          PassNumber;
  UINT32                          WarnNumber;
  UINT32                          FailNumber;
  CHAR16                          TestName[EFI_SCT_NAME_LEN];
  CHAR16                          TestCategory[EFI_SCT_NAME_LEN];
  EFI_SCT_ASSERTION_INFOR         *FailAssertion;
  EFI_SCT_ASSERTION_INFOR         *PassAssertion;
};

//
// EFI_SCT_REPORT_INFOR
//

typedef struct {
  UINT32                          TotalPass;
  UINT32                          TotalWarn;
  UINT32                          TotalFail;
  EFI_SCT_REPORT_ITEM             *ReportItem;
} EFI_SCT_REPORT_INFOR;

//
// Module functions declarations
//

BOOLEAN
FileExist (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  );

EFI_STATUS
ReadFileToBuffer (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT UINTN                       *BufferSize,
  OUT VOID                        **Buffer
  );

EFI_STATUS
GetIndexFromFileName (
  IN OUT CHAR16                   *FileName,
  OUT CHAR16                      **CaseIndex,
  OUT CHAR16                      **CaseIteration
  );

EFI_STATUS
AutoStrCat (
  IN OUT CHAR16                   **DstBuffer,
  IN CHAR16                       *SrcBuffer
  );

CHAR16 *
StrTokenLine (
  IN CHAR16                       *String OPTIONAL,
  IN CHAR16                       *CharSet
  );

CHAR16 *
StrTokenField (
  IN CHAR16                       *String OPTIONAL,
  IN CHAR16                       *CharSet
  );

EFI_STATUS
LoadGuidDatabase (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  );

EFI_STATUS
UnloadGuidDatabase (
  VOID
  );

EFI_STATUS
SearchGuidDatabase (
  IN CHAR16                       *GuidStr,
  OUT CHAR16                      *TitleStr,
  OUT CHAR16                      *IndexStr
  );

EFI_STATUS
LoadGuidAssertion (
  IN CHAR16                       *Buffer,
  IN BOOLEAN                      Duplicate,
  OUT EFI_SCT_LOG_STATE           *FileState
  );

EFI_STATUS
UnloadGuidAssertion (
  VOID
  );

EFI_STATUS
GetAssertionNumber (
  IN OUT UINT32                   *PassNumber,
  IN OUT UINT32                   *WarnNumber,
  IN OUT UINT32                   *FailNumber
  );

EFI_STATUS
LoadReportInfor (
  IN CHAR16                       *CaseIndexStr,
  IN CHAR16                       *CaseIterationStr,
  IN CHAR16                       *Buffer,
  IN CHAR16                       *FileName
  );

EFI_STATUS
UnloadReportInfor (
  VOID
  );

EFI_STATUS
GetReportInfor (
  OUT CHAR16                      **Buffer
  );

EFI_STATUS
SctReportConfig (
  OUT UINTN               *BufferSize,
  OUT VOID                **Buffer
  );

#endif
