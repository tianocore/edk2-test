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
                                                                
  Copyright (c) 2010 - 2012, Phoenix Corporation. All rights reserved.<BR>   
   
--*/
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
