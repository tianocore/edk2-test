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
  SerialIoBbTestConformance.c

Abstract:
  Source file for Serial IO Protocol Black-Box Test - Conformance Test.

--*/

#include "SctLib.h"
#include "SerialIoBBTestMain.h"

//
// Prototypes (external)
//

EFI_STATUS
EFIAPI
SetAttributesConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
SetControlConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
ReadConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes (internal)
//

EFI_STATUS
EFIAPI
SetAttributesConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
SetControlConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
ReadConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
ReadConfTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

//
// Functions
//

/**
 *  TDS 4.1 - Entry Point for SerialIo->SetAttributes() Conformance Test.
 *  @param This          A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
SetAttributesConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Invoke SetAttribute() service with unsupported value
  //
  Status = SetAttributesConfTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.2 - Entry Point for SerialIo->SetControl() Conformance Test.
 *  @param This          A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
SetControlConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Question: Is it possible for an implementation to support additional
  // control bits? If yes, we need to remove the next checkpoint.
  //

  //
  // Invoke SetControl() service with unsupported value
  //
  Status = SetControlConfTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 4.4 - Entry Point for SerialIo->Read() Conformance Test.
 *  @param This          A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
ReadConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Invoke Read() service without enough characters will be read in hardware-
  // loopback mode
  //
  Status = ReadConfTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Invoke Read() service without enough characters will be read in software-
  // loopback mode
  //
 Status = ReadConfTestSub2 (
            (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
            StandardLib,
            LoggingLib
            );

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**************************************************************/
/* Internal functions                                         */
/**************************************************************/

/**
 *  Invoke SetAttribute() service with unsupported value.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
SetAttributesConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT32                InvalidParityArray[]    = {SpaceParity+1, 0};
  UINT32                InvalidStopBitsArray[]  = {TwoStopBits+1, 0};

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetAttributeConfTestSub1",
                  L"TDS 4.1.2.1"
                  );
  }

  //
  // Set invalid attributes - Parity
  //
  for (Index = 0; InvalidParityArray[Index] != 0; Index++) {
    Status = SerialIo->SetAttributes (
                         SerialIo,
                         0,                       // BaudRate
                         0,                       // ReceiveFifoDepth
                         0,                       // Timeout
                         (EFI_PARITY_TYPE)InvalidParityArray[Index],
                         0,                       // DataBits
                         0                        // StopBits
                         );
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion & message
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gSerialIoBbTestConformanceAssertionGuid004,
                   L"SerialIo.SetAttributes - With unsupported Parity",
                   L"%a:%d: Parity=%s, Status=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   gParityString[InvalidParityArray[Index]],
                   Status,
                   EFI_INVALID_PARAMETER
                   );
  }

  //
  // Set invalid attributes - StopBits
  //
  for (Index = 0; InvalidStopBitsArray[Index] != 0; Index++) {
    Status = SerialIo->SetAttributes (
                         SerialIo,
                         0,                       // BaudRate
                         0,                       // ReceiveFifoDepth
                         0,                       // Timeout
                         DefaultParity,           // Parity
                         0,                       // DataBits
                         (EFI_STOP_BITS_TYPE)InvalidStopBitsArray[Index]
                         );
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion & message
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gSerialIoBbTestConformanceAssertionGuid006,
                   L"SerialIo.SetAttributes - With unsupported StopBits",
                   L"%a:%d: StopBits=%s, Status=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   gStopBitsString[InvalidStopBitsArray[Index]],
                   Status,
                   EFI_INVALID_PARAMETER
                   );
  }

  //
  // SetAttributes with default attributes (restore environment)
  //
  Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetAttributesConfTestSub1",
                  L"TDS 4.1.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Invoke SetControl() service with unsupported value.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
SetControlConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT32                ControlBits;
  UINT32                ValidControlBits =
    EFI_SERIAL_REQUEST_TO_SEND          | EFI_SERIAL_DATA_TERMINAL_READY      |
    EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE | EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE |
    EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetControlConfTestSub1",
                  L"TDS 4.2.2.1"
                  );
  }

  //
  // Scan all 32-bit control bits
  //
  for (Index = 0; Index < 32; Index++) {
    ControlBits = 1 << Index;

    //
    // Skip valid ControlBits
    //
    if ((ControlBits & ValidControlBits) != 0) {
      continue;
    }

    //
    // Set unsupported ControlBits
    //
    Status = SerialIo->SetControl (
                         SerialIo,
                         ControlBits
                         );
    if (Status == EFI_UNSUPPORTED) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion & message
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gSerialIoBbTestConformanceAssertionGuid007,
                   L"SerialIo.SetControl - with unsupported ControlBits",
                   L"%a:%d: ControlBits=0x%x, Status=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ControlBits,
                   Status,
                   EFI_UNSUPPORTED
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetControlConfTestSub1",
                  L"TDS 4.2.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Invoke Read() service without enough characters will be read.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
ReadConfTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ReadConfTestSub1",
                  L"TDS 4.4.2.1"
                  );
  }

  //
  // Set the default attributes
  //
  Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set attributes to default values",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.4.2.1 - Cannot set attributes to default values"
                    );
    }

    return Status;
  }

  //
  // Print out a warning message
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Don't send anything to serial port..."
                 );

  //
  // Set current mode to hardware-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to hardware-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.4.2.1 - Cannot set to hardware-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in the input buffer
  //
  // NOTES: DON'T remove below codes. Record assertion or message maybe write
  // data to serial port.
  //
  while (TRUE) {
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
      break;
    }
  }

  //
  // Read one byte
  //
  BufferSize = 1;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_TIMEOUT) &&
      (BufferSize     == 0          )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Reset serial device (restore environment)
  //
  Status = SerialIo->Reset (SerialIo);

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSerialIoBbTestConformanceAssertionGuid008,
                 L"SerialIo.Read - Read one byte (no byte exists)",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,
                 EFI_TIMEOUT,
                 BufferSize,
                 0
                 );

  //
  // Clean up all data in input buffer
  //
  // NOTES: DON'T remove below codes. Record assertion or message maybe write
  // data to serial port.
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to hardware-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.4.2.1 - Cannot set to hardware-loopback mode"
                    );
    }

    return Status;
  }

  while (TRUE) {
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
      break;
    }
  }

  //
  // Write one byte
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    Status = SerialIo->Reset (SerialIo);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot write a byte to serial port",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.3.2.1 - Cannot write a byte to serial port"
                    );
    }

    return Status;
  }

  //
  // Read two bytes
  //
  Buffer[0]  = 0x00;
  BufferSize = 2;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_TIMEOUT) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )){
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Reset serial device (restore environment)
  //
  Status = SerialIo->Reset (SerialIo);

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSerialIoBbTestConformanceAssertionGuid009,
                 L"SerialIo.Read - Read two bytes (one byte exists)",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,      EFI_TIMEOUT,
                 BufferSize,  1,
                 Buffer[0],   0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadConfTestSub1",
                  L"TDS 4.3.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  Invoke Read() service without enough characters will be read.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
EFIAPI
ReadConfTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ReadConfTestSub2",
                  L"TDS 4.4.2.1"
                  );
  }

  //
  // Set the default attributes
  //
  Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set attributes to default values",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub2",
                    L"TDS 4.4.2.1 - Cannot set attributes to default values"
                    );
    }

    return Status;
  }

  //
  // Print out a warning message
  //
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Don't send anything to serial port..."
                 );

  //
  // Set current mode to software-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to software-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.4.2.1 - Cannot set to software-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in the input buffer
  //
  // NOTES: DON'T remove below codes. Record assertion or message maybe write
  // data to serial port.
  //
  while (TRUE) {
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
      break;
    }
  }

  //
  // Read one byte
  //
  BufferSize = 1;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_TIMEOUT) &&
      (BufferSize     == 0          )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Reset serial device (restore environment)
  //
  Status = SerialIo->Reset (SerialIo);

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSerialIoBbTestConformanceAssertionGuid010,
                 L"SerialIo.Read - Read one byte (no byte exists)",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,    EFI_TIMEOUT,
                 BufferSize,        0
                 );

  //
  // Clean up all data in input buffer
  //
  // NOTES: DON'T remove below codes. Record assertion or message maybe write
  // data to serial port.
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to software-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.4.2.1 - Cannot set to software-loopback mode"
                    );
    }

    return Status;
  }
  while (TRUE) {
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
      break;
    }
  }

  //
  // Write one byte
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    Status = SerialIo->Reset (SerialIo);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot write a byte to serial port",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadConfTestSub1",
                    L"TDS 4.3.2.1 - Cannot write a byte to serial port"
                    );
    }

    return Status;
  }

  //
  // Read two bytes
  //
  Buffer[0]  = 0x00;
  BufferSize = 2;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_TIMEOUT) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )){
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Reset serial device (restore environment)
  //
  Status = SerialIo->Reset (SerialIo);

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gSerialIoBbTestConformanceAssertionGuid011,
                 L"SerialIo.Read - Read two bytes (one byte exists)",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,      EFI_TIMEOUT,
                 BufferSize,  1,
                 Buffer[0],   0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadConfTestSub2",
                  L"TDS 4.3.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
