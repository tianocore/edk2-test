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
    TimeStampBBTestFunction.c

Abstract:
    for EFI Driver Time Stamp Protocol's function Test

--*/
#include "TimeStampBBTestMain.h"


//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetTimestampFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TIMESTAMP_PROTOCOL                *TimeStamp;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                TimeStampValue;
  EFI_TIMESTAMP_PROPERTIES              Properties;
  

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
  
  TimeStampValue = TimeStamp->GetTimestamp();

  Status =  TimeStamp->GetProperties(&Properties);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"TIME_STAMP_PROTOCOL.GetProperties - GetProperties() fail",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
	 return Status;
  }

  if (TimeStampValue <= Properties.EndValue) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gTimeStampBBTestFunctionAssertionGuid001 ,
           L"TIME_STAMP_PROTOCOL.GetTimestamp - GetTimestamp() returns reasonable value.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetPropertiesFunctionAutoTest (
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
  EFI_TIMESTAMP_PROPERTIES              Properties;
  UINT64                                Num;
  UINTN                                 Index;

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
  
  Status =  TimeStamp->GetProperties(&Properties);
  
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {

    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gTimeStampBBTestFunctionAssertionGuid002 ,
           L"TIME_STAMP_PROTOCOL.GetProperties - GetProperties() returns EFI_SUCCESS with Properties being no NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  if (Properties.EndValue == 0xFFFFFFFFFFFFFFFF)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;  	
    for (Index = 1; Index < 64; Index++) {
      Num = (1<<Index) - 1;
	  if (Num == Properties.EndValue) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
		break;
      }	
	  if (Num > Properties.EndValue) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
		break;
      }	
    }
  }

  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gTimeStampBBTestFunctionAssertionGuid003 ,
           L"TIME_STAMP_PROTOCOL.GetProperties - Properties.EndValue returned from GetProperties() should be in 0xFFFF format.",
           L"%a:%d: EndValue - 0x%x",
           __FILE__,
           (UINTN)__LINE__,
           Properties.EndValue
           );
  
  return EFI_SUCCESS;
}

