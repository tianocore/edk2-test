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

  Debug.c

--*/

#include "Debug.h"
#include "ParseConf.h"

EFI_GUID              gPCDPableGuid = HCDP_TABLE_GUID;
RUNTIME_HANDOFF       *HandOffPtr = NULL;


EFI_STATUS
RecordHandOff (
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE          Gas
  )
{
  //
  // Only concern System Memory Space and System I/O Space
  //
  if(Gas.AddressSpaceId == EFI_ACPI_3_0_SYSTEM_MEMORY) {
    HandOffPtr->DebuggerInfo.MmioFlag = TRUE;
    HandOffPtr->DebuggerInfo.MmioBase = (UINTN)Gas.Address;
    SctPrint(L"Debugger Port registered in MMIO @ 0x%x.\n", HandOffPtr->DebuggerInfo.MmioBase);
  } else if (Gas.AddressSpaceId == EFI_ACPI_3_0_SYSTEM_IO) {
    HandOffPtr->DebuggerInfo.MmioFlag = FALSE;
    HandOffPtr->DebuggerInfo.IoPort = (UINTN)Gas.Address;
    SctPrint(L"Debugger Port registered in IO port @ 0x%x.\n", HandOffPtr->DebuggerInfo.IoPort);
  }
  return EFI_SUCCESS;
}

VOID
DefaultHandOff (
  VOID
  )
{
  //
  // Default use Legacy I/O COM1
  //
  HandOffPtr->DebuggerInfo.MmioFlag = FALSE;
  HandOffPtr->DebuggerInfo.IoPort   = 0x3f8;
}


EFI_STATUS
ProbePCDPTable (
  OUT EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE    *UARTGas
  )
{
  UINTN                                         Index;
  UINT32                                        TableLength;
  BOOLEAN                                       UARTFound;
  PCDP_TABLE_HEADER                             *PCDPTable;
  DEVICE_DESCRIPTOR_ENTRY                       DeviceDes;

  UARTFound           = FALSE;
  PCDPTable           = NULL;

  //
  // found PCDP table from system table
  //
  for (Index = 0; Index < tST->NumberOfTableEntries; Index++) {
    if (SctCompareGuid (&(tST->ConfigurationTable[Index].VendorGuid), &gPCDPableGuid) == 0) {
      //
      // A match was found.
      //
      PCDPTable = tST->ConfigurationTable[Index].VendorTable;
      if (PCDPTable->Header.Signature == HCDP_TABLE_SIGNATURE) {
        break;
      }
    }
  }

  if ((PCDPTable == NULL) || (PCDPTable->Header.Signature != HCDP_TABLE_SIGNATURE)){
    return EFI_NOT_FOUND;
  }

  TableLength   = PCDPTable->Header.Length;
  TableLength  -= sizeof(PCDP_TABLE_HEADER);
  DeviceDes.Raw = (UINT8*)((UINTN)PCDPTable + sizeof(PCDP_TABLE_HEADER));
  while (TableLength > 0) {
    //
    // The first byte of Device Descriptor is the entry type. We just concern Type 0 and Type 1.
    // We will use the first registered UART.
    //
    if ((*DeviceDes.Raw == UART_BIDIRECTIONAL_CONSOLE ) || (*DeviceDes.Raw == UART_DEBUG_PORT)) {
      UARTFound = TRUE;  
      break;
    }
    DeviceDes.Raw = (UINT8 *)((UINTN)DeviceDes.Raw + (UINTN)DeviceDes.PCDPDeviceDes->Length);
    TableLength -= (UINT32)DeviceDes.PCDPDeviceDes->Length;
  }

  if (!UARTFound) {
    return EFI_NOT_FOUND;
  }

  *UARTGas =  DeviceDes.UARTDeviceDes->BaseAddress;
  return EFI_SUCCESS;
}



EFI_STATUS
ProbeSPCRTable (
  OUT EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE    *UARTGas
  )
{
  UINTN                                         Index;
  UINTN                                         TableEntry;
  SPCR_ACPI_TABLE                               *spcrt;
  EFI_ACPI_DESCRIPTION_HEADER                   *Rsdt;
  EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;

  Rsdp   =  NULL;
  Rsdt   =  NULL;
  spcrt  =  NULL;
  
  //
  // found ACPI table RSD_PTR from system table
  //
  for (Index = 0; Index < tST->NumberOfTableEntries; Index++) {
    if ((SctCompareGuid (&(tST->ConfigurationTable[Index].VendorGuid), &gEfiAcpi20TableGuid) == 0) ||
        (SctCompareGuid (&(tST->ConfigurationTable[Index].VendorGuid), &gEfiAcpiTableGuid) == 0)
          ) {
      //
      // A match was found.
      //
      Rsdp = tST->ConfigurationTable[Index].VendorTable;
      break;
    }
  }

  if (Rsdp == NULL) {
    return EFI_NOT_FOUND;
  }

  Rsdt = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN) Rsdp->RsdtAddress;
  if (Rsdt == NULL || Rsdt->Signature != EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
    return EFI_NOT_FOUND;
  }

  for (Index = sizeof (EFI_ACPI_DESCRIPTION_HEADER); Index < Rsdt->Length; Index = Index + sizeof (UINT32)) {

    TableEntry  = (UINTN)(*(UINT32 *) ((UINTN)Rsdt + Index));
    spcrt    = (SPCR_ACPI_TABLE *) TableEntry;
    if (spcrt->Header.Signature == SPCR_TABLE_SIGNATURE) {
      break;
    }
  }

  if (spcrt == NULL || spcrt->Header.Signature != SPCR_TABLE_SIGNATURE) {
    return EFI_NOT_FOUND;
  }

  *UARTGas = spcrt->BaseAddress;
  return EFI_SUCCESS;
}



EFI_STATUS
RuntimeHandOff (
  IN  CONF_INFO                *ConfInfo,
  OUT UINTN                    *HandOffAddr
  )
{
  EFI_STATUS                                Status;
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE    Gas;

  Status = tBS->AllocatePool (
                 EfiRuntimeServicesData,
                 sizeof(RUNTIME_HANDOFF),
                 (VOID **)&HandOffPtr
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  *HandOffAddr =  (UINTN)HandOffPtr;
  SctZeroMem (HandOffPtr, sizeof(RUNTIME_HANDOFF));
  HandOffPtr->ConfigureInfo  = *ConfInfo;

  //
  // First probe SPCR Table for debugger information
  //
  if (!EFI_ERROR(ProbeSPCRTable(&Gas))) {
    SctPrint(L"Find Debugger Port registered in SPCRTable.\n"); 
    Status = RecordHandOff(Gas);
    return Status;
  } else if (!EFI_ERROR(ProbePCDPTable(&Gas))) {
    //
    // If SPCR not exists, then probe PCDP.
    //
    SctPrint(L"Find Debugger Port registered in PCDPTable.\n"); 
    Status = RecordHandOff(Gas);
    return Status;    
  } else {
    //
    // If not find PCDP and SCRT, use COM2 as default.
    //
    SctPrint(L"No Debugger Port registered in SPCRTable and PCDPTable. Use COM1 default\n"); 
    DefaultHandOff();
    return EFI_SUCCESS;
  }
}
