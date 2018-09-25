/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  UsbIoTestMain.c

Abstract:
  The main source file for Usb Io tesing.

--*/

//
// Includes
//

#include "SctLib.h"
#include "UsbIoTest.h"

//
// Declarations
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  USB_IO_TEST_REVISION,
  IHV_USB_IO_PROTOCOL_GUID,
  L"Usb Io Protocol Interface Tests",
  L"UEFI Usb Io Protocol Interface Test"
};

EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    USB_IO_USBCONTROLTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbControlTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbControlTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbControlTransferConformanceAutoTest
  },
  {
    USB_IO_USBBULKTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbBulkTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbBulkTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbBulkTransferConformanceAutoTest
  },
  {
    USB_IO_USBASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbAsyncInterruptTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbAsyncInterruptTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbAsyncInterruptTransferConformanceAutoTest
  },
  {
    USB_IO_USBSYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbSyncInterruptTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbSyncInterruptTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbSyncInterruptTransferConformanceAutoTest
  },
  {
    USB_IO_USBASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbAsyncIsochronousTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbAsyncIsochronousTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbAsyncIsochronousTransferConformanceAutoTest
  },
  {
    USB_IO_USBISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID,
    L"UsbIsochronousTransfer_Conf",
    L"Perform conformance checks on the UsbIo->UsbIsochronousTransfer.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbIsochronousTransferConformanceAutoTest
  },
  {
    USB_IO_USBGETDEVICEDESCRIPTOR_CONFORMANCE_AUTO_GUID,
    L"UsbGetDeviceDescriptor_Conf",
    L"Perform conformance checks on the UsbIo->UsbGetDeviceDescriptor.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbGetDeviceDescriptorConformanceAutoTest
  },
  {
    USB_IO_USBGETCONFIGDESCRIPTOR_CONFORMANCE_AUTO_GUID,
    L"UsbGetConfigDescriptor_Conf",
    L"Perform conformance checks on the UsbIo->UsbGetConfigDescriptor.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbGetConfigDescriptorConformanceAutoTest
  },
  {
    USB_IO_USBGETINTERFACEDESCRIPTOR_CONFORMANCE_AUTO_GUID,
    L"UsbGetInterfaceDescriptor_Conf",
    L"Perform conformance checks on the UsbIo->UsbGetInterfaceDescriptor.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbGetInterfaceDescriptorConformanceAutoTest
  },
  {
    USB_IO_USBGETENDPOINTDESCRIPTOR_CONFORMANCE_AUTO_GUID,
    L"UsbGetEndpointDescriptor_Conf",
    L"Perform conformance checks on the UsbIo->UsbGetEndpointDescriptor.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbGetEndpointDescriptorConformanceAutoTest
  },
  {
    USB_IO_USBPORTRESET_CONFORMANCE_AUTO_GUID,
    L"UsbPortReset_Conf",
    L"Perform conformance checks on the UsbIo->UsbPortReset.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbPortResetConformanceAutoTest
  },
  {
    USB_IO_USBGETSTRINGDESCRIPTOR_CONFORMANCE_AUTO_GUID,
    L"UsbGetStringDescriptor_Conf",
    L"Perform conformance checks on the UsbIo->UsbGetStringDescriptor.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbGetStringDescriptorConformanceAutoTest
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

//
// Functions
//


/**
 *  Creates/installs the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @param SystemTable    The system table.
 *  @return EFI_SUCCESS   The interface was installed successfully.
 *  @return EFI_OUT_OF_RESOURCES    Failed due to the lack of resources.
 *  @return EFI_INVALID_PARAMETER   One of parameters is invalid.
 */
EFI_STATUS
EFIAPI
InitializeBBTestUsbIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestUsbIoUnload,
           &gBBTestProtocolInterface
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
EFIAPI
BBTestUsbIoUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeIHVBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
