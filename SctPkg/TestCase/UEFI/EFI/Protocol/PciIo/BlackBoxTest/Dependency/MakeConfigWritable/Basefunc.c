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

  BaseFunc.h

Abstract:
  based Function to read and write Pci configuration.

--*/

#include "Common.h"
#include <UEFI/Protocol/PciIo.h>

/*
 *  Read a byte from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a byte read out from the configuration space.
 */
UINT8
ReadConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT8       Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint8, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  Read a word from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a word read out from the configuration space.
 */
UINT16
ReadConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT16      Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint16, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  Read Double word from configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @return a Dword read out from the configuration space.
 */
UINT32
ReadConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset
  )
{
  UINT64      FuncAddress;
  UINT32      Data;

  FuncAddress = 0x0;
  Data        = 0x0;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;

  RootBridgeIo->Pci.Read (RootBridgeIo, EfiPciIoWidthUint32, FuncAddress, 1, &Data);
  return Data;
}


/*
 *  write a byte into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigByte (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT8                             Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint8, FuncAddress, 1, &Value);
}


/*
 *  write a word into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT16                             Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint16, FuncAddress, 1, &Value);
}

/*
 *  write double word into configuration space.
 *  @param RootBridge the Root Bridge IO protocol interface.
 *  @param Bus the Destination Bus Number.
 *  @param Device the Destination Device Number.
 *  @param Func the Destination Function Number.
 *  @param Offset the Register offset in configuraion space.
 *  @param Value the value to be written.
 */
VOID
WriteConfigDWord (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Func,
  IN  UINT8                             Offset,
  IN  UINT32                            Value
  )
{
  UINT64                        FuncAddress;

  FuncAddress = 0x00;
  FuncAddress = (Bus << 24) + (Device << 16) + (Func << 8) + Offset;
  RootBridgeIo->Pci.Write (RootBridgeIo, EfiPciIoWidthUint32, FuncAddress, 1, &Value);
}
