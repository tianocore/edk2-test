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

  AcpiTableProtocol.h

Abstract:

  ACPI Table Protocol from the UEFI 2.1 specification.

  This protocol may be used to install or remove an ACPI table from a platform.

--*/

#ifndef _ACPI_TABLE_PROTOCOL_H_
#define _ACPI_TABLE_PROTOCOL_H_


//
// Global ID for the Acpi Table Protocol
//
#define EFI_ACPI_TABLE_PROTOCOL_GUID \
  { 0xffe06bdd, 0x6107, 0x46a6, 0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c }

typedef struct _EFI_ACPI_TABLE_PROTOCOL EFI_ACPI_TABLE_PROTOCOL;;

typedef struct {
  UINT32  Signature;
  UINT32  Length;
  UINT8   Revision;
  UINT8   Checksum;
  UINT8   OemId[6];
  UINT64  OemTableId;
  UINT32  OemRevision;
  UINT32  CreatorId;
  UINT32  CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_TABLE_INSTALL_ACPI_TABLE) (
  IN EFI_ACPI_TABLE_PROTOCOL                    *This,
  IN VOID                                       *AcpiTableBuffer,
  IN UINTN                                      AcpiTableBufferSize,
  OUT UINTN                                     *TableKey
  )
/*++

  Routine Description:
    Installs an ACPI table into the RSDT/XSDT.

  Arguments:
    This                  - Protocol instance pointer.
    AcpiTableBuffer       - A pointer to a buffer containing the ACPI table to be installed.
    AcpiTableBufferSize   - Specifies the size, in bytes, of the AcpiTableBuffer buffer.
    TableKey              - Reurns a key to refer to the ACPI table.

  Returns:
    EFI_SUCCESS           - The table was successfully inserted.
    EFI_INVALID_PARAMETER - Either AcpiTableBuffer is NULL, TableKey is NULL, or AcpiTableBufferSize 
                            and the size field embedded in the ACPI table pointed to by AcpiTableBuffer
                            are not in sync.
    EFI_OUT_OF_RESOURCES  - Insufficient resources exist to complete the request.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE) (
  IN EFI_ACPI_TABLE_PROTOCOL                    *This,
  IN UINTN                                      TableKey
  )
/*++

  Routine Description:
    Removes an ACPI table from the RSDT/XSDT.

  Arguments:
    This          - Protocol instance pointer.
    TableKey      - Specifies the table to uninstall.  The key was returned from InstallAcpiTable().

  Returns:
    EFI_SUCCESS   - The table was successfully uninstalled.
    EFI_NOT_FOUND - TableKey does not refer to a valid key for a table entry.

--*/
;

//
// Interface structure for the ACPI Table Protocol
//
struct _EFI_ACPI_TABLE_PROTOCOL {
  EFI_ACPI_TABLE_INSTALL_ACPI_TABLE    InstallAcpiTable;
  EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE  UninstallAcpiTable;
};

extern EFI_GUID gBlackBoxEfiAcpiTableProtocolGuid;

#endif
