/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  SerialIoBbTestFunction.c

Abstract:
  Source file for Serial IO Protocol Black-Box Test - Function Test.

--*/

#include "SctLib.h"
#include "SerialIoBbTestMain.h"

//
// Prototypes (external)
//

EFI_STATUS
ResetFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
SetAttributesFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
SetControlFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
GetControlFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
WriteFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
ReadFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes (internal)
//

EFI_STATUS
ResetFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetAttributesFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetAttributesFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetAttributesFuncTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetControlFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetControlFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
WriteFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
WriteFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
WriteFuncTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
ReadFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
ReadFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

//
// Functions
//

/**
 *  TDS 3.1 - Entry Point for SerialIo->Reset() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
ResetFuncTest (
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
  // Reset the serial device
  //
  Status = ResetFuncTestSub1 (
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
 *  TDS 3.2 - Entry Point for SerialIo->SetAttributes() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
SetAttributesFuncTest (
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
  // SetAttributes with standard attributes
  //
  Status = SetAttributesFuncTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // SetAttributes with default attributes
  //
  Status = SetAttributesFuncTestSub2 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // SetAttributes with nonstandard attributes
  //
#if 0  
  Status = SetAttributesFuncTestSub3 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );
#endif
  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 3.3 - Entry Point for SerialIo->SetControl() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
SetControlFuncTest (
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
  // SetControl with valid control-bits
  //
  Status = SetControlFuncTestSub1 (
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
 *  TDS 3.4 - Entry Point for SerialIo->GetControl() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
GetControlFuncTest (
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
  // GetControl to check valid control-bits
  //
  Status = GetControlFuncTestSub1 (
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
 *  TDS 3.5 - Entry Point for SerialIo->Write() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
WriteFuncTest (
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
  // Write data in software-loopback mode
  //
  Status = WriteFuncTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Write data in hardware-loopback mode
  //
  Status = WriteFuncTestSub2 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Write data in non-loopback mode
  //
  Status = WriteFuncTestSub3 (
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
 *  TDS 3.6 - Entry Point for SerialIo->Read() Function Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
ReadFuncTest (
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
  // Read data in software-loopback mode
  //
  Status = ReadFuncTestSub1 (
             (EFI_SERIAL_IO_PROTOCOL *)ClientInterface,
             StandardLib,
             LoggingLib
             );

  //
  // Read data in hardware-loopback mode
  //
  Status = ReadFuncTestSub2 (
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
 *  Reset the serial device.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
ResetFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"ResetFuncTestSub1",
                  L"TDS 3.1.2.1"
                  );
  }

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
                 gSerialIoBbTestFunctionAssertionGuid001,
                 L"SerialIo.Reset - Reset the serial device",
                 L"%a:%d: Return Status - %r, Expected - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ResetFuncTestSub1",
                  L"TDS 3.1.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetAttributes with standard attributes.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetAttributesFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT64                BaudRateArray[]   = {115200, 0};
  //UINT32                FifoDepthArray[]  = {1, 8, 16, 0};
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
                  L"SetAttributesFuncTestSub1",
                  L"TDS 3.2.2.1"
                  );
  }

  //
  // Set standard attributes - BaudRate
  //
  for (Index = 0; BaudRateArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 BaudRateArray[Index],
                                 0,                       // ReceiveFifoDepth
                                 0,                       // Timeout
                                 0,                       // Parity
                                 0,                       // DataBits
                                 0                        // StopBits
                                 );
    if ((ReturnedStatus           == EFI_SUCCESS         ) &&
        (SerialIo->Mode->BaudRate == BaudRateArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid002,
                   L"SerialIo.SetAttributes - With standard BaudRate",
                   L"%a:%d: Status=%r, Expected=%r, BaudRate=%ld, Expected=%ld",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   SerialIo->Mode->BaudRate,
                   BaudRateArray[Index]
                   );


    //
    // SetAttributes with default attributes (restore environment)
    //
    Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);
	
  }

#if 0
  //
  // Set standard attributes - ReceiveFifoDepth
  //
  for (Index = 0; FifoDepthArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 0,                       // BaudRate
                                 FifoDepthArray[Index],
                                 0,                       // Timeout
                                 0,                       // Parity
                                 0,                       // DataBits
                                 0                        // StopBits
                                 );
    if (ReturnedStatus == EFI_SUCCESS) {
      if (SerialIo->Mode->ReceiveFifoDepth == FifoDepthArray[Index]) {
        Result = EFI_TEST_ASSERTION_PASSED;
      } else {
        Result = EFI_TEST_ASSERTION_FAILED;
      }
    } else if (ReturnedStatus != EFI_INVALID_PARAMETER || ReturnedStatus != EFI_DEVICE_ERROR) {
      Result = EFI_TEST_ASSERTION_FAILED;
    } else {
      Result = EFI_TEST_ASSERTION_PASSED;
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
                   gSerialIoBbTestFunctionAssertionGuid003,
                   L"SerialIo.SetAttributes - With standard ReceiveFifoDepth",
                   L"%a:%d: Status=%r, Expected=%r, ReceiveFifoDepth=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   SerialIo->Mode->ReceiveFifoDepth,
                   FifoDepthArray[Index]
                   );
  }
#endif  

  //
  // Set standard attributes - Timeout
  //
  for (Index = 0; TimeoutArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 0,                       // BaudRate
                                 0,                       // ReceiveFifoDepth
                                 TimeoutArray[Index],
                                 0,                       // Parity
                                 0,                       // DataBits
                                 0                        // StopBits
                                 );
    if ((ReturnedStatus          == EFI_SUCCESS        ) &&
        (SerialIo->Mode->Timeout == TimeoutArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid004,
                   L"SerialIo.SetAttributes - With standard Timeout",
                   L"%a:%d: Status=%r, Expected=%r, Timeout=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   SerialIo->Mode->Timeout,
                   TimeoutArray[Index]
                   );

    //
    // SetAttributes with default attributes (restore environment)
    //
    Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);
	
  }

  //
  // Set standard attributes - Parity
  //
  for (Index = 0; ParityArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 0,                       // BaudRate
                                 0,                       // ReceiveFifoDepth
                                 0,                       // Timeout
                                 (EFI_PARITY_TYPE)ParityArray[Index],
                                 0,                       // DataBits
                                 0                        // StopBits
                                 );
    if ((ReturnedStatus         == EFI_SUCCESS       ) &&
        (SerialIo->Mode->Parity == ParityArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid005,
                   L"SerialIo.SetAttributes - With standard Parity",
                   L"%a:%d: Status=%r, Expected=%r, Parity=%s, Expected=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   gParityString[SerialIo->Mode->Parity],
                   gParityString[ParityArray[Index]]
                   );

    //
    // SetAttributes with default attributes (restore environment)
    //
    Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);	
  }

  //
  // Set standard attributes - DataBits
  //
  for (Index = 0; DataBitsArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 0,                       // BaudRate
                                 0,                       // ReceiveFifoDepth
                                 0,                       // Timeout
                                 0,                       // Parity
                                 (UINT8)DataBitsArray[Index],
                                 0                        // StopBits
                                 );
    if ((ReturnedStatus           == EFI_SUCCESS         ) &&
        (SerialIo->Mode->DataBits == DataBitsArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid006,
                   L"SerialIo.SetAttributes - With standard DataBits",
                   L"%a:%d: Status=%r, Expected=%r, DataBits=%d, Expected=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   SerialIo->Mode->DataBits,
                   DataBitsArray[Index]
                   );

    //
    // SetAttributes with default attributes (restore environment)
    //
    Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);

  }

  //
  // Set standard attributes - StopBits
  //
  for (Index = 0; StopBitsArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 0,                       // BaudRate
                                 0,                       // ReceiveFifoDepth
                                 0,                       // Timeout
                                 0,                       // Parity
                                 0,                       // DataBits
                                 (EFI_STOP_BITS_TYPE)StopBitsArray[Index]
                                 );
    if ((ReturnedStatus           == EFI_SUCCESS         ) &&
        (SerialIo->Mode->StopBits == StopBitsArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid007,
                   L"SerialIo.SetAttributes - With standard StopBits",
                   L"%a:%d: Status=%r, Expected=%r, StopBits=%s, Expected=%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   gStopBitsString[SerialIo->Mode->StopBits],
                   gStopBitsString[StopBitsArray[Index]]
                   );

    //
    // SetAttributes with default attributes (restore environment)
    //
    Status = SerialIo->SetAttributes (SerialIo, 0, 0, 0, 0, 0, 0);

  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetAttributesFuncTestSub1",
                  L"TDS 3.2.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetAttributes with default attributes.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetAttributesFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINT64                DefaultBaudRate   = 115200;
  UINT32                DefaultFifoDepth  = 1;
  UINT32                DefaultTimeout    = 1000000;
  UINT32                DefaultParity     = NoParity;
  UINT32                DefaultDataBits   = 8;
  UINT32                DefaultStopBits   = OneStopBit;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetAttributesFuncTestSub2",
                  L"TDS 3.2.2.2"
                  );
  }

  //
  // Set default attributes
  //
  ReturnedStatus = SerialIo->SetAttributes (
                               SerialIo,
                               DefaultBaudRate,
                               DefaultFifoDepth,
                               DefaultTimeout,
                               (EFI_PARITY_TYPE)DefaultParity,
                               (UINT8)DefaultDataBits,
                               (EFI_STOP_BITS_TYPE)DefaultStopBits
                               );
  if ((ReturnedStatus                   == EFI_SUCCESS     ) &&
      (SerialIo->Mode->BaudRate         == DefaultBaudRate ) &&
      (SerialIo->Mode->ReceiveFifoDepth == DefaultFifoDepth) &&
      (SerialIo->Mode->Timeout          == DefaultTimeout  ) &&
      (SerialIo->Mode->Parity           == DefaultParity   ) &&
      (SerialIo->Mode->DataBits         == DefaultDataBits ) &&
      (SerialIo->Mode->StopBits         == DefaultStopBits )) {
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
                 gSerialIoBbTestFunctionAssertionGuid008,
                 L"SerialIo.SetAttributes - With default attributes",
                 L"%a:%d: Status=%r, Expected=%r, "
                 L"BaudRate=%ld, Expected=%ld, "
                 L"ReceiveFiFoDepth=%d, Expected=%d "
                 L"Timeout=%d, Expected=%d "
                 L"Parity=%s, Expected=%s "
                 L"DataBits=%d, Expected=%d "
                 L"StopBits=%s, Expected=%s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,                            EFI_SUCCESS,
                 SerialIo->Mode->BaudRate,                  DefaultBaudRate,
                 SerialIo->Mode->ReceiveFifoDepth,          DefaultFifoDepth,
                 SerialIo->Mode->Timeout,                   DefaultTimeout,
                 gParityString[SerialIo->Mode->Parity],     gParityString[DefaultParity],
                 SerialIo->Mode->DataBits,                  DefaultDataBits,
                 gStopBitsString[SerialIo->Mode->StopBits], gStopBitsString[DefaultStopBits]
                 );

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
                  L"SetAttributesFuncTestSub2",
                  L"TDS 3.2.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetAttributes with nonstandard attributes.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetAttributesFuncTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT64                BaudRateArray[]         = {19200+1, 38400+1, 48000, 57600-1, 57600+1, 86400, 115200-1, 115200+1, 0};
  UINT64                StandardBaudRateArray[] = {19200,   38400,   38400, 38400,   57600,   57600, 57600,    115200,   0};

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetAttributesFuncTestSub3",
                  L"TDS 3.2.2.3"
                  );
  }

  //
  // Set nonstandard attributes - BaudRate
  //
  for (Index = 0; BaudRateArray[Index] != 0; Index++) {
    ReturnedStatus = SerialIo->SetAttributes (
                                 SerialIo,
                                 BaudRateArray[Index],
                                 0,                       // ReceiveFifoDepth
                                 0,                       // Timeout
                                 0,                       // Parity
                                 0,                       // DataBits
                                 0                        // StopBits
                                 );
    if ((ReturnedStatus           == EFI_SUCCESS                 ) &&
        (SerialIo->Mode->BaudRate == StandardBaudRateArray[Index])) {
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
                   gSerialIoBbTestFunctionAssertionGuid009,
                   L"SerialIo.SetAttributes - With nonstandard BaudRate",
                   L"%a:%d: Status=%r, Expected=%r, BaudRate=%ld, Expected=%ld",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,            EFI_SUCCESS,
                   SerialIo->Mode->BaudRate,  StandardBaudRateArray[Index]
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetAttributesFuncTestSub3",
                  L"TDS 3.2.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetControl with valid control-bits.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetControlFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            TempStatus;
  EFI_STATUS            ReturnedStatus;
  EFI_TEST_ASSERTION    Result;
  UINTN                 Index;
  UINT32                SxControlBits;
  UINT32                RxControlBits;

  //
  // UEFI 2.0 spec does not require all control bits can be set. From
  // investigation, we think only SEND and READY control bit may required.
  //
  UINT32                ValidControlBits = EFI_SERIAL_REQUEST_TO_SEND |
                                           EFI_SERIAL_DATA_TERMINAL_READY;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetControlFuncTestSub1",
                  L"TDS 3.3.2.1"
                  );
  }

  //
  // Walk through all 32 control-bits
  //
  for (Index = 0; Index < 32; Index++) {
    SxControlBits = 1 << Index;

    //
    // Skip invalid ControlBits
    //
    if ((SxControlBits & ValidControlBits) == 0) {
      continue;
    }

    //
    // SetControl with valid control-bits
    //
    ReturnedStatus = SerialIo->SetControl (
                                 SerialIo,
                                 SxControlBits
                                 );

    //
    // Get the control-bits for checking results
    //
    Status = SerialIo->GetControl (
                         SerialIo,
                         &RxControlBits
                         );
    if (EFI_ERROR(Status)) {
      TempStatus = SerialIo->Reset (SerialIo);

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
                   gSerialIoBbTestFunctionAssertionGuid010,
                   L"SerialIo.SetControl - With valid control-bits",
                   L"%a:%d: Status=%r, Expected=%r, ControlBits=0x%x, Expected=0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   RxControlBits & SxControlBits,
                   SxControlBits
                   );
  }

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetControlFuncTestSub1",
                  L"TDS 3.3.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetControl to check valid control-bits.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetControlFuncTestSub1 (
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
  UINTN                 Index;
  UINT32                SxControlBits;
  UINT32                RxControlBits;

  //
  // UEFI 2.0 spec does not require all control bits can be set. From
  // investigation, we think only SEND and READY control bit may required.
  //
  UINT32                ValidControlBits = EFI_SERIAL_REQUEST_TO_SEND |
                                           EFI_SERIAL_DATA_TERMINAL_READY;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetControlFuncTestSub1",
                  L"TDS 3.4.2.1"
                  );
  }

  //
  // Walk through all 32 control-bits
  //
  for (Index = 0; Index < 32; Index++) {
    SxControlBits = 1 << Index;

    //
    // Skip invalid ControlBits
    //
    if ((SxControlBits & ValidControlBits) == 0) {
      continue;
    }

    //
    // Set ControlBits with valid control-bits
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
                   gSerialIoBbTestFunctionAssertionGuid011,
                   L"SerialIo.GetControl - Check valid control-bits",
                   L"%a:%d: Status=%r, Expected=%r, ControlBits=0x%x, Expected=0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   ReturnedStatus,
                   EFI_SUCCESS,
                   RxControlBits & SxControlBits,
                   SxControlBits
                   );
  }

  //
  // Clean up all data in input buffer
  //
  // NOTES: DON'T remove below codes. Record assertion or message maybe write
  // data to serial port.
  //
  Status = SerialIo->Reset (SerialIo);

  while (TRUE) {
    BufferSize = MAX_BUFFER_SIZE;
    Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
      break;
    }
  }
      //
    // Get the control-bits
    //
  ReturnedStatus = SerialIo->GetControl (
                               SerialIo,
                               &RxControlBits
                               );
  if ((ReturnedStatus                  == EFI_SUCCESS  ) &&
      ((RxControlBits & EFI_SERIAL_INPUT_BUFFER_EMPTY) != 0)) {
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
                 gSerialIoBbTestFunctionAssertionGuid017,
                 L"SerialIo.GetControl - Check valid control-bits EFI_SERIAL_INPUT_BUFFER_EMPTY",
                 L"%a:%d: Status=%r, Expected=%r, ControlBits=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,
                 EFI_SUCCESS,
                 RxControlBits & EFI_SERIAL_INPUT_BUFFER_EMPTY,
                 EFI_SERIAL_INPUT_BUFFER_EMPTY
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetControlFuncTestSub1",
                  L"TDS 3.4.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Write data in software-loopback mode.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
WriteFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            TempStatus;
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
                  L"WriteFuncTestSub1",
                  L"TDS 3.5.2.1"
                  );
  }

  //
  // Set to software-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot set to software-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteFuncTestSub1",
                    L"TDS 3.5.2.1 - Cannot set to software-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in input buffer
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
  // Write one byte to serial port (NOTES: more bytes are device specific and
  // implementation specific.)
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  ReturnedStatus = SerialIo->Write (SerialIo, &BufferSize, Buffer);

  //
  // Read the byte from serial port
  //
  BufferSize = 1;
  Buffer[0]  = 0x00;
  Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    TempStatus = SerialIo->Reset (SerialIo);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot read data from serial port",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteFuncTestSub1",
                    L"TDS 3.5.2.1 - Cannot read data from serial port"
                    );
    }

    return Status;
  }

  if ((ReturnedStatus == EFI_SUCCESS) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )) {
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
                 gSerialIoBbTestFunctionAssertionGuid012,
                 L"SerialIo.Write - In software-loopback mode",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,      EFI_SUCCESS,
                 BufferSize,          1,
                 Buffer[0],           0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteFuncTestSub1",
                  L"TDS 3.5.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Write data in hardware-loopback mode.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
WriteFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            TempStatus;
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
                  L"WriteFuncTestSub2",
                  L"TDS 3.5.2.2"
                  );
  }

  //
  // Set to hardware-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot set to hardware-loopback mode",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteFuncTestSub2",
                    L"TDS 3.5.2.2 - Cannot set to hardware-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in input buffer
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
  // Write one byte to serial port (NOTES: more bytes are device specific and
  // implementation specific.)
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  ReturnedStatus = SerialIo->Write (SerialIo, &BufferSize, Buffer);

  //
  // Read the byte from serial port
  //
  BufferSize = 1;
  Buffer[0]  = 0x00;
  Status = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    TempStatus = SerialIo->Reset (SerialIo);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"SerialIo.Write - Cannot read data from serial port",
                   L"%a:%d: Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"WriteFuncTestSub2",
                    L"TDS 3.5.2.2 - Cannot read data from serial port"
                    );
    }

    return Status;
  }

  if ((ReturnedStatus == EFI_SUCCESS) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )) {
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
                 gSerialIoBbTestFunctionAssertionGuid013,
                 L"SerialIo.Write - In hardware-loopback mode",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,      EFI_SUCCESS,
                 BufferSize,          1,
                 Buffer[0],           0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteFuncTestSub2",
                  L"TDS 3.5.2.2"
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
WriteFuncTestSub3 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 BufferSize;
  UINT8                 Buffer[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"WriteFuncTestSub3",
                  L"TDS 3.5.2.3"
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
                    L"WriteFuncTestSub3",
                    L"TDS 3.5.2.3 - Cannot set to non-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Write one byte to serial port
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
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
                 gSerialIoBbTestFunctionAssertionGuid014,
                 L"SerialIo.Write - In non-loopback mode",
                 L"%a:%d: Status=%r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"WriteFuncTestSub3",
                  L"TDS 3.5.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Read data in software-loopback mode.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
ReadFuncTestSub1 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            TempStatus;
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
                  L"ReadFuncTestSub1",
                  L"TDS 3.6.2.1"
                  );
  }

  //
  // Set to software-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
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
                    L"ReadFuncTestSub1",
                    L"TDS 3.6.2.1 - Cannot set to software-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in input buffer
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
  // Write one byte to serial port (NOTES: more bytes are device specific and
  // implementation specific.)
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    TempStatus = SerialIo->Reset (SerialIo);

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
                    L"ReadFuncTestSub1",
                    L"TDS 3.6.2.1 - Cannot write a byte to serial port"
                    );
    }

    return Status;
  }

  //
  // Read the byte from serial port
  //
  BufferSize = 1;
  Buffer[0]  = 0x00;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_SUCCESS) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )) {
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
                 gSerialIoBbTestFunctionAssertionGuid015,
                 L"SerialIo.Read - In software-loopback mode",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,    EFI_SUCCESS,
                 BufferSize,        1,
                 Buffer[0],         0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadFuncTestSub1",
                  L"TDS 3.6.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Read data in hardware-loopback mode.
 *  @param SerialIo     A pointer to EFI_SERIAL_IO_PROTOCOL instance.
 *  @param StandardLib  A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                      instance.
 *  @param LoggingLib   A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                      instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
ReadFuncTestSub2 (
  IN EFI_SERIAL_IO_PROTOCOL               *SerialIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_STATUS            TempStatus;
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
                  L"ReadFuncTestSub2",
                  L"TDS 3.6.2.2"
                  );
  }

  //
  // Set to hardware-loopback mode
  //
  Status = SerialIo->SetControl (
                       SerialIo,
                       EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE
                       );
  if (EFI_ERROR(Status)) {
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
                    L"ReadFuncTestSub2",
                    L"TDS 3.6.2.2 - Cannot set to hardware-loopback mode"
                    );
    }

    return Status;
  }

  //
  // Clean up all data in input buffer
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
  // Write one byte to serial port (NOTES: more bytes are device specific and
  // implementation specific.)
  //
  BufferSize = 1;
  Buffer[0]  = 0x5A;
  Status = SerialIo->Write (SerialIo, &BufferSize, Buffer);
  if (EFI_ERROR(Status)) {
    TempStatus = SerialIo->Reset (SerialIo);

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
                    L"ReadFuncTestSub2",
                    L"TDS 3.6.2.2 - Cannot write a byte to serial port"
                    );
    }

    return Status;
  }

  //
  // Read the byte from serial port
  //
  BufferSize = 1;
  Buffer[0]  = 0x00;
  ReturnedStatus = SerialIo->Read (SerialIo, &BufferSize, Buffer);
  if ((ReturnedStatus == EFI_SUCCESS) &&
      (BufferSize     == 1          ) &&
      (Buffer[0]      == 0x5A       )) {
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
                 gSerialIoBbTestFunctionAssertionGuid016,
                 L"SerialIo.Read - In hardware-loopback mode",
                 L"%a:%d: Status=%r, Expected=%r, BufferSize=%d, Expected=%d, Buffer=0x%x, Expected=0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 ReturnedStatus,    EFI_SUCCESS,
                 BufferSize,        1,
                 Buffer[0],         0x5A
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"ReadFuncTestSub2",
                  L"TDS 3.6.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
