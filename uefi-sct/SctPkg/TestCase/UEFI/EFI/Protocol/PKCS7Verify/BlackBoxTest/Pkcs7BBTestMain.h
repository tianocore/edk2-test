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

  Pkcs7BBTestMain.h

Abstract:

  Test Driver of Pkcs7 Verify Protocol header file

--*/

#ifndef _PKCS7_BB_TEST_MAIN
#define _PKCS7_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/Pkcs7Verify.h>
#include "Guid.h"


#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x5c6a8139, 0xad48, 0x4d52, {0x86, 0x37, 0x6, 0x9d, 0xf6, 0xad, 0x81, 0x5e }}

#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x413c4823, 0x263a, 0x417d, {0xa3, 0xd7, 0x14, 0x79, 0xf9, 0x2b, 0xf1, 0xb4 }}


//
// Entry GUIDs for Conf Test
//
#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x562af518, 0xd04e, 0x435e, {0xa8, 0x9f, 0x79, 0xbb, 0x6f, 0x48, 0x16, 0x9a }}

#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xaf5e33d1, 0x3e08, 0x451a, {0xb1, 0x92, 0xe7, 0xb9, 0x91, 0x67, 0x83, 0xae }}


extern UINT8 TestRootCert[781];
extern UINT8 TestSubCert[780];
extern UINT8 TestSubCertHash[32];
extern UINT8 TSRootCert[1181];

extern UINT8 TestBin[64];
extern UINT8 TestBinHash[32];
extern UINT8 TestInHash[32];

extern UINT8 P7Embedded[3365];
extern UINT8 P7Detached[1163];
extern UINT8 P7TestSignature[3480];

//
//
//
EFI_STATUS
EFIAPI
InitializePkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadPkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle
  );

//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestVerifyBufferConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestVerifySignatureConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestVerifyBufferFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestVerifySignatureFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
