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

  DebugSupportBBTestMain.h

Abstract:

  BB test header file of Debugsupport protocol

--*/


#ifndef _DEBUG_SUPPORT_BBTEST_H_
#define _DEBUG_SUPPORT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DebugSupport.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  DEBUG_SUPPORT_PROTOCOL_TEST_REVISION    0x00010000

extern EFI_INSTRUCTION_SET_ARCHITECTURE PlatformIsa;

EFI_STATUS
InitializeBBTestDebugSupport (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestIsaFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetMaximumProcessorIndexFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterPeriodicCallbackFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterExceptionCallbackFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestInvalidateInstructionCacheFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
void
PeriodicCallback (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
PeriodicCallback1 (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
ExceptionCallback (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

void
ExceptionCallback1 (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  );

//
// Entry GUIDs
//

#define DEBUG_SUPPORT_PROTOCOL_ISA_FUNCTION_AUTO_GUID \
  { 0x48d4f0dd, 0x2ec1, 0x4e84, { 0xb0, 0xfc, 0x2c, 0xd0, 0x1, 0x7f, 0x64, 0x2f } }

#define DEBUG_SUPPORT_PROTOCOL_GETMAXIMUMPROCESSORINDEX_FUNCTION_AUTO_GUID \
  { 0x7a73d0f1, 0x7cab, 0x4f45, { 0x96, 0x20, 0x3a, 0x25, 0x35, 0xdf, 0x48, 0x43 } }

#define DEBUG_SUPPORT_PROTOCOL_REGISTERPERIODICCALLBACK_FUNCTION_AUTO_GUID \
  { 0x12acc495, 0x91a6, 0x4600, { 0xbd, 0xc8, 0xe0, 0x4c, 0xca, 0xa9, 0x54, 0x64 } }

#define DEBUG_SUPPORT_PROTOCOL_REGISTEREXCEPTIONCALLBACK_FUNCTION_MANUAL_GUID \
  { 0x2e5204a3, 0x6a7e, 0x4371, { 0x87, 0xeb, 0x9, 0xf7, 0x9c, 0x18, 0xb8, 0xec } }

#define DEBUG_SUPPORT_PROTOCOL_INVALIDATEINSTRUCTIONCACHE_FUNCTION_AUTO_GUID \
  { 0x5c107c17, 0x4c2f, 0x440c, { 0xae, 0xa5, 0xd2, 0xf1, 0x47, 0x77, 0x1c, 0xcb } }



#endif

