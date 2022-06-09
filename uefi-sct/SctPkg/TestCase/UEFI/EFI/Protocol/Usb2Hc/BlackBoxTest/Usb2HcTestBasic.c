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
  Usb2HcTestBasic.c

Abstract:
  Source file for Usb2 Hc Basic testing.

--*/
#include "SctLib.h"
#include "Usb2HcTest.h"

//
// Prototypes
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilitySubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest8 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest9 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest8 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest9 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

//
// Functions
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilityBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetCapability() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.1.2.1  GetCapability() Basic Functionality
  //
  Status = Usb2HcGetCapabilitySubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Reset() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.2.2.1  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL
  //
  Status = Usb2HcResetBasicSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.2  Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER
  //
  Status = Usb2HcResetBasicSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.3  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER
  //
  Status = Usb2HcResetBasicSubTest3 (Usb2Hc, StandardLib, LoggingLib);
  //
  // TDS 4.2.2.4  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG
  //
  Status = Usb2HcResetBasicSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.5  Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG
  //
  Status = Usb2HcResetBasicSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.1.2.6  Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG | EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG
  //
  Status = Usb2HcResetBasicSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetState() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.3.2.1  GetState() while state is EfiUsbHcStateHalt
  //
  Status = Usb2HcGetStateBasicSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.2  GetState() while state is EfiUsbHcStateOperational
  //
  Status = Usb2HcGetStateBasicSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.3.2.3  GetState() while state is EfiUsbHcStateSuspend
  //
  Status = Usb2HcGetStateBasicSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetState() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.4.2.1  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt
  //
  Status = Usb2HcSetStateBasicSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.2  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational
  //
  Status = Usb2HcSetStateBasicSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.3  SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend
  //
  Status = Usb2HcSetStateBasicSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.4  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational
  //
  Status = Usb2HcSetStateBasicSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.5  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt
  //
  Status = Usb2HcSetStateBasicSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.6  SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend
  //
  Status = Usb2HcSetStateBasicSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.7  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend
  //
  Status = Usb2HcSetStateBasicSubTest7 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.8  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt
  //
  Status = Usb2HcSetStateBasicSubTest8 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.4.2.9  SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational
  //
  Status = Usb2HcSetStateBasicSubTest9 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.5.2.1 GetRootHubPortStatus: Port Enable/Disable
  //
  Status = Usb2HcGetRootHubPortStatusSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.2 GetRootHubPortStatus: Suspend
  //
  Status = Usb2HcGetRootHubPortStatusSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.3 GetRootHubPortStatus: Port Reset
  //
  Status = Usb2HcGetRootHubPortStatusSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.5.2.4 GetRootHubPortStatus: Port Power
  //
  Status = Usb2HcGetRootHubPortStatusSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.6.2.1 GetRootHubPortStatus: Connect Status
  //
  Status = Usb2HcGetRootHubPortStatusSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.6.2.2 GetRootHubPortStatus:Over-Current Indicator
  //
  Status = Usb2HcGetRootHubPortStatusSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.6.2.3 GetRootHubPortStatus: Different Speed Device Attached
  //
  Status = Usb2HcGetRootHubPortStatusSubTest7 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetRootHubPortFeature() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.7.2.1 SetRootHubPortFeature: EfiUsbPortEnable
  //
  Status = Usb2HcSetRootHubPortFeatureSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.2 SetRootHubPortFeature: EfiUsbPortSuspend
  //
  Status = Usb2HcSetRootHubPortFeatureSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.3 SetRootHubPortFeature: EfiUsbPortReset
  //
  Status = Usb2HcSetRootHubPortFeatureSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.7.2.4 SetRootHubPortFeature: EfiUsbPortPower
  //
  Status = Usb2HcSetRootHubPortFeatureSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Basic Auto Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.8.2.1 ClearRootHubPortFeature: EfiUsbPortEnable
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.2 ClearRootHubPortFeature: EfiUsbPortSuspend
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.3 ClearRootHubPortFeature: EfiUsbPortReset
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.4 ClearRootHubPortFeature: EfiUsbPortPower
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.5 ClearRootHubPortFeature: EfiUsbPortEnableChange
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.8.2.6 ClearRootHubPortFeature: EfiUsbPortSuspendChange
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Basic Manual Test.

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB2_HC_PROTOCOL                *Usb2Hc;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
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

  //
  // Test Logging Support Library is optional
  //
  // Get the Usb2 Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 4.9.2.1 ClearRootHubPortFeature: EfiUsbPortConnectChange
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest7 (Usb2Hc, StandardLib, LoggingLib);

  //
  // TDS 4.9.2.2 ClearRootHubPortFeature: EfiUsbPortOverCurrentChange
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest8 (Usb2Hc, StandardLib, LoggingLib);
  //
  // TDS 4.9.2.2 ClearRootHubPortFeature: EfiUsbPortOverCurrentChange
  //
  Status = Usb2HcClearRootHubPortFeatureSubTest9 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}
//
// Sub functions
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilitySubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetCapability () Basic Functionality (Manual) 

Arguments:

  This                    - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface         - A pointer to the interface to be tested.
  TestLevel               - Test "thoroughness" control.
  SupportHandle           - A handle containing support protocols.

Returns:

  EFI_SUCCESS             - Successfully.
  Other value             - Something failed.

--*/
{
  EFI_STATUS          Status;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilitySubTest1",
                  L"TDS 4.1.2.1 - GetCapability Basic Functionality\n"
                  );
  }

  Str     = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);

  Status  = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"this Host Controller %s's MaxSpeed is %d, PortNumber is %d, Is64BitCapable is %d",
                   Str,
                   MaxSpeed,
                   PortNumber,
                   Is64BitCapable
                   );
    //          
    // Check whether it is consistent with the hardware manually
    //
    if (AutoJudge (5, TRUE, L"\r\nMaxSpeed, PortNumber and Is64BitCapable correct?\r\n") == TRUE) {
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
                 gUsb2HcTestBasicAssertionGuid001,
                 L"USB2_HC_PROTOCOL.GetCapability - GetCapability() to get MaxSpeed, PortNumber and Is64BitCapable",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilitySubTest1",
                  L"TDS 4.4.2.1 - GetRootHubPortNumber Basic Functionality\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL

Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest1",
                  L"TDS 4.2.2.1 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_GLOBAL);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // record
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestBasicAssertionGuid002,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_GLOBAL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest1",
                  L"TDS 4.2.2.1 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER

Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest2",
                  L"TDS 4.2.2.2 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_HOST_CONTROLLER);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // record
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestBasicAssertionGuid003,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest2",
                  L"TDS 4.2.2.2 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other valu      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest3",
                  L"TDS 4.2.2.3 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
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
                 gUsb2HcTestBasicAssertionGuid004,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest3",
                  L"TDS 4.2.2.3 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest4",
                  L"TDS 4.2.2.4 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_GLOBAL_DEBUG);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // record
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestBasicAssertionGuid005,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest4",
                  L"TDS 4.2.2.4 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest5",
                  L"TDS 4.2.2.5 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // record
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestBasicAssertionGuid006,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest5",
                  L"TDS 4.2.2.5 - Call Reset while Attributes is EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetBasicSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG | EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest6",
                  L"TDS 4.2.2.6 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG | EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG\n"
                  );
  }

  Status = Usb2Hc->Reset (Usb2Hc, EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER);
  if (!EFI_ERROR (Status)) {
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
      Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
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
                 gUsb2HcTestBasicAssertionGuid007,
                 L"USB2_HC_PROTOCOL.Reset - Reset() must success with Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG | EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetBasicSubTest6",
                  L"TDS 4.2.2.6 - Call Reset while Attributes is EFI_USB_HC_RESET_GLOBAL_DEBUG | EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call GetState() while state is EfiUsbHcStateHalt 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest1",
                  L"TDS 4.3.2.1 - Call GetState() while state is EfiUsbHcStateHalt\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;

  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
  if (!EFI_ERROR (Status1)) {
    Status = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
  } else {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
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
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid008,
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest1",
                  L"TDS 4.3.2.1 - Call GetState() while state is EfiUsbHcStateHalt\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call GetState() while state is EfiUsbHcStateOperational 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest2",
                  L"TDS 4.3.2.2 - Call GetState() while state is EfiUsbHcStateOperational\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
  if (!EFI_ERROR (Status1)) {
    Status = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
  } else {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
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
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid009,
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest2",
                  L"TDS 4.3.2.2 - Call GetState() while state is EfiUsbHcStateOperational\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call GetState() while state is EfiUsbHcStateSuspend 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest3",
                  L"TDS 4.3.2.3 - Call GetState() while state is EfiUsbHcStateSuspend\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result = EFI_TEST_ASSERTION_FAILED;
    goto record;
  }

  Status1 = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR (Status1)) {
    Status = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
  } else {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
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
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid010,
                   L"USB2_HC_PROTOCOL.GetState - GetState() must success with current state is EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetStateBasicSubTest3",
                  L"TDS 4.3.2.3 - Call GetState() while state is EfiUsbHcStateSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest1",
                  L"TDS 4.4.2.1 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;

  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid011,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest1",
                  L"TDS 4.4.2.1 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateHalt\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from from EfiUsbHcStateHalt to EfiUsbHcStateOperational 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest2",
                  L"TDS 4.4.2.2 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid012,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest2",
                  L"TDS 4.4.2.2 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateOperational\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateBasicSubTest3",
                  L"TDS 4.3.2.3 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;

  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid013,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateHalt to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest3",
                  L"TDS 4.4.2.3 - Call SetState() from EfiUsbHcStateHalt to EfiUsbHcStateSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest4",
                  L"TDS 4.4.2.4 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateOperational) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid014,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest4",
                  L"TDS 4.4.2.4 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateOperational\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest5",
                  L"TDS 4.4.2.5 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;

  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid015,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest5",
                  L"TDS 4.4.2.5 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateHalt\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest6",
                  L"TDS 4.4.2.6 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid016,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateOperational to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest6",
                  L"TDS 4.4.2.6 - Call SetState() from EfiUsbHcStateOperational to EfiUsbHcStateSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest7",
                  L"TDS 4.4.2.7 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateSuspend) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid017,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest7",
                  L"TDS 4.4.2.7 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest8 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest8",
                  L"TDS 4.4.2.8 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status          = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateHalt);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status) && State == EfiUsbHcStateHalt) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid018,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from EfiUsbHcStateSuspend to EfiUsbHcStateHalt",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest8",
                  L"TDS 4.4.2.8 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateHalt\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetStateBasicSubTest9 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_HC_STATE    State;
  EFI_USB_HC_STATE    StateOld;
  BOOLEAN             UseGenericGuid;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest9",
                  L"TDS 4.4.2.9 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational\n"
                  );
  }

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  UseGenericGuid  = FALSE;
  Status1         = Usb2Hc->GetState (Usb2Hc, &StateOld);
  if (EFI_ERROR (Status1)) {
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
    goto record;
  }

  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateSuspend);
  if (!EFI_ERROR (Status)) {
    Status  = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateOperational);
    Status1 = Usb2Hc->GetState (Usb2Hc, &State);
    if (!EFI_ERROR (Status1) && State == EfiUsbHcStateOperational) {
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"HcStatePerational Success--- by wff");
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"HcStateOperational Failed--- by wff");
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    Usb2Hc->SetState (Usb2Hc, StateOld);
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
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from from EfiUsbHcStateSuspend to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestBasicAssertionGuid019,
                   L"USB2_HC_PROTOCOL.SetState - SetState() must success with State from from EfiUsbHcStateSuspend to EfiUsbHcStateOperational",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateBasicSubTest9",
                  L"TDS 4.4.2.9 - Call SetState() from EfiUsbHcStateSuspend to EfiUsbHcStateOperational\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Port Enabled/Disabled 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatusOld;
  EFI_USB_PORT_STATUS PortStatus;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusSubTest1",
                  L"TDS 4.5.2.1 - GetRootHubPortStatus: Port Enabled/Disabled \n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;

  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port status
      //
      for (port = 0; port < PortNumber; port++) {
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatusOld);
        if (EFI_ERROR (Status1)) {
          Result = EFI_TEST_ASSERTION_FAILED;
          goto record;
        }
        //
        // Set Port enable
        //
        Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                         port,
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status1) && PortStatus.PortStatus & USB_PORT_STAT_ENABLE) {
            //
            // Disable Port
            //
            Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortEnable);
            gtBS->Stall (1000 * 1000);
            if (!EFI_ERROR (Status)) {
              Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                             port,
                             PortStatus.PortStatus,
                             PortStatus.PortChangeStatus
                             );
              if (!EFI_ERROR (Status1) &&
                  ((PortStatus.PortStatus & USB_PORT_STAT_ENABLE) == 0) &&
                  PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE
                  ) {
                Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
                StandardLib->RecordMessage (
                               StandardLib,
                               EFI_VERBOSE_LEVEL_DEFAULT,
                               L"Port: %d, GetRootHubPortStatus(4): %d, %d",
                               port,
                               PortStatus.PortStatus,
                               PortStatus.PortChangeStatus
                               );
                if (!EFI_ERROR (Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE) == 0)) {
                  Result = EFI_TEST_ASSERTION_PASSED;
                } else {
                  Result = EFI_TEST_ASSERTION_FAILED;
                }
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result          = EFI_TEST_ASSERTION_FAILED;
              UseGenericGuid  = TRUE;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          //
          // RecordAssertion for Genenric Guid
          //
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
        //
        // restore port
        //
        if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
          Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortEnable);
          gtBS->Stall (1000 * 1000);
        } else {
          Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortEnable);
          gtBS->Stall (1000 * 1000);
        }
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Port Enabled/Disabled",
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
                   gUsb2HcTestBasicAssertionGuid021,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Port Enabled/Disabled",
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
                  L"Usb2HcGetRootHubPortStatusSubTest1",
                  L"TDS 4.5.2.1 - GetRootHubPortStatus: Port Enabled/Disabled\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Suspend
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusSubTest2",
                  L"TDS 4.5.2.2 - GetRootHubPortStatus: Suspend\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;

  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();
      for (port = 0; port < PortNumber; port++) {
        //
        // save the port status
        //
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatusOld);
        if (EFI_ERROR (Status1)) {
          Result = EFI_TEST_ASSERTION_FAILED;
          goto record;
        }
        //
        // put port into suspend state
        //
        Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                         port,
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status1) && PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) {
            //
            // restore port from the previous suspend state
            //
            Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortSuspend);
            gtBS->Stall (1000 * 1000);
            if (!EFI_ERROR (Status)) {
              Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                             port,
                             PortStatus.PortStatus,
                             PortStatus.PortChangeStatus
                             );
              if (!EFI_ERROR (Status1) &&
                  ((PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) == 0) &&
                  PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND
                  ) {
                Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
                StandardLib->RecordMessage (
                               StandardLib,
                               EFI_VERBOSE_LEVEL_DEFAULT,
                               L"Port: %d, GetRootHubPortStatus(4): %d, %d",
                               port,
                               PortStatus.PortStatus,
                               PortStatus.PortChangeStatus
                               );
                if (!EFI_ERROR (Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND) == 0)) {
                  Result = EFI_TEST_ASSERTION_PASSED;
                } else {
                  Result = EFI_TEST_ASSERTION_FAILED;
                }
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result          = EFI_TEST_ASSERTION_FAILED;
              UseGenericGuid  = TRUE;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          //
          // RecordAssertion for Genenric Guid
          //
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
        //
        // restore port
        //
        if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
          Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortSuspend);
          gtBS->Stall (1000 * 1000);
        } else {
          Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortSuspend);
          gtBS->Stall (1000 * 1000);
        }
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Suspend",
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
                   gUsb2HcTestBasicAssertionGuid022,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Suspend",
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
                  L"Usb2HcGetRootHubPortStatusSubTest2",
                  L"TDS 4.5.2.2 - GetRootHubPortStatus: Suspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Port Reset
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest3",
                  L"TDS 4.5.2.3 - GetRootHubPortStatus: Port Reset\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();
      for (port = 0; port < PortNumber; port++) {
        //
        // save the port 0 status
        //
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatusOld);
        if (EFI_ERROR (Status1)) {
          Result = EFI_TEST_ASSERTION_FAILED;
          goto record;
        }
        //
        // clear the RESET signal of port
        //
        Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                         port,
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_RESET) == 0)) {
            //
            // reset port
            //
            Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortReset);
            if (!EFI_ERROR (Status)) {
              gtBS->Stall (1000 * 1000);
              Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                             port,
                             PortStatus.PortStatus,
                             PortStatus.PortChangeStatus
                             );
              if (!EFI_ERROR (Status1) &&
                  (PortStatus.PortStatus & USB_PORT_STAT_RESET) &&
                  PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET
                  ) {
                Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
                StandardLib->RecordMessage (
                               StandardLib,
                               EFI_VERBOSE_LEVEL_DEFAULT,
                               L"Port: %d, GetRootHubPortStatus(4): %d, %d",
                               port,
                               PortStatus.PortStatus,
                               PortStatus.PortChangeStatus
                               );
                if (!EFI_ERROR (Status1) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET) == 0)) {
                  Result = EFI_TEST_ASSERTION_PASSED;
                } else {
                  Result = EFI_TEST_ASSERTION_FAILED;
                }
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              //
              // RecordAssertion for Genenric Guid
              //
              Result          = EFI_TEST_ASSERTION_FAILED;
              UseGenericGuid  = TRUE;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          //
          // RecordAssertion for Genenric Guid
          //
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
        //
        // restore port
        //
        if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
          Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortReset);
          gtBS->Stall (1000 * 1000);
        } else {
          Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortReset);
          gtBS->Stall (1000 * 1000);
        }
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Port Reset",
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
                   gUsb2HcTestBasicAssertionGuid023,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Port Reset",
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
                  L"Usb2HcGetRootHubPortStatusSubTest3",
                  L"TDS 4.5.2.3 - GetRootHubPortStatus: Port Reset\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Port Power 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusSubTest4",
                  L"TDS 4.5.2.4 - GetRootHubPortStatus: Port Power\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();
      for (port = 1; port < PortNumber; port++) {
        //
        // save the port status
        //
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatusOld);
        if (EFI_ERROR (Status1)) {
          Result = EFI_TEST_ASSERTION_FAILED;
          goto record;
        }
        //
        // power the port
        //
        Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Port : %d, GetRootHubPortStatus(2): %d, %d",
                         port,
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status1) && PortStatus.PortStatus & USB_PORT_STAT_POWER) {
            //
            // shutdown the power of port
            //
            Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortPower);
            gtBS->Stall (1000 * 1000);
            if (!EFI_ERROR (Status)) {
              Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                             port,
                             PortStatus.PortStatus,
                             PortStatus.PortChangeStatus
                             );
              if (!EFI_ERROR (Status1) && ((PortStatus.PortStatus & USB_PORT_STAT_POWER) == 0)) {
                Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              Result          = EFI_TEST_ASSERTION_FAILED;
              UseGenericGuid  = TRUE;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          //
          // RecordAssertion for Genenric Guid
          //
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
        //
        // restore port
        //
        if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
          Usb2Hc->SetRootHubPortFeature (Usb2Hc, port, EfiUsbPortPower);
          gtBS->Stall (1000 * 1000);
        } else {
          Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortPower);
          gtBS->Stall (1000 * 1000);
        }
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Power Port",
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
                   gUsb2HcTestBasicAssertionGuid024,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Power Port",
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
                  L"Usb2HcGetRootHubPortStatusSubTest4",
                  L"TDS 4.5.2.4 - GetRootHubPortStatus: Power Port\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Connect Status 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  //
  // EFI_INPUT_KEY           Key;
  //
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusSubTest5",
                  L"TDS 4.6.2.1 - GetRootHubPortStatus: Connect Status\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // make sure there is no device present on each port
      // SctPrint(L"make sure there is no device present on each port, Press any key to continue\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"make sure there is no device present on each port of Host Controller %s, waiting for 20s\n",
                     Str
                     );
      //
      // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
      //
      StallForChangeDevice (StandardLib, 20);
      for (port = 0; port < PortNumber; port++) {
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Port: %d, GetRootHubPortStatus(1): %d, %d",
                       port,
                       PortStatus.PortStatus,
                       PortStatus.PortChangeStatus
                       );
        if (EFI_ERROR (Status1) && !((PortStatus.PortStatus & USB_PORT_STAT_CONNECTION) == 0)) {
          Result = EFI_TEST_ASSERTION_FAILED;
          goto record;
        }
      }
      //
      // SctPrint(L"Plug a device into a port, Press any key to continue\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Plug a device into a port of Host Controller %s, waiting for 20s\n",
                     Str
                     );
      //
      // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
      //
      StallForChangeDevice (StandardLib, 20);
      for (port = 0; port < PortNumber; port++) {
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                       port,
                       PortStatus.PortStatus,
                       PortStatus.PortChangeStatus
                       );
        if (!EFI_ERROR (Status1) &&
            (PortStatus.PortStatus & USB_PORT_STAT_CONNECTION) &&
            (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)
            ) {
          //
          // SctPrint(L"Pull out the device from the port, Press any key to continue\n");
          //
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Pull out the device from the port of Host Controller %s, waiting for 20s\n",
                         Str
                         );
          //
          // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
          //
          StallForChangeDevice (StandardLib, 20);
          Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                         port,
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status1) &&
              ((PortStatus.PortStatus & USB_PORT_STAT_CONNECTION) == 0) &&
              (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)
              ) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }

          goto record;
        } else {
        }
      }

      Result = EFI_TEST_ASSERTION_FAILED;
record:
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with State being Connect Status",
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
                   gUsb2HcTestBasicAssertionGuid025,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Connect Status",
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
                  L"Usb2HcGetRootHubPortStatusSubTest5",
                  L"TDS 4.6.2.1 - GetRootHubPortStatus: Connect Status\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Over-Current Indicator 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  //
  // TBD
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  GetRootHubPortStatus(): Different Speed Device Attached 
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  //
  // EFI_INPUT_KEY           Key;
  //
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusSubTest7",
                  L"TDS 4.6.2.3 - GetRootHubPortStatus: Different Speed Device Attached\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // make sure there is no device present on each port
      // SctPrint(L"make sure there is no device present on each port and pull a usb keyboard into a port, Press any key to continue\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"make sure there is no device present on each port and pull a usb keyboard into a port of Host Controller %s, waiting for 20s\n",
                     Str
                     );
      //
      // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
      //
      StallForChangeDevice (StandardLib, 20);
      for (port = 0; port < PortNumber; port++) {
        Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Port: %d, GetRootHubPortStatus(1): %d, %d",
                       port,
                       PortStatus.PortStatus,
                       PortStatus.PortChangeStatus
                       );

        if (!EFI_ERROR (Status1) && (PortStatus.PortStatus & USB_PORT_STAT_CONNECTION)) {
          if (!EFI_ERROR (Status1) &&
              (PortStatus.PortStatus & USB_PORT_STAT_LOW_SPEED) &&
              ((PortStatus.PortStatus & USB_PORT_STAT_HIGH_SPEED) == 0)
              ) {
            //
            // SctPrint(L"Pull out the usb keyboard from the port and plug a usb1.0 zip, Press any key to continue\n");
            //
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"Pull out the usb keyboard from the port of Host Controller %s and plug a usb1.0 zip, waiting for 20s\n",
                           Str
                           );
            //
            // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
            //
            StallForChangeDevice (StandardLib, 20);
            Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                           PortStatus.PortStatus,
                           PortStatus.PortChangeStatus
                           );
            if (!EFI_ERROR (Status1) &&
                ((PortStatus.PortStatus & USB_PORT_STAT_LOW_SPEED) == 0) &&
                ((PortStatus.PortStatus & USB_PORT_STAT_HIGH_SPEED) == 0)
                ) {
              //
              // SctPrint(L"Pull out the usb1.0 zip from the port and plug a usb2.0 zip, Press any key to continue\n");
              //
              StandardLib->RecordMessage (
                            StandardLib,
                            EFI_VERBOSE_LEVEL_DEFAULT,
                            L"Pull out the usb1.0 zip from the port of Host Controller %s and plug a usb2.0 zip, waiting for 20s\n",
                            Str
                            );
              //
              // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
              //
              StallForChangeDevice (StandardLib, 20);
              Status1 = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_DEFAULT,
                             L"Port: %d, GetRootHubPortStatus(3): %d, %d",
                             port,
                             PortStatus.PortStatus,
                             PortStatus.PortChangeStatus
                             );
              if (!EFI_ERROR (Status1) && (PortStatus.PortStatus & USB_PORT_STAT_HIGH_SPEED)) {
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
          //
          // endif USB_PORT_STAT_LOW_SPEED
          //
          goto recode;
        }
      }
      //
      // endif USB_PORT_STAT_CONNECTION
      //
      Result = EFI_TEST_ASSERTION_FAILED;
recode:
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Different Speed Device Attached",
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
                   gUsb2HcTestBasicAssertionGuid026,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() with Different Speed Device Attached",
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
                  L"Usb2HcGetRootHubPortStatusSubTest7",
                  L"TDS 4.6.2.3 - GetRootHubPortStatus: Different Speed Device Attached\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  SetRootHubPortFeature(): EfiUsbPortEnable  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureSubTest1",
                  L"TDS 4.7.2.1 - SetRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }
  //
  // _asm jmp $
  //
  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"(wff--)Current_GetRootHubPortStatus(2): %d, %d",
                     PortStatusOld.PortStatus,
                     PortStatusOld.PortChangeStatus
                     );

      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // disable port 0
      //
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // enable port 0
        //
        Status1 = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) &&
              (PortStatus.PortStatus & USB_PORT_STAT_ENABLE) &&
              (PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE)
              ) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortEnable",
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
                   gUsb2HcTestBasicAssertionGuid027,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortEnable",
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
                  L"Usb2HcSetRootHubPortFeatureSubTest1",
                  L"TDS 4.7.2.1 - SetRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  SetRootHubPortFeature(): EfiUsbPortSuspend  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureSubTest2",
                  L"TDS 4.7.2.2 - SetRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // restore port 0 from the suspend state
      //
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // put port 0 into suspend state
        //
        Status1 = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) &&
              (PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) &&
              (PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND)
              ) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortSuspend",
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
                   gUsb2HcTestBasicAssertionGuid028,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortSuspend",
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
                  L"Usb2HcSetRootHubPortFeatureSubTest2",
                  L"TDS 4.7.2.2 - SetRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  SetRootHubPortFeature(): EfiUsbPortReset  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureSubTest3",
                  L"TDS 4.7.2.3 - SetRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // clear the RESET signal for port 0
      //
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // reset port 0
        //
        Status1 = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        if (!EFI_ERROR (Status1)) {
          gtBS->Stall (1000 * 1000);
          //
          //          Status1 = UsbHc->ClearRootHubPortFeature(UsbHc, 0, EfiUsbPortReset);
          //
          if (!EFI_ERROR (Status1)) {
            Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"GetRootHubPortStatus(2): %d, %d",
                           PortStatus.PortStatus,
                           PortStatus.PortChangeStatus
                           );
            if (!EFI_ERROR (Status) &&
                (PortStatus.PortStatus & USB_PORT_STAT_RESET) &&
                (PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET)
                ) {
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
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortReset",
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
                   gUsb2HcTestBasicAssertionGuid029,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortReset",
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
                  L"Usb2HcSetRootHubPortFeatureSubTest3",
                  L"TDS 4.7.2.3 - SetRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  SetRootHubPortFeature(): EfiUsbPortPower  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureSubTest4",
                  L"TDS 4.7.2.4 - SetRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // shutdown the power from port 0
      //
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // power the port 0.
        //
        Status1 = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) && (PortStatus.PortStatus & USB_PORT_STAT_POWER)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortPower",
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
                   gUsb2HcTestBasicAssertionGuid030,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() with EfiUsbPortPower",
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
                  L"Usb2HcSetRootHubPortFeatureSubTest4",
                  L"TDS 4.7.2.4 - SetRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortEnable  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                            LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureSubTest1",
                  L"TDS 4.8.2.1 - ClearRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // Enable Port 0
      //
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // Disable Port 0
        //
        Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) &&
              ((PortStatus.PortStatus & USB_PORT_STAT_ENABLE) == 0) &&
              (PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE)
              ) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnable",
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
                   gUsb2HcTestBasicAssertionGuid031,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnable",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest1",
                  L"TDS 4.8.2.1 - ClearRootHubPortFeature: EfiUsbPortEnable\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortSuspend  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureSubTest2",
                  L"TDS 4.8.2.2 - ClearRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // Put Port 0 into suspend state
      //
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // restore port 0 from the previous suspend state
        //
        Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) &&
              ((PortStatus.PortStatus & USB_PORT_STAT_SUSPEND) == 0) &&
              (PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND)
              ) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspend",
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
                   gUsb2HcTestBasicAssertionGuid032,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspend",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest2",
                  L"TDS 4.8.2.2 - ClearRootHubPortFeature: EfiUsbPortSuspend\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortReset  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureSubTest3",
                  L"TDS 4.8.2.3 - ClearRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // reset port 0
      //
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // clear the RESET signal for port 0
        //
        Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) && ((PortStatus.PortStatus & USB_PORT_STAT_RESET) == 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_RESET) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortReset);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortReset",
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
                   gUsb2HcTestBasicAssertionGuid033,
                    L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortReset",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest3",
                  L"TDS 4.8.2.3 - ClearRootHubPortFeature: EfiUsbPortReset\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortPower  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest4",
                  L"TDS 4.8.2.4 - ClearRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller is %s %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // power the port 0
      //
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // shutdown the power from port 0
        //
        Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status1)) {
          Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"GetRootHubPortStatus(2): %d, %d",
                         PortStatus.PortStatus,
                         PortStatus.PortChangeStatus
                         );
          if (!EFI_ERROR (Status) && ((PortStatus.PortStatus & USB_PORT_STAT_POWER) == 0)) {
            Result = EFI_TEST_ASSERTION_PASSED;
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_POWER) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortPower);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();

    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortPower",
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
                   gUsb2HcTestBasicAssertionGuid034,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortPower",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest4",
                  L"TDS 4.8.2.4 - ClearRootHubPortFeature: EfiUsbPortPower\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortEnableChange  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureSubTest5",
                  L"TDS 4.8.2.5 - ClearRootHubPortFeature: EfiUsbPortEnableChange\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // disable port 0
      //
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // enable port 0
        //
        Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnableChange);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR (Status1)) {
            Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"GetRootHubPortStatus(2): %d, %d",
                           PortStatus.PortStatus,
                           PortStatus.PortChangeStatus
                           );
            if (!EFI_ERROR (Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_ENABLE) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_ENABLE) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortEnable);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnableChange",
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
                   gUsb2HcTestBasicAssertionGuid035,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortEnableChange",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest5",
                  L"TDS 4.8.2.5 - ClearRootHubPortFeature: EfiUsbPortEnableChange\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortSuspendChange  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  EFI_USB_PORT_STATUS PortStatusOld;
  BOOLEAN             UseGenericGuid;
  UINT16              *Str;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.8.2.6 - ClearRootHubPortFeature: EfiUsbPortSuspendChange\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();
      //
      // save the port 0 status
      //
      Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatusOld);
      if (EFI_ERROR (Status)) {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
        goto record;
      }
      //
      // put port 0 into suspend state
      //
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
      gtBS->Stall (1000 * 1000);
      if (!EFI_ERROR (Status)) {
        //
        // restore port 0 from suspend state
        //
        Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
        if (!EFI_ERROR (Status)) {
          Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspendChange);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR (Status1)) {
            Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, 0, &PortStatus);
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"GetRootHubPortStatus(2): %d, %d",
                           PortStatus.PortStatus,
                           PortStatus.PortChangeStatus
                           );
            if (!EFI_ERROR (Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_SUSPEND) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          Result          = EFI_TEST_ASSERTION_FAILED;
          UseGenericGuid  = TRUE;
        }
      } else {
        Result          = EFI_TEST_ASSERTION_FAILED;
        UseGenericGuid  = TRUE;
      }
      //
      // restore port 0
      //
      if (PortStatusOld.PortStatus & USB_PORT_STAT_SUSPEND) {
        Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      } else {
        Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, EfiUsbPortSuspend);
        gtBS->Stall (1000 * 1000);
      }

      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
record:
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspendChange",
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
                   gUsb2HcTestBasicAssertionGuid036,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortSuspendChange",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.8.2.6 - ClearRootHubPortFeature: EfiUsbPortSuspendChange\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest7 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortConnectChange  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;
  EFI_USB_PORT_STATUS PortStatus;
  BOOLEAN             UseGenericGuid;
  //
  // EFI_INPUT_KEY           Key;
  //
  UINT16              *Str;
  UINT8               port;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureSubTest7",
                  L"TDS 4.9.2.1 - ClearRootHubPortFeature: EfiUsbPortConnectChange\n"
                  );
  }

  Str             = SctDevicePathStrFromProtocol (Usb2Hc, &gBlackBoxEfiUsb2HcProtocolGuid);
  UseGenericGuid  = FALSE;
  Status          = EFI_SUCCESS;
  Status1         = EFI_SUCCESS;
  Result          = EFI_TEST_ASSERTION_FAILED;
  Status          = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The PortNumber for this Host Controller %s is %d",
                   Str,
                   PortNumber
                   );
    if (PortNumber > 0) {
      //
      // mask timer interrupt
      //
      MaskTimerInterrupt ();

      //
      // SctPrint(L"Make sure that there is no device on each port\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Make sure that there is no device on each of Host Conteoller %s\n",
                     Str
                     );
      //
      // SctPrint(L"Plug a device into a port\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Plug a device into a port of Host Controller %s\n", 
                     Str
                     );
      //
      // SctPrint(L"Pull out the device from the port\n");
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Pull out the device from the port of Host Controller %s\n",
                     Str
                     );
      //
      // SctPrint(L"Press any key to continue\n");
      //
      StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Waiting for 20s\n");
      //
      // SctWaitForSingleEvent (gtST->ConIn->WaitForKey, 0);
      //
      StallForChangeDevice (StandardLib, 20);
      for (port = 0; port < PortNumber; port++) {
        Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Port: %d, GetRootHubPortStatus(1): %d, %d",
                       port,
                       PortStatus.PortStatus,
                       PortStatus.PortChangeStatus
                       );
        if (!EFI_ERROR (Status) && (PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION)) {
          Status1 = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, port, EfiUsbPortConnectChange);
          gtBS->Stall (1000 * 1000);
          if (!EFI_ERROR (Status1)) {
            Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, port, &PortStatus);
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"Port: %d, GetRootHubPortStatus(2): %d, %d",
                           port,
                           PortStatus.PortStatus,
                           PortStatus.PortChangeStatus
                           );
            if (!EFI_ERROR (Status) && ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_CONNECTION) == 0)) {
              Result = EFI_TEST_ASSERTION_PASSED;
            } else {
              Result = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            Result = EFI_TEST_ASSERTION_FAILED;
          }

          goto record;
        }
      }

      Result          = EFI_TEST_ASSERTION_FAILED;
      UseGenericGuid  = TRUE;
record:
      UnmaskTimerInterrupt ();
    } else {
      goto done;
    }
    //
    // end portnumber > 0
    //
  } else {
    //
    // RecordAssertion for Genenric Guid
    //
    Result          = EFI_TEST_ASSERTION_FAILED;
    UseGenericGuid  = TRUE;
  }
  //
  // endif GetRootHubPortNumber
  //
  if (UseGenericGuid) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortConnectChange",
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
                   gUsb2HcTestBasicAssertionGuid037,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - ClearRootHubPortFeature() with EfiUsbPortConnectChange",
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
                  L"Usb2HcClearRootHubPortFeatureSubTest6",
                  L"TDS 4.9.2.1 - ClearRootHubPortFeature: EfiUsbPortConnectChange\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest8 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortOverCurrentChange  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  //
  // TBD
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureSubTest9 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  ClearRootHubPortFeature(): EfiUsbPortResetChange  
  
Arguments:

  Usb2Hc          - A pointer to EFI_USB2_HC_PROTOCOL instance.
  StandardLib     - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib      - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS     - Successfully.
  Other value     - Something failed.

--*/
{
  //
  // TBD
  //
  return EFI_SUCCESS;
}
