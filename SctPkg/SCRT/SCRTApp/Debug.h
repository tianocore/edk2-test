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

  Debug.h

--*/
#ifndef _DEBUG_ACCESS_H
#define _DEBUG_ACCESS_H

#include "Efi.h"
#include EFI_GUID_DEFINITION (Acpi)
#include <IndustryStandard/Acpi20.h>
#include <IndustryStandard/Acpi30.h>

#include <PiPei.h>
#include <Ppi/CpuIo.h>


//
// HCDP/PCDP Table Definition
//
#define HCDP_TABLE_GUID        \
    {0xF951938D, 0x620B, 0x42EF, 0x82, 0x79, 0xA8, 0x4B, 0x79, 0x61, 0x78, 0x98}
//
// HCDP/PCDP Table Signature Definition
//
#define HCDP_TABLE_SIGNATURE EFI_SIGNATURE_32 ('H', 'C', 'D', 'P')

//
// UART PCDP Device Type 
//
#define UART_BIDIRECTIONAL_CONSOLE                0
#define UART_DEBUG_PORT                           1

#pragma pack(1)

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER          Header;
  UINT32                               NumberEntry;
} PCDP_TABLE_HEADER;

//
// UART Device Descriptor
//
typedef  struct {
  UINT8                                       EntryType;
  UINT8                                       DataBits;
  UINT8                                       Parity;
  UINT8                                       StopBits;
  UINT8                                       PciSegNum;
  UINT8                                       PciBusNum;
  UINT8                                       PciDeviceNum;
  UINT8                                       PciFuncNum;
  UINT8                                       BaudRate[8];
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE      BaseAddress;
  UINT16                                      DeviceId;
  UINT16                                      VendorId;
  UINT32                                      Interrupt;
  UINT32                                      PseudoClockRate;
  UINT8                                       PCIClassCode;
  UINT8                                       PCIDeviceFlag;
  UINT8                                       EfiConOutDevIndex;
  UINT32                                      Reserved;
} UART_DEVICE_DESCRIPTOR;

//
// Other new standard device descriptor(Other than UART Device Descriptor)
// Here is a template struct. 
//
typedef struct {
    UINT8                                       EntryType;
    UINT8                                       PrimaryConsoleFlag;
    UINT16                                      Length;
    UINT16                                      EfiConOutDevIndex;
} PCDP_DEVICE_DESCRIPTOR;

typedef  union {
  UART_DEVICE_DESCRIPTOR                        *UARTDeviceDes;
  PCDP_DEVICE_DESCRIPTOR                        *PCDPDeviceDes;
  UINT8                                         *Raw;
} DEVICE_DESCRIPTOR_ENTRY;


//
// SPCR Table Signature Definition
//
#define SPCR_TABLE_SIGNATURE EFI_SIGNATURE_32 ('S', 'P', 'C', 'R')

//
// SPCR Table Definition
//
typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER                   Header; 
  UINT8                                         InterfaceType;
  UINT8                                         Reserved1[3];
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE        BaseAddress;
  UINT8                                         InterruptType;
  UINT8                                         Irq;
  UINT32                                        GlobalSysInter;
  UINT8                                         BaudRate;
  UINT8                                         Parity;
  UINT8                                         StopBits;
  UINT8                                         FlowControl;
  UINT8                                         TerminalType;
  UINT8                                         Reserved2;
  UINT16                                        PciDeviceId;
  UINT16                                        PciVendorId;
  UINT8                                         PciBusNum;
  UINT8                                         PciDevNum;
  UINT8                                         PciFuncNum;
  UINT32                                        PciFlag;
  UINT8                                         PciSeg;
  UINT32                                        Reserved;
} SPCR_ACPI_TABLE;

#pragma pack()


EFI_STATUS
EfiIoRead (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  );

EFI_STATUS
EfiIoWrite (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  );

#endif
