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

  PciRootBridgeIoBBTestFunction_1.c

Abstract:

  function test case source file for Pci Root Bridge Io Protocol

--*/


#include "SctLib.h"
#include "PciRootBridgeIoBBTestMain.h"
#include "PciRootBridgeIoBBTestSupport.h"



#define SECTION_NAME_POLLMEM_TEST           L"PollMem_Func"
#define SECTION_NAME_POLLIO_TEST            L"PollIo_Func"
#define SECTION_NAME_MEMREAD_TEST           L"MemRead_Func"
#define SECTION_NAME_MEMWRITE_TEST          L"MemWrite_Func"
#define SECTION_NAME_IOREAD_TEST            L"IoRead_Func"
#define SECTION_NAME_IOWRITE_TEST           L"IoWrite_Func"

/**
 *  Entrypoint for PollMem() Interface manual Test.
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
  EFI_STATUS                              Status;
  UINT64                                  Address;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINT32                                  Length;
  UINT64                                  Mask;
  UINT64                                  TargetValue;
  UINT64                                  AlternateValue;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  while (TRUE) {

    if (!QueryGoOnTesting ()) {
      break;
    }


    //
    //get Address
    //
    Address = 0;
    Status = GetAddress (&Address);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidth (&RootBridgeIoWidth);

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Length = 1;
        break;
      case EfiPciWidthUint16:
        Length = 2;
        break;
      case EfiPciWidthUint32:
        Length = 4;
        break;
      case EfiPciWidthUint64:
        Length = 8;
        break;
      default:
        Length = 0;
        break;
    }
    if (Length == 0) {
      SctPrint (L"Invalid PciRootBridgeIoWidth -%s for PollMem\n", WidthCode[RootBridgeIoWidth]);
      continue;
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
    //call PollMemCheckPoint three times with different Mask value.
    //

    //
    //first with 1 bit set with 1.
    //

    Mask = 0x01;
    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with multi-bit set with 1.
    //

    Mask = 0x0F;
    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with all bit set with 1.
    //

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Mask = MASK8BIT;
        break;
      case EfiPciWidthUint16:
        Mask = MASK16BIT;
        break;
      case EfiPciWidthUint32:
        Mask = MASK32BIT;
        break;
      default:
        Mask = MASK64BIT;
        break;
    }

    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  the internal sub function to run the check point for PollMem.
 *  @param RootBridgeIo the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL interface.
 *  @param StandardLib the Standard Test Lib interface.
 *  @param RootBridgeIoWidth the root bridge io width.
 *  @param Address the Address.
 *  @param Mask the Mask value.
 *  @param TargetValue the Target Value for this address.
 *  @param AlternateValue the Alternate Value for this address.
 *  @return EFI_SUCCESS the check point was checked successfully.
 */
EFI_STATUS
EFIAPI
PollMemCheckPoint (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH RootBridgeIoWidth,
  IN  UINT64                                Address,
  IN  UINT64                                Mask,
  IN  UINT64                                TargetValue,
  IN  UINT64                                AlternateValue
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
  Status = RootBridgeIo->Mem.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               &OldValue
                               );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - read from memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //set Target value.
  //

  switch (RootBridgeIoWidth) {
    case EfiPciWidthUint8:
      TargetValue    = (UINT64)(TargetValue & MASK8BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK8BIT);
      break;
    case  EfiPciWidthUint16:
      TargetValue    = (UINT64)(TargetValue & MASK16BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK16BIT);
      break;
    case  EfiPciWidthUint32:
      TargetValue    = (UINT64)(TargetValue & MASK32BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK32BIT);
      break;
    case  EfiPciWidthUint64:
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

  EventContext->RootBridgeIo      = RootBridgeIo;
  EventContext->StandardLib       = StandardLib;
  EventContext->RootBridgeIoWidth  = RootBridgeIoWidth;
  EventContext->Address           = Address;
  EventContext->DestValue         = TargetValue;

  //
  //create a timer event.
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) EventNotifyWriteMem,
                   EventContext,
                   &TimeOutEvent
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\n"
                   L"%a:%d.\n",
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
                 L"PollMem env\n"
                 L"%a:%d:RootBridgeIoWidth - %s,Mask - %LXh,TargetValue - %LXh,AlternateValue - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 WidthCode[RootBridgeIoWidth],
                 Mask,
                 TargetValue,
                 AlternateValue
                 );

  //
  //write alternate value to the destinaion address.
  //

  Status = RootBridgeIo->Mem.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write alternate value to memory",
                 L"%a:%d:Status - %r, Alternate Value - %LXh",
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
                   L"error with tBS->SetTimer()"
                   L"%a:%d:Status - %r",
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
  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid001,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - Target address set the valid value before time out",
                 L"%a:%d:Status - %r,Target Value - %LXh, Result - %LXh",
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
  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid002,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - Target address has the valid value before calling",
                 L"%a:%d:Status - %r, target value - %LXh, Result Value - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );

  //
  //set the alternate value on the address
  //

  Status = RootBridgeIo->Mem.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - write the alternate value again",
                 L"%a:%d:Status - %r, alternate value - %LXh",
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
  TimeOutValue = 0L;
  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid003,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - with delay equal 0",
                 L"%a:%d:Status - %r,alternate value - %LXh,Result - %LXh",
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
  TimeOutValue  = 5 * 10000000;
  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid004,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - with 5 seconds delay",
                 L"%a:%d:Status - %r,alternate Value -%LXh, Result - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );
  //
  //write orginal value back to the destinaiton address.
  //
  RootBridgeIo->Mem.Write (
                      RootBridgeIo,
                      RootBridgeIoWidth,
                      Address,
                      1,
                      &OldValue
                      );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PollMem() Interface automatically Test.
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
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  Address;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINT32                                  Length;
  UINT64                                  Mask;
  UINT64                                  TargetValue;
  UINT64                                  AlternateValue;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem -not found the profile.\n"
                   L"%a:%d: Status - %r \n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

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

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem -no item found for this test case.\n"
                   L"%a:%d.\n",
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    Length = 0;
    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Length = 1;
        break;
      case EfiPciWidthUint16:
        Length = 2;
        break;
      case EfiPciWidthUint32:
        Length = 4;
        break;
      case EfiPciWidthUint64:
        Length = 8;
        break;
      default:
        break;
    }

    if (Length == 0) {

      //
      //invalid PciIoWidth.
      //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem -Invalid Width for PollMem.\n"
                   L"%a:%d, Width -%s.\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   WidthCode[RootBridgeIoWidth]
                   );
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
    //call PollMemCheckPoint three times with different Mask value.
    //

    //
    //first with 1 bit set with 1.
    //

    Mask = 0x01;
    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with multi-bit set with 1.
    //

    Mask = 0x0F;
    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with all bit set with 1.
    //

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Mask = MASK8BIT;
        break;
      case EfiPciWidthUint16:
        Mask = MASK16BIT;
        break;
      case EfiPciWidthUint32:
        Mask = MASK32BIT;
        break;
      default:
        Mask = MASK64BIT;
        break;
    }

    PollMemCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

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
 *  Entrypoint for PollIo() Interface manual Test.
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
  EFI_STATUS                              Status;
  UINT64                                  Address;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINT32                                  Length;
  UINT64                                  Mask;
  UINT64                                  TargetValue;
  UINT64                                  AlternateValue;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  while (TRUE) {

    if (!QueryGoOnTesting ()) {
      break;
    }


    //
    //get Address
    //
    Address = 0;
    Status = GetAddress (&Address);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidth (&RootBridgeIoWidth);

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Length = 1;
        break;
      case EfiPciWidthUint16:
        Length = 2;
        break;
      case EfiPciWidthUint32:
        Length = 4;
        break;
      case EfiPciWidthUint64:
        Length = 8;
        break;
      default:
        Length = 0;
        break;
    }

    if (Length == 0) {
      SctPrint (L"Invalid RootBridgeIoWidth -%s for PollIo\n", WidthCode[RootBridgeIoWidth]);
      continue;
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
    //call PollIoCheckPoint three times with different Mask value.
    //

    //
    //first with 1 bit set with 1.
    //

    Mask = 0x01;
    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with multi-bit set with 1.
    //

    Mask = 0x0F;
    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with all bit set with 1.
    //

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Mask = MASK8BIT;
        break;
      case EfiPciWidthUint16:
        Mask = MASK16BIT;
        break;
      case EfiPciWidthUint32:
        Mask = MASK32BIT;
        break;
      default:
        Mask = MASK64BIT;
        break;
    }

    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  the internal sub function to run the check point for PollIo.
 *  @param RootBridgeIo the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL interface.
 *  @param StandardLib the Standard Test Lib interface.
 *  @param RootBridgeIoWidth the PCI root bridge Io Width .
 *  @param Address the Address Offset.
 *  @param Mask the Mask value.
 *  @param TargetValue the Target Value for this address.
 *  @param AlternateValue the Alternate Value for this address.
 *  @return EFI_SUCCESS the check point was checked successfully.
 */
EFI_STATUS
EFIAPI
PollIoCheckPoint (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo,
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH RootBridgeIoWidth,
  IN  UINT64                                Address,
  IN  UINT64                                Mask,
  IN  UINT64                                TargetValue,
  IN  UINT64                                AlternateValue
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
  Status = RootBridgeIo->Io.Read (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              &OldValue
                              );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - read from Io space",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //set Target value.
  //

  switch (RootBridgeIoWidth) {
    case EfiPciWidthUint8:
      TargetValue    = (UINT64)(TargetValue & MASK8BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK8BIT);
      break;
    case  EfiPciWidthUint16:
      TargetValue    = (UINT64)(TargetValue & MASK16BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK16BIT);
      break;
    case  EfiPciWidthUint32:
      TargetValue    = (UINT64)(TargetValue & MASK32BIT);
      AlternateValue = (UINT64)(AlternateValue & MASK32BIT);
      break;
    case  EfiPciWidthUint64:
      break;
    default:
      return EFI_INVALID_PARAMETER;
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

  EventContext->RootBridgeIo      = RootBridgeIo;
  EventContext->StandardLib       = StandardLib;
  EventContext->RootBridgeIoWidth  = RootBridgeIoWidth;
  EventContext->Address           = Address;
  EventContext->DestValue         = TargetValue;

  //
  //create a timer event.
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) EventNotifyWriteIo,
                   EventContext,
                   &TimeOutEvent
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\n"
                   L"%a:%d.\n",
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
                 L"PollIo env\n"
                 L"%a:%d:RootBridgeIoWidth - %s,Mask - %LXh,TargetValue - %LXh,AlternateValue - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 WidthCode[RootBridgeIoWidth],
                 Mask,
                 TargetValue,
                 AlternateValue
                 );

  //
  //write alternate value to the destinaion address.
  //

  Status = RootBridgeIo->Io.Write (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write alternate value to Io space",
                 L"%a:%d:Status - %r, Alternate Value - %LXh",
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
                   L"error with tBS->SetTimer()"
                   L"%a:%d:Status - %r",
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

  Result = 0x00;
  TimeOutValue = 5 * 10000000;

  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid005,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - Target address set the valid value before time out",
                 L"%a:%d:Status - %r,Target Value - %LXh, Result - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );

  //
  //check point 2.
  //
  //call PollIo again it will return immediately with EFI_SUCCESS.
  //

  Result = 0x00;
  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid006,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - Target address has the valid value before calling",
                 L"%a:%d:Status - %r, target value - %LXh, Result Value - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 TargetValue,
                 Result
                 );

  //
  //set the alternate value on the address
  //

  Status = RootBridgeIo->Io.Write (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write() - write the alternate value again",
                 L"%a:%d:Status - %r, alternate value - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue
                 );

  //
  //check point 3.
  //
  //destination address has invalid value,PollIo with delay equal 0.
  //

  Result = 0x00;
  TimeOutValue = 0x0;
  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid007,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - with delay equal 0",
                 L"%a:%d:Status - %r,alternate value - %LXh,Result - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );

  //
  //check point 4.
  //destination address has invalid value,PollIo with 5 seconds delay .
  //

  Result = 0x00;
  TimeOutValue = 5 * 10000000;
  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
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
                 gPciRootBridgeIoBBTestFunction_1AssertionGuid008,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - with 5 seconds delay",
                 L"%a:%d:Status - %r,alternate Value -%LXh, Result - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AlternateValue,
                 Result
                 );
  //
  //write orginal value back to the destinaiton address.
  //
  RootBridgeIo->Io.Write (
                     RootBridgeIo,
                     RootBridgeIoWidth,
                     Address,
                     1,
                     &OldValue
                     );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PollIo() Interface automatically Test.
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
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  Address;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINT32                                  Length;
  UINT64                                  Mask;
  UINT64                                  TargetValue;
  UINT64                                  AlternateValue;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo -not found the profile.\n"
                   L"%a:%d.\n",
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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo -no item found for this test case.\n"
                   L"%a:%d.\n",
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
               SECTION_NAME_POLLIO_TEST,
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLIO_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    Length = 0;
    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Length = 1;
        break;
      case EfiPciWidthUint16:
        Length = 2;
        break;
      case EfiPciWidthUint32:
        Length = 4;
        break;
      case EfiPciWidthUint64:
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
               SECTION_NAME_POLLIO_TEST,
               Index,
               &AlternateValue
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call PollIoCheckPoint three times with different Mask value.
    //

    //
    //first with 1 bit set with 1.
    //

    Mask = 0x01;
    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with multi-bit set with 1.
    //

    Mask = 0x0F;
    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

    //
    //then with all bit set with 1.
    //

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        Mask = MASK8BIT;
        break;
      case EfiPciWidthUint16:
        Mask = MASK16BIT;
        break;
      case EfiPciWidthUint32:
        Mask = MASK32BIT;
        break;
      default:
        Mask = MASK64BIT;
        break;
    }

    PollIoCheckPoint (
      RootBridgeIo,
      StandardLib,
      RootBridgeIoWidth,
      Address,
      Mask,
      TargetValue,
      AlternateValue
      );

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
 *  Entrypoint for Mem.Read() Interface automatically Test.
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
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  Address;
  UINT32                                  AddressLength;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   FirstWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   SecondWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   ThirdWidth;
  UINT32                                  UnitLength;
  UINT64                                  Mask;
  UINTN                                   SubIndex;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read -not found the profile.\n"
                   L"%a:%d.\n",
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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read -no item found for this test case.\n"
                   L"%a:%d.\n",
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
               SECTION_NAME_MEMREAD_TEST,
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    FirstWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               Index,
               &FirstWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (FirstWidth) {
      case EfiPciWidthUint8:
        UnitLength  = 1;
        Mask        = MASK8BIT;
        SecondWidth = EfiPciWidthFifoUint8;
        ThirdWidth  = EfiPciWidthFillUint8;
        break;

      case EfiPciWidthUint16:
        UnitLength  = 2;
        Mask        = MASK16BIT;
        SecondWidth = EfiPciWidthFifoUint16;
        ThirdWidth  = EfiPciWidthFillUint16;
        break;

      case EfiPciWidthUint32:
        UnitLength  = 4;
        Mask        = MASK32BIT;
        SecondWidth = EfiPciWidthFifoUint32;
        ThirdWidth  = EfiPciWidthFillUint32;
        break;

      default:
        UnitLength  = 8;
        Mask        = MASK64BIT;
        SecondWidth = EfiPciWidthFifoUint64;
        ThirdWidth  = EfiPciWidthFillUint64;
        break;
    }

    //
    //get address length.
    //

    AddressLength = 0;

    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //get target unit value.
    //

    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {

      //
      //create data units by program.
      //

      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {

        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }

      for (SubIndex = 0; SubIndex < AddressLength; SubIndex++) {
        Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
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

    Status = RootBridgeIo->Mem.Read (
                                 RootBridgeIo,
                                 FirstWidth,
                                 Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid009,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - Read data out return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    // write the buffer into destination address range.
    //

    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //then read out the data in destination address range.
    //

    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
                                Count,
                                ReadBuffer
                                );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid010,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid011,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - the data read out must be the same as what written",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //read out the data using EfiPciWidthFifoUintX.
    //

    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                SecondWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid012,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data with EfiPciWidthFifoX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );


    //
    //the data read out must be the same as the first data unit.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid013,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read -each data unit read out must equal the first data unit at the start address",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //set the readbuffer with all the unit value as the first unit value in Buffer.
    //
    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      SctCopyMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength);
    }

    //
    //read out the data using EfiPciIoWidthFillUintX.
    //

    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                ThirdWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid014,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data with EfiPciIoWidthFillX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
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

    for (SubIndex = 1; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid015,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - the first data unit must equal the last data unit in the address range",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );


    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write back Data.",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

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
 *  Entrypoint for Mem.Write() Interface automatically Test.
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
  EFI_STATUS                              Status;
  UINT64                                  Address;
  UINT32                                  AddressLength;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   FirstWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   SecondWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   ThirdWidth;
  UINT32                                  UnitLength;
  UINT64                                  Mask;
  UINTN                                   SubIndex;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write -not found the profile.\n"
                   L"%a:%d.\n",
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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read -no item found for this test case.\n"
                   L"%a:%d.\n",
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
               SECTION_NAME_MEMWRITE_TEST,
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    FirstWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               Index,
               &FirstWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (FirstWidth) {
      case EfiPciWidthUint8:
        UnitLength  = 1;
        Mask        = MASK8BIT;
        SecondWidth = EfiPciWidthFifoUint8;
        ThirdWidth  = EfiPciWidthFillUint8;
        break;

      case EfiPciWidthUint16:
        UnitLength  = 2;
        Mask        = MASK16BIT;
        SecondWidth = EfiPciWidthFifoUint16;
        ThirdWidth  = EfiPciWidthFillUint16;
        break;

      case EfiPciWidthUint32:
        UnitLength  = 4;
        Mask        = MASK32BIT;
        SecondWidth = EfiPciWidthFifoUint32;
        ThirdWidth  = EfiPciWidthFillUint32;
        break;

      default:
        UnitLength  = 8;
        Mask        = MASK64BIT;
        SecondWidth = EfiPciWidthFifoUint64;
        ThirdWidth  = EfiPciWidthFillUint64;
        break;
    }

    //
    //get address length.
    //

    AddressLength = 0;

    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //get target unit value.
    //

    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {

      //
      //create data units by program.
      //

      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {

        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }

      for (SubIndex = 0; SubIndex < AddressLength; SubIndex++) {
        Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
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

    Status = RootBridgeIo->Mem.Read (
                                 RootBridgeIo,
                                 FirstWidth,
                                 Address,
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - Read data out",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    // write the buffer into destination address range.
    //

    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid016,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write data to memory address space return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //then read out the data in destination address range.
    //

    Status = RootBridgeIo->Mem.Read (
                                 RootBridgeIo,
                                 FirstWidth,
                                 Address,
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
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data from the address space",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid017,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - the data read out must be the same as what written",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //write the data using EfPciWidthFifoUintX.
    //
    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                SecondWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid018,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write data with EfiPciWidthFifoUintX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //read out the data using EfiPciIoWidthUintX.
    //

    Status = RootBridgeIo->Mem.Read (
                                 RootBridgeIo,
                                 FirstWidth,
                                 Address,
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
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    //
    //the data read out the first data unit must be the same as the last data
    //unit written and the other data unit remain unchange.
    //

    AssertionType = EFI_TEST_ASSERTION_PASSED;

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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid019,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read -the first data unit read out must be the same as written last data unit.",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //write the data using EfiPciIoWidthFillUintX.
    //
    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                ThirdWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid020,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write data with EfiPciWidthFillUintX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );
    //
    //read out the data
    //

    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid021,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out the data",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //the data uint read out must be the same as the first data unit has been
    //written.
    //

    AssertionType = EFI_TEST_ASSERTION_PASSED;

    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid022,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - all the data unit must equal the first data unit in the address range",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );


    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid023,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write back Data.",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

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
 *  Entrypoint for Io.Read() Interface automatically Test.
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
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  Address;
  UINT32                                  AddressLength;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   FirstWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   SecondWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   ThirdWidth;
  UINT32                                  UnitLength;
  UINT64                                  Mask;
  UINTN                                   SubIndex;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read -not found the profile.\n"
                   L"%a:%d.\n",
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

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read -no item found for this test case.\n"
                   L"%a:%d.\n",
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
               SECTION_NAME_IOREAD_TEST,
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    FirstWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               Index,
               &FirstWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (FirstWidth) {
      case EfiPciWidthUint8:
        UnitLength  = 1;
        Mask        = MASK8BIT;
        SecondWidth = EfiPciWidthFifoUint8;
        ThirdWidth  = EfiPciWidthFillUint8;
        break;

      case EfiPciWidthUint16:
        UnitLength  = 2;
        Mask        = MASK16BIT;
        SecondWidth = EfiPciWidthFifoUint16;
        ThirdWidth  = EfiPciWidthFillUint16;
        break;

      case EfiPciWidthUint32:
        UnitLength  = 4;
        Mask        = MASK32BIT;
        SecondWidth = EfiPciWidthFifoUint32;
        ThirdWidth  = EfiPciWidthFillUint32;
        break;

      default:
        UnitLength  = 8;
        Mask        = MASK64BIT;
        SecondWidth = EfiPciWidthFifoUint64;
        ThirdWidth  = EfiPciWidthFillUint64;
        break;
    }

    //
    //get address length.
    //

    AddressLength = 0;

    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //get target unit value.
    //

    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_IOREAD_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {

      //
      //create data units by program.
      //

      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {

        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }

      for (SubIndex = 0; SubIndex < AddressLength; SubIndex++) {
        Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
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

    Status = RootBridgeIo->Io.Read (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid024,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    // write the buffer into destination address range.
    //

    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
                               Count,
                               Buffer
                               );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write data to memory address space",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //then read out the data in destination address range.
    //

    Status =RootBridgeIo->Io.Read (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid025,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid026,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - the data read out must be the same as what written",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );
    //
    //read out the data using EfiPciWidthFifoUintX.
    //

    Status =RootBridgeIo->Io.Read (
                               RootBridgeIo,
                               SecondWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid027,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the data with EfiPciWidthFifoX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //the data read out must be the same as the first data unit.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid028,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read -each data unit read out must equal the first data unit at the start address",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //set the readbuffer with all the unit value as the first unit value in Buffer.
    //
    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      SctCopyMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength);
    }

    //
    //read out the data using EfiPciIoWidthFillUintX.
    //

    Status =RootBridgeIo->Io.Read (
                               RootBridgeIo,
                               ThirdWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid029,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the data with EfiPciIoWidthFillX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Width -%s",
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

    for (SubIndex = 1; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid030,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - the first data unit must equal the last data unit in the address range",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );


    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write back Data.",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

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
 *  Entrypoint for Io.Write() Interface automatically Test.
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
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  Address;
  UINT32                                  AddressLength;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   FirstWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   SecondWidth;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   ThirdWidth;
  UINT32                                  UnitLength;
  UINT64                                  Mask;
  UINTN                                   SubIndex;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  UINTN                                   Index;
  UINTN                                   MaxOrder;
  EFI_INI_FILE_HANDLE                     FileHandle;
  CHAR16                                  *FilePath;
  CHAR16                                  *PciDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

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
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write -not found the profile.\n"
                   L"%a:%d.\n",
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

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write -no item found for this test case.\n"
                   L"%a:%d.\n",
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
               SECTION_NAME_IOWRITE_TEST,
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
    //get use input for Address and width.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               Index,
               &Address
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    FirstWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               Index,
               &FirstWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (FirstWidth) {
      case EfiPciWidthUint8:
        UnitLength  = 1;
        Mask        = MASK8BIT;
        SecondWidth = EfiPciWidthFifoUint8;
        ThirdWidth  = EfiPciWidthFillUint8;
        break;

      case EfiPciWidthUint16:
        UnitLength  = 2;
        Mask        = MASK16BIT;
        SecondWidth = EfiPciWidthFifoUint16;
        ThirdWidth  = EfiPciWidthFillUint16;
        break;

      case EfiPciWidthUint32:
        UnitLength  = 4;
        Mask        = MASK32BIT;
        SecondWidth = EfiPciWidthFifoUint32;
        ThirdWidth  = EfiPciWidthFillUint32;
        break;

      default:
        UnitLength  = 8;
        Mask        = MASK64BIT;
        SecondWidth = EfiPciWidthFifoUint64;
        ThirdWidth  = EfiPciWidthFillUint64;
        break;
    }

    //
    //get address length.
    //

    AddressLength = 0;

    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //get target unit value.
    //

    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {

      //
      //create data units by program.
      //

      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {

        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }

      for (SubIndex = 0; SubIndex < AddressLength; SubIndex++) {
        Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
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
    Status = RootBridgeIo->Io.Read (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    // write the buffer into destination address range.
    //

    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid031,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write data return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    //
    //then read out the data in destination address range.
    //

    Status =RootBridgeIo->Io.Read (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid032,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - the data read out must be the same as what written",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    //
    //write the data using EfPciWidthFifoUintX.
    //
    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               SecondWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid033,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write data with EfiPciWidthFifoUintX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //read out the data using EfiPciIoWidthUintX.
    //

    Status = RootBridgeIo->Io.Read (
                                RootBridgeIo,
                                FirstWidth,
                                Address,
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
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the data",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    //
    //the data read out the first data unit must be the same as the last data
    //unit written and the other data unit remain unchange.
    //

    AssertionType = EFI_TEST_ASSERTION_PASSED;

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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid034,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write -the first data unit read out must be the same as written last data unit.",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );


    //
    //write the data using EfiPciIoWidthFillUintX.
    //
    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               ThirdWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid035,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write data with EfiPciWidthFillUintX return status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );

    //
    //read out the data
    //

    Status =RootBridgeIo->Io.Read (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read - read out the data",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    //
    //the data uint read out must be the same as the first data unit has been
    //written.
    //

    AssertionType = EFI_TEST_ASSERTION_PASSED;

    for (SubIndex = 0; SubIndex < Count; SubIndex++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + SubIndex * UnitLength, Buffer, UnitLength) != 0) {
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid036,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - all the data unit must equal the first data unit in the address range",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );


    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Io.Write (
                               RootBridgeIo,
                               FirstWidth,
                               Address,
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
                   gPciRootBridgeIoBBTestFunction_1AssertionGuid037,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write - Write back Data.",
                   L"%a:%d:Status - %r, Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

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