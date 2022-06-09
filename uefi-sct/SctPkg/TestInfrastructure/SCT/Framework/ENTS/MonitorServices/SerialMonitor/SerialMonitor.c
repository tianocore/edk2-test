/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SerialMonitor.c

Abstract:

  Serial Port Monitor services implementations.

--*/

#include "SctLib.h"
#include <Library/EntsLib.h>
#include "SerialMonitor.h"

#define SIGNAL_TAG_LENGTH 2
#define HANDLE_IN_USE     2

//
// global variables
//
CHAR8                     gSerialSignalStart[SIGNAL_TAG_LENGTH] = { 0x55, 0x55 };
CHAR8                     gSerialSignalEnd[SIGNAL_TAG_LENGTH]   = { 0x57, 0x57 };

#define SERIAL_BUFFER_OUT_MAX 4096
CHAR8                     SerialBufferOut[SERIAL_BUFFER_OUT_MAX];

EFI_ENTS_MONITOR_PROTOCOL *gSerialMonitorInterface = NULL;

//
// Local Functions Declaration
//
BOOLEAN
IsComdBegin (
  IN CHAR8                          *Buffer,
  IN UINTN                          Size
  );

BOOLEAN
IsComdEnd (
  IN CHAR8                          *Buffer,
  IN UINTN                          Size
  );

EFI_STATUS
GetByte (
  IN EFI_SERIAL_IO_PROTOCOL   *SerialIo,
  IN OUT UINTN                *BufferSize,
  OUT    CHAR8                *Buffer
  );

EFI_STATUS
EFIAPI
SerialMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  );

//
// External functions implementations
//
EFI_STATUS
EFIAPI
SerialMonitorEntryPoint (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point of SerialMonitor.
  
Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = SerialMonitorUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_MONITOR_PROTOCOL),
                  (VOID **)&gSerialMonitorInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gSerialMonitorInterface->MonitorName      = ENTS_SERIAL_MONITOR_NAME;
  gSerialMonitorInterface->MonitorIo        = NULL;
  gSerialMonitorInterface->InitMonitor      = InitSerial;
  gSerialMonitorInterface->ResetMonitor     = ResetSerial;
  gSerialMonitorInterface->MonitorListener  = SerialListener;
  gSerialMonitorInterface->MonitorSender    = SerialSender;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  gSerialMonitorInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gSerialMonitorInterface != NULL) {
    tBS->FreePool (gSerialMonitorInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
SerialMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  )
/*++

Routine Description:

  Unload SerialMonitor.

Arguments:

  ImageHandle           - The image handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  Status = tBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  gSerialMonitorInterface,
                  NULL
                  );

  if (gSerialMonitorInterface != NULL) {
    tBS->FreePool (gSerialMonitorInterface);
  }

  return Status;
}

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
{
  EFI_STATUS              Status;
  EFI_SERIAL_IO_PROTOCOL  *SerialIo;
  UINTN                   NoHandle;
  EFI_HANDLE              *HandleBuffer;

  SerialIo = NULL;

  Status = EntsLocateHandle (
            ByProtocol,
            &gEfiSerialIoProtocolGuid,
            NULL,
            &NoHandle,
            &HandleBuffer
            );

  if (NoHandle >= HANDLE_IN_USE) {
    tBS->HandleProtocol (
          HandleBuffer[HANDLE_IN_USE - 1],
          &gEfiSerialIoProtocolGuid,
          (VOID **) &SerialIo
          );
  } else {
    Status = tBS->LocateProtocol (
                    &gEfiSerialIoProtocolGuid,
                    NULL,
                    (VOID **) &SerialIo
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  Status = SerialIo->SetAttributes (
                      SerialIo,
                      9600,
                      0,  // ReceiveFifoDepth
                      0,  // Timeout
                      0,  // Parity
                      8,  // DataBits
                      1   // StopBits
                      );

  if (EFI_ERROR (Status)) {
    EntsPrint (L"Set Serial attribute 9600 - %r\n", Status);
    return Status;
  }

  SerialIo->Reset (SerialIo);

  This->MonitorIo = (VOID *) SerialIo;

  EntsFreePool(HandleBuffer);

  return EFI_SUCCESS;
}

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
{
  EFI_STATUS              Status;
  EFI_SERIAL_IO_PROTOCOL  *SerialIo;

  SerialIo = This->MonitorIo;

  Status = SerialIo->SetAttributes (
                      SerialIo,
                      115200,
                      0,  // ReceiveFifoDepth
                      0,  // Timeout
                      0,  // Parity
                      8,  // DataBits
                      1   // StopBits
                      );

  if (EFI_ERROR (Status)) {
    EntsPrint (L"Set Serial attribute 115200 - %r\n", Status);
  }

  SerialIo->Reset (SerialIo);
  This->MonitorIo = NULL;

  return Status;
}

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
{
  EFI_STATUS              Status;
  EFI_SERIAL_IO_PROTOCOL  *SerialIo;

  SerialIo = This->MonitorIo;

  if ((Size == NULL) || (Buffer == NULL) || (*Buffer != NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status  = EFI_SUCCESS;

  *Size   = 0;

  //
  // Find start signal
  //
  do {
    Status = GetByte (SerialIo, Size, SerialBufferOut);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    if (IsComdBegin (SerialBufferOut, *Size)) {
      EntsSetMem (SerialBufferOut, *Size, 0);
      *Size = 0;
      break;
    }
  } while (1);

  //
  // Retrieve serial port until sig end is got
  //
  do {
    Status = GetByte (SerialIo, Size, SerialBufferOut);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    if (IsComdEnd (SerialBufferOut, *Size)) {
      EntsSetMem (SerialBufferOut + (*Size) - SIGNAL_TAG_LENGTH, SIGNAL_TAG_LENGTH, 0);
      *Size -= SIGNAL_TAG_LENGTH;
      break;
    }

  } while (1);

  *Buffer = EntsAllocatePool(*Size + 1);
  if (*Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status = Char8ToChar16 (SerialBufferOut, *Size, *Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EntsSetMem (SerialBufferOut, 1024, 0);

  return EFI_SUCCESS;
}

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
{
  EFI_STATUS              Status;
  UINTN                   BufferSize;
  CHAR8                   *BufferTmp;
  EFI_SERIAL_IO_PROTOCOL  *SerialIo;

  SerialIo  = This->MonitorIo;
  Status    = EFI_SUCCESS;

  //
  // Convert CHAR16 string to CHAR8 string
  //
  BufferSize = EntsStrLen(Buffer);
  BufferTmp = EntsAllocatePool(BufferSize + 1);
  if (BufferTmp == NULL) {
  	return EFI_OUT_OF_RESOURCES;
  }
  Status    = Char16ToChar8 (Buffer, BufferTmp, BufferSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // write data: Adding SigStart/SigEnd tag
  //
  BufferSize  = SIGNAL_TAG_LENGTH;
  Status      = SerialIo->Write (SerialIo, &BufferSize, gSerialSignalStart);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_STATUS ((L"SerialWrite device Error\n"));
    EntsPrint (L"In Sender: can't write start sig Status - %r", Status);
    tBS->FreePool (BufferTmp);
    return Status;
  }

  BufferSize  = EntsStrLen (Buffer) + 1;
  Status      = SerialIo->Write (SerialIo, &BufferSize, BufferTmp);
  tBS->FreePool (BufferTmp);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_STATUS ((L"SerialWrite device Error\n"));
    EntsPrint (L"In Sender: can't write data - %r", Status);
    return Status;
  }

  BufferSize  = SIGNAL_TAG_LENGTH;
  Status      = SerialIo->Write (SerialIo, &BufferSize, gSerialSignalEnd);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_STATUS ((L"SerialWrite device Error\n"));
    EntsPrint (L"In Sender: can't write end sig. Status - %r", Status);
    return Status;
  }

  BufferSize  = 1;
  Status      = SerialIo->Write (SerialIo, &BufferSize, L"\n");
  if (EFI_ERROR (Status)) {
    EFI_ENTS_STATUS ((L"SerialWrite device Error\n"));
    EntsPrint (L"In Sender: can't write data - %r", Status);
    return Status;
  }

  Status = SerialIo->Reset (SerialIo);
  if (EFI_ERROR (Status)) {
    EntsPrint (L"in Sender:Error when reset serialIo");
  }

  return Status;
}

//
// Internal functions implementations
//
BOOLEAN
IsComdBegin (
  IN CHAR8                          *Buffer,
  IN UINTN                          Size
  )
/*++

Routine Description:

  This func is to search a start signal at the end of a buffer.

Arguments:

  Buffer  - The buffer to search.
  Size    - The data length of the buffer.

Returns:

  TRUE    - Operation succeeded.
  FALSE   - Operation failed.

--*/
{
  if (Size < SIGNAL_TAG_LENGTH) {
    return FALSE;
  }

  if (EntsCompareMem (Buffer + Size - SIGNAL_TAG_LENGTH, gSerialSignalStart, SIGNAL_TAG_LENGTH) == 0) {
    EntsPrint ((L"\nget sig begin\n"));
    return TRUE;
  }

  return FALSE;
}

BOOLEAN
IsComdEnd (
  IN CHAR8                          *Buffer,
  IN UINTN                          Size
  )
/*++

Routine Description:

  This func is to search a end signal at the end of a buffer.

Arguments:

  Buffer  - The buffer to search.
  Size    - The data length of the buffer.

Returns:

  TRUE    - Operation succeeded.
  FALSE   - Operation failed.

--*/
{
  if (Size < SIGNAL_TAG_LENGTH) {
    return FALSE;
  }

  if (EntsCompareMem (Buffer + Size - SIGNAL_TAG_LENGTH, gSerialSignalEnd, SIGNAL_TAG_LENGTH) == 0) {
    EntsPrint ((L"\nget sig end\n"));
    return TRUE;
  }

  return FALSE;
}

EFI_STATUS
GetByte (
  IN EFI_SERIAL_IO_PROTOCOL   *SerialIo,
  IN OUT UINTN                *BufferSize,
  OUT CHAR8                   *Buffer
  )
/*++

Routine Description:

  This func is to read one byte from serialIO port, and append this byte to a buffer.

Arguments:

  SerialIo    - Interface of SerialIo Protocol
  BufferSize  - Pointer of the size of the prelocated buffer. the size will be changed after reading
  Buffer      - To append the byte got from serial port

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Some failure happened.


--*/
{
  EFI_STATUS  Status;
  UINTN       Size;
  CHAR8       BufferTmp;

  if ((Buffer == NULL) || (BufferSize == NULL)) {
    EFI_ENTS_STATUS ((L"Invalid parameter for GetByte"));
    return EFI_INVALID_PARAMETER;
  }

  Size = 1;
  while (1) {
    Status = SerialIo->Read (SerialIo, &Size, &BufferTmp);
    if (0 == Size) {
      Size = 1;
      continue;
    }

    if (Status == EFI_SUCCESS) {
      break;
    } else {
      EntsPrint (L"GetByte Statue:%r\n", Status);
    }

    if (Status == EFI_DEVICE_ERROR) {
      EFI_ENTS_STATUS ((L"SerialRead device Error\n"));
      EntsPrint (L"getByte: device_error\n");
      return Status;
    }
  }

  EntsCopyMem (Buffer + (*BufferSize), &BufferTmp, Size);
  *BufferSize += Size;

  return EFI_SUCCESS;
}
