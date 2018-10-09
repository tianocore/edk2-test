/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SimplePointerProtocol.h

Abstract:

  Simple Pointer Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_SIMPLE_POINTER_FOR_TEST_H_
#define _EFI_SIMPLE_POINTER_FOR_TEST_H_

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
  { 0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }}


typedef struct _EFI_SIMPLE_POINTER_PROTOCOL EFI_SIMPLE_POINTER_PROTOCOL;;

//*******************************************************
// EFI_SIMPLE_POINTER_MODE
//*******************************************************
typedef struct {
  UINT64              ResolutionX;
  UINT64              ResolutionY;
  UINT64              ResolutionZ;
  BOOLEAN             LeftButton;
  BOOLEAN             RightButton;
} EFI_SIMPLE_POINTER_MODE;

//*******************************************************
// EFI_SIMPLE_POINTER_STATE
//*******************************************************
typedef struct {
  INT32              RelativeMovementX;
  INT32              RelativeMovementY;
  INT32              RelativeMovementZ;
  BOOLEAN            LeftButton;
  BOOLEAN            RightButton;
} EFI_SIMPLE_POINTER_STATE;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_RESET) (
  IN EFI_SIMPLE_POINTER_PROTOCOL  *This,
  IN BOOLEAN                      ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_GET_STATE) (
  IN EFI_SIMPLE_POINTER_PROTOCOL   *This,
  IN OUT EFI_SIMPLE_POINTER_STATE  *State
  );


struct _EFI_SIMPLE_POINTER_PROTOCOL {
  EFI_SIMPLE_POINTER_RESET        Reset;
  EFI_SIMPLE_POINTER_GET_STATE    GetState;
  EFI_EVENT                       WaitForInput;
  EFI_SIMPLE_POINTER_MODE         *Mode;
};

extern EFI_GUID gBlackBoxEfiSimplePointerProtocolGuid;

#endif
