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
#if 0  
  {
    EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0102,
    L"VerifySignatureFunction",
    L"Function auto test for Pkcs7 Verify  Protocol VerifySignature().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVerifySignatureFunctionTest
  },
#endif  
  {
    EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0201,
    L"VerifyBufferConformance",
    L"Conformance auto test for Pkcs7 Verify Protocol VerifyBuffer().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVerifyBufferConformanceTest
  },
#if 0   
  {
    EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0202,
    L"VerifySignatureConformance",
    L"Conformance auto test for Pkcs7 Verify Protocol VerifySignature().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVerifySignatureConformanceTest
  },
#endif  
  0
};


EFI_STATUS
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
  DbEntry5 = SctAllocatePool (sizeof (EFI_SIGNATURE_LIST) + 16 + 48);
  DbEntry5->SignatureType       = gBlackBoxEfiCertX509Sha256Guid;
  DbEntry5->SignatureListSize   = sizeof (EFI_SIGNATURE_LIST) + 16 + 48;
  DbEntry5->SignatureHeaderSize = 0;
  DbEntry5->SignatureSize       = 16 + 48;
  SctCopyMem ((UINT8 *)DbEntry5 + sizeof (EFI_SIGNATURE_LIST) + 16, TestSubHash, 32);
  RevokedTime = (EFI_TIME *) ((UINT8 *)DbEntry5 + sizeof (EFI_SIGNATURE_LIST) + 16 + 32);
  RevokedTime->Year  = 2015;
  RevokedTime->Month = 8;
  RevokedTime->Day   = 19;  

  return Status;
}


EFI_STATUS
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


