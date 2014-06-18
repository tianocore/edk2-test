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

#define IHV_EXT_SCSI_PASS_THRU_PROTOCOL_GUID \
  { 0x9d5fc9db, 0x2f5d, 0x4a92, { 0xa4, 0x2a, 0xef, 0xc0, 0xb7, 0x1e, 0xa1, 0x3d } }

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
  { 0x4fa4100c, 0xf525, 0x49b6, { 0x96, 0xe2, 0x11, 0x8c, 0x27, 0x4e, 0x38, 0x2b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0x46ac5e82, 0x87a4, 0x4c3c, { 0xbe, 0x79, 0xf6, 0x11, 0x32, 0x19, 0x45, 0x51 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xb6f781f9, 0xd987, 0x485d, { 0xbf, 0x44, 0xbc, 0x9d, 0x23, 0xfa, 0xc0, 0x87 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID \
  { 0xe1dbfca, 0xb25f, 0x4384, { 0x87, 0xdd, 0x25, 0xfb, 0xfd, 0x4e, 0xbe, 0x3 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xd154dc51, 0x7b45, 0x45c2, { 0x83, 0x5e, 0xdd, 0x94, 0x9a, 0xc5, 0xad, 0x28 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_FUNCTION_AUTO_GUID \
  { 0x27852ae2, 0xfd6c, 0x4519, { 0x88, 0x64, 0x76, 0x16, 0x1a, 0x3b, 0xfc, 0x53 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0x5d5699c4, 0x5f6e, 0x477d, { 0xa6, 0x6f, 0x3b, 0x2c, 0x61, 0x7f, 0xac, 0xf8 } }


#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0xb8d48dc7, 0x574b, 0x467e, { 0xae, 0xc8, 0x5, 0x96, 0x8b, 0xb7, 0xde, 0x21 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0xdf3b1109, 0xba8b, 0x435c, { 0xa2, 0x2b, 0x4c, 0xe9, 0x5a, 0x64, 0xa4, 0x46 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0xe8a6734, 0xdb9c, 0x45f4, { 0xb4, 0x4f, 0xbe, 0xc1, 0x8d, 0x41, 0xc6, 0x8b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0xa8a6fc0a, 0x7f72, 0x4826, { 0x91, 0x6b, 0xdb, 0x98, 0x3f, 0xeb, 0xbe, 0x9c } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_CONFORMANCE_AUTO_GUID \
  { 0xf8216443, 0x39c9, 0x4a5a, { 0x8c, 0xbc, 0xa8, 0x31, 0x1e, 0x26, 0xd6, 0xbc } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0x73f5091b, 0xe6ae, 0x452d, { 0xb9, 0xb0, 0x44, 0x27, 0xb8, 0x84, 0x20, 0x1f } }

#endif

