/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
EFIAPI
InitializeBBTestPlatformToDriverConfiguration (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
BBTestQueryFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResponseFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestQueryConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResponseConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestCLPCommandAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCLPReturnStringAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCLPCmdStatusAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestCLPErrorValueAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
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
  { 0x78b3faf, 0xf8c7, 0x4bc5, { 0xba, 0x22, 0x54, 0x19, 0xa9, 0xe2, 0x86, 0x4d } }

#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_FUNCTION_AUTO_GUID \
  { 0x1e3b73de, 0xca5b, 0x4abe, { 0xb2, 0xd, 0x14, 0x5b, 0x1e, 0x92, 0xeb, 0x35 } }
  
#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_CONFORMANCE_AUTO_GUID \
  { 0xcc4fd861, 0x3835, 0x47d3, { 0xbc, 0x2a, 0x36, 0xb6, 0x6f, 0xd7, 0x77, 0xb } }

#define PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_CONFORMANCE_AUTO_GUID \
  { 0x13b8070e, 0x3d37, 0x4484, { 0xb6, 0x2c, 0xa5, 0xfa, 0xbb, 0x4a, 0x43, 0xfd } }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPCOMMAND_AUTO_GUID \
  { 0xaa7fccd8, 0x29ec, 0x4fa9, { 0xbf, 0x51, 0x29, 0x12, 0x59, 0xcf, 0xda, 0x7a} }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTRING_AUTO_GUID \
  { 0x6b937184, 0xa12, 0x4cae, { 0x8b, 0xea, 0x6, 0xd, 0xb6, 0x78, 0x4, 0x4f } }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTATUS_AUTO_GUID \
  { 0x72bacd55, 0xb57f, 0x420f, { 0xbd, 0xdc, 0x62, 0x15, 0x21, 0x5, 0x90, 0x9e } }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPERRORVALUE_AUTO_GUID \
  { 0x915c6b04, 0xd93a, 0x4f56, { 0xa3, 0x8e, 0xc6, 0x1b, 0x3f, 0xde, 0xec, 0x1b } }

#define CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPMESSAGECODE_AUTO_GUID \
  { 0xf5d77969, 0x4706, 0x4b47, { 0x91, 0x78, 0x84, 0xf1, 0x35, 0x74, 0xa5, 0x21 } }


#endif


