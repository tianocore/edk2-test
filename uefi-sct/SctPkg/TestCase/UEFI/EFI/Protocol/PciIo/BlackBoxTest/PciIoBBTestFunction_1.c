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

  PciIoBBTestFunction_1.c

Abstract:

  function test case source file for PciIo Protocol

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"

#define SECTION_NAME_POLLMEM_TEST           L"PollMem_Func"
#define SECTION_NAME_POLLIO_TEST            L"PollIo_Func"
#define SECTION_NAME_MEMREAD_TEST           L"MemRead_Func"
#define SECTION_NAME_MEMWRITE_TEST          L"MemWrite_Func"
#define SECTION_NAME_IOREAD_TEST            L"IoRead_Func"
#define SECTION_NAME_IOWRITE_TEST           L"IoWrite_Func"


/**
 *  Entrypoint for PciIo->PollMem() Interface manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.1
//
EFI_STATUS
EFIAPI
PollMem_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                Length;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT64                                AlternateValue;
  UINTN                                 Index;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  while (TRUE) {

    if (!QueryGoOnTesting ()) {
      break;
    }
    //
    //get use input for BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndex (&BarIndex);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffset (&AddressOffset);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidth (&PciIoWidth);
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        Length = 1;
        break;
      case EfiPciIoWidthUint16:
        Length = 2;
        break;
      case EfiPciIoWidthUint32:
        Length = 4;
        break;
      default:
        Length = 8;
        break;
    }

    //
    //get target value
    //
    TargetValue = 0x00;
    Status = GetTargetValue (&TargetValue);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get alternate value
    //
    AlternateValue = 0x00;
    Status = GetAlternateValue (&AlternateValue);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, BarIndex, AddressOffset + Length)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }
    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <=5) {
      RepeatNum = 2;
    }
    for (Index = 0; Index < RepeatNum; Index++) {
      if (Index == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }

      //
      //call PollMemCheckPoint three times with different Mask value.
      //

      //
      //first with 1 bit set with 1.
      //
      Mask = 0x01;
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with multi-bit set with 1.
      //
      Mask = 0x0F;
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with all bit set with 1.
      //
      switch (PciIoWidth) {
        case EfiPciIoWidthUint8:
          Mask = MASK8BIT;
          break;
        case EfiPciIoWidthUint16:
          Mask = MASK16BIT;
          break;
        case EfiPciIoWidthUint32:
          Mask = MASK32BIT;
          break;
        default:
          Mask = MASK64BIT;
          break;
      }
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );
    }
  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
/**
 *  the internal sub function to run the check point for PollMem.
 *  @param PciIo the EFI_PCI_IO_PROTOCOL interface.
 *  @param StandardLib the Standard Test Lib interface.
 *  @param PciIoWidth the PCI IO Width .
 *  @param BarIndex the Bar Index value.
 *  @param AddressOffset the Address Offset.
 *  @param Mask the Mask value.
 *  @param TargetValue the Target Value for this address.
 *  @param AlternateValue the Alternate Value for this address.
 *  @return EFI_SUCCESS the check point was checked successfully.
 */
EFI_STATUS
EFIAPI
PollMemCheckPoint (
  IN  EFI_PCI_IO_PROTOCOL                 *PciIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH           PciIoWidth,
  IN  UINT8                               BarIndex,
  IN  UINT64                              AddressOffset,
  IN  UINT64                              Mask,
  IN  UINT64                              TargetValue,
  IN  UINT64                              AlternateValue
  )
{
  EFI_STATUS                            Status;
  UINT64                                OldValue;
  UINT64                                Result;
  UINT64                                TimeOutValue;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EVENT                             TimeOutEvent;
  TIMER_EVENT_CONTEXT                   *EventContext;

  //
  //get original value in the destination address.
  //
  OldValue = 0x00;
  Status = PciIo->Mem.Read (PciIo,  PciIoWidth, BarIndex, AddressOffset, 1, &OldValue);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read() - read from memory",
                 L"%a:%d:Status - %r, Value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 OldValue
                 );
  //
  //set Target value.
  //
  switch (PciIoWidth) {
    case EfiPciIoWidthUint8:
      TargetValue    = (UINT64)(TargetValue & MASK8BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK8BIT);
      break;
    case  EfiPciIoWidthUint16:
      TargetValue    = (UINT64)(TargetValue & MASK16BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK16BIT);
      break;
    case  EfiPciIoWidthUint32:
      TargetValue    = (UINT64)(TargetValue & MASK32BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK32BIT);
      break;
    default:

    break;
  }
  //
  //allocate a TIMER_EVENT_CONTEXT.
  //
  EventContext = NULL;
  EventContext = SctAllocateZeroPool (sizeof (TIMER_EVENT_CONTEXT));
  if (EventContext == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  EventContext->PciIo         = PciIo;
  EventContext->StandardLib   = StandardLib;
  EventContext->PciIoWidth    = PciIoWidth;
  EventContext->BarIndex      = BarIndex;
  EventContext->AddressOffset = AddressOffset;
  EventContext->DestValue     = TargetValue;

  //
  //create a timer event.
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   EventNotifyWriteMem,
                   EventContext,
                   &TimeOutEvent
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\r\n"
                   L"%a:%d.\r\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (EventContext);
    return Status;
  }
  //
  //record test envionment.
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"PollMem env. \r\n"
                 L"%a:%d:BarIndex - %2xh, AddressOffset - %lXh, Mask - %lXh, TargetValue - %lXh, AlternateValue - %lXh, PciIoWidth - %d\r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 BarIndex,
                 AddressOffset,
                 Mask,
                 TargetValue,
                 AlternateValue,
                 PciIoWidth
                 );

  //
  //write alternate value to the destinaion address.
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        BarIndex,
                        AddressOffset,
                        (UINTN)1,
                        &AlternateValue
                        );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write alternate value to memory",
                 L"%a:%d:Status - %r, Alternate Value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue
                 );

  //
  //set 3 seconds timer.
  //
  Status = gtBS->SetTimer (
                   TimeOutEvent,
                   TimerRelative,
                   10000000 * 3
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"error with tBS->SetTimer().\r\n"
                   L"%a:%d:Status - %r\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (TimeOutEvent);
    gtBS->FreePool (EventContext);
    return Status;
  }
  //
  //check point 1.
  //
  //pollmem with 5 second delay and set the timer event to write
  //the correct value at the destination address before time out.
  //
  Result = 0x00;
  TimeOutValue = 5 * 10000000;
  Status = PciIo->PollMem (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //close the timer event not to be used.
  //
  gtBS->CloseEvent (TimeOutEvent);
  gtBS->FreePool (EventContext);

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid001,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - Target address set the valid value before time out",
                 L"%a:%d:Status - %r, Target Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );

  //
  //check point 2.
  //
  //call PollMem again it will return immediately with EFI_SUCCESS.
  //
  Result = 0x00;
  Status = PciIo->PollMem (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid002,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - Target address has the valid value before calling",
                 L"%a:%d:Status - %r, Target value - %lXh, Result Value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );
  //
  //set the alternate value on the address
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        BarIndex,
                        AddressOffset,
                        (UINTN)1,
                        &AlternateValue
                        );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write() - write the alternate value again",
                 L"%a:%d:Status - %r, alternate value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue
                 );
  //
  //check point 3.
  //
  //destination address has invalid value,Poll Mem with delay equal 0.
  //
  Result = 0x00;
  TimeOutValue = 0;
  Status = PciIo->PollMem (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid003,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - with delay equal 0 it should return EFI_SUCCESS",
                 L"%a:%d:Status - %r, alternate value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );

  //
  //check point 4.
  //destination address has invalid value,Poll Mem with 5 seconds delay .
  //
  Result = 0x00;
  TimeOutValue = 5 * 10000000;
  Status = PciIo->PollMem (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );

  if (Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid004,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - with 5 seconds delay",
                 L"%a:%d:Status - %r, alternate Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );
  //
  //write orginal value back to the destinaiton address.
  //
  PciIo->Mem.Write (
               PciIo,
               PciIoWidth,
               BarIndex,
               AddressOffset,
               (UINTN)1,
               &OldValue
               );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->PollMem() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.2
//

EFI_STATUS
EFIAPI
PollMem_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                Length;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT64                                AlternateValue;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 MaxOrder;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollMem- not found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_POLLMEM_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);

    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollMem- no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }
  for (Index = 0; Index < MaxOrder; Index++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    Length = 0;
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        Length = 1;
        break;
      case EfiPciIoWidthUint16:
        Length = 2;
        break;
      case EfiPciIoWidthUint32:
        Length = 4;
        break;
      case EfiPciIoWidthUint64:
        Length = 8;
        break;
      default:
        break;
    }
    if (Length == 0) {
      //
      //invalid PciIoWidth.
      //
      continue;
    }
    //
    //get target value
    //
    TargetValue = 0x00;
    Status = GetTargetValueByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &TargetValue
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get alternate value
    //
    AlternateValue = 0x00;
    Status = GetAlternateValueByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &AlternateValue
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, BarIndex, AddressOffset + Length)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }
    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <= 5) {
      RepeatNum = 2;
    }
    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }

      //
      //call PollMemCheckPoint three times with different Mask value.
      //

      //
      //first with 1 bit set with 1.
      //
      Mask = 0x01;
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with multi-bit set with 1.
      //
      Mask = 0x0F;
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with all bit set with 1.
      //
      switch (PciIoWidth) {
        case EfiPciIoWidthUint8:
          Mask = MASK8BIT;
          break;
        case EfiPciIoWidthUint16:
          Mask = MASK16BIT;
          break;
        case EfiPciIoWidthUint32:
          Mask = MASK32BIT;
          break;
        default:
          Mask = MASK64BIT;
          break;
      }
      PollMemCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );
    }
  }
  //
  //free resource.
  //
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->PollIo() Interface manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.3
//
EFI_STATUS
EFIAPI
PollIo_Func_Manual (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  UINT32                                Length;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT64                                AlternateValue;
  UINTN                                 Index;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  while (TRUE) {
    if (!QueryGoOnTesting ()) {
      break;
    }
    //
    //get use input for BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndex (&BarIndex);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffset (&AddressOffset);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    Status = GetPciIoWidth (&PciIoWidth);
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        Length = 1;
        break;
      case EfiPciIoWidthUint16:
        Length = 2;
        break;
      case EfiPciIoWidthUint32:
        Length = 4;
        break;
      default:
        Length = 8;
        break;
    }
    //
    //get target value
    //
    TargetValue = 0x00;
    Status = GetTargetValue (&TargetValue);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get alternate value
    //
    AlternateValue = 0x00;
    Status = GetAlternateValue (&AlternateValue);
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_IO, BarIndex, AddressOffset + Length)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }
    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <=5) {
      RepeatNum = 2;
    }
    for (Index = 0; Index < RepeatNum; Index++) {
      if (Index == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }

      //
      //call PollIoCheckPoint three times with different Mask value.
      //

      //
      //first with 1 bit set with 1.
      //
      Mask = 0x01;
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with multi-bit set with 1.
      //
      Mask = 0x0F;
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with all bit set with 1.
      //
      switch (PciIoWidth) {
        case EfiPciIoWidthUint8:
          Mask = MASK8BIT;
          break;
        case EfiPciIoWidthUint16:
          Mask = MASK16BIT;
          break;
        case EfiPciIoWidthUint32:
          Mask = MASK32BIT;
          break;
        default:
          Mask = MASK64BIT;
          break;
      }
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );
    }
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
/**
 *  the internal sub function to run the check point for PollIo.
 *  @param PciIo the EFI_PCI_IO_PROTOCOL interface.
 *  @param StandardLib the Standard Test Lib interface.
 *  @param PciIoWidth the PCI IO Width .
 *  @param BarIndex the Bar Index value.
 *  @param AddressOffset the Address Offset.
 *  @param Mask the Mask value.
 *  @param TargetValue the Target Value for this address.
 *  @param AlternateValue the Alternate Value for this address.
 *  @return EFI_SUCCESS the check point was checked successfully.
 */
EFI_STATUS
EFIAPI
PollIoCheckPoint (
  IN  EFI_PCI_IO_PROTOCOL                 *PciIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH           PciIoWidth,
  IN  UINT8                               BarIndex,
  IN  UINT64                              AddressOffset,
  IN  UINT64                              Mask,
  IN  UINT64                              TargetValue,
  IN  UINT64                              AlternateValue
  )
{
  EFI_STATUS                            Status;
  UINT64                                OldValue;
  UINT64                                Result;
  UINT64                                TimeOutValue;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EVENT                             TimeOutEvent;
  TIMER_EVENT_CONTEXT                   *EventContext;

  //
  //get original value in the destination address.
  //
  OldValue = 0x00;
  Status = PciIo->Io.Read (PciIo,  PciIoWidth, BarIndex, AddressOffset, 1, &OldValue);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read() - read from Io space",
                 L"%a:%d:Status - %r, read Value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 OldValue
                 );

  //
  //set Target value.
  //
  switch (PciIoWidth) {
    case EfiPciIoWidthUint8:
      TargetValue    = (UINT64)(TargetValue & MASK8BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK8BIT);
      break;
    case  EfiPciIoWidthUint16:
      TargetValue    = (UINT64)(TargetValue & MASK16BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK16BIT);
      break;
    case  EfiPciIoWidthUint32:
      TargetValue    = (UINT64)(TargetValue & MASK32BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK32BIT);
      break;
    default:
    break;
  }

  //
  //allocate a TIMER_EVENT_CONTEXT.
  //
  EventContext = NULL;
  EventContext = SctAllocateZeroPool (sizeof (TIMER_EVENT_CONTEXT));
  if (EventContext == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  EventContext->PciIo         = PciIo;
  EventContext->StandardLib   = StandardLib;
  EventContext->PciIoWidth    = PciIoWidth;
  EventContext->BarIndex      = BarIndex;
  EventContext->AddressOffset = AddressOffset;
  EventContext->DestValue     = TargetValue;

  //
  //create a timer event.
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   EventNotifyWriteIo,
                   EventContext,
                   &TimeOutEvent
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\r\n"
                   L"%a:%d.\r\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (EventContext);
    return Status;
  }

  //
  //record test envionment.
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"PollIo env. \r\n"
                 L"%a:%d:BarIndex - %2xh, AddressOffset - %lXh, Mask - %lXh, TargetValue - %lXh, AlternateValue - %lXh, PciIoWidth - %d\r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 BarIndex,
                 AddressOffset,
                 Mask,
                 TargetValue,
                 AlternateValue,
                 PciIoWidth
                 );
  //
  //write alternate value to the destinaion address.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       BarIndex,
                       AddressOffset,
                       (UINTN)1,
                       &AlternateValue
                       );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - write alternatevalue into Io space",
                 L"%a:%d:Status - %r, alternate value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue
                 );

  //
  //set 3 seconds timer.
  //
  Status = gtBS->SetTimer (
                   TimeOutEvent,
                   TimerRelative,
                   10000000 * 3
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"error with tBS->SetTimer().\r\n"
                   L"%a:%d:Status - %r\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (TimeOutEvent);
    gtBS->FreePool (EventContext);
    return Status;
  }

  //
  //check point 1.
  //
  //pollIo with 5 second delay and set the timer event to write
  //the correct value at the destination address before time out.
  //
  TimeOutValue = 5 * 10000000;
  Status = PciIo->PollIo (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //close the timer event not to be used.
  //
  gtBS->CloseEvent (TimeOutEvent);
  gtBS->FreePool (EventContext);

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid005,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - Target address set the valid value before time out",
                 L"%a:%d:Status - %r, Target Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 TargetValue,
                 Result
                 );

  //
  //check point 2.
  //
  //call PollIo again it will return immediately with EFI_SUCCESS.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid006,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - Target address has the valid value before calling",
                 L"%a:%d:Status - %r, Target Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );
  //
  //set the alternate value on the address
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       BarIndex,
                       AddressOffset,
                       (UINTN)1,
                       &AlternateValue
                       );
  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 EFI_TEST_ASSERTION_FAILED,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write() - write the alternate value",
                 L"%a:%d:Status - %r, alternate value - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue
                 );
  //
  //check point 3.
  //
  //destination address has invalid value,Poll Io with delay equal 0.
  //
  TimeOutValue = 0;
  Status = PciIo->PollIo (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid007,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - with delay equal 0 return status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r, Alternate Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );

  //
  //check point 4.
  //destination address has invalid value, Poll Io with 5 seconds delay .
  //
  TimeOutValue = 5 * 10000000;
  Status = PciIo->PollIo (
                    PciIo,
                    PciIoWidth,
                    BarIndex,
                    AddressOffset,
                    Mask,
                    (TargetValue & Mask),
                    TimeOutValue,
                    &Result
                    );
  if (Status == EFI_TIMEOUT) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_1AssertionGuid008,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - with 5 seconds delay",
                 L"%a:%d:Status - %r, Alternate Value - %lXh, Result - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 AlternateValue,
                 Result
                 );
  //
  //write orginal value back to the destinaiton address.
  //
  PciIo->Io.Write (
              PciIo,
              PciIoWidth,
              BarIndex,
              AddressOffset,
              (UINTN)1,
              &OldValue
              );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PciIo->PollIo() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.4
//

EFI_STATUS
EFIAPI
PollIo_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{

  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                Length;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT64                                AlternateValue;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 MaxOrder;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_POLLIO_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    Length = 0;
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        Length = 1;
        break;
      case EfiPciIoWidthUint16:
        Length = 2;
        break;
      case EfiPciIoWidthUint32:
        Length = 4;
        break;
      case EfiPciIoWidthUint64:
        Length = 8;
        break;
      default:
        break;
    }
    if (Length == 0) {
      //
      //invalid PciIoWidth.
      //
      continue;
    }
    //
    //get target value
    //
    TargetValue = 0x00;
    Status = GetTargetValueByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &TargetValue
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get alternate value
    //
    AlternateValue = 0x00;
    Status = GetAlternateValueByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               RepeatIndex,
               &AlternateValue
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_IO, BarIndex, AddressOffset + Length)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }
    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <=5) {
      RepeatNum = 2;
    }
    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }

      //
      //call PollMemCheckPoint three times with different Mask value.
      //

      //
      //first with 1 bit set with 1.
      //
      Mask = 0x01;
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with multi-bit set with 1.
      //
      Mask = 0x0F;
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );

      //
      //then with all bit set with 1.
      //
      switch (PciIoWidth) {
        case EfiPciIoWidthUint8:
          Mask = MASK8BIT;
          break;
        case EfiPciIoWidthUint16:
          Mask = MASK16BIT;
          break;
        case EfiPciIoWidthUint32:
          Mask = MASK32BIT;
          break;
        default:
          Mask = MASK64BIT;
          break;
      }
      PollIoCheckPoint (
        PciIo,
        StandardLib,
        PciIoWidth,
        BarIndex,
        AddressOffset,
        Mask,
        TargetValue,
        AlternateValue
        );
    }
  }

  //
  //free resource.
  //
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Mem.Read() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.5
//

EFI_STATUS
EFIAPI
MemRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *BackupBuffer;
  VOID                                  *ReadBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMREAD_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    SctPrint (L"After Get BarIndex\r\n");
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    SctPrint (L"After Get Bar Offset\r\n");
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }

    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);

    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, BarIndex, AddressOffset + AddressLength)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }

    //
    //allocate read buffer.
    //
    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //allocate BackupBuffer.
    //
    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }


    //
    //first read the data out.
    //
    Status = PciIo->Mem.Read (
                          PciIo,
                          PciIoWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          BackupBuffer
                          );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_1AssertionGuid009,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - Read data out",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <= 5) {
      RepeatNum = 2;
    }

    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }

      //
      //record test envionment.
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"MemRead env. \r\n"
                     L"%a:%d:PciIoWidth - %s, BarIndex - %02xh, Count- %xh, AddressOffset - %lXh\r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     WidthCode[PciIoWidth],
                     BarIndex,
                     (UINT32)Count,
                     AddressOffset
                     );

      //
      //first write the buffer into destination address range.
      //
      Status =PciIo->Mem.Write (
                           PciIo,
                           PciIoWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           Buffer
                           );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion.
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                     L"%a:%d:Status - %r, Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[PciIoWidth]
                     );

      //
      //then read out the data in destination address range.
      //
      Status =PciIo->Mem.Read (
                           PciIo,
                           PciIoWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           ReadBuffer
                           );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid010,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out the data from the address space",
                     L"%a:%d:Status - %r, Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[PciIoWidth]
                     );

      //
      //the data read out must be the same as write into.
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid011,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read -  the data read out must be the same as write into.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

      //
      //read out the data using EfiPciIoWidthFifoUintX.
      //
      Status =PciIo->Mem.Read (
                           PciIo,
                           SecondWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           ReadBuffer
                           );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid012,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out the data with EfiPciIoWidthFifoX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );

      //
      //the data read out must be the same as the first data unit.
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (Index = 0; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid013,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read - with EfiPciIoWidthFifoX the data read out must be the same as the first data unit.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

      //
      //make the readbuffer units all with the same value as the first unit in buffer
      //by force.
      //
      for (Index = 0; Index < Count; Index++) {
        SctCopyMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength);
      }

      //
      //read out the data using EfiPciIoWidthFillUintX.
      //
      Status =PciIo->Mem.Read (
                           PciIo,
                           ThirdWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           ReadBuffer
                           );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid014,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out the data with EfiPciIoWidthFillX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );



      //
      //the data read out first unit in buffer must equal last unit in address space
      //and the other unit unchange.
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count -1) * UnitLength, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      for (Index = 1; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid015,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Read - with EfiPciIoWidthFillX the data read out first unit in buffer must equal last unit in address space",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

    }
    //
    //at last write the data back.
    //
    Status =PciIo->Mem.Write (
                         PciIo,
                         PciIoWidth,
                         BarIndex,
                         AddressOffset,
                         Count,
                         BackupBuffer
                         );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write back Data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);
  }
  //
  //free resources.
  //
  gtBS->FreePool (PciDevicePathStr);

  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PciIo->Mem->Write() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.6
//
EFI_STATUS
EFIAPI
MemWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *BackupBuffer;
  VOID                                  *ReadBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - not found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMWRITE_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                   ProfileLib,
                   FileHandle
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }


  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, BarIndex, AddressOffset + AddressLength)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                       ProfileLib,
                       FileHandle
                       );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //
    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //allocate BackupBuffer.
    //
    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );

      return EFI_OUT_OF_RESOURCES;
    }
    //
    //first read the data out.
    //
    Status = PciIo->Mem.Read (
                          PciIo,
                          PciIoWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          BackupBuffer
                          );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - Read data out",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <= 5) {
      RepeatNum = 2;
    }

    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }
      //
      //record test envionment.
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"MemRead env. \r\n"
                     L"%a:%d:PciIoWidth - %s, BarIndex - %02xh, Count - %xh, AddressOffset - %lXh\r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     WidthCode[PciIoWidth],
                     BarIndex,
                     (UINT32)Count,
                     AddressOffset
                     );

      //
      //first write the buffer into destination address range.
      //
      Status = PciIo->Mem.Write (
                            PciIo,
                            PciIoWidth,
                            BarIndex,
                            AddressOffset,
                            Count,
                            Buffer
                            );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid016,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                     L"%a:%d:Status - %r, Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[PciIoWidth]
                     );
      //
      //then read out the data in destination address range.
      //
      PciIo->Mem.Read (
                   PciIo,
                   PciIoWidth,
                   BarIndex,
                   AddressOffset,
                   Count,
                   ReadBuffer
                   );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      //the data read out must be the same as write into.
      //
      if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //check point 2.
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid017,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - the data read out must be the same as write into.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      //
      //write the data using EfiPciIoWidthFifoUintX.
      //
      Status =PciIo->Mem.Write (
                           PciIo,
                           SecondWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           Buffer
                           );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid018,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - write the data with EfiPciIoWidthFifoX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );
      //
      //read the data out again using EfiPciIoWidthUintX.
      //
      PciIo->Mem.Read (
                   PciIo,
                   PciIoWidth,
                   BarIndex,
                   AddressOffset,
                   Count,
                   ReadBuffer
                   );

      AssertionType = EFI_TEST_ASSERTION_PASSED;
      //
      //the first data unit must be the last data unit and
      //the other data unchange.
      //

      if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count - 1) * UnitLength, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if (Count > 1) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + UnitLength, (UINT8 *)Buffer + UnitLength, AddressLength - UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid019,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - with EfiPciIoWidthFifoX the first data unit must be the last data unit.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

      //
      //write the data using EfiPciIoWidthFillUintX.
      //
      Status = PciIo->Mem.Write (
                            PciIo,
                            ThirdWidth,
                            BarIndex,
                            AddressOffset,
                            Count,
                            Buffer
                            );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid020,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write - write the data with EfiPciIoWidthFillX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );

      //
      //read out the data again using EfiPciIoWidthUintX.
      //
      PciIo->Mem.Read (
                   PciIo,
                   PciIoWidth,
                   BarIndex,
                   AddressOffset,
                   Count,
                   ReadBuffer
                   );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      //all the data unit read out must be the first data unit in the address  space.
      //
      for (Index = 0; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid021,
                     L"EFI_PCI_IO_PROTOCOL.Mem.Write -with EfiPciIoWidthFillX all the data unit read out must be the first data unit in the address  space.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );
    }

    //
    //at last write the data back.
    //
    Status =PciIo->Mem.Write (
                         PciIo,
                         PciIoWidth,
                         BarIndex,
                         AddressOffset,
                         Count,
                         BackupBuffer
                         );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_1AssertionGuid022,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write back Data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    //
    //free resource.
    //
    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);

  }

  //
  //free resources.
  //
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Io.Read() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.7
//
EFI_STATUS
EFIAPI
IoRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *BackupBuffer;
  VOID                                  *ReadBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - not found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOREAD_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }


  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_IO, BarIndex, AddressOffset + AddressLength)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //allocate BackupBuffer.
    //
    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );

      return EFI_OUT_OF_RESOURCES;
    }
    //
    //first read the data out.
    //
    Status = PciIo->Io.Read (
                         PciIo,
                         PciIoWidth,
                         BarIndex,
                         AddressOffset,
                         Count,
                         BackupBuffer
                         );
    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_1AssertionGuid023,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <= 5) {
      RepeatNum = 2;
    }

    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }
      //
      //record test envionment.
      //
     StandardLib->RecordMessage (
                    StandardLib,
                    EFI_VERBOSE_LEVEL_DEFAULT,
                    L"IoRead env. \r\n"
                    L"%a:%d:PciIoWidth - %s, BarIndex - %02xh, Count - %xh, AddressOffset - %lXh\r\n",
                    __FILE__,
                    (UINTN)__LINE__,
                    WidthCode[PciIoWidth],
                    BarIndex,
                    (UINT32)Count,
                    AddressOffset
                    );

      //
      //first write the buffer into destination address range.
      //
      Status =PciIo->Io.Write (
                          PciIo,
                          PciIoWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          Buffer
                          );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - Write data to Io address space",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      //
      //then read out the data in destination address range.
      //
      Status =PciIo->Io.Read (
                          PciIo,
                          PciIoWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          ReadBuffer
                          );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion.
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid024,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - read out the data from Io address space",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[PciIoWidth]
                     );


      //
      //the data read out must be the same as write into.
      //
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid025,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - the data read out must be the same as write into.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

      //
      //read out the data using EfiPciIoWidthFifoUintX.
      //
      Status =PciIo->Io.Read (
                          PciIo,
                          SecondWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          ReadBuffer
                          );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion.
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid026,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - read out the data with EfiPciIoWidthFifoX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );

      //
      //the data read out must be the same as the first data unit.
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;

      for (Index = 0; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid027,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - read out the data with EfiPciIoWidthFifoX, all the data must equal with the first data unit.",
                     L"%a:%d:",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      //
      //make the readbuffer units all with the same value as the first unit in buffer
      //by force.
      //
      for (Index = 0; Index < Count; Index++) {
        SctCopyMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength);
      }

      //
      //read out the data using EfiPciIoWidthFillUintX.
      //
      Status =PciIo->Io.Read (
                          PciIo,
                          ThirdWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          ReadBuffer
                          );
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion.
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid028,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - read out the data with EfiPciIoWidthFillX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );


      //
      //the data read out first unit in buffer must equal last unit in address space
      //and the other unit unchange.
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count -1) * UnitLength, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      for (Index = 1; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid029,
                     L"EFI_PCI_IO_PROTOCOL.Io.Read - read out the data with EfiPciIoWidthFillX the first data unit must eqal with the last data unit in destination address.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

    }

    //
    //at last write the data back.
    //
    Status =PciIo->Io.Write (
                        PciIo,
                        PciIoWidth,
                        BarIndex,
                        AddressOffset,
                        Count,
                        BackupBuffer
                        );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion.
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - Write back Data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //free resource.
    //
    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);
  }

  //
  //free resources.
  //
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Io.Write() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.8
//
EFI_STATUS
EFIAPI
IoWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 BarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *ReadBuffer;
  VOID                                  *BackupBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);
  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - not found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOWRITE_TEST,
                         (UINT32 *)&MaxOrder
                         );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - no item found for thist test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }


  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }
    gtBS->FreePool (TempDevicePathStr);

    //
    //get BarIndex/Offset and width.
    //
    BarIndex = 0;
    Status = GetBarIndexByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               &BarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //then get Offset.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_IO, BarIndex, AddressOffset + AddressLength)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //allocate BackupBuffer.
    //
    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //first read the data out.
    //
    Status = PciIo->Io.Read (
                         PciIo,
                         PciIoWidth,
                         BarIndex,
                         AddressOffset,
                         Count,
                         BackupBuffer
                         );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    RepeatNum = 1;
    if (BarIndex >= 0 && BarIndex <= 5) {
      RepeatNum = 2;
    }

    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        AddressOffset = PciIoDevice->BarAddress[BarIndex] + AddressOffset;
        BarIndex      = EFI_PCI_IO_PASS_THROUGH_BAR;
      }
      //
      //record test envionment.
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IoWrite env. \r\n"
                     L"%a:%d:PciIoWidth - %s, BarIndex - %02xh, Count- %xh, AddressOffset - %lXh\r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     WidthCode[PciIoWidth],
                     BarIndex,
                     (UINT32)Count,
                     AddressOffset
                     );

      //
      //first write the buffer into destination address range.
      //
      Status = PciIo->Io.Write (
                           PciIo,
                           PciIoWidth,
                           BarIndex,
                           AddressOffset,
                           Count,
                           Buffer
                           );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid030,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - Write data to Io address space",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[PciIoWidth]
                     );
      //
      //then read out the data in destination address range.
      //
      Status = PciIo->Io.Read (
                  PciIo,
                  PciIoWidth,
                  BarIndex,
                  AddressOffset,
                  Count,
                  ReadBuffer
                  );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      //the data read out must be the same as write into.
      //
      if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid031,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - the data read must equal with the data written",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      //
      //write the data using EfiPciIoWidthFifoUintX.
      //
      Status =PciIo->Io.Write (
                          PciIo,
                          SecondWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          Buffer
                          );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid032,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - write the data with EfiPciIoWidthFifoX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );

      //
      //read the data out again using EfiPciIoWidthUintX.
      //
      PciIo->Io.Read (
                  PciIo,
                  PciIoWidth,
                  BarIndex,
                  AddressOffset,
                  Count,
                  ReadBuffer
                  );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      //the first data unit must be the last data unit and
      //the other data unchange.
      //

      if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count - 1) * UnitLength, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if (Count > 1) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + UnitLength, (UINT8 *)Buffer + UnitLength, AddressLength - UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid033,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - with EfiPciIoWidthFifoUintX the first data unit must be the last data unit.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

      //
      //write the data using EfiPciIoWidthFillUintX.
      //
      Status =PciIo->Io.Write (
                          PciIo,
                          ThirdWidth,
                          BarIndex,
                          AddressOffset,
                          Count,
                          Buffer
                          );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid034,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write - write the data with EfiPciIoWidthFillX",
                     L"%a:%d:Status - %r, Width - %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );

      //
      //read out the data again using EfiPciIoWidthUintX.
      //
      PciIo->Io.Read (
                  PciIo,
                  PciIoWidth,
                  BarIndex,
                  AddressOffset,
                  Count,
                  ReadBuffer
                  );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      //all the data unit read out must be the first data unit in the address  space.
      //

      for (Index = 0; Index < Count; Index++) {
        if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
      //
      //record assertion
      //

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestFunction_1AssertionGuid035,
                     L"EFI_PCI_IO_PROTOCOL.Io.Write -with EfiPciIoWidthFillUintX all the data unit read out must be the first data unit in the address space.",
                     L"%a:%d",
                     __FILE__,
                     (UINTN)__LINE__
                     );

    }

    //
    //at last write the data back.
    //
    Status = PciIo->Io.Write (
                         PciIo,
                         PciIoWidth,
                         BarIndex,
                         AddressOffset,
                         Count,
                         BackupBuffer
                         );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_1AssertionGuid036,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - Write back Data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //free resource.
    //
    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);
  }

  //
  //free resources.
  //
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
