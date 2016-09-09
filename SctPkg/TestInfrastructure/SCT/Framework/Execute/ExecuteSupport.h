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

  ExecuteSupport.h

Abstract:

  This file provides the support services for test execution.

--*/

#ifndef _EFI_EXECUTE_SUPPORT_H_
#define _EFI_EXECUTE_SUPPORT_H_

//
// EFI_SCT_EXECUTE_INFO
//

typedef struct {
  EFI_SCT_TEST_CASE         *TestCase;

  EFI_SCT_CATEGORY_DATA     *Category;
  EFI_SCT_TEST_FILE         *TestFile;

  EFI_SCT_SKIPPED_CASE      *SkippedCase;

  VOID                      *TestProtocol;
  VOID                      *TestEntry;

  EFI_SCT_LOG_STATE         State;

  UINT32                    Index;
  UINT32                    Iteration;
  UINT32                    Passes;
  UINT32                    Warnings;
  UINT32                    Failures;
} EFI_SCT_EXECUTE_INFO;

//
// Support functions declaration
//

EFI_STATUS
InitializeExecuteInfo (
  IN EFI_SCT_TEST_CASE            *TestCase,
  OUT EFI_SCT_EXECUTE_INFO        *ExecuteInfo
  );

EFI_STATUS
GetFileMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FilePath,
  OUT CHAR16                      **MetaName
  );

EFI_STATUS
GetFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  );

EFI_STATUS
GetKeyFileMetaName(
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FilePath,
  OUT CHAR16                      **MetaName
);

EFI_STATUS
GetKeyFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  );

EFI_STATUS
ResetExecuteTestResults (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

typedef
BOOLEAN
(EFIAPI *EFI_INTERFACE_FILTER) (
  IN  VOID                              *ClientInterface,
  IN  EFI_HANDLE                        SupportHandle,
  IN  EFI_GUID                          *ProtocolGuid
  );

BOOLEAN
IhvInterfaceFilter (
  IN VOID                       *ClientInterface,
  IN EFI_HANDLE                 SupportHandle,
  IN EFI_GUID                   *ProtocolGuid
  );


#endif
