/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    TimeStampBBTestConformance.c

Abstract:
    for EFI Driver Time Stamp Protocol's conformance Test

--*/
#include "TimeStampBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestGetPropertiesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TIMESTAMP_PROTOCOL               *TimeStamp;
  EFI_TEST_ASSERTION                    AssertionType;
  
  //
  // init
  //
  TimeStamp = (EFI_TIMESTAMP_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status =  TimeStamp->GetProperties(NULL);
  
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gTimeStampBBTestConformanceAssertionGuid001 ,
           L"TIME_STAMP_PROTOCOL.GetProperties - GetProperties() returns EFI_INVALID_PARAMETER with Properties being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}
