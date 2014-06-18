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

  TestRecoveryLibrary.h

Abstract:

  This file defines the EFI Test Recovery Library Protocol.

--*/

#ifndef _EFI_TEST_RECOVERY_LIBRARY_H_
#define _EFI_TEST_RECOVERY_LIBRARY_H_

//
// Includes
//

//
// EFI Test Recovery Library Protocol Definitions
//

#define EFI_TEST_RECOVERY_LIBRARY_GUID      \
  { 0x7fd8c38d, 0x7c5c, 0x42fc, 0xb0, 0x44, 0x3a, 0x83, 0x4a, 0x61, 0x74, 0x76 }

#define EFI_TEST_RECOVERY_LIBRARY_REVISION  0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TEST_RECOVERY_LIBRARY_PROTOCOL EFI_TEST_RECOVERY_LIBRARY_PROTOCOL;

//
// EFI Test Recovery Library Protocol API - ReadResetRecord
//
typedef
EFI_STATUS
(EFIAPI *EFI_TRL_READ_RESET_RECORD) (
  IN  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL          *This,
  OUT UINTN                                       *Size,
  OUT VOID                                        *Buffer
  )
/*++

Routine Description:

  Reads the information which is recorded before of system reset. It can
  only be used to transfer the data between system reset in one test case. The
  test management system will clean up all recorded information after a test
  case is completed.

Arguments:

  This          - Test recovery library protocol instance.

  Size          - The number of byte returned in the Buffer.

  Buffer        - The buffer is used to restore the output information. The
                  buffer is allocated by the caller and should be larger than
                  1024 bytes.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Recovery Library Protocol API - WriteResetRecord
//
typedef
EFI_STATUS
(EFIAPI *EFI_TRL_WRITE_RESET_RECORD) (
  IN  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL          *This,
  IN  UINTN                                       Size,
  IN  VOID                                        *Buffer
  )
/*++

Routine Description:

  Writes the information which will be used after system reset. It is also used
  to indicate this system reset is scheduled by the test case in plan. The test
  management system will restart this test case if it finds any recorded
  information. So the test case should clean up the recorded information after
  it is restarted.

Arguments:

  This          - Test recovery library protocol instance.

  Size          - The number of byte to be written.

  Buffer        - The buffer is used to restore the output information. This
                  buffer should not larger than 1024 bytes.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Recovery Library Protocol
//

struct _EFI_TEST_RECOVERY_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TRL_READ_RESET_RECORD             ReadResetRecord;
  EFI_TRL_WRITE_RESET_RECORD            WriteResetRecord;
};

//
// Global ID for EFI Test Recovery Library Protocol
//

extern EFI_GUID gEfiTestRecoveryLibraryGuid;

#endif
