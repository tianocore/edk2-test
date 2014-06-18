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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ProtocolHandlerBBTest.h

Abstract:

  head file of test driver of Protocol Handler Boot Services

--*/

#ifndef _PROTOCOL_HANDLER_BBTEST_H
#define _PROTOCOL_HANDLER_BBTEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"

#include EFI_PROTOCOL_DEFINITION (PlatformDriverOverride)

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_REVISION  0x00010002

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_GUID      \
  { 0x58688B05, 0xF5C2, 0x4e8b, 0xA0, 0x35, 0xC2, 0x47, 0xD6, 0xA4, 0x0E, 0xB4 }

#define INVALID_HANDLE  0xffffffff

extern EFI_HANDLE                   mImageHandle;
extern EFI_DEVICE_PATH_PROTOCOL     *mDevicePath;
extern CHAR16                       *mFilePath;

#define TPL_ARRAY_SIZE 3

extern EFI_TPL TplArray [TPL_ARRAY_SIZE];

//
// Why need to stall, need more investigation later
//
#define STALL_10_SECONDS    10000000 // in microsecond unit

#define MAX_STRING_LEN      250

#define DEPENDENCY_DIR_NAME   L"Dependency\\ProtocolHandlerServicesBBTest"


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Consistency Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0101 \
 {0x6df68724, 0x5d03, 0x4555, {0x9f, 0xdc, 0xab, 0x4c, 0xe4, 0x2b, 0x45, 0x9} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0102 \
 {0xc46151f4, 0x362f, 0x41f6, {0x8b, 0xbe, 0x81, 0xd0, 0xc6, 0xa9, 0x38, 0x1f} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0103 \
 {0x9fef66c1, 0x3509, 0x4e88, {0x84, 0x6d, 0xb9, 0xcc, 0x26, 0x4f, 0x69, 0xbc} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0104 \
 {0x91666998, 0x769f, 0x4075, {0x8d, 0x43, 0xc5, 0xf3, 0x91, 0x73, 0x64, 0x53} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0105 \
 {0xb6de8de0, 0x7375, 0x4804, {0xa0, 0x29, 0x9e, 0xd0, 0xcb, 0x43, 0xf7, 0x4d} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0106 \
 {0xdb11a27e, 0x2fc0, 0x42f0, {0xa0, 0xc6, 0xf1, 0x2b, 0xc2, 0xe2, 0x55, 0xe3} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0107 \
 {0xa829fd94, 0xb308, 0x4b8f, {0x87, 0x3f, 0x1e, 0xaf, 0xf3, 0x54, 0x64, 0xbc} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0108 \
 {0x6bae06d3, 0x3be7, 0x480e, {0x9e, 0x71, 0x33, 0x2a, 0xd0, 0xc8, 0x21, 0x3e} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0109 \
 {0x231e4965, 0xfda4, 0x4fa2, {0x8a, 0xe2, 0x8c, 0x79, 0x2, 0xc5, 0x7, 0xe9} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0110 \
 {0x852c03c5, 0x5ff1, 0x48e6, {0xa8, 0xa4, 0x49, 0x6e, 0xa1, 0x14, 0x8a, 0x33} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0111 \
 {0x624e28e8, 0x78bc, 0x4d77, {0xab, 0x85, 0xd2, 0xcb, 0xd3, 0x74, 0x4e, 0x21} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0112 \
 {0xf02e4084, 0x6fd5, 0x4b01, {0x8c, 0x3e, 0xac, 0xc9, 0x59, 0xfb, 0x6b, 0xa0} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0113 \
 {0xf9df2097, 0x7c10, 0x4551, {0x91, 0x4c, 0x55, 0x11, 0x92, 0xc0, 0x19, 0x81} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0114 \
 {0x85302e6f, 0x328b, 0x407b, {0xbd, 0x6d, 0x83, 0x5d, 0xd5, 0x4b, 0xa5, 0x4b} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0115 \
 {0x6b57a087, 0xf432, 0x4da7, {0xab, 0x65, 0xa3, 0xbc, 0x2f, 0x2c, 0xe3, 0xf1} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0116 \
 {0xb6c90cce, 0x9063, 0x4a76, {0xb8, 0x2d, 0xca, 0xd4, 0x19, 0x1e, 0x75, 0x14} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0117 \
 {0x94eedbec, 0x55ca, 0x442e, {0xb9, 0x9f, 0x7, 0x88, 0xb8, 0xe5, 0x1c, 0x10} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Interface Function Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0200 \
 {0xedc7240b, 0x6a14, 0x45d4, {0x93, 0x7b, 0xa2, 0xb6, 0x2c, 0x51, 0x12, 0x7b} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0201 \
 {0x4aa7dd8f, 0xe3c3, 0x434d, {0xae, 0x27, 0x8c, 0x9d, 0xa6, 0x6f, 0x58, 0xa3} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0202 \
 {0x8188cfec, 0x5094, 0x41bb, {0x89, 0x4d, 0x4f, 0x75, 0xd8, 0x42, 0xf5, 0xfc} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0203 \
 {0xcdf41a28, 0xec2a, 0x4b25, {0x92, 0x2c, 0x77, 0xb0, 0xec, 0x18, 0xc7, 0x97} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0204 \
 {0xb6a82616, 0xe08e, 0x4226, {0xa8, 0xe2, 0xe6, 0x91, 0x2b, 0xaa, 0x8e, 0x8c} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0205 \
 {0x717259a7, 0x658c, 0x4616, {0xb5, 0x2c, 0x6c, 0x8f, 0x66, 0x1e, 0xa7, 0x26} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0206 \
 {0x283ccdda, 0xd4cd, 0x4bd1, {0x8a, 0x9d, 0xa4, 0xae, 0xf1, 0xa7, 0xa2, 0x14} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0207 \
 {0x11779290, 0x1b6e, 0x4a3f, {0xab, 0xad, 0x8, 0x16, 0xeb, 0xca, 0x6e, 0x5f} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0208 \
 {0xa21ffa59, 0x9a2, 0x46d4, {0xa1, 0xff, 0x94, 0xd5, 0xc6, 0x6, 0x14, 0x91} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0209 \
 {0xd689e19d, 0x54fe, 0x40dc, {0x91, 0x18, 0xb9, 0xab, 0xf2, 0xc0, 0x0, 0x48} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0210 \
 {0xe5d3c7d0, 0x1cf8, 0x4cc1, {0x8f, 0x0, 0xcc, 0x91, 0xac, 0xf2, 0x88, 0x9e} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0211 \
 {0x8e436aaf, 0x37e9, 0x4190, {0x8d, 0xc7, 0x57, 0x99, 0xd4, 0x76, 0x9b, 0x19} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0212 \
 {0xc1126254, 0x8fd3, 0x4170, {0xa0, 0xa1, 0x99, 0xd4, 0xce, 0xe2, 0x14, 0xcb} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0213 \
 {0x7a4b18a0, 0x7b00, 0x4786, {0x81, 0x28, 0x56, 0x4f, 0x3b, 0xa4, 0x1c, 0xe1} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0214 \
 {0x4f00a0c1, 0x77bf, 0x4ce9, {0xb4, 0xa6, 0x57, 0x89, 0x76, 0xdf, 0x52, 0x88} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0215 \
 {0xd0bb122f, 0x231e, 0x4eef, {0x94, 0xd4, 0x4e, 0x3, 0xa7, 0x9c, 0x46, 0x9d} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0216 \
 {0x11b44246, 0xa65e, 0x4832, {0x85, 0x89, 0x8f, 0x60, 0x69, 0x29, 0xc9, 0xfb} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0217 \
 {0x89fbae4a, 0x6132, 0x44e0, {0xbb, 0xf0, 0xb, 0x5c, 0x3c, 0xa8, 0xa2, 0xa5} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0218 \
 {0x705e2497, 0x1b8f, 0x4307, {0x91, 0xe1, 0xf3, 0x3f, 0x2f, 0x2b, 0x55, 0x6} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0219 \
 {0x2aeea797, 0xc967, 0x463e, {0xbb, 0xbc, 0x1d, 0x24, 0x90, 0xd1, 0x7c, 0x91} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Combination Test
//
#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0301 \
 {0x9872d562, 0xa6dd, 0x4b02, {0x80, 0x73, 0x52, 0xe7, 0xb8, 0x21, 0xbc, 0x3d} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0302 \
 {0x1e97fd0c, 0x1a8d, 0x4961, {0x8f, 0xa2, 0xaf, 0xb4, 0xc0, 0x8a, 0xd0, 0xaa} }

#define PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0303 \
 {0xc64c46fa, 0x3789, 0x4c3f, {0xbc, 0x39, 0x82, 0x36, 0xd, 0x22, 0x53, 0x27} }

//
// Functions for MainTest.c
//
EFI_STATUS
InitializeBBTestProtocolHandlerBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestProtocolHandlerBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
InitializeGlobalData ();

VOID
ReleaseGlobalData ();

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestInstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
BBTestUninstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
BBTestReinstallProtocolInterfaceConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
BBTestRegisterProtocolNotifyConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.5
//
EFI_STATUS
BBTestInstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.6
//
EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.7
//
EFI_STATUS
BBTestLocateHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.8
//
EFI_STATUS
BBTestLocateHandleBufferConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.9
//
EFI_STATUS
BBTestHandleProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.10
//
EFI_STATUS
BBTestLocateProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.11
//
EFI_STATUS
BBTestLocateDevicePathConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.12
//
EFI_STATUS
BBTestProtocolsPerHandleConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.13
//
EFI_STATUS
BBTestOpenProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.14
//
EFI_STATUS
BBTestCloseProtocolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.15
//
EFI_STATUS
BBTestOpenProtocolInformationConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.16
//
EFI_STATUS
BBTestConnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.17
//
EFI_STATUS
BBTestDisconnectControllerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Interface Function Test
//

//
// TDS 4.1
//
EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.6
//
EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.7
//
EFI_STATUS
BBTestLocateHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.8
//
EFI_STATUS
BBTestLocateHandleBufferInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.9
//
EFI_STATUS
BBTestHandleProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.10
//
EFI_STATUS
BBTestLocateProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.11
//
EFI_STATUS
BBTestLocateDevicePathInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.12
//
EFI_STATUS
BBTestProtocolsPerHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.13
//
EFI_STATUS
BBTestOpenProtocolInterfaceTest111 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.14
//
EFI_STATUS
BBTestOpenProtocolInterfaceTest222 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.15
//
EFI_STATUS
BBTestOpenProtocolInterfaceTest333 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.16
//
EFI_STATUS
BBTestCloseProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.17
//
EFI_STATUS
BBTestOpenProtocolInformationInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.18
//
EFI_STATUS
BBTestConnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.19
//
EFI_STATUS
BBTestDisconnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint Functions for InstallProtocolInterface()
//
EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for UninstallProtocolInterface()
//

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ReinstallProtocolInterface()
//

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ReinstallProtocolInterface()
//

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestRegisterProtocolNotifyInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for InstallMultipleProtocolInterfaces()
//

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for UninstallMultipleProtocolInterfaces()
//

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for SctLocateHandle ()
//

EFI_STATUS
BBTestLocateHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateHandleInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateHandleInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateHandleInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for LocateHandleBuffer()
//

EFI_STATUS
BBTestLocateHandleBufferInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateHandleBufferInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateHandleBufferInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for HandleProtocol()
//

EFI_STATUS
BBTestHandleProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for SctLocateProtocol ()
//

EFI_STATUS
BBTestLocateProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLocateProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for LocateDevicePath()
//

EFI_STATUS
BBTestLocateDevicePathInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ProtocolsPerHandle()
//

EFI_STATUS
BBTestProtocolsPerHandleInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest111()
//

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest111CheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest222()
//

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest222CheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for BBTestOpenProtocolInterfaceTest333
//

EFI_STATUS
BBTestOpenProtocolInterfaceTest333CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest333CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestOpenProtocolInterfaceTest333CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for CloseProtocol
//

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCloseProtocolInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for OpenProtocolInformation
//

EFI_STATUS
BBTestOpenProtocolInformationInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for ConnectController()
//

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint7_13 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint11 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint12 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint14 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint15 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestConnectControllerInterfaceTestCheckPoint16 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint Functions for DisconnectController()
//

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestDisconnectControllerInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

///////////////////////////////////////////////////////////////////////////////
//
// Functions for Combination Test
//

//
// TDS 5.1
//
EFI_STATUS
BBTestCombinationTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
BBTestCombinationTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
BBTestCombinationTest3 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint Functions
//

EFI_STATUS
BBTestCombinationTest2CheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCombinationTest2CheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCombinationTest2CheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCombinationTest2CheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );


#endif
