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

  PciIoBBTestSupport.c

Abstract:

  Pci Io Protocol test support funcitons source file

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"
#include <IndustryStandard/Acpi.h>

//
//global varibles.
//

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gRootBridgeIo      = NULL;
PCI_IO_PROTOCOL_DEVICE          *gPciIoDevices      = NULL;
UINTN                           gPciIoDeviceNumber  = 0;
EFI_DEVICE_PATH_PROTOCOL        *gDevicePath        = NULL;
CHAR16                          *gFilePath          = NULL;
STATIC  BOOLEAN                 Initialized         = FALSE;
//
//WidthCode String
//
WIDTHCODE  WidthCode[]  = {
  L"EfiPciIoWidthUint8",
  L"EfiPciIoWidthUint16",
  L"EfiPciIoWidthUint32",
  L"EfiPciIoWidthUint64",
  L"EfiPciIoWidthFifoUint8",
  L"EfiPciIoWidthFifoUint16",
  L"EfiPciIoWidthFifoUint32",
  L"EfiPciIoWidthFifoUint64",
  L"EfiPciIoWidthFillUint8",
  L"EfiPciIoWidthFillUint16",
  L"EfiPciIoWidthFillUint32",
  L"EfiPciIoWidthFillUint64",
  L"EfiPciIoWidthMaximum"
};

//
//OperationCode String
//
WIDTHCODE OperationCode[] = {
  L"EfiPciIoOperationBusMasterRead",
  L"EfiPciIoOperationBusMasterWrite",
  L"EfiPciIoOperationBusMasterCommonBuffer",
  L"EfiPciIoOperationMaximum"
};

//
//AttributeOperationCode String
//
WIDTHCODE AttribOperationCode[] = {
  L"EfiPciIoAttributeOperationGet",
  L"EfiPciIoAttributeOperationSet",
  L"EfiPciIoAttributeOperationEnable",
  L"EfiPciIoAttributeOperationDisable",
  L"EfiPciIoAttributeOperationSupported",
  L"EfiPciIoAttributeOperationMaximum"
};

//
//MemoryTypeCode String
//
WIDTHCODE MemoryTypeCode[] = {
  L"EfiReservedMemoryType",
  L"EfiLoaderCode",
  L"EfiLoaderData",
  L"EfiBootServicesCode",
  L"EfiBootServicesData",
  L"EfiRuntimeServicesCode",
  L"EfiRuntimeServicesData",
  L"EfiConventionalMemory",
  L"EfiUnusableMemory",
  L"EfiACPIReclaimMemory",
  L"EfiACPIMemoryNVS",
  L"EfiMemoryMappedIO",
  L"EfiMemoryMappedIOPortSpace",
  L"EfiPalCode",
  L"EfiPreDxeAllocation",
  L"EfiMaxMemoryType"
};

//
//internal support functions
//

/*
 *  Print the Pci Device Path
 *  @param PciIo the EFI_PCI_IO_PROTOCOL instance pointer
 *  @return EFI_SUCCESS the device path string was printed successfully
 */
EFI_STATUS
PrintPciIoDevice (
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
{
  CHAR16                      *DevicePathStr;

  if (DevicePath == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //print the device path.
  //

  gtST->ConOut->OutputString (gtST->ConOut, L"This Pci Device's Device Path:\r\n");
  gtST->ConOut->OutputString (gtST->ConOut, DevicePathStr);
  gtST->ConOut->OutputString (gtST->ConOut, L"\r\n");
  gtBS->FreePool (DevicePathStr);

  return EFI_SUCCESS;
}

/*
 *  get the if user want to go on testing.
 *  @return FALSE user don't want to go on  testing.
 *  @return TRUE  user wants to go on testing.
 */
BOOLEAN
QueryGoOnTesting (
  VOID
  )
{
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;
  EFI_STATUS    Status;

  //
  //query user if go on testing.
  //
  InputBuffer = NULL;
  TempBuffer  = NULL;
  TempBuffer = SctPoolPrint (L"go on testing (Y/N)? please reply in %ds\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return FALSE;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);
  //
  //get user response.
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );
  if (EFI_ERROR(Status) || InputBuffer == NULL) {
    return FALSE;
  }

  if (SctStrLen (InputBuffer) == 0) {
    gtBS->FreePool (InputBuffer);
    return FALSE;
  }
  //
  //compare user responsed char.
  //
  if (SctMetaiMatch (InputBuffer, L"y")) {
    gtBS->FreePool (InputBuffer);
    return TRUE;
  } else {
    gtBS->FreePool (InputBuffer);
    return FALSE;
  }
}

/**
 *  get the BarIndex inputed by user.
 *  @param Bar the Bar Index returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetBarIndex (
  IN UINT8    *Bar
  )
{
  EFI_STATUS    Status;
  UINT8         BarIndex;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  BarIndex    = 0;
  InputBuffer = NULL;
  TempBuffer  = NULL;
  TempBuffer = SctPoolPrint (L"Please input the BarIndex (0-5) in %ds\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BarIndex = (UINT8)AToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Bar = BarIndex;
  return EFI_SUCCESS;
}

/**
 *  get the SrcBarIndex inputed by user.
 *  @param Bar the Src Bar Index returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetSrcBarIndex (
  IN UINT8    *Bar
  )
{
  EFI_STATUS    Status;
  UINT8         SrcBarIndex;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  SrcBarIndex    = 0;
  InputBuffer = NULL;
  TempBuffer  = NULL;
  TempBuffer = SctPoolPrint (L"Please input the Src Bar Index (0-5) in %ds\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);
  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  SrcBarIndex = (UINT8)AToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Bar = SrcBarIndex;
  return EFI_SUCCESS;
}

/**
 *  get the DestBarIndex inputed by user.
 *  @param Bar the Dest Bar Index returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetDestBarIndex (
  IN UINT8         *Bar
  )
{
  EFI_STATUS    Status;
  UINT8         DestBarIndex;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  DestBarIndex  = 0;
  InputBuffer   = NULL;
  TempBuffer    = NULL;
  TempBuffer = SctPoolPrint (L"Please input the Dest Bar Index (0-5) in %ds\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);
  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  DestBarIndex = (UINT8)AToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Bar = DestBarIndex;

  return EFI_SUCCESS;
}

/**
 *  get the address offset inputed by user.
 *  @param Offset the Address Offset returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetAddressOffset (
  IN UINT64    *Offset
  )
{
  EFI_STATUS    Status;
  UINT64        AddressOffset;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  AddressOffset   = 0;
  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Address Offset(Hex) in %ds.\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  AddressOffset = (UINT64)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Offset = AddressOffset;

  return EFI_SUCCESS;
}


/**
 *  get the Src address offset inputed by user.
 *  @param Offset the Src Address Offset returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetSrcAddressOffset (
  IN UINT64    *Offset
  )
{
  EFI_STATUS    Status;
  UINT64        AddressOffset;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  AddressOffset   = 0;
  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Src Address Offset(Hex) in %ds.\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  AddressOffset = (UINT64)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Offset = AddressOffset;

  return EFI_SUCCESS;
}


/**
 *  get the Dest address offset inputed by user.
 *  @param Offset the Dest Address Offset returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetDestAddressOffset (
  IN UINT64    *Offset
  )
{
  EFI_STATUS    Status;
  UINT64        AddressOffset;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  AddressOffset   = 0;
  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Dest Address Offset(Hex) in %ds.\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  AddressOffset = (UINT64)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);
  *Offset = AddressOffset;

  return EFI_SUCCESS;
}


/**
 *  get the Target Value inputed by user.
 *  @param TargetValue the Target Value returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetTargetValue (
  IN UINT64    *TargetValue
  )
{
  EFI_STATUS    Status;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Target Value(Hex) in %ds.\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *TargetValue = (UINT64)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);

  return EFI_SUCCESS;
}

/**
 *  get the Data uints inputed by user.
 *  @param Length the Data length.
 *  @param DataUnits the data Units returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetDataUnits (
  IN UINTN         Length,
  IN UINT8         **DataUnits
  )
{
  EFI_STATUS    Status;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;
  UINT8         *ReturnBuffer;

  InputBuffer = NULL;
  TempBuffer  = NULL;
  TempBuffer = SctPoolPrint (L"Please input the DataUnits(Hex) in %ds\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (InputBuffer) == 0) {
    return EFI_NOT_FOUND;
  }

  Status = ConvertStringToHex (
             InputBuffer,
             (UINT32)Length,
             &ReturnBuffer
             );

  gtBS->FreePool (InputBuffer);

  if (EFI_ERROR(Status)) {
    return Status;
  }
  *DataUnits = ReturnBuffer;

  return EFI_SUCCESS;
}

/**
 *  get the Address Length inputed by user.
 *  @param AddressLength the Target Value returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetAddressLength (
  IN UINT32    *AddressLength
  )
{
  EFI_STATUS    Status;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Address Length (Hex) in %ds.\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  *AddressLength = (UINT32)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);

  return EFI_SUCCESS;
}

/**
 *  get the Alternate Value inputed by user.
 *  @param AlternateValue the Alternate Value returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetAlternateValue (
  IN UINT64     *AlternateValue
  )
{
  EFI_STATUS    Status;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  InputBuffer     = NULL;
  TempBuffer      = NULL;

  TempBuffer = SctPoolPrint (L"Please input the Alternate Value(Hex) in %ds.\r\n", LONG_WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             LONG_WAIT_TIME
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *AlternateValue = (UINT64)XToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);

  return EFI_SUCCESS;
}

/**
 *  get thePci Io Width inputed by user.
 *  @param PcIoWidth the Pci Io Width returned by this function.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetPciIoWidth (
  IN EFI_PCI_IO_PROTOCOL_WIDTH             *PciIoWidth
  )
{
  EFI_STATUS    Status;
  UINT32        Width;
  CHAR16        *InputBuffer;
  CHAR16        *TempBuffer;

  InputBuffer = NULL;
  TempBuffer  = NULL;
  TempBuffer = SctPoolPrint (L"Please input the Width (8/16/32/64)bits in %ds\r\n", WAIT_TIME);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  gtST->ConOut->OutputString (gtST->ConOut, TempBuffer);
  gtBS->FreePool (TempBuffer);

  //
  //get user response
  //
  Status = GetUserInputOrTimeOut (
             &InputBuffer,
             WAIT_TIME
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  Width = (UINT32)AToUint64 (InputBuffer);
  gtBS->FreePool (InputBuffer);

  switch (Width) {
    case 8:
      *PciIoWidth = EfiPciIoWidthUint8;
      break;
    case 16:
      *PciIoWidth = EfiPciIoWidthUint16;
      break;
    case 32:
      *PciIoWidth = EfiPciIoWidthUint32;
      break;
    case 64:
      *PciIoWidth = EfiPciIoWidthUint64;
      break;
    default:
      return EFI_ABORTED;
      break;
  }

  return EFI_SUCCESS;
}

/**
 *  get the device path from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param DevicePath the returned devicepath string.
 *  @return EFI_SUCCESS the devicepath was get successfully.
 */
EFI_STATUS
GetSystemDevicePathByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **DevicePath
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  CHAR16          *TempStr;

  if (SectionName == NULL || DevicePath == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DevicePath",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  TempStr = NULL;
  TempStr = SctStrDuplicate (Buffer);
  if (TempStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  *DevicePath = TempStr;

  return EFI_SUCCESS;
}

/**
 *  get the Bar Index from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param BarIndex the returned Bar Index.
 *  @return EFI_SUCCESS the Bar Index was get successfully.
 */
EFI_STATUS
GetBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8               *BarIndex
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || BarIndex == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"BarIndex",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *BarIndex = (UINT8)AToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Src Bar Index from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param SrcBarIndex the returned Bar Index.
 *  @return EFI_SUCCESS the Src Bar Index was get successfully.
 */
EFI_STATUS
GetSrcBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8               *SrcBarIndex
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || SrcBarIndex == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"SrcBarIndex",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *SrcBarIndex = (UINT8)AToUint64 (Buffer);
  return EFI_SUCCESS;
}


/**
 *  get the Dest Bar Index from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param DestBarIndex the returned Bar Index.
 *  @return EFI_SUCCESS the Dest Bar Index was get successfully.
 */
EFI_STATUS
GetDestBarIndexByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT8               *DestBarIndex
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || DestBarIndex == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DestBarIndex",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *DestBarIndex = (UINT8)AToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Address Offset from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param AddressOffset the returned Address Offset.
 *  @return EFI_SUCCESS the Address Offset was get successfully.
 */
EFI_STATUS
GetAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *AddressOffset
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || AddressOffset == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"AddressOffset",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *AddressOffset = (UINT64)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Src Address Offset from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param SrcAddressOffset the returned Src Address Offset.
 *  @return EFI_SUCCESS the Src Address Offset was get successfully.
 */
EFI_STATUS
GetSrcAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *SrcAddressOffset
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || SrcAddressOffset == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"SrcAddressOffset",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *SrcAddressOffset = (UINT64)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Dest Address Offset from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param DestAddressOffset the returned Dest Address Offset.
 *  @return EFI_SUCCESS the Dest Address Offset was get successfully.
 */
EFI_STATUS
GetDestAddressOffsetByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *DestAddressOffset
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || DestAddressOffset == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DestAddressOffset",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *DestAddressOffset = (UINT64)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Data Units from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param Length the Data Units Length.
 *  @param DataUnits returned Data Units pointer.
 *  @return EFI_SUCCESS the DataUnits was get successfully.
 */
EFI_STATUS
GetDataUnitsByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  UINTN                   Length,
  OUT UINT8               **DataUnits
  )
{
  CHAR16          Buffer[1024];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  UINT8           *ReturnBuffer;

  if (SectionName == NULL || DataUnits == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = 1024;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DataUnits",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  ReturnBuffer = NULL;
  Status = ConvertStringToHex (
             Buffer,
             (UINT32)Length,
             &ReturnBuffer
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *DataUnits = ReturnBuffer;
  return EFI_SUCCESS;
}

/**
 *  get the Address Length from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param AddressLength the returned Address Length.
 *  @return EFI_SUCCESS the Address Length was get successfully.
 */
EFI_STATUS
GetAddressLengthByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *AddressLength
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || AddressLength == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"Length",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *AddressLength = (UINT32)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 * get the Pci Io Width from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param PciIoWidth the returned Pci Io Width.
 *  @return EFI_SUCCESS the  Pci Io Width was gotten successfully.
 */
EFI_STATUS
GetPciIoWidthByFile (
  IN EFI_INI_FILE_HANDLE         FileHandle,
  IN CHAR16                      *SectionName,
  IN UINTN                       Order,
  OUT EFI_PCI_IO_PROTOCOL_WIDTH  *PciIoWidth
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  UINTN           Index;

  if (SectionName == NULL || PciIoWidth == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"PciIoWidth",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  for (Index = 0; Index < EfiPciIoWidthMaximum; Index++) {
    if (SctStriCmp (WidthCode[Index], Buffer) == 0) {
      *PciIoWidth = (EFI_PCI_IO_PROTOCOL_WIDTH)Index;
      return EFI_SUCCESS;
    }
  }
  //
  //not found
  //
  return EFI_NOT_FOUND;
}

/**
 *  get the Target Value from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param TargetValue the returned Target Value.
 *  @return EFI_SUCCESS the Target Value was get successfully.
 */
EFI_STATUS
GetTargetValueByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *TargetValue
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || TargetValue == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"TargetValue",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *TargetValue = (UINT64)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  get the Alternate Value from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param AlternateValue the returned Alternate Value.
 *  @return EFI_SUCCESS the Alternate Value was get successfully.
 */
EFI_STATUS
GetAlternateValueByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *AlternateValue
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || AlternateValue == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';
  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"AlternateValue",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  *AlternateValue = (UINT64)XToUint64 (Buffer);
  return EFI_SUCCESS;
}

/**
 *  convert the sring value into hex value.
 *  @param SrcBuffer the input string buffer.
 *  @param Length return buffer length
 *  @param RetBuffer the return Buffer pointer.
 *  @return EFI_SUCCESS the string was converted into hex value successfully.
 */
EFI_STATUS
ConvertStringToHex (
  IN CHAR16             *SrcBuffer,
  IN UINT32             Length,
  OUT UINT8             **RetBuffer
  )
{
  UINTN               Index;
  UINTN               ConvertBytes;
  CHAR16              Buffer[4];
  UINT8               *TempBuffer;
  CHAR16              *StrPtr;

  if (SrcBuffer == NULL || RetBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  StrPtr = SrcBuffer;
  //
  //skip the space if it really has.
  //
  while (*StrPtr == L' ') {
    StrPtr = StrPtr + 1;
  }

  //
  //skip the "0x" prefix if it really has.
  //
  if (SctStrLen (StrPtr) >= 2) {
    if (StrPtr[0] == L'0' && (StrPtr[1] == L'x' || StrPtr[1] == L'X')) {
      StrPtr = StrPtr + 2;
    }
  }

  ConvertBytes = SctStrLen (StrPtr) / 2;
  if (ConvertBytes > Length) {
    ConvertBytes = Length;
  }
  TempBuffer = NULL;
  TempBuffer = SctAllocatePool (Length);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Buffer[2] =0x00;
  //
  //convert string to hex value.
  //
  for (Index = 0; Index < ConvertBytes; Index++) {
    Buffer[0] = StrPtr[Index * 2];
    Buffer[1] = StrPtr[Index * 2 + 1];
    TempBuffer[Index] = (UINT8) SctXtoi (Buffer);
  }
  if (ConvertBytes < Length) {
    for (Index = ConvertBytes; Index < Length; Index++) {
      TempBuffer[Index] = (UINT8) (Index & 0xFF);
    }
  }
  *RetBuffer = TempBuffer;
  return EFI_SUCCESS;
}

/**
 *  get Pci Io Device by PciIo protocol interface.
 *  @param PciIo the PCI_IO_PROTOCOL interface.
 *  @return PCI_IO_PROTOCOL_DEVICE instance.
 */
PCI_IO_PROTOCOL_DEVICE *
GetPciIoDevice (
  IN  EFI_PCI_IO_PROTOCOL     *PciIo
  )
{
  UINTN                       Index;

  for (Index = 0; Index < gPciIoDeviceNumber; Index++) {
    if (gPciIoDevices[Index].PciIo == PciIo) {
      return &gPciIoDevices[Index];
    }
  }
  return NULL;
}

/*
 *  get pci device attribute.
 *  @param the PCI_IO_PROTOCOL_DEVICE instance pointer.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetPciIoDeviceAttributes (
  IN  PCI_IO_PROTOCOL_DEVICE        *PciIoDevice
  )
{
  UINTN                     Seg;
  UINTN                     Bus;
  UINTN                     Dev;
  UINTN                     Func;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  EFI_STATUS                Status;
  UINT8                     HeaderType;
  UINT8                     Index;

  PciIo = PciIoDevice->PciIo;

  if (PciIo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = PciIo->GetLocation (PciIo, &Seg, &Bus, &Dev, &Func);
  if (EFI_ERROR(Status)) {
    return EFI_ABORTED;
  }

  PciIoDevice->Seg  = (UINT8)Seg;
  PciIoDevice->Bus  = (UINT8)Bus;
  PciIoDevice->Dev  = (UINT8)Dev;
  PciIoDevice->Func = (UINT8)Func;

  //
  //get other device info.
  //
  Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8, OFF_HEADERTYPE, 1, &HeaderType);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  if ((HeaderType & 0x7f) == 0) {
    PciIoDevice->Bridge  = FALSE;
  } else  {
    PciIoDevice->Bridge  = TRUE;
  }

  //
  //get all the bar attributes
  //
  for (Index = 0; Index < REGNUM; Index++) {
    ParseBar (PciIoDevice, Index);
  }

  //
  //done successfully return EFI_SUCCESS.
  //
  return EFI_SUCCESS;
}
/**
 *  parse the bar resource
 *  @param PciIoDevice the Pci Io Device instance
 *  @param BarIndex the Bar index value.
 */
EFI_STATUS
ParseBar (
  IN PCI_IO_PROTOCOL_DEVICE  *PciIoDevice,
  IN UINT8                   BarIndex
  )
{
  EFI_STATUS                            Status;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR     *Ptr;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  UINT64                                BarAttributes;
  VOID                                  *Resources;

  PciIo = PciIoDevice->PciIo;
  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    &BarAttributes,
                    &Resources
                    );

  if (EFI_ERROR(Status)) {
    PciIoDevice->BarHasEffect[BarIndex] = FALSE;
    return EFI_SUCCESS;
  }

  Ptr = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *)Resources;

  if (Ptr->Desc == ACPI_ADDRESS_SPACE_DESCRIPTOR) {

    PciIoDevice->BarHasEffect[BarIndex] = TRUE;
    PciIoDevice->BarAddress[BarIndex]   = Ptr->AddrRangeMin;
    PciIoDevice->BarLength[BarIndex]    = (UINT32)Ptr->AddrLen;

    if (Ptr->ResType == ACPI_ADDRESS_SPACE_TYPE_IO) {
      PciIoDevice->BarAttrib[BarIndex] = (UINT8)0x01;
    } else {
      PciIoDevice->BarAttrib[BarIndex] = (UINT8)0x0;
      if (Ptr->AddrSpaceGranularity == 64) {
        PciIoDevice->BarAttrib[BarIndex] |= (UINT8)0x04;
      }
      if (Ptr->SpecificFlag == 0x6) {
        PciIoDevice->BarAttrib[BarIndex] |= (UINT8)0x08;
      }
    }
  } else {
    PciIoDevice->BarHasEffect[BarIndex] = FALSE;
  }

  //
  //free this resource.
  //
  gtBS->FreePool (Resources);
  return EFI_SUCCESS;
}

/*
 *  create all the Pci Io Devices in this system.
 *  @return EFI_SUCCESS the all the devices were gotten successfully.
 */
EFI_STATUS
InitializeCaseEnvironment (
  VOID
  )
{
  EFI_STATUS                          Status;
  EFI_STATUS                          EfiStatus;
  UINTN                               HandleNum;
  EFI_HANDLE                          *HandleBuffer;
  EFI_PCI_IO_PROTOCOL                 *PciIo;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  UINTN                               Index;



  EfiStatus    = EFI_SUCCESS;

  if (Initialized) {
    return EFI_SUCCESS;
  }

  //
  //get PciRootBrigeIo Protocol Interface.
  //
  HandleNum    = 0;
  Status      = SctLocateHandle (
                  ByProtocol,
                  &gBlackBoxEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_ABORTED;
  }
  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiPciRootBridgeIoProtocolGuid,
                   (VOID **) &gRootBridgeIo
                   );
  gtBS->FreePool (HandleBuffer);
  if (EFI_ERROR(Status)) {
    return EFI_ABORTED;
  }
  //
  //locate all the pci Io protocols.
  //
  HandleNum    = 0;
  Status      = SctLocateHandle (
                  ByProtocol,
                  &gBlackBoxEfiPciIoProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_ABORTED;
  }
  //
  // allocate buffer for Pci IO
  //
  gPciIoDevices    = (PCI_IO_PROTOCOL_DEVICE *) SctAllocateZeroPool (HandleNum * sizeof (PCI_IO_PROTOCOL_DEVICE));
  if (gPciIoDevices == NULL) {
    return EFI_ABORTED;
  }

  gPciIoDeviceNumber = 0;

  //
  //get all the pci io devices PciIo protocol and DevicePath protocol instance.
  //
  for (Index = 0 ; Index < HandleNum ; Index++) {
    Status = gtBS->HandleProtocol (HandleBuffer[Index], &gBlackBoxEfiPciIoProtocolGuid, (VOID **) &PciIo);
    if (EFI_ERROR(Status)) {
      EfiStatus  = Status;
      continue;
    }
    Status = gtBS->HandleProtocol (HandleBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID **) &DevicePath);
    if (EFI_ERROR(Status)) {
      EfiStatus = Status;
      continue;
    }
    gPciIoDevices[gPciIoDeviceNumber].PciIo       = PciIo;
    gPciIoDevices[gPciIoDeviceNumber].DevicePath = DevicePath;
    gPciIoDeviceNumber++;
  }
  gtBS->FreePool (HandleBuffer);
  if (gPciIoDeviceNumber == 0) {
    gtBS->FreePool (gPciIoDevices);
    gPciIoDevices = NULL;
    return EFI_ABORTED;
  }
  //
  //get all the Pci Device Attribute.
  //
  for (Index = 0; Index < gPciIoDeviceNumber; Index++) {
    Status = GetPciIoDeviceAttributes (&gPciIoDevices[Index]);

    if (EFI_ERROR(Status)) {
      gtBS->FreePool (gPciIoDevices);
      gPciIoDevices = NULL;
      return EFI_ABORTED;
    }
  }

  Initialized = TRUE;

  return EFI_SUCCESS;
}

/*
 *  get the system device path and file path.
 *  @param ProfileLib the Profile Library Protocol instance.
 *  @return EFI_SUCCESS the system device path and file path were gotten successfully.
 */
EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  CHAR16                      *TempFilePath;
  EFI_STATUS                  Status;

  //
  // If gFilePath and gDevicePath has been assigned, return directly.
  //
  if ((gFilePath != NULL) && (gDevicePath != NULL)) {
    return EFI_SUCCESS;
  }

  //
  // Free gFilePath or gDevicePath
  //
  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
    gFilePath = NULL;
  }
  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
    gDevicePath = NULL;
  }

  //
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                          ProfileLib,
                          &TempDevicePath,
                          &TempFilePath
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //make up the file path.
  //
  gFilePath = NULL;
  gFilePath = SctPoolPrint (L"%s\\%s", TempFilePath, DEPENDECY_DIR_NAME);

  gtBS->FreePool (TempFilePath);

  if (gFilePath == NULL) {
    gtBS->FreePool (TempDevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gDevicePath = TempDevicePath;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}

/*
 *  get the device handle.
 *  @param ImageHandle the Image Handle instance.
 *  @return EFI_SUCCESS the device handle was gotten successfully.
 */
EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  )
{

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}


/**
 *  check if the BarIndex and Address range is valid for this device.
 *  @param PciDevice the PCI_IO_PROTOCOL_DEVICE instance.
 *  @CheckType the MEM or IO.
 *  @BarIndex the Bar Index value.
 *  @AddressOffset the Address Offset.
 *  return TURE these value is valid for this device.
 */
BOOLEAN
CheckBarAndRange (
  IN PCI_IO_PROTOCOL_DEVICE   *PciDevice,
  IN UINT8                    CheckType,
  IN UINT8                    BarIndex,
  IN UINT64                   AddressOffset
  )
{
  UINT64            MaxAddress;
  UINTN             Index;

  if (BarIndex >= 0 && BarIndex <= 5) {
    if (!PciDevice->BarHasEffect[BarIndex]) {
      return FALSE;
    }
    if (AddressOffset > PciDevice->BarLength[BarIndex]) {
      return FALSE;
    }
    if ((PciDevice->BarAttrib[BarIndex] & 0x01) != CheckType) {
      return FALSE;
    }
    return TRUE;

  } else if (BarIndex == EFI_PCI_IO_PASS_THROUGH_BAR) {
    for (Index = 0; Index < REGNUM; Index++) {
      if (!PciDevice->BarHasEffect[Index]) {
        continue;
      }
      if ((PciDevice->BarAttrib[Index] & 0x01) != CheckType) {
        continue;
      }
      MaxAddress = PciDevice->BarAddress[Index] + PciDevice->BarLength[Index];
      if (AddressOffset >= PciDevice->BarAddress[Index] && AddressOffset < MaxAddress) {
        return TRUE;
      }
    }
    return FALSE;
  } else {
    return FALSE;
  }
}

/**
 *  the Event Notify function it will write the assigned value
 *  into the destinaiton address.
 */
VOID
EFIAPI
EventNotifyWriteMem (
  IN EFI_EVENT      Event,
  IN  VOID          *Context
  )
{
  TIMER_EVENT_CONTEXT                 *EventContext;
  EFI_PCI_IO_PROTOCOL                 *PciIo;
  EFI_TEST_ASSERTION                  AssertionType;
  UINT64                              ReadValue;
  EFI_STATUS                          Status;

  EventContext = (TIMER_EVENT_CONTEXT *)Context;
  PciIo        = EventContext->PciIo;

  Status = PciIo->Mem.Write (
                        PciIo,
                        EventContext->PciIoWidth,
                        EventContext->BarIndex,
                        EventContext->AddressOffset,
                        1,
                        &EventContext->DestValue
                        );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  EventContext->StandardLib->RecordAssertion (
                               EventContext->StandardLib,
                               AssertionType,
                               gTestGenericFailureGuid,
                               L"EFI_PCI_IO_PROTOCOL.Mem.Write - time out event to write target value",
                               L"%a:%d:status - %r,write value - %lX",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               EventContext->DestValue
                               );
 ReadValue = 0x00;
  Status = PciIo->Mem.Read (
                        PciIo,
                        EventContext->PciIoWidth,
                        EventContext->BarIndex,
                        EventContext->AddressOffset,
                        1,
                        &ReadValue
                        );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  EventContext->StandardLib->RecordAssertion (
                               EventContext->StandardLib,
                               AssertionType,
                               gTestGenericFailureGuid,
                               L"EFI_PCI_IO_PROTOCOL.Mem.Read - ",
                               L"%a:%d:status - %r,write value - %lX ReadValue - %lX",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               EventContext->DestValue,
                               ReadValue
                               );


  return;
}

/**
 *  the Event Notify function it will write the assigned value
 *  into the destinaiton address.
 */
VOID
EFIAPI
EventNotifyWriteIo (
  IN EFI_EVENT      Event,
  IN  VOID          *Context
  )
{
  TIMER_EVENT_CONTEXT                 *EventContext;
  EFI_PCI_IO_PROTOCOL                 *PciIo;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_STATUS                          Status;
  UINT64                              ReadValue;

  EventContext = (TIMER_EVENT_CONTEXT *)Context;
  PciIo        = EventContext->PciIo;

  Status = PciIo->Io.Write (
                       PciIo,
                       EventContext->PciIoWidth,
                       EventContext->BarIndex,
                       EventContext->AddressOffset,
                       1,
                       &EventContext->DestValue
                       );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  EventContext->StandardLib->RecordAssertion (
                               EventContext->StandardLib,
                               AssertionType,
                               gTestGenericFailureGuid,
                               L"EFI_PCI_IO_PROTOCOL.Io.Write - time out event to write target value",
                               L"%a:%d:status - %r,write value - %lX",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               EventContext->DestValue
                               );
  ReadValue = 0x00;
  Status = PciIo->Io.Read (
                       PciIo,
                       EventContext->PciIoWidth,
                       EventContext->BarIndex,
                       EventContext->AddressOffset,
                       1,
                       &ReadValue
                       );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  EventContext->StandardLib->RecordAssertion (
                               EventContext->StandardLib,
                               AssertionType,
                               gTestGenericFailureGuid,
                               L"EFI_PCI_IO_PROTOCOL.Io.Read - ",
                               L"%a:%d:status - %r,write value - %lX ReadValue - %lX",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status,
                               EventContext->DestValue,
                               ReadValue
                               );
  return;
}

/**
 *  check if the resource list is valid ACPI 2.0 QWORD address space descriptor.
 *  @param Resources the descriptor list pointer.
 *  @return TRUE the list is valid ASD.
 */
BOOLEAN
IsValidResourceDescrptor (
  VOID          *Resources
  )
{
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR  *Ptr;
  EFI_ACPI_END_TAG_DESCRIPTOR        *PtrEnd;

  if (Resources == NULL) {
    return FALSE;
  }

  //
  //only at most one resource descriptor allowed.
  //
  Ptr = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *)Resources;

  switch (Ptr->Desc) {
    case ACPI_ADDRESS_SPACE_DESCRIPTOR:
      //
      //there was one resource descriptor.
      //
      switch (Ptr->ResType) {
        case ACPI_ADDRESS_SPACE_TYPE_MEM :
          if (Ptr->AddrSpaceGranularity != 32 && Ptr->AddrSpaceGranularity != 64) {
            return FALSE;
          } 
          break;
  
        case ACPI_ADDRESS_SPACE_TYPE_IO  :
          break;

        default:
          //
          //can only be Mem or Io.
          //
          return FALSE;
          break;
      }

      PtrEnd = (EFI_ACPI_END_TAG_DESCRIPTOR *)((UINT8*)Ptr + sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR));

      if ((PtrEnd->Desc == ACPI_END_TAG_DESCRIPTOR) && (PtrEnd->Checksum == 0)){
        return TRUE;
      } else {
        return FALSE;
      }
      break;

    case ACPI_END_TAG_DESCRIPTOR:
      //
      //only has a end Tag no resource bind with this bar.
      //
      PtrEnd = (EFI_ACPI_END_TAG_DESCRIPTOR *)Ptr;
      if (PtrEnd->Checksum == 0) {
        return TRUE;
      } else {
        return FALSE;
      }
      break;
    default :
      //
      //invalid Tag.
      //
      return FALSE;
  }
}

/**
 *  compare the two Acpi resource descriptor descript the same resources.
 *  @param Resource1 the first resource list pointer.
 *  @param Resource2 the second resource list pointer.
 *  @return TRUE the two descriptor descript the same resources.
 */
BOOLEAN
CompareAcpiResourceDescrptor (
  IN  VOID              *Resource1,
  IN  VOID              *Resource2
  )
{
  BOOLEAN                            IsEqual;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR  *Ptr1;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR  *Ptr2;
  UINTN                              MaxResourceNum;

  if (Resource1 == NULL || Resource2 == NULL) {
    return FALSE;
  }
  MaxResourceNum = 0;
  IsEqual        = FALSE;

  Ptr1 = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *)Resource1;
  Ptr2 = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *)Resource2;
  while (TRUE) {
    if (MaxResourceNum  == 100) {
      break;
    }
    switch (Ptr1->Desc) {
      case ACPI_ADDRESS_SPACE_DESCRIPTOR:
        if (SctCompareMem (Ptr1, Ptr2, sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR)) != 0) {
          return FALSE;
        }
        Ptr1 = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) ((UINT8*)Ptr1 + sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR));
        Ptr2 = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) ((UINT8*)Ptr2 + sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR));
        break;
      case ACPI_END_TAG_DESCRIPTOR:
        if (SctCompareMem (Ptr1, Ptr2, sizeof (EFI_ACPI_END_TAG_DESCRIPTOR)) != 0) {
          return FALSE;
        } else {
          return TRUE;
        }
        break;
      default :
        return IsEqual;
    }
    MaxResourceNum++;
  } // end while.
  return IsEqual;
}

/**
 *  wait for user input and the timer if user didnot input any char during seconds
 *  period then the Buffer will point to NULL.
 *  @param Buffer the returned user input buffer.
 *  @param Seconds the timer wait time
 *  @return EFI_SUCCESS seccessfully done
 */
EFI_STATUS
GetUserInputOrTimeOut (
  OUT CHAR16                       **Buffer,
  IN  UINTN                        Seconds
  )
{
  EFI_EVENT             TimeOutEvent;
  EFI_EVENT             OneSecondTimer;
  EFI_EVENT             WaitList[2];
  BOOLEAN               Wait;
  EFI_STATUS            Status;
  CHAR16                *InputBuffer;
  UINTN                 InputLength;
  UINTN                 WaitIndex;
  EFI_INPUT_KEY         Key;
  CHAR16                PrintBuffer[2];

  InputLength = 0;
  InputBuffer = NULL;

  //
  //allocate string buffer.
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MAX_STRING_LEN * sizeof (CHAR16),
                   (VOID **)&InputBuffer
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Wait   = TRUE;
  //
  //create time event
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER ,
                   0,
                   NULL,
                   NULL,
                   &TimeOutEvent
                   );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (InputBuffer);
    return Status;
  }

  Status = gtBS->CreateEvent (
                   EVT_TIMER,
                   0,
                   NULL,
                   NULL,
                   &OneSecondTimer
                   );
  if (EFI_ERROR(Status)) {
    gtBS->CloseEvent (TimeOutEvent);
    gtBS->FreePool (InputBuffer);
    return Status;
  }

  //
  //set the Timer
  //
  Status = gtBS->SetTimer (
                   TimeOutEvent,
                   TimerRelative,
                   10000000 * Seconds
                   );

  if (EFI_ERROR(Status)) {
    gtBS->CloseEvent (TimeOutEvent);
    gtBS->CloseEvent (OneSecondTimer);
    gtBS->FreePool (InputBuffer);
    return Status;
  }

  //
  // Set up a wait list for a key and the timer
  //

  Wait = TRUE;

  WaitList[0] = gtST->ConIn->WaitForKey;
  WaitList[1] = OneSecondTimer;
  PrintBuffer[1] = '\0';
  //
  // Wait for timeout or string input.
  //
  while (Wait) {
    //
    // Set one second timer
    //
    Status = gtBS->SetTimer (
                     OneSecondTimer,
                     TimerRelative,
                     10000000
                     );
    if (EFI_ERROR(Status)) {
      gtBS->CloseEvent (TimeOutEvent);
      gtBS->CloseEvent (OneSecondTimer);
      gtBS->FreePool (InputBuffer);
      return Status;
    }
    Status = gtBS->WaitForEvent (
                     2,
                     WaitList,
                     &WaitIndex
                     );
    if (EFI_ERROR(Status)) {
      gtBS->CloseEvent (TimeOutEvent);
      gtBS->CloseEvent (OneSecondTimer);
      gtBS->FreePool (InputBuffer);
      return Status;
    }
    switch (WaitIndex) {
      case 1:
        //
        //the OneSecondTimer is triggered
        //
        break;

      case 0:
        //
        //key press event is triggered.
        //
        Key.ScanCode = SCAN_NULL;
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        if (!EFI_ERROR(Status)) {
          if (Key.ScanCode == SCAN_NULL) {
            if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
                Wait = FALSE;
                break;
            }
            if (Key.UnicodeChar >= 0x20 && Key.UnicodeChar <= 0x7f) {
              InputBuffer[InputLength] = Key.UnicodeChar;
              InputLength++;
              //
              //print this char in screen.
              //
              PrintBuffer[0] = Key.UnicodeChar;
              gtST->ConOut->OutputString (gtST->ConOut, PrintBuffer);

              if ((InputLength + 1) == MAX_STRING_LEN) {
                Wait = FALSE;
              }
            }
          }
        }
        break;

      default:
        break;
    }// end switch.

    if (Wait) {
      //
      //check if the Timer has been signaled.
      //
      Status = gtBS->CheckEvent (TimeOutEvent);
      if (!EFI_ERROR(Status)) {
        Wait = FALSE;
      }
    }
  }//end while.

  //
  //close the timer.
  //
  gtBS->CloseEvent (TimeOutEvent);
  gtBS->CloseEvent (OneSecondTimer);

  if (InputLength > 0) {
    InputBuffer[InputLength] = '\0';
    *Buffer = InputBuffer;
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (InputBuffer);
    return EFI_TIMEOUT;
  }
}
/**
 *  convert the string of hex value to uint64
 *  @param Str the input hex string value.
 *  @return converted UINT64 value.
 */
UINT64
XToUint64 (
  CHAR16  *Str
  )
{
    UINT64      U64;
    CHAR16      Char;

    //
    //skip preceeding white space
    //
    while (*Str && *Str == ' ') {
        Str += 1;
    }

    //
    // skip preceeding zeros
    //
    while (*Str && *Str == '0') {
      Str += 1;
    }

    //
    // skip preceeding white space
    //
    if (*Str && (*Str == 'x' || *Str == 'X')) {
      Str += 1;
    }

    //
    // convert hex digits
    //
    U64 = 0;
    Char = *(Str++);
    while (Char) {
      if (Char >= 'a'  &&  Char <= 'f') {
        Char -= 'a' - 'A';
      }

      if ((Char >= '0'  &&  Char <= '9')  ||  (Char >= 'A'  &&  Char <= 'F')) {
        U64 = SctLShiftU64 (U64, 4)  |  (Char - (Char >= 'A' ? 'A'-10 : '0'));
      } else {
        break;
      }
      Char = *(Str++);
    }

    return U64;
}

UINT64
AToUint64 (
  CHAR16  *Str
  )
{
    UINT64      U64;
    CHAR16      Char;

    //
    //skip preceeding white space
    //
    while (*Str && *Str == ' ') {
        Str += 1;
    }

    //
    // convert digits
    //
    U64 = 0;
    Char = *(Str++);
    while (Char) {
      if (Char >= '0' && Char <= '9') {
        U64 = SctMultU64x32 (U64 , 10) + Char - '0';
      } else {
        break;
      }
      Char = *(Str++);
    }
    return U64;
}
