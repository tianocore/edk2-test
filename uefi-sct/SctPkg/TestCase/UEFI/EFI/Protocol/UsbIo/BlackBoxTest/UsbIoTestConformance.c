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
  UsbIoTestConformance.c

Abstract:
  Source file for Usb Io conformance testing.

--*/

#include "SctLib.h"
#include "UsbIoTest.h"

//
// Prototypes (internal)
//

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest5 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetDeviceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetConfigDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetInterfaceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbPortResetConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetUsbEndpointNotOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  );

EFI_STATUS
GetUsbEndpointOfAttr (
  IN  EFI_USB_IO_PROTOCOL                 *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  );

EFI_STATUS
EFIAPI
UsbInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  );

EFI_STATUS
EFIAPI
UsbIsochronousCallBack (
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
UsbControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbControlTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.1.2.1
  //

  //
  // the parameter Direction is not valid
  //
  Status = UsbControlTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Request is NULL
  //
  Status = UsbControlTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbControlTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Timeout is 0
  //
  Status = UsbControlTransferConformanceSubTest4 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbBulkTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.2.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbBulkTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Data is NULL
  //
  Status = UsbBulkTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter DateLength is NULL
  //
  Status = UsbBulkTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbBulkTransferConformanceSubTest4 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Timeout is 0
  //
  Status = UsbBulkTransferConformanceSubTest5 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbAsyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.3.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbAsyncInterruptTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter PollingInterval is not valid
  //
  Status = UsbAsyncInterruptTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbSyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.4.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbSyncInterruptTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Data is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter DataLength is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest4 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbAsyncIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.12.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbAsyncIsochronousTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.11.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbIsochronousTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetDeviceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetDeviceDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.5.2.1
  //

  //
  // Call UsbGetDeviceDescriptor() with invalid parameter
  //
  Status = UsbGetDeviceDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetConfigDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetConfigDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.6.2.1
  //

  //
  // Call UsbGetConfigDescriptor() with invalid parameter
  //
  Status = UsbGetConfigDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetInterfaceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetInterfaceDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.7.2.1
  //

  //
  // Call UsbGetInterfaceDescriptor() with invalid parameter
  //
  Status = UsbGetInterfaceDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetEndpointDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.8.2.1
  //

  //
  // Call UsbGetEndpointDescriptor() with invalid parameter
  //
  Status = UsbGetEndpointDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // TDS 5.8.2.2
  //

  //
  // Call UsbGetEndpointDescriptor() with non-existed endpoint
  //
  Status = UsbGetEndpointDescriptorConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbPortResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbPortReset() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.9.2.1
  //

  //
  // Call UsbPortReset() with invalid parameter
  //
  Status = UsbPortResetConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetStringDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

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
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.10.2.1
  // Call UsbGetStringDescriptor() with unsupported languageID
  //

  //
  // Comment it out, because no such description in EFI1.1 spec.
  //
  //  Status = UsbGetStringDescriptorConformanceSubTest1(UsbIo, StandardLib, LoggingLib);

  //
  // TDS 5.10.2.1
  // Call UsbGetStringDescriptor() with unsupported StringIndex
  //

  //
  // Comment it out, because no such description in EFI1.1 spec.
  //
  //  Status = UsbGetStringDescriptorConformanceSubTest2(UsbIo, StandardLib, LoggingLib);

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
UsbControlTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbControlTransfer should return EFI_INVALID_PARAMETER when Direction is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest1",
                  L"TDS 5.1.2.1 - Direction is not valid\n"
                  );
  }

  //
  // build a request
  //
  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    -1, // invalid Direction
                    3000,
                    NULL,
                    0,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid001,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Direction being not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    0x7FFFFFF,  // invalid Direction
                    3000,
                    NULL,
                    0,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid001,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Direction being not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest1",
                  L"TDS 5.1.2.1 - Direction is not valid\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbControlTransfer should return EFI_INVALID_PARAMETER when the parameter Request is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32              UsbStatus;
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest2",
                  L"TDS 5.1.2.1 - the parameter Request is NULL\n"
                  );
  }

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    NULL, // Request is NULL
                    EfiUsbNoData,
                    3000,
                    NULL,
                    0,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid002,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Request is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest2",
                  L"TDS 5.1.2.1 - the parameter Request is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbControlTransfer should return EFI_INVALID_PARAMETER when the parameter Status is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
  
--*/
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest3",
                  L"TDS 5.1.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // build a request
  //
  Request.RequestType = 0x21;
  Request.Request     = 0xFF;
  Request.Value       = 0;
  Request.Index       = 0;
  Request.Length      = 0;

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    EfiUsbNoData,
                    3000,
                    NULL,
                    0,
                    NULL  // Status is NULL
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
                 gUsbIoTestConformanceAssertionGuid003,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest3",
                  L"TDS 5.1.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbControlTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbControlTransfer should return EFI_SUCCESS or EFI_DEVICE_ERROR when the parameter Timeout is 0.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
  
--*/
{
  EFI_STATUS                 Status;
  EFI_TEST_ASSERTION         Result;
  EFI_USB_DEVICE_REQUEST     Request;
  UINT32                     UsbStatus;
  EFI_USB_DEVICE_DESCRIPTOR  DevDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest4",
                  L"The parameter Timeout is 0\n"
                  );
  }

  //
  // Build a Bulk-Only Mass Storage Reset Request
  //
  Request.RequestType = 0x80;
  Request.Request     = 0x6;
  Request.Value       = 0x100;
  Request.Index       = 0;
  Request.Length      = sizeof(EFI_USB_DEVICE_DESCRIPTOR);

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    EfiUsbDataIn,
                    0,            //Timeout is 0
                    &DevDesc,
                    sizeof(EFI_USB_DEVICE_DESCRIPTOR),
                    &UsbStatus  
                    );

  if (Status == EFI_SUCCESS || Status == EFI_DEVICE_ERROR) {
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
                 gUsbIoTestConformanceAssertionGuid046,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_SUCCESS or EFI_DEVICE_ERROR when the parameter Timeout is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest4",
                  L"The parameter Timeout is 0\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbBulkTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
  
Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest1",
                  L"TDS 5.2.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid004,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid005,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid006,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid007,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. The endpoint is not a BULK endpoint(with attribute != 0x02)
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a NonBulk endpoint. Skipped this test for BulkTransfer.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    DataLength = 128;
    Status = UsbIo->UsbBulkTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      (VOID *)Data,
                      &DataLength,
                      1000,
                      &UsbStatus
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
                   gUsbIoTestConformanceAssertionGuid008,
                   L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a BULK endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest1",
                  L"TDS 5.2.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbBulkTransfer should return EFI_INVALID_PARAMETER when Data is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest2",
                  L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest2",
                    L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 3. the parameter Data is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    NULL,
                    &DataLength,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid009,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest2",
                  L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbBulkTransfer should return EFI_INVALID_PARAMETER when DataLength is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest3",
                  L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest3",
                    L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 4. The Parameter DataLength is NULL
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    NULL,
                    1000,
                    &UsbStatus
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
                 gUsbIoTestConformanceAssertionGuid010,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DataLength is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest3",
                  L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbBulkTransfer should return EFI_INVALID_PARAMETER when Status is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest4",
                  L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest4",
                    L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 5. The Parameter Status is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    &DataLength,
                    1000,
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
                 gUsbIoTestConformanceAssertionGuid011,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest4",
                  L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbBulkTransferConformanceSubTest5 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbBulkTransfer should return EFI_SUCCESS or EFI_DEVICE_ERROR when Timeout is 0.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
#ifndef EFIARM
  EFI_STATUS                   Status;
  EFI_TEST_ASSERTION           Result;
  UINT32                       Data[512];
  UINTN                        DataLength;
  UINT32                       UsbStatus;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;


  EFI_USB_INTERFACE_DESCRIPTOR Interface;
  EFI_USB_ENDPOINT_DESCRIPTOR  EndPoint;
  UINT8                        Index;
  USB_BOT_PROTOCOL             *UsbBot;
  USB_BOT_CBW                  Cbw;
  USB_BOOT_READ10_CMD          ReadCmd;
  USB_BOT_CSW                  Csw;


  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest5",
                  L"The parameter Timeout is 0\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest5",
                    L"The parameter Timeout is 0\n"
                    );
    }

    return Status;
  }

  //
  // 6. The Parameter Timeout is 0
  //

  // Send the command to the device.
  
  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &Interface);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to get the InterfaceDescriptor. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest5",
                    L"The parameter Timeout is 0\n"
                    );
    }
    return Status;
  } 
 
  if (Interface.InterfaceProtocol != USB_MASS_STORE_BOT && 
    Interface.InterfaceProtocol != USB_MASS_STORE_CBI0 &&
    Interface.InterfaceProtocol != USB_MASS_STORE_CBI1) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find Mass Store Device. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest5",
                    L"The parameter Timeout is 0\n"
                    );
    }
    return EFI_UNSUPPORTED;
  }

  if (Interface.InterfaceProtocol == USB_MASS_STORE_BOT) {
    UsbBot = SctAllocateZeroPool (sizeof (USB_BOT_PROTOCOL) + 2 * sizeof (EFI_USB_ENDPOINT_DESCRIPTOR));
 
    SctZeroMem (UsbBot, sizeof (USB_BOT_PROTOCOL) + 2 * sizeof (EFI_USB_ENDPOINT_DESCRIPTOR));
    
    UsbBot->UsbIo     = UsbIo;
    UsbBot->Interface = &Interface;

    //
    // Locate and save the first bulk-in and bulk-out endpoint
    //
    for (Index = 0; Index < Interface.NumEndpoints; Index++) {
      Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, Index, &EndPoint);

      if (EFI_ERROR (Status) || !USB_IS_BULK_ENDPOINT (EndPoint.Attributes)) {
        continue;
      }

      if (USB_IS_IN_ENDPOINT (EndPoint.EndpointAddress) &&
       (UsbBot->BulkInEndpoint == NULL)) {

        UsbBot->BulkInEndpoint  = (EFI_USB_ENDPOINT_DESCRIPTOR *) (UsbBot + 1);
        SctCopyMem (UsbBot->BulkInEndpoint, &EndPoint, sizeof (EndPoint));
      }

      if (USB_IS_OUT_ENDPOINT (EndPoint.EndpointAddress) &&
       (UsbBot->BulkOutEndpoint == NULL)) {

        UsbBot->BulkOutEndpoint   = (EFI_USB_ENDPOINT_DESCRIPTOR *) (UsbBot + 1) + 1;
        SctCopyMem (UsbBot->BulkOutEndpoint, &EndPoint, sizeof(EndPoint));
      }
    }

    //
    // If bulk-in or bulk-out endpoint is not found, report error.
    //
    if ((UsbBot->BulkInEndpoint == NULL) || (UsbBot->BulkOutEndpoint == NULL)) {
      Status = EFI_UNSUPPORTED;
      if (LoggingLib != NULL) {
        LoggingLib->ExitFunction (
                      LoggingLib,
                      L"UsbBulkTransferConformanceSubTest5",
                      L"The parameter Timeout is 0\n"
                      );
      }
      return EFI_SUCCESS;
    }

    //
    // The USB BOT protocol uses CBWTag to match the CBW and CSW.
    //
    UsbBot->CbwTag = 0x01;

    //
    // Fill in the command
    //
    SctZeroMem (&ReadCmd, sizeof (USB_BOOT_READ10_CMD));

    ReadCmd.OpCode  = USB_BOOT_READ10_OPCODE;
    ReadCmd.Lun     = 0;
    SctWriteUnaligned32 ((UINT32 *) ReadCmd.Lba, SctSwapBytes32 (200));
    SctWriteUnaligned16 ((UINT16 *) ReadCmd.TransferLen, SctSwapBytes16 (1));

    //
    // Fill in the Command Block Wrapper.
    //
    Cbw.Signature = USB_BOT_CBW_SIGNATURE;
    Cbw.Tag       = UsbBot->CbwTag;
    Cbw.DataLen   = 512;
    Cbw.Flag      = BIT7;
    Cbw.Lun       = 0;
    Cbw.CmdLen    = sizeof (USB_BOOT_READ10_CMD);

    SctZeroMem (Cbw.CmdBlock, USB_BOT_MAX_CMDLEN);
    SctCopyMem (Cbw.CmdBlock, &ReadCmd, Cbw.CmdLen);

    UsbStatus  = 0;
    DataLength = sizeof (USB_BOT_CBW);

    //
    // Use USB I/O Protocol to send the Command Block Wrapper to the device.
    //
    Status = UsbBot->UsbIo->UsbBulkTransfer (
                              UsbBot->UsbIo,
                              UsbBot->BulkOutEndpoint->EndpointAddress,
                              &Cbw,
                              &DataLength,
                              0,
                              &UsbStatus
                              );
    
    if (Status == EFI_SUCCESS || Status == EFI_DEVICE_ERROR) {
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
                   gUsbIoTestConformanceAssertionGuid047,
                   L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_SUCCESS or EFI_DEVICE_ERROR when Timeout is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (Status != EFI_SUCCESS) {
      if (LoggingLib != NULL) {
        LoggingLib->ExitFunction (
                      LoggingLib,
                      L"UsbBulkTransferConformanceSubTest5",
                      L"The parameter Timeout is 0\n"
                      );
      }
      return EFI_SUCCESS;
    }

    //
    // Data Transfer
    //
    DataLength = 512;
    UsbStatus  = 0;
    
    Status = UsbBot->UsbIo->UsbBulkTransfer (
                              UsbBot->UsbIo,
                              UsbBot->BulkInEndpoint->EndpointAddress,
                              Data,
                              &DataLength,
                              0,
                              &UsbStatus
                              );
    
    if (Status == EFI_SUCCESS || Status == EFI_DEVICE_ERROR) {
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
                   gUsbIoTestConformanceAssertionGuid047,
                   L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_SUCCESS or EFI_DEVICE_ERROR when Timeout is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (Status != EFI_SUCCESS) {
      if (LoggingLib != NULL) {
        LoggingLib->ExitFunction (
                      LoggingLib,
                      L"UsbBulkTransferConformanceSubTest5",
                      L"The parameter Timeout is 0\n"
                      );
      }
      return EFI_SUCCESS;
    }


    //
    // CSW
    //
    SctZeroMem (&Csw, sizeof (USB_BOT_CSW));
     
    UsbStatus  = 0;
    DataLength = sizeof (USB_BOT_CSW);
    
    Status = UsbIo->UsbBulkTransfer (
                      UsbBot->UsbIo,
                      UsbBot->BulkInEndpoint->EndpointAddress,
                      &Csw,
                      &DataLength,
                      0,
                      &UsbStatus
                      );
    
    if (Status == EFI_SUCCESS || Status == EFI_DEVICE_ERROR) {
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
                   gUsbIoTestConformanceAssertionGuid047,
                   L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_SUCCESS or EFI_DEVICE_ERROR when Timeout is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    
    if (Status != EFI_SUCCESS) {
      if (LoggingLib != NULL) {
        LoggingLib->ExitFunction (
                      LoggingLib,
                      L"UsbBulkTransferConformanceSubTest5",
                      L"The parameter Timeout is 0\n"
                      );
      }
      return EFI_SUCCESS;
    }

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest5",
                  L"The parameter Timeout is 0\n"
                  );
  }
#endif
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbAsyncInterruptTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.3.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0,  // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid012,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid013,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid014,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid015,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Interrupt endpoint
  //
  // Attributes != 0x03 means this is not an Interrupt endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncInterruptTransfer: Failed to find an non-interrupt endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Status = UsbIo->UsbAsyncInterruptTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      TRUE,
                      100,
                      DataLength,
                      UsbInterruptCallBack,
                      NULL
                      );

    //
    // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                   gUsbIoTestConformanceAssertionGuid016,
                   L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Interrupt endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.3.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbAsyncInterruptTransfer should return EFI_INVALID_PARAMETER when PollingInterval is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbAsyncInterruptTransferConformanceSubTest2",
                    L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                    );
    }

    return Status;
  }

  //
  // 3. the parameter PollingInterval is invalid
  // PollingInterval is 0
  //
  DataLength = 128;
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    TRUE,
                    0,  // invalid polling interval
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid017,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // PollingInterval is 256
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    TRUE,
                    256,  // invalid polling interval
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid018,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is 256",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbSyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid019,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid020,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid021,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid022,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Interrupt endpoint
  //
  // Attributes != 0x03 means this is not an Interrupt endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer:  Failed to find an non-interrupt endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Status = UsbIo->UsbSyncInterruptTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      (VOID *)Data,
                      &DataLength,
                      1000,
                      &UsbStatus
                      );

    //
    // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                   gUsbIoTestConformanceAssertionGuid023,
                   L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Interrupt endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbSyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when Data is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest2",
                    L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 3. the parameter Data is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    NULL,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid024,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when DataLength is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  UINT32                      UsbStatus;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest3",
                    L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 4. The Parameter DataLength is NULL
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    NULL,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid025,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when Status is NULL.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINT32                      Data[255];
  UINTN                       DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest4",
                    L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 5. The Parameter Status is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    NULL
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid026,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
UsbAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbAsyncIsochronousTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;
  UINT32                      Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0,  // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid036,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid037,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid038,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid039,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Isochronous endpoint
  //
  // Attributes != 0x01 means this is not an Isochronous endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x01, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncIsochronousTransfer: Failed to find an non-isochronous endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Status = UsbIo->UsbAsyncIsochronousTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      Data,
                      DataLength,
                      UsbIsochronousCallBack,
                      NULL
                      );

    //
    // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                   gUsbIoTestConformanceAssertionGuid040,
                   L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Isochronous endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbIsochronousTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  UINTN                       DataLength;
  UINT32                      UsbStatus;
  UINT32                      Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbIsochronousTransferConformanceSubTest1",
                  L"TDS 5.11.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0,  // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid041,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid042,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid043,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                 gUsbIoTestConformanceAssertionGuid044,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Isochronous endpoint
  //
  // Attributes != 0x01 means this is not an Isochronous endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x01, 0x03, &EndpointDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbIsochronousTransfer: Failed to find an non-isochronous endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Status = UsbIo->UsbIsochronousTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      Data,
                      DataLength,
                      &UsbStatus
                      );

    //
    // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
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
                   gUsbIoTestConformanceAssertionGuid045,
                   L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Isochronous endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbIsochronousTransferConformanceSubTest1",
                  L"TDS 5.11.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetDeviceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetDeviceDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.
  
Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetDeviceDescriptorConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call UsbGetDeviceDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter DeviceDescriptor is NULL
  //
  Status = UsbIo->UsbGetDeviceDescriptor (UsbIo, NULL);

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
                 gUsbIoTestConformanceAssertionGuid027,
                 L"EFI_USB_IO_PROTOCOL.UsbGetDeviceDescriptor - UsbGetDeviceDescriptor() returns EFI_INVALID_PARAMETER with DeviceDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetDeviceDescriptorConformanceSubTest1",
                  L"TDS 5.5.2.1 - Calling UsbGetDeviceDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetConfigDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetConfigDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetConfigDescriptorConformanceSubTest1",
                  L"TDS 5.6.2.1 - Call UsbGetConfigDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter ConfigurationDescriptor is NULL
  //
  Status = UsbIo->UsbGetConfigDescriptor (UsbIo, NULL);

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
                 gUsbIoTestConformanceAssertionGuid028,
                 L"EFI_USB_IO_PROTOCOL.UsbGetConfigDescriptor - UsbGetConfigDescriptor() returns EFI_INVALID_PARAMETER with ConfigurationDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetConfigDescriptorConformanceSubTest1",
                  L"TDS 5.6.2.1 - Calling UsbGetConfigDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetInterfaceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetInterfaceDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetInterfaceDescriptorConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call UsbGetInterfaceDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter InterfaceDescriptor is NULL
  //
  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, NULL);

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
                 gUsbIoTestConformanceAssertionGuid029,
                 L"EFI_USB_IO_PROTOCOL.UsbGetInterfaceDescriptor - UsbGetInterfaceDescriptor() returns EFI_INVALID_PARAMETER with InterfaceDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetInterfaceDescriptorConformanceSubTest1",
                  L"TDS 5.7.2.1 - Calling UsbGetInterfaceDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetEndpointDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          Result;
  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDescriptor;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call UsbGetEndpointDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter EndpointDescriptor is NULL
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, 0, NULL);
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
                 gUsbIoTestConformanceAssertionGuid030,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_INVALID_PARAMETER with EndpointDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // the parameter EndpointIndex > 15
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, 16, &EndpointDescriptor);
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
                 gUsbIoTestConformanceAssertionGuid031,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_INVALID_PARAMETER with EndpointIndex > 15",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest1",
                  L"TDS 5.8.2.1 - Calling UsbGetEndpointDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetEndpointDescriptor should return EFI_NOT_FOUND when endpoint is non-existed.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                    Status;
  EFI_TEST_ASSERTION            Result;
  EFI_USB_ENDPOINT_DESCRIPTOR   EndpointDescriptor;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest2",
                  L"TDS 5.8.2.2 - Call UsbGetEndpointDescriptor with non-existed endpoint\n"
                  );
  }

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbGetEndpointDescriptorConformanceSubTest2: FAILED in UsbGetInterfaceDescriptor--Skip this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbGetEndpointDescriptorConformanceSubTest2--Skipped",
                    L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                    );
    }

    return Status;
  }

  if (InterfaceDesc.NumEndpoints == 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbGetEndpointDescriptorConformanceSubTest2: Couldn't get an undefined endpoint--Skip this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbGetEndpointDescriptorConformanceSubTest2--Skipped",
                    L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                    );
    }

    return Status;

  }

  //
  // the parameter EndpointIndex >= InterfaceDescriptor.NumEndpoints
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, (UINT8)(InterfaceDesc.NumEndpoints), &EndpointDescriptor);
  if (Status == EFI_NOT_FOUND) {
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
                 gUsbIoTestConformanceAssertionGuid032,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_NOT_FOUND with EndpointIndex >= InterfaceDescriptor.NumEndpoints",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest2",
                  L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbPortResetConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbPortReset should return EFI_INVALID_PARAMETER when parameter is invalid.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS                    Status;
  EFI_TEST_ASSERTION            Result;
  EFI_USB_DEVICE_DESCRIPTOR     DeviceDesc;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbPortResetConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbPortReset with invalid parameter\n"
                  );
  }

  //
  // The controller specified by parameter This is a USB hub
  //
  Status = UsbIo->UsbGetDeviceDescriptor (UsbIo, &DeviceDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbPortResetConformanceSubTest1: FAILEDin UsbGetDeviceDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbPortResetConformanceSubTest1: FAILEDin UsbGetInterfaceDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // this usbio is for usb hub
  //
  if ((DeviceDesc.DeviceClass == 0x09) && (InterfaceDesc.InterfaceClass == 0x09)) {
    Status = UsbIo->UsbPortReset (UsbIo);
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
                   gUsbIoTestConformanceAssertionGuid033,
                   L"EFI_USB_IO_PROTOCOL.UsbPortReset - UsbPortReset() returns EFI_INVALID_PARAMETER with the controller specified by parameter This is a USB hub",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbPortResetConformanceSubTest1: The controller specified by parameter This is not a USB hub. Skip conf. test for portreset",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbPortResetConformanceSubTest1",
                  L"TDS 5.9.2.1 - Calling UsbPortReset() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetStringDescriptor should return EFI_NOT_FOUND when LangID is not found.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted LangID\n"
                  );
  }

  //
  // LangID=0
  //
  Status = UsbIo->UsbGetStringDescriptor (UsbIo, 0, 1, NULL);
  if (Status == EFI_NOT_FOUND) {
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
                 gUsbIoTestConformanceAssertionGuid034,
                 L"EFI_USB_IO_PROTOCOL.UsbGetStringDescriptor - UsbGetStringDescriptor() returns EFI_NOT_FOUND with LangID = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted LangID\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
/*++

Routine Description:

  UsbGetStringDescriptor should return EFI_NOT_FOUND when StringIndex is not found.

Arguments:

  UsbIo         - A pointer to EFI_USB_IO_PROTOCOL instance.
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  LoggingLib    - A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL instance.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.
  
--*/
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted StringIndex\n"
                  );
  }

  //
  // StringIndex=0
  //
  Status = UsbIo->UsbGetStringDescriptor (UsbIo, 1, 0, NULL);
  if (Status == EFI_NOT_FOUND) {
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
                 gUsbIoTestConformanceAssertionGuid035,
                 L"EFI_USB_IO_PROTOCOL.UsbGetStringDescriptor - UsbGetStringDescriptor() returns EFI_NOT_FOUND with StringIndex = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted StringIndex\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
GetUsbEndpointNotOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  )
/*++

Routine Description:

  This function retrieves the endpoint descriptor to find an non-bulk endpoint

Arguments:

  UsbIo         - A pointer to the EFI_USB_IO_PROTOCOL instance
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance
  Attributes    - The attribute of the endpoint we don't want to retrieve
  AttribMask    - The mask of attribute of the endpoint we want to retrieve
  pEndpointDesc - A pointer to the caller allocated USB Endpoint Descriptor
                  to store the resulted non-bulk endpoint
Returns:

  EFI_SUCESS    - if find an non-bulk endpoint
  Other value   - if fail to find an non-bulk endpoint

--*/
{
  EFI_STATUS                    Status;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDesc;
  UINT8                         Index;

  Status  = EFI_SUCCESS;

  Status  = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if ((EFI_ERROR (Status)) || (InterfaceDesc.NumEndpoints == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"GetUsbEndpointNotOfAttr: FAILED at UsbGetInterfaceDescriptor.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_ABORTED;
  }

  for (Index = 0; Index < InterfaceDesc.NumEndpoints; Index++) {
    Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, Index, pEndpointDesc);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"GetUsbEndpointNotOfAttr: FAILED at UsbGetEndpointDescriptor.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return EFI_ABORTED;
    }

    if ((pEndpointDesc->Attributes & AttribMask) == (Attributes & AttribMask)) {
      break;
    }
  }

  if (Index == InterfaceDesc.NumEndpoints) {
    Status = EFI_SUCCESS;
  } else {
    Status = EFI_NOT_FOUND;
  }

  return Status;
}

EFI_STATUS
GetUsbEndpointOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  )
/*++

Routine Description:

  This function retrieves the endpoint descriptor to find a bulk endpoint

Arguments:

  UsbIo         - A pointer to the EFI_USB_IO_PROTOCOL instance
  StandardLib   - A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance
  Attributes    - The attribute of the endpoint we don't want to retrieve
  AttribMask    - The mask of attribute of the endpoint we want to retrieve
  pEndpointDesc - A pointer to the caller allocated USB Endpoint Descriptor
                  to store the resulted non-bulk endpoint
Returns:

  EFI_SUCESS    - if find an non-bulk endpoint
  Other value   - if fail to find an non-bulk endpoint

--*/
{
  EFI_STATUS                    Status;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDesc;
  UINT8                         Index;

  Status  = EFI_SUCCESS;

  Status  = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if ((EFI_ERROR (Status)) || (InterfaceDesc.NumEndpoints == 0)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"GetUsbEndpointOfAttr: FAILED at UsbGetInterfaceDescriptor.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return EFI_ABORTED;
  }

  for (Index = 0; Index < InterfaceDesc.NumEndpoints; Index++) {
    Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, Index, pEndpointDesc);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"GetUsbEndpointNotOfAttr: FAILED at UsbGetEndpointDescriptor.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return EFI_ABORTED;
    }

    if ((pEndpointDesc->Attributes & AttribMask) == (Attributes & AttribMask)) {
      break;
    }
  }

  if (Index == InterfaceDesc.NumEndpoints) {
    Status = EFI_NOT_FOUND;
  } else {
    Status = EFI_SUCCESS;
  }

  return Status;
}

EFI_STATUS
EFIAPI
UsbInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  )
/*++

Routine Description:

  Interrupt Transfer Callback Function

Arguments:

  Data        - Data
  DataLength  - DataLength
  Context     - Context
  Status      - Status

Returns:

  EFI_SUCCESS - Successfully

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UsbIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  )
/*++

Routine Description:

  Isochronous Transfer Callback Function

Arguments:

  Data        - Data
  DataLength  - DataLength
  Context     - Context
  Status      - Status

Returns:

  EFI_SUCCESS - Successfully

--*/
{
  return EFI_SUCCESS;
}
