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
                                                                
  Copyright (c) 2010, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DriverSupportedEfiVersionBBTestMain.h

Abstract:

  BB test header file of Efi Driver Support Efi Version Protocol

--*/


#ifndef _DRIVER_SUPPORTED_EFI_VERSION_BBTEST_H_
#define _DRIVER_SUPPORTED_EFI_VERSION_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <UEFI/Protocol/DriverSupportedEfiVersion.h>
#include <Library/EfiTestLib.h>

#define  DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_TEST_REVISION    0x00010000

#define IHV_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID        \
{                  \
        0xcd0463ca, 0x97cf, 0x499b, 0xb9, 0xf3, 0x8c, 0x82, 0x90, 0x9c, 0x7, 0x89       \
}


EFI_STATUS
InitializeBBTestDriverSupportedEfiVersion (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDriverSupportedEfiVersionProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
BBTestLengthParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFirmwareVersionParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Entry GUIDs
//

#define DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_LENGTH_PARAMETER_AUTO_GUID \
  { 0xecbbdc3, 0x286b, 0x484c, 0x8b, 0x14, 0x67, 0x90, 0x39, 0x50, 0x97, 0xef }

#define DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_FIRMWAREVERSION_PARAMETER_AUTO_GUID \
  { 0xc5a6f8f6, 0x8092, 0x4c0e, 0x90, 0xa5, 0x7a, 0x54, 0xee, 0xc0, 0xd3, 0xc3 }

#endif

