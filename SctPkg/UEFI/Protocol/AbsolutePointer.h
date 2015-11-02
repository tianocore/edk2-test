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
                                                                
  Copyright (c) 2010 - 2012, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AbsolutePointer.h

Abstract:

  Absolute Pointer protocol as defined in the UEFI 2.1 specification.

--*/


#ifndef _ABSOLUTE_POINTER_FOR_TEST_H_
#define _ABSOLUTE_POINTER_FOR_TEST_H_

//
// Global ID for the Absolute Pointer Protocol
//
#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
    { 0x8d59d32b, 0xc655, 0x4ae9, { 0x9b, 0x15, 0xf2, 0x59, 0x04, 0x99, 0x2a, 0x43} }

typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;



//******************************************************* 
// EFI_ABSOLUTE_POINTER_STATE 
//******************************************************* 
typedef struct { 
  UINT64 CurrentX; 
  UINT64 CurrentY; 
  UINT64 CurrentZ; 
  UINT32 ActiveButtons; 
} EFI_ABSOLUTE_POINTER_STATE;

//****************************** 
//definitions of bits within ActiveButtons 
//****************************** 
#define EFI_ABSP_TouchActive                  0x00000001 
#define EFI_ABS_AltActive                     0x00000002

//******************************************************* 
// EFI_ABSOLUTE_POINTER_MODE 
//******************************************************* 
typedef struct {
  UINT64 AbsoluteMinX; 
  UINT64 AbsoluteMinY; 
  UINT64 AbsoluteMinZ; 
  UINT64 AbsoluteMaxX; 
  UINT64 AbsoluteMaxY; 
  UINT64 AbsoluteMaxZ; 
  UINT32 Attributes; 
} EFI_ABSOLUTE_POINTER_MODE; 

#define EFI_ABSP_SupportsAltActive                       0x00000001
#define EFI_ABSP_SupportsPressureAsZ                     0x00000002


//
// Prototypes for the Absolute Pointer Protocol
//

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_RESET) (
  IN  EFI_ABSOLUTE_POINTER_PROTOCOL             *This,
  IN  BOOLEAN                                   ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_GET_STATE) (
   IN EFI_ABSOLUTE_POINTER_PROTOCOL               *This, 
   IN OUT EFI_ABSOLUTE_POINTER_STATE               *State 
   );

//
// Interface structure for the Absolute Pointer Protocol
//
struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
  EFI_ABSOLUTE_POINTER_RESET       Reset;
  EFI_ABSOLUTE_POINTER_GET_STATE    GetState;
  EFI_EVENT                         WaitForInput;
  EFI_ABSOLUTE_POINTER_MODE         *Mode;
};

extern EFI_GUID gBlackBoxEfiAbsolutePointerProtocolGuid;



#endif /* _ABSOLUTE_POINTER_FOR_TEST_H_ */
