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

  PlatformToDriverConfigurationBBTestMain.h

Abstract:

  BB test header file of Platform To Driver Configuration protocol

--*/


#ifndef _PLATFORM_TO_DRIVER_CONFIGURATION_BBTEST_H_
#define _PLATFORM_TO_DRIVER_CONFIGURATION_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/PlatformToDriverConfiguration.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_TEST_REVISION    0x00010000

EFI_HANDLE DriverImageHandle;

#define IHV_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID    \
{   \
  0xf0b5e017, 0xcfc9, 0x4b37, 0x98, 0xb8, 0xd9, 0xaa, 0x9b, 0x7e, 0x1f, 0xec    \
}

//
//define the data structure
//
typedef struct{
  CHAR8 CLPCmdVerb[8];
  CHAR8 CLPCmdOption[13];
  CHAR8 CLPCmdTarget[100];
  UINT8  CLPCmdTargetLength;
  }CLP_CMD;

#define Num_CLPCmdVerb    13
#define Num_CLPCmdOption  22

 typedef enum{
   COMMAND_COMPLETED,
   COMMAND_SPAWNED,
   COMMAND_PROCESSING_FAILED,
   COMMAND_EXECUTION_FAILED,
   COMMAND_STATUS_ERROR
  }STATUS_TAG;


 typedef enum   {
	COMMAND_ERROR_UNSPECIFIED,
	COMMAND_NOT_SUPPORTED,
	COMMAND_NOT_RECOGNIZED,
	COMMAND_SYNTAX_ERROR,
	INVALID_OPTION,
	INVALID_ARGUMENT,
	OUTPUT_FORMAT_NOT_SUPPORTED,
	MISSING_ARGUMENT,
	OPTION_NOT_SUPPORTED,
	INVALID_TARGET,
	REQUIRED_OPTION_MISSING,
	QUEUE_FULL,
	UNRECOGNIZED_OEM_EXTENSION,
	MISSING_REQUIRED_TARGET,
	FUNCTION_NOT_SUPPORTED,
	ERROR_VALUE_NOT_FOUND
	}ERROR_TAG;
//
// Function Interface test declaration section
//


EFI_STATUS
InitializeBBTestPlatformToDriverConfiguration (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
BBTestQueryFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResponseFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestQueryConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResponseConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestCLPCommandAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestCLPReturnStringAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestCLPCmdStatusAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestCLPErrorValueAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestCLPMessageCodeAutoTest (
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


#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_FUNCTION_AUTO_GUID \
  { 0xcb8b2739, 0xe3c9, 0x4e0b, 0xb9, 0x74, 0xb7, 0x8c, 0xdc, 0xdb, 0x11, 0x25 }

#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_FUNCTION_AUTO_GUID \
  { 0x9452640e, 0x6c2c, 0x4548, 0xbd, 0x9, 0x4, 0x34, 0x87, 0xef, 0x81, 0x32 }
  
#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_CONFORMANCE_AUTO_GUID \
  { 0x57c124b6, 0x9282, 0x470d, 0xb2, 0xb5, 0x40, 0xc3, 0xea, 0x46, 0xe5, 0x77}

#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_CONFORMANCE_AUTO_GUID \
  { 0x44e3e587, 0xd1d, 0x4fc3, 0x9d, 0x68, 0x9c, 0x42, 0x91, 0xbc, 0xa9, 0xdd }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPCOMMAND_AUTO_GUID \
  { 0x7664ca47, 0xf362, 0x494f, 0xa1, 0xbb, 0x14, 0x6f, 0xa5, 0x93, 0xd2, 0x78 }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTRING_AUTO_GUID \
  { 0x6849d895, 0x468e, 0x4de0, 0x8f, 0x95, 0x6d, 0x5d, 0xf8, 0x8e, 0x6c, 0x7a }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTATUS_AUTO_GUID \
  { 0x55a55677, 0xf5bc, 0x413a, 0xaa, 0x34, 0x60, 0x2c, 0xdc, 0xec, 0xa2, 0xc8 }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPERRORVALUE_AUTO_GUID \
  { 0xc5221d4d, 0xd402, 0x484a, 0xb9, 0x21, 0x5f, 0x23, 0xd9, 0x38, 0x4, 0xdb }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPMESSAGECODE_AUTO_GUID \
  { 0x837171d3, 0xa28, 0x4d91, 0x92, 0xf6, 0xea, 0xf4, 0x71, 0x99, 0xa5, 0x57 }


#endif


