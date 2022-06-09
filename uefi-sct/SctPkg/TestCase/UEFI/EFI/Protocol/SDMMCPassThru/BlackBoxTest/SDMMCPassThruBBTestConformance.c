/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    SDMMCPassThruBBTestConformance.c

Abstract:

    for EFI Driver SDMMC Pass Thru Protocol's Conformance Test

--*/

#include "SDMMCPassThruBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestPassThruConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  
  EFI_SD_MMC_PASS_THRU_PROTOCOL         *SDMMC;
  UINT8                                 Slot;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;

  EFI_SD_MMC_COMMAND_BLOCK              SdMmcCmdBlk;
  EFI_SD_MMC_STATUS_BLOCK               SdMmcStatusBlk;
  EFI_SD_MMC_PASS_THRU_COMMAND_PACKET   Packet;

  UINTN                                 BufferSize;
  VOID                                  *Buffer;


  SDMMC = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)ClientInterface;
  

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Assume the 2M bytes buffer for reading
  //
  BufferSize = 2 * 1024 * 1024;
  Buffer = AllocateAlignedPool (EfiBootServicesData, BufferSize, SDMMC->IoAlign);
  if (Buffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SctAllocateZeroPooll - SctAllocateZeroPool fails",
                   L" - %a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_OUT_OF_RESOURCES;
  }
  SctZeroMem (Buffer, BufferSize);

  Slot = 0xFF;

  if (SDMMC->GetNextSlot (SDMMC, &Slot) == EFI_SUCCESS) {
    Status = SDMMC->PassThru(SDMMC, Slot, NULL, NULL);
    if (Status == EFI_INVALID_PARAMETER)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSDMMCPassThruBBTestConformanceAssertionGuid001,
                   L"EFI_SD_MMC_PASS_THRU_PROTOCOL.PassThru - EFI_INVALID_PARAMETER should be returned when Packet is invalid.",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    SctZeroMem (&Packet, sizeof (Packet));
    Status = SDMMC->PassThru(SDMMC, Slot, &Packet, NULL);
    if (Status == EFI_INVALID_PARAMETER)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSDMMCPassThruBBTestConformanceAssertionGuid002,
                   L"EFI_SD_MMC_PASS_THRU_PROTOCOL.PassThru - EFI_INVALID_PARAMETER should be returned when the contents of the Packet is invalid.",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (EFI_SUCCESS == SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath)) {
      if (DevicePath->SubType == 26) {
        SctZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
        SctZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
        SctZeroMem (&Packet, sizeof (Packet));

        Packet.SdMmcCmdBlk    = &SdMmcCmdBlk;
        Packet.SdMmcStatusBlk = &SdMmcStatusBlk;
        Packet.InDataBuffer     = NULL;
        Packet.InTransferLength = (UINT32)BufferSize;
          
        //Taking 2MB/s as divisor as it's the lowest transfer speed of Class 2.
        Packet.Timeout        = (BufferSize / (2 * 1024 * 1024) + 1) * 1000 * 1000;

        SdMmcCmdBlk.CommandIndex    = 18;                   //SD_READ_MULTIPLE_BLOCK
        SdMmcCmdBlk.CommandType     = SdMmcCommandTypeAdtc;
        SdMmcCmdBlk.ResponseType    = SdMmcResponseTypeR1;

        // Assume the capacity is larger than 2GB and Lba read from 1000 
        SdMmcCmdBlk.CommandArgument = (UINT32)1000;

        Status = SDMMC->PassThru(SDMMC, Slot, &Packet, NULL);

      }
      if (DevicePath->SubType == 29) {
        SctZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
        SctZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
        SctZeroMem (&Packet, sizeof (Packet));

        Packet.SdMmcCmdBlk      = &SdMmcCmdBlk;
        Packet.SdMmcStatusBlk   = &SdMmcStatusBlk;
        Packet.InDataBuffer     = NULL;
        Packet.InTransferLength = (UINT32)BufferSize;
          
        //Taking 2MB/s as divisor is because it's nearest to the eMMC lowest speed(2.4MB/s) 
        Packet.Timeout          = (BufferSize / (2 * 1024 * 1024) + 1) * 1000 * 1000;

        SdMmcCmdBlk.CommandIndex    = 18;                    //EMMC_READ_MULTIPLE_BLOCK
        SdMmcCmdBlk.CommandType     = SdMmcCommandTypeAdtc;
        SdMmcCmdBlk.ResponseType    = SdMmcResponseTypeR1;

        // Assume the capacity is larger than 2GB and Lba read from 1000           
        SdMmcCmdBlk.CommandArgument = (UINT32)1000;

        Status = SDMMC->PassThru(SDMMC, Slot, &Packet, NULL);
      }	
    }

    if (Status == EFI_INVALID_PARAMETER)
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSDMMCPassThruBBTestConformanceAssertionGuid003,
                   L"EFI_SD_MMC_PASS_THRU_PROTOCOL.PassThru - EFI_INVALID_PARAMETER should be returned when Packet defines a data command but both InDataBuffer and OutDataBuffer are NULL.",
                   L"%a:%d:Status - %r, Slot - %d, DevicePath->SubType - 0x%x\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Slot,
                   (UINTN)DevicePath->SubType
                   );
  }

  do {
    Status = SDMMC->GetNextSlot (SDMMC, &Slot);
  } while(!EFI_ERROR(Status));

  Slot++;

  SctZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
  SctZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
  SctZeroMem (&Packet, sizeof (Packet));

  Packet.SdMmcCmdBlk      = &SdMmcCmdBlk;
  Packet.SdMmcStatusBlk   = &SdMmcStatusBlk;
  Packet.InDataBuffer     = Buffer;
  Packet.InTransferLength = (UINT32)BufferSize;
          
  //Taking 2MB/s as divisor is because it's nearest to the eMMC lowest speed(2.4MB/s) or the lowest transfer speed of SD Class 2.
  Packet.Timeout          = (BufferSize / (2 * 1024 * 1024) + 1) * 1000 * 1000;

  SdMmcCmdBlk.CommandIndex    = 18;                    //READ_MULTIPLE_BLOCK
  SdMmcCmdBlk.CommandType     = SdMmcCommandTypeAdtc;
  SdMmcCmdBlk.ResponseType    = SdMmcResponseTypeR1;

  // Assume the capacity is larger than 2GB and Lba read from 1000           
  SdMmcCmdBlk.CommandArgument = (UINT32)1000;

  Status = SDMMC->PassThru(SDMMC, Slot, &Packet, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestConformanceAssertionGuid004,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.PassThru - EFI_INVALID_PARAMETER should be returned when Slot is invalid.",
                 L"%a:%d:Status - %r, Slot - %d\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Slot
                 );
  
  FreeAlignedPool(Buffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSlotConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SD_MMC_PASS_THRU_PROTOCOL         *SDMMC;
  EFI_TEST_ASSERTION                    AssertionType;  
  UINT8                                 Slot;


  SDMMC = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)ClientInterface;
  

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Slot = 0xFF;
  do {
    Status = SDMMC->GetNextSlot (SDMMC, &Slot);
  } while (!EFI_ERROR(Status));

  if (Status != EFI_NOT_FOUND)
    return Status;

  Slot++;

  Status = SDMMC->GetNextSlot (SDMMC, &Slot);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestConformanceAssertionGuid005,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetNextSlot - EFI_INVALID_PARAMETER should be returned when Slot is not 0xFF and Slot was not returned on a previous call",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestResetDeviceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SD_MMC_PASS_THRU_PROTOCOL         *SDMMC;
  EFI_TEST_ASSERTION                    AssertionType;  
  UINT8                                 Slot;


  SDMMC = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)ClientInterface;
  

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Slot = 0xFF;
  do {
    Status = SDMMC->GetNextSlot (SDMMC, &Slot);
  } while (!EFI_ERROR(Status));

  if (Status != EFI_NOT_FOUND)
    return Status;

  Slot++;

  Status = SDMMC->ResetDevice (SDMMC, Slot);
  if (Status == EFI_INVALID_PARAMETER || Status == EFI_UNSUPPORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestConformanceAssertionGuid006,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.ResetDevice - EFI_INVALID_PARAMETER should be returned when Slot number is invalid or the SD controller does not support a device reset operation.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}  

EFI_STATUS
EFIAPI
BBTestBuildDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;  
  EFI_SD_MMC_PASS_THRU_PROTOCOL         *SDMMC;
  EFI_TEST_ASSERTION                    AssertionType;  
  UINT8                                 Slot;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;


  SDMMC = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)ClientInterface;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Slot = 0xFF;
  do {
    Status = SDMMC->GetNextSlot (SDMMC, &Slot);
    if (Status == EFI_SUCCESS) {
      Status1 = SDMMC->BuildDevicePath (SDMMC, Slot, NULL);
      if (Status1 == EFI_INVALID_PARAMETER)
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED; 

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestConformanceAssertionGuid007,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.BuildDevicePath - EFI_INVALID_PARAMETER should be returned when DevicePath is NULL.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1
                     );  

    }
  } while (!EFI_ERROR(Status));

  if (Status != EFI_NOT_FOUND)
    return Status;

  Slot++;
  DevicePath = NULL;

  Status = SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath);
  if (Status == EFI_NOT_FOUND && DevicePath == NULL)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestConformanceAssertionGuid008,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.BuildDevicePath - EFI_NOT_FOUND should be returned when the SD card specified by Slot does not exist on the SD controller.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetSlotNumberConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SD_MMC_PASS_THRU_PROTOCOL         *SDMMC;
  EFI_TEST_ASSERTION                    AssertionType;  
  UINT8                                 Slot;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;


  SDMMC = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)ClientInterface;
  DevicePath = NULL;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, &Slot);
  if (Status == EFI_INVALID_PARAMETER)
  	 AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_INVALID_PARAMETER should be returned when DevicePath is NULL.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );      

  Slot = 0xFF;
  if (EFI_SUCCESS == SDMMC->GetNextSlot (SDMMC, &Slot)) {
    if (EFI_SUCCESS == SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath)) {

      Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, NULL);
      if (Status == EFI_INVALID_PARAMETER)
  	     AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestConformanceAssertionGuid010,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_INVALID_PARAMETER should be returned when Slot is NULL.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );


      DevicePath->Length[0] = 6;
      Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, &Slot);
      if (Status == EFI_UNSUPPORTED)
  	     AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestConformanceAssertionGuid011,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_UNSUPPORTED should be returned when DevicePath is not a device path node type that the SD PassThru driver supports.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );


      DevicePath->Length[0] = 5;
      DevicePath->Type = 2;
      Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, &Slot);
      if (Status == EFI_UNSUPPORTED)
  	     AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestConformanceAssertionGuid011,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_UNSUPPORTED should be returned when DevicePath is not a device path node type that the SD PassThru driver supports.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      DevicePath->Type = 3;
      DevicePath->SubType = 27;
      Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, &Slot);      
      if (Status == EFI_UNSUPPORTED)
  	     AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestConformanceAssertionGuid011,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_UNSUPPORTED should be returned when DevicePath is not a device path node type that the SD PassThru driver supports.",
                     L"%a:%d:Status - %r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );


    }
  }

  if (DevicePath != NULL)
    SctFreePool(DevicePath);

  return EFI_SUCCESS;
}  
