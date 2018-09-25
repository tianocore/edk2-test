/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Eas.h

Abstract:

  ENTS Test definitions.

--*/

#ifndef _EFI_EAS_H_
#define _EFI_EAS_H_

//
// Includes
//

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsProtocol)
#include "Rivl.h"
#include "EasType.h"
#include "EasLoad.h"
#include "EasCmdDisp.h"
#include "EasArg.h"

#define EFI_ENTS_NAME                   L"EFI Network Test Suit"
#define EFI_ENTS_VERSION                L"0.1"

#define EFI_ENTS_SHORT_NAME             L"EAS"
#define EFI_SCT_CONTINUE_EXECUTION_NAME L"TEST_EXEC sct -c"
#define SCT_COMMAND                     L"sct"

//
// File and Path
//
#define EFI_NETWORK_PATH_TEST     L"Ents\\Test"
#define EFI_NETWORK_PATH_SUPPORT  L"Ents\\Support"

//
// Sync Command
//
#define RIVL_DEFTYPE_CMD          L"RIVL_DEFTYPE"
#define RIVL_CRTVAR_CMD           L"RIVL_CRTVAR"
#define RIVL_SETVAR_CMD           L"RIVL_SETVAR"
#define RIVL_GETVAR_CMD           L"RIVL_GETVAR"
#define RIVL_DELTYPE_CMD          L"RIVL_DELTYPE"
#define RIVL_DELVAR_CMD           L"RIVL_DELVAR"
#define EFI_NETWORK_ABORT_COMMAND L"TEST_ABORT"
#define EFI_NETWORK_EXEC_COMMAND  L"TEST_EXEC"
#define EFI_NETWORK_GET_FILE      L"GET_FILE"
#define EFI_NETWORK_PUT_FILE      L"PUT_FILE"


//
// Variable
//
#define ENTS_VENDOR_GUID \
  { \
    0x868b4f16, 0xc83a, 0x4205, {0xa9, 0x3c, 0x3f, 0x51, 0xcf, 0x7f, 0x61, 0xc0 } \
  }

#define ENTS_SERVER_MAC_ADDRESS_NAME  L"ServerMac"
#define ENTS_SERVER_IPV4_ADDRESS_NAME L"ServerIp"

//
// Global variables
//
extern EFI_NETWORK_TEST_FRAMEWORK_TABLE *gEasFT;
extern EFI_HANDLE                       mImageHandle;
extern EFI_HANDLE                       mEftpTargetHandle;

//
// Core functions
//
EFI_STATUS
InitResources (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  IN CHAR16                    *FilePath,
  IN CHAR16                    *MonitorName
  )
/*++

Routine Description:

  Initialize the system resources.

Arguments:

  ImageHandle - The image handle.
  SystemTable - The system table.
  DevicePath  - The device path of the image handle.
  FilePath    - The file path of the image handle.
  MonitorName - Monitor name for Communication layer, current we define the 
                following three types: Mnp  Ip4  Serial

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
;

EFI_STATUS
FreeResources (
  VOID
  )
/*++

Routine Description:

  Detach all test data.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
;

EFI_STATUS
SctPassiveExecute (
  VOID
  )
/*++

Routine Description:

  Start SCT agent to enter passive mode.

Arguments:
  
  ImageHandle           - The image handle.
  SystemTable           - The system table.
  DevicePath            - The device path of the image handle.
  FilePath              - The file path of the image handle.
  MonitorName           - Monitor name for Communication layer, current we 
                          define the following three types: Mnp  Ip4  Serial

Returns:

  EFI_SUCCESS           - Agent quits successfully.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Problems occur in monitor initialization, command 
                          dispatch or environment cleanup.

--*/
;

EFI_STATUS
DelaySctAgentCmdPost (
  IN CHAR16                         *CmdBuffer,
  IN EFI_STATUS                     CmdReturn,
  IN ENTS_CMD_RESULT                CmdResult
  );

EFI_STATUS
PostSctAgentDelayedCmd (
  VOID
  );

#endif
