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

  PlatformDriverOverrideBBTestConformance.c

Abstract:

  Conformance Test Cases of Platform Driver Override Protocol

--*/


#include "SctLib.h"
#include "PlatformDriverOverrideBBTestMain.h"

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriver Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
BBTestGetDriverConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_HANDLE                             DriverImageHandle;

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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.1.2.1
  // Check Point 1
  // Invoke GetDriver() with invalide controller handle
  //
  DriverImageHandle = NULL;
  Handles = NULL;
  Status = PlatformDriverOverride->GetDriver (
                                     PlatformDriverOverride,
                                     Handles,
                                     &DriverImageHandle
                                     );
  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformDriverOverrideBBTestConformanceAssertionGuid001,
             L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver - Invoke GetDriver() with invalid controller handle",
             L"%a:%d:Status - %r",
             __FILE__,
             (UINTN)__LINE__,
             Status
             );

  //
  // Check Point 2
  // Invoke GetDriver() with invalide DriverImageHandle
  //

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);

  for (HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++) {
    DriverImageHandle = NULL;
    Status = PlatformDriverOverride->GetDriver (
                                       PlatformDriverOverride,
                                       Handles[HandleIndex],
                                       &DriverImageHandle
                                       );
    
    if (Status == EFI_SUCCESS){
      Status = PlatformDriverOverride->GetDriver (
                                         PlatformDriverOverride,
                                         Handles[HandleIndex],
                                         NULL
                                         );
      
      if(Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid002,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver - Invoke GetDriver() with invalid DriverImageHandle.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
    }
  }

  if (Handles) {
    SctFreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriverPath Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
BBTestGetDriverPathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath;

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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.2.2.1
  // Check Point 1
  // Invoke GetDriverPath() with invalide controller handle
  //
  DriverImagePath = NULL;
  Handles = NULL;
  Status = PlatformDriverOverride->GetDriverPath (
                                     PlatformDriverOverride,
                                     Handles,
                                     &DriverImagePath
                                     );
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid003,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath - Invoke GetDriverPath() with invalid controller handle",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2
  // Invoke GetDriverPath() with invalide DriverImagePath
  //

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);


  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImagePath = NULL;
    Status = PlatformDriverOverride->GetDriverPath (
                                       PlatformDriverOverride,
                                       Handles[HandleIndex],
                                       &DriverImagePath
                                       );
    if (Status == EFI_SUCCESS) {
      Status = PlatformDriverOverride->GetDriverPath (
                                         PlatformDriverOverride,
                                         Handles[HandleIndex],
                                         NULL
                                         );
      if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPlatformDriverOverrideBBTestConformanceAssertionGuid004,
                     L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath - Invoke GetDriverPath() with invalid DriverImageHandle.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
  }

  if (Handles) {
    SctFreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.DriverLoaded Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
BBTestDriverLoadedConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  EFI_HANDLE                             ControllerHandle;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath;
  EFI_DEVICE_PATH_PROTOCOL               *NewDriverImagePath;
  EFI_HANDLE                             DriverImageHandle;
  EFI_DEVICE_PATH_PROTOCOL               *FilePath;
  CHAR16                                 *TempFileName;

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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);

  ControllerHandle = NULL;
  DriverImagePath = NULL;
  NewDriverImagePath = NULL;
  DriverImageHandle = NULL;
  FilePath = NULL;
  TempFileName = L"PlatformDriverOverrideBBTest.efi";

  //
  // Get the Controller handle and the driver image path.
  //
  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImagePath = NULL;
    Status = PlatformDriverOverride->GetDriverPath (
                                       PlatformDriverOverride,
                                       Handles[HandleIndex],
                                       &DriverImagePath
                                       );
    if (Status == EFI_SUCCESS) {
      ControllerHandle = Handles[HandleIndex];
      NewDriverImagePath = DriverImagePath;
      Status = PlatformDriverOverride->GetDriverPath (
                                         PlatformDriverOverride,
                                         Handles[HandleIndex],
                                         &NewDriverImagePath
                                         );
      if(Status == EFI_SUCCESS) {
        break;
      }
    }
  }

  if (Status != EFI_SUCCESS) {
    //
    // GetDevicePath() is optional in UEFI 2.0 spec. Skip this test if this
    // interface is not provided.
    //
    return EFI_SUCCESS;
  }

  //
  // Get the driver image handle.
  //
  FilePath = SctFileDevicePath (NULL, TempFileName);
  Status = gtBS->LoadImage(
                   FALSE,
                   DriverImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &DriverImageHandle
                   );

  //
  // Assertion Point 4.3.2.1
  // Call DriverLoaded() with DriverImagePath not got from the prior call to GetDriverPath().
  //
  Status = PlatformDriverOverride->DriverLoaded (
                                     PlatformDriverOverride,
                                     ControllerHandle,
                                     DriverImagePath,
                                     DriverImageHandle
                                     );

  if ((Status == EFI_NOT_FOUND) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid005,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with DriverImagePath not got from the prior call to GetDriverPath().",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );



  //
  // Assertion Point 4.3.2.2
  // Check point 1. Invalid ControllerHandle.
  //
  Status = PlatformDriverOverride->DriverLoaded (
                                     PlatformDriverOverride,
                                     NULL,
                                     DriverImagePath,
                                     DriverImageHandle
                                     );

  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid006,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid ControllerHandle.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check point 2. Invalid DriverImagePath.
  //
  Status = PlatformDriverOverride->DriverLoaded (
                                     PlatformDriverOverride,
                                     ControllerHandle,
                                     NULL,
                                     DriverImageHandle
                                     );

  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid007,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid DriverImagePath.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check point 3. Invalid DriverImageHandle.
  //
  Status = PlatformDriverOverride->DriverLoaded (
                                     PlatformDriverOverride,
                                     ControllerHandle,
                                     DriverImagePath,
                                     NULL
                                     );

  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid008,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid DriverImageHandle.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Handles) {
    SctFreePool (Handles);
  }

  return EFI_SUCCESS;
}
