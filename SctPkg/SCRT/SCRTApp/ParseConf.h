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

  ParseConf.h

--*/

#include "SctLib.h"


#define CONF_FILE_NAME                    L"SCRT.conf"
#define CONF_FILE_SIZE                    (1024*1024)
#define CONFIGURE_INFO_SIGNATURE          0x5AA5

//
// Configuration file strings
//
#define VARIABLE_SECTION_STRING            "[variable]"
#define TIME_SECTION_STRING                "[time]"
#define CAPSULE_SECTION_STRING             "[capsule]"
#define MONOTONICCOUNT_SECTION_STRING      "[monotonicCount]"
#define RESET_SECTION_STRING               "[reset]"

#define GET_VARIABLE_STRING                "GetVariable"
#define SET_VARIABLE_STRING                "SetVariable"
#define GET_NEXT_VARIABLE_NAME_STRING      "GetNextVariableName"
#define QUERY_VARIABLE_INFO_STRING         "QueryVariableInfo"
#define GET_TIME_STRING                    "GetTime"
#define SET_TIME_STRING                    "SetTime"
#define GET_WAKEUP_TIME_STRING             "GetWakeupTime"
#define SET_WAKEUP_TIME_STRING             "SetWakeupTime"
#define UPDATE_CAPSULE_STRING              "UpdateCapsule"
#define QUERY_CAPSULE_CAPABILITIES_STRING  "QueryCapsuleCapabilities"
#define GET_NEXT_HIGH_MONOTONIC_STRING     "GetNextHighMonotonicCount"
#define COLD_RESET_STRING                  "ColdReset"
#define WARM_RESET_STRING                  "WarmReset"
#define SHUT_DOWN_STRING                   "ShutDown"
#define TRUE_STRING                        "TRUE"
#define FALSE_STRING                       "FALSE"
#define _MAX_PATH                          260


typedef struct {
  UINT8 *FileImage;
  CHAR8 *Eof;
  CHAR8 *CurrentFilePointer;
} MEMORY_FILE;


//
// Configuration File Info
//
typedef union _CONF_INFO
{
  struct {
  UINT32 SetVariable        : 1;
  UINT32 GetVariable        : 1;
  UINT32 GetNextVariable    : 1;
  UINT32 QueryVariable      : 1;
  UINT32 GetTime            : 1;
  UINT32 SetTime            : 1;
  UINT32 SetWakeupTime      : 1;
  UINT32 GetWakeupTime      : 1;
  UINT32 QueryCapsule       : 1;
  UINT32 UpdateCapsule      : 1;
  UINT32 GetNextCount       : 1;
  UINT32 ColdReset          : 1;
  UINT32 WarmReset          : 1;
  UINT32 ShutDown           : 1;
  UINT32 Reserved           : 2;
  UINT32 Signature          : 16;
  } BitMap;
  UINT32  InfoData;
} CONF_INFO;


typedef struct _DEBUGGER_INFO {
  BOOLEAN               MmioFlag;
  UINTN                 IoPort;
  UINTN                 IoBase;
  UINTN                 MmioBase;
} DEBUGGER_INFO;



typedef struct  _RUNTIME_HANDOFF{
  CONF_INFO         ConfigureInfo;
  DEBUGGER_INFO     DebuggerInfo;
}RUNTIME_HANDOFF; 


VOID
ParseConf (
  IN MEMORY_FILE  *InfFile,
  IN CONF_INFO    *FileInfo
  )
/*++

Routine Description:

  This function parses a configuration file and copies info into a CONF_INFO structure.

Arguments:

  InfFile    -     Memory file image.
  FileInfo   -     Information read from INF file.
  
Returns:

  NONE
  
--*/
;

EFI_STATUS
RuntimeHandOff (
  IN CONF_INFO               *ConfInfo,
  OUT UINTN                  *HandOffAddr
  );  
