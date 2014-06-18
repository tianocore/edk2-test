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

  EasType.h

Abstract:

  ENTS Typ edefinitions.

--*/
#ifndef _EAS_TYPE_H_
#define _EAS_TYPE_H_

//
// EFI_NETWORK_TEST_FILE
//
#define EFI_NETWORK_TEST_FILE_SIGNATURE   EFI_SIGNATURE_32 ('n', 't', 'f', 'l')
#define EFI_NETWORK_TEST_FILE_VERSION     0x10

#define EFI_NETWORK_TEST_FILE_UNKNOWN     0x00
#define EFI_NETWORK_TEST_FILE_DRIVER      0x01
#define EFI_NETWORK_TEST_FILE_APPLICATION 0x02
#define EFI_NETWORK_TEST_FILE_SCRIPT      0x03
#define EFI_NETWORK_TEST_FILE_PY_SCRIPT   0x04
#define EFI_NETWORK_TEST_FILE_SUPPORT     0x05

typedef struct _EFI_NETWORK_TEST_FILE {
  UINT32                    Signature;
  UINTN                     Version;

  SCT_LIST_ENTRY            Link;

  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *FileName;
  CHAR16                    *CmdName;
  EFI_HANDLE                ImageHandle;

  UINTN                     Type;
  VOID                      *Context;
} EFI_NETWORK_TEST_FILE;

//
// ENTS_MONITOR_COMMAND
//
typedef enum {
  ELET_CMD          = 1,
  RIVL_DEFTYPE,
  RIVL_CRTVAR,
  RIVL_SETVAR,
  RIVL_GETVAR,
  RIVL_DELTYPE,
  RIVL_DELVAR,
  ABORT,
  EXECUTE,
  RUNTIME_INFO_REQ,
  RUNTIME_INFO_CLEAR,
  GET_FILE,
  PUT_FILE,
} ENTS_CMD_TYPE;

typedef enum _ENTS_CMD_RESULT
{
  PASS,
  FAIL,
} ENTS_CMD_RESULT;

#define EFI_MONITOR_COMMAND_SIGNATURE EFI_SIGNATURE_32 ('n', 's', 'c', 'd')
#define EFI_MONITOR_COMMAND_VERSION   0x10

typedef struct _EFI_MONITOR_COMMAND {
  UINT32                Signature;
  UINTN                 Version;

  CHAR16                *ComdName;
  CHAR16                *ComdArg;

  CHAR16                *ComdRuntimeInfo;
  UINTN                 ComdRuntimeInfoSize;

  CHAR16                *ComdOutput;
  UINTN                 ComdOutputSize;

  ENTS_CMD_RESULT       ComdResult;
  ENTS_CMD_TYPE         CmdType;

  EFI_NETWORK_TEST_FILE *TestFile;
  CHAR16                *ComdInterface;
} EFI_MONITOR_COMMAND;

//
// EFI_SCT_FRAMEWORK_TABLE
//
#define EFI_NETWORK_TEST_FRAMEWORK_TABLE_SIGNATURE  EFI_SIGNATURE_32 ('n', 'f', 'w', 't')
#define EFI_NETWORK_TEST_FRAMEWORK_TABLE_VERSION    0x10

typedef struct _EFI_NETWORK_TEST_FRAMEWORK_TABLE {
  UINT32                    Signature;
  UINTN                     Version;

  //
  // Image data
  //
  EFI_HANDLE                ImageHandle;
  EFI_SYSTEM_TABLE          *SystemTable;

  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *FilePath;

  //
  // Test data
  //
  SCT_LIST_ENTRY            TestAppList;

  //
  // Test support list
  //
  SCT_LIST_ENTRY            SupportList;

  //
  // Test support data
  //
  VOID                      *Monitor;
  EFI_MONITOR_COMMAND       *Cmd;
} EFI_NETWORK_TEST_FRAMEWORK_TABLE;

//
// Data type
//
#define OCTET1  0x11
#define OCTET2  0x12
#define OCTET4  0x13
#define OCTET8  0x14
#define OCTETN  0x15
#define BOOL    0x16
#define POINTER 0x17

#endif
