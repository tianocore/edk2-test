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

  PlatformDriverOverrideBBTestMain.h

Abstract:

  BB test header file of Platform Driver Override protocol

--*/


#ifndef _PLATFORM_DRIVER_OVERRIDE_BBTEST_H_
#define _PLATFORM_DRIVER_OVERRIDE_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/PlatformDriverOverride.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  PLATFORM_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION    0x00010000

#define  IHV_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID         \
  { 0x5e344e28, 0x3bc0, 0x4c23, 0x8d, 0x5f, 0xfb, 0xed, 0x3f, 0xb2, 0x7e, 0x72 }

EFI_HANDLE DriverImageHandle;

EFI_STATUS
InitializeBBTestPlatformDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestPlatformDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetDriverFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverPathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestDriverLoadedFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverPathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestDriverLoadedConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//

//
// Entry GUIDs
//
#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_FUNCTION_AUTO_GUID         \
  { 0x898caad7, 0xf932, 0x4f13, 0x8b, 0x42, 0x2e, 0x2b, 0x7c, 0x53, 0x52, 0xb3 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_FUNCTION_AUTO_GUID    \
  { 0xd4db9e09, 0x3da8, 0x42c9, 0xbc, 0x85, 0x4f, 0x9c, 0xbc, 0x63, 0x36, 0xcc }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_FUNCTION_AUTO_GUID      \
  { 0xe6db5b7f, 0x289f, 0x4731, 0xaf, 0x1a, 0x17, 0xa2, 0x4e, 0x30, 0xeb, 0x4f }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_CONFORMANCE_AUTO_GUID      \
  { 0x719b0d60, 0x5606, 0x47ab, 0x88, 0xf9, 0x9e, 0x4a, 0xe1, 0xf5, 0x98, 0x29 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_CONFORMANCE_AUTO_GUID \
  { 0xa1578d06, 0xd8e2, 0x427d, 0x9a, 0x20, 0x57, 0x8d, 0x0a, 0x4a, 0x12, 0x73 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_CONFORMANCE_AUTO_GUID   \
  { 0x7f57365f, 0xdd8b, 0x4094, 0x8b, 0xeb, 0xaa, 0xda, 0x63, 0x10, 0x68, 0x15 }


#endif

