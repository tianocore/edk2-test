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

  TslInit.h

Abstract:

  This file defines the EFI Test Support Library Initiation Interface.

  This interface provides a union format to install, uninstall, and initialize
  the test support library protocols. Using this interface the test management
  system can detect any test support libraries automatically.

--*/

#ifndef _EFI_TSL_INIT_H_
#define _EFI_TSL_INIT_H_

//
// Includes
//

//
// EFI TSL Initiation Interface Definitions
//

#define EFI_TSL_INIT_INTERFACE_GUID       \
  { 0x625c0828, 0xa47d, 0x493d, 0xb7, 0x97, 0x97, 0x85, 0x55, 0x72, 0xdb, 0xc8 }

#define EFI_TSL_INIT_INTERFACE_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TSL_INIT_INTERFACE EFI_TSL_INIT_INTERFACE;

//
// EFI TSL Initiation Interface API - Open
//
typedef
EFI_STATUS
(EFIAPI *EFI_TSL_OPEN) (
  IN     EFI_TSL_INIT_INTERFACE         *This,
  IN OUT EFI_HANDLE                     *LibHandle,
     OUT VOID                           **PrivateInterface
  )
/*++

Routine Description:

  Opens the test support library to get the handle with the public interface
  and the private interface.

Arguments:

  This              - TSL Initiation Interface instance.

  LibHandle         - The pointer to the handle on which the public interface
                      is installed.

  PrivateInterface  - The private interface of the test support library.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI TSL Initiation Interface API - Close
//
typedef
EFI_STATUS
(EFIAPI *EFI_TSL_CLOSE) (
  IN EFI_TSL_INIT_INTERFACE             *This,
  IN EFI_HANDLE                         LibHandle
  )
/*++

Routine Description:

  Closes the test support library to free the public interface.

Arguments:

  This              - TSL Initiation Interface instance.

  LibHandle         - The handle on which the public interface was installed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI TSL Initiation Interface
//

struct _EFI_TSL_INIT_INTERFACE {
  UINT64                                Revision;
  EFI_GUID                              LibraryGuid;
  EFI_TSL_OPEN                          Open;
  EFI_TSL_CLOSE                         Close;
};

//
// Global ID for EFI TSL Initiation Interface
//

extern EFI_GUID gEfiTslInitInterfaceGuid;

#endif
