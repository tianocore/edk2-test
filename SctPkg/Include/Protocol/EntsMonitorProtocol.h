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

  EntsMonitorProtocol.h

Abstract:

--*/

#ifndef _ENTS_MONITOR_PROTOCOL_H_
#define _ENTS_MONITOR_PROTOCOL_H_

#define EFI_ENTS_MONITOR_PROTOCOL_GUID \
  { \
    0xf3f93305, 0x57e1, 0x43bf, 0x96, 0x20, 0xf1, 0x4a, 0xb3, 0x31, 0xe2, 0x7d \
  }

extern EFI_GUID gEfiEntsMonitorProtocolGuid;

typedef struct _EFI_ENTS_MONITOR_PROTOCOL EFI_ENTS_MONITOR_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_INIT_MONITOR) (
  IN EFI_ENTS_MONITOR_PROTOCOL           * This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_RESET_MONITOR) (
  IN EFI_ENTS_MONITOR_PROTOCOL           * This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MONITOR_LISTENER) (
  IN     EFI_ENTS_MONITOR_PROTOCOL       * This,
  IN OUT UINTN                           *Size,
  OUT CHAR16                             **Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MONITOR_SENDER) (
  IN EFI_ENTS_MONITOR_PROTOCOL           * This,
  IN CHAR16                              *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MONITOR_VALIDATER) (
  IN EFI_ENTS_MONITOR_PROTOCOL           * This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MONITOR_SAVECONTEXT) (
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MONITOR_RESTORECONTEXT) (
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  );

struct _EFI_ENTS_MONITOR_PROTOCOL {
  VOID                        *MonitorName;
  VOID                        *MonitorIo;
  EFI_INIT_MONITOR            InitMonitor;
  EFI_RESET_MONITOR           ResetMonitor;
  BOOLEAN                     CleanUpEnvironmentFlag;
  EFI_MONITOR_LISTENER        MonitorListener;
  EFI_MONITOR_SENDER          MonitorSender;
  EFI_MONITOR_SAVECONTEXT     MonitorSaveContext;
  EFI_MONITOR_RESTORECONTEXT  MonitorRestoreContext;
};

#endif // _ENTS_MONITOR_PROTOCOL_H_
