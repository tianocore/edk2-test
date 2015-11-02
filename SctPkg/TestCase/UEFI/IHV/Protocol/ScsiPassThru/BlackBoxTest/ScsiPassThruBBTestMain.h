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

  ScsiPassThruBBTestMain.h

Abstract:

  BB test header file of Scsi Pass Through protocol

--*/


#ifndef _SCSI_PASS_THRU_BBTEST_H_
#define _SCSI_PASS_THRU_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/ScsiPassThru.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  SCSI_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

#define  IHV_SCSI_PASS_THRU_PROTOCOL_GUID         \
  { 0x29479dbb, 0x951, 0x43ec, { 0x8a, 0xfa, 0x47, 0x3f, 0x1f, 0x40, 0xbb, 0xbb } }


EFI_STATUS
InitializeBBTestScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetNextDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetChannelFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetTargetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestPassThruFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
VOID
NotifyFunction (
  EFI_EVENT Event,
  VOID      *Context
  );

EFI_STATUS
GetInvalidTargetLun(
  IN       EFI_SCSI_PASS_THRU_PROTOCOL   *ScsiPassThru,
  IN OUT   UINT32                        *Target,
  IN OUT   UINT64                        *Lun
);

EFI_STATUS
GetPresentTargetLun(
  IN       EFI_SCSI_PASS_THRU_PROTOCOL   *ScsiPassThru,
  IN OUT   UINT32                        *Target,
  IN OUT   UINT64                        *Lun
);

//
// Entry GUIDs
//

#define SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID \
  { 0x3d3807c, 0xc647, 0x4d33, { 0xb6, 0xcc, 0xfd, 0x8, 0x5, 0xb4, 0x0, 0xea } }

#define SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0xe9d6e987, 0x5850, 0x4679, { 0xab, 0xc9, 0x77, 0xb, 0xdc, 0x84, 0x69, 0xf4 } }

#define SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xb9be3749, 0x7658, 0x4d87, { 0xb7, 0x39, 0x63, 0x54, 0x5d, 0x82, 0x44, 0xee } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID \
  { 0x23544719, 0x8ffd, 0x47f9, { 0x96, 0x47, 0x68, 0x68, 0x87, 0xa5, 0xaf, 0x30 } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_FUNCTION_AUTO_GUID \
  { 0x8fc44d87, 0x7926, 0x48a9, { 0xbe, 0x55, 0x89, 0x41, 0x5d, 0xcb, 0xe1, 0x96 } }

#define SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0xb6a8c9f8, 0x8894, 0x45aa, { 0x97, 0xeb, 0x8f, 0x7, 0xcd, 0xce, 0x40, 0xee } }

#define SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0xf7c70e6b, 0x885a, 0x4bfa, { 0x94, 0xe3, 0xa2, 0x2d, 0x44, 0x2f, 0x1f, 0xc } }

#define SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0x63ffa935, 0xb7cf, 0x4791, { 0x95, 0xbe, 0xca, 0x3e, 0xb1, 0x44, 0x5f, 0x48 } }

#define SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x1ed1319d, 0x605e, 0x46e9, { 0xb6, 0x6d, 0x1b, 0x97, 0xc9, 0x47, 0x9b, 0x3e } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_CONFORMANCE_AUTO_GUID \
  { 0xfa1c0b95, 0x8a9d, 0x4977, { 0x8f, 0x1b, 0x5a, 0x43, 0x77, 0xf6, 0x2f, 0xcc } }

#define SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0x990e62bc, 0xa197, 0x4b07, { 0xa1, 0x6, 0xe4, 0x6b, 0x2d, 0xcd, 0xf1, 0xa3 } }



#endif

