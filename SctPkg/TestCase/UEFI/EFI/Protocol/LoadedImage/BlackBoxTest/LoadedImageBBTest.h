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

  ImageTest.h

Abstract:

  head file for Loaded Image Protocol Black Box Test

--*/

#ifndef _LOADED_IMAGE_BBTEST_H
#define _LOADED_IMAGE_BBTEST_H

#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "LoadedImageBBTestProtocolDefinition.h"
#include "Guid.h"

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define LOADED_IMAGE_PROTOCOL_TEST_REVISION 0x00010000
//
// directory and file name definition
//
#define DEPENDENCY_DIR_NAME                 L"Dependency\\LoadedImageBBTest"

#define EFI_APPLICATION_1_NAME              L"LoadedImageApplication1.efi"
#define EFI_APPLICATION_2_NAME              L"LoadedImageApplication2.efi"

#define BOOT_SERVICES_DRIVER_1_NAME         L"LoadedImageBootServicesDriver1.efi"
#define BOOT_SERVICES_DRIVER_2_NAME         L"LoadedImageBootServicesDriver2.efi"

#define RUNTIME_SERVICES_DRIVER_1_NAME      L"LoadedImageRuntimeServicesDriver1.efi"
#define RUNTIME_SERVICES_DRIVER_2_NAME      L"LoadedImageRuntimeServicesDriver2.efi"

extern EFI_HANDLE   mImageHandle;

#define MAX_STRING_LEN      250

typedef struct {
  UINTN     ProtocolIndex;
  VOID      *Registration[6];
} NOTIFY_CONTEXT;

//////////////////////////////////////////////////////////////////////////////
//
// Test Entry GUIDs
//
#define LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0xdebe1157, 0x53d2, 0x42a1, {0xb6, 0xde, 0xe0, 0xd4, 0x6c, 0x9a, 0xce, 0xd7} }

#define LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x524114f0, 0xfb32, 0x494b, { 0x81, 0x4d, 0x95, 0x97, 0x5, 0x9e, 0xe5, 0xc5} }

//
// Functions definitions
//
EFI_STATUS
InitializeBBTestLoadedImageProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestLoadedImageProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


//
// TDS 3.1
//
EFI_STATUS
BBTestLoadedImageTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
BBTestLoadedImageTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );

VOID
TestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );
#endif
