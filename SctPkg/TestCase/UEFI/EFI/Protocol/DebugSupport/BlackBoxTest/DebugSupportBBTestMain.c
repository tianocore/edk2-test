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

  DebugSupportBBTestMain.c

Abstract:

  Test Driver of DebugSupport Protocol

--*/

#include "DebugSupportBBTestMain.h"


//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DEBUG_SUPPORT_PROTOCOL_TEST_REVISION,
  EFI_DEBUG_SUPPORT_PROTOCOL_GUID,
  L"Debug Support Protocol Test",
  L"UEFI Debug Support Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DEBUG_SUPPORT_PROTOCOL_ISA_FUNCTION_AUTO_GUID,
    L"Isa_Func",
    L"Verify the correctness of Isa within the testcase",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestIsaFunctionAutoTest
  },

  {
    DEBUG_SUPPORT_PROTOCOL_GETMAXIMUMPROCESSORINDEX_FUNCTION_AUTO_GUID,
    L"GetMaximumProcessorIndex_Func",
    L"Invoke GetMaximumProcessorIndex and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetMaximumProcessorIndexFunctionAutoTest
  },

  {
    DEBUG_SUPPORT_PROTOCOL_REGISTERPERIODICCALLBACK_FUNCTION_AUTO_GUID,
    L"RegisterPeriodicCallback_Func",
    L"Invoke RegisterPeriodicCallback and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_RESET_REQUIRED,
    BBTestRegisterPeriodicCallbackFunctionAutoTest
  },
  {
    DEBUG_SUPPORT_PROTOCOL_INVALIDATEINSTRUCTIONCACHE_FUNCTION_AUTO_GUID,
    L"InvalidateInstructionCache_Func",
    L"Invoke InvalidateInstructionCache and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInvalidateInstructionCacheFunctionAutoTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    DEBUG_SUPPORT_PROTOCOL_REGISTEREXCEPTIONCALLBACK_FUNCTION_MANUAL_GUID,
    L"RegisterExceptionCallback_Func_Manual",
    L"Invoke RegisterExceptionCallback and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL | EFI_TEST_CASE_RESET_REQUIRED,
    BBTestRegisterExceptionCallbackFunctionManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Debug Support Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDebugSupport (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDebugSupportProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDebugSupportProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

volatile  UINTN InvokedPeriodicCallback;

VOID
PeriodicCallback (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  InvokedPeriodicCallback = TRUE;
  return;
}

VOID
PeriodicCallback1 (
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  return;
}

volatile  UINTN InvokedExceptionCallback;

VOID
ExceptionCallback (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  InvokedExceptionCallback = TRUE;
  return;
}

VOID
ExceptionCallback1 (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  return;
}

