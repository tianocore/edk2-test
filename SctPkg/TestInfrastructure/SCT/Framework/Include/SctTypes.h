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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SctTypes.h

Abstract:

  This file defines the global types and structures of SCT.

--*/

#ifndef _EFI_SCT_TYPES_H_
#define _EFI_SCT_TYPES_H_

//
// EFI_SCT_CONFIG_DATA
//

#define EFI_SCT_CONFIG_DATA_SIGNATURE       EFI_SIGNATURE_32('s','c','f','g')
#define EFI_SCT_CONFIG_DATA_REVISION        0x00010000

#define TEST_CASE_MAX_RUN_TIME_DEFAULT      0
#define ENABLE_SCREEN_OUTPUT_DEFAULT        TRUE
#define BIOS_ID_DEFAULT                     L"UEFI 2.4A"
#define PLATFORM_NUMBER_DEFAULT             0
#define CONFIGURATION_NUMBER_DEFAULT        0
#define SCENARIO_STRING_DEFAULT             L""
#define EDIT_COMMAND_DEFAULT                L"edit"
#define DEFAULT_SCT_DIRECTORY   L"SCT"

#define TEST_CASE_MAX_RUN_TIME_MIN          0

#define PLATFORM_NUMBER_MAX                 0x7FFFFFFF
#define PLATFORM_NUMBER_MIN                 0

#define CONFIGURATION_NUMBER_MAX            0x7FFFFFFF
#define CONFIGURATION_NUMBER_MIN            0

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  UINTN                     TestCaseMaxRunTime;
  BOOLEAN                   EnableScreenOutput;

  CHAR16                    *BiosId;
  UINTN                     PlatformNumber;
  UINTN                     ConfigurationNumber;
  CHAR16                    *ScenarioString;

  CHAR16                    *EditCommandString;

  EFI_TEST_LEVEL            TestLevel;
  EFI_VERBOSE_LEVEL         VerboseLevel;
} EFI_SCT_CONFIG_DATA;

//
// EFI_SCT_CATEGORY_DATA
//

#define EFI_SCT_CATEGORY_DATA_SIGNATURE     EFI_SIGNATURE_32('s','c','a','t')
#define EFI_SCT_CATEGORY_DATA_REVISION      0x00010000

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  SCT_LIST_ENTRY            Link;

  UINTN                     Index;
  EFI_GUID                  CategoryGuid;
  EFI_GUID                  InterfaceGuid;
  CHAR16                    *Name;
  CHAR16                    *Description;
} EFI_SCT_CATEGORY_DATA;

//
// EFI_SCT_TEST_CASE
//

#define EFI_SCT_TEST_CASE_SIGNATURE         EFI_SIGNATURE_32('s','t','c','s')
#define EFI_SCT_TEST_CASE_REVISION          0x00010000

#define EFI_SCT_TEST_CASE_INVALID           0xFFFFFFFF
#define EFI_SCT_TEST_CASE_RUNNING           0xFFFFFFFE

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  SCT_LIST_ENTRY            Link;

  EFI_GUID                  Guid;
  CHAR16                    *Name;

  UINT32                    Order;
  UINT32                    Iterations;
  UINT32                    Passes;
  UINT32                    Warnings;
  UINT32                    Failures;
} EFI_SCT_TEST_CASE;


//
// EFI_SCT_TEST_FILE
//

#define EFI_SCT_TEST_FILE_SIGNATURE         EFI_SIGNATURE_32('s','t','f','l')
#define EFI_SCT_TEST_FILE_REVISION          0x00010000

typedef UINTN EFI_SCT_TEST_FILE_TYPE;

#define EFI_SCT_TEST_FILE_TYPE_UNKNOWN      0x00
#define EFI_SCT_TEST_FILE_TYPE_BLACK_BOX    0x01
#define EFI_SCT_TEST_FILE_TYPE_WHITE_BOX    0x02
#define EFI_SCT_TEST_FILE_TYPE_APPLICATION  0x03
#define EFI_SCT_TEST_FILE_TYPE_SCRIPT       0x04
#define EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX   0x05
#define EFI_SCT_TEST_FILE_TYPE_SUPPORT      0x80

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  SCT_LIST_ENTRY            Link;

  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *FileName;
  EFI_HANDLE                ImageHandle;

  EFI_SCT_TEST_FILE_TYPE    Type;
  VOID                      *Context;
} EFI_SCT_TEST_FILE;

//
// EFI_SCT_TEST_NODE
//

#define EFI_SCT_TEST_NODE_SIGNATURE         EFI_SIGNATURE_32('s','t','n','d')
#define EFI_SCT_TEST_NODE_REVISION          0x00010000

typedef UINT32 EFI_SCT_TEST_NODE_TYPE;

#define EFI_SCT_TEST_NODE_TYPE_UNKNOWN      0x00
#define EFI_SCT_TEST_NODE_TYPE_CATEGORY     0x01
#define EFI_SCT_TEST_NODE_TYPE_CASE         0x02

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  SCT_LIST_ENTRY            Link;
  SCT_LIST_ENTRY            Child;

  UINTN                     Index;
  CHAR16                    *Name;
  CHAR16                    *Description;

  EFI_SCT_TEST_NODE_TYPE    Type;
  EFI_GUID                  Guid;
} EFI_SCT_TEST_NODE;

//
// EFI_SCT_LOG_STATE
//

typedef UINTN EFI_SCT_LOG_STATE;

#define EFI_SCT_LOG_STATE_UNKNOWN           0x00
#define EFI_SCT_LOG_STATE_EMPTY             0x01
#define EFI_SCT_LOG_STATE_RUNNING           0x02
#define EFI_SCT_LOG_STATE_FINISHED          0x03

//
// EFI_SCT_TEST_STATE
//

typedef UINTN EFI_SCT_TEST_STATE;

#define EFI_SCT_TEST_STATE_UNKNOWN          0x00
#define EFI_SCT_TEST_STATE_NOT_IN_LIST      0x01
#define EFI_SCT_TEST_STATE_READY            0x02
#define EFI_SCT_TEST_STATE_RUNNING          0x03
#define EFI_SCT_TEST_STATE_FINISHED         0x04

//
// EFI_SCT_OPERTAIONS
//

typedef UINTN EFI_SCT_OPERATIONS;

#define EFI_SCT_OPERATIONS_NONE             0x0000
#define EFI_SCT_OPERATIONS_INVALID          0xFFFF

#define EFI_SCT_OPERATIONS_HIGH_MASK        0xFF00
#define EFI_SCT_OPERATIONS_LOW_MASK         0x00FF

#define EFI_SCT_OPERATIONS_ALL              0x0001
#define EFI_SCT_OPERATIONS_CONTINUE         0x0002
#define EFI_SCT_OPERATIONS_SEQUENCE         0x0004
#define EFI_SCT_OPERATIONS_UI               0x0008
#define EFI_SCT_OPERATIONS_PASSIVEMODE      0x0010

#define EFI_SCT_OPERATIONS_RESET            0x0100
#define EFI_SCT_OPERATIONS_REPORT           0x0200
#define EFI_SCT_OPERATIONS_VERBOSE          0x0400
#define EFI_SCT_OPERATIONS_EXTENDED         0x8000
//
// SKIPPED_CASE
//

#define EFI_SCT_SKIPPED_CASE_SIGNATURE         EFI_SIGNATURE_32('s','s','c','s')
#define EFI_SCT_SKIPPED_CASE_REVISION          0x00010000

typedef struct {
  UINT32                              Signature;
  UINT32                              Revision;
  
  SCT_LIST_ENTRY                      Link;
  CHAR16                              *CaseName;
  EFI_GUID                            CaseGuid;

  CHAR16                              *ProtocolName;
  EFI_GUID                            ProtocolGuid;

  UINT32                              Order;
  
} EFI_SCT_SKIPPED_CASE;

//
// EFI_SCT_FRAMEWORK_TABLE
//

#define EFI_SCT_FRAMEWORK_TABLE_SIGNATURE   EFI_SIGNATURE_32('s','f','w','t')
#define EFI_SCT_FRAMEWORK_TABLE_REVISION    0x00010000

typedef struct {
  UINT32                              Signature;
  UINT32                              Revision;

  //
  // Image data
  //
  EFI_HANDLE                          ImageHandle;
  EFI_SYSTEM_TABLE                    *SystemTable;

  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FilePath;

  //
  // Monitor name for Communication layer
  //
  CHAR16                              *MonitorName;
  
  //
  // Test data
  //
  EFI_SCT_OPERATIONS                  Operations;
  CHAR16                              *SeqFileName;
  CHAR16                              *RepFileName;
  CHAR16                              *TestCaseFileName;

  BOOLEAN                             IsFirstTimeExecute;

  EFI_INI_FILE_HANDLE                 TestCaseIniFile;

  EFI_SCT_CONFIG_DATA                 *ConfigData;

  SCT_LIST_ENTRY                      CategoryList;

  SCT_LIST_ENTRY                      TestFileList;
  SCT_LIST_ENTRY                      SupportFileList;
  SCT_LIST_ENTRY                      ProxyFileList;

  SCT_LIST_ENTRY                      TestCaseList;
  SCT_LIST_ENTRY                      TestNodeList;

  SCT_LIST_ENTRY                      SkippedCaseList;
  //
  // Test support data
  //
  EFI_HANDLE                          SupportHandle;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StslProtocol;
  EFI_STANDARD_TSL_PRIVATE_INTERFACE  *StslInterface;

  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *TplProtocol;

  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *TllProtocol;
  EFI_TLL_PRIVATE_INTERFACE           *TllInterface;

  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *TrlProtocol;
  EFI_TRL_PRIVATE_INTERFACE           *TrlInterface;

  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL    *TolProtocol;
} EFI_SCT_FRAMEWORK_TABLE;

//
// MDK_LIBRARY_INSTAMCE
//

#define MDK_LIBRARY_INSTANCE_SIGNATURE         EFI_SIGNATURE_32('m','d','k','l')
#define MDK_LIBRARY_INSTANCE_REVISION          0x00010000

typedef struct {
  UINT32                    Signature;
  UINT32                    Revision;

  SCT_LIST_ENTRY            Link;

  CHAR16                    *Name;
  VOID                      *Interface;
} MDK_LIBRARY_INSTANCE;

#endif
