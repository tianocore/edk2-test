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

  TestLoggingLibrary.h

Abstract:

  This file defines the EFI Test Logging Library Protocol.

--*/

#ifndef _EFI_TEST_LOGGING_LIBRARY_H_
#define _EFI_TEST_LOGGING_LIBRARY_H_

//
// Includes
//

//
// EFI Test Logging Library Protocol Definitions
//

#define EFI_TEST_LOGGING_LIBRARY_GUID       \
  { 0x1ab99b08, 0x58c6, 0x40dd, 0x86, 0xd8, 0xe8, 0xff, 0x2f, 0xa8, 0x4e, 0x4d }

#define EFI_TEST_LOGGING_LIBRARY_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TEST_LOGGING_LIBRARY_PROTOCOL EFI_TEST_LOGGING_LIBRARY_PROTOCOL;

//
// EFI Test Logging Library Protocol API - Line
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_LINE) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  UINT32                                      Length
  )
/*++

Routine Description:

  Writes a line into the log file. Generally it is for separating the different
  test results or message.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - EnterFunction
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_ENTER_FUNCTION) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  CHAR16                                      *FunctionName,
  IN  CHAR16                                      *Format,
  ...
  )
/*++

Routine Description:

  Records the tracing message of entering a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.

  FunctionName  - Name of enter function.

  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - ExitFunction
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_EXIT_FUNCTION) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  CHAR16                                      *FunctionName,
  IN  CHAR16                                      *Format,
  ...
  )
/*++

Routine Description:

  Records the tracing message of exiting a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.

  FunctionName  - Name of exit function.

  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - DumpMask
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_DUMP_MASK) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  UINT32                                      BitMask,
  IN  UINT32                                      Length
  )
/*++

Routine Description:

  Dump a bit-map mask.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

  BitMask       - Bit Mask to be dumpped.

  Length        - The number of bits to be dumpped.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

#define EFI_DUMP_HEX    0x01
#define EFI_DUMP_ASCII  0x02

//
// EFI Test Logging Library Protocol API - DumpBuf
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_DUMP_BUF) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  CHAR16                                      *Buffer,
  IN  UINT32                                      Length,
  IN  UINT32                                      Flags
  )
/*++

Routine Description:

  Dump a buffer in Hex, ASCII, or both styles.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

  Buffer        - Buffer to be dumpped.

  Length        - The number of bytes to be dumpped.

  Flags         - Dumpping format. HEX, ASCII, or BOTH.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol
//

struct _EFI_TEST_LOGGING_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TLL_LINE                          Line;
  EFI_TLL_ENTER_FUNCTION                EnterFunction;
  EFI_TLL_EXIT_FUNCTION                 ExitFunction;
  EFI_TLL_DUMP_MASK                     DumpMask;
  EFI_TLL_DUMP_BUF                      DumpBuf;
};

//
// Global ID for EFI Test Logging Library Protocol
//

extern EFI_GUID gEfiTestLoggingLibraryGuid;

#endif
