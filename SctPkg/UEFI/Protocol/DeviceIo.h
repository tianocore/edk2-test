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

  DeviceIoProtocol.h

Abstract:

  Device IO protocol as defined in the EFI 1.1 specification.

  Device IO is used to abstract hardware access to devices. It includes
  memory mapped IO, IO, PCI Config space, and DMA.


--*/

#ifndef _DEVICE_IO_PROTOCOL_H_
#define _DEVICE_IO_PROTOCOL_H_

//
// Prevent the original DeviceIo.h is included
//
#define _DEVICE_IO_H_

#define EFI_DEVICE_IO_PROTOCOL_GUID \
  { 0xaf6ac311, 0x84c3, 0x11d2, 0x8e, 0x3c, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

typedef struct _EFI_DEVICE_IO_PROTOCOL EFI_DEVICE_IO_PROTOCOL;;

typedef enum {
  IO_UINT8 = 0,
  IO_UINT16,
  IO_UINT32,
  IO_UINT64,
  MMIO_COPY_UINT8,
  MMIO_COPY_UINT16,
  MMIO_COPY_UINT32,
  MMIO_COPY_UINT64,
  IO_WIDTH_MAXIMUM
} EFI_IO_WIDTH;

typedef
EFI_STATUS
(EFIAPI *EFI_DEVICE_IO) (
  IN EFI_DEVICE_IO_PROTOCOL *This,
  IN EFI_IO_WIDTH                   Width,
  IN UINT64                         Address,
  IN UINTN                          Count,
  IN OUT VOID                       *Buffer
  );

typedef struct {
  EFI_DEVICE_IO                   Read;
  EFI_DEVICE_IO                   Write;
} EFI_IO_ACCESS;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_DEVICE_PATH) (
  IN EFI_DEVICE_IO_PROTOCOL   *This,
  IN UINT64                           Address,
  IN OUT EFI_DEVICE_PATH_PROTOCOL     **PciDevicePath
  );

typedef enum {
  EfiBusMasterRead,
  EfiBusMasterWrite,
  EfiBusMasterCommonBuffer
} EFI_IO_OPERATION_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_IO_MAP) (
  IN EFI_DEVICE_IO_PROTOCOL   *This,
  IN EFI_IO_OPERATION_TYPE            Operation,
  IN EFI_PHYSICAL_ADDRESS             *HostAddress,
  IN OUT UINTN                        *NumberOfBytes,
  OUT EFI_PHYSICAL_ADDRESS            *DeviceAddress,
  OUT VOID                            **Mapping
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_UNMAP) (
  IN EFI_DEVICE_IO_PROTOCOL   *This,
  IN VOID                             *Mapping
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_ALLOCATE_BUFFER) (
  IN EFI_DEVICE_IO_PROTOCOL   *This,
  IN EFI_ALLOCATE_TYPE                Type,
  IN EFI_MEMORY_TYPE                  MemoryType,
  IN UINTN                            Pages,
  IN OUT EFI_PHYSICAL_ADDRESS         *HostAddress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_FLUSH) (
  IN EFI_DEVICE_IO_PROTOCOL  *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_FREE_BUFFER) (
  IN EFI_DEVICE_IO_PROTOCOL   *This,
  IN UINTN                            Pages,
  IN EFI_PHYSICAL_ADDRESS             HostAddress
  );

struct _EFI_DEVICE_IO_PROTOCOL {
  EFI_IO_ACCESS                       Mem;
  EFI_IO_ACCESS                       Io;
  EFI_IO_ACCESS                       Pci;
  EFI_IO_MAP                          Map;
  EFI_PCI_DEVICE_PATH                 PciDevicePath;
  EFI_IO_UNMAP                        Unmap;
  EFI_IO_ALLOCATE_BUFFER              AllocateBuffer;
  EFI_IO_FLUSH                        Flush;
  EFI_IO_FREE_BUFFER                  FreeBuffer;
};


extern EFI_GUID gBlackBoxEfiDeviceIoProtocolGuid;

#endif
