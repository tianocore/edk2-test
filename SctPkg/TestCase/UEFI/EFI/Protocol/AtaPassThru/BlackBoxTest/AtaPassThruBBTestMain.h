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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AtaPassThruBBTestMain.h

Abstract:

  BB test header file of ATA Pass Through protocol

--*/


#ifndef _ATA_PASS_THRU_BBTEST_H_
#define _ATA_PASS_THRU_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/AtaPassThru.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  ATA_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

#define EFI_ATA_STALL_1_SECOND       10000000

EFI_STATUS
InitializeBBTestAtaPassThru (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
  );

EFI_STATUS
BBTestAtaPassThruProtocolUnload (
  IN EFI_HANDLE    ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetNextPortFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestGetDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestResetPortFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestResetDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestGetNextDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestPassThruFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestGetNextPortConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestGetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestResetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

EFI_STATUS
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  );

//
// Other function declaration section
//
VOID
NotifyFunction (
  EFI_EVENT    Event,
  VOID         *Context
  );
/**
 *  Function scan all legal Port, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetInvalidPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  OUT   UINT16                        *InvalidPort
);
/**
 *  Function scan all legal Port
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetValidPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  OUT   UINT16                        *Port
);
/**
 *  Function scan all legal PortMultiplierPort, find the max of them, 
 *  and add 1 to the max, get the invalid
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @return EFI_SUCCESS if get the invalid Port successfully.
 */
EFI_STATUS
GetInvalidPortMultiplierPort(
  IN    EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  IN    UINT16                        Port,
  OUT   UINT16                        *InvalidPortMultiplierPort
);
/**
 *  Function check return status
 *  @param AtaStatus.
 *  @return TRUE if identify device successfully.
 */
BOOLEAN
NormalOutput(
  IN    UINT8    AtaStatus
);
/**
 *  Function probe all legal port, find valid PortMultiplierPort
 *  which point to the present device on port
 *  @param a pointer of EFI_ATA_PASS_THRU_PROTOCOL.
 *  @param a pointer of Port.
 *  @param a pointer of PortMultiplierPort.
 *  @param a pointer of AtaStatus.
 *  @return EFI_SUCCESS if get the valid device successfully.
 */
 EFI_STATUS
GetPresentDevice(
  IN       EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  IN OUT   UINT16                        *Port,
  IN OUT   UINT16                        *PortMultiplierPort,
     OUT   UINT8*                        AtaStatus
);
//
// Entry GUIDs
//

#define ATA_PASS_THRU_PROTOCOL_GET_NEXT_PORT_FUNCTION_AUTO_GUID \
  { 0xbcc59919, 0xf5a5, 0x4afd, { 0x94, 0x4a, 0xb1, 0x56, 0xbe, 0x57, 0x11, 0x4b } }

#define ATA_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0xcdfb7a19, 0x1c3b, 0x4d83, { 0xa0, 0x4a, 0xf1, 0x45, 0x3d, 0xea, 0x2b, 0xb6 } }

#define ATA_PASS_THRU_PROTOCOL_GET_DEVICE_FUNCTION_AUTO_GUID \
  { 0x6c119d86, 0xe670, 0x4959, { 0x9c, 0x21, 0xab, 0xac, 0xdb, 0xcc, 0x7b, 0xe1 } }

#define ATA_PASS_THRU_PROTOCOL_RESET_PORT_FUNCTION_AUTO_GUID \
  { 0xf8de6d6a, 0x609a, 0x4d57, { 0xa6, 0xc5, 0xc4, 0xb0, 0xc6, 0x5f, 0xbf, 0x73 } }

#define ATA_PASS_THRU_PROTOCOL_RESET_DEVICE_FUNCTION_AUTO_GUID \
  { 0xb7930dd1, 0x1c27, 0x48c4, { 0x8a, 0x84, 0xbb, 0x22, 0x62, 0x95, 0xe8, 0x24 } }

#define ATA_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID \
  { 0xf745ccbe, 0x1182, 0x4068, { 0xa9, 0xbc, 0x58, 0xc4, 0xba, 0x33, 0xa6, 0xc4 } }

#define ATA_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0x6fc224f5, 0x8026, 0x4e7f, { 0x81, 0x54, 0xb5, 0x92, 0x4a, 0xf8, 0x2b, 0xd5 } }

#define ATA_PASS_THRU_PROTOCOL_MODE_CONFORMANCE_AUTO_GUID \
  { 0x09ec9bf2, 0x743f, 0x4eed, 0x82, 0xbc, 0x35, 0xf2, 0xcc, 0x56, 0x45, 0xda }

#define ATA_PASS_THRU_PROTOCOL_GET_NEXT_PORT_CONFORMANCE_AUTO_GUID \
  { 0xc4c77246, 0x1855, 0x4f4f, { 0xb7, 0xb1, 0x1, 0x4b, 0x7d, 0xda, 0x29, 0x41 } }

#define ATA_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0xf13aeea0, 0x104f, 0x4a54, { 0x8c, 0x5b, 0xa8, 0x34, 0x4a, 0x99, 0x55, 0xe2 } }

#define ATA_PASS_THRU_PROTOCOL_GET_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x9a2ebb7, 0x309f, 0x4587, { 0x80, 0xe, 0xe5, 0xa5, 0x28, 0x9d, 0xd, 0x1 } }

#define ATA_PASS_THRU_PROTOCOL_RESET_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x8608672a, 0x98f1, 0x485c, { 0x8e, 0x11, 0x19, 0x5a, 0x7e, 0x2c, 0xc8, 0x9b } }

#define ATA_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x6b7ee5e0, 0xcee, 0x4981, { 0xa2, 0x83, 0x35, 0x37, 0x68, 0xe4, 0xcc, 0xf5 } }

#define ATA_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0xbb534381, 0x9a15, 0x4de2, { 0xae, 0x98, 0x83, 0x88, 0x87, 0xe3, 0xdc, 0x3a } }

#endif

