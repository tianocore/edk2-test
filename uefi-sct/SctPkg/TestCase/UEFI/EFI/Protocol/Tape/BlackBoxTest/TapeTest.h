/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TapeTest.h

Abstract:

  Some definitions for TapeIo test driver

--*/

#ifndef _TAPE_TEST_H
#define _TAPE_TEST_H

#include <SctLib.h>
#include <UEFI/Protocol/Tape.h>

//
// Function prototypes
//
EFI_STATUS
EFIAPI
BBTestTapeFunctionRead (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestTapeFunctionWrite (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestTapeFunctionRewind (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestTapeFunctionSpace (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestTapeFunctionWriteFM (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestTapeFunctionReset (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );
  
extern void TapeTestWaitForAnyInput (void);
//#define _TestWaitForAnyInput() TapeTestWaitForAnyInput()

#define my_printf(x)  SctPrint	x
#define my_logMsgPrintf  SctPrint

#define logMsg(_guid,_title,_message,_result,_maskRes) \
  StandardLib->RecordAssertion (StandardLib,\
                    ( (_maskRes==_result) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_FAILED ),\
                   _guid,\
                   L"EFI Tape IO Protocol Testing ",\
                   L" - %a\n  %a\n  %a:%d\n  Status(0x%x) - %r",\
                   _title, _message, \
                   __FILE__, (UINTN)__LINE__,\
                   _result, ( (_maskRes==_result) ? EFI_SUCCESS : EFI_UNSUPPORTED )\
                   );
//#undef logMsg
//#define logMsg(_guid,_title,_message,_result,_maskRes)  
#define LogEnterFunction 	LoggingLib->EnterFunction   
#define LogExitFunction 	LoggingLib->ExitFunction                 


#endif
