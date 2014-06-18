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

    iScsiInitiatorNameBBTestConformance.c

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec 2.0 )

Revision History

--*/

#include "SctLib.h"
#include "iScsiInitiatorNameBBTestMain.h"

EFI_STATUS
BBTestGetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1, Status2;
  EFI_ISCSI_INITIATOR_NAME_PROTOCOL    *iScsiInitiatorName;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                BufferSize;
  UINTN                                OutBufferSize;
  CHAR8                                Buffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];

  //
  // Get the Standard Library Interface
  //
  Status1 = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status1) ) {
    return Status1;
  }

  iScsiInitiatorName = (EFI_ISCSI_INITIATOR_NAME_PROTOCOL *)ClientInterface;

  BufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;
  Status = iScsiInitiatorName->Get (iScsiInitiatorName, &BufferSize, (VOID *)Buffer);
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Get() Fail, please init iScsiInitiatorName or check the hardware",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status1 = iScsiInitiatorName->Get (iScsiInitiatorName, NULL, (VOID *)Buffer);
  Status2 = iScsiInitiatorName->Get (iScsiInitiatorName, &BufferSize, NULL);
  if ((Status1 == EFI_INVALID_PARAMETER) && (Status2 == EFI_INVALID_PARAMETER)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestConformanceAssertionGuid002,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Get() with invalid parameter",
                 L"%a:%d:Status1 - %r; Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2
                 );

  OutBufferSize = 0;
  Status1 = iScsiInitiatorName->Get (iScsiInitiatorName, &OutBufferSize, (VOID *)Buffer);
  if (Status1 == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if ( BufferSize != OutBufferSize )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestConformanceAssertionGuid003,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Get() with InValidBufferSize which is too small to the result",
                 L"%a:%d:Status1 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status[2];
  EFI_ISCSI_INITIATOR_NAME_PROTOCOL    *iScsiInitiatorName;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                BufferSize;
  UINTN                                InvalidBufferSize;
  CHAR8                                GetBuffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];
  CHAR8                                SetBuffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];

  //
  // Get the Standard Library Interface
  //
  Status[0] = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status[0]) ) {
    return Status[0];
  }

  iScsiInitiatorName = (EFI_ISCSI_INITIATOR_NAME_PROTOCOL *)ClientInterface;

  BufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;

  Status[0] = iScsiInitiatorName->Get (iScsiInitiatorName, &BufferSize, (VOID *)GetBuffer);
  if ( EFI_ERROR(Status[0]) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Get() Fail, please init iScsiInitiatorName or check the hardware",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status[0]
                   );
    return Status[0];
  }

  Status[0] = iScsiInitiatorName->Set (iScsiInitiatorName, NULL, (VOID *)SetBuffer);
  Status[1] = iScsiInitiatorName->Set (iScsiInitiatorName, &BufferSize, NULL);
  if ((Status[0] == EFI_INVALID_PARAMETER) && (Status[1] == EFI_INVALID_PARAMETER)) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestConformanceAssertionGuid005,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set - Invoke Set() with invalid parameter",
                 L"%a:%d:Status0 - %r, Status1 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status[0],
                 Status[1]
                 );

  InvalidBufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE+1;
  Status[0] = iScsiInitiatorName->Set (iScsiInitiatorName, &InvalidBufferSize, (VOID *)SetBuffer);
//  if ((Status[0] == EFI_INVALID_PARAMETER) && (InvalidBufferSize == BufferSize)) {
  if (Status[0] == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestConformanceAssertionGuid006,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set - Invoke Set() with InvalidBufferSize which exceeds the maximum allow limit",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status[0]
                 );

  return EFI_SUCCESS;
}
