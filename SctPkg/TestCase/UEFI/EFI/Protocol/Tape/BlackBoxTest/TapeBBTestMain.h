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
                                                                
  Copyright (c) 2010, Phoenix Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TapeBBTestMain.h

Abstract:

  Test Driver of TapeIo Protocol

--*/

#ifndef __EFI_TAPE_TEST_H__
#define __EFI_TAPE_TEST_H__


#include "SctLib.h"

#include <Library/EfiTestLib.h>
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#include "TapeGuid.h"
#include "TapeTest.h"


#define TAPE_TEST_REVISION 0x00010000

#define TAPE_FUNCTION_TEST_GUID \
  {0x5f1ad29a, 0x2e9e, 0x4758, 0xa9, 0x6d, 0x9b, 0xbc, 0x28, 0x46, 0xdd, 0x13 }
  

EFI_STATUS
InitializeTapeTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
UnloadTapeTest (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS getStandardLibInterface( EFI_HANDLE SupportHandle );
    
extern void TapeTestWaitForAnyInput ( void );
extern EFI_STATUS getStandardLibInterface( EFI_HANDLE SupportHandle );

extern EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
extern EFI_TEST_LOGGING_LIBRARY_PROTOCOL	*LoggingLib;

extern EFI_TAPE_IO_PROTOCOL *gTapeIoProtocol;
  
#endif
