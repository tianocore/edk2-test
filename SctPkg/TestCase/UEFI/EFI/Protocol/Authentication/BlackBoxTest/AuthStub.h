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

  authStub.h

Abstract:

  This driver supports platform authtest service

--*/

#ifndef _AUTH_STUB_H_
#define _AUTH_STUB_H_

#define 	EFI_AUTHENTICATION_INFO_PROTOCOL_GUID {0x7671d9d0, 0x52db, 0x4173, 0xaa,0x69,0x23,0x27,0xf2,0x1f,0x0b,0xc7}

typedef struct _EFI_AUTHENTICATION_INFO_PROTOCOL EFI_AUTHENTICATION_INFO_PROTOCOL;;

typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_GET)(
	IN EFI_AUTHENTICATION_INFO_PROTOCOL *this,
	IN EFI_HANDLE *ControllerHandle,
	OUT void *Buffer);	

typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_SET)(
	IN EFI_AUTHENTICATION_INFO_PROTOCOL *this,
	IN EFI_HANDLE *ControllerHandle,
	IN void *Buffer);	

typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_DEL)(
	IN EFI_AUTHENTICATION_INFO_PROTOCOL *this,
	IN EFI_HANDLE *ControllerHandle
	);	

typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_DUMPALL)(
	IN EFI_AUTHENTICATION_INFO_PROTOCOL *this
	);	
	
typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_CLEANALL)(
	IN EFI_AUTHENTICATION_INFO_PROTOCOL *this
	);	
			
struct _EFI_AUTHENTICATION_INFO_PROTOCOL {
	EFI_AUTHENTICATION_INFO_PROTOCOL_GET Get;
	EFI_AUTHENTICATION_INFO_PROTOCOL_SET Set;
	EFI_AUTHENTICATION_INFO_PROTOCOL_DEL Del;
	EFI_AUTHENTICATION_INFO_PROTOCOL_DUMPALL DumpAll;
	EFI_AUTHENTICATION_INFO_PROTOCOL_CLEANALL CleanAll;
};

#pragma pack(1)
typedef struct {
	EFI_GUID guid;
	UINT16 length;
	unsigned char authenticationData[1];
}GenericAuthenticationNodeStruct;
#pragma pack()

#define EFI_AUTHENTICATION_CHAP_RADIUS_GUID {0xd6062b50, 0x15ca, 0x11da, 0x9219, 0x00,0x10,0x83,0xff,0xca,0x4d}	

#endif
