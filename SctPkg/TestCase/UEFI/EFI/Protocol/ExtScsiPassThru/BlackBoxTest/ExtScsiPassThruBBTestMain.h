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

  ExtScsiPassThruBBTestMain.h

Abstract:

  BB test header file of Extended Scsi Pass Through protocol

--*/


#ifndef _EXT_SCSI_PASS_THRU_BBTEST_H_
#define _EXT_SCSI_PASS_THRU_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/ExtScsiPassThru.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  EXT_SCSI_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
InitializeBBTestExtScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestExtScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetNextTargetLunFunctionAutoTest (
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
BBTestResetTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetNextTargetFunctionAutoTest (
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
BBTestGetNextTargetLunConformanceAutoTest (
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
BBTestResetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetNextTargetConformanceAutoTest (
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
BufToUHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  );

EFI_STATUS
GetInvalidTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
);


 EFI_STATUS
GetPresentTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
);

//
// Entry GUIDs
//

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xacc59919, 0xf5a5, 0x4afd, { 0x94, 0x4a, 0xb1, 0x56, 0xbe, 0x57, 0x11, 0x4b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0xbdfb7a19, 0x1c3b, 0x4d83, { 0xa0, 0x4a, 0xf1, 0x45, 0x3d, 0xea, 0x2b, 0xb6 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0x5c119d86, 0xe670, 0x4959, { 0x9c, 0x21, 0xab, 0xac, 0xdb, 0xcc, 0x7b, 0xe1 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID \
  { 0xe8de6d6a, 0x609a, 0x4d57, { 0xa6, 0xc5, 0xc4, 0xb0, 0xc6, 0x5f, 0xbf, 0x73 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xa7930dd1, 0x1c27, 0x48c4, { 0x8a, 0x84, 0xbb, 0x22, 0x62, 0x95, 0xe8, 0x24 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_FUNCTION_AUTO_GUID \
  { 0xe745ccbe, 0x1182, 0x4068, { 0xa9, 0xbc, 0x58, 0xc4, 0xba, 0x33, 0xa6, 0xc4 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0x5fc224f5, 0x8026, 0x4e7f, { 0x81, 0x54, 0xb5, 0x92, 0x4a, 0xf8, 0x2b, 0xd5 } }


#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0xb4c77246, 0x1855, 0x4f4f, { 0xb7, 0xb1, 0x1, 0x4b, 0x7d, 0xda, 0x29, 0x41 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0xe13aeea0, 0x104f, 0x4a54, { 0x8c, 0x5b, 0xa8, 0x34, 0x4a, 0x99, 0x55, 0xe2 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x8a2ebb7, 0x309f, 0x4587, { 0x80, 0xe, 0xe5, 0xa5, 0x28, 0x9d, 0xd, 0x1 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x7608672a, 0x98f1, 0x485c, { 0x8e, 0x11, 0x19, 0x5a, 0x7e, 0x2c, 0xc8, 0x9b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_CONFORMANCE_AUTO_GUID \
  { 0x5b7ee5e0, 0xcee, 0x4981, { 0xa2, 0x83, 0x35, 0x37, 0x68, 0xe4, 0xcc, 0xf5 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0xab534381, 0x9a15, 0x4de2, { 0xae, 0x98, 0x83, 0x88, 0x87, 0xe3, 0xdc, 0x3a } }

#endif

