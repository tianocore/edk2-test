/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SerialMonitor.h

Abstract:

  NetworkTest Serial Port Monitor services declarations.

--*/

#ifndef _SERIAL_MONITOR_H_
#define _SERIAL_MONITOR_H_

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)

#define ENTS_SERIAL_MONITOR_NAME  L"Serial"

//
// External functions declarations
//
EFI_STATUS
EFIAPI
SerialListener (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN OUT UINTN                     *Size,
  OUT CHAR16                       **Buffer
  )
/*++

Routine Description:

  This func is to read data from serial port.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Size    - To indicate buffer length
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Some failure happened.

--*/
;

EFI_STATUS
EFIAPI
SerialSender (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN CHAR16                        *Buffer
  )
/*++

Routine Description:

  This func is to write data to serial port.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_ACCESS_DENIED    - Cannot send out packet in state SendOutPacket.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.
  
--*/
;

EFI_STATUS
EFIAPI
InitSerial (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Initialize Serial port.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EFIAPI
ResetSerial (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Reset Serial port.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

#endif
