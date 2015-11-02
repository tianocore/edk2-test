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

    iScsiInitiatorNameBBTestFunction.c

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec 2.0 )

Revision History

--*/

#include "SctLib.h"
#include "iScsiInitiatorNameBBTestMain.h"

EFI_STATUS
BBTestGetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_ISCSI_INITIATOR_NAME_PROTOCOL    *iScsiInitiatorName;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                BufferSize;
  CHAR8                                Buffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];
  UINTN                                InBufferSize0 = 24;
  CHAR8                                InBuffer0[24] = "iqn.2001-04.com.example";
  UINTN                                InBufferSize1 = 21;
  CHAR8                                InBuffer1[21] = "eui.02004567A425678D";
  UINTN                                OutBufferSize;
  CHAR8                                OutBuffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];
  EFI_STATUS                           Status[2];

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
  SctZeroMem ((VOID *)Buffer, BufferSize);
  Status[0] = iScsiInitiatorName->Get (iScsiInitiatorName, &BufferSize, &Buffer);

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

  Status[0] = iScsiInitiatorName->Set (iScsiInitiatorName, &InBufferSize0, &InBuffer0);
  Status[1] = iScsiInitiatorName->Set (iScsiInitiatorName, &InBufferSize1, &InBuffer1);
  if ( EFI_ERROR(Status[0]) && EFI_ERROR(Status[1]) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Set a new iScsiInitiatorName Fail",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status[0],
                   Status[1]
                   );
    return Status[0];
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if ( (Status[0] == EFI_SUCCESS) && EFI_ERROR(Status[1]) ) {
  	OutBufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;
    Status[0] = iScsiInitiatorName->Get (iScsiInitiatorName, &OutBufferSize, &OutBuffer);
    if ( (Status[0] != EFI_SUCCESS) || (OutBufferSize != InBufferSize0) || (SctCompareMem ( InBuffer0, OutBuffer, OutBufferSize) != 0) )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    Status[1] = iScsiInitiatorName->Get (iScsiInitiatorName, &OutBufferSize, &OutBuffer);
	OutBufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;
    if ( (Status[0] != EFI_SUCCESS) || (OutBufferSize != InBufferSize1) || (SctCompareMem ( InBuffer1, OutBuffer, OutBufferSize) != 0) )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestFunctionAssertionGuid001,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Get() and verify interface correctness within test case",
                 L"%a:%d:Status1 - %r, Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status[0],
                 Status[1]
                 );

  Status[0] = iScsiInitiatorName->Set (iScsiInitiatorName, &BufferSize, &Buffer);
  if ( EFI_ERROR(Status[0]) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get - Invoke Set() to restore Env Fail",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status[0]
                   );
    return Status[0];
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_ISCSI_INITIATOR_NAME_PROTOCOL    *iScsiInitiatorName;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                GetBufferSize;
  UINTN                                SetBufferSize;
  CHAR8                                GetBuffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];
  CHAR8                                SetBuffer[ISCSI_INITIATORNAME_MAXIMUM_SIZE];

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  iScsiInitiatorName = (EFI_ISCSI_INITIATOR_NAME_PROTOCOL *)ClientInterface;

  GetBufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;
  SctZeroMem ((VOID *)GetBuffer, GetBufferSize);
  Status = iScsiInitiatorName->Get (iScsiInitiatorName, &GetBufferSize, (VOID *)GetBuffer);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set - Invoke Get() and can not get initiator name",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
	return Status;
  }

  SctCopyMem ((VOID *)SetBuffer, (VOID *)GetBuffer, GetBufferSize);
  SetBufferSize = GetBufferSize;
  Status = iScsiInitiatorName->Set (iScsiInitiatorName, &SetBufferSize, (VOID *)SetBuffer);

  if ( Status == EFI_SUCCESS ){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
	GetBufferSize = ISCSI_INITIATORNAME_MAXIMUM_SIZE;
	Status = iScsiInitiatorName->Get (iScsiInitiatorName, &GetBufferSize, (VOID *)GetBuffer);
	if ( (Status != EFI_SUCCESS) || (GetBufferSize != SetBufferSize) || (SctCompareMem ( SetBuffer, GetBuffer, GetBufferSize) != 0) )
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else if ( (Status == EFI_DEVICE_ERROR) || (Status == EFI_UNSUPPORTED) ) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIScsiInitiatorNameBBTestFunctionAssertionGuid002,
                 L"EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set - Invoke Set() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
