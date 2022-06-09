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
EFIAPI
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
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Function test with EmbeddedData
  //

  // Content signature was verified against hash of content, the signer certificate was not found in RevokedDb, and was found in AllowedDb.
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
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when Content signature was verified against hash of content, the signer's certificate was not found in RevokedDb, and was found in AllowedDb.",
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
  // Content signature was verified against hash of content, the signer's certificate was not found in RevokedDb, and was found in AllowedDb.
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
                 L"PKCS7_VERIFY_PROTOCOL.VerifyBuffer - VerifyBuffer() should returns EFI_SUCCESS when Content signature was verified against hash of content, the signer's certificate was not found in RevokedDb, and was found in AllowedDb.",
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


EFI_STATUS
EFIAPI
BBTestVerifySignatureFunctionTest (
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

  //
  // Signed hash was verified against caller-provided hash of content, the signer's certificate was not found in RevokedDb, and was found in AllowedDb
  //
  AllowedDb[0] = DbEntry1;

  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);

  if (Status == EFI_SUCCESS)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid005 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SUCCESS when Signed hash was verified against caller-provided hash of content, the signer's certificate was not found in RevokedDb, and was found in AllowedDb.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // signer is found in both AllowedDb and RevokedDb, the signing was allowed by reference to TimeStampDb, and no hash matching content hash was found in RevokedDb
  AllowedDb[0]   = DbEntry1;
  RevokedDb[0]   = DbEntry5;
  TimestampDb[0] = DbEntry3;

  Status = Pkcs7Verify->VerifySignature (Pkcs7Verify, P7TestSignature, sizeof(P7TestSignature), TestInHash, sizeof(TestInHash), AllowedDb, RevokedDb, TimestampDb);

  if (Status == EFI_SUCCESS)
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPkcs7BBTestFunctionAssertionGuid006 ,
                 L"PKCS7_VERIFY_PROTOCOL.VerifySignature - VerifySignature() should returns EFI_SUCCESS when signer is found in both AllowedDb and RevokedDb, the signing was allowed by reference to TimeStampDb, and no hash matching content hash was found in RevokedDb.",
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
