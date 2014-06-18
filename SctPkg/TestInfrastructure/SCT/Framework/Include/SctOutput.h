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

  SctOutput.h

Abstract:

  This file provides a default test output library.

--*/

#ifndef _EFI_SCT_OUTPUT_H_
#define _EFI_SCT_OUTPUT_H_

//
// Private interface data structures of TestOutput protocol
//

#define TEST_OUTPUT_PRIVATE_DATA_SIGNATURE  EFI_SIGNATURE_32('T','O','L','I')

#define TEST_OUTPUT_PRIVATE_DATA_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//
typedef struct _TEST_OUTPUT_FILE TEST_OUTPUT_FILE;

struct _TEST_OUTPUT_FILE {
  TEST_OUTPUT_FILE            *Next;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  CHAR16                      *FileName;
  EFI_FILE_HANDLE             FileHandle;
  UINTN                       OpenCount;
};

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          TestOutput;
  TEST_OUTPUT_FILE                          *OutputFileList;
} TEST_OUTPUT_PRIVATE_DATA;

#define TEST_OUTPUT_PRIVATE_DATA_FROM_THIS(a) \
  CR(a, TEST_OUTPUT_PRIVATE_DATA, TestOutput, TEST_OUTPUT_PRIVATE_DATA_SIGNATURE)

//
// Global variables
//

extern EFI_TEST_OUTPUT_LIBRARY_PROTOCOL *gOutputProtocol;

#endif
