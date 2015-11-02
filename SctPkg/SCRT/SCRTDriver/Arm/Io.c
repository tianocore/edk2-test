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
                                                                
  Copyright (c) 2011 - 2012, ARM Ltd. All rights reserved.
   
--*/

/*++

Module Name:

  Io.c

--*/

#include "Io.h"

STATIC
EFI_STATUS
EFIAPI
CpuIoServiceWrite (
  IN EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN UINT64                     UserAddress,
  IN UINTN                      Count,
  IN VOID                       *UserBuffer
  )
/*++

Routine Description:

  Perform the port I/O write service

Arguments:

  Width   - Width of the port I/O operation
  Address - Base address of the port I/O operation
  Count   - Count of the number of accesses to perform
  Buffer  - Pointer to the source buffer from which to write data

Returns:

  EFI_SUCCESS           - The data was written.
  EFI_INVALID_PARAMETER - Width is invalid.
  EFI_INVALID_PARAMETER - Buffer is NULL.
  EFI_UNSUPPORTED       - The Buffer is not aligned for the given Width.
  EFI_UNSUPPORTED       - The address range specified by Address, Width,
                          and Count is not valid.

--*/
{
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EfiIoWrite (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:
  Perform an IO write into Buffer.

Arguments:
  Width   - Width of write transaction, and repeat operation to use
  Address - IO address to write
  Count   - Number of times to write the IO address.
  Buffer  - Buffer to write data from. size is Width * Count

Returns:
  Status code

--*/
{
  return CpuIoServiceWrite(Width, Address, Count, Buffer);
}


EFI_STATUS
EfiIoRead (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  )
/*++

Routine Description:
  Perform an IO read into Buffer.

Arguments:
  Width   - Width of read transaction, and repeat operation to use
  Address - IO address to read
  Count   - Number of times to read the IO address.
  Buffer  - Buffer to read data into. size is Width * Count

Returns:
  Status code

--*/
{
  return EFI_UNSUPPORTED;
}


VOID
FixAddress (
  IN UINTN     *PhyAddress
  ) 
{
		//
		//Note: On ARM platforms don't have to do this as all the functions are virtually mapped.
		//
}

// Quick port to ARM

VOID
Port80 ( 
  UINT8 Number
  )
{
  //EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Port80 %02x", Number));
}
