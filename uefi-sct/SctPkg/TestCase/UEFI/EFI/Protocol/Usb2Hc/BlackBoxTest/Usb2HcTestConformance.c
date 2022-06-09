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
  Usb2HcTestConformance.c

Abstract:
  Source file for USB2 host controller conformance testing.

--*/
#include "SctLib.h"
#include "Usb2HcTest.h"

//
// Prototypes
//
EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcResetConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetStateConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetStateConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  );

EFI_STATUS
EFIAPI
Usb2HcInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  );

EFI_STATUS
EFIAPI
Usb2HcIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  );

//
// Functions
//


EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetCapability() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.1.2.1
  //
  //
  // Call GetCapability() with MaxSpeed being NULL
  //
  Status = Usb2HcGetCapabilityConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);
  //
  // Call GetCapability() with PortNumber being NULL
  //
  Status = Usb2HcGetCapabilityConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);
  //
  // Call GetCapability() with Is64BitCapable being NULL
  //
  Status = Usb2HcGetCapabilityConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Reset() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.2.2.1
  //
  //
  // Call Reset() with Invalid Parameters
  //
  Status = Usb2HcResetConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetState() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.3.2.1
  //
  //
  // Call GetState() with Invalid Parameters
  //
  Status = Usb2HcGetStateConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->Setstate() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.4.2.1
  //
  //
  // Call SetState() with Invalid Parameters
  //
  Status = Usb2HcSetStateConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ControlTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.5.2.1
  //
  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferDirection is invalid.
  //
  Status = Usb2HcControlTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferDirection, Data, and DataLength do not match one of the three
  // control transfer types described above.
  //
  Status = Usb2HcControlTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // Request pointer is NULL.
  //
  Status = Usb2HcControlTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // MaximumPacketLength is not valid.
  // If IsSlowDevice is TRUE, then MaximumPacketLength must be 8.
  // If IsSlowDevice is FALSE, then MaximumPacketLength must be 8, 16, 32,
  // or 64.
  //
  Status = Usb2HcControlTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferResult pointer is NULL.
  //
  Status = Usb2HcControlTransferConformanceSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ControlTransfer() Conformance manual Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.6.2.1
  //
  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // Translator is NULL
  //
  Status = Usb2HcControlTransferConformanceSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->BulkTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.7.2.1
  //
  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = Usb2HcBulkTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = Usb2HcBulkTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // MaximumPacketLength is not valid.
  // The legal value of this parameter is 8, 16, 32, or 64.
  //
  Status = Usb2HcBulkTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // DataToggle points to a value other than 0 and 1.
  //
  Status = Usb2HcBulkTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = Usb2HcBulkTransferConformanceSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->AsyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.8.2.1
  //
  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // Data transfer direction indicated by EndPointAddress is other than EfiUsbDataIn.
  //
  //Status = Usb2HcAsyncInterruptTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and DataLength is 0.
  //
  Status = Usb2HcAsyncInterruptTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and DataToggle points to a value other than 0 and 1.
  //
  Status = Usb2HcAsyncInterruptTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255.
  //
  Status = Usb2HcAsyncInterruptTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.9.2.1
  //
  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // Data transfer direction indicated by EndPointAddress is not EfiUsbDataIn.
  //
  //Status = Usb2HcSyncInterruptTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = Usb2HcSyncInterruptTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = Usb2HcSyncInterruptTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  //
  // MaximumPacketLength is invalid.
  //
  Status = Usb2HcSyncInterruptTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // DataToggle points to a value other than 0 and 1.
  //
  Status = Usb2HcSyncInterruptTransferConformanceSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = Usb2HcSyncInterruptTransferConformanceSubTest6 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->AsyncIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.14.2.1
  //
  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = Usb2HcAsyncIsochronousTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = Usb2HcAsyncIsochronousTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // MaximumPacketLength is larger than 1023.
  //
  Status = Usb2HcAsyncIsochronousTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // DeviceSpeed is not one of the supported values.
  //
  Status = Usb2HcAsyncIsochronousTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->IsochronousTransfer() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.13.2.1
  //
  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = Usb2HcIsochronousTransferConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = Usb2HcIsochronousTransferConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // MaximumPacketLength is larger than 1023.
  //
  Status = Usb2HcIsochronousTransferConformanceSubTest3 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = Usb2HcIsochronousTransferConformanceSubTest4 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // DeviceSpeed is not one of the supported values.
  //
  Status = Usb2HcIsochronousTransferConformanceSubTest5 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->GetRootHubPortStatus() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.10.2.1
  //
  //
  // 5.10.2.1  Call GetRootHubPortStatus () with Invalid Parameters
  //
  Status = Usb2HcGetRootHubPortStatusConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->SetRootHubPortFeature() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // Get the Usb Hc protocol interface
  //
  Usb2Hc = (EFI_USB2_HC_PROTOCOL *) ClientInterface;

  //
  // TDS 5.11.2.1
  //
  //
  // Call SetRootHubPortFeature() with Invalid PortNumber
  //
  Status = Usb2HcSetRootHubPortFeatureConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call SetRootHubPortFeature() with Invalid PortFeature
  //
  Status = Usb2HcSetRootHubPortFeatureConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for Usb2Hc->ClearRootHubPortFeature() Conformance Auto Test.

Arguments:

  This                  - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface       - A pointer to the interface to be tested.
  TestLevel             - Test "thoroughness" control.
  SupportHandle         - A handle containing support protocols.

Returns:

  EFI_SUCCESS           - Successfully.
  Other value           - Something failed.

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
  // TDS 5.12.2.1
  //
  //
  // Call ClearRootHubPortFeature() with Invalid PortNumber
  //
  Status = Usb2HcClearRootHubPortFeatureConformanceSubTest1 (Usb2Hc, StandardLib, LoggingLib);

  //
  // Call ClearRootHubPortFeature() with Invalid PortFeature
  //
  Status = Usb2HcClearRootHubPortFeatureConformanceSubTest2 (Usb2Hc, StandardLib, LoggingLib);

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
Usb2HcGetCapabilityConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->GetCapability() with MaxSpeed being NULL.

Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with MaxSpeed being NULL\n"
                  );
  }
  //
  // MaxSpeed is NULL
  //
  Status = Usb2Hc->GetCapability (Usb2Hc, NULL, &PortNumber, &Is64BitCapable);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid001,
                 L"USB2_HC_PROCOTOL.GetCapability - GetCapability() returns EFI_INVALID_PARAMETER with MaxSpeed being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with MaxSpeed being NULL\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->GetCapability() with PortNumber being NULL.

Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  UINT8               MaxSpeed;
  UINT8               Is64BitCapable;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with PortNumber being NULL\n"
                  );
  }
  //
  // PortNumber is NULL
  //
  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, NULL, &Is64BitCapable);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid002,
                 L"USB2_HC_PROCOTOL.GetCapability - GetCapability() returns EFI_INVALID_PARAMETER with PortNumber being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with PortNumber being NULL\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetCapabilityConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->GetCapability() with Is64BitCapable being NULL.

Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with Is64BitCapable being NULL\n"
                  );
  }
  //
  // Is64BitCapable is NULL
  //
  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid003,
                 L"USB2_HC_PROCOTOL.GetCapability - GetCapability() returns EFI_INVALID_PARAMETER with Is64BitCapable being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetCapabilityConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call Usb2Hc->GetCapability() with Is64BitCapable being NULL\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcResetConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->Reset() with Invalid Parameters.

Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcResetConformanceSubTest1",
                  L"TDS 5.2.2.1 - Call Usb2Hc->Reset() with Invalid Parameters\n"
                  );
  }
  //
  // the parameter Attributes is not EFI_USB_HC_RESET_GLOBAL, EFI_USB_HC_RESET_HOST_CONTROLLER,
  // EFI_USB_HC_RESET_GLOBAL_DEBUG or EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG
  //
  Status = Usb2Hc->Reset (Usb2Hc, 0x0000);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid004,
                 L"Reset - Call Usb2Hc->Reset() with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcResetConformanceSubTest1",
                  L"TDS 5.2.2.1 - Call UsbHc->Reset() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcGetStateConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call UsbHc->GetState() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetStateConformanceSubTest1",
                  L"TDS 5.3.2.1 - Call Usb2Hc->GetState() with Invalid Parameters\n"
                  );
  }
  //
  // the parameter State is NULL
  //
  Status = Usb2Hc->GetState (Usb2Hc, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid005,
                 L"USB2_HC_Protocol.GetState- GetState()returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetStateConformanceSubTest1",
                  L"TDS 5.3.2.1 - Call Usb2Hc->GetState() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcSetStateConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SetState() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetStateConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call Usb2Hc->SetState() with Invalid Parameters\n"
                  );
  }
  //
  // the parameter State is invalid
  //
  Status = Usb2Hc->SetState (Usb2Hc, -1);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid006,
                 L"USB2_HC_PROTOCOL.SetState - SetState() returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // the parameter State is invalid
  //
  Status = Usb2Hc->SetState (Usb2Hc, EfiUsbHcStateMaximum);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid006,
                 L"USB2_HC_PROTOCOL.SetState - SetState() returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetStateConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call Usb2Hc->SetState() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  //
  // Parameter TransferDirection is invalid (not EfiUsbNoData,EfiUsbDataOut, EfiUsbDataIn).
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     -1, // invalid
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid007,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid TransferDirection",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     0x7FFFFFFF, // invalid
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid007,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid TransferDirection",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  EFI_USB_DEVICE_REQUEST  Request;
  UINT32                  Data[255];
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest2",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  //
  //  Paramerer TransferDirection is EfiUsbDataIn ,parameter DataLength is 128 but parameter Data is NULL
  //
  DataLength = 128;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     EfiUsbDataIn,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid008,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data and DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Paramerer TransferDirection is EfiUsbDataOut, parameter DataLength is 0 and parameter Data is NULL
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     EfiUsbDataOut,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid008,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data and DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Paramerer TransferDirection is EfiUsbNoData, parameter DataLength is not NULL and parameter Data is not NULL
  //
  DataLength = 128;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     EfiUsbNoData,
                     Data,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid008,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data and DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest2",
                  L"TDS 5.5.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest3",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Parameter Request is NULL
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     NULL, // Request
                     EfiUsbNoData,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid009,
                 L"USB2_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with Request being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest3",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest4",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  //
  // Parameter MaximumPacketLength is invalid
  //
  // 1. DeviceSpeed is EFI_USB_SPEED_LOW, MaximumPacketLength is not 8
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     2,
                     &Request,
                     EfiUsbNoData,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid010,
                 L"USB2_HC_PROCOTOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with DeviceSpeed is EFI_USB_SPEED_LOW, MaximumPacketLength is not 8",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. DeviceSpeed is EFI_USB_SPEED_FULL, MaximumPacketLength is 128 (not 8/16/32/64)
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_FULL,
                     128,
                     &Request,
                     EfiUsbNoData,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid011,
                 L"USB2_HC_PROCOTOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with DeviceSpeed is EFI_USB_SPEED_FULL, MaximumPacketLength is 128 (not 8/16/32/64)",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3. Devicespeed is EFI_USB_SPEED_HIGH, MaximumPacketLength is 128 (not 8/16/32/64)
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_HIGH,
                     128,
                     &Request,
                     EfiUsbNoData,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid012,
                 L"USB2_HC_PROCOTOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with DeviceSpeed is EFI_USB_SPEED_HIGH, MaximumPacketLength is 128 (not 8/16/32/64)",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Usb2Hc->MajorRevision >= 0x3) {
    //
    // 4. DeviceSpeed is EFI_USB_SPEED_SUPER, MaximumPacketLength is 256 (not 512)
    //
    DataLength = 0;
    Status = Usb2Hc->ControlTransfer (
                       Usb2Hc,
                       2,
                       EFI_USB_SPEED_SUPER,
                       256,
                       &Request,
                       EfiUsbNoData,
                       NULL,
                       &DataLength,
                       1000,
                       NULL,
                       &TransferResult
                       );

    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid013,
                   L"USB2_HC_PROCOTOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with DeviceSpeed is EFI_USB_SPEED_SUPER, MaximumPacketLength is 256 (not 512)",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest4",
                  L"TDS 5.5.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest5",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  //
  // Parameter TransferResult is NULL
  //
  DataLength = 0;
  Status = Usb2Hc->ControlTransfer (
                     Usb2Hc,
                     2,
                     EFI_USB_SPEED_LOW,
                     8,
                     &Request,
                     EfiUsbNoData,
                     NULL,
                     &DataLength,
                     1000,
                     NULL,
                     NULL  // TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid014,
                 L"USB2_HC_PROCOTOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcControlTransferConformanceSubTest5",
                  L"TDS 5.5.2.1 - Call Usb2Hc->ControlTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcControlTransferConformanceSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ControlTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  //
  // TDB
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              TransferResult;
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data is NULL
  //
  DataLength  = 128;
  DataToggle  = 0;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_FULL,
                     64,
                     0,
                     NULL, // Data
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid015,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest2",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataLength is 0
  //
  DataLength  = 0;
  DataToggle  = 0;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_FULL,
                     64,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid016,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest2",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest3",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DeviceSpeed is EFI_USB_SPEED_LOW
  //
  DataLength  = 128;
  DataToggle  = 0;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_LOW,
                     64,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid017,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with DeviceSpeed is EFI_USB_SPEED_LOW",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest3",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest4",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // MaximumPacketLength is 65 when DeviceSpeed is EFI_USB_SPEED_FULL
  //
  DataLength  = 128;
  DataToggle  = 0;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_FULL,
                     65,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid018,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is 65 when DeviceSpeed is EFI_USB_SPEED_FULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // MaximumPacketLength is 513 when DeviceSpeed is EFI_USB_SPEED_HIGH
  //
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_HIGH,
                     513,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid018,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is 513 when DeviceSpeed is EFI_USB_SPEED_HIGH",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Usb2Hc->MajorRevision >= 0x3) {
    //
    // MaximumPacketLength is 1025 when DeviceSpeed is EFI_USB_SPEED_SUPER
    //
    Status = Usb2Hc->BulkTransfer (
                       Usb2Hc,
                       2,
                       1,
                       EFI_USB_SPEED_SUPER,
                       1025,
                       1,
                       (void **) &Data,
                       &DataLength,
                       &DataToggle,
                       1000,
                       NULL,
                       &TransferResult
                       );

    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid018,
                   L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is 1025 when DeviceSpeed is EFI_USB_SPEED_SUPER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }
  
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest4",
                  L"TDS 5.7.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest5",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataToggle points to a value other than 0 and 1
  //
  DataLength  = 128;
  DataToggle  = 2;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_HIGH,
                     64,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid019,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with DataToggle pointing to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest5",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcBulkTransferConformanceSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->BulkTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT32              Data[255];
  UINTN               DataLength;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest6",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // TransferResult is NULL
  //
  DataLength  = 128;
  DataToggle  = 0;
  Status = Usb2Hc->BulkTransfer (
                     Usb2Hc,
                     2,
                     1,
                     EFI_USB_SPEED_HIGH,
                     64,
                     1,
                     (void **) &Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     NULL  // TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid020,
                 L"USB2_HC_PROCOTOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcBulkTransferConformanceSubTest6",
                  L"TDS 5.7.2.1 - Call Usb2Hc->BulkTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data transfer direction indicated by EndPointAddress is other than EfiUsbDataIn
  //
  DataToggle = 0;
  Status = Usb2Hc->AsyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     1,  // invalid
                     EFI_USB_SPEED_LOW,
                     8,
                     TRUE,
                     &DataToggle,
                     100,
                     128,
                     NULL,
                     Usb2HcInterruptCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid021,
                 L"USB2_HC_PROCOTOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with invalid EndPointAddress",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.8.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // IsNewTransfer is TRUE and DataLength is 0
  //
  DataToggle = 0;
  Status = Usb2Hc->AsyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     TRUE,
                     &DataToggle,
                     100,
                     0,  // invalid
                     NULL,
                     Usb2HcInterruptCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid022,
                 L"USB2_HC_PROCOTOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.8.2.1 - Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.8.2.1 - Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // IsNewTransfer is TRUE and DataToggle points to a value other than 0 and 1
  //
  DataToggle = 2;
  Status = Usb2Hc->AsyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     TRUE,
                     &DataToggle,
                     100,
                     128,
                     NULL,
                     Usb2HcInterruptCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid023,
                 L"USB2_HC_PROCOTOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataToggle points to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.8.2.1 - Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.8.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255
  //
  DataToggle = 0;
  Status = Usb2Hc->AsyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     TRUE,
                     &DataToggle,
                     0,  // invalid
                     128,
                     NULL,
                     Usb2HcInterruptCallBack,
                     NULL
                     );
                  
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {        
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid024,
                 L"USB2_HC_PROCOTOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is not in the range 1..255",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255
  //
  DataToggle = 0;
  Status = Usb2Hc->AsyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     TRUE,
                     &DataToggle,
                     256,  // invalid
                     128,
                     NULL,
                     Usb2HcInterruptCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid024,
                 L"USB2_HC_PROCOTOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is not in the range 1..255",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.8.2.1 - Call Usb2Hc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data transfer direction indicated by EndPointAddress is not EfiUsbDataIn
  //
  DataToggle  = 0;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     1,  // invalid
                     EFI_USB_SPEED_LOW,
                     8,
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid025,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with invalid EndPointAddress",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.8.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data is NULL
  //
  DataToggle  = 0;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     NULL, // Data
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid026,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataLength is 0
  //
  DataToggle  = 0;
  DataLength  = 0;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid027,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength being 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.9.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // MaxiumPacketLenth is not valid.
  // The legal value of this parameter should be 3072 or less for the high-speed device,
  // 64 or less for the full-speed device,
  // for the slow device, it is limited to 8 or less.
  //
  DataToggle  = 0;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     9,  // invalid
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid028,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with MaxiumPacketLenth is not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  DataToggle  = 0;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     65, // invalid
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid028,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with MaxiumPacketLenth is not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  DataToggle  = 0;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_HIGH,
                     3073, // invalid
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid028,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with MaxiumPacketLenth is not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              Data[255];
  UINT32              TransferResult;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest5",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataToggle points to a value other than 0 and 1
  //
  DataToggle  = 2;
  DataLength  = 128;
  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid029,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataToggle points to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest5",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSyncInterruptTransferConformanceSubTest6 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/ 
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               DataToggle;
  UINT32              Data[255];
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest6",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // TransferResult is NULL.
  //
  DataToggle  = 0;
  DataLength  = 128;

  Status = Usb2Hc->SyncInterruptTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     (VOID *) Data,
                     &DataLength,
                     &DataToggle,
                     1000,
                     NULL,
                     NULL  // TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid030,
                 L"USB2_HC_PROCOTOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSyncInterruptTransferConformanceSubTest6",
                  L"TDS 5.9.2.1 - Call Usb2Hc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data is NULL
  //
  DataLength = 128;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     8,
                     0,
                     NULL, // Data
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid031,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest2",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataLength is 0
  //
  DataLength = 0;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     8,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid032,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest2",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest3",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // MaximumPacketLength is larger than 1023 when it is the full-speed device
  //
  DataLength = 128;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     1024,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid033,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1023",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // MaximumPacketLength is larger than 1024 when it is the high-speed device
  //
  DataLength = 128;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_HIGH,
                     1025,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid033,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1024",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // MaximumPacketLength is larger than 1024 when it is the super-device
  //
  DataLength = 128;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_SUPER,
                     1025,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid033,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1024",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest3",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcAsyncIsochronousTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest4",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DeviceSpeed is not one of the supported values
  //
  DataLength = 128;
  Status = Usb2Hc->AsyncIsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     Usb2HcIsochronousCallBack,
                     NULL
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid044,
                 L"USB2_HC_PROCOTOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER when DeviceSpeed is not one of the supported values",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcAsyncIsochronousTransferConformanceSubTest4",
                  L"TDS 5.14.2.1 - Call Usb2Hc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->IsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest1",
                  L"TDS 5.132.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Data is NULL
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     8,
                     0,
                     NULL, // Data
                     DataLength,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid034,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest1",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->IsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];
  UINT32              TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest2",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DataLength is 0
  //
  DataLength = 0;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     8,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid035,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest2",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest3 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->IsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];
  UINT32              TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest3",
                  L"TDS 5.13.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // MaximumPacketLength is larger than 1023 when it is the full-speed device
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     1024,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid036,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1023",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // MaximumPacketLength is larger than 1024 when it is the high-speed device
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_HIGH,
                     1025,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid036,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1024",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // MaximumPacketLength is larger than 1024 when it is the super-speed device
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_SUPER,
                     1025,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     &TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid036,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is larger than 1024",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest3",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest4 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->IsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest4",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // TransferResult is NULL
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_FULL,
                     8,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     NULL  // TransferResult
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid037,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest4",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcIsochronousTransferConformanceSubTest5 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->IsochronousTransfer() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINTN               DataLength;
  UINT32              Data[255];
  UINT32              TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest5",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // DeviceSpeed is EFI_USB_SPEED_LOW
  //
  DataLength = 128;
  Status = Usb2Hc->IsochronousTransfer (
                     Usb2Hc,
                     2,
                     0x81,
                     EFI_USB_SPEED_LOW,
                     8,
                     1,
                     (void **) &Data,
                     DataLength,
                     NULL,
                     &TransferResult  
                     );

  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }
  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsb2HcTestConformanceAssertionGuid043,
                 L"USB2_HC_PROCOTOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER When DeviceSpeed is not one of the supported values",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcIsochronousTransferConformanceSubTest5",
                  L"TDS 5.13.2.1 - Call Usb2Hc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcGetRootHubPortStatusConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->GetRootHubPortStatus() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;
  EFI_USB_PORT_STATUS PortStatus;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call Usb2Hc->GetRootHubPortStatus() with Invalid Parameters\n"
                  );
  }
  //
  // PortNumber is greater than or equal to the number of ports returned by GetCapability
  //
  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    Status = Usb2Hc->GetRootHubPortStatus (Usb2Hc, PortNumber, &PortStatus);
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid038,
                   L"USB2_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() returns EFI_INVALID_PARAMETER with Invalid PortNumber",
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"USB_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test GetRootHubPortStatus",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcGetRootHubPortStatusConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call Usb2Hc->GetRootHubPortStatus() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SetRootHubPortStatus() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.11.2.1 - Call Usb2Hc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    //
    // 1. PortNumber is greater than or equal to the number of ports returned by GetCapability()
    //
    Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, PortNumber, EfiUsbPortEnable);
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid039,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortNumber ",
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test SetRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.11.2.1 - Call Usb2Hc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcSetRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->SetRootHubPortStatus() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINT8                 MaxSpeed;
  UINT8                 PortNumber;
  UINT8                 Is64BitCapable;
  UINT8                 Index;
  EFI_USB_PORT_FEATURE  InvalidUsbPortFeature[7] = {
    -1,
    EfiUsbPortConnectChange,
    EfiUsbPortEnableChange,
    EfiUsbPortSuspendChange,
    EfiUsbPortOverCurrentChange,
    EfiUsbPortResetChange,
    0x7FFFFFFF
  };

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.11.2.1 - Call Usb2Hc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    //
    // 2. PortFeature is not EfiUsbPortEnable, EfiUsbPortSuspend, EfiUsbPortReset nor EfiUsbPortPower.
    //
    Result = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0; Index < 7; Index++) {
      Status = Usb2Hc->SetRootHubPortFeature (Usb2Hc, 0, InvalidUsbPortFeature[Index]);
      if (Status != EFI_INVALID_PARAMETER) {
        Result = EFI_TEST_ASSERTION_FAILED;
      }
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid040,
                   L"USB2_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortFeature",
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test SetRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcSetRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.11.2.1 - Call Usb2Hc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;
  UINT8               MaxSpeed;
  UINT8               PortNumber;
  UINT8               Is64BitCapable;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.12.2.1 - Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    //
    // 1. PortNumber is greater than or equal to the number of ports returned by GetCapability()
    //
    Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, PortNumber, EfiUsbPortEnable);
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid041,
                   L"USB2_HC_PROTOCOL.ClearRootHubPortFeature - ClearRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortNumber is greater than or equal to the number of ports",
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test ClearRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.12.2.1 - Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}
 
EFI_STATUS
EFIAPI
Usb2HcClearRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB2_HC_PROTOCOL                  *Usb2Hc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib
  )
/*++

Routine Description:

  Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters.
  
Arguments:

  Usb2Hc           - A pointer to EFI_USB2_HC_PROTOCOL instance. 
  
  StandardLib      - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  
  LoggingLib       - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - Successfully.
  Other value      - Something failed.

--*/
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINT8                 MaxSpeed;
  UINT8                 PortNumber;
  UINT8                 Is64BitCapable;
  UINT8                 Index;
  EFI_USB_PORT_FEATURE  InvalidUsbPortFeature[2] = {
    -1,
    0x7FFFFFFF
  };

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.12.2.1 - Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = Usb2Hc->GetCapability (Usb2Hc, &MaxSpeed, &PortNumber, &Is64BitCapable);
  if (!EFI_ERROR (Status)) {
    //
    // 2. PortFeature is not EfiUsbPortEnable, EfiUsbPortSuspend, EfiUsbPortPower, EfiUsbPortConnectChange, EfiUsbPortResetChange, EfiUsbPortEnableChange, EfiUsbPortSuspendChange, nor EfiUsbPortOverCurrentChange.
    //
    Result = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0; Index < 2; Index++) {
      Status = Usb2Hc->ClearRootHubPortFeature (Usb2Hc, 0, InvalidUsbPortFeature[Index]);
      if (Status != EFI_INVALID_PARAMETER) {
        Result = EFI_TEST_ASSERTION_FAILED;
      }
    }
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsb2HcTestConformanceAssertionGuid042,
                   L"USB2_HC_PROTOCOL.ClearRootHubPortFeature - ClearRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortFeature",
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
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"USB2_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test ClearRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"Usb2HcClearRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.12.2.1 - Call Usb2Hc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  )
/*++

Routine Description:

  USB2.0 host controller Interrupt Transfer callback function

Arguments:

  Data             - Data
  DataLength       - Data length
  Context          - Context
  Status           - Status

Returns:

  EFI_SUCCESS      - Successful.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Usb2HcIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  )
/*++

Routine Description:

  USB2.0 host controller Isochronous Transfer callback function

Arguments:

  Data           - Data
  DataLength     - Data Length
  Context        - Context
  Status         - Status

Returns:

  EFI_SUCCESS    - Successful.

--*/
{
  return EFI_SUCCESS;
}
