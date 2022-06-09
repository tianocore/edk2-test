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

  ExeModeBBTestRequired.c

Abstract:

  BB test file for UEFI processor execution mode

--*/

#include "SctLib.h"
#include "ExeModeBBTest.h"

/**
 *  @brief For Check the value of FPU control word test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required 
 *  @return EFI_SUCCESS 
 */ 

EFI_STATUS
EFIAPI
BBTestFpuControlWordTest (
    IN EFI_BB_TEST_PROTOCOL       *This, 
    IN VOID                       *ClientInterface,    
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  UINT16  FpuCw;
  EFI_TEST_ASSERTION  AssertionType;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
   
  //
  // record assertion for the returned FPU control word.
  //
  Status = GetFpuControlWord(&FpuCw);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Execution Mode - Could NOT get FPU control word",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  if ((sizeof(UINTN) == 4 && FpuCw == FPU_CONTROL_WORD_VALUE_IA32) || 
    (sizeof(UINTN) == 8 && FpuCw == FPU_CONTROL_WORD_VALUE_X64)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBasicTestAssertionGuid001,
                 L"EFI_EXE_MODE - Get FPU control word",
                 L"%a:%d:FPU control word got %x",
                 __FILE__,
                 __LINE__,
                 FpuCw
                 );
  
  
  
  return EFI_SUCCESS;
}

/**
 *  @brief For Check the value of MX CSR test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required 
 *  @return EFI_SUCCESS 
 */ 
EFI_STATUS
EFIAPI
BBTestMxCsrTest (
    IN EFI_BB_TEST_PROTOCOL       *This, 
    IN VOID                       *ClientInterface,    
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                MxCsr;
  
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // record assertion for the returned MX CSR.
  //
  Status = GetMxCsr(&MxCsr);
  
  if (MxCsr == MX_CSR_VALUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBasicTestAssertionGuid002,
                 L"EFI_EXE_MODE - Get MX CSR",
                 L"%a:%d:MX CSR got %x",
                 __FILE__,
                 __LINE__,
                 MxCsr
                 );
  

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}


