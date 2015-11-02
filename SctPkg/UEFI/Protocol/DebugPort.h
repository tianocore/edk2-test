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

  DebugPortProtocol.h

Abstract:

--*/


#ifndef _DEBUG_PORT_FOR_TEST_H_
#define _DEBUG_PORT_FOR_TEST_H_

//
// DebugPort protocol {EBA4E8D2-3858-41EC-A281-2647BA9660D0}
//
#define EFI_DEBUGPORT_PROTOCOL_GUID \
  { 0xEBA4E8D2, 0x3858, 0x41EC, 0xA2, 0x81, 0x26, 0x47, 0xBA, 0x96, 0x60, 0xD0 }

extern EFI_GUID  gBlackBoxEfiDebugPortProtocolGuid;

typedef struct _EFI_DEBUGPORT_PROTOCOL EFI_DEBUGPORT_PROTOCOL;;

//
// DebugPort member functions
//
typedef
EFI_STATUS
(EFIAPI *EFI_DEBUGPORT_RESET) (
  IN EFI_DEBUGPORT_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_DEBUGPORT_WRITE) (
  IN EFI_DEBUGPORT_PROTOCOL               *This,
  IN UINT32                               Timeout,
  IN OUT UINTN                            *BufferSize,
  IN VOID                                 *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_DEBUGPORT_READ) (
  IN     EFI_DEBUGPORT_PROTOCOL               *This,
  IN     UINT32                               Timeout,
  IN OUT UINTN                                *BufferSize,
     OUT VOID                                 *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_DEBUGPORT_POLL) (
  IN EFI_DEBUGPORT_PROTOCOL               *This
  );

//
// DebugPort protocol definition
//
struct _EFI_DEBUGPORT_PROTOCOL {
  EFI_DEBUGPORT_RESET                     Reset;
  EFI_DEBUGPORT_WRITE                     Write;
  EFI_DEBUGPORT_READ                      Read;
  EFI_DEBUGPORT_POLL                      Poll;
};

//
// DEBUGPORT variable definitions...
//
#define EFI_DEBUGPORT_VARIABLE_NAME L"DEBUGPORT"
#define EFI_DEBUGPORT_VARIABLE_GUID EFI_DEBUGPORT_PROTOCOL_GUID
#define gBlackBoxEfiDebugPortVariableGuid gEfiDebugPortProtocolGuid

//
// DebugPort device path definitions...
//

#define DEVICE_PATH_MESSAGING_DEBUGPORT EFI_DEBUGPORT_PROTOCOL_GUID
#define gBlackBoxEfiDebugPortDevicePathGuid gEfiDebugPortProtocolGuid

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL                Header;
  EFI_GUID                                Guid;
} DEBUGPORT_DEVICE_PATH;

#endif /* _DEBUG_PORT_FOR_TEST_H_ */

