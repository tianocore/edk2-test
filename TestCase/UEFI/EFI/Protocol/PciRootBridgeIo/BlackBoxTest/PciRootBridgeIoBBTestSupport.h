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
EventNotifyWriteMem (
  IN EFI_EVENT      Event,
  IN  VOID          *Context
  );

VOID
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
