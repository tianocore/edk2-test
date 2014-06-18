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

#define SERIAL_IO_BB_TEST_REVISION      0x00010000

#define IHV_SERIAL_IO_PROTOCOL_GUID     \
  { 0x90066ec9, 0xbd47, 0x4d36, 0x9e, 0x1e, 0x2c, 0x4e, 0xa1, 0xd0, 0x65, 0xbc }


// GUIDs for each test case
#define RESET_FUNC_TEST_GUID                        \
  { 0x826c6331, 0xdb40, 0x4791, { 0xa3, 0xda, 0x2c, 0x88, 0xb1, 0x8d, 0x97, 0x25 } }
#define SET_ATTRIBUTES_FUNC_TEST_GUID               \
  { 0x72922920, 0x6ae1, 0x4ba1, { 0x85, 0x67, 0x7d, 0x4a, 0xd9, 0x6d, 0x69, 0xc4 } }
#define SET_CONTROL_FUNC_TEST_GUID                  \
  { 0x88e96ad3, 0x281c, 0x4044, { 0x85, 0xc5, 0xd0, 0x6c, 0xec, 0xde, 0x89, 0x08 } }
#define GET_CONTROL_FUNC_TEST_GUID                  \
  { 0xe9f9d05a, 0xa5e6, 0x45aa, { 0x8a, 0xc0, 0x01, 0xd8, 0xaf, 0xa1, 0x1e, 0xfa } }
#define WRITE_FUNC_TEST_GUID                        \
  { 0xca46c8b2, 0xe9fd, 0x407c, { 0x97, 0xba, 0x48, 0x89, 0x6b, 0xa2, 0x0c, 0xd4 } }
#define READ_FUNC_TEST_GUID                         \
  { 0x6c4ded78, 0x3a93, 0x4843, { 0xa5, 0x13, 0xac, 0xef, 0xfd, 0x46, 0x33, 0x83 } }

#define SET_ATTRIBUTES_CONF_TEST_GUID               \
  { 0x724219da, 0x9412, 0x4848, { 0x95, 0xd3, 0x73, 0x38, 0xfe, 0xd1, 0x89, 0x26 } }
#define SET_CONTROL_CONF_TEST_GUID                  \
  { 0x4c87cd89, 0x89e5, 0x43b7, { 0x9f, 0x80, 0x93, 0xe0, 0x83, 0x6f, 0x39, 0x5e } }
#define WRITE_CONF_TEST_GUID                        \
  { 0x33f0fd18, 0x79f6, 0x4c0e, { 0x98, 0x65, 0x45, 0x26, 0x4a, 0xba, 0x8a, 0x2d } }
#define READ_CONF_TEST_GUID                         \
  { 0x0fd7665e, 0xc1d4, 0x4c03, { 0xb3, 0x82, 0xe1, 0xba, 0x80, 0x9b, 0xf8, 0x1d } }

#define RESET_STRESS_TEST_GUID                      \
  { 0xaee1904e, 0xf875, 0x40c4, { 0x95, 0xd5, 0xd4, 0x2f, 0x61, 0xf6, 0x7e, 0x8e } }
#define SET_ATTRIBUTES_STRESS_TEST_GUID             \
  { 0x521c21b5, 0x7494, 0x47f1, { 0x87, 0x84, 0xdc, 0xb7, 0xf6, 0xd3, 0x68, 0x93 } }
#define SET_CONTROL_STRESS_TEST_GUID                \
  { 0x60b97f85, 0xb3f3, 0x42be, { 0x91, 0x99, 0xd1, 0x27, 0x50, 0x7a, 0x72, 0x65 } }
#define GET_CONTROL_STRESS_TEST_GUID                \
  { 0x299465b7, 0x0528, 0x42d3, { 0xb9, 0x36, 0x9e, 0x1c, 0x66, 0xc4, 0xc4, 0x31 } }
#define WRITE_STRESS_TEST_GUID                      \
  { 0x7139bab1, 0x005a, 0x4cd5, { 0xa7, 0x22, 0xf4, 0x3b, 0x9f, 0x69, 0x33, 0x14 } }
#define READ_STRESS_TEST_GUID                       \
  { 0xe8ccc2c1, 0xf563, 0x40b0, { 0xbd, 0xc5, 0x10, 0x73, 0xef, 0xe0, 0xa9, 0x7b } }

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
