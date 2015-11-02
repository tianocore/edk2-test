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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  SerialIoBbTestMain.c

Abstract:
  Source file for Serial IO Protocol Black-Box Test.

--*/

#include "SctLib.h"
#include "SerialIoBBTestMain.h"

//
// Declarations
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SERIAL_IO_BB_TEST_REVISION,
  EFI_SERIAL_IO_PROTOCOL_GUID,
  L"Serial IO Protocol Test",
  L"UEFI Serial IO Protocol Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    RESET_FUNC_TEST_GUID,
    L"Reset_Func",
    L"Test the functionality of Reset() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ResetFuncTest
  },
  {
    SET_ATTRIBUTES_FUNC_TEST_GUID,
    L"SetAttributes_Func",
    L"Test the functionality of SetAttributes() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesFuncTest
  },
  {
    SET_CONTROL_FUNC_TEST_GUID,
    L"SetControl_Func",
    L"Test the functionality of SetControl() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlFuncTest
  },
  {
    GET_CONTROL_FUNC_TEST_GUID,
    L"GetControl_Func",
    L"Test the functionality of GetControl() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetControlFuncTest
  },
  {
    WRITE_FUNC_TEST_GUID,
    L"Write_Func",
    L"Test the functionality of Write() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    WriteFuncTest
  },
  {
    READ_FUNC_TEST_GUID,
    L"Read_Func",
    L"Test the functionality of Read() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ReadFuncTest
  },
  {
    SET_ATTRIBUTES_CONF_TEST_GUID,
    L"SetAttributes_Conf",
    L"Perform the consistency check of SetAttributes() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesConfTest
  },
  {
    SET_CONTROL_CONF_TEST_GUID,
    L"SetControl_Conf",
    L"Perform the consistency check of SetControl() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlConfTest
  },
  {
    READ_CONF_TEST_GUID,
    L"Read_Conf",
    L"Perform the consistency check of Read() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ReadConfTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    RESET_STRESS_TEST_GUID,
    L"Reset_Stress",
    L"Stress test for Reset() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    ResetStressTest
  },
  {
    SET_ATTRIBUTES_STRESS_TEST_GUID,
    L"SetAttributes_Stress",
    L"Stress test for SetAttributes() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetAttributesStressTest
  },
  {
    SET_CONTROL_STRESS_TEST_GUID,
    L"SetControl_Stress",
    L"Stress test for SetControl() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetControlStressTest
  },
  {
    GET_CONTROL_STRESS_TEST_GUID,
    L"GetControl_Stress",
    L"Stress test for GetControl() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetControlStressTest
  },
  {
    WRITE_STRESS_TEST_GUID,
    L"Write_Stress_Manual",
    L"Stress test for Write() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    WriteStressTest
  },
  {
    READ_STRESS_TEST_GUID,
    L"Read_Stress_Manual",
    L"Stress test for Read() service.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    ReadStressTest
  },
#endif

  0
};

CHAR16 *gParityString[] = {
  L"DefaultParity",
  L"NoParity",
  L"EvenParity",
  L"OddParity",
  L"MarkParity",
  L"SpaceParity",
  L"InvalidParity"
};

CHAR16 *gStopBitsString[] = {
  L"DefaultStopBits",
  L"OneStopBit",
  L"OneFiveStopBits",
  L"TwoStopBits",
  L"InvalidStopBits"
};

EFI_BB_TEST_PROTOCOL      *gBBTestProtocolInterface;

//
// Prototypes
//

EFI_STATUS
InitializeSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
UnloadSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle
  );

//
// Functions
//


/**
 *  Creates/installs the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @param SystemTable    The system table.
 *  @return EFI_SUCCESS   The interface was installed successfully.
 *  @return EFI_OUT_OF_RESOURCES    Failed due to the lack of resources.
 *  @return EFI_INVALID_PARAMETER   One of parameters is invalid.
 */
EFI_STATUS
InitializeSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  SctInitializeLib (ImageHandle, SystemTable);
  EfiInitializeTestLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadSerialIoBbTest,
           &gBBTestProtocolInterface
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
UnloadSerialIoBbTest (
  IN EFI_HANDLE           ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  *StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test logging support library interface
  //
  *LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   LoggingLib
                   );
  // Test logging support library is optional

  //
  // Done
  //
  return EFI_SUCCESS;
}
