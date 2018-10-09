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

  SimpleTextInputEx.h

Abstract:

  Time Stamp Protocol from the UEFI 2.4 specification.

--*/

#ifndef _TIME_STAMP_PROTOCOL_H_
#define _TIME_STAMP_PROTOCOL_H_


//
// Global ID for the Time Stamp Protocol
//
#define EFI_TIMESTAMP_PROTOCOL_GUID \
{ 0xafbfde41, 0x2e6e, 0x4262, {0xba, 0x65, 0x62, 0xb9, 0x23, 0x6e, 0x54, 0x95 }}

typedef struct _EFI_TIMESTAMP_PROTOCOL EFI_TIMESTAMP_PROTOCOL;;

typedef struct {
  UINT64 Frequency;
  UINT64 EndValue;
} EFI_TIMESTAMP_PROPERTIES;


typedef
UINT64
(EFIAPI *TIMESTAMP_GET) (
VOID
);


typedef
EFI_STATUS
(EFIAPI *TIMESTAMP_GET_PROPERTIES) (
OUT EFI_TIMESTAMP_PROPERTIES *Properties
);

//
// Interface structure for the Time Stamp Protocol
//
typedef struct _EFI_TIMESTAMP_PROTOCOL {
  TIMESTAMP_GET            GetTimestamp;
  TIMESTAMP_GET_PROPERTIES GetProperties;
} EFI_TIMESTAMP_PROTOCOL;

extern EFI_GUID gEfiTimeStampProtocolGuid;

#endif
