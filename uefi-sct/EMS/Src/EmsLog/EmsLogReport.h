/** @file
 
  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsLogReport.h
    
Abstract:

    Data definition for report library

--*/

#ifndef __EMS_REPORT_H__
#define __EMS_REPORT_H__

#include <EmsTypes.h>

#define EMS_REPORT_DIR      "Report"

#define EMS_INDEX_LEN       20
#define EMS_DESCRIPTION_LEN 1000
#define EMS_GUID_LEN        40
#define EMS_NAME_LEN        100

#define EMS_FILE_BUFFER_LEN 100000

typedef struct _EMS_CASE_INFOR {
  struct _EMS_CASE_INFOR  *Next;
  struct _EMS_CASE_INFOR  *Prev;
  INT8                    Index[EMS_INDEX_LEN];
  INT8                    TestName[EMS_NAME_LEN];
  INT8                    TestDescription[EMS_DESCRIPTION_LEN];
  INT8                    Guid[EMS_GUID_LEN];
} EMS_CASE_INFOR;

typedef struct _EMS_REPORT_ITEM {
  struct _EMS_REPORT_ITEM *Next;
  struct _EMS_REPORT_ITEM *Prev;
  UINT32                  PassNumber;
  UINT32                  WarnNumber;
  UINT32                  FailNumber;
  INT8                    TestCategory[EMS_NAME_LEN];
  EMS_CASE_INFOR          *FailCase;
  EMS_CASE_INFOR          *PassCase;
} EMS_REPORT_ITEM;

typedef struct {
  UINT32          TotalPass;
  UINT32          TotalWarn;
  UINT32          TotalFail;
  EMS_REPORT_ITEM *ReportItem;
} EMS_REPORT_INFOR;

typedef struct _EMS_REPORT_GUID {
  struct _EMS_REPORT_GUID *Next;
  struct _EMS_REPORT_GUID *Prev;
  UINT32                  GuidNumber;
  INT8                    Guid[EMS_GUID_LEN];
} EMS_REPORT_GUID;


//
// EMS library GenerateReport API for assertions
//
EFI_STATUS
GenerateReport (
  INT8               *ReportName
  )
/*++

Routine Description:

  Generate the final log report for assertion

Arguments:

  ReportName  - the report file name

Returns:

  EFI_SUCCESS - Generate the final log report successfully
  OTHERS        - Something failed.

--*/
;

//
// EMS library GenerateReportCase API for cases
//
EFI_STATUS
GenerateReportCase (
  INT8               *ReportName
  )
/*++

Routine Description:

  Generate the final log report for case

Arguments:

  ReportName  - the report file name

Returns:

  EFI_SUCCESS - Generate the final log report successfully
  OTHERS        - Something failed.

--*/
;

#endif // __EMS_REPORT_H__
