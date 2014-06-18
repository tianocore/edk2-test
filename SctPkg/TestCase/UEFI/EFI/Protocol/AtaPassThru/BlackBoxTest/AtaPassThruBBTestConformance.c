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

  AtaPassThruBBTestConformance.c

Abstract:

  Conformance Test Cases of ATA Pass Through Protocol

--*/


#include "SctLib.h"
#include "AtaPassThruBBTestMain.h"

extern UINT8 EnterEvent;

BOOLEAN
IsPowerOfTwo (UINT32 Value)
{
  BOOLEAN  MetBitOne;
  UINT8    Index;

  MetBitOne = FALSE;

  for (Index = 0; Index < 32; Index ++) {
    if (Value == 0) {
      return TRUE;
    }

    if ((Value & 0x00000001) == 1) {
      if (MetBitOne) {
        return FALSE;
      }
      MetBitOne = TRUE;
    }

    Value = Value >> 1;
  }

  return TRUE;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.Mode Conformance Test.
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
BBTestModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  if ((AtaPassThru->Mode)->Attributes & (EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL | EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid020,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.Mode - check Attributes.",
                 L"%a:%d: Mode - 0x%X\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 (AtaPassThru->Mode)->Attributes
                 );

  if (IsPowerOfTwo ((AtaPassThru->Mode)->IoAlign)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid021,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.IoAlign - check IoAlign.",
                 L"%a:%d: Mode - 0x%X\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 (AtaPassThru->Mode)->IoAlign
                 );

  return Status;
  
}
/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort Conformance Test.
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
BBTestGetNextPortConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                InvalidPort;
  UINT16                                Port1;
  UINT16                                Port2;

  Port1 = 0xFFFF;
  Port2 = 0xFFFF;

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Port
  //
  Status = GetInvalidPort (AtaPassThru, &InvalidPort);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Check point 1, call GetNextPort with invalid port.
  //

  Status = AtaPassThru->GetNextPort (AtaPassThru, &InvalidPort);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid001,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort - call GetNextPort with invalid Port.",
                 L"%a:%d:Status - %r, Port - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 InvalidPort
                 );

  //
  // Check point 2
  // If Port is not 0xFFFF and Port was not returned on a previous call to GetNextPort(), then EFI_INVALID_PARAMETER is returned.  
  //

  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port1);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get the 1st port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Port2 = Port1;

  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port1);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get 2nd port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port2);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid002,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort - call GetNextPort When Port is not 0xFFFF and Port was not returned on a previous call.",
                 L"%a:%d:Status - %r, Port - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port2
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath Conformance Test.
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
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                InvalidPort;
  UINT16                                Port;
  UINT16                                PortMultiplierPort;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINT8                                 AtaStatus;
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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Call BuildDevicePath() with NULL DevicePath.
  //
  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;

  Status = GetPresentDevice(AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on ATA channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto CheckPoint2;
  }
  
  Status = AtaPassThru->BuildDevicePath (AtaPassThru, Port, PortMultiplierPort, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid003,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with NULL DevicePath.",
                 L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort
                 );

CheckPoint2:
  //
  // Get invalid Port
  //
  Status = GetInvalidPort (AtaPassThru, &InvalidPort);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Call BuildDevicePath() with invalid Port.
  //

  Status = AtaPassThru->BuildDevicePath (AtaPassThru, InvalidPort, PortMultiplierPort, &DevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid004,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Port.",
                 L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort
                 );

  //
  // Check point 2, call BuildDevicePath with invalid PortMultiplierPort.
  //
  Status = GetValidPort (AtaPassThru, &Port);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get valid port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = GetInvalidPortMultiplierPort (AtaPassThru, Port, &PortMultiplierPort);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid PortMultiplierPort fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  Status = AtaPassThru->BuildDevicePath (AtaPassThru, Port, PortMultiplierPort, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid005,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid PortMultiplierPort",
                 L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort
                 );

  
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetDevice Conformance Test.
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
BBTestGetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINT16                                Port;
  UINT16                                PortMultiplierPort;
  UINT8                                 AtaStatus;
  
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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Call GetDevice()with NULL DevicePath, NULL Port/MultiplierPort.
  //
  //
  // Check Point 1. NULL Device Path.
  //
  Status = AtaPassThru->GetDevice (AtaPassThru, NULL, &Port, &PortMultiplierPort);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid006,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetDevice - Invoke GetDevice() with NULL Device Path",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;
  Status = GetPresentDevice (AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on ATA channel",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }
  //
  // Get the present Device Path Node.
  //
  Status = AtaPassThru->BuildDevicePath (AtaPassThru, Port, PortMultiplierPort, &DevicePath);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath",
                   L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Port,
                   PortMultiplierPort
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check Point 2. NULL Port.
  //
  Status = AtaPassThru->GetDevice (AtaPassThru, DevicePath, NULL, &PortMultiplierPort);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid007,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetDevice - Invoke GetDevice() with NULL Port",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3. NULL Device.
  //
  Status = AtaPassThru->GetDevice (AtaPassThru, DevicePath, &Port, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid008,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetDevice - Invoke GetDevice() with NULL PortMultiplierPort",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Set the Device Path to End Device Path.
  //
  DevicePath->Type    = 0x7F;
  DevicePath->SubType = 0xFF;

  Status = AtaPassThru->GetDevice (AtaPassThru, DevicePath, &Port, &PortMultiplierPort);

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetDevice - Invoke GetDevice() with unsupported Device Path",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //Free the DevicePath.
  SctFreePool (DevicePath);
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.ResetDevice Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
BBTestResetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                InvalidPort;
  UINT16                                InvalidPortMultiplierPort;
  UINT16                                Port;
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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get invalid Port
  //
  Status = GetInvalidPort (AtaPassThru, &InvalidPort);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid port fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Assertion Point 4.4.2.1
  // Call ResetDevice() with invalid port or invalid PortMultiplierPort.
  //

  //
  // Check point 1, call ResetDevice with invalid Port.
  //
  Status = AtaPassThru->ResetDevice (AtaPassThru, InvalidPort, 0);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid010,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.ResetDevice - call ResetDevice with invalid Port.",
                 L"%a:%d:Status - %r, InvalidPort - 0x%x, Device - 0\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 InvalidPort
                 );

  //
  // Check point 2, call ResetDevice with invalid PortMultiplierPort.
  //
  
  //
  // Get valid port from which to get an invalid PortMultiplierPort.
  //  
  Status = GetValidPort (AtaPassThru, &Port);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get valid port",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  Status = GetInvalidPortMultiplierPort (AtaPassThru, Port, &InvalidPortMultiplierPort);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get invalid PortMultiplierPort",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }
    
  Status = AtaPassThru->ResetDevice (AtaPassThru, Port, InvalidPortMultiplierPort);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid011,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.ResetDevice - call ResetDevice with invalid PortMultiplierPort.",
                 L"%a:%d:Status - %r, Port - 0x%x, InvalidDevice - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 InvalidPortMultiplierPort
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetNextTarget Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                Port;
  UINT16                                InvalidPortMultiplierPort;
  UINT16                                PortMultiplierPort1;
  UINT16                                PortMultiplierPort2;

  PortMultiplierPort1 = 0xFFFF;
  PortMultiplierPort2 = 0xFFFF;

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get First Port.
  //
  Port = 0xFFFF;
  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check Point1
  //
  Status = GetInvalidPortMultiplierPort (AtaPassThru, Port, &InvalidPortMultiplierPort);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get invalid PortMultiplierPort fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &InvalidPortMultiplierPort);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid012,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice with invalid PortMultiplierPort.",
                 L"%a:%d:Status - %r, Port - 0x%x, InvalidDevice - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 InvalidPortMultiplierPort
                 );

  //
  // Check Point2.
  //
  Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort1);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get 1st PortMultiplierPort fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  PortMultiplierPort2 = PortMultiplierPort1;

  Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort1);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Get 2nd PortMultiplierPort fail",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort2);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid013,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice When PortMultiplierPort is not 0xFFFF and PortMultiplierPort was not returned on a previous call.",
                 L"%a:%d:Status - %r, Port - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 PortMultiplierPort2
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.PassThru Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// TDS 4.6
//
EFI_STATUS
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ATA_PASS_THRU_PROTOCOL            *AtaPassThru;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                Port;
  UINT16                                PortMultiplierPort;
  EFI_ATA_PASS_THRU_COMMAND_PACKET      Packet;
  EFI_ATA_STATUS_BLOCK                  *Asb;
  VOID                                  *InData;
  EFI_ATA_COMMAND_BLOCK                 Acb;
  UINT16                                InvalidPort;
  UINT16                                InvalidPortMultiplierPort;
  UINT8*                                AlignedAsb;
  UINT8*                                AlignedBuffer;
  UINT8                                 AtaStatus;

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
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Get valid Device
  //
  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;

  Status = GetPresentDevice (AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get present device on ATA channel",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  Asb    = NULL;
  InData = NULL;
  Asb    = SctAllocateZeroPool (AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  InData = SctAllocateZeroPool (AtaPassThru->Mode->IoAlign + 512);
  if ((Asb == NULL) || (InData == NULL)){
    Status = EFI_OUT_OF_RESOURCES;
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't allocate buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  AlignedAsb    = (UINT8 *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  AlignedBuffer = (UINT8 *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));

  Acb.AtaCommand    = 0xEC;
  Acb.AtaDeviceHead = (UINT8)((UINT8)(PortMultiplierPort) << 4);
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
    
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
    goto NonIoAlignCheck;
  } 

  Packet.Asb          = (EFI_ATA_STATUS_BLOCK*)AlignedAsb;
  Packet.InDataBuffer = AlignedBuffer;
   
  //InDataBuffer not meet Io align. 
  Packet.InDataBuffer = AlignedBuffer + 1;
  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid014,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with Non-IoAligned InDataBuffer",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb.AtaCommand    = 0xEC;
  Acb.AtaDeviceHead = (UINT8)((UINT8)(PortMultiplierPort) << 4);
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  SctZeroMem (Asb, AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  SctZeroMem (InData, AtaPassThru->Mode->IoAlign + 512);

  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
  Packet.InDataBuffer      = AlignedBuffer;
   
  //Asb not meet Io align. 
  Packet.Asb = (EFI_ATA_STATUS_BLOCK*)(AlignedAsb + 1);
  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid015,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with Non-IoAligned Asb",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb.AtaCommand    = 0xEC;
  Acb.AtaDeviceHead = (UINT8)((UINT8)(PortMultiplierPort) << 4);
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  SctZeroMem (Asb, AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  SctZeroMem (InData, AtaPassThru->Mode->IoAlign + 512);

  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  
  Packet.OutTransferLength = 512;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
  Packet.InDataBuffer      = AlignedBuffer;
  Packet.Asb               = (EFI_ATA_STATUS_BLOCK*)AlignedAsb; 

  //OutDataBuffer not meet Io align. 
  Packet.OutDataBuffer     = AlignedBuffer + 1;
  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid016,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with Non-IoAligned OutDataBuffer",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
NonIoAlignCheck:

  // Port or PortMultiplierPort is invalid.

  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb.AtaCommand    = 0xEC;
  Acb.AtaDeviceHead = (UINT8)((UINT8)(PortMultiplierPort) << 4);
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  SctZeroMem (Asb, AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  SctZeroMem (InData, AtaPassThru->Mode->IoAlign + 512);

  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
  Packet.InDataBuffer      = AlignedBuffer;
  Packet.Asb               = (EFI_ATA_STATUS_BLOCK*)AlignedAsb;

  Status = GetInvalidPort(AtaPassThru, &InvalidPort);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get invalid port on ATA channel",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto BufferLengthCheck;
  }

  Status = AtaPassThru->PassThru (AtaPassThru, InvalidPort, PortMultiplierPort, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid017,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with Invalid Port",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = GetInvalidPortMultiplierPort(AtaPassThru, Port, &InvalidPortMultiplierPort);
  if (Status != EFI_SUCCESS){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't get PortMultiplierPort on ATA channel",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto BufferLengthCheck;
  }

  Status = AtaPassThru->PassThru (AtaPassThru, Port, InvalidPortMultiplierPort, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid018,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with Invalid PortMultiplierPort",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

BufferLengthCheck:
  //
  // Call PassThru() with too long InTransferLength.
  //
  
  //
  // Initialize ACB.
  //
  SctZeroMem (&Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb.AtaCommand    = 0xEC;
  Acb.AtaDeviceHead = (UINT8)((UINT8)(PortMultiplierPort) << 4);
  //
  // Initialize the Request Packet.
  //
  SctZeroMem (&Packet,sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  SctZeroMem (Asb, AtaPassThru->Mode->IoAlign + sizeof(EFI_ATA_STATUS_BLOCK));
  SctZeroMem (InData, AtaPassThru->Mode->IoAlign + 512);

  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 0xFFFFFFFF;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
  Packet.InDataBuffer      = AlignedBuffer;
  Packet.Asb               = (EFI_ATA_STATUS_BLOCK*)AlignedAsb;
 

  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (Status == EFI_BAD_BUFFER_SIZE || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestConformanceAssertionGuid019,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long InTransferLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

Done:
  if (Asb != NULL) {
    SctFreePool (Asb);
  }
  if (InData != NULL) {
    SctFreePool (InData);
  }

  return Status;
}
