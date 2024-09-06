# Appendix A - Format of Test Profiles

## EFI Requirements Test Profile
```sh
**File Path: SCT\Dependency\EfiCompliantBBTest\EfiCompliant.Ini**

[Platform Specific]
ConsoleDevices = <yes: if this platform includes console devices>
GraphicalConsoleDevices = <yes: if this platform includes graphical console devices>
PointerDevices = <yes: if this platform includes a pointer device as part of its console support>
BootFromDiskDevices = <yes: if this platform supports to boot from a disk device>
BootFromNetworkDevices = <yes: if this platform supports to boot from a network device>
UartDevices = <yes: if this platform includes a byte-stream device such as a UART>
PciBusSupport = <yes: if this platform includes PCI bus support>
UsbBusSupport = <yes: if this platform includes USB bus support>
ScsiPassThru = <yes: if this platform includes an I/O system that uses SCSI command packets>
DebugSupport = <yes: if this platform supports debugging capabilities>
PlatformDriverOverride = <yes: includes the ability to override the default driver>
```

## EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL Test Profile
```sh
[PollMem_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The memory address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
TargetValue = <The target value to be set and polled in destination address, in hex format>
AlternateValue = <The alternate value to be set in destination address, in hex format>

[PollIo_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The Io address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
TargetValue = <The target value to be set and polled in destination address, in hex format>
AlternateValue = <The alternate value to be set in destination address, in hex format>

[MemRead_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The memory address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[MemWrite_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The memory address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[IoRead_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The Io address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[IoWrite_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The Io address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[PciRead_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The PCI address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[PciWrite_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The PCI address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[CopyMem_Func]
DevicePath = <The PCI root bridge device path string>
Address = <The memory address controlled by this root bridge>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH>
Length = <The tested address length, in hex format>
DataUnits = <The data unit to be written in to tested area, this item can be **NULL**>

[MemRead_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[MemWrite_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[IoRead_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[IoWrite_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[PciRead_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[PciWrite_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>

[CopyMem_Conf]
DevicePath = <The PCI root bridge device path string>
RootBridgeIoWidth = <The EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH invalid for this system>
```

## EFI_PCI_IO_PROTOCOL Test Profile

```sh
[PollMem_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
TargetValue = <The target value to Poll in destination address, in hex format>
AlternateValue = <The alternate value set in destination address, in hex format>

[PollIo_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
TargetValue = <The target value to Poll in destination address, in hex format>
AlternateValue = <The alternate value set in destination address, in hex format>

[MemRead_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[MemWrite_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[IoRead_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[IoWrite_Func]
DevicePath = <The Pci Device Path String>
BarIndex = <The BAR Index valid value is 0-5>
AddressOffset = <The Address offset in this BAR, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[PciRead_Func]
DevicePath = <The Pci Device Path String>
AddressOffset = <The Address offset in configuration space for this device, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[PciWrite_Func]
DevicePath = <The Pci Device Path String>
AddressOffset = <The Address offset in configuration space for this device, in hex format>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the destination address, can be **NULL**>

[CopyMem_Func]
DevicePath = <The Pci Device Path String>
SrcBarIndex = <Source BAR index valid value is 0-5>
DestBarIndex = <Destination BAR index valid value is 0-5>
SrcAddressOffset = <The address offset in source BAR resource>
DestAddressOffset = <The address offset in destination BAR resource>
Length = <The Address length to be tested, in hex format>
PciIoWidth = <The EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint8>
DatUnits = <The data units to be write into the source address, can be **NULL**>

[PollMem_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[PollIo_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[MemRead_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[MemWrite_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[IoRead_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[IoWrite_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[PciRead_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[PciWrite_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>

[CopyMem_Conf]
DevicePath = <The Pci Device Path String>
PciIoWidth = <The invalid EFI_PCI_IO_PROTOCOL_WIDTH. For example EfiPciIoWidthUint64 on IA32 platform>
```

## EFI_DEVICE_IO_PROTOCOL Test Profile
```sh
[MemRead_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Memory address in this Device>
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>

[MemWrite_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Memory address in this Device>
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>

[IoRead_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Io address in this Device>
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>

[IoWrite_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Io address in this Device>
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>

[PciRead_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The PCI address>
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>
DataUnits = <The data for this PCI address range>

[PciWrite_Func]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The PCI address >
ValidEfiIoWidth = <The valid EFI_IO_WIDTH value>
Length = <The Data length to be tested>
DataUnits = <The data to be written for this PCI address range>

[MemRead_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Memory address in this device>
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[MemWrite_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Memory address in this device>
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[IoRead_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Io address in this device>
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[IoWrite_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Io address in this device>
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[PciRead_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Valid PCI address >
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[PciWrite_Conf]
DevicePath = <The Device IO Protocol instance device path>
ValidBaseAddress = <The Valid PCI address >
InvalidEfiIoWidth = <The EFI_IO_WIDTH invalid for this system>

[AllocateBuffer_Conf]
DevicePath = <The Device IO Protocol instance device path>
InvalidBaseAddress= <The memory address invalid for this system>

[PciDevicePath_Conf]
DevicePath = <The Device IO Protocol instance device path>
InvalidBaseAddress= <The PCI address invalid for this system>
```
