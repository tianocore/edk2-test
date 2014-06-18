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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestProfile.h

Abstract:

  Driver to publish the Test Profile Library Protocol.

--*/

#ifndef _EFI_TEST_PROFILE_H_
#define _EFI_TEST_PROFILE_H_

//
// Includes
//

#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

//
// Private Data definition for TestProfileLibrary protocol
//
#define TEST_PROFILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('A','D','V','L')

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         TestProfile;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FilePath;
} TEST_PROFILE_PRIVATE_DATA;

#define TEST_PROFILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, TEST_PROFILE_PRIVATE_DATA, TestProfile, TEST_PROFILE_PRIVATE_DATA_SIGNATURE)

//
// Private Data definition for EFI_INI_FILE interface
//
#define EFI_INI_FILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('I','N','I','F')

#define MAX_STRING_LEN      100
#define MAX_LINE_LEN        512

//
// Forward reference for pure ANSI compatibility
//

typedef struct _INI INI;
typedef struct _COMMENTLINE COMMENTLINE;

struct _INI {
  UINT32                          commentNo;
  CHAR8                           ptrSection[MAX_STRING_LEN + 1];
  CHAR8                           ptrEntry[MAX_STRING_LEN + 1];
  CHAR8                           ptrValue[MAX_STRING_LEN + 1];
  INI                             *ptrNext;
};


struct _COMMENTLINE {
  UINT32                          commentNo;
  CHAR8                           ptrComment[MAX_LINE_LEN];
  COMMENTLINE                     *ptrNext;
};

typedef struct {
  UINT32                          Signature;
  EFI_INI_FILE                    Handle;
  EFI_DEVICE_PATH_PROTOCOL        *DevPath;
  CHAR16                          *FileName;
  INI                             *Head;
  INI                             *Tail;
  COMMENTLINE                     *CommentLineHead;
  BOOLEAN                         isUnicode;
  BOOLEAN                         Modified;
} EFI_INI_FILE_PRIVATE_DATA;

#define EFI_INI_FILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, EFI_INI_FILE_PRIVATE_DATA, Handle, EFI_INI_FILE_PRIVATE_DATA_SIGNATURE)

#endif
