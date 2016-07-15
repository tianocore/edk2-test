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
                                                                
  Copyright 2006 - 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

