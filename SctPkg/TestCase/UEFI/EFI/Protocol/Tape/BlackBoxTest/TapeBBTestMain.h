/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TapeBBTestMain.h

Abstract:

  Test Driver of TapeIo Protocol

--*/

#ifndef __EFI_TAPE_TEST_H__
#define __EFI_TAPE_TEST_H__


#include "SctLib.h"

#include <Library/EfiTestLib.h>
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#include "TapeGuid.h"
#include "TapeTest.h"


#define TAPE_TEST_REVISION 0x00010000

#define TAPE_FUNCTION_TEST_GUID \
  { 0x1e93e633, 0xd65a, 0x459e, {0xab, 0x84, 0x93, 0xd9, 0xec, 0x26, 0x6d, 0x18 }}

EFI_STATUS
EFIAPI
InitializeTapeTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadTapeTest (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS getStandardLibInterface( EFI_HANDLE SupportHandle );
    
extern void TapeTestWaitForAnyInput ( void );
extern EFI_STATUS getStandardLibInterface( EFI_HANDLE SupportHandle );

extern EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
extern EFI_TEST_LOGGING_LIBRARY_PROTOCOL	*LoggingLib;

extern EFI_TAPE_IO_PROTOCOL *gTapeIoProtocol;
  
#endif
