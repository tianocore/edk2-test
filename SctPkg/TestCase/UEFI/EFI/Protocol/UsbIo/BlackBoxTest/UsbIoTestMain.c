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
  EFI_USB_IO_PROTOCOL_GUID,
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
InitializeBBTestUsbIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
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
BBTestUsbIoUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
