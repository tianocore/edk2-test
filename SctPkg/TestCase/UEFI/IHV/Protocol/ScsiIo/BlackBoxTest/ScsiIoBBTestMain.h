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

  ScsiIoBBTestMain.h

Abstract:

  BB test header file of Scsi Io protocol

--*/


#ifndef _SCSI_IO_BBTEST_H_
#define _SCSI_IO_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/ScsiIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  SCSI_IO_PROTOCOL_TEST_REVISION    0x00010000

#define	 IHV_SCSI_IO_PROTOCOL_GUID \
   { 0x840e7711, 0x7308, 0x4cf8, { 0x9b, 0xa5, 0xcd, 0x7b, 0xe0, 0xd5, 0x7f, 0x74 } }


EFI_STATUS
InitializeBBTestScsiIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestScsiIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetDeviceTypeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDeviceLocationFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetBusFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestExecuteScsiCommandFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDeviceTypeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDeviceLocationConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetBusConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestExecuteScsiCommandConformanceAutoTest (
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

//
// Entry GUIDs
//

#define SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_FUNCTION_AUTO_GUID \
  { 0x7c7a9bb4, 0x2932, 0x41c1, { 0x9f, 0x22, 0x55, 0x9f, 0xa8, 0xd4, 0xeb, 0xa6 } }

#define SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_FUNCTION_AUTO_GUID \
  { 0x8b48ac68, 0x9d43, 0x4ba0, { 0x81, 0x15, 0x5c, 0x7b, 0xdc, 0x47, 0x1a, 0x45 } }

#define SCSI_IO_PROTOCOL_RESET_BUS_FUNCTION_AUTO_GUID \
  { 0xaf2f1d4, 0x7a25, 0x477b, { 0xb1, 0xad, 0xcc, 0x97, 0x6c, 0xf6, 0x70, 0x63 } }

#define SCSI_IO_PROTOCOL_RESET_DEVICE_FUNCTION_AUTO_GUID \
  { 0x33c83014, 0x3b02, 0x4804, { 0x80, 0x42, 0x30, 0xa8, 0x13, 0xa9, 0x9b, 0x18 } }

#define SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_FUNCTION_AUTO_GUID \
  { 0xca8e7fbb, 0x8cf7, 0x4f50, { 0x8d, 0x42, 0x7d, 0x5, 0x70, 0xf9, 0x23, 0x9c } }


#define SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_CONFORMANCE_AUTO_GUID \
  { 0xfaa0d5b6, 0xfd65, 0x439c, { 0x95, 0xfd, 0xe4, 0xa7, 0x2e, 0xe5, 0x11, 0xf4 } }

#define SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_CONFORMANCE_AUTO_GUID \
  { 0x6993f924, 0xed4f, 0x4866, { 0xa7, 0x82, 0xa9, 0x85, 0x68, 0xe5, 0xc, 0x19 } }

#define SCSI_IO_PROTOCOL_RESET_BUS_CONFORMANCE_AUTO_GUID \
  { 0xc1a0999a, 0xa6bc, 0x4ff7, { 0x92, 0xc1, 0x9, 0x9, 0x4e, 0xb1, 0x25, 0x40 } }

#define SCSI_IO_PROTOCOL_RESET_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x75f7304a, 0x3f80, 0x4919, { 0xb6, 0xe3, 0x4a, 0x39, 0xa6, 0x70, 0x1c, 0xcf } }

#define SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_CONFORMANCE_AUTO_GUID \
  { 0xc32a97a5, 0xdcc1, 0x4773, { 0x8c, 0x7f, 0xf6, 0xab, 0xfa, 0x85, 0xa4, 0x21 } }

#endif

