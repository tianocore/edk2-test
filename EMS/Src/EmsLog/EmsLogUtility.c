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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsLogUtility.c
    
Abstract:

    Implementation of log library

    VSPrint, SPrint format specification has the following form

    %[flags][width]type

    flags:
      '-' - Left justify
      '+' - Prefix a sign
      ' ' - Prefix a blank
      ',' - Place commas in numbers
      '0' - Prefix for width with zeros
      'L','l' - u_int64_t
    width:
      '*' - Get width from a unsigned int argument from the argument list
            Decimal number that represems width of print
    type:
      'X' - argument is a unsigned int hex number, prefix '0'
      'x' - argument is a hex number
      'd' - argument is a decimal number
      'a' - argument is an ascii string
      'g' - argument is a pointer to an EFI_GUID
      't' - argument is a pointer to an EFI_TIME structure
      'c' - argument is an ascii character
      'r' - argumatn is EFI_STATUS
      '%' = Print a %

--*/

#include "EmsNet.h"
#include "EmsLogUtility.h"
#include "EmsUtilityString.h"

STATIC INT8           HexStr[] = {
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F'
};

STATIC INT8           *m_dashline = "------------------------------------------------------------\n";

STATIC CONST UINT32   MonthLength[2][12] = {
  {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
  },
  {
    31,
    29,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
  }
};

EMS_PRIVATE           Private = {
  0,                                  // test_revision
  NULL,                               // case_name
  NULL,                               // case_category
  NULL,                               // case_description
  NULL,                               // case_index
  0,                                  // pass_count
  0,                                  // warn_count
  0,                                  // fail_count
  NULL,                               // case_status
  0,                                  // test_status
  {
    0
  },                                  // start_time
  {
    0
  },                                  // end_time
  NULL,                               // summary_log
  NULL,                               // summary_key
  NULL,                               // case_log
  NULL,                               // case_key
  0,                                  // test_level
  0,                                  // case_attribute
  0,                                  // verbose_level
  {
    0
  },                                  // guid
};

extern INT8           *EmsInterface;
STATIC pcap_t         *PacketDumper;  /* Pcap Capturer, for logging all the packets */
STATIC pcap_dumper_t  *DumperContext;

STATIC
VOID_P
SavePacket (
  IN u_char                   *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  );

EMS_ASSERTION_INFOR   *AssertionInforCase;
BOOLEAN               Found;

//
// internal functions
//
STATIC
EFI_STATUS
WriteLogFile (
  INT8                  *String
  );

STATIC
EFI_STATUS
WriteKeyFile (
  INT8                  *String
  );

STATIC
EFI_STATUS
GetTimeStamp (
  EFI_TIME              *Time
  );

STATIC
UINT32
SecondsElapsedFromBaseYear (
  EFI_TIME              Time
  );

//
// vsprint functions
//
STATIC
UINT32
vsprint (
  INT8                  *StartOfBuffer,
  UINT32                BufferSize,
  INT8                  *FormatString,
  va_list               Marker
  );

STATIC
UINT32
EfiValueToHexStr (
  INT8                   *Buffer,
  UINT64                 Value,
  UINT32                 Flags,
  UINT32                 Width
  );

STATIC
UINT32
EfiValueToString (
  INT8                   *Buffer,
  INT64                  Value,
  UINT32                 Flags,
  UINT32                 Width
  );

STATIC
INT8                  *
GetFlagsAndWidth (
  INT8                   *Format,
  UINT32                 *Flags,
  UINT32                 *Width,
  va_list                *Marker
  );

STATIC
UINT32
GuidToString (
  EFI_GUID               *Guid,
  INT8                   *Buffer,
  UINT32                 BufferSize
  );

STATIC
UINT32
TimeToString (
  EFI_TIME               *Time,
  INT8                   *Buffer,
  UINT32                 BufferSize
  );

STATIC
UINT32
EfistatusToString (
  EFI_STATUS             Status,
  INT8                   *Buffer,
  UINT32                 BufferSize
  );

//
// Function for ResendCapturedPacket.
//
libnet_t              *pLibNet;
UINT8                 ReproducingCount;
INT8                  LibnetErrBuff[LIBNET_ERRBUF_SIZE];

EFI_STATUS
ResendCapturedPacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  );

//
// functions implementations
//

EFI_STATUS
RecordAssertion (
  EmsTestAssertion      TestAssertionType,
  INT8                  *Guid,  // insert guid item
  INT8                  *Description,
  INT8                  *Detail,
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
{
  EFI_STATUS          Status;
  va_list             Marker;
  INT8                Buffer[EMS_MAX_PRINT_BUFFER];
  INT8                AssertionType[10];
  EFI_TIME            Time;

  EMS_ASSERTION_INFOR *AssertionInfor;
  EMS_ASSERTION_INFOR *AssertionInforNew;

  //
  // get current time
  //
  GetTimeStamp (&Time);

  //
  // check the parameter
  //
  if (strlen (Description) + 14 > EMS_MAX_PRINT_BUFFER) {
    return EFI_BAD_BUFFER_SIZE;
  }
  //
  // write log file detail data
  //
  switch (TestAssertionType) {
  case EMS_TEST_ASSERTION_PASSED:
    strcpy (AssertionType, "PASS");
    Private.PassCount++;
    break;

  case EMS_TEST_ASSERTION_WARNING:
    strcpy (AssertionType, "WARNING");
    Private.WarnCount++;
    break;

  case EMS_TEST_ASSERTION_FAILED:
    strcpy (AssertionType, "FAILURE");
    Private.FailCount++;
    break;

  default:
    return EFI_INVALID_PARAMETER;
  }

  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a -- %a\n%t\n",
    Description,
    AssertionType,
    &Time
    );

  Status = WriteLogFile (Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  va_start (Marker, Detail);
  vsprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    Detail,
    Marker
    );
  va_end (Marker);

  if (strlen (Buffer) + 3 < EMS_MAX_PRINT_BUFFER) {
    strcat (Buffer, "\n\n");
  }

  Status = WriteLogFile (Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // write key file detail line
  //
  AssertionInfor = AssertionInforCase;

  while (AssertionInfor != NULL) {
    if (strcmp (AssertionInfor->Guid, Guid) != 0) {
      Found           = FALSE;
      AssertionInfor  = AssertionInfor->Next;
      continue;
    } else {
      Found           = TRUE;
      AssertionInfor  = NULL;
    }
  }

  if (Found == FALSE || (strcmp (Guid, GenericGuid) == 0)) {
    //
    //  not found
    // create a new assertion infor
    //
    AssertionInforNew = (EMS_ASSERTION_INFOR *) malloc (sizeof (EMS_ASSERTION_INFOR));
    if (AssertionInforNew == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    AssertionInforNew->Guid               = Guid;
    AssertionInforNew->TestAssertionType  = TestAssertionType;
    AssertionInforNew->Description        = Description;

    //
    // add the new assertion infor
    //
    AssertionInforNew->Prev = NULL;
    AssertionInfor          = AssertionInforCase;
    AssertionInforCase      = AssertionInforNew;
    AssertionInforNew->Next = AssertionInfor;
    if (AssertionInfor != NULL) {
      AssertionInfor->Prev = AssertionInforNew;
    }

    Sprint (
      Buffer,
      EMS_MAX_PRINT_BUFFER,
      "%a|%a|%a:",
      AssertionInforCase->Guid,
      AssertionType,
      Description
      );
    Status = WriteKeyFile (Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    va_start (Marker, Detail);
    vsprint (
      Buffer,
      EMS_MAX_PRINT_BUFFER,
      Detail,
      Marker
      );
    va_end (Marker);
    if (strlen (Buffer) + 2 < EMS_MAX_PRINT_BUFFER) {
      strcat (Buffer, "\n");
    }

    Status = WriteKeyFile (Buffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
RecordMessage (
  EmsVerboseLevel       VerboseLevel,
  INT8                  *Message,
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
{
  EFI_STATUS  Status;
  va_list     Marker;
  INT8        Buffer[EMS_MAX_PRINT_BUFFER];

  //
  // check the parameter
  //
  if (strlen (Message) + 14 > EMS_MAX_PRINT_BUFFER) {
    return EFI_BAD_BUFFER_SIZE;
  }
  //
  // only when the verbose level is no higher than the case config level,
  // this message is recorded to log file
  //
  if (VerboseLevel > Private.VerboseLevel) {
    return EFI_SUCCESS;
  }
  //
  // write log file detail data
  //
  va_start (Marker, Message);
  vsprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    Message,
    Marker
    );
  va_end (Marker);

  if (strlen (Buffer) + 3 < EMS_MAX_PRINT_BUFFER) {
    strcat (Buffer, "\n\n");
  }

  Status = WriteLogFile (Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
RecordMessageAgent (
  EmsVerboseLevel       VerboseLevel,
  INT8                  *Message,
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
{
  EFI_STATUS  Status;
  va_list     Marker;
  INT8        Buffer[EMS_MAX_PRINT_BUFFER];

  //
  // check the parameter
  //
  if (strlen (Message) + 14 > EMS_MAX_PRINT_BUFFER) {
    return EFI_BAD_BUFFER_SIZE;
  }
  //
  // only when the verbose level is no higher than the case config level,
  // this message is recorded to log file
  //
  if (VerboseLevel > Private.VerboseLevel) {
    return EFI_SUCCESS;
  }
  //
  // write log file detail data
  //
  Status = WriteLogFile ("Agent Side Message START\n");
  if (EFI_ERROR (Status)) {
    return Status;
  }

  va_start (Marker, Message);
  vsprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    Message,
    Marker
    );
  va_end (Marker);

  if (strlen (Buffer) + 3 < EMS_MAX_PRINT_BUFFER) {
    strcat (Buffer, "\n\n");
  }

  Status = WriteLogFile (Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = WriteLogFile ("Agent Side Message END\n");
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // write key file detail data
  //
  Status = WriteLogFile ("Agent Side Message START\n");
  if (EFI_ERROR (Status)) {
    return Status;
  }

  va_start (Marker, Message);
  vsprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    Message,
    Marker
    );
  va_end (Marker);

  if (strlen (Buffer) + 2 < EMS_MAX_PRINT_BUFFER) {
    strcat (Buffer, "\n");
  }

  Status = WriteKeyFile (Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = WriteLogFile ("Agent Side Message END\n");
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

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
{
  if(Private.CaseLog) fclose(Private.CaseLog);
  if(Private.CaseKey) fclose(Private.CaseKey);
  if(Private.SummaryLog) fclose (Private.SummaryLog);
  if(Private.SummaryKey) fclose (Private.SummaryKey);

  memset(&Private, 0, sizeof(EMS_PRIVATE));
}

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
{
  INT8  Buffer[EMS_MAX_PRINT_BUFFER];

  if ((Private.SummaryLog != NULL) ||
      (Private.SummaryKey != NULL) ||
      (Private.CaseLog != NULL) ||
      (Private.CaseKey != NULL)
      ){
    goto BeginLogging_Err;
  }

  AssertionInforCase  = NULL;
  Found               = FALSE;

  //
  // get start time
  //
  GetTimeStamp (&Private.StartTime);

  //
  // open summary log file
  //
  mkdir (EMS_OVERALL_DIR, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a.Log",
    EMS_OVERALL_DIR,
    EMS_OVERALL_FILE
    );

  Private.SummaryLog = fopen (Buffer, "ab");
  if (Private.SummaryLog == NULL) {
    goto BeginLogging_Err;
  }
  //
  // open summary key file
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a.ekl",
    EMS_OVERALL_DIR,
    EMS_OVERALL_FILE
    );

  Private.SummaryKey = fopen (Buffer, "ab");
  if (Private.SummaryKey == NULL) {
    fclose (Private.SummaryLog);
    goto BeginLogging_Err;
  }
  //
  // open case log file
  //
  mkdir (EMS_LOG_DIR, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a",
    EMS_LOG_DIR,
    Private.CaseCategory
    );

  mkdir (Buffer, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a/%a.Log",
    EMS_LOG_DIR,
    Private.CaseCategory,
    Private.CaseName
    );

  Private.CaseLog = fopen (Buffer, "wb");
  if (Private.CaseLog == NULL) {
    fclose (Private.SummaryLog);
    fclose (Private.SummaryKey);
    goto BeginLogging_Err;
  }
  //
  // open case key file
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a/%a.ekl",
    EMS_LOG_DIR,
    Private.CaseCategory,
    Private.CaseName
    );

  Private.CaseKey = fopen (Buffer, "wb");
  if (Private.CaseKey == NULL) {
    fclose (Private.SummaryLog);
    fclose (Private.SummaryKey);
    fclose (Private.CaseLog);
    goto BeginLogging_Err;
  }
  //
  // write head log infor
  //
  WriteLogFile (m_dashline);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "%a\n", Private.CaseName);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Revision: 0x%08x\n", Private.TestRevision);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Test GUID: %g\n", &Private.Guid);
  WriteLogFile (Buffer);

  WriteLogFile (m_dashline);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "%a\n", Private.CaseDescription);
  WriteLogFile (Buffer);

  WriteLogFile (m_dashline);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Logfile: \"Log/%a/%a.Log\"\n", Private.CaseCategory, Private.CaseName);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Test Started: %t\n", &Private.StartTime);
  WriteLogFile (Buffer);

  WriteLogFile (m_dashline);

  //
  // write head key infor
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "|HEAD|||||%02d-%02d-%04d|%02d:%02d:%02d|%g|0x%08x|%a|%a|%a|%a|\n",
    Private.StartTime.Day,
    Private.StartTime.Month,
    Private.StartTime.Year,
    Private.StartTime.Hour,
    Private.StartTime.Minute,
    Private.StartTime.Second,
    &(Private.Guid),
    Private.TestRevision,
    Private.CaseIndex,
    Private.CaseName,
    Private.CaseCategory,
    Private.CaseDescription
    );
  WriteKeyFile (Buffer);

  return TCL_OK;

BeginLogging_Err:
  return TCL_ERROR;
}

STATIC HANDLE      SavedLogDataMutex = NULL;
STATIC EMS_PRIVATE SavedLogData;

VOID
SavedLogDataLock (VOID)
/*++

Routine Description:

  Make saving log data operation to be atomic

Arguments:

  None

Returns:

  None

--*/
{
  if(SavedLogDataMutex == NULL)
  	SavedLogDataMutex = CreateMutex (NULL, FALSE, NULL);
  WaitForSingleObject(SavedLogDataMutex, INFINITE);
}

VOID
SavedLogDataUnlock(VOID)
/*++

Routine Description:

  Make saving log data operation to be atomic

Arguments:

  None

Returns:

  None

--*/
{
  ReleaseMutex(SavedLogDataMutex);
}

STATIC
EFI_STATUS
SaveLogDataTemporary (
  VOID
  )
/*++

Routine Description:

  Save the log data temporarily

Arguments:

  None

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  SavedLogDataLock();
  SavedLogData = Private;
  SavedLogDataUnlock();
  return EFI_SUCCESS;
}

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
{
  SavedLogDataLock();
  *LogData = SavedLogData;
  memset(&SavedLogData, 0x0, sizeof(EMS_PRIVATE));
  SavedLogDataUnlock();
  return EFI_SUCCESS;
}

EFI_STATUS
EndLogging (
  EFI_STATUS         TestStatus
  )
/*++

Routine Description:

  the end logging process, include record term infor, close log files

Arguments:

  TestStatus  - the test exit status

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  INT8    Buffer[EMS_MAX_PRINT_BUFFER];
  UINT32  DaysElapsed;
  UINT32  HoursElapsed;
  UINT32  MinutesElapsed;
  UINT32  SecondsElapsed;
  EMS_ASSERTION_INFOR *AssertionFree;

  if ((Private.SummaryLog == NULL) ||
      (Private.SummaryKey == NULL) ||
      (Private.CaseLog == NULL) ||
      (Private.CaseKey == NULL)
      ) {
    return EFI_SUCCESS;
  }
  //
  // get end time
  //
  GetTimeStamp (&Private.EndTime);
  Private.TestStatus = TestStatus;

  //
  // write term log infor
  //
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\nReturned Status: %r\n", Private.TestStatus);
  WriteLogFile (Buffer);

  if ((Private.PassCount > 0) && (Private.WarnCount == 0) && (Private.FailCount == 0)) {
    Private.CaseStatus = "PASS";
  } else if ((Private.PassCount > 0) && (Private.WarnCount > 0) && (Private.FailCount == 0)) {
    Private.CaseStatus = "WARNING";
  } else if ((Private.PassCount >= 0) && (Private.WarnCount >= 0) && (Private.FailCount > 0)) {
    Private.CaseStatus = "FAILURE";
  } else {
    Private.CaseStatus = "NOT SUPPORTED";
  }

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\n%a: [%a]\n", Private.CaseName, Private.CaseStatus);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "  PASS .......... %d\n", Private.PassCount);
  WriteLogFile (Buffer);
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "  WARN .......... %d\n", Private.WarnCount);
  WriteLogFile (Buffer);
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "  FAIL .......... %d\n", Private.FailCount);
  WriteLogFile (Buffer);
  WriteLogFile (m_dashline);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "%a\n", Private.CaseName);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Revision: 0x%08x\n", Private.TestRevision);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Test GUID: %g\n", &(Private.Guid));
  WriteLogFile (Buffer);

  WriteLogFile (m_dashline);
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Logfile: \"Log/%a/%a.Log\"\n", Private.CaseCategory, Private.CaseName);
  WriteLogFile (Buffer);

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "Test Finished: %t\n", &Private.EndTime);
  WriteLogFile (Buffer);

  //
  // get the elapsed time
  //
  SecondsElapsed  = SecondsElapsedFromBaseYear (Private.EndTime) - SecondsElapsedFromBaseYear (Private.StartTime);

  DaysElapsed     = SecondsElapsed / SECS_PER_DAY;
  SecondsElapsed -= DaysElapsed * SECS_PER_DAY;
  HoursElapsed = SecondsElapsed / SECS_PER_HOUR;
  SecondsElapsed -= HoursElapsed * SECS_PER_HOUR;
  MinutesElapsed = SecondsElapsed / SECS_PER_MIN;
  SecondsElapsed -= MinutesElapsed * SECS_PER_MIN;

  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "Elapsed Time: %d Days %02d:%02d:%02d\n",
    DaysElapsed,
    HoursElapsed,
    MinutesElapsed,
    SecondsElapsed
    );
  WriteLogFile (Buffer);
  WriteLogFile (m_dashline);
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\n");
  WriteLogFile (Buffer);

  //
  // write term key infor
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "|TERM|%04x|%02d-%02d-%04d|%02d:%02d:%02d|%d %02d:%02d:%02d|%a|",
    (UINT16) (Private.TestStatus & 0xFFFF),
    Private.EndTime.Day,
    Private.EndTime.Month,
    Private.EndTime.Year,
    Private.EndTime.Hour,
    Private.EndTime.Minute,
    Private.EndTime.Second,
    DaysElapsed,
    HoursElapsed,
    MinutesElapsed,
    SecondsElapsed,
    Private.CaseStatus
    );
  WriteKeyFile (Buffer);

  SaveLogDataTemporary();

  while(AssertionInforCase) {
  	AssertionFree = AssertionInforCase;
	AssertionInforCase = AssertionInforCase->Next;
	free(AssertionFree);
  }
  //
  // close files
  //
  fclose (Private.CaseLog);
  fclose (Private.CaseKey);
  fclose (Private.SummaryLog);
  fclose (Private.SummaryKey);

  Private.CaseLog     = NULL;
  Private.CaseKey     = NULL;
  Private.SummaryLog  = NULL;
  Private.SummaryKey  = NULL;

  Private.PassCount   = 0;
  Private.WarnCount   = 0;
  Private.FailCount   = 0;
  Private.CaseStatus  = NULL;
  Private.TestStatus  = 0;

  return EFI_SUCCESS;
}


EFI_STATUS
SetConfig (
  EMS_CASE_CONFIG         CaseConfig
  )
/*++

Routine Description:

  set the case private config information

Arguments:

  CaseConfig  - the case config information

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  //
  //  memset (&private, 0, sizeof(private));
  //
  // set config information
  //
  Private.TestRevision    = EMS_TEST_REVISION;
  Private.CaseName        = CaseConfig.CaseName;
  Private.CaseCategory    = CaseConfig.CaseCategory;
  Private.CaseDescription = CaseConfig.CaseDescription;
  Private.CaseIndex       = CaseConfig.CaseIndex;
  Private.TestLevel       = CaseConfig.TestLevel;
  Private.CaseAttribute   = CaseConfig.CaseAttribute;
  Private.VerboseLevel    = CaseConfig.VerboseLevel;
  memcpy (&Private.Guid, &CaseConfig.Guid, sizeof (EFI_GUID));

  return EFI_SUCCESS;
}

EFI_STATUS
WriteLogFile (
  INT8                  *String
  )
/*++

Routine Description:

  write string to log files

Arguments:

  String  - message to be written

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  //
  // write to case log file and summary log file
  //
  if (Private.CaseLog != NULL) {
    fwrite (String, strlen (String), 1, Private.CaseLog);
  }

  if (Private.SummaryLog != NULL) {
    fwrite (String, strlen (String), 1, Private.SummaryLog);
  }
  //
  // output screen
  //
  Output2Screen (String);
  return EFI_SUCCESS;
}

EFI_STATUS
WriteKeyFile (
  INT8                  *String
  )
/*++

Routine Description:

  write string to key files

Arguments:

  String  - message to be written

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  //
  // write to case key file and summary key file
  //
  if (Private.CaseKey != NULL) {
    fwrite (String, strlen (String), 1, Private.CaseKey);
  }

  if (Private.SummaryKey != NULL) {
    fwrite (String, strlen (String), 1, Private.SummaryKey);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetTimeStamp (
  EFI_TIME              *Time
  )
/*++

Routine Description:

  get the current time

Arguments:

  Time  - struct to hold the time

Returns:

  EFI_SUCCESS   - Successfully.

--*/
{
  struct tm   *NowTime;
  __time64_t  LongTime;

  _time64 (&LongTime);  /* Get time as long integer. */
  NowTime           = _localtime64 (&LongTime); /* Convert to local time. */

  Time->Year        = NowTime->tm_year + 1900;
  Time->Month       = NowTime->tm_mon + 1;
  Time->Day         = NowTime->tm_mday;
  Time->Hour        = NowTime->tm_hour;
  Time->Minute      = NowTime->tm_min;
  Time->Second      = NowTime->tm_sec;
  Time->Pad1        = 0;
  Time->NanoSecond  = 0;
  Time->TimeZone    = 0;
  Time->DayLight    = 0;
  Time->Pad2        = 0;
  return EFI_SUCCESS;

}

UINT32
SecondsElapsedFromBaseYear (
  EFI_TIME        Time
  )
/*++

Routine Description:

  Calculate the elapsed seconds from base year

Arguments:

  Time  - Struct to hold the time

Returns:

  The elapsed seconds

--*/
{
  UINT32  LeapYear;
  UINT32  Index;
  UINT32  Seconds;
  UINT32  Year;
  UINT32  Month;
  UINT32  Day;
  UINT32  Hour;
  UINT32  Minute;
  UINT32  Second;

  Seconds = 0;
  Year    = Time.Year;
  Month   = Time.Month;
  Day     = Time.Day;
  Hour    = Time.Hour;
  Minute  = Time.Minute;
  Second  = Time.Second;
  //
  // calculate the year
  //
  for (Index = BASE_YEAR; Index < Year; Index++) {
    if (IS_LEAP (Index)) {
      Seconds += DAYS_PER_LYEAR * SECS_PER_DAY;
    } else {
      Seconds += DAYS_PER_NYEAR * SECS_PER_DAY;
    }
  }
  //
  // calculate the month
  //
  LeapYear = IS_LEAP (Year);
  for (Index = 0; Index < Month - 1; Index++) {
    Seconds += MonthLength[LeapYear][Index] * SECS_PER_DAY;
  }
  //
  // calculate the day
  //
  for (Index = 0; Index < Day - 1; Index++) {
    Seconds += SECS_PER_DAY;
  }
  //
  // calculate the hour, minute, and second
  //
  for (Index = 0; Index < Hour; Index++) {
    Seconds += SECS_PER_HOUR;
  }

  for (Index = 0; Index < Minute; Index++) {
    Seconds += SECS_PER_MIN;
  }

  Seconds += Second;

  //
  // get the seconds
  //
  return (UINT32) Seconds;
}

UINT32
Sprint (
  INT8                   *Buffer,
  UINT32                 BufferSize,
  INT8                   *Format,
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
{
  UINT32  ReturnValue;
  va_list Marker;

  va_start (Marker, Format);
  ReturnValue = vsprint (Buffer, BufferSize, Format, Marker);
  va_end (Marker);

  return ReturnValue;
}

UINT32
vsprint (
  INT8                   *StartOfBuffer,
  UINT32                 BufferSize,
  INT8                   *FormatString,
  va_list                Marker
  )
/*++

Routine Description:

  Vsprint function to process format and place the results in buffer
  since a va_list is used this rountine allows the nesting of vararg routings
  thus this is the main print working routine

Arguments:

  StartOfBuffer - Ascii buffer to print the results of the parsing of format into
  BufferSize    - Maximun number of characters to put into buffer. 0 means no limit
  FormatString  - Ascii format string see file header for more details
  Marker        - Vararg list consumed by processing format

Returns:

  Number of characters printed.

--*/
{
  INT8      *Buffer;
  INT8      *AsciiStr;
  INT8      *Format;
  UINT32    Index;
  UINT32    Flags;
  UINT32    Width;
  UINT32    Count;
  UINT64    Value;
  EFI_GUID  *TmpGuid;

  //
  // process the format string. Stop it buffer is over run.
  //
  Buffer  = StartOfBuffer;
  Format  = (INT8 *) FormatString;
  for (Index = 0; (*Format != '\0') && (Index < BufferSize); Format++) {
    if (*Format != '%') {
      Buffer[Index++] = *Format;
    } else {
      //
      // now it's time to parse what follow after %
      //
      Format = GetFlagsAndWidth (Format, &Flags, &Width, &Marker);
      switch (*Format) {
      case 'X':
        Flags |= PREFIX_ZERO;
        Width = sizeof (UINT64) * 2;

      //
      // break skiped on purpose
      //
      case 'x':
        if ((Flags & LONG_TYPE) == LONG_TYPE) {
          Value = va_arg (Marker, UINT64);
        } else {
          Value = va_arg (Marker, UINT32);
        }

        Index += EfiValueToHexStr (&Buffer[Index], Value, Flags, Width);
        break;

      case 'd':
        if ((Flags & LONG_TYPE) == LONG_TYPE) {
          Value = va_arg (Marker, UINT64);
        } else {
          Value = (UINT32) va_arg (Marker, UINT32);
        }

        Index += EfiValueToString (&Buffer[Index], Value, Flags, Width);
        break;

      case 'a':
        AsciiStr = (INT8 *) va_arg (Marker, INT8 *);
        if (AsciiStr == NULL) {
          AsciiStr = "<null String>";
        }

        for (Count = 0; *AsciiStr != '\0'; AsciiStr++, Count++) {
          Buffer[Index++] = *AsciiStr;
        }
        //
        // add padding if needed
        //
        for (; Count < Width; Count++) {
          Buffer[Index++] = ' ';
        }
        break;

      case 'c':
        Buffer[Index++] = (INT8) va_arg (Marker, UINT32);
        break;

      case 'g':
        TmpGuid = va_arg (Marker, EFI_GUID *);
        if (TmpGuid != NULL) {
          Index += GuidToString (TmpGuid, &Buffer[Index], BufferSize);
        }
        break;

      case 't':
        Index += TimeToString (
                  va_arg (Marker,
                  EFI_TIME *),
                  &Buffer[Index],
                  BufferSize
                  );
        break;

      case 'r':
        Index += EfistatusToString (
                  va_arg (Marker,
                  EFI_STATUS),
                  &Buffer[Index],
                  BufferSize
                  );
        break;

      case '%':
        Buffer[Index++] = *Format;
        break;

      default:
        //
        // if the type is unknown print it to the screem
        //
        Buffer[Index++] = *Format;
      }
    }
  }

  Buffer[Index++] = '\0';

  return &Buffer[Index] - StartOfBuffer;
}

STATIC
INT8 *
GetFlagsAndWidth (
  INT8                   *Format,
  UINT32                 *Flags,
  UINT32                 *Width,
  va_list                *Marker
  )
/*++

Routine Description:

  vsprint worker function that parses flag and width information from the
  format string and returns the next index into the format string that needs
  to be parsed. See file headed for details of flag and width.

Arguments:

  Format  - current location in the vsprint format string
  Flags   - returns flags
  Width   - returns width of element
  Marker  - vararg list that may be paritally consumed and returned

Returns:

  pointer indexed into the format string for all the information parsed by 
  this routine

--*/
{
  UINT32  Count;
  BOOLEAN Done;

  *Flags  = 0;
  *Width  = 0;
  for (Done = FALSE; !Done;) {
    Format++;

    switch (*Format) {
    case '-':
      *Flags |= LEFT_JUSTIFY;
      break;

    case '+':
      *Flags |= PREFIX_SIGN;
      break;

    case ' ':
      *Flags |= PREFIX_BLANK;
      break;

    case ',':
      *Flags |= COMMA_TYPE;
      break;

    case 'L':
    case 'l':
      *Flags |= LONG_TYPE;
      break;

    case '*':
      *Width = va_arg (*Marker, UINT32);
      break;

    case '0':
      *Flags |= PREFIX_ZERO;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      Count = 0;
      do {
        Count = (Count * 10) +*Format - '0';
        Format++;
      } while ((*Format >= '0') && (*Format <= '9'));
      Format--;
      *Width = Count;
      break;

    default:
      Done = TRUE;
    }
  }

  return Format;
}

STATIC
UINT32
GuidToString (
  EFI_GUID              *Guid,
  INT8                  *Buffer,
  UINT32                BufferSize
  )
/*++

Routine Description:

  vsprint worker function that prints an EFI_GUID

Arguments:

  Guid        - pointer to EFI_GUID to print
  Buffer      - buffer to print guid into
  BufferSize  - size of buffer

Returns:

  number of characters printed

--*/
{
  UINT32  Size;

  Size = Sprint (
          Buffer,
          BufferSize,
          "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
          Guid->Data1,
          Guid->Data2,
          Guid->Data3,
          Guid->Data4,
          Guid->Data5,
          Guid->Data6,
          Guid->Data7,
          Guid->Data8,
          Guid->Data9,
          Guid->Data10,
          Guid->Data11
          );

  //
  // SPrint will null terminated the string. The -1 skips the null.
  //
  return Size - 1;
}

STATIC
UINT32
TimeToString (
  EFI_TIME              *Time,
  INT8                  *Buffer,
  UINT32                BufferSize
  )
/*++

Routine Description:

  vsprint worker function that prints EFI_TIME

Arguments:

  Time        - pointer to EFI_TIME struct to print
  Buffer      - buffer to print time into
  BufferSize  - size of buffer

Returns:

  number of characters printed

--*/
{
  UINT32  Size;

  Size = Sprint (
          Buffer,
          BufferSize,
          "%02d/%02d/%04d %02d:%02d:%02d",
          Time->Month,
          Time->Day,
          Time->Year,
          Time->Hour,
          Time->Minute,
          Time->Second
          );

  //
  // Sprint will null terminate the string. The -1 skips the null.
  //
  return Size - 1;
}

struct {
  EFI_STATUS  Status;
  INT8        *String;
}
status_string[] = {
  {
    EFI_SUCCESS,
    "Success"
  },
  {
    EFI_LOAD_ERROR,
    "Load Error"
  },
  {
    EFI_INVALID_PARAMETER,
    "Invalid Parameter"
  },
  {
    EFI_UNSUPPORTED,
    "Unsupported"
  },
  {
    EFI_BAD_BUFFER_SIZE,
    "Bad Buffer Size"
  },
  {
    EFI_BUFFER_TOO_SMALL,
    "Buffer Too Small"
  },
  {
    EFI_NOT_READY,
    "Not Ready"
  },
  {
    EFI_DEVICE_ERROR,
    "Device Error"
  },
  {
    EFI_WRITE_PROTECTED,
    "Write Protected"
  },
  {
    EFI_OUT_OF_RESOURCES,
    "Out of Resources"
  },
  {
    EFI_VOLUME_CORRUPTED,
    "Volume Corrupted"
  },
  {
    EFI_VOLUME_FULL,
    "Volume Full"
  },
  {
    EFI_NO_MEDIA,
    "No Media"
  },
  {
    EFI_MEDIA_CHANGED,
    "Media Changed"
  },
  {
    EFI_NOT_FOUND,
    "Not Found"
  },
  {
    EFI_ACCESS_DENIED,
    "Access Denied"
  },
  {
    EFI_NO_RESPONSE,
    "No Response"
  },
  {
    EFI_NO_MAPPING,
    "No Mapping"
  },
  {
    EFI_TIMEOUT,
    "Time out"
  },
  {
    EFI_NOT_STARTED,
    "Not Started"
  },
  {
    EFI_ALREADY_STARTED,
    "Already Started"
  },
  {
    EFI_ABORTED,
    "Aborted"
  },
  {
    EFI_ICMP_ERROR,
    "ICMP Error"
  },
  {
    EFI_TFTP_ERROR,
    "TFTP Error"
  },
  {
    EFI_PROTOCOL_ERROR,
    "Protocol Error"
  },
  {
    EFI_INCOMPATIBLE_VERSION,
    "Incompatible Version"
  },
  {
    EFI_SECURITY_VIOLATION,
    "Security Violation"
  },
  {
    EFI_CRC_ERROR,
    "CRC Error"
  },
  {
    EFI_NOT_AVAILABLE_YET,
    "Not Available Yet"
  },
  {
    EFI_UNLOAD_IMAGE,
    "Unload Image"
  },
  {
    EFI_NETWORK_UNREACHABLE,
    "Network Unreachable"
  },
  { 
    EFI_HOST_UNREACHABLE,     
    "Host Unreachable"
  },
  {
    EFI_PROTOCOL_UNREACHABLE,
    "Protocol Unreachable"
  },
  {
    EFI_PORT_UNREACHABLE,
    "Port Unreachable"
  },
  {
    EFI_CONNECTION_REFUSED,
    "Connection Refused"
  },
  {
    EFI_WARN_UNKNOWN_GLYPH,
    "Warning Unknown Glyph"
  },
  {
    EFI_WARN_DELETE_FAILURE,
    "Warning Delete Failure"
  },
  {
    EFI_WARN_WRITE_FAILURE,
    "Warning Write Failure"
  },
  {
    EFI_WARN_BUFFER_TOO_SMALL,
    "Warning Buffer Too Small"
  },
  {
    EFI_WARN_RETURN_FROM_LONG_JUMP,
    "Warning Return From Long Jump"
  },
  {
    EFI_MAX_BIT,
    NULL
  }
};

STATIC
UINT32
EfistatusToString (
  EFI_STATUS            Status,
  INT8                  *Buffer,
  UINT32                BufferSize
  )
/*++

Routine Description:

  vsprint worker function that prints EFI_STATUS as a string
  if string is not knowm a hex value will be printed

Arguments:

  Status      - EFI_STATUS structure to print
  Buffer      - buffer to print EFI_STATUS messaga string into
  BufferSize  - size of buffer

Returns:

  number of characters printed

--*/
{
  UINT32  Size;
  INT8    *Desc;
  UINT32  Index;
  BOOLEAN Found;

  Desc  = NULL;
  Index = 0;
  Found = FALSE;

  while (Found != TRUE) {
    if (Status == status_string[Index].Status || EFI_MAX_BIT == status_string[Index].Status) {
      Found = TRUE;
      Desc  = status_string[Index].String;
      break;
    } else {
      Index++;
    }
  }
  //
  // if we found a match, copy the message to the user's buffer. Otherwise
  // Sprint the hex status code to their buffer.
  //
  if (Desc != NULL) {
    Size = Sprint (Buffer, BufferSize, "%a", Desc);
  } else {
    Size = Sprint (Buffer, BufferSize, "%X", Status);
  }

  return Size - 1;
}

STATIC
UINT32
EfiValueToHexStr (
  INT8                  *Buffer,
  UINT64                Value,
  UINT32                Flags,
  UINT32                Width
  )
/*++

Routine Description:

  vsprint worker function that prints a value as a hex number in buffer

Arguments:

  Buffer  - location to place ascii hex string of Value
  Value   - hex value to convert to a string in Buffer
  Flags   - flags to use in printing hex string, see file header for details
  Width   - width of hex value

Returns:

  number of characters printed

--*/
{
  INT8    TempBuffer[30];
  INT8    *TempStr;
  INT8    Prefix;
  INT8    *BufferPtr;
  UINT32  Count;
  UINT32  Index;

  TempStr   = TempBuffer;
  BufferPtr = Buffer;

  //
  // count starts at one since we will null terminate. Each iteration of the
  // loop picks off one nibble. Oh yea TempStr ends up backwards
  //
  Count = 0;
  do {
    Index         = ((UINT32) Value & 0xf);
    *(TempStr++)  = HexStr[Index];
    Value         = Value >> 4;
    Count++;
  } while (Value != 0);

  if (Flags & PREFIX_ZERO) {
    Prefix = '0';
  } else if (!(Flags & LEFT_JUSTIFY)) {
    Prefix = ' ';
  } else {
    Prefix = 0x00;
  }

  for (Index = Count; Index < Width; Index++) {
    *(TempStr++) = Prefix;
  }
  //
  // reverse temp string into buffer.
  //
  while (TempStr != TempBuffer) {
    *(BufferPtr++) = *(--TempStr);
  }

  *BufferPtr = 0;
  return Index;
}

STATIC
UINT32
EfiValueToString (
  INT8                  *Buffer,
  INT64                 Value,
  UINT32                Flags,
  UINT32                Width
  )
/*++

Routine Description:

  vsprint worker function that prints a value as a decimal number in buffer

Arguments:

  Buffer  - location to place ascii hex string of Value
  Value   - decimal value to convert to a string in Buffer
  Flags   - flags to use in printing decimal string, see file header for details
  Width   - width of decimal value

Returns:

  number of characters printed

--*/
{
  INT8    TempBuffer[30];
  INT8    *TempStr;
  INT8    *BufferPtr;
  UINT32  Count;
  UINT32  Remainder;
  INT8    Prefix;
  UINT32  Index;

  TempStr   = TempBuffer;
  BufferPtr = Buffer;
  Count     = 0;

  if (Value < 0) {
    *(BufferPtr++)  = '-';
    Value           = -Value;
    Count++;
  }

  do {
    Remainder     = (UINT32) Value % 10;
    Value         = Value / 10;
    *(TempStr++)  = (INT8) (Remainder + '0');
    Count++;
    if ((Flags & COMMA_TYPE) == COMMA_TYPE) {
      if (Count % 3 == 0) {
        *(TempStr++) = ',';
      }
    }
  } while (Value != 0);

  if (Flags & PREFIX_ZERO) {
    Prefix = '0';
  } else if (!(Flags & LEFT_JUSTIFY)) {
    Prefix = ' ';
  } else {
    Prefix = 0x00;
  }

  for (Index = Count; Index < Width; Index++) {
    *(TempStr++) = Prefix;
  }
  //
  // reverse temp string into buffer.
  //
  while (TempStr != TempBuffer) {
    *(BufferPtr++) = *(--TempStr);
  }

  *BufferPtr = 0;
  return Index;
}

UINT32
CharToNum (
  INT8     Ch
  )
/*++

Routine Description:

  Convert char to number

Arguments:

  Ch  - The charactor

Returns:

  number of characters printed

--*/
{
  UINT32  Index;

  Index = 0;

  switch (Ch) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    Index = Ch - 0x30;
    return Index;

  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
    Index = Ch - 0x61 + 0xa;
    return Index;

  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
    Index = Ch - 0x41 + 0xA;
    return Index;

  default:
    return Index;
  }
}

INT32
StrToGuid (
  INT8                  *Str,
  EFI_GUID              *Guid
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
{
  INT32 Index;
  INT8  Ch;

  if (strlen (Str) > 36) {
    return -1;
  }

  for (Index = 0; Index < 36; Index++) {
    Ch = Str[Index];
    if ((Index == 8) || (Index == 13) || (Index == 18) || (Index == 23)) {
      if (Ch != '-') {
        return -1;
      }

      continue;
    }

    if (!((Ch >= '0' && Ch <= '9') || (Ch >= 'a' && Ch <= 'f') || (Ch >= 'A' && Ch <= 'F'))) {
      return -1;
    }
  }

  memset (Guid, 0, sizeof (EFI_GUID));
  Guid->Data1 = CharToNum (Str[0]) <<
    28 |
    CharToNum (Str[1]) <<
    24 |
    CharToNum (Str[2]) <<
    20 |
    CharToNum (Str[3]) <<
    16 |
    CharToNum (Str[4]) <<
    12 |
    CharToNum (Str[5]) <<
    8 |
    CharToNum (Str[6]) <<
    4 |
    CharToNum (Str[7]);
  Guid->Data2   = CharToNum (Str[9]) << 12 | CharToNum (Str[10]) << 8 | CharToNum (Str[11]) << 4 | CharToNum (Str[12]);
  Guid->Data3   = CharToNum (Str[14]) << 12 | CharToNum (Str[15]) << 8 | CharToNum (Str[16]) << 4 | CharToNum (Str[17]);
  Guid->Data4   = CharToNum (Str[19]) << 4 | CharToNum (Str[20]);
  Guid->Data5   = CharToNum (Str[21]) << 4 | CharToNum (Str[22]);
  Guid->Data6   = CharToNum (Str[24]) << 4 | CharToNum (Str[25]);
  Guid->Data7   = CharToNum (Str[26]) << 4 | CharToNum (Str[27]);
  Guid->Data8   = CharToNum (Str[28]) << 4 | CharToNum (Str[29]);
  Guid->Data9   = CharToNum (Str[30]) << 4 | CharToNum (Str[31]);
  Guid->Data10  = CharToNum (Str[32]) << 4 | CharToNum (Str[33]);
  Guid->Data11  = CharToNum (Str[34]) << 4 | CharToNum (Str[35]);

  return 0;
}

EFI_STATUS
BeginPacketLogging (
  CONST INT8            *FileName,
  CONST INT8            *Filter
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
{
  INT8                Buffer[EMS_MAX_PRINT_BUFFER];
  INT8                ErrBuff[PCAP_ERRBUF_SIZE];
  struct bpf_program  Bp;

  //
  // open case log file
  //
  mkdir (EMS_LOG_DIR, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a",
    EMS_LOG_DIR,
    Private.CaseCategory
    );
  mkdir (Buffer, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a/%a",
    EMS_LOG_DIR,
    Private.CaseCategory,
    Private.CaseName
    );
  mkdir (Buffer, 0755);
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a/%a/%a/%a",
    EMS_LOG_DIR,
    Private.CaseCategory,
    Private.CaseName,
    FileName
    );

  if ((
        PacketDumper = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuff               // error buffer
                    )) == NULL) {
    free (PacketDumper);
  }

  if (-1 == pcap_compile (PacketDumper, &Bp, Filter, 0, 0xFFFFFF)) {
    free (PacketDumper);
  }

  if (-1 == pcap_setfilter (PacketDumper, &Bp)) {
    free (PacketDumper);
  }

  DumperContext = pcap_dump_open (PacketDumper, Buffer);
  if (NULL == DumperContext) {
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EndPacketLogging (
  VOID_P
  )
/*++

Routine Description:

  The end logging process, include record term infor, close log files

Arguments:

  VOID_P - None

Returns:

  EFI_SUCCESS - The end logging process successfully

--*/
{
  INT32 Res;

  while (1) {
    Res = pcap_dispatch (
            PacketDumper,
            1,
            SavePacket,
            NULL
            );
    if (0 == Res) {
      break;
    }

    Tcl_Sleep (1);
  }

  pcap_dump_close (DumperContext);
  pcap_close (PacketDumper);

  return EFI_SUCCESS;
}

STATIC
VOID_P
SavePacket (
  IN u_char                   *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  Callback fucntion to receive packet.

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None.

--*/
{
  pcap_dump (DumperContext, PktHdr, (pcap_dumper_t *) Packet);
}

EFI_STATUS
LoggingPacketProcess (
  CONST INT8            *FileName
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
{
  libnet_t            *l;
  INT8                ErrBuffNet[LIBNET_ERRBUF_SIZE];
  pcap_t              *pPcap;
  struct pcap_pkthdr  PktHeader;
  u_char              *Packet;
  u_long              HeaderLen;
  INT8                Buffer[EMS_MAX_PRINT_BUFFER];
  INT8                ErrBuffPcap[PCAP_ERRBUF_SIZE];

  //
  // get log file path.
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "%a",
    FileName
    );

  //
  // open log file for reading.
  //
  pPcap = pcap_open_offline (Buffer, ErrBuffPcap);
  if (NULL == pPcap) {
    printf ("pcap_open_offline() failed, %s", ErrBuffPcap);
    goto ErrorExit;
  }
  //
  // Initialize the libnet to be advancecd mode.
  //
  l = libnet_init (
        LIBNET_LINK_ADV,  // injection type
        EmsInterface,     // network interface
        ErrBuffNet        // errbuf
        );

  if (NULL == l) {
    pcap_close (pPcap);
    printf ("libnet_init() failed, %s", ErrBuffNet);
    goto ErrorExit;
  }

  while (1) {
    Packet = pcap_next (pPcap, &PktHeader);
    if (Packet == NULL) {
      break;
    }

    HeaderLen = PktHeader.len;

    if (-1 == libnet_adv_write_link (l, Packet, HeaderLen)) {
      printf ("libnet_adv_write_link() failed");
      continue;
    }
  }

  pcap_close (pPcap);
  libnet_cq_remove(l);
  libnet_destroy (l);
  return EFI_SUCCESS;

ErrorExit:
  return EFI_LOAD_ERROR;
}

EFI_STATUS
ProcessCapturedPacket (
  CONST INT8         *Filter,
  UINT32             Timeout,
  UINT32             Interval,
  UINT8              Count
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
{
  pcap_t              *pPcap;
  INT8                ErrBuffPcap[PCAP_ERRBUF_SIZE];
  struct bpf_program  Bp;
  UINT32              DueTime;

  if ((
        pPcap = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    1,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuffPcap      // error buffer
                    )) == NULL) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "ProcessCapturedPacket: Cannot open network device to capture Packet - %a %a:%d",
      ErrBuffPcap,
      __FILE__,
      __LINE__
      );
    free (pPcap);
    goto ErrorExit;
  }

  if (-1 == pcap_compile (pPcap, &Bp, Filter, 0, 0xFFFFFF)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "ProcessCapturedPacket: Cannot open network device to capture Packet - %a:%d",
      __FILE__,
      __LINE__
      );
    free (pPcap);
    goto ErrorExit;
  }

  if (-1 == pcap_setfilter (pPcap, &Bp)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "ProcessCapturedPacket: Cannot open network device to capture Packet - %a:%d",
      __FILE__,
      __LINE__
      );
    free (pPcap);
    goto ErrorExit;
  }
  //
  // Initialize the libnet to be advancecd mode for sending preparation.
  //
  pLibNet = libnet_init (
              LIBNET_LINK_ADV,  // injection type
              EmsInterface,     // network interface
              LibnetErrBuff     // errbuf
              );

  if (NULL == pLibNet) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "ProcessCapturedPacket: Cannot initial libnet to send Packet - %a:%d",
      __FILE__,
      __LINE__
      );
    goto ErrorExit;
  }
  //
  // Capture packets during the timeout time period and resend it out.
  //
  ReproducingCount  = Count;
  DueTime           = GetTickCount () + Timeout * 1000;

  while (1) {
    //
    // Capture packets.
    //
    pcap_dispatch (pPcap, 1, ResendCapturedPacket, NULL);

    if (GetTickCount () >= DueTime) {
      break;
    }

    Tcl_Sleep (Interval);
  }

  libnet_cq_remove(pLibNet);
  libnet_destroy (pLibNet);
  pcap_close (pPcap);
  return EFI_SUCCESS;

ErrorExit:
  return EFI_LOAD_ERROR;
}

EFI_STATUS
ResendCapturedPacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  Capture specified packets and resends them out.

Arguments:

  UserStr - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  EFI_SUCCESS    - Processing captured packets successfully.
  EFI_LOAD_ERROR - Some error happens.

--*/
{
  INT32 LoopIndex;

  for (LoopIndex = 0; LoopIndex < ReproducingCount; LoopIndex++) {
    if (-1 == libnet_adv_write_link (pLibNet, Packet, PktHdr->len)) {
      printf ("libnet_adv_write_link() failed");
      goto ErrorExit;
    }
  }

  return EFI_SUCCESS;

ErrorExit:
  return EFI_LOAD_ERROR;
}
