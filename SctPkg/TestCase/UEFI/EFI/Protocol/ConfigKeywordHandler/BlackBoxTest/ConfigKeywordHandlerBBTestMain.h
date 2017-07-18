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
                                                                
  Copyright 2016 - 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Hash2BBTestMain.h

Abstract:

  Test Driver of Config Keyword Handler Protocol header file

--*/

#ifndef _CONFIG_KEYWORD_HANDLER_BB_TEST_MAIN
#define _CONFIG_KEYWORD_HANDLER_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/ConfigKeywordHandler.h>
#include "Guid.h"
#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_REVISION    0x00010000


#define DEPENDENCY_DIR_NAME                 L"Dependency\\ConfigKeywordHandlerBBTest"

#define DRIVER_SAMPLE_NAME                  L"DriverSample.efi"

extern EFI_GUID gBlackBoxEfiLoadedImageProtocolGuid;

//
// Entry GUIDs for Func Test
//
#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x3d2238a7, 0xc736, 0x436b, {0xbd, 0xff, 0xb2, 0x36, 0x1c, 0xfd, 0x21, 0x17 }}

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x631624c4, 0x62bd, 0x4fdf, {0xae, 0x7e, 0x74, 0x30, 0x41, 0x5e, 0xc6, 0x6c }}


//
// Entry GUIDs for Conf Test
//
#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xa180b9b0, 0xcea8, 0x472f, {0x8e, 0x31, 0xc7, 0x89, 0x6c, 0x79, 0xb5, 0x1 }}

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3269d631, 0x42a0, 0x464e, {0xbd, 0x5d, 0xcc, 0x3c, 0xc8, 0xd, 0x8e, 0x3a }}


//
//
//
EFI_STATUS
EFIAPI
InitializeConfigKeywordHandlerBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadConfigKeywordHandlerBBTest (
  IN EFI_HANDLE                   ImageHandle
  );

EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );
  
//
//Test Cases
//
EFI_STATUS
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestSetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif

