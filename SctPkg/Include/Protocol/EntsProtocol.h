/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsProtocol.h

Abstract:

--*/

#ifndef _ENTS_PROTOCOL_H_
#define _ENTS_PROTOCOL_H_

#define EFI_ENTS_PROTOCOL_GUID \
  { \
    0x5bfcffb2, 0x84c0, 0x49f0, 0x9a, 0x3a, 0x0, 0x71, 0x5f, 0xec, 0xfb, 0x32 \
  }

extern EFI_GUID gEfiEntsProtocolGuid;

#define ENTS_PROTOCOL_ATTRIBUTE_BOOT_SERVICE                      1
#define ENTS_PROTOCOL_ATTRIBUTE_RUNTIME_SERVICE                   2
#define ENTS_PROTOCOL_ATTRIBUTE_GENERIC_SERVICE                   4
#define ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL                          8
#define ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED  9

typedef
EFI_STATUS
(EFIAPI *ENTS_INTERFACE_ENTRY) (
  IN VOID                      *ClientInterface
  );

typedef struct _ENTS_ARG_FIELD {
  UINTN Type;
  VOID  *Data;
} ENTS_ARG_FIELD;

typedef struct _ENTS_INTERFACE {
  CHAR16                *InterfaceName;
  ENTS_INTERFACE_ENTRY  EntsInterfaceEntry;
  ENTS_ARG_FIELD        *ArgFieldList;
} ENTS_INTERFACE;

typedef struct _EFI_ENTS_PROTOCOL {
  UINTN           Revision;
  VOID            *ClientName;
  UINTN           ClientAttribute;
  EFI_GUID        *ClientGuid;
  EFI_HANDLE      ClientHandle;
  VOID            *ClientInterface;
  ENTS_INTERFACE  *EntsInterfaceList;
  CHAR16          *RuntimeInfo;
  UINTN           RuntimeInfoSize;
} EFI_ENTS_PROTOCOL;

#endif // _ENTS_PROTOCOL_H_
