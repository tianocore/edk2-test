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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
