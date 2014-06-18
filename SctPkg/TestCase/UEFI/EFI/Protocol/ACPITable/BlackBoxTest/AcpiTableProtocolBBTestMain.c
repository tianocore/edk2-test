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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AcpiTableBBTestMain.c

Abstract:

  Test Driver of Acpi Table Protocol

--*/

#include "SctLib.h"
#include "AcpiTableProtocolBBTestMain.h"

//
// Global variables
//

EFI_HANDLE mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_ACPI_TABLE_PROTOCOL_TEST_REVISION,
  EFI_ACPI_TABLE_PROTOCOL_GUID,
  L"Acpi Table Protocol Test",
  L"UEFI Acpi Table Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0101,
    L"InstallAcpiTableFunction",
    L"Function test for Acpi Table Protocol InstallAcpiTable().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestInstallAcpiTableFunctionTest
  },
  {
    EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0102,
    L"UninstallAcpiTableFunction",
    L"Function test for Acpi Table Protocol UninstallAcpiTable().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallAcpiTableFunctionTest
  },
  {
    EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0201,
    L"InstallAcpiTableConformance",
    L"Conformance test for Acpi Table Protocol InstallAcpiTable().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestInstallAcpiTableConformanceTest
  },
  {
    EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0202,
    L"UninstallAcpiTableConformance",
    L"Conformance test for Acpi Table Protocol UninstallAcpiTable( ).",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallAcpiTableConformanceTest
  },
  0
};

EFI_BB_TEST_PROTOCOL                  *gBBTestProtocolInterface;

//
// Unload function
//

EFI_STATUS
UnloadAcpiTableProtocolBBTest (
  IN EFI_HANDLE                   ImageHandle
  );


EFI_STATUS
InitializeBBTestAcpiTableProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadBBTestAcpiTableProtocol,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadBBTestAcpiTableProtocol (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
  Calculate the sum of all elements in a buffer in unit of UINT8. 
  During calculation, the carry bits are dropped.

  This function calculates the sum of all elements in a buffer 
  in unit of UINT8. The carry bits in result of addition are dropped. 
  The result is returned as UINT8. If Length is Zero, then Zero is 
  returned.
  
  If Buffer is NULL, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT(). 

  @param  Buffer    Pointer to the buffer to carry out the sum operation.
  @param  Length    The size, in bytes, of Buffer .

  @return Sum       The sum of Buffer with carry bits dropped during additions.

**/
STATIC
UINT8
EFIAPI
CalculateSum8 (
  IN      CONST UINT8               *Buffer,
  IN      UINTN                     Length
  )
{
  UINT8     Sum;
  UINTN     Count;

  ASSERT (Buffer != NULL);
  //ASSERT (Length <= (MAX_ADDRESS - ((UINTN) Buffer) + 1));

  for (Sum = 0, Count = 0; Count < Length; Count++) {
    Sum = (UINT8) (Sum + *(Buffer + Count));
  }
  
  return Sum;
}


/**
  Returns the two's complement checksum of all elements in a buffer 
  of 8-bit values.

  This function first calculates the sum of the 8-bit values in the 
  buffer specified by Buffer and Length.  The carry bits in the result 
  of addition are dropped. Then, the two's complement of the sum is 
  returned.  If Length is 0, then 0 is returned.
  
  If Buffer is NULL, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().


  @param  Buffer    Pointer to the buffer to carry out the checksum operation.
  @param  Length    The size, in bytes, of Buffer.

  @return Checksum  The 2's complement checksum of Buffer.

**/
UINT8
EFIAPI
TestCalculateCheckSum8 (
  IN      CONST UINT8             *Buffer,
  IN      UINTN                   Length
  )
{
  UINT8     CheckSum;

  CheckSum = CalculateSum8 (Buffer, Length);

  //
  // Return the checksum based on 2's complement.
  //
  return (UINT8) (0x100 - CheckSum);
}
