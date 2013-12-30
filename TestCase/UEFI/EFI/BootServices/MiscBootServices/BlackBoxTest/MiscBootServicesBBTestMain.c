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

  MiscBootServicesBBTestMain.c

Abstract:

  Test Driver of Miscellaneous Boot Services

--*/

#include "MiscBootServicesBBTestMain.h"

#define MAX_MAP_SIZE 0x2000
UINT8 MemoryMap[MAX_MAP_SIZE];

EFI_GUID gMiscBootServicesTestTableGuid = MISC_BOOT_SERVICES_TEST_TABLE_GUID;

//
// Change size from TPL_ARRAY_SIZE to TPL_ARRAY_SIZE + 1
// for Stall test in EFI_TPL_HIGH_LEVEL
//
EFI_TPL TplArray[TPL_ARRAY_SIZE + 1] = {
  EFI_TPL_APPLICATION,
  EFI_TPL_CALLBACK,
  EFI_TPL_NOTIFY,
  EFI_TPL_HIGH_LEVEL
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  MISCELLANEOUS_BOOT_SERVICES_TEST_REVISION,
  MISCELLANEOUS_BOOT_SERVICES_TEST_GUID,
  L"Misc. Boot Services Test",
  L"UEFI Misc. Boot Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    MISC_BOOT_SERVICES_SETWATCHDOGTIMER_CONSISTENCY_GUID,
    L"SetWatchdogTimer_Conf",
    L"Consistency Test for SetWatchdogTimer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetWatchdogTimerConsistencyTest
  },
  {
    MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_CONSISTENCY_GUID,
    L"GetNextMonotonicCount_Conf",
    L"Consistency Test for GetNextMonotonicCount",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextMonotonicCountConsistencyTest
  },
  {
    MISC_BOOT_SERVICES_INSTALLCONFIGURATIONTABLE_CONSISTENCY_GUID,
    L"InstallConfigurationTable_Conf",
    L"Consistency Test for InstallConfigurationTable",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallConfigurationTableConsistencyTest
  },
  {
    MISC_BOOT_SERVICES_CALCULATECRC32_CONSISTENCY_GUID,
    L"CalculateCrc32_Conf",
    L"Consistency Test for CalculateCrc32",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCalculateCrc32ConsistencyTest
  },
  {
    MISC_BOOT_SERVICES_SETWATCHDOGTIMER_INTERFACE_GUID,
    L"SetWatchdogTimer_Func",
    L"Interface Test for SetWatchdogTimer",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestSetWatchdogTimerInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_STALL_INTERFACE_GUID,
    L"Stall_Func",
    L"Interface Test for Stall",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStallInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_COPYMEM_INTERFACE_GUID,
    L"CopyMem_Func",
    L"Interface Test for CopyMem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCopyMemInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_SETMEM_INTERFACE_GUID,
    L"SetMem_Func",
    L"Interface Test for SetMem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetMemInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_INTERFACE_GUID,
    L"GetNextMonotonicCount_Func",
    L"Interface Test for GetNextMonotonicCount",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextMonotonicCountInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_INSTALLCONFIGURATIONTABLE_INTERFACE_GUID,
    L"InstallConfigurationTable_Func",
    L"Interface Test for InstallConfigurationTable",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallConfigurationTableInterfaceTest
  },
  {
    MISC_BOOT_SERVICES_CALCULATECRC32_INTERFACE_GUID,
    L"CalculateCrc32_Func",
    L"Interface Test for CalculateCrc32",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCalculateCrc32InterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MISC_BOOT_SERVICES_SETWATCHDOGTIMER_STRESS_TEST_GUID,
    L"SetWatchdogTimer_Stress",
    L"Stress Test for SetWatchdogTimer",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetWatchdogTimerStressTest
  },
  {
    MISC_BOOT_SERVICES_STALL_STRESS_TEST_GUID,
    L"Stall_Stress",
    L"Stress Test for Stall",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStallStressTest
  },
  {
    MISC_BOOT_SERVICES_COPYMEM_STRESS_TEST_GUID,
    L"CopyMem_Stress",
    L"Stress Test for CopyMem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCopyMemStressTest
  },
  {
    MISC_BOOT_SERVICES_SETMEM_STRESS_TEST_GUID,
    L"SetMem_Stress",
    L"Stress Test for SetMem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetMemStressTest
  },
  {
    MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_STRESS_TEST_GUID,
    L"GetNextMonotonicCount_Stress",
    L"Stress Test for GetNextMonotonicCount",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextMonotonicCountStressTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestMiscBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBBTestMiscBootServices)

/**
 *  Miscellaneous Boot Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestMiscBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestMiscBootServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
*/
EFI_STATUS
BBTestMiscBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  Calculate the elapsed seconds from the base year.
 *  @param BaseYear the base year.
 *  @param Year current year.
 *  @param Month current month.
 *  @param Day current day.
 *  @param Hour current hour.
 *  @param Minute current minute.
 *  @param Second current second.
 *  @return  seconds the elapsed seconds.
 */
UINT32
SecondsElapsedFromBaseYear (
  UINT16      BaseYear,
  UINT16      Year,
  UINT8       Month,
  UINT8       Day,
  UINT8       Hour,
  UINT8       Minute,
  UINT8       Second
  )
{
  UINTN       seconds;
  UINT32      leapyear;
  INTN        i;

  seconds  = 0;
  for (i = BaseYear; i < Year; ++i) {
    if (isleap (i)) {
      seconds += DAYSPERLYEAR * SECSPERDAY;
    } else {
      seconds += DAYSPERNYEAR * SECSPERDAY;
    }
  }
  leapyear = isleap (Year);
  for (i = 0; i < Month - 1; ++i) {
    seconds += mon_lengths[leapyear][i] * SECSPERDAY;
  }
  for (i = 0; i < Day - 1; ++i) {
    seconds += SECSPERDAY;
  }
  for (i = 0; i < Hour; ++i) {
    seconds += SECSPERHOUR;
  }
  for (i = 0; i < Minute; ++i) {
    seconds += SECSPERMIN;
  }

  return (UINT32) (seconds + Second);
}

/**
 *  Calculate the elapsed seconds between two times.
 *  @param StartTime the start time.
 *  @param EndTime the end time.
 *  @return  seconds the elapsed seconds.
 */
UINT32
GetSecondsElapsed (
  EFI_TIME       *StartTime,
  EFI_TIME       *EndTime
  )
{
  UINT32    SecondsElapsed;

  SecondsElapsed = SecondsElapsedFromBaseYear (
                     StartTime->Year,
                     EndTime->Year,
                     EndTime->Month,
                     EndTime->Day,
                     EndTime->Hour,
                     EndTime->Minute,
                     EndTime->Second
                     ) -
                   SecondsElapsedFromBaseYear (
                     StartTime->Year,
                     StartTime->Year,
                     StartTime->Month,
                     StartTime->Day,
                     StartTime->Hour,
                     StartTime->Minute,
                     StartTime->Second
                     );

  return SecondsElapsed;
}

/**
 *  Fill a buffer with a specified value.
 *  @param Buffer the buffer to set value.
 *  @param Size the size of the buffer.
 *  @param Value the value to set.
 */
VOID
SetTestMem (
  IN UINT8 *Buffer,
  IN UINTN Size,
  IN UINT8 Value
  )
{
  UINTN          Index;

  for (Index = 0; Index < Size; Index ++) {
    Buffer[Index] = Value;
  }
}

/**
 *  Check a buffer with a specified value.
 *  @param Buffer the buffer to check value.
 *  @param Size the size of the buffer.
 *  @param Value the value to check.
 */
EFI_STATUS
CheckTestMem (
  IN UINT8 *Buffer,
  IN UINTN Size,
  IN UINT8 Value
  )
{
  UINTN          Index;

  for (Index = 0; Index < Size; Index ++) {
    if (Buffer[Index] != Value) {
      return EFI_ABORTED;
    }
  }
  return EFI_SUCCESS;
}

/**
 *  Check the memory type.
 *  @param Memory the memory start address.
 *  @param Size the memory size in byte.
 *  @param Type the memory type.
 *  @return EFI_SUCCESS the memory type is correct.
 *  @return EFI_NOT_FOUND the memory type is not correct.
 */
EFI_STATUS
CheckMemoryType (
  EFI_PHYSICAL_ADDRESS        Memory,
  UINTN                       Size,
  UINT32                      Type
  )
{
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINT8                                *MemoryMap;
  UINT8                                TmpMemoryMap[1];
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                Index;
  EFI_MEMORY_DESCRIPTOR                *Descriptor;
  EFI_PHYSICAL_ADDRESS                 MemoryEnd;
  EFI_PHYSICAL_ADDRESS                 Start;
  EFI_PHYSICAL_ADDRESS                 End;

  MemoryMapSize = 1;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)TmpMemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  MemoryMapSize += EFI_PAGE_SIZE;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MemoryMapSize,
                   (VOID**)&MemoryMap
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (
            (VOID*)MemoryMap
            );
    return Status;
  }

  MemoryEnd = Memory + Size - 1;
  for (Index = 0; Index < MemoryMapSize; Index += DescriptorSize) {
    Descriptor = (EFI_MEMORY_DESCRIPTOR *) (MemoryMap + Index);
    Start = Descriptor->PhysicalStart;
    End = Start + LShiftU64 (Descriptor->NumberOfPages, EFI_PAGE_SHIFT) - 1;
    if ((Start <= Memory) && (MemoryEnd <= End) &&
        (Descriptor->Type == Type)) {
      gtBS->FreePool (
              (VOID*)MemoryMap
              );
      return EFI_SUCCESS;
    }
  }

  gtBS->FreePool (
          (VOID*)MemoryMap
          );
  return EFI_NOT_FOUND;
}

UINT32 mCrcTable[256] = {
  0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F,
  0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
  0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
  0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
  0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
  0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
  0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
  0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
  0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
  0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
  0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106,
  0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
  0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D,
  0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
  0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
  0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
  0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7,
  0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
  0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA,
  0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
  0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
  0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
  0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84,
  0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
  0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
  0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
  0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
  0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
  0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55,
  0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
  0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28,
  0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
  0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
  0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
  0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
  0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
  0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69,
  0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
  0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
  0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
  0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693,
  0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
  0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
  };

EFI_STATUS
StdCalculateCrc32 (
  IN     UINT8                          *Data,
  IN     UINTN                          DataSize,
  IN OUT UINT32                         *CrcOut
  )
/*++

Routine Description:

  The CalculateCrc32 routine.

Arguments:

  Data        - The buffer contaning the data to be processed
  DataSize    - The size of data to be processed
  CrcOut      - A pointer to the caller allocated UINT32 that on
                contains the CRC32 checksum of Data

Returns:

  EFI_SUCCESS               - Calculation is successful.
  EFI_INVALID_PARAMETER     - Data / CrcOut = NULL, or DataSize = 0

--*/
{
  UINT32  Crc;
  UINTN   Index;
  UINT8   *Ptr;

  if (( DataSize == 0) || (Data == NULL) || (CrcOut == NULL) )
  {
    return EFI_INVALID_PARAMETER;
  }

  Crc = 0xffffffff;
  for (Index = 0, Ptr = Data; Index < DataSize; Index++, Ptr++) {
    Crc = (Crc >> 8) ^ mCrcTable[(UINT8) Crc ^ *Ptr];
  }
  *CrcOut = Crc ^ 0xffffffff;

  return EFI_SUCCESS;
}
