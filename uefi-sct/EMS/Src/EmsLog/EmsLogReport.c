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
  
    EmsLogReport.c
    
Abstract:

    Implementation for report library

--*/

#include <windows.h>
#include "EmsLogReport.h"
#include "EmsLogUtility.h"
#include "EmsUtilityString.h"

//
// internal functions
//
EFI_STATUS
SetReportItem (
  EMS_REPORT_INFOR      *ReportInfo,
  INT8                  *TestName,
  INT8                  *TestCategory,
  INT8                  *TestDescription,
  INT8                  *TestIndex,
  INT8                  *TestGuid,
  INT8                  *CaseStatus
  );

EFI_STATUS
GetReportInfo (
  EMS_REPORT_INFOR      *ReportInfo,
  HANDLE                ReportFile
  );

//
// strtok functions implementations
//
INT8  *___strtok_line   = NULL;
INT8  *___strtok_field  = NULL;

INT8  *
strtok_line (
  INT8                  *s,
  CONST INT8            *ct
  );

INT8  *
strtok_field (
  INT8                  *s,
  CONST INT8            *ct
  );

EFI_STATUS
GenerateReport (
  INT8                  *ReportName
  )
/*++

Routine Description:

  Generate the final log report for assertion

Arguments:

  ReportName  - the report file name

Returns:

  EFI_SUCCESS - Generate the final log report successfully
  OTHERS        - Something failed.

--*/
{
  HANDLE            CaseFile;
  HANDLE            ReportFile;
  HANDLE            ProtocolFind;
  HANDLE            LogFind;

  EMS_REPORT_INFOR  *ReportInfo;
  INT8              ProtocolDirFilter[EMS_MAX_PRINT_BUFFER];
  INT8              LogDirFilter[EMS_MAX_PRINT_BUFFER];
  INT8              FileNameBuffer[EMS_MAX_PRINT_BUFFER];
  INT8              FileBuffer[EMS_FILE_BUFFER_LEN];
  INT8              *LineBuffer;
  INT8              *NameBuf;
  INT8              *CategoryBuf;
  INT8              *DescriptionBuf;
  INT8              *IndexBuf;
  INT8              *GuidBuf;
  INT8              *CaseStatusBuf;
  BOOLEAN           ProtocolFinished;
  BOOLEAN           LogFinished;
  DWORD             nBytesRead;
  WIN32_FIND_DATA   FindFileData;
  WIN32_FIND_DATA   FindLogFileData;

  //
  // variable for assertion information
  //
  INT8              *DescriptionBufAssertion;
  INT8              *GuidBufAssertion;
  INT8              *AssertionStatusBuf;

  INT8              *CategoryBufAssertion;
  INT8              *NameBufAssertion;
  INT8              *IndexBufAssertion;
  EMS_REPORT_GUID   *ReportGuidOld;
  EMS_REPORT_GUID   *ReportGuidNew;
  EMS_REPORT_GUID   *ReportGuidTemp;

  EMS_REPORT_GUID   *ReportGuid;
  BOOLEAN           Search;

  ProtocolFinished  = FALSE;
  LogFinished       = FALSE;
  ReportGuid        = NULL;
  Search            = FALSE;

  if (ReportName == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ReportInfo = (EMS_REPORT_INFOR *) malloc (sizeof (EMS_REPORT_INFOR));
  if (ReportInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  memset (ReportInfo, 0, sizeof (EMS_REPORT_INFOR));

  //
  // open report file
  //
  CreateDirectory (EMS_REPORT_DIR, NULL);

  Sprint (FileNameBuffer, EMS_MAX_PRINT_BUFFER, "%a/%a", EMS_REPORT_DIR, ReportName);

  ReportFile = CreateFile (
                FileNameBuffer,           // file to create
                GENERIC_WRITE,            // open for writing
                0,                        // do not share
                NULL,                     // default security
                CREATE_ALWAYS,            // overwrite existing
                FILE_ATTRIBUTE_NORMAL,    // normal file
                NULL                      // no attr. template
                );

  if (ReportFile == INVALID_HANDLE_VALUE) {
    printf ("####Error: GenerateReport() Could not open file (error %d)\n", GetLastError ());
    return EFI_ACCESS_DENIED;
  }

  Sprint (ProtocolDirFilter, EMS_MAX_PRINT_BUFFER, "%a/%a", EMS_LOG_DIR, "*");
  ProtocolFind = FindFirstFile (ProtocolDirFilter, &FindFileData);
  if (ProtocolFind == INVALID_HANDLE_VALUE) {
    printf ("\n####Error: GenerateReport() - No Protocol dirs Found.");
    return EFI_SUCCESS;
  }

  while (!ProtocolFinished) {
    if (!FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      goto NextProtocol;
    }

    if (!strcmp (FindFileData.cFileName, ".") || !strcmp (FindFileData.cFileName, "..")) {
      goto NextProtocol;
    }

    Sprint (
      LogDirFilter,
      EMS_MAX_PRINT_BUFFER,
      "%a/%a/%a",
      EMS_LOG_DIR,
      FindFileData.cFileName,
      "*.ekl"
      );

    LogFind = FindFirstFile (LogDirFilter, &FindLogFileData);
    if (LogFind == INVALID_HANDLE_VALUE) {
      goto NextProtocol;
    }

    LogFinished = FALSE;
    while (!LogFinished) {
      if (FindLogFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        goto NextLog;
      }

      Sprint (
        FileNameBuffer,
        EMS_MAX_PRINT_BUFFER,
        "%a/%a/%a",
        EMS_LOG_DIR,
        FindFileData.cFileName,
        FindLogFileData.cFileName
        );

      CaseFile = CreateFile (
                  FileNameBuffer,         // file to open
                  GENERIC_READ,           // open for reading
                  FILE_SHARE_READ,        // share for reading
                  NULL,                   // default security
                  OPEN_EXISTING,          // existing file only
                  FILE_ATTRIBUTE_NORMAL,  // normal file
                  NULL                    // no attr. template
                  );
      if (CaseFile == INVALID_HANDLE_VALUE) {
        goto NextLog;
      }

      ReadFile (CaseFile, &FileBuffer, EMS_FILE_BUFFER_LEN, &nBytesRead, NULL);

      LineBuffer = strtok_line (FileBuffer, "\n");
      while (LineBuffer != NULL) {
        if (LineBuffer[0] == '|') {
          switch (LineBuffer[1]) {
          //
          // HEAD line
          //
          case 'H':
            strtok_field (LineBuffer, "|");
            //
            // HEAD
            //
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            //
            // date
            //
            strtok_field (NULL, "|");
            //
            // time
            //
            strtok_field (NULL, "|");
            //
            // guid
            //
            GuidBuf = strtok_field (NULL, "|");
            //
            // revision
            //
            strtok_field (NULL, "|");
            //
            //
            //
            IndexBuf = strtok_field (NULL, "|");
            //
            // name
            //
            NameBuf = strtok_field (NULL, "|");
            //
            // category
            //
            CategoryBuf = strtok_field (NULL, "|");
            //
            // description
            //
            DescriptionBuf = strtok_field (NULL, "|");
            break;

          //
          // TERM line
          //
          case 'T':
            strtok_field (LineBuffer, "|");
            //
            // TERM
            //
            strtok_field (NULL, "|");
            //
            // test status
            //
            strtok_field (NULL, "|");
            //
            // date
            //
            strtok_field (NULL, "|");
            //
            // time
            //
            strtok_field (NULL, "|");
            //
            // duration
            //
            strtok_field (NULL, "|");
            //
            // case status
            //
            CaseStatusBuf = strtok_field (NULL, "|");
            break;

          default:
            break;
          }
        } else {
          //
          // to deal with the assertion item line
          // read each assertion information, write to the report data structrue
          //
          // guid
          //
          GuidBufAssertion = strtok_field (LineBuffer, "|");
          //
          // assertion status
          //
          AssertionStatusBuf = strtok_field (NULL, "|");
          //
          // description
          //
          DescriptionBufAssertion = strtok_field (NULL, "\n");

          IndexBufAssertion       = IndexBuf;
          CategoryBufAssertion    = CategoryBuf;
          NameBufAssertion        = NameBuf;

          //
          // check whether the guid is exist in report_guid link
          //
          ReportGuidTemp = ReportGuid;

          while (ReportGuidTemp != NULL) {
            if (strcmp (GuidBufAssertion, ReportGuidTemp->Guid) != 0) {
              Search          = FALSE;
              ReportGuidTemp  = ReportGuidTemp->Next;
              continue;
            } else {
              Search          = TRUE;
              ReportGuidTemp  = NULL;
            }
          }

          if (Search == FALSE && strcmp (GuidBufAssertion, GenericGuid) != 0) {
            ReportGuidNew = (EMS_REPORT_GUID *) malloc (sizeof (EMS_REPORT_GUID));
            if (ReportGuidNew == NULL) {
              return EFI_OUT_OF_RESOURCES;
            }

            memcpy(ReportGuidNew->Guid, GuidBufAssertion, EMS_GUID_LEN);
            ReportGuidNew->GuidNumber++;

            ReportGuidNew->Prev = NULL;
            ReportGuidOld       = ReportGuid;
            ReportGuid          = ReportGuidNew;
            ReportGuidNew->Next = ReportGuidOld;
            if (ReportGuidOld != NULL) {
              ReportGuidOld->Prev = ReportGuidNew;
            }

            SetReportItem (
              ReportInfo,
              NameBufAssertion,
              CategoryBufAssertion,
              DescriptionBufAssertion,
              IndexBufAssertion,
              GuidBufAssertion,
              AssertionStatusBuf
              );
          }
        }

        LineBuffer = strtok_line (NULL, "\n");
        continue;
      }

      CloseHandle (CaseFile);

NextLog:
      if (!FindNextFile (LogFind, &FindLogFileData)) {
        if (GetLastError () == ERROR_NO_MORE_FILES) {
          LogFinished = TRUE;
        } else {
          LogFinished = TRUE;
        }
      }
    }

NextProtocol:
    if (!FindNextFile (ProtocolFind, &FindFileData)) {
      if (GetLastError () == ERROR_NO_MORE_FILES) {
        ProtocolFinished = TRUE;
      } else {
        ProtocolFinished = TRUE;
      }
    }
  }
  //
  // write the repotr information to the report file
  //
  GetReportInfo (ReportInfo, ReportFile);

  CloseHandle (ReportFile);

  free (ReportInfo);

  return EFI_SUCCESS;
}

EFI_STATUS
GenerateReportCase (
  INT8                  *ReportName
  )
/*++

Routine Description:

  Generate the final log report for case

Arguments:

  ReportName  - the report file name

Returns:

  EFI_SUCCESS - Generate the final log report successfully
  OTHERS        - Something failed.

--*/
{
  HANDLE            CaseFile;
  HANDLE            ReportFile;
  HANDLE            ProtocolFind;
  HANDLE            LogFind;

  EMS_REPORT_INFOR  *ReportInfo;
  INT8              ProtocolDirFilter[EMS_MAX_PRINT_BUFFER];
  INT8              LogDirFilter[EMS_MAX_PRINT_BUFFER];
  INT8              FileNameBuffer[EMS_MAX_PRINT_BUFFER];
  INT8              FileBuffer[EMS_FILE_BUFFER_LEN];
  INT8              *LineBuffer;
  INT8              *NameBuf;
  INT8              *CategoryBuf;
  INT8              *DescriptionBuf;
  INT8              *IndexBuf;
  INT8              *GuidBuf;
  INT8              *CaseStatusBuf;
  BOOLEAN           ProtocolFinished;
  BOOLEAN           LogFinished;
  DWORD             nBytesRead;
  WIN32_FIND_DATA   FindFileData;
  WIN32_FIND_DATA   FindLogFileData;

  ProtocolFinished  = FALSE;
  LogFinished       = FALSE;

  if (ReportName == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ReportInfo = (EMS_REPORT_INFOR *) malloc (sizeof (EMS_REPORT_INFOR));
  if (ReportInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  memset (ReportInfo, 0, sizeof (EMS_REPORT_INFOR));

  //
  // open report file
  //
  CreateDirectory (EMS_REPORT_DIR, NULL);

  Sprint (FileNameBuffer, EMS_MAX_PRINT_BUFFER, "%a/%a", EMS_REPORT_DIR, ReportName);

  ReportFile = CreateFile (
                FileNameBuffer,           // file to create
                GENERIC_WRITE,            // open for writing
                0,                        // do not share
                NULL,                     // default security
                CREATE_ALWAYS,            // overwrite existing
                FILE_ATTRIBUTE_NORMAL,    // normal file
                NULL                      // no attr. template
                );

  if (ReportFile == INVALID_HANDLE_VALUE) {
    printf ("####Error: GenerateReport() Could not open file (error %d)\n", GetLastError ());
    return EFI_ACCESS_DENIED;
  }

  Sprint (ProtocolDirFilter, EMS_MAX_PRINT_BUFFER, "%a/%a", EMS_LOG_DIR, "*");
  ProtocolFind = FindFirstFile (ProtocolDirFilter, &FindFileData);
  if (ProtocolFind == INVALID_HANDLE_VALUE) {
    printf ("\n####Error: GenerateReport() - No Protocol dirs Found.");
    return EFI_SUCCESS;
  }

  while (!ProtocolFinished) {
    if (!FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      goto NextProtocol;
    }

    if (!strcmp (FindFileData.cFileName, ".") || !strcmp (FindFileData.cFileName, "..")) {
      goto NextProtocol;
    }

    Sprint (
      LogDirFilter,
      EMS_MAX_PRINT_BUFFER,
      "%a/%a/%a",
      EMS_LOG_DIR,
      FindFileData.cFileName,
      "*.ekl"
      );

    LogFind = FindFirstFile (LogDirFilter, &FindLogFileData);
    if (LogFind == INVALID_HANDLE_VALUE) {
      goto NextProtocol;
    }

    LogFinished = FALSE;
    while (!LogFinished) {
      if (FindLogFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        goto NextLog;
      }

      Sprint (
        FileNameBuffer,
        EMS_MAX_PRINT_BUFFER,
        "%a/%a/%a",
        EMS_LOG_DIR,
        FindFileData.cFileName,
        FindLogFileData.cFileName
        );

      CaseFile = CreateFile (
                  FileNameBuffer,         // file to open
                  GENERIC_READ,           // open for reading
                  FILE_SHARE_READ,        // share for reading
                  NULL,                   // default security
                  OPEN_EXISTING,          // existing file only
                  FILE_ATTRIBUTE_NORMAL,  // normal file
                  NULL                    // no attr. template
                  );

      if (CaseFile == INVALID_HANDLE_VALUE) {
        goto NextLog;
      }

      ReadFile (CaseFile, &FileBuffer, EMS_FILE_BUFFER_LEN, &nBytesRead, NULL);

      LineBuffer = strtok_line (FileBuffer, "\n");
      while (LineBuffer != NULL) {
        if (LineBuffer[0] == '|') {
          switch (LineBuffer[1]) {
          //
          // HEAD line
          //
          case 'H':
            strtok_field (LineBuffer, "|");
            //
            // HEAD
            //
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            strtok_field (NULL, "|");
            //
            // date
            //
            strtok_field (NULL, "|");
            //
            // time
            //
            strtok_field (NULL, "|");
            //
            // guid
            //
            GuidBuf = strtok_field (NULL, "|");
            //
            // revision
            //
            strtok_field (NULL, "|");
            //
            //
            //
            IndexBuf = strtok_field (NULL, "|");
            //
            // name
            //
            NameBuf = strtok_field (NULL, "|");
            //
            // category
            //
            CategoryBuf = strtok_field (NULL, "|");
            //
            // description
            //
            DescriptionBuf = strtok_field (NULL, "|");
            break;

          //
          // TERM line
          //
          case 'T':
            strtok_field (LineBuffer, "|");
            //
            // TERM
            //
            strtok_field (NULL, "|");
            //
            // test status
            //
            strtok_field (NULL, "|");
            //
            // date
            //
            strtok_field (NULL, "|");
            //
            // time
            //
            strtok_field (NULL, "|");
            //
            // duration
            //
            strtok_field (NULL, "|");
            //
            // case status
            //
            CaseStatusBuf = strtok_field (NULL, "|");
            break;

          default:
            break;
          }
        }

        LineBuffer = strtok_line (NULL, "\n");
        continue;
      }

      CloseHandle (CaseFile);

      //
      // read each case information, write to the report data structrue
      // If IndexBuf is NULL, the ekl file should be NULL.
      //
      if (IndexBuf != NULL) {
      SetReportItem (
        ReportInfo,
        NameBuf,
        CategoryBuf,
        DescriptionBuf,
        IndexBuf,
        GuidBuf,
        CaseStatusBuf
        );
      }

NextLog:
      if (!FindNextFile (LogFind, &FindLogFileData)) {
        if (GetLastError () == ERROR_NO_MORE_FILES) {
          LogFinished = TRUE;
        } else {
          LogFinished = TRUE;
        }
      }
    }

NextProtocol:
    if (!FindNextFile (ProtocolFind, &FindFileData)) {
      if (GetLastError () == ERROR_NO_MORE_FILES) {
        ProtocolFinished = TRUE;
      } else {
        ProtocolFinished = TRUE;
      }
    }
  }
  //
  // write the repotr information to the report file
  //
  GetReportInfo (ReportInfo, ReportFile);

  CloseHandle (ReportFile);

  free (ReportInfo);

  return EFI_SUCCESS;
}

EFI_STATUS
SetReportItem (
  EMS_REPORT_INFOR      *ReportInfo,
  INT8                  *TestName,
  INT8                  *TestCategory,
  INT8                  *TestDescription,
  INT8                  *TestIndex,
  INT8                  *TestGuid,
  INT8                  *CaseStatus
  )
/*++

Routine Description:

  Set the report item to the report infor struct

Arguments:

  ReportInfo      - the report infor struct
  TestName        - the test name
  TestCategory    - the test category
  TestDescription - the test description
  TestIndex       - the test index
  TestGuid        - the test guid
  CaseStatus      - the test case status

Returns:

  EFI_SUCCESS - Set the report item successfully
  OTHERS        - Something failed.

--*/
{
  EMS_REPORT_ITEM *ReportItem;
  EMS_REPORT_ITEM *NewReportItem;
  EMS_CASE_INFOR  *CaseInfor;
  EMS_CASE_INFOR  *NewCaseInfor;

  ReportItem    = NULL;
  NewReportItem = NULL;
  CaseInfor     = NULL;
  NewCaseInfor  = NULL;

  if ((CaseStatus == NULL) || (ReportInfo == NULL) || (TestName == NULL) || 
  	  (TestCategory == NULL) || (TestDescription == NULL) || (TestIndex == NULL) ||
  	  (TestGuid == NULL)) {
  	return EFI_INVALID_PARAMETER;
  }

  //
  // search each report item
  //
  ReportItem = ReportInfo->ReportItem;
  while (ReportItem != NULL) {
    if (strcmp (ReportItem->TestCategory, TestCategory) != 0) {
      ReportItem = ReportItem->Next;
      continue;
    }
    //
    // create a new case infor
    //
    NewCaseInfor = (EMS_CASE_INFOR *) malloc (sizeof (EMS_CASE_INFOR));
    if (NewCaseInfor == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    memset (NewCaseInfor, 0, sizeof (EMS_CASE_INFOR));
    strcpy (NewCaseInfor->Index, TestIndex);
    strcpy (NewCaseInfor->TestName, TestName);
    strcpy (NewCaseInfor->TestDescription, TestDescription);
    strcpy (NewCaseInfor->Guid, TestGuid);

    if (strcmp (CaseStatus, "PASS") == 0) {
      ReportInfo->TotalPass++;
      ReportItem->PassNumber++;

      //
      // add the new case infor to the report item
      //
      NewCaseInfor->Prev    = NULL;
      CaseInfor             = ReportItem->PassCase;
      ReportItem->PassCase  = NewCaseInfor;
      NewCaseInfor->Next    = CaseInfor;
      if (CaseInfor != NULL) {
        CaseInfor->Prev = NewCaseInfor;
      }
    } else if (strcmp (CaseStatus, "WARNING") == 0) {
      ReportInfo->TotalWarn++;
      ReportItem->WarnNumber++;
    } else if (strcmp (CaseStatus, "FAILURE") == 0) {
      ReportInfo->TotalFail++;
      ReportItem->FailNumber++;

      //
      // add the new case infor to the report item
      //
      NewCaseInfor->Prev    = NULL;
      CaseInfor             = ReportItem->FailCase;
      ReportItem->FailCase  = NewCaseInfor;
      NewCaseInfor->Next    = CaseInfor;

      if (CaseInfor != NULL) {
        CaseInfor->Prev = NewCaseInfor;
      }
    } else {
      return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
  }
  //
  // not found
  //
  //
  // create a new report item
  //
  NewReportItem = (EMS_REPORT_ITEM *) malloc (sizeof (EMS_REPORT_ITEM));
  if (NewReportItem == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  memset (NewReportItem, 0, sizeof (EMS_REPORT_ITEM));
  NewReportItem->PassNumber = 0;
  NewReportItem->WarnNumber = 0;
  NewReportItem->FailNumber = 0;
  strcpy (NewReportItem->TestCategory, TestCategory);
  NewReportItem->FailCase = NULL;
  NewReportItem->PassCase = NULL;

  //
  // add the new report item to the report infor
  //
  NewReportItem->Prev     = NULL;
  ReportItem              = ReportInfo->ReportItem;
  ReportInfo->ReportItem  = NewReportItem;
  NewReportItem->Next     = ReportItem;
  if (ReportItem != NULL) {
    ReportItem->Prev = NewReportItem;
  }

  ReportItem = NewReportItem;

  //
  // create a new case infor
  //
  NewCaseInfor = (EMS_CASE_INFOR *) malloc (sizeof (EMS_CASE_INFOR));
  if (NewCaseInfor == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  memset (NewCaseInfor, 0, sizeof (EMS_CASE_INFOR));
  strcpy (NewCaseInfor->Index, TestIndex);
  strcpy (NewCaseInfor->TestName, TestName);
  strcpy (NewCaseInfor->TestDescription, TestDescription);
  strcpy (NewCaseInfor->Guid, TestGuid);

  if (strcmp (CaseStatus, "PASS") == 0) {
    ReportInfo->TotalPass++;
    ReportItem->PassNumber++;
    //
    // add the new case infor to the report item
    //
    NewCaseInfor->Prev    = NULL;
    CaseInfor             = ReportItem->PassCase;
    ReportItem->PassCase  = NewCaseInfor;
    NewCaseInfor->Next    = CaseInfor;
    if (CaseInfor != NULL) {
      CaseInfor->Prev = NewCaseInfor;
    }
  } else if (strcmp (CaseStatus, "WARNING") == 0) {
    ReportInfo->TotalWarn++;
    ReportItem->WarnNumber++;
  } else if (strcmp (CaseStatus, "FAILURE") == 0) {
    ReportInfo->TotalFail++;
    ReportItem->FailNumber++;

    //
    // add the new case infor to the report item
    //
    NewCaseInfor->Prev    = NULL;
    CaseInfor             = ReportItem->FailCase;
    ReportItem->FailCase  = NewCaseInfor;
    NewCaseInfor->Next    = CaseInfor;
    if (CaseInfor != NULL) {
      CaseInfor->Prev = NewCaseInfor;
    }
  } else {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetReportInfo (
  EMS_REPORT_INFOR      *ReportInfo,
  HANDLE                ReportFile
  )
/*++

Routine Description:

  Get the report infor struct, and set to the report file

Arguments:

  ReportInfo  - the report infor struct
  ReportFile  - the report file

Returns:

  EFI_SUCCESS - Set the report file successfully
  OTHERS        - Something failed.

--*/
{
  INT8            Buffer[EMS_MAX_PRINT_BUFFER];
  EMS_REPORT_ITEM *ReportItemHead;
  EMS_REPORT_ITEM *ReportItemTerm;
  EMS_CASE_INFOR  *CaseInforHead;
  EMS_CASE_INFOR  *CaseInforTerm;
  DWORD           nBytesWriteData;

  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\"EFI Network Test Suite Report\"\n");
  WriteFile (
    ReportFile,
    Buffer,
    strlen (Buffer),
    &nBytesWriteData,
    NULL
    );

  //
  // add summary part "Protocol Name","Total","Failed","Passed"
  //
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\"Protocol Name\",\"Total\",\"Failed\",\"Passed\"\n");
  WriteFile (
    ReportFile,
    Buffer,
    strlen (Buffer),
    &nBytesWriteData,
    NULL
    );

  ReportItemHead  = ReportInfo->ReportItem;
  ReportItemTerm  = NULL;
  while (ReportItemHead != NULL) {
    ReportItemTerm  = ReportItemHead;
    ReportItemHead  = ReportItemHead->Next;
  }
  //
  // search each report item
  //
  while (ReportItemTerm != NULL) {
    //
    // add each protocol infor
    //
    Sprint (
      Buffer,
      EMS_MAX_PRINT_BUFFER,
      "\"%a\",\"%d\",\"%d\",\"%d\"\n",
      ReportItemTerm->TestCategory,
      ReportItemTerm->PassNumber + ReportItemTerm->FailNumber,
      ReportItemTerm->FailNumber,
      ReportItemTerm->PassNumber
      );
    WriteFile (
      ReportFile,
      Buffer,
      strlen (Buffer),
      &nBytesWriteData,
      NULL
      );

    ReportItemTerm = ReportItemTerm->Prev;
  }
  //
  // add total infor
  //
  Sprint (
    Buffer,
    EMS_MAX_PRINT_BUFFER,
    "\"Total Protocol\",\"%d\",\"%d\",\"%d\"\n",
    ReportInfo->TotalPass + ReportInfo->TotalFail,
    ReportInfo->TotalFail,
    ReportInfo->TotalPass
    );
  WriteFile (
    ReportFile,
    Buffer,
    strlen (Buffer),
    &nBytesWriteData,
    NULL
    );

  //
  // add fail detail part "Category","Guid","Result","Name","Description"
  //
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\n\"Category\",\"Guid\",\"Result\",\"Name\",\"Description\"\n");
  WriteFile (
    ReportFile,
    Buffer,
    strlen (Buffer),
    &nBytesWriteData,
    NULL
    );

  ReportItemHead  = ReportInfo->ReportItem;
  ReportItemTerm  = NULL;
  while (ReportItemHead != NULL) {
    ReportItemTerm  = ReportItemHead;
    ReportItemHead  = ReportItemHead->Next;
  }
  //
  // search each report item
  //
  while (ReportItemTerm != NULL) {
    CaseInforHead = ReportItemTerm->FailCase;
    CaseInforTerm = NULL;
    while (CaseInforHead != NULL) {
      CaseInforTerm = CaseInforHead;
      CaseInforHead = CaseInforHead->Next;
    }
    //
    // search each case infor
    //
    while (CaseInforTerm != NULL) {
      //
      // add each case infor
      //
      Sprint (
        Buffer,
        EMS_MAX_PRINT_BUFFER,
        "\"%a\",\"%a\",\"FAILED\",\"%a\",\"%a\"\n",
        ReportItemTerm->TestCategory,
        CaseInforTerm->Guid,
        CaseInforTerm->TestName,
        CaseInforTerm->TestDescription
        );
      WriteFile (
        ReportFile,
        Buffer,
        strlen (Buffer),
        &nBytesWriteData,
        NULL
        );
      CaseInforTerm = CaseInforTerm->Prev;
    }

    ReportItemTerm = ReportItemTerm->Prev;
  }
  //
  // add pass detail part "Category","Guid","Result","Name","Description"
  //
  Sprint (Buffer, EMS_MAX_PRINT_BUFFER, "\n\"Category\",\"Guid\",\"Result\",\"Name\",\"Description\"\n");
  WriteFile (
    ReportFile,
    Buffer,
    strlen (Buffer),
    &nBytesWriteData,
    NULL
    );

  ReportItemHead  = ReportInfo->ReportItem;
  ReportItemTerm  = NULL;
  while (ReportItemHead != NULL) {
    ReportItemTerm  = ReportItemHead;
    ReportItemHead  = ReportItemHead->Next;
  }
  //
  // search each report item
  //
  while (ReportItemTerm != NULL) {
    CaseInforHead = ReportItemTerm->PassCase;
    CaseInforTerm = NULL;
    while (CaseInforHead != NULL) {
      CaseInforTerm = CaseInforHead;
      CaseInforHead = CaseInforHead->Next;
    }
    //
    // search each case infor
    //
    while (CaseInforTerm != NULL) {
      //
      // add each case infor
      //
      Sprint (
        Buffer,
        EMS_MAX_PRINT_BUFFER,
        "\"%a\",\"%a\",\"PASSED\",\"%a\",\"%a\"\n",
        ReportItemTerm->TestCategory,
        CaseInforTerm->Guid,
        CaseInforTerm->TestName,
        CaseInforTerm->TestDescription
        );
      WriteFile (
        ReportFile,
        Buffer,
        strlen (Buffer),
        &nBytesWriteData,
        NULL
        );
      CaseInforTerm = CaseInforTerm->Prev;
    }

    ReportItemTerm = ReportItemTerm->Prev;
  }
  //
  // free the resource
  //
  ReportItemHead = ReportInfo->ReportItem;
  while (ReportItemHead != NULL) {
    CaseInforHead = ReportItemHead->FailCase;
    while (CaseInforHead != NULL) {
      //
      // free the case_infor
      //
      CaseInforTerm             = CaseInforHead->Next;
      ReportItemHead->FailCase  = CaseInforTerm;
      free (CaseInforHead);
      CaseInforHead = ReportItemHead->FailCase;
    }

    CaseInforHead = ReportItemHead->PassCase;
    while (CaseInforHead != NULL) {
      //
      // free the case_infor
      //
      CaseInforTerm             = CaseInforHead->Next;
      ReportItemHead->PassCase  = CaseInforTerm;
      free (CaseInforHead);
      CaseInforHead = ReportItemHead->PassCase;
    }
    //
    // free the report_item
    //
    ReportItemTerm          = ReportItemHead->Next;
    ReportInfo->ReportItem  = ReportItemTerm;
    free (ReportItemHead);
    ReportItemHead = ReportInfo->ReportItem;
  }

  return EFI_SUCCESS;
}

INT8 *
strtok_line (
  INT8                  *s,
  CONST INT8            *ct
  )
/*++

Routine Description:

  find the next token in a string

Arguments:

  s   - the string
  ct  - the cutter

Returns:

  the start char pointer

--*/
{
  INT8  *sbegin;
  INT8  *send;

  sbegin = s ? s : ___strtok_line;
  if (!sbegin) {
    return NULL;
  }

  sbegin += strspn (sbegin, ct);

  if (*sbegin == '\0') {
    ___strtok_line = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___strtok_line = send;
  return sbegin;
}

INT8 *
strtok_field (
  INT8                  *s,
  CONST INT8            *ct
  )
/*++

Routine Description:

  find the next token in a string

Arguments:

  s   - the string
  ct  - the cutter

Returns:

  the start char pointer

--*/
{
  INT8  *sbegin;
  INT8  *send;

  sbegin = s ? s : ___strtok_field;
  if (!sbegin) {
    return NULL;
  }
  //
  // Difference with strtok_line()
  // do not find the first substring, just use this char as begin
  //
  if (*sbegin == '\0') {
    ___strtok_field = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___strtok_field = send;
  return sbegin;
}
