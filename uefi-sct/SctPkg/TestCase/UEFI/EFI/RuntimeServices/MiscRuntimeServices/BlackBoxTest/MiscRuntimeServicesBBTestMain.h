/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MiscRuntimeServicesBBTestMain.h

Abstract:

  BB test header file of Miscellaneous Runtime Services

--*/


#ifndef _MISC_RUNTIME_SERVICES
#define _MISC_RUNTIME_SERVICES

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"
#include <Protocol/Capsule.h>

#define CAPSULE_FLAGS_INITIATE_RESET   0x00040000 

typedef struct _RESET_DATA {
  UINTN           Step;
  UINTN           TplIndex;
  UINT32          RepeatTimes;
} RESET_DATA;

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)

#define MISC_RUNTIME_SERVICES_TEST_REVISION   0x00010000

#define MISC_RUNTIME_SERVICES_TEST_GUID       \
  { 0x65AB91D6, 0xAB78, 0x4a5d, {0xBA, 0x80, 0x1A, 0xBD, 0x23, 0x58, 0xC3, 0xA4 }}

#define TPL_ARRAY_SIZE 3

#ifndef EFI_CAPSULE_GUID
#define EFI_CAPSULE_GUID \
  { 0x3B6686BD, 0x0D76, 0x4030, {0xB7, 0x0E, 0xB5, 0x51, 0x9E, 0x2F, 0xC5, 0xA0 }}
#endif

extern EFI_TPL TplArray[TPL_ARRAY_SIZE];

extern EFI_GUID  mEfiCapsuleHeaderGuid;

//
// Prototypes of Interface Test
//

//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestResetSystemInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestResetSystemManualTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Combination Test
//

//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestResetSystemStressTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestResetSystemManualStressTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestQueryCapsuleCapabilitiesTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestUpdateCapsuleConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestQueryCapsuleCapabilitiesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//


//
// Entry GUIDs
//

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_INTERFACE_GUID \
  { 0x1dbeb615, 0x9504, 0x4e2f, {0xba, 0xfc, 0xb3, 0xc6, 0xb2, 0xde, 0xbc, 0x7b }}

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_GUID \
  { 0x3ae30328, 0x85ef, 0x46af, {0x9a, 0xb7, 0x3c, 0x9e, 0x9a, 0x1a, 0x86, 0x10 }}

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_STRESS_TEST_GUID \
  { 0x5cc0a7c, 0x62f6, 0x4971, {0xbe, 0x33, 0xec, 0x8a, 0xbd, 0x48, 0xf, 0xdd }}

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_STRESS_TEST_GUID \
  { 0x3966be0c, 0xf04b, 0x465f, {0xaa, 0x46, 0x22, 0x93, 0xd2, 0xdf, 0xd4, 0x6f }}


#define MISC_RUNTIME_SERVICES_QUERYCAPSULEBILITIES_INTERFACE_TEST_GUID \
  { 0x72087efe, 0xf36c, 0x4e46, {0x8c, 0xcd, 0x5e, 0x6, 0xa7, 0x48, 0xbe, 0xf1 }}

#define MISC_RUNTIME_SERVICES_QUERYCAPSULEBILITIES_CONFORMANCE_TEST_GUID \
  { 0x2411c48b, 0x74d1, 0x4e2f, {0x94, 0x2b, 0xc3, 0x1e, 0x54, 0xb5, 0xe1, 0xb4 }}

#define MISC_RUNTIME_SERVICES_UPDATECAPSULE_COFORMANCE_TEST_GUID \
  { 0x7227cfac, 0xca96, 0x4680, {0x93, 0x14, 0xe3, 0xfb, 0xc6, 0xa, 0x2a, 0x61 }}

#endif
