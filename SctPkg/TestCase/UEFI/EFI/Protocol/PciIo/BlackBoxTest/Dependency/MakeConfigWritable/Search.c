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

  Search.c

Abstract:
  function implementation used to search Pci Test card.

--*/

#include "Common.h"
#include "Main.h"
#include <UEFI/Protocol/PciIo.h>

//
//function protype
//
EFI_STATUS
FindTestCard (
  IN PCIDev        **Dev
  );

EFI_STATUS
FoundTestCardUnderRB (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo,
  IN PCIDev                          **TestDev
  );

EFI_STATUS
AllocateNewDevice (
  IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN OUT PCIDev                            **TestDev,
  IN     UINT8                             Bus,
  IN     UINT8                             Dev,
  IN     UINT8                             Func
  );

/*
 *  found a Pci Test card in current system.
 *  @param Dev the Pci Device structure pointer.
 *  @return EFI_SUCCESS pci test card has been found.
 */

EFI_STATUS
FindTestCard (
  IN PCIDev        **Dev
  )
{
  EFI_HANDLE                        *HandleBuffer;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo;
  UINTN                             HandleNum;
  EFI_STATUS                        Status;
  EFI_STATUS                        EfiStatus;
  UINTN                             Index;

  HandleBuffer = NULL;
  HandleNum    = 0;
  EfiStatus    = EFI_NOT_FOUND;

  Status = SctLocateHandle(
             ByProtocol,
             &gBlackBoxEfiPciRootBridgeIoProtocolGuid,
             NULL,
             &HandleNum,
             &HandleBuffer
             );

  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_NOT_FOUND;
  }
  for (Index = 0; Index < HandleNum; Index++) {
    Status = tBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiPciRootBridgeIoProtocolGuid,
                   &RootBridgeIo
                   );
    if (EFI_ERROR(Status)) {
      continue;
    }

    Status = FoundTestCardUnderRB (RootBridgeIo, Dev);

    if (!EFI_ERROR(Status)) {
      EfiStatus = EFI_SUCCESS;
      break;
    }
  }

  if (HandleBuffer != NULL) {
    SctFreePool (HandleBuffer);
  }

  return EfiStatus;
}
/*
 *  Find test card under a root bridge.
 *  @param RootBridge the root bridge Io protocol interface.
 *  @param Dev the returned Device pointer.
 *  @return EFI_SUCCESS one test card was found.
 */
EFI_STATUS
FoundTestCardUnderRB (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo,
  IN PCIDev                          **TestDev
  )
{
  UINTN                            Bus;
  UINTN                            Dev;
  UINTN                            Func;
  EFI_STATUS                       Status;
  UINT16                           VendId;
  UINT16                           DevId;
  UINT8                            RevId;
  BOOLEAN                          NewCard;


  //
  //now check all the special device under this root bridge. using the Pci Root
  //bridge Pci.Read to enumerate the devices, because the pci devices may be
  //rejected for shortage of resources.
  //

  for (Bus = 0; Bus < 0xff; Bus++) {
    for (Dev = 0; Dev < 0x20; Dev++) {
      for (Func = 0; Func < 0x8; Func++) {

        NewCard = FALSE;

        VendId = ReadConfigWord (RootBridgeIo, (UINT8)Bus, (UINT8)Dev, (UINT8)Func, OFF_VENDOR_ID);

        if (VendId == 0xffff) {
          if (Func == 0) {
            Func = 8;
          }
          continue;
        }
        DevId = ReadConfigWord (RootBridgeIo, (UINT8)Bus, (UINT8)Dev, (UINT8)Func, OFF_DEVICE_ID);
        RevId = ReadConfigByte (RootBridgeIo, (UINT8)Bus, (UINT8)Dev, (UINT8)Func, OFF_REVISION_ID);

        //
        //check if they are special devices.
        //
        if (((VendId == 0x12DB) && (DevId == 0x0003)) ||
            ((VendId == 0x8086 ) && ((DevId & 0x3FFF) == 0x0453) &&
            (RevId == NC_REVISION_ID))) {
          NewCard = TRUE;
        }

        if (NewCard) {

          SctPrint (L"Found a Special Card\r\n");
          Status = AllocateNewDevice (
                     RootBridgeIo,
                     TestDev,
                     (UINT8)Bus,
                     (UINT8)Dev,
                     (UINT8)Func
                     );
          if (!EFI_ERROR(Status)) {
            return EFI_SUCCESS;
          }
        }
      }
    }
  }

  return EFI_NOT_FOUND;
}

/*
 *  Allocate New Device
 *  @param RootBridgeIo the root bridge Io protocol interface.
 *  @param TestDev the Test Pci Device pointer.
 *  @param Bus the Bus Number of this device.
 *  @param Dev the device number of this device.
 *  @param Func the function number of this device.
 *  @return EFI_SUCCESS the device was allocated successfully.
 */
EFI_STATUS
AllocateNewDevice (
  IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN OUT PCIDev                            **TestDev,
  IN     UINT8                             Bus,
  IN     UINT8                             Dev,
  IN     UINT8                             Func
  )
{
  PCIDev            *NewDev;

  NewDev = NULL;
  NewDev = (PCIDev *)SctAllocateZeroPool (sizeof (PCIDev));
  if (NewDev == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //Get device information
  //
  NewDev->BaseInfo.DevId   = ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_DEVICE_ID);
  NewDev->BaseInfo.VenId   = ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_VENDOR_ID);

  NewDev->BaseInfo.Command = ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_COMMAND);
  NewDev->BaseInfo.Status  = ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_STATUS);

  NewDev->BaseInfo.RevId     = ReadConfigByte (RootBridgeIo, Bus, Dev, Func, OFF_REVISION_ID);
  NewDev->BaseInfo.ClassCode = ReadConfigDWord (RootBridgeIo,Bus, Dev, Func, OFF_REVISION_ID);
  NewDev->BaseInfo.ClassCode >>= 8;

  NewDev->BaseInfo.CacheLS      = (UINT8)(ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_CACHELS) & 0xFF);
  NewDev->BaseInfo.LatencyTimer = (UINT8)(ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_CACHELS) >> 8 );
  NewDev->BaseInfo.HeaderType   = (UINT8)(ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_HEADERTYPE) & 0xFF );

  NewDev->BaseInfo.Bist = (UINT8)(ReadConfigWord (RootBridgeIo, Bus, Dev, Func, OFF_HEADERTYPE) >> 8);

  NewDev->BaseInfo.SegNum   = (UINT8)RootBridgeIo->SegmentNumber;
  NewDev->BaseInfo.BusNum   = (UINT8)Bus;
  NewDev->BaseInfo.DevNum   = (UINT8)Dev;
  NewDev->BaseInfo.FuncNum  = (UINT8)Func;

  NewDev->RootBridgeIo      = RootBridgeIo;

  NewDev->BaseInfo.ROMMask  = ReadConfigDWord (RootBridgeIo, Bus, Dev, Func, NC_EXPROM_REG);
  NewDev->BaseInfo.Scratch  = ReadConfigDWord (RootBridgeIo, Bus, Dev, Func, 0xb4);

  NewDev->BaseInfo.CardId   = 0;
  NewDev->BaseInfo.CardType = NC_NEW_CARD;

  //
  //done successfully.
  //
  *TestDev = NewDev;
  return EFI_SUCCESS;
}
