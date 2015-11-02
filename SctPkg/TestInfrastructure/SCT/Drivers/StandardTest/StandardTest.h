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

  StandardTest.h

Abstract:

  Driver to publish the Standard Test Library Protocol.

--*/

#ifndef _EFI_STANDARD_TEST_H_
#define _EFI_STANDARD_TEST_H_

//
// Includes
//

#include "LibPrivate.h"


//
// Global definitions
//

#define EFI_MAX_PRINT_BUFFER                1024

//
// Private data structures
//

#define STANDARD_TEST_PRIVATE_DATA_SIGNATURE  EFI_SIGNATURE_32('S','T','S','L')

typedef struct {
  BOOLEAN                                   EnableScreenOutput;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FileName;
  BOOLEAN                                   OverwriteFile;
  EFI_FILE_HANDLE                           FileHandle;
} EFI_LIB_CONFIG_FILE_HANDLE;

typedef struct {
  UINT32                                    Signature;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL        StandardTest;
  EFI_STANDARD_TSL_PRIVATE_INTERFACE        PrivateInterface;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *OutputProtocol;

  EFI_LIB_CONFIG_FILE_HANDLE                SystemLogFile;
  EFI_LIB_CONFIG_FILE_HANDLE                SystemKeyFile;
  EFI_LIB_CONFIG_FILE_HANDLE                CaseLogFile;
  EFI_LIB_CONFIG_FILE_HANDLE                CaseKeyFile;

  CHAR16                                    *BiosId;
  UINT32                                    PlatformNumber;
  UINT32                                    ConfigurationNumber;
  CHAR16                                    *ScenarioString;

  UINT64                                    TestRevision;
  CHAR16                                    *TestName;
  EFI_GUID                                  EntryId;
  CHAR16                                    *EntryName;
  CHAR16                                    *EntryDescription;
  EFI_GUID                                  *SupportProtocols;
  EFI_VERBOSE_LEVEL                         VerboseLevel;

  BOOLEAN                                   IsRecovery;
  UINT32                                    PassCount;
  UINT32                                    WarningCount;
  UINT32                                    FailCount;

  CHAR16                                    *TestCategory;
  CHAR16                                    *DevicePath;

  BOOLEAN                                   BeginLogging;
  EFI_TIME                                  StartTime;
} STANDARD_TEST_PRIVATE_DATA;

#define STANDARD_TEST_PRIVATE_DATA_FROM_STSL(a) \
  CR(a, STANDARD_TEST_PRIVATE_DATA, StandardTest, STANDARD_TEST_PRIVATE_DATA_SIGNATURE)

#define STANDARD_TEST_PRIVATE_DATA_FROM_PI(a)   \
  CR(a, STANDARD_TEST_PRIVATE_DATA, PrivateInterface, STANDARD_TEST_PRIVATE_DATA_SIGNATURE)


EFI_STATUS
MyUINTToStr (
  IN UINTN        Num,
  OUT CHAR16      *StringNum
);

#endif
