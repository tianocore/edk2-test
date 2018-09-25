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
  
    EmsLogUtility.h
    
Abstract:

    Incude header files for log utility
    
--*/

#ifndef __EMS_LOG_UTILITY_H__
#define __EMS_LOG_UTILITY_H__

#include "EmsMain.h"
#include "Tcl.h"

//
// definition
//
#define EMS_TEST_REVISION               0x00010000
#define EMS_MAX_PRINT_BUFFER            4096
#define EMS_OVERALL_DIR                 "Overall"
#define EMS_OVERALL_FILE                "Summary"
#define EMS_LOG_DIR                     "Log"

#define DEFAULT_CASE_NAME               "DefaultCaseName"
#define DEFAULT_CASE_CATEGORY           "DefaultCaseCategory"
#define EMS_DEFAULT_CASE_INDEX          "DefaultCaseIndex"
#define DEFAULT_CASE_DESCRIPTION        "Default case Description"

#define LEFT_JUSTIFY                    0x01
#define PREFIX_SIGN                     0x02
#define PREFIX_BLANK                    0x04
#define COMMA_TYPE                      0x08
#define LONG_TYPE                       0x10
#define PREFIX_ZERO                     0x20

#define EMS_DRIVER_LIB_MAX_PRINT_BUFFER (80 * 4)

#define EMS_TEST_LEVEL_MINIMAL          0x01
#define EMS_TEST_LEVEL_DEFAULT          0x02
#define EMS_TEST_LEVEL_EXHAUSTIVE       0x04

#define EMS_CASE_ATTRIBUTE_AUTO         0x00
#define EMS_CASE_ATTRIBUTE_MANUAL       0x01

#define BASE_YEAR                       1970

#define MINS_PER_HOUR                   60
#define HOURS_PER_DAY                   24
#define SECS_PER_MIN                    60
#define SECS_PER_HOUR                   (SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY                    (SECS_PER_HOUR * HOURS_PER_DAY)
#define DAYS_PER_NYEAR                  365
#define DAYS_PER_LYEAR                  366

#define IS_LEAP(y)                      (((((y) % 4) == 0) && (((y) % 100) != 0)) || (((y) % 400) == 0))

#define GenericGuid                     "00000000-0000-0000-0000-000000000000"

//
// test assertion type
//
typedef enum {
  EMS_TEST_ASSERTION_PASSED,
  EMS_TEST_ASSERTION_WARNING,
  EMS_TEST_ASSERTION_FAILED
} EmsTestAssertion;

//
// verbose level type
//
typedef enum {
  EMS_VERBOSE_LEVEL_QUIET,
  EMS_VERBOSE_LEVEL_MINIMAL,
  EMS_VERBOSE_LEVEL_DEFAULT,
  EMS_VERBOSE_LEVEL_NOISY,
  EMS_VERBOSE_LEVEL_EXHAUSTIVE
} EmsVerboseLevel;

//
// test level type
//
typedef UINT32 EmsTestLevel;

//
// case attribute type
//
typedef UINT32 EmsCaseAttribute;

//
// test case configuration information
//
typedef struct {
  INT8              *CaseName;
  INT8              *CaseCategory;
  INT8              *CaseDescription;
  INT8              *CaseIndex;
  EmsTestLevel      TestLevel;
  EmsCaseAttribute  CaseAttribute;
  EmsVerboseLevel   VerboseLevel;
  EFI_GUID          Guid;
} EMS_CASE_CONFIG;

//
// private data definition for EMS test case
//
typedef struct {
  UINT32            TestRevision;
  INT8              *CaseName;
  INT8              *CaseCategory;
  INT8              *CaseDescription;
  INT8              *CaseIndex;
  UINT32            PassCount;
  UINT32            WarnCount;
  UINT32            FailCount;
  INT8              *CaseStatus;
  EFI_STATUS        TestStatus;
  EFI_TIME          StartTime;
  EFI_TIME          EndTime;
  FILE              *SummaryLog;
  FILE              *SummaryKey;
  FILE              *CaseLog;
  FILE              *CaseKey;
  EmsTestLevel      TestLevel;
  EmsCaseAttribute  CaseAttribute;
  EmsVerboseLevel   VerboseLevel;
  EFI_GUID          Guid;
} EMS_PRIVATE;

//
// EMS assertion information data strucuture
//
typedef struct _EMS_ASSERTION_INFOR {
  struct _EMS_ASSERTION_INFOR *Next;
  struct _EMS_ASSERTION_INFOR *Prev;

  EmsTestAssertion            TestAssertionType;
  INT8                        *Guid;  // insert guid item
  INT8                        *Description;
  INT8                        *Detail;
} EMS_ASSERTION_INFOR;

//
// EMS library RecordAssertion API
//
EFI_STATUS
RecordAssertion (
  EmsTestAssertion     TestAssertionType,
  INT8                 *Guid,
  INT8                 *Description,
  INT8                 *Detail,
  ...
  )
/*++

Routine Description:

  Record a test assertion to log file

Arguments:

  TestAssertionType - Assertion type.
  Guid              - Assertion guid.
  Description       - The assertion description.
  Detail            - The detail runtime information.
  ...               - Variable parameters.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
;

//
// EMS library RecordMessage API
//
EFI_STATUS
RecordMessage (
  EmsVerboseLevel      VerboseLevel,
  INT8                 *Message,
  ...
  )
/*++

Routine Description:

  record message to log file

Arguments:

  VerboseLevel  - The level of the verbose
  Message       - The message data
  ...           - Variable parameters.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
;

EFI_STATUS
RecordMessageAgent (
  EmsVerboseLevel      VerboseLevel,
  INT8                 *Message,
  ...
  )
/*++

Routine Description:

  record message to log file for agent side only

Arguments:

  VerboseLevel  - The level of the verbose
  Message       - The message data
  ...           - Variable parameters.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
;

INT32
BeginLogging (
  VOID_P
  )
/*++

Routine Description:

  the begin logging process, include create log files, record head infor

Arguments:

  None

Returns:

  EFI_SUCCESS   - Successfully.

--*/
;

EFI_STATUS
EndLogging (
  EFI_STATUS           TestStatus
  )
/*++

Routine Description:

  the end logging process, include record term infor, close log files

Arguments:

  TestStatus  - the test exit status

Returns:

  EFI_SUCCESS   - Successfully.

--*/
;


EFI_STATUS
SetConfig (
  EMS_CASE_CONFIG      CaseConfig
  )
/*++

Routine Description:

  set the case private config information

Arguments:

  CaseConfig  - the case config information

Returns:

  EFI_SUCCESS   - Successfully.

--*/
;

UINT32
Sprint (
  INT8                 *Buffer,
  UINT32               BufferSize,
  INT8                 *Format,
  ...
  )
/*++

Routine Description:

  Sprint function to process format and place the results in buffer

Arguments:

  Buffer      - Ascii buffer to print the results of the parsing of format into
  BufferSize  - Maximun number of characters to put into buffer. 0 means no limit
  Format      - Ascii format string see file header for more details
  ...         - Variable parameters

Returns:

  Number of characters printed.

--*/
;

INT32
StrToGuid (
  INT8                 *Str,
  EFI_GUID             *Guid
  )
/*++

Routine Description:

  Convert string to guid structure.

Arguments:

  Str   - String to be converted.
  Guid  - Output Guid structure pointer.

Returns:

  0  - Success;
  -1 - Failure.

--*/
;

INT32
Output2Screen (
  INT8                 *Str
  )
/*++

Routine Description:

  Oupput the string to screen, using specified Tcl command

Arguments:

  Str - String to be output.

Returns:

  TCL_OK or TCL_ERROR

--*/
;

EFI_STATUS
BeginPacketLogging (
  CONST INT8           *FileName,
  CONST INT8           *Filter
  )
/*++

Routine Description:

  Begin logging packets, including create packet dump file

Arguments:

  FileName  - Filename string.
  Filter    - Filter string.

Returns:

  EFI_SUCCESS - The begin logging process successfully

--*/
;

EFI_STATUS
EndPacketLogging (
  VOID
  )
/*++

Routine Description:

  The end logging process, include record term infor, close log files

Arguments:

  VOID_P - None

Returns:

  EFI_SUCCESS - The end logging process successfully

--*/
;

EFI_STATUS
LoggingPacketProcess (
  CONST INT8           *FileName
  )
/*++

Routine Description:

  Read packets from Log file and send them out.

Arguments:

  FileName  - Filename string.

Returns:

  EFI_SUCCESS - The log packet reading and sending process successfully
  EFI_LOAD_ERROR - Some error happens.

--*/
;

EFI_STATUS
ProcessCapturedPacket (
  CONST INT8  *Filter,
  UINT32      Timeout,
  UINT32      Interval,
  UINT8       Count
  )
/*++

Routine Description:

  Capture specified packets and resends them out.

Arguments:

  Filter    - Filter string.
  Timeout   - Timeout value.
  Interval  - Interval time
  Count     - The count of Reproducing

Returns:

  EFI_SUCCESS - Processing captured packets successfully.
  EFI_LOAD_ERROR - Some error happens.

--*/
;

EFI_STATUS
GetTemporaryLogData(
  EMS_PRIVATE *LogData
  )
/*++

Routine Description:

  Get the temporary log data

Arguments:

  None

Returns:

  EFI_SUCCESS   - Successfully.

--*/
;

VOID
SavedLogDataLock (
  VOID
  )
/*++

Routine Description:

  Make saving log data operation to be atomic

Arguments:

  None

Returns:

  None

--*/
;

VOID
SavedLogDataUnlock(
  VOID
  )
/*++

Routine Description:

  Make saving log data operation to be atomic

Arguments:

  None

Returns:

  None

--*/
;

VOID
EmsClearLog(
  VOID
  )
/*++

Routine Description:

  Close log files and clear private data

Arguments:

  None

Returns:

  None

--*/
;

#endif // __EMS_LOG_UTILITY_H__
