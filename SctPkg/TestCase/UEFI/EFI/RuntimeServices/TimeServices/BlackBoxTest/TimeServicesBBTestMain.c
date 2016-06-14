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

  TimeServicesBBTestMain.c

Abstract:

  Test Driver of Time Services

--*/

#include "SctLib.h"
#include "TimeServicesBBTestMain.h"

BOOLEAN
DayValid (
  IN  EFI_TIME  *Time
  );

BOOLEAN
IsLeapYear (
  IN EFI_TIME   *Time
  );

INTN DayOfMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  TPL_APPLICATION,
  TPL_CALLBACK
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  TIME_SERVICES_TEST_REVISION,
  TIME_SERVICES_TEST_GUID,
  L"Time Services Test",
  L"UEFI Time Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    TIME_SERVICES_GETTIME_CONSISTENCY_GUID,
    L"GetTime_Conf",
    L"Consistency Test for GetTime",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTimeConsistencyTest
  },
  {
    TIME_SERVICES_SETTIME_CONSISTENCY_GUID,
    L"SetTime_Conf",
    L"Consistency Test for SetTime",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetTimeConsistencyTest
  },
  {
    TIME_SERVICES_GETWAKEUPTIME_CONSISTENCY_GUID,
    L"GetWakeupTime_Conf",
    L"Consistency Test for GetWakeupTime",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetWakeupTimeConsistencyTest
  },
  {
    TIME_SERVICES_SETWAKEUPTIMEL_CONSISTENCY_GUID,
    L"SetWakeupTime_Conf",
    L"Consistency Test for SetWakeupTime",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetWakeupTimeConsistencyTest
  },
  {
    TIME_SERVICES_GETTIME_INTERFACE_GUID,
    L"GetTime_Func",
    L"Interface Test for GetTime",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTimeInterfaceTest
  },
  {
    TIME_SERVICES_SETTIME_INTERFACE_GUID,
    L"SetTime_Func",
    L"Interface Test for SetTime",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetTimeInterfaceTest
  },
  {
    TIME_SERVICES_GETWAKEUPTIME_INTERFACE_GUID,
    L"GetWakeupTime_Func",
    L"Interface Test for GetWakeupTime",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetWakeupTimeInterfaceTest
  },
  {
    TIME_SERVICES_SETWAKEUPTIME_INTERFACE_GUID,
    L"SetWakeupTime_Func",
    L"Interface Test for SetWakeupTime",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetWakeupTimeInterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    TIME_SERVICES_GETTIME_STRESS_TEST_GUID,
    L"GetTime_Stress",
    L"Stress Test for GetTime",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTimeStressTest
  },
  {
    TIME_SERVICES_GETWAKEUPTIME_STRESS_TEST_GUID,
    L"GetWakeupTime_Stress",
    L"Stress Test for GetWakeupTime",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetWakeupTimeStressTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestTimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Time Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestTimeServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestTimeServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestTimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  Verify the time.
 *  @param Time the time structure to be verified.
 *  @return TRUE the time is valid.
 *  @return FALSE the time is invalid.
 */
BOOLEAN
TimeFieldsValid (
  IN EFI_TIME *Time
  )
{
  if (Time->Year < 1998 || Time->Year > 2099) {
    return FALSE;
  }

  if (Time->Month < 1 || Time->Month > 12) {
    return FALSE;
  }

  if ( !DayValid(Time) ) {
    return FALSE;
  }

  if (Time->Hour > 23) {
    return FALSE;
  }

  if (Time->Minute > 59) {
    return FALSE;
  }

  if (Time->Second > 59) {
    return FALSE;
  }

  if (Time->Nanosecond > 999999999) {
    return FALSE;
  }

  if (!(Time->TimeZone == EFI_UNSPECIFIED_TIMEZONE ||
        (Time->TimeZone >= -1440 && Time->TimeZone <= 1440))) {
    return FALSE;
  }

  if (Time->Daylight & (~(EFI_TIME_ADJUST_DAYLIGHT | EFI_TIME_IN_DAYLIGHT))) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  Verify the day.
 *  @param Time the time structure including the day to be verified.
 *  @return TRUE the day is valid.
 *  @return FALSE the day is invalid.
 */
BOOLEAN
DayValid (
  IN  EFI_TIME  *Time
  )
{
  if (Time->Day < 1) {
    return FALSE;
  }

  if ( Time->Day > DayOfMonth[Time->Month - 1] ) {
    return FALSE;
  }

  //
  // Pay attention to month==2
  //
  if ( Time->Month == 2 && (!IsLeapYear (Time) && Time->Day > 28) ) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  Judge whether the year in the Time structure is a leap year.
 *  @param Time the time sturcture including the year to be judged.
 *  @return TRUE the year is a leap year.
 *  @return FALSE the year is not a leap year.
 */
BOOLEAN
IsLeapYear (
  IN EFI_TIME   *Time
  )
{
  if ( Time->Year % 4 == 0 ) {
    if ( Time->Year % 100 == 0 ) {
      if ( Time->Year % 400 == 0 ) {
        return TRUE;
      } else {
        return FALSE;
      }
    } else {
      return TRUE;
    }
  } else {
    return FALSE;
  }
}

void AddOneHour (
  IN OUT EFI_TIME   *Time
  )
{
  if (Time->Hour != 23) {
    Time->Hour += 1;
    return;
  }

  Time->Hour = 0;

  if ( (Time->Day != DayOfMonth[Time->Month - 1]) &&
       (!(Time->Month == 2 && (!IsLeapYear (Time) && Time->Day == 28))) ) {
    Time->Day += 1;
    return;
  }

  Time->Day = 1;

  if ( Time->Month != 12 ) {
    Time->Month += 1;
    return;
  }

  Time->Month = 1;
  Time->Year += 1;

  return;
}

/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param RecoveryLib    A pointer to Test Recovery Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  *StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test recovery support library interface
  //
  *RecoveryLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   RecoveryLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test logging support library interface
  //
  *LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   LoggingLib
                   );
  // Test logging support library is optional

  //
  // Done
  //
  return EFI_SUCCESS;
}

INTN
CompareTime (
  IN EFI_TIME   From,
  IN EFI_TIME   To
  )
/*++

Routine Description: 

  Compare the Year, Month, Day, Hour, Minute and Second of the 'From' time and the 'To' time.
  Ignore other fields here. 

Arguments:

  From  -   the first time
  To    -   the second time 

Returns:

  0  : The H/M/S of the 'From' time is same as those of 'To' time
  1  : Others
--*/
{
  if ((From.Year != To.Year) || (From.Month != To.Month) || (From.Day != To.Day) || 
  	(From.Hour != To.Hour) || (From.Minute != To.Minute) || (From.Second != To.Second) ||
  	(From.Nanosecond != To.Nanosecond) || (From.TimeZone != To.TimeZone) || (From.Daylight != To.Daylight)) {
    return 1;
  } else {
    return 0;
  }
}