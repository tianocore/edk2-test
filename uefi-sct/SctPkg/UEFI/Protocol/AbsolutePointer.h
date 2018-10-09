/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AbsolutePointer.h

Abstract:

  Absolute Pointer protocol as defined in the UEFI 2.1 specification.

--*/


#ifndef _ABSOLUTE_POINTER_FOR_TEST_H_
#define _ABSOLUTE_POINTER_FOR_TEST_H_

//
// Global ID for the Absolute Pointer Protocol
//
#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
    { 0x8d59d32b, 0xc655, 0x4ae9, { 0x9b, 0x15, 0xf2, 0x59, 0x04, 0x99, 0x2a, 0x43} }

typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;



//******************************************************* 
// EFI_ABSOLUTE_POINTER_STATE 
//******************************************************* 
typedef struct { 
  UINT64 CurrentX; 
  UINT64 CurrentY; 
  UINT64 CurrentZ; 
  UINT32 ActiveButtons; 
} EFI_ABSOLUTE_POINTER_STATE;

//****************************** 
//definitions of bits within ActiveButtons 
//****************************** 
#define EFI_ABSP_TouchActive                  0x00000001 
#define EFI_ABS_AltActive                     0x00000002

//******************************************************* 
// EFI_ABSOLUTE_POINTER_MODE 
//******************************************************* 
typedef struct {
  UINT64 AbsoluteMinX; 
  UINT64 AbsoluteMinY; 
  UINT64 AbsoluteMinZ; 
  UINT64 AbsoluteMaxX; 
  UINT64 AbsoluteMaxY; 
  UINT64 AbsoluteMaxZ; 
  UINT32 Attributes; 
} EFI_ABSOLUTE_POINTER_MODE; 

#define EFI_ABSP_SupportsAltActive                       0x00000001
#define EFI_ABSP_SupportsPressureAsZ                     0x00000002


//
// Prototypes for the Absolute Pointer Protocol
//

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_RESET) (
  IN  EFI_ABSOLUTE_POINTER_PROTOCOL             *This,
  IN  BOOLEAN                                   ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_GET_STATE) (
   IN EFI_ABSOLUTE_POINTER_PROTOCOL               *This, 
   IN OUT EFI_ABSOLUTE_POINTER_STATE               *State 
   );

//
// Interface structure for the Absolute Pointer Protocol
//
struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
  EFI_ABSOLUTE_POINTER_RESET       Reset;
  EFI_ABSOLUTE_POINTER_GET_STATE    GetState;
  EFI_EVENT                         WaitForInput;
  EFI_ABSOLUTE_POINTER_MODE         *Mode;
};

extern EFI_GUID gBlackBoxEfiAbsolutePointerProtocolGuid;



#endif /* _ABSOLUTE_POINTER_FOR_TEST_H_ */
