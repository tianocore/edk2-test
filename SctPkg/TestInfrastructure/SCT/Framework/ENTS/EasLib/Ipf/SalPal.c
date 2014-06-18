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

  SalPal.c

Abstract:

  Functions to make SAL and PAL proc calls

--*/

#include "Sctlib.h"
#include <Library/EntsLib.h>
#include "Libsalpal.h"

SAL_PROC                mSalProc;
EFI_PLABEL              mSalProcPlabel;
PAL_PROC                mPalProc;
EFI_PLABEL              mPalProcPlabel;
SAL_SYSTEM_TABLE_HEADER *mSalSystemTable;
BOOLEAN                 SalPalLibInitialized = FALSE;

EFI_STATUS
LibInitSalAndPalProc (
  VOID
  )
/*++

Routine Description:

  Initialize SAL and PAL procedure calling.

Arguments:

  None

Returns:

  EFI_SUCCESS - Always return success.

--*/
{
  SAL_ST_ENTRY_POINT_DESCRIPTOR *SalEpDesc;
  EFI_PLABEL                    *PlabelPtr;
  UINT8                         Checksum;
  UINT8                         *TableByte;
  UINTN                         Offset;
  EFI_STATUS                    Status;

  if (!SalPalLibInitialized) {
    SalPalLibInitialized  = TRUE;
    mSalProc              = NULL;
    mPalProc              = NULL;
    mSalSystemTable       = NULL;

    Status                = SctGetSystemConfigurationTable (&gtEfiSalSystemTableGuid, (VOID **) (&mSalSystemTable));
    if (EFI_ERROR (Status)) {
      SctPrint (L"Error : Sal System Table NOT found\r\n");
      return EFI_SUCCESS;
    }
    //
    // Check signature, number of entries and size. Then checksum the table.
    //
    if (((EntsCompareMem (&mSalSystemTable->Signature, EFI_SAL_ST_HEADER_SIGNATURE, 4)) != 0) &&
        (mSalSystemTable->EntryCount == 0) &&
        (mSalSystemTable->Length == 0)
        ) {
      return EFI_SUCCESS;
    }

    TableByte = (UINT8 *) mSalSystemTable;
    Checksum  = 0;
    for (Offset = 0; Offset < mSalSystemTable->Length; Offset++, TableByte++) {
      Checksum = Checksum +*TableByte;
    }

    if (Checksum != 0) {
      SctPrint (L"Error : Sal System Table checksum is invalid\r\n");
      return EFI_SUCCESS;
    }

    SalEpDesc = NULL;
    SalEpDesc = (SAL_ST_ENTRY_POINT_DESCRIPTOR *) LibSearchSalSystemTable (EFI_SAL_ST_ENTRY_POINT);

    if (SalEpDesc == NULL) {
      SctPrint (L"Error : Sal entry point not found\r\n");
      return EFI_SUCCESS;
    }

    mSalProcPlabel.EntryPoint = SalEpDesc->SalProcEntry;
    mSalProcPlabel.GP         = SalEpDesc->SalGlobalDataPointer;
    PlabelPtr                 = &mSalProcPlabel;
    mSalProc                  = *(SAL_PROC *) (&PlabelPtr);

    if ((mSalProc == NULL) || (mSalProcPlabel.EntryPoint == 0)) {
      SctPrint (L"Error : Sal entry point invalid\r\n");
      return EFI_SUCCESS;
    }

    mPalProcPlabel.EntryPoint = SalEpDesc->PalProcEntry;
    mPalProcPlabel.GP         = SalEpDesc->SalGlobalDataPointer;
    PlabelPtr                 = &mPalProcPlabel;
    mPalProc                  = *(PAL_PROC *) (&PlabelPtr);

    if (mPalProcPlabel.EntryPoint == 0) {
      SctPrint (L"Error : PAL entry point invalid\r\n");
      return EFI_SUCCESS;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
LibGetSalVersionInfo (
  IN  OUT   UINT16  *SalSpecRev,
  IN  OUT   UINT16  *SalARev,
  IN  OUT   UINT16  *SalBRev
  )
/*++

Routine Description:

  Get SAL version infomation.

Arguments:

  SalSpecRev  - SAL Spec reversion.
  SalARev     - SAL A reversion.
  SalBRev     - SAL B reversion.

Returns:

  EFI_UNSUPPORTED - mSalSystemTable is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  if (mSalSystemTable == NULL) {
    return EFI_UNSUPPORTED;
  }

  *SalSpecRev = mSalSystemTable->SalRevision;
  *SalARev    = mSalSystemTable->SalAVersion;
  *SalBRev    = mSalSystemTable->SalBVersion;
  return EFI_SUCCESS;
}

EFI_STATUS
LibGetSalIoPortMapping (
  OUT UINT64  *IoPortMapping
  )
/*++

Routine Description:

  Get the IO Port Map from the SAL System Table.

Arguments:

  IoPortMapping  - Pointer to receive IO port mapping address.

Returns:

  EFI_UNSUPPORTED - mSalSystemTable is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  SAL_ST_MEMORY_DESCRIPTOR_ENTRY  *SalMemDesc;

  SalMemDesc = (SAL_ST_MEMORY_DESCRIPTOR_ENTRY *) LibSearchSalSystemTable (EFI_SAL_ST_MEMORY_DESCRIPTOR);

  if (SalMemDesc == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (SalMemDesc->Type == EFI_SAL_ST_MEMORY_DESCRIPTOR) {
    if (SalMemDesc->MemoryType == SAL_IO_PORT_MAPPING) {
      *IoPortMapping = SalMemDesc->PhysicalMemoryAddress;
      return EFI_SUCCESS;
    }

    SalMemDesc++;
  }

  return EFI_UNSUPPORTED;
}

EFI_STATUS
LibGetSalIpiBlock (
  OUT UINT64  *IpiBlock
  )
/*++

Routine Description:

  Get the IPI block from the SAL system table

Arguments:

  IpiBlock  - Pointer to receive IPI block address.

Returns:

  EFI_UNSUPPORTED - SalMemDesc is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  SAL_ST_MEMORY_DESCRIPTOR_ENTRY  *SalMemDesc;

  SalMemDesc = (SAL_ST_MEMORY_DESCRIPTOR_ENTRY *) LibSearchSalSystemTable (EFI_SAL_ST_MEMORY_DESCRIPTOR);

  if (SalMemDesc == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (SalMemDesc->Type == EFI_SAL_ST_MEMORY_DESCRIPTOR) {
    if (SalMemDesc->MemoryType == SAL_SAPIC_IPI_BLOCK) {
      *IpiBlock = SalMemDesc->PhysicalMemoryAddress;
      return EFI_SUCCESS;
    }

    SalMemDesc++;
  }

  return EFI_UNSUPPORTED;
}

EFI_STATUS
LibGetSalWakeupVector (
  OUT UINT64  *WakeVector
  )
/*++

Routine Description:

  Get the wakeup vector from the SAL system table

Arguments:

  WakeVector  - Pointer to receive wakeup vector.

Returns:

  EFI_UNSUPPORTED - Cannot find wakeup decriptor.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  SAL_ST_AP_WAKEUP_DECRIPTOR  *ApWakeUp;

  ApWakeUp = (SAL_ST_AP_WAKEUP_DECRIPTOR *) LibSearchSalSystemTable (EFI_SAL_ST_AP_WAKEUP);
  if (!ApWakeUp) {
    return EFI_UNSUPPORTED;
  }

  *WakeVector = ApWakeUp->ExternalInterruptVector;
  return EFI_SUCCESS;
}

VOID *
LibSearchSalSystemTable (
  IN  UINT8   EntryType
  )
/*++

Routine Description:

  Search SAL system table.

Arguments:

  EntryType - SAL entry type.

Returns:

  None.

--*/
{

  UINT8   *SalTableHack;
  UINT16  EntryCount;
  UINT16  Count;

  if (mSalSystemTable == NULL) {
    return NULL;
  }

  EntryCount = mSalSystemTable->EntryCount;
  if (EntryCount == 0) {
    return NULL;
  }
  //
  // BugBug: Add code to test checksum on the Sal System Table
  //
  SalTableHack = (UINT8 *) mSalSystemTable;
  SalTableHack += sizeof (SAL_SYSTEM_TABLE_HEADER);

  for (Count = 0; Count < EntryCount; Count++) {
    if (*SalTableHack == EntryType) {
      return (VOID *) SalTableHack;
    }

    switch (*SalTableHack) {
    case EFI_SAL_ST_ENTRY_POINT:
      SalTableHack += sizeof (SAL_ST_ENTRY_POINT_DESCRIPTOR);
      break;

    case EFI_SAL_ST_MEMORY_DESCRIPTOR:
      SalTableHack += sizeof (SAL_ST_MEMORY_DESCRIPTOR_ENTRY);
      break;

    case EFI_SAL_ST_PLATFORM_FEATURES:
      SalTableHack += sizeof (SAL_ST_PLATFORM_FEATURES);
      break;

    case EFI_SAL_ST_TR_USAGE:
      SalTableHack += sizeof (SAL_ST_TR_DECRIPTOR);
      break;

    case EFI_SAL_ST_PTC:
      SalTableHack += sizeof (SAL_ST_CACHE_COHERENCE_DECRIPTOR);
      break;

    case EFI_SAL_ST_AP_WAKEUP:
      SalTableHack += sizeof (SAL_ST_AP_WAKEUP_DECRIPTOR);
      break;

    default:
      ASSERT (FALSE);
      break;
    }
  }

  return NULL;
}

SAL_RETURN_REGS
LibSalProc (
  IN  UINT64    Arg1,
  IN  UINT64    Arg2,
  IN  UINT64    Arg3,
  IN  UINT64    Arg4,
  IN  UINT64    Arg5,
  IN  UINT64    Arg6,
  IN  UINT64    Arg7,
  IN  UINT64    Arg8
  )
{
  return mSalProc (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);
}
