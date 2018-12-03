/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
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

  Pkcs7BBTestMain.c

Abstract:

  Test Driver of Pkcs7 Verify Protocol

--*/

#include "SctLib.h"
#include "Pkcs7BBTestMain.h"


#define EFI_PKCS7_VERIFY_TEST_GUID \
  { 0x47889fb2, 0xd671, 0x4fab, {0xa0, 0xca, 0xdf, 0xe, 0x44, 0xdf, 0x70, 0xd6 }}

//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_SIGNATURE_LIST    *DbEntry1 = NULL;
EFI_SIGNATURE_LIST    *DbEntry2 = NULL;
EFI_SIGNATURE_LIST    *DbEntry3 = NULL;
EFI_SIGNATURE_LIST    *DbEntry4 = NULL;
EFI_SIGNATURE_LIST    *DbEntry5 = NULL;

EFI_SIGNATURE_LIST    *AllowedDb[3]   = { NULL, NULL, NULL };
EFI_SIGNATURE_LIST    *RevokedDb[3]   = { NULL, NULL, NULL };
EFI_SIGNATURE_LIST    *TimestampDb[3] = { NULL, NULL, NULL };

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_PKCS7_VERIFY_PROTOCOL_TEST_REVISION,
  EFI_PKCS7_VERIFY_TEST_GUID,
  L"Pkcs7 Verify Protocol Test",
  L"UEFI Pkcs7 Verify Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0101,
    L"VerifyBufferFunction",
    L"Function auto test for Pkcs7 Verify Protocol VerifyBuffer().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVerifyBufferFunctionTest
  },
  {
    EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0201,
    L"VerifyBufferConformance",
    L"Conformance auto test for Pkcs7 Verify Protocol VerifyBuffer().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVerifyBufferConformanceTest
  },
  0
};


EFI_STATUS
EFIAPI
InitializePkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_TIME      *RevokedTime;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  Status = EfiInitAndInstallBBTestInterface (
             &ImageHandle,
             &gBBTestProtocolField,
             gBBTestEntryField,
             UnloadPkcs7VerifyBBTest,
             &gBBTestProtocolInterface
             );

  //
  // Initialize Signature List Entry for testing.
  //
  DbEntry1 = NULL;
  DbEntry2 = NULL;
  DbEntry3 = NULL;
  DbEntry4 = NULL;
  DbEntry5 = NULL;
  RevokedTime = NULL;


  // Signature List of TestRoot Certificate
  //
  DbEntry1 = SctAllocatePool (sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert));
  DbEntry1->SignatureType       = gBlackBoxEfiCertX509Guid;
  DbEntry1->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestRootCert);
  DbEntry1->SignatureHeaderSize = 0;
  DbEntry1->SignatureSize       = 16 + sizeof (TestRootCert);
  SctCopyMem ((UINT8 *)DbEntry1 + sizeof (EFI_SIGNATURE_LIST) + 16, TestRootCert, sizeof (TestRootCert));

  //
  // Signature List of TestSub Certificate
  //
  DbEntry2 = SctAllocatePool (sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestSubCert));
  DbEntry2->SignatureType       = gBlackBoxEfiCertX509Guid;
  DbEntry2->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TestSubCert);
  DbEntry2->SignatureHeaderSize = 0;
  DbEntry2->SignatureSize       = 16 + sizeof (TestSubCert);
  SctCopyMem ((UINT8 *)DbEntry2 + sizeof (EFI_SIGNATURE_LIST) + 16, TestSubCert, sizeof (TestSubCert));

  //
  // Signature List of TSRoot Certificate
  //
  DbEntry3 = SctAllocatePool (sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TSRootCert));
  DbEntry3->SignatureType       = gBlackBoxEfiCertX509Guid;
  DbEntry3->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + sizeof (TSRootCert);
  DbEntry3->SignatureHeaderSize = 0;
  DbEntry3->SignatureSize       = 16 + sizeof (TSRootCert);
  SctCopyMem ((UINT8 *)DbEntry3 + sizeof (EFI_SIGNATURE_LIST) + 16, TSRootCert, sizeof (TSRootCert));

  //
  // Signature List of Binary Data Hash for Revocation Checking
  //
  DbEntry4 = SctAllocatePool (sizeof (EFI_SIGNATURE_LIST) + 16 + 32);
  DbEntry4->SignatureType       = gBlackBoxEfiCertSha256Guid;
  DbEntry4->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + 32;
  DbEntry4->SignatureHeaderSize = 0;
  DbEntry4->SignatureSize       = 16 + 32;
  SctCopyMem ((UINT8 *)DbEntry4 + sizeof (EFI_SIGNATURE_LIST) + 16, TestBinHash, 32);

  //
  // Signature List of Certificate Hash for Timestamp Signature Checking
  //
  DbEntry5 = SctAllocateZeroPool (sizeof (EFI_SIGNATURE_LIST) + 16 + 48);
  DbEntry5->SignatureType       = gBlackBoxEfiCertX509Sha256Guid;
  DbEntry5->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + 48;
  DbEntry5->SignatureHeaderSize = 0;
  DbEntry5->SignatureSize       = 16 + 48;
  SctCopyMem ((UINT8 *)DbEntry5 + sizeof (EFI_SIGNATURE_LIST) + 16, TestSubHash, 32);
  RevokedTime = (EFI_TIME *) ((UINT8 *)DbEntry5 + sizeof (EFI_SIGNATURE_LIST) + 16 + 32);
  RevokedTime->Year  = 2015;
  RevokedTime->Month = 8;
  RevokedTime->Day   = 20;

  return Status;
}


EFI_STATUS
EFIAPI
UnloadPkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  if (DbEntry1 != NULL) {
    SctFreePool (DbEntry1);
  }
  if (DbEntry2 != NULL) {
    SctFreePool (DbEntry2);
  }
  if (DbEntry3 != NULL) {
    SctFreePool (DbEntry3);
  }
  if (DbEntry4 != NULL) {
    SctFreePool (DbEntry4);
  }
  if (DbEntry5 != NULL) {
    SctFreePool (DbEntry5);
  }

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
