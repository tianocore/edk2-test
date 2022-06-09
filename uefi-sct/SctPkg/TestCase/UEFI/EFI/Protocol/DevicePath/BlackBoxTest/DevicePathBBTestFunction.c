/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathBBTestFunction.c

Abstract:

  Interface Function Test Cases of Device Path Protocol

--*/

#include "DevicePathBBTestMain.h"

EFI_GUID  gBlackBoxEfiDevicePathMessagingUartFlowControlGuid  = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
EFI_GUID  gBlackBoxEfiDevicePathMessagingSASGuid              = DEVICE_PATH_MESSAGING_SAS;
#endif

/**
 *  Entrypoint for EFI_DEVICE_PATH_PROTOCOL_GUID Path Node Conformance Test.
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
BBTestDevicePathNodeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_TEST_ASSERTION                  AssertionType;
  UINT16                              Type;
  UINT16                              SubType;
  UINT16                              Length;
  MEMMAP_DEVICE_PATH                  *MemMap;
  MAC_ADDR_DEVICE_PATH                *Mac;
  IPV4_DEVICE_PATH                    *IPv4;
  IPV6_DEVICE_PATH                    *IPv6;
  ATAPI_DEVICE_PATH                   *Atapi;
  UART_DEVICE_PATH                    *Uart;
  UART_FLOW_CONTROL_DEVICE_PATH       *UartFlow;
  VENDOR_DEVICE_PATH                  *Vendor;
  VLAN_DEVICE_PATH                    *Vlan;
  HARDDRIVE_DEVICE_PATH               *Hd;
  CHAR16                              *DevStr;
  BMC_DEVICE_PATH                     *BMC;
  DNS_DEVICE_PATH                     *DNS;
  BLUETOOTH_LE_DEVICE_PATH            *BlueToothLE;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePath  = (EFI_DEVICE_PATH_PROTOCOL *) ClientInterface;

  DevStr      = SctDevicePathToStr (DevicePath);
  StandardLib->RecordMessage (
                StandardLib,
                EFI_VERBOSE_LEVEL_QUIET,
                L"\nVerifying device path: %s\n",
                DevStr
                );
  gtBS->FreePool (DevStr);

  while (!SctIsDevicePathEnd (DevicePath)) {
    Type    = (UINT16) SctDevicePathType (DevicePath);
    SubType = (UINT16) SctDevicePathSubType (DevicePath);
    Length  = (UINT16) SctDevicePathNodeLength (DevicePath);

    //
    // Assertion Point 3.1.2.2
    // Check End of Hardware Device Path: End This Device Path
    //
    if ((Type == 0x7F ) && (SubType == 0x01)) {
      if (Length == 4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid001,
                    L"EFI_DEVICE_PATH_PROTOCOL - End of Hardware Device Path - End This Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.3
    // Check Hardware Device Path: PCI Device Path
    //
    else if ((Type == 1) && (SubType == 1)) {
      if (Length == 6) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid002,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - PCI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.4
    // Check Hardware Device Path: PCCARD Device Path
    //
    else if ((Type == 1) && (SubType == 2)) {
      if (Length == 5) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid003,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - PCCARD Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.5
    // Check Hardware Device Path: Memory Mapped Device Path
    //
    else if ((Type == 1) && (SubType == 3)) {
      MemMap = (MEMMAP_DEVICE_PATH *) DevicePath;
      if ((Length == 24) &&
          (MemMap->MemoryType < EfiMaxMemoryType || MemMap->MemoryType > 0x7FFFFFFF) &&
          (MemMap->EndingAddress >= MemMap->StartingAddress)
          ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid004,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Memory Mapped Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.6
    // Check Hardware Device Path: Vendor Device Path
    //
    else if ((Type == 1) && (SubType == 4)) {
      if (Length >= 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid005,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Vendor Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.7
    // Check Hardware Device Path: Controller Device Path
    //
    else if ((Type == 1) && (SubType == 5)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid006,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Controller Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // 
    // Check Hardware Device Path: BMC Device Path
    //
    else if ((Type == 1) && (SubType == 6)) {
      BMC = (BMC_DEVICE_PATH *) DevicePath;
      if (Length == 13 && BMC->InterfaceType >= 0x00 && BMC->InterfaceType <= 0x03) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid042,
                    L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Controller Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d, InterfaceType - %x",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length,
					BMC->InterfaceType
                    );
    }
	
    //
    // Assertion Point 3.1.2.8
    // Check ACPI Device Path: ACPI Device Path
    //
    else if ((Type == 2) && (SubType == 1)) {
      if (Length == 12) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid007,
                    L"EFI_DEVICE_PATH_PROTOCOL - ACPI Device Path - ACPI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.9
    // Check ACPI Device Path: Expanded ACPI Device Path
    //
    else if ((Type == 2) && (SubType == 2)) {
      if (Length >= 19) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid008,
                    L"EFI_DEVICE_PATH_PROTOCOL - ACPI Device Path - Expanded ACPI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)	
    //
    // Assertion Point 3.1.2.10
    // Check ACPI _ADR Device Path: ACPI _ADR Device Path
    //
    else if ((Type == 2) && (SubType == 3)) {
      if (Length >= 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid031,
                    L"EFI_DEVICE_PATH_PROTOCOL - ACPI _ADR Device Path - ACPI _ADR Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
#endif

    //
    // Assertion Point 3.1.2.11
    // Check Messaging Device Path: ATAPI Device Path
    //
    else if ((Type == 3) && (SubType == 1)) {
      Atapi = (ATAPI_DEVICE_PATH *) DevicePath;
      if ((Length == 8) &&
          (Atapi->PrimarySecondary == 0 || Atapi->PrimarySecondary == 1) &&
          (Atapi->SlaveMaster == 0 || Atapi->SlaveMaster == 1)
          ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid009,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - ATAPI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.12
    // Check Messaging Device Path: SCSI Device Path
    //
    else if ((Type == 3) && (SubType == 2)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid010,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - SCSI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.13
    // Check Messaging Device Path: Fibre Channel Device Path
    //
    else if ((Type == 3) && (SubType == 3)) {
      if (Length == 24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid011,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Fibre Channel Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.14
    // Check Messaging Device Path: 1394 Device Path
    //
    else if ((Type == 3) && (SubType == 4)) {
      if (Length == 16) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid012,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - 1394 Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.15
    // Check Messaging Device Path: USB Device Path
    //
    else if ((Type == 3) && (SubType == 5)) {
      if (Length == 6) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid013,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)		
    //
    // Add a new CheckPoint for SATA Device Path which belong to UEFI 2.1
    // Check SATA Device Path
    //
    else if ((Type == 3) && (SubType == 18)) {
      if (Length == 10) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid039,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - SATA Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }	
#endif	
    //
    // Assertion Point 3.1.2.16
    // Check Messaging Device Path: USB Device Path(WWID)
    //
    else if ((Type == 3) && (SubType == 16)) {
      if (Length >= 10) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid032,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Device Path(WWID)",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.17
    // Check Messaging Device Path: Device Logical Unit
    //
    else if ((Type == 3) && (SubType == 17)) {
      if (Length == 5) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid033,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Device Path(WWID)",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.18
    // Check Messaging Device Path: USB Device Path(Class)
    //
    else if ((Type == 3) && (SubType == 15)) {
      if (Length == 11) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid014,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Class Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.19
    // Check Messaging Device Path: I2O Device Path
    //
    else if ((Type == 3) && (SubType == 6)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid015,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - I2O Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.20
    // Check Messaging Device Path: MAC Address Device Path
    //
    else if ((Type == 3) && (SubType == 11)) {
      Mac = (MAC_ADDR_DEVICE_PATH *)DevicePath;
      if (Length == 37) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid016,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - MAC Address Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d, IfType - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length,
                    Mac->IfType
                    );
    }
    //
    // Assertion Point 3.1.2.21
    // Check Messaging Device Path: IPv4 Device Path
    //
    else if ((Type == 3) && (SubType == 12)) {
      IPv4 = (IPV4_DEVICE_PATH *) DevicePath;
      if ((Length == 27) && (IPv4->StaticIpAddress == 0 || IPv4->StaticIpAddress == 1)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid017,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - IPv4 Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.22
    // Check Messaging Device Path: IPv6 Device Path
    //
    else if ((Type == 3) && (SubType == 13)) {
      IPv6 = (IPV6_DEVICE_PATH *) DevicePath;
      if ((Length == 60) && (IPv6->IPAddressOrigin == 0 || IPv6->IPAddressOrigin == 1 || IPv6->IPAddressOrigin == 2)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid018,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - IPv6 Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new CheckPoint for VLAN Device Path which belong to UEFI 2.3
    // Check Messaging Device Path: Vlan Device Path
    //
    else if ((Type == 3) && (SubType == 20)) {
      Vlan = (VLAN_DEVICE_PATH *) DevicePath;
      if (Vlan->VlanId > 4094 || Vlan->VlanId) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid043,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Vlan Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, VlanId - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Vlan->VlanId
                    );      
    }
    //
    // Add a new CheckPoint for Fibre Channel Ex device path
    // Check Messaging Device Path: Fibre Channel Ex device path
    //
    else if ((Type == 3) && (SubType == 21)) {
      if (Length == 24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid036,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Fibre Channel Ex device path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new CheckPoint for Serial Attached SCSI(SAS) Ex device path
    // Check Messaging Device Path: Serial Attached SCSI(SAS) Ex device path
    //
    else if ((Type == 3) && (SubType == 22)) {
      if (Length == 32) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid037,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Serial Attached SCSI(SAS) Ex device path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for NVM Express Namespace Device Path
    // Check Messaging Device Path: NVM Express Namespace Device Path
    //
    else if ((Type == 3) && (SubType == 23)) {
      if (Length  ==16) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid038,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - NVM Express Namespace Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );  
    }
    //
    // Add a new checkpoint for Uniform Resource Identifiers (URI) Device Path
    // Check Messaging Device Path: Uniform Resource Identifiers (URI) Device Path
    //
    else if ((Type == 3) && (SubType == 24)) {
      if (Length  >= 4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid044,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Uniform Resource Identifiers (URI) Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for Universal Flash Storage (UFS) Device Path
    // Check Messaging Device Path: Universal Flash Storage (UFS) Device Path
    //
    else if ((Type == 3) && (SubType == 25)) {
      if (Length  == 6) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid045,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Universal Flash Storage (UFS) Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for Secure Digital (SD) Device Path
    // Check Messaging Device Path: Secure Digital (SD) Device Path
    //
    else if ((Type == 3) && (SubType == 26)) {
      if (Length  == 5) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid046,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Secure Digital (SD) Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for Bluetooth Device Path
    // Check Messaging Device Path: Bluetooth Device Path
    //
    else if ((Type == 3) && (SubType == 27)) {
      if (Length  == 10) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid047,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Bluetooth Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for WIFI Device Path
    // Check Messaging Device Path: WIFI Device Path
    //
    else if ((Type == 3) && (SubType == 28)) {
      if (Length  == 36) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid048,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - WIFI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for eMMC Device Path
    // Check Messaging Device Path: eMMC Device Path
    //
    else if ((Type == 3) && (SubType == 29)) {
      if (Length  == 5) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid051,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - eMMC (Embedded Multi-Media Card) Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Add a new checkpoint for BlueToothLE Device Path
    // Check Messaging Device Path: BlueToothLE Device Path
    //
    else if ((Type == 3) && (SubType == 30)) {
      BlueToothLE = (BLUETOOTH_LE_DEVICE_PATH *) DevicePath;   	
      if ((Length  == 11) && ((BlueToothLE->LEAddress.Type == 0) || (BlueToothLE->LEAddress.Type == 1))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid052,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - BlueToothLE Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d, Type - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length,
                    (UINTN)BlueToothLE->LEAddress.Type
                    );
    }
    //
    // Add a new checkpoint for DNS Device Path
    // Check Messaging Device Path: DNS Device Path
    //
    else if ((Type == 3) && (SubType == 31)) {
      DNS = (DNS_DEVICE_PATH *) DevicePath;
      if (((Length - 5) % sizeof(EFI_IP_ADDRESS) == 0) && ((DNS->IsIPv6 == 0) || (DNS->IsIPv6 == 1))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid030,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - DNS Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d, IsIPv6 - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length,
                    (UINTN)DNS->IsIPv6
                    );
    }
    //
    // Assertion Point 3.1.2.23
    // Check Messaging Device Path: InfiniBand Device Path
    //
    else if ((Type == 3) && (SubType == 9)) {
      if (Length == 48) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid019,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - InfiniBand Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.24
    // Check Messaging Device Path: UART Device Path
    //
    else if ((Type == 3) && (SubType == 14)) {
      Uart = (UART_DEVICE_PATH *) DevicePath;
      if ((Length == 19) &&
          (Uart->Parity >= 0x00 && Uart->Parity <= 0x05) &&
          (Uart->StopBits >= 0x00 && Uart->StopBits <= 0x03)
          ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid020,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - UART Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    } else if ((Type == 3) && (SubType == 10)) {
      Vendor = (VENDOR_DEVICE_PATH *) DevicePath;
      //
      // Assertion Point 3.1.2.26
      // Check Messaging Device Path: UART Flow Control Messaging Path
      //
      if (SctCompareMem (&Vendor->Guid, &gBlackBoxEfiDevicePathMessagingUartFlowControlGuid, sizeof (EFI_GUID)) == 0) {
        UartFlow = (UART_FLOW_CONTROL_DEVICE_PATH *) DevicePath;
        if ((Length == 24) && 
            (UartFlow->FlowControlMap == 0x0 ||
             UartFlow->FlowControlMap == 0x1 || 
             UartFlow->FlowControlMap == 0x2)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                      StandardLib,
                      AssertionType,
                      gDevicePathBBTestFunctionAssertionGuid022,
                      L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - UART Flow Control Messaging Path",
                      L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                      __FILE__,
                      (UINTN)__LINE__,
                      (UINTN)Type,
                      (UINTN)SubType,
                      (UINTN)Length
                      );
      }
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)	  
      //
      // Assertion Point 3.1.2.27
      // Check Messaging Device Path: Serial Attached SCSI (SAS) Device Path
      //
      else if (SctCompareMem (&Vendor->Guid, &gBlackBoxEfiDevicePathMessagingSASGuid, sizeof (EFI_GUID)) == 0) {
        if (Length == 44) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                      StandardLib,
                      AssertionType,
                      gDevicePathBBTestFunctionAssertionGuid034,
                      L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Serial Attached SCSI (SAS) Device Path",
                      L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                      __FILE__,
                      (UINTN)__LINE__,
                      (UINTN)Type,
                      (UINTN)SubType,
                      (UINTN)Length
                      );
      }
#endif
	  //
      // Assertion Point 3.1.2.25
      // Check Messaging Device Path: Vendor-Defined Device Path
      //
      else {
        if (Length >= 20) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                      StandardLib,
                      AssertionType,
                      gDevicePathBBTestFunctionAssertionGuid021,
                      L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Vendor-Defined Device Path",
                      L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                      __FILE__,
                      (UINTN)__LINE__,
                      (UINTN)Type,
                      (UINTN)SubType,
                      (UINTN)Length
                      );
      }
    }
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)	
    //
    // Assertion Point 3.1.2.28
    // Check Messaging Device Path: iSCSI Device Path
    //
    else if ((Type == 3) && (SubType == 19)) {
      if (Length >= 18) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid035,
                    L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path -  iSCSI Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
#endif	
    //
    // Assertion Point 3.1.2.29
    // Check Media Device Path: Hard Drive Media Device Path
    //
    else if ((Type == 4) && (SubType == 1)) {
      Hd = (HARDDRIVE_DEVICE_PATH *) DevicePath;
      if ((Length == 42) &&
          (Hd->MBRType == 0x01 || Hd->MBRType == 0x02) &&
          (Hd->SignatureType == 0x00 || Hd->SignatureType == 0x01 || Hd->SignatureType == 0x02)
          ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid023,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Hard Drive Media Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.30
    // Check Media Device Path: CD-ROM Media Device Path
    //
    else if ((Type == 4) && (SubType == 2)) {
      if (Length == 24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid024,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - CD-ROM Media Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.31
    // Check Media Device Path: Vendor-Defined Media Device Path
    //
    else if ((Type == 4) && (SubType == 3)) {
      if (Length >= 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid025,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Vendor-Defined Media Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.32
    // Check Media Device Path: File Path Media Device Path
    //
    else if ((Type == 4) && (SubType == 4)) {
      if (Length >= 4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid026,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - File Path Media Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
    //
    // Assertion Point 3.1.2.33
    // Check Media Device Path: Media Protocol Device Path
    //
    else if ((Type == 4) && (SubType == 5)) {
      if (Length == 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid027,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Media Protocol Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)		
    //
    // Add a new CheckPoint for PIWG Firmware Volume which belong to UEFI 2.1
    // Check SATA Device Path
    //
    else if ((Type == 4) && (SubType == 6)) {
      if (Length >=4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid040,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - PIWG Firmware Volume",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }	
    //
    // Add a new CheckPoint for PIWG Firmware File which belong to UEFI 2.1
    // Check SATA Device Path
    //
    else if ((Type == 4) && (SubType == 7)) {
      if (Length >=4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid041,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - PIWG Firmware File",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }		
#endif
    //
    // Add a new CheckPoint for Relative Offset Range
    // Check Relative Offset Range Device Path
    //
    else if ((Type == 4) && (SubType == 8)) {
      if (Length ==24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid049,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Relative Offset Range",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }	
    //
    // Add a new CheckPoint for RAM Disk
    // Check RAM Disk Device Path
    //
    else if ((Type == 4) && (SubType == 9)) {
      if (Length ==38) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid050,
                    L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - RAM Disk",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }		
    //
    // Assertion Point 3.1.2.34
    // Check BIOS Boot Specification Device Path
    //
    else if ((Type == 5) && (SubType == 1)) {
      if (Length >= 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gDevicePathBBTestFunctionAssertionGuid028,
                    L"EFI_DEVICE_PATH_PROTOCOL - BIOS Boot Specification Device Path",
                    L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                    __FILE__,
                    (UINTN)__LINE__,
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    } else {
      StandardLib->RecordMessage (
                    StandardLib,
                    EFI_VERBOSE_LEVEL_QUIET,
                    L"Unknown Node(Type - %d, Subtype - %d, Length - %d)\n",
                    (UINTN)Type,
                    (UINTN)SubType,
                    (UINTN)Length
                    );
    }

    DevicePath = SctNextDevicePathNode (DevicePath);
  }
  //
  // Assertion Point 3.1.2.1
  // Check End of Hardware Device Path: End Entire Device Path
  //
  Type    = (UINT16) SctDevicePathType (DevicePath);
  SubType = (UINT16) SctDevicePathSubType (DevicePath);
  Length  = (UINT16) SctDevicePathNodeLength (DevicePath);

  if ((Type == 0x7F) && (SubType == 0xFF)) {
    if (Length == 4) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gDevicePathBBTestFunctionAssertionGuid029,
                  L"EFI_DEVICE_PATH_PROTOCOL - End of Hardware Device Path - End Entire Device Path",
                  L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  (UINTN)Type,
                  (UINTN)SubType,
                  (UINTN)Length
                  );
  }

  return EFI_SUCCESS;
}
