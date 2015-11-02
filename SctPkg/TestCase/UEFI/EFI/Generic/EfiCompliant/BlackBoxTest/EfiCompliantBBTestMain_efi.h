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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EfiCompliantBbTestMain.h

Abstract:

  EFI Compliant Black-Box Test.

--*/

#ifndef _EFI_COMPLIANT_BB_TEST_MAIN_H_
#define _EFI_COMPLIANT_BB_TEST_MAIN_H_

//
// Includes
//

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "Guid_efi.h"

#include EFI_TEST_PROTOCOL_DEFINITION (BbTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

//
// Definitions
//

#define EFI_COMPLIANT_BB_TEST_REVISION      0x00010001

// {4796995E-528F-4e7e-8BAF-FA4A931D2502}
#define EFI_COMPLIANT_BB_TEST_GUID          \
  { 0x4796995e, 0x528f, 0x4e7e, 0x8b, 0xaf, 0xfa, 0x4a, 0x93, 0x1d, 0x25, 0x02 }

#define EFI_COMPLIANT_BB_TEST_INI_PATH      L"Dependency\\EfiCompliantBBTest"
#define EFI_COMPLIANT_BB_TEST_INI_FILE      L"EfiCompliant.Ini"

//
// Prototype of conformance tests
//

EFI_STATUS
RequiredElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

EFI_STATUS
PlatformSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

EFI_STATUS
DriverSpecificElementsBbTest (
  IN EFI_BB_TEST_PROTOCOL         *This,
  IN VOID                         *ClientInterface,
  IN EFI_TEST_LEVEL               TestLevel,
  IN EFI_HANDLE                   SupportHandle
  );

//
// Support services
//

EFI_STATUS
OpenIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  CHAR16                              *IniPathName,
  IN  CHAR16                              *IniFileName,
  OUT EFI_INI_FILE_HANDLE                 *IniFile
  );

EFI_STATUS
CloseIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_INI_FILE_HANDLE                 IniFile
  );

//
// GUIDs for the test entry points
//

// {117C9ABC-489D-4504-ACDB-12AACE8F505B}
#define REQUIRED_ELEMENTS_BB_TEST_GUID                \
  { 0x117c9abc, 0x489d, 0x4504, 0xac, 0xdb, 0x12, 0xaa, 0xce, 0x8f, 0x50, 0x5b }

// {A0A8BED3-3D6F-4ad8-907A-84D52EE1543B}
#define PLATFORM_SPECIFIC_ELEMENTS_BB_TEST_GUID       \
  { 0xa0a8bed3, 0x3d6f, 0x4ad8, 0x90, 0x7a, 0x84, 0xd5, 0x2e, 0xe1, 0x54, 0x3b }

// {EED18069-2B1F-47c0-9C3C-20D5B070B84C}
#define DRIVER_SPECIFIC_ELEMENTS_BB_TEST_GUID         \
  { 0xeed18069, 0x2b1f, 0x47c0, 0x9c, 0x3c, 0x20, 0xd5, 0xb0, 0x70, 0xb8, 0x4c }

#endif
