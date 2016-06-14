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

  BusSpecificDriverOverrideBBTestConformance.c

Abstract:

  Interface Conformance Test Cases of BusSpecificDriverOverride Protocol

--*/


#include "SctLib.h"
#include "BusSpecificDriverOverrideBBTestMain.h"


/**
 *  Entrypoint for EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.1
//
EFI_STATUS
BBTestGetDriverConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib;
  EFI_STATUS                                  Status;
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL   *BusOverride;


  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DriverImageHandle;
  EFI_HANDLE                                  InvalidDriverImageHandle;
  BOOLEAN                                     Invalid;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  BusOverride = (EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  DriverImageHandle = NULL;
  Invalid = TRUE;
  InvalidDriverImageHandle = (EFI_HANDLE)(INTN)(0x8);

  if (InvalidDriverImageHandle == DriverImageHandle) {
    Invalid = FALSE;
  }

  //
  // Circularly call GetDriver() with DriverImageHandle
  // being the one retrieved by the last call of GetDriver(),
  // until EFI_NOT_FOUND returned.
  //

  do {
    Status = BusOverride->GetDriver (
                            BusOverride,
                            &DriverImageHandle
                            );
    if (!EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBusSpecificDriverOverrideBBTestFunctionAssertionGuid001,
                     L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - Verification of GetDriver interface",
                     L"%a:%d:ImageHandle:0x%x",
                     __FILE__,
                     (UINTN)__LINE__,
                     DriverImageHandle
                     );

      if (InvalidDriverImageHandle == DriverImageHandle) {
        Invalid = FALSE;
      }
    }
  } while (!EFI_ERROR (Status));

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBusSpecificDriverOverrideBBTestConformanceAssertionGuid001,
                 L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - Verification of GetDriver interface",
                 L"%a:%d:Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_FOUND
                 );

  //
  // pass the invalid driver image handle to the GetDriver
  //
  if (Invalid == TRUE) {
    Status = BusOverride->GetDriver (
                            BusOverride,
                            &InvalidDriverImageHandle
                            );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBusSpecificDriverOverrideBBTestConformanceAssertionGuid002,
                   L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - with the invalid handle, the return status should be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );
  }

  return EFI_SUCCESS;
}
