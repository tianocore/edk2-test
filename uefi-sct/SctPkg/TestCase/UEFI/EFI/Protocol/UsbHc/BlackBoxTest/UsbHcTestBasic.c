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
  UsbHcTestBasic.c

Abstract:
  Source file for Usb Hc Basic testing.

--*/

#include "SctLib.h"
#include "UsbHcTest.h"

//
// Prototypes (internal)
//
EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );


EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest8 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest9 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest8 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );



//
// Functions
//
/**
 *  TDS 4.1 - Entry point for UsbHc->Reset() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.1.2.1  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL
  //
  Status = UsbHcResetBasicSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.2  Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER
  //
  Status = UsbHcResetBasicSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.3  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER
  //
  Status = UsbHcResetBasicSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.2 - Entry point for UsbHc->GetState() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.2.2.1  GetState() while state is EfiUsbHcStateHalt
  //
  Status = UsbHcGetStateBasicSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.2.2.2  GetState () while state is EfiUsbHcStateOperational
  //
  Status = UsbHcGetStateBasicSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.2.2.3  GetState () while state is EfiUsbHcStateSuspend
  //
  Status = UsbHcGetStateBasicSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3 - Entry point for UsbHc->SetState() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.3.2.1  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt
  //
  Status = UsbHcSetStateBasicSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.2  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational
  //
  Status = UsbHcSetStateBasicSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.3  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend
  //
  //Status = UsbHcSetStateBasicSubTest3(UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.4  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational
  //
  Status = UsbHcSetStateBasicSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.5  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt
  //
  Status = UsbHcSetStateBasicSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.6  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend
  //
  Status = UsbHcSetStateBasicSubTest6 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.7  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend
  //
  Status = UsbHcSetStateBasicSubTest7 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.8  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt
  //
  //Status = UsbHcSetStateBasicSubTest8(UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.9  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational
  //
  //Status = UsbHcSetStateBasicSubTest9(UsbHc, StandardLib, LoggingLib);


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.4 - Entry point for UsbHc->GetRootHubPortNumber() Basic Manual Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.4.2.1  GetRootHubPortNumber () Basic Functionality
  //
  Status = UsbHcGetRootHubPortNumberSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.5 - Entry point for UsbHc->GetRootHubPortStatus() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.5.2.1 GetRootHubPortStatus: Port Enable/Disable
  //
  Status = UsbHcGetRootHubPortStatusSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.2 GetRootHubPortStatus: Suspend
  //
  Status = UsbHcGetRootHubPortStatusSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.3 GetRootHubPortStatus: Port Reset
  //
  Status = UsbHcGetRootHubPortStatusSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.4 GetRootHubPortStatus: Port Power
  //
  Status = UsbHcGetRootHubPortStatusSubTest4 (UsbHc, StandardLib, LoggingLib);


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.6 - Entry point for UsbHc->GetRootHubPortStatus() Basic Manual Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.6.2.1 GetRootHubPortStatus: Connect Status
  //
  Status = UsbHcGetRootHubPortStatusSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.6.2.2 GetRootHubPortStatus:Over-Current Indicator
  //
  Status = UsbHcGetRootHubPortStatusSubTest6 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.6.2.3 GetRootHubPortStatus: Low Speed Device Attached
  //
  Status = UsbHcGetRootHubPortStatusSubTest7 (UsbHc, StandardLib, LoggingLib);


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.7 - Entry point for UsbHc->SetRootHubPortFeature() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.7.2.1 SetRootHubPortFeature: EfiUsbPortEnable
  //
  Status = UsbHcSetRootHubPortFeatureSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.2 SetRootHubPortFeature: EfiUsbPortSuspend
  //
  Status = UsbHcSetRootHubPortFeatureSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.3 SetRootHubPortFeature: EfiUsbPortReset
  //
  Status = UsbHcSetRootHubPortFeatureSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.4 SetRootHubPortFeature: EfiUsbPortPower
  //
  Status = UsbHcSetRootHubPortFeatureSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.8 - Entry point for UsbHc->ClearRootHubPortFeature() Basic Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.8.2.1 ClearRootHubPortFeature: EfiUsbPortEnable
  //
  Status = UsbHcClearRootHubPortFeatureSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.2 ClearRootHubPortFeature: EfiUsbPortSuspend
  //
  Status = UsbHcClearRootHubPortFeatureSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.3 ClearRootHubPortFeature: EfiUsbPortReset
  //
  Status = UsbHcClearRootHubPortFeatureSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.4 ClearRootHubPortFeature: EfiUsbPortPower
  //
  Status = UsbHcClearRootHubPortFeatureSubTest4 (UsbHc, StandardLib, LoggingLib);


  //
  // TDS 4.8.2.5 ClearRootHubPortFeature: EfiUsbPortEnableChange
  //
  Status = UsbHcClearRootHubPortFeatureSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.6 ClearRootHubPortFeature: EfiUsbPortSuspendChange
  //
  Status = UsbHcClearRootHubPortFeatureSubTest6 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.9 - Entry point for UsbHc->ClearRootHubPortFeature() Basic Manual Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_HC_PROTOCOL                 *UsbHc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Hc protocol interface
  //
  UsbHc = (EFI_USB_HC_PROTOCOL *)ClientInterface;

  //
  // TDS 4.9.2.1 ClearRootHubPortFeature: EfiUsbPortConnectChange
  //
  Status = UsbHcClearRootHubPortFeatureSubTest7 (UsbHc, StandardLib, LoggingLib);

  //
  // TDS 4.9.2.2 ClearRootHubPortFeature: EfiUsbPortOverCurrentChange
  //
  Status = UsbHcClearRootHubPortFeatureSubTest8 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

// Sub functions

/**
 *  TDS 4.1.2.1 -  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
/*  EFI_USB_PORT_STATUS     PortStatus;
  BOOLEAN                 UseGenericGuid ;
*/
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest1",
                  L"TDS 4.1.2.1 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL\n"
                  );
  }

  Status = UsbHc->Reset (UsbHc, EFI_USB_HC_RESET_GLOBAL);
  if (!EFI_ERROR(Status)) {
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //record
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbHcTestBasicAssertionGuid001,
                 L"USB_HC_PROTOCOL.Reset - Reset() must success with Attributes",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

 if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest1",
                  L"TDS 4.1.2.1 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.1.2.2 -  Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{

  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
/*EFI_USB_PORT_STATUS     PortStatus;
  BOOLEAN                 UseGenericGuid ;
*/
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest2",
                  L"TDS 4.1.2.2 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }

  Status = UsbHc->Reset (UsbHc, EFI_USB_HC_RESET_HOST_CONTROLLER);
  if (!EFI_ERROR(Status)) {
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //record
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbHcTestBasicAssertionGuid002,
                 L"USB_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

 if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest1",
                  L"TDS 4.1.2.2 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.1.2.3 -  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest3",
                  L"TDS 4.1.2.3 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }


  Status = UsbHc->Reset (UsbHc, EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER);
  if (!EFI_ERROR(Status)) {
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbHcTestBasicAssertionGuid003,
                 L"USB_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcResetBasicSubTest3",
                  L"TDS 4.1.2.3 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.2.2.1 - Call GetState() while state is EfiUsbHcStateHalt
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest1",
                  L"TDS 4.2.2.1 - Call GetState() while state is EfiUsbHcStateHalt\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;

  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
  if (!EFI_ERROR(Status1)) {
    Status = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid004,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest1",
                  L"TDS 4.2.2.1 - Call GetState() while state is EfiUsbHcStateHalt\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.2.2.2 - Call GetState() while state is EfiUsbHcStateOperational
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest2",
                  L"TDS 4.2.2.2 - Call GetState() while state is EfiUsbHcStateOperational\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
  if (!EFI_ERROR(Status1)) {
    Status = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid005,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest2",
                  L"TDS 4.2.2.2 - Call GetState() while state is EfiUsbHcStateOperational\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.2.2.3 - Call GetState() while state is EfiUsbHcStateSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest3",
                  L"TDS 4.2.2.3 - Call GetState() while state is EfiUsbHcStateSuspend\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR(Status1)) {
    Status = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid006,
                   L"USB_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetStateBasicSubTest3",
                  L"TDS 4.2.2.3 - Call GetState() while state is EfiUsbHcStateSuspend\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.3.2.1 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest1",
                  L"TDS 4.3.2.1 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;

  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }

  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid007,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest1",
                  L"TDS 4.3.2.1 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.3.2.2 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest2",
                  L"TDS 4.3.2.2 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }

  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid008,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest2",
                  L"TDS 4.3.2.2 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.3 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest3",
                  L"TDS 4.3.2.3 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;

  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }

  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid009,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest3",
                  L"TDS 4.3.2.3 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.4 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest4",
                  L"TDS 4.3.2.4 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }
  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid010,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest4",
                  L"TDS 4.3.2.4 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.5 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest5",
                  L"TDS 4.3.2.5 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;

  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }

  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
     } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid011,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest5",
                  L"TDS 4.3.2.5 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.6 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest6",
                  L"TDS 4.3.2.6 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend\n"
                  );
  }


  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }
  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid012,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest6",
                  L"TDS 4.3.2.6 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.7 - Call SetState() EfiUsbHcStateSuspend to EfiUsbHcStateSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest7",
                  L"TDS 4.3.2.7 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }

  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid013,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest7",
                  L"TDS 4.3.2.7 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.8 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest8 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest8",
                  L"TDS 4.3.2.8 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }
  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateHalt);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid014,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest8",
                  L"TDS 4.3.2.8 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.3.2.9 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateBasicSubTest9 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_HC_STATE        State;
  EFI_USB_HC_STATE        StateOld;
  BOOLEAN                 UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest9",
                  L"TDS 4.3.2.9 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational\n"
                  );
  }

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  UseGenericGuid = FALSE;
  Status1 = UsbHc->GetState (UsbHc, &StateOld);
  if (EFI_ERROR (Status1)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
    goto record;
  }
  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->SetState (UsbHc, EfiUsbHcStateOperational);
    Status1 = UsbHc->GetState (UsbHc, &State);
    if (!EFI_ERROR(Status1) && State == EfiUsbHcStateOperational) {
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"HcStatePerational Success--- by wff");
      Result = EFI_TEST_ASSERTION_PASSED;
     } else {
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"HcStateOperational Failed--- by wff");
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    UsbHc->SetState (UsbHc, StateOld);
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from from EfiUsbHcStateSuspend to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid015,
                   L"USB_HC_PROTOCOL.SetState - SetState() must success with State from from EfiUsbHcStateSuspend to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest9",
                  L"TDS 4.3.2.9 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.4.2.1 - GetRootHubPortNumber () Basic Functionality (Manual)
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  UINT16                  *Str;


  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest1",
                  L"TDS 4.4.2.1 - GetRootHubPortNumber Basic Functionality\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    // Check whether it is consistent with the hardware manually
    if (AutoJudge (5, TRUE, L"\r\nPortNumber correct?\r\n") == TRUE) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbHcTestBasicAssertionGuid016,
                 L"USB_HC_PROTOCOL.GetRootHubPortNumber - GetRootHubPortNumber() to get PortNumber",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest1",
                  L"TDS 4.4.2.1 - GetRootHubPortNumber Basic Functionality\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.5.2.1 - GetRootHubPortStatus(): Port Enabled/Disabled
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatusOld;
  EFI_USB_PORT_STATUS     PortStatus;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest1",
                  L"TDS 4.5.2.1 - GetRootHubPortStatus: Port Enabled/Disabled \n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status1)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        goto record;
      }

      // Set Port 0 enable
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
        if (!EFI_ERROR(Status1) && PortStatus.PortStatus & USB_PORT_STAT_ENABLE) {
          // Disable Port 0
          Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR(Status)) {
            Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(3): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_ENABLE) == 0) && PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE) {
              Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
              StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(4): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
              if (!EFI_ERROR(Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE) == 0)) {
                Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
            UseGenericGuid = TRUE;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        // RecordAssertion for Genenric Guid
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }

      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Port Enabled/Disabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid017,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Port Enabled/Disabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest1",
                  L"TDS 4.5.2.1 - GetRootHubPortStatus: Port Enabled/Disabled\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.5.2.2 - GetRootHubPortStatus(): Suspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest2",
                  L"TDS 4.5.2.2 - GetRootHubPortStatus: Suspend\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;

  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status1)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        goto record;
      }

      // put port 0 into suspend state
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
        if (!EFI_ERROR(Status1) && PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) {
          // restore port 0 from the previous suspend state
          Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR(Status)) {
            Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(3): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) == 0) && PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND) {
              Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
              StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(4): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
              if (!EFI_ERROR(Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND) == 0)) {
                Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
            UseGenericGuid = TRUE;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        // RecordAssertion for Genenric Guid
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }

      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Suspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid018,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Suspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest2",
                  L"TDS 4.5.2.2 - GetRootHubPortStatus: Suspend\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.5.2.3 - GetRootHubPortStatus(): Port Reset
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest3",
                  L"TDS 4.5.2.3 - GetRootHubPortStatus: Port Reset\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status1)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        goto record;
      }

      // clear the RESET signal of port 0
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
        if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_RESET) == 0)) {
          // reset port 0
          Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
          if (!EFI_ERROR(Status)) {
            gtBS->Stall (1000 * 1000);
    //      Status = UsbHc->ClearRootHubPortFeature(UsbHc, 0, EfiUsbPortReset);
            Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(3): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status1) && (PortStatus.PortStatus & USB_PORT_STAT_RESET) && PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET) {
            Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
              StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(4): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
              if (!EFI_ERROR(Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET) == 0)) {
                 Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                 Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          }else {
            //RecordAssertion for Genenric Guid
            Result = EFI_TEST_ASSERTION_FAILED;
            UseGenericGuid = TRUE;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        // RecordAssertion for Genenric Guid
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Port Reset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid019,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Port Reset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest3",
                  L"TDS 4.5.2.3 - GetRootHubPortStatus: Port Reset\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.5.2.4 - GetRootHubPortStatus(): Port Power
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest4",
                  L"TDS 4.5.2.4 - GetRootHubPortStatus: Port Power\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status1)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        goto record;
      }

      // power the port 0
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
        if (!EFI_ERROR(Status1) && PortStatus.PortStatus & USB_PORT_STAT_POWER) {
          // shutdown the power of port 0
          Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR(Status)) {
            Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(3): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_POWER) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
            UseGenericGuid = TRUE;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        // RecordAssertion for Genenric Guid
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Power Port",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid020,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Power Port",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest4",
                  L"TDS 4.5.2.4 - GetRootHubPortStatus: Power Port\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.6.2.1 - GetRootHubPortStatus(): Connect Status
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  //EFI_INPUT_KEY           Key;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest5",
                  L"TDS 4.6.2.1 - GetRootHubPortStatus: Connect Status\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // make sure there is no device present on port 0
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"make sure there is no device present on port 0 of Host Controller %s, waiting for 20s\n", Str);
      StallForChangeDevice (StandardLib, 20);

      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(1): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
      if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_CONNECTION) == 0)) {
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Plug a device into port 0 of Host Controller %s, waiting for 20s\n", Str);
        StallForChangeDevice (StandardLib, 20);

        Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
        StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
        if (!EFI_ERROR(Status1) && (PortStatus.PortStatus & USB_PORT_STAT_CONNECTION) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)) {
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Pull out the device from port 0 of Host Controller %s, waiting for 20s\n", Str);
          StallForChangeDevice (StandardLib, 20);
          Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(3): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_CONNECTION)== 0) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber


  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Connect Status",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid021,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Connect Status",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest5",
                  L"TDS 4.6.2.1 - GetRootHubPortStatus: Connect Status\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.6.2.2 - GetRootHubPortStatus(): Over-Current Indicator
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  // TBD
  return EFI_SUCCESS;
}

/**
 *  TDS 4.6.2.3 - GetRootHubPortStatus(): Low Speed Device Attached
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  //EFI_INPUT_KEY           Key;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest7",
                  L"TDS 4.6.2.3 - GetRootHubPortStatus: Low Speed Device Attached\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // make sure there is no device present on port 0
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"make sure there is no device present on port 0 and pull a usb keyboard into port 0 of Host Controller %s, waiting for 20s\n", Str);
      StallForChangeDevice (StandardLib, 20);
      Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(1): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);

      if (!EFI_ERROR(Status1) && (PortStatus.PortStatus & USB_PORT_STAT_CONNECTION)) {
        if (!EFI_ERROR(Status1) && (PortStatus.PortStatus & USB_PORT_STAT_LOW_SPEED)) {
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Pull out the usb keyboard from port 0 of Host Controller %s and plug a usb zip, waiting for 20s\n", Str);
          StallForChangeDevice (StandardLib, 20);
          Status1 = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_LOW_SPEED)== 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        } //endif USB_PORT_STAT_LOW_SPEED
      }else{
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      } // endif USB_PORT_STAT_CONNECTION

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber


  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Low Speed Device Attached",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid022,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Low Speed Device Attached",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest7",
                  L"TDS 4.6.2.3 - GetRootHubPortStatus: Low Speed Device Attached\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.7.2.1 - SetRootHubPortFeature(): EfiUsbPortEnable
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest1",
                  L"TDS 4.7.2.1 - SetRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }

 // _asm jmp $

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"(wff--)Current_GetRootHubPortStatus(2): %d, %d", PortStatusOld.PortStatus, PortStatusOld.PortChangeStatus);

      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // disable port 0
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // enable port 0
        Status1 = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && (PortStatus.PortStatus & USB_PORT_STAT_ENABLE) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }

      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortEnable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid023,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortEnable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest1",
                  L"TDS 4.7.2.1 - SetRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.7.2.2 - SetRootHubPortFeature(): EfiUsbPortSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest2",
                  L"TDS 4.7.2.2 - SetRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // restore port 0 from the suspend state
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // put port 0 into suspend state
        Status1 = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && (PortStatus.PortStatus & USB_PORT_STAT_SUSPEND)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid024,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest2",
                  L"TDS 4.7.2.2 - SetRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.7.2.3 - SetRootHubPortFeature(): EfiUsbPortReset
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest3",
                  L"TDS 4.7.2.3 - SetRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // clear the RESET signal for port 0
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // reset port 0
        Status1 = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        if (!EFI_ERROR (Status1)) {
          gtBS->Stall (1000 * 1000);
//          Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
          if (!EFI_ERROR(Status1)) {
            Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status) && (PortStatus.PortStatus & USB_PORT_STAT_RESET) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        }else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortReset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid025,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortReset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest3",
                  L"TDS 4.7.2.3 - SetRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.7.2.4 - SetRootHubPortFeature(): EfiUsbPortPower
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest4",
                  L"TDS 4.7.2.4 - SetRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // shutdown the power from port 0
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // power the port 0.
        Status1 = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && (PortStatus.PortStatus & USB_PORT_STAT_POWER)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortPower",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid026,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortPower",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureSubTest4",
                  L"TDS 4.7.2.4 - SetRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.8.2.1 - ClearRootHubPortFeature(): EfiUsbPortEnable
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest1",
                  L"TDS 4.8.2.1 - ClearRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }
      // Enable Port 0
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // Disable Port 0
        Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && ((PortStatus.PortStatus & USB_PORT_STAT_ENABLE) == 0) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid027,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest1",
                  L"TDS 4.8.2.1 - ClearRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.8.2.2 - ClearRootHubPortFeature(): EfiUsbPortSuspend
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest2",
                  L"TDS 4.8.2.2 - ClearRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // Put Port 0 into suspend state
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // restore port 0 from the previous suspend state
        Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && ((PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) == 0) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid028,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest2",
                  L"TDS 4.8.2.2 - ClearRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.8.2.3 - ClearRootHubPortFeature(): EfiUsbPortReset
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest3",
                  L"TDS 4.8.2.3 - ClearRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // reset port 0
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        // clear the RESET signal for port 0
        Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && ((PortStatus.PortStatus & USB_PORT_STAT_RESET) == 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      }else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }

      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortReset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid029,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortReset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest3",
                  L"TDS 4.8.2.3 - ClearRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.8.2.4 - ClearRootHubPortFeature(): EfiUsbPortPower
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest4",
                  L"TDS 4.8.2.4 - ClearRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller is %s %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }
      // power the port 0
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // shutdown the power from port 0
        Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && ((PortStatus.PortStatus & USB_PORT_STAT_POWER) == 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();

    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortPower",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid030,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortPower",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest4",
                  L"TDS 4.8.2.4 - ClearRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.8.2.5 - ClearRootHubPortFeature(): EfiUsbPortEnableChange
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest5",
                  L"TDS 4.8.2.5 - ClearRootHubPortFeature: EfiUsbPortEnableChange\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // disable port 0
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // enable port 0
        Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status)) {
          Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnableChange);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR(Status1)) {
            Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid = TRUE;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnableChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid031,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnableChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest5",
                  L"TDS 4.8.2.5 - ClearRootHubPortFeature: EfiUsbPortEnableChange\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.8.2.6 - ClearRootHubPortFeature(): EfiUsbPortSuspendChange
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  EFI_USB_PORT_STATUS     PortStatusOld;
  BOOLEAN                 UseGenericGuid;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.8.2.6 - ClearRootHubPortFeature: EfiUsbPortSuspendChange\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();
      // save the port 0 status
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatusOld);
      if (EFI_ERROR(Status)) {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
        goto record;
      }

      // put port 0 into suspend state
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR(Status)) {
        // restore port 0 from suspend state
        Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status)) {
          Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspendChange);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR(Status1)) {
            Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
            StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
            if (!EFI_ERROR(Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid = TRUE;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }


      // restore port 0
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        UsbHc->SetRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber

record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspendChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid032,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspendChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.8.2.6 - ClearRootHubPortFeature: EfiUsbPortSuspendChange\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.9.2.1 - ClearRootHubPortFeature(): EfiUsbPortConnectChange
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest7 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_STATUS              Status1;
  //EFI_STATUS              Status2;
  //EFI_STATUS              Status3;
  UINT8                   PortNumber;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_PORT_STATUS     PortStatus;
  BOOLEAN                 UseGenericGuid;
  //EFI_INPUT_KEY           Key;
  UINT16                  *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest7",
                  L"TDS 4.9.2.1 - ClearRootHubPortFeature: EfiUsbPortConnectChange\n"
                  );
  }

  Str = SctDevicePathStrFromProtocol (UsbHc, &gBlackBoxEfiUsbHcProtocolGuid);
  UseGenericGuid = FALSE;
  Status = EFI_SUCCESS;
  Status1 = EFI_SUCCESS;
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"The PortNumber for this Host Controller %s is %d", Str, PortNumber);
    if (PortNumber > 0) {
      // mask timer interrupt
      MaskTimerInterrupt ();

      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Make sure that there is no device on port 0 of Host Conteoller %s\n", Str);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Plug a device into port 0 of Host Controller %s\n", Str);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Pull out the device from port 0 of Host Controller %s\n", Str);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Waiting for 20s\n");
      StallForChangeDevice(StandardLib, 20);
      Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(1): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
      if (!EFI_ERROR(Status) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)) {
        Status1 = UsbHc->ClearRootHubPortFeature (UsbHc, 0, EfiUsbPortConnectChange);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR(Status1)) {
          Status = UsbHc->GetRootHubPortStatus (UsbHc, 0, &PortStatus);
          StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"GetRootHubPortStatus(2): %d, %d", PortStatus.PortStatus, PortStatus.PortChangeStatus);
          if (!EFI_ERROR(Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION) == 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid = TRUE;
      }
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    } // end portnumber > 0
  } else {
    // RecordAssertion for Genenric Guid
    Result = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid = TRUE;
  } // endif GetRootHubPortNumber


  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortConnectChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbHcTestBasicAssertionGuid033,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortConnectChange",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  }

done:
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.9.2.1 - ClearRootHubPortFeature: EfiUsbPortConnectChange\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 4.9.2.2 - ClearRootHubPortFeature(): EfiUsbPortOverCurrentChange
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureSubTest8 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  // TBD
  return EFI_SUCCESS;
}


