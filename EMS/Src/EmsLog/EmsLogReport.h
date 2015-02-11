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
