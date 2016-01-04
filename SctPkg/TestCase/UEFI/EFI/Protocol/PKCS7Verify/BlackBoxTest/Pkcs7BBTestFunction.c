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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    Pkcs7BBTestFunction.c

Abstract:

    for EFI Driver Pkcs7 Verify Protocol's Function Test

--*/

#include "Pkcs7BBTestMain.h"

extern EFI_SIGNATURE_LIST    *DbEntry1;
extern EFI_SIGNATURE_LIST    *DbEntry2;
extern EFI_SIGNATURE_LIST    *DbEntry3;
extern EFI_SIGNATURE_LIST    *DbEntry4;
extern EFI_SIGNATURE_LIST    *DbEntry5;

extern EFI_SIGNATURE_LIST    *AllowedDb[3];
extern EFI_SIGNATURE_LIST    *RevokedDb[3];
extern EFI_SIGNATURE_LIST    *TimestampDb[3];

EFI_STATUS
BBTestVerifyBufferFunctionTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PKCS7_VERIFY_PROTOCOL             *Pkcs7Verify = NULL;
  VOID                                  *Content;
  UINTN                                 ContentSize;

  Pkcs7Verify = (EFI_PKCS7_VERIFY_PROTOCOL*)ClientInterface;
  if (Pkcs7Verify == NULL)
  	return EFI_UNSUPPORTED;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Function test with EmbeddedData
  //

  // Content signature was verified against hash of content, the signer¡¯certificate was not found in RevokedDb, and was found in AllowedDb.
  AllowedDb[0] = DbEntry2;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);

  if (Status == EFI_SUCCESS)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid001 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when Content signature was verified against hash of content, the signer¡¯certificate was not found in RevokedDb, and was found in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Content     = &Status; //The trick method to give Content a value.
  ContentSize = 0;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, Content, &ContentSize);

  if (Status == EFI_BUFFER_TOO_SMALL)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid002 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_BUFFER_TOO_SMALL when the size of buffer indicated by ContentSize is too small to hold the content. ContentSize updated to required size.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  


  Content = SctAllocateZeroPool(ContentSize);
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, Content, &ContentSize);

  AssertionType = EFI_TEST_ASSERTION_FAILED;
  
  if ((Status == EFI_SUCCESS) && (ContentSize == sizeof(TestBin)) && (!SctCompareMem(TestBin, Content, ContentSize)))
    AssertionType = EFI_TEST_ASSERTION_PASSED;

  SctFreePool (Content);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid003,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when the size of buffer indicated by ContentSize is big enough to hold the content, and retrive the correct content.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  // Content signature was verified against hash of content, signer is found in both AllowedDb and RevokedDb, the signing was allowed by reference to TimeStampDb.
  AllowedDb[0]   = DbEntry2;
  RevokedDb[0]   = DbEntry5;
  TimestampDb[0] = DbEntry3;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);

  if (Status == EFI_SUCCESS)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid004 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when Content signature was verified against hash of content, signer is found in both AllowedDb and RevokedDb, the signing was allowed by reference to TimeStampDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Clean the Data in all Dbs
  //
  AllowedDb[0]   = NULL;
  RevokedDb[0]   = NULL;
  TimestampDb[0] = NULL;

  //
  // Function test with DetachedData
  //  
  // Content signature was verified against hash of content, the signer¡¯certificate was not found in RevokedDb, and was found in AllowedDb.
  AllowedDb[0] = DbEntry2;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);

  if (Status == EFI_SUCCESS)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid001 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when Content signature was verified against hash of content, the signer¡¯certificate was not found in RevokedDb, and was found in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Content     = &Status; //The trick method to give Content a value.
  ContentSize = 0;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, Content, &ContentSize);

  if (Status == EFI_BUFFER_TOO_SMALL)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid002 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_BUFFER_TOO_SMALL when the size of buffer indicated by ContentSize is too small to hold the content. ContentSize updated to required size.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  


  Content = SctAllocateZeroPool(ContentSize);
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, Content, &ContentSize);

  AssertionType = EFI_TEST_ASSERTION_FAILED;
  
  if ((Status == EFI_SUCCESS) && (ContentSize == sizeof(TestBin)) && (!SctCompareMem(TestBin, Content, ContentSize)))
    AssertionType = EFI_TEST_ASSERTION_PASSED;

  SctFreePool (Content);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid003 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when the size of buffer indicated by ContentSize is big enough to hold the content, and retrive the correct content.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  


  //
  // Clean the Data in all Dbs
  //
  AllowedDb[0]   = NULL;
  RevokedDb[0]   = NULL;
  TimestampDb[0] = NULL;

  return EFI_SUCCESS;
}

