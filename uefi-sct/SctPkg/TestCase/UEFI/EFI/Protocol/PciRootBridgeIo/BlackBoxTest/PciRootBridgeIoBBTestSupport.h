/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PciRootBridgeIoBBTestSupport.h

Abstract:

  support head file for for Pci Root Bridge Io Protocol BB Test

--*/

#ifndef _PCI_ROOT_BRIDGE_IO_BBTEST_SUPPORT_H_
#define _PCI_ROOT_BRIDGE_IO_BBTEST_SUPPORT_H_

#define MASK8BIT        0xFF
#define MASK16BIT       0xFFFF
#define MASK32BIT       0xFFFFFFFF
#define MASK64BIT       0xFFFFFFFFFFFFFFFF

typedef struct {
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINT8                                 PriBus;
  UINT8                                 SubBus;
  UINT32                                IOBase;
  UINT32                                IOLength;
  UINT32                                Mem32Base;
  UINT32                                Mem32Length;
  UINT32                                PreMem32Base;
  UINT32                                PreMem32Length;
  UINT64                                Mem64Base;
  UINT64                                Mem64Length;
  UINT64                                PreMem64Base;
  UINT64                                PreMem64Length;
} EFI_PCI_ROOT_BRIDGE_IO_DEVICE;

typedef CHAR16 WIDTHCODE[64];

typedef struct _MEMORY_POOL_MAPPING_LIST {
 struct _MEMORY_POOL_MAPPING_LIST   *Next;
  VOID                              *HostAddress;
  VOID                              *Mapping;
} MEMORY_POOL_MAPPING_LIST;

#define MAX_STRING_LEN          256
#define WAIT_TIME               10
#define LONG_WAIT_TIME          30

#define CHECK_TYPE_MEM          0
#define CHECK_TYPE_IO           1

typedef struct {
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINT64                                  Address;
  UINT64                                  DestValue;
 }TIMER_EVENT_CONTEXT;

//
//global varibles
//
#define DEPENDECY_DIR_NAME                  L"Dependency\\PciRootBridgeIoBbTest"
#define PCI_ROOT_BRIDGE_IO_TEST_INI_FILE    L"PciRootBridgeIoBbTest.ini"

extern EFI_PCI_ROOT_BRIDGE_IO_DEVICE        *gRootBridgeIoDevices;
extern UINTN                                gRootBridgeIoDevNumber;
extern EFI_DEVICE_PATH_PROTOCOL             *gDevicePath;
extern CHAR16                               *gFilePath;

extern WIDTHCODE                            WidthCode[];
extern WIDTHCODE                            MemoryTypeCode[];

//
//support funcitons
//

EFI_STATUS
GetValidMemoryAddress (
  IN EFI_PCI_ROOT_BRIDGE_IO_DEVICE *RBDev,
  IN UINT64                        *Address
  );

EFI_STATUS
GetSomeMemeryResource (
  IN EFI_PCI_ROOT_BRIDGE_IO_DEVICE *RBDev,
  IN UINT64                        *Address,
  IN UINT64                        *Length
  );

EFI_STATUS
GetInValidMemoryAddress (
  IN EFI_PCI_ROOT_BRIDGE_IO_DEVICE *RBDev,
  IN UINT64                        *Address
  );


EFI_STATUS
InitializeCaseEnvironment (
  VOID
 );

EFI_STATUS
GetRootBridgeIoDeviceInfo (
  IN EFI_PCI_ROOT_BRIDGE_IO_DEVICE *RBDev
  );

BOOLEAN
QueryGoOnTesting (
  VOID
  );

EFI_STATUS
GetAddress (
  IN UINT64    *Offset
  );

EFI_STATUS
GetTargetValue (
  IN UINT64    *TargetValue
  );

EFI_STATUS
GetAlternateValue (
  IN UINT64    *AlternateValue
  );

EFI_STATUS
GetDataUnits (
  IN UINTN         Length,
  IN UINT8         **DataUnits
  );

EFI_STATUS
GetAddressLength (
  IN UINT32    *AddressLength
  );

EFI_STATUS
GetRootBridgeIoWidth (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   *RootBridgeIoWidth
  );

EFI_STATUS
GetSystemDevicePathByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **DevicePath
  );

EFI_STATUS
GetAddressByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *Address
  );


EFI_STATUS
GetDataUnitsByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  UINTN                   Length,
  OUT UINT8               **DataUnits
  );

EFI_STATUS
GetAddressLengthByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *AddressLength
  );


EFI_STATUS
GetRootBridgeIoWidthByFile (
  IN EFI_INI_FILE_HANDLE                      FileHandle,
  IN CHAR16                                   *SectionName,
  IN UINTN                                    Order,
  OUT EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   *RootBridgeIoWidth
  );

EFI_STATUS
GetTargetValueByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *TargetValue
  );

EFI_STATUS
GetAlternateValueByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *AlternateValue
  );

VOID
EFIAPI
EventNotifyWriteMem (
  IN EFI_EVENT      Event,
  IN  VOID          *Context
  );

VOID
EFIAPI
EventNotifyWriteIo (
  IN EFI_EVENT      Event,
  IN  VOID          *Context
  );

EFI_STATUS
ConvertStringToHex (
  IN CHAR16             *SrcBuffer,
  IN UINT32             Length,
  OUT UINT8             **RetBuffer
  );

EFI_STATUS
GetUserInputOrTimeOut (
  OUT CHAR16                       **Buffer,
  IN  UINTN                        Seconds
  );

EFI_STATUS
PrintRootBridgeDevPath (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  );

EFI_PCI_ROOT_BRIDGE_IO_DEVICE *
GetRootBridgeIoDevice (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo
  );

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE        ImageHandle
  );

BOOLEAN
IsValidResourceDescrptor (
  VOID                  *Resources
  );


BOOLEAN
CompareAcpiResourceDescrptor (
  IN  VOID              *Resource1,
  IN  VOID              *Resource2
  );

UINT64
XToUint64 (
  IN CHAR16  *str
  );

UINT64
AToUint64 (
  IN CHAR16  *str
  );

#endif
