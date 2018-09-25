/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
