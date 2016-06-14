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
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
