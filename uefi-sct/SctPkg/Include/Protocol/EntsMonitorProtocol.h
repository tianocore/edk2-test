/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
