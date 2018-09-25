/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MiscBootServicesBBTestMain.c

Abstract:

  Test Driver of Miscellaneous Boot Services

--*/

#include "SctLib.h"
#include "MiscBootServicesBBTestMain.h"



EFI_GUID gMiscBootServicesTestTableGuid = MISC_BOOT_SERVICES_TEST_TABLE_GUID;

//
// Change size from TPL_ARRAY_SIZE to TPL_ARRAY_SIZE + 1
// for Stall test in TPL_HIGH_LEVEL
//
EFI_TPL TplArray[TPL_ARRAY_SIZE + 1] = {
  TPL_APPLICATION,
  TPL_CALLBACK,
  TPL_NOTIFY,
  TPL_HIGH_LEVEL
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
EFIAPI
BBTestMiscBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Miscellaneous Boot Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestMiscBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

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
EFIAPI
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
    End = Start + SctLShiftU64 (Descriptor->NumberOfPages, EFI_PAGE_SHIFT) - 1;
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
