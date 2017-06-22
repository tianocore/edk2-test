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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    SDMMCPassThruBBTestFunction.c

Abstract:

    for EFI Driver SDMMC Pass Thru Protocol's Function Test

--*/

#include "SDMMCPassThruBBTestMain.h"

extern UINT8 EnterEvent;

EFI_STATUS
BBTestPassThruFunctionTest (
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

  if ((SDMMC->IoAlign != 0) && ((SDMMC->IoAlign & (SDMMC->IoAlign - 1)) != 0)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestFunctionAssertionGuid001,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.IoAlign - IoAlign should be the power of 2",
                 L"%a:%d:IoAlign - 0x%x\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 SDMMC->IoAlign
                 );
  
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
                   L"AllocateAlignedPool - AllocateAlignedPool fails",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_OUT_OF_RESOURCES;
  }

  SctZeroMem (Buffer, BufferSize);

  Slot = 0xFF;

  while(!EFI_ERROR(SDMMC->GetNextSlot (SDMMC, &Slot))) { 
    if (EFI_SUCCESS == SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    	
      if (DevicePath->SubType == 26) {
        SctZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
        SctZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
        SctZeroMem (&Packet, sizeof (Packet));

        Packet.SdMmcCmdBlk    = &SdMmcCmdBlk;
        Packet.SdMmcStatusBlk = &SdMmcStatusBlk;
        Packet.InDataBuffer     = Buffer;
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
        Packet.Timeout          = 2500 * 1000;
        
        SdMmcCmdBlk.CommandIndex    = 23;                    //EMMC_SET_BLOCK_COUNT
        SdMmcCmdBlk.CommandType     = SdMmcCommandTypeAc;
        SdMmcCmdBlk.ResponseType    = SdMmcResponseTypeR1;
        SdMmcCmdBlk.CommandArgument = (UINT32)(BufferSize / 512);      //Assume the BlockSize is 512
        
        Status = SDMMC->PassThru(SDMMC, Slot, &Packet, NULL);

        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"\r\nSetBlkNum: %r",
                       Status
                       );        
      	
        SctZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
        SctZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
        SctZeroMem (&Packet, sizeof (Packet));

        Packet.SdMmcCmdBlk      = &SdMmcCmdBlk;
        Packet.SdMmcStatusBlk   = &SdMmcStatusBlk;
        Packet.InDataBuffer     = Buffer;
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

      if (Status == EFI_SUCCESS )
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      else if (Status == EFI_UNSUPPORTED || Status == EFI_NO_MEDIA || Status == EFI_DEVICE_ERROR)
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestFunctionAssertionGuid002,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.PassThru - EFI_SUCCESS should be returned when the SD Command Packet was sent by the host.",
                     L"%a:%d:Status - %r, DevicePath->SubType - %d, Slot - %d\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINTN)DevicePath->SubType,
                     Slot
                     ); 

    }
  }


  FreeAlignedPool(Buffer);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetNextSlotFunctionTest (
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

  if (Status == EFI_NOT_FOUND)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestFunctionAssertionGuid003,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetNextSlot - EFI_NOT_FOUND should be returned when There are no more slots on this SD controller.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestResetDeviceFunctionTest (
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

  Status = SDMMC->GetNextSlot (SDMMC, &Slot);
  if (Status != EFI_SUCCESS)
    return Status;

  Status = SDMMC->ResetDevice (SDMMC, Slot);
  if (Status == EFI_SUCCESS )
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else if (Status == EFI_UNSUPPORTED || Status == EFI_NO_MEDIA || Status == EFI_DEVICE_ERROR)
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSDMMCPassThruBBTestFunctionAssertionGuid004,
                 L"EFI_SD_MMC_PASS_THRU_PROTOCOL.ResetDevice - EFI_SUCCESS should be returned when The SD card specified by Slot was reset.",
                 L"%a:%d:Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  return EFI_SUCCESS;
}  

EFI_STATUS
BBTestBuildDevicePathFunctionTest (
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

  Slot = 0xFF;

  if (EFI_SUCCESS == SDMMC->GetNextSlot (SDMMC, &Slot)) {

    Status = SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (DevicePath->Type != 3 || (DevicePath->SubType != 26 && DevicePath->SubType != 29) || (DevicePath->Length[0] | DevicePath->Length[1] << 8) != 5)
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: Type - %d, SubType - 0x%x, Length - %d",
                     (UINTN)DevicePath->Type,
                     (UINTN)DevicePath->SubType,
                     (UINTN)(DevicePath->Length[0] | DevicePath->Length[1] << 8)
                     );
    } else if (Status == EFI_OUT_OF_RESOURCES)
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSDMMCPassThruBBTestFunctionAssertionGuid005,
                   L"EFI_SD_MMC_PASS_THRU_PROTOCOL.BuildDevicePath - EFI_SUCCESS should be returned when the device path node that describes the SD card specified by Slot was allocated and returned in DevicePath.",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );  

  }


  if (DevicePath != NULL)
    SctFreePool(DevicePath);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetSlotNumberFunctionTest (
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
  UINT8                                 Slot1;
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

  Slot = 0xFF;
  if (EFI_SUCCESS == SDMMC->GetNextSlot (SDMMC, &Slot)) {
    if (EFI_SUCCESS == SDMMC->BuildDevicePath (SDMMC, Slot, &DevicePath)) {

      Status = SDMMC->GetSlotNumber (SDMMC, DevicePath, &Slot1);
      if (Status == EFI_SUCCESS && (Slot == Slot1))
  	     AssertionType = EFI_TEST_ASSERTION_PASSED;
      else
        AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSDMMCPassThruBBTestFunctionAssertionGuid006,
                     L"EFI_SD_MMC_PASS_THRU_PROTOCOL.GetSlotNumber - EFI_SUCCESS should be returned when SD card slot number is returned in Slot.",
                     L"%a:%d:Status - %r, Slot - %d, Slot1 - %d\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Slot,
                     Slot1
                     );
    }
  }

  if (DevicePath != NULL)
    SctFreePool(DevicePath);

  return EFI_SUCCESS;
}  