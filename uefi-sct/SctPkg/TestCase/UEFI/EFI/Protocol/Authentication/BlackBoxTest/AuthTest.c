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

  authTest.c

Abstract:
  
  This driver supports platform authtest service

--*/

#include "AuthenticationBBTestMain.h"
#include "AuthTest.h"

#include EFI_TEST_PROTOCOL_DEFINITION(StandardTestLibrary)

//
// Worker functions
//

/*********************************************************


*********************************************************/
void hex_dump(unsigned char buffer[], int length)
{
	int index;
	unsigned char *ptr = buffer;

	if(ptr != NULL)
	{
		for(index=0; index<length; index++)
		{
			my_printf(( L"%02x", *ptr++));
		}
	}
}

/***********************************************************************************

***********************************************************************************/
	
	
EFI_STATUS GetAuthInfoTest( EFI_AUTHENTICATION_INFO_PROTOCOL *_this, EFI_HANDLE *handle)
{
	GenericAuthenticationNodeStruct *info = NULL;
	EFI_STATUS result;
	
	result = _this->Get(_this, handle, &info);	
	logMsg(gAuthenticationBBTestMainAssertionGuid003,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Get", 
					"with valid parameters", 
					result, 
					EFI_SUCCESS);					
	if( result != EFI_SUCCESS)
	{
		return EFI_UNSUPPORTED;
	}
	
	if (info != NULL) {
      tBS->FreePool (info);
      info = NULL;
    }
		
	result = _this->Get(_this, NULL, &info);	
	logMsg(gAuthenticationBBTestMainAssertionGuid004,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Get", 
					"with invalid parameters(ControllerHandle=NULL)", 
					result, 
					EFI_INVALID_PARAMETER);
	if( result != EFI_INVALID_PARAMETER)
	{
		;
	}
	
	result = _this->Get(_this, handle, NULL);	
	logMsg(gAuthenticationBBTestMainAssertionGuid005,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Get", 
					"with invalid parameters(Buffer=NULL)", 
					result, 
					EFI_INVALID_PARAMETER);
	if( result != EFI_INVALID_PARAMETER)
	{
		;
	}
	
	return EFI_SUCCESS;		
}

EFI_STATUS SetAuthInfoTest( EFI_AUTHENTICATION_INFO_PROTOCOL *_this, EFI_HANDLE *handle)
{
	GenericAuthenticationNodeStruct info;
	EFI_STATUS result;
	int index;
	UINT16 len[8]={0,1,2,7,8,15,16,17};
	
	info.length = 0x20;
	result = _this->Set(_this, handle, &info);	
	logMsg(gAuthenticationBBTestMainAssertionGuid006,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Set", 
					"with valid parameters", 
					result, 
					EFI_SUCCESS);
	if( result != EFI_SUCCESS)
	{
		return EFI_UNSUPPORTED;
	}

	result = _this->Set(_this, NULL, &info);	
	logMsg(gAuthenticationBBTestMainAssertionGuid007,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Set", 
					"with invalid parameters(ControllerHandle=NULL)", 
					result, 
					EFI_INVALID_PARAMETER);
	if( result != EFI_INVALID_PARAMETER)
	{
		;
	}
	
	result = _this->Set(_this, handle, NULL);	
	logMsg(gAuthenticationBBTestMainAssertionGuid008,
					"EFI_AUTHENTICATION_INFO_PROTOCOL.Set", 
					"with invalid parameters(Buffer=NULL)", 
					result, 
					EFI_INVALID_PARAMETER);
	if( result != EFI_INVALID_PARAMETER)
	{
		;
	}

	for(index=0; index<sizeof(len)/sizeof(UINT16); index++)
	{
		info.length = len[index];
		result = _this->Set(_this, handle, &info);	
		logMsg(gAuthenticationBBTestMainAssertionGuid009,
						"EFI_AUTHENTICATION_INFO_PROTOCOL.Set", 
						"with invalid parameters(info.length<18)", 
						result, 
						EFI_INVALID_PARAMETER);
		if( result != EFI_INVALID_PARAMETER)
		{
			;
		}
  }	
	return EFI_SUCCESS;		
}
