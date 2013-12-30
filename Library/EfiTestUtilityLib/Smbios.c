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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Smbios.c

Abstract:

  Lib fucntions for SMBIOS. Used to get system serial number and GUID

--*/

#include "lib.h"


EFI_STATUS
LibGetSmbiosSystemGuidAndSerialNumber (
  IN  EFI_GUID    *SystemGuid,
  OUT CHAR8       **SystemSerialNumber
  )
{
  EFI_STATUS                  Status;
  SMBIOS_STRUCTURE_TABLE      *SmbiosTable;
  SMBIOS_STRUCTURE_POINTER    Smbios;
  SMBIOS_STRUCTURE_POINTER    SmbiosEnd;
  UINT16                      Index;

  Status = LibGetSystemConfigurationTable(&gtEfiSMBIOSTableGuid, (VOID **)&SmbiosTable);
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  //
  // BUGBUG: Disabled warnings 4306, converting a 32 bit pointer into a
  // 64 bit pointer. In SMBIOS tables, the addresses are 32 bit, and
  // causes warning:4306 with 64 bit pointers. Probably need a better
  // solution.
  //
#ifndef __GNUC__
#  pragma warning ( disable : 4306 )
#endif

  Smbios.Hdr = (SMBIOS_HEADER *)SmbiosTable->TableAddress;

  SmbiosEnd.Raw = (UINT8 *)(SmbiosTable->TableAddress + SmbiosTable->TableLength);
  for (Index = 0; Index < SmbiosTable->TableLength ; Index++) {
    if (Smbios.Hdr->Type == 1) {
      if (Smbios.Hdr->Length < 0x19) {
        //
        // Older version did not support Guid and Serial number
        //
        continue;
      }

      //
      // SMBIOS tables are byte packed so we need to do a byte copy to
      //  prevend alignment faults on Itanium-based platform.
      //
      CopyMem (SystemGuid, &Smbios.Type1->Uuid, sizeof(EFI_GUID));
      *SystemSerialNumber = LibGetSmbiosString(&Smbios, Smbios.Type1->SerialNumber);
      return EFI_SUCCESS;
    }

    //
    // Make Smbios point to the next record
    //
    LibGetSmbiosString (&Smbios, (UINT16)(-1));

    if (Smbios.Raw >= SmbiosEnd.Raw) {
      //
      // SMBIOS 2.1 incorrectly stated the length of SmbiosTable as 0x1e.
      //  given this we must double check against the lenght of
      /// the structure. My home PC has this bug.ruthard
      //
      return EFI_SUCCESS;
    }
  }

  return EFI_SUCCESS;
}

CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  )
/*++

  Return SMBIOS string given the string number.

  Arguments:
      Smbios - Pointer to SMBIOS structure
      StringNumber - String number to return. -1 is used to skip all strings and
          point to the next SMBIOS structure.

  Returns:
      Pointer to string, or pointer to next SMBIOS strcuture if StringNumber == -1
--*/
{
  UINT16  Index;
  CHAR8   *String;

  //
  // Skip over formatted section
  //
  String = (CHAR8 *)(Smbios->Raw + Smbios->Hdr->Length);

  //
  // Look through unformated section
  //
  for (Index = 1; Index <= StringNumber; Index++) {
    if (StringNumber == Index) {
      return String;
    }

    //
    // Skip string
    //
    for (; *String != 0; String++);
    String++;

    if (*String == 0) {
      //
      // If double NULL then we are done.
      //  Retrun pointer to next structure in Smbios.
      //  if you pass in a -1 you will always get here
      //
      Smbios->Raw = (UINT8 *)++String;
      return NULL;
    }
  }
  return NULL;
}
#ifndef __GNUC__
#  pragma warning ( default : 4306 )
#endif
