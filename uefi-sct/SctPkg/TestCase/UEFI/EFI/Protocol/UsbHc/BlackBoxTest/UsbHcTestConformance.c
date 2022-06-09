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
  UsbHcTestConformance.c

Abstract:
  Source file for Usb Hc conformance testing.

--*/

#include "SctLib.h"
#include "UsbHcTest.h"

//
// Prototypes (internal)
//

EFI_STATUS
EFIAPI
UsbHcResetConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetStateConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetStateConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbHcInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
);

EFI_STATUS
EFIAPI
UsbHcIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
);

//
// Functions
//

/**
 *  TDS 5.1 - Entry point for UsbHc->Reset() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetConformanceAutoTest (
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
  //TDS 5.1.2.1
  //

  //
  // Call Reset() with Invalid Parameters
  //
  Status = UsbHcResetConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.2 - Entry point for UsbHc->GetState() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateConformanceAutoTest (
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
  //TDS 5.2.2.1
  //

  //
  // Call GetState() with Invalid Parameters
  //
  Status = UsbHcGetStateConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.3 - Entry point for UsbHc->SetState() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateConformanceAutoTest (
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
  //TDS 5.3.2.1
  //

  //
  // Call SetState() with Invalid Parameters
  //
  Status = UsbHcSetStateConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4 - Entry point for UsbHc->ControlTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceAutoTest (
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
  //TDS 5.4.2.1
  //

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferDirection is invalid.
  //
  Status = UsbHcControlTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferDirection, Data, and DataLength do not match one of the three
  // control transfer types described above.
  //
  Status = UsbHcControlTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // Request pointer is NULL.
  //
  Status = UsbHcControlTransferConformanceSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // MaximumPacketLength is not valid.
  // If IsSlowDevice is TRUE, then MaximumPacketLength must be 8.
  // If IsSlowDevice is FALSE, then MaximumPacketLength must be 8, 16, 32,
  // or 64.
  //
  Status = UsbHcControlTransferConformanceSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Call ControlTransfer () with Invalid Parameters
  //
  // TransferResult pointer is NULL.
  //
  Status = UsbHcControlTransferConformanceSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5 - Entry point for UsbHc->BulkTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceAutoTest (
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
  //TDS 5.5.2.1
  //

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = UsbHcBulkTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = UsbHcBulkTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // MaximumPacketLength is not valid.
  // The legal value of this parameter is 8, 16, 32, or 64.
  //
  Status = UsbHcBulkTransferConformanceSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // DataToggle points to a value other than 0 and 1.
  //
  Status = UsbHcBulkTransferConformanceSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Call BulkTransfer () with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = UsbHcBulkTransferConformanceSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6 - Entry point for UsbHc->AsyncInterruptTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceAutoTest (
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
  //TDS 5.6.2.1
  //

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // Data transfer direction indicated by EndPointAddress is other than EfiUsbDataIn.
  //
  Status = UsbHcAsyncInterruptTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and DataLength is 0.
  //
  Status = UsbHcAsyncInterruptTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and DataToggle points to a value other than 0 and 1.
  //
  Status = UsbHcAsyncInterruptTransferConformanceSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Call AsyncInterruptTransfer() with Invalid Parameters
  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255.
  //
  Status = UsbHcAsyncInterruptTransferConformanceSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7 - Entry point for UsbHc->SyncInterruptTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceAutoTest (
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
  //TDS 5.7.2.1
  //

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // Data transfer direction indicated by EndPointAddress is not EfiUsbDataIn.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer () with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // Spec updated:
  // MaximumPacketLength is not valid.
  // The legal value of this parameter should be 64 or less for the full-speed device,
  // for the slow device, it is limited to 8.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // DataToggle points to a value other than 0 and 1.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest5 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SyncInterruptTransfer() with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = UsbHcSyncInterruptTransferConformanceSubTest6 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.13 - Entry point for UsbHc->AsyncIsochronousTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceAutoTest (
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
  //TDS 5.13.2.1
  //

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = UsbHcAsyncIsochronousTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = UsbHcAsyncIsochronousTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call AsyncIsochronousTransfer() with Invalid Parameters
  //
  // MaximumPacketLength is larger than 1023.
  // (This is a bug in spec, UINT8 can not greater than 1023)
  //
  // Status = UsbHcAsyncIsochronousTransferConformanceSubTest3(UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12 - Entry point for UsbHc->IsochronousTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceAutoTest (
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
  //TDS 5.12.2.1
  //

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // Data is NULL.
  //
  Status = UsbHcIsochronousTransferConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // DataLength is 0.
  //
  Status = UsbHcIsochronousTransferConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // MaximumPacketLength is larger than 1023.
  // (This is a bug in spec, UINT8 can not greater than 1023)
  //
  // Status = UsbHcIsochronousTransferConformanceSubTest3 (UsbHc, StandardLib, LoggingLib);

  //
  // Call IsochronousTransfer() with Invalid Parameters
  //
  // TransferResult is NULL.
  //
  Status = UsbHcIsochronousTransferConformanceSubTest4 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.8 - Entry point for UsbHc->GetRootHubPortNumber() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberConformanceAutoTest (
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
  //TDS 5.8.2.1
  //

  //
  // Call GetRootHubPortNumber() with Invalid Parameters
  //
  Status = UsbHcGetRootHubPortNumberConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.9 - Entry point for UsbHc->GetRootHubPortStatus() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusConformanceAutoTest (
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
  //TDS 5.9.2.1
  //

  //
  // 5.9.2.1  Call GetRootHubPortStatus () with Invalid Parameters
  //
  Status = UsbHcGetRootHubPortStatusConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.10 - Entry point for UsbHc->SetRootHubPortFeature() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceAutoTest (
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
  //TDS 5.10.2.1
  //

  //
  // Call SetRootHubPortFeature() with Invalid PortNumber
  //
  Status = UsbHcSetRootHubPortFeatureConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call SetRootHubPortFeature() with Invalid PortFeature
  //
  Status = UsbHcSetRootHubPortFeatureConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.11 - Entry point for UsbHc->ClearRootHubPortFeature() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceAutoTest (
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
  //TDS 5.11.2.1
  //

  //
  // Call ClearRootHubPortFeature() with Invalid PortNumber
  //
  Status = UsbHcClearRootHubPortFeatureConformanceSubTest1 (UsbHc, StandardLib, LoggingLib);

  //
  // Call ClearRootHubPortFeature() with Invalid PortFeature
  //
  Status = UsbHcClearRootHubPortFeatureConformanceSubTest2 (UsbHc, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

// Sub functions

/**
 *  TDS 5.1.2.1 - Call UsbHc->Reset() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcResetConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcResetConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call UsbHc->Reset() with Invalid Parameters\n"
                  );
  }

  //
  // the parameter Attributes is neither EFI_USB_HC_RESET_GLOBAL nor EFI_USB_HC_RESET_HOST_CONTROLLER
  //
  Status = UsbHc->Reset (UsbHc, 0x0000);

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
                 gUsbHcTestConformanceAssertionGuid001,
                 L"Reset - Call UsbHc->Reset() with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcResetConformanceSubTest1",
                  L"TDS 5.1.2.1 - Call UsbHc->Reset() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.2.2.1 - Call UsbHc->GetState() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetStateConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetStateConformanceSubTest1",
                  L"TDS 5.2.2.1 - Call UsbHc->GetState() with Invalid Parameters\n"
                  );
  }

  //
  // the parameter State is NULL
  //
  Status = UsbHc->GetState (UsbHc, NULL);

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
                 gUsbHcTestConformanceAssertionGuid002,
                 L"USB_HC_Protocol.GetState- GetState()returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetStateConformanceSubTest1",
                  L"TDS 5.2.2.1 - Call UsbHc->GetState() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.3.2.1 - Call UsbHc->SetState() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetStateConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetStateConformanceSubTest1",
                  L"TDS 5.3.2.1 - Call UsbHc->SetState() with Invalid Parameters\n"
                  );
  }

  //
  // the parameter State is invalid
  //
  Status = UsbHc->SetState (UsbHc, -1);

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
                 gUsbHcTestConformanceAssertionGuid003,
                 L"USB_HC_PROTOCOL.SetState - SetState() returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // the parameter State is invalid
  //
  Status = UsbHc->SetState (UsbHc, EfiUsbHcStateMaximum);

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
                 gUsbHcTestConformanceAssertionGuid003,
                 L"USB_HC_PROTOCOL.SetState - SetState() returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetStateConformanceSubTest1",
                  L"TDS 5.3.2.1 - Call UsbHc->SetState() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - Call ControlTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  //
  // Parameter TransferDirection is invalid (not EfiUsbNoData,EfiUsbDataOut, EfiUsbDataIn).
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    -1,  // invalid
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid004,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid TransferDirection",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    0x7FFFFFFF,  // invalid
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid004,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid TransferDirection",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - Call ControlTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
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
                  L"UsbHcControlTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  //
  //  Paramerer TransferDirection is EfiUsbDataIn ,parameter DataLength is 0 or parameter Data is NULL
  //
  DataLength = 128;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    EfiUsbDataIn,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid005,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data or DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Paramerer TransferDirection is EfiUsbDataOut, parameter DataLength is 0 or parameter Data is NULL
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    EfiUsbDataOut,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid005,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data or DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Paramerer TransferDirection is EfiUsbNoData, parameter DataLength is not NULL or parameter Data is not NULL
  //
  DataLength = 128;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    EfiUsbNoData,
                    Data,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid005,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with invalid Data or DataLength",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - Call ControlTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Parameter Request is NULL
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    NULL, // Request
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid006,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with Request being NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - Call ControlTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  //
  // Parameter MaximumPacketLength is invalid
  //
  // 1. IsSlowDevice is TRUE, MaximumPacketLength is 2
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    2,
                    &Request,
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid007,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with IsSlowDevice is TRUE, MaximumPacketLength is 2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. IsSlowDevice is FALSE, MaximumPacketLength is 128
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    FALSE,
                    128,
                    &Request,
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid008,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with IsSlowDevice is FALSE, MaximumPacketLength is 128",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3. IsSlowDevice is TRUE, MaximumPacketLength is 9
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    9,
                    &Request,
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid009,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with IsSlowDevice is TRUE, MaximumPacketLength is 9",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 4. IsSlowDevice is FALSE, MaximumPacketLength is 9
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    FALSE,
                    9,
                    &Request,
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid010,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with IsSlowDevice is FALSE, MaximumPacketLength is 9",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - Call ControlTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest5",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  //
  // Parameter TransferResult is NULL
  //
  DataLength = 0;
  Status = UsbHc->ControlTransfer (
                    UsbHc,
                    2,
                    TRUE,
                    8,
                    &Request,
                    EfiUsbNoData,
                    NULL,
                    &DataLength,
                    1000,
                    NULL // TransferResult
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
                 gUsbHcTestConformanceAssertionGuid011,
                 L"USB_HC_PROTOCOL.ControlTransfer - ControlTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcControlTransferConformanceSubTest5",
                  L"TDS 5.4.2.1 - Call UsbHc->ControlTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  TransferResult;
  UINTN                   DataLength;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data is NULL
  //
  DataLength = 128;
  DataToggle = 0;
  Status = UsbHc->BulkTransfer (
                    UsbHc,
                    2,
                    1,
                    64,
                    NULL, // Data
                    &DataLength,
                    &DataToggle,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid012,
                 L"USB_HC_PROTOCOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest2",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataLength is 0
  //
  DataLength = 0;
  DataToggle = 0;
  Status = UsbHc->BulkTransfer (
                    UsbHc,
                    2,
                    1,
                    64,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid013,
                 L"USB_HC_PROTOCOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest2",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest3",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // MaximumPacketLength is 2
  //
  DataLength = 128;
  DataToggle = 0;
  Status = UsbHc->BulkTransfer (
                    UsbHc,
                    2,
                    1,
                    2,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid014,
                 L"USB_HC_PROTOCOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with MaximumPacketLength is 2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest3",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest4",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataToggle points to a value other than 0 and 1
  //
  DataLength = 128;
  DataToggle = 2;
  Status = UsbHc->BulkTransfer (
                    UsbHc,
                    2,
                    1,
                    64,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
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
                 gUsbHcTestConformanceAssertionGuid015,
                 L"USB_HC_PROTOCOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with DataToggle pointing to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest4",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINTN                   DataLength;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest5",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // TransferResult is NULL
  //
  DataLength = 128;
  DataToggle = 0;
  Status = UsbHc->BulkTransfer (
                    UsbHc,
                    2,
                    1,
                    64,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    NULL // TransferResult
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
                 gUsbHcTestConformanceAssertionGuid016,
                 L"USB_HC_PROTOCOL.BulkTransfer - BulkTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcBulkTransferConformanceSubTest5",
                  L"TDS 5.5.2.1 - Call UsbHc->BulkTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data transfer direction indicated by EndPointAddress is other than EfiUsbDataIn
  //
  DataToggle = 0;
  Status = UsbHc->AsyncInterruptTransfer (
                    UsbHc,
                    2,
                    1, // invalid
                    TRUE,
                    8,
                    TRUE,
                    &DataToggle,
                    100,
                    128,
                    UsbHcInterruptCallBack,
                    NULL
                    );

  //
  // AsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid017,
                 L"USB_HC_PROTOCOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with invalid EndPointAddress",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // IsNewTransfer is TRUE and DataLength is 0
  //
  DataToggle = 0;
  Status = UsbHc->AsyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    TRUE,
                    &DataToggle,
                    100,
                    0, // invalid
                    UsbHcInterruptCallBack,
                    NULL
                    );

  //
  // AsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid018,
                 L"USB_HC_PROTOCOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // IsNewTransfer is TRUE and DataToggle points to a value other than 0 and 1
  //
  DataToggle = 2;
  Status = UsbHc->AsyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    TRUE,
                    &DataToggle,
                    100,
                    128,
                    UsbHcInterruptCallBack,
                    NULL
                    );

  //
  // AsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid019,
                 L"USB_HC_PROTOCOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataToggle points to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255
  //
  DataToggle = 0;
  Status = UsbHc->AsyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    TRUE,
                    &DataToggle,
                    0, // invalid
                    128,
                    UsbHcInterruptCallBack,
                    NULL
                    );

  //
  // AsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid020,
                 L"USB_HC_PROTOCOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is not in the range 1..255",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // IsNewTransfer is TRUE and PollingInterval is not in the range 1..255
  //
  DataToggle = 0;
  Status = UsbHc->AsyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    TRUE,
                    &DataToggle,
                    256, // invalid
                    128,
                    UsbHcInterruptCallBack,
                    NULL
                    );

  //
  // AsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid020,
                 L"USB_HC_PROTOCOL.AsyncInterruptTransfer - AsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is not in the range 1..255",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.6.2.1 - Call UsbHc->AsyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data transfer direction indicated by EndPointAddress is not EfiUsbDataIn
  //
  DataToggle = 0;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    1, // invalid
                    TRUE,
                    8,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid021,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with invalid EndPointAddress",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data is NULL
  //
  DataToggle = 0;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    NULL, // Data
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid022,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataLength is 0
  //
  DataToggle = 0;
  DataLength = 0;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid023,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength being 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Spec updated:
  // MaxiumPacketLenth is not valid.
  // The legal value of this parameter should be 64 or less for the full-speed device,
  // for the slow device, it is limited to 8.
  //
  DataToggle = 0;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    16, // invalid
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid024,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with MaxiumPacketLenth is not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Spec updated:
  // MaxiumPacketLenth is not valid.
  // The legal value of this parameter should be 64 or less for the full-speed device,
  // for the slow device, it is limited to 8.
  //
  DataToggle = 0;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    FALSE,
                    65, // invalid
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid024,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with MaxiumPacketLenth is not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest5 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  Data[255];
  UINT32                  TransferResult;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest5",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataToggle points to a value other than 0 and 1
  //
  DataToggle = 2;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    &TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid025,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataToggle points to a value other than 0 and 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest5",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceSubTest6 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   DataToggle;
  UINT32                  Data[255];
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest6",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // TransferResult is NULL.
  //
  DataToggle = 0;
  DataLength = 128;
  Status = UsbHc->SyncInterruptTransfer (
                    UsbHc,
                    2,
                    0x81,
                    TRUE,
                    8,
                    (VOID *)Data,
                    &DataLength,
                    &DataToggle,
                    1000,
                    NULL // TransferResult
                    );

  //
  // SyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid026,
                 L"USB_HC_PROTOCOL.SyncInterruptTransfer - SyncInterruptTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSyncInterruptTransferConformanceSubTest6",
                  L"TDS 5.7.2.1 - Call UsbHc->SyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data is NULL
  //
  DataLength = 128;
  Status = UsbHc->AsyncIsochronousTransfer (
                    UsbHc,
                    2,
                    0x81,
                    8,
                    NULL, // Data
                    DataLength,
                    UsbHcIsochronousCallBack,
                    NULL
                    );

  //
  // AsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid033,
                 L"USB_HC_PROTOCOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcAsyncIsochronousTransferConformanceSubTest2",
                  L"TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataLength is 0
  //
  DataLength = 0;
  Status = UsbHc->AsyncIsochronousTransfer (
                    UsbHc,
                    2,
                    0x81,
                    8,
                    Data,
                    DataLength,
                    UsbHcIsochronousCallBack,
                    NULL
                    );

  //
  // AsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid034,
                 L"USB_HC_PROTOCOL.AsyncIsochronousTransfer - AsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcAsyncIsochronousTransferConformanceSubTest2",
                  L"TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.13.2.1 - Call UsbHc->AsyncIsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Data is NULL
  //
  DataLength = 128;
  Status = UsbHc->IsochronousTransfer (
                    UsbHc,
                    2,
                    0x81,
                    8,
                    NULL, // Data
                    DataLength,
                    &TransferResult
                    );

  //
  // IsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid036,
                 L"USB_HC_PROTOCOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  Data[255];
  UINT32                  TransferResult;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest2",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // DataLength is 0
  //
  DataLength = 0;
  Status = UsbHc->IsochronousTransfer (
                    UsbHc,
                    2,
                    0x81,
                    8,
                    Data,
                    DataLength,
                    &TransferResult
                    );

  //
  // IsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid037,
                 L"USB_HC_PROTOCOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with DataLength is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest2",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest3 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceSubTest4 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  Data[255];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest4",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // TransferResult is NULL
  //
  DataLength = 128;
  Status = UsbHc->IsochronousTransfer (
                    UsbHc,
                    2,
                    0x81,
                    8,
                    Data,
                    DataLength,
                    NULL // TransferResult
                    );

  //
  // IsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
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
                 gUsbHcTestConformanceAssertionGuid039,
                 L"USB_HC_PROTOCOL.IsochronousTransfer - IsochronousTransfer() returns EFI_INVALID_PARAMETER with TransferResult is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcIsochronousTransferConformanceSubTest4",
                  L"TDS 5.12.2.1 - Call UsbHc->IsochronousTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.8.2.1 - Call UsbHc->GetRootHubPortNumber() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortNumberConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call UsbHc->GetRootHubPortNumber() with Invalid Parameters\n"
                  );
  }

  //
  // PortNumber is NULL
  //
  Status = UsbHc->GetRootHubPortNumber (UsbHc, NULL);

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
                 gUsbHcTestConformanceAssertionGuid027,
                 L"USB_HC_PROTOCOL.GetRootHubPortNumber - GetRootHubPortNumber() returns EFI_INVALID_PARAMETER with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortNumberConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call UsbHc->GetRootHubPortNumber() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.9.2.1 - Call UsbHc->GetRootHubPortStatus() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   PortNumber;
  EFI_USB_PORT_STATUS     PortStatus;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcGetRootHubPortStatusConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbHc->GetRootHubPortStatus() with Invalid Parameters\n"
                  );
  }

  //
  // PortNumber is greater than or equal to the number of ports returned by GetRootHubPortNumber()
  //
  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    Status = UsbHc->GetRootHubPortStatus (UsbHc, PortNumber, &PortStatus);
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
                   gUsbHcTestConformanceAssertionGuid028,
                   L"USB_HC_PROTOCOL.GetRootHubPortStatus - GetRootHubPortStatus() returns EFI_INVALID_PARAMETER with Invalid PortNumber",
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
                  L"UsbHcGetRootHubPortStatusConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbHc->GetRootHubPortStatus() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   PortNumber;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    //
    // 1. PortNumber is greater than or equal to the number of ports returned by GetRootHubPortNumber()
    //
    Status = UsbHc->SetRootHubPortFeature (UsbHc, PortNumber, EfiUsbPortEnable);
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
                   gUsbHcTestConformanceAssertionGuid029,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortNumber ",
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
                   L"USB_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test SetRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   PortNumber;
  UINT8                   Index;
  EFI_USB_PORT_FEATURE    InvalidUsbPortFeature[7] = {
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
                  L"UsbHcSetRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    //
    // 2. PortFeature is not EfiUsbPortEnable, EfiUsbPortSuspend, EfiUsbPortReset nor EfiUsbPortPower.
    //
    Result = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0; Index < 7; Index++) {
      Status = UsbHc->SetRootHubPortFeature (UsbHc, 0, InvalidUsbPortFeature[Index]);
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
                   gUsbHcTestConformanceAssertionGuid030,
                   L"USB_HC_PROTOCOL.SetRootHubPortFeature - SetRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortFeature",
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
                   L"USB_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test SetRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcSetRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbHc->SetRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceSubTest1 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   PortNumber;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    //
    // 1. PortNumber is greater than or equal to the number of ports returned by GetRootHubPortNumber()
    //
    Status = UsbHc->ClearRootHubPortFeature (UsbHc, PortNumber, EfiUsbPortEnable);
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
                   gUsbHcTestConformanceAssertionGuid031,
                   L"USB_HC_PROTOCOL.ClearRootHubPortFeature - ClearRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortNumber is greater than or equal to the number of ports",
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
                   L"USB_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test ClearRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureConformanceSubTest1",
                  L"TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceSubTest2 (
  IN EFI_USB_HC_PROTOCOL                  *UsbHc,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT8                   PortNumber;
  UINT8                   Index;
  EFI_USB_PORT_FEATURE    InvalidUsbPortFeature[2] = {
    -1,
//    EfiUsbPortReset  // bug in spec
    0x7FFFFFFF
  };

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  Status = UsbHc->GetRootHubPortNumber (UsbHc, &PortNumber);
  if (!EFI_ERROR(Status)) {
    //
    // 2. PortFeature is not EfiUsbPortEnable, EfiUsbPortSuspend, EfiUsbPortPower, EfiUsbPortConnectChange, EfiUsbPortResetChange, EfiUsbPortEnableChange, EfiUsbPortSuspendChange, nor EfiUsbPortOverCurrentChange.
    //
    Result = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0; Index < 2; Index++) {
      Status = UsbHc->ClearRootHubPortFeature (UsbHc, 0, InvalidUsbPortFeature[Index]);
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
                   gUsbHcTestConformanceAssertionGuid032,
                   L"USB_HC_PROTOCOL.ClearRootHubPortFeature - ClearRootHubPortFeature() returns EFI_INVALID_PARAMETER with invalid PortFeature",
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
                   L"USB_HC_PROTOCOL.GetRootHubPortNumber Fail, Skip the test ClearRootHubPortFeature",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbHcClearRootHubPortFeatureConformanceSubTest2",
                  L"TDS 5.11.2.1 - Call UsbHc->ClearRootHubPortFeature() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbHcInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbHcIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
)
{
  return EFI_SUCCESS;
}
