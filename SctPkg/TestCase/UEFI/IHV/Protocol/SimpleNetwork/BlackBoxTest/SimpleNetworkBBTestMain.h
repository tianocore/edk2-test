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

  SimpleNetworkBBTestMain.h

Abstract:

  BB test header file of SimpleNetwork Protocol

--*/


#ifndef _SIMPLE_NETWORK_H_
#define _SIMPLE_NETWORK_H_

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/SimpleNetwork.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define SIMPLE_NETWORK_TEST_REVISION 0x00010001

#define IHV_SIMPLE_NETWORK_PROTOCOL_GUID \
  { 0xdd8d519f, 0xc437, 0x40e2, { 0xaf, 0xd0, 0xab, 0xbe, 0x9, 0x81, 0x9c, 0x21 } }


//
// TDS 4.1
//
EFI_STATUS
BBTestStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
BBTestInitializeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
BBTestResetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
BBTestShutdownFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.6
//
EFI_STATUS
BBTestReceiveFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.7
//
EFI_STATUS
BBTestStationAddressFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.8
//
EFI_STATUS
BBTestStatisticsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.9
//
EFI_STATUS
BBTestMCastIpToMacFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.10
//
EFI_STATUS
BBTestNVDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.11
//
EFI_STATUS
BBTestGetStatusFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.12
//
EFI_STATUS
BBTestTransmitFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.13
//
EFI_STATUS
BBTestReceiveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Conformance Test
//

//
// TDS 5.1
//
EFI_STATUS
BBTestStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
BBTestStopConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
BBTestInitializeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
BBTestResetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
BBTestShutdownConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.6
//
EFI_STATUS
BBTestReceiveFilterConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.7
//
EFI_STATUS
BBTestStationAddressConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.8
//
EFI_STATUS
BBTestStatisticsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.9
//
EFI_STATUS
BBTestMCastIpToMacConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.10
//
EFI_STATUS
BBTestNVDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.11
//
EFI_STATUS
BBTestGetStatusConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.12
//
EFI_STATUS
BBTestTransmitConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.13
//
EFI_STATUS
BBTestReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Internal Functions
//


//
// Entry GUIDs
//

#define SNP_START_FUNCTION_TEST_GUID \
  { 0xb6c9991f, 0x90ba, 0x4f59, { 0x82, 0x97, 0x2b, 0x31, 0xa2, 0xa6, 0x71, 0xf3 } }

#define SNP_STOP_FUNCTION_TEST_GUID \
  { 0xfe05b71, 0x7e8f, 0x4226, { 0xb7, 0xb7, 0xba, 0x92, 0x84, 0xa1, 0x8f, 0xb5 } }

#define SNP_INITIALIZE_FUNCTION_TEST_GUID \
  { 0x23e14e1c, 0x92e6, 0x4733, { 0x82, 0x9d, 0xb5, 0x8c, 0x97, 0xd8, 0x6e, 0xf7 } }

#define SNP_RESET_FUNCTION_TEST_GUID \
  { 0x4883024c, 0xb0b2, 0x4260, { 0x9a, 0x79, 0x6b, 0x5, 0x4, 0xa2, 0x97, 0x79 } }

#define SNP_SHUTDOWN_FUNCTION_TEST_GUID \
  { 0x3ebddb33, 0xadec, 0x46ec, { 0x94, 0x16, 0xd4, 0x75, 0xd7, 0x89, 0x64, 0x27 } }

#define SNP_RECEIVEFILTERS_FUNCTION_TEST_GUID \
  { 0xcca11068, 0x15b4, 0x4f0f, { 0xb1, 0x27, 0xd, 0xd1, 0xaa, 0xb2, 0xc8, 0x77 } }

#define SNP_STATIONADDRESS_FUNCTION_TEST_GUID \
  { 0x587cb66d, 0xd469, 0x4754, { 0x9f, 0x3a, 0xc0, 0x3e, 0x89, 0x81, 0x4f, 0x4b } }

#define SNP_STATISTICS_FUNCTION_TEST_GUID \
  { 0x7d11c004, 0x64b, 0x411e, { 0x9b, 0xf2, 0xcf, 0xa6, 0x35, 0x21, 0xe3, 0x73 } }

#define SNP_MCASTIPTOMAC_FUNCTION_TEST_GUID \
  { 0x92fbceb, 0xca5f, 0x4056, { 0x8f, 0x48, 0xf2, 0x97, 0xb9, 0x17, 0xcf, 0x70 } }

#define SNP_NVDATA_FUNCTION_TEST_GUID \
  { 0x6db147bf, 0x1f10, 0x4349, { 0x87, 0x31, 0x54, 0x7b, 0x67, 0x66, 0xae, 0x84 } }

#define SNP_GETSTATUS_FUNCTION_TEST_GUID \
  { 0xf8e2cbee, 0x438e, 0x4a32, { 0xa7, 0x3, 0x7e, 0xae, 0xe0, 0xe2, 0xcb, 0x15 } }

#define SNP_TRANSMIT_FUNCTION_TEST_GUID \
  { 0x1d877bf1, 0x3975, 0x486e, { 0x86, 0xf0, 0xb4, 0xd6, 0x15, 0x96, 0x4a, 0x78 } }

#define SNP_RECEIVE_FUNCTION_TEST_GUID \
  { 0x9541b922, 0xe632, 0x458f, { 0x85, 0x62, 0xd, 0x9, 0x9c, 0x41, 0xee, 0x43 } }

#define SNP_START_CONFORMANCE_TEST_GUID \
  { 0xdb892500, 0x5e10, 0x4c3d, { 0x8e, 0x93, 0x10, 0xc6, 0x1, 0x80, 0xf3, 0xf3 } }

#define SNP_STOP_CONFORMANCE_TEST_GUID \
  { 0xe20fcbcb, 0xfe94, 0x49dc, { 0x84, 0xd8, 0x76, 0x29, 0x11, 0xa7, 0xda, 0xeb } }

#define SNP_INITIALIZE_CONFORMANCE_TEST_GUID \
  { 0xc4510dbb, 0x5909, 0x4b4f, { 0xba, 0x4c, 0xc, 0xf6, 0x3d, 0x92, 0xe3, 0xa1 } }

#define SNP_RESET_CONFORMANCE_TEST_GUID \
  { 0xbcdad4c4, 0x2a8d, 0x45ab, { 0xa6, 0x62, 0xc0, 0x60, 0x1b, 0x71, 0x3c, 0x28 } }

#define SNP_SHUTDOWN_CONFORMANCE_TEST_GUID \
  { 0xa22ff81d, 0xd866, 0x4aaa, { 0x83, 0xa2, 0x30, 0x1b, 0x7c, 0x3f, 0x61, 0x4b } }

#define SNP_RECEIVEFILTERS_CONFORMANCE_TEST_GUID \
  { 0xeebb79d0, 0x3649, 0x49c8, { 0x80, 0x6b, 0xe7, 0x5d, 0xc8, 0x7d, 0xfb, 0x8a } }

#define SNP_STATIONADDRESS_CONFORMANCE_TEST_GUID \
  { 0x1145113d, 0xebf2, 0x41f7, { 0xb8, 0x74, 0x0, 0x9b, 0x92, 0xce, 0xe9, 0x43 } }

#define SNP_STATISTICS_CONFORMANCE_TEST_GUID \
  { 0xcb7df80d, 0xa7a4, 0x499b, { 0xb1, 0x45, 0x43, 0xb5, 0x87, 0x10, 0x8d, 0xcf } }

#define SNP_MCASTIPTOMAC_CONFORMANCE_TEST_GUID \
  { 0xaa32a619, 0x9974, 0x4eaa, { 0xa8, 0x74, 0x65, 0x25, 0xf8, 0xe9, 0x44, 0xc1 } }

#define SNP_NVDATA_CONFORMANCE_TEST_GUID \
  { 0x21e04b51, 0x183e, 0x42d1, { 0xa6, 0xf4, 0xe5, 0x9f, 0x36, 0xb1, 0x9d, 0x69 } }

#define SNP_GETSTATUS_CONFORMANCE_TEST_GUID \
  { 0x3b46dc53, 0x54b2, 0x4d70, { 0x8b, 0x67, 0xe1, 0xf5, 0x5b, 0x30, 0xe7, 0xf6 } }

#define SNP_TRANSMIT_CONFORMANCE_TEST_GUID \
  { 0x68ce3d21, 0x7022, 0x4935, { 0xbf, 0x19, 0x95, 0x57, 0x1, 0x4d, 0xe4, 0x29 } }

#define SNP_RECEIVE_CONFORMANCE_TEST_GUID \
  { 0x37f96af6, 0x2ff2, 0x497b, { 0x89, 0xe7, 0xd4, 0x1f, 0xc2, 0x89, 0x27, 0x76 } }


#endif
