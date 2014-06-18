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
    0x868b4f16, 0xc83a, 0x4205, 0xa9, 0x3c, 0x3f, 0x51, 0xcf, 0x7f, 0x61, 0xc0 \
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
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable,
  IN CHAR16             *MonitorName
  )
/*++

Routine Description:

  Initialize the system resources.

Arguments:

  ImageHandle - The image handle.
  SystemTable - The system table.
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
  TestCaseListHead      - Head point of the test case list.
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
