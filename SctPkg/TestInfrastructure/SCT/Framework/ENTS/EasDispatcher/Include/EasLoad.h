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

  EasLoad.h

Abstract:

  ENTS extended data services declarations.

--*/

#ifndef _EFI_LOAD_H_
#define _EFI_LOAD_H_

//
// External functions declarations
//
EFI_STATUS
EntsLoadSupportFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive
  )
/*++

Routine Description:

  Load all support files.

Arguments:

  DevicePath  - Device path of the test files.
  FilePath    - Path of the test files.
  Recursive   - Resursively.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EntsUnloadSupportFiles (
  IN SCT_LIST_ENTRY               *TestAppList
  )
/*++

Routine Description:

  Unload all support files.

Arguments:

  TestAppList - Pointer to the test file list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EntsLoadTestFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive
  )
/*++

Routine Description:

  Load all application files.

Arguments:

  DevicePath  - Device path of the test files.
  FilePath    - Path of the test files.
  Recursive   - Resursively.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Invalid parameter.
  Others                - Operation failed.

--*/
;

EFI_STATUS
EntsUnloadTestFiles (
  IN SCT_LIST_ENTRY               *TestAppList
  )
/*++

Routine Description:

  Unload all test files.

Arguments:

  TestAppList - Pointer to the test file list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Operation failed.

--*/
;

EFI_STATUS
EntsFindTestFileByName (
  IN CHAR16                       *CmdName,
  IN OUT EFI_NETWORK_TEST_FILE    **TestFile
  )
/*++

Routine Description:

  Find a test file by a name.

Arguments:

  CmdName   - Command name.
  TestFile  - Pointer to the testFile structure.
  
Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
;

#endif
