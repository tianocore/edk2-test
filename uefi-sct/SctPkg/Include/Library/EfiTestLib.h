/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EfiTestLib.h

Abstract:

  EFI common test library.

--*/

#ifndef _EFI_TEST_LIB_H_
#define _EFI_TEST_LIB_H_

//
// Includes
//
#include "EfiTest.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_TEST_PROTOCOL_DEFINITION(StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(BbTest)
#include EFI_TEST_PROTOCOL_DEFINITION(WbTest)


//
// Structure definitions
//

//
// These test field structures are created based on Black-Box test protocol
// and White-Box test protocol. Using below structures and interfaces to
// generate the test information will be a little easier than using the test
// protocols directly.
//

//
// Black-box test entry field
//
typedef struct {
  EFI_GUID            EntryId;
  CHAR16              *Name;
  CHAR16              *Description;
  EFI_TEST_LEVEL      TestLevelSupportMap;
  EFI_GUID            *SupportProtocols;
  EFI_TEST_ATTRIBUTE  CaseAttribute;
  EFI_BB_ENTRY_POINT  EntryPoint;
} EFI_BB_TEST_ENTRY_FIELD;

//
// Black-box test protocol field
//
typedef struct {
  UINT64              TestRevision;
  EFI_GUID            CategoryGuid;
  CHAR16              *Name;
  CHAR16              *Description;
} EFI_BB_TEST_PROTOCOL_FIELD;

//
// White-box test entry field
//
typedef struct {
  EFI_GUID            EntryId;
  CHAR16              *Name;
  CHAR16              *Description;
  EFI_TEST_LEVEL      TestLevelSupportMap;
  EFI_GUID            *SupportProtocols;
  EFI_TEST_ATTRIBUTE  CaseAttribute;
  EFI_WB_ENTRY_POINT  EntryPoint;
} EFI_WB_TEST_ENTRY_FIELD;

//
// White-box test protocol field
//
typedef struct {
  UINT64              TestRevision;
  EFI_GUID            CategoryGuid;
  CHAR16              *Name;
  CHAR16              *Description;
} EFI_WB_TEST_PROTOCOL_FIELD;

//
// Functions declaration
//

EFI_STATUS
EFIAPI
EfiInitializeTestLib (
  IN  EFI_HANDLE                  ImageHandle,
  IN  EFI_SYSTEM_TABLE            *SystemTable
  )
/*++

Routine Description:

  Intialize test library if it has not yet been initialized.

Arguments:

  ImageHandle   - The firmware allocated handle for the EFI image.

  SystemTable   - A pointer to the EFI System Table.

Returns:

  EFI_SUCCESS is always returned.

--*/
;

EFI_STATUS
EFIAPI
EfiInitAndInstallBBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_BB_TEST_PROTOCOL_FIELD  *BBTestProtocolField,
  IN  EFI_BB_TEST_ENTRY_FIELD     *BBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_BB_TEST_PROTOCOL        **BBTestProtocolInterface
  )
/*++

Routine Description:

  Initialize a black-box test protocol interface from the protocol field and
  entry field, and then install the black-box test protocol on the handle.

Arguments:

  Handle                  - The driver image handle, and the protocol interface
                            is installed on this handle.

  BBTestProtocolField     - The black-box test protocol field to provide the
                            test info for the whole black-box test.

  BBTestEntryField        - An array of black-box test entry field to provide
                            the test info for each test entry point.

  UnloadFunction          - The unload function pointer for the test image.

  BBTestProtocolInterface - Pointer to the black-box test protocol interface.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

EFI_STATUS
EFIAPI
EfiInitAndInstallIHVBBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_BB_TEST_PROTOCOL_FIELD  *BBTestProtocolField,
  IN  EFI_BB_TEST_ENTRY_FIELD     *BBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_BB_TEST_PROTOCOL        **BBTestProtocolInterface
  );

EFI_STATUS
EFIAPI
EfiUninstallAndFreeBBTestInterface (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_BB_TEST_PROTOCOL        *BBTestProtocolInterface
  )
/*++

Routine Description:

  Uninstall the black-box test protocol from the handle, and then free the
  black-box test protocol interface.

Arguments:

  Handle                  - The handle on which the protocol interface was
                            installed.

  BBTestProtocolInterface - Pointer to the black-box test protocol interface.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

EFI_STATUS
EFIAPI
EfiUninstallAndFreeIHVBBTestInterface (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_BB_TEST_PROTOCOL        *BBTestProtocolInterface
  );

EFI_STATUS
EFIAPI
EfiInitAndInstallWBTestInterface (
  IN  EFI_HANDLE                  *Handle,
  IN  EFI_WB_TEST_PROTOCOL_FIELD  *WBTestProtocolField,
  IN  EFI_WB_TEST_ENTRY_FIELD     *WBTestEntryField,
  IN  EFI_IMAGE_UNLOAD            UnloadFunction,
  OUT EFI_WB_TEST_PROTOCOL        **WBTestProtocolInterface
  )
/*++

Routine Description:

  Initialize a white-box test protocol interface from the protocol field and
  entry field, and then install the white-box test protocol on the handle.

Arguments:

  Handle                  - The driver image handle, and the protocol interface
                            is installed on this handle.

  WBTestProtocolField     - The white-box test protocol field to provide the
                            test info for the whole black-box test.

  WBTestEntryField        - An array of white-box test entry field to provide
                            the test info for each test entry point.

  UnloadFunction          - The unload function pointer for the test image.

  WBTestProtocolInterface - Pointer to the white-box test protocol interface.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

EFI_STATUS
EFIAPI
EfiUninstallAndFreeWBTestInterface (
  IN EFI_HANDLE                   Handle,
  IN EFI_WB_TEST_PROTOCOL         *WBTestProtocolInterface
  )
/*++

Routine Description:

  Uninstall the white-box test protocol from the handle, and then free the
  black-box test protocol interface.

Arguments:

  Handle                  - The handle on which the protocol interface was
                            installed.

  WBTestProtocolInterface - Pointer to the white-box test protocol interface.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

BOOLEAN
CheckBBTestCanRunAndRecordAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN CHAR16                              *AssertionString,
  IN CHAR8                               *FILE,
  IN UINT32                              LINE
  )
/*++

Routine Description:

  Check whether the black-box test case can run, because some UEFI test case
  can not run on EFI.

Arguments:

  StandardLib             - The pointer to the standard test library protocol.
  AssertionString         - The string to be print if test case can not run.
  FILE                    - The name of the test case's source file
  LINE                    - The line number in the test case's source file

Returns:

  TRUE   if the test case can run
  FALSE  if the test case can not run

--*/
;

//
// GUIDs for special usage
//

//
// Generic Failure GUID is designed for the test environment issues or
// the walking-on issues. It will be recorded in the log files, but will not be
// summarized in the test report by the EFI SCT Suite.
//
#define TEST_GENERIC_FAILURE_GUID         \
  { 0x6a8caa83, 0xb9da, 0x46c7, { 0x98, 0xf6, 0xd4, 0x96, 0x9d, 0xab, 0xda, 0xa0 }}

extern EFI_GUID gTestGenericFailureGuid;

//
// Dummy GUID is designed as a temporary GUID that will be replaced with a
// formal GUID later. It will be easy to use this GUID in prototype phase,
// and then use a tool to do the replacement.
//
#define TEST_DUMMY_GUID                   \
  { 0xece4bdd5, 0x8177, 0x448b, { 0x82, 0x03, 0x2d, 0x11, 0x0c, 0x1c, 0x20, 0xb8 }}

extern EFI_GUID gTestDummyGuid;

//
// Global variables for the services tables
//

extern EFI_SYSTEM_TABLE          *gtST;
extern EFI_BOOT_SERVICES         *gtBS;
extern EFI_RUNTIME_SERVICES      *gtRT;
extern EFI_DXE_SERVICES          *gtDS;

#endif
