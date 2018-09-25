/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  authTest.h

Abstract:

  This driver supports platform authtest service

--*/

#ifndef _AUTH_TEST_H
#define _AUTH_TEST_H

#include "AuthStub.h"


//
// Function prototypes
//


#undef my_printf

#ifdef DEBUG_HASHTEST
	#define my_printf(x)  SctPrint	
	#define my_logMsgPrintf  SctPrint
#else
	#define my_printf(x) // SctPrint	
	#define my_logMsgPrintf  SctPrint
#endif

#define logMsg(_guid,_title,_message,_result,_maskRes) \
  StandardLib->RecordAssertion (StandardLib,\
                    ( (_maskRes==_result) ? EFI_TEST_ASSERTION_PASSED : EFI_TEST_ASSERTION_FAILED ),\
                   _guid,\
                   L"EFI Authentication Protocol Testing ",\
                   L" - %a\n  %a\n  %a:%d\n  Status(0x%x) - %r",\
                   _title, _message, \
                   __FILE__, (UINTN)__LINE__,\
                   _result, ( (_maskRes==_result) ? EFI_SUCCESS : EFI_UNSUPPORTED )\
                   );
                   
extern EFI_GUID gBlackBoxEfiAuthenticationProtocolGuid;
EFI_STATUS GetAuthInfoTest( EFI_AUTHENTICATION_INFO_PROTOCOL *_this, EFI_HANDLE *handle);
EFI_STATUS SetAuthInfoTest( EFI_AUTHENTICATION_INFO_PROTOCOL *_this, EFI_HANDLE *handle);

#endif
