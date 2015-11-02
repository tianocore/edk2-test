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

  TestOutputLibrary.h

Abstract:

  This file defines the EFI Test Output Library Protocol.

  This protocol will be invoked by the standard test library protocol, the test
  logging library protocol, or the other user-defined library protocols.
  Generally a test case should only invoke the standard test library protocol
  or the test logging library protocol to record the output message. It can not
  touch this test output library protocol directly.

--*/

#ifndef _EFI_TEST_OUTPUT_LIBRARY_H_
#define _EFI_TEST_OUTPUT_LIBRARY_H_

//
// Includes
//

#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)

//
// EFI Test Output Library Protocol Definitions
//

#define EFI_TEST_OUTPUT_LIBRARY_GUID        \
  { 0x8bfeab85, 0x83cf, 0x4c7b, 0x9e, 0xcd, 0xcf, 0x14, 0x28, 0x87, 0xe7, 0x12 }

#define EFI_TEST_OUTPUT_LIBRARY_REVISION    0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TEST_OUTPUT_LIBRARY_PROTOCOL EFI_TEST_OUTPUT_LIBRARY_PROTOCOL;

//
// EFI Test Output Library Protocol API - Open
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_OPEN) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  IN  BOOLEAN                                   Overwrite,
  OUT EFI_FILE                                  **FileHandle
  )
/*++

Routine Description:

  Open an output file.

Arguments:

  This          - Test output library protocol instance.

  DevicePath    - Device path of the output file.

  FileName      - File name of the output file.

  Overwrite     - Control write operations. TRUE stands for overwrite the old
                  file, FALSE for append it.

  FileHandle    - Handle for the opened file.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol API - Close
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_CLOSE) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_FILE                                  *FileHandle
  )
/*++

Routine Description:

  Close an output file.

Arguments:

  This          - Test output library protocol instance.

  FileHandle    - File handle to be closed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol API - Write
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_WRITE) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_FILE                                  *FileHandle,
  IN  CHAR16                                    *String
  )
/*++

Routine Description:

  Write a string to the output file.

Arguments:

  This          - Test output library protocol instance.

  FileHandle    - Handle for the opened file.

  String        - Null terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol
//

struct _EFI_TEST_OUTPUT_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TOL_OPEN                          Open;
  EFI_TOL_CLOSE                         Close;
  EFI_TOL_WRITE                         Write;
};

//
// Global ID for EFI Test Output Library Protocol
//

extern EFI_GUID gEfiTestOutputLibraryGuid;

#endif
