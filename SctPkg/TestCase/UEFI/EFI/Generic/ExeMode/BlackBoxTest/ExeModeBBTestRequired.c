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
                  &StandardLib
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
                  &StandardLib
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


