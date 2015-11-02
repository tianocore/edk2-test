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

  DriverSupportedEfiVersionBBTestFunction.c

Abstract:

  Interface Function Test Cases of Efi Driver Support Efi Version Protocol

--*/


#include "SctLib.h"
#include "DriverSupportedEfiVersionBBTestMain.h"


/**
 *  Entrypoint for EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.Length Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
BBTestLengthParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL       *DriverSupportedEfiVersion;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                                         EfiVersionProtocolLength;
  
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

  DriverSupportedEfiVersion = (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *)ClientInterface;
  EfiVersionProtocolLength =sizeof( EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL);
  
  if(DriverSupportedEfiVersion->Length ==EfiVersionProtocolLength){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
  }else{
        AssertionType = EFI_TEST_ASSERTION_FAILED;
   }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid001,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.Length,compare with length of EfiVersionProtocol",
                 L"%a:%d: Length = %d, EfiVersionProtocolLength = %d, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 DriverSupportedEfiVersion->Length,
                 EfiVersionProtocolLength,
                 EFI_SUCCESS
                 );
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
BBTestFirmwareVersionParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL       *DriverSupportedEfiVersion;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                                        S1,S2;


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
  DriverSupportedEfiVersion = (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *)ClientInterface;
  S1 = DriverSupportedEfiVersion->FirmwareVersion;
  S2 = EFI_2_10_SYSTEM_TABLE_REVISION;
  
  if (S1==S2) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
     if(S2==EFI_2_00_SYSTEM_TABLE_REVISION ||
	  S2==EFI_1_10_SYSTEM_TABLE_REVISION ||
	  S2==EFI_1_02_SYSTEM_TABLE_REVISION ) {
           AssertionType = EFI_TEST_ASSERTION_WARNING;
	    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid002,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion,compare with system table revision",
                 L"%a:%d: FirmwareVersion = %r, FirmwareRevision = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 S1,
                 S2,
                 EFI_SUCCESS
                 );
          return EFI_INCOMPATIBLE_VERSION;
	 } else {
	   AssertionType = EFI_TEST_ASSERTION_FAILED;
	 }
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDriverSupportedEfiVersionTestAssertionGuid002,
                 L"EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion,compare with system table revision",
                 L"%a:%d: FirmwareVersion = %r, FirmwareRevision = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 S1,
                 S2,
                 EFI_SUCCESS
                 );
  return EFI_SUCCESS;
}
