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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_FOR_TEST_H_
#define _DEVICE_PATH_FOR_TEST_H_

//
// Device Path protocol
//
#ifndef EFI_DEVICE_PATH_PROTOCOL_GUID
#define EFI_DEVICE_PATH_PROTOCOL_GUID \
  { \
    0x9576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b \
  }
#endif

#pragma pack(1)

/**
  This protocol can be used on any device handle to obtain generic path/location
  information concerning the physical device or logical device. If the handle does
  not logically map to a physical device, the handle may not necessarily support
  the device path protocol. The device path describes the location of the device
  the handle is for. The size of the Device Path can be determined from the structures
  that make up the Device Path.
**/
typedef struct {
  UINT8 Type;       ///< 0x01 Hardware Device Path.
                    ///< 0x02 ACPI Device Path.
                    ///< 0x03 Messaging Device Path.
                    ///< 0x04 Media Device Path.
                    ///< 0x05 BIOS Boot Specification Device Path.
                    ///< 0x7F End of Hardware Device Path.

  UINT8 SubType;    ///< Varies by Type
                    ///< 0xFF End Entire Device Path, or
                    ///< 0x01 End This Instance of a Device Path and start a new
                    ///< Device Path.

  UINT8 Length[2];  ///< Specific Device Path data. Type and Sub-Type define
                    ///< type of data. Size of data is included in Length.

} EFI_DEVICE_PATH_PROTOCOL;


#define DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL \
  { \
    0x37499a9d, 0x542f, 0x4c89, {0xa0, 0x26, 0x35, 0xda, 0x14, 0x20, 0x94, 0xe4 } \
  }

#define EFI_SAS_DEVICE_PATH_GUID \
  { \
    0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d } \
  }

#define DEVICE_PATH_MESSAGING_SAS          EFI_SAS_DEVICE_PATH_GUID

#define EFI_PC_ANSI_GUID \
  { \
    0xe0c14753, 0xf9be, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
  }

#define EFI_VT_100_GUID \
  { \
    0xdfa66065, 0xb419, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
  }

#define EFI_VT_100_PLUS_GUID \
  { \
    0x7baec70b, 0x57e0, 0x4c76, {0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43 } \
  }

#define EFI_VT_UTF8_GUID \
  { \
    0xad15a0d6, 0x8bec, 0x4acf, {0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88 } \
  }

#define DEVICE_PATH_MESSAGING_PC_ANSI     EFI_PC_ANSI_GUID
#define DEVICE_PATH_MESSAGING_VT_100      EFI_VT_100_GUID
#define DEVICE_PATH_MESSAGING_VT_100_PLUS EFI_VT_100_PLUS_GUID
#define DEVICE_PATH_MESSAGING_VT_UTF8     EFI_VT_UTF8_GUID

///
/// A new device path node is defined to declare flow control characteristics.
/// UART Flow Control Messaging Device Path
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL GUID.
  ///
  EFI_GUID                        Guid;
  ///
  /// Bitmap of supported flow control types.
  /// Bit 0 set indicates hardware flow control.
  /// Bit 1 set indicates Xon/Xoff flow control.
  /// All other bits are reserved and are clear.
  ///
  UINT32                          FlowControlMap;
} UART_FLOW_CONTROL_DEVICE_PATH;

///
/// Memory Mapped Device Path SubType.
///
#define HW_MEMMAP_DP              0x03

///
/// Memory Mapped Device Path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// EFI_MEMORY_TYPE
  ///
  UINT32                          MemoryType;
  ///
  /// Starting Memory Address.
  ///
  EFI_PHYSICAL_ADDRESS            StartingAddress;
  ///
  /// Ending Memory Address.
  ///
  EFI_PHYSICAL_ADDRESS            EndingAddress;
} MEMMAP_DEVICE_PATH;

///
/// MAC Address Device Path SubType.
///
#define MSG_MAC_ADDR_DP           0x0b
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// The MAC address for a network interface padded with 0s.
  ///
  EFI_MAC_ADDRESS                 MacAddress;
  ///
  /// Network interface type(i.e. 802.3, FDDI).
  ///
  UINT8                           IfType;
} MAC_ADDR_DEVICE_PATH;

///
/// ATAPI Device Path SubType
///
#define MSG_ATAPI_DP              0x01
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Set to zero for primary, or one for secondary.
  ///
  UINT8                           PrimarySecondary;
  ///
  /// Set to zero for master, or one for slave mode.
  ///
  UINT8                           SlaveMaster;
  ///
  /// Logical Unit Number.
  ///
  UINT16                          Lun;
} ATAPI_DEVICE_PATH;

///
/// UART Device Path SubType.
///
#define MSG_UART_DP               0x0e
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Reserved.
  ///
  UINT32                          Reserved;
  ///
  /// The baud rate setting for the UART style device. A value of 0
  /// means that the device's default baud rate will be used.
  ///
  UINT64                          BaudRate;
  ///
  /// The number of data bits for the UART style device. A value
  /// of 0 means that the device's default number of data bits will be used.
  ///
  UINT8                           DataBits;
  ///
  /// The parity setting for the UART style device.
  /// Parity 0x00 - Default Parity.
  /// Parity 0x01 - No Parity.
  /// Parity 0x02 - Even Parity.
  /// Parity 0x03 - Odd Parity.
  /// Parity 0x04 - Mark Parity.
  /// Parity 0x05 - Space Parity.
  ///
  UINT8                           Parity;
  ///
  /// The number of stop bits for the UART style device.
  /// Stop Bits 0x00 - Default Stop Bits.
  /// Stop Bits 0x01 - 1 Stop Bit.
  /// Stop Bits 0x02 - 1.5 Stop Bits.
  /// Stop Bits 0x03 - 2 Stop Bits.
  ///
  UINT8                           StopBits;
} UART_DEVICE_PATH;

///
/// Hardware Vendor Device Path SubType.
///
#define HW_VENDOR_DP              0x04

///
/// The Vendor Device Path allows the creation of vendor-defined Device Paths. A vendor must
/// allocate a Vendor GUID for a Device Path. The Vendor GUID can then be used to define the
/// contents on the n bytes that follow in the Vendor Device Path node.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Vendor-assigned GUID that defines the data that follows.
  ///
  EFI_GUID                        Guid;
  ///
  /// Vendor-defined variable size data.
  ///
} VENDOR_DEVICE_PATH;

///
/// The Media Protocol Device Path is used to denote the protocol that is being
/// used in a device path at the location of the path specified.
/// Many protocols are inherent to the style of device path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// The ID of the protocol.
  ///
  EFI_GUID                        Protocol;
} MEDIA_PROTOCOL_DEVICE_PATH;

//
// Media Device Path
//
#define MEDIA_DEVICE_PATH         0x04

///
/// Media relative offset range device path.
///
#define MEDIA_RELATIVE_OFFSET_RANGE_DP 0x08

///
/// Hard Drive Media Device Path SubType.
///
#define MEDIA_HARDDRIVE_DP        0x01

///
/// The Hard Drive Media Device Path is used to represent a partition on a hard drive.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Describes the entry in a partition table, starting with entry 1.
  /// Partition number zero represents the entire device. Valid
  /// partition numbers for a MBR partition are [1, 4]. Valid
  /// partition numbers for a GPT partition are [1, NumberOfPartitionEntries].
  ///
  UINT32                          PartitionNumber;
  ///
  /// Starting LBA of the partition on the hard drive.
  ///
  UINT64                          PartitionStart;
  ///
  /// Size of the partition in units of Logical Blocks.
  ///
  UINT64                          PartitionSize;
  ///
  /// Signature unique to this partition:
  /// If SignatureType is 0, this field has to be initialized with 16 zeros.
  /// If SignatureType is 1, the MBR signature is stored in the first 4 bytes of this field.
  /// The other 12 bytes are initialized with zeros.
  /// If SignatureType is 2, this field contains a 16 byte signature.
  ///
  UINT8                           Signature[16];
  ///
  /// Partition Format: (Unused values reserved).
  /// 0x01 - PC-AT compatible legacy MBR.
  /// 0x02 - GUID Partition Table.
  ///
  UINT8                           MBRType;
  ///
  /// Type of Disk Signature: (Unused values reserved).
  /// 0x00 - No Disk Signature.
  /// 0x01 - 32-bit signature from address 0x1b8 of the type 0x01 MBR.
  /// 0x02 - GUID signature.
  ///
  UINT8                           SignatureType;
} HARDDRIVE_DEVICE_PATH;

#define NO_DISK_SIGNATURE         0x00
#define SIGNATURE_TYPE_MBR        0x01
#define SIGNATURE_TYPE_GUID       0x02

///
/// VLAN Device Path SubType.
///
#define MSG_VLAN_DP               0x14
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// VLAN identifier (0-4094).
  ///
  UINT16                          VlanId;
} VLAN_DEVICE_PATH;

#define MSG_IPV6_DP               0x0d
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  EFI_IPv6_ADDRESS                LocalIpAddress;
  EFI_IPv6_ADDRESS                RemoteIpAddress;
  UINT16                          LocalPort;
  UINT16                          RemotePort;
  UINT16                          Protocol;
  UINT8                           IPAddressOrigin;
  UINT8                           PrefixLength;
  EFI_IPv6_ADDRESS                GatewayIPAddress;
} IPV6_DEVICE_PATH;

#define MSG_IPV4_DP               0x0c
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  EFI_IPv4_ADDRESS                LocalIpAddress;
  EFI_IPv4_ADDRESS                RemoteIpAddress;
  UINT16                          LocalPort;
  UINT16                          RemotePort;
  UINT16                          Protocol;
  BOOLEAN                         StaticIpAddress;
  EFI_IPv4_ADDRESS                GatewayIPAddress;
  EFI_IPv4_ADDRESS                SubnetMask;
} IPV4_DEVICE_PATH;

///
/// ACPI Device Path SubType.
///
#define ACPI_DP                   0x01
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Device's PnP hardware ID stored in a numeric 32-bit
  /// compressed EISA-type ID. This value must match the
  /// corresponding _HID in the ACPI name space.
  ///
  UINT32                          HID;
  ///
  /// Unique ID that is required by ACPI if two devices have the
  /// same _HID. This value must also match the corresponding
  /// _UID/_HID pair in the ACPI name space. Only the 32-bit
  /// numeric value type of _UID is supported. Thus, strings must
  /// not be used for the _UID in the ACPI name space.
  ///
  UINT32                          UID;
} ACPI_HID_DEVICE_PATH;

///
/// Expanded ACPI Device Path SubType.
///
#define ACPI_EXTENDED_DP          0x02
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Device's PnP hardware ID stored in a numeric 32-bit
  /// compressed EISA-type ID. This value must match the
  /// corresponding _HID in the ACPI name space.
  ///
  UINT32                          HID;
  ///
  /// Unique ID that is required by ACPI if two devices have the
  /// same _HID. This value must also match the corresponding
  /// _UID/_HID pair in the ACPI name space.
  ///
  UINT32                          UID;
  ///
  /// Device's compatible PnP hardware ID stored in a numeric
  /// 32-bit compressed EISA-type ID. This value must match at
  /// least one of the compatible device IDs returned by the
  /// corresponding _CID in the ACPI name space.
  ///
  UINT32                          CID;
  ///
  /// Optional variable length _HIDSTR.
  /// Optional variable length _UIDSTR.
  /// Optional variable length _CIDSTR.
  ///
} ACPI_EXTENDED_HID_DEVICE_PATH;

//
//  EISA ID Macro
//  EISA ID Definition 32-bits
//   bits[15:0] - three character compressed ASCII EISA ID.
//   bits[31:16] - binary number
//    Compressed ASCII is 5 bits per character 0b00001 = 'A' 0b11010 = 'Z'
//
#define PNP_EISA_ID_CONST         0x41d0
#define EISA_ID(_Name, _Num)      ((UINT32)((_Name) | (_Num) << 16))
#define EISA_PNP_ID(_PNPId)       (EISA_ID(PNP_EISA_ID_CONST, (_PNPId)))
#define EFI_PNP_ID(_PNPId)        (EISA_ID(PNP_EISA_ID_CONST, (_PNPId)))

///
/// ACPI _ADR Device Path SubType.
///
#define ACPI_ADR_DP               0x03

///
/// The _ADR device path is used to contain video output device attributes to support the Graphics
/// Output Protocol. The device path can contain multiple _ADR entries if multiple video output
/// devices are displaying the same output.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// _ADR value. For video output devices the value of this
  /// field comes from Table B-2 of the ACPI 3.0 specification. At
  /// least one _ADR value is required.
  ///
  UINT32                          ADR;
  //
  // This device path may optionally contain more than one _ADR entry.
  //
} ACPI_ADR_DEVICE_PATH;

///
/// SCSI Device Path SubType.
///
#define MSG_SCSI_DP               0x02
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Target ID on the SCSI bus (PUN).
  ///
  UINT16                          Pun;
  ///
  /// Logical Unit Number (LUN).
  ///
  UINT16                          Lun;
} SCSI_DEVICE_PATH;

///
/// 1394 Device Path SubType
///
#define MSG_1394_DP               0x04
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Reserved for the future.
  ///
  UINT32                          Reserved;
  ///
  /// 1394 Global Unique ID (GUID).
  ///
  UINT64                          Guid;
} F1394_DEVICE_PATH;

///
/// USB Device Path SubType.
///
#define MSG_USB_DP                0x05
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// USB Parent Port Number.
  ///
  UINT8                         ParentPortNumber;
  ///
  /// USB Interface Number.
  ///
  UINT8                         InterfaceNumber;
} USB_DEVICE_PATH;

///
/// USB Class Device Path SubType.
///
#define MSG_USB_CLASS_DP          0x0f
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// Vendor ID assigned by USB-IF. A value of 0xFFFF will
  /// match any Vendor ID.
  ///
  UINT16                        VendorId;
  ///
  /// Product ID assigned by USB-IF. A value of 0xFFFF will
  /// match any Product ID.
  ///
  UINT16                        ProductId;
  ///
  /// The class code assigned by the USB-IF. A value of 0xFF
  /// will match any class code.
  ///
  UINT8                         DeviceClass;
  ///
  /// The subclass code assigned by the USB-IF. A value of
  /// 0xFF will match any subclass code.
  ///
  UINT8                         DeviceSubClass;
  ///
  /// The protocol code assigned by the USB-IF. A value of
  /// 0xFF will match any protocol code.
  ///
  UINT8                         DeviceProtocol;
} USB_CLASS_DEVICE_PATH;

///
/// Fibre Channel SubType.
///
#define MSG_FIBRECHANNEL_DP       0x03
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Reserved for the future.
  ///
  UINT32                          Reserved;
  ///
  /// Fibre Channel World Wide Number.
  ///
  UINT64                          WWN;
  ///
  /// Fibre Channel Logical Unit Number.
  ///
  UINT64                          Lun;
} FIBRECHANNEL_DEVICE_PATH;

///
/// I2O Device Path SubType.
///
#define MSG_I2O_DP                0x06
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Target ID (TID) for a device.
  ///
  UINT32                          Tid;
} I2O_DEVICE_PATH;

///
/// InfiniBand Device Path SubType.
///
#define MSG_INFINIBAND_DP         0x09
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Flags to help identify/manage InfiniBand device path elements:
  /// Bit 0 - IOC/Service (0b = IOC, 1b = Service).
  /// Bit 1 - Extend Boot Environment.
  /// Bit 2 - Console Protocol.
  /// Bit 3 - Storage Protocol.
  /// Bit 4 - Network Protocol.
  /// All other bits are reserved.
  ///
  UINT32                          ResourceFlags;
  ///
  /// 128-bit Global Identifier for remote fabric port.
  ///
  UINT8                           PortGid[16];
  ///
  /// 64-bit unique identifier to remote IOC or server process.
  /// Interpretation of field specified by Resource Flags (bit 0).
  ///
  UINT64                          ServiceId;
  ///
  /// 64-bit persistent ID of remote IOC port.
  ///
  UINT64                          TargetPortId;
  ///
  /// 64-bit persistent ID of remote device.
  ///
  UINT64                          DeviceId;
} INFINIBAND_DEVICE_PATH;

///
/// Device Logical Unit SubType.
///
#define MSG_DEVICE_LOGICAL_UNIT_DP  0x11
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// Logical Unit Number for the interface.
  ///
  UINT8                         Lun;
} DEVICE_LOGICAL_UNIT_DEVICE_PATH;

///
/// CD-ROM Media Device Path SubType.
///
#define MEDIA_CDROM_DP            0x02

///
/// The CD-ROM Media Device Path is used to define a system partition that exists on a CD-ROM.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Boot Entry number from the Boot Catalog. The Initial/Default entry is defined as zero.
  ///
  UINT32                          BootEntry;
  ///
  /// Starting RBA of the partition on the medium. CD-ROMs use Relative logical Block Addressing.
  ///
  UINT64                          PartitionStart;
  ///
  /// Size of the partition in units of Blocks, also called Sectors.
  ///
  UINT64                          PartitionSize;
} CDROM_DEVICE_PATH;

///
/// BIOS Boot Specification Device Path SubType.
///
#define BBS_BBS_DP                0x01
///
/// This Device Path is used to describe the booting of non-EFI-aware operating systems.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Device Type as defined by the BIOS Boot Specification.
  ///
  UINT16                          DeviceType;
  ///
  /// Status Flags as defined by the BIOS Boot Specification.
  ///
  UINT16                          StatusFlag;
  ///
  /// Null-terminated ASCII string that describes the boot device to a user.
  ///
  CHAR8                           String[1];
} BBS_BBS_DEVICE_PATH;

//
// DeviceType definitions - from BBS specification
//
#define BBS_TYPE_FLOPPY           0x01
#define BBS_TYPE_HARDDRIVE        0x02
#define BBS_TYPE_CDROM            0x03
#define BBS_TYPE_PCMCIA           0x04
#define BBS_TYPE_USB              0x05
#define BBS_TYPE_EMBEDDED_NETWORK 0x06
#define BBS_TYPE_BEV              0x80
#define BBS_TYPE_UNKNOWN          0xFF

///
/// File Path Media Device Path SubType
///
#define MEDIA_FILEPATH_DP         0x04
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// A NULL-terminated Path string including directory and file names.
  ///
  CHAR16                          PathName[1];
} FILEPATH_DEVICE_PATH;

///
/// Serial Attached SCSI (SAS) Device Path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// DEVICE_PATH_MESSAGING_SAS GUID.
  ///
  EFI_GUID                        Guid;
  ///
  /// Reserved for future use.
  ///
  UINT32                          Reserved;
  ///
  /// SAS Address for Serial Attached SCSI Target.
  ///
  UINT64                          SasAddress;
  ///
  /// SAS Logical Unit Number.
  ///
  UINT64                          Lun;
  ///
  /// More Information about the device and its interconnect.
  ///
  UINT16                          DeviceTopology;
  ///
  /// Relative Target Port (RTP).
  ///
  UINT16                          RelativeTargetPort;
} SAS_DEVICE_PATH;

///
/// PCI Device Path SubType.
///
#define HW_PCI_DP                 0x01

///
/// PCI Device Path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// PCI Function Number.
  ///
  UINT8                           Function;
  ///
  /// PCI Device Number.
  ///
  UINT8                           Device;
} PCI_DEVICE_PATH;

///
/// PCCARD Device Path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Function Number (0 = First Function).
  ///
  UINT8                           FunctionNumber;
} PCCARD_DEVICE_PATH;

///
/// Controller Device Path SubType.
///
#define HW_CONTROLLER_DP          0x05

///
/// Controller Device Path.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Controller number.
  ///
  UINT32                          ControllerNumber;
} CONTROLLER_DEVICE_PATH;

#pragma pack()

#define END_DEVICE_PATH_TYPE                 0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE       0xFF
#define END_INSTANCE_DEVICE_PATH_SUBTYPE     0x01

extern EFI_GUID gBlackBoxEfiDevicePathProtocolGuid;
extern EFI_GUID gBlackBoxEfiDevicePathUtilitiesProtocolGuid;

extern EFI_GUID gBlackBoxEfiPcAnsiGuid;
extern EFI_GUID gBlackBoxEfiVT100Guid;
extern EFI_GUID gBlackBoxEfiVT100PlusGuid;
extern EFI_GUID gBlackBoxEfiVTUTF8Guid;

#endif /* _DEVICE_PATH_FOR_TEST_H_ */
