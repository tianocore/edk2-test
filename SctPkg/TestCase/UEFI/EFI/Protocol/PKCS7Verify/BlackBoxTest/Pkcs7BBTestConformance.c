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

    Pkcs7BBTestConformance.c

Abstract:

    for EFI Driver Pkcs7 Verify Protocol's Conformance Test

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
BBTestVerifyBufferConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status, Status1, Status2, Status3, Status4, Status5, Status6, Status7, Status8;
  EFI_PKCS7_VERIFY_PROTOCOL             *Pkcs7Verify;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT8                                 Content[10];

  Pkcs7Verify = (EFI_PKCS7_VERIFY_PROTOCOL*)ClientInterface;
  if (Pkcs7Verify == NULL)
  	return EFI_UNSUPPORTED;

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

  AllowedDb[0] = DbEntry1;

  // SignedData is NULL
  Status1 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, NULL, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  Status2 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, NULL, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);

  // SignedDataSize is 0
  Status3 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, 0, NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  Status4 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, 0, TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);

  // Content is not NULL and ContentSize is NULL.
  Status5 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, Content, NULL);
  Status6 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, Content, NULL);

  // AllowedDb is NULL
  AllowedDb[0] = NULL;
  Status7 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, NULL, RevokedDb, TimestampDb, NULL, 0);
  Status8 = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), NULL, RevokedDb, TimestampDb, NULL, 0);
  
  
  if ((Status1 == EFI_INVALID_PARAMETER) && (Status2 == EFI_INVALID_PARAMETER) && (Status3 == EFI_INVALID_PARAMETER) && (Status4 == EFI_INVALID_PARAMETER) &&
  	(Status5 == EFI_INVALID_PARAMETER) && (Status6 == EFI_INVALID_PARAMETER) && (Status7 == EFI_INVALID_PARAMETER) && (Status8 == EFI_INVALID_PARAMETER))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid001 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_INVALID_PARAMETER.",
                 L"%a:%d: Status1 - %r, Status2 - %r, Status3 - %r, Status4 - %r, Status5 - %r, Status6 - %r, Status7 - %r, Status8 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2,
                 Status3,
                 Status4,
                 Status5,
                 Status6,
                 Status7,
                 Status8
                 );

  //
  // Conformance test with EmbeddedData
  //
  
  // SignedData buffer is not correctly formatted for processing by the function.
  P7Embedded[0] = 0x40;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  P7Embedded[0] = 0x30;
  
  if (Status == EFI_UNSUPPORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid002 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_UNSUPPORTED when SignedData buffer is not correctly formatted for processing.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Unsupported or invalid format in AllowedDb
  DbEntry1->SignatureListSize = 16;
  AllowedDb[0] = DbEntry1;
  
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  AllowedDb[0] = NULL;
  DbEntry1->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert);;

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid003 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Unsupported or invalid format in RevokedDb
  DbEntry1->SignatureListSize = 16;
  RevokedDb[0] = DbEntry1;
  
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  RevokedDb[0] = NULL;
  DbEntry1->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert);

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid004 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in RevokedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
  // Unsupported or invalid format in TimeStampDb
  DbEntry3->SignatureListSize = 16;
  RevokedDb[0]   = DbEntry1;
  AllowedDb[0]   = DbEntry1;
  TimestampDb[0] = DbEntry3;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  RevokedDb[0]   = NULL;
  AllowedDb[0]   = NULL;
  TimestampDb[0] = NULL;
  
  DbEntry3->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TSRootCert);

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid005 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in TimeStampDb.",
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


  // Buffer is correctly formatted but signer is not in AllowedDb.
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid006 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but signer is not in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  // Buffer is correctly formatted but signer is in RevokedDb.
  AllowedDb[0] = DbEntry2;
  RevokedDb[0] = DbEntry2;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid007 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but signer is in RevokedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Buffer is correctly formatted but the content hash is in RevokedDb.
  AllowedDb[0] = DbEntry2;
  RevokedDb[0] = DbEntry4;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid008 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but the content hash is in RevokedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  


  // Signed data embedded in SignedData but InData is not NULL
  AllowedDb[0] = DbEntry1;
  RevokedDb[0] = NULL;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Embedded, sizeof(P7Embedded), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_UNSUPPORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid009 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_UNSUPPORTED when Signed data embedded in SignedData but InData is not NULL.",
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
  // Conformance test with DetachedData
  //

  // SignedData buffer is not correctly formatted for processing by the function.
  P7Detached[0] = 0x40;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  P7Detached[0] = 0x30;
  
  if (Status == EFI_UNSUPPORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid002 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_UNSUPPORTED when SignedData buffer is not correctly formatted for processing.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Content not found because InData is NULL and no content embedded in SignedData.
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), NULL, 0, AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_NOT_FOUND)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid010 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_NOT_FOUND when InData is NULL and no content embedded in SignedData.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );    

  // Unsupported or invalid format in AllowedDb
  DbEntry1->SignatureListSize = 16;
  AllowedDb[0] = DbEntry1;
  
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  AllowedDb[0] = NULL;
  DbEntry1->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert);;

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid003 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  // Unsupported or invalid format in RevokedDb
  DbEntry1->SignatureListSize = 16;
  RevokedDb[0] = DbEntry1;
  
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  RevokedDb[0] = NULL;  
  DbEntry1->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert);

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid004 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in RevokedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  // Unsupported or invalid format in TimeStampDb
  DbEntry3->SignatureListSize = 16;
  RevokedDb[0]   = DbEntry1;
  AllowedDb[0]   = DbEntry1;
  TimestampDb[0] = DbEntry3;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  RevokedDb[0]   = NULL;
  AllowedDb[0]   = NULL;
  TimestampDb[0] = NULL;
  
  DbEntry5->SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TSRootCert);

  if (Status == EFI_ABORTED)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid005 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_ABORTED when invalid format in TimeStampDb.",
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
  
  // Buffer is correctly formatted but signer is not in AllowedDb.
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid006 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but signer is not in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  // Buffer is correctly formatted but signer is in RevokedDb.
  AllowedDb[0] = DbEntry2;
  RevokedDb[0] = DbEntry2;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid007 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but signer is in RevokedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Buffer is correctly formatted but the content hash is in RevokedDb.
  AllowedDb[0] = DbEntry2;
  RevokedDb[0] = DbEntry4;
  Status = Pkcs7Verify->VerifyBuffer (Pkcs7Verify, P7Detached, sizeof(P7Detached), TestBin, sizeof(TestBin), AllowedDb, RevokedDb, TimestampDb, NULL, 0);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid008 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SECURITY_VIOLATION when Buffer is correctly formatted but the content hash is in RevokedDb.",
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


