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

  AtaPassThruBBTestFunction.c

Abstract:

  Interface Function Test Cases of ATA Pass Through Protocol

--*/


#include "SctLib.h"
#include "AtaPassThruBBTestMain.h"

extern UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestGetNextPortFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;
   
  Port   = 0xFFFF;

  Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);

  while (!EFI_ERROR(Status)) {
    Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"ATA device: Port - 0x%x\n",
                     Port
                     );
    }
  }

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid001,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextPort - Invoke GetNextPort() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestBuildDevicePathFunctionAutoTest (
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
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINT8                                 AtaStatus;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;

  Status = GetPresentDevice (AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Using correct parameters to get present device on ATA channel, but fail",
                   L"%a:%d:Status - %r, Port - 0x%x, PortMultiplierPort - 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Port,
                   PortMultiplierPort
                   );
    return EFI_UNSUPPORTED;
  }
  
  Status = AtaPassThru->BuildDevicePath (AtaPassThru, Port, PortMultiplierPort, &DevicePath);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    gtBS->FreePool (DevicePath);
  } else if(Status == EFI_OUT_OF_RESOURCES) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid002,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.BuildDevicePath - Invoke BuildDevicePath() and verify interface correctness within test case",
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
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetDevice Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestGetDeviceFunctionAutoTest (
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
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINT16                                PortRetrieved;
  UINT16                                PortMultiplierPortRetrieved;
  UINT8                                 AtaStatus;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;

  Status = GetPresentDevice (AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS) {
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
  
  //
  // Get the valid Device Path Node.
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

  Status = AtaPassThru->GetDevice (AtaPassThru, DevicePath, &PortRetrieved, &PortMultiplierPortRetrieved);  

  //Free the DevicePath.
  gtBS->FreePool (DevicePath);

  if ((!EFI_ERROR(Status)) && 
      (Port == PortRetrieved) && 
      (PortMultiplierPort == PortMultiplierPortRetrieved)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid003,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.GetDevice - Invoke GetDevice() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, TestPort - 0x%x, TestDevice - 0x%x\n, PortRetrieved - 0x%x, DeviceRetrieved - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort,
                 PortRetrieved,
                 PortMultiplierPortRetrieved
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.ResetPort Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestResetPortFunctionAutoTest (
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

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;

  Port   = 0xFFFF;  
  Status = EFI_SUCCESS;

  while (!EFI_ERROR(Status)) {
    Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"ATA device: Port - 0x%x\n",
                     Port
                     );
      break;
    }
  }

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ATA_PASS_THRU_PROTOCOL.ResetPort - Get an existing Port",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  Status = AtaPassThru->ResetPort (AtaPassThru, Port);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_DEVICE_ERROR || Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid004,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.ResetPort - Invoke ResetPort() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Port - 0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.ResetDevice Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestResetDeviceFunctionAutoTest (
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
  UINT8                                 AtaStatus;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;
  
  Port               = 0xFFFF;
  PortMultiplierPort = 0xFFFF;
  Status = GetPresentDevice (AtaPassThru, &Port, &PortMultiplierPort, &AtaStatus);
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Using correct parameters to get present device on ATA channel, but fail",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  Status = AtaPassThru->ResetDevice (AtaPassThru, Port, PortMultiplierPort);

  if (Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_DEVICE_ERROR || Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid005,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.ResetDevice - Invoke ResetDevice() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Port - 0x%x, PortMultiplierPort - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.GetNextDevice Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.6
//
EFI_STATUS
EFIAPI
BBTestGetNextDeviceFunctionAutoTest (
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
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)ClientInterface;
  
  Port   = 0xFFFF;  
  Status = EFI_SUCCESS;

  while (!EFI_ERROR(Status)) {
    Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
    if (!EFI_ERROR(Status )) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"ATA device: Port - 0x%x\n",
                     Port
                     );

      PortMultiplierPort = 0xFFFF;
      Status             = EFI_SUCCESS;

      Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort);

      while (!EFI_ERROR(Status)) { 
        Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort);
        if (!EFI_ERROR(Status )) {
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_QUIET,
                         L"ATA device: PortMultiplierPort - 0x%x\n",
                         PortMultiplierPort
                         );

        }
      }

      if (Status == EFI_NOT_FOUND) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAtaPassThruBBTestFunctionAssertionGuid006,
                     L"EFI_ATA_PASS_THRU_PROTOCOL.GetNextDevice - Invoke GetNextDevice() and verify interface correctness within test case",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
  } 

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_ATA_PASS_THRU_PROTOCOL.PassThru Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// TDS 3.7
//
EFI_STATUS
EFIAPI
BBTestPassThruFunctionAutoTest (
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
  EFI_EVENT                             Event;
  UINT8                                 AtaStatus; 

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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
  //
  // Call PassThru() with NULL Event.
  //
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
    
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
  } else {
    Packet.Asb          = (VOID *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
    Packet.InDataBuffer = (VOID *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  }  
   
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 1;  /*Using block granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  // Not set the byte: Packet.Length != EFI_ATA_PASS_THRU_LENGTH_BYTES;
  // Make the length not mean "no data"
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;

  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (NormalOutput((Packet.Asb)->AtaStatus)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAtaPassThruBBTestFunctionAssertionGuid007,
                   L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with NULL Event and block-granularity and get EFI_SUCCESS",
                   L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   (Packet.Asb)->AtaStatus
                   );
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR || Status == EFI_TIMEOUT || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid008,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with NULL Event and block-granularity to send 'IDENTIFY DEVICE' command",
                 L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x, AsbStatus - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort,
                 (Packet.Asb)->AtaStatus
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
    
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
  } else {
    Packet.Asb          = (VOID *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
    Packet.InDataBuffer = (VOID *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  }  
   
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;

  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, NULL);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (NormalOutput((Packet.Asb)->AtaStatus)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAtaPassThruBBTestFunctionAssertionGuid007,
                   L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with NULL Event and byte-granularity and get EFI_SUCCESS",
                   L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   (Packet.Asb)->AtaStatus
                   );
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR || Status == EFI_TIMEOUT || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid009,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with NULL Event and byte-granularity to send 'IDENTIFY DEVICE' command",
                 L"%a:%d:Status - %r, Port - 0x%x, Device - 0x%x, AsbStatus - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Port,
                 PortMultiplierPort,
                 (Packet.Asb)->AtaStatus
                 );

  //
  // Call PassThru() with Event.
  //

  //
  // Create Event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunction,
                   NULL,
                   &Event
                   );
  
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  EnterEvent = 0;

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
  
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
  } else {
    Packet.Asb          = (VOID *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
    Packet.InDataBuffer = (VOID *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  }  
   
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 1;  /*Using block granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  // Not set the byte: Packet.Length != EFI_ATA_PASS_THRU_LENGTH_BYTES;
  // Make the length not mean "no data"
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;

  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, Event);

  if (!(AtaPassThru->Mode->Attributes & EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO)) {
    if (!EFI_ERROR(Status) && (EnterEvent == 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (NormalOutput((Packet.Asb)->AtaStatus)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAtaPassThruBBTestFunctionAssertionGuid007,
                     L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with no NULL Event and block-granularity, Blocking Io and get EFI_SUCCESS",
                     L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     (Packet.Asb)->AtaStatus
                     );
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    gtBS->Stall (3*1000*1000);
    if (!EFI_ERROR(Status) && (EnterEvent == 1)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (NormalOutput((Packet.Asb)->AtaStatus)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAtaPassThruBBTestFunctionAssertionGuid007,
                     L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with no NULL Event and block-granularity, non Blocking Io and get EFI_SUCCESS",
                     L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     (Packet.Asb)->AtaStatus
                     );
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
    if (EnterEvent == 1) {//Event should NOT be triggered if return not ready.
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid010,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with Event",
                 L"%a:%d:Status - %r, EnterEvent - %d, Port - 0x%x, Device - 0x%x, AsbStatus - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EnterEvent,
                 Port,
                 PortMultiplierPort, 
                 (Packet.Asb)->AtaStatus
                 );

  EnterEvent = 0;

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
  
  if ((AtaPassThru->Mode->IoAlign == 0) || (AtaPassThru->Mode->IoAlign == 1)){
    Packet.Asb          = Asb;
    Packet.InDataBuffer = InData;
  } else {
    Packet.Asb          = (VOID *)(((UINTN)Asb + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
    Packet.InDataBuffer = (VOID *)(((UINTN)InData + AtaPassThru->Mode->IoAlign - 1)& 
                              ~((UINTN)(AtaPassThru->Mode->IoAlign - 1)));
  }  
   
  Packet.Timeout           = 2 * EFI_ATA_STALL_1_SECOND;
  Packet.Acb               = &Acb;
  Packet.InTransferLength  = 512;  /*Using byte granularity*/
  Packet.OutDataBuffer     = NULL;
  Packet.OutTransferLength = 0;
  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;

  Status = AtaPassThru->PassThru (AtaPassThru, Port, PortMultiplierPort, &Packet, Event);

  if (!(AtaPassThru->Mode->Attributes & EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO)) {
    if (!EFI_ERROR(Status) && (EnterEvent == 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (NormalOutput((Packet.Asb)->AtaStatus)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAtaPassThruBBTestFunctionAssertionGuid007,
                     L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with no NULL Event and byte-granularity, Blocking Io and get EFI_SUCCESS",
                     L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     (Packet.Asb)->AtaStatus
                     );
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    gtBS->Stall (3*1000*1000);
    if (!EFI_ERROR(Status) && (EnterEvent == 1)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (NormalOutput((Packet.Asb)->AtaStatus)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAtaPassThruBBTestFunctionAssertionGuid007,
                     L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Check AtaStatus after sending 'IDENTIFY DEVICE' command with no NULL Event and byte-granularity, non Blocking Io and get EFI_SUCCESS",
                     L"%a:%d: Returned AtaStatus - 0x%x, Expected AsbStatus - (AtaStatus & 0xE9) == 0x40\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     (Packet.Asb)->AtaStatus
                     );
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  if (Status == EFI_NOT_READY || Status == EFI_DEVICE_ERROR || Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
    if (EnterEvent == 1) {//Event should NOT be triggered if return not ready.
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAtaPassThruBBTestFunctionAssertionGuid011,
                 L"EFI_ATA_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with Event",
                 L"%a:%d:Status - %r, EnterEvent - %d, Port - 0x%x, Device - 0x%x, AsbStatus - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EnterEvent,
                 Port,
                 PortMultiplierPort, 
                 (Packet.Asb)->AtaStatus
                 );

  // Close the event
  Status = gtBS->CloseEvent (Event);

Done:
  if (Asb != NULL) {
    SctFreePool (Asb);
  }
  if (InData != NULL) {
    SctFreePool (InData);
  }

  return Status;
}


