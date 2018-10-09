/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  authStub.h

Abstract:

  This driver supports platform authtest service

--*/

#ifndef _AUTH_STUB_H_
#define _AUTH_STUB_H_

#define 	EFI_AUTHENTICATION_INFO_PROTOCOL_GUID { 0x7671d9d0, 0x52db, 0x4173, {0xaa,0x69,0x23,0x27,0xf2,0x1f,0x0b,0xc7 }}

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

#define EFI_AUTHENTICATION_CHAP_RADIUS_GUID { 0xd6062b50, 0x15ca, 0x11da, {0x9219, 0x00,0x10,0x83,0xff,0xca,0x4d }}

#endif
