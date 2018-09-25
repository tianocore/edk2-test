/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  RandomNumberGeneratorProtocol.h

Abstract:

  EFI Random Number Generator Protocol

--*/

#ifndef _RANDOM_NUMBER_PROTOCOL_H_
#define _RANDOM_NUMBER_PROTOCOL_H_

//
// Global ID for the Random Number Protocol
//
#define EFI_RANDOM_NUMBER_PROTOCOL_GUID    \
  {0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c,0xdc, 0x29, 0x1f, 0x44 }}



typedef struct _EFI_RNG_PROTOCOL EFI_RNG_PROTOCOL;;

typedef EFI_GUID EFI_RNG_ALGORITHM;

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_INFO) (
  IN     EFI_RNG_PROTOCOL     *This,
  IN OUT UINTN                *RNGAlgorithmListSize,
     OUT EFI_RNG_ALGORITHM    *RNGAlgorithmList
);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_RNG) (
  IN     EFI_RNG_PROTOCOL     *This,
  IN     EFI_RNG_ALGORITHM    *RNGAlgorithm, OPTIONAL
  IN     UINTN                RNGValueLength,
     OUT UINT8                *RNGValue
);

//
// Interface structure for the Random Number Protocol
//
struct _EFI_RNG_PROTOCOL {
  EFI_RNG_GET_INFO GetInfo;
  EFI_RNG_GET_RNG  GetRNG;
};

extern EFI_GUID gEfiRandomNumberProtocolGuid;

#endif
