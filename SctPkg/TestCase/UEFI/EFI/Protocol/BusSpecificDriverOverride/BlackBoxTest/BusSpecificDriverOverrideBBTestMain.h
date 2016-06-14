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

  BusSpecificDriverOverrideBBTestMain.h

Abstract:

  BB test header file of Bus Specific Driver Override Protocol

--*/


#ifndef _BUS_SPECIFIC_DRIVER_OVERRIDE_BBTEST_H_
#define _BUS_SPECIFIC_DRIVER_OVERRIDE_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/BusSpecificDriverOverride.h>

#define  BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION    0x00010000


extern   EFI_EVENT                         TimerEvent;

EFI_STATUS
InitializeBBTestBusSpecificDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestBusSpecificDriverOverrideProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );


EFI_STATUS
BBTestGetDriverFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LocateDevicePathFromBusOverride(
  IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL    *BusOverride,
  IN EFI_DEVICE_PATH_PROTOCOL                     **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib
  );

//
// Entry GUIDs
//

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_FUNCTION_MANUAL_GUID \
  { 0xaa0ec76e, 0x28c, 0x4fde, { 0xac, 0x44, 0xe3, 0xd4, 0x9b, 0x7c, 0x67, 0x33 } }

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_CONFORMANCE_GUID \
  { 0x4a1352a6, 0x49a2, 0x4075, { 0xa0, 0x6f, 0xd8, 0x9, 0xb4, 0x6e, 0x5e, 0xf2 } }

#endif
