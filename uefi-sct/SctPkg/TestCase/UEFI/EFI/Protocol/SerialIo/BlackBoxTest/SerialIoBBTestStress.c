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
  SerialIoBbTestStress.c

Abstract:
  Source file for Serial IO Protocol Black-Box Test - Stress Test.

--*/

#include "SctLib.h"
#include "SerialIoBBTestMain.h"

#define MULTIPLE_TEST_TIMES     5

//
// Prototypes (external)
//

EFI_STATUS
EFIAPI
ResetStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
SetAttributesStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
SetControlStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
GetControlStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
WriteStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
ReadStressTest (
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
ResetStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
SetAttributesStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
SetControlStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
GetControlStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
WriteStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
WriteStressTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
WriteStressTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
ReadStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
ReadStressTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
EFIAPI
ReadStressTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

//
// Functions
//

/**
 *  TDS 5.1 - Entry Point for SerialIo->Reset() Stress Test.
 *  @param This          A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
ResetStressTest (
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
  // Reset the serial device multiple times
  //
  Status = ResetStressTestSub1 (
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
 *  TDS 5.2 - Entry Point for SerialIo->SetAttributes() Stress Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
SetAttributesStressTest (
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
  // SetAttributes with all standard combination attributes
  //
  Status = SetAttributesStressTestSub1 (
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
 *  TDS 5.3 - Entry Point for SerialIo->SetControl() Stress Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
SetControlStressTest (
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
  // SetControl with all valid combination control-bits
  //
  Status = SetControlStressTestSub1 (
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
 *  TDS 5.4 - Entry Point for SerialIo->GetControl() Stress Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
GetControlStressTest (
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
  // GetControl to check all valid combination control-bits
  //
  Status = GetControlStressTestSub1 (
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
 *  TDS 5.5 - Entry Point for SerialIo->Write() Stress Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
WriteStressTest (
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
  // Write data in non-loopback mode
  //
  Status = WriteStressTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Write data in standard attributes
  //
  Status = WriteStressTestSub2 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Write data multiple times
  //
  Status = WriteStressTestSub3 (
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
 *  TDS 5.6 - Entry Point for SerialIo->Read() Stress Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
EFIAPI
ReadStressTest (
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
  // Read data in non-loopback mode
  //
  Status = ReadStressTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Read data in standard attributes
  //
  Status = ReadStressTestSub2 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Read data multiple times
  //
  Status = ReadStressTestSub3 (
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
 *  Reset the serial device multiple times.
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
ResetStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ResetStressTestSub1",
                  L"TDS 5.1.2.1"
                  );
  }

  //
  // Reset the serial device multiple times
  //
  for (Index = 0; Index < MULTIPLE_TEST_TIMES; Index++) {
    //
    // Reset the serial device
    //
    Status = SerialIo->Reset (SerialIo);
    if (Status == EFI_SUCCESS) {
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
                   gSerialIoBbTestStressAssertionGuid001,
                   L"SerialIo.Reset - Reset the serial device multiple times",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                   L"Index=%d\n"
                   L"Status=%r, Expected=%r\n",
                   Index,
                   Status,      EFI_SUCCESS
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ResetStressTestSub1",
                  L"TDS 5.1.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetAttributes with all standard combination attributes.
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
SetAttributesStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index1, Index2, Index3, Index4, Index5, Index6;
  // NOTES: All standard baud rates are made from implementation.
  UINT64                BaudRateArray[]   = {50, 75, 110, 134, 150, 300, 600, 1200, 1800, 2000, 2400, 3600, 4800, 7200, 9600, 19200, 38400, 57600, 115200, 0};
  UINT32                FifoDepthArray[]  = {1, 8, 16, 0};
  UINT32                TimeoutArray[]    = {1, 1000000, 100000000, 0};
  UINT32                ParityArray[]     = {NoParity, EvenParity, OddParity, MarkParity, SpaceParity, 0};
  UINT32                DataBitsArray[]   = {7, 8, 0};
  UINT32                StopBitsArray[]   = {OneStopBit, TwoStopBits, 0};

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetAttributesStressTestSub1",
                  L"TDS 5.2.2.1"
                  );
  }

  //
  // For each of standard attributes
  //
  for (Index1 = 0; BaudRateArray[Index1] != 0; Index1++) {
    for (Index2 = 0; FifoDepthArray[Index2] != 0; Index2++) {
      for (Index3 = 0; TimeoutArray[Index3] != 0; Index3++) {
        for (Index4 = 0; ParityArray[Index4] != 0; Index4++) {
          for (Index5 = 0; DataBitsArray[Index5] != 0; Index5++) {
            for (Index6 = 0; StopBitsArray[Index6] != 0; Index6++) {
              //
              // SetAttributes with the standard combination attributes
              //
              ReturnedStatus = SerialIo->SetAttributes (
                                           SerialIo,
                                           BaudRateArray[Index1],
                                           FifoDepthArray[Index2],
                                           TimeoutArray[Index3],
                                           (EFI_PARITY_TYPE)ParityArray[Index4],
                                           (UINT8)DataBitsArray[Index5],
                                           (EFI_STOP_BITS_TYPE)StopBitsArray[Index6]
                                           );
              if ((ReturnedStatus                   == EFI_SUCCESS           ) &&
                  (SerialIo->Mode->BaudRate         <= BaudRateArray[Index1] ) &&
                  (SerialIo->Mode->ReceiveFifoDepth == FifoDepthArray[Index2]) &&
                  (SerialIo->Mode->Timeout          == TimeoutArray[Index3]  ) &&
                  (SerialIo->Mode->Parity           == ParityArray[Index4]   ) &&
                  (SerialIo->Mode->DataBits         == DataBitsArray[Index5] ) &&
                  (SerialIo->Mode->StopBits         == StopBitsArray[Index6] )) {
                Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }

              //
              // SetAttributes with default attributes (restore environment)
              //
              Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);

              //
              // Record assertion & message
              //
              StandardLib->RecordAssertion (
                             StandardLib,
                             Result,
                             gSerialIoBbTestStressAssertionGuid002,
                             L"SerialIo.SetAttributes - With standard combination attributes",
                             L"%a:%d",
                             __FILE__,
                             (UINTN)__LINE__
                             );

              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                             L"Status=%r, Expected=%r\n"
                             L"BaudRate=%ld, Expected=%ld\n"
                             L"ReceiveFifoDepth=%d, Expected=%d\n"
                             L"Timeout=%d, Expected=%d\n"
                             L"Parity=%s, Expected=%s\n"
                             L"DataBits=%d, Expected=%d\n"
                             L"StopBits=%s, Expected=%s\n",
                             ReturnedStatus,                            EFI_SUCCESS,
                             SerialIo->Mode->BaudRate,                  BaudRateArray[Index1],
                             SerialIo->Mode->ReceiveFifoDepth,          FifoDepthArray[Index2],
                             SerialIo->Mode->Timeout,                   TimeoutArray[Index3],
                             gParityString[SerialIo->Mode->Parity],     gParityString[ParityArray[Index4]],
                             SerialIo->Mode->DataBits,                  DataBitsArray[Index5],
                             gStopBitsString[SerialIo->Mode->StopBits], gStopBitsString[StopBitsArray[Index6]]
                             );
            } // StopBits
          } // DataBits
        } // Parity
      } // Timeout
    } // FifoDepth
  } // BaudRate

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetAttributesStressTestSub1",
                  L"TDS 5.2.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetControl with all valid combination control-bits.
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
SetControlStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT32                SxControlBits;
  UINT32                RxControlBits;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetControlStressTestSub1",
                  L"TDS 5.3.2.1"
                  );
  }

  //
  // Walk through all valid combination control-bits
  //
  for (Index = 0; Index < 32; Index++) {
    SxControlBits = 0;

    //
    // Create a valid combination control-bits
    //
    if ((Index & 0x01) != 0) {
      SxControlBits |= EFI_SERIAL_REQUEST_TO_SEND;
    }
    if ((Index & 0x02) != 0) {
      SxControlBits |= EFI_SERIAL_DATA_TERMINAL_READY;
    }
    if ((Index & 0x04) != 0) {
      SxControlBits |= EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE;
    }
    if ((Index & 0x08) != 0) {
      SxControlBits |= EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE;
    }
    if ((Index & 0x10) != 0) {
      SxControlBits |= EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE;
    }

    //
    // SetControl with the combination control-bits
    //
    ReturnedStatus = SerialIo->SetControl (
                                 SerialIo,
                                 SxControlBits
                                 );

    //
    // Get the controlbits for checking results
    //
    Status = SerialIo->GetControl (
                         SerialIo,
                         &RxControlBits
                         );
    if (EFI_ERROR(Status)) {
      Status = SerialIo->Reset (SerialIo);

      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"SerialIo.SetControl - Cannot get control-bits",
                     L"%a:%d: Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      continue;
    }

    if ((ReturnedStatus                  == EFI_SUCCESS  ) &&
        ((RxControlBits & SxControlBits) == SxControlBits)) {
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
                   gSerialIoBbTestStressAssertionGuid003,
                   L"SerialIo.SetControl - With valid combination control-bits",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                   L"Status=%r, Expected=%r\n"
                   L"ControlBits=0x%x, Expected=0x%x\n",
                   ReturnedStatus,                EFI_SUCCESS,
                   RxControlBits & SxControlBits, SxControlBits
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetControlStressTestSub1",
                  L"TDS 5.3.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetControl to check all valid combination control-bits.
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
GetControlStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT32                SxControlBits;
  UINT32                RxControlBits;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetControlStressTestSub1",
                  L"TDS 5.4.2.1"
                  );
  }

  //
  // Walk through all valid combination control-bits
  //
  for (Index = 0; Index < 32; Index++) {
    SxControlBits = 0;

    //
    // Create a valid combination control-bits
    //
    if ((Index & 0x01) != 0) {
      SxControlBits |= EFI_SERIAL_REQUEST_TO_SEND;
    }
    if ((Index & 0x02) != 0) {
      SxControlBits |= EFI_SERIAL_DATA_TERMINAL_READY;
    }
    if ((Index & 0x04) != 0) {
      SxControlBits |= EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE;
    }
    if ((Index & 0x08) != 0) {
      SxControlBits |= EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE;
    }
    if ((Index & 0x10) != 0) {
      SxControlBits |= EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE;
    }

    //
    // SetControl with the combination control-bits
    //
    Status = SerialIo->SetControl (
                         SerialIo,
                         SxControlBits
                         );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"SerialIo.GetControl - Cannot set control-bits",
                     L"%a:%d: Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      continue;
    }

    //
    // Get the control-bits
    //
    ReturnedStatus = SerialIo->GetControl (
                                 SerialIo,
                                 &RxControlBits
                                 );
    if ((ReturnedStatus                  == EFI_SUCCESS  ) &&
        ((RxControlBits & SxControlBits) == SxControlBits)) {
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
                   gSerialIoBbTestStressAssertionGuid004,
                   L"SerialIo.GetControl - Check valid combination control-bits",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                   L"Status=%r, Expected=%r\n"
                   L"ControlBits=0x%x, Expected=0x%x\n",
                   ReturnedStatus,                EFI_SUCCESS,
                   RxControlBits & SxControlBits, SxControlBits
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetControlStressTestSub1",
                  L"TDS 5.4.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Write data in non-loopback mode.
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
WriteStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  EFI_INPUT_KEY         Key;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"WriteStressTestSub1",
                  L"TDS 5.5.2.1"
                  );
  }

  //
  // Set to non-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       0
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot set to non-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteStressTestSub1",
                    L"TDS 5.5.2.1 - Cannot set to non-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Print out message
  //
  SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
  SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
  SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
  SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
  SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
  SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);

  SctPrint (L"Press any key to receive data from serial port...\n");
  gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
  gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

  //
  // Write a block of data to serial port
  //
  BufferSize = MAX_BUFFER_SIZE;
  for (Index = 0; Index < MAX_BUFFER_SIZE; Index++) {
    Buffer[Index] = (UINT8)Index;
  }

  Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
  if (Status == EFI_SUCCESS) {
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
                 gSerialIoBbTestStressAssertionGuid005,
                 L"SerialIo.Write - In non-loopback mode",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                 L"Status=%r, Expected=%r\n",
                 Status,      EFI_SUCCESS
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteStressTestSub1",
                  L"TDS 5.5.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Write data in standard attributes.
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
WriteStressTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINTN                 Index1, Index2, Index3, Index4, Index5, Index6;
  // NOTES: All standard baud rates are made from implementation.
  UINT64                BaudRateArray[]   = {50, 75, 110, 134, 150, 300, 600, 1200, 1800, 2000, 2400, 3600, 4800, 7200, 9600, 19200, 38400, 57600, 115200, 0};
  UINT32                FifoDepthArray[]  = {1, 8, 16, 0};
  UINT32                TimeoutArray[]    = {1, 1000000, 100000000, 0};
  UINT32                ParityArray[]     = {NoParity, EvenParity, OddParity, MarkParity, SpaceParity, 0};
  UINT32                DataBitsArray[]   = {7, 8, 0};
  UINT32                StopBitsArray[]   = {OneStopBit, TwoStopBits, 0};
  EFI_INPUT_KEY         Key;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"WriteStressTestSub2",
                  L"TDS 5.5.2.2"
                  );
  }

  //
  // For each of standard attributes
  //
  for (Index1 = 0; BaudRateArray[Index1] != 0; Index1++) {
    for (Index2 = 0; FifoDepthArray[Index2] != 0; Index2++) {
      for (Index3 = 0; TimeoutArray[Index3] != 0; Index3++) {
        for (Index4 = 0; ParityArray[Index4] != 0; Index4++) {
          for (Index5 = 0; DataBitsArray[Index5] != 0; Index5++) {
            for (Index6 = 0; StopBitsArray[Index6] != 0; Index6++) {
              //
              // SetAttributes with the standard combination attributes
              //
              Status = SerialIo->SetAttributes (
                                   SerialIo,
                                   BaudRateArray[Index1],
                                   FifoDepthArray[Index2],
                                   TimeoutArray[Index3],
                                   (EFI_PARITY_TYPE)ParityArray[Index4],
                                   (UINT8)DataBitsArray[Index5],
                                   (EFI_STOP_BITS_TYPE)StopBitsArray[Index6]
                                   );
              if (EFI_ERROR(Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_WARNING,
                               gTestGenericFailureGuid,
                               L"SerialIo.Write - Cannot set standard combination attributes",
                               L"%a:%d: Status=%r",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status
                               );

                continue;
              }

              //
              // Print out message
              //
              SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
              SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
              SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
              SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
              SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
              SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);
              SctPrint (L"Press any key to receive data from serial port...\n");
              gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
              gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

              //
              // Write a block of data to serial port
              //
              BufferSize = MAX_BUFFER_SIZE;
              for (Index = 0; Index < MAX_BUFFER_SIZE; Index++) {
                Buffer[Index] = (UINT8)Index;
              }

              ReturnedStatus = SerialIo->Write (SerialIo, &BufferSize, Buffer);
              if (ReturnedStatus == EFI_SUCCESS) {
                Result = EFI_TEST_ASSERTION_PASSED;
              } else {
                Result = EFI_TEST_ASSERTION_FAILED;
              }

              //
              // SetAttributes with default attributes (restore environment)
              //
              Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);

              //
              // Record assertion & message
              //
              StandardLib->RecordAssertion (
                             StandardLib,
                             Result,
                             gSerialIoBbTestStressAssertionGuid006,
                             L"SerialIo.Write - With standard combination attributes",
                             L"%a:%d",
                             __FILE__,
                             (UINTN)__LINE__
                             );

              StandardLib->RecordMessage (
                             StandardLib,
                             EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                             L"Status=%r, Expected=%r\n",
                             ReturnedStatus,    EFI_SUCCESS
                             );
            } // StopBits
          } // DataBits
        } // Parity
      } // Timeout
    } //FifoDepth
  } // BaudRate


  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteStressTestSub2",
                  L"TDS 5.5.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Write data multiple times.
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
WriteStressTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINTN                 Index1;
  EFI_INPUT_KEY         Key;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"WriteStressTestSub3",
                  L"TDS 5.5.2.3"
                  );
  }

  //
  // Set to non-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       0
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot set to non-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteStressTestSub3",
                    L"TDS 5.5.2.3 - Cannot set to non-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Write data to serial port multiple times
  //
  for (Index = 0; Index < MULTIPLE_TEST_TIMES; Index++) {
    //
    // Print out message
    //
    SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
    SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
    SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
    SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
    SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
    SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);
    SctPrint (L"Press any key to receive data from serial port...\n");
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

    //
    // Write a block of data to serial port
    //
    BufferSize = MAX_BUFFER_SIZE;
    for (Index1 = 0; Index1 < MAX_BUFFER_SIZE; Index1++) {
      Buffer[Index1] = (UINT8)Index1;
    }

    Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
    if (Status == EFI_SUCCESS) {
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
                   gSerialIoBbTestStressAssertionGuid007,
                   L"SerialIo.Write - In non-loopback mode",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                   L"Index=%d\n"
                   L"Status=%r, Expected=%r\n",
                   Index,
                   Status,      EFI_SUCCESS
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteStressTestSub3",
                  L"TDS 5.5.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Read data in non-loopback mode.
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
ReadStressTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 BufferSize;
  UINTN                 TotalSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  EFI_INPUT_KEY         Key;
  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ReadStressTestSub1",
                  L"TDS 5.6.2.1"
                  );
  }

  //
  // Set to non-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       0
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to non-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadStressTestSub1",
                    L"TDS 5.6.2.1 - Cannot set to non-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Print out message
  //
  SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
  SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
  SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
  SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
  SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
  SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);
  SctPrint (L"Please send data to serial port and confirm by stroke a key...\n");

  gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
  gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

  //
  // Read a block of data from serial port
  //
  TotalSize = 0;

  while (TotalSize < MAX_BUFFER_SIZE) {
    //
    // Read data from serial port
    //
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if ((Status == EFI_SUCCESS) || (Status == EFI_TIMEOUT)) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    TotalSize += BufferSize;

    //
    // Record assertion & message
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gSerialIoBbTestStressAssertionGuid008,
                   L"SerialIo.Read - In non-loopback mode",
                   L"%a:%d: Total received=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TotalSize
                   );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                   L"Status=%r, Expected=%r or %r\n",
                   Status,      EFI_SUCCESS,      EFI_TIMEOUT
                   );

    if (LoggingLib != NULL) {
      LoggingLib->DumpBuf (
                    LoggingLib,
                    EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                    (CHAR16 *)Buffer,
                    (UINT32)((BufferSize + 1) / 2),
                    EFI_DUMP_HEX
                    );
    }
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadStressTestSub1",
                  L"TDS 5.6.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Reset the serial device multiple times.
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
ReadStressTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index1, Index2, Index3, Index4, Index5, Index6;
  // NOTES: All standard baud rates are made from implementation.
  UINT64                BaudRateArray[]   = {50, 75, 110, 134, 150, 300, 600, 1200, 1800, 2000, 2400, 3600, 4800, 7200, 9600, 19200, 38400, 57600, 115200, 0};
  UINT32                FifoDepthArray[]  = {1, 8, 16, 0};
  UINT32                TimeoutArray[]    = {1, 1000000, 100000000, 0};
  UINT32                ParityArray[]     = {NoParity, EvenParity, OddParity, MarkParity, SpaceParity, 0};
  UINT32                DataBitsArray[]   = {7, 8, 0};
  UINT32                StopBitsArray[]   = {OneStopBit, TwoStopBits, 0};
  UINTN                 BufferSize;
  UINTN                 TotalSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  EFI_INPUT_KEY         Key;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ReadStressTestSub2",
                  L"TDS 5.5.2.2"
                  );
  }

  //
  // For each of standard attributes
  //
  for (Index1 = 0; BaudRateArray[Index1] != 0; Index1++) {
    for (Index2 = 0; FifoDepthArray[Index2] != 0; Index2++) {
      for (Index3 = 0; TimeoutArray[Index3] != 0; Index3++) {
        for (Index4 = 0; ParityArray[Index4] != 0; Index4++) {
          for (Index5 = 0; DataBitsArray[Index5] != 0; Index5++) {
            for (Index6 = 0; StopBitsArray[Index6] != 0; Index6++) {
              //
              // SetAttributes with the standard combination attributes
              //
              Status = SerialIo->SetAttributes (
                                   SerialIo,
                                   BaudRateArray[Index1],
                                   FifoDepthArray[Index2],
                                   TimeoutArray[Index3],
                                   (EFI_PARITY_TYPE)ParityArray[Index4],
                                   (UINT8)DataBitsArray[Index5],
                                   (EFI_STOP_BITS_TYPE)StopBitsArray[Index6]
                                   );
              if (EFI_ERROR(Status)) {
                StandardLib->RecordAssertion (
                               StandardLib,
                               EFI_TEST_ASSERTION_WARNING,
                               gTestGenericFailureGuid,
                               L"SerialIo.Read - Cannot set standard combination attributes",
                               L"%a:%d: Status=%r",
                               __FILE__,
                               (UINTN)__LINE__,
                               Status
                               );

                continue;
              }

              //
              // Print out message
              //
              SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
              SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
              SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
              SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
              SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
              SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);
              SctPrint (L"Please send data to serial port and confirm by key stroke...\n");
              gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
              gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
              //
              // Read a block of data from serial port
              //
              TotalSize = 0;

              while (TotalSize < MAX_BUFFER_SIZE) {
                //
                // Read data from serial port
                //
                BufferSize = MAX_BUFFER_SIZE;
                Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
                if ((Status == EFI_SUCCESS) || (Status == EFI_TIMEOUT)) {
                  Result = EFI_TEST_ASSERTION_PASSED;
                } else {
                  Result = EFI_TEST_ASSERTION_FAILED;
                }

                TotalSize += BufferSize;

                //
                // NOTES: DON'T set to default attributes at here. Tester can
                // send a file and receive the log message at a same attributes.
                //

                //
                // Record assertion & message
                //
                StandardLib->RecordAssertion (
                               StandardLib,
                               Result,
                               gSerialIoBbTestStressAssertionGuid009,
                               L"SerialIo.Read - With standard combination attributes",
                               L"%a:%d: Total received=%d",
                               __FILE__,
                               (UINTN)__LINE__,
                               TotalSize
                               );

                StandardLib->RecordMessage (
                               StandardLib,
                               EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                               L"Status=%r, Expected=%r or %r\n",
                               Status,  EFI_SUCCESS,  EFI_TIMEOUT
                               );

                if (LoggingLib != NULL) {
                  LoggingLib->DumpBuf (
                                LoggingLib,
                                EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                                (CHAR16 *)Buffer,
                                (UINT32)((BufferSize + 1) / 2),
                                EFI_DUMP_HEX
                                );
                }
              }
            } // StopBits
          } // DataBits
        } // Parity
      } // Timeout
    } //FifoDepth
  } // BaudRate

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
                  L"ReadStressTestSub2",
                  L"TDS 5.6.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Read data multiple times.
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
ReadStressTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINTN                 BufferSize;
  UINTN                 TotalSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];
  UINTN                 WaitIndex;
  EFI_INPUT_KEY         Key;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ReadStressTestSub3",
                  L"TDS 5.6.2.3"
                  );
  }

  //
  // Set to non-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       0
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Read - Cannot set to non-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"ReadStressTestSub3",
                    L"TDS 5.6.2.3 - Cannot set to non-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Read data from serial port multiple times
  //
  for (Index = 0; Index < MULTIPLE_TEST_TIMES; Index++) {
    //
    // Print out message
    //
    SctPrint (L"BaudRate         = %d\n", SerialIo->Mode->BaudRate);
    SctPrint (L"ReceiveFifoDepth = %d\n", SerialIo->Mode->ReceiveFifoDepth);
    SctPrint (L"Timeout          = %d\n", SerialIo->Mode->Timeout);
    SctPrint (L"Parity           = %s\n", gParityString[SerialIo->Mode->Parity]);
    SctPrint (L"DataBits         = %d\n", SerialIo->Mode->DataBits);
    SctPrint (L"StopBits         = %s\n", gStopBitsString[SerialIo->Mode->StopBits]);
    SctPrint (L"Please send data to serial port and confirm by key stroke...\n");
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    //
    // Read a block of data from serial port
    //
    TotalSize = 0;

    while (TotalSize < MAX_BUFFER_SIZE) {
      //
      // Read data from serial port
      //
      BufferSize = MAX_BUFFER_SIZE;
      Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
      if ((Status == EFI_SUCCESS) || (Status == EFI_TIMEOUT)) {
        Result = EFI_TEST_ASSERTION_PASSED;
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
      }

      TotalSize += BufferSize;

      //
      // NOTES: DON'T set to default attributes at here. Tester can send a file
      // and receive the log message at a same attributes.
      //

      //
      // Record assertion & message
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     Result,
                     gSerialIoBbTestStressAssertionGuid010,
                     L"SerialIo.Read - In non-loopback mode",
                     L"%a:%d: Total received=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TotalSize
                     );

      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                     L"Status=%r, Expected=%r or %r\n",
                     Status,  EFI_SUCCESS,  EFI_TIMEOUT
                     );

      if (LoggingLib != NULL) {
        LoggingLib->DumpBuf (
                      LoggingLib,
                      EFI_VERBOSE_LEVEL_EXHAUSTIVE,
                      (CHAR16 *)Buffer,
                      (UINT32)((BufferSize + 1) / 2),
                      EFI_DUMP_HEX
                      );
      }
    }
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadStressTestSub3",
                  L"TDS 5.6.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
