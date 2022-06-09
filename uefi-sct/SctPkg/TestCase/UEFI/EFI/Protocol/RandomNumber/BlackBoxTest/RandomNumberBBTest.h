/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    RandomNumberBBTest.h

Abstract:
    head file of test driver of EFI RANDOM NUMBER Protocol Test

--*/

#ifndef _RANDOM_NUMBER_TEST_H
#define _RANDOM_NUMBER_TEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/RandomNumber.h>
#include "Guid.h"

#define EFI_RANDOM_NUMBER_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x39ff9c71, 0x4b41, 0x4e5b, {0xae, 0xd7, 0x87, 0xc7, 0x94, 0x18, 0x7d, 0x66} }

#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0xdc5b2884, 0xedfb, 0x4078, {0xa2, 0x88, 0x4d, 0xfd, 0xa8, 0x49, 0xa0, 0x8d} }


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0x861f4a3b, 0x8125, 0x4a5a, {0x99, 0xcc, 0xda, 0x77, 0x79, 0xc2, 0xb0, 0x20} }

#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0xddbbe5ab, 0x206e, 0x4f35, {0x95, 0x56, 0x18, 0x6d, 0xa8, 0x7c, 0x2a, 0x86} }



//
// functions declaration
//
EFI_STATUS
EFIAPI
InitializeBBTestRandomNumber (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestRandomNumberUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
BBTestGetInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetRNGFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
EFIAPI
BBTestGetRNGFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
EFIAPI
BBTestGetRNGFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_RNG_PROTOCOL                     *RandomNumber
  );


EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetRNGConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
EFIAPI
BBTestGetRNGConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
EFIAPI
BBTestGetRNGConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


#endif
