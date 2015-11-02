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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  SerialIoBbTestMain.h

Abstract:
  Header file for Serial IO Protocol Black-Box Test.

--*/

#ifndef _SERIAL_IO_BB_TEST_MAIN_H
#define _SERIAL_IO_BB_TEST_MAIN_H

//
// Includes
//
#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#include <UEFI/Protocol/SerialIo.h>

//
// Definitions
//
#define MAX_BUFFER_SIZE             256

#define SERIAL_IO_BB_TEST_REVISION     0x00010000

// GUIDs for each test case
#define RESET_FUNC_TEST_GUID                        \
  { 0x0cfb28f0, 0xe1af, 0x496c, { 0xa1, 0xae, 0x9e, 0x83, 0xe7, 0x10, 0x94, 0x26 } }
#define SET_ATTRIBUTES_FUNC_TEST_GUID               \
  { 0xc3e72c51, 0x39b3, 0x46a7, { 0xa6, 0xcc, 0x6d, 0x0d, 0x5b, 0xba, 0xb3, 0x5c } }
#define SET_CONTROL_FUNC_TEST_GUID                  \
  { 0x2e6c2b4c, 0x7734, 0x49cc, { 0xa6, 0x9c, 0x64, 0x7d, 0xc2, 0xcf, 0x8d, 0x5e } }
#define GET_CONTROL_FUNC_TEST_GUID                  \
  { 0x1d917b22, 0x8e0c, 0x41fa, { 0x92, 0xbf, 0x68, 0xc0, 0x98, 0x18, 0x1e, 0x46 } }
#define WRITE_FUNC_TEST_GUID                        \
  { 0x88e03425, 0x9ef0, 0x480b, { 0x8b, 0x2c, 0xa4, 0xc7, 0xc3, 0xba, 0x41, 0x2f } }
#define READ_FUNC_TEST_GUID                         \
  { 0x58bb756a, 0x7cf6, 0x4965, { 0xbe, 0x19, 0x31, 0xc1, 0x4e, 0x81, 0x7b, 0xf4 } }

#define SET_ATTRIBUTES_CONF_TEST_GUID               \
  { 0x92c07cca, 0x9d78, 0x4f1d, { 0x8b, 0x5e, 0x52, 0x80, 0x4f, 0x67, 0x1f, 0xbb } }
#define SET_CONTROL_CONF_TEST_GUID                  \
  { 0xb7767573, 0xdee3, 0x424c, { 0x99, 0x1c, 0x1f, 0x55, 0x81, 0x43, 0x3f, 0x02 } }
#define WRITE_CONF_TEST_GUID                        \
  { 0xffdb507c, 0x57b4, 0x4553, { 0x9a, 0xe6, 0x98, 0xc8, 0x59, 0x3d, 0x29, 0xe2 } }
#define READ_CONF_TEST_GUID                         \
  { 0x41d1bced, 0xcad6, 0x435e, { 0xa8, 0x46, 0x7c, 0x88, 0xdb, 0x3a, 0x6e, 0x7e } }

#define RESET_STRESS_TEST_GUID                      \
  { 0x00ba266e, 0x34d6, 0x4ba0, { 0xa5, 0x51, 0x1e, 0x04, 0x44, 0x09, 0xbc, 0x80 } }
#define SET_ATTRIBUTES_STRESS_TEST_GUID             \
  { 0x40e6c23a, 0x22d6, 0x4078, { 0xa6, 0xe5, 0x84, 0xb6, 0xcf, 0xe4, 0x23, 0x81 } }
#define SET_CONTROL_STRESS_TEST_GUID                \
  { 0x0422999b, 0x2221, 0x4566, { 0x93, 0x6b, 0x82, 0xe2, 0x77, 0x12, 0x8b, 0x20 } }
#define GET_CONTROL_STRESS_TEST_GUID                \
  { 0x60715db7, 0xe4fb, 0x40a2, { 0xb2, 0xb0, 0xa2, 0x82, 0x96, 0x1d, 0x6a, 0xdd } }
#define WRITE_STRESS_TEST_GUID                      \
  { 0x6b777ad5, 0x25c9, 0x4bde, { 0x89, 0xcb, 0x9b, 0x18, 0x27, 0x05, 0xa8, 0xee } }
#define READ_STRESS_TEST_GUID                       \
  { 0xd86a7630, 0xe129, 0x4019, { 0xa3, 0x41, 0x4d, 0xd2, 0x4e, 0x36, 0x4c, 0x6f } }

//
// Global Variables
//

extern CHAR16 *gParityString[];
extern CHAR16 *gStopBitsString[];

//
// Prototypes
//

//
// TDS 3.1
//
EFI_STATUS
ResetFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
SetAttributesFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
SetControlFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
GetControlFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.5
//
EFI_STATUS
WriteFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.6
//
EFI_STATUS
ReadFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1
//
EFI_STATUS
SetAttributesConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
SetControlConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
WriteConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
ReadConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1
//
EFI_STATUS
ResetStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
SetAttributesStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
SetControlStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
GetControlStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
WriteStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.6
//
EFI_STATUS
ReadStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Support Functions
//

EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );

#endif
