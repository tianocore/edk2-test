/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PciIoBBTestSupport.h

Abstract:

  Pci Io Protocol test support funcitons head file

--*/
#ifndef _EFI_PCI_IO_BBTEST_SUPPORT_H_
#define _EFI_PCI_IO_BBTEST_SUPPORT_H_

#include <UEFI/Protocol/PciRootBridgeIo.h>

//#define PCI_MAX_CONFIG_OFFSET  0x100

#define ENABLE_BIT      0x01
#define ZERO            0x00
#define STEPBIT         0x03
#define IOBIT           0x01
#define INBIT           0x04
#define OUTBIT          0x08
#define MULTIFUNCBIT    0x80
#define PREFETCHBIT     0x08

#define LASTBUS          0x02
#define REGNUM           0x06

#define OFF_VENDOR_ID    0x00
#define OFF_DEVICE_ID    0x02
#define OFF_HEADERTYPE   0x0e
#define OFF_BASEREG      0x10

#define MASK8BIT        0xFF
#define MASK16BIT       0xFFFF
#define MASK32BIT       0xFFFFFFFF
#define MASK64BIT       0xFFFFFFFFFFFFFFFF

typedef struct {
  EFI_PCI_IO_PROTOCOL        *PciIo;
  EFI_DEVICE_PATH_PROTOCOL   *DevicePath;
  UINT8                      Seg;
  UINT8                      Bus;
  UINT8                      Dev;
  UINT8                      Func;
  UINT64                     BarAddress[REGNUM];
  UINT32                     BarLength[REGNUM];
  UINT8                      BarAttrib[REGNUM];
  BOOLEAN                    BarHasEffect[REGNUM];
  BOOLEAN                    Bridge;
} PCI_IO_PROTOCOL_DEVICE;

typedef struct {
  UINT16   VendorId;
  UINT16   DeviceId;
  UINT16   Command;
  UINT16   Status;
  UINT8    RevisionId;
  UINT8    ClassCode[3];
  UINT8    CacheLineSize;
  UINT8    PrimaryLatencyTimer;
  UINT8    HeaderType;
  UINT8    BIST;
} PCI_COMMON_HEADER;

typedef CHAR16 WIDTHCODE[64];

typedef struct _MEMORY_POOL_MAPPING_LIST {
 struct _MEMORY_POOL_MAPPING_LIST   *Next;
  VOID                              *HostAddress;
  VOID                              *Mapping;
} MEMORY_POOL_MAPPING_LIST;


#define PCIIOPROTOCOLDEVICESIZE (sizeof(PCI_IO_PROTOCOL_DEVICE))
#define PCICOMMONHEADERSIZE      (sizeof(PCI_COMMON_HEADER))
#define MAX_STRING_LEN          256
#define WAIT_TIME               10
#define LONG_WAIT_TIME          30

#define CHECK_TYPE_MEM          0
#define CHECK_TYPE_IO           1

typedef struct {
  EFI_PCI_IO_PROTOCOL                     *PciIo;
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_PCI_IO_PROTOCOL_WIDTH               PciIoWidth;
  UINT8                                   BarIndex;
  UINT64                                  AddressOffset;
  UINT64                                  DestValue;
 }TIMER_EVENT_CONTEXT;

//
//global varibles
//
#define DEPENDECY_DIR_NAME            L"dependency\\PciIoBBTest"
#define PCI_IO_TEST_INI_FILE          L"PciIoBBTest.ini"

extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL      *gRootBridgeIo;

extern PCI_IO_PROTOCOL_DEVICE       *gPciIoDevices;
extern UINTN                        gPciIoDeviceNumber;

extern EFI_DEVICE_PATH_PROTOCOL     *gDevicePath;
extern CHAR16                       *gFilePath;

extern WIDTHCODE                    WidthCode[];
extern WIDTHCODE                    OperationCode[];
extern WIDTHCODE                    AttribOperationCode[];
extern WIDTHCODE                    MemoryTypeCode[];

//
//support funcitons
//

EFI_STATUS
InitializeCaseEnvironment (
  VOID
 );

EFI_STATUS
ParseBar (
  IN PCI_IO_PROTOCOL_DEVICE  *PciIoDevice,
  IN UINT8                   BarIndex
  );

 BOOLEAN
QueryGoOnTesting (
  VOID
  );

EFI_STATUS
GetBarIndex (
  IN UINT8          *Bar
  );

EFI_STATUS
GetSrcBarIndex (
  IN UINT8         *Bar
  );

EFI_STATUS
GetDestBarIndex (
  IN UINT8         *Bar
  );

EFI_STATUS
GetAddressOffset (
  IN UINT64     *Offset
  );

EFI_STATUS
GetSrcAddressOffset (
  IN UINT64    *Offset
  );

EFI_STATUS
GetDestAddressOffset (
  IN UINT64    *Offset
  );

EFI_STATUS
GetAddressLength (
  IN UINT32    *AddressLength
  );

EFI_STATUS
GetPciIoWidth (
  IN EFI_PCI_IO_PROTOCOL_WIDTH   *PciIoWidth
  );

EFI_STATUS
GetTargetValue (
  IN UINT64    *TargetValue
  );

EFI_STATUS
GetAlternateValue (
  IN UINT64     *AlternateValue
  );

EFI_STATUS
GetDataUnits (
  IN UINTN         Length,
  IN UINT8         **DataUnits
  );

EFI_STATUS
GetSystemDevicePathByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **DevicePath
  );

EFI_STATUS
GetBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8              *BarIndex
  );

EFI_STATUS
GetSrcBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8               *SrcBarIndex
  );

EFI_STATUS
GetDestBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8               *DestBarIndex
  );

EFI_STATUS
GetAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *AddressOffset
  );

EFI_STATUS
GetSrcAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *SrcAddressOffset
  );

EFI_STATUS
GetDestAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *DestAddressOffset
  );

EFI_STATUS
GetAddressLengthByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *AddressLength
  );

EFI_STATUS
GetPciIoWidthByFile (
  IN EFI_INI_FILE_HANDLE         FileHandle,
  IN CHAR16                      *SectionName,
  IN UINTN                       Order,
  OUT EFI_PCI_IO_PROTOCOL_WIDTH  *PciIoWidth
  );
EFI_STATUS
GetTargetValueByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *TargetValue
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

BOOLEAN
CheckBarAndRange (
  IN PCI_IO_PROTOCOL_DEVICE   *PciDevice,
  IN UINT8                    CheckType,
  IN UINT8                    BarIndex,
  IN UINT64                   AddressOffset
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
PrintPciIoDevice (
  IN EFI_DEVICE_PATH_PROTOCOL            *DevicePath
  );

PCI_IO_PROTOCOL_DEVICE *
GetPciIoDevice (
  IN  EFI_PCI_IO_PROTOCOL     *PciIo
  );

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

BOOLEAN
IsValidResourceDescrptor (
  VOID              *Resources
  );


BOOLEAN
CompareAcpiResourceDescrptor (
  IN  VOID              *Resource1,
  IN  VOID              *Resource2
  );

UINT64
XToUint64 (
  IN CHAR16  *Str
  );

UINT64
AToUint64 (
  IN CHAR16  *Str
  );

#endif
