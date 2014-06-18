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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PciRootBridgeIoBBTestFunction_2.c

Abstract:

  function test case source file for Pci Root Bridge Io Protocol

--*/

#include "SctLib.h"
#include "PciRootBridgeIoBBTestMain.h"
#include "PciRootBridgeIoBBTestSupport.h"




#define SECTION_NAME_PCIREAD_TEST            L"PciRead_Func"
#define SECTION_NAME_PCIWRITE_TEST           L"PciWrite_Func"
#define SECTION_NAME_COPYMEM_TEST            L"CopyMem_Func"
#define SECTION_NAME_ATTRIBUTES_TEST         L"Attributes_Func"


/**
 *  Entrypoint for Pci.Read() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.9
//
EFI_STATUS
PciRead_Func (
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
  UINTN                                   RepeatIndex;
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
                   &StandardLib
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
                   &ProfileLib
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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read -not found the profile.\n"
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
                         SECTION_NAME_PCIREAD_TEST,
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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read -no item found for this test case.\n"
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
               SECTION_NAME_PCIREAD_TEST,
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
               SECTION_NAME_PCIREAD_TEST,
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
               SECTION_NAME_PCIREAD_TEST,
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
               SECTION_NAME_PCIREAD_TEST,
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
               SECTION_NAME_PCIREAD_TEST,
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

    Status = RootBridgeIo->Pci.Read (
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid001,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - Read data out",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    Address = Address & 0xFFFFFFFF;

    for (RepeatIndex = 0; RepeatIndex < 2; RepeatIndex++) {

      if (RepeatIndex == 1) {
        Address = (Address & 0xFFFFFF00) | SctLShiftU64 ((Address & 0xFF), 32);
      }

      //
      // write the buffer into destination address range.
      //

      Status =RootBridgeIo->Pci.Write (
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
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write data to configuration address space",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[FirstWidth]
                     );

      //
      //then read out the data in destination address range.
      //

      Status =RootBridgeIo->Pci.Read (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid002,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data return status should be EFI_SUCCESS",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid003,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - the data read out must be the same as what written",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[FirstWidth]
                     );
      //
      //read out the data using EfiPciWidthFifoUintX.
      //

      Status =RootBridgeIo->Pci.Read (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid004,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data with EfiPciWidthFifoX return status should be EFI_SUCCESS",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid005,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read -each data unit read out must equal the first data unit at the start address",
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

      Status =RootBridgeIo->Pci.Read (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid006,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data with EfiPciIoWidthFillX the return status should be EFI_SUCCESS",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid007,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - the first data unit must equal the last data unit in the address range",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );


    }

    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Pci.Write (
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write back Data.",
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
 *  Entrypoint for Pci.Write() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.10
//
EFI_STATUS
PciWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
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
  UINTN                                   RepeatIndex;
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
                   &StandardLib
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
                   &ProfileLib
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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write -not found the profile.\n"
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
                         SECTION_NAME_PCIWRITE_TEST,
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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write -no item found for this test case.\n"
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
               SECTION_NAME_PCIWRITE_TEST,
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
               SECTION_NAME_PCIWRITE_TEST,
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
               SECTION_NAME_PCIWRITE_TEST,
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
               SECTION_NAME_PCIWRITE_TEST,
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
               SECTION_NAME_PCIWRITE_TEST,
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

    Status = RootBridgeIo->Pci.Read (
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
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - Read data out",
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[FirstWidth]
                   );


    Address = Address & 0xFFFFFFFF;

    for (RepeatIndex = 0; RepeatIndex < 2; RepeatIndex++) {

      if (RepeatIndex == 1) {
        Address = (Address & 0xFFFFFF00) | SctLShiftU64 ((Address & 0xFF), 32);
      }

      //
      // write the buffer into destination address range.
      //

      Status =RootBridgeIo->Pci.Write (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid008,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write data return status should be EFI_SUCCESS",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[FirstWidth]
                     );

      //
      //then read out the data in destination address range.
      //

      Status =RootBridgeIo->Pci.Read (
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
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data from the address space",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid009,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - the data read out must be the same as what written",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[FirstWidth]
                     );

      //
      //write the data using EfPciWidthFifoUintX.
      //
      Status =RootBridgeIo->Pci.Write (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid010,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write data with EfiPciWidthFifoUintX return status should be EFI_SUCCESS",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );

      //
      //read out the data using EfiPciIoWidthUintX.
      //

      Status =RootBridgeIo->Pci.Read (
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
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid011,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write -the first data unit read out must be the same as written last data unit.",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[SecondWidth]
                     );


      //
      //write the data using EfiPciIoWidthFillUintX.
      //
      Status =RootBridgeIo->Pci.Write (
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid012,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write data with EfiPciWidthFillUintX return status should be EFI_SUCCESS",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );


      //
      //read out the data
      //

      Status =RootBridgeIo->Pci.Read (
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
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read - read out the data",
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
                     gPciRootBridgeIoBBTestFunction_2AssertionGuid013,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - all the data unit must equal the first data unit in the address range",
                     L"%a:%d:Status - %r,Width -%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     WidthCode[ThirdWidth]
                     );

    }

    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Pci.Write (
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid014,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write - Write back Data.",
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
 *  Entrypoint for SctCopyMem () Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.11
//
EFI_STATUS
CopyMem_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT32                                  UnitLength;
  UINT8                                   *Buffer;
  UINTN                                   BufferSize;
  VOID                                    *ReadBuffer;
  VOID                                    *BackupBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  UINT64                                  Address;
  UINT32                                  AddressLength;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE           *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   RootBridgeIoWidth;
  UINTN                                   SubIndex;
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
                   &StandardLib
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
                   &ProfileLib
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

  gtST->ConOut->OutputString (
                  gtST->ConOut,
                  L"Test Root Bridge Io Protocol SctCopyMem () interface.\n"
                  );

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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem -not found the profile.\n"
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
                         SECTION_NAME_COPYMEM_TEST,
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
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem -no item found for this test case.\n"
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
               SECTION_NAME_COPYMEM_TEST,
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
    //get use input for Address/Length and width.
    //

    //
    //get Addresst.
    //

    Address = 0;
    Status = GetAddressByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               Index,
               &Address
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (RootBridgeIoWidth) {
      case EfiPciWidthUint8:
        UnitLength  = 1;
        break;
      case EfiPciWidthUint16:
        UnitLength  = 2;
        break;
      case EfiPciWidthUint32:
        UnitLength  = 4;
        break;
      case EfiPciWidthUint64:
        UnitLength  = 8;
        break;
      default:
        UnitLength = 0;
        break;
    }

    if (UnitLength == 0) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem -Invalid Width for CopyMem.\n"
                     L"%a:%d:Width -%d.\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     RootBridgeIoWidth
                     );

      continue;
    }
    //
    //get address length.
    //

    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               Index,
               &AddressLength
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    if (Count < 3) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //AddressLength is the full Address length to be impact, the BufferSize is
    //the data length every time read and write operation impacted.
    //

    BufferSize = AddressLength / (2 * UnitLength);
    Count      = BufferSize / UnitLength;
    BufferSize = (UINT32)(Count * UnitLength);

    if (Count == 0) {
      continue;
    }

    //
    //get target unit value.
    //

    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if (EFI_ERROR(Status)) {

      //
      //create data units by program.
      //
      Buffer = (UINT8 *)SctAllocatePool (BufferSize);
      if (Buffer == NULL) {

        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (SubIndex = 0; SubIndex < BufferSize; SubIndex++) {
        Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
      }
    }

    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (BufferSize);
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
    //allocate backup buffer.
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
                                 RootBridgeIoWidth,
                                 Address,
                                 AddressLength / UnitLength,
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //first write the buffer into the beginning address.
    //
    Status = RootBridgeIo->Mem.Write (
                                 RootBridgeIo,
                                 RootBridgeIoWidth,
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
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //Copying Data between non-overlapping regions.
    //

    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             Address + BufferSize,
                             Address,
                             Count
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid015,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between non-overlapping regions.",
                   L"%a:%d:Status - %r,Src Address -%LXh,Dest Address -%LXh,Count -%xh,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Address,
                   Address + BufferSize,
                   Count,
                   WidthCode[RootBridgeIoWidth]
                   );
    //
    //then read out the data compare if they are equal with what have been write.
    //

    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                RootBridgeIoWidth,
                                Address + BufferSize,
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
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out copied data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid016,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between non-overlapping regions the destination data must be the same as source data",
                   L"%a:%d: Compare memory of source address and dest address",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //copy data between overlap regions with destination address > source address.
    //

    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             Address + BufferSize / 2,
                             Address,
                             Count
                             );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid017,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions dest address > src address.",
                   L"%a:%d:Status - %r,Src Address -%LXh,Dest Address -%LXh,Count -%xh,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Address,
                   Address + BufferSize/2,
                   Count,
                   WidthCode[RootBridgeIoWidth]
                   );

    //
    //then read out the data compare if they are equal with what have been copied.
    //
    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                RootBridgeIoWidth,
                                Address + BufferSize / 2,
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
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out copied data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertoin
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid018,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions (Dest > src) the destination data must be the same as source data",
                   L"%a:%d: compare memory of source address and dest address",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //copy data between over-lapping region with dest address < src address.
    //
    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             Address,
                             Address + BufferSize / 2,
                             Count
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid019,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions with Dest < Src.",
                   L"%a:%d:Status - %r,Src Address -%LXh,Dest Address -%LXh,Count -%xh,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Address + BufferSize/2,
                   Address,
                   Count,
                   WidthCode[RootBridgeIoWidth]
                   );

    //
    //then read out the data compare if they are equal with what have been write.
    //
    Status =RootBridgeIo->Mem.Read (
                                RootBridgeIo,
                                RootBridgeIoWidth,
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
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read - read out copied data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid020,
                   L"EFI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem - Copying Data between non-overlapping regions the destination data must be the same as the source data",
                   L"%a:%d: compare memory of source address and dest address.",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //at last write the data back.
    //

    Status =RootBridgeIo->Mem.Write (
                                RootBridgeIo,
                                RootBridgeIoWidth,
                                Address,
                                AddressLength / UnitLength,
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
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //free resource.
    //

    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
    gtBS->FreePool (BackupBuffer);

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
 *  Entrypoint for Map() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.12
//
EFI_STATUS
Map_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  VOID                                         *HostAddress;
  UINTN                                        NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                         DeviceAddress;
  VOID                                         *Mapping;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation;
  UINTN                                        Index;
  UINT8                                        *Buffer;
  UINTN                                        BufferSize;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;

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
                   &StandardLib
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


  //
  //check point 4.1.12.2.1 Map() wih Bus Master Read.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //fill in this buffer with some data.
  //

  gtBS->SetMem (Buffer, BufferSize, 0x01);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterRead;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid021,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Read return status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid022,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - NumberOfBytest should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );

  //
  // Remove the memory values checking since we cannot make the assumption
  // that the mapped address returned from the device is the same as the CPU
  // IO address. Large systems may have more than one way of accessing the
  // IO space from the CPU or from the device.
  //
  /*
  if (SctCompareMem ((VOID*)Buffer, (VOID*)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid023,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the mapped data must be the same as original data",
                 L"%a:%d: Operation -%d",
                 __FILE__,
                 __LINE__,
                 Operation
                 );
  */

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //check point 4.1.12.2.2 Map with EfiPciOperationBusMasterRead64.
  //
  Operation     = EfiPciOperationBusMasterRead64;
  NumberOfBytes = BufferSize;
  HostAddress   = (void *)Buffer;
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid024,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Read 64 return status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid025,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - NumberOfBytest should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );

  if (SctCompareMem ((VOID*)Buffer, (VOID*)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid026,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the mapped data must be the same as original data",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //free this buffer.
  //
  gtBS->FreePool (Buffer);

  //
  //check point 4.1.12.2.3 Map() wih Bus Master Write.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //set some data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterWrite;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid027,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Write",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid028,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the NumberOfBytes should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  for (Index = 0;Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid029,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the original data should remain unchnged just after mapp with BusMasterWrite",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );


  //
  //Unmap this area.
  //
  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //check point 4.1.12.2.4 Map() wih Bus Master Write 64.
  //

  //
  //set some data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterWrite64;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid030,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Write 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid031,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the NumberOfBytes should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  for (Index = 0;Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid032,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the original data should remain unchnged just after mapp with BusMasterWrite 64",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );


  //
  //Unmap this area.
  //
  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //free this buffer
  //
  gtBS->FreePool (Buffer);


  //
  //check point 4.1.12.2.5 Map() with Bus Master Common Buffer
  //

  //
  //first allocate 2 page with Pci Root Bridge Io protocol.
  //
  Buffer = NULL;
  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           AllocateAnyPages,
                           EfiBootServicesData,
                           2,
                           &Buffer,
                           0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;

  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  //
  //map with operation as EfiPciOperationBusMasterCommonBuffer.
  //

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterCommonBuffer;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid033,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );


  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid034,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - NumberOfBytes should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );

  //
  // Remove the memory values checking since we cannot make the assumption
  // that the mapped address returned from the device is the same as the CPU
  // IO address. Large systems may have more than one way of accessing the
  // IO space from the CPU or from the device.
  //
  /*
  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid035,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data after map must be the same as original data",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 __LINE__,
                 Operation
                 );

  //
  //Fill in Mapped address with some fixed data.
  //
  gtBS->SetMem ((VOID*)(UINTN)DeviceAddress, NumberOfBytes, 0x0);

  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid036,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data in original area should remain sync with mapped area",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 __LINE__,
                 Operation
                 );

  //
  //Fill in original address with some fixed data.
  //
  gtBS->SetMem (Buffer, NumberOfBytes, 0x01);

  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid037,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data in mapped area should remain sync with original area",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 __LINE__,
                 Operation
                 );
  */

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //at last free buffer
  //

  Status = RootBridgeIo->FreeBuffer (
                           RootBridgeIo,
                           2,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //check point 4.1.12.2.6 Map() with Bus Master Common Buffer 64
  //

  //
  //first allocate 2 page with Pci Root Bridge Io protocol.
  //
  Buffer = NULL;
  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           AllocateAnyPages,
                           EfiBootServicesData,
                           2,
                           &Buffer,
                           0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;

  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  //
  //map with operation as EfiPciOperationBusMasterCommonBuffer.
  //

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterCommonBuffer64;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid038,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );


  if (NumberOfBytes == 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid039,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - NumberOfBytes should not be zero",
                 L"%a:%d:NumberOfBytes - %xh,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 NumberOfBytes,
                 Operation
                 );


  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid040,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data after map must be the same as original data",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //Fill in Mapped address with some fixed data.
  //
  gtBS->SetMem ((VOID*)(UINTN)DeviceAddress, NumberOfBytes, 0x0);

  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid041,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data in original area should remain sync with mapped area",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //Fill in original address with some fixed data.
  //
  gtBS->SetMem (Buffer, NumberOfBytes, 0x01);

  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid042,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - the data in mapped area should remain sync with original area",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //at last free buffer
  //

  Status = RootBridgeIo->FreeBuffer (
                           RootBridgeIo,
                           2,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Unmap() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.13
//
EFI_STATUS
Unmap_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  VOID                                         *HostAddress;
  UINTN                                        NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                         DeviceAddress;
  VOID                                         *Mapping;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation;
  UINTN                                        Index;
  UINT8                                        *Buffer;
  UINTN                                        BufferSize;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;

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
                   &StandardLib
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


  //
  //check point 4.1.13.2.1 Unmap() area that mapped wih Bus Master Read.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //fill in this buffer with some data.
  //

  gtBS->SetMem (Buffer, BufferSize, 0x01);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterRead;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Read return status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid043,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x1) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid044,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the data should remain unchanged after Unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //check point 4.1.13.2.2 Unmap() area that mapped wih Bus Master Read 64.
  //

  //
  //fill in this buffer with some data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterRead64;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Read 64 return status should be EFI_SUCCESS",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid045,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x1) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid046,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the data should remain unchanged after Unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //free this buffer.
  //
  gtBS->FreePool (Buffer);

  //
  //check point 4.1.13.2.3 Unmap() area that mapped wih Bus Master Write.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterWrite;
  HostAddress   = (void *)Buffer;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Write",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //set mapped area some data.
  //
  gtBS->SetMem ((VOID *)(UINTN)DeviceAddress, NumberOfBytes, 0x01);

  //
  //Unmap this area.
  //
  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid047,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );


  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < NumberOfBytes; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid048,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the original data should be the same as written in mapped area after unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //check point 4.1.13.2.4 Unmap() area that mapped wih Bus Master Write 64.
  //

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterWrite64;
  HostAddress   = (void *)Buffer;
  gtBS->SetMem (Buffer, BufferSize, 0x0);

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Write 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //set mapped area some data.
  //
  gtBS->SetMem ((VOID *)(UINTN)DeviceAddress, NumberOfBytes, 0x01);

  //
  //Unmap this area.
  //
  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid049,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );


  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < NumberOfBytes; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid050,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the original data should be the same as written in mapped area after unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //free this buffer
  //
  gtBS->FreePool (Buffer);


  //
  //check point 4.1.13.2.5 Unmap() area that mapped with Bus Master Common Buffer
  //

  //
  //first allocate 2 page with Pci Root Bridge Io protocol.
  //
  Buffer = NULL;
  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           AllocateAnyPages,
                           EfiBootServicesData,
                           2,
                           &Buffer,
                           0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;

  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  //
  //map with operation as EfiPciOperationBusMasterCommonBuffer.
  //

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterCommonBuffer;
  HostAddress   = (void *)Buffer;


  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid051,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid052,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the original data should remain unchanged after unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //at last free buffer
  //
  Status = RootBridgeIo->FreeBuffer (
                           RootBridgeIo,
                           2,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //check point 4.1.13.2.6 Unmap() area that mapped with
  //Bus Master Common Buffer 64
  //

  //
  //first allocate 2 page with Pci Root Bridge Io protocol.
  //
  Buffer = NULL;
  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           AllocateAnyPages,
                           EfiBootServicesData,
                           2,
                           &Buffer,
                           0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;

  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x01);

  //
  //map with operation as EfiPciOperationBusMasterCommonBuffer.
  //

  NumberOfBytes = BufferSize;
  Operation     = EfiPciOperationBusMasterCommonBuffer64;
  HostAddress   = (void *)Buffer;


  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
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
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //Unmap this area.
  //

  Status = RootBridgeIo->Unmap (
                           RootBridgeIo,
                           Mapping
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid053,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read 64",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid054,
                 L"EFI_ROOT_BRIDGE_IO_PROTOCOL.Unmap - the original data should remain unchanged after unmap",
                 L"%a:%d:Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation
                 );

  //
  //at last free buffer
  //
  Status = RootBridgeIo->FreeBuffer (
                           RootBridgeIo,
                           2,
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for AllocateBuffer()Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.14
//
EFI_STATUS
AllocateBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STATUS                                   EfiStatus;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  UINT8                                        *Buffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_ALLOCATE_TYPE                            AllocateType;
  EFI_MEMORY_TYPE                              MemoryType[2];
  UINT64                                       Attributes[8];
  UINTN                                        MemoryTypeNum;
  UINTN                                        AttributesNum;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;


  AllocateType = 0;

  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  Attributes[0] = 0;
  Attributes[1] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
  Attributes[2] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
  Attributes[3] = EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;

  Attributes[4] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;
  Attributes[5] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;
  Attributes[6] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;

  Attributes[7] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;



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
                   &StandardLib
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

  EfiStatus = EFI_SUCCESS;

  for (MemoryTypeNum = 0; MemoryTypeNum < 2; MemoryTypeNum++) {
    for (AttributesNum = 0; AttributesNum < 8; AttributesNum++) {

      Status = RootBridgeIo->AllocateBuffer (
                               RootBridgeIo,
                               AllocateType,
                               MemoryType[MemoryTypeNum],
                               2,
                               &Buffer,
                               Attributes[AttributesNum]
                               );
      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS."
                     L"%a:%d:Status - %r,MemoryType:%d,Attributes:%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     MemoryType[MemoryTypeNum],
                     Attributes[AttributesNum]
                     );

      if (EFI_ERROR(Status)) {
        EfiStatus = Status;
        continue;
      }

      Status = RootBridgeIo->FreeBuffer (
                               RootBridgeIo,
                               2,
                               Buffer
                               );

      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS."
                     L"%a:%d:Status - %r,MemoryType:%d,Attributes:%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     MemoryType[MemoryTypeNum],
                     Attributes[AttributesNum]
                     );

    }
  }


  if (!EFI_ERROR(EfiStatus)) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid055,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for FreeBuffer() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.15
//
EFI_STATUS
FreeBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STATUS                                   EfiStatus;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  UINT8                                        *Buffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_ALLOCATE_TYPE                            AllocateType;
  EFI_MEMORY_TYPE                              MemoryType[2];
  UINT64                                       Attributes[8];
  UINTN                                        MemoryTypeNum;
  UINTN                                        AttributesNum;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;


  AllocateType = 0 ;

  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  Attributes[0] = 0;
  Attributes[1] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
  Attributes[2] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
  Attributes[3] = EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;

  Attributes[4] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;
  Attributes[5] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;
  Attributes[6] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;

  Attributes[7] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                  EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                  EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;



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
                   &StandardLib
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

  EfiStatus = EFI_SUCCESS;

  for (MemoryTypeNum = 0; MemoryTypeNum < 2; MemoryTypeNum++) {
    for (AttributesNum = 0; AttributesNum < 8; AttributesNum++) {

      Status = RootBridgeIo->AllocateBuffer (
                               RootBridgeIo,
                               AllocateType,
                               MemoryType[MemoryTypeNum],
                               2,
                               &Buffer,
                               Attributes[AttributesNum]
                               );
      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS."
                     L"%a:%d:Status - %r,MemoryType:%d,Attributes:%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     MemoryType[MemoryTypeNum],
                     Attributes[AttributesNum]
                     );

      if (EFI_ERROR(Status)) {
        continue;
      }

      Status = RootBridgeIo->FreeBuffer (
                               RootBridgeIo,
                               2,
                               Buffer
                               );

      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS."
                     L"%a:%d:Status - %r,MemoryType:%d,Attributes:%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     MemoryType[MemoryTypeNum],
                     Attributes[AttributesNum]
                     );

      if (EFI_ERROR(Status)) {
        EfiStatus = Status;
      }

    }
  }


  if (!EFI_ERROR(EfiStatus)) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid056,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Flush() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.16
//
EFI_STATUS
Flush_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE         *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;


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
                   &StandardLib
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

  Status = RootBridgeIo->Flush (RootBridgeIo);

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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid057,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Flush - the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for GetAttributes() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.17
//
EFI_STATUS
GetAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE         *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                SupportedAttributes;
  UINT64                                CurrentAttributes;
  UINT64                                SecondSupportedAttributes;
  UINT64                                SecondCurrentAttributes;

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
                   &StandardLib
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

  //
  //call GetAttributes to get current attributes and supported attributes.
  //
  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           &SupportedAttributes,
                           &CurrentAttributes
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid058,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get Supported and Current attribute status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ((CurrentAttributes & SupportedAttributes) == CurrentAttributes) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid059,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - current attributes must within Supported attributes",
                 L"%a:%d:Current Attributes - %LXh, Supported Attributes - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 CurrentAttributes,
                 SupportedAttributes
                 );

  //
  //call GetAttributes to get current attributes only
  //
  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           NULL,
                           &SecondCurrentAttributes
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid060,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get Current attribute only status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (CurrentAttributes == SecondCurrentAttributes) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid061,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - two time returned Current attributes should equal",
                 L"%a:%d:First Time Attributes - %LXh, Second Time Attributes - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 CurrentAttributes,
                 SecondCurrentAttributes
                 );

  //
  //call GetAttributes to get current supported attributes only
  //
  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           &SecondSupportedAttributes,
                           NULL
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid062,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get supported attribute only status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (SupportedAttributes == SecondSupportedAttributes) {
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid063,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - two time returned supported attributes should equal",
                 L"%a:%d:First Time Attributes - %LXh, Second Time Attributes - %LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 SupportedAttributes,
                 SecondSupportedAttributes
                 );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for SetAttributes Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.18
//
EFI_STATUS
SetAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE         *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                SupportedAttributes;
  UINT64                                CommonAttributes;
  UINT64                                ResourceBase;
  UINT64                                ResourceLength;
  UINTN                                 Index;
  UINTN                                 AttributesNumber;
  UINT64                                ThisAttribute;
  BOOLEAN                               FoundAttribute;

  UINT64          AllAttributes[11] = {
    EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO,
    EFI_PCI_ATTRIBUTE_ISA_IO,
    EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO,
    EFI_PCI_ATTRIBUTE_VGA_MEMORY,
    EFI_PCI_ATTRIBUTE_VGA_IO,
    EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO,
    EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO,
    EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE,
    EFI_PCI_ATTRIBUTE_MEMORY_CACHED,
    EFI_PCI_ATTRIBUTE_MEMORY_DISABLE,
    EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE
  };

  UINT64 RequireResourceAttributes = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                                     EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                                     EFI_PCI_ATTRIBUTE_MEMORY_DISABLE;

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
                   &StandardLib
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

  //
  //call GetAttributes to get current supported attributes.
  //

  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           &SupportedAttributes,
                           NULL
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get Supported attribute status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //found a supported attributes that not need a resource.
  //
  AttributesNumber = 11;
  FoundAttribute   = FALSE;

  ThisAttribute = 0;
  for (Index = 0; Index < AttributesNumber; Index++) {

    ThisAttribute = AllAttributes[Index];
    if (ThisAttribute & RequireResourceAttributes) {
      continue;
    }

    if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {
      FoundAttribute = TRUE;
      break;
    }
  }

  //
  //call SetAttributes with Supported attributes.
  //
  if (FoundAttribute) {
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             NULL,
                             NULL
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid064,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Supported attribute that not need resource status must be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Set Attributes -%LXh,Supported Attributes -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute,
                   SupportedAttributes
                   );
    //
    //call Get Attributes to verify this attribute really set.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CommonAttributes
                    );

    if ((ThisAttribute & CommonAttributes) == ThisAttribute) {
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
               gPciRootBridgeIoBBTestFunction_2AssertionGuid065,
               L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Supported attribute should really set",
               L"%a:%d:Set Attribute - %LXh, Gotten Attributes - %LXh",
               __FILE__,
               (UINTN)__LINE__,
               ThisAttribute,
               CommonAttributes
               );
  }

  //
  //get some valid memory resource controlled by this Root Bridge.
  //
  Status = GetSomeMemeryResource (
             RBDev,
             &ResourceBase,
             &ResourceLength
             );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes-not found valid memory resource.\n"
                   L"%a:%d.\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return EFI_SUCCESS;
  }


  //
  //found a supported attributes that need a resource.
  //
  ThisAttribute = 0;
  FoundAttribute = FALSE;

  for (Index = 0; Index < AttributesNumber; Index++) {

    ThisAttribute = AllAttributes[Index];

    if ((ThisAttribute & RequireResourceAttributes) == 0) {
      continue;
    }

    if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {
      FoundAttribute = TRUE;
      break;
    }
  }

  //
  //call SetAttributes with Supported attributes.
  //
  if (FoundAttribute) {

    if (ResourceLength > 0x1000) {
      ResourceLength = 0x1000;
    }

    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             &ResourceLength
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid066,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Supported attribute which require a resource status must be EFI_SUCCESS",
                   L"%a:%d:Status - %r,Set Attributes -%LXh,Supported Attributes -%LXh, Address -%LXh, Length -%lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute,
                   SupportedAttributes,
                   ResourceBase,
                   ResourceLength
                   );
    //
    //call Get Attributes to verify this attribute really set.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CommonAttributes
                    );

    if ((ThisAttribute & CommonAttributes) == ThisAttribute) {
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
                   gPciRootBridgeIoBBTestFunction_2AssertionGuid067,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Supported attribute should really set",
                   L"%a:%d:Set Attribute - %LXh, Gotten Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   ThisAttribute,
                   CommonAttributes
                   );
  } else {

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - not found a supported attributes that need a resource.\n"
                   L"%a:%d.\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}



/**
 *  Entrypoint for Configuration() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.23
//
EFI_STATUS
Configuration_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_ASSERTION                           AssertionType;
  VOID                                         *Resource;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;


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
                   &StandardLib
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

  //
  //call Configuration to get the resource list.
  //

  Status = RootBridgeIo->Configuration (
                           RootBridgeIo,
                           &Resource
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
                 gPciRootBridgeIoBBTestFunction_2AssertionGuid068,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Configuration - the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (IsValidResourceDescrptor (Resource)) {
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
                  gPciRootBridgeIoBBTestFunction_2AssertionGuid069,
                  L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Configuration - resource must point to a valid QWord descriptor.",
                  L"%a:%d: IsValidResourceDescriptor - %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  IsValidResourceDescrptor (Resource)
                  );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
