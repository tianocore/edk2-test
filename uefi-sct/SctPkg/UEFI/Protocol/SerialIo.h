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

  SerialIo.h

Abstract:

  Serial IO protocol as defined in the EFI 1.0 specification.

  Abstraction of a basic serial device. Targeted at 16550 UART, but
  could be much more generic.

  (just for test)

--*/

#ifndef _SERIAL_IO_FOR_TEST_H
#define _SERIAL_IO_FOR_TEST_H

typedef struct _EFI_SERIAL_IO_PROTOCOL EFI_SERIAL_IO_PROTOCOL;;

#define EFI_SERIAL_IO_PROTOCOL_GUID     \
  { 0xBB25CF6F, 0xF1D4, 0x11D2, {0x9A, 0x0C, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0xFD }}

#define SERIAL_IO_INTERFACE_REVISION    0x00010000

//***********************************************
// SERIAL_IO_MODE
//***********************************************
typedef struct {
  UINT32                  ControlMask;

  // current Attributes
  UINT32                  Timeout;
  UINT64                  BaudRate;
  UINT32                  ReceiveFifoDepth;
  UINT32                  DataBits;
  UINT32                  Parity;
  UINT32                  StopBits;
} EFI_SERIAL_IO_MODE;

//***********************************************
// EFI_PARITY_TYPE
//***********************************************
typedef enum {
  DefaultParity,
  NoParity,
  EvenParity,
  OddParity,
  MarkParity,
  SpaceParity
} EFI_PARITY_TYPE;

//***********************************************
// EFI_STOP_BITS_TYPE
//***********************************************
typedef enum {
  DefaultStopBits,
  OneStopBit,           // 1 stop bit
  OneFiveStopBits,      // 1.2 stop bits
  TwoStopBits           // 2 stop bits
} EFI_STOP_BITS_TYPE;

//***********************************************
// CONTROL BITS
//***********************************************
#define EFI_SERIAL_CLEAR_TO_SEND                  0x0010
#define EFI_SERIAL_DATA_SEND_READY                0x0020
#define EFI_SERIAL_RING_INDICATE                  0x0040
#define EFI_SERIAL_CARRIER_DETECT                 0x0080
#define EFI_SERIAL_REQUEST_TO_SEND                0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY            0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY             0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY            0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE       0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE       0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE   0x4000

//
// Prototypes
//

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_RESET) (
  IN EFI_SERIAL_IO_PROTOCOL         *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_SET_ATTRIBUTES) (
  IN EFI_SERIAL_IO_PROTOCOL         *This,
  IN UINT64                         BaudRate,
  IN UINT32                         ReceiveFifoDepth,
  IN UINT32                         Timeout,
  IN EFI_PARITY_TYPE                Parity,
  IN UINT8                          DataBits,
  IN EFI_STOP_BITS_TYPE             StopBits
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_SET_CONTROL_BITS) (
  IN EFI_SERIAL_IO_PROTOCOL         *This,
  IN UINT32                         Control
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_GET_CONTROL_BITS) (
  IN EFI_SERIAL_IO_PROTOCOL         *This,
  OUT UINT32                        *Control
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_WRITE) (
  IN EFI_SERIAL_IO_PROTOCOL         *This,
  IN OUT UINTN                      *BufferSize,
  IN VOID                           *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_READ) (
  IN EFI_SERIAL_IO_PROTOCOL         *This,
  IN OUT UINTN                      *BufferSize,
  OUT VOID                          *Buffer
  );

struct _EFI_SERIAL_IO_PROTOCOL {
  UINT32                       Revision;
  EFI_SERIAL_RESET             Reset;
  EFI_SERIAL_SET_ATTRIBUTES    SetAttributes;
  EFI_SERIAL_SET_CONTROL_BITS  SetControl;
  EFI_SERIAL_GET_CONTROL_BITS  GetControl;
  EFI_SERIAL_WRITE             Write;
  EFI_SERIAL_READ              Read;

  EFI_SERIAL_IO_MODE           *Mode;
};

extern EFI_GUID  gBlackBoxEfiSerialIoProtocolGuid;

#endif
