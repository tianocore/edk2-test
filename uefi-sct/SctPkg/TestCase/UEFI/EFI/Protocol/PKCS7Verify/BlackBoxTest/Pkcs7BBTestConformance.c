/** @file

  Copyright 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
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
EFIAPI
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

EFI_STATUS
EFIAPI
BBTestVerifySignatureConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_PKCS7_VERIFY_PROTOCOL             *Pkcs7Verify;
  EFI_TEST_ASSERTION                    AssertionType;

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

  //
  // Checkpoint 1 - EFI_INVALID_PARAMETER
  //

  // Signature is NULL
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, NULL, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, NULL, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid011,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_INVALID_PARAMETER when Signature is NULL.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // SignatureSize is 0
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, 0, TestInHash, sizeof(TestInHash), AllowedDb, NULL, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid011,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_INVALID_PARAMETER when SignatureSize is 0.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // InHash is NULL.
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), NULL, sizeof(TestInHash), AllowedDb, NULL, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid011,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_INVALID_PARAMETER when InHash is NULL.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // InHashSize is 0.
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, 0, AllowedDb, NULL, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid011,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_INVALID_PARAMETER when InHashSize is 0.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // AllowedDb is NULL
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), NULL, NULL, NULL);
  if (Status == EFI_INVALID_PARAMETER)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid011,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_INVALID_PARAMETER when AllowedDb is NULL.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 2 - EFI_UNSUPPORTED
  //    NOTE: It's hard to distinguish unsupported Signature or security-violated signature for VerifySignature() interface
  //          since we don't need to extra the attached content from input signature as VerifyBuffer() interface.
  //          So it's OK to bypass this check or just check the EFI_SECURITY_VIOLATION result.
  //

  //
  // Modify the Data in the P7TestSignature to make it the invalid one
  //
  P7TestSignature[0] = 0x40;

  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, NULL, NULL);

  if ((Status == EFI_UNSUPPORTED) || (Status == EFI_SECURITY_VIOLATION))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid012,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_UNSUPPORTED when Signature buffer was not clrrectly formatted.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Restore the P7TestSignature to the valid one
  //
  P7TestSignature[0] = 0x30;

  //
  // Checkpoint 4 - EFI_COMPROMISED_DATA
  //     NOTE: P7Verify leverage OpenSSL for pkcs7 signature verification
  //           It's hard for EFI_COMPROMISED_DATA check. Just use EFI_SECURITY_VIOLATION for wrong InHash input.
  //

  //
  // Modify the Data in the InHash to make it the invalid one
  //
  TestInHash[0] = 0x3E;
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid013,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SECURITY_VIOLATION when hash differs from signed hash.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Restore the InHash
  //
  TestInHash[0] = 0x3D;

  //
  // Input the invalid Hashsize
  //
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash)- 2, AllowedDb, RevokedDb, TimestampDb);
  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid013,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SECURITY_VIOLATION when encrypted hash is different size.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Checkpoint 5 - EFI_SECURITY_VIOLATION
  //

  //
  // The SignedData buffer was correctly formatted but signer was in RevokedDb
  //
  AllowedDb[0] = DbEntry1;
  RevokedDb[0] = DbEntry1;

  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);

  AllowedDb[0] = NULL;
  RevokedDb[0] = NULL;

  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid014,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SECURITY_VIOLATION when the SignedData buffer was correctly formatted but signer was in RevokedDb.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // The SignedData buffer was correctly formatted but signer was not in AllowedDb
  //
  AllowedDb[0] = NULL;

  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);

  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid014,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SECURITY_VIOLATION when the SignedData buffer was correctly formatted but signer was not in AllowedDb.",
                 L"%a:%d: Status - %r\n",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Matching content hash found in the RevokedDb
  //
  SctCopyMem ((UINT8 *)DbEntry4 + sizeof (EFI_SIGNATURE_LIST) + sizeof(EFI_GUID), TestInHash, sizeof(TestInHash));
  RevokedDb[0] = DbEntry4;
  AllowedDb[0] = DbEntry1;
  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);

  RevokedDb[0] = NULL;
  AllowedDb[0] = NULL;

  if (Status == EFI_SECURITY_VIOLATION)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestConformanceAssertionGuid014,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SECURITY_VIOLATION when matching content hash found in the RevokedDb.",
                 L"%a:%d: Status - %r\n",
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
